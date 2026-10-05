"""autoscalars.py [--apply] LO HI: define the scalar globals of a binary data gap in their units
(PLAN M5).

Each 4-byte slot of [LO, HI) gets an owner: the unit whose placed code references it (when
several do, the one whose name is declared in its own source, else the first), or, unreferenced,
the owner of the slot before it. Its name and type come from the referenced decorated name
(`?flt_X@@3MA` RwReal, `HA` RwInt32, `MB`/`HB` their const forms), or for an unreferenced slot
from its bytes (flt_ when they read as a plausible float). A slot referenced through a pointer,
struct or array name stops the run there (left for hand work). With --apply: the definitions go
into each unit's sorted m5defs block, the match lines into its data block, and each slot gets its own
config/splits.txt range; then commit with cmf per unit."""
import collections
import os
import re
import struct
import subprocess
import sys

sys.path.insert(0, os.path.join(os.path.dirname(os.path.abspath(__file__)), '..'))
from coff import Coff, IMAGE_REL_I386_DIR32, IMAGE_REL_I386_REL32  # noqa: E402
from xbe import Xbe  # noqa: E402
sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import m5defs  # noqa: E402

ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
args = sys.argv[1:]
apply = '--apply' in args
args = [a for a in args if a != '--apply']
lo, hi = int(args[0], 16), int(args[1], 16)
image = Xbe(os.path.join(ROOT, 'orig', 'Game_XboxMultiplayer.xbe'))
section = image.section_at(lo)['name']
const = section == '.rdata'

refs = collections.defaultdict(list)   # address -> [(unit source, decorated name)]
# objects link in the order of their code: a unit's place is its lowest placed code address
place = {}
for l in open(os.path.join(ROOT, 'config', 'compiled.txt'), encoding='utf-8'):
    q = l.split()
    if len(q) >= 3 and q[0].startswith('0x') and 'build/src/' in q[1] and int(q[0], 16) < 0x3C0000:
        s = os.path.splitext(q[1][len('build/'):])[0]
        for ext in ('.cpp', '.c'):
            if os.path.exists(os.path.join(ROOT, s + ext)):
                place[s + ext] = min(place.get(s + ext, 1 << 32), int(q[0], 16))
for l in open(os.path.join(ROOT, 'config', 'compiled.txt'), encoding='utf-8'):
    q = l.split()
    if len(q) < 3 or not q[0].startswith('0x') or 'build/src/' not in q[1]:
        continue
    addr, path, name = int(q[0], 16), q[1], q[2]
    try:
        c = Coff(os.path.join(ROOT, path))
        code, relocs = c.function_bytes(c.find_function(name))
    except Exception:
        continue
    original = image.read(addr, len(code))
    for off, target, rtype in relocs:
        if rtype not in (IMAGE_REL_I386_DIR32, IMAGE_REL_I386_REL32):
            continue
        field = struct.unpack_from('<I', original, off)[0]
        enc = addr + off + 4 + struct.unpack('<i', struct.pack('<I', field))[0] \
            if rtype == IMAGE_REL_I386_REL32 else field
        if lo <= enc < hi:
            src = os.path.splitext(path[len('build/'):])[0]
            for ext in ('.cpp', '.c'):
                if os.path.exists(os.path.join(ROOT, src + ext)):
                    refs[enc].append((src + ext, target))
                    break
# a name that carries an address (unk_427408) starts its object there, though the code may only
# reach into it (at +4)
for enc in list(refs):
    for src_, target in list(refs[enc]):
        m = re.match(r'^\?(?:dword|flt|unk|off|stru|byte|word|dbl)_([0-9A-F]{6})@@', target)
        if m:
            start = int(m.group(1), 16)
            if lo <= start < enc and (src_, target) not in refs[start]:
                refs[start].append((src_, target))


PLACED = {}
for l in open(os.path.join(ROOT, 'config', 'compiled.txt'), encoding='utf-8'):
    q = l.split()
    if len(q) >= 3 and q[0].startswith('0x'):
        PLACED.setdefault(int(q[0], 16), q[2])


