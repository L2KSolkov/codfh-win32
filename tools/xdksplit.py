"""xdksplit.py: after tools/xdkplace.py, adjust config/splits.txt to the
placed XDK functions:

- a placed function's range ends where the function does when other bytes
  follow it in the range (code IDA did not split off, such as a member's
  static functions): the rest becomes its own binary range (`sub_ADDRESS`),
  so the placement linker keeps its original bytes instead of filling after
  the placed piece. Tails of 0xCC (what the linker fills) are left alone;
- a placed function that IDA split in two (it runs past its range's end)
  gets the ranges it covers merged into one, when nothing else is placed in
  them."""
import bisect
import os
import sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
from coff import Coff  # noqa: E402
from xbe import Xbe  # noqa: E402

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))


def read_ranges(lines):
    ranges = []
    for k, l in enumerate(lines):
        p = l.split()
        if len(p) >= 3 and p[0].startswith('0x'):
            ranges.append((int(p[0], 16), int(p[1], 16), k))
    ranges.sort()
    return ranges


def main():
    img = Xbe(os.path.join(ROOT, 'orig', 'Game_XboxMultiplayer.xbe'))
    spath = os.path.join(ROOT, 'config', 'splits.txt')
    lines = open(spath, encoding='utf-8').read().split('\n')
    cache = {}
    spans = []
    for l in open(os.path.join(ROOT, 'config', 'compiled.txt'), encoding='utf-8'):
        if not l.startswith('0x') or 'build/xdk/' not in l:
            continue
        a, obj, name = l.split(None, 2)
        a = int(a, 16)
        if obj not in cache:
            cache[obj] = Coff(os.path.join(ROOT, obj))
        c = cache[obj]
        code, _ = c.function_bytes(c.find_function(name.strip()))
        spans.append((a, a + len(code)))
    piece_starts = set(int(l.split()[0], 16) for l in open(os.path.join(ROOT, 'config', 'compiled.txt'))
                       if l.startswith('0x'))

    # a placed function that runs past its range's end (IDA split it, or
    # placed a boundary inside it): the range grows to the function's end and
    # the following ranges start after it (or go, when it covers them)
    merged = 0
    while True:
        ranges = read_ranges(lines)
        starts = [r[0] for r in ranges]
        done = True
        for a, end in sorted(spans):
            k = bisect.bisect_right(starts, a) - 1
            if k < 0 or end <= ranges[k][1]:
                continue
            nxt = [r for r in ranges[k + 1:] if r[0] < end]
            if any(r[0] in piece_starts for r in nxt):
                continue  # another piece is placed inside: the link reports it
            p = lines[ranges[k][2]].split(None, 3)
            lines[ranges[k][2]] = '%s 0x%08X %-10s %s' % (p[0], end, p[2], p[3] if len(p) > 3 else '')
            for r in sorted(nxt, key=lambda r: -r[2]):
                if r[1] <= end:
                    del lines[r[2]]
                else:
                    q = lines[r[2]].split(None, 3)
                    lines[r[2]] = '0x%08X %s %-10s %s' % (end, q[1], q[2], q[3] if len(q) > 3 else '')
            merged += 1
            done = False
            break
        if done:
            break

    # split the ranges a placed function ends inside
    ranges = read_ranges(lines)
    starts = [r[0] for r in ranges]
    new = []
    for end in sorted(set(e for _, e in spans)):
        k = bisect.bisect_right(starts, end - 1) - 1
        if k < 0:
            continue
        lo, hi, idx = ranges[k]
        if not (lo < end < hi) or end in piece_starts:
            continue
        rest = img.read(end, hi - end)
        if all(b == 0xCC for b in rest):
            continue
        new.append((end, hi, idx))
    # a range several placed pieces end inside is cut at each of those ends
    # into consecutive ranges
    cuts = {}
    for end, hi, idx in new:
        cuts.setdefault(idx, []).append(end)
    for idx in sorted(cuts, reverse=True):
        p = lines[idx].split(None, 3)
        hi = int(p[1], 16)
        ends = sorted(set(cuts[idx]))
        lines[idx] = '%s 0x%08X %-10s %s' % (p[0], ends[0], p[2], p[3] if len(p) > 3 else '')
        for k, end in enumerate(ends):
            nxt = ends[k + 1] if k + 1 < len(ends) else hi
            lines.insert(idx + 1 + k, '0x%08X 0x%08X %-10s sub_%X' % (end, nxt, p[2], end))
    open(spath, 'w', encoding='utf-8').write('\n'.join(lines))
    print('split %d ranges, merged %d' % (len(new), merged))


if __name__ == '__main__':
    main()
