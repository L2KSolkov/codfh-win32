"""ordtry70.py SRC [RULE] [/Dxxx ...]: compile SRC with the flags config/flags.txt gives the unit
RULE (default src/rwa/x.c: RenderWare Audio's VC7.0 /O2) and print its code sections in order
(PLAN M7: which source shapes make the compiler emit functions out of source order)."""
import os
import struct
import sys

sys.path.insert(0, os.path.join(os.path.dirname(os.path.abspath(__file__)), '..'))
from build_probes import compile_unit, flags_for, load_flags  # noqa: E402

src = sys.argv[1]
rule = sys.argv[2] if len(sys.argv) > 2 and not sys.argv[2].startswith('/') else 'src/rwa/x.c'
extra = [a for a in sys.argv[2:] if a.startswith('/')]
obj = os.path.join(os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__)))), 'build', 'tooltmp', 'ordtry70.obj')
out = []
if not compile_unit(src, obj, flags_for(rule, load_flags()) + extra, out):
    print('\n'.join(out))
    sys.exit(1)
d = open(obj, 'rb').read()
_, nsec, _, symptr, nsyms, optsize, _ = struct.unpack_from('<HHIIIHH', d, 0)
strtab = symptr + nsyms * 18
names = {}
i = 0
while i < nsyms:
    o = symptr + i * 18
    raw = d[o:o + 8]
    value, secno, typ, cls, naux = struct.unpack_from('<IhHBB', d, o + 8)
    if raw[:4] == b'\0\0\0\0':
        so = struct.unpack_from('<I', raw, 4)[0]
        n = d[strtab + so:d.index(b'\0', strtab + so)].decode('latin-1')
    else:
        n = raw.rstrip(b'\0').decode('latin-1')
    if cls in (2, 3) and secno > 0 and typ == 0x20:
        names.setdefault(secno, n)
    i += 1 + naux
print(' '.join(names[k] for k in sorted(names)))
