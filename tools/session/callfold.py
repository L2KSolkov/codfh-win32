"""callfold.py [--apply]: the folds callcheck.py's output (build/m7/callcheck_all.txt) shows,
as config/aliases.txt lines (PLAN M7).

A call our link binds to NAME where the image's call reaches the row of another function,
TARGET, is the image folding NAME into TARGET (identical bodies: the xgraphics optimizer's set
instances over Register and Instruction pointers). Each such NAME not yet an alias gets the
line `NAME 0xADDR  folded (/OPT:ICF) into TARGET (...)`, ADDR TARGET's row, so the placement
build resolves it there and the M7 probe folds it (M7FORCEFOLD). Prints the plan."""
import os
import re
import sys

ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
rows = {}
for l in open(os.path.join(ROOT, 'config', 'compiled.txt'), encoding='utf-8'):
    q = l.split()
    if len(q) >= 3 and q[0].startswith('0x'):
        rows.setdefault(q[2], int(q[0], 16))
aliased = set(l.split()[0] for l in open(os.path.join(ROOT, 'config', 'aliases.txt'), encoding='utf-8') if l.split())
plan = {}
for l in open(os.path.join(ROOT, 'build', 'm7', 'callcheck_all.txt'), encoding='utf-8', errors='replace'):
    m = re.search(r': (\S+) \(map 0x[0-9A-F]+\) -> image (\S+) \(map', l)
    if not m:
        continue
    name, target = m.group(1), m.group(2)
    if name in aliased or name in rows or target not in rows:
        continue
    plan.setdefault(name, target)
for n, t in sorted(plan.items()):
    print('%s -> %s 0x%08X' % (n[:80], t[:60], rows[t]))
print(len(plan), 'folds')
if '--apply' in sys.argv and plan:
    with open(os.path.join(ROOT, 'config', 'aliases.txt'), 'a', encoding='utf-8', newline='\n') as f:
        for n, t in sorted(plan.items()):
            f.write('%-29s 0x%08X  folded (/OPT:ICF) into %s (the image binds its calls there; '
                    'callfold.py)\n' % (n, rows[t], t))
