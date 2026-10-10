"""Generates port/src/debug/triggerfields.inc: a field table for every trigger
class, for the debug tools' Trigger tab (port/src/debug/trigtools.cpp).

Each class's own members come from its header (include/types/<Class>.h; the
base Trigger's from types/type_44350.h), in declaration order, with the
attribute command that sets each and how it is stored from its
HandleAttributes (src/recovered). The compiler gives the offsets
(offsetof), so the tables follow each build's layout. What each field does
comes from tools/triggerfields_desc.json ({class: {member: [description,
kind or null]}}), where it has been traced; else the header's comment.

    python tools/gen_triggerfields.py
"""
import glob
import io
import json
import os
import re
import sys

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
OUT = os.path.join(ROOT, 'port', 'src', 'debug', 'triggerfields.inc')
DESC = os.path.join(ROOT, 'tools', 'triggerfields_desc.json')

# kind (vf_008) of each class; classes that share a kind are told apart in
# the tab by hand ("view as")
KINDS = {
    'Trigger': 0, 'PlayerTrigger': 1, 'FlakTrigger': 3, 'SectionTrigger': 4, 'SoldierTrigger': 5,
    'DogTrigger': 6, 'VehicleTrigger': 7, 'AnimatedBGTrigger': 8, 'ConfinedAreaTrigger': 9,
    'SoundBankTrigger': 0xA, 'CustomTrigger': 0xB, 'StreamTrigger': 0xC, 'PlaySoundTrigger': 0xD,
    'StreamVolume': 0xE, 'StopSoundStreamTrigger': 0xF, 'AnimPackTrigger': 0x10,
    'SimpleMechanicTrigger': 0x11, 'ParticleTrigger': 0x12, 'ProjectileGeneratorTrigger': 0x13,
    'DestructableObjectTrigger': 0x14, 'MeshSwapDestructableObjectTrigger': 0x16, 'AddTaskTrigger': 0x17,
    'PickupTrigger': 0x18, 'CCESSPoolTrigger': 0x19, 'VehicleEnterExitTrigger': 0x1A,
    'MountedWeaponTrigger': 0x1B, 'StreamClumpTrigger': 0x1C, 'LevelClumpBankParamTrigger': 0x1C,
    'LevelScriptTrigger': 0x1E, 'GimpTrigger': 0x1F, 'LadderTrigger': 0x20, 'ShrimpTrigger': 0x21,
    'PulseZoneTrigger': 0x22, 'GimpVehicleTrigger': 0x23, 'EndLevelTrigger': 0x24, 'FogTrigger': 0x25,
    'cNetSpawnPoint': 0x25, 'PASTrigger': 0x26,
    # the test triggers and the multiplayer kinds share their bases' kinds
    'AnimTestTrigger': 5, 'HitDeathTestTrigger': 5, 'SceneTestTrigger': 5, 'cNetSoldierTrigger': 5,
    'cNetPlayerTrigger': 1, 'cNetPickupTrigger': 0x18,
    'SceneTrigger': -1, 'cNetStaticCamTrigger': -1,
}
# not trigger objects (RenderTrigger is an attribute handler of its own)
SKIP = {'RenderTrigger'}

SCALAR = {
    'RwInt32': 'INT', 'RwUInt32': 'INT', 'int': 'INT', 'unsigned': 'INT', 'RwBool': 'INT', 'long': 'INT',
    'RwReal': 'REAL', 'float': 'REAL', 'RwV3d': 'V3D', 'RwV2d': 'V2D', 'RwRGBA': 'RGBA',
    'RwInt16': 'I16', 'RwUInt16': 'I16', 'short': 'I16',
    'RwInt8': 'BYTE', 'RwUInt8': 'BYTE', 'RwChar': 'BYTE', 'bool': 'BYTE', 'char': 'BYTE',
    'type_3DF8D8_04': 'KEY', 'Trigger_key': 'KEY', 'type_D48D0': 'INT', 'type_439E78_00': 'INT',
}
MATRIX = ('RwMatrixTag', 'RwMatrix')


def read(p):
    return io.open(p, encoding='utf-8', errors='replace').read().replace('\r\n', '\n')


