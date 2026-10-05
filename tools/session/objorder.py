"""objorder.py: each compiled object's code order against the image (PLAN M7).

link.exe lays out an object's .text COMDATs in the object's section order, so for the authentic
link a unit's functions must come out of the compiler in image address order. For every object
in config/compiled.txt: its functions (the compiled.txt rows it places) in section order, the
longest run that is already in image order, and the rest, the misplaced ones.

    objorder.py               a count per object, worst first
    objorder.py OBJ...        that object's misplaced functions, with where they belong
    objorder.py OBJ=FILE      the same for FILE, compiled from OBJ's source elsewhere (cc1.py's)"""
import bisect
import collections
import os
import sys

sys.path.insert(0, os.path.join(os.path.dirname(os.path.abspath(__file__)), '..'))
from coff import Coff  # noqa: E402

ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
TEXT_END = 0x2F0000             # game, RenderWare and library code; not the XDK sections

rows = collections.defaultdict(dict)
for l in open(os.path.join(ROOT, 'config', 'compiled.txt'), encoding='utf-8'):
    q = l.split()
    if len(q) >= 3 and q[0].startswith('0x') and int(q[0], 16) < TEXT_END:
        rows[q[1].replace('\\', '/')][q[2]] = int(q[0], 16)


def order(obj, path=None):
    """[(image address, name)] in the object's code-section order."""
    c = Coff(os.path.join(ROOT, path or obj))
    want = rows[obj]
    seen = []
    for s in c.symbol_list:
        if s['section'] > 0 and s['class'] in (2, 3) and s['name'] in want:
            sec = c.sections[s['section'] - 1]
            if sec['chars'] & 0x20:
                seen.append((s['section'], s['value'], want[s['name']], s['name']))
    seen.sort()
    return [(a, n) for _sec, _v, a, n in seen]


def misplaced(seq):
    """Indices outside one longest increasing run of addresses."""
    tails, tails_i, prev = [], [], [-1] * len(seq)
    for i, (a, _n) in enumerate(seq):
        k = bisect.bisect_left(tails, a)
        if k == len(tails):
            tails.append(a)
            tails_i.append(i)
        else:
            tails[k] = a
            tails_i[k] = i
        prev[i] = tails_i[k - 1] if k else -1
    keep = set()
    i = tails_i[-1] if tails_i else -1
    while i >= 0:
        keep.add(i)
        i = prev[i]
    return [i for i in range(len(seq)) if i not in keep]


if __name__ == "__main__" and len(sys.argv) > 1:
    for obj in sys.argv[1:]:
        obj, _eq, path = obj.replace('\\', '/').partition('=')
        seq = order(obj, path or None)
        bad = set(misplaced(seq))
        print('%s: %d functions, %d misplaced' % (obj, len(seq), len(bad)))
        for i, (a, n) in enumerate(seq):
            print('  %s 0x%06X %s' % ('*' if i in bad else ' ', a, n[:90]))
elif __name__ == "__main__":
    out = []
    total = 0
    for obj in rows:
        if not os.path.exists(os.path.join(ROOT, obj)):
            continue
        seq = order(obj)
        bad = misplaced(seq)
        total += len(bad)
        if bad:
            out.append((len(bad), len(seq), obj))
    out.sort(reverse=True)
    for k, n, obj in out:
        print('%4d of %4d  %s' % (k, n, obj))
    print('%d objects out of order, %d functions misplaced' % (len(out), total))
