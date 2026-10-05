"""objdata.py [--apply] OBJ SYMBOL ADDR [END]: place an object's data symbols around one known address (PLAN M5).

The symbols of SYMBOL's section in OBJ (a non-COMDAT .data or .rdata keeps its definition
order) are laid out from SYMBOL at ADDR by their section offsets, each running to the next
symbol (or the section's end), and stopped at END when given. Each is byte-compared with the
image outside its relocations; the ones that match and sit in uncovered (`-`) ranges are
printed, and with --apply get `// match:` lines (after the source's last data match line below
their address, else before its first match line) and config/splits.txt rows."""
import os
import re
import sys

sys.path.insert(0, os.path.join(os.path.dirname(os.path.abspath(__file__)), '..'))
from coff import Coff  # noqa: E402
from xbe import Xbe  # noqa: E402

ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
args = sys.argv[1:]
apply = '--apply' in args
args = [a for a in args if a != '--apply']
obj, anchor, addr = args[0], args[1], int(args[2], 16)
end = int(args[3], 16) if len(args) > 3 else 1 << 32
image = Xbe(os.path.join(ROOT, 'orig', 'Game_XboxMultiplayer.xbe'))
c = Coff(os.path.join(ROOT, obj))
a0 = c.find_function(anchor)
if a0 is None:
    sys.exit('no %s in %s' % (anchor, obj))
sec = a0['section']
syms = sorted({s['value']: s for s in c.symbol_list
               if s.get('section') == sec and s['class'] in (2, 3) and not s['name'].startswith('.')}.values(),
              key=lambda s: s['value'])
data = bytes(c.sections[sec - 1]['data'])
relocs = {r[0] for r in c.sections[sec - 1]['relocs']} if c.sections[sec - 1]['relocs'] and \
    isinstance(c.sections[sec - 1]['relocs'][0], tuple) else set()
free = []
splits = open(os.path.join(ROOT, 'config', 'splits.txt'), encoding='utf-8').read().split('\n')
for l in splits:
    p = l.split()
    if len(p) >= 4 and p[0].startswith('0x') and p[3] == '-':
        free.append((int(p[0], 16), int(p[1], 16)))
plan = []
for k, s in enumerate(syms):
    lo = s['value']
    hi = syms[k + 1]['value'] if k + 1 < len(syms) else c.sections[sec - 1]['size']
    a = addr + lo - a0['value']
    e = min(a + hi - lo, end)
    if a >= end or a < addr - a0['value']:
        continue
    code, rel = c.function_bytes(s)
    code = code[:e - a]
    img = bytearray(image.read(a, len(code)))
    mine = bytearray(code)
    for off, _t, _r in rel:
        if off < len(code):
            mine[off:off + 4] = img[off:off + 4] = b'\0\0\0\0'
    ok = bytes(mine) == bytes(img)
    covered = any(f0 <= a and e <= f1 for f0, f1 in free)
    print('0x%06X-0x%06X %4X %-5s %-9s %s' % (a, e, e - a, 'ok' if ok else 'DIFF',
                                              'free' if covered else 'placed', s['name'][:90]))
    if ok and covered:
        plan.append((a, e, s['name']))
if not apply or not plan:
    sys.exit(0)
src = next(os.path.join(ROOT, obj[len('build/'):-len('.obj')] + x) for x in ('.c', '.cpp')
           if os.path.exists(os.path.join(ROOT, obj[len('build/'):-len('.obj')] + x)))
raw = open(src, 'rb').read()
nl = '\r\n' if b'\r\n' in raw else '\n'
t = raw.decode('latin-1').replace('\r\n', '\n')
for a, e, n in plan:
    ml = '// match: %s @ 0x%08X\n' % (n, a)
    best = None
    for m in re.finditer(r'^// match: \S+ @ 0x([0-9A-F]+)\n', t, re.M):
        v = int(m.group(1), 16)
        if 0x3C0000 <= v < a and (best is None or v > best[0]):
            best = (v, m.end())
    if best:
        t = t[:best[1]] + ml + t[best[1]:]
    else:
        m = re.search(r'^// match: ', t, re.M)
        t = t[:m.start()] + ml + t[m.start():]
open(src, 'wb').write(t.replace('\n', nl).encode('latin-1'))
for a, e, n in plan:
    res = []
    for l in splits:
        p = l.split()
        if len(p) >= 4 and p[0].startswith('0x') and p[3] == '-' and int(p[0], 16) <= a < int(p[1], 16):
            s0, e0, sc = int(p[0], 16), int(p[1], 16), p[2]
            if a > s0:
                res.append('0x%08X 0x%08X %-10s -' % (s0, a, sc))
            res.append('0x%08X 0x%08X %-10s %s' % (a, e, sc, n))
            if e < e0:
                res.append('0x%08X 0x%08X %-10s -' % (e, e0, sc))
        else:
            res.append(l)
    splits = res
open(os.path.join(ROOT, 'config', 'splits.txt'), 'w', encoding='utf-8', newline='\n').write('\n'.join(splits))
print('applied', len(plan))
