"""Generates port/src/debug/aifields.inc: field tables for an AI's whole state, for the live
link's full AI view (port/src/debug/trigdraw.cpp, the web suite's level viewer): AIData (the AI
object), and the entity classes a soldier is made of, type_3D3548 (every entity), type_3D32F8
and type_3DAFC8 (the soldier).

Each class's own members come from its header, in declaration order (gen_triggerfields.py's
parser), with their comments. A member whose type is a struct defined in include/ is expanded
into its members ("unk_F80[3].unk_02"), two levels down, arrays of structs up to 64 elements;
anything else not a scalar is shown as raw words. The compiler gives the offsets (offsetof) and
sizes, so the tables follow each build's layout.

What each member does comes from tools/aifields_desc.json where it has been traced ({key:
{"name", "desc", "kind", "bits", "values", "evidence", "confidence"}}; the key is the member's
name for AIData's own members, "<type>.<member>" for a record type's or another class's), else
the header's comment.

    python tools/gen_aifields.py
"""
import glob
import json
import os
import re
import sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import gen_triggerfields as g  # noqa: E402

ROOT = g.ROOT
OUT = os.path.join(ROOT, 'port', 'src', 'debug', 'aifields.inc')
DESC = os.path.join(ROOT, 'tools', 'aifields_desc.json')
DESCS = {}
# a traced kind for the table's kinds
TRACED_KIND = {'int': 'INT', 'uint': 'UINT', 'flags': 'UINT', 'real': 'REAL', 'intreal': 'INTREAL', 'bool': 'INT',
               'enum': 'INT', 'handle': 'HANDLE', 'ptr': 'PTR'}

# the classes, with the header that defines each
CLASSES = [
    ('AIData', 'include/types/AIData.h'),
    ('type_3D3548', 'include/types/type_3D3548.h'),
    ('type_3D32F8', 'include/types/type_3D32F8.h'),
    ('type_3DAFC8', 'include/types/type_3DAFC8.h'),
]
# members not expanded (another table covers them, or they are the class itself)
NO_EXPAND = {'AIData', 'type_3D3548', 'type_3D32F8', 'type_3DAFC8'}

KIND = {
    'RwInt32': 'INT', 'int': 'INT', 'long': 'INT', 'RwBool': 'INT',
    'RwUInt32': 'UINT', 'unsigned': 'UINT',
    'RwReal': 'REAL', 'float': 'REAL',
    'RwInt16': 'I16', 'short': 'I16', 'RwUInt16': 'U16',
    'RwInt8': 'I8', 'RwUInt8': 'U8', 'RwChar': 'U8', 'bool': 'U8', 'char': 'U8',
    'RwV3d': 'V3D', 'RwV2d': 'V2D', 'RwRGBA': 'RGBA', 'RwMatrix': 'MATRIX', 'RwMatrixTag': 'MATRIX',
    'type_D48D0': 'HANDLE', 'type_439E78_00': 'HANDLE', 'type_3DF8D8_04': 'KEY',
    'ptr': 'PTR',
}

STRUCTS = {}


def index_structs():
    for path in glob.glob(os.path.join(ROOT, 'include', '**', '*.h'), recursive=True):
        text = g.read(path)
        for m in re.finditer(r'^(?:struct|class)\s+(\w+)\s*(?::[^{;]*)?\{', text, re.M):
            STRUCTS.setdefault(m.group(1), path)


def members_of(name):
    path = STRUCTS.get(name)
    if path is None:
        return None
    body, _ = g.class_body(g.read(path), name)
    if body is None:
        return None
    return g.parse_members(body)


def cstr(s):
    return s.replace('\\', '\\\\').replace('"', '\\"')[:300]


def traced(owner, name):
    """The traced description of member name of the type owner (AIData's own by name)."""
    return DESCS.get('%s.%s' % (owner, name)) or (DESCS.get(name) if owner == 'AIData' else None)


def extra_of(d, bits):
    """The row's extra text: the traced bits and values ("4=..|9=..", "v:6=..|7=.."), else the bit names."""
    if d and d.get('bits'):
        return '|'.join('%s=%s' % (k, v) for k, v in sorted(d['bits'].items(), key=lambda kv: int(kv[0], 0)))
    if d and d.get('values'):
        return 'v:' + '|'.join('%s=%s' % (k, v) for k, v in sorted(d['values'].items(), key=lambda kv: int(kv[0], 0)))
    return bits


