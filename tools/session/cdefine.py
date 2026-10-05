"""cdefine.py [--apply] SRC NAME ADDR END: a C unit's typed global from the image (PLAN M5/M6).

NAME's declarator comes from its extern in SRC (or a header): its type and dimensions. Its
value is laid out from the image's bytes [ADDR, END) by that type: scalars, pointers (a function
or placed data by name, a string by literal, an image address by `&unk_XXXXXX`), character
arrays as strings, arrays and structs (from struct definitions in SRC, src/rwa/*.h and include/;
unions by their first member; function pointer fields and typedefs as pointers). A declaration
that is `const` at the top loses it everywhere (the image keeps NAME in .data, a const one would
be in .rdata) unless the range is in .rdata. With --apply: the definition goes into SRC's sorted
m5defs block, the match line `_NAME` into its data block, the range into config/splits.txt.
Opaque `RwUInt8 x[]` declarations are left to tools/session/ctable.py."""
import glob
import os
import re
import struct
import sys

sys.path.insert(0, os.path.join(os.path.dirname(os.path.abspath(__file__)), '..'))
sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import m5defs  # noqa: E402
from xbe import Xbe  # noqa: E402

ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
args = sys.argv[1:]
apply = '--apply' in args
args = [a for a in args if a != '--apply']
src, name, lo, hi = args[0], args[1], int(args[2], 16), int(args[3], 16)
image = Xbe(os.path.join(ROOT, 'orig', 'Game_XboxMultiplayer.xbe'))
section = image.section_at(lo)['name']
full = os.path.join(ROOT, src)
srctext = open(full, encoding='utf-8').read()
texts = [srctext] + [open(f, encoding='utf-8', errors='replace').read() for f in
                     glob.glob(os.path.join(ROOT, 'src', 'rwa', '**', '*.h'), recursive=True) +
                     glob.glob(os.path.join(ROOT, 'src', 'rw', '**', '*.h'), recursive=True) +
                     glob.glob(os.path.join(ROOT, 'include', '**', '*.h'), recursive=True)]
placed = {}
for l in open(os.path.join(ROOT, 'config', 'compiled.txt'), encoding='utf-8'):
    q = l.split()
    if len(q) >= 3 and q[0].startswith('0x'):
        placed.setdefault(int(q[0], 16), q[2])
CODE = {'.text', 'BINK', 'XPP', 'D3D', 'DSOUND', 'XGRPH', 'XONLINE', 'XNET', 'WMADEC'}
SCALAR = {'RwInt32': ('i', 4), 'RwUInt32': ('I', 4), 'RwReal': ('f', 4), 'RwInt16': ('h', 2),
          'RwUInt16': ('H', 2), 'RwInt8': ('b', 1), 'RwUInt8': ('B', 1), 'RwChar': ('c', 1),
          'RwBool': ('i', 4), 'int': ('i', 4), 'unsigned int': ('I', 4), 'float': ('f', 4),
          'short': ('h', 2), 'unsigned short': ('H', 2), 'char': ('c', 1), 'unsigned char': ('B', 1),
          'RwUInt64': ('Q', 8), 'RwInt64': ('q', 8), 'double': ('d', 8), 'long': ('i', 4),
          'unsigned long': ('I', 4), 'DWORD': ('I', 4), 'WORD': ('H', 2), 'BYTE': ('B', 1)}
decls = set()


def cname(sym):
    if sym.startswith('_') and not sym.startswith('__'):
        return sym[1:]
    m = re.match(r'^\?(\w+)@@', sym)
    return m.group(1) if m else None


def cstr(raw):
    out = ''
    for ch in raw:
        c = chr(ch)
        out += '\\\\' if c == '\\' else '\\"' if c == '"' else c if 32 <= ch < 127 else '\\%03o' % ch
    return '"' + out + '"'


def pointer(v):
    if v == 0:
        return '0'
    s = image.section_at(v) if v >= 0x10000 else None
    if not s:
        return '(void *)0x%X' % v
    sym = placed.get(v)
    nm = cname(sym) if sym else None
    if s['name'] in CODE:
        nm = nm or 'sub_%06X' % v
        decls.add(('func', nm))
        return nm
    if sym and sym.startswith('??_C@'):
        raw = bytes(image.read(v, 512)).split(b'\0')[0]
        return cstr(raw)
    nm = nm or 'unk_%06X' % v
    decls.add(('data', nm))
    return '&%s' % nm


def typedef_of(t):
    """The underlying type text of a typedef name, or None."""
    for x in texts:
        m = re.search(r'^typedef\s+([^;]*?)\s*\b%s\s*;' % re.escape(t), x, re.M)
        if m and not m.group(1).startswith('struct ' + t):
            return m.group(1)
        m = re.search(r'^typedef\s+[\w\s\*]+\(\s*\*\s*%s\s*\)\s*\(' % re.escape(t), x, re.M)
        if m:
            return 'FUNCPTR'
    return None


