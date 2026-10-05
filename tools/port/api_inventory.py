"""api_inventory.py: every external symbol the plain link's own objects (build/plain/link.rsp) take
from an Xbox SDK library, with the objects using it, into build/port/inv.json; then run
tools/port/api_inventory_md.py to write docs/WIN32_PORT_API.md. Run after tools/plainbuild.py
(without --define, so no research objects are linked)."""
import ctypes, json, os, re, struct, sys
from collections import defaultdict

ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
OUT = os.path.join(ROOT, 'build', 'port')
os.makedirs(OUT, exist_ok=True)
rsp = open(os.path.join(ROOT, 'build', 'plain', 'link.rsp')).read().split('\n')
objs = [l.strip('"') for l in rsp if l.endswith('.obj"')]
libs = [l for l in rsp if l and not l.endswith('.obj"')]


def coff_syms(path):
    d = open(path, 'rb').read()
    # anonymous / bigobj header?
    sig1, sig2 = struct.unpack_from('<HH', d, 0)
    if sig1 == 0 and sig2 == 0xFFFF:
        # import object or bigobj
        ver = struct.unpack_from('<H', d, 4)[0]
        if ver >= 2:  # bigobj
            nsec, ptr, nsym = struct.unpack_from('<III', d, 44)
            symsz = 20
            secfmt = '<i'
        else:
            return [], []
    else:
        nsec = sig2
        ptr, nsym = struct.unpack_from('<II', d, 8)
        symsz = 18
        secfmt = '<h'
    strtab = ptr + nsym * symsz
    undef, defined = [], []
    i = 0
    while i < nsym:
        o = ptr + i * symsz
        name = d[o:o + 8]
        if name[:4] == b'\0\0\0\0':
            off = struct.unpack_from('<I', name, 4)[0]
            e = d.index(b'\0', strtab + off)
            nm = d[strtab + off:e].decode('latin1')
        else:
            nm = name.rstrip(b'\0').decode('latin1')
        value = struct.unpack_from('<I', d, o + 8)[0]
        sec = struct.unpack_from(secfmt, d, o + 12)[0]
        typ, cls, naux = struct.unpack_from('<HBB', d, o + 12 + (4 if symsz == 20 else 2))
        if cls == 2:
            if sec == 0 and value == 0:
                undef.append(nm)
            elif sec != 0 or value:
                defined.append(nm)
        elif cls == 105:
            defined.append(nm)
        i += 1 + naux
    return undef, defined


def src_of(obj):
    rel = obj.replace('/', '\\')
    for pre in (ROOT + '\\build\\plain\\obj\\', ROOT + '\\build\\'):
        if rel.lower().startswith(pre.lower()):
            rel = rel[len(pre):]
            break
    base = rel[:-4]
    for e in ('.cpp', '.c', '.asm'):
        if os.path.exists(os.path.join(ROOT, base + e)):
            return (base + e).replace('\\', '/')
    return (base + '.?').replace('\\', '/')


# map: symbol -> (libobj, isfunc)
mapsym = {}
inpub = False
for line in open(os.path.join(ROOT, 'build', 'plain', 'game.map'), encoding='latin1'):
    if 'Publics by Value' in line:
        inpub = True
        continue
    if not inpub:
        continue
    if line.startswith(' entry point') or 'Static symbols' in line:
        break
    p = line.split()
    if len(p) < 4 or ':' not in p[0]:
        continue
    sym = p[1]
    isf = len(p) >= 5 and p[3] == 'f'
    lo = p[-1]
    mapsym.setdefault(sym, (lo, isf))

# library linker members, as fallback
def lib_index(path):
    d = open(path, 'rb').read()
    assert d[:8] == b'!<arch>\n'
    o = 8
    hdr = d[o:o + 60]
    size = int(hdr[48:58])
    body = d[o + 60:o + 60 + size]
    n = struct.unpack_from('>I', body, 0)[0]
    names = body[4 + 4 * n:].split(b'\0')[:n]
    return set(x.decode('latin1') for x in names)

LIBDIR = r'C:\XDK\xbox\lib'
libidx = []
for l in libs:
    p = l if os.path.isabs(l) else os.path.join(LIBDIR, l)
    try:
        libidx.append((os.path.basename(l)[:-4].lower(), lib_index(p)))
    except Exception as e:
        print('lib fail', l, e)

ours_defined = set()
uses = defaultdict(set)   # sym -> sources
for o in objs:
    u, dfn = coff_syms(o)
    ours_defined.update(dfn)
    s = src_of(o)
    for nm in u:
        uses[nm].add(s)

# undname
dbghelp = ctypes.WinDLL('dbghelp')
def undname(s):
    if s.startswith('?'):
        buf = ctypes.create_string_buffer(4096)
        n = dbghelp.UnDecorateSymbolName(s.encode('latin1'), buf, 4096, 0x0)
        if n:
            return buf.value.decode('latin1')
        return s
    t = s
    if t.startswith('__imp_'):
        t = t[6:]
    m = re.match(r'^[_@](.*?)(@\d+)?$', t)
    if m:
        return m.group(1)
    return t

result = []
unres = []
for sym, srcs in uses.items():
    if sym in ours_defined:
        continue
    lo, isf = mapsym.get(sym, (None, None))
    lib = None
    if lo and ':' in lo:
        lib = lo.split(':')[0].lower()
        member = lo.split(':', 1)[1]
    elif lo:
        lib = None  # ours / linker-generated
        member = lo
    if lib is None:
        for ln, idx in libidx:
            if sym in idx:
                lib, member = ln, '(not in map)'
                break
    if lib is None:
        unres.append((sym, lo, sorted(srcs)))
        continue
    result.append(dict(sym=sym, name=undname(sym), lib=lib, member=member, isfunc=isf,
                       users=sorted(srcs)))

json.dump(dict(result=result, unres=unres), open(os.path.join(OUT, 'inv.json'), 'w'), indent=1)
by = defaultdict(list)
for r in result:
    by[r['lib']].append(r)
for k, v in sorted(by.items()):
    us = set(u for r in v for u in r['users'])
    print(k, len(v), len(us))
print('unresolved', len(unres))
for x in unres[:40]:
    print(' ', x[0], x[1], x[2][:3])
