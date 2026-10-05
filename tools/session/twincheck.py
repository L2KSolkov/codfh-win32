"""twincheck.py: XDK member rows whose relocations land on rows of other names (PLAN M7).

A member function the M3 placement put at a structurally identical twin's address (the bodies
agree with relocation fields aside: CreateSoundBuffer and CreateSoundStream) relocates to the
twin's callees. For every XDK member row this compares each relocation's target name with the
row the image's field points at: a target row of another name, neither an alias of the name
(config/aliases.txt) nor a stand-in piece's made-up name, is printed as
`ROW_ADDR ROW_NAME +OFF: TARGET_NAME -> image ADDR ROW_THERE`."""
import bisect
import os
import re
import struct
import sys

sys.path.insert(0, os.path.join(os.path.dirname(os.path.abspath(__file__)), '..'))
from coff import Coff  # noqa: E402
from xbe import Xbe  # noqa: E402

ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
img = Xbe(os.path.join(ROOT, 'orig', 'Game_XboxMultiplayer.xbe'))
rows = []
for l in open(os.path.join(ROOT, 'config', 'compiled.txt'), encoding='utf-8'):
    q = l.split()
    if len(q) >= 3 and q[0].startswith('0x'):
        rows.append((int(q[0], 16), q[1], q[2]))
at = {}
for a, o, n in rows:
    at.setdefault(a, []).append(n)
alias = {}
for l in open(os.path.join(ROOT, 'config', 'aliases.txt'), encoding='utf-8'):
    q = l.split()
    if len(q) >= 2 and q[1].startswith('0x'):
        alias[q[0]] = int(q[1], 16)
MADE = re.compile(r'^_?(sub|unk|loc|off|dword|byte|word|stru|flt|dbl)_[0-9A-F]+$')
cache = {}
only = sys.argv[1] if len(sys.argv) > 1 else None
for a, o, n in sorted(rows):
    if not o.startswith('build/xdk/') or a >= 0x3CD300 or (only and only not in o):
        continue
    if o not in cache:
        try:
            cache[o] = Coff(os.path.join(ROOT, o))
        except Exception:
            cache[o] = None
    c = cache[o]
    if c is None:
        continue
    s = next((x for x in c.symbol_list if x['section'] > 0 and x['name'] == n), None)
    if s is None:
        continue
    try:
        code, rel = c.function_bytes(s)
    except Exception:
        continue
    for off, tn, rt in rel:
        if rt != 20 or tn.startswith('$') or tn.startswith('.'):
            continue
        v = struct.unpack('<i', img.read(a + off, 4))[0]
        t = (a + off + 4 + v - struct.unpack_from('<i', code, off)[0]) & 0xFFFFFFFF
        there = at.get(t)
        if not there or tn in there or alias.get(tn) == t:
            continue
        if all(MADE.match(x) for x in there):
            continue
        print('0x%08X %s +0x%X: %s -> image 0x%08X %s' % (a, n[:60], off, tn[:70], t, there[0][:70]))
