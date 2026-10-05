"""vtoverride.py [--apply]: add the trivial virtual overrides the recovered classes miss (PLAN M5).

A vtable slot the image fills with a trivial function other than the one its base's vtable holds
(the classic checked downcasts: the base returns 0, the class itself returns this) is an override
the recovered class does not declare, so its compiled vtable names the base's function. For each
such slot whose image function is a known trivial body (ICF folded them all into one address
each), the override goes into the class that introduces it (the most-base class among those with
that slot value), defined in the class with that body. The base name's alias is corrected when it
holds an override's address. Then build, and tools/session/vtplace.py aliases the new names to the
folded addresses and places the vtables."""
import collections
import glob
import os
import re
import struct
import sys

sys.path.insert(0, os.path.join(os.path.dirname(os.path.abspath(__file__)), '..'))
import match  # noqa: E402
from coff import Coff, IMAGE_REL_I386_DIR32  # noqa: E402
from xbe import Xbe  # noqa: E402

ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
apply = '--apply' in sys.argv
image = Xbe(match.ORIGINAL)
# folded trivial bodies: address -> (body, argument bytes popped)
TRIVIAL = {0x6FCD0: ('return this;', 0), 0x1E4CB0: ('return 0;', 0), 0x32260: ('return 0;', 4),
           0x1F5A00: ('return 1;', 4), 0x15FB30: ('', 4), 0x9E000: ('return 4;', 0),
           0x1E4AA0: ('return false;', 0), 0x1E41C0: ('', 0)}
ANY = '--any' in sys.argv   # copy any short body (tools/session/vtplace.py checks its bytes)

rows = []
for l in open(os.path.join(ROOT, 'config', 'compiled.txt'), encoding='utf-8'):
    q = l.split()
    if len(q) >= 3 and q[0].startswith('0x'):
        rows.append((int(q[0], 16), q[1], q[2]))
placed_name = {}
for a, o, n in rows:
    placed_name.setdefault(n, a)
objs = {}


def coff(o):
    if o not in objs:
        objs[o] = Coff(os.path.join(ROOT, o))
    return objs[o]


vts = {}
for a, o, n in rows:
    if n.startswith('??_7') and 'build/src/' in o:
        vts[(n, a)] = o
for a, o, n in rows:
    if 'build/src/' not in o or o.startswith('build/src/xdk'):
        continue
    try:
        c = coff(o)
        code, relocs = c.function_bytes(c.find_function(n))
    except Exception:
        continue
    orig = image.read(a, len(code))
    for off, t, rt in relocs:
        if t.startswith('??_7') and rt == IMAGE_REL_I386_DIR32:
            enc = struct.unpack_from('<I', orig, off)[0] - struct.unpack_from('<i', code, off)[0]
            vts.setdefault((t, enc), o)
votes = collections.defaultdict(lambda: collections.defaultdict(set))
for (vt, addr), o in vts.items():
    s = coff(o).find_function(vt)
    if s is None:
        continue
    code, relocs = coff(o).function_bytes(s)
    img = image.read(addr, len(code))
    m = re.match(r'^\?\?_7(\w+)@', vt)
    if not m:
        continue
    for off, t, rt in relocs:
        v = struct.unpack_from('<I', img, off)[0] - struct.unpack_from('<i', code, off)[0]
        votes[t][v].add(m.group(1))

H = {}
for h in glob.glob(os.path.join(ROOT, 'include', '**', '*.h'), recursive=True):
    H[h] = open(h, encoding='utf-8', errors='replace').read()
parent = {}
for h, t in H.items():
    for m in re.finditer(r'^(?:struct|class) (\w+)\s*:\s*([^{;]+)\{', t, re.M):
        parent[m.group(1)] = [b.replace('public', '').replace('virtual', '').strip().split('::')[-1]
                              for b in m.group(2).split(',')]


def ancestors(c):
    out, todo_ = [], list(parent.get(c, []))
    while todo_:
        b = todo_.pop()
        if b not in out:
            out.append(b)
            todo_ += parent.get(b, [])
    return out


def struct_span(cls):
    """(header, start of the struct's body, index of its closing `};`)."""
    for h, t in H.items():
        m = re.search(r'^(?:struct|class) %s\b[^;{]*\{' % cls, t, re.M)
        if not m:
            continue
        depth, i = 1, m.end()
        while depth and i < len(t):
            if t[i] == '{':
                depth += 1
            elif t[i] == '}':
                depth -= 1
            i += 1
        return h, m.end(), i - 1
    return None


def declaration(cls, meth):
    # the class's own declaration, else the nearest ancestor's
    for c in [cls] + ancestors(cls):
        sp = struct_span(c)
        if not sp:
            continue
        h, s, e = sp
        m = re.search(r'^\s*(virtual [^;{]*\b%s\s*\([^;{]*\))\s*(;|\{)' % meth, H[h][s:e], re.M)
        if m:
            return m.group(1)
    return None


