"""rowsync.py OLD NEW: after a split (unitsplit.py), make config/compiled.txt and the EH lines follow
the moved match lines (PLAN M7).

1. Every config/compiled.txt row at an address one of NEW's match lines gives, and naming OLD's
   object, gets NEW's object (match lines may give a short name, the rows the decorated one).
2. The EH-table match lines (`__ehhandler$NAME>1>8` and the like: pseudo-names, not object
   symbols, so rehome.py cannot see them) of every function NEW now has a row for move from
   OLD to NEW, with their rows."""
import os
import sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
from unitsplit import base_name, LINE  # noqa: E402

ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
CFG = os.path.join(ROOT, 'config', 'compiled.txt')


def rd(p):
    raw = open(p, 'rb').read().decode('utf-8', errors='surrogateescape')
    return ('\r\n' if '\r\n' in raw else '\n'), raw.replace('\r\n', '\n')


def objname(p):
    return 'build/' + os.path.splitext(os.path.relpath(os.path.abspath(p), ROOT))[0].replace(os.sep, '/') + '.obj'


old, new = sys.argv[1], sys.argv[2]
objo, objn = objname(old), objname(new)
nlo, to = rd(old)
nln, tn = rd(new)
rows = open(CFG, encoding='utf-8').read().split('\n')
addrs = set(int(m.group(2), 16) for m in (LINE.match(l) for l in tn.split('\n')) if m)
moved_rows = 0
for j, l in enumerate(rows):
    q = l.split()
    if len(q) >= 3 and q[0].startswith('0x') and q[1] == objo and int(q[0], 16) in addrs:
        rows[j] = l.replace(objo, objn, 1)
        moved_rows += 1
defined = set(q[2] for q in (l.split() for l in rows) if len(q) >= 3 and q[1] == objn)
go, keep = [], []
for l in to.split('\n'):
    m = LINE.match(l)
    if m and base_name(m.group(1)) in defined:
        go.append(l)
    else:
        keep.append(l)
if go:
    lines = tn.split('\n')
    at = max(i for i, l in enumerate(lines) if l.startswith(('#include', 'using namespace')))
    lines[at + 1:at + 1] = [''] + go
    open(new, 'wb').write('\n'.join(lines).replace('\n', nln).encode('utf-8', errors='surrogateescape'))
    open(old, 'wb').write('\n'.join(keep).replace('\n', nlo).encode('utf-8', errors='surrogateescape'))
    names = set(LINE.match(l).group(1) for l in go)
    for j, l in enumerate(rows):
        q = l.split()
        if len(q) >= 3 and q[1] == objo and q[2] in names:
            rows[j] = l.replace(objo, objn, 1)
open(CFG, 'w', encoding='utf-8', newline='\n').write('\n'.join(rows))
print('%d rows by address, %d EH lines moved' % (moved_rows, len(go)))
