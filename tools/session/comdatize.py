"""comdatize.py IN OUT: a copy of the COFF object IN whose plain code sections are packaged
(COMDAT, no duplicates), so the M7 link's /ORDER file can place them (PLAN M7; the owner's
/ORDER decision, docs/PLAN.md). Each such section's COMDAT symbol is the first symbol defined in
it after its section symbol; when that is not external it becomes external, renamed
`_cdz_<object>_<section>` when its name is not one only it has. Prints, per section made a
COMDAT, `NAME FIRST_DEFINED_NAME...` lines on stdout (the order file names the section by NAME;
the other names locate it in the image)."""
import os
import re
import struct
import sys
sys.path.insert(0, os.path.join(os.path.dirname(os.path.abspath(__file__)), '..'))
import anonfix  # noqa: E402  (anonymous-namespace hashes of other checkouts)

# the COMDAT names of the sections convert() packaged that were plain (the original link kept
# such a section whenever its object was linked: /OPT:REF removes COMDATs only)
PLAIN = []
# the names of file-local (static) packaged functions convert() made external under a name of
# their own
STATIC_NAMES = set()
# the names convert() disowned (see disown)
DISOWNED = []
# the external names the disowned copies refer to (see disown)
DISOWN_REFS = set()
BSS_ZAP = os.environ.get('M7BSSZAP', '1') != '0'
# (m7probe.py, config/m7bssrw.txt: uninitialized variables the image's library version holds
# initialized, among its _RW section's variables: placed under the _RW name)
BSS_RW = set()
# (M7CRTLOW, default on: the initializer table, 0x426D58..0x4273B4, keyed by its addresses'
# low five digits, which link.exe's eight-character suffix comparison sees after XCU)
KEY_LOW = {'.CRT$XCU'} if os.environ.get('M7CRTLOW', '1') != '0' else set()
# a running count for CDZ_PADSTATIC (different fill lengths across objects)
_PAD = [0]
# the section bodies to pad (m7probe's duplicate .text$yc/.text$yd bodies); None pads every one
PAD_BODIES = None


def convert(src, dst, tag, nofold=False, disown=frozenset(), nofold_static=None):
    d = bytearray(open(src, 'rb').read())
    machine, nsec, _, symptr, nsyms, optsize, _ = struct.unpack_from('<HHIIIHH', d, 0)
    if machine != 0x14C:
        open(dst, 'wb').write(bytes(d))
        return []
    strtab_off = symptr + nsyms * 18
    strtab = bytearray(d[strtab_off:])
    secs = []
    for i in range(nsec):
        o = 20 + optsize + i * 40
        chars = struct.unpack_from('<I', d, o + 36)[0]
        size = struct.unpack_from('<I', d, o + 16)[0]
        secs.append((o, chars, size))
    syms = []
    i = 0
    while i < nsyms:
        off = symptr + i * 18
        raw = bytes(d[off:off + 8])
        v, sec, t, c, na = struct.unpack_from('<IhHBB', d, off + 8)
        if raw[:4] == b'\0\0\0\0':
            so = struct.unpack_from('<I', raw, 4)[0]
            nm = bytes(strtab[so:strtab.index(b'\0', so)]).decode('latin-1')
        else:
            nm = raw.rstrip(b'\0').decode('latin-1')
        syms.append((i, off, nm, v, sec, t, c, na))
        i += 1 + na
    out = []
    unfold = []
    pads = []
    for sn, (o, chars, size) in enumerate(secs, 1):
        if (chars & 0x20) and (chars & 0x1000) and size:
            # a packaged function whose COMDAT symbol is static (a file-local function):
            # external under a name of its own, so /ORDER can name it
            mine = [s for s in syms if s[4] == sn]
            # (a file-local function by its own set when one is given: a static of another object
            # with a row's name may fold, XGRAPHICS' per-object operator delete)
            _nf = nofold_static if (nofold_static is not None and len(mine) > 1 and mine[1][6] == 3) else nofold
            if len(mine) > 1 and (_nf == 'all' or (isinstance(_nf, (set, frozenset)) and mine[1][2] in _nf)
                                  or (_nf is not None and not isinstance(_nf, (bool, str, set, frozenset)) and mine[1][2] in _nf)):
                unfold.append((o, mine[1][0]))
            if len(mine) > 1 and mine[0][6] == 3:
                idx, off, nm, v, sec, t, c, na = mine[1]
                # (not an EH handler thunk: the order file leaves those out, and an external
                # name in a function's .text$x keeps link.exe from folding the function with
                # identical ones, which the image's are: unit_1FC320's _Buynode instances)
                # (CDZ_KEEPY=1, measuring: nor a dynamic initializer or terminator, .text$yc/.text$yd: an external name
                # lets link.exe fold identical ones, which the image keeps apart (logic.obj's
                # empty $E28/$E30/$E32), and static they keep their objects' order in their group)
                if c == 3 and t == 0x20 and not nm.startswith('$') and not nm.startswith('.') \
                        and not nm.startswith('__ehhandler$') \
                        and not (os.environ.get('CDZ_KEEPY', '0') != '0' and bytes(d[o:o + 7]) == b'.text$y'):
                    newname = '_cdz_%s_%d' % (tag, sn)
                    enc = newname.encode('latin-1')
                    if len(enc) <= 8:
                        d[off:off + 8] = enc.ljust(8, b'\0')
                    else:
                        d[off:off + 8] = struct.pack('<II', 0, len(strtab))
                        strtab += enc + b'\0'
                    d[off + 16] = 2
                    out.append((newname, [nm]))
                    STATIC_NAMES.add(nm)
                    # (CDZ_PADSTATIC, default on for .text$yc/.text$yd: the original link never
                    # folds a file-local function, so an identical one made external here gets
                    # int3 bytes of its own count after its end, inside the 16-byte alignment
                    # fill link.exe lays down anyway: it can no longer fold, and nothing moves)
                    _ptr = struct.unpack_from('<I', d, o + 20)[0]
                    if os.environ.get('CDZ_PADSTATIC', 'y') == 'all' or \
                            (os.environ.get('CDZ_PADSTATIC', 'y') == 'y' and bytes(d[o:o + 7]) == b'.text$y'
                             and (PAD_BODIES is None or bytes(d[_ptr:_ptr + size]) in PAD_BODIES)):
                        # (the room the section's own alignment leaves; a byte-aligned section, UIX's
                        # initializers, has none)
                        al = 1 << (((chars >> 20) & 0xF) - 1) if (chars >> 20) & 0xF else 16
                        room = (al - size % al) % al
                        if room:
                            _PAD[0] += 1
                            pads.append((o, 1 + _PAD[0] % room, mine[0][1] + 18))
            continue
        if not (chars & 0x20) or (chars & 0x1000) or size == 0:
            continue
        mine = [s for s in syms if s[4] == sn]
        if not mine or mine[0][6] != 3 or mine[0][7] < 1:
            continue        # no section symbol with an aux record
        secsym = mine[0]
        rest = [s for s in mine[1:] if s[6] in (2, 3, 6)]
        if not rest:
            continue
        first = rest[0]
        idx, off, nm, v, sec, t, c, na = first
        newname = nm
        if c != 2:
            newname = '_cdz_%s_%d' % (tag, sn)
            enc = newname.encode('latin-1')
            if len(enc) <= 8:
                d[off:off + 8] = enc.ljust(8, b'\0')
            else:
                d[off:off + 8] = struct.pack('<II', 0, len(strtab))
                strtab += enc + b'\0'
            d[off + 16] = 2
        # the section: packaged, its symbol's aux selection "no duplicates"
        struct.pack_into('<I', d, o + 36, chars | 0x1000)
        d[secsym[1] + 18 + 14] = 1
        if nofold:
            unfold.append((o, idx))
        out.append((newname, [s[2] for s in rest if s[6] == 2 or s is first]))
        PLAIN.append((tag,) + out[-1])
    # disown: a packaged function (an inline the header gives many objects) whose image copy
    # is another object's: this copy's COMDAT symbol becomes file-local under a name of its
    # own and the object's references go to a new undefined symbol of the name, so the link
    # takes the owner's copy whichever object comes first (and drops this one, unreferenced)
    newsyms = []
    retarget = {}
    removed_secs = {}   # removed copy's section -> its name's new undefined symbol
    for sn, (o, chars, size) in enumerate(secs, 1):
        # (a string literal's COMDAT too, when the image pools it into another copy)
        if not disown or not ((chars & 0x20) or (chars & 0x40)) or not ((chars & 0x1000) and size):
            continue
        mine = [s for s in syms if s[4] == sn]
        if len(mine) < 2 or mine[1][6] != 2 or mine[1][2] not in disown:
            continue
        if not (chars & 0x20) and not mine[1][2].startswith('??_C@'):
            continue
        idx, off, nm, v, sec, ty, c, na = mine[1]
        local = ('_cdzx_%s_%d' % (tag, sn)).encode('latin-1')
        d[off:off + 8] = struct.pack('<II', 0, len(strtab))
        strtab += local + b'\0'
        d[off + 16] = 3
        enc = nm.encode('latin-1')
        if len(enc) <= 8:
            name8 = enc.ljust(8, b'\0')
        else:
            name8 = struct.pack('<II', 0, len(strtab))
            strtab += enc + b'\0'
        retarget[idx] = nsyms + len(newsyms)
        newsyms.append(name8 + struct.pack('<IhHBB', 0, 0, 0x20, 2, 0))
        DISOWNED.append(nm)
        # (DISOWN_REMOVE, default on, for the functions config/aliases.txt folds: the copy itself removed, IMAGE_SCN_LNK_REMOVE: left in,
        # identical-function folding may keep it, under its file-local name no /ORDER line
        # names, and the whole folded group goes to the end: unit_1FC320's _Buynode)
        if os.environ.get('DISOWN_REMOVE', '1') != '0' and (chars & 0x20) and nm in REMOVE_OK:
            struct.pack_into('<I', d, o + 36, chars | 0x800)
            removed_secs[sn] = retarget[idx]
        # (the external names this copy refers to: link.exe would count them referenced whether
        # it kept the copy or folded it, so the caller keeps them)
        relptr_ = struct.unpack_from('<I', d, o + 24)[0]
        nrel_ = struct.unpack_from('<H', d, o + 32)[0]
        byidx = dict((s_[0], s_) for s_ in syms)
        for r in range(nrel_):
            si_ = struct.unpack_from('<I', d, relptr_ + r * 10 + 4)[0]
            t_ = byidx.get(si_)
            if t_ is not None and t_[6] == 2:
                DISOWN_REFS.add(t_[2])
    if newsyms:
        sym_at = dict((s_[0], (s_[3], s_[4], s_[6])) for s_ in syms)
        for sn, (o, chars, size) in enumerate(secs, 1):
            ptr = struct.unpack_from('<I', d, o + 24)[0]
            cnt = struct.unpack_from('<H', d, o + 32)[0]
            for r in range(cnt):
                si = struct.unpack_from('<I', d, ptr + r * 10 + 4)[0]
                if si in retarget:
                    struct.pack_into('<I', d, ptr + r * 10 + 4, retarget[si])
                # (a label inside a removed copy, a kept EH table's catch block or funclet
                # target: the copy's name plus the label's offset, so it lands in the copy the
                # image folds it into; left alone, the label went to an unrelated body)
                elif removed_secs and si in sym_at and sym_at[si][1] in removed_secs and sym_at[si][2] == 3:
                    va = struct.unpack_from('<I', d, ptr + r * 10)[0]
                    t = struct.unpack_from('<H', d, ptr + r * 10 + 8)[0]
                    dp = struct.unpack_from('<I', d, o + 20)[0]
                    if t in (6, 0x14) and dp:
                        struct.pack_into('<I', d, ptr + r * 10 + 4, removed_secs[sym_at[si][1]])
                        struct.pack_into('<i', d, dp + va, struct.unpack_from('<i', d, dp + va)[0] + sym_at[si][0])
        struct.pack_into('<I', d, 12, nsyms + len(newsyms))
        d = d[:strtab_off] + b''.join(newsyms)
        strtab_off = len(d)
    struct.pack_into('<I', strtab, 0, len(strtab))
    d = d[:strtab_off] + strtab
    # nofold: a section that was plain (the original link could neither fold nor move it) gets
    # an ignored relocation (IMAGE_REL_I386_ABSOLUTE) to its own COMDAT symbol, so link.exe's
    # identical-function folding never merges it with another
    for o, idx in unfold:
        ptr = struct.unpack_from('<I', d, o + 24)[0]
        cnt = struct.unpack_from('<H', d, o + 32)[0]
        old = bytes(d[ptr:ptr + 10 * cnt]) if cnt else b''
        newptr = len(d)
        d += old + struct.pack('<IIH', 0, idx, 0)
        struct.pack_into('<I', d, o + 24, newptr)
        struct.pack_into('<H', d, o + 32, cnt + 1)
    for o, k, aux in pads:
        ptr = struct.unpack_from('<I', d, o + 20)[0]
        size = struct.unpack_from('<I', d, o + 16)[0]
        newptr = len(d)
        d += bytes(d[ptr:ptr + size]) + b'\xcc' * k
        struct.pack_into('<I', d, o + 20, newptr)
        struct.pack_into('<I', d, o + 16, size + k)
        struct.pack_into('<I', d, aux, size + k)
    open(dst, 'wb').write(bytes(d))
    return out


