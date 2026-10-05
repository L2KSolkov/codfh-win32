"""crtplace.py [--apply] LO HI SECTION: place the objects' CRT initializer pointers (PLAN M5).

The image's .CRT$XCU (the C++ dynamic initializers, between ___xc_a and ___xc_z) and its kin
are each object's own .CRT$Xxx section, concatenated in link order: one pointer per initializer
function. For each pointer in [LO, HI) the placed function it points at names the object; the
object's whole SECTION piece (`SECTION+0`, every entry it has) is placed at its first pointer
once the following pointers agree with the object's relocations, in order. With --apply: the
match lines go into each unit's data block and config/splits.txt gets each piece's range."""
import os
import re
import struct
import subprocess
import sys

sys.path.insert(0, os.path.join(os.path.dirname(os.path.abspath(__file__)), '..'))
from coff import Coff  # noqa: E402
from xbe import Xbe  # noqa: E402

ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
args = sys.argv[1:]
apply = '--apply' in args
args = [a for a in args if a != '--apply']
lo, hi, sec = int(args[0], 16), int(args[1], 16), args[2]
image = Xbe(os.path.join(ROOT, 'orig', 'Game_XboxMultiplayer.xbe'))
placed = {}
for l in open(os.path.join(ROOT, 'config', 'compiled.txt'), encoding='utf-8'):
    q = l.split()
    if len(q) >= 3 and q[0].startswith('0x'):
        placed.setdefault(int(q[0], 16), (q[1], q[2]))



def real_piece(a):
    """Whether A is already placed by a compiled piece (a stand-in's label does not count)."""
    return a in placed and not placed[a][0].startswith('build/src/xdk/standin')


pieces = []   # (address, obj, entries)
a = lo
while a < hi:
    v = struct.unpack('<I', bytes(image.read(a, 4)))[0]
    if v not in placed:
        print('0x%X -> 0x%X: not placed' % (a, v))
        a += 4
        continue
    obj, name = placed[v]
    c = Coff(os.path.join(ROOT, obj))
    s = next((s for s in c.sections if s['name'] == sec), None)
    if s is None:
        print('0x%X -> 0x%X %s: %s has no %s' % (a, v, name, obj, sec))
        a += 4
        continue
    targets = [c.symbols[r[1]]['name'] for r in sorted(s['relocs'])]
    if not targets or targets[0] != name:
        print('0x%X: %s is not the first of %s %s %s' % (a, name, obj, sec, targets))
        a += 4
        continue
    ok = True
    for k, t in enumerate(targets):
        w = struct.unpack('<I', bytes(image.read(a + 4 * k, 4)))[0]
        if placed.get(w, (None, None)) != (obj, t):
            ok = False
            print('0x%X: entry %d of %s is 0x%X, not %s' % (a, k, obj, w, t))
            break
    if ok:
        pieces.append((a, obj, len(targets)))
        a += 4 * len(targets)
    else:
        a += 4
for p in pieces:
    print('0x%X %-50s %d' % p)
print('%d pieces, %d of %d entries' % (len(pieces), sum(p[2] for p in pieces), (hi - lo) // 4))

if apply and pieces:
    hdr = "// Its data (PLAN M5): literals, constants and tables where the image has them.\n"
    for addr, obj, n in pieces:
        src = os.path.splitext(obj[len('build/'):])[0]
        src = next(src + e for e in ('.cpp', '.c') if os.path.exists(os.path.join(ROOT, src + e)))
        full = os.path.join(ROOT, src)
        text = open(full, encoding='utf-8').read()
        # one piece per entry: each has a static label of its own ($S), so a piece ends at 4 bytes
        ml = ''.join('// match: %s+%d @ 0x%08X\n' % (sec, 4 * k, addr + 4 * k) for k in range(n)
                     if not real_piece(addr + 4 * k))
        if hdr in text:
            text = text.replace(hdr, hdr + ml, 1)
        else:
            m = re.search(r'^// match: ', text, re.M)
            text = text[:m.start()] + hdr + ml + '\n' + text[m.start():]
        open(full, 'w', encoding='utf-8', newline='\n').write(text)
    cut = {addr + 4 * k: (addr + 4 * k + 4, '%s+%d' % (sec, 4 * k)) for addr, obj, n in pieces for k in range(n)
           if not real_piece(addr + 4 * k)}
    res = []
    for l in open(os.path.join(ROOT, 'config', 'splits.txt'), encoding='utf-8').read().split('\n'):
        p = l.split()
        if len(p) >= 4 and p[0].startswith('0x') and p[3] == '-' and \
                any(int(p[0], 16) <= x < int(p[1], 16) for x in cut):
            s0, e0, s = int(p[0], 16), int(p[1], 16), p[2]
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
