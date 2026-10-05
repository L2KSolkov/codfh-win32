"""pieceoffs.py [--apply]: stand-in references PIECE+N that leave the piece (PLAN M7).

After cuts a piece is shorter: `dd _unk_31F452+2` meant the image's 0x31F454, now a member's row
of its own (d3d8's "1.00.5849.1"). Such a reference, PIECE+N with the piece's range ending at or
before PIECE+N, becomes the address name there (`_unk_XXXXXX`, which match.py, xbelink and
xdkrepack resolve to the row at that address, plus any offset into it). Prints the plan; --apply
edits (adding EXTERNs)."""
import bisect
import glob
import os
import re
import sys

ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
rows = {}
for l in open(os.path.join(ROOT, 'config', 'compiled.txt'), encoding='utf-8'):
    q = l.split()
    if len(q) >= 3 and q[0].startswith('0x'):
        rows.setdefault(q[2], int(q[0], 16))
ext = {}
for l in open(os.path.join(ROOT, 'config', 'splits.txt'), encoding='utf-8'):
    q = l.split()
    if len(q) >= 2 and q[0].startswith('0x') and q[1].startswith('0x'):
        ext[int(q[0], 16)] = int(q[1], 16)
starts = sorted(set(rows.values()))
n = 0
for p in sorted(glob.glob(os.path.join(ROOT, 'src', 'xdk', 'standin_*.asm'))):
    t = open(p, encoding='utf-8').read()
    new_ext = set()

    def fix(m):
        global n
        name, off = m.group(1), int(m.group(2), 0)
        a = rows.get(name)
        if a is None or a not in ext or a + off < ext[a]:
            return m.group(0)
        tgt = a + off
        k = bisect.bisect_right(starts, tgt) - 1
        base = starts[k]
        nm = '_unk_%06X' % base
        new_ext.add(nm)
        n += 1
        print('%s: %s -> %s' % (os.path.basename(p), m.group(0), nm + ('+%d' % (tgt - base) if tgt != base else '')))
        return nm + ('+%d' % (tgt - base) if tgt != base else '')
    t2 = re.sub(r'(?<![\w$?@])(_(?:unk|sub)_[0-9A-F]{6,8})\+(0x[0-9A-Fa-f]+|\d+)', fix, t)
    if t2 != t and '--apply' in sys.argv:
        for nm in sorted(new_ext):
            if not re.search(r'^(EXTERN|PUBLIC) %s\b' % nm, t2, re.M) and not re.search(r'^%s\b' % nm, t2, re.M):
                first = re.search(r'^EXTERN ', t2, re.M)
                pos = first.start() if first else t2.index('\n') + 1
                t2 = t2[:pos] + 'EXTERN %s:BYTE\n' % nm + t2[pos:]
        open(p, 'w', encoding='utf-8', newline='\n').write(t2)
print(n, 'references')
