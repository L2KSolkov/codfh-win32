"""comdatsel.py OBJ [NAME-substring]: each code COMDAT's selection (1 nodup, 2 any, ...) and name, in section order."""
import struct
import sys

d = open(sys.argv[1], 'rb').read()
pat = sys.argv[2] if len(sys.argv) > 2 else ''
_, nsec, _, symptr, nsyms, optsize, _ = struct.unpack_from('<HHIIIHH', d, 0)
strtab = symptr + nsyms * 18
sel, names = {}, {}
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
    if cls == 3 and naux == 1 and value == 0 and secno > 0 and n.startswith('.text'):
        sel[secno] = d[o + 18 + 14]
    elif cls in (2, 3) and secno > 0 and typ == 0x20:
        names.setdefault(secno, n)
    i += 1 + naux
for s in sorted(names):
    if pat in names[s]:
        print(s, sel.get(s), names[s])