def func_name(v):
    """The C name of the placed function at V (0 for null), or None."""
    if not v:
        return '0'
    sym = PLACED.get(v)
    m = re.match(r'^\?(\w+)@@Y', sym or '')
    if m:
        return m.group(1)
    m = re.match(r'^\?(\w+)@(\w+)@@S', sym or '')   # a static member function
    if m:
        return '%s::%s' % (m.group(2), m.group(1))
    if sym and re.match(r'^\w+$', sym):             # a row by its plain name
        return sym.lstrip('_') if sym.startswith('_sub_') else sym
    return None


def cstr_bytes(b):
    """A string literal for the bytes B."""
    r = ''
    for ch in b:
        c = chr(ch)
        r += BS + BS if c == BS else BS + '"' if c == '"' else c if 32 <= ch < 127 else BS + '%03o' % ch
    return '"' + r + '"'


def cstr(a):
    """A string literal for the string at A (0 for a null pointer)."""
    if not a:
        return '0'
    r = ''
    for ch in bytes(image.read(a, 512)).split(b'\0')[0]:
        c = chr(ch)
        r += BS + BS if c == BS else BS + '"' if c == '"' else c if 32 <= ch < 127 else BS + '%03o' % ch
    return '"' + r + '"'


BS = chr(92)
SCALARS = {'RwReal': ('f', 4), 'float': ('f', 4), 'RwInt32': ('i', 4), 'RwUInt32': ('u', 4), 'DWORD': ('u', 4),
           'RwBool': ('i', 4), 'RwInt16': ('h', 2), 'RwUInt16': ('H', 2), 'RwUInt8': ('B', 1),
           'RwInt8': ('b', 1), 'RwChar': ('b', 1), 'bool': ('B', 1)}


def parse_struct(sname, depth=0):
    """([(format, size, offset)], size) of a header struct of scalar, pointer, string, array and
    nested struct fields (natural alignment), or None when it has anything else."""
    for text in HEADERS.values():
        m = re.search(r'^struct %s\s*\{(.*?)^\};' % sname, text, re.M | re.S)
        if m:
            break
    else:
        return None
    out, off, align = [], 0, 1
    # an anonymous union initializes through its first member
    body = re.sub(r'//[^\n]*', '', m.group(1))
    body = re.sub(r'union\s*\{\s*([^;{}]+;)[^{}]*\};', r'\1', body)
    # member functions' bodies, enums and the like hold no data
    while True:
        b2 = re.sub(r'\{[^{}]*\}', ';', body)
        if b2 == body:
            break
        body = b2
    for line in body.split('\n'):
        line = line.split('//')[0].strip()
        fp = re.match(r'^[\w\s\*]+\(\s*\*\s*(\w+)\s*\)\s*\(.*\)\s*;$', line)
        if fp:
            # a function pointer field
            off = (off + 3) // 4 * 4
            out.append(('F', 4, off))
            off += 4
            align = max(align, 4)
            continue
        if not line or line == ';' or '(' in line or line.endswith(':') \
                or line.startswith(('static ', 'enum', 'typedef ', 'friend ', 'using ')):
            continue
        f = re.match(r'^(const RwChar \*|[\w:]+ ?\*+|\w+) ?(\w+)((?:\[\w+\])*);$', line)
        if not f:
            return None
        typ, dims = f.group(1).strip(), [int(d, 0) for d in re.findall(r'\[(\w+)\]', f.group(3))]
        n = 1
        for d in dims:
            n *= d
        if typ in ('const RwChar *', 'RwChar *'):
            item = [('s', 4, 0)], 4, 4
        elif typ == 'RwChar' and dims:
            # a character array: one string field
            out_off = (off + 0)
            out.append(('c', n, out_off))
            off += n
            continue
        elif typ.endswith('*'):
            item = [('p', 4, 0)], 4, 4
        elif typ in SCALARS:
            item = [(SCALARS[typ][0], SCALARS[typ][1], 0)], SCALARS[typ][1], SCALARS[typ][1]
        else:
            sub = parse_struct(typ, depth + 1) if depth < 4 else None
            if typ in ('RwV3d', 'RwV2d', 'RwRGBAReal', 'RwSphere', 'RwTexCoords'):
                sub = ([('f', 4, 4 * k) for k in range(len(STRUCTS[typ]))], 4 * len(STRUCTS[typ]))
            elif typ == 'RwRGBA':
                sub = ([('B', 1, k) for k in range(4)], 4)
            if not sub:
                return None
            item = sub[0], sub[1], max(s for _, s, _ in sub[0])
        fields, size, al = item
        off = (off + al - 1) // al * al
        for k in range(n):
            out += [(fm, sz, off + k * size + o) for fm, sz, o in fields]
        off += n * size
        align = max(align, al)
    return out, (off + align - 1) // align * align


