"""rwbybytes.py [--near]: every function built from the tracked src/rw sources
that is not placed, against every unplaced image function of the same size
in the RenderWare range (0x24F88A-0x30DBF0), bytes compared with relocations
masked. Prints "SRC SYM ADDR NAME" for exact matches (and with --near the
closest same-size candidate by differing bytes)."""
import os as _os_repo
_REPO = _os_repo.path.dirname(_os_repo.path.dirname(_os_repo.path.abspath(__file__)))  # the repository root, from this file's location
import os
import subprocess
import sys

sys.path.insert(0, _os_repo.path.join(_REPO, r'tools'))
from coff import Coff, IMAGE_REL_I386_DIR32, IMAGE_REL_I386_REL32  # noqa: E402
import re  # noqa: E402
import struct  # noqa: E402
from xbe import Xbe  # noqa: E402

ROOT = _REPO
os.chdir(ROOT)
near = '--near' in sys.argv
x = Xbe(os.path.join(ROOT, 'orig', 'Game_XboxMultiplayer.xbe'))
placedrows = [l.split() for l in open('config/compiled.txt') if l.startswith('0x')]
placed = set(int(p[0], 16) for p in placedrows)
placedsym = set((p[1], p[2]) for p in placedrows)
known = {}
for p in placedrows:
    known.setdefault(p[2], int(p[0], 16))
for l in open('config/aliases.txt'):
    p = l.split()
    if len(p) >= 2 and not l.startswith('#') and p[1].startswith('0x'):
        known.setdefault(p[0], int(p[1], 16))
for l in open('config/symbols.txt'):
    p = l.split()
    if len(p) >= 5 and p[0].startswith('0x'):
        known.setdefault(p[-1], int(p[0], 16))
known = dict((k, v) for k, v in known.items() if not re.match(r'_\$E\d+$', k))
cands = {}
for l in open('config/symbols.txt'):
    p = l.split()
    if len(p) >= 5 and p[1] == 'function' and p[0].startswith('0x'):
        a = int(p[0], 16)
        if 0x24F88A <= a < 0x30DBF0 and a not in placed:
            cands.setdefault(int(p[2], 16), []).append((a, p[-1]))
tracked = [l.strip() for l in subprocess.run(['git', 'ls-files', 'src/rw'], capture_output=True, text=True).stdout.splitlines()
           if l.endswith('.c')]
for src in tracked:
    objrel = 'build/' + src[:-2] + '.obj'
    if not os.path.exists(objrel):
        continue
    c = Coff(objrel)
    for s in c.symbols.values():
        if s.get('section', 0) <= 0 or (objrel, s['name']) in placedsym:
            continue
        try:
            code, rels = c.function_bytes(s)
        except Exception:
            continue
        code = bytes(code)
        if len(code) < 8:
            continue
        mask = set()
        need = []
        for off, sym, typ in rels:
            mask.update(range(off, off + 4))
            if sym in known and typ == IMAGE_REL_I386_DIR32:
                need.append((off, known[sym] + struct.unpack_from('<I', code, off)[0], 'a'))
            elif sym in known and typ == IMAGE_REL_I386_REL32:
                need.append((off, known[sym], 'r'))
        best = None
        for a, name in cands.get(len(code), []):
            b = x.read(a, len(code))
            nd = sum(1 for k in range(len(code)) if k not in mask and code[k] != b[k])
            for off, g, kind in need:
                v = struct.unpack_from('<I', b, off)[0]
                if (kind == 'a' and (v & 0xFFFFFFFF) != (g & 0xFFFFFFFF)) or                         (kind == 'r' and ((a + off + 4 + struct.unpack_from('<i', b, off)[0]) & 0xFFFFFFFF) != g):
                    nd += 4
            if nd == 0:
                print('%s %s %06X %s' % (src[:-2], s['name'], a, name))
                best = None
                break
            if best is None or nd < best[0]:
                best = (nd, a, name)
        if near and best and best[0] <= len(code) // 8:
            print('NEAR %s %s %06X %s (%d of %d bytes differ)' % (src[:-2], s['name'], best[1], best[2], best[0], len(code)))
