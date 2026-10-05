"""xdkdata.py [--apply]: place the XDK library data that placed pieces reference by name (M3/M5).

Placed pieces (library members, stand-ins, our units) reference external data names (xvoice's
codebooks, dsound's AC3 images, ...) whose bytes are still binary. For each such name and the
image address the references encode, the installed libraries (and the xdklib/ copies) are
searched for a member defining it in a data section; the member is extracted to build/xdk/ and
the symbol compared there with match.compare (bytes and relocations, nothing unverified). With
--apply: a range of its own (cut from the binary range), the compiled.txt row and the member's
config/xdk_members.txt row. Run it again until it finds nothing (placed data references more)."""
import bisect
import collections
import os
import re
import struct
import sys

sys.path.insert(0, os.path.join(os.path.dirname(os.path.abspath(__file__)), '..'))
import match  # noqa: E402
from coff import Coff, IMAGE_REL_I386_DIR32, IMAGE_REL_I386_REL32  # noqa: E402
from lib import Library  # noqa: E402
from lib_scan import LIBRARIES, lib_path  # noqa: E402
from xbe import Xbe  # noqa: E402

ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
CFG = os.path.join(ROOT, 'config')
apply = '--apply' in sys.argv
image = Xbe(match.ORIGINAL)

placed_starts = {int(l.split()[0], 16) for l in open(os.path.join(CFG, 'compiled.txt'), encoding='utf-8')
                  if l.startswith('0x')}
ranges = []
for l in open(os.path.join(CFG, 'splits.txt'), encoding='utf-8'):
    p = l.split()
    if len(p) >= 4 and p[0].startswith('0x') and p[3] == '-' and not p[2].startswith('.text')             and int(p[0], 16) not in placed_starts:   # a stand-in piece may cover a '-' range
        ranges.append((int(p[0], 16), int(p[1], 16), p[2]))
ranges.sort()
rstarts = [r[0] for r in ranges]


def binary_range(a):
    k = bisect.bisect_right(rstarts, a) - 1
    if k >= 0 and ranges[k][0] <= a < ranges[k][1]:
        return ranges[k]
    return None


compiled = [l.split() for l in open(os.path.join(CFG, 'compiled.txt'), encoding='utf-8') if l.startswith('0x')]
placed_names = {q[2] for q in compiled}
need = collections.defaultdict(set)
objs = {}
for q in compiled:
    addr, path, name = int(q[0], 16), q[1], q[2]
    try:
        c = objs.get(path) or Coff(os.path.join(ROOT, path))
        objs[path] = c
        code, relocs = c.function_bytes(c.find_function(name))
    except Exception:
        continue
    original = image.read(addr, len(code))
    for off, target, rtype in relocs:
        if rtype not in (IMAGE_REL_I386_DIR32, IMAGE_REL_I386_REL32) or target in placed_names:
            continue
        if any(s['name'] == target and s['section'] > 0 for s in c.symbol_list):
            continue  # defined in its own object: datafind.py's job
        addend = struct.unpack_from('<i', code, off)[0]
        field = struct.unpack_from('<I', original, off)[0]
        enc = addr + off + 4 + struct.unpack('<i', struct.pack('<I', field))[0] \
            if rtype == IMAGE_REL_I386_REL32 else field
        enc = (enc - addend) & 0xFFFFFFFF
        if binary_range(enc):
            need[target].add(enc)
print('names to find: %d' % len(need))

libs = list(LIBRARIES) + ['xdklib/' + f for f in sorted(os.listdir(os.path.join(ROOT, 'xdklib')))
                          if f.endswith('.lib')]
defs = collections.defaultdict(list)   # name -> [(lib, member, body)]
for lib in libs:
    try:
        L = Library(lib_path(lib))
    except Exception:
        continue
    for member, body in L.members:
        if body[:2] != b'\x4c\x01':
            continue
        try:
            c = Coff(member, data=body)
        except Exception:
            continue
        for s in c.symbol_list:
            if s['class'] == 2 and s['section'] > 0 and s['name'] in need:
                defs[s['name']].append((lib, member, body))


def objpath_for(lib, member):
    base = lib.replace('xdklib/', 'xdklib_').replace('.lib', '')
    return 'build/xdk/%s/%s' % (base, re.sub(r'[\\/:]', '_', member))


found = []
for name, addrs in sorted(need.items()):
    if len(addrs) != 1:
        continue
    a = next(iter(addrs))
    for lib, member, body in defs.get(name, []):
        path = objpath_for(lib, member)
        full = os.path.join(ROOT, path)
        if not os.path.exists(full):
            os.makedirs(os.path.dirname(full), exist_ok=True)
            open(full, 'wb').write(body)
        c = Coff(full)
        sym = c.find_function(name)
        kind = match.section_kind(c.sections[sym['section'] - 1]['name'])
        if kind in (None, '.text'):
            continue
        ok, msg = match.compare(c, name, a, image=image)
        if ok and 'unverified' not in msg:
            size = len(c.function_bytes(sym)[0])
            r = binary_range(a)
            if a + size <= r[1]:
                found.append((a, path, name, size, lib, member))
                break
found.sort()
final, end = [], 0
for f in found:
    if f[0] >= end:
        final.append(f)
        end = f[0] + f[3]
for f in final:
    print('0x%08X %s %s %d' % f[:4])
print('pieces %d, bytes %d' % (len(final), sum(f[3] for f in final)))

if apply and final:
    cuts = {f[0]: (f[0] + f[3], f[2]) for f in final}
    res = []
    for l in open(os.path.join(CFG, 'splits.txt'), encoding='utf-8').read().split('\n'):
        p = l.split()
        if not (len(p) >= 4 and p[0].startswith('0x')) or p[3] != '-':
            res.append(l)
            continue
        lo, hi, sec = int(p[0], 16), int(p[1], 16), p[2]
        cur = lo
        for a in sorted(x for x in cuts if lo <= x < hi):
            e, name = cuts[a]
            if a > cur:
                res.append('0x%08X 0x%08X %-10s -' % (cur, a, sec))
            res.append('0x%08X 0x%08X %-10s %s' % (a, e, sec, name))
            cur = e
        if cur < hi:
            res.append('0x%08X 0x%08X %-10s -' % (cur, hi, sec))
    open(os.path.join(CFG, 'splits.txt'), 'w', encoding='utf-8', newline='\n').write('\n'.join(res))
    with open(os.path.join(CFG, 'compiled.txt'), 'a', encoding='utf-8', newline='\n') as f:
        for a, path, name, size, lib, member in final:
            f.write('0x%08X %s %s\n' % (a, path, name))
    man = os.path.join(CFG, 'xdk_members.txt')
    have = {l.split()[0] for l in open(man, encoding='utf-8') if l.strip() and not l.startswith('#')}
    with open(man, 'a', encoding='utf-8', newline='\n') as f:
        for a, path, name, size, lib, member in final:
            if path not in have:
                f.write('%s %s %s\n' % (path, lib, member))
                have.add(path)
