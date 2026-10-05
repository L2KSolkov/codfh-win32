"""bssdefs.py [--apply]: define the uninitialized globals placed code reads but no source defines (PLAN M5/M7).

The image's .bss (past .data's raw bytes) has no bytes to place, so only the real link (M7)
checks it; until then its globals are extern declarations resolved by address. For every .bss
address placed code reads: its readers (objects) and the names they use. Owners follow link
order: an object's .bss is one contiguous block in definition order, so walking the addresses
upward each takes the first reader not earlier in link order than the previous owner (else the
previous owner). The definition reuses the sources' own declaration of the name (an
`extern T name...;` line, without `extern`) when there is exactly one form, else
`RwUInt8 name[size]` up to the next known address. With --apply each goes into its owner's
sorted data block. Prints the plan and the names it could not define."""
import bisect
import os
import re
import struct
import sys

sys.path.insert(0, os.path.join(os.path.dirname(os.path.abspath(__file__)), '..'))
sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import m5defs  # noqa: E402
from coff import Coff  # noqa: E402
from xbe import Xbe  # noqa: E402

ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
apply = '--apply' in sys.argv
image = Xbe(os.path.join(ROOT, 'orig', 'Game_XboxMultiplayer.xbe'))
data = next(s for s in image.sections if s['name'] == '.data')
BSS_LO, BSS_HI = data['va'] + data['rsize'], data['va'] + data['vsize']
OURGLOBALS = 0x5200E0              # RenderWare's ourGlobals[RWGLOBALSIZE / 4] (badevice.c)
code_rows, first = {}, {}
for l in open(os.path.join(ROOT, 'config', 'compiled.txt'), encoding='utf-8'):
    q = l.split()
    if len(q) >= 3 and q[0].startswith('0x') and int(q[0], 16) < 0x3C0000:
        code_rows.setdefault(q[1], []).append((int(q[0], 16), q[2]))
for o, p in code_rows.items():
    first[o] = min(a for a, n in p)
readers, names = {}, {}
for obj, pieces in code_rows.items():
    if not obj.startswith('build/src/') or not os.path.exists(os.path.join(ROOT, obj)):
        continue
    c = Coff(os.path.join(ROOT, obj))
    defined = set(s['name'] for s in c.symbol_list if s.get('section', 0) > 0)
    for addr, name in pieces:
        s = c.find_function(name)
        if s is None:
            continue
        _code, rel = c.function_bytes(s)
        for off, tgt, _r in rel:
            v = struct.unpack('<I', bytes(image.read(addr + off, 4)))[0]
            if BSS_LO <= v < BSS_HI:
                readers.setdefault(v, set()).add(obj)
                if tgt not in defined:
                    names.setdefault(v, set()).add(tgt)
unres = set(l.strip() for l in open(os.path.join(ROOT, 'build', 'm7', 'unresolved.txt')) if l.strip())
# one definition per name: at the address its name carries (else its lowest reference)
bydec = {}
for v, ns in names.items():
    for n in ns:
        if n not in unres:
            continue
        m = re.search(r'_([0-9A-F]{6})(?:@|$)', n)
        a = int(m.group(1), 16) if m and BSS_LO <= int(m.group(1), 16) < BSS_HI else None
        d = bydec.setdefault(n, {'addr': a, 'refs': set(), 'readers': set()})
        d['refs'].add(v)
        d['readers'] |= readers[v]
for n, d in bydec.items():
    if d['addr'] is None:
        d['addr'] = min(d['refs'])
# names placed code does not read directly (data tables' pointers, parked code): their address
# from the name, their readers from the probe's link log
log_readers = {}
by_base = {}
for o in code_rows:
    by_base.setdefault(os.path.basename(o), o)
for l in open(os.path.join(ROOT, 'build', 'm7', 'link.log'), errors='replace'):
    m = re.match(r'^(\S+\.obj) : error LNK20\d\d: unresolved external symbol (?:"[^"]*" \((\S+)\)|(\S+))', l)
    if m and m.group(1) in by_base:
        log_readers.setdefault(m.group(2) or m.group(3), set()).add(by_base[m.group(1)])
for n in unres:
    m = re.search(r'_([0-9A-F]{6})(?:@|$)', n)
    if n in bydec or not m or not (BSS_LO <= int(m.group(1), 16) < BSS_HI) or n not in log_readers:
        continue
    bydec[n] = {'addr': int(m.group(1), 16), 'refs': {int(m.group(1), 16)}, 'readers': log_readers[n]}
addrs = sorted(set(d['addr'] for d in bydec.values()) | set(readers))
# anchors: addresses only one unit reads (that unit defines them); a unit's .bss is one block,
# so an address between two anchors of one unit (which reads it) is that unit's
texts = {}
for top in ('src', 'include'):
    for dp, _dn, fs in os.walk(os.path.join(ROOT, top)):
        for f in fs:
            if f.endswith(('.c', '.cpp', '.h')):
                texts[os.path.normpath(os.path.join(dp, f))] = open(os.path.join(dp, f), encoding='utf-8', errors='replace').read()
