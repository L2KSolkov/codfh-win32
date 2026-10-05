"""litowner2.py [--apply]: give shared literal rows (??_C@ strings, __real@ constants) to the object
whose data surrounds them in the image (PLAN M7).

A COMDAT literal is the first defining object's, in link order, and lands among that object's
.rdata. For each such row this finds the object owning the nearest preceding own (non-literal)
row in .rdata (and the next one); when that object (one of the link's, build/m7/cdz/objects.txt)
defines the literal and the row names another object, the row moves to it (and the source's
match line, when one names it, is left to the caller). Prints the plan; --apply rewrites
config/compiled.txt."""
import bisect
import os
import re
import sys

sys.path.insert(0, os.path.join(os.path.dirname(os.path.abspath(__file__)), '..'))
from coff import Coff  # noqa: E402

ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
apply = '--apply' in sys.argv
LO, HI = int(os.environ.get('LIT_LO', '0x3CD300'), 16), 0x41AC9C

linked = []
for l in open(os.path.join(ROOT, 'build', 'm7', 'cdz', 'objects.txt')):
    p = l.split()[1]
    linked.append(p)
members = {}
for l in open(os.path.join(ROOT, 'build', 'm7', 'standin', 'members.txt')):
    lib, base, path = l.split()
    members[base] = path


def src_of(p):
    pre = 'build/m7/obj/'
    return p[len(pre):] if p.startswith(pre) else p


rows = []
for l in open(os.path.join(ROOT, 'config', 'compiled.txt'), encoding='utf-8'):
    q = l.split()
    if len(q) >= 3 and q[0].startswith('0x'):
        a = int(q[0], 16)
        if LO <= a < HI:
            rows.append((a, q[1], q[2]))
rows.sort()


def lit(n):
    return n.startswith('??_C@') or n.startswith('__real@')


cache = {}


def defines(path, name):
    real = members.get(path, path)
    if not os.path.exists(os.path.join(ROOT, real)):
        real = 'build/m7/obj/' + path
    if real not in cache:
        try:
            c = Coff(os.path.join(ROOT, real))
            cache[real] = set(x['name'] for x in c.symbol_list if x['section'] > 0)
        except Exception:
            cache[real] = set()
    return name in cache[real]


plan = []
for k, (a, o, n) in enumerate(rows):
    if not lit(n):
        continue
    prev = next((r for r in reversed(rows[:k]) if not lit(r[2]) and not r[1].startswith('build/src/xdk/')), None)
    nxt = next((r for r in rows[k + 1:] if not lit(r[2]) and not r[1].startswith('build/src/xdk/')), None)
    for cand in (prev, nxt):
        if cand is None or cand[1] == o:
            break
        if abs(cand[0] - a) > 0x400:
            continue
        if defines(cand[1], n):
            plan.append((a, o, n, cand[1]))
            break
for a, o, n, c in plan:
    print('0x%08X %s: %s -> %s' % (a, n[:40], o.split('/')[-1], c.split('/')[-1]))
print(len(plan))
if apply:
    path = os.path.join(ROOT, 'config', 'compiled.txt')
    t = open(path, encoding='utf-8').read()
    for a, o, n, c in plan:
        t = re.sub(r'^0x%08X %s %s$' % (a, re.escape(o), re.escape(n)), '0x%08X %s %s' % (a, c, n), t, flags=re.M)
    open(path, 'w', encoding='utf-8', newline='\n').write(t)
