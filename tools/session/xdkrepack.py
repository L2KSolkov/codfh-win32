"""xdkrepack.py [LIB/MEMBER ...]: build stand-in library members for the XDK members the image
holds in another version than the installed or 5849 libraries (PLAN M3: "link from stand-in
libraries the repacker builds, preserving the original member granularity so the link pulls
them in the same order"; M7).

A member is mixed when its rows (config/compiled.txt, build/xdk/LIB/... or xdklib_LIB/...) come
from both library versions, or when stand-in pieces (build/src/xdk/standin_*.obj rows) lie
between its rows. Its stand-in is one COFF object merged from the objects that already hold its
pieces with exact relocations: every section holding a piece (in image order), the sections
those reference within the same source object (static data, string literals, vtables), and the
base member's .drectve (its default libraries). Writes build/m7/standin/LIB/MEMBER.obj and
build/m7/standin/members.txt (LIB, the member's archive name, the object).

With no arguments: every mixed member."""
import bisect
import re
import collections
import os
import struct
import sys

ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
sys.path.insert(0, os.path.join(ROOT, 'tools'))
from xbe import Xbe  # noqa: E402
sys.path.insert(0, os.path.join(os.path.dirname(os.path.abspath(__file__)), '..'))
import anonfix  # noqa: E402  (anonymous-namespace hashes of other checkouts)
image = Xbe(os.path.join(ROOT, 'orig', 'Game_XboxMultiplayer.xbe'))
OUT = os.path.join(ROOT, 'build', 'm7', 'standin')


class Obj(object):
    """The parts of a COFF object the merge needs."""

    def __init__(self, path):
        self.path = path
        d = open(path, 'rb').read()
        self.d = d
        _, nsec, _, symptr, nsyms, optsize, _ = struct.unpack_from('<HHIIIHH', d, 0)
        self.strtab = symptr + nsyms * 18
        self.secs = []
        for i in range(nsec):
            o = 20 + optsize + i * 40
            raw = d[o:o + 8]
            vsize, va, size, ptr, relptr, lnptr, nrel, nln, chars = struct.unpack_from('<IIIIIIHHI', d, o + 8)
            name = raw.rstrip(b'\0').decode('latin-1')
            if name.startswith('/'):
                k = int(name[1:])
                name = d[self.strtab + k:d.index(b'\0', self.strtab + k)].decode('latin-1')
            data = d[ptr:ptr + size] if ptr and not (chars & 0x80) else b''
            relocs = [struct.unpack_from('<IIH', d, relptr + 10 * r) for r in range(nrel)]
            self.secs.append({'name': name, 'size': size, 'chars': chars, 'data': data, 'relocs': relocs})
        self.syms = []      # (index, name, value, secno, type, cls, aux bytes)
        i = 0
        while i < nsyms:
            o = symptr + i * 18
            raw = d[o:o + 8]
            value, secno, typ, cls, naux = struct.unpack_from('<IhHBB', d, o + 8)
            if raw[:4] == b'\0\0\0\0':
                so = struct.unpack_from('<I', raw, 4)[0]
                name = d[self.strtab + so:d.index(b'\0', self.strtab + so)].decode('latin-1')
            else:
                name = raw.rstrip(b'\0').decode('latin-1')
            self.syms.append((i, name, value, secno, typ, cls, d[o + 18:o + 18 + 18 * naux]))
            i += 1 + naux
        self.by_index = {s[0]: s for s in self.syms}
        self.defined = {}
        for s in self.syms:
            if s[3] > 0 and s[5] in (2, 3, 6) and not s[1].startswith('.'):
                self.defined.setdefault(s[1], s)


cache = {}


def obj(path):
    if path not in cache:
        cache[path] = Obj(os.path.join(ROOT, path))
    return cache[path]


def _crt_piece(obj, name):
    """Whether the stand-in object's NAME lies in a .CRT$ section."""
    from coff import Coff
    try:
        c = Coff(os.path.join(ROOT, obj))
    except Exception:
        return False
    y = next((y for y in c.symbol_list if y['name'] == name and y['section'] > 0), None)
    return y is not None and c.sections[y['section'] - 1]['name'].startswith('.CRT$')


def rows():
    out = []
    for l in anonfix.lines(os.path.join(ROOT, 'config', 'compiled.txt')):
        q = l.split()
        if len(q) >= 3 and q[0].startswith('0x'):
            a = int(q[0], 16)
            # the CRT tables (.CRT$xxx, 0x426D40-0x427400): the libraries' members give their
            # entries in their own grouped sections; a stand-in piece there would be a copy
            # (unless the piece is itself in a .CRT$ section: entries no member gives, the four
            # null initializers at 0x4271C4)
            if q[1].startswith('build/src/xdk/standin_') and 0x426D40 <= a < 0x427400 \
                    and not _crt_piece(q[1], q[2]):
                continue
            out.append((a, q[1], q[2]))
    return sorted(out)


def members(all_rows):
    """{(lib, member file): [(addr, obj, name)]} of the XDK members, both versions."""
    out = collections.defaultdict(list)
    for a, o, n in all_rows:
        if o.startswith('build/xdk/'):
            out[keyof(o)].append((a, o, n))
    return out


def keyof(o):
    """The member key of an XDK member object (xonlines' copies of xnets' members are xnets')."""
    lib = o.split('/')[2].replace('xdklib_', '')
    if lib == 'xonlines' and os.path.exists(os.path.join(ROOT, 'build', 'xdk', 'xnets', os.path.basename(o))):
        lib = 'xnets'
    return (lib, os.path.basename(o))


ASSIGN = {}
# XDK_RETARGET=0: a picked section's references into its own data stay (see merge)
RETARGET = os.environ.get('XDK_RETARGET', '1') != '0'
obj_row = {}
REFERENCED = set()
# config/m7binarize.txt: `LIB MEMBER` lines, members the image holds in another version than any
# library we have (PLAN M7, the owner's call): their stand-in takes only the sections rows and
# pieces place (and those sections' EH associates), and every reference to a name no row has
# goes where the image's bytes point (the row there plus the offset), so the member's bytes are
# the image's and nothing of the library's version comes along
BINARIZE = set()
STATIC_TARGETS = set()     # (row object, static name) a binarized reference goes to
if os.path.exists(os.path.join(ROOT, 'config', 'm7binarize.txt')):
    for _l in open(os.path.join(ROOT, 'config', 'm7binarize.txt'), encoding='utf-8'):
        _q = _l.split()
        if len(_q) == 2 and not _l.startswith('#'):
            BINARIZE.add((_q[0], _q[1]))