# RenderWare structs by their fields (f float, i int32, B byte)
STRUCTS = {'RwV3d': 'fff', 'RwV2d': 'ff', 'RwRGBA': 'BBBB', 'RwRGBAReal': 'ffff', 'RwSphere': 'ffff',
           'RwTexCoords': 'ff'}


def is_string(v):
    """Whether V points at a printable, terminated string in .rdata."""
    s = image.section_at(v) if v else None
    if not s or s['name'] != '.rdata':
        return False
    b = bytes(image.read(v, 256)).split(bytes(1))
    return len(b) > 1 and all(32 <= c < 127 or c in (9, 10, 13) or c >= 0xA0 for c in b[0])


def float_lit(bits):
    v = struct.unpack('<f', struct.pack('<I', bits))[0]
    if abs(v) < 1e7:
        for k in range(0, 10):
            s = '%.*f' % (k, v)
            if struct.pack('<f', float(s)) == struct.pack('<I', bits):
                return (s if '.' in s else s + '.0') + 'f'
    for d in range(1, 10):
        s = '%.*g' % (d, v)
        if struct.pack('<f', float(s)) == struct.pack('<I', bits):
            return s + 'f'
    return repr(v) + 'f'


TYPES = {'MA': 'RwReal', 'HA': 'RwInt32', 'MB': 'const RwReal', 'HB': 'const RwInt32',
         'PBDB': 'const RwChar *', 'PBDA': 'const RwChar *', '_NA': 'bool', '_NB': 'const bool', 'EA': 'RwUInt8', 'FA': 'RwInt16', 'GA': 'RwUInt16', 'FB': 'const RwInt16', 'GB': 'const RwUInt16', 'EB': 'const RwUInt8', 'DA': 'RwChar', 'KA': 'DWORD', 'IA': 'RwUInt32', 'KB': 'const DWORD', 'IB': 'const RwUInt32'}
HEADERS = {}
for d, _, fs in os.walk(os.path.join(ROOT, 'include')):
    for f in fs:
        if f.endswith('.h'):
            HEADERS[os.path.join(d, f)] = open(os.path.join(d, f), encoding='utf-8', errors='replace').read()
FALLBACK = '?'
NS = {}
slots = []
owner = None
# the owner before LO: the object of the placed piece just before it (its successors come no earlier)
prev_rows = [l.split() for l in open(os.path.join(ROOT, 'config', 'compiled.txt'), encoding='utf-8')
             if l.startswith('0x') and image.section_at(lo)['va'] <= int(l.split()[0], 16) < lo]
if prev_rows:
    s = os.path.splitext(max(prev_rows, key=lambda q: int(q[0], 16))[1][len('build/'):])[0]
    for ext in ('.cpp', '.c'):
        if os.path.exists(os.path.join(ROOT, s + ext)) and s + ext in place:
            owner = s + ext
seed = owner
a = lo - lo % 4 if lo % 4 else lo
REAL = set()
for l in open(os.path.join(ROOT, 'config', 'compiled.txt'), encoding='utf-8'):
    q = l.split()
    if len(q) >= 3 and q[0].startswith('0x') and 'build/src/xdk/standin' not in q[1]:
        REAL.add(int(q[0], 16))
