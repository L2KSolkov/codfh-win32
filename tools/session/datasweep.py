"""datasweep.py [--apply]: objdata.py over every object (PLAN M5).

For each object with a placed symbol in a .data or .rdata section that holds several symbols
(non-COMDAT data keeps its definition order), the section's other symbols are laid out from that
anchor; those whose bytes match the image (outside relocations) inside uncovered (`-`) ranges
are listed, and with --apply placed through objdata.py --apply, one object at a time."""
import os
import subprocess
import sys

sys.path.insert(0, os.path.join(os.path.dirname(os.path.abspath(__file__)), '..'))
from coff import Coff  # noqa: E402
from xbe import Xbe  # noqa: E402

ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
apply = '--apply' in sys.argv
image = Xbe(os.path.join(ROOT, 'orig', 'Game_XboxMultiplayer.xbe'))
rows = {}
for l in open(os.path.join(ROOT, 'config', 'compiled.txt'), encoding='utf-8'):
    q = l.split()
    if len(q) >= 3 and q[0].startswith('0x') and int(q[0], 16) >= 0x3C0000 and q[1].startswith('build/src/'):
        rows.setdefault(q[1], {})[q[2]] = int(q[0], 16)
free = []
for l in open(os.path.join(ROOT, 'config', 'splits.txt'), encoding='utf-8'):
    p = l.split()
    if len(p) >= 4 and p[0].startswith('0x') and p[3] == '-' and p[2] in ('.data', '.rdata'):
        free.append((int(p[0], 16), int(p[1], 16)))
free.sort()


def is_free(a, e):
    for f0, f1 in free:
        if f0 <= a and e <= f1:
            return True
        if f0 > a:
            return False
    return False


todo = []
for obj, names in sorted(rows.items()):
    if not os.path.exists(os.path.join(ROOT, obj)):
        continue
    c = Coff(os.path.join(ROOT, obj))
    done = set()
    for name, addr in names.items():
        s = c._defined().get(name)
        if s is None or s['section'] <= 0 or s['section'] in done:
            continue
        sec = c.sections[s['section'] - 1]
        if not sec['name'].startswith(('.data', '.rdata')):
            continue
        syms = sorted({y['value']: y for y in c.symbol_list if y.get('section') == s['section'] and
                       y['class'] in (2, 3) and not y['name'].startswith('.')}.values(), key=lambda y: y['value'])
        if len(syms) < 2:
            continue
        done.add(s['section'])
        hits = []
        for k, y in enumerate(syms):
            if y['name'] in names:
                continue
            hi = syms[k + 1]['value'] if k + 1 < len(syms) else sec['size']
            a = addr + y['value'] - s['value']
            e = a + hi - y['value']
            if not is_free(a, e):
                continue
            code, rel = c.function_bytes(y)
            img = bytearray(image.read(a, len(code)))
            mine = bytearray(code)
            for off, _t, _r in rel:
                mine[off:off + 4] = img[off:off + 4] = b'\0\0\0\0'
            if bytes(mine) == bytes(img):
                hits.append((a, e, y['name']))
        for a, e, n in hits:
            print('0x%06X-0x%06X %4X %s  %s' % (a, e, e - a, obj, n[:80]))
        if hits:
            todo.append((obj, name, addr))
if apply:
    for obj, name, addr in todo:
        r = subprocess.run([sys.executable, os.path.join(ROOT, 'tools', 'session', 'objdata.py'), '--apply',
                            obj, name, '0x%X' % addr], capture_output=True, text=True, cwd=ROOT)
        print(obj, (r.stdout.strip().split('\n') or [''])[-1], r.stderr.strip()[-200:])