def strip_comment(line):
    i = line.find('//')
    return (line[:i], line[i + 2:].strip()) if i >= 0 else (line, '')


def class_body(text, name):
    m = re.search(r'^(class|struct) %s\s*:\s*public\s+([\w:]+)[^{]*\{' % re.escape(name), text, re.M)
    if not m:
        m = re.search(r'^(class|struct) %s\s*(?::[^{]*)?\{' % re.escape(name), text, re.M)
        base = None
    else:
        base = m.group(2)
    if not m:
        return None, None
    i = m.end()
    depth = 1
    j = i
    while depth and j < len(text):
        if text[j] == '{':
            depth += 1
        elif text[j] == '}':
            depth -= 1
        j += 1
    return text[i:j - 1], base


def int_of(s):
    s = s.strip()
    try:
        return int(s, 0)
    except ValueError:
        return None


class Member:
    def __init__(self, typ, name, count, comment, cond, alias_real=False, bits=None):
        self.typ, self.name, self.count, self.comment, self.cond = typ, name, count, comment, cond
        self.alias_real, self.bits = alias_real, bits or []


DECL = re.compile(r'^\s*(?:const\s+)?((?:struct\s+|class\s+)?[\w:]+)\s*(\*+)?\s*(\w+)\s*(\[[^\]]+\])?\s*(?::\s*\d+)?\s*;\s*$')


def parse_members(body):
    """The data members at the body's top level, unions resolved to one view."""
    lines = body.split('\n')
    out = []
    cond = []
    i = 0
    n = len(lines)

    def skip_function(k):
        # from a line with '(' that opens a body: to its closing brace
        depth = 0
        started = False
        while k < n:
            code, _ = strip_comment(lines[k])
            depth += code.count('{') - code.count('}')
            if '{' in code:
                started = True
            if (started and depth <= 0) or (not started and code.rstrip().endswith(';')):
                return k + 1
            k += 1
        return k

    def collect(k, stop_depth):
        """Members until the brace closing this level; returns (list, next line)."""
        items = []
        while k < n:
            raw = lines[k]
            code, com = strip_comment(raw)
            s = code.strip()
            if s.startswith('#'):
                d = s.split()
                if d[0] in ('#ifdef', '#ifndef') and len(d) > 1:
                    cond.append((d[1], d[0] == '#ifdef'))
                elif d[0] == '#if':
                    cond.append(('(' + ' '.join(d[1:]) + ')', True))
                elif d[0] == '#else' and cond:
                    c = cond.pop()
                    cond.append((c[0], not c[1]))
                elif d[0] == '#endif' and cond:
                    cond.pop()
                k += 1
                continue
            if not s:
                k += 1
                continue
            if s.startswith('}'):
                return items, k + 1
            if s in ('union', 'struct') or re.match(r'^(union|struct)\s*\{?$', s):
                kind = s.split()[0].rstrip('{')
                if '{' not in s:
                    k += 1  # the brace line
                sub, k = collect(k + 1, stop_depth + 1)
                items.append((kind, sub))
                continue
            if s.startswith(('public:', 'private:', 'protected:', 'typedef', 'enum', 'friend', 'using',
                             'static', 'virtual', 'RWS_', 'template', 'inline', 'explicit', '~', 'operator')) \
                    or '(' in s:
                k = skip_function(k)
                continue
            m = DECL.match(code)
            if m:
                typ, ptr, name, arr = m.group(1), m.group(2), m.group(3), m.group(4)
                typ = typ.replace('struct ', '').replace('class ', '')
                # the comment, with its continuation lines
                coms = [com] if com else []
                kk = k + 1
                while kk < n and lines[kk].strip().startswith('//') and com:
                    coms.append(lines[kk].strip()[2:].strip())
                    kk += 1
                count = None
                if arr:
                    count = int_of(arr[1:-1])
                bit = ':' in code.split(name, 1)[1]
                items.append(('decl', Member(('ptr' if ptr else typ), name, count, ' '.join(coms),
                                             list(cond)), bit))
                k += 1
                continue
            k += 1
        return items, k

    items, _ = collect(0, 0)

    def flatten(items):
        res = []
        for it in items:
            if it[0] == 'decl':
                if not it[2]:
                    res.append(it[1])
            elif it[0] == 'struct':
                res.extend(flatten(it[1]))
            elif it[0] == 'union':
                res.extend(resolve_union(it[1]))
        return res

    def resolve_union(alts):
        decls = [a[1] for a in alts if a[0] == 'decl' and not a[2]]
        structs = [a for a in alts if a[0] == 'struct']
        bitstructs = [s for s in structs if any(x[0] == 'decl' and x[2] for x in s[1])]
        # a matrix over named parts: the matrix
        for d in decls:
            if d.typ in MATRIX:
                return [d]
        plain = [s for s in structs if s not in bitstructs]
        if plain:
            sub = flatten(plain[0][1])
            if sub and not all(m.typ in ('RwUInt8', 'RwInt8') and m.count for m in sub):
                return sub
        if decls:
            first = decls[0]
            reals = [d for d in decls if d.typ in ('RwReal', 'float')]
            if first.typ not in ('RwReal', 'float') and reals and first.count is None:
                first.alias_real = True
            if bitstructs:
                first.bits = [x[1].name for x in bitstructs[0][1] if x[0] == 'decl']
            return [first]
        if plain:
            return flatten(plain[0][1])
        return []

    return flatten(items)