while a < hi:
    if a in REAL:
        print('stop at 0x%X: already placed' % a)
        break
    rs = refs.get(a, [])
    if a % 4 and not rs:
        # after a byte global: zero bytes up to the next dword are padding, others a byte of their own
        if not any(image.read(a, 4 - a % 4)):
            a += 4 - a % 4
            continue
    elif a + 4 > hi:
        break
    bits = struct.unpack('<I', bytes(image.read(a, 4)))[0]
    if rs:
        names = {t for s, t in rs}
        if len(names) != 1:
            print('stop at 0x%X: several names %s' % (a, sorted(names)))
            break
        t = next(iter(names))
        mns = re.match(r'^\?(\w+)@(\w+)@@3(.*)$', t)
        if mns:
            # a namespace's global: parsed by its plain form, defined inside the namespace
            NS[a] = (mns.group(2), t)
            t = '?%s@@3%s' % (mns.group(1), mns.group(3).replace('@1@', '@@'))
        md = re.match(r'^\?(\w+)@@3PAY(\d)((?:\d|[A-P]+@)+)([MHIKDE])A$', t)
        if md:
            # a multi-dimensional array of scalars (PAY0<dims><type>): rows of its inner dimensions
            dims, rest = [], md.group(3)
            while rest:
                if rest[0].isdigit():
                    dims.append(int(rest[0]) + 1)
                    rest = rest[1:]
                else:
                    k = rest.index('@')
                    dims.append(int(''.join('%X' % (ord(c) - 65) for c in rest[:k]), 16))
                    rest = rest[k + 1:]
            name = md.group(1)
            fmt = {'M': 'f', 'H': 'i', 'I': 'u', 'K': 'u', 'D': 'b', 'E': 'B'}[md.group(4)]
            ctype = {'M': 'RwReal', 'H': 'RwInt32', 'I': 'RwUInt32', 'K': 'DWORD', 'D': 'RwChar', 'E': 'RwUInt8'}[md.group(4)]
            esz = 1 if fmt in 'bB' else 4
            inner = 1
            for d in dims:
                inner *= d
            rowsz = inner * esz
            count = 0
            for h in HEADERS:
                d = re.search(BS + 'b%s' % name + BS + '[(' + BS + 'w+)' + BS + ']', HEADERS[h])
                if d and d.group(1).isdigit():
                    count = int(d.group(1), 0)
                    break
            if not count:
                count = (min([r for r in refs if r > a
                              and any(nm != t and nm != NS.get(a, (0, t))[1] for _, nm in refs[r])] + [hi]) - a) // rowsz
            width = rowsz * count
            if width >= 64 and a % 8:
                print('stop at 0x%X: %d bytes off an 8-byte boundary' % (a, width))
                break
            raw = bytes(image.read(a, width))

            def val(k):
                if esz == 1:
                    return '%d' % (raw[k] if fmt == 'B' else struct.unpack_from('<b', raw, k)[0])
                v = struct.unpack_from('<I', raw, k)[0]
                return float_lit(v) if fmt == 'f' else ('0x%X' % v) if fmt == 'u' else \
                    '%d' % struct.unpack('<i', struct.pack('<I', v))[0]

            def nest(off, ds):
                if not ds:
                    return val(off)
                step = esz
                for d in ds[1:]:
                    step *= d
                return '{ ' + ', '.join(nest(off + k * step, ds[1:]) for k in range(ds[0])) + ' }'
            body = '{' + chr(10) + ''.join('    %s,' % nest(r * rowsz, dims) + chr(10) for r in range(count)) + '}'
            decl = '%s %s[%d]%s = %s;' % (ctype, name, count, ''.join('[%d]' % d for d in dims), body)
            units = sorted({s for s, _ in rs}, key=lambda u: place.get(u, 1 << 32))
            later = [u for u in units if owner is None or place.get(u, 1 << 32) >= place.get(owner, 0)]
            owner = later[0] if later else FALLBACK + (owner or units[0])
            slots.append((a, owner, name, t, decl, width, True))
            a += width
            continue
        ms = re.match(r'^\?(\w+)@@3(PA)?U(\w+)@@([AB])$', t)
        if ms and ms.group(3) not in STRUCTS:
            layout = parse_struct(ms.group(3))
            if layout:
                STRUCTS[ms.group(3)] = layout
        if ms and ms.group(3) in STRUCTS:
            # a struct (or an array of them): its fields brace-initialized
            name, fields, ctype = ms.group(1), STRUCTS[ms.group(3)], ms.group(3)
            if ms.group(4) == 'B':
                ctype = 'const ' + ctype
            if isinstance(fields, str):
                fields = [(f, 1 if f == 'B' else 4, k) for k, f in
                          zip(range(0, 64, 4) if 'B' not in fields else range(0, 64), fields)]
                fields = (fields, fields[-1][2] + fields[-1][1])
            fields, size = fields
            count = 0
            if ms.group(2):
                for h in HEADERS:
                    d = re.search(BS + 'b%s' % name + BS + '[(' + BS + 'w+)' + BS + ']', HEADERS[h])
                    if d:
                        count = int(d.group(1), 0)
                        break
                if not count:
                    # up to the next object referenced by another name (refs into this one bear its)
                    # (a reference off an element boundary is into an element: the type's tail)
                    count = (min([r for r in refs if r > a and (r - a) % size == 0
                                  and any(nm != t for _, nm in refs[r])] + [hi]) - a) // size
            width = size * max(count, 1)
            if width >= 64 and a % 8:
                print('stop at 0x%X: %d bytes off an 8-byte boundary' % (a, width))
                break
            elems = []
            stop = False
            for e in range(max(count, 1)):
                raw = bytes(image.read(a + e * size, size))
                vals = []
                for f, fsize, k in fields:
                    if f == 'c':
                        txt = raw[k:k + fsize].split(bytes(1))[0]
                        if any(raw[k + len(txt):k + fsize]):
                            print('stop at 0x%X: a character array with bytes after its string' % a)
                            stop = True
                        vals.append(cstr_bytes(txt))
                    elif f in 'Bb':
                        vals.append('%d' % (raw[k] if f == 'B' else struct.unpack_from('<b', raw, k)[0]))
                    elif f in 'hH':
                        vals.append('%d' % struct.unpack_from('<' + f, raw, k)[0])
                    elif f == 'F':
                        v = struct.unpack_from('<I', raw, k)[0]
                        nm = func_name(v)
                        if nm is None:
                            stop = True
                        vals.append(nm or '0')
                    elif f == 'p':
                        if raw[k:k + 4] != bytes(4):
                            stop = True
                        vals.append('0')
                    else:
                        v = struct.unpack_from('<I', raw, k)[0]
                        vals.append(float_lit(v) if f == 'f' else cstr(v) if f == 's' else
                                    ('0x%X' % v) if f == 'u' else '%d' % struct.unpack('<i', struct.pack('<I', v))[0])
                elems.append('{ %s }' % ', '.join(vals))
            if stop:
                print('stop at 0x%X: %s holds a pointer' % (a, t))
                break
            units = sorted({s for s, _ in rs}, key=lambda u: place.get(u, 1 << 32))
            later = [u for u in units if owner is None or place.get(u, 1 << 32) >= place.get(owner, 0)]
            owner = later[0] if later else FALLBACK + (owner or units[0])
            if count:
                body = '{' + chr(10) + ''.join('    %s,' % e + chr(10) for e in elems) + '}'
                decl = '%s %s[%d] = %s;' % (ctype, name, count, body)
            else:
                decl = '%s %s = %s;' % (ctype, name, elems[0])
            decl = ('extern ' if ctype.startswith('const') else '') + decl
            slots.append((a, owner, name, t, decl, width, True))
            a += width
            continue
        m = re.match(r'^\?(\w+)@@3(PA)?(PBD[AB]|_?[A-Z][AB])$', t)
        if not m or m.group(3) not in TYPES or (m.group(2) and m.group(3) not in ('MA', 'HA', 'KA', 'IA', 'PBDA', 'EA', 'DA', 'FA', 'GA')):
            # a lone pointer (function or data): its header's extern gives the declarator
            mp = re.match(r'^\?(\w+)@@3P', t)
            decl0 = None
            if mp:
                for h in HEADERS.values():
                    d = re.search(r'^extern ([^;\n]*\b%s\b[^;\n]*);' % mp.group(1), h, re.M)
                    if d and '[' not in d.group(1):
                        decl0 = d.group(1)
                        break
            v = struct.unpack('<I', bytes(image.read(a, 4)))[0]
            val0 = None
            if decl0:
                if v == 0:
                    val0 = '0'
                elif '(' in decl0:
                    val0 = func_name(v)
                elif 'RwChar' in decl0 and is_string(v):
                    val0 = cstr(v)
            if val0 is None:
                print('stop at 0x%X: %s' % (a, t))
                break
            name = mp.group(1)
            units = sorted({s for s, _ in rs}, key=lambda u: place.get(u, 1 << 32))
            later = [u for u in units if owner is None or place.get(u, 1 << 32) >= place.get(owner, 0)]
            owner = later[0] if later else FALLBACK + (owner or units[0])
            slots.append((a, owner, name, t, '%s = %s;' % (decl0, val0), 4, True))
            a += 4
            continue
        name, ctype = m.group(1), TYPES[m.group(3)]
        esz = {'EA': 1, 'DA': 1, 'FA': 2, 'GA': 2}.get(m.group(3), 4)
        width = 1 if ctype.split()[-1] in ('bool', 'RwUInt8', 'RwChar') else             2 if ctype.split()[-1] in ('RwInt16', 'RwUInt16') else 4
        count = 0
        if m.group(2):
            # an array: its size from a header's declaration, else up to the next referenced slot
            for h in HEADERS:
                d = re.search(r'\b%s\[(\w+)\]' % name, HEADERS[h])
                if d:
                    count = int(d.group(1), 0)
                    break
            if not count:
                count = (min([r for r in refs if r > a and any(nm != t for _, nm in refs[r])] + [hi]) - a) // esz
            width = esz * count
            if width >= 64 and a % 8:
                print('stop at 0x%X: an array of %d bytes off an 8-byte boundary' % (a, width))
                break
        units = sorted({s for s, t in rs})
        # units link in address order and each one's data is contiguous: the owner comes no
        # earlier than the slot before's
        units = sorted(units, key=lambda u: place.get(u, 1 << 32))
        later = [u for u in units if owner is None or place.get(u, 1 << 32) >= place.get(owner, 0)]
        mine = [u for u in later if re.search(r'\b%s\b' % name, open(os.path.join(ROOT, u), encoding='utf-8',
                                                                    errors='replace').read())]
        owner = ((mine or later)[0] if len(later) != 1 else later[0]) if later else FALLBACK + (owner or units[0])
        mangled = t
    else:
        if owner is None:
            print('stop at 0x%X: no owner yet' % a)
            break
        v = struct.unpack('<f', struct.pack('<I', bits))[0]
        isf = bits != 0 and 1e-6 < abs(v) < 1e7
        width = 4 if a % 4 == 0 else 1
        count = 0
        if width == 1:
            name, ctype = 'byte_%06X' % a, ('const ' if const else '') + 'RwUInt8'
            mangled = '?%s@@3E%s' % (name, 'B' if const else 'A')
        elif is_string(bits):
            name, ctype = 'off_%06X' % a, 'const RwChar *'
            mangled = '?%s@@3PBDB' % name   # MSVC: a pointer variable's letter is its pointee's cv
        else:
            name = ('flt_%06X' if isf else 'dword_%06X') % a
            ctype = ('const ' if const else '') + ('RwReal' if isf else 'RwInt32')
            mangled = '?%s@@3%s%s' % (name, 'M' if isf else 'H', 'B' if const else 'A')
    if width == 1:
        bits &= 0xFF
    elif width == 2:
        bits &= 0xFFFF
    if count:
        vals = struct.unpack('<%d%s' % (count, {1: 'B', 2: 'H', 4: 'I'}[esz]), bytes(image.read(a, esz * count)))
        if esz < 4 and 'RwChar' not in ctype:
            vals = [v if 'U' in ctype else (v - (1 << (8 * esz)) if v >> (8 * esz - 1) else v) for v in vals]
        value = '{ %s }' % ', '.join(cstr(v) if 'RwChar *' in ctype else float_lit(v) if 'RwReal' in ctype else ('0x%X' % v) if 'U' in ctype or 'DWORD' in ctype
                                     else ('%d' % struct.unpack('<i', struct.pack('<I', v))[0]) for v in vals)
        name_decl = '%s[%d]' % (name, count)
        raw_c = bytes(image.read(a, esz * count))
        if ctype.endswith('RwChar') and esz == 1 and b'\0' in raw_c and not any(raw_c[raw_c.index(b'\0'):]):
            value = cstr_bytes(raw_c[:raw_c.index(b'\0')])
    elif 'RwChar *' in ctype:
        value = cstr(bits)
    elif 'RwReal' in ctype:
        value = float_lit(bits)
    elif 'bool' in ctype:
        value = 'true' if bits else 'false'
    elif width == 1:
        value = '%d' % (bits if 'RwUInt8' in ctype else struct.unpack('<b', bytes([bits]))[0])
    elif width == 2:
        value = '%d' % (bits if 'RwUInt16' in ctype else struct.unpack('<h', struct.pack('<H', bits))[0])
    else:
        value = '%d' % struct.unpack('<i', struct.pack('<I', bits))[0]
    decl = ('extern ' if ctype.startswith('const') and not ctype.endswith('*') else '') + ('%s %s = %s;' % (
        ctype, name_decl if count else name, value)).replace('* ', '*')
    slots.append((a, owner, name, mangled, decl, width, bool(rs)))
    a += width
