"""xdkeh.py [--apply] [LO HI]: place the EH funclet sections (.text$x) of placed functions whose
unwind code sits in unplaced .text ranges.

Every placed function with an EH frame pushes its own `__ehhandler$F` address in its prologue; the
image's operand there gives the handler's address, so each handler maps to exactly one object
section (no guessing between byte-identical funclets). The section is placed at handler - offset,
one piece per symbol in it (`__unwindfunclet$...`, `__ehhandler$...`; the first funclet, which has
only a compiler label, as `SYMBOL-OFFSET`). Each piece is checked with match.compare. A piece that
does not start a range cuts it (config/splits.txt). With --apply, writes the cuts and the
config/compiled.txt rows."""
import os
import sys

sys.path.insert(0, os.path.join(os.path.dirname(os.path.abspath(__file__)), '..'))
import match  # noqa: E402
from coff import Coff  # noqa: E402
from xbe import Xbe  # noqa: E402

ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
CFG = os.path.join(ROOT, 'config')
args = sys.argv[1:]
apply = '--apply' in args
if apply:
    args.remove('--apply')
lo, hi = (int(args[0], 16), int(args[1], 16)) if len(args) == 2 else (0x300000, 0x30A000)

image = Xbe(match.ORIGINAL)
rows = []
for l in open(os.path.join(CFG, 'compiled.txt'), encoding='utf-8'):
    q = l.split()
    if len(q) >= 3 and q[0].startswith('0x'):
        rows.append((int(q[0], 16), q[1], q[2]))
placed = {r[0] for r in rows}

splits = []
for l in open(os.path.join(CFG, 'splits.txt'), encoding='utf-8'):
    p = l.split()
    if len(p) >= 4 and p[0].startswith('0x'):
        splits.append((int(p[0], 16), int(p[1], 16), p[2], p[3]))
todo = [s for s in splits if s[2] == '.text' and lo <= s[0] < hi and s[0] not in placed]


def containing(a):
    for s in splits:
        if s[0] <= a < s[1]:
            return s
    return None


objs = {}


def coff(path):
    if path not in objs:
        objs[path] = Coff(os.path.join(ROOT, path))
    return objs[path]


# handler address -> (object path, handler symbol)
handlers = {}
for addr, path, name in rows:
    if not path.endswith('.obj') or '-' in name or name.startswith('.'):
        continue
    try:
        c = coff(path)
        sym = c.find_function(name)
        if sym is None:
            continue
        code, relocs = c.function_bytes(sym)
    except Exception:
        continue
    for off, target, rtype in relocs:
        if target.startswith('__ehhandler$'):
            h = int.from_bytes(bytes(image.read(addr + off, 4)), 'little')
            handlers[h] = (path, target)

pieces = []
for a, e, sec, nm in todo:
    for h, (path, target) in sorted(handlers.items()):
        c = coff(path)
        hs = [y for y in c.symbol_list if y['name'] == target and y['section'] > 0]
        if not hs:
            continue
        section = c.sections[hs[0]['section'] - 1]
        base = h - hs[0]['value']
        if not (base <= a < base + section['size']):
            continue
        syms = sorted({y['value']: y for y in c.symbol_list
                       if y['section'] == section['index'] and not y['name'].startswith('$')
                       and not y['name'].startswith('.')}.values(), key=lambda y: y['value'])
        starts = sorted({0} | {y['value'] for y in syms})
        for off in starts:
            at = [y for y in syms if y['value'] == off]
            if at:
                name = at[0]['name']
            else:
                nxt = [y for y in syms if y['value'] > off][0]
                name = '%s-0x%X' % (nxt['name'], nxt['value'] - off)
            pieces.append((base + off, path, name))
        break

pieces = sorted(set(pieces))
cuts = [p[0] for p in pieces if p[0] not in {s[0] for s in splits}]
bad = 0
for addr, path, name in pieces:
    ok, msg = match.compare(coff(path), name, addr, image=image)
    if not ok and 'original continues' in msg and (
            addr + len(coff(path).function_bytes(coff(path).find_function(name))[0]) in
            ({s[0] for s in splits} | set(cuts))):
        ok = True
    if not ok or 'unverified' in msg:
        bad += 1
        print('BAD 0x%08X %s %s: %s' % (addr, path, name, msg.splitlines()[0][:160]))
    else:
        print('PIECE 0x%08X %s %s' % (addr, path, name))
left = [s for s in todo if not any(s[0] <= p[0] < s[1] for p in pieces)]
for s in left:
    print('LEFT 0x%08X 0x%08X %s' % (s[0], s[1], s[3]))
print('pieces %d, cuts %d, bad %d, ranges left %d' % (len(pieces), len(cuts), bad, len(left)))

if apply and not bad:
    cutset = set(cuts)
    res = []
    for l in open(os.path.join(CFG, 'splits.txt'), encoding='utf-8').read().split('\n'):
        p = l.split()
        if len(p) >= 4 and p[0].startswith('0x'):
            a, e = int(p[0], 16), int(p[1], 16)
            bounds = [a] + sorted(c for c in cutset if a < c < e) + [e]
            for k in range(len(bounds) - 1):
                res.append('0x%08X 0x%08X %-10s %s' % (bounds[k], bounds[k + 1], p[2],
                                                       p[3] if k == 0 else 'sub_%X' % bounds[k]))
        else:
            res.append(l)
    open(os.path.join(CFG, 'splits.txt'), 'w', encoding='utf-8', newline='\n').write('\n'.join(res))
    with open(os.path.join(CFG, 'compiled.txt'), 'a', encoding='utf-8', newline='\n') as f:
        for addr, path, name in pieces:
            if addr not in placed:
                f.write('0x%08X %s %s\n' % (addr, path, name))