def handle_attributes(cls, sources):
    """{base member name (and subscript): [(command, how)]} from the class's HandleAttributes."""
    pat = re.compile(r'\b%s::HandleAttributes\s*\([^)]*\)\s*\{' % re.escape(cls))
    res = {}
    for text in sources:
        m = pat.search(text)
        if not m:
            continue
        i = m.end()
        depth = 1
        j = i
        while depth and j < len(text):
            if text[j] == '{':
                depth += 1
            elif text[j] == '}':
                depth -= 1
            j += 1
        body = text[i:j]
        cases = [(c.start(), c.group(1)) for c in re.finditer(r'\bcase\s+(\w+)\s*:', body)]
        for idx, (pos, cmd) in enumerate(cases):
            end = cases[idx + 1][0] if idx + 1 < len(cases) else len(body)
            seg = body[pos:end]
            num = int_of(cmd)
            if num is None:
                continue
            how = []
            if 'GetAs_RwReal' in seg:
                how.append('a real')
            elif 'GetAs_RwInt32' in seg:
                how.append('an integer')
            elif 'GetAs_RwChar_ptr' in seg:
                how.append('data (a key, a name or a block)')
            for k, v in (('100.0f', 'x100'), ('60.0f', 'x60'), ('1000.0f', 'x1000'), ('0.5f', 'halved'),
                         ('0.0087266462f', 'the cosine of half the angle'), ('cos(', 'a cosine'),
                         ('sub_BD490', 'a block'), ('(bool)', 'a flag')):
                if k in seg and v not in how:
                    how.append(v)
            # an assignment of a negated value (not a comparison with, or a store of, -1)
            if re.search(r'(?<![=!<>])=\s*-\s*(?!\d)[\w(]', seg):
                how.append('negated')
            for t in re.finditer(r'(?<![\w.>])(unk_[0-9A-F]+)(?:_[a-z0-9]+)?(\[\s*\w+\s*\])?(?:\.(unk_[0-9A-F]+)(?:_[a-z0-9]+)?)?\s*(?:[*+\-/|&]?=)(?!=)', seg):
                key = t.group(1) + (t.group(2).replace(' ', '') if t.group(2) else '')
                if t.group(3):
                    key += '.' + t.group(3)
                res.setdefault(key, [])
                if (num, ', '.join(how)) not in res[key]:
                    res[key].append((num, ', '.join(how)))
            for t in re.finditer(r'(?:&|GetCommandData\(\s*)(unk_[0-9A-F]+)\b', seg):
                key = t.group(1)
                res.setdefault(key, [])
                if (num, ', '.join(how)) not in res[key]:
                    res[key].append((num, ', '.join(how)))
    return res


