"""icfrename.py [--apply] [OBJ...]: rows that name the wrong one of several identical functions an
object emits (PLAN M7 layout).

Identical instantiations (templates over different types, same code) fold together under
/OPT:ICF, and a compiled.txt row names one of them; the object's emission order then shows the
row's function in the wrong place, where an identical function with no row of its own sits
right. For each row out of order in its object (objorder.py's longest in-order run): a function
of the same object with the same masked bytes and relocation targets, no row, whose section
lies between the sections of the in-order rows around the row's address. With --apply the row
takes that name and the old name gets a config/aliases.txt entry at the row's address."""
import bisect
import collections
import os
import sys

sys.path.insert(0, os.path.join(os.path.dirname(os.path.abspath(__file__)), '..'))
from coff import Coff  # noqa: E402

ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
TEXT_END = 0x2F0000
apply = '--apply' in sys.argv
args = [a for a in sys.argv[1:] if a != '--apply']
rows = collections.defaultdict(dict)
all_names = set()
for l in open(os.path.join(ROOT, 'config', 'compiled.txt'), encoding='utf-8'):
    q = l.split()
    if len(q) >= 3 and q[0].startswith('0x'):
        all_names.add(q[2])
        if int(q[0], 16) < TEXT_END:
            rows[q[1]][q[2]] = int(q[0], 16)


def shape(c, sym):
    data, relocs = c.function_bytes(sym)
    b = bytearray(data)
    for off, t, ty in relocs:
        b[off:off + 4] = b'\0\0\0\0'
    return bytes(b), tuple((off, t) for off, t, ty in relocs)


changes = []
for obj in (args or sorted(rows)):
    path = os.path.join(ROOT, obj)
    if not obj.startswith('build/src/recovered/') and not args or not os.path.exists(path):
        continue
    c = Coff(path)
    seq = []            # (section, name) of functions, section order
    sym_of = {}
    for s in c.symbol_list:
        if s['type'] == 0x20 and s['section'] > 0 and s['class'] in (2, 3):
            if s['name'] not in sym_of:
                sym_of[s['name']] = s
                seq.append((s['section'], s['name']))
    seq.sort()
    pos = {n: i for i, (sec, n) in enumerate(seq)}
    r = [(pos[n], a, n) for n, a in rows[obj].items() if n in pos]
    r.sort()
    # longest increasing run of addresses in emission order
    tails, idx, parent = [], [], [-1] * len(r)
    for i, (p, a, n) in enumerate(r):
        j = bisect.bisect_left(tails, a)
        if j == len(tails):
            tails.append(a)
            idx.append(i)
        else:
            tails[j] = a
            idx[j] = i
        parent[i] = idx[j - 1] if j else -1
    keep, i = set(), idx[-1] if idx else -1
    while i >= 0:
        keep.add(i)
        i = parent[i]
    good = sorted((a, p) for k, (p, a, n) in enumerate(r) if k in keep)
    gaddr = [a for a, p in good]
    for k, (p, a, n) in enumerate(r):
        if k in keep:
            continue
        j = bisect.bisect_left(gaddr, a)
        lo = good[j - 1][1] if j > 0 else -1
        hi = good[j][1] if j < len(good) else len(seq)
        try:
            want = shape(c, sym_of[n])
        except Exception:
            continue
        cands = []
        for q in range(lo + 1, hi):
            cn = seq[q][1]
            if cn == n or cn in all_names:
                continue
            try:
                if shape(c, sym_of[cn]) == want:
                    cands.append(cn)
            except Exception:
                pass
        if len(cands) == 1:
            changes.append((obj, a, n, cands[0]))
            print('0x%06X %s: %s -> %s' % (a, os.path.basename(obj), n[:70], cands[0][:70]))
print(len(changes), 'rows')
if apply and changes:
    p = os.path.join(ROOT, 'config', 'compiled.txt')
    t = open(p, encoding='utf-8').read()
    al = []
    for obj, a, n, cn in changes:
        old = '0x%08X %s %s' % (a, obj, n)
        if old in t:
            t = t.replace(old, '0x%08X %s %s' % (a, obj, cn), 1)
            al.append('%s 0x%08X  identical to %s, the copy the object emits there (/OPT:ICF; icfrename.py)' % (n, a, cn))
    open(p, 'w', encoding='utf-8', newline='\n').write(t)
    with open(os.path.join(ROOT, 'config', 'aliases.txt'), 'a', encoding='utf-8', newline='\n') as f:
        f.write(''.join(x + '\n' for x in al))
    print(len(al), 'applied')
