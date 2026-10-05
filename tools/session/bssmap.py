"""bssmap.py: the image address of every .bss variable (and COMMON symbol) the M7 link takes
(PLAN M7), written to build/m7/bssmap.txt as `ADDR OBJECT NAME` lines, and a coverage summary.

VC7.1 lays out an object's .bss in its symbol hash's order, which recovered names cannot
reproduce, so the M7 probe places each variable by its image address (comdatize.bss_split).
The addresses come from (a) a name carrying one (dword_4B8640, _unk_516CC0) and (b) the placed
pieces' relocations: for every config/compiled.txt row's code or data whose relocation names a
.bss or COMMON symbol, the image's dword at that site (minus the addend; a REL32's target
computed) is the symbol's address."""
import collections
import os
import re
import struct
import sys

sys.path.insert(0, os.path.join(os.path.dirname(os.path.abspath(__file__)), '..'))
from coff import Coff  # noqa: E402
from xbe import Xbe  # noqa: E402
sys.path.insert(0, os.path.join(os.path.dirname(os.path.abspath(__file__)), '..'))
import anonfix  # noqa: E402  (anonymous-namespace hashes of other checkouts)

ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
img = Xbe(os.path.join(ROOT, 'orig', 'Game_XboxMultiplayer.xbe'))
data = [s for s in img.sections if s['name'] == '.data'][0]
BSS_LO, BSS_HI = data['va'] + data['rsize'], data['va'] + data['vsize']
# (every section's zero tail: the libraries' uninitialized sections, D3D_URW, lie in their
# merged sections' tails)
TAILS = [(s_['va'] + s_['rsize'], s_['va'] + s_['vsize']) for s_ in img.sections if s_['vsize'] > s_['rsize']]


def in_bss(a):
    return any(lo <= a < hi for lo, hi in TAILS)
NAMED = re.compile(r'(?:dword|unk|flt|byte|word|qword|off|stru|dbl|asc)_([0-9A-F]{6,8})\b')

rows = collections.defaultdict(list)
for l in anonfix.lines(os.path.join(ROOT, 'config', 'compiled.txt')):
    q = l.split()
    if len(q) >= 3 and q[0].startswith('0x'):
        rows[q[1]].append((int(q[0], 16), q[2]))

# (OBJECT or None for an external, NAME) -> {address: votes}
votes = collections.defaultdict(collections.Counter)
# every .bss / COMMON symbol the objects define
defined = {}
cache = {}


def coff(o):
    if o not in cache:
        try:
            cache[o] = Coff(os.path.join(ROOT, o))
        except Exception:
            cache[o] = None
    return cache[o]


def bss_symbol(c, si):
    """(key, is_common) when the symbol index SI of C is a .bss variable or a COMMON."""
    y = c.symbols.get(si)
    if y is None:
        return None
    if y['section'] > 0:
        s = c.sections[y['section'] - 1]
        if s['chars'] & 0x80 and y['name'] != s['name']:
            return (y['name'] if y['class'] == 2 else None, y['name'])
        return None
    if y['section'] == 0 and y['class'] == 2:
        return ('?', y['name'])     # (an external: resolved below if it is someone's .bss)
    return None