def staticfold(src, dst, defines, refs):
    """Writes the object SRC to DST with the file-local functions the image folds into another
    object's copy sent there (PLAN M7, staticfold.py): DEFINES maps a function this object
    holds (the image's copy) to an alias name, added as an external symbol at the same place;
    REFS maps a static of this object to the alias of the copy the image keeps, its
    relocations going to a new undefined external of that name (the static, unreferenced,
    is dropped by /OPT:REF). Returns the number of symbols added."""
    d = bytearray(open(src, 'rb').read())
    machine, nsec, _, symptr, nsyms, optsize, _ = struct.unpack_from('<HHIIIHH', d, 0)
    if machine != 0x14C:
        return 0
    strtab = bytearray(d[symptr + nsyms * 18:])
    syms = []
    i = 0
    while i < nsyms:
        off = symptr + i * 18
        raw = bytes(d[off:off + 8])
        v, sec, t, c, na = struct.unpack_from('<IhHBB', d, off + 8)
        if raw[:4] == b'\0\0\0\0':
            so = struct.unpack_from('<I', raw, 4)[0]
            nm = bytes(strtab[so:strtab.index(b'\0', so)]).decode('latin-1')
        else:
            nm = raw.rstrip(b'\0').decode('latin-1')
        syms.append((i, nm, v, sec, t, c, na))
        i += 1 + na

    def name8(nm):
        enc = nm.encode('latin-1')
        if len(enc) <= 8:
            return enc.ljust(8, b'\0')
        r = struct.pack('<II', 0, len(strtab))
        strtab.extend(enc + b'\0')
        return r

    new = []
    done = set()
    for idx, nm, v, sec, t, c, na in syms:
        if nm in defines and sec > 0 and c in (2, 3) and nm not in done:
            done.add(nm)
            new.append(name8(defines[nm]) + struct.pack('<IhHBB', v, sec, t, 2, 0))
    retarget = {}
    for idx, nm, v, sec, t, c, na in syms:
        # (a static function symbol has an aux record too under /Zi; a section symbol is not one)
        if nm in refs and sec > 0 and c == 3 and (not na or t == 0x20):
            retarget[idx] = nsyms + len(new)
            new.append(name8(refs[nm]) + struct.pack('<IhHBB', 0, 0, 0x20, 2, 0))
    if not new:
        open(dst, 'wb').write(bytes(d))
        return 0
    for sn in range(1, nsec + 1):
        o = 20 + optsize + (sn - 1) * 40
        ptr = struct.unpack_from('<I', d, o + 24)[0]
        cnt = struct.unpack_from('<H', d, o + 32)[0]
        for r in range(cnt):
            si = struct.unpack_from('<I', d, ptr + r * 10 + 4)[0]
            if si in retarget:
                struct.pack_into('<I', d, ptr + r * 10 + 4, retarget[si])
    struct.pack_into('<I', d, 12, nsyms + len(new))
    struct.pack_into('<I', strtab, 0, len(strtab))
    d = d[:symptr + nsyms * 18] + b''.join(new) + strtab
    open(dst, 'wb').write(bytes(d))
    return len(new)