def aliases_fix(name, addr):
    p = os.path.join(ROOT, 'config', 'aliases.txt')
    t = open(p, encoding='utf-8').read()
    m = re.search(r'^%s\s+0x([0-9A-Fa-f]+)\b.*$' % re.escape(name), t, re.M)
    if m and int(m.group(1), 16) != addr:
        t = t[:m.start()] + '%s 0x%08X  # the base\'s own (its vtable); overrides return elsewhere (vtoverride.py)' % (
            name, addr) + t[m.end():]
        open(p, 'w', encoding='utf-8', newline='\n').write(t)
        return True
    return False


SRC = None


def simple_body(addr):
    """The one statement of the placed function at ADDR when it is a field get or set or a
    forward to another virtual (`return unk_68;`, `unk_68 = arg_0;`, `return vf_06C(arg_0);`)."""
    global SRC
    sym = next((n for a, o, n in rows if a == addr and 'build/src/' in o), None)
    m = re.match(r'^\?(\w+)@(\w+)@@', sym or '')
    if not m:
        return None
    if SRC is None:
        SRC = [open(f, encoding='utf-8', errors='replace').read()
               for f in glob.glob(os.path.join(ROOT, 'src', '**', '*.cpp'), recursive=True)]
    pat = re.compile(r'^[^\n;]*\b%s::%s\(([^)]*)\)( const)?\n\{\n(    [^\n;]*;\n)?\}' % (m.group(2), m.group(1)), re.M)
    multi = re.compile(r'^[^\n;]*\b%s::%s\(([^)]*)\)( const)?\n\{\n(.*?)\n\}\n' % (m.group(2), m.group(1)),
                       re.M | re.S)
    for t in SRC:
        d = multi.search(t)
        if d and d.group(3).count('\n') < 8:
            body = d.group(3)
            code = re.sub(r'"(\\.|[^"])*"', '""', body)
            bare = re.findall(r'(?<![\w>.:])\b(unk_\w+|get_\w+|sub_\w+|vf_\w+|this)\b', code)
            if ANY or (not bare and not re.search(r'^\s*\w[\w\s*]*\s\w+\s*(\[|;|=)', code, re.M)):
                # only its arguments (and globals): the same code in any class; no locals
                return '\n'.join(l[4:] if l.startswith('    ') else l for l in body.split('\n'))
        d = pat.search(t)
        if d:
            if d.group(3) is None:
                return ''   # an empty body
            st = d.group(3).strip()
            if re.match(r'^(return \(?[\w *]*\)?unk_[0-9A-F]+(_\w+)?;|unk_[0-9A-F]+ = arg_0;|'
                        r'(return )?(\w+::)?vf_[0-9A-F]+\(((arg_\w+|pMsg)(, )?)*\);|return -?(0x[0-9A-F]+|\d+);|'
                        r'(\w+::)+\w+\(((arg_\w+|pMsg)(, )?)*\);)$', st):
                return st
    return None


todo = collections.defaultdict(list)   # class -> [(method, body, base class, folded address)]
for name, by in votes.items():
    mm = re.match(r'^\?(\w+)@(\w+)@(?:\w+@)?@', name)
    if not mm or len(by) < 2:
        continue
    meth, base = mm.group(1), mm.group(2)
    own = [v for v, cs in by.items() if base in cs]
    ab = own[0] if own else max(by, key=lambda v: len(by[v]))
    for v, cs in by.items():
        if v == ab:
            continue
        body = TRIVIAL[v][0] if v in TRIVIAL else simple_body(v)
        if body is None:
            continue
        intro = [c for c in cs if not set(ancestors(c)) & (cs - {c})]
        for c in intro:
            todo[c].append((meth, body, base, v, name, ab))
added = 0
for cls, items in sorted(todo.items()):
    for meth, body, base, v, name, ab in items:
        decl = declaration(base, meth)
        sp = struct_span(cls)
        if not decl or not sp:
            print('%s::%s: %s' % (cls, meth, 'no base declaration' if not decl else 'no struct'))
            continue
        h, s, e = sp
        ret = re.match(r'^virtual\s+(.*?)\b%s\s*\(' % meth, decl).group(1).strip()
        if body == 'return this;' and not ret.endswith('*'):
            if ret in ('RwInt32', 'RwUInt32'):
                body = 'return (%s)this;' % ret
            else:
                print('%s::%s: returns %s, not a pointer (its declaration is wrong)' % (cls, meth, ret or 'void'))
                continue
        if ret == 'void' and body.startswith('return '):
            print('%s::%s: void, but its body returns (its declaration is wrong)' % (cls, meth))
            continue
        if re.search(r'\b%s\s*\(' % meth, H[h][s:e]):
            print('%s::%s already declared' % (cls, meth))
            continue
        text = '    // %s, as the image\'s vtable has it (a trivial body, folded into\n' \
               '    // sub_%X with every other copy).\n    %s\n    {\n%s    }\n' % (
                   meth, v, decl, ''.join(('        %s' % l).rstrip() + '\n' for l in body.split('\n')) if body else '')
        print('%s: %s -> sub_%X' % (cls, decl, v))
        added += 1
        if apply:
            H[h] = H[h][:e] + text + H[h][e:]
            open(h, 'w', encoding='utf-8', newline='\n').write(H[h])
            if aliases_fix(name, ab):
                print('  alias of %s -> 0x%X' % (name, ab))
print(added, 'overrides')
