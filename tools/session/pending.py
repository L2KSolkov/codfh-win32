"""pending.py [LO HI]: match lines not yet in config/compiled.txt, as tools/cmfm.py arguments.

Lists, per source unit, the `// match:` addresses (in [LO, HI) when given) that have no
compiled.txt row, EH pieces excluded (cmf adds them with their function), so a batch of new
definitions commits in one `python tools/cmfm.py -m "..." $(python tools/session/pending.py)`."""
import glob
import os
import re
import sys

ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
lo, hi = (int(sys.argv[1], 16), int(sys.argv[2], 16)) if len(sys.argv) > 2 else (0, 1 << 32)
rows = set()
for l in open(os.path.join(ROOT, 'config', 'compiled.txt'), encoding='utf-8'):
    if l.startswith('0x'):
        rows.add(int(l.split()[0], 16))
out = []
for src in sorted(glob.glob(os.path.join(ROOT, 'src', '**', '*.c*'), recursive=True)):
    if not src.endswith(('.c', '.cpp')):
        continue
    text = open(src, encoding='utf-8', errors='replace').read()
    addrs = [int(a, 16) for n, a in re.findall(r'^// match: (\S+) @ 0x([0-9A-Fa-f]+)$', text, re.M)
             if not n.startswith('__ehhandler')]
    addrs = [a for a in addrs if lo <= a < hi and a not in rows]
    if addrs:
        rel = os.path.splitext(os.path.relpath(src, os.path.join(ROOT, 'src')))[0].replace(os.sep, '/')
        out.append('%s:%s' % (rel.replace('recovered/', ''), ','.join('0x%X' % a for a in sorted(addrs))))
print(' '.join(out))
