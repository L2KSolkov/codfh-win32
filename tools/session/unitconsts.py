"""unitconsts.py [--apply] [LO HI]: the units' remaining header constants (PLAN M5).

Besides the frame time (frametime.py), each game unit's constant section holds its copies of
other header constants: pairs of 0.01f, 1.0/0.0 axis triples, -5.0f and the like, read from
memory under /Od or not at all. An uncovered float-like run in game .rdata joins the unit whose
constant it directly continues (a placed `flt_` item ending where the run starts) or directly
precedes, else the next unit (whose section it opens); each dword becomes
`extern const RwReal flt_ADDR = value;` in that unit's sorted data block. Runs holding strings,
pointers or odd values are left. Prints the plan; --apply writes the sources (match lines
follow from tools/session/ftmatch-style placement after a build)."""
import bisect
import os
import re
import struct
import sys

sys.path.insert(0, os.path.join(os.path.dirname(os.path.abspath(__file__)), '..'))
sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import m5defs  # noqa: E402
from xbe import Xbe  # noqa: E402

ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
args = sys.argv[1:]
apply = '--apply' in args
args = [a for a in args if a != '--apply']
LO, HI = (int(args[0], 16), int(args[1], 16)) if args else (0x3CD000, 0x3EB100)
image = Xbe(os.path.join(ROOT, 'orig', 'Game_XboxMultiplayer.xbe'))
rows = []
for l in open(os.path.join(ROOT, 'config', 'compiled.txt'), encoding='utf-8'):
    q = l.split()
    if len(q) >= 3 and q[0].startswith('0x'):
        a = int(q[0], 16)
        if 0x3C0000 <= a < 0x426000:
            rows.append((a, q[1], q[2]))
rows.sort()
addrs = [a for a, o, n in rows]
ends = {}
for l in open(os.path.join(ROOT, 'config', 'splits.txt'), encoding='utf-8'):
    p = l.split()
    if len(p) >= 4 and p[0].startswith('0x') and p[3] != '-':
        ends[int(p[0], 16)] = int(p[1], 16)
free = []
for l in open(os.path.join(ROOT, 'config', 'splits.txt'), encoding='utf-8'):
    p = l.split()
    if len(p) >= 4 and p[0].startswith('0x') and p[2] == '.rdata' and p[3] == '-':
        s, e = int(p[0], 16), int(p[1], 16)
        if LO <= s < HI:
            free.append((s, e))


def game(o):
    return o.startswith('build/src/') and not o.startswith(
        ('build/src/rw/', 'build/src/rwa/', 'build/src/xdk/', 'build/src/bink/'))


def unit_const(n):
    return re.search(r'flt_[0-9A-F]{6}', n) is not None


def floatlike(v):
    if v == 0:
        return True
    f = struct.unpack('<f', struct.pack('<I', v))[0]
    return f == f and 1e-6 <= abs(f) <= 1e9 and not (0x10000 <= v < 0x600000)


covered = []
for b, o, nm in rows:
    if b in ends:
        covered.append((b, ends[b]))
covered.sort()
cstarts = [c[0] for c in covered]


def is_covered(a):
    k = bisect.bisect_right(cstarts, a) - 1
    return k >= 0 and covered[k][0] <= a < covered[k][1]


texts = {}
for top in ('src', 'include'):
    for dp, _dn, fs in os.walk(os.path.join(ROOT, top)):
        for f in fs:
            if f.endswith(('.c', '.cpp', '.h')):
                texts[os.path.join(dp, f)] = open(os.path.join(dp, f), encoding='utf-8', errors='replace').read()
fix = []
known = set()
for dp, _dn, fs in os.walk(os.path.join(ROOT, 'src')):
    for f in fs:
        if f.endswith(('.c', '.cpp', '.h')):
            known.update(re.findall(r'\bflt_([0-9A-F]{6})\b', open(os.path.join(dp, f), encoding='utf-8', errors='replace').read()))
for dp, _dn, fs in os.walk(os.path.join(ROOT, 'include')):
    for f in fs:
        if f.endswith('.h'):
            known.update(re.findall(r'\bflt_([0-9A-F]{6})\b', open(os.path.join(dp, f), encoding='utf-8', errors='replace').read()))
