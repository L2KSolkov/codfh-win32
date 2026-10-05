"""rwardata.py [--apply] LO HI: define RenderWare Audio's .rdata items in [LO, HI) (PLAN M5/M6).

Items start where placed code or data refers (by an address-carrying name, or the referenced
address); each runs to the next item. Owners follow link order: an item is the first of its
referencing RWA units that is not earlier than the previous item's owner, else the previous
owner's (the units' data is contiguous); the run starts from the RWA object placed just below LO.
A 16-byte item without pointers is a `const RwaUUID`; others go to tools/session/cdefine.py
(declared types) or ctable.py (opaque; `void *const` slots in .rdata). The defining unit's
own extern declarations of the name go. Prints the plan; --apply writes it."""
import os
import re
import struct
import subprocess
import sys

sys.path.insert(0, os.path.join(os.path.dirname(os.path.abspath(__file__)), '..'))
sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import m5defs  # noqa: E402
from xbe import Xbe  # noqa: E402

ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
args = sys.argv[1:]
apply = '--apply' in args
entries = None
for a in args:
    if a.startswith('--entries='):
        sz, rng = a[len('--entries='):].split(':')
        entries = (int(sz, 16), int(rng.split('-')[0], 16), int(rng.split('-')[1], 16))
# --owner=OBJ: every item to OBJ (where link order by code address does not hold)
force_owner = next((a[len('--owner='):] for a in args if a.startswith('--owner=')), None)
args = [a for a in args if a != '--apply' and not a.startswith(('--entries=', '--owner='))]
LO, HI = int(args[0], 16), int(args[1], 16)
image = Xbe(os.path.join(ROOT, 'orig', 'Game_XboxMultiplayer.xbe'))
place, rows, starts_placed = {}, [], set()
for l in open(os.path.join(ROOT, 'config', 'compiled.txt'), encoding='utf-8'):
    q = l.split()
    if len(q) >= 3 and q[0].startswith('0x'):
        a = int(q[0], 16)
        starts_placed.add(a)
        if not q[2].startswith(('__real@', '??_C@', '__xmm@')):   # pooled literals: anyone's
            rows.append((a, q[1]))
        if 'src/rwa/' in q[1] and a < 0x3C0000:
            place[q[1]] = min(place.get(q[1], 1 << 32), a)


def is_ptr(v):
    """A dword that is an address: the start of a placed piece (a UUID's bytes can look like one)."""
    return v in starts_placed


def src_of(obj):
    for d in ('src/rwa', 'src/rwa/xbox'):
        p = os.path.join(ROOT, d, os.path.basename(obj).replace('.obj', '.c'))
        if os.path.exists(p):
            return os.path.relpath(p, ROOT).replace(os.sep, '/')
    return None


items = {}
for l in open(os.path.join(ROOT, 'build', 'tooltmp', 'owners_rdata.txt'), encoding='utf-8'):
    m = re.match(r'^\s+0x([0-9A-F]+) (\S+)\s+(\S+) \(', l)
    if not m:
        continue
    a, obj, sym = int(m.group(1), 16), m.group(2), m.group(3)
    if not LO <= a < HI:
        continue
    name = sym[1:] if sym.startswith('_') and not sym.startswith('__') else None
    mm = re.search(r'_([0-9A-F]{6})(@|$)', sym)
    start = int(mm.group(1), 16) if mm and LO <= int(mm.group(1), 16) < HI else a
    if name is None:
        nm = re.match(r'^\?(\w+)@@', sym)
        name = nm.group(1) if nm else None
    if name is None:
        continue
    it = items.setdefault(start, {'names': set(), 'refs': set()})
    it['names'].add(name)
    s = src_of(obj)
    if s:
        it['refs'].add('build/' + s[:-2] + '.obj')
# data pointing into the range starts items too (tables of entries referenced one by one)
for sec in image.sections:
    if sec['name'] in ('.rdata', '.data'):
        blob = bytes(image.read(sec['va'], sec['vsize']))
        for i in range(0, len(blob) - 3, 4):
            v = struct.unpack_from('<I', blob, i)[0]
            if LO <= v < HI and v % 4 == 0 and v not in items:
                items[v] = {'names': {'unk_%06X' % v}, 'refs': set()}
starts = sorted(items)
below = [o for a, o in rows if a < LO and 'src/rwa/' in o]
prev = max((o for a, o in rows if a < LO and 'src/rwa/' in o), key=lambda o: max(a for a, oo in rows if oo == o and a < LO),
           default=None) if below else None