# A standalone zero global compiles into .bss: an unreferenced run of dwords holding a zero is one
# object of its unit (written as a dword array, floats noted), not separate globals.
merged = []
i = 0
while i < len(slots):
    j = i
    while j < len(slots) and not slots[j][6] and slots[j][5] == 4 and slots[j][1] == slots[i][1]:
        j += 1
    run = slots[i:j]
    strs = [s for s in run if s[2].startswith('off_')]
    if len(run) > 1 and len(strs) == len(run):
        # a run of unreferenced string pointers: one table
        a0, n = run[0][0], len(run)
        vals = struct.unpack('<%dI' % n, bytes(image.read(a0, 4 * n)))
        name = 'off_%06X' % a0
        decl = 'const RwChar *%s[%d] = {\n%s\n};' % (name, n, '\n'.join('    %s,' % cstr(v) for v in vals))
        merged.append((a0, run[0][1], name, '?%s@@3PAPBDA' % name, decl, 4 * n, False))
        i = j
        continue
    if run and all(re.search(r'= (0|false);$', s[4]) for s in run):
        # all zeros: the next unit's alignment padding (unpad.py) or the tail of the global
        # before it (aggregate.py); left binary for that decision
        print('zero run 0x%X-0x%X left out: padding or the tail of the global before it'
              % (run[0][0], run[-1][0] + 4))
        i = j
        continue
    if run and any(re.search(r'= (0|false);$', s[4]) for s in run) and any(
            0x10000 <= v and image.section_at(v) for v in struct.unpack('<%dI' % len(run), bytes(image.read(run[0][0], 4 * len(run))))):
        # pointers among them: their relocations need a typed table (hand work)
        print('run 0x%X-0x%X left out: it holds pointers' % (run[0][0], run[-1][0] + 4))
        i = j
        continue
    if run and any(re.search(r'= (0|false);$', s[4]) for s in run):
        a0, n = run[0][0], len(run)
        vals = struct.unpack('<%dI' % n, bytes(image.read(a0, 4 * n)))
        body = ', '.join('0x%X' % v + ('' if not v or 'RwReal' not in s[4] else ' /* %s */' % float_lit(v))
                         for v, s in zip(vals, run))
        name = 'unk_%06X' % a0
        decl = '%sRwUInt32 %s[%d] = { %s };' % ('extern const ' if const else '', name, n, body)
        merged.append((a0, run[0][1], name, ('?%s@@3QBIB' if const else '?%s@@3PAIA') % name, decl, 4 * n, False))
        i = j
        continue
    merged.append(slots[i] if not run else run[0])
    i = i + 1