def cstr(s):
    return s.replace('\\', '\\\\').replace('"', '\\"')


def base_name(n):
    return re.sub(r'^(unk_[0-9A-F]+)_[a-z0-9]+$', r'\1', n)


def rows_for(cls, members, attrs, desc):
    out = []
    d = desc.get(cls, {})
    used = set()

    def emit(expr, kind, cmd, text, cond, size=0, label=None):
        lines = []
        for c, pos in cond:
            if c.startswith('('):
                lines.append(('#if %s' if pos else '#if !%s') % c)
            else:
                lines.append(('#ifdef %s' if pos else '#ifndef %s') % c)
        lines.append('    { "%s", offsetof(%s, %s), PF_%s, %d, "%s", %d },'
                     % (cstr(label or expr), cls, expr, kind, cmd, cstr(text), size))
        lines.extend('#endif' for _ in cond)
        out.extend(lines)

    def info(key, typ_kind, comment):
        cmds = attrs.get(key) or attrs.get(base_name(key)) or []
        cmd = cmds[0][0] if cmds else -1
        how = cmds[0][1] if cmds else ''
        extra = ''
        if len(cmds) > 1:
            extra = ' (commands %s)' % ', '.join(str(c[0]) for c in cmds)
        if key in d or base_name(key) in d:
            ent = d.get(key) or d.get(base_name(key))
            text, kind = ent[0], ent[1]
            if cmd < 0 and len(ent) > 2 and ent[2] is not None:
                cmd = ent[2]
            used.add(key)
            used.add(base_name(key))
            return cmd, kind or typ_kind, text
        text = comment
        if how:
            text = ('[%s] ' % how) + text if text else '[%s]' % how
        return cmd, typ_kind, (text + extra).strip()

    for m in members:
        typ = m.typ
        if typ == 'ptr':
            cmd, kind, text = info(m.name, 'RO', m.comment)
            emit(m.name, 'RO', cmd, text or '(a pointer)', m.cond)
            continue
        if typ in MATRIX:
            for part in ('right', 'up', 'at', 'pos'):
                expr = '%s.%s' % (m.name, part)
                cmd, kind, text = info(expr, 'V3D', '')
                out_expr = m.name
                emit_lines = []
                cond = m.cond
                lines = []
                out.append('    { "%s", offsetof(%s, %s) + offsetof(RwMatrixTag, %s), PF_V3D, %d, "%s", 0 },'
                           % (expr, cls, m.name, part, cmd, cstr(text or 'its matrix: ' + part)))
            continue
        # a struct member the descriptions break down
        subs = sorted(k for k in d if k.startswith(m.name + '.'))
        if subs and typ not in SCALAR:
            for k in subs:
                text, kind = d[k][0], d[k][1]
                used.add(k)
                cmd, _, _ = info(k, 'INT', '')
                sub = k.split('.', 1)[1]
                sp = None
                if kind == 'SPREAL':
                    pass
                out.append('    { "%s", offsetof(%s, %s) + offsetof(%s, %s), PF_%s, %d, "%s", 0 },'
                           % (k, cls, m.name, typ, sub, kind or 'INT', cmd, cstr(text)))
            continue
        tk = SCALAR.get(typ)
        if m.count is not None:
            if typ in ('RwChar',) and m.count <= 256:
                cmd, kind, text = info(m.name, 'TEXT', m.comment)
                emit(m.name, kind, cmd, text, m.cond, m.count)
                continue
            elem = ['%s[%d]' % (m.name, i) for i in range(m.count)]
            described = [e for e in elem if e in d] or [e for e in elem if e in attrs]
            if tk == 'BYTE' and not described:
                cmd, kind, text = info(m.name, 'RO', m.comment)
                emit(m.name, 'RO', cmd, text or '(%d bytes)' % m.count, m.cond)
                continue
            if tk is None:
                cmd, kind, text = info(m.name, 'RO', m.comment)
                emit(m.name, 'RO', cmd, '(%s x%d) %s' % (typ, m.count, text), m.cond)
                continue
            for e in elem[:64]:
                cmd, kind, text = info(e, tk, m.comment if e == elem[0] else '')
                if not text and e in d:
                    text = d[e][0]
                emit(e, kind, cmd, text, m.cond)
            continue
        if tk is None:
            cmd, kind, text = info(m.name, 'RO', m.comment)
            emit(m.name, kind if kind != 'INT' else 'RO', cmd, '(%s) %s' % (typ, text), m.cond)
            continue
        if m.alias_real and tk == 'INT':
            tk = 'INTREAL'
        if m.bits:
            tk = 'HEX'
            m.comment = (m.comment + ' bits: ' if m.comment else 'bits: ') + ', '.join(m.bits)
        cmd, kind, text = info(m.name, tk, m.comment)
        if kind == 'SPREAL':
            out.append('#ifdef CODFH_SP')
            emit(m.name, 'REAL', cmd, text, m.cond)
            out.append('#else')
            emit(m.name, 'INTREAL', cmd, text, m.cond)
            out.append('#endif')
            continue
        emit(m.name, kind, cmd, text, m.cond)
    missing = [k for k in d if k not in used]
    if missing:
        sys.stderr.write('%s: descriptions with no member: %s\n' % (cls, ', '.join(missing[:12])))
    return out