# .bss addresses a unit's data block already defines (a `// 0xADDR` line before a definition)
defined_at = set()
for p, t in texts.items():
    if not p.endswith(('.c', '.cpp')):
        continue
    rel = os.path.relpath(p, ROOT).replace(os.sep, '/')
    obj = 'build/' + os.path.splitext(rel)[0] + '.obj'
    for m in re.finditer(r'^// 0x([0-9A-F]{8})\n(?!extern)[A-Za-z_]', t, re.M):
        v = int(m.group(1), 16)
        if BSS_LO <= v < BSS_HI:
            defined_at.add((v, obj))
anchors = sorted(set((v, next(iter(rs))) for v, rs in readers.items() if len(rs) == 1) | defined_at)
akeys = [v for v, o in anchors]
# the longest chain of anchors whose objects' first code addresses do not decrease
fa = [first.get(o, -1) for v, o in anchors]
best, back = [1] * len(fa), [-1] * len(fa)
tails, tail_idx = [], []
for i, f in enumerate(fa):
    k = bisect.bisect_right(tails, f)
    back[i] = tail_idx[k - 1] if k > 0 else -1
    if k == len(tails):
        tails.append(f)
        tail_idx.append(i)
    else:
        tails[k] = f
        tail_idx[k] = i
chain, i = [], tail_idx[-1] if tail_idx else -1
while i >= 0:
    chain.append(anchors[i])
    i = back[i]
mono = sorted(chain)
mkeys = [v for v, o in mono]
plan, prev = [], None
OWNERS = {}
if '--owners' in sys.argv:
    _bybase = dict((os.path.basename(o)[:-4], o) for o in code_rows)
    for l in open(sys.argv[sys.argv.index('--owners') + 1]):
        q = l.split()
        if len(q) >= 2 and q[0].startswith('0x'):
            OWNERS[int(q[0], 16)] = _bybase[q[1]]
for n, d in sorted(bydec.items(), key=lambda x: x[1]['addr']):
    if OURGLOBALS <= d['addr'] < OURGLOBALS + 0x4000:
        continue                    # RenderWare's globals: fields of ourGlobals, not variables
    rs = sorted(d['readers'], key=lambda o: first.get(o, 1 << 32))
    if d['addr'] in OWNERS:         # --owners FILE: owners decided by hand (ADDR UNIT per line)
        plan.append((d['addr'], OWNERS[d['addr']], [n]))
        continue
    if len(rs) == 1:
        plan.append((d['addr'], rs[0], [n]))
        continue
    j = bisect.bisect_left(akeys, d['addr'])
    below = anchors[j - 1][1] if j > 0 else None
    above = next((o for v, o in anchors[j:] if v != d['addr']), None)
    if below and below == above and below in rs:
        plan.append((d['addr'], below, [n]))
        continue
    # --mono: objects' .bss blocks follow link (first code address) order; the anchors that
    # keep that order (the longest monotone chain) bound the owner: the one reader whose first
    # address lies between theirs
    if '--mono' in sys.argv:
        k = bisect.bisect_left(mkeys, d['addr'])
        lo_f = first.get(mono[k - 1][1], 0) if k > 0 else 0
        hi_f = first.get(mono[k][1], 1 << 32) if k < len(mono) else 1 << 32
        cand = [o for o in rs if lo_f <= first.get(o, -1) <= hi_f]
        if len(cand) == 1:
            plan.append((d['addr'], cand[0], [n]))
            continue
        # --near: of several, the reader the trusted neighbour below (else above) is, else the
        # first candidate in link order (a guess: layout identity checks it)
        if '--near' in sys.argv:
            nb = [mono[k - 1][1] if k > 0 else None, mono[k][1] if k < len(mono) else None]
            pick = next((o for o in nb if o in rs), None) or (cand[0] if cand else None)
            if pick:
                plan.append((d['addr'], pick, [n]))
                continue
    if os.environ.get('BSSDEBUG'):
        sh = lambda o: o and os.path.basename(o)[:-4]
        print('unowned 0x%06X %-30s below %s above %s readers %s' % (d['addr'], n[:30], sh(below), sh(above),
                                                                    ','.join(sh(o) for o in rs[:5])))


def plain_name(dec):
    m = re.match(r'^\?(\w+)@', dec)
    if m:
        return m.group(1)
    return dec[1:] if dec.startswith('_') else dec


def owner_src(o):
    base = os.path.join(ROOT, o[len('build/'):-len('.obj')])
    return next((os.path.normpath(base + x) for x in ('.cpp', '.c') if os.path.exists(base + x)), None)