slots = merged
# namespace globals keep their decorated names and are defined in their namespace
for i, s in enumerate(slots):
    if s[0] in NS:
        ns, orig = NS[s[0]]
        slots[i] = (s[0], s[1], s[2], orig, 'namespace %s\n{\n%s\n}' % (ns, s[4])) + s[5:]
# A slot only earlier units reference (as externs) is the next referenced slot's unit when that
# comes no earlier than the one before, else the one before's.
for i, s in enumerate(slots):
    if s[1].startswith(FALLBACK):
        prev = next((x[1] for x in reversed(slots[:i]) if not x[1].startswith(FALLBACK)), s[1][len(FALLBACK):])
        nxt = next((x[1] for x in slots[i + 1:] if not x[1].startswith(FALLBACK)), None)
        own = nxt if nxt and place.get(nxt, 0) >= place.get(prev, 0) else prev
        slots[i] = (s[0], own) + s[2:]
for i in range(len(slots) - 2, -1, -1):
    # nor later than the slot after's
    if place.get(slots[i][1], 0) > place.get(slots[i + 1][1], 1 << 32):
        slots[i] = (slots[i][0], slots[i + 1][1]) + slots[i][2:]
for s in slots:
    print('0x%06X %-40s %s' % (s[0], s[1], s[4]))