_taildata = set()
for o, rs in rows.items():
    c = coff(o)
    if c is None:
        continue
    by = {}
    for y in c.symbol_list:
        if y['section'] > 0:
            by.setdefault(y['name'], y)
        if y['section'] > 0 and c.sections[y['section'] - 1]['chars'] & 0x80 and \
                y['name'] != c.sections[y['section'] - 1]['name']:
            defined[(o, y['name'])] = y['class']
        if y['section'] == 0 and y['class'] == 2 and y['value'] > 0:
            defined[('<common>', y['name'])] = 2
    for a, n in rs:
        y = by.get(n) or by.get('_' + n)
        if y is None:
            continue
        s = c.sections[y['section'] - 1]
        # (named symbols only: a function's .bf/.lf/.ef debug records, class 101, are not its end)
        later = sorted(z['value'] for z in c.symbol_list if z['section'] == y['section'] and z['value'] > y['value']
                       and z['class'] in (2, 3, 6))
        end = later[0] if later else s['size']
        for va, si, t in s['relocs']:
            if not y['value'] <= va < end or t not in (6, 20):
                continue
            k = bss_symbol(c, si)
            addend = struct.unpack_from('<i', s['data'], va)[0] if s['data'] else 0
            sec_off = 0
            # (a datum of an initialized data section the image keeps in a section's zero tail,
            # a binarized member's variable, xgraphics' WaR_dependants: placed like .bss)
            z_ = c.symbols.get(si)
            if k is None and z_ is not None and z_['section'] > 0:
                zs_ = c.sections[z_['section'] - 1]
                if not zs_['chars'] & 0x20 and not zs_['chars'] & 0x80 and z_['name'] != zs_['name'] \
                        and z_['class'] in (2, 3) and not z_['name'].startswith(('??_C@', '__real@', '$')):
                    k = (z_['name'] if z_['class'] == 2 else None, z_['name'])
                    _taildata.add((o, z_['name']))
            if k is None:
                # (a function's static local, referred to through its .bss section's symbol plus
                # its offset: the static at that offset)
                z = c.symbols.get(si)
                if z is None or z['section'] <= 0:
                    continue
                zs = c.sections[z['section'] - 1]
                if not (zs['chars'] & 0x80) or z['name'] != zs['name']:
                    continue
                at_ = [w for w in c.symbol_list if w['section'] == z['section'] and w['name'] != zs['name']
                       and w['value'] == addend]
                if not at_:
                    continue
                k = (at_[0]['name'] if at_[0]['class'] == 2 else None, at_[0]['name'])
                sec_off = addend
            site = a + va - y['value']
            try:
                v = struct.unpack('<I', img.read(site, 4))[0]
            except ValueError:
                continue
            tgt = (site + 4 + v) & 0xFFFFFFFF if t == 20 else v
            tgt = (tgt - addend + sec_off) & 0xFFFFFFFF
            if in_bss(tgt):
                owner = o if k[0] is None else None
                votes[(owner, k[1])][tgt] += 1
                if (o, k[1]) in _taildata:
                    defined.setdefault((o, k[1]), 2 if k[0] is not None else 3)
# names carrying an address
for (o, n) in list(defined):
    m = NAMED.search(n)
    if m and in_bss(int(m.group(1), 16)):
        votes[(o if defined[(o, n)] != 2 else None, n)][int(m.group(1), 16)] += 100
# (c) the database's names (config/symbols.txt): an inline function's local static, a library's
# global
_defnames = set(n for o, n in defined)
for l in anonfix.lines(os.path.join(ROOT, 'config', 'symbols.txt')):
    q = l.split()
    if len(q) >= 5 and q[0].startswith('0x') and q[0] != '0xADDRESS':
        a = int(q[0], 16)
        for nm in (q[4], '_' + q[4]):
            if in_bss(a) and nm in _defnames:
                votes[(None, nm)][a] += 50
# (d) config/aliases.txt: a library variable's address (___piob, from libcmt's references)
for l in anonfix.lines(os.path.join(ROOT, 'config', 'aliases.txt')):
    q = l.split()
    if len(q) >= 2 and q[1].startswith('0x'):
        try:
            a = int(q[1], 16)
        except ValueError:
            continue
        for nm in (q[0], '_' + q[0]):
            if in_bss(a) and nm in _defnames:
                votes[(None, nm)][a] += 50
# (the names an extracted library object defines in an uninitialized section, linked or not)
# (every member of the libraries the M7 link searches, extracted or not: d3d8's globals)
from lib import Library  # noqa: E402
_libdefs = set()
_xdk = os.environ.get('XDK', r'C:\XDK')
for _lp in [os.path.join(ROOT, 'xdklib', 'd3d8.lib'), os.path.join(ROOT, 'xdklib', 'dsound.lib')] + [
        os.path.join(_xdk, 'xbox', 'lib', _n) for _n in ('xapilib.lib', 'd3dx8.lib', 'xonlines.lib', 'uix.lib',
                                                       'xvoice.lib', 'libcmt.lib', 'libcpmt.lib', 'xgraphics.lib',
                                                       'xnets.lib')]:
    if not os.path.exists(_lp):
        continue
    for _mn, _body in Library(_lp).members:
        try:
            _c = Coff(_lp + ':' + _mn, _body)
        except Exception:
            continue
        for _y in _c.symbol_list:
            if _y['section'] > 0 and _y['class'] == 2 and _c.sections[_y['section'] - 1]['chars'] & 0x80:
                _libdefs.add(_y['name'])
out = []
conflicts = 0
for (o, n), cnt in votes.items():
    # (only what an object defines: a name only referenced, an address inside another variable
    # the stand-ins name apart, would take that variable's room)
    # (an external no rowed object defines, a library member without rows, D3D's globals:
    # referenced by rowed code, it is placed wherever it comes from)
    if n not in _defnames and (o is not None or n not in _libdefs):
        continue
    (addr, k), = cnt.most_common(1)
    if len(cnt) > 1:
        conflicts += 1
    out.append((addr, o or '-', n))
