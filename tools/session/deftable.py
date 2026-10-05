"""deftable.py [--apply] UNIT 'DECLARATOR' MANGLED ADDR SPEC COUNT: define a data table from the
image's bytes (PLAN M5).

DECLARATOR is the C text before ` = ` (`const RwChar *Str2[5]`, `type_428E80 dword_428E80[10]`),
MANGLED the decorated name the code references (the match line's), SPEC the fields of one
element, comma-separated:
  s  pointer to a string literal       f  float          i  int32     u  uint32
  h  int16 (H unsigned)   b  int8 (B unsigned)   p  pointer, written as the name placed there
  (`&name`, or a function's name; 0 as 0)   x  pointer kept as a number   z  4 zero bytes (0)
COUNT elements; an element with one field is written bare, several in braces. With --apply the
definition goes into the unit's sorted m5defs block, its match line into the data block and its bytes get
their own config/splits.txt range."""
import os
import re
import struct
import subprocess
import sys

sys.path.insert(0, os.path.join(os.path.dirname(os.path.abspath(__file__)), '..'))
from coff import Coff  # noqa: E402
from xbe import Xbe  # noqa: E402
sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import m5defs  # noqa: E402

ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
args = sys.argv[1:]
apply = '--apply' in args
args = [a for a in args if a != '--apply']
unit, decl, mangled, addr, spec, count = args[0], args[1], args[2], int(args[3], 16), args[4].split(','), int(args[5])
src = unit if os.path.exists(os.path.join(ROOT, unit)) else os.path.join('src', 'recovered', unit + '.cpp')
image = Xbe(os.path.join(ROOT, 'orig', 'Game_XboxMultiplayer.xbe'))
SIZES = {'s': 4, 'f': 4, 'i': 4, 'u': 4, 'p': 4, 'x': 4, 'z': 4, 'h': 2, 'H': 2, 'b': 1, 'B': 1}
placed = {}
for l in open(os.path.join(ROOT, 'config', 'compiled.txt'), encoding='utf-8'):
    q = l.split()
    if len(q) >= 3 and q[0].startswith('0x'):
        placed.setdefault(int(q[0], 16), (q[1], q[2]))


def cstr(a):
    b = bytes(image.read(a, 512)).split(b'\0')[0]
    r = ''
    for ch in b:
        c = chr(ch)
        if c == '\\':
            r += '\\\\'
        elif c == '"':
            r += '\\"'
        elif 32 <= ch < 127:
            r += c
        else:
            r += '\\%03o' % ch   # octal: a hex escape would swallow a following hex digit
    return '"' + r + '"'


def float_lit(bits):
    v = struct.unpack('<f', struct.pack('<I', bits))[0]
    if abs(v) < 1e7:
        for k in range(0, 10):
            s = '%.*f' % (k, v)
            if struct.pack('<f', float(s)) == struct.pack('<I', bits):
                return (s if '.' in s else s + '.0') + 'f'
    for d in range(1, 10):
        s = '%.*g' % (d, v)
        if struct.pack('<f', float(s)) == struct.pack('<I', bits):
            return s + 'f'
    return repr(v) + 'f'


def pname(a):
    if a == 0:
        return '0'
    if a in placed:
        path, name = placed[a]
        sym = Coff(os.path.join(ROOT, path)).find_function(name)['name']
        m = re.match(r'^\?(\w+)@@', sym)
        base = m.group(1) if m else sym.lstrip('_')
        code = image.section_at(a)['name'] not in ('.rdata', '.data')
        return base if code else '&' + base
    return '(void *)0x%08X' % a


elems = []
a = addr
for n in range(count):
    fields = []
    for k in spec:
        size = SIZES[k]
        raw = bytes(image.read(a, size))
        if k == 's':
            v = struct.unpack('<I', raw)[0]
            fields.append(cstr(v) if v else '0')
        elif k == 'f':
            fields.append(float_lit(struct.unpack('<I', raw)[0]))
        elif k == 'i':
            fields.append('%d' % struct.unpack('<i', raw)[0])
        elif k == 'u':
            fields.append('0x%X' % struct.unpack('<I', raw)[0])
        elif k == 'p':
            fields.append(pname(struct.unpack('<I', raw)[0]))
        elif k == 'x':
            fields.append('0x%08X' % struct.unpack('<I', raw)[0])
        elif k == 'z':
            fields.append('0')
        elif k in 'hH':
            fields.append('%d' % struct.unpack('<h' if k == 'h' else '<H', raw)[0])
        elif k in 'bB':
            fields.append('%d' % struct.unpack('<b' if k == 'b' else '<B', raw)[0])
        a += size
    align = max(SIZES[k] for k in spec)   # an element's size rounds up to its widest field
    a = (a + align - 1) // align * align
    elems.append(fields[0] if len(fields) == 1 else '{ ' + ', '.join(fields) + ' }')
end = a
if count == 1 and '[' not in decl:
    body = '%s = %s;' % (decl, elems[0])
else:
    body = '%s = {\n%s\n};' % (decl, '\n'.join('    %s,' % e for e in elems))
print(body)
print('// 0x%X-0x%X' % (addr, end))
if apply:
    full = os.path.join(ROOT, src)
    # an existing definition elsewhere in the unit moves into the block (its comment kept)
    prev = m5defs.take_existing(full, re.findall(r'(\w+)\s*(?:\[[^\]]*\])?\s*$', decl)[0])
    note = ''.join(l + '\n' for l in (prev or '').split('\n') if l.startswith('//'))
    m5defs.insert(full, addr, note + body)
    text = open(full, encoding='utf-8').read()
    hdr = "// Its data (PLAN M5): literals, constants and tables where the image has them.\n"
    ml = '// match: %s @ 0x%08X\n' % (mangled, addr)
    if hdr in text:
        text = text.replace(hdr, hdr + ml, 1)
    else:
        m = re.search(r'^// match: ', text, re.M)
        text = text[:m.start()] + hdr + ml + '\n' + text[m.start():]
    open(full, 'w', encoding='utf-8', newline='\n').write(text)
    res = []
    for l in open(os.path.join(ROOT, 'config', 'splits.txt'), encoding='utf-8').read().split('\n'):
        p = l.split()
        if len(p) >= 4 and p[0].startswith('0x') and p[3] == '-' and int(p[0], 16) <= addr < int(p[1], 16):
            s0, e0, sec = int(p[0], 16), int(p[1], 16), p[2]
            if addr > s0:
                res.append('0x%08X 0x%08X %-10s -' % (s0, addr, sec))
            res.append('0x%08X 0x%08X %-10s %s' % (addr, end, sec, mangled))
            if end < e0:
                res.append('0x%08X 0x%08X %-10s -' % (end, e0, sec))
        else:
            res.append(l)
    open(os.path.join(ROOT, 'config', 'splits.txt'), 'w', encoding='utf-8', newline='\n').write('\n'.join(res))
    subprocess.run([sys.executable, os.path.join(ROOT, 'tools', 'session', 'datablocks.py')], cwd=ROOT)
