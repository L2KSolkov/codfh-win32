"""rwall.py SRC.c LO HI [flags...]: compile a RenderWare source with VC7.1
and match every function in the object against the image functions in
[LO, HI) (by size and bytes, relocations masked); prints each object
function with the image function it matches (or the closest)."""
import os as _os_repo
_REPO = _os_repo.path.dirname(_os_repo.path.dirname(_os_repo.path.abspath(__file__)))  # the repository root, from this file's location
import os, re, sys
sys.path.insert(0, _os_repo.path.join(_REPO, r'tools'))
from build_probes import ROOT, compile_unit
from coff import Coff
from xbe import Xbe

src, lo, hi = sys.argv[1], int(sys.argv[2], 16), int(sys.argv[3], 16)
extra = sys.argv[4:] or ['/O2', '/Ob2']
RW = r'D:\RW_372_src\RWSDK'
inc = [os.path.dirname(src), os.path.join(RW, 'build', 'noasm', 'include', 'null'), os.path.join(RW, 'src'),
       os.path.join(RW, 'src', 'plcore'), os.path.join(RW, 'driver', 'null'), os.path.join(RW, 'driver', 'common'),
       os.path.join(RW, 'os', 'win'), os.path.join(os.path.dirname(os.path.abspath(__file__)), 'rwshim')]
flags = ['/c', '/nologo', '/G6', '/Gy', '/W3', '/D_XBOX', '/DNDEBUG'] + extra + ['/I' + i for i in inc]
out = os.path.join(ROOT, 'build', 'rwprobe')
os.makedirs(out, exist_ok=True)
ob = os.path.join(out, os.path.splitext(os.path.basename(src))[0] + '.obj')
msgs = []
if not compile_unit(src, ob, flags, out=msgs):
    print('\n'.join(msgs)[:3000])
    sys.exit('compile failed')
img = Xbe(os.path.join(ROOT, 'orig', 'Game_XboxMultiplayer.xbe'))
funcs = []
for l in open(os.path.join(ROOT, 'config', 'symbols.txt')):
    p = l.split()
    if len(p) >= 5 and p[1] == 'function' and p[0].startswith('0x'):
        a = int(p[0], 16)
        if lo <= a < hi:
            funcs.append((a, int(p[2], 16), p[-1]))
c = Coff(ob)
names = sorted(set(s['name'] for s in c.symbols.values()
                   if s.get('section') and s.get('section') > 0 and s.get('type') == 0x20))
if not names:
    names = sorted(set(re.findall(rb'_[A-Za-z_][A-Za-z0-9_]{2,}', open(ob, 'rb').read())))
    names = [n.decode() for n in names]
used = set()
for n in names:
    i = c.find_function(n)
    if i is None:
        continue
    try:
        code, rel = c.function_bytes(i)
    except Exception:
        continue
    code = bytes(code)
    mask = set()
    for off, _, _ in rel:
        mask.update(range(off, off + 4))
    best = None
    for a, size, nm in funcs:
        b = img.read(a, len(code))
        d = sum(1 for k in range(len(code)) if k not in mask and code[k] != b[k])
        if best is None or (d, abs(size - len(code))) < best[0]:
            best = ((d, abs(size - len(code))), a, size, nm)
    (d, sd), a, size, nm = best
    print('%-40s len %#5x -> %#x %-40s size %#5x  %s' % (n, len(code), a, nm, size,
          'MATCH' if d == 0 and sd == 0 else 'diff %d' % d))