def selfcalls(path):
    """Gives each raw recursive call of a function in the object PATH (a stand-in piece's
    `db 0E8h, ...` to its own entry, which MASM resolved inside the segment) a REL32
    relocation to the function's symbol, its field zeroed: the bytes the link writes are the
    same, but link.exe's identical-function folding no longer takes byte-identical recursive
    pieces for one function, which the image keeps apart (XGRAPHICS' clear_node instances;
    an IMAGE_REL_I386_ABSOLUTE relocation does not keep them apart). Returns the number
    added."""
    d = bytearray(open(path, 'rb').read())
    machine, nsec, _, symptr, nsyms, optsize, _ = struct.unpack_from('<HHIIIHH', d, 0)
    if machine != 0x14C:
        return 0
    bysec = {}
    i = 0
    while i < nsyms:
        off = symptr + i * 18
        v, sec, t, c, na = struct.unpack_from('<IhHBB', d, off + 8)
        if sec > 0 and c in (2, 3, 6) and not (c == 3 and na and t != 0x20):
            bysec.setdefault(sec, []).append((v, i))
        i += 1 + na
    added = 0
    for sn in range(1, nsec + 1):
        o = 20 + optsize + (sn - 1) * 40
        chars = struct.unpack_from('<I', d, o + 36)[0]
        size, ptr, rptr = struct.unpack_from('<III', d, o + 16)
        nrel = struct.unpack_from('<H', d, o + 32)[0]
        if not (chars & 0x20) or not size or sn not in bysec:
            continue
        covered = set()
        for r in range(nrel):
            va = struct.unpack_from('<I', d, rptr + r * 10)[0]
            covered.update(range(va, va + 4))
        starts = sorted(set(bysec[sn]))
        ends = [s[0] for s in starts[1:]] + [size]
        new = []
        for (v, idx), e in zip(starts, ends):
            k = d.find(b'\xe8', ptr + v, ptr + e - 4)
            while k >= 0:
                site = k - ptr + 1
                if site not in covered and site + 3 not in covered \
                        and struct.unpack_from('<i', d, k + 1)[0] == v - (site + 4):
                    new.append((site, idx))
                    covered.update(range(site, site + 4))
                k = d.find(b'\xe8', k + 1, ptr + e - 4)
        if not new:
            continue
        for site, idx in new:
            struct.pack_into('<i', d, ptr + site, 0)
        old = bytes(d[rptr:rptr + 10 * nrel]) if nrel else b''
        newptr = len(d)
        d += old + b''.join(struct.pack('<IIH', site, idx, 0x14) for site, idx in new)
        struct.pack_into('<I', d, o + 24, newptr)
        struct.pack_into('<H', d, o + 32, nrel + len(new))
        added += len(new)
    if added:
        open(path, 'wb').write(bytes(d))
    return added


_EH_TABLE_ROWS = None     # (ehfold: handler names whose funcinfo has a row)


MULTI_DEFINED = set()     # (m7probe.py: functions more than one object defines)


REMOVE_OK = set()     # (m7probe.py: names the image folds into another's body, config/aliases.txt)
LOOSE_OK = set()     # (m7probe.py: functions config/aliases.txt folds into another's body)


def ehfold(path, pairs):
    """Rewrites the object PATH so each (DUP, KEEP) pair of EH handler names (static, in .text$x
    sections associative to their functions) is folded the image's way: every reference to a
    symbol of DUP's section goes to the symbol at the same offset of KEEP's (the function's
    handler push and its funcinfo's unwind funclets), and DUP's section becomes a standalone
    COMDAT, which /OPT:REF then drops. link.exe folds identical handlers itself, but which copy
    it keeps depends on its whole input (tested: 15 unrelated objects together flip unit_1C3120's
    pair), so the image's survivor, its row's name, is chosen here. Returns the pairs done."""
    sys.path.insert(0, os.path.join(os.path.dirname(os.path.abspath(__file__)), '..'))
    from coff import Coff
    c = Coff(path)
    d = bytearray(c.data)
    symptr = struct.unpack_from('<I', d, 8)[0]
    nsec = struct.unpack_from('<H', d, 2)[0]
    optsize = struct.unpack_from('<H', d, 16)[0]
    by = {}
    for y in c.symbol_list:
        if y['section'] > 0:
            by.setdefault(y['name'], y)
    remap, drop, alone, done = {}, set(), set(), []
    for dup, keep in pairs:
        ds, ks = by.get(dup), by.get(keep)
        if ds is None or ks is None or ds['section'] == ks['section']:
            continue
        dsec, ksec = c.sections[ds['section'] - 1], c.sections[ks['section'] - 1]
        # (EHFOLD_LOOSE, default on: a handler of the same length whose bytes differ, a copy of
        # a function the link drops anyway (config/aliases.txt folds it): its funclets are the
        # kept one's, its table kept with them: list<type_3E4E40>'s destructor, whose frame
        # offset the specialization for sub_1D0390 moved)
        _same = dsec['data'] == ksec['data'] or (
            os.environ.get('EHFOLD_LOOSE', '1') != '0' and dup[len('__ehhandler$'):] in LOOSE_OK
            and len(dsec['data'] or b'') == len(ksec['data'] or b''))
        if dsec['name'] != '.text$x' or not _same:
            continue
        kat = {}
        for y in c.symbol_list:
            if y['section'] == ks['section'] and y['name'] != ksec['name']:
                kat.setdefault(y['value'], y['index'])
        mine = [y for y in c.symbol_list if y['section'] == ds['section'] and y['name'] != dsec['name']]
        if any(y['value'] not in kat for y in mine):
            continue
        for y in mine:
            remap[y['index']] = kat[y['value']]
        drop.add(ds['section'])
        alone.add(ks['section'])
        done.append((dup, keep))
    for i in range(nsec):
        if i + 1 in drop and i + 1 not in alone:
            continue
        o = 20 + optsize + i * 40
        relptr, nrel = struct.unpack_from('<I', d, o + 24)[0], struct.unpack_from('<H', d, o + 32)[0]
        for r in range(nrel):
            ro = relptr + r * 10
            si = struct.unpack_from('<I', d, ro + 4)[0]
            if si in remap:
                struct.pack_into('<I', d, ro + 4, remap[si])
    # (the kept copy standalone too, when EHFOLD_KEEPALONE is not 0: every function of the group,
    # folded ones included, then has the same associative sections)
    if os.environ.get('EHFOLD_KEEPALONE', '1') != '0':
        drop |= alone - drop
    for sn in drop:
        secsym = next(y for y in c.symbol_list if y['section'] == sn and y['name'] == c.sections[sn - 1]['name'])
        ao = symptr + (secsym['index'] + 1) * 18
        struct.pack_into('<H', d, ao + 12, 0)
        d[ao + 14] = 2          # (any: unreferenced, /OPT:REF removes it)
    # (EHFOLD_KEEPXDATA, default on: a folded handler's own funcinfo stays, a plain section
    # where its function's COMDATs were: the image keeps every instance's EH tables although
    # the functions and their handlers fold, unit_1FC320's _Tree instances)
    if os.environ.get('EHFOLD_KEEPXDATA', '1') != '0':
        global _EH_TABLE_ROWS
        if _EH_TABLE_ROWS is None:
            root = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
            _EH_TABLE_ROWS = set()
            for l in anonfix.lines(os.path.join(root, 'config', 'compiled.txt')):
                q = l.split()
                if len(q) >= 3 and q[2].startswith('__ehhandler$') and '>' in q[2]:
                    _EH_TABLE_ROWS.add(q[2].split('>')[0])
        for dup, keep in done:
            # (only a funcinfo the image keeps beside the kept one's: both rows, the handlers'
            # names with >1; unit_1E9F60's _Uninit_copy pair has one table, named the dup's)
            if dup not in _EH_TABLE_ROWS or (keep not in _EH_TABLE_ROWS and os.environ.get("EHFOLD_KEEPBOTH") == "1"):
                continue
            # (EHFOLD_SOLE=1: not a header inline another object defines too, whose copy there
            # keeps its own table)
            if os.environ.get('EHFOLD_SOLE') == '1' and dup[len('__ehhandler$'):] in MULTI_DEFINED:
                continue
            dsn = by[dup]['section']
            # (EHFOLD_KEEPXDATA_KEEP=1, measuring, off: no effect so far; the kept handler's own funcinfo too, which
            # otherwise goes with its function's COMDATs: unit_1D0100's sub_1D3F80<type_3E4E40>)
            hsecs = [dsn]
            if os.environ.get('EHFOLD_KEEPXDATA_KEEP') == '1' and keep in _EH_TABLE_ROWS and keep in by:
                hsecs.append(by[keep]['section'])
            # (and every table those name in turn: the try map's handler arrays, in sections
            # of their own, associative to the function too)
            work_ = [r_ for h_ in hsecs for r_ in c.sections[h_ - 1]['relocs']]
            seen_ = set()
            while work_:
                va, si, t = work_.pop()
                ts = c.symbols[si]['section']
                if ts > 0 and c.sections[ts - 1]['name'] == '.xdata$x' and ts not in seen_:
                    seen_.add(ts)
                    work_.extend(c.sections[ts - 1]['relocs'])
                    o = 20 + optsize + (ts - 1) * 40
                    ch = struct.unpack_from('<I', d, o + 36)[0]
                    struct.pack_into('<I', d, o + 36, ch & ~0x1000)
                    if os.environ.get('EHFOLD_LOG') and ch & 0x1000:
                        with open(os.environ['EHFOLD_LOG'], 'a') as f_:
                            f_.write('%s %s %d\n' % (path, dup, len(c.sections[ts - 1]['data'] or b'')))
    if done:
        open(path, 'wb').write(bytes(d))
    return done


