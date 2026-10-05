"""piecesec.py FILE LO HI SECTION [rw]: moves the stand-in segments of FILE whose pieces lie in
[LO, HI) (image addresses) into SECTION, a library's merged data section (DSOUND_RD, XGRPH_RD):
read-only data unless `rw`. The pieces were cut from a code section's data tail, which the
library's /merge directive fills with its data sections after its code; in a code segment
they stayed with the code (PLAN M7). Their $L_ADDR labels become references to the piece's
label plus offset (in a data segment a label would end the piece for the placement build)."""
import re
import sys

p, lo, hi, sec = sys.argv[1], int(sys.argv[2], 16), int(sys.argv[3], 16), sys.argv[4]
rw = len(sys.argv) > 5 and sys.argv[5] == 'rw'
s = open(p, encoding='utf-8').read()
lines = s.split('\n')
# segments holding a piece in range
inrange, seg = set(), None
for l in lines:
    m = re.match(r'^(\w+) SEGMENT ', l)
    if m:
        seg = m.group(1)
    m = re.match(r'^; // match: \S+ @ 0x([0-9A-F]+)', l)
    if m and seg and lo <= int(m.group(1), 16) < hi:
        inrange.add(seg)
attr = "BYTE PUBLIC %sALIAS('%s') 'DATA'" % ('' if rw else 'READONLY ', sec)
out, repl, cur, piece, paddr = [], {}, None, None, None
for l in lines:
    m = re.match(r'^(\w+) SEGMENT (.*)$', l)
    if m:
        cur = m.group(1)
        if cur in inrange:
            l = '%s SEGMENT %s' % (cur, attr)
    m = re.match(r'^; // match: (\S+) @ 0x([0-9A-F]+)', l)
    if m:
        piece, paddr = m.group(1), int(m.group(2), 16)
    m = re.match(r'^\$L_([0-9a-f]+):$', l.strip())
    if m and cur in inrange and piece:
        a = int(m.group(1), 16)
        repl['$L_' + m.group(1)] = piece if a == paddr else '%s+%d' % (piece, a - paddr)
        continue
    # (a code piece's own label, `NAME:`, becomes a data label)
    m = re.match(r'^(\S+):$', l.strip())
    if m and cur in inrange and not m.group(1).startswith('$L_'):
        l = '%s LABEL BYTE' % m.group(1)
    out.append(l)
s = '\n'.join(out)
for k, v in repl.items():
    s = re.sub(r'(?<![\w$])' + re.escape(k) + r'(?!\w)', v, s)
open(p, 'w', encoding='utf-8', newline='\n').write(s)
print(len(inrange), 'segments,', len(repl), 'labels')
