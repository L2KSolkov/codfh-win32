"""vtplace.py [--apply] [UNIT...]: place the vtables still binary in .rdata (PLAN M5).

For each `??_7` name placed code references inside a binary .rdata range (or only the listed
units'), the referencing unit's compiled vtable is checked slot by slot against the image: a slot
whose name resolves (placed piece, symbols.txt, aliases.txt) must hold that address; a slot whose
name nothing resolves is an alias candidate (the name -> the image's slot value: an ICF fold, a
virtual placed under its database name). A vtable is placeable when it fits its range, every
resolved slot agrees and each candidate name gets one address across all vtables. With --apply:
the aliases go to config/aliases.txt, the match lines into the units' data blocks and the ranges
into config/splits.txt. Conflicts (a resolved slot that differs) are printed for hand work."""
import collections
import os
import re
import struct
import subprocess
import sys

sys.path.insert(0, os.path.join(os.path.dirname(os.path.abspath(__file__)), '..'))
import match  # noqa: E402
from coff import Coff, IMAGE_REL_I386_DIR32, IMAGE_REL_I386_REL32  # noqa: E402
from xbe import Xbe  # noqa: E402

ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
args = sys.argv[1:]
apply = '--apply' in args
only = [a for a in args if a != '--apply']
image = Xbe(match.ORIGINAL)

placed = {}
rows_by_addr = {}
for l in open(os.path.join(ROOT, 'config', 'compiled.txt'), encoding='utf-8'):
    q = l.split()
    if len(q) >= 3 and q[0].startswith('0x'):
        placed.setdefault((q[1], q[2]), int(q[0], 16))
        placed.setdefault((None, q[2]), int(q[0], 16))
        rows_by_addr[int(q[0], 16)] = q
gaps = []
for l in open(os.path.join(ROOT, 'config', 'splits.txt'), encoding='utf-8'):
    q = l.split()
    if len(q) >= 4 and q[0].startswith('0x') and q[2] == '.rdata' and q[3] == '-':
        gaps.append((int(q[0], 16), int(q[1], 16)))


def in_gap(a, size):
    return any(g0 <= a and a + size <= g1 for g0, g1 in gaps)


def resolve(target):
    a = match.resolve_name(target, {})
    if a is None:
        a = placed.get((None, target))
    return a


# vtables referenced by placed code into binary .rdata
cands = {}
for (obj, name), addr in list(placed.items()):
    if obj is None or 'build/src/' not in obj or obj.startswith('build/src/xdk'):
        continue
    unit = os.path.splitext(obj.split('/')[-1])[0]
    if only and unit not in only:
        continue
    try:
        c = Coff(os.path.join(ROOT, obj))
        code, relocs = c.function_bytes(c.find_function(name))
    except Exception:
        continue
    original = image.read(addr, len(code))
    for off, target, rtype in relocs:
        if not target.startswith('??_7') or rtype != IMAGE_REL_I386_DIR32:
            continue
        enc = struct.unpack_from('<I', original, off)[0] - struct.unpack_from('<i', code, off)[0]
        if in_gap(enc, 4) and enc not in rows_by_addr:
            cands.setdefault((target, enc), obj)

