"""xdataplace.py [--apply]: place mixed XDK members' own EH data (.xdata$x FuncInfo sections) by
their handlers, cutting the raw stand-in data pieces that hold the same bytes (PLAN M7).

A placed `__ehhandler$F` row of a member (build/xdk/...) loads its FuncInfo's address (`mov eax,
offset $Tn`, B8 imm32): the image's operand is where the member's .xdata$x section holding $Tn
goes (operand - $Tn's offset). When that section's bytes agree with the image there (relocated
dwords aside) and it lies inside raw stand-in data pieces (db lines only), the section's
symbols get rows and the pieces are cut around it (the parts before and after stay pieces, under
_unk_ADDR names). Prints the plan; --apply edits src/xdk/standin_data_*.asm,
config/compiled.txt and config/splits.txt."""
import bisect
import collections
import os
import re
import struct
import sys

sys.path.insert(0, os.path.join(os.path.dirname(os.path.abspath(__file__)), '..'))
from coff import Coff  # noqa: E402
from xbe import Xbe  # noqa: E402

ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
apply = '--apply' in sys.argv
img = Xbe(os.path.join(ROOT, 'orig', 'Game_XboxMultiplayer.xbe'))

rows = []
for l in open(os.path.join(ROOT, 'config', 'compiled.txt'), encoding='utf-8'):
    q = l.split()
    if len(q) >= 3 and q[0].startswith('0x'):
        rows.append((int(q[0], 16), q[1], q[2]))
rows.sort()
starts = [r[0] for r in rows]
named = set((o, n) for a, o, n in rows)
size = {}
for l in open(os.path.join(ROOT, 'config', 'splits.txt'), encoding='utf-8'):
    q = l.split()
    if len(q) >= 4 and q[0].startswith('0x'):
        size.setdefault(int(q[0], 16), int(q[1], 16) - int(q[0], 16))

# raw pieces: name -> (address, bytes length, source file, segment line range)
pieces = {}
for p in sorted(os.listdir(os.path.join(ROOT, 'src', 'xdk'))):
    if not re.match(r'standin_data_.*\.asm$', p):
        continue
    L = open(os.path.join(ROOT, 'src', 'xdk', p), encoding='utf-8').read().split('\n')
    i = 0
    while i < len(L):
        m = re.match(r'^; // match: (\S+) @ 0x([0-9A-F]{8})$', L[i])
        if m:
            j = i + 1
            raw = True
            n = 0
            while j < len(L) and not L[j].startswith('; // match:') and not re.match(r'^\w+ ENDS$', L[j]):
                s = L[j].strip()
                if s.startswith('db '):
                    n += len([x for x in s[3:].split(',') if x.strip()])
                elif s.startswith('dd ') or s.startswith('dw '):
                    raw = False
                j += 1
            pieces[m.group(1)] = (int(m.group(2), 16), n, p, i, j, raw)
            i = j
        else:
            i += 1
piece_at = sorted((v[0], k) for k, v in pieces.items())
piece_starts = [x[0] for x in piece_at]


def piece_covering(a):
    i = bisect.bisect_right(piece_starts, a) - 1
    if i < 0:
        return None
    n = piece_at[i][1]
    p = pieces[n]
    return n if p[0] <= a < p[0] + p[1] else None


cache = {}


def coff(o):
    if o not in cache:
        cache[o] = Coff(os.path.join(ROOT, o))
    return cache[o]


plans = []
seen = set()
# --rows: every data section of a member one of whose names has a row (its other bytes in
# raw pieces or in this member's rows)
if '--rows' in sys.argv:
    own_cover = collections.defaultdict(set)
    for a, o, n in rows:
        if o.startswith('build/xdk/'):
            own_cover[o].update(range(a, a + size.get(a, 0)))
    for a, o, n in rows:
        if not o.startswith('build/xdk/') or re.search(r'(-0x|>\d)', n) or not 0x3CD300 <= a < 0x540000:
            continue
        try:
            c = coff(o)
        except Exception:
            continue
        s = next((x for x in c.symbol_list if x['name'] == n and x['section'] > 0), None)
        if s is None:
            continue
        xs = c.sections[s['section'] - 1]
        if not re.match(r'[.](rdata|data|xdata)', xs['name']):
            continue
        key = (o, s['section'])
        if key in seen:
            continue
        seen.add(key)
        s0 = a - s['value']
        data = xs['data']
        if not data:
            continue
        imgd = img.read(s0, len(data))
        relocd = set()
        for va, si, ty in xs['relocs']:
            relocd.update(range(va, va + 4))
        if any(data[k] != imgd[k] for k in range(len(data)) if k not in relocd):
            continue
        inpiece = [k for k in range(len(data)) if piece_covering(s0 + k) is not None and pieces[piece_covering(s0 + k)][5]]
        if not inpiece:
            continue
        if any(not (k in set(inpiece) or (s0 + k) in own_cover[o]) for k in range(len(data))):
            continue
        syms = [(x['value'], x['name']) for x in c.symbol_list if x['section'] == s['section'] and x['name'] != xs['name']]
        if any((o, nm) in named and not any(r[0] == s0 + v and r[1] == o and r[2] == nm for r in rows) for v, nm in syms):
            continue
        # the piece bytes are cut as one range per contiguous run
        runs, run = [], None
        for k in inpiece:
            if run and k == run[1]:
                run[1] = k + 1
            else:
                run = [k, k + 1]
                runs.append(run)
        for lo_, hi_ in runs:
            plans.append((s0 + lo_, hi_ - lo_, o, sorted((v - lo_, nm) for v, nm in syms
                                                         if (o, nm) not in named and lo_ <= v < hi_)))
