"""ehorphan.py [--apply] LO HI: place EH tables whose handler thunk /OPT:ICF folded away (PLAN M5).

When two functions' EH handler thunks are identical (same-shaped function info, unwind maps that
reach identical funclets), /OPT:ICF keeps one thunk and one funclet, but both functions' .xdata
tables stay in the image, the folded one's referenced by nothing. Such a table is still named
from its own thunk in the object: `__ehhandler$F>1` (function info), `>1>8` (unwind map),
`>1>16` (try block map), `>1>16>16`, `>1>16>36`... (each try block's handler array).

For every uncovered .rdata run in [LO, HI), the objects placed around it are searched for
thunks whose function info is not placed; their tables, in the object's order, are laid
against the image from the run's start (byte-compared outside relocations), in object order,
skipping thunks that do not fit. With --apply the match lines go into the unit's sources
(after its last data match line below the address), the ranges into config/splits.txt and the
rows into config/compiled.txt."""
import os
import re
import struct
import sys

sys.path.insert(0, os.path.join(os.path.dirname(os.path.abspath(__file__)), '..'))
from coff import Coff  # noqa: E402
from xbe import Xbe  # noqa: E402

ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
args = sys.argv[1:]
apply = '--apply' in args
# --any: skip the link-order check (a recovered unit can instantiate more than the original did)
any_copy = '--any' in args
args = [a for a in args if a not in ('--apply', '--any')]
LO, HI = int(args[0], 16), int(args[1], 16)
image = Xbe(os.path.join(ROOT, 'orig', 'Game_XboxMultiplayer.xbe'))
splits = open(os.path.join(ROOT, 'config', 'splits.txt'), encoding='utf-8').read().split('\n')
rows = []
placed = {}
for l in open(os.path.join(ROOT, 'config', 'compiled.txt'), encoding='utf-8'):
    q = l.split()
    if len(q) >= 3 and q[0].startswith('0x'):
        rows.append((int(q[0], 16), q[1]))
        placed.setdefault(q[1], set()).add(q[2])
rows.sort()
# match lines not yet in compiled.txt count as placed too
for dp, _dn, fs in os.walk(os.path.join(ROOT, 'src')):
    for f in fs:
        if f.endswith(('.cpp', '.c')):
            full = os.path.join(dp, f)
            obj = 'build/' + os.path.relpath(full, ROOT).replace(os.sep, '/').rsplit('.', 1)[0] + '.obj'
            for m in re.finditer(r'^// match: (\S+) @ ', open(full, encoding='utf-8', errors='replace').read(), re.M):
                placed.setdefault(obj, set()).add(m.group(1))
aliased = set()   # folded (/OPT:ICF) functions: an object's copy whose code went
for l in open(os.path.join(ROOT, 'config', 'aliases.txt'), encoding='utf-8'):
    q = l.split()
    if len(q) >= 2 and not l.startswith('#') and q[1].startswith('0x'):
        aliased.add(q[0])
runs = []
for l in splits:
    p = l.split()
    if len(p) >= 4 and p[0].startswith('0x') and p[2] == '.rdata' and p[3] == '-':
        s, e = int(p[0], 16), int(p[1], 16)
        if LO <= s < HI:
            runs.append((s, e))
coffs = {}


# a function placed from no object at all was folded whole (its code dropped, its tables kept)
everywhere = set().union(*placed.values())
first, raw = {}, {}   # each object's first code address (its link order); object bytes
for a, o in rows:
    if a < 0x3C0000 and o not in first:
        first[o] = a


def coff(obj):
    if obj not in coffs:
        coffs[obj] = Coff(os.path.join(ROOT, obj)) if os.path.exists(os.path.join(ROOT, obj)) else None
    return coffs[obj]


def is_placed(obj, f):
    """F (decorated) is placed from OBJ, by that name or by its bare first component (sub_X)."""
    names = placed.get(obj, set())
    m = re.match(r'^\?(\w+)@@', f)
    if f in names or (m is not None and m.group(1) in names):
        return True
    if f not in aliased and (f in everywhere or (m is not None and m.group(1) in everywhere)):
        return False
    if any_copy:
        return True
    # a folded COMDAT: its tables come from the copy the linker kept, the first in link order
    key = ('__ehhandler$' + f).encode('latin-1')
    for other, _a in sorted(first.items(), key=lambda x: x[1]):
        if other == obj:
            return True
        if other.startswith('build/src/') and os.path.exists(os.path.join(ROOT, other)):
            if other not in raw:
                raw[other] = open(os.path.join(ROOT, other), 'rb').read()
            if key + b'\0' in raw[other]:
                return False
    return True


