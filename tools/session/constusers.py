"""constusers.py UNIT: the functions of build/src/recovered/UNIT.obj that reference each of its
named data constants (?flt_/?stru_/?dbl_... rows in .rdata; --all: every .rdata row), with the image addresses of both
(PLAN M7: the image has a function-local static's data among that function's literals, so a
named constant only one function reads, sitting among the literals, is that function's static)."""
import collections
import os
import sys

sys.path.insert(0, os.path.join(os.path.dirname(os.path.abspath(__file__)), '..'))
from coff import Coff  # noqa: E402

ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
u = [a for a in sys.argv[1:] if not a.startswith('--')][0]
p = os.path.join(ROOT, 'build', 'src', 'recovered', u + '.obj')
c = Coff(p)
addr = {}
rel = 'build/src/recovered/%s.obj' % u
for l in open(os.path.join(ROOT, 'config', 'compiled.txt'), encoding='utf-8'):
    q = l.split()
    if len(q) >= 3 and q[0].startswith('0x') and q[1] == rel:
        addr[q[2]] = int(q[0], 16)
users = collections.defaultdict(set)
for s in c.sections:
    if not (s['chars'] & 0x20):
        continue
    funcs = sorted((x['value'], x['name']) for x in c.symbol_list
                   if x['section'] == s['index'] and x['class'] in (2, 3) and x['type'] == 0x20)
    for v, si, t in s['relocs']:
        tgt = c.symbols[si]['name']
        owner = None
        for fv, fn in funcs:
            if fv <= v:
                owner = fn
        users[tgt].add(owner)
every = '--all' in sys.argv
for n, a in sorted(addr.items(), key=lambda kv: kv[1]):
    if 0x3CD300 <= a < 0x426D40 and (every or not (n.startswith('??_C@') or n.startswith('__real@')
                                                   or n.startswith('??_7') or n.startswith('??_R'))):
        us = sorted(users.get(n, ()), key=lambda f: addr.get(f, 0))
        print('0x%06X %-28s %s' % (a, n, ' '.join('%X' % addr[f] if f in addr else str(f) for f in us)))