out.sort()


# (a variable no code the image holds refers to, its functions dropped by /OPT:REF, d3dbase's
# g_OverscanColor: its bytes are zeros wherever it lies, so it goes into a gap the placed
# variables leave in its section's tail, a placed one's room past its own size; first fit)
def _size_of(o, n):
    c = coff(o)
    if c is None:
        return None
    y = next((y for y in c.symbol_list if y['name'] == n and y['section'] > 0), None)
    if y is None:
        return None
    sec = c.sections[y['section'] - 1]
    later = sorted(z['value'] for z in c.symbol_list if z['section'] == y['section'] and z['value'] > y['value']
                   and z['class'] in (2, 3))
    return (later[0] if later else sec['size']) - y['value'], sec['name'].split('$')[0]


_owner = {}
for (o_, n_), cls_ in defined.items():
    if o_ != '<common>':
        _owner.setdefault(n_, o_)
_tail_of = lambda a: next(((lo, hi) for lo, hi in TAILS if lo <= a < hi), None)  # noqa: E731
_sec_of = lambda a: next((s_['name'] for s_ in img.sections if s_['va'] <= a < s_['va'] + s_['vsize']), None)  # noqa: E731
_addrs = [a for a, o, n in out]
gaps = []
for i_, (a, o, n) in enumerate(out):
    t_ = _tail_of(a)
    if t_ is None:
        continue
    nxt_ = _addrs[i_ + 1] if i_ + 1 < len(_addrs) and _addrs[i_ + 1] < t_[1] else t_[1]
    so_ = _size_of(o if o != '-' else _owner.get(n, ''), n)
    if so_ is None:
        continue
    end_ = a + ((so_[0] + 3) & ~3)
    if nxt_ - end_ >= 4:
        gaps.append([end_, nxt_, _sec_of(a), o if o != '-' else _owner.get(n, '')])
placed_ = set((o, n) for a, o, n in out)
placed_names = set(n for a, o, n in out)
fill = []
cands = []
for (o_, n_), cls_ in sorted(defined.items()):
    if o_ == '<common>' or n_ in placed_names or (o_, n_) in placed_:
        continue
    so_ = _size_of(o_, n_)
    if so_ is None or so_[0] <= 0:
        continue
    c_ = coff(o_)
    v_ = next((y['value'] for y in c_.symbol_list if y['name'] == n_ and y['section'] > 0), 0)
    cands.append((o_, v_, n_, cls_, so_))
cands.sort()


def _fit(g, same):
    for c in list(cands):
        o_, v_, n_, cls_, (size_, secn_) = c
        if n_ in placed_names or (same and o_ != g[3]) or (not same and o_ == g[3]):
            continue
        want_ = '.data' if secn_.startswith('.bss') else secn_[:-4] if secn_.endswith('_URW') else None
        al_ = 8 if size_ >= 8 else 4
        start_ = (g[0] + al_ - 1) // al_ * al_
        if g[2] == want_ and start_ + size_ <= g[1]:
            fill.append((start_, o_ if cls_ != 2 else '-', n_))
            g[0] = start_ + ((size_ + 3) & ~3)
            placed_names.add(n_)


# (the gap's own object's variables first: a section's unreferenced statics after its placed
# ones, shadersnapshot's g_lastOpcode; then any)
for g in gaps:
    _fit(g, True)
for g in gaps:
    _fit(g, False)
out = sorted(out + fill)
print('%d unplaced variables fitted into gaps' % len(fill))
# (the filled externals, for the probe to /INCLUDE: an unreferenced COMDAT variable, d3dbase's
# g_Channel, is dropped by /OPT:REF and its room with it)
with open(os.path.join(ROOT, 'build', 'm7', 'bssfill.txt'), 'w') as f:
    for a, o, n in sorted(fill):
        if o == '-':
            f.write(n + '\n')
with open(os.path.join(ROOT, 'build', 'm7', 'bssmap.txt'), 'w') as f:
    for a, o, n in out:
        f.write('0x%08X %s %s\n' % (a, o, n))
known = set((o if o != '-' else None, n) for a, o, n in out)
ext_known = set(n for o, n in known if o is None)
unknown = [k for k in defined if (k[0] if defined[k] != 2 else None, k[1]) not in known and k[1] not in ext_known]
print('%d .bss symbols placed (%d with conflicting votes), %d defined without an address' % (len(out), conflicts, len(unknown)))
print('image .bss 0x%X-0x%X' % (BSS_LO, BSS_HI))