def eh_export(path, handler, tag):
    """Makes the symbols of the section holding the handler HANDLER (static) in the object PATH
    external, named `_cdzeh_<tag>_<offset>`, so another object's identical copy can be folded
    into it (eh_import). Returns True when done."""
    sys.path.insert(0, os.path.join(os.path.dirname(os.path.abspath(__file__)), '..'))
    from coff import Coff
    c = Coff(path)
    h = next((y for y in c.symbol_list if y['name'] == handler and y['section'] > 0), None)
    if h is None:
        return False
    d = bytearray(c.data)
    symptr = struct.unpack_from('<I', d, 8)[0]
    nsyms = struct.unpack_from('<I', d, 12)[0]
    strtab = bytearray(d[symptr + nsyms * 18:])
    sec = c.sections[h['section'] - 1]
    for y in c.symbol_list:
        if y['section'] == h['section'] and y['name'] != sec['name']:
            off = symptr + y['index'] * 18
            nm = ('_cdzeh_%s_%d' % (tag, y['value'])).encode('latin-1')
            d[off:off + 8] = struct.pack('<II', 0, len(strtab))
            strtab += nm + b'\0'
            d[off + 16] = 2
    struct.pack_into('<I', strtab, 0, len(strtab))
    d = d[:symptr + nsyms * 18] + strtab
    open(path, 'wb').write(bytes(d))
    return True


def eh_import(path, handler, tag):
    """The object PATH's handler HANDLER (static, in a .text$x section) folded into another
    object's identical copy exported by eh_export under TAG: references to its section's
    symbols go to new undefined externals `_cdzeh_<tag>_<offset>`, and the section becomes a
    standalone COMDAT, which /OPT:REF drops. Returns True when done."""
    sys.path.insert(0, os.path.join(os.path.dirname(os.path.abspath(__file__)), '..'))
    from coff import Coff
    c = Coff(path)
    h = next((y for y in c.symbol_list if y['name'] == handler and y['section'] > 0), None)
    if h is None:
        return False
    d = bytearray(c.data)
    nsec = struct.unpack_from('<H', d, 2)[0]
    symptr = struct.unpack_from('<I', d, 8)[0]
    nsyms = struct.unpack_from('<I', d, 12)[0]
    optsize = struct.unpack_from('<H', d, 16)[0]
    hdr = 20 + optsize
    strtab = bytearray(d[symptr + nsyms * 18:])
    sec = c.sections[h['section'] - 1]
    news, remap = [], {}
    for y in c.symbol_list:
        if y['section'] == h['section'] and y['name'] != sec['name']:
            nm = ('_cdzeh_%s_%d' % (tag, y['value'])).encode('latin-1')
            name8 = struct.pack('<II', 0, len(strtab))
            strtab += nm + b'\0'
            remap[y['index']] = nsyms + len(news)
            news.append(name8 + struct.pack('<IhHBB', 0, 0, 0x20, 2, 0))
    for i in range(nsec):
        if i + 1 == h['section']:
            continue
        o = hdr + i * 40
        relptr, nrel = struct.unpack_from('<I', d, o + 24)[0], struct.unpack_from('<H', d, o + 32)[0]
        for r in range(nrel):
            ro = relptr + r * 10
            si = struct.unpack_from('<I', d, ro + 4)[0]
            if si in remap:
                struct.pack_into('<I', d, ro + 4, remap[si])
    secsym = next(y for y in c.symbol_list if y['section'] == h['section'] and y['name'] == sec['name'])
    ao = symptr + (secsym['index'] + 1) * 18
    struct.pack_into('<H', d, ao + 12, 0)
    d[ao + 14] = 2
    struct.pack_into('<I', d, 12, nsyms + len(news))
    struct.pack_into('<I', strtab, 0, len(strtab))
    d = d[:symptr + nsyms * 18] + b''.join(news) + strtab
    open(path, 'wb').write(bytes(d))
    return True



def _keyname(name, addr):
    """NAME keyed by ADDR: NAME$ADDR, or for a name with a $ already (.xdata$x, .text$x) the
    address appended to its suffix in as few digits as keep the suffix eight characters
    (M7KEY8, default on): link.exe orders a group's sections by the first eight characters
    of the suffix, so x$0041E764 and x$0041E788 tied and kept their input order."""
    if '$' in name and os.environ.get('M7KEY8', '1') != '0':
        base, sub = name.split('$', 1)
        digits = 8 - len(sub)
        if digits >= 6 and addr < 16 ** digits:
            return '%s$%s%0*X' % (base, sub, digits, addr)
        # (KEY_LOW: the address's low digits only, a table lying within one window of them:
        # .CRT$XCU$ADDR names tied at XCU$0042 and kept the objects' order)
        if name in KEY_LOW:
            return '%s$%s%0*X' % (base, sub, digits, addr % 16 ** digits)
    return '%s$%08X' % (name, addr)


def _zname(name):
    """NAME's unkeyed name, after every keyed one: NAME$zzzzzzzz, or for a KEY_LOW name its
    suffix filled out with z's (XCUzzzzz: XCU$zzzz would sort before XCU26D58)."""
    if name in KEY_LOW and os.environ.get('M7KEY8', '1') != '0':
        base, sub = name.split('$', 1)
        return '%s$%s%s' % (base, sub, 'z' * (8 - len(sub)))
    return '%s$zzzzzzzz' % name


