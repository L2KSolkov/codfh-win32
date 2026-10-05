"""islandrows.py [--apply]: compiled.txt code rows owned by another object than the rows on
both sides of them, where the surrounding object emits a function with the same bytes
(relocation fields masked, same relocation offsets): an /OPT:ICF survivor or a same-code
template instance whose copy sits in the surrounding object (PLAN M7: m7probe orders objects
by their rows, and the row belongs to the object whose copy is there).

Prints ADDR, the row's object and name, and the surrounding object's candidate(s). With
--apply, a row with exactly one candidate gets that object and name, and the row's old name
gets a config/aliases.txt entry (the placement link resolves the old name's references)."""
import collections
import os
import sys

sys.path.insert(0, os.path.join(os.path.dirname(os.path.abspath(__file__)), '..'))
from coff import Coff  # noqa: E402

ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
apply = '--apply' in sys.argv
rows = []
owners = collections.defaultdict(set)
for l in open(os.path.join(ROOT, 'config', 'compiled.txt'), encoding='utf-8'):
    q = l.split()
    if len(q) >= 3 and q[0].startswith('0x') and q[1].startswith('build/src/') and int(q[0], 16) < 0x2F0000 \
            and not q[2].startswith('__ehhandler$'):
        rows.append((int(q[0], 16), q[1], q[2]))
        owners[int(q[0], 16)].add(q[1])
rows.sort()
single = [r for r in rows if len(owners[r[0]]) == 1]
cache = {}


def shapes(obj):
    """{masked bytes: [names]} of an object's functions."""
    if obj not in cache:
        out = collections.defaultdict(list)
        try:
            c = Coff(os.path.join(ROOT, obj))
        except (OSError, ValueError):
            cache[obj] = out
            return out
        for sym in c.symbol_list:
            if sym['type'] != 0x20 or sym['section'] <= 0 or sym['class'] not in (2, 3):
                continue
            name = sym['name']
            try:
                data, relocs = c.function_bytes(sym)
            except Exception:
                continue
            b = bytearray(data)
            offs = []
            for r in relocs:
                off = r[0]
                for k in range(4):
                    if off + k < len(b):
                        b[off + k] = 0
                offs.append(off)
            out[(bytes(b), tuple(sorted(offs)))].append(name)
        cache[obj] = out
    return cache[obj]


def shape_of(obj, name):
    for k, v in shapes(obj).items():
        if name in v:
            return k
    return None


# each object's main span: its longest run of consecutive rows (a run outside it is an island)
runs = []
i = 0
while i < len(single):
    j = i
    while j + 1 < len(single) and single[j + 1][1] == single[i][1]:
        j += 1
    runs.append((single[i][1], i, j))
    i = j + 1
main = {}
for o, i, j in runs:
    if j - i > main.get(o, (0, -1))[1] - main.get(o, (0, -1))[0]:
        main[o] = (i, j)
found = []
i = 1
while i < len(single) - 1:
    # a run of up to 8 rows of one object between rows of another
    j = i
    while j + 1 < len(single) and single[j + 1][1] == single[i][1] and j - i < 8:
        j += 1
    o = single[i][1]
    po = single[i - 1][1]
    no = single[j + 1][1] if j + 1 < len(single) else None
    if j - i < 8 and po != o and main.get(o) != (i, j):
        # the object before (or, failing that, after) the run emits the same code
        for a, _, n in single[i:j + 1]:
            k = shape_of(o, n)
            if k is None:
                continue
            for nb in [po] + ([no] if no and no != o and no != po else []):
                cands = [x for x in shapes(nb).get(k, []) if x != n]
                if cands:
                    found.append((a, o, n, nb, cands))
                    print('0x%06X %s %s -> %s: %s' % (a, os.path.basename(o), n[:70], os.path.basename(nb),
                                                       ' '.join(c[:70] for c in cands)))
                    break
    i = j + 1
print(len(found), 'island rows with a candidate')
if apply:
    t = open(os.path.join(ROOT, 'config', 'compiled.txt'), encoding='utf-8').read()
    al = []
    have = set(q.split()[2] for q in t.splitlines() if len(q.split()) >= 3)
    for a, o, n, po, cands in found:
        c = [x for x in cands if x not in have]
        if len(c) != 1:
            continue
        old = '0x%08X %s %s' % (a, o, n)
        if old in t:
            t = t.replace(old, '0x%08X %s %s' % (a, po, c[0]), 1)
            al.append('%s 0x%08X  identical to %s\'s %s, whose copy /OPT:ICF keeps there (islandrows.py)'
                      % (n, a, os.path.basename(po), c[0]))
    open(os.path.join(ROOT, 'config', 'compiled.txt'), 'w', encoding='utf-8', newline='\n').write(t)
    with open(os.path.join(ROOT, 'config', 'aliases.txt'), 'a', encoding='utf-8', newline='\n') as f:
        f.write(''.join(x + '\n' for x in al))
    print(len(al), 'rows moved')