aliases = collections.defaultdict(set)
partial = collections.defaultdict(set)
plans = []
for (vt, addr), obj in sorted(cands.items(), key=lambda kv: kv[0][1]):
    c = Coff(os.path.join(ROOT, obj))
    sym = c.find_function(vt)
    if sym is None:
        print('%s: no %s in %s' % (hex(addr), vt, obj))
        continue
    code, relocs = c.function_bytes(sym)
    if not in_gap(addr, len(code)):
        print('0x%X %s: %d bytes do not fit a binary range' % (addr, vt, len(code)))
        continue
    img = image.read(addr, len(code))
    bad, want = [], {}
    for off, target, rtype in relocs:
        v = struct.unpack_from('<I', img, off)[0] - struct.unpack_from('<i', code, off)[0]
        r = resolve(target)
        if r is None:
            # an alias candidate: when the object compiles the function, its bytes must be the
            # image's at that address (an ICF fold of an identical body)
            if c.find_function(target) is not None and target.startswith('?'):
                ok, msg = match.compare(c, target, v, image, {})
                if not ok:
                    bad.append('slot %d %s: its body is not 0x%X\'s (%s)' % (off // 4, target, v, msg.split('\n')[0][-60:]))
                    continue
            want[target] = v
        elif r != v:
            # resolve_name may find a class's method by its bare database name (the base's): an
            # override this object compiles, byte for byte the image's slot function, is aliased
            al = match.link_aliases().get(target)
            if al is None and target.startswith('?') and c.find_function(target) is not None \
                    and match.compare(c, target, v, image, {})[0]:
                want[target] = v
                continue
            bad.append('slot %d %s -> 0x%X, image 0x%X' % (off // 4, target, r, v))
    if bad:
        print('0x%X %s (%s): %d differing slots: %s' % (addr, vt, obj.split('/')[-1], len(bad), '; '.join(bad[:3])))
        # its verified aliases (bodies compiled here, byte for byte the image's) still hold
        for t, v in want.items():
            if c.find_function(t) is not None:
                partial[t].add(v)
        continue
    for t, v in want.items():
        aliases[t].add(v)
    plans.append((addr, vt, obj, len(code), want))
clash = {t for t, vs in aliases.items() if len(vs) > 1}
ok = [p for p in plans if not clash & set(p[4])]
for p in plans:
    if p not in ok:
        print('0x%X %s: alias clash %s' % (p[0], p[1], sorted(clash & set(p[4]))[:3]))
print('%d vtables placeable, %d aliases' % (len(ok), len({t for p in ok for t in p[4]})))
extra = {t: next(iter(vs)) for t, vs in partial.items() if len(vs) == 1 and t not in clash
         and not (aliases.get(t, set()) - vs)}
if apply and extra:
    with open(os.path.join(ROOT, 'config', 'aliases.txt'), 'a', encoding='utf-8', newline='\n') as f:
        for t, v in sorted(extra.items()):
            if not any(t in p[4] for p in ok):
                f.write('%s 0x%08X  # vtable slot, its body the image\'s (vtplace.py)\n' % (t, v))
    print('%d aliases from vtables not yet whole' % len(extra))
if apply and ok:
    with open(os.path.join(ROOT, 'config', 'aliases.txt'), 'a', encoding='utf-8', newline='\n') as f:
        done = set()
        for p in ok:
            for t, v in sorted(p[4].items()):
                if t not in done:
                    f.write('%s 0x%08X  # vtable slot (vtplace.py)\n' % (t, v))
                    done.add(t)
    hdr = "// Its data (PLAN M5): literals, constants and tables where the image has them.\n"
    for addr, vt, obj, size, want in ok:
        src = os.path.splitext(obj[len('build/'):])[0]
        src = next(src + e for e in ('.cpp', '.c') if os.path.exists(os.path.join(ROOT, src + e)))
        full = os.path.join(ROOT, src)
        text = open(full, encoding='utf-8').read()
        ml = '// match: %s @ 0x%08X\n' % (vt, addr)
        if hdr in text:
            text = text.replace(hdr, hdr + ml, 1)
        else:
            m = re.search(r'^// match: ', text, re.M)
            text = text[:m.start()] + hdr + ml + '\n' + text[m.start():]
        open(full, 'w', encoding='utf-8', newline='\n').write(text)
    cut = {addr: (addr + size, vt) for addr, vt, obj, size, want in ok}
    res = []
    for l in open(os.path.join(ROOT, 'config', 'splits.txt'), encoding='utf-8').read().split('\n'):
        q = l.split()
        if len(q) >= 4 and q[0].startswith('0x') and q[3] == '-' and \
                any(int(q[0], 16) <= x < int(q[1], 16) for x in cut):
            s0, e0, s = int(q[0], 16), int(q[1], 16), q[2]
            cur = s0
            for x in sorted(x for x in cut if s0 <= x < e0):
                if x > cur:
                    res.append('0x%08X 0x%08X %-10s -' % (cur, x, s))
                res.append('0x%08X 0x%08X %-10s %s' % (x, cut[x][0], s, cut[x][1]))
                cur = cut[x][0]
            if cur < e0:
                res.append('0x%08X 0x%08X %-10s -' % (cur, e0, s))
        else:
            res.append(l)
    open(os.path.join(ROOT, 'config', 'splits.txt'), 'w', encoding='utf-8', newline='\n').write('\n'.join(res))
    subprocess.run([sys.executable, os.path.join(ROOT, 'tools', 'session', 'datablocks.py')], cwd=ROOT)