def rows(cls, prefix, expr, members, depth, out, owner=None):
    """Rows for members (of the type owner), their offsets as offsetof(cls, expr...)."""
    owner = owner or cls
    for m in members:
        path = (prefix + '.' if prefix else '') + m.name
        acc = (expr + '.' if expr else '') + m.name
        guard = [('#ifdef %s' if on else '#ifndef %s') % c if not c.startswith('(') else '#if %s' % c
                 for c, on in m.cond]
        for line in guard:
            out.append(line)
        kind = 'INTREAL' if m.alias_real and KIND.get(m.typ) in ('INT', 'UINT') else KIND.get(m.typ)
        d = traced(owner, m.name)
        bits = cstr(extra_of(d, ','.join(m.bits)))
        desc = cstr(d['desc'] if d and d.get('desc') else m.comment)
        label = cstr(d.get('name', '') if d else '')
        if d and d.get('kind') in TRACED_KIND and kind in ('INT', 'UINT', 'REAL', 'INTREAL', 'HANDLE', 'PTR'):
            kind = TRACED_KIND[d['kind']]
        sub = None
        if kind is None and depth < 2 and m.typ not in NO_EXPAND:
            sub = members_of(m.typ)
        if kind is not None:
            if m.bits and kind in ('INT', 'UINT'):
                kind = 'UINT'
            out.append('    { "%s", offsetof(%s, %s), AF_%s, %d, sizeof(((%s *)0)->%s), "%s", "%s", "%s" },'
                       % (path, cls, acc, kind, m.count or 1, cls, acc, desc, bits, label))
        elif sub:
            n = m.count or 1
            if m.count:
                out.append('    { "%s", offsetof(%s, %s), AF_GROUP, %d, sizeof(((%s *)0)->%s), "%s", "%s", "%s" },'
                           % (path, cls, acc, n, cls, acc, desc, m.typ, label))
                for i in range(min(n, 64)):
                    rows(cls, '%s[%d]' % (path, i), '%s[%d]' % (acc, i), sub, depth + 1, out, m.typ)
            else:
                out.append('    { "%s", offsetof(%s, %s), AF_GROUP, 1, sizeof(((%s *)0)->%s), "%s", "%s", "%s" },'
                           % (path, cls, acc, cls, acc, desc, m.typ, label))
                rows(cls, path, acc, sub, depth + 1, out, m.typ)
        else:
            out.append('    { "%s", offsetof(%s, %s), AF_RAW, %d, sizeof(((%s *)0)->%s), "%s", "%s", "%s" },'
                       % (path, cls, acc, m.count or 1, cls, acc, desc, cstr(m.typ), label))
        for _ in guard:
            out.append('#endif')


def main():
    index_structs()
    if os.path.exists(DESC):
        with open(DESC, encoding='utf-8') as f:
            DESCS.update(json.load(f))
    out = ['// Generated by tools/gen_aifields.py: the full AI view\'s field tables (trigdraw.cpp).',
           '// Each row: the member\'s path, offset, kind, count (an array\'s), size, the header\'s',
           '// comment or traced description, the bits ("n=meaning|..", or the bit members\' names) or',
           '// values ("v:n=meaning|..") or the type (AF_GROUP, AF_RAW), and the traced readable name.', '']
    tables = []
    for cls, header in CLASSES:
        body, _ = g.class_body(g.read(os.path.join(ROOT, header)), cls)
        if body is None:
            sys.exit('no %s in %s' % (cls, header))
        lines = []
        rows(cls, '', '', g.parse_members(body), 0, lines)
        out.append('static const AiField s_aAiFields_%s[] =' % cls)
        out.append('{')
        out.extend(lines)
        out.append('};')
        out.append('')
        tables.append(cls)
    out.append('static const AiFieldClass s_aAiFieldClasses[] =')
    out.append('{')
    for cls in tables:
        out.append('    { "%s", s_aAiFields_%s, sizeof(s_aAiFields_%s) / sizeof(s_aAiFields_%s[0]), sizeof(%s) },'
                   % (cls, cls, cls, cls, cls))
    out.append('};')
    with open(OUT, 'w', encoding='utf-8', newline='\n') as f:
        f.write('\n'.join(out) + '\n')
    n = sum(1 for line in out if line.startswith('    { "') and 'offsetof' in line)
    print('%s: %d classes, %d rows' % (os.path.relpath(OUT, ROOT), len(tables), n))


if __name__ == '__main__':
    main()