def data_layout(path, row_addr, names, comdat_addr=None):
    """Renames the object PATH's data sections named in NAMES to `NAME$ADDRESS` (link sorts a
    group's sections by name across objects, so they lie in the image's order whatever the
    objects' order): ADDRESS the image address of the section's first row (ROW_ADDR, symbol
    name -> address); a section without a row follows the previous keyed section of its object
    (`NAME$ADDRESS_n`), one before any keyed section goes last (`NAME$zzzzzzzz`). Returns the
    number of sections renamed."""
    sys.path.insert(0, os.path.join(os.path.dirname(os.path.abspath(__file__)), '..'))
    from coff import Coff
    c = Coff(path)
    d = bytearray(c.data)
    symptr = struct.unpack_from('<I', d, 8)[0]
    nsyms = struct.unpack_from('<I', d, 12)[0]
    optsize = struct.unpack_from('<H', d, 16)[0]
    hdr = 20 + optsize
    strtab = bytearray(d[symptr + nsyms * 18:])
    first = {}
    for y in c.symbol_list:
        if y['section'] <= 0:
            continue
        a = row_addr.get(y['name'])
        # (a name only another object's rows give, COMDATS_ADDR: for a COMDAT only, one copy of
        # it kept; a plain section's own duplicate definition, contsig's _WDrive, is not that row)
        if a is None and comdat_addr and c.sections[y['section'] - 1]['chars'] & 0x1000:
            a = comdat_addr.get(y['name'])
        if a is not None:
            first[y['section']] = min(first.get(y['section'], 1 << 40), a)
    # (a section without symbols, an initializer table's .CRT$XCU: its row is `NAME+0`)
    for sn, s in enumerate(c.sections, 1):
        if s['name'] in names and sn not in first and row_addr.get(s['name'] + '+0') is not None:
            first[sn] = row_addr[s['name'] + '+0']
    n = 0
    # (the previous keyed section of the same name: XON_RD after a .data row is not its follower)
    prev_of, count_of = {}, {}
    for sn, s in enumerate(c.sections, 1):
        if s['name'] not in names:
            continue
        prev, count = prev_of.get(s['name']), count_of.get(s['name'], 0)
        if s['chars'] & 0x1000:
            # (a COMDAT keeps one name in every object that defines it, or link no longer
            # takes the copies for one: its own row's address, or the end)
            new = _keyname(s['name'], first[sn]) if sn in first else _zname(s['name'])
        elif sn in first:
            prev, count = first[sn], 0
            new = _keyname(s['name'], first[sn])
        elif prev is not None:
            count += 1
            new = '%s_%d' % (_keyname(s['name'], prev), count)
        else:
            new = _zname(s['name'])
        prev_of[s['name']], count_of[s['name']] = prev, count
        # (DATA_ZAP, default on: an empty unkeyed section byte-aligned, so its alignment pads
        # nothing before the next group: an empty 16-aligned .rdata put .xdata$x 4 late)
        # (and an unkeyed COMDAT, which /OPT:REF drops, the image having no room for it: the
        # group's start is still aligned for it, an empty .rdata$zzzzzzzz put .xdata$x 4 late)
        # (not an EH table's: one with no row is still kept, its handler live)
        if new == _zname(s['name']) and (not s['size'] or (s['chars'] & 0x1000
                                                             and not s['name'].startswith('.xdata'))) \
                and os.environ.get('DATA_ZAP', '1') != '0':
            o_ = hdr + (sn - 1) * 40 + 36
            struct.pack_into('<I', d, o_, (struct.unpack_from('<I', d, o_)[0] & ~0x00F00000) | 0x00100000)
        enc = new.encode('latin-1')
        off = len(strtab)
        strtab.extend(enc + b'\0')
        d[hdr + (sn - 1) * 40:hdr + (sn - 1) * 40 + 8] = ('/%d' % off).encode('latin-1').ljust(8, b'\0')
        n += 1
    if n:
        struct.pack_into('<I', strtab, 0, len(strtab))
        d = d[:symptr + nsyms * 18] + strtab
        open(path, 'wb').write(bytes(d))
    return n


def bss_layout(path, placed, commons=frozenset()):
    """Rewrites the object PATH's uninitialized data so link lays it out at the image's addresses
    (PLAN M7): each .bss variable PLACED gives (its name -> (address, size)) gets a section of its
    own named `.bss$ADDRESS` (link sorts a group's sections by name, across objects), aligned to
    1 and sized to the next placed variable's address; the variables without an address are
    compacted into `.bss$zzzzzzzz`, after them all. A COMDAT .bss section (an inline function's
    local static) is renamed and resized whole. The COMMON symbols named in COMMONS become this
    object's definitions, at their addresses. References through a split section's own symbol go
    to the variable's symbol (the addend moved). VC7.1 lays out an object's .bss in its symbol
    hash's order, which recovered names cannot reproduce. Returns the number of variables placed."""
    sys.path.insert(0, os.path.join(os.path.dirname(os.path.abspath(__file__)), '..'))
    from coff import Coff
    c = Coff(path)
    d = bytearray(c.data)
    nsec = struct.unpack_from('<H', d, 2)[0]
    symptr = struct.unpack_from('<I', d, 8)[0]
    nsyms = struct.unpack_from('<I', d, 12)[0]
    optsize = struct.unpack_from('<H', d, 16)[0]
    hdr = 20 + optsize
    strtab = bytearray(d[symptr + nsyms * 18:])
    newhdrs = []        # (name, size, chars)
    sym_sec = {}        # symbol index -> (new section index in newhdrs, value)
    retarget = {}       # old section number -> [(start, end, symbol index)]
    n = 0

    def hdr_name(name):
        enc = name.encode('latin-1')
        if len(enc) <= 8:
            return enc.ljust(8, b'\0')
        off = len(strtab)
        strtab.extend(enc + b'\0')
        return ('/%d' % off).encode('latin-1').ljust(8, b'\0')

    for sn, s in enumerate(c.sections, 1):
        if not (s['chars'] & 0x80) or not (s['name'].startswith('.bss') or s['name'].split('$')[0].endswith('_URW')):
            continue
        # (a library's uninitialized section, D3D_URW: its variables under its own name)
        pfx = s['name'].split('$')[0]

        def pfx_of(nm, pfx=pfx):
            return pfx[:-4] + '_RW' if nm in BSS_RW and pfx.endswith('_URW') else pfx
        mine = sorted((y['value'], y['index'], y['name']) for y in c.symbol_list
                      if y['section'] == sn and y['name'] != s['name'])
        o = hdr + (sn - 1) * 40
        if s['chars'] & 0x1000:
            # (a COMDAT: one variable, renamed and resized in place)
            k = next((nm for v, i, nm in mine if nm in placed), None)
            if k is not None:
                a, size = placed[k]
                d[o:o + 8] = hdr_name('%s$%08X' % (pfx_of(k), a))
                struct.pack_into('<I', d, o + 16, size)
                struct.pack_into('<I', d, o + 36, (s['chars'] & ~0x00F00000) | 0x00100000)
                n += 1
            continue
        rest, spans = [], []
        for k_, (v, i, nm) in enumerate(mine):
            end = mine[k_ + 1][0] if k_ + 1 < len(mine) else s['size']
            if nm in placed:
                a, size = placed[nm]
                sym_sec[i] = (len(newhdrs), 0)
                spans.append((v, end, i))
                newhdrs.append(('%s$%08X' % (pfx_of(nm), a), size, (s['chars'] & ~0x00F00000) | 0x00100000))
                n += 1
            else:
                rest.append((v, end, i))
        retarget[sn] = spans
        # the rest, compacted in their order (4-aligned, 8 for 8 bytes or more)
        pos = 0
        for v, end, i in rest:
            al = 8 if end - v >= 8 else 4
            pos = (pos + al - 1) // al * al
            struct.pack_into('<I', d, symptr + i * 18 + 8, pos)
            spans.append((v, end, None, pos))
            pos += end - v
        d[o:o + 8] = hdr_name('%s$zzzzzzzz' % pfx)
        # (BSS_ZAP: the unplaced rest takes no room: the placed variables' rooms, each up to the
        # next one's address, already hold the image's unreferenced ones)
        struct.pack_into('<I', d, o + 16, 0 if BSS_ZAP else pos)
        if BSS_ZAP:
            # (and no alignment: an empty 16-aligned section pads its group's end)
            struct.pack_into('<I', d, o + 36, (s['chars'] & ~0x00F00000) | 0x00100000)
    # COMMONs this object defines
    for y in c.symbol_list:
        if y['section'] == 0 and y['class'] == 2 and y['value'] > 0 and y['name'] in commons and y['name'] in placed:
            a, size = placed[y['name']]
            sym_sec[y['index']] = (len(newhdrs), 0)
            newhdrs.append(('.bss$%08X' % a, size, 0xC0100080))
            n += 1
    if not n:
        # (nothing placed: the renamed, compacted sections only)
        struct.pack_into('<I', strtab, 0, len(strtab))
        d = d[:symptr + nsyms * 18] + strtab
        open(path, 'wb').write(bytes(d))
        return 0
    # references through a split section's own symbol: to the variable's symbol, addend moved
    secsym = {}
    for y in c.symbol_list:
        if y['section'] in retarget and y['name'] == c.sections[y['section'] - 1]['name'] and y['class'] == 3:
            secsym[y['index']] = y['section']
    for sn, s in enumerate(c.sections, 1):
        ptr = struct.unpack_from('<I', d, hdr + (sn - 1) * 40 + 20)[0]
        relptr = struct.unpack_from('<I', d, hdr + (sn - 1) * 40 + 24)[0]
        nrel = struct.unpack_from('<H', d, hdr + (sn - 1) * 40 + 32)[0]
        for r in range(nrel):
            ro = relptr + r * 10
            va, si, t = struct.unpack_from('<IIH', d, ro)
            if si not in secsym or t not in (6, 7):
                continue
            add = struct.unpack_from('<i', d, ptr + va)[0]
            for sp in retarget[secsym[si]]:
                if sp[0] <= add < sp[1]:
                    if sp[2] is not None:
                        struct.pack_into('<I', d, ro + 4, sp[2])
                        struct.pack_into('<i', d, ptr + va, add - sp[0])
                    else:
                        struct.pack_into('<i', d, ptr + va, add - sp[0] + sp[3])
                    break
    # the new section headers, appended (everything after the header table moves)
    hend = hdr + nsec * 40
    extra = b''.join(hdr_name(nm) + struct.pack('<IIIIIIHHI', 0, 0, size, 0, 0, 0, 0, 0, ch)
                     for nm, size, ch in newhdrs)
    shift = len(extra)
    d = bytearray(d[:hend]) + extra + bytearray(d[hend:symptr + nsyms * 18])
    struct.pack_into('<H', d, 2, nsec + len(newhdrs))
    for i in range(nsec + len(newhdrs)):
        o = hdr + i * 40
        for f in (20, 24, 28):
            v = struct.unpack_from('<I', d, o + f)[0]
            if v:
                struct.pack_into('<I', d, o + f, v + shift)
    symptr += shift
    struct.pack_into('<I', d, 8, symptr)
    for i, (k, v) in sym_sec.items():
        struct.pack_into('<Ih', d, symptr + i * 18 + 8, v, nsec + 1 + k)
    struct.pack_into('<I', strtab, 0, len(strtab))
    d += strtab
    # (BSS_RW: those sections initialized, zeros appended after the string table: link.exe
    # lays out a group's uninitialized contributions after its initialized ones; and no
    # COMDAT: the image keeps them unreferenced, as a plain section's data)
    nsec = struct.unpack_from('<H', d, 2)[0]
    for i in range(nsec):
        o = hdr + i * 40
        raw = bytes(d[o:o + 8])
        if raw[:1] == b'/':
            so = int(raw[1:].rstrip(b'\0'))
            nm = bytes(strtab[so:strtab.index(b'\0', so)]).decode('latin-1')
        else:
            nm = raw.rstrip(b'\0').decode('latin-1')
        ch = struct.unpack_from('<I', d, o + 36)[0]
        size = struct.unpack_from('<I', d, o + 16)[0]
        if BSS_RW and '_RW$' in nm and ch & 0x80 and size:
            struct.pack_into('<I', d, o + 20, len(d))
            struct.pack_into('<I', d, o + 36, (ch & ~0x1080) | 0x40)
            d += bytes(size)
    open(path, 'wb').write(bytes(d))
    return n