def has_ctor(decl, nm):
    """True when the declaration's class type (or a base) has a constructor, a virtual or a base:
    a global of it gets a dynamic initializer the image does not have."""
    m = re.match(r'^(?:const\s+)?(?:struct\s+|class\s+)?((?:\w+::)*\w+)\s+%s\b' % re.escape(nm), decl)
    if not m or '*' in decl:
        return False
    cls = m.group(1).split('::')[-1]
    if cls.startswith('D3DX'):
        return True                 # the XDK's C++ D3DX types have constructors
    for p, t in texts.items():
        if not p.endswith('.h'):
            continue
        cm = re.search(r'^\s*(?:struct|class)\s+%s\b([^;{]*)\{' % re.escape(cls), t, re.M)
        if not cm:
            continue
        if ':' in cm.group(1):
            return True
        depth, k = 0, cm.end() - 1
        while k < len(t):
            depth += {'{': 1, '}': -1}.get(t[k], 0)
            if depth == 0:
                break
            k += 1
        body = t[cm.end():k]
        return bool(re.search(r'\b%s\s*\(|\bvirtual\b' % re.escape(cls), body))
    return False


out, skipped = [], []
for k, (a, owner, todo) in enumerate(plan):
    nxt = addrs[addrs.index(a) + 1] if addrs.index(a) + 1 < len(addrs) else BSS_HI
    for dec in todo:
        nm = plain_name(dec)
        forms = set()
        for p, t in texts.items():
            for m in re.finditer(r'^\s*extern\s+(?!"C")([^;\n]*\b%s\b[^;\n]*);' % re.escape(nm), t, re.M):
                forms.add(' '.join(m.group(1).split()))
        # forms that differ only in an array's bound: the sized one
        if len(forms) > 1 and len(set(re.sub(r'\[\d*\]', '[]', f) for f in forms)) == 1:
            sized = [f for f in forms if re.search(r'\[\d+\]', f)]
            if len(set(sized)) == 1:
                forms = set(sized)
        pod = re.compile(r'^(const\s+)?(RwInt32|RwUInt32|RwInt16|RwUInt16|RwInt8|RwUInt8|RwChar|RwReal|RwBool|RwBool32|'
                         r'DWORD|BYTE|WORD|BOOL|int|unsigned\s+int|char|unsigned\s+char|short|float|U8|U16|U32|S8|S16|S32|F32)\s+'
                         r'%s(\s*\[[^\]]*\])*$|^[\w\s]+\*+\s*%s(\s*\[[^\]]*\])*$' % (re.escape(nm), re.escape(nm)))
        structs = re.compile(r'^(?:struct\s+)?(?:\w+::)*(?:type_\w+|Rw\w+|Rp\w+|Rt\w+)\s+%s(\s*\[[^\]]*\])*$' % re.escape(nm))
        if len(forms) == 1 and not pod.match(list(forms)[0]) and not ('--structs' in sys.argv and structs.match(list(forms)[0])) \
                and '--any' not in sys.argv:
            skipped.append((hex(a), dec, 'not plain data'))
            continue
        if len(forms) == 1 and re.match(r'^\?\w+@((?:\w+@)+)@[23]', dec) and '--scoped' not in sys.argv:
            skipped.append((hex(a), dec, 'scoped'))
            continue
        if len(forms) == 1 and has_ctor(list(forms)[0], nm):
            skipped.append((hex(a), dec, 'constructed type'))
            continue
        if len(forms) == 1 and re.search(r'^(?!extern)(?:static\s+|const\s+)*[A-Za-z_][\w:]*(?:\s*\*+\s*|\s+)%s\b\s*(\[[^\]]*\])*\s*(=[^;]*)?;' % re.escape(nm),
                                         texts.get(owner_src(owner), ''), re.M):
            skipped.append((hex(a), dec, 'defined'))
            continue
        if '// 0x%08X\n' % a in texts.get(owner_src(owner), '') or any(x[0] == a and x[1] == owner for x in out):
            skipped.append((hex(a), dec, 'address defined under another name'))
            continue
        if len(forms) == 1:
            d = list(forms)[0]
            # a namespace's or class's name: qualified (?name@kujuUI@@ -> kujuUI::name)
            sm = re.match(r'^\?\w+@((?:\w+@)+)@[23]', dec)
            if sm:
                # inside the namespace, where its own type names resolve unqualified
                scopes = list(reversed(sm.group(1).rstrip('@').split('@')))
                out.append((a, owner, dec, ''.join('namespace %s { ' % s for s in scopes) + d + '; ' + '} ' * len(scopes)))
                out[-1] = out[-1][:3] + (out[-1][3].rstrip(),)
                continue
            out.append((a, owner, dec, d + ';'))
        else:
            skipped.append((hex(a), dec, len(forms)))
for a, o, dec, d in out[:int(os.environ.get("NSHOW", "30"))]:
    print('0x%06X %-28s %s' % (a, os.path.basename(o), d))
print(len(out), 'definitions,', len(skipped), 'skipped (no single declaration form)')
for s in skipped[:int(os.environ.get("NSKIP", "20"))]:
    print('  skip', s)
if not apply:
    sys.exit(0)
for a, o, dec, d in out:
    base = os.path.join(ROOT, o[len('build/'):-len('.obj')])
    src = next((base + x for x in ('.cpp', '.c') if os.path.exists(base + x)), None)
    if src:
        m5defs.insert(src, a, d)
print('applied')
