"""m7layout.py: the real link's layout (build/m7/game.map, m7probe.py's) against the image (PLAN M7).

For every compiled.txt row whose symbol the map lists, the map address minus the image
address: identical layout means one constant offset per image section. Prints, per image
section, the most common offset, how many rows have it, and the first rows (by image address)
where the offset changes (where the real link's order or sizes first differ)."""
import collections
import os
import re
import sys

sys.path.insert(0, os.path.join(os.path.dirname(os.path.abspath(__file__)), '..'))
from xbe import Xbe  # noqa: E402

ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
image = Xbe(os.path.join(ROOT, 'orig', 'Game_XboxMultiplayer.xbe'))
secs = [(s['va'], s['va'] + s['vsize'], s['name']) for s in image.sections]
# a symbol's map address by (name, object): statics ($E1, string literals' neighbours,
# file-local helpers) repeat across objects; a name only one object has is found by name
# alone (library members are named LIB:MEMBER in the map)
by_obj, by_name = {}, collections.defaultdict(set)
for l in open(os.path.join(ROOT, 'build', 'm7', 'game.map'), errors='replace'):
    m = re.match(r'^\s*[0-9a-f]{4}:[0-9a-f]{8}\s+(\S+)\s+([0-9a-f]{8})\s+(.*)$', l)
    if m:
        obj = m.group(3).split()[-1].split(':')[-1].lower()
        by_obj.setdefault((m.group(1), obj), int(m.group(2), 16))
        by_name[m.group(1)].add(int(m.group(2), 16))
mapped = {}
rows = []
for l in open(os.path.join(ROOT, 'config', 'compiled.txt'), encoding='utf-8'):
    q = l.split()
    if len(q) >= 3 and q[0].startswith('0x'):
        v = by_obj.get((q[2], os.path.basename(q[1]).lower()))
        if v is None and len(by_name.get(q[2], ())) == 1:
            v = next(iter(by_name[q[2]]))
        if v is not None:
            key = q[2] + '@' + q[1]
            mapped[key] = v
            rows.append((int(q[0], 16), key, q[1]))
rows.sort()
per = collections.defaultdict(list)
for a, n, o in rows:
    sec = next((s for s in secs if s[0] <= a < s[1]), None)
    if sec:
        per[sec[2]].append((a, n, o, mapped[n] - a))
show = int(os.environ.get('NSHOW', '4'))
for name in sorted(per, key=lambda k: per[k][0][0]):
    items = per[name]
    c = collections.Counter(d for a, n, o, d in items)
    best, k = c.most_common(1)[0]
    print('%-10s %6d rows; offset 0x%X for %d (%.0f%%)' % (name, len(items), best & 0xFFFFFFFF, k, 100.0 * k / len(items)))
    prev, shown = None, 0
    for a, n, o, d in items:
        if prev is not None and d != prev and shown < show:
            print('    at 0x%06X %-50s %s: 0x%X -> 0x%X' % (a, n[:50], os.path.basename(o), prev & 0xFFFFFFFF, d & 0xFFFFFFFF))
            shown += 1
        prev = d

if os.environ.get('ORDER'):
    # ORDER=1: order only, without the /OPT:ICF groups (map addresses several symbols share;
    # link picks their survivor by a sort over every candidate, so they settle last). Per
    # section, the longest run of rows already in image order, and the rows outside it
    # (counted per object, then the first ones by image address).
    import bisect
    count = collections.Counter(mapped.values())
    print('\n== order (ICF groups left out)')
    for name in sorted(per, key=lambda k: per[k][0][0]):
        items = [(a, n, o, d) for a, n, o, d in per[name] if count[mapped[n]] == 1]
        seq = [a + d for a, n, o, d in items]
        tails, idx, parent = [], [], [-1] * len(seq)
        for i, v in enumerate(seq):
            j = bisect.bisect_left(tails, v)
            if j == len(tails):
                tails.append(v)
                idx.append(i)
            else:
                tails[j] = v
                idx[j] = i
            parent[i] = idx[j - 1] if j else -1
        keep, i = set(), idx[-1] if idx else -1
        while i >= 0:
            keep.add(i)
            i = parent[i]
        out = [items[i] for i in range(len(items)) if i not in keep]
        print('%-10s %6d rows, %d out of order' % (name, len(items), len(out)))
        per_obj = collections.Counter(os.path.basename(o) for a, n, o, d in out)
        if out and os.environ.get('ORDER') != 'brief':
            print('    ' + ', '.join('%s %d' % kv for kv in per_obj.most_common(8)))
            for a, n, o, d in out[:show]:
                print('    0x%06X %-50s %s' % (a, n[:50], os.path.basename(o)))