def move_families(path, units):
    """Rewrites the object PATH so the sections UNITS names (a list of section numbers, in the
    order wanted) and, with each, every section associative to it come after all the others,
    in that order: their headers are appended to the section table (the old slots left empty
    and IMAGE_SCN_LNK_REMOVE), symbols and associative references renumbered. link.exe lays
    out a group's unlisted COMDATs, the EH handlers' .text$x and the funcinfo .xdata$x,
    associative to their functions, in the section order of those functions, which the
    compiler's template instantiation order sets (unit_1E8350's set<type_1F8040>: erase's
    handler after _Insert's here, before it in the image; moving a handler's own header does
    nothing, its function's family moves it: tested). Returns the moved section numbers."""
    sys.path.insert(0, os.path.join(os.path.dirname(os.path.abspath(__file__)), '..'))
    from coff import Coff
    c = Coff(path)
    d = bytearray(c.data)
    nsec = struct.unpack_from('<H', d, 2)[0]
    symptr = struct.unpack_from('<I', d, 8)[0]
    optsize = struct.unpack_from('<H', d, 16)[0]
    hdr = 20 + optsize
    secsym, assoc = {}, {}
    for y in c.symbol_list:
        sn = y['section']
        if sn > 0 and y['class'] == 3 and y['value'] == 0 and y['name'] == c.sections[sn - 1]['name'] \
                and sn not in secsym:
            secsym[sn] = y['index']
            if c.sections[sn - 1]['chars'] & 0x1000 and d[symptr + y['index'] * 18 + 17]:
                ao = symptr + (y['index'] + 1) * 18
                if d[ao + 14] == 5:
                    assoc[sn] = struct.unpack_from('<H', d, ao + 12)[0]
    moved = []
    for p in units:
        if p in moved:
            continue
        fam = [p]
        changed = True
        while changed:
            changed = False
            for s, par in assoc.items():
                if par in fam and s not in fam:
                    fam.append(s)
                    changed = True
        # (MOVE_THROWINFO=1, measuring, off: the catchable types and throw info a family's code
        # names, .xdata$x COMDATs of no function, go with it, as the compiler emitted them
        # beside the function: left behind, they come before every moved family's funcinfo)
        if os.environ.get('MOVE_THROWINFO') == '1':
            refd = []
            for s in [p] + sorted(fam[1:]):
                for va, si, t in c.sections[s - 1]['relocs']:
                    ts = c.symbols[si]['section'] if si in c.symbols else 0
                    if ts > 0 and ts not in fam and ts not in assoc and ts not in moved and ts not in refd \
                            and c.sections[ts - 1]['name'] == '.xdata$x' and c.sections[ts - 1]['chars'] & 0x1000:
                        refd.append(ts)
            # (and what those name in turn: a throw info's catchable type array and types)
            k = 0
            while k < len(refd):
                for va, si, t in c.sections[refd[k] - 1]['relocs']:
                    ts = c.symbols[si]['section'] if si in c.symbols else 0
                    if ts > 0 and ts not in fam and ts not in assoc and ts not in moved and ts not in refd \
                            and c.sections[ts - 1]['name'] == '.xdata$x' and c.sections[ts - 1]['chars'] & 0x1000:
                        refd.append(ts)
                k += 1
            fam.extend(refd)
        moved.extend(s for s in [p] + sorted(fam[1:]) if s not in moved)
    if not moved:
        return []
    hend = hdr + nsec * 40
    newnum = {s: nsec + 1 + i for i, s in enumerate(moved)}
    extra = b''.join(bytes(d[hdr + (s - 1) * 40:hdr + s * 40]) for s in moved)
    for s in moved:
        o = hdr + (s - 1) * 40
        d[o + 16:o + 40] = struct.pack('<IIIIHHI', 0, 0, 0, 0, 0, 0, 0x800)
    shift = len(extra)
    d = bytearray(d[:hend]) + extra + bytearray(d[hend:])
    struct.pack_into('<H', d, 2, nsec + len(moved))
    for i in range(nsec + len(moved)):
        o = hdr + i * 40
        for f in (20, 24, 28):
            v = struct.unpack_from('<I', d, o + f)[0]
            if v:
                struct.pack_into('<I', d, o + f, v + shift)
    symptr += shift
    struct.pack_into('<I', d, 8, symptr)
    for y in c.symbol_list:
        off = symptr + y['index'] * 18
        sn = y['section']
        if sn in newnum:
            struct.pack_into('<h', d, off + 12, newnum[sn])
        if sn > 0 and secsym.get(sn) == y['index'] and sn in assoc and assoc[sn] in newnum:
            struct.pack_into('<H', d, off + 18 + 12, newnum[assoc[sn]])
    open(path, 'wb').write(bytes(d))
    return moved