def chain(c, stub):
    """[(name, symbol)] of the thunk's tables, in the object's order."""
    out = []
    fi = c.find_function(stub + '>1')
    if fi is None:
        return []
    out.append((stub + '>1', fi))
    code, relocs = c.function_bytes(fi)
    for off, _t, _r in relocs:
        if off in (8, 16):
            s = c.find_function('%s>1>%d' % (stub, off))
            if s is not None:
                out.append(('%s>1>%d' % (stub, off), s))
            if off == 16:
                tcode, trel = c.function_bytes(s)
                for toff, _t2, _r2 in trel:
                    if toff % 20 == 16:
                        h = c.find_function('%s>1>16>%d' % (stub, toff))
                        if h is not None:
                            out.append(('%s>1>16>%d' % (stub, toff), h))
    out.sort(key=lambda x: (x[1]['section'], x[1]['value']))
    return out


def fits(c, pieces, at):
    """The pieces' addresses from AT if their bytes match the image there, else None."""
    res = []
    for name, sym in pieces:
        code, relocs = c.function_bytes(sym)
        at = (at + 3) & ~3
        img = bytes(image.read(at, len(code)))
        mask = bytearray(code)
        im = bytearray(img)
        for off, _t, _r in relocs:
            mask[off:off + 4] = b'\0\0\0\0'
            im[off:off + 4] = b'\0\0\0\0'
        if bytes(mask) != bytes(im):
            return None
        res.append((at, at + len(code), name))
        at += len(code)
    return res


plan, used = [], set()
for s, e in runs:
    before = [o for a, o in rows if a < s]
    after = [o for a, o in rows if a >= e]
    cands = []
    for o in ([before[-1]] if before else []) + ([after[0]] if after else []):
        if o not in cands:
            cands.append(o)
    at = s
    for o in cands:
        c = coff(o)
        if c is None:
            continue
        stubs = []
        for sym in c.symbol_list:
            # the thunk's function is this object's copy (a COMDAT's other copies were dropped)
            if sym['name'].startswith('__ehhandler$') and sym.get('section', 0) > 0 and \
                    (sym['name'] + '>1') not in placed.get(o, set()) and (o, sym['name']) not in used and \
                    is_placed(o, sym['name'][len('__ehhandler$'):]):
                ch = chain(c, sym['name'])
                if ch:
                    stubs.append((ch[0][1]['section'], ch[0][1]['value'], sym['name'], ch))
        stubs.sort()
        for _sec, _v, stub, ch in stubs:
            if at >= e:
                break
            r = fits(c, ch, at)
            if r and r[-1][1] <= e:
                for a0, e0, n in r:
                    plan.append((a0, e0, n, o))
                used.add((o, stub))
                at = r[-1][1]
    if at < e:
        rest = bytes(image.read(at, e - at))
        if any(rest):
            print('0x%06X-0x%06X: 0x%X bytes left at 0x%06X (%s)' % (s, e, e - at, at, ' '.join(cands)))
for a, e, n, o in plan:
    print('0x%06X-0x%06X %3X %s  %s' % (a, e, e - a, o, n))
if not apply:
    sys.exit(0)
bysrc = {}
for a, e, n, o in plan:
    base = os.path.join(ROOT, o[len('build/'):-len('.obj')])
    src = next((base + x for x in ('.cpp', '.c') if os.path.exists(base + x)), None)
    if src is None:
        print('no source for', o)
        continue
    bysrc.setdefault(src, []).append((a, n))
for src, items in bysrc.items():
    t = open(src, encoding='utf-8').read()
    for a, n in sorted(items):
        ml = '// match: %s @ 0x%08X\n' % (n, a)
        best = None
        for m in re.finditer(r'^// match: \S+ @ 0x([0-9A-F]+)\n', t, re.M):
            v = int(m.group(1), 16)
            if 0x3C0000 <= v < a and (best is None or v > best[0]):
                best = (v, m.end())
        if best:
            t = t[:best[1]] + ml + t[best[1]:]
        else:
            m = re.search(r'^// match: ', t, re.M)
            t = t[:m.start()] + ml + t[m.start():]
    open(src, 'w', encoding='utf-8', newline='\n').write(t)
for a, e, n, o in sorted(plan):
    res = []
    for l in splits:
        p = l.split()
        if len(p) >= 4 and p[0].startswith('0x') and p[3] == '-' and int(p[0], 16) <= a < int(p[1], 16):
            s0, e0, sc = int(p[0], 16), int(p[1], 16), p[2]
            if a > s0:
                res.append('0x%08X 0x%08X %-10s -' % (s0, a, sc))
            res.append('0x%08X 0x%08X %-10s %s' % (a, e, sc, n))
            if e < e0:
                res.append('0x%08X 0x%08X %-10s -' % (e, e0, sc))
        else:
            res.append(l)
    splits = res
open(os.path.join(ROOT, 'config', 'splits.txt'), 'w', encoding='utf-8', newline='\n').write('\n'.join(splits))
# their functions are committed already, so cmf adds no rows for them (pending.py skips EH lines)
with open(os.path.join(ROOT, 'config', 'compiled.txt'), 'a', encoding='utf-8', newline='\n') as f:
    for a, e, n, o in sorted(plan):
        f.write('0x%08X %s %s\n' % (a, o, n))