def assign(all_rows):
    """Every stand-in row to the XDK member whose row precedes it with nothing but stand-in
    rows between (the member's pieces the libraries lack: newer code, EH funclets, chunks)."""
    last = None
    sec_of = None
    for r in all_rows:
        a, o, n = r
        # (a run never crosses an image section: the import table opening .rdata is not the
        # last code row's member's, xapilib mrb.obj)
        s_ = image.section_at(a)
        s_ = s_['name'] if s_ else None
        if s_ != sec_of:
            sec_of = s_
            last = None
        if o.startswith('build/xdk/'):
            last = keyof(o)
        elif o.startswith('build/src/xdk/'):
            if last is not None:
                ASSIGN[r] = last
        elif n.startswith('__real@') or n.startswith('??_C@') or n.startswith('__xmm@'):
            # (a shared literal another object's row names, a COMDAT any of them may give:
            # it does not end the member's run of pieces)
            continue
        else:
            last = None


def reassign_by_statics(all_rows, by_addr, static_owner):
    """A stand-in piece that calls or reads another member's static is that member's (only
    its own object can reach a static)."""
    for r in list(ASSIGN):
        a, o, n = r
        ob = obj(o)
        s = ob.defined.get(n)
        if s is None:
            continue
        for va, si, t in ob.secs[s[3] - 1]['relocs']:
            ts = ob.by_index.get(si)
            if ts is None:
                continue
            m = re.match(r'^_(sub|unk|loc)_([0-9A-F]{6,8})$', ts[1])
            nm = by_addr.get(int(m.group(2), 16)) if m else ts[1]
            if nm in static_owner and static_owner[nm] != ASSIGN[r]:
                ASSIGN[r] = static_owner[nm]
                break


def pieces_of(key, mrows, all_rows):
    """The member's rows and the stand-in rows assigned to it, in image order."""
    return sorted(set(mrows) | set(r for r, k in ASSIGN.items() if k == key))


def mixed(key, mrows, all_rows):
    versions = set(o.split('/')[2] for a, o, n in mrows)
    return len(versions) > 1 or len(pieces_of(key, mrows, all_rows)) > len(mrows)


_row_obj_at = {}


def _is_static_in(o, name):
    try:
        ob = obj(o)
    except Exception:
        return False
    d = [y for y in ob.syms if y[1] == name and y[3] > 0]
    return bool(d) and all(y[5] == 3 for y in d)


def _sf_tail(p):
    q = p.replace(os.sep, '/').lower().split('/')
    return (q[-2][len('xdklib_'):] if q[-2].startswith('xdklib_') else q[-2]) + '/' + q[-1] if len(q) > 1 else q[-1]


def _sfold_alias(o, name):
    import hashlib
    return '__sfold_' + hashlib.md5((_sf_tail(o) + ' ' + name).encode('latin-1')).hexdigest()[:16]