# --search: a raw piece's bytes found in a data section of the member whose row precedes it
obj_rows = dict(((o, n), a) for a, o, n in rows)
name_rows = {}
for a, o, n in rows:
    name_rows.setdefault(n, a)
if '--search' in sys.argv:
    own_cover = collections.defaultdict(set)
    for a, o, n in rows:
        if o.startswith('build/xdk/'):
            own_cover[o].update(range(a, a + size.get(a, 0)))
    for pn, (p0, plen, pf, pi, pj, raw) in sorted(pieces.items(), key=lambda x: x[1][0]):
        if not raw or plen == 0:
            continue
        i = bisect.bisect_left(starts, p0) - 1
        while i >= 0 and rows[i][1].startswith('build/src/xdk/'):
            i -= 1
        if i < 0 or not rows[i][1].startswith('build/xdk/'):
            continue
        o = rows[i][1]
        try:
            c = coff(o)
        except Exception:
            continue
        done_ = False
        for sn, xs in enumerate(c.sections, 1):
            if done_ or not re.match(r'[.](rdata|data)', xs['name']) or not xs['data']:
                continue
            if (o, sn) in seen:
                continue
            data = xs['data']
            relocd = set()
            for va, si, ty in xs['relocs']:
                relocd.update(range(va, va + 4))
            for off in range(len(data)):
                s0 = p0 - off
                if s0 + len(data) < p0 + 1:
                    continue
                imgd = img.read(s0, len(data))
                if any(data[k] != imgd[k] for k in range(len(data)) if k not in relocd):
                    continue
                # relocated dwords must point where their targets' rows are; at least 8
                # bytes must be checked one way or the other
                checked = len(data) - len(relocd)
                bad = False
                for va, si, ty in xs['relocs']:
                    tn = c.symbols[si]['name']
                    tr = obj_rows.get((o, tn)) or name_rows.get(tn)
                    if tr is None or ty != 6:
                        continue
                    add = struct.unpack_from('<I', data, va)[0]
                    if struct.unpack_from('<I', imgd, va)[0] != (tr + add) & 0xFFFFFFFF:
                        bad = True
                        break
                    checked += 4
                if bad or checked < 8:
                    continue
                inpiece = [k for k in range(len(data)) if piece_covering(s0 + k) is not None and pieces[piece_covering(s0 + k)][5]]
                if any(not (k in set(inpiece) or (s0 + k) in own_cover[o]) for k in range(len(data))):
                    continue
                syms = [(x['value'], x['name']) for x in c.symbol_list if x['section'] == sn and x['name'] != xs['name']]
                if any((o, nm) in named for v, nm in syms):
                    continue
                seen.add((o, sn))
                runs, run = [], None
                for k in inpiece:
                    if run and k == run[1]:
                        run[1] = k + 1
                    else:
                        run = [k, k + 1]
                        runs.append(run)
                for lo_, hi_ in runs:
                    plans.append((s0 + lo_, hi_ - lo_, o, sorted((v - lo_, nm) for v, nm in syms if lo_ <= v < hi_)))
                done_ = True
                break
