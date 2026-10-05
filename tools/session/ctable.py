"""ctable.py [--apply] SRC NAME ADDR END: define a C unit's data table from the image (PLAN M5/M6).

For the C units (src/rwa, src/rw) whose recovered sources declare their tables opaquely
(`extern RwUInt8 unk_42E1C8[];`). The bytes [ADDR, END) become NAME, typed by what they hold:
- every dword a float (and none an image address): `RwReal NAME[n]`;
- else `void *NAME[n]`, a slot per dword: a function's address as its placed name, an address of
  placed data as `&name` (or `(void *)&unk_XXXXXX`, which the placement link resolves by address),
  anything else as `(void *)0xN`.
Words and bytes are kept inside the dwords (the table's own layout is not recovered: its bytes and
relocations are). With --apply the definition goes into SRC's sorted m5defs block, SRC's extern
declarations of NAME are changed to the same type, the match line `_NAME` goes into its data
block and the range into config/splits.txt."""
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
placed = {}
for l in open(os.path.join(ROOT, 'config', 'compiled.txt'), encoding='utf-8'):
    q = l.split()
    if len(q) >= 3 and q[0].startswith('0x'):
        placed.setdefault(int(q[0], 16), q[2])
inside = []   # placed data items (config/splits.txt), for pointers into them
for l in open(os.path.join(ROOT, 'config', 'splits.txt'), encoding='utf-8'):
    p = l.split()
    if len(p) >= 4 and p[0].startswith('0x') and p[3] != '-' and p[2] in ('.rdata', '.data'):
        inside.append((int(p[0], 16), int(p[1], 16), p[3]))
code_secs = {'.text', 'BINK', 'XPP', 'D3D', 'DSOUND', 'XGRPH', 'XONLINE', 'XNET', 'WMADEC'}


def cname(sym):
    """A placed symbol's C name: `_sub_X` -> sub_X, `?f@@...` -> f."""
    if sym.startswith('_') and not sym.startswith('__'):
        return sym[1:]
    m = re.match(r'^\?(\w+)@@', sym)
    return m.group(1) if m else None


n = (hi - lo) // 4
vals = struct.unpack('<%dI' % n, bytes(image.read(lo, 4 * n)))
tail = bytes(image.read(lo + 4 * n, hi - lo - 4 * n))
decls = set()


def slot(v):
    s = image.section_at(v) if v >= 0x10000 else None
    if not s:
        return '(void *)0x%X' % v if v else '0'
    sym = placed.get(v)
    nm = cname(sym) if sym else None
    if s['name'] in code_secs:
        if nm:
            decls.add(('func', nm))
            return '(void *)%s' % nm
        # not a placed function's start: a number that falls in code (192000 = 0x2EE00), in
        # decimal (the source audit takes hex in code's range for an address)
        return '(void *)%d' % v
    if nm:
        decls.add(('data', nm))
        return '(void *)&%s' % nm
    # inside a placed item (an entry of another table): an offset from it
    for s0, e0, n0 in inside:
        if s0 < v < e0:
            inner = cname(n0)
            if inner:
                decls.add(('data', inner))
                return '(void *)((RwUInt8 *)&%s + 0x%X)' % (inner, v - s0)
    decls.add(('data', 'unk_%06X' % v))
    return '(void *)&unk_%06X' % v


def is_float(v):
    f = struct.unpack('<f', struct.pack('<I', v))[0]
    return v != 0 and 1e-6 < abs(f) < 1e7 and not image.section_at(v)


SCALAR = {'RwInt32': '<i', 'RwUInt32': '<I', 'RwReal': '<f', 'RwInt16': '<h', 'RwUInt16': '<H',
          'RwInt8': '<b', 'RwUInt8': '<B', 'RwChar': '<b', 'RwBool': '<i'}
srctext = open(os.path.join(ROOT, src), encoding='utf-8').read()
old = re.search(r'^extern\s+(?:volatile\s+)?(\w+)\s+%s\s*(\[[^\]]*\])?\s*;' % re.escape(name), srctext, re.M)
typed = old and old.group(1) in SCALAR and not (old.group(1) == 'RwUInt8' and old.group(2) is not None
                                                and old.group(2).strip('[]') == '')
if typed:
    # the unit uses it as a scalar (or an array of them): keep its type, values by element
    t = old.group(1)
    fmt = SCALAR[t]
    size = struct.calcsize(fmt)
    raw = bytes(image.read(lo, hi - lo))
    if len(raw) % size:
        sys.exit('0x%X-0x%X: not whole %s elements' % (lo, hi, t))
    els = struct.unpack('<%d%s' % (len(raw) // size, fmt[1]), raw)

    def fmtv(v):
        if t == 'RwReal':
            for k in range(10):
                s_ = '%.*f' % (k, v)
                if struct.pack('<f', float(s_)) == struct.pack('<f', v):
                    return s_ + 'f'
            return repr(v) + 'f'
        return '%d' % v
    if old.group(2) is not None:
        definition = '%s %s[%d] =\n{\n%s\n};' % (t, name, len(els), '\n'.join('    %s,' % fmtv(v) for v in els))
    elif len(els) == 1:
        definition = '%s %s = %s;' % (t, name, fmtv(els[0]))
    else:
        sys.exit('%s is declared a scalar but 0x%X-0x%X holds %d of them' % (name, lo, hi, len(els)))
    ext = [old.group(0)]
    print(definition)
    if not apply:
        sys.exit(0)
    full = os.path.join(ROOT, src)
    m5defs.insert(full, lo, definition)
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
    sys.exit(0)
if tail:
    sys.exit('0x%X-0x%X: not a whole number of dwords' % (lo, hi))
if all(is_float(v) or v == 0 for v in vals) and any(is_float(v) for v in vals):
    def fl(v):
        for k in range(10):
            t = '%.*f' % (k, struct.unpack('<f', struct.pack('<I', v))[0])
            if struct.pack('<f', float(t)) == struct.pack('<I', v):
                return t + 'f'
        return repr(struct.unpack('<f', struct.pack('<I', v))[0]) + 'f'
    ctype = 'RwReal'
    body = ', '.join(fl(v) for v in vals)
else:
    ctype = 'void *'
    body = ', '.join(slot(v) for v in vals)
# one slot per line keeps long tables readable
items = body.split(', ')
if image.section_at(lo)['name'] == '.rdata':
    # a constant table: in .rdata only when const
    ctype = ctype + 'const ' if ctype.endswith('*') else 'const ' + ctype
definition = '%s%s%s[%d] =\n{\n%s\n};' % (ctype, '' if ctype.endswith(('*', ' ')) else ' ', name, n,
                                         '\n'.join('    %s,' % it for it in items))
ext = ['extern %s%s%s[];' % (ctype, '' if ctype.endswith('*') else ' ', name)]
for kind, d in sorted(decls):
    if kind == 'func':
        ext.append('extern void %s(void);' % d)
    else:
        ext.append('extern RwUInt8 %s[];' % d)
print('\n'.join(ext))
print(definition)
if apply:
    full = os.path.join(ROOT, src)
    text = open(full, encoding='utf-8').read()
    # the unit's own declarations of NAME take the new type
    text = re.sub(r'^extern [^;\n]*\b%s\b[^;\n]*;[^\n]*\n' % re.escape(name), '', text, flags=re.M)
    open(full, 'w', encoding='utf-8', newline='\n').write(text)
    need = []
    for kind, d in sorted(decls):
        if re.search(r'\b%s\b' % re.escape(d), text):
            continue
        need.append('extern void %s(void);' % d if kind == 'func' else 'extern RwUInt8 %s[];' % d)
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
