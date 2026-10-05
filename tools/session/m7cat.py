"""m7cat.py [CATEGORY]: sort build/m7/unresolved.txt into categories (PLAN M7 bookkeeping).

alias: named in config/aliases.txt (ICF-folded; needs its own definition); placed: a compiled.txt
row names it (defined under that name by a placed object that the probe did not link?);
bss/data/rdata/code: an address-named (or symbols.txt-named) symbol in that image range;
BINKDATA; other. With CATEGORY, lists its names (with the address when known)."""
import collections
import os
import re
import sys

ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
unres = [l.strip() for l in open(os.path.join(ROOT, 'build', 'm7', 'unresolved.txt')) if l.strip()]
aliases = set()
for l in open(os.path.join(ROOT, 'config', 'aliases.txt'), encoding='utf-8'):
    q = l.split()
    if q and not l.startswith('#'):
        aliases.add(q[0])
rows = {}
for l in open(os.path.join(ROOT, 'config', 'compiled.txt'), encoding='utf-8'):
    q = l.split()
    if len(q) >= 3 and q[0].startswith('0x'):
        rows[q[2]] = (int(q[0], 16), q[1])
syms = {}
for l in open(os.path.join(ROOT, 'config', 'symbols.txt'), encoding='utf-8', errors='replace'):
    q = l.split()
    if len(q) >= 5 and q[0].startswith('0x'):
        syms[q[4]] = int(q[0], 16)


def plain(n):
    m = re.match(r'^\?(\w+)@', n)
    if m:
        return m.group(1)
    m = re.match(r'^_(\w+?)(@\d+)?$', n)
    return m.group(1) if m else n


def where(a):
    if a < 0x3C0000:
        return 'code'
    if a < 0x426D40:
        return 'rdata'
    if a < 0x438C8C:
        return 'data'
    return 'bss'


cats = collections.defaultdict(list)
for n in unres:
    p = plain(n)
    m = re.search(r'_([0-9A-F]{6})$', p)
    if n in aliases:
        cats['alias'].append((n, None))
    elif n in rows:
        cats['placed'].append((n, rows[n][0]))
    elif 'BINK' in n.upper() and 'DATA' in n.upper():
        cats['BINKDATA'].append((n, None))
    elif m:
        cats[where(int(m.group(1), 16))].append((n, int(m.group(1), 16)))
    elif p in syms or ('_' + p) in syms:
        a = syms.get(p, syms.get('_' + p))
        cats['named ' + where(a)].append((n, a))
    else:
        cats['other'].append((n, None))
if len(sys.argv) > 1:
    for n, a in sorted(cats[' '.join(sys.argv[1:])], key=lambda x: x[1] or 0):
        print('0x%06X' % a if a else '        ', n)
else:
    for k, v in sorted(cats.items(), key=lambda x: -len(x[1])):
        print('%-12s %d' % (k, len(v)))