def merge(key, pieces, base_path, sources, by_addr, name_addr, name_row, alias_names, static_rows=frozenset()):
    """Write the stand-in object; returns its path."""
    picked = []         # (source path, section number) in output order
    sec_base = {}       # its image address (where a piece of it is placed)
    first_addr = {}
    for a, o, n in pieces:
        ob = obj(o)
        s = ob.defined.get(n)
        if s is None:
            continue
        k = (o, s[3])
        if k not in first_addr:
            first_addr[k] = a
            sec_base[k] = a - s[2]
            picked.append(k)
    # sections a picked section references within its source (static data, literals,
    # vtables, other functions), their COMDAT associates (EH data and the like), and the base
    # member's .CRT$ initializer pointers; repeated until nothing more comes in
    base0 = obj(base_path)
    extra = [(base_path, i + 1) for i, sc in enumerate(base0.secs) if sc['name'].startswith('.CRT$')
             and (base_path, i + 1) not in first_addr]
    # (and any source's .XAPI$ registration entry: xonline's launch hook in .XAPI$LNI, which the
    # installed version has and the 5849 copy lacks)
    for sp_ in sources:
        so_ = obj(sp_)
        extra += [(sp_, i + 1) for i, sc in enumerate(so_.secs) if sc['name'].startswith('.XAPI$')
                  and (sp_, i + 1) not in first_addr and (sp_, i + 1) not in extra]
    # every function and datum the member's own objects define (the link drops what nothing
    # references, and other members call some the pieces do not)
    bin_ = key in BINARIZE
    # (a binarized member keeps its uninitialized data, referenced or not: no bytes, and the
    # image keeps its room, fscaler's _gbTimer)
    if bin_:
        for p_ in sources:
            for i_, sc_ in enumerate(obj(p_).secs):
                if sc_['chars'] & 0x80 and (p_, i_ + 1) not in first_addr and (p_, i_ + 1) not in extra:
                    extra.append((p_, i_ + 1))
    taken_names = set()
    piece_addrs = set(a for a, o, n in pieces)
    for k in picked:
        taken_names.update(s[1] for s in obj(k[0]).syms if s[3] == k[1] and s[5] == 2)
    for p in ([] if bin_ else sources):
        ob = obj(p)
        for s in ob.syms:
            if s[5] == 2 and s[3] > 0 and s[1] not in taken_names:
                # (only what a row places or another object of the link names: a function of
                # the base version only, which the image's version lacks, would pull its own
                # callees' members in, and their data stays though /OPT:REF drops the code)
                if REFERENCED and s[1] not in name_row and s[1] not in REFERENCED:
                    continue
                # (nor a name a row places in another member: xnets' ip.obj has inline empty
                # IpConfigTerm/IpConfigReset, which the image has in ipcfg.obj)
                if s[1] in name_row and name_row[s[1]] not in piece_addrs:
                    continue
                nm_ = ob.secs[s[3] - 1]['name']
                if nm_.startswith('.debug') or nm_ == '.drectve':
                    continue
                k = (p, s[3])
                if k not in first_addr and k not in extra:
                    extra.append(k)
                taken_names.add(s[1])
    # a picked section's absolute reference into its own object's data that the image points
    # into one of this member's stand-in pieces (a table the image's version has in another
    # form: psffts' FFT tables) goes to that piece instead, and the object's own datum stays
    # out (it would keep its statics, code the image does not hold)
    retarget = {}
    if RETARGET:
        _pa = sorted(set(a for a, o, n in pieces if o.startswith('build/src/xdk/standin')))
        _all = sorted(by_addr)
        _pend = {}
        for a in _pa:
            k2 = bisect.bisect_right(_all, a)
            _pend[a] = _all[k2] if k2 < len(_all) else a
            # (no further than its image section's file bytes: past them lie the section's
            # uninitialized variables, D3D_URW, not this piece)
            for sc_ in image.sections:
                if sc_['va'] <= a < sc_['va'] + sc_['rsize']:
                    _pend[a] = min(_pend[a], sc_['va'] + sc_['rsize'])
        _pname = dict((a, n) for a, o, n in pieces if o.startswith('build/src/xdk/standin'))
        # (the picked sections, and the sources' data sections a row gives an address: a
        # member's table of string pointers, pathmisc's drive table)
        _bases = dict((k, sec_base[k]) for k in picked if k in sec_base)
        for p_ in sources:
            ob_ = obj(p_)
            for s_ in ob_.syms:
                if s_[3] > 0 and s_[1] in name_row and (p_, s_[3]) not in _bases \
                        and not ob_.secs[s_[3] - 1]['chars'] & 0x20:
                    _bases[(p_, s_[3])] = name_row[s_[1]] - s_[2]
        for (o, sn), _b in sorted(_bases.items()):
            if o.startswith('build/src/xdk/'):
                continue
            ob = obj(o)
            for va, si, t in ob.secs[sn - 1]['relocs']:
                s = ob.by_index.get(si)
                # (a static, or a literal COMDAT: pathmisc's \??\X: strings the image packs into
                # one of its pieces)
                if s is None or s[3] <= 0 or t != 6 or not (s[5] == 3 or s[1].startswith('??_C@')
                                                             or s[1].startswith('__real@')):
                    continue
                if ob.secs[s[3] - 1]['chars'] & 0x20:
                    continue
                try:
                    v = struct.unpack('<I', image.read(_b + va, 4))[0]
                except Exception:
                    continue
                stored = struct.unpack_from('<i', ob.secs[sn - 1]['data'], va)[0]
                tgt = (v - stored - s[2]) & 0xFFFFFFFF if s[5] == 3 and s[1] == ob.secs[s[3] - 1]['name'] else v
                k2 = bisect.bisect_right(_pa, v) - 1
                if k2 < 0 or not (_pa[k2] <= v < _pend[_pa[k2]]):
                    continue
                retarget[(o, sn, va)] = (_pname[_pa[k2]], v - _pa[k2])
    bret = {}           # (source, section, field) -> (row name, offset): binarized references
    bret_done = set()
    tail_refs = set()   # binarized references into a section's zero tail (their targets come along)
    tail_secs = set()   # sections only such references reach: zero-filled, without relocations
    if bin_:
        _rows_all = sorted(by_addr)
        _img_lo = min(sc_['va'] for sc_ in image.sections)
        _img_hi = max(sc_['va'] + sc_['vsize'] for sc_ in image.sections)

    # (a row named STATIC-0xN places the static N bytes after it: an EH handler's funclets)
    _minus = {}
    if bin_:
        for (o_, n_), a_ in obj_row.items():
            m_ = re.match(r'^(.*)-0x([0-9A-Fa-f]+)$', n_)
            if m_:
                _minus.setdefault((o_, m_.group(1)), a_ + int(m_.group(2), 16))
    _piece_at = dict((a_, n_) for a_, o_, n_ in pieces if o_.startswith('build/src/xdk/'))

    def _img_base(o, sn):
        # (a section's image address: its piece's, or a row of a name or static it defines)
        if (o, sn) in sec_base:
            return sec_base[(o, sn)]
        # (a row may name either library version's copy of the object)
        alt_ = [o, o.replace('/xdk/xdklib_', '/xdk/'), re.sub(r'/xdk/(?!xdklib_)', '/xdk/xdklib_', o, count=1)]
        for y_ in obj(o).syms:
            if y_[3] != sn:
                continue
            if y_[5] == 2 and y_[1] in name_row:
                return name_row[y_[1]] - y_[2]
            for oo_ in alt_:
                if y_[5] == 3 and (oo_, y_[1]) in obj_row:
                    return obj_row[(oo_, y_[1])] - y_[2]
                if y_[5] == 3 and (oo_, y_[1]) in _minus:
                    return _minus[(oo_, y_[1])] - y_[2]
        return None

    def _placed(o, sn):
        # (what a binarized member keeps: what the image places, and uninitialized data, also
        # zero-filled data the image holds in a section's zero tail: xgraphics' d3dxasm arrays)
        sc_ = obj(o).secs[sn - 1]
        if _img_base(o, sn) is not None or bool(sc_['chars'] & 0x80)                 or (not sc_['chars'] & 0x20 and bool(sc_['data']) and not any(sc_['data']) and not sc_['relocs']):
            return True
        # (a datum whose known address, config/aliases.txt's, lies in a section's zero tail)
        for y_ in obj(o).syms:
            if y_[3] == sn and y_[1] in name_addr and not sc_['chars'] & 0x20:
                a_ = name_addr[y_[1]]
                if any(x_['va'] + x_['rsize'] <= a_ < x_['va'] + x_['vsize'] for x_ in image.sections):
                    return True
        return False

    def _own_version(nm):
        # (a name only this member's sections no row places define: the library's version)
        for p_ in sources:
            d_ = obj(p_).defined.get(nm)
            if d_ is not None and (p_, d_[3]) not in first_addr:
                return True
        return False

    def _bret_section(o, sn):
        # (a binarized member's section the image places: each reference to a name no row has
        # goes where the image's field points)
        if (o, sn) in bret_done:
            return
        bret_done.add((o, sn))
        b_ = _img_base(o, sn)
        if b_ is None:
            return
        ob_ = obj(o)
        for va_, si_, t_ in ob_.secs[sn - 1]['relocs']:
            if t_ not in (6, 0x14) or (o, sn, va_) in retarget:
                continue
            y_ = ob_.by_index.get(si_)
            if y_ is None or (y_[1] in name_row and not _own_version(y_[1])):
                continue
            if y_[3] > 0 and ((o, y_[3]) in first_addr or (o, y_[1]) in obj_row):
                continue
            try:
                v_ = struct.unpack('<i', image.read(b_ + va_, 4))[0]
            except Exception:
                continue
            tg_ = (b_ + va_ + 4 + v_) if t_ == 0x14 else (v_ & 0xFFFFFFFF)
            # (a target in a section's zero tail, data the image's file does not hold: the
            # member's own variable, by its name)
            if any(sc_['va'] + sc_['rsize'] <= tg_ < sc_['va'] + sc_['vsize'] for sc_ in image.sections):
                tail_refs.add((o, sn, va_))
                continue
            k_ = bisect.bisect_right(_rows_all, tg_) - 1
            if tg_ in _piece_at:
                # (the image's piece there: the version this member's own code is not)
                bret[(o, sn, va_)] = (_piece_at[tg_], 0)
            elif _img_lo <= tg_ < _img_hi and k_ >= 0 and tg_ - _rows_all[k_] < 0x10000:
                nm_ = by_addr[_rows_all[k_]]
                # (a file-local function of another object, cd3dxstack's operator delete[]: by
                # the alias name the M7 probe gives it, tools/session/m7probe.py M7STATICFOLD)
                ro_ = _row_obj_at.get(_rows_all[k_])
                if ro_ and ro_ != o and _is_static_in(ro_, nm_):
                    STATIC_TARGETS.add((ro_, nm_))
                    nm_ = _sfold_alias(ro_, nm_)
                bret[(o, sn, va_)] = (nm_, tg_ - _rows_all[k_])
    if bin_:
        for o, sn in picked:
            _bret_section(o, sn)
    changed = True
    while changed:
        changed = False
        for o, sn in list(picked) + list(extra):
            ob = obj(o)
            if bin_:
                _bret_section(o, sn)
            for va, si, t in ([] if (o, sn) in tail_secs else ob.secs[sn - 1]['relocs']):
                if (o, sn, va) in retarget or (o, sn, va) in bret:
                    continue
                s = ob.by_index.get(si)
                if s is None:
                    continue
                if s[3] <= 0:
                    # a name the member's own objects define (a function with no row of its
                    # own, its image copy folded elsewhere) comes along from there; not one a
                    # row places in another member (ipcfg's IpConfigTerm, which xnets' ip.obj
                    # has as an empty inline)
                    if s[1] in name_row and name_row[s[1]] not in piece_addrs:
                        continue
                    for p in sources:
                        d = obj(p).defined.get(s[1])
                        if d is not None and d[5] == 2:
                            k = (p, d[3])
                            # (a binarized member takes only what the image places)
                            if bin_ and _img_base(o, sn) is not None and not _placed(p, d[3]) \
                                    and (o, sn, va) not in tail_refs:
                                break
                            if bin_ and (o, sn, va) in tail_refs and not _placed(p, d[3]):
                                tail_secs.add(k)
                            if k not in first_addr and k not in extra:
                                extra.append(k)
                                changed = True
                            break
                    continue
                k = (o, s[3])
                nm = ob.secs[s[3] - 1]['name']
                if k in first_addr or k in extra or nm.startswith('.debug') or nm == '.drectve':
                    continue
                # an external function another piece defines comes from that piece
                if s[5] == 2 and any(s[1] in obj(p).defined and (p, obj(p).defined[s[1]][3]) in first_addr
                                     for p, _ in picked):
                    continue
                # a public name with a row of its own (a piece of another member, or of this
                # one placed by its row) is linked by name, not copied along
                if s[5] == 2 and s[1] in name_row and o.startswith('build/src/xdk/'):
                    continue
                if bin_ and _img_base(o, sn) is not None and not _placed(o, s[3]) and (o, sn, va) not in tail_refs:
                    continue
                if bin_ and (o, sn, va) in tail_refs and not _placed(o, s[3]):
                    tail_secs.add(k)
                extra.append(k)
                changed = True
        for o, sn in list(picked) + list(extra):
            ob = obj(o)
            for s in ob.syms:
                if s[3] > 0 and s[5] == 3 and s[6] and s[1] == ob.secs[s[3] - 1]['name']:
                    if s[6][14] == 5 and struct.unpack_from('<H', s[6], 12)[0] == sn                             and not ob.secs[s[3] - 1]['name'].startswith('.debug'):
                        k = (o, s[3])
                        # (a binarized member: only EH data the image places; a function's own
                        # handler the image folds into another's is not there)
                        if bin_ and _img_base(o, s[3]) is None:
                            continue
                        if k not in first_addr and k not in extra:
                            extra.append(k)
                            changed = True
    # every section in image order: a section's address is its piece's, or the row address of
    # a name it defines; one with neither follows its predecessor in its source object
    def addr_of(k):
        if k in first_addr:
            return first_addr[k]
        o, sn = k
        for s in obj(o).syms:
            if s[3] == sn and s[5] == 2 and s[1] in name_row:
                return name_row[s[1]]
        # a static with a row of this very object (an EH FuncInfo, $Tn): the section starts
        # at that row less the static's offset
        for s in obj(o).syms:
            if s[3] == sn and s[5] == 3 and (o, s[1]) in obj_row:
                return obj_row[(o, s[1])] - s[2]
        return None
    keyed = []
    for k in picked + extra:
        a = addr_of(k)
        if a is None:
            o, sn = k
            prev = [x for x in picked + extra if x[0] == o and x[1] < sn and addr_of(x) is not None]
            a = addr_of(max(prev, key=lambda x: x[1])) if prev else 1 << 40
            keyed.append(((a, 1, sn), k))
        else:
            # (a row's own section before another version's copy of the same name, which
            # takes the row's address too and would otherwise claim the name first)
            keyed.append(((a, 0 if k in first_addr else 0.5, k[1]), k))
    order = [k for key_, k in sorted(keyed, key=lambda x: x[0])]
    # a section whose external names an earlier section already defines (the same COMDAT
    # literal or function from both versions) is left out; its references go to the first
    claimed = set()
    keep = []
    # the image's pieces (the stand-in sources, under the member's names) claim their names
    # first: the member's own version of such a function is left out wherever it would sit
    piece_names = set()
    for o, sn in order:
        if o.startswith('build/src/xdk/'):
            piece_names.update(s[1] for s in obj(o).syms if s[3] == sn and s[5] == 2)
    for o, sn in order:
        ob = obj(o)
        ext = [s[1] for s in ob.syms if s[3] == sn and s[5] == 2]
        if not o.startswith('build/src/xdk/') and ext and all(x in piece_names for x in ext):
            continue
        if ext and all(x in claimed for x in ext):
            continue
        # a COMDAT section is its COMDAT symbol (the first after the section's own): once
        # that name is claimed, the section goes
        if ob.secs[sn - 1]['chars'] & 0x1000:
            own = [s for s in ob.syms if s[3] == sn and s[1] != ob.secs[sn - 1]['name']]
            if own and own[0][1] in claimed:
                continue
        claimed.update(ext)
        keep.append((o, sn))
    # (a binarized member: only what the image places and what that reaches, by the references
    # left after the image's rewriting; a section the closure took for one since left out goes)
    if bin_:
        keepset = set(keep)
        live = set(k for k in keep if k in first_addr or _img_base(*k) is not None
                   or obj(k[0]).secs[k[1] - 1]['chars'] & 0x80
                   or obj(k[0]).secs[k[1] - 1]['name'].startswith(('.CRT$', '.XAPI$')))
        todo = list(live)
        while todo:
            o, sn = todo.pop()
            ob = obj(o)
            nxt = []
            for va, si, t in ([] if (o, sn) in tail_secs else ob.secs[sn - 1]['relocs']):
                if (o, sn, va) in retarget or (o, sn, va) in bret:
                    continue
                y = ob.by_index.get(si)
                if y is None:
                    continue
                if y[3] > 0:
                    nxt.append((o, y[3]))
                else:
                    for p in sources:
                        d = obj(p).defined.get(y[1])
                        if d is not None and d[5] == 2:
                            nxt.append((p, d[3]))
                            break
            # (its associates: EH data a kept function's section carries)
            for y in ob.syms:
                if y[3] > 0 and y[5] == 3 and y[6] and y[1] == ob.secs[y[3] - 1]['name'] and y[6][14] == 5 \
                        and struct.unpack_from('<H', y[6], 12)[0] == sn:
                    nxt.append((o, y[3]))
            for k in nxt:
                if k in keepset and k not in live:
                    live.add(k)
                    todo.append(k)
        if os.environ.get('XDK_DEBUGNAME'):
            for k in keep:
                if any(y[3] == k[1] and os.environ['XDK_DEBUGNAME'] in y[1] for y in obj(k[0]).syms):
                    print('DEBUG', k, k in live, k in first_addr, _img_base(*k))
        keep = [k for k in keep if k in live]
    # associative COMDAT sections right after the section they belong to
    assoc_of = {}
    for o, sn in keep:
        ob = obj(o)
        for s in ob.syms:
            if s[3] == sn and s[5] == 3 and s[6] and s[1] == ob.secs[sn - 1]['name'] and s[6][14] == 5:
                # (an associate with an image address of its own, an EH FuncInfo placed by its
                # row, keeps that place: the link lays .xdata$x out in section order)
                if ob.secs[sn - 1]['name'].startswith('.xdata') and addr_of((o, sn)) is not None:
                    continue
                # (one whose parent is not kept, a piece holding that function: on its own)
                if (o, struct.unpack_from('<H', s[6], 12)[0]) not in keep:
                    continue
                assoc_of[(o, sn)] = (o, struct.unpack_from('<H', s[6], 12)[0])
    order = []
    for k in keep:
        if k in assoc_of:
            continue
        order.append(k)
        order.extend(x for x in keep if assoc_of.get(x) == k)
    # (an associate whose section was left out goes with it)
    base = obj(base_path)
    drectve = [(base_path, i + 1) for i, sc in enumerate(base.secs) if sc['name'] == '.drectve']
    order = drectve + order
    newsec = {k: i + 1 for i, k in enumerate(order)}
    # the names a section of the stand-in defines itself (an alias name goes to a transcribed
    # piece only when no real definition has it)
    # a section with no piece but a row by name (a vtable, a table) has its image address too
    for o, sn in order:
        if (o, sn) not in sec_base:
            for s in obj(o).syms:
                if s[3] == sn and s[5] in (2, 3) and s[1] in name_row and s[1] != obj(o).secs[sn - 1]['name']:
                    sec_base[(o, sn)] = name_row[s[1]] - s[2]
                    break
    real_names = set()
    for o, sn in order:
        real_names.update(s[1] for s in obj(o).syms if s[3] == sn and s[5] == 2)
    # a data section of the member's own objects with no image address whose names are all
    # file-local (psffts' FFT tables): packaged, so /OPT:REF drops it with the code that
    # alone refers to it (a plain section would stay, and keep the statics it points at)
    dropdata = set()
    if RETARGET:
        for k in order:
            o, sn = k
            ob = obj(o)
            sc = ob.secs[sn - 1]
            if o.startswith('build/src/xdk/') or sc['chars'] & 0x20 or sc['chars'] & 0x1000 \
                    or sc['name'].startswith('.debug') or sc['name'] == '.drectve' or not sc['data'] \
                    or '$' in sc['name'] or sc['name'].startswith('.CRT'):
                continue
            if k in sec_base or k in first_addr:
                continue
            mine = [s for s in ob.syms if s[3] == sn and s[1] != sc['name']]
            secsym = [s for s in ob.syms if s[3] == sn and s[1] == sc['name'] and s[5] == 3 and s[6]]
            # (not one that points at a row's function: the image holds that, reached through
            # this table, psdfts' rFFT statics)
            refs_row = any(ob.by_index.get(si) is not None and ob.by_index[si][1] in name_row
                           for va, si, ty in sc['relocs'])
            if mine and secsym and all(s[5] == 3 and s[1] not in name_row for s in mine) \
                    and mine[0][2] == 0 and not refs_row:
                dropdata.add(k)
    # (a binarized member's data section whose variables' rows disagree with its own layout,
    # the image's version another: the image's bytes from its first row to the next object's
    # row, each variable at its row, one without a row at the start. x86.obj's WMADEC_RW: the
    # image's version has g_bSupportCMOV (-1) first, then g_iSupportMMXCount)
    relaid = {}
    if bin_:
        for k in order:
            o, sn = k
            sc = obj(o).secs[sn - 1]
            if sc['chars'] & 0xA0 or sc['relocs'] or not sc['data']:
                continue
            alt_ = [o, o.replace('/xdk/xdklib_', '/xdk/'), re.sub(r'/xdk/(?!xdklib_)', '/xdk/xdklib_', o, count=1)]
            at = {}
            for y_ in obj(o).syms:
                if y_[3] != sn or y_[5] not in (2, 3) or y_[1] == sc['name']:
                    continue
                a_ = name_row.get(y_[1]) if y_[5] == 2 else \
                    next((obj_row[(oo_, y_[1])] for oo_ in alt_ if (oo_, y_[1]) in obj_row), None)
                if a_ is not None:
                    at[y_[1]] = (a_, y_[2])
            if len(at) < 2 or len(set(a_ - v_ for a_, v_ in at.values())) == 1:
                continue
            base = min(a_ for a_, v_ in at.values())
            k_ = bisect.bisect_right(_rows_all, base)
            while k_ < len(_rows_all) and _row_obj_at.get(_rows_all[k_]) in alt_:
                k_ += 1
            end = min(_rows_all[k_] if k_ < len(_rows_all) else base + len(sc['data']), base + len(sc['data']))
            relaid[k] = (base, end - base, dict((nm_, a_ - base) for nm_, (a_, v_) in at.items()))
    # symbols: per section its section symbol (with aux) and defined symbols; then externals
    out_syms = []       # (name, value, secno, type, cls, aux)
    index_of = {}       # (source path, old index) -> new index
    names_defined = {}
    names_static = {}
    n = 0
    for k in order:
        o, sn = k
        ob = obj(o)
        for s in ob.syms:
            # function begin/end/line records (.bf, .ef, .lf) and function aux records point
            # at the source's symbol indices; the link needs neither
            if s[3] != sn or s[5] in (101, 103):
                continue
            aux = s[6]
            if not (s[5] == 3 and s[1] == ob.secs[sn - 1]['name']):
                aux = b''
            if aux and k in dropdata and s[5] == 3 and s[1] == ob.secs[sn - 1]['name']:
                aux = aux[:14] + bytes([2]) + aux[15:]
            if aux and s[5] == 3 and s[1] == ob.secs[sn - 1]['name']:
                sel = aux[14]
                if sel == 5:
                    assoc = struct.unpack_from('<H', aux, 12)[0]
                    na = newsec.get((o, assoc), 0)
                    aux = aux[:12] + struct.pack('<H', na) + aux[14:]
                    if not na:
                        # (its parent left out, a piece holding that function: a COMDAT of its
                        # own, kept by its row's references)
                        aux = aux[:14] + bytes([2]) + aux[15:]
            if s[5] == 2 and s[1] in names_defined:
                index_of[(o, s[0])] = names_defined[s[1]]
                continue
            index_of[(o, s[0])] = n
            if s[5] == 2:
                names_defined[s[1]] = n
            elif s[5] == 3 and s[1] != ob.secs[sn - 1]['name'] and not s[1].startswith('$'):
                # a static of the stand-in (a transcribed piece reaches it by its row's name)
                names_static.setdefault(s[1], n)
            _val = s[2]
            if k in relaid and s[1] != ob.secs[sn - 1]['name']:
                _val = relaid[k][2].get(s[1], 0)
            out_syms.append((s[1], _val, newsec[k], s[4], s[5], aux))
            n += 1 + len(aux) // 18
            # a transcribed piece (_sub_XXXXXX) also defines the names config/aliases.txt
            # gives its address (the export the game calls it by)
            m = re.match(r'^_(sub|unk|loc)_([0-9A-F]{6,8})$', s[1])
            if m and s[5] == 2:
                for al in alias_names.get(int(m.group(2), 16), []):
                    if al not in names_defined and al not in real_names:
                        names_defined[al] = n
                        out_syms.append((al, s[2], newsec[k], s[4], 2, b''))
                        n += 1
    externs = {}
    pending = {}
    weak = {}
    absolute = {}
    delta_of = {}
    row_addrs = sorted(by_addr)
    for k in order:
        o, sn = k
        ob = obj(o)
        for va, si, t in ([] if k in tail_secs else ob.secs[sn - 1]['relocs']):
            if (o, sn, va) in retarget or (o, sn, va) in bret or (o, si) in index_of:
                continue
            s = ob.by_index[si]
            nm = s[1]
            if nm in names_defined:
                index_of[(o, si)] = names_defined[nm]
            elif s[3] > 0 and s[5] == 3:
                # (a binarized member: the field keeps the image's value, unrelocated)
                if bin_ and sec_base.get((o, sn)) is not None and t == 6:
                    absolute[(o, sn, va)] = True
                    continue
                # a static in a section left out (debug): keep it as an undefined name
                raise SystemExit('%s: %s refers to %s in an omitted section' % (key, o, nm))
            else:
                # a name of the stand-ins' transcription (_sub_XXXXXX/_unk_XXXXXX address
                # names, the database's names): the row at that address gives the linked name;
                # an address inside a row's piece is that row plus the offset (added to the
                # relocated field)
                addr = None
                m = re.match(r'^_(sub|unk|loc|off|byte|word|dword|flt|dbl|stru|asc)_([0-9A-F]{6,8})$', nm)
                # (an import's address slot, __imp_X, stays a name: the link takes it from the
                # import library and lists it in the import table imagebld turns into the
                # kernel thunk table; the image's slot lies inside the stand-in table piece)
                if nm.startswith('__imp_'):
                    m = None
                elif m:
                    addr = int(m.group(2), 16)
                elif nm in name_addr:
                    addr = name_addr[nm]
                if addr is not None:
                    if addr in by_addr:
                        nm = by_addr[addr]
                    elif m or o.startswith("build/src/xdk/"):
                        k2 = bisect.bisect_right(row_addrs, addr) - 1
                        if k2 >= 0:
                            nm = by_addr[row_addrs[k2]]
                            delta_of[(o, si)] = addr - row_addrs[k2]
                # a name no row has: the image says where the field points (a piece of known
                # address); the row there gives the linked name
                if nm not in name_row and nm not in names_defined and (o, sn) in sec_base and t in (6, 0x14) \
                        and not nm.startswith('__imp_'):
                    fa = sec_base[(o, sn)] + va
                    try:
                        v = struct.unpack('<i', image.read(fa, 4))[0]
                        tgt = (fa + 4 + v) if t == 0x14 else (v & 0xFFFFFFFF)
                        stored = struct.unpack_from('<i', ob.secs[sn - 1]['data'], va)[0]
                        tgt -= stored
                        if tgt in by_addr:
                            nm = by_addr[tgt]
                    except Exception:
                        pass
                if nm in names_static and nm not in names_defined:
                    index_of[(o, si)] = names_static[nm]
                    continue
                # a static of another object (a row's name, reached by a dword that only looks
                # like an address): an absolute field keeps the image's value, unrelocated
                if nm in static_rows and nm not in names_defined and t == 6:
                    absolute[(o, sn, va)] = True
                    continue
                # a vector deleting destructor no row has, where the class's scalar deleting
                # destructor has one: the image's version of the class has only that (its
                # vtable slot holds it, as config/aliases.txt records for others)
                if nm.startswith('??_E') and nm not in name_row and nm not in names_defined                         and ('??_G' + nm[4:]) in name_row:
                    nm = '??_G' + nm[4:]
                if nm in names_defined:
                    index_of[(o, si)] = names_defined[nm]
                    continue
                if nm not in externs:
                    externs[nm] = (len(externs), s[2] if s[3] == 0 else 0, s[4])
                    if s[5] == 105 and s[6]:
                        # a weak external (??_E defaulting to ??_G): its default by name
                        dflt = ob.by_index.get(struct.unpack_from('<I', s[6], 0)[0])
                        if dflt is not None:
                            weak[nm] = (dflt[1], s[6][4:])
                pending[(o, si)] = nm
    # (a member's common variables, which no kept relocation may name when its code is the
    # image's bytes: xcontent's RootDirectory; the probe places them by address like .bss)
    if os.environ.get('XR_COMMONS', '1') != '0':
        for o_ in dict.fromkeys(o for o, sn in order):
            for s in obj(o_).syms:
                if s[3] == 0 and s[5] == 2 and s[2] > 0 and s[1] not in names_defined and s[1] not in externs:
                    externs[s[1]] = (len(externs), s[2], s[4])
    # the undefined names in the base member's symbol-table order (the link queues them in
    # that order, which decides what it pulls next), then the rest as first referenced
    base_order = {}
    for s in obj(base_path).syms:
        if s[3] == 0 and s[5] == 2:
            base_order.setdefault(s[1], len(base_order))
    ext_index = {}
    for nm in sorted(externs, key=lambda x: (0, base_order[x]) if x in base_order else (1, externs[x][0])):
        if nm in weak:
            continue
        ext_index[nm] = n
        out_syms.append((nm, externs[nm][1], 0, externs[nm][2], 2, b''))
        n += 1
    for nm, (dflt, rest) in sorted(weak.items()):
        if dflt in names_defined:
            di = names_defined[dflt]
        elif dflt in ext_index:
            di = ext_index[dflt]
        else:
            di = n
            ext_index[dflt] = n
            out_syms.append((dflt, 0, 0, 0x20, 2, b''))
            n += 1
        ext_index[nm] = n
        out_syms.append((nm, 0, 0, externs[nm][2], 105, struct.pack('<I', di) + rest))
        n += 2
    for nm, _off in sorted(set(bret.values())):
        if nm not in names_defined and nm not in names_static and nm not in ext_index:
            ext_index[nm] = n
            out_syms.append((nm, 0, 0, 0x20, 2, b''))
            n += 1
    for k_, nm in pending.items():
        index_of[k_] = ext_index[nm]
    # write
    strtab = bytearray()

    def sname(nm):
        b = nm.encode('latin-1')
        if len(b) <= 8:
            return b.ljust(8, b'\0')
        off = len(strtab) + 4
        strtab.extend(b + b'\0')
        return struct.pack('<II', 0, off)

    hdr_size = 20 + 40 * len(order)
    body = bytearray()
    sec_hdrs = []
    pos = hdr_size
    for k in order:
        o, sn = k
        sc = obj(o).secs[sn - 1]
        nm = sc['name'].encode('latin-1')
        # (a zero-filled tail section of a binarized member: uninitialized data under the
        # library's uninitialized name, XGRPH_URW, laid out by address like .bss)
        if k in tail_secs and sc['name'].endswith('_RW'):
            nm = (sc['name'][:-3] + '_URW').encode('latin-1')
        # (a binarized member's data the image holds in another output section, x86.obj's
        # WMADEC_RW the image's version has in .data: that section's name)
        if bin_ and not sc['chars'] & 0x20 and _img_base(o, sn) is not None:
            _isec = next((x_['name'] for x_ in image.sections
                          if x_['va'] <= _img_base(o, sn) < x_['va'] + x_['vsize']), None)
            _own = re.sub(r'_(RD|RW|URW)$', '', sc['name'].split('$')[0])
            if _isec in ('.data', '.rdata') and _own not in ('.data', '.rdata', '.bss', _isec)                     and not _own.startswith('.'):
                nm = _isec.encode('latin-1')
        if len(nm) > 8:
            raw = ('/%d' % (len(strtab) + 4)).encode().ljust(8, b'\0')
            strtab.extend(nm + b'\0')
        else:
            raw = nm.ljust(8, b'\0')
        data = bytearray(sc['data'])
        if k in tail_secs:
            data = bytearray()
        # (a binarized member's data section longer than the room the image gives it, before
        # the next row: the image's version is shorter, x86.obj's two-variable WMADEC_RW)
        trunc = None
        if k in relaid:
            trunc = relaid[k][1]
            data = bytearray(image.read(relaid[k][0], trunc))
        elif bin_ and not sc['chars'] & 0x20 and data and _img_base(o, sn) is not None:
            _b = _img_base(o, sn)
            _k = bisect.bisect_right(_rows_all, _b)
            if _k < len(_rows_all) and _rows_all[_k] - _b < len(data) and                     _row_obj_at.get(_rows_all[_k]) not in (o, o.replace('/xdk/xdklib_', '/xdk/')):
                trunc = _rows_all[_k] - _b
                data = data[:trunc]
        for va, si, t in ([] if k in tail_secs else sc['relocs']):
            if trunc is not None and va + 4 > trunc:
                continue
            if (o, sn, va) in retarget:
                struct.pack_into('<i', data, va, retarget[(o, sn, va)][1])
                continue
            if (o, sn, va) in bret:
                struct.pack_into('<i', data, va, bret[(o, sn, va)][1])
                continue
            dl = delta_of.get((o, si))
            if dl and t in (6, 7, 0x14) and va + 4 <= len(data):
                struct.pack_into('<i', data, va, struct.unpack_from('<i', data, va)[0] + dl)
        for va, si, t in ([] if k in tail_secs else sc['relocs']):
            if (o, sn, va) in absolute and sec_base.get((o, sn)) is not None                     and (trunc is None or va + 4 <= trunc):
                # the image's value stays in the field
                data[va:va + 4] = image.read(sec_base[(o, sn)] + va, 4)
        data = bytes(data)
        ptr = pos if data else 0
        body.extend(data)
        pos += len(data)
        rel = bytearray()
        nrel = 0
        for va, si, t in ([] if k in tail_secs else sc['relocs']):
            if trunc is not None and va + 4 > trunc:
                continue
            if (o, sn, va) in absolute:
                continue
            if (o, sn, va) in retarget:
                rel.extend(struct.pack('<IIH', va, names_defined[retarget[(o, sn, va)][0]], t))
                nrel += 1
                continue
            if (o, sn, va) in bret:
                _bn = bret[(o, sn, va)][0]
                rel.extend(struct.pack('<IIH', va, names_defined[_bn] if _bn in names_defined
                                       else names_static[_bn] if _bn in names_static else ext_index[_bn], t))
                nrel += 1
                continue
            rel.extend(struct.pack('<IIH', va, index_of[(o, si)], t))
            nrel += 1
        relptr = pos if rel else 0
        body.extend(rel)
        pos += len(rel)
        _ch = sc['chars'] | (0x1000 if k in dropdata else 0)
        if k in tail_secs:
            _ch = (_ch & ~0x40) | 0x80
        sec_hdrs.append(raw + struct.pack('<IIIIIIHHI', 0, 0, trunc if trunc is not None else sc['size'], ptr, relptr, 0,
                                          nrel, 0, _ch))
    symptr = pos
    symbytes = bytearray()
    for nm, value, secno, typ, cls, aux in out_syms:
        symbytes.extend(sname(nm) + struct.pack('<IhHBB', value, secno, typ, cls, len(aux) // 18) + aux)
    head = struct.pack('<HHIIIHH', 0x14C, len(order), 0, symptr, n, 0, 0)
    blob = head + b''.join(sec_hdrs) + bytes(body) + bytes(symbytes) + struct.pack('<I', len(strtab) + 4) + bytes(strtab)
    lib, mem = key
    path = os.path.join(OUT, lib, mem)
    os.makedirs(os.path.dirname(path), exist_ok=True)
    open(path, 'wb').write(blob)
    return path


def main():
    all_rows = rows()
    mem = members(all_rows)
    assign(all_rows)
    # an address's name: its row, a real (not address-named) one first
    by_addr = {}
    for a, o, n in all_rows:
        # pseudo-names of EH table rows (NAME-0x8, NAME>1>8) are no symbols
        if re.search(r'(-0x[0-9A-Fa-f]+|>\d.*)$', n):
            continue
        # a section's name (XNET) is no symbol to link by
        if n[:1] not in '_?$':
            continue
        if not re.match(r'^_(sub|unk|loc)_', n) or a not in by_addr:
            by_addr[a] = n
    name_row = {}
    for a, o, n in all_rows:
        name_row.setdefault(n, a)
    for a, o, n in all_rows:
        _row_obj_at.setdefault(a, o)
    global obj_row
    obj_row = dict(((o, n), a) for a, o, n in all_rows)
    # every name an object of the link (one with rows) leaves undefined
    if os.environ.get('XDK_REFONLY') == '1':
        for o in sorted(set(o for a, o, n in all_rows)):
            try:
                ob = obj(o)
            except (OSError, ValueError, struct.error):
                continue
            REFERENCED.update(s[1] for s in ob.syms if s[3] == 0 and s[5] == 2)
    # rows that are statics of their object (no other object can name them)
    static_rows = set()
    static_owner = {}
    for a, o, n in all_rows:
        try:
            s = obj(o).defined.get(n)
        except (OSError, ValueError, struct.error):
            continue
        if s is not None and s[5] == 3:
            static_rows.add(n)
            if o.startswith('build/xdk/'):
                static_owner[n] = keyof(o)
    # a database or alias name's address (the transcription names targets by them)
    name_addr = {}
    for l in anonfix.lines(os.path.join(ROOT, 'config', 'symbols.txt'), errors='replace'):
        q = l.split(None, 4)
        if len(q) == 5 and q[0].startswith('0x'):
            nm = q[4].strip()
            name_addr.setdefault(nm if nm[:1] in '_?' else '_' + nm, int(q[0], 16))
    alias_names = collections.defaultdict(list)
    for l in anonfix.lines(os.path.join(ROOT, 'config', 'aliases.txt')):
        q = l.split('#', 1)[0].split()
        if len(q) >= 2 and q[1].startswith('0x'):
            name_addr.setdefault(q[0], int(q[1], 16))
            alias_names[int(q[1], 16)].append(q[0])
    # (a row's own name at its row: the database names another copy so too, CXnBase's
    # PoolAllocZ at XONLINE's 0x3698D9, the row's is XNET's at 0x37EEAA)
    name_addr.update(name_row)
    # an address a transcribed piece holds is linked by its alias name rather than _sub_
    for a, o, n in all_rows:
        if re.match(r'^_(sub|unk|loc)_', n) and by_addr.get(a) == n and alias_names.get(a):
            by_addr[a] = alias_names[a][0]
    reassign_by_statics(all_rows, by_addr, static_owner)
    want = [tuple(x.split('/')) for x in sys.argv[1:]]
    out = []
    used = set()
    for key in sorted(mem):
        if want and key not in want:
            continue
        mrows = mem[key]
        if not mixed(key, mrows, all_rows) and key not in BINARIZE:
            continue
        # the base: the version holding most of its rows (its .drectve and archive name)
        base = collections.Counter(o for a, o, n in mrows).most_common(1)[0][0]
        sources = [base] + sorted(set(o for a, o, n in mrows) - {base})
        path = merge(key, pieces_of(key, mrows, all_rows), base, sources, by_addr, name_addr, name_row, alias_names, static_rows)
        # every library copy of the member (xnets' and xonlines') takes the stand-in
        for b in sorted(set(o for a, o, n in mrows if not o.split('/')[2].startswith('xdklib_')) | {base}):
            out.append((key[0], b, path))
        print('%s/%s: %d pieces -> %s' % (key[0], key[1], len(pieces_of(key, mrows, all_rows)), os.path.relpath(path, ROOT)))
        used.update(r for r in pieces_of(key, mrows, all_rows) if r[1].startswith('build/src/xdk/'))
    if not want:
        # the stand-in pieces no member took (the TrueType interpreter, crypto thunks, CRT
        # and EH pieces, import thunks...): one object the probe links explicitly
        rest = [r for r in all_rows if r[1].startswith('build/src/xdk/') and r not in used]
        # (the import table opening .rdata, 0x3CD300-0x3CD5A0: an object of its own, which the
        # probe links first)
        imp = [r for r in rest if 0x3CD300 <= r[0] < 0x3CD5A0]
        rest = [r for r in rest if r not in imp]
        if imp:
            path = merge(('standin', 'imports.obj'), imp, imp[0][1], [], by_addr, name_addr, name_row, alias_names, static_rows)
            out.append(('IMPORTS', '-', path))
            print('imports: %d pieces -> %s' % (len(imp), os.path.relpath(path, ROOT)))
        if rest:
            path = merge(('standin', 'rest.obj'), rest, rest[0][1], [], by_addr, name_addr, name_row, alias_names, static_rows)
            out.append(('REST', '-', path))
            print('rest: %d pieces -> %s' % (len(rest), os.path.relpath(path, ROOT)))
        with open(os.path.join(OUT, 'static_targets.txt'), 'w') as f:
            for o_, n_ in sorted(STATIC_TARGETS):
                f.write('%s %s\n' % (o_, n_))
        with open(os.path.join(OUT, 'members.txt'), 'w') as f:
            for lib, base, path in out:
                f.write('%s %s %s\n' % (lib, base, os.path.relpath(path, ROOT).replace(os.sep, '/')))


main()