def struct_fields(t):
    """[(type text, field name, dims)] of struct T, or None."""
    t = t.replace('struct ', '').strip()
    for x in texts:
        m = re.search(r'^(?:typedef\s+)?struct\s+%s\s*\{' % re.escape(t), x, re.M)
        if not m:
            m = re.search(r'^typedef\s+struct\s*\w*\s*\{', x[0:0], re.M)
        if m:
            d, i = 1, m.end()
            while d and i < len(x):
                d += {'{': 1, '}': -1}.get(x[i], 0)
                i += 1
            body = re.sub(r'/\*.*?\*/', '', x[m.end():i - 1], flags=re.S)
            body = re.sub(r'//[^\n]*', '', body)
            body = re.sub(r'union\s*\{\s*([^;{}]+;)[^{}]*\}\s*\w*\s*;', r'\1', body)
            out = []
            for line in body.split(';'):
                line = ' '.join(line.split())
                if not line:
                    continue
                fp = re.match(r'^(.*?)\(\s*\*\s*(\w+)\s*\)\s*\(.*\)$', line)
                if fp:
                    out.append(('FUNCPTR', fp.group(2), []))
                    continue
                for part in line.split(','):
                    part = part.strip()
                    f = re.match(r'^((?:const\s+|unsigned\s+|signed\s+|struct\s+|volatile\s+)*\w+\s*\**)\s*(\w+)((?:\[\w+\])*)$', part)
                    if f:
                        typ = f.group(1).strip()
                        out.append((typ, f.group(2), [int(d_, 0) if d_.isdigit() or d_.startswith('0x') else macro(d_)
                                                      for d_ in re.findall(r'\[(\w+)\]', f.group(3))]))
                    elif out and re.match(r'^\**\s*\w+((?:\[\w+\])*)$', part):
                        base = re.sub(r'\*', '', out[-1][0]).strip()
                        g = re.match(r'^(\**)\s*(\w+)((?:\[\w+\])*)$', part)
                        out.append((base + ' ' + g.group(1), g.group(2), [int(d_, 0) for d_ in re.findall(r'\[(\w+)\]', g.group(3))]))
                    else:
                        return None
            return out
    return None


def macro(n):
    for x in texts:
        m = re.search(r'^#define\s+%s\s+(\w+)' % re.escape(n), x, re.M)
        if m:
            return int(m.group(1), 0)
    raise ValueError('unknown size %s' % n)


def layout(t):
    """(size, align, emit(raw, off) -> initializer text) for type text T."""
    t = re.sub(r'\bconst\b|\bvolatile\b', '', t).strip()
    t = ' '.join(t.split())
    if t.endswith('*') or t == 'FUNCPTR':
        if re.sub(r'\s', '', t) in ('RwChar*', 'char*'):
            def em(raw, off):
                v = struct.unpack_from('<I', raw, off)[0]
                return pointer(v)
            return 4, 4, em
        return 4, 4, lambda raw, off: pointer(struct.unpack_from('<I', raw, off)[0])
    if t in SCALAR:
        f, s = SCALAR[t]

        def em(raw, off, f=f):
            if f == 'f':
                v = struct.unpack_from('<f', raw, off)[0]
                b = raw[off:off + 4]
                for k in range(10):
                    x = '%.*f' % (k, v)
                    if struct.pack('<f', float(x)) == b:
                        return (x if '.' in x else x + '.0') + 'f'
                return repr(v) + 'f'
            if f == 'd':
                return repr(struct.unpack_from('<d', raw, off)[0])
            if f == 'c':
                return '%d' % struct.unpack_from('<b', raw, off)[0]
            return '%d' % struct.unpack_from('<' + f, raw, off)[0] if f.islower() else \
                '0x%X' % struct.unpack_from('<' + f, raw, off)[0]
        return s, s, em
    td = typedef_of(t)
    if td == 'FUNCPTR':
        return 4, 4, lambda raw, off: pointer(struct.unpack_from('<I', raw, off)[0])
    if td:
        return layout(td)
    fields = struct_fields(t)
    if fields is None:
        raise ValueError('unknown type %s' % t)
    items, off, al = [], 0, 1
    for ft, fn, dims in fields:
        s, a, em = layout(ft)
        n = 1
        for d in dims:
            n *= d
        off = (off + a - 1) // a * a
        items.append((off, s, n, em, dims, ft))
        off += s * n
        al = max(al, a)
    size = (off + al - 1) // al * al

    def emit(raw, base):
        parts = []
        for o, s, n, em, dims, ft in items:
            if dims:
                if re.sub(r'\bconst\b', '', ft).strip() in ('RwChar', 'char') and len(dims) == 1:
                    b = raw[base + o:base + o + n]
                    z = b.split(b'\0')[0]
                    if not any(b[len(z):]):
                        parts.append(cstr(z))
                        continue
                parts.append('{ ' + ', '.join(em(raw, base + o + k * s) for k in range(n)) + ' }')
            else:
                parts.append(em(raw, base + o))
        return '{ ' + ', '.join(parts) + ' }'
    return size, al, emit


ext = None
for x in texts:
    m = re.search(r'^extern\s+([^;\n]*?)\b%s\b\s*((?:\[\w*\])*)\s*;' % re.escape(name), x, re.M)
    if m:
        ext = m
        break
