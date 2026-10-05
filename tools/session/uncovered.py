"""uncovered.py [SECTION...]: the image's data no piece produces, classified by owner (PLAN M5/M6).

Each run of bytes coverage.py counts as `nothing` (no compiled piece, stand-in or fill) is given
its referencing objects (placed code and data whose relocations land in it) and its neighbours,
and a class: `xdk` (only XDK library objects refer to it and neighbour it: a data stand-in may
hold it, PLAN M3), `rw`, `rwa`, `bink`, `game` (any game unit refers to it or neighbours it on
both sides), else `mixed`. Prints the runs and totals per class."""
import bisect
import collections
import os
import struct
import sys

sys.path.insert(0, os.path.join(os.path.dirname(os.path.abspath(__file__)), '..'))
from coff import Coff, IMAGE_REL_I386_DIR32, IMAGE_REL_I386_REL32  # noqa: E402
from xbe import Xbe  # noqa: E402

ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
secs = sys.argv[1:] or ['.rdata', '.data']
image = Xbe(os.path.join(ROOT, 'orig', 'Game_XboxMultiplayer.xbe'))


def kind(o):
    o = o.replace('\\', '/')
    if 'src/recovered' in o or 'src/Source' in o:
        return 'game'
    if 'src/rws/' in o:
        return 'game'
    if 'src/rwa/' in o:
        return 'rwa'
    if 'src/rw/' in o:
        return 'rw'
    if 'src/bink' in o:
        return 'bink'
    if 'xdk' in o:
        return 'xdk'
    return 'other'


objs, pieces = {}, []
for l in open(os.path.join(ROOT, 'config', 'compiled.txt'), encoding='utf-8'):
    q = l.split()
    if len(q) < 3 or not q[0].startswith('0x'):
        continue
    a, o, n = int(q[0], 16), q[1], q[2]
    try:
        c = objs.get(o) or Coff(os.path.join(ROOT, o))
        objs[o] = c
        code, relocs = c.function_bytes(c.find_function(n))
    except Exception:
        continue
    pieces.append((a, a + len(code), o, code, relocs))
pieces.sort()
cover = []
for a, e, o, code, relocs in pieces:
    cover.append((a, e))
starts = [p[0] for p in pieces]
refs = collections.defaultdict(set)   # address -> referencing object kinds/names
for a, e, o, code, relocs in pieces:
    orig = image.read(a, len(code))
    for off, t, rt in relocs:
        if rt not in (IMAGE_REL_I386_DIR32, IMAGE_REL_I386_REL32) or off + 4 > len(orig):
            continue
        f = struct.unpack_from('<I', orig, off)[0]
        enc = a + off + 4 + struct.unpack('<i', struct.pack('<I', f))[0] if rt == IMAGE_REL_I386_REL32 else f
        refs[enc].add(o)
totals = collections.Counter()
for s in image.sections:
    if s['name'] not in secs:
        continue
    lo, hi = s['va'], s['va'] + min(s['vsize'], s['rsize'])
    cov = bytearray(hi - lo)
    for a, e in cover:
        for i in range(max(a, lo) - lo, min(e, hi) - lo):
            cov[i] = 1
    raw = bytes(image.read(lo, hi - lo))
    i = 0
    while i < hi - lo:
        if cov[i]:
            i += 1
            continue
        j = i
        while j < hi - lo and not cov[j]:
            j += 1
        a0, a1 = lo + i, lo + j
        if not (j - i < 16 and all(b in (0, 0xCC) for b in raw[i:j])):
            k = bisect.bisect_left(starts, a0)
            prev = pieces[k - 1][2] if k else ''
            nxt = pieces[k][2] if k < len(pieces) else ''
            rk = set()
            for x in range(a0, a1):
                rk |= refs.get(x, set())
            kinds = {kind(o) for o in rk}
            around = {kind(prev), kind(nxt)}
            if 'game' in kinds or around == {'game'}:
                cl = 'game'
            elif kinds and len(kinds) == 1:
                cl = next(iter(kinds))
            elif not kinds and len(around) == 1:
                cl = next(iter(around))
            else:
                cl = 'mixed'
            totals[(s['name'], cl)] += a1 - a0
            print('%-7s %-6s 0x%06X-0x%06X %5X  after %s  before %s  refs %s' % (
                s['name'], cl, a0, a1, a1 - a0, prev.split('/')[-1], nxt.split('/')[-1],
                ' '.join(sorted({o.split('/')[-1] for o in rk}))[:120]))
        i = j
for k, v in sorted(totals.items()):
    print('# %-7s %-6s %6X' % (k[0], k[1], v))