if __name__ == '__main__':
    src, dst = sys.argv[1:3]
    tag = re.sub(r'\W', '_', os.path.splitext(os.path.basename(src))[0])[:40]
    for name, names in convert(src, dst, tag):
        print(name, ' '.join(names))


def set_align(path, aligns):
    """Sets the alignment of the sections holding the symbols ALIGNS names (name -> bytes, a
    power of two) in the object PATH (PLAN M7, config/m7align.txt: a stand-in member's function
    the image starts on a boundary its object's section does not ask for). Returns the count."""
    sys.path.insert(0, os.path.join(os.path.dirname(os.path.abspath(__file__)), '..'))
    from coff import Coff
    try:
        c = Coff(path)
    except ValueError:
        return 0        # (an import library member)
    d = bytearray(c.data)
    optsize = struct.unpack_from('<H', d, 16)[0]
    n = 0
    for y in c.symbol_list:
        if y['section'] > 0 and y['name'] in aligns:
            o = 20 + optsize + (y['section'] - 1) * 40
            chars = struct.unpack_from('<I', d, o + 36)[0]
            code = aligns[y['name']].bit_length()
            struct.pack_into('<I', d, o + 36, (chars & ~0x00F00000) | (code << 20))
            n += 1
    if n:
        open(path, 'wb').write(bytes(d))
    return n


def zap_empty_code(path):
    """Gives the empty plain code sections of the object PATH byte alignment (PLAN M7,
    M7ZAPTEXT): every compiled object has an empty 16-aligned .text (and ml 14 an empty
    .text$mn); link.exe lays unordered plain sections after the /ORDER'ed ones, and the
    padding up to an empty one is never written, so it stays zero where the original link,
    meeting them in object order, padded the end of .text with int3 (0x2FF17C, after
    __itoa). Returns the count."""
    sys.path.insert(0, os.path.join(os.path.dirname(os.path.abspath(__file__)), '..'))
    from coff import Coff
    try:
        c = Coff(path)
    except ValueError:
        return 0
    d = bytearray(c.data)
    optsize = struct.unpack_from('<H', d, 16)[0]
    n = 0
    for i, s in enumerate(c.sections):
        if s['name'] in ('.text', '.text$mn') and not s['size'] and s['chars'] & 0x20 \
                and not s['chars'] & 0x1000:
            o = 20 + optsize + i * 40
            chars = struct.unpack_from('<I', d, o + 36)[0]
            struct.pack_into('<I', d, o + 36, (chars & ~0x00F00000) | 0x00100000)
            n += 1
    if n:
        open(path, 'wb').write(bytes(d))
    return n


def set_section_names(path, names):
    """Renames the sections holding the symbols NAMES maps (name -> new section name, eight
    characters at most) in the object PATH (PLAN M7, config/m7tls.txt: the thread-local
    variables in the image's .tls order, which link.exe otherwise takes in object order).
    Returns the count."""
    sys.path.insert(0, os.path.join(os.path.dirname(os.path.abspath(__file__)), '..'))
    from coff import Coff
    try:
        c = Coff(path)
    except ValueError:
        return 0
    d = bytearray(c.data)
    optsize = struct.unpack_from('<H', d, 16)[0]
    n = 0
    for y in c.symbol_list:
        if y['section'] > 0 and y['name'] in names:
            o = 20 + optsize + (y['section'] - 1) * 40
            d[o:o + 8] = names[y['name']].encode('latin-1').ljust(8, b'\0')
            n += 1
    if n:
        open(path, 'wb').write(bytes(d))
    return n


def weak_retarget(path, targets):
    """Points each weak external (storage class 105) of the object PATH whose name TARGETS maps
    to a target at a new undefined external of that target's name, as its default: the name
    no object defines resolves where the image folds it (PLAN M7, M7FORCEFOLD), not to the
    compiler's default (a vector deleting destructor's scalar one). Returns the count."""
    d = bytearray(open(path, 'rb').read())
    machine, nsec, _, symptr, nsyms, optsize, _ = struct.unpack_from('<HHIIIHH', d, 0)
    if machine != 0x14C:
        return 0
    strtab = bytearray(d[symptr + nsyms * 18:])
    new = []
    have = {}
    i = 0
    while i < nsyms:
        off = symptr + i * 18
        raw = bytes(d[off:off + 8])
        v, sec, t, c, na = struct.unpack_from('<IhHBB', d, off + 8)
        if raw[:4] == b'\0\0\0\0':
            so = struct.unpack_from('<I', raw, 4)[0]
            nm = bytes(strtab[so:strtab.index(b'\0', so)]).decode('latin-1')
        else:
            nm = raw.rstrip(b'\0').decode('latin-1')
        if c == 105 and na and nm in targets:
            tg = targets[nm]
            if tg not in have:
                enc = tg.encode('latin-1')
                if len(enc) <= 8:
                    n8 = enc.ljust(8, b'\0')
                else:
                    n8 = struct.pack('<II', 0, len(strtab))
                    strtab.extend(enc + b'\0')
                have[tg] = nsyms + len(new)
                new.append(n8 + struct.pack('<IhHBB', 0, 0, 0x20, 2, 0))
            struct.pack_into('<I', d, off + 18, have[tg])
        i += 1 + na
    if not new:
        return 0
    struct.pack_into('<I', d, 12, nsyms + len(new))
    struct.pack_into('<I', strtab, 0, len(strtab))
    d = d[:symptr + nsyms * 18] + b''.join(new) + strtab
    open(path, 'wb').write(bytes(d))
    return len(new)


def weak_names(path):
    """The weak external names (storage class 105) the object PATH refers to."""
    d = open(path, 'rb').read()
    machine, nsec, _, symptr, nsyms, optsize, _ = struct.unpack_from('<HHIIIHH', d, 0)
    if machine != 0x14C:
        return set()
    strtab = d[symptr + nsyms * 18:]
    out = set()
    i = 0
    while i < nsyms:
        off = symptr + i * 18
        raw = d[off:off + 8]
        v, sec, t, c, na = struct.unpack_from('<IhHBB', d, off + 8)
        if c == 105:
            if raw[:4] == b'\0\0\0\0':
                so = struct.unpack_from('<I', raw, 4)[0]
                out.add(strtab[so:strtab.index(b'\0', so)].decode('latin-1'))
            else:
                out.add(raw.rstrip(b'\0').decode('latin-1'))
        i += 1 + na
    return out


def drop_defs(path, names):
    """Empties, in the object PATH, the sections defining NAMES and makes those symbols
    file-local under names of their own (PLAN M7, config/m7drop.txt: a stand-in piece holding
    bytes imagebld writes, the TLS directory, whose library member the link must use). Returns
    the count. Only a definition in a section without relocations goes."""
    d = bytearray(open(path, 'rb').read())
    machine, nsec, _, symptr, nsyms, optsize, _ = struct.unpack_from('<HHIIIHH', d, 0)
    if machine != 0x14C:
        return 0
    strtab = d[symptr + nsyms * 18:]
    n = 0
    i = 0
    while i < nsyms:
        off = symptr + i * 18
        raw = bytes(d[off:off + 8])
        v, sec, t, c, na = struct.unpack_from('<IhHBB', d, off + 8)
        if raw[:4] == b'\0\0\0\0':
            so = struct.unpack_from('<I', raw, 4)[0]
            nm = bytes(strtab[so:strtab.index(b'\0', so)]).decode('latin-1')
        else:
            nm = raw.rstrip(b'\0').decode('latin-1')
        # (only a copy without relocations: the stand-in's image bytes, not the member's;
        # a name given as *NAME goes whatever its section holds, a static too: a library
        # member's datum the image keeps as a stand-in piece, xonlines' s_StringURLs)
        if (nm in names and sec > 0 and c == 2 and
                not struct.unpack_from('<H', d, 20 + optsize + (sec - 1) * 40 + 32)[0])                 or ('*' + nm in names and sec > 0 and c in (2, 3)):
            d[off:off + 8] = ('$drp%d' % n).encode('latin-1').ljust(8, b'\0')
            d[off + 16] = 3
            o = 20 + optsize + (sec - 1) * 40
            struct.pack_into('<I', d, o + 16, 0)
            struct.pack_into('<H', d, o + 32, 0)
            n += 1
        # (-NAME: the definition becomes a reference, its section left as it is; the name
        # resolves through config/m7alt.txt to a label another object defines, a library
        # member's variable the image keeps partly in a stand-in piece: XGRAPHICS'
        # Instruction::collections, its first dword the stand-in's and its rest XGRPH's tail)
        elif '-' + nm in names and sec > 0 and c == 2:
            struct.pack_into('<I', d, off + 8, 0)
            struct.pack_into('<h', d, off + 12, 0)
            n += 1
        # (*NAME for a common variable: an absolute symbol instead, taking no room; the PCH
        # objects' ___@@_PchSym_ commons, which the image's .bss does not hold)
        elif '*' + nm in names and sec == 0 and c == 2 and v > 0:
            struct.pack_into('<I', d, off + 8, 0)
            struct.pack_into('<h', d, off + 12, -1)
            n += 1
        i += 1 + na
    if n:
        open(path, 'wb').write(bytes(d))
    return n


