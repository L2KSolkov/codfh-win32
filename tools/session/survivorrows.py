"""survivorrows.py: compiled.txt rows that name a folded twin where the image's own name
(config/symbols.txt) is a function another compiled object defines (PLAN M7: rows for a fold
survivor belong to the object that emits it; m7probe orders objects by their rows).

Prints ADDR, the row's object and name, and the object defining the image's name."""
import collections
import os
import struct
import sys

ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))


def defined(path):
    """External function names an object defines."""
    d = open(path, 'rb').read()
    _, nsec, _, symptr, nsyms, _, _ = struct.unpack_from('<HHIIIHH', d, 0)
    strtab = symptr + nsyms * 18
    out = set()
    i = 0
    while i < nsyms:
        o = symptr + i * 18
        raw = d[o:o + 8]
        value, secno, typ, cls, naux = struct.unpack_from('<IhHBB', d, o + 8)
        if cls == 2 and secno > 0 and typ == 0x20:
            if raw[:4] == b'\0\0\0\0':
                so = struct.unpack_from('<I', raw, 4)[0]
                out.add(d[strtab + so:d.index(b'\0', strtab + so)].decode('latin-1'))
            else:
                out.add(raw.rstrip(b'\0').decode('latin-1'))
        i += 1 + naux
    return out


names = {}
for l in open(os.path.join(ROOT, 'config', 'symbols.txt'), encoding='utf-8', errors='replace'):
    q = l.split()
    if len(q) >= 5 and q[0].startswith('0x') and q[1] == 'function':
        names[int(q[0], 16)] = q[4]
rows = []
objs = set()
for l in open(os.path.join(ROOT, 'config', 'compiled.txt'), encoding='utf-8'):
    q = l.split()
    if len(q) >= 3 and q[0].startswith('0x') and q[1].startswith('build/src/'):
        rows.append((int(q[0], 16), q[1], q[2]))
        objs.add(q[1])
by_name = collections.defaultdict(set)
for o in sorted(objs):
    p = os.path.join(ROOT, o)
    if os.path.exists(p):
        for n in defined(p):
            by_name[n].add(o)
row_names = set(n for a, o, n in rows)
for a, o, n in sorted(rows):
    img = names.get(a)
    if img and img != n and img not in row_names and by_name.get(img) and o not in by_name[img]:
        print('0x%06X %s %s -> %s defines %s' % (a, os.path.basename(o), n, ','.join(os.path.basename(x) for x in sorted(by_name[img])), img))
