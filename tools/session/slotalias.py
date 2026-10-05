"""slotalias.py [--apply] [FIND]: alias rows for the names data pieces cannot resolve (M5).

datafind.py marks a piece `unverified` when a relocation names something no placed piece,
config/symbols.txt or config/aliases.txt resolves: a vtable slot naming a declared virtual
(`?vf_0A8@type_X@@...`) whose function is placed under its database name, a compiler-generated
deleting destructor (??_E) folded into another, a library global. The image's encoding at that
slot is the evidence of the name's address. A name is aliased only when every unverified
reference to it, across all pieces, gives the same address. With --apply, appends the rows to
config/aliases.txt."""
import collections
import os
import struct
import sys

sys.path.insert(0, os.path.join(os.path.dirname(os.path.abspath(__file__)), '..'))
import match  # noqa: E402
from coff import Coff, IMAGE_REL_I386_DIR32, IMAGE_REL_I386_REL32  # noqa: E402
from xbe import Xbe  # noqa: E402

ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
args = sys.argv[1:]
apply = '--apply' in args
args = [a for a in args if a != '--apply']
find = args[0] if args else os.path.join(ROOT, 'build', 'tooltmp', 'datafind.txt')
image = Xbe(match.ORIGINAL)
seen = collections.defaultdict(set)
evidence = {}
objs = {}
for l in open(find, encoding='utf-8'):
    p = l.split()
    if len(p) < 5 or not p[4].startswith('unverified'):
        continue
    addr, path, name = int(p[0], 16), p[1], p[2]
    c = objs.get(path) or Coff(os.path.join(ROOT, path))
    objs[path] = c
    code, relocs = c.function_bytes(c.find_function(name))
    original = image.read(addr, len(code))
    for off, target, rtype in relocs:
        if rtype not in (IMAGE_REL_I386_DIR32, IMAGE_REL_I386_REL32):
            continue
        if match.resolve_name(target, {}) is not None:
            continue
        if any(s['name'] == target and s['section'] > 0 for s in c.symbol_list):
            continue
        addend = struct.unpack_from('<i', code, off)[0]
        field = struct.unpack_from('<I', original, off)[0]
        enc = addr + off + 4 + struct.unpack('<i', struct.pack('<I', field))[0] \
            if rtype == IMAGE_REL_I386_REL32 else field
        seen[target].add((enc - addend) & 0xFFFFFFFF)
        evidence.setdefault(target, '%s +0x%X in the image (0x%08X)' % (name, off, addr))
rows = []
for target, addrs in sorted(seen.items()):
    if len(addrs) == 1:
        a = next(iter(addrs))
        if image.section_at(a) is not None:
            rows.append((target, a))
print('names %d, consistent %d' % (len(seen), len(rows)))
if apply and rows:
    have = {l.split()[0] for l in open(os.path.join(ROOT, 'config', 'aliases.txt'), encoding='utf-8')
            if l.strip() and not l.startswith('#')}
    with open(os.path.join(ROOT, 'config', 'aliases.txt'), 'a', encoding='utf-8', newline='\n') as f:
        for target, a in rows:
            if target not in have:
                f.write('%-29s 0x%08X  the address %s encodes (M5)\n' % (target, a, evidence[target]))
