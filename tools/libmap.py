"""libmap.py OBJDIR LO HI [-v]: map the functions of a library's extracted
objects (OBJDIR/*.obj) to the image's functions between LO and HI (hex), by
normalised instruction listings (ncmp's masking). Prints, per library
function, the best image function, its symbols.txt name and the ncmp
difference count; exact (0) matches first. Used for Bink with RAD's
binkxbox.lib (docs/reference/Bink)."""
import difflib
import glob
import os
import sys

S = os.path.dirname(os.path.abspath(__file__))
sys.path.insert(0, S)
import ncmp  # noqa: E402
from coff import Coff  # noqa: E402


def image_functions(lo, hi):
    out = []
    for l in open(os.path.join(os.path.dirname(S), 'config', 'symbols.txt')):
        p = l.split()
        if len(p) >= 5 and p[1] == 'function':
            a = int(p[0], 16)
            if lo <= a < hi:
                out.append((a, int(p[2], 16), p[4]))
    return out


def main():
    objdir, lo, hi = sys.argv[1], int(sys.argv[2], 16), int(sys.argv[3], 16)
    x = ncmp._img()
    imgs = []
    for a, size, name in image_functions(lo, hi):
        lst = ncmp._norm(x.read(a, size), a, [], False)
        while lst and lst[-1].strip() in ('nop', 'int3'):
            lst.pop()
        imgs.append((a, name, lst))
    rows = []
    for obj in sorted(glob.glob(os.path.join(objdir, '*.obj'))):
        c = Coff(obj)
        for s in c.symbols.values():
            if s.get('section', 0) <= 0 or s.get('type') != 0x20:
                continue
            code, rels = c.function_bytes(s)
            ours = ncmp._norm(bytes(code), 0, [o for o, _, _ in rels], True)
            while ours and ours[-1].strip() in ('nop', 'int3'):
                ours.pop()
            best = None
            for a, name, theirs in imgs:
                if abs(len(theirs) - len(ours)) > max(8, len(ours) // 4):
                    continue
                sm = difflib.SequenceMatcher(None, ours, theirs, autojunk=False)
                if sm.real_quick_ratio() < 0.6 or sm.quick_ratio() < 0.6:
                    continue
                n = 0
                for tag, i1, i2, j1, j2 in sm.get_opcodes():
                    if tag != 'equal':
                        n += max(i2 - i1, j2 - j1)
                if best is None or n < best[0]:
                    best = (n, a, name)
                    if n == 0:
                        break
            rows.append((os.path.basename(obj), s['name'], best))
    rows.sort(key=lambda r: (r[2] is None, r[2][0] if r[2] else 0))
    for obj, name, best in rows:
        if best:
            print('%-14s %-50s 0x%06X %-30s %d' % (obj, name, best[1], best[2], best[0]))
        else:
            print('%-14s %-50s none' % (obj, name))


if __name__ == '__main__':
    main()
