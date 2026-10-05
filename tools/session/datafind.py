"""datafind.py [OUT]: data pieces our objects define, located through placed code (PLAN M5).

For every placed compiled piece, each relocation to a symbol its own object defines in a data
section (.rdata/.data/.xdata/library data sections; literals ??_C@, __real@ constants, EH tables,
static data $SG/$T labels, vtables, globals) gives that symbol's image address: the address the
original encodes there, minus the addend. Every such (object, symbol, address) is checked with
match.compare (bytes and the piece's own relocations) and written to OUT as
`ADDR OBJ SYMBOL SIZE STATUS` (STATUS ok / differs / conflict). Symbols already placed are
skipped."""
import collections
import os
import struct
import sys

sys.path.insert(0, os.path.join(os.path.dirname(os.path.abspath(__file__)), '..'))
import match  # noqa: E402
from coff import Coff, IMAGE_REL_I386_DIR32, IMAGE_REL_I386_REL32  # noqa: E402
from xbe import Xbe  # noqa: E402

ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
out_path = sys.argv[1] if len(sys.argv) > 1 else os.path.join(ROOT, 'build', 'tooltmp', 'datafind.txt')
image = Xbe(match.ORIGINAL)

rows = []
for l in open(os.path.join(ROOT, 'config', 'compiled.txt'), encoding='utf-8'):
    q = l.split()
    if len(q) >= 3 and q[0].startswith('0x'):
        rows.append((int(q[0], 16), q[1], q[2]))
placed_names = {(p, n) for a, p, n in rows}
placed_addrs = {a for a, p, n in rows}

objs = {}


def coff(path):
    if path not in objs:
        objs[path] = Coff(os.path.join(ROOT, path))
    return objs[path]


DATA_KINDS = ('.rdata', '.data', 'BINKDATA', 'DOLBY', 'XON_RD', '.data1')
found = collections.defaultdict(set)
stable = {}   # (path, symbol) -> {addresses}
for addr, path, name in rows:
    try:
        c = coff(path)
        sym = c.find_function(name)
        if sym is None:
            continue
        code, relocs = c.function_bytes(sym)
    except Exception:
        continue
    if match.section_kind(c.sections[sym['section'] - 1]['name']) in DATA_KINDS:
        pass  # data pieces reference data too (vtables -> RTTI, tables -> strings)
    original = image.read(addr, len(code))
    for off, target, rtype in relocs:
        if rtype not in (IMAGE_REL_I386_DIR32, IMAGE_REL_I386_REL32):
            continue
        defs = [s for s in c.symbol_list if s['name'] == target and s['section'] > 0]
        if not defs:
            continue
        d = defs[0]
        kind = match.section_kind(c.sections[d['section'] - 1]['name'])
        if kind not in DATA_KINDS:
            continue
        if (path, target) in placed_names:
            continue
        addend = struct.unpack_from('<i', code, off)[0]
        field = struct.unpack_from('<I', original, off)[0]
        if rtype == IMAGE_REL_I386_REL32:
            enc = addr + off + 4 + struct.unpack('<i', struct.pack('<I', field))[0]
        else:
            enc = field
        found[(path, target)].add((enc - addend) & 0xFFFFFFFF)
        if target.startswith('$') and not name.startswith('$'):
            # a stable name for a compiler-numbered label: the reference that reaches it
            ref = '%s>%d' % (name, off)
            if (path, target) not in stable or len(ref) < len(stable[(path, target)]):
                stable[(path, target)] = ref

placed_at = {}
for a, p_, n in rows:
    placed_at.setdefault((p_, n), a)
global_at = {}
for a, p_, n in rows:
    try:
        sy = coff(p_).find_function(n)
        if sy is not None and sy['class'] not in (3, 6):
            global_at.setdefault(sy['name'], a)
    except Exception:
        pass


def link_ok(c, path, name, a):
    # resolve every relocation the way xbelink does and compare with the image's encoding
    sym = c.find_function(name)
    code, relocs = c.function_bytes(sym)
    original = image.read(a, len(code))
    for off, target, rtype in relocs:
        if rtype not in (IMAGE_REL_I386_DIR32, IMAGE_REL_I386_REL32):
            continue
        resolved = placed_at.get((path, target))
        if resolved is None:
            resolved = match.resolve_name(target, {})
        if resolved is None:
            resolved = global_at.get(target)
        if resolved is None:
            continue  # object-local: the section-kind check in match.compare
        addend = struct.unpack_from('<i', code, off)[0]
        field = struct.unpack_from('<I', original, off)[0]
        enc = a + off + 4 + struct.unpack('<i', struct.pack('<I', field))[0]             if rtype == IMAGE_REL_I386_REL32 else field
        if (enc - addend) & 0xFFFFFFFF != resolved:
            return False
    return True


res = []
for (path, target), addrs in sorted(found.items()):
    c = coff(path)
    if len(addrs) != 1:
        res.append((min(addrs), path, target, 0, 'conflict'))
        continue
    a = addrs.pop()
    if a in placed_addrs:
        continue
    try:
        if target.startswith('$') and not path.replace(chr(92), '/').startswith('build/xdk/'):
            if (path, target) not in stable:
                continue
            target = stable[(path, target)]
        sym = c.find_function(target)
        data, _ = c.function_bytes(sym)
    except Exception:
        continue
    try:
        ok, msg = match.compare(c, target, a, image=image)
        if ok and not link_ok(c, path, target, a):
            ok, msg = False, 'a relocation resolves elsewhere in the link'
    except Exception as e:  # outside the image's file bytes (.bss)
        ok, msg = False, str(e)
    status = ('ok' if 'unverified' not in msg else 'unverified: ' + msg.split('unverified:')[1][:120])         if ok else 'differs: ' + msg.splitlines()[0][:150]
    res.append((a, path, target, len(data), status))
with open(out_path, 'w', encoding='utf-8') as f:
    for r in sorted(res):
        f.write('0x%08X %s %s %d %s\n' % r)
ok = [r for r in res if r[4] == 'ok']
print('candidates %d, ok %d (%d bytes), differs %d, conflict %d'
      % (len(res), len(ok), sum(r[3] for r in ok),
         sum(1 for r in res if r[4].startswith('differs')), sum(1 for r in res if r[4] == 'conflict')))