# the RWA object whose placed piece is just below LO
cand = [(a, o) for a, o in rows if a < LO]
cand.sort()
prev = cand[-1][1] if cand and 'src/rwa/' in cand[-1][1] else None   # after another library: no seed
plan = []
for k, a in enumerate(starts):
    e = starts[k + 1] if k + 1 < len(starts) else HI
    refs = sorted(items[a]['refs'], key=lambda o: place.get(o, 1 << 32))
    later = [o for o in refs if prev is None or place.get(o, 1 << 32) >= place.get(prev, 0)]
    owner = force_owner or (later[0] if later else prev)
    prev = owner
    names = sorted(items[a]['names'], key=lambda n: (not n.startswith('unk_'),
                                                     not re.match(r'(unk|off|dword|stru|flt|byte|word)_[0-9A-F]{6}$', n), n))
    if not re.match(r'(unk|off|dword|stru|flt|byte|word)_[0-9A-F]{6}$', names[0]):
        # a database name (`aM`, read as a string): the address name, in every RWA source
        new = 'unk_%06X' % a
        for dp, _dn, fs in os.walk(os.path.join(ROOT, 'src', 'rwa')):
            for f in fs:
                p = os.path.join(dp, f)
                if apply and f.endswith(('.c', '.h')):
                    t0 = open(p, encoding='utf-8').read()
                    t1 = re.sub(r'\b%s\b' % re.escape(names[0]), new, t0)
                    if t1 != t0:
                        open(p, 'w', encoding='utf-8', newline='\n').write(t1)
        names[0] = new
    raw = bytes(image.read(a, e - a))
    n16 = (e - a) // 16
    if n16 and not any(is_ptr(v) for v in struct.unpack('<%dI' % (4 * n16), raw[:16 * n16])) \
            and (e - a > 16 or (e - a) % 16 == 0):
        # UUIDs, the code naming the first; a tail after them is an item of its own
        for k2 in range(a, a + 16 * n16, 16):
            plan.append((k2, k2 + 16, names[0] if k2 == a else 'unk_%06X' % k2, owner))
        if a + 16 * n16 < e:
            plan.append((a + 16 * n16, e, 'unk_%06X' % (a + 16 * n16), owner))
        continue
    plan.append((a, e, names[0], owner))
if entries:
    # --entries=SIZE:LO-HI: a table of SIZE-byte entries, each its own item (all under 64 bytes,
    # as the image keeps them 4-aligned)
    size, lo2, hi2 = entries
    out = []
    for a, e, n, o in plan:
        if lo2 <= a < hi2 and e - a > size and (e - a) % size == 0:
            out.extend((k, k + size, n if k == a else 'unk_%06X' % k, o) for k in range(a, e, size))
        else:
            out.append((a, e, n, o))
    plan = out
for a, e, n, o in plan:
    print('0x%06X-0x%06X %4X %-14s %s' % (a, e, e - a, n, o))
if not apply:
    sys.exit(0)
hdr = "// Its data (PLAN M5): literals, constants and tables where the image has them.\n"
for a, e, n, o in plan:
    src = src_of(o)
    if not src:
        print('no source for', o)
        continue
    full = os.path.join(ROOT, src)
    raw = bytes(image.read(a, e - a))
    if e - a == 16 and not any(is_ptr(v) for v in struct.unpack('<4I', raw)):
        t = open(full, encoding='utf-8').read()
        t = re.sub(r'^extern [^;\n]*\b%s\b[^;\n]*;[^\n]*\n' % n, '', t, flags=re.M)
        open(full, 'w', encoding='utf-8', newline='\n').write(t)
        tl, tm, th = struct.unpack_from('<IHH', raw)
        node = ', '.join('0x%02X' % b for b in raw[8:])
        m5defs.insert(full, a, 'const RwaUUID %s = { 0x%08X, 0x%04X, 0x%04X, { %s } };' % (n, tl, tm, th, node))
        t = open(full, encoding='utf-8').read()
        ml = '// match: _%s @ 0x%08X\n' % (n, a)
        t = t.replace(hdr, hdr + ml, 1) if hdr in t else \
            t[:re.search(r'^// match: ', t, re.M).start()] + hdr + ml + '\n' + t[re.search(r'^// match: ', t, re.M).start():]
        open(full, 'w', encoding='utf-8', newline='\n').write(t)
        res = []
        for l in open(os.path.join(ROOT, 'config', 'splits.txt'), encoding='utf-8').read().split('\n'):
            p = l.split()
            if len(p) >= 4 and p[0].startswith('0x') and p[3] == '-' and int(p[0], 16) <= a < int(p[1], 16):
                s0, e0, sec = int(p[0], 16), int(p[1], 16), p[2]
                if a > s0:
                    res.append('0x%08X 0x%08X %-10s -' % (s0, a, sec))
                res.append('0x%08X 0x%08X %-10s _%s' % (a, e, sec, n))
                if e < e0:
                    res.append('0x%08X 0x%08X %-10s -' % (e, e0, sec))
            else:
                res.append(l)
        open(os.path.join(ROOT, 'config', 'splits.txt'), 'w', encoding='utf-8', newline='\n').write('\n'.join(res))
        print('uuid  ', n, src)
        continue
    txt = open(full, encoding='utf-8').read()
    decl = re.search(r'^extern\s+([^;\n]*?)\b' + n + r'\b\s*((?:\[\w*\])*)\s*;', txt, re.M)
    opaque = decl is None or (re.sub(r'\s', '', decl.group(1)) == 'RwUInt8' and decl.group(2) == '[]')
    tool = 'ctable.py' if opaque else 'cdefine.py'
    r = subprocess.run([sys.executable, os.path.join(ROOT, 'tools', 'session', tool), '--apply', src, n,
                        '0x%X' % a, '0x%X' % e], capture_output=True, text=True, cwd=ROOT)
    print(tool, n, src, 'ok' if r.returncode == 0 else 'FAIL ' + (r.stderr or r.stdout).strip().split('\n')[-1][:100])
