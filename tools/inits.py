"""inits.py: list the unplaced dynamic initializers (0x3096E0-0x30DBF0) with
the global each constructs, how (ctor call / vector ctor / inline stores),
the matching exit function (0x30DBF0-), the units whose code references the
global, and the global's current declaration."""
import os as _os_repo
_REPO = _os_repo.path.dirname(_os_repo.path.dirname(_os_repo.path.abspath(__file__)))  # the repository root, from this file's location
import bisect
import glob
import os
import re
import struct
import sys

import capstone

sys.path.insert(0, _os_repo.path.join(_REPO, r'tools'))
from xbe import Xbe

ROOT = _REPO
x = Xbe(os.path.join(ROOT, 'orig', 'Game_XboxMultiplayer.xbe'))
names = {}
fs = []
for l in open(os.path.join(ROOT, 'config', 'symbols.txt')):
    p = l.split()
    if len(p) >= 5 and p[0].startswith('0x'):
        a = int(p[0], 16)
        names[a] = p[-1]
        if p[1] == 'function':
            fs.append((a, int(p[2], 16), p[-1]))
fs.sort()
st = [f[0] for f in fs]
placed = set(int(l.split()[0], 16) for l in open(os.path.join(ROOT, 'config', 'compiled.txt')) if l.startswith('0x'))
units = sorted(int(os.path.basename(f)[5:11], 16) for f in glob.glob(os.path.join(ROOT, 'src', 'recovered', 'unit_*.cpp')))
md = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)
code = x.read(0x12000, 0x3096E0 - 0x12000)


def unit_of(a):
    i = bisect.bisect_right(units, a) - 1
    return 'unit_%06X' % units[i] if i >= 0 else '?'


def refs(g):
    out = []
    for m in re.finditer(re.escape(struct.pack('<I', g)), code):
        a = 0x12000 + m.start()
        out.append(unit_of(a))
    return sorted(set(out))


def decode(a, size):
    ins = list(md.disasm(x.read(a, size), a))
    glob_ = None
    how = []
    for i in ins:
        s = i.op_str
        m = re.search(r'0x([45][0-9a-f]{5})\b', s)
        if m and glob_ is None and i.mnemonic in ('mov', 'push', 'lea'):
            glob_ = int(m.group(1), 16)
        if i.mnemonic == 'call':
            t = int(s, 16) if s.startswith('0x') else None
            how.append(names.get(t, s) if t else s)
    if not how:
        how = ['inline']
    return glob_, how


inits = [f for f in fs if 0x3096E0 <= f[0] < 0x30DBF0]
exits = [f for f in fs if 0x30DBF0 <= f[0] < 0x30F0F4]
for a, size, n in inits:
    if a in placed:
        continue
    g, how = decode(a, size)
    # the exit is the function the initializer registers (push <exit>; call atexit)
    ex = None
    for i in md.disasm(x.read(a, size), a):
        if i.mnemonic == 'push' and i.op_str.startswith('0x'):
            v = int(i.op_str, 16)
            if 0x30DBF0 <= v < 0x30F0F4:
                ex = v
    print('%06X %06X g=%s %-40s refs=%s' % (a, ex or 0, ('%06X' % g) if g else '?', ','.join(how)[:40],
                                              ','.join(refs(g)) if g else ''))