if not ext:
    sys.exit('no extern declaration of %s' % name)
typ = ext.group(1).strip()
dims = re.findall(r'\[(\w*)\]', ext.group(2))
if re.sub(r'\s', '', typ) == 'RwUInt8' and dims == ['']:
    sys.exit('%s is opaque (RwUInt8[]): use tools/session/ctable.py' % name)
el_t = typ
size, al, emit = layout(el_t)
raw = bytes(image.read(lo, hi - lo))
inner = 1
for d in dims[1:]:
    inner *= int(d, 0) if d[:1].isdigit() else macro(d)
if dims:
    first = dims[0]
    count = (int(first, 0) if first[:1].isdigit() else macro(first)) if first else (hi - lo) // (size * inner)
    if count * size * inner > hi - lo:
        sys.exit('%s: %d elements do not fit 0x%X-0x%X' % (name, count, lo, hi))
    cdims = [count] + [int(d, 0) if d[:1].isdigit() else macro(d) for d in dims[1:]]
    char_array = re.sub(r'\bconst\b', '', typ).strip() in ('RwChar', 'char') and len(dims) == 1

    def rec(off, ds):
        if not ds:
            return emit(raw, off)
        step = size
        for d in ds[1:]:
            step *= d
        return '{ ' + ', '.join(rec(off + k * step, ds[1:]) for k in range(ds[0])) + ' }'
    if char_array:
        b = raw[:count]
        z = b.split(b'\0')[0]
        value = cstr(z) if not any(b[len(z):]) else rec(0, cdims)
    else:
        value = '{\n' + ''.join('    %s,\n' % rec(k * size * inner, cdims[1:]) for k in range(count)) + '}'
    declarator = '%s%s' % (name, ''.join('[%s]' % d for d in ([str(count)] + [str(d) for d in cdims[1:]])))
else:
    value = emit(raw, 0)
    declarator = name
in_rdata = section == '.rdata'
dtype = typ if in_rdata else re.sub(r'^const\s+', '', typ) if not typ.rstrip().endswith('*') or typ.startswith('const RwChar') or typ.startswith('const char') \
    else typ
if not in_rdata:
    dtype = re.sub(r'\*\s*const\b', '*', dtype)
    if not dtype.rstrip().endswith('*'):
        dtype = re.sub(r'^const\s+', '', dtype)
definition = '%s %s = %s;' % (dtype.strip(), declarator, value)
definition = definition.replace('* ' + name, '*' + name)
need = []
for kind, d in sorted(decls):
    if re.search(r'\b%s\b' % re.escape(d), srctext) or any(re.search(r'\b%s\s*\(' % re.escape(d), x) for x in texts[1:]):
        continue
    need.append('extern void %s(void);' % d if kind == 'func' else 'extern RwUInt8 %s[];' % d)
print('\n'.join(need))
print(definition)
if apply:
    if not in_rdata:
        # its declarations lose a top-level const (a const global would be in .rdata)
        for f in [full] + glob.glob(os.path.join(ROOT, 'src', 'rwa', '**', '*.[ch]'), recursive=True):
            t = open(f, encoding='utf-8').read()
            n2 = re.sub(r'^(extern\s+)const\s+((?!RwChar\s*\*|char\s*\*)[^;\n*]*\b%s\b)' % re.escape(name), r'\1\2', t, flags=re.M)
            n2 = re.sub(r'^(extern\s+[^;\n]*\*)\s*const\s+(%s\b)' % re.escape(name), r'\1\2', n2, flags=re.M)
            if n2 != t:
                open(f, 'w', encoding='utf-8', newline='\n').write(n2)
    m5defs.insert(full, lo, ('\n'.join(need) + '\n' if need else '') + definition)
    text = open(full, encoding='utf-8').read()
    hdr = "// Its data (PLAN M5): literals, constants and tables where the image has them.\n"
    ml = '// match: _%s @ 0x%08X\n' % (name, lo)
    if hdr in text:
        text = text.replace(hdr, hdr + ml, 1)
    else:
        m = re.search(r'^// match: ', text, re.M)
        text = text[:m.start()] + hdr + ml + '\n' + text[m.start():]
    open(full, 'w', encoding='utf-8', newline='\n').write(text)
    res = []
    for l in open(os.path.join(ROOT, 'config', 'splits.txt'), encoding='utf-8').read().split('\n'):
        p = l.split()
        if len(p) >= 4 and p[0].startswith('0x') and p[3] == '-' and int(p[0], 16) <= lo < int(p[1], 16):
            s0, e0, sec = int(p[0], 16), int(p[1], 16), p[2]
            if lo > s0:
                res.append('0x%08X 0x%08X %-10s -' % (s0, lo, sec))
            res.append('0x%08X 0x%08X %-10s _%s' % (lo, hi, sec, name))
            if hi < e0:
                res.append('0x%08X 0x%08X %-10s -' % (hi, e0, sec))
        else:
            res.append(l)
    open(os.path.join(ROOT, 'config', 'splits.txt'), 'w', encoding='utf-8', newline='\n').write('\n'.join(res))
