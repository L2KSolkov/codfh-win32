"""coverage.py [SECTION] [N]: how much of the image no placed piece produces (PLAN M5/M7).

Every config/compiled.txt row is sized from its object (as tools/xbelink.py places it; pieces
from stand-ins count separately, as transcriptions). Prints, per image section, its size, the
bytes compiled pieces cover, the bytes stand-ins (src/xdk/standin_*) cover and the bytes nothing
covers; with SECTION, its N largest uncovered runs with their neighbours."""
import bisect
import collections
import os
import sys

sys.path.insert(0, os.path.join(os.path.dirname(os.path.abspath(__file__)), '..'))
from coff import Coff  # noqa: E402
from xbe import Xbe  # noqa: E402

ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
want = sys.argv[1] if len(sys.argv) > 1 else None
top = int(sys.argv[2]) if len(sys.argv) > 2 else 25
image = Xbe(os.path.join(ROOT, 'orig', 'Game_XboxMultiplayer.xbe'))
objs = {}
pieces = []
for l in open(os.path.join(ROOT, 'config', 'compiled.txt'), encoding='utf-8'):
    q = l.split()
    if len(q) < 3 or not q[0].startswith('0x'):
        continue
    a, o, n = int(q[0], 16), q[1], q[2]
    try:
        c = objs.get(o) or Coff(os.path.join(ROOT, o))
        objs[o] = c
        code, _ = c.function_bytes(c.find_function(n))
    except Exception:
        continue
    pieces.append((a, a + len(code), 'standin' if 'standin' in o else 'compiled', o))
pieces.sort()
for s in image.sections:
    if want and s['name'] != want:
        continue
    lo, hi = s['va'], s['va'] + s['vsize']
    cov = bytearray(hi - lo)   # 0 nothing, 1 compiled, 2 stand-in
    for a, e, k, o in pieces:
        if e <= lo or a >= hi:
            continue
        v = 1 if k == 'compiled' else 2
        for i in range(max(a, lo) - lo, min(e, hi) - lo):
            if not cov[i]:
                cov[i] = v
    # bytes past the raw data (BSS-like tails) need no source
    raw_end = min(hi, lo + s['rsize'])
    # a short run of the linker's fill (0xCC in code, zeros in data) between pieces is alignment
    raw = bytes(image.read(lo, raw_end - lo))
    i = 0
    while i < raw_end - lo:
        if cov[i]:
            i += 1
            continue
        j = i
        while j < raw_end - lo and not cov[j]:
            j += 1
        if j - i < 16 and all(b in (0xCC, 0) for b in raw[i:j]):
            for k in range(i, j):
                cov[k] = 3
        i = j
    cnt = collections.Counter(cov[:raw_end - lo])
    print('%-10s size %7X  compiled %7X  stand-in %7X  fill %5X  nothing %7X' % (
        s['name'], raw_end - lo, cnt[1], cnt[2], cnt[3], cnt[0]))
    if want:
        runs, i = [], 0
        while i < raw_end - lo:
            if cov[i]:
                i += 1
                continue
            j = i
            while j < raw_end - lo and not cov[j]:
                j += 1
            runs.append((j - i, lo + i, lo + j))
            i = j
        starts = [p[0] for p in pieces]
        for size, a, e in sorted(runs, reverse=True)[:top]:
            k = bisect.bisect_left(starts, a)
            before = pieces[k - 1][3].split('/')[-1] if k else ''
            after = pieces[k][3].split('/')[-1] if k < len(pieces) else ''
            print('  0x%06X-0x%06X %5X  after %s  before %s' % (a, e, size, before, after))