if apply and slots:
    by = collections.defaultdict(list)
    for s in slots:
        by[s[1]].append(s)
    for unit, items in by.items():
        full = os.path.join(ROOT, unit)
        for s in items:
            # an existing definition elsewhere in the unit moves into the block (its comment kept)
            prev = m5defs.take_existing(full, s[2])
            note = ''.join(l + '\n' for l in (prev or '').split('\n') if l.startswith('//'))
            if prev:
                print('moved the existing definition of %s' % s[2])
            m5defs.insert(full, s[0], note + s[4])
        text = open(full, encoding='utf-8').read()
        hdr = "// Its data (PLAN M5): literals, constants and tables where the image has them.\n"
        ml = ''.join('// match: %s @ 0x%08X\n' % (s[3], s[0]) for s in items)
        if hdr in text:
            text = text.replace(hdr, hdr + ml, 1)
        else:
            m = re.search(r'^// match: ', text, re.M)
            text = text[:m.start()] + hdr + ml + '\n' + text[m.start():]
        open(full, 'w', encoding='utf-8', newline='\n').write(text)
    cut = {s[0]: s[3] for s in slots}
    widths = {s[0]: s[5] for s in slots}
    res = []
    for l in open(os.path.join(ROOT, 'config', 'splits.txt'), encoding='utf-8').read().split('\n'):
        p = l.split()
        if len(p) >= 4 and p[0].startswith('0x') and p[3] == '-' and int(p[0], 16) <= min(cut) < int(p[1], 16):
            s0, e0, sec = int(p[0], 16), int(p[1], 16), p[2]
            cur = s0
            order = sorted(cut)
            for k, a in enumerate(order):
                if a > cur:
                    res.append('0x%08X 0x%08X %-10s -' % (cur, a, sec))
                # a piece runs to the next one (a byte global's padding with it), the last to a dword
                w = widths[a]
                end = order[k + 1] if k + 1 < len(order) and order[k + 1] - a < max(w, 4) else (a + w + 3) & ~3
                res.append('0x%08X 0x%08X %-10s %s' % (a, end, sec, cut[a]))
                cur = end
            if cur < e0:
                res.append('0x%08X 0x%08X %-10s -' % (cur, e0, sec))
        else:
            res.append(l)
    open(os.path.join(ROOT, 'config', 'splits.txt'), 'w', encoding='utf-8', newline='\n').write('\n'.join(res))
    subprocess.run([sys.executable, os.path.join(ROOT, 'tools', 'session', 'datablocks.py')], cwd=ROOT)
    # one batch for tools/cmfm.py
    print('CMFM ' + ' '.join('%s:%s' % (os.path.splitext(unit[len('src/'):])[0].replace('recovered/', ''),
                                         ','.join('0x%X' % s[0] for s in items)) for unit, items in by.items()))
