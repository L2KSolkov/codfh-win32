"""rwmissed.py: functions compiled in build/src/rw/**.obj whose name matches an
unplaced image function (config/symbols.txt, with or without the leading
underscore) and whose bytes equal the image's with relocations masked.
Prints "SRC SYM ADDR" (and near misses with --near: first differing offset)."""
import os as _os_repo
_REPO = _os_repo.path.dirname(_os_repo.path.dirname(_os_repo.path.abspath(__file__)))  # the repository root, from this file's location
import glob
import os
import sys

sys.path.insert(0, _os_repo.path.join(_REPO, r'tools'))
from coff import Coff  # noqa: E402
from xbe import Xbe  # noqa: E402

ROOT = _REPO
near = '--near' in sys.argv
x = Xbe(os.path.join(ROOT, 'orig', 'Game_XboxMultiplayer.xbe'))
placed = set(int(l.split()[0], 16) for l in open(os.path.join(ROOT, 'config', 'compiled.txt')) if l.startswith('0x'))
byname = {}
for l in open(os.path.join(ROOT, 'config', 'symbols.txt')):
    p = l.split()
    if len(p) >= 5 and p[1] == 'function' and p[0].startswith('0x'):
        a = int(p[0], 16)
        if a not in placed:
            n = p[-1]
            byname.setdefault(n, []).append((a, int(p[2], 16)))
            if not n.startswith('_'):
                byname.setdefault('_' + n, []).append((a, int(p[2], 16)))
for obj in glob.glob(os.path.join(ROOT, 'build', 'src', 'rw', '**', '*.obj'), recursive=True):
    try:
        c = Coff(obj)
    except Exception:
        continue
    for s in c.symbols.values():
        if s.get('section', 0) <= 0 or s['name'] not in byname:
            continue
        try:
            code, rels = c.function_bytes(s)
        except Exception:
            continue
        code = bytes(code)
        mask = set()
        for off, _, _ in rels:
            mask.update(range(off, off + 4))
        for a, size in byname[s['name']]:
            b = x.read(a, max(size, len(code)))
            diff = [k for k in range(len(code)) if k not in mask and code[k] != b[k]]
            src = os.path.relpath(obj, os.path.join(ROOT, 'build')).replace('\\', '/')[:-4]
            if not diff and len(code) >= size:
                print('%s %s %06X' % (src, s['name'], a))
            elif near:
                print('NEAR %s %s %06X first diff +0x%X (ours %d, image %d bytes)' % (
                    src, s['name'], a, diff[0] if diff else len(code), len(code), size))