# each run of dwords no placed piece covers is judged alone (a range can hold placed vtables
# and stray pointers beside the constants)
subruns = []
for s, e in free:
    a = (s + 3) & ~3
    start = None
    while a + 4 <= e:
        if is_covered(a):
            if start is not None:
                subruns.append((start, a))
                start = None
        elif start is None:
            start = a if a > s + 3 or a == s else s
        a += 4
    if start is not None:
        subruns.append((start, e))
plan = []
for s, e in subruns:
    a0 = (s + 3) & ~3
    n = (e - a0) // 4
    if n <= 0:
        continue
    vals = struct.unpack('<%dI' % n, bytes(image.read(a0, 4 * n)))
    if any(b for b in bytes(image.read(a0 + 4 * n, e - a0 - 4 * n))):
        continue
    # the dwords placed pieces already cover (a vtable placed inside the range) do not count
    live = [(k, v) for k, v in enumerate(vals) if not is_covered(a0 + 4 * k)]
    if not live or not all(floatlike(v) for k, v in live) or not any(v for k, v in live):
        continue
    # the unit whose constant this continues or precedes, else the next unit
    j = bisect.bisect_left(addrs, a0)
    owner = None
    if j > 0:
        b, o, nm = rows[j - 1]
        if unit_const(nm) and ends.get(b, b + 4) >= s - 3 and game(o):
            owner = o
    if owner is None and j < len(rows):
        b, o, nm = rows[j]
        if unit_const(nm) and b == a0 + 4 * n and game(o):
            owner = o
    if owner is None:
        nxt = next((o for b, o, nm in rows[j:] if game(o) and not nm.startswith(('??_C@', '__real@'))), None)
        owner = nxt
    if not owner:
        continue
    for k, v in enumerate(vals):
        a = a0 + 4 * k
        if is_covered(a):
            continue
        if ('%06X' % a) in known:
            # a name the sources declare: only plain `extern [const] RwReal flt_X;` declarations
            # (the non-const ones become const: the image keeps it in .rdata)
            nm = 'flt_%06X' % a
            decls = [(p0, m0) for p0, t0 in texts.items()
                     for m0 in re.finditer(r'^[^/\n]*\b%s\b[^\n]*$' % nm, t0, re.M)]
            plain = re.compile(r'^\s*extern\s+(const\s+)?RwReal\s+%s\s*;' % nm)
            # declarations of the name itself (a local `RwReal x = flt_X;` only reads it)
            uses = [d for d in decls if re.match(r'^\s*(extern\s+)?(static\s+)?(const\s+)?[A-Za-z_]\w*\s+\**\s*%s\s*[\[=;]'
                                                 % nm, d[1].group(0))]
            if not uses or not all(plain.match(d[1].group(0)) for d in uses):
                continue
            fix.extend(d for d in uses if not plain.match(d[1].group(0)).group(1))
        plan.append((a, v, owner))
for a, v, o in plan:
    print('0x%06X %-12r %s' % (a, struct.unpack('<f', struct.pack('<I', v))[0], o))
print(len(plan), 'constants in', len(set(o for a, v, o in plan)), 'units')
if not apply:
    sys.exit(0)


def fmt(v):
    f = struct.unpack('<f', struct.pack('<I', v))[0]
    for d in range(1, 10):
        t = '%.*f' % (d, f)
        if struct.pack('<f', float(t)) == struct.pack('<I', v):
            return t + 'f'
    return repr(f) + 'f'


for p0, m0 in fix:
    t0 = open(p0, encoding='utf-8').read()
    old = m0.group(0)
    t0 = t0.replace(old, re.sub(r'\bextern\s+RwReal\b', 'extern const RwReal', old), 1)
    open(p0, 'w', encoding='utf-8', newline='\n').write(t0)
for a, v, o in plan:
    base = os.path.join(ROOT, o[len('build/'):-len('.obj')])
    src = next((base + x for x in ('.cpp', '.c') if os.path.exists(base + x)), None)
    if not src:
        continue
    m5defs.insert(src, a, 'extern const RwReal flt_%06X = %s;' % (a, fmt(v)))
print('applied')
