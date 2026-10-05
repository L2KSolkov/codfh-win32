"""run.py SRC [defines...]: compile with the game flags, print the code COMDATs in section order."""
import os as _os_repo
_REPO = _os_repo.path.dirname(_os_repo.path.dirname(_os_repo.path.dirname(_os_repo.path.abspath(__file__))))  # the repository root, from this file's location
import os
import subprocess
import sys

sys.path.insert(0, _os_repo.path.join(_REPO, 'tools'))
from coff import Coff  # noqa: E402

VC = r'C:\XDK\xbox\bin\vc71'
env = dict(os.environ)
env['PATH'] = VC + os.pathsep + r'C:\XDK\xbox\bin' + os.pathsep + env['PATH']
env['INCLUDE'] = r'C:\XDK\xbox\include'
src = sys.argv[1]
obj = os.path.splitext(src)[0] + '.obj'
flags = '/c /nologo /Od /Ob1 /Gy /GS /EHsc /GR- /G6 /GF /MT /W3 /D_XBOX'.split()
r = subprocess.run([os.path.join(VC, 'cl.exe')] + flags + ['/D' + d for d in sys.argv[2:]] + ['/Fo' + obj, src],
                   env=env, capture_output=True, text=True)
if r.returncode:
    print(r.stdout, r.stderr)
    sys.exit(1)
c = Coff(obj)
secs = {}
for s in c.symbol_list() if callable(getattr(c, 'symbol_list', None)) else c.symbols:
    pass
import struct
d = c.data
_, nsec, _, symptr, nsyms, optsize, _ = struct.unpack_from('<HHIIIHH', d, 0)
strtab = symptr + nsyms * 18
names = {}
i = 0
while i < nsyms:
    raw = d[symptr + i * 18:symptr + i * 18 + 8]
    value, secno, typ, cls, naux = struct.unpack_from('<IhHBB', d, symptr + i * 18 + 8)
    if raw[:4] == b'\0\0\0\0':
        o = struct.unpack_from('<I', raw, 4)[0]
        n = d[strtab + o:d.index(b'\0', strtab + o)].decode()
    else:
        n = raw.rstrip(b'\0').decode()
    if cls in (2, 3) and secno > 0 and typ == 0x20 and value == 0:
        names.setdefault(secno, n)
    i += 1 + naux
for k in sorted(names):
    print(k, names[k])
