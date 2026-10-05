"""frametime.py [--apply]: every unit's own copy of 16.666666f (0x41855555) as a unit constant (PLAN M5).

The game's units each keep a copy of the frame time in milliseconds at the start of their .rdata
(or where their first user put it), and /Od code reads its own unit's copy from memory. Each
uncovered copy goes to the unit placed around it (at a boundary, the next unit: the copy opens
its .rdata) as `extern const RwReal flt_ADDR = 16.666666f;` in its sorted data block, and the
functions whose relocations read the copy have their `16.666666f` literals replaced by the name.
Prints the plan; --apply writes sources and config/splits.txt (the match lines are written to
the units; cmfm adds the rows)."""
import bisect
import os
import re
import struct
import sys

sys.path.insert(0, os.path.join(os.path.dirname(os.path.abspath(__file__)), '..'))
sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import m5defs  # noqa: E402
from coff import Coff  # noqa: E402
from xbe import Xbe  # noqa: E402

ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
apply = '--apply' in sys.argv
image = Xbe(os.path.join(ROOT, 'orig', 'Game_XboxMultiplayer.xbe'))
sec = next(s for s in image.sections if s['name'] == '.rdata')
blob = bytes(image.read(sec['va'], sec['vsize']))
copies = [sec['va'] + m.start() for m in re.finditer(re.escape(b'\x55\x55\x85\x41'), blob) if m.start() % 4 == 0]
rows, code_rows = [], {}
for l in open(os.path.join(ROOT, 'config', 'compiled.txt'), encoding='utf-8'):
    q = l.split()
    if len(q) >= 3 and q[0].startswith('0x'):
        a = int(q[0], 16)
        if 0x3C0000 <= a < 0x426000:
            rows.append((a, q[1], q[2]))
        elif a < 0x3C0000:
            code_rows.setdefault(q[1], []).append((a, q[2]))
rows.sort()
addrs = [a for a, o, n in rows]
placed = {a: n for a, o, n in rows}
free = []
for l in open(os.path.join(ROOT, 'config', 'splits.txt'), encoding='utf-8'):
    p = l.split()
    if len(p) >= 4 and p[0].startswith('0x') and p[2] == '.rdata' and p[3] == '-':
        free.append((int(p[0], 16), int(p[1], 16)))


def src_of(obj):
    base = os.path.join(ROOT, obj[len('build/'):-len('.obj')])
    return next((base + x for x in ('.cpp', '.c') if os.path.exists(base + x)), None)


# who reads each address: an item's owner is the first unit in link order that reads it (a
# pooled literal sits in the first reader's data); copies read through the literal also give
# their reading functions
first = {}
for obj, pieces in code_rows.items():
    first[obj] = min(a for a, n in pieces)
readers, readby = {}, {}
for obj, pieces in code_rows.items():
    if not os.path.exists(os.path.join(ROOT, obj)):
        continue
    c = Coff(os.path.join(ROOT, obj))
    for addr, name in pieces:
        s = c.find_function(name)
        if s is None:
            continue
        _code, rel = c.function_bytes(s)
        for off, tgt, _r in rel:
            v = struct.unpack('<I', bytes(image.read(addr + off, 4)))[0]
            if 0x3C0000 <= v < 0x426000:
                readby.setdefault(v, set()).add(obj)
            if tgt == '__real@41855555' or ('flt_' in tgt and struct.unpack('<I', bytes(image.read(v, 4)))[0] == 0x41855555):
                readers.setdefault(v, set()).add((obj, name))


def owner_of(a, obj, name):
    objs = readby.get(a)
    if objs:
        return min(objs, key=lambda o: first.get(o, 1 << 32))
    return None if name.startswith(('??_C@', '__real@', '__xmm@')) else obj


def game(o):
    return o and o.startswith('build/src/') and not o.startswith(
        ('build/src/rw/', 'build/src/rwa/', 'build/src/xdk/', 'build/src/bink/'))


owned = [(a, owner_of(a, o, n)) for a, o, n in rows]
plan = []
for a in copies:
    if a in placed and placed[a] != '__real@41855555':
        continue
    if not any(f0 <= a and a + 4 <= f1 for f0, f1 in free) and placed.get(a) != '__real@41855555':
        continue
    users = readers.get(a, set())
    if users:
        owner = sorted(users)[0][0]
    else:
        j = bisect.bisect_left(addrs, a)
        nxt = next((o for b, o in owned[j:] if b != a and o), None)
        prv = next((o for b, o in reversed(owned[:j]) if o), None)
        owner = prv if prv == nxt else nxt
        if not game(owner) and game(prv):
            owner = prv
    plan.append((a, owner, users))
# one copy per object: an object's constants are one contiguous section, so a unit holding
# copies apart is several original files (left for the unit split: listed, not placed)
keep, split = [], []
byunit = {}
for a, o, u in plan:
    byunit.setdefault(o, []).append((a, o, u))
occupied = set(o for a, o, n in rows if a in set(copies) and 'flt_' in n)
for o, items in byunit.items():
    read = [it for it in items if it[2]]
    chosen = read if read else ([] if o in occupied else [min(items)])
    keep.extend(chosen)
    split.extend(it for it in items if it not in chosen)
plan = sorted(keep)
print('left for unit splits:', len(split), ' '.join('%X:%s' % (a, o.split('/')[-1][:-4]) for a, o, u in sorted(split)))
bad = [(hex(a), o) for a, o, u in plan if not o or not src_of(o)]
print('copies', len(copies), 'planned', len(plan), 'with readers', sum(1 for p in plan if p[2]), 'odd owners', bad[:10])
from collections import Counter  # noqa: E402
cnt = Counter(o for a, o, u in plan)
print('units', len(cnt), 'with several', [(o.split('/')[-1], n) for o, n in cnt.items() if n > 1])
if not apply:
    sys.exit(0)
for a, owner, users in plan:
    if owner in [b for _a, b in bad]:
        continue
    src = src_of(owner)
    full = os.path.abspath(src)
    name = 'flt_%06X' % a
    text = open(full, encoding='utf-8').read()
    # a header's declaration (extern const RwReal flt_X;) is satisfied by the definition
    m5defs.insert(full, a, 'extern const RwReal %s = 16.666666f;' % name)
    text = open(full, encoding='utf-8').read()
    for obj, fn in users:
        mm = re.search(r'^// match: %s @ 0x[0-9A-F]+\n' % re.escape(fn), text, re.M)
        if not mm:
            print('no match line for', fn)
            continue
        body_start = text.index('\n{', mm.end())
        depth, k = 0, body_start + 1
        while True:
            ch = text[k]
            if ch == '{':
                depth += 1
            elif ch == '}':
                depth -= 1
                if depth == 0:
                    break
            k += 1
        body = text[body_start:k]
        text = text[:body_start] + body.replace('16.666666f', name) + text[k:]
    open(full, 'w', encoding='utf-8', newline='\n').write(text)
print('applied')
