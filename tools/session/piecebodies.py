"""piecebodies.py: XDK stand-in pieces whose bytes are an installed member's function (PLAN M7).

A stand-in piece (src/xdk/standin_*.asm, a config/compiled.txt row of build/src/xdk/standin_*)
that is byte for byte (relocation fields aside) the body of a function some XDK member
(build/xdk/<lib>/*.obj) defines, at the piece's full length, is that member's function: the
row belongs to the member, under the member's name, and the piece goes. Prints, per piece,
`ADDR PIECE -> MEMBER NAME` (every candidate when several members' bodies match)."""
import collections
import glob
import os
import re
import struct
import sys

sys.path.insert(0, os.path.join(os.path.dirname(os.path.abspath(__file__)), '..'))
from coff import Coff  # noqa: E402
from xbe import Xbe  # noqa: E402

ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
img = Xbe(os.path.join(ROOT, 'orig', 'Game_XboxMultiplayer.xbe'))

rows = []
for l in open(os.path.join(ROOT, 'config', 'compiled.txt'), encoding='utf-8'):
    q = l.split()
    if len(q) >= 3 and q[0].startswith('0x'):
        rows.append((int(q[0], 16), q[1], q[2]))
rows.sort()
size = {}
for l in open(os.path.join(ROOT, 'config', 'splits.txt'), encoding='utf-8'):
    q = l.split()
    if len(q) >= 2 and q[0].startswith('0x') and q[1].startswith('0x'):
        size[int(q[0], 16)] = int(q[1], 16) - int(q[0], 16)

# every member function: (length, bytes with relocation fields zeroed) -> [(member, name)]
bodies = collections.defaultdict(list)
for p in glob.glob(os.path.join(ROOT, 'build', 'xdk', '*', '*.obj')):
    try:
        c = Coff(p)
    except Exception:
        continue
    for x in c.symbol_list:
        if x['section'] <= 0 or x['class'] != 2:
            continue
        s = c.sections[x['section'] - 1]
        if not (s['chars'] & 0x20):
            continue
        try:
            code, rel = c.function_bytes(x)
        except Exception:
            continue
        b = bytearray(code)
        for o, t, ty in rel:
            b[o:o + 4] = b'\0\0\0\0'
        bodies[(len(b), bytes(b[:16]))].append((os.path.relpath(p, ROOT).replace(os.sep, '/'), x['name'], bytes(b), rel))

bylen = collections.defaultdict(list)
for k, v in bodies.items():
    bylen[k[0]].extend(v)
at = collections.defaultdict(set)
for a, o, n in rows:
    at[a].add(n)
alias = {}
for l in open(os.path.join(ROOT, 'config', 'aliases.txt'), encoding='utf-8'):
    q = l.split()
    if len(q) >= 2 and q[1].startswith('0x'):
        alias[q[0]] = int(q[1], 16)
MADE = re.compile(r'^_?(sub|unk|loc|off|dword|byte|word|stru|flt|dbl)_[0-9A-F]+$')


def score(a, raw, b, rel):
    """(contradictions, confirmations): relocations whose image target is a row of another
    name, and of the name itself (or its alias)."""
    bad = good = 0
    for off, tn, ty in rel:
        field = struct.unpack_from('<I', raw, off)[0]
        addend = struct.unpack_from('<i', b, off)[0]
        if ty == 20:
            t = (a + off + 4 + struct.unpack('<i', struct.pack('<I', field))[0]) & 0xFFFFFFFF
        elif ty == 6:
            t = field
        else:
            continue
        names = at.get(t)
        if alias.get(tn) == t or (names and tn in names):
            good += 1
        elif names and not all(MADE.match(x) for x in names):
            bad += 1
    return bad, good


for a, o, n in rows:
    if not o.startswith('build/src/xdk/standin_') or a >= 0x3CD300 or a not in size:
        continue
    ln = size[a]
    cands = []
    for trim in range(0, 16):
        L = ln - trim
        if L < 6:
            break
        try:
            raw = bytes(img.read(a, L))
        except Exception:
            break
        for path, name, b, rel in bylen.get(L, []):
            r = bytearray(raw)
            for off, t_, ty in rel:
                r[off:off + 4] = b'\0\0\0\0'
            if bytes(r) == b:
                cands.append((path, name, L, score(a, raw, b, rel)))
        if cands:
            break
    if len(cands) > 1:
        # several bodies agree: those whose relocations land where the image's do
        best = [c for c in cands if c[3][0] == 0]
        if best:
            top = max(c[3][1] for c in best)
            if top:
                cands = [c for c in best if c[3][1] == top]
    if cands:
        print('0x%08X %s -> %s' % (a, n, ' | '.join('%s %s (%d)' % (p, nm, L) for p, nm, L, s in cands)))