def main():
    desc = {}
    if os.path.exists(DESC):
        desc = json.load(io.open(DESC, encoding='utf-8'))
    sources = []
    for p in sorted(glob.glob(os.path.join(ROOT, 'src', 'recovered', '*.cpp'))):
        t = read(p)
        if '::HandleAttributes' in t:
            sources.append(t)
    headers = {}
    for p in glob.glob(os.path.join(ROOT, 'include', 'types', '*.h')):
        headers[os.path.splitext(os.path.basename(p))[0]] = p
    classes = []
    for cls in sorted(KINDS, key=lambda c: (KINDS[c] if KINDS[c] >= 0 else 999, c)):
        if cls in SKIP:
            continue
        hp = os.path.join(ROOT, 'include', 'types', 'type_44350.h') if cls == 'Trigger' else headers.get(cls)
        if not hp:
            sys.stderr.write('no header for %s\n' % cls)
            continue
        body, base = class_body(read(hp), cls)
        if body is None:
            sys.stderr.write('no class %s in %s\n' % (cls, hp))
            continue
        classes.append((cls, hp, body, base))

    out = ['// Generated by tools/gen_triggerfields.py: every trigger class\'s own fields, with',
           '// the attribute command that sets each and what it does (tools/triggerfields_desc.json,',
           '// else the header\'s comment; [how] when only the storage is known). For trigtools.cpp.',
           '']
    incs = []
    for cls, hp, body, base in classes:
        if cls != 'Trigger':
            incs.append('#include "types/%s.h"' % os.path.splitext(os.path.basename(hp))[0])
    out.extend(sorted(set(incs)))
    out.append('')
    table = []
    for cls, hp, body, base in classes:
        members = parse_members(body)
        attrs = handle_attributes(cls, sources)
        rows = rows_for(cls, members, attrs, desc)
        if not rows:
            rows = ['    { "(no fields of its own)", 0, PF_RO, -1, "", 0 },']
        out.append('static const PgField s_aTF_%s[] =' % cls)
        out.append('{')
        out.extend(rows)
        out.append('};')
        out.append('')
        table.append('    { "%s", %d, "%s", s_aTF_%s, sizeof(s_aTF_%s) / sizeof(s_aTF_%s[0]) },'
                     % (cls, KINDS[cls], base or '', cls, cls, cls))
    out.append('static const TrigFieldClass s_aTrigFieldClasses[] =')
    out.append('{')
    out.extend(table)
    out.append('};')
    out.append('')
    s = '\n'.join(out)
    old = io.open(OUT, encoding='utf-8').read() if os.path.exists(OUT) else ''
    if s != old.replace('\r\n', '\n'):
        io.open(OUT, 'w', encoding='utf-8', newline='\r\n').write(s)
    print('%d classes, %d rows -> %s' % (len(classes), s.count('offsetof('), os.path.relpath(OUT, ROOT)))


if __name__ == '__main__':
    main()