for a, o, n in rows:
    if '--rows' in sys.argv or '--search' in sys.argv:
        break
    if not (o.startswith('build/xdk/') and n.startswith('__ehhandler$') and not re.search(r'-0x[0-9A-F]+$', n)):
        continue
    if img.read(a, 1) != b'\xb8':
        continue
    fi = struct.unpack('<I', img.read(a + 1, 4))[0]
    c = coff(o)
    s = next((x for x in c.symbol_list if x['name'] == n and x['section'] > 0), None)
    if s is None:
        continue
    sec = c.sections[s['section'] - 1]
    rel = [r for r in sec['relocs'] if r[0] == s['value'] + 1]
    if not rel:
        continue
    t = c.symbols[rel[0][1]]
    if t['section'] <= 0:
        continue
    xs = c.sections[t['section'] - 1]
    if not xs['name'].startswith('.xdata'):
        continue
    key = (o, t['section'])
    if key in seen:
        continue
    seen.add(key)
    s0 = fi - t['value']
    data = xs['data']
    imgd = img.read(s0, len(data))
    relocd = set()
    for va, si, ty in xs['relocs']:
        relocd.update(range(va, va + 4))
    if any(data[k] != imgd[k] for k in range(len(data)) if k not in relocd):
        continue
    syms = [(x['value'], x['name']) for x in c.symbol_list if x['section'] == t['section'] and x['name'] != xs['name']]
    # a symbol of it already placed must be where this placement puts it
    placed = [(v, nm) for v, nm in syms if (o, nm) in named]
    if any(not any(r[0] == s0 + v and r[1] == o and r[2] == nm for r in rows) for v, nm in placed):
        continue
    # the bytes before its first placed symbol must be in raw pieces (the rest is placed)
    end = min([v for v, nm in placed] + [len(data)])
    if end == 0:
        continue
    covered = all(piece_covering(s0 + k) is not None and pieces[piece_covering(s0 + k)][5] for k in range(end))
    if not covered:
        continue
    plans.append((s0, end, o, sorted((v, nm) for v, nm in syms if (o, nm) not in named)))
for s0, ln, o, syms in plans:
    print('0x%08X +%d %s %s' % (s0, ln, o.split('/')[-1], ' '.join('%s@+%d' % (nm, v) for v, nm in syms)))
print(len(plans), 'sections')
if not apply:
    sys.exit(0)

# cut the pieces: every piece's byte ranges minus the sections' ranges
taken = collections.defaultdict(list)       # piece name -> [(lo, hi)]
for s0, ln, o, syms in plans:
    for k in range(s0, s0 + ln):
        pass
    k = s0
    while k < s0 + ln:
        pn = piece_covering(k)
        p = pieces[pn]
        hi = min(s0 + ln, p[0] + p[1])
        taken[pn].append((k, hi))
        k = hi
by_file = collections.defaultdict(list)
for pn, rs in taken.items():
    by_file[pieces[pn][2]].append(pn)
newrows, gone = [], set()
for f, pns in by_file.items():
    path = os.path.join(ROOT, 'src', 'xdk', f)
    raw = open(path, 'rb').read().decode('utf-8')
    nl = '\r\n' if '\r\n' in raw else '\n'
    L = raw.replace('\r\n', '\n').split('\n')
    for pn in sorted(pns, key=lambda x: -pieces[x][3]):
        a0, ln, _, i, j, _ = pieces[pn]
        keep = []
        cur = a0
        for lo, hi in sorted(taken[pn]):
            if cur < lo:
                keep.append((cur, lo))
            cur = max(cur, hi)
        if cur < a0 + ln:
            keep.append((cur, a0 + ln))
        out = []
        for lo, hi in keep:
            nm = pn if lo == a0 else '_unk_%06X' % lo
            out += ['; // match: %s @ 0x%08X' % (nm, lo), 'PUBLIC %s' % nm, '%s LABEL BYTE' % nm]
            d = img.read(lo, hi - lo)
            for k in range(0, len(d), 16):
                out.append('        db ' + ', '.join('0%02Xh' % b for b in d[k:k + 16]))
            if nm != pn:
                newrows.append((lo, 'build/src/xdk/' + f[:-4] + '.obj', nm))
        if not keep or keep[0][0] != a0:
            gone.add(pn)
        # (a segment left with no piece keeps an empty body; MASM accepts it)
        L[i:j] = out
    open(path, 'wb').write('\n'.join(L).replace('\n', nl).encode('utf-8'))
cp = os.path.join(ROOT, 'config', 'compiled.txt')
lines = open(cp, encoding='utf-8').read().rstrip('\n').split('\n')
out = []
for l in lines:
    q = l.split()
    if len(q) >= 3 and q[0].startswith('0x') and q[1].startswith('build/src/xdk/standin_data_') and q[2] in gone:
        continue
    out.append(l)
for lo, o, nm in newrows:
    out.append('0x%08X %s %s' % (lo, o, nm))
for s0, ln, o, syms in plans:
    for v, nm in syms:
        out.append('0x%08X %s %s' % (s0 + v, o, nm))
open(cp, 'w', encoding='utf-8', newline='\n').write('\n'.join(out) + '\n')
print('rows: +%d, pieces gone %d' % (len(newrows) + sum(len(x[3]) for x in plans), len(gone)))