def xdata_plain(path):
    """Makes the object PATH's associative .xdata$x COMDATs plain sections (PLAN M7,
    M7XDATAPLAIN): the image keeps an EH table of a function link.exe folds into an identical
    one (unit_1FC320's _Tree instances), so the table must not go with its function. Returns
    the count."""
    d = bytearray(open(path, 'rb').read())
    machine, nsec, _, symptr, nsyms, optsize, _ = struct.unpack_from('<HHIIIHH', d, 0)
    if machine != 0x14C:
        return 0
    strtab = d[symptr + nsyms * 18:]
    n = 0
    i = 0
    while i < nsyms:
        off = symptr + i * 18
        raw = bytes(d[off:off + 8])
        v, sec, t, c, na = struct.unpack_from('<IhHBB', d, off + 8)
        if c == 3 and na and sec > 0:
            o = 20 + optsize + (sec - 1) * 40
            sraw = bytes(d[o:o + 8])
            if sraw[:1] == b'/':
                so = int(sraw[1:].rstrip(b'\0'))
                sname = bytes(strtab[so:strtab.index(b'\0', so)]).decode('latin-1')
            else:
                sname = sraw.rstrip(b'\0').decode('latin-1')
            chars = struct.unpack_from('<I', d, o + 36)[0]
            if sname.startswith('.xdata$x') and chars & 0x1000 and d[off + 18 + 14] == 5:
                struct.pack_into('<I', d, o + 36, chars & ~0x1000)
                n += 1
        i += 1 + na
    if n:
        open(path, 'wb').write(bytes(d))
    return n


def xbld_fix(path, table):
    """The object PATH's library version records (.XBLD$V/.XBLD$A sections, which imagebld
    turns into the XBE header's library table) as the image's (PLAN M7, M7XBLD): TABLE maps
    a library name to (rank, its 16-byte record from the image). A record of a library the
    image lists is renamed .XBLD$V<letter by rank> (the image's order: the link sorts by name) with
    the image's bytes (a member of another version, xonlines' 5849.17, records that);
    one of a library the image does not list (xnets) is emptied. Returns the count."""
    d = bytearray(open(path, 'rb').read())
    machine, nsec, _, symptr, nsyms, optsize, _ = struct.unpack_from('<HHIIIHH', d, 0)
    if machine != 0x14C:
        return 0
    strtab_off = symptr + nsyms * 18
    n = 0
    for i in range(nsec):
        o = 20 + optsize + i * 40
        raw = bytes(d[o:o + 8])
        if raw[:1] == b'/':
            so = int(raw[1:].rstrip(b'\0'))
            nm = bytes(d[strtab_off + so:d.index(b'\0', strtab_off + so)]).decode('latin-1')
        else:
            nm = raw.rstrip(b'\0').decode('latin-1')
        if nm not in ('.XBLD$V', '.XBLD$A'):
            continue
        size, ptr = struct.unpack_from('<II', d, o + 16)
        if size < 16 or not ptr:
            continue
        lib = bytes(d[ptr:ptr + 8]).rstrip(b'\0').decode('latin-1')
        if lib in table:
            rank, rec = table[lib]
            d[ptr:ptr + 16] = rec
            # (.XBLD$V and a letter by rank: eight characters, a short name; the ranks before
            # xboxkrnl's .XBLD$A and a letter, since its import library's record, which no
            # copy renames, keeps .XBLD$V)
            k_ = table.get('XBOXKRNL', (99,))[0]
            d[o:o + 8] = (('.XBLD$A' if rank < k_ else '.XBLD$V') + chr(ord('A') + rank)).encode('latin-1')
        else:
            struct.pack_into('<I', d, o + 16, 0)
        n += 1
    if n:
        open(path, 'wb').write(bytes(d))
    return n


def static_comdat(path, names):
    """Makes, in the object PATH, each COMDAT section whose symbol NAMES lists a plain section
    and that symbol file-local (PLAN M7, config/m7static.txt): a literal the image keeps apart
    from the copy every other object shares (RenderWare's "" at 0x3EE8B8 beside unit_067B10's
    at 0x3D292F). Returns the count."""
    d = bytearray(open(path, 'rb').read())
    machine, nsec, _, symptr, nsyms, optsize, _ = struct.unpack_from('<HHIIIHH', d, 0)
    if machine != 0x14C:
        return 0
    strtab = d[symptr + nsyms * 18:]
    n = 0
    i = 0
    while i < nsyms:
        off = symptr + i * 18
        raw = bytes(d[off:off + 8])
        v, sec, t, c, na = struct.unpack_from('<IhHBB', d, off + 8)
        if raw[:4] == b'\0\0\0\0':
            so = struct.unpack_from('<I', raw, 4)[0]
            nm = bytes(strtab[so:strtab.index(b'\0', so)]).decode('latin-1')
        else:
            nm = raw.rstrip(b'\0').decode('latin-1')
        if nm in names and sec > 0 and c == 2:
            o = 20 + optsize + (sec - 1) * 40
            ch = struct.unpack_from('<I', d, o + 36)[0] & ~0x1000
            # (NAMES a dict: NAME -> alignment the image gives the copy, fsyst's 4-aligned "")
            al = names.get(nm) if isinstance(names, dict) else None
            if al:
                ch = (ch & ~0x00F00000) | (al.bit_length() << 20)
            struct.pack_into('<I', d, o + 36, ch)
            d[off + 16] = 3
            n += 1
        i += 1 + na
    if n:
        open(path, 'wb').write(bytes(d))
    return n


def keep_tables(path, handlers):
    """Makes, in the object PATH, the funcinfo .xdata$x of each handler in HANDLERS a plain
    section (PLAN M7): a function the image folds into another's body (config/aliases.txt,
    the M7 link's forced fold) whose EH tables the image still keeps (their rows). Returns
    the count."""
    sys.path.insert(0, os.path.join(os.path.dirname(os.path.abspath(__file__)), '..'))
    from coff import Coff
    try:
        c = Coff(path)
    except ValueError:
        return 0        # (an import library's member)
    d = bytearray(c.data)
    optsize = struct.unpack_from('<H', d, 16)[0]
    n = 0
    for y in c.symbol_list:
        if y['name'] in handlers and y['section'] > 0:
            for va, si, t in c.sections[y['section'] - 1]['relocs']:
                ts = c.symbols[si]['section']
                if ts > 0 and c.sections[ts - 1]['name'] == '.xdata$x':
                    o = 20 + optsize + (ts - 1) * 40
                    ch = struct.unpack_from('<I', d, o + 36)[0]
                    if ch & 0x1000:
                        struct.pack_into('<I', d, o + 36, ch & ~0x1000)
                        n += 1
    if n:
        open(path, 'wb').write(bytes(d))
    return n
