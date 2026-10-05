"""libswitch.py FROM TO [--apply]: XDK rows of library copy FROM (build/xdk/FROM/) that the same
object of library copy TO defines with the same body (relocation fields aside) move to TO
(PLAN M7). The original link took each object from one library; rows matched against either
of two copies of an object (xnets.lib's networking objects are xonlines.lib's too) are put
on one copy. Prints the moves and the rows that do not match in TO."""
import os
import sys

sys.path.insert(0, os.path.join(os.path.dirname(os.path.abspath(__file__)), '..'))
from coff import Coff  # noqa: E402
from xbe import Xbe  # noqa: E402

ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
src, dst = sys.argv[1], sys.argv[2]
apply = '--apply' in sys.argv
img = Xbe(os.path.join(ROOT, 'orig', 'Game_XboxMultiplayer.xbe'))
cache = {}


def coff(p):
    if p not in cache:
        cache[p] = Coff(os.path.join(ROOT, p)) if os.path.exists(os.path.join(ROOT, p)) else None
    return cache[p]


def body(c, n):
    x = next((s for s in c.symbol_list if s['section'] > 0 and s['name'] == n), None) if c else None
    if x is None:
        return None
    try:
        code, rel = c.function_bytes(x)
    except Exception:
        try:
            s = c.sections[x['section'] - 1]
            code, rel = bytes(s['data'][x['value']:]), [(va - x['value'], '', t) for va, si, t in s['relocs']]
        except Exception:
            return None
    return code, rel


def same_at(a, b):
    code, rel = b
    ra = set()
    for o, t, ty in rel:
        ra.update(range(o, o + 4))
    try:
        i = img.read(a, len(code))
    except Exception:
        return False
    return all(code[k] == i[k] for k in range(len(code)) if k not in ra)


moves, keep = {}, []
lines = open(os.path.join(ROOT, 'config', 'compiled.txt'), encoding='utf-8').read().split('\n')
for k, l in enumerate(lines):
    q = l.split()
    if len(q) < 3 or not q[0].startswith('0x') or not q[1].startswith('build/xdk/%s/' % src):
        continue
    a = int(q[0], 16)
    other = q[1].replace('build/xdk/%s/' % src, 'build/xdk/%s/' % dst)
    b = body(coff(other), q[2])
    if b and same_at(a, b):
        moves[k] = '%s %s %s' % (q[0], other, q[2])
    else:
        keep.append(l)
print(len(moves), 'move;', len(keep), 'stay')
for l in keep:
    print('  stays:', l[:120])
if apply:
    for k, l in moves.items():
        lines[k] = l
    open(os.path.join(ROOT, 'config', 'compiled.txt'), 'w', encoding='utf-8', newline='\n').write('\n'.join(lines))
