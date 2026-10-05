"""segsplit.py [--apply]: split stand-in segments at gaps between their pieces (PLAN M7).

A segment of src/xdk/standin_*.asm holds pieces the image has back to back. When a piece in the
middle left (piece2member.py: it became its member's row), or a data segment's pieces surround
a member's datum (xvoice interp.obj's _function between two pieces), its pieces stay together
and the link lays them out together, without what sits between them in the image. Each segment
whose next piece does not start where the previous ends is ended there and a new segment of the
same attributes begins. A piece's end is counted from its db/dw/dd lines when it has nothing
else, else taken from config/splits.txt. Prints the plan; --apply edits."""
import glob
import os
import re
import sys

ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
apply = '--apply' in sys.argv
end = {}
for l in open(os.path.join(ROOT, 'config', 'splits.txt'), encoding='utf-8'):
    q = l.split()
    if len(q) >= 2 and q[0].startswith('0x') and q[1].startswith('0x'):
        end[int(q[0], 16)] = int(q[1], 16)
MATCH = re.compile(r'^; // match: (\S+) @ 0x([0-9A-F]{8})$')
SIZES = {'db': 1, 'dw': 2, 'dd': 4}


def data_size(lines):
    """Bytes the piece's lines emit, or None when they hold more than db/dw/dd data."""
    n = 0
    for x in lines:
        s = x.split(';', 1)[0].strip()
        if not s or s.startswith('PUBLIC ') or s.startswith('EXTERN ') or re.match(r'^\S+ LABEL BYTE$', s) \
                or re.match(r'^[\w$@?]+:$', s):
            continue
        m = re.match(r'^(db|dw|dd)\s+(.*)$', s)
        if not m or "'" in m.group(2) or 'DUP' in m.group(2).upper():
            return None
        n += SIZES[m.group(1)] * len([v for v in m.group(2).split(',') if v.strip()])
    return n


total = 0
for p in sorted(glob.glob(os.path.join(ROOT, 'src', 'xdk', 'standin_*.asm'))):
    raw = open(p, 'rb').read().decode('utf-8')
    nl = '\r\n' if '\r\n' in raw else '\n'
    L = raw.replace('\r\n', '\n').split('\n')
    names = set(re.findall(r'^(\w+) SEGMENT', raw.replace('\r\n', '\n'), re.M))
    # each piece's own end
    piece_end = {}
    for i, x in enumerate(L):
        mm = MATCH.match(x)
        if not mm:
            continue
        j = i + 1
        while j < len(L) and not MATCH.match(L[j]) and not re.match(r'^\w+ (ENDS|SEGMENT)', L[j]):
            j += 1
        a = int(mm.group(2), 16)
        sz = data_size(L[i + 1:j])
        piece_end[(i, a)] = a + sz if sz is not None else end.get(a)
    out = []
    seg = None          # (name, header line)
    prev_end = None
    n = 0
    inproc = 0
    for i, x in enumerate(L):
        if re.match(r'^\S+ PROC', x):
            inproc += 1
        elif re.match(r'^\S+ ENDP', x):
            inproc -= 1
        m = re.match(r'^(\w+) SEGMENT (.*)$', x)
        if m:
            seg = (m.group(1), m.group(2))
            prev_end = None
            out.append(x)
            continue
        if seg and re.match(r'^\w+ ENDS$', x):
            out.append('%s ENDS' % seg[0])
            seg = None
            continue
        mm = MATCH.match(x)
        if mm and seg:
            a = int(mm.group(2), 16)
            if prev_end is not None and a != prev_end and a > 0 and not inproc:
                # end the segment here and open a new one like it
                # (from the base name, a counter: names stay short however often it splits)
                base = re.sub(r'(_s\d+)+$', '', seg[0])
                k = 1
                while '%s_s%d' % (base, k) in names:
                    k += 1
                name = '%s_s%d' % (base, k)
                names.add(name)
                out.append('%s ENDS' % seg[0])
                out.append('')
                out.append('%s SEGMENT %s' % (name, seg[1]))
                out.append('')
                seg = (name, seg[1])
                n += 1
            prev_end = piece_end.get((i, a))
        out.append(x)
    if n:
        total += n
        print('%s: %d splits' % (os.path.basename(p), n))
        if apply:
            open(p, 'wb').write('\n'.join(out).replace('\n', nl).encode('utf-8'))
print(total, 'splits')
