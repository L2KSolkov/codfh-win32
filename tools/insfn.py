"""insfn.py UNIT BLK [OUT]: insert the function block BLK (starting with its
'// match: NAME @ 0xADDR' line) into UNIT before the next function's match
block (the smallest function address above ADDR; EH handler lines are not
functions), keeping that block's leading comment lines together. Writes OUT
(default: UNIT). Line endings follow UNIT."""
import re
import sys

unit, blkf = sys.argv[1], sys.argv[2]
out = sys.argv[3] if len(sys.argv) > 3 else unit
raw = open(unit, encoding='utf-8', newline='').read()
nl = '\r\n' if '\r\n' in raw else '\n'
u = raw.replace('\r\n', '\n')
blk = open(blkf, encoding='utf-8').read().replace('\r\n', '\n')
m = re.search(r'^// match: \S+ @ 0x([0-9A-Fa-f]+)$', blk, re.M)
addr = int(m.group(1), 16)
best = None
for m in re.finditer(r'^// match: (\S+) @ 0x([0-9A-Fa-f]+)\n', u, re.M):
    a = int(m.group(2), 16)
    if m.group(1).startswith('__ehhandler') or m.group(1).startswith('__unwind'):
        continue
    if a > addr and (best is None or a < best[0]):
        best = (a, m.start())
if best is None:
    i = len(u.rstrip('\n')) + 1
    u = u[:i] + '\n' + blk.rstrip('\n') + '\n'
else:
    j = best[1]
    # the match lines directly above belong to the same block
    while True:
        k = u.rfind('\n', 0, j - 1) + 1
        line = u[k:j - 1]
        if j > 0 and line.startswith('//'):
            j = k
        else:
            break
    u = u[:j] + blk.rstrip('\n') + '\n\n' + u[j:]
open(out, 'w', encoding='utf-8', newline='').write(u.replace('\n', nl))
print('inserted 0x%X before 0x%X' % (addr, best[0] if best else 0))
