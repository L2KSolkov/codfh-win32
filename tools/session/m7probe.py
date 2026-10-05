"""m7probe.py: link every compiled object (in first-address order) and the XDK libraries with the real
link.exe (/FORCE), and count the errors (PLAN M7 groundwork): build/m7/link.log, game.map and
unresolved.txt (one decorated name per line)."""
import collections
import os
import re
import bisect
import subprocess
import sys
sys.path.insert(0, os.path.join(os.path.dirname(os.path.abspath(__file__)), '..'))
import anonfix  # noqa: E402  (anonymous-namespace hashes of other checkouts)

ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
os.chdir(ROOT)
XDK = r'C:\XDK'
BIN = os.path.join(XDK, 'xbox', 'bin')
VC = os.path.join(BIN, 'vc71')
first = {}
# (names the link must keep that no object refers to: M7-only fill pieces)
keep_extra = []
owners = collections.defaultdict(set)
rows = []
for l in anonfix.lines('config/compiled.txt'):
    q = l.split()
    if len(q) >= 3 and q[0].startswith('0x') and q[1].startswith('build/src/') and not q[1].startswith('build/src/xdk/'):
        rows.append((int(q[0], 16), q[1], q[2]))
        owners[int(q[0], 16)].add(q[1])
for a, o, n in rows:
    # an address several objects' rows give is a fold's survivor (/OPT:ICF), not where the
    # object is, and a template's instance is the first defining object's: they order nothing
    if len(owners[a]) == 1 and '?$' not in n and not n.startswith('??$'):
        first[o] = min(first.get(o, 1 << 32), a if a < 0x3C0000 else (1 << 31) + a)
for a, o, n in rows:
    first.setdefault(o, 1 << 32)
# a lone function far below the rest of its object's code (one the original's /ORDER file put
# elsewhere: a factory compiled in a later object) does not place the object
codes = collections.defaultdict(list)
for a, o, n in rows:
    if a < 0x3C0000 and len(owners[a]) == 1 and '?$' not in n and not n.startswith('??$') and not n.startswith('__ehhandler$') and not n.startswith('_$E'):
        codes[o].append(a)
for o, xs in codes.items():
    xs.sort()
    if len(xs) >= 4 and xs[1] - xs[0] > 0x4000 and first[o] == xs[0]:
        first[o] = xs[1]
# (not the kernel thunk stand-in: the link makes the import address table itself, from the
# __imp__ names the code calls through)
objs = [o for o, a in sorted(first.items(), key=lambda x: x[1]) if os.path.exists(o)
        and not o.endswith('standin_kthunk.obj')]
print(len(objs), 'objects')
out = os.path.join('build', 'm7')
# (the previous link's map the probe reads: ICF groups, EH fold labels. build/m7/seed.map, a
# good link's map kept with M7SEEDMAP=1 or by hand, when it exists: the probe otherwise feeds
# on its own last map, and one bad link can keep the next ones bad)
_PREV_MAP = os.path.join(out, 'seed.map') if os.path.exists(os.path.join(out, 'seed.map'))     else os.path.join(out, 'game.map')
os.makedirs(out, exist_ok=True)
# objects config/objaliases.txt gives extra external symbols are linked as patched copies
import objalias  # noqa: E402
for i, o in enumerate(objs):
    pairs = objalias.aliases_for(o)
    if pairs:
        objs[i] = os.path.join(out, 'obj', o)
        if not objalias.patch(o, objs[i], pairs):
            raise SystemExit(1)
if os.environ.get('M7ORDER'):
    # /ORDER cannot name a static function: each of our objects' static functions that has a
    # code row and a name no other object of ours uses becomes external in the linked copy
    # (storage class 3 -> 2; the code is unchanged)
    import struct  # noqa: E402
    row_names = collections.defaultdict(set)
    for l in anonfix.lines('config/compiled.txt'):
        q = l.split()
        if len(q) >= 3 and q[0].startswith("0x") and int(q[0], 16) < 0x3CD300:
            row_names[q[1]].add(q[2])

    def symtab(d):
        _, _, _, sp, ns, _, _ = struct.unpack_from('<HHIIIHH', d, 0)
        st = sp + ns * 18
        i = 0
        while i < ns:
            off = sp + i * 18
            raw = bytes(d[off:off + 8])
            v, sec, t, c, na = struct.unpack_from('<IhHBB', d, off + 8)
            if raw[:4] == b'\0\0\0\0':
                so = struct.unpack_from('<I', raw, 4)[0]
                nm = bytes(d[st + so:d.index(b'\0', st + so)]).decode('latin-1')
            else:
                nm = raw.rstrip(b'\0').decode('latin-1')
            yield off, nm, sec, t, c
            i += 1 + na
    count = collections.Counter()
    data = {}
    for o in objs:
        data[o] = bytearray(open(o, 'rb').read())
        for off, nm, sec, t, c in symtab(data[o]):
            if sec > 0 and c in (2, 3):
                count[nm] += 1
    for i, o in enumerate(objs):
        src = o if not o.startswith(os.path.join(out, 'obj')) else os.path.relpath(o, os.path.join(out, 'obj')).replace(os.sep, '/')
        rn = row_names.get(src, ())
        d = data[o]
        flipped = 0
        for off, nm, sec, t, c in list(symtab(d)):
            # (not an EH handler thunk: the order file leaves those out, so it stays static, as
            # compiled)
            if sec > 0 and c == 3 and t == 0x20 and count[nm] == 1 and not nm.startswith('__ehhandler$') and \
                    (nm in rn or nm.lstrip('_') in rn or ('_' + nm) in rn):
                d[off + 16] = 2
                flipped += 1
        if flipped:
            dst = os.path.join(out, 'obj', src)
            os.makedirs(os.path.dirname(dst), exist_ok=True)
            open(dst, 'wb').write(bytes(d))
            objs[i] = dst
rsp = os.path.join(out, 'link.rsp')
# the installed libraries M3 placed members from (config/xdk_members.txt)
libs = ['xapilib.lib', 'xboxkrnl.lib', 'd3d8.lib', 'd3dx8.lib', 'dsound.lib', 'xgraphics.lib', 'xnets.lib',
        'xonlines.lib', 'uix.lib', 'xvoice.lib', 'libcmt.lib', 'libcpmt.lib']
# (M7LIBORDER, default on: the image header's library table order, the order the original link
# met the libraries' version stamps; xnets.lib, whose stamp the table lacks, last)
if os.environ.get('M7LIBORDER', '1') != '0':
    libs = ['xapilib.lib', 'd3d8.lib', 'd3dx8.lib', 'dsound.lib', 'xboxkrnl.lib', 'xonlines.lib', 'uix.lib',
            'xvoice.lib', 'libcpmt.lib', 'libcmt.lib', 'xgraphics.lib', 'xnets.lib']
# repacked: an installed library whose members M3 placed from the XDK 5849 copies
# (xdklib/, config/xdk_members.txt) gets those members in place of its own, and a member the
# image holds in another version gets its stand-in (tools/session/xdkrepack.py,
# build/m7/standin/members.txt; STANDINS=0 leaves them out)
import shutil  # noqa: E402
repack = collections.defaultdict(dict)        # lib -> {member name: source}
member_of = {}
for l in open('config/xdk_members.txt', encoding='utf-8'):
    q = l.split(None, 2)
    if len(q) == 3 and q[0].startswith('build/'):
        member_of[q[0]] = (os.path.basename(q[1]), q[2].strip())
        if q[1].startswith('xdklib/'):
            repack[os.path.basename(q[1])][q[2].strip()] = ('xdklib', q[1])
sfile = os.path.join(out, 'standin', 'members.txt')
standin_rest = None
standin_imports = None
if os.environ.get('STANDINS', '1') != '0' and os.path.exists(sfile):
    for l in open(sfile):
        lib, base, path = l.split()
        if lib == 'IMPORTS':
            standin_imports = path
            continue
        if lib == 'REST':
            # the stand-in pieces no member holds: linked as an object after ours
            standin_rest = path
            continue
        if base in member_of:
            lname, mname = member_of[base]
            repack[lname][mname] = ('file', path)
BASELIBS = [x for x in os.environ.get('M7BASELIBS', 'd3d8.lib,dsound.lib').split(',') if x]


def _base_lib(lib):
    if lib in BASELIBS and os.path.exists(os.path.join('xdklib', lib)):
        return os.path.abspath(os.path.join('xdklib', lib))
    return os.path.join(XDK, 'xbox', 'lib', lib)


libdir = os.path.join(out, 'lib')
for lib, members in sorted(repack.items()):
    work = os.path.join(libdir, os.path.splitext(lib)[0])
    # a relative member name is replaced in place (the file at that path under work/); one
    # with a drive (xvoice's h:\nightly\...) is removed and its copy added under its base name
    adds, removes = [], []
    for m, (kind, src) in sorted(members.items()):
        absolute = bool(os.path.splitdrive(m)[0])
        rel = os.path.basename(m.replace('\\', '/')) if absolute else m
        dst = os.path.join(work, rel)
        os.makedirs(os.path.dirname(dst), exist_ok=True)
        if kind == 'xdklib':
            subprocess.run([os.path.join(VC, 'lib.exe'), '/nologo', os.path.abspath(src),
                            '/EXTRACT:' + m, '/OUT:' + dst], check=True, capture_output=True)
        else:
            shutil.copyfile(src, dst)
        adds.append(rel)
        if absolute:
            removes.append('/REMOVE:' + m)
    target = os.path.abspath(os.path.join(libdir, lib))
    subprocess.run([os.path.join(VC, 'lib.exe'), '/nologo', '/OUT:' + target, _base_lib(lib)]
                   + removes + adds, cwd=work, check=True, capture_output=True)
    libs[libs.index(lib)] = '"%s"' % target
# (a library the image holds in the 5849 version, its header's library table: d3d8 and dsound
# 1.0.5849.1, not the installed QFE's; M7BASELIBS names them)
for lib in BASELIBS:
    if lib in libs and lib not in repack:
        libs[libs.index(lib)] = '"%s"' % _base_lib(lib)
if os.environ.get('LIBS', '1') != '0':
    # (LIBS=0 links them as objects.) The image's .text holds the game's objects first and then library members in
    # the order link pulled them (xapilib, xgraphics, RenderWare Audio, the RW toolkits,
    # Bink, ... interleaved), so RenderWare, RenderWare Audio and Bink are libraries here:
    # an object the image has before the first XDK member is linked as an object, the rest
    # go into libraries by directory (RW: rwcore for src/driver/os, rpworld, rp<plugin>,
    # rt<toolkit>; rwa, rwaxbox; binkxbox), and every library comes in the order of its first
    # member in the image.
    def libname(o):
        p = o.replace('\\', '/').split('/')
        if p[2] == 'rw':
            if p[3] in ('src', 'driver', 'os'):
                return 'rwcore'
            if p[3] == 'world':
                return 'rpworld'
            return ('rp' if p[3] == 'plugin' else 'rt') + p[4]
        if p[2] == 'rwa':
            return 'rwaxbox' if p[3] == 'xbox' else 'rwa'
        if p[2] == 'bink':
            return 'binkxbox'
        return None
    xdk_first = 0x22CB5B          # xapilib's first member in the image
    ours = collections.defaultdict(list)
    explicit = []
    for o, src in zip(objs, [o for o, a in sorted(first.items(), key=lambda x: x[1]) if os.path.exists(o)]):
        n = libname(src)
        if n is None or first[src] < xdk_first:
            explicit.append(o)
        else:
            ours[n].append(o)
    lib_first = {}
    for n, members in ours.items():
        srcs = set(m if not m.startswith(os.path.join(out, 'obj')) else os.path.relpath(m, os.path.join(out, 'obj')).replace(os.sep, '/') for m in members)
        lib_first['"%s"' % os.path.abspath(os.path.join(libdir, n + '.lib'))] = min(first[s] for s in srcs)
        target = os.path.join(libdir, n + '.lib')
        if os.path.exists(target):
            os.replace(target, target + '.old')
        lrsp = os.path.join(libdir, n + '.rsp')
        open(lrsp, 'w').write('\n'.join('"%s"' % os.path.abspath(m) for m in members) + '\n')
        subprocess.run([os.path.join(VC, 'lib.exe'), '/nologo', '/OUT:' + target, '@' + lrsp], check=True, capture_output=True)
    for l in anonfix.lines('config/compiled.txt'):
        q = l.split()
        if len(q) >= 3 and q[0].startswith('0x') and q[1].startswith('build/xdk/'):
            stem = q[1].split('/')[2].replace('xdklib_', '')
            key = next((x for x in libs if os.path.splitext(os.path.basename(x.strip('"')))[0] == stem), None)
            if key:
                a = int(q[0], 16)
                lib_first[key] = min(lib_first.get(key, 1 << 32), a if a < 0x3C0000 else (1 << 31) + a)
    for x in libs:
        lib_first.setdefault(x, 1 << 33)
    libs = [x for x, a in sorted(lib_first.items(), key=lambda kv: kv[1])]
    objs = explicit
    print(len(objs), 'objects,', len(ours), 'libraries of ours:', ' '.join(libs))
if standin_rest:
    objs = objs + [standin_rest]
if standin_imports:
    objs = objs + [standin_imports]
if os.environ.get('M7FLAT'):
    # M7FLAT=1: every library member the image holds is linked as an object, all objects in
    # the order of their data in the image (the code's order is the /ORDER file's), so data
    # need no pull order; the libraries stay for whatever else is pulled
    rows_of = collections.defaultdict(list)
    # (a shared literal's row is where the first object defining it put it: it does not place
    # an object whose own rows say otherwise)
    own_rows_of = collections.defaultdict(list)
    for l in anonfix.lines('config/compiled.txt'):
        q = l.split()
        if len(q) >= 3 and q[0].startswith('0x'):
            rows_of[q[1]].append(int(q[0], 16))
            # (shared COMDATs, the first definer's: literals and, M7SHAREDRTTI on by default,
            # the exception type data __CT/__CTA/__TI and RTTI descriptors ??_R)
            if not (q[2].startswith('__real@') or q[2].startswith('??_C@') or
                    (os.environ.get('M7SHAREDRTTI', '1') != '0' and q[2].startswith(('__CT', '__TI', '??_R')))):
                own_rows_of[q[1]].append(int(q[0], 16))
    standin_for = {}
    if os.path.exists(sfile):
        for l in open(sfile):
            lib, base, path = l.split()
            if lib not in ('REST', 'IMPORTS'):
                standin_for.setdefault(path, []).append(base)
    replaced = set(b for bs in standin_for.values() for b in bs)

    def src_of(o):
        p = o.replace(os.sep, '/')
        pre = os.path.join(out, 'obj').replace(os.sep, '/') + '/'
        return p[len(pre):] if p.startswith(pre) else p

    sys.path.insert(0, os.path.join(os.path.dirname(os.path.abspath(__file__)), '..'))
    from xbe import Xbe  # noqa: E402
    sec_range = dict((s['name'], (s['va'], s['va'] + s['vsize']))
                     for s in Xbe(os.path.join('orig', 'Game_XboxMultiplayer.xbe')).sections)

    # a stand-in member also holds the image pieces it was given (build/src/xdk stand-in rows,
    # by their names in its symbol table)
    piece_addr = {}
    for l in anonfix.lines('config/compiled.txt'):
        q = l.split()
        if len(q) >= 3 and q[0].startswith('0x') and q[1].startswith('build/src/xdk/standin_'):
            piece_addr[q[2]] = int(q[0], 16)
    piece_rows = {}

    def pieces_of(path):
        if path not in piece_rows:
            names = set()
            try:
                from coff import Coff  # noqa: E402
                names = set(s['name'] for s in Coff(path).symbol_list if s['section'] > 0)
            except Exception:
                pass
            piece_rows[path] = [piece_addr[n] for n in names if n in piece_addr]
        return piece_rows[path]

    # where .xdata$x (EH and exception type tables, sorted after .rdata by name) starts: the
    # first __CT/__CTA/__TI row
    xdata_lo = None
    if os.environ.get('M7XDATA', '1') != '0':
        _xl = [int(q[0], 16) for q in (l.split() for l in anonfix.lines('config/compiled.txt'))
               if len(q) >= 3 and q[0].startswith('0x') and q[2].startswith(('__CT', '__TI'))
               and sec_range['.rdata'][0] <= int(q[0], 16) < sec_range['.rdata'][1]]
        xdata_lo = min(_xl) if _xl else None

    def sec_min(o, name):
        srcs = standin_for.get(src_of(o), [src_of(o)])
        lo, hi = sec_range[name]
        a = [x for s in srcs for x in own_rows_of.get(s, ()) if lo <= x < hi]
        if name == '.data':
            # (the CRT tables, .CRT$xxx at 0x426D40-0x427400, are sorted by section name, not
            # by object: they order nothing)
            a = [x for x in a if not 0x426D40 <= x < 0x427400]
        if name == '.rdata' and xdata_lo:
            # (nor the EH tables, .xdata$x after .rdata, M7XDATA on by default)
            a = [x for x in a if x < xdata_lo]
        if not a:
            # only shared literals: where most of them are (its own run), not its lowest one
            lits = sorted(x for s in srcs for x in rows_of.get(s, ()) if lo <= x < hi
                          and not (name == '.data' and 0x426D40 <= x < 0x427400))
            runs, run = [], []
            for x in lits:
                if run and x - run[-1] > 0x80:
                    runs.append(run)
                    run = []
                run.append(x)
            if run:
                runs.append(run)
            a = max(runs, key=len)[:1] if runs else []
        if (src_of(o) in standin_for or o == standin_rest) and (not a or os.environ.get('M7PIECEMIN')):
            # (not the CRT tables nor the import thunk table at .rdata's start; only for an
            # object with no row of its own there: a stand-in piece several members share,
            # UIX's CScreen vtable, orders none of them)
            a += [x for x in pieces_of(o) if lo <= x < hi and not 0x426D40 <= x < 0x427400
                  and not 0x3CD300 <= x < 0x3CD5A0]
        return min(a) if a else None

    def data_order(objs):
        # .data's order, the objects without .data among them by .rdata's (each before the
        # first object with .data whose .rdata comes after its own), then those with neither
        # (an object whose data is all in BINKDATA, which follows .data, by its BINKDATA: Bink's
        # library members, whose order there is their pull order)
        # (an object with BINKDATA and .rdata but no .data is ordered by its .rdata; one with
        # only BINKDATA goes right after the object whose BINKDATA precedes its own)
        bonly = [o for o in objs if sec_min(o, '.data') is None and sec_min(o, '.rdata') is None
                 and sec_min(o, 'BINKDATA') is not None]

        def dkey(o):
            return sec_min(o, '.data')
        withd = sorted((o for o in objs if dkey(o) is not None), key=dkey)
        if os.environ.get('M7DEBUG'):
            for o in objs:
                if os.environ['M7DEBUG'] in o:
                    print('DEBUG', o, [hex(x) if x else None for x in (sec_min(o, '.data'), sec_min(o, '.rdata'), sec_min(o, 'BINKDATA'))])
        rest = [o for o in objs if dkey(o) is None and o not in set(bonly)]
        withr = sorted((o for o in rest if sec_min(o, '.rdata') is not None), key=lambda o: sec_min(o, '.rdata'))
        neither = [o for o in rest if sec_min(o, '.rdata') is None]
        if os.environ.get('M7NEITHERCODE', '1') != '0':
            # (M7NEITHERCODE, default on: by their first code row, their pull order: their data
            # in a library's merged section, DSOUND's and XGRPH's, follows it)
            def _cm(o):
                a_ = [x for s in standin_for.get(src_of(o), [src_of(o)]) for x in own_rows_of.get(s, ())
                      if 0x12000 <= x < 0x3CD300]
                return min(a_) if a_ else 1 << 40
            neither = sorted(neither, key=_cm)
        if os.environ.get('M7RDATA_AFTER', '0') != '0':
            # each object without .data right after the object with .data whose .rdata row comes
            # last before its own (the block its .rdata follows in the image)
            import bisect
            lo, hi = sec_range['.rdata']
            marks = sorted((x, k) for k, o in enumerate(withd)
                           for s in standin_for.get(src_of(o), [src_of(o)])
                           for x in rows_of.get(s, ()) if lo <= x < hi)
            keys = [m[0] for m in marks]
            after = collections.defaultdict(list)
            for o in withr:
                j = bisect.bisect_left(keys, sec_min(o, '.rdata')) - 1
                after[marks[j][1] if j >= 0 else -1].append(o)
            out = list(after[-1])
            for k, o in enumerate(withd):
                out.append(o)
                out += after[k]
            out = out + neither
        else:
            out = []
            i = 0
            for o in withd:
                r = sec_min(o, '.rdata')
                if r is not None:
                    while i < len(withr) and sec_min(withr[i], '.rdata') < r:
                        out.append(withr[i])
                        i += 1
                out.append(o)
            out = out + withr[i:] + neither
        # (an object with neither .data nor .rdata but XON_RD rows, xonline's members, goes
        # right before the first object whose XON_RD comes after its own: XON_RD follows the
        # object order)
        if 'XON_RD' in sec_range and os.environ.get('M7XONRD', '1') != '0':
            xonly = sorted((o for o in out if sec_min(o, '.data') is None and sec_min(o, '.rdata') is None
                            and sec_min(o, 'XON_RD') is not None), key=lambda o: sec_min(o, 'XON_RD'))
            out = [o for o in out if o not in set(xonly)]
            for o in xonly:
                x = sec_min(o, 'XON_RD')
                nxt = [k for k, y in enumerate(out) if (sec_min(y, 'XON_RD') or -1) > x]
                out.insert(nxt[0] if nxt else len(out), o)
        for o in sorted(bonly, key=lambda o: sec_min(o, 'BINKDATA')):
            b = sec_min(o, 'BINKDATA')
            prev = [k for k, x in enumerate(out) if (sec_min(x, 'BINKDATA') or 1 << 40) < b]
            out.insert(prev[-1] + 1 if prev else len(out), o)
        # Bink's code-only members (the colour converters' named code sections) right after
        # yuv.obj, the first to make those sections, so no other library's section (XONLINE)
        # comes between them: the image has every BINK* section before XONLINE
        bcode = [o for o in neither if 'src/bink/' in src_of(o)]
        if bcode:
            out = [o for o in out if o not in set(bcode)]
            last = next((k for k, o in enumerate(out) if src_of(o).endswith('src/bink/yuv.obj')), len(out) - 1)
            out[last + 1:last + 1] = bcode
        # (M7BINKDATA, default on: Bink's objects without .data rows, whose MASM objects carry an
        # empty 16-aligned .data, right before rgb32mx2.obj: the image's Bink .data run, mmx's
        # word, then rgb32mx2's and rgb32m's 16-aligned tables, has no other 16-byte fill)
        if os.environ.get('M7BINKDATA', '1') != '0':
            bnod = [o for o in out if 'src/bink/' in src_of(o) and dkey(o) is None and sec_min(o, '.rdata') is None and sec_min(o, 'BINKDATA') is None]
            at_ = next((o for o in out if src_of(o).endswith('src/bink/rgb32mx2.obj')), None)
            if bnod and at_ is not None:
                out = [o for o in out if o not in set(bnod)]
                k_ = out.index(at_)
                out[k_:k_] = bnod
        # (M7MASMDATA, default on: a library member without data rows whose MASM object carries
        # an empty .data aligned to 16 or more, libcmt's memset, right after the object with
        # .data rows its code follows (right before the first one whose code comes after its
        # own): the image's 4 zero bytes before exsup's
        # __NLG_Destination are that alignment, memset coming between fpinit and exsup)
        if os.environ.get('M7MASMDATA', '1') != '0':
            from coff import Coff  # noqa: E402

            def _empty_aligned(o):
                try:
                    c_ = Coff(o)
                except Exception:
                    return False
                return any(s_['name'] == '.data' and s_['size'] == 0 and (s_['chars'] >> 20) & 0xF >= 5
                           for s_ in c_.sections)
            def _code_min(o):
                a_ = [x for s in standin_for.get(src_of(o), [src_of(o)]) for x in own_rows_of.get(s, ())
                      if 0x12000 <= x < 0x30F0F4]
                return min(a_) if a_ else None
            # (libcmt's only, M7MASMDATA=all every member's: xvoice's IPP objects' data does not
            # follow their code's order)
            _masm_dirs = ('build/xdk/',) if os.environ.get('M7MASMDATA') == 'all' else ('build/xdk/libcmt/',)
            masm = [o for o in out if src_of(o).startswith(_masm_dirs) and dkey(o) is None
                    and sec_min(o, '.rdata') is None and _code_min(o) is not None and _empty_aligned(o)]
            if masm:
                out = [o for o in out if o not in set(masm)]
                for o in sorted(masm, key=_code_min):
                    nxt = [k for k, x in enumerate(out) if dkey(x) is not None
                           and (_code_min(x) or -1) > _code_min(o)]
                    out.insert(nxt[0] if nxt else len(out), o)
        return out
    # the explicit objects keep their order; the members follow in their data's order
    flat = []
    if os.environ.get('LIBS', '1') != '0':
        for n, ms in ours.items():
            flat += ms
    # one object per member: its stand-in, else the first of its versions (installed, the
    # 5849 copy; xonlines' copies of xnets' members are the same member)
    def member_key(o):
        lib = o.split('/')[2].replace('xdklib_', '')
        if lib == 'xonlines' and os.path.exists(os.path.join('build', 'xdk', 'xnets', os.path.basename(o))):
            lib = 'xnets'
        return (lib, os.path.basename(o))
    chosen = {}
    for path, bases in standin_for.items():
        for b in bases:
            chosen[member_key(b)] = path
    for o in sorted(set(o for o in rows_of if o.startswith('build/xdk/'))):
        if os.path.exists(o):
            chosen.setdefault(member_key(o), o)
    flat += list(dict.fromkeys(chosen.values()))
    # objects whose code the image has among the library members (after xapilib's first) are
    # ordered with them
    early = [o for o in objs if first.get(src_of(o), 1 << 33) < int(os.environ.get("M7FLAT_EARLY", "0x22CB5B"), 16)]
    late = [o for o in objs if o not in set(early)]
    # game objects without code (data only, or code the original link dropped) go among the
    # early ones, right after the one whose .rdata row comes last before their own
    import bisect
    lo_r, hi_r = sec_range['.rdata']
    nocode = [o for o in late if src_of(o).startswith('build/src/recovered/') and first.get(src_of(o), 1 << 33) >= 1 << 31
              and sec_min(o, '.rdata') is not None]
    if nocode:
        marks = sorted((x, k) for k, o in enumerate(early) for x in rows_of.get(src_of(o), ()) if lo_r <= x < hi_r)
        keys = [m[0] for m in marks]
        after = collections.defaultdict(list)
        for o in sorted(nocode, key=lambda o: sec_min(o, '.rdata')):
            j = bisect.bisect_left(keys, sec_min(o, '.rdata')) - 1
            after[marks[j][1] if j >= 0 else -1].append(o)
        e2 = list(after[-1])
        for k, o in enumerate(early):
            e2.append(o)
            e2 += after[k]
        early = e2
        late = [o for o in late if o not in set(nocode)]
    def topo_order(order):
        # M7TOPO=1: every data section's row order as constraints (an object whose rows come
        # right before another's in .data, .rdata, BINKDATA... is linked before it), sorted
        # topologically with the heuristic order breaking ties and cycles
        import heapq
        pos = dict((o, k) for k, o in enumerate(order))
        src2o = {}
        for o in order:
            for s in standin_for.get(src_of(o), [src_of(o)]):
                src2o[s] = o
            for x in pieces_of(o) if (src_of(o) in standin_for or o == standin_rest) else ():
                pass
        succ = collections.defaultdict(set)
        pred = collections.defaultdict(set)
        for name in ('.data', '.rdata', 'BINKDATA', 'DOLBY', 'XON_RD', '.data1'):
            if name not in sec_range:
                continue
            lo, hi = sec_range[name]
            seq = []
            for s, xs in own_rows_of.items():
                o = src2o.get(s)
                if o is None:
                    continue
                for x in xs:
                    if lo <= x < hi and not (name == '.data' and 0x426D40 <= x < 0x427400):
                        seq.append((x, o))
            for o in order:
                if src_of(o) in standin_for:
                    for x in pieces_of(o):
                        if lo <= x < hi and not (name == '.data' and 0x426D40 <= x < 0x427400):
                            seq.append((x, o))
            seq.sort()
            prev = None
            for x, o in seq:
                if prev is not None and o != prev and o not in pred[prev] and prev not in succ[o]:
                    succ[prev].add(o)
                    pred[o].add(prev)
                prev = o
        indeg = dict((o, len(pred[o])) for o in order)
        heap = [(pos[o], o) for o in order if indeg[o] == 0]
        heapq.heapify(heap)
        done, out = set(), []
        while len(out) < len(order):
            if not heap:
                # a cycle: take the earliest remaining object
                o = min((x for x in order if x not in done), key=lambda x: pos[x])
            else:
                o = heapq.heappop(heap)[1]
                if o in done:
                    continue
            done.add(o)
            out.append(o)
            for n in succ[o]:
                if n in done:
                    continue
                indeg[n] -= 1
                if indeg[n] == 0:
                    heapq.heappush(heap, (pos[n], n))
        return out
    rest_order = data_order(list(dict.fromkeys(late + flat)))
    if os.environ.get('M7TOPO'):
        rest_order = topo_order(rest_order)
    objs = list(dict.fromkeys(early + rest_order))
    if os.environ.get('M7SECORDER', '1') != '0' and os.path.exists('build/src/xbe/secorder.obj'):
        # (M7SECORDER, default on: src/xbe/secorder.asm first, its empty sections making the
        # output sections in the image's order)
        objs = ['build/src/xbe/secorder.obj'] + [o for o in objs if not src_of(o).endswith('src/xbe/secorder.obj')]
        # (src/xbe/dataalign.asm right after it: .data's 16-byte alignment fill, dataalign.py)
        if os.path.exists('build/src/xbe/dataalign.obj'):
            objs = objs[:1] + ['build/src/xbe/dataalign.obj'] + [o for o in objs[1:]
                                                               if not src_of(o).endswith('src/xbe/dataalign.obj')]
        # (src/xbe/xppfill.asm: XPP's four unattributed zero bytes at 0x3C44B8)
        if os.path.exists('build/src/xbe/xppfill.obj'):
            objs = [o for o in objs if not src_of(o).endswith('src/xbe/xppfill.obj')] + ['build/src/xbe/xppfill.obj']
        # (src/xbe/binkdatafill.asm: the zero dword closing BINKDATA's virtual size)
        if os.path.exists('build/src/xbe/binkdatafill.obj'):
            objs = [o for o in objs if not src_of(o).endswith('src/xbe/binkdatafill.obj')] + ['build/src/xbe/binkdatafill.obj']
        # (src/xbe/rdatafill.asm: the zeros closing .rdata's virtual size)
        if os.path.exists('build/src/xbe/rdatafill.obj'):
            objs = [o for o in objs if not src_of(o).endswith('src/xbe/rdatafill.obj')] + ['build/src/xbe/rdatafill.obj']
        # (src/xbe/xgrphfill.asm: the eight bytes opening XGRPH's tail at 0x3AA2C0)
        if os.path.exists('build/src/xbe/xgrphfill.obj'):
            objs = [o for o in objs if not src_of(o).endswith('src/xbe/xgrphfill.obj')] + ['build/src/xbe/xgrphfill.obj']
        # (src/xbe/textfill.asm: the int3s closing .text, a plain section, which link lays
        # after the /ORDER'ed functions; /OPT:REF drops it unless included)
        if os.path.exists('build/src/xbe/textfill.obj'):
            objs = [o for o in objs if not src_of(o).endswith('src/xbe/textfill.obj')] + ['build/src/xbe/textfill.obj']
            keep_extra.append('_m7_textfill')
        # (src/xbe/datafill.asm: the dword of no known object at 0x436D04)
        if os.path.exists('build/src/xbe/datafill.obj'):
            objs = [o for o in objs if not src_of(o).endswith('src/xbe/datafill.obj')] + ['build/src/xbe/datafill.obj']
        # (src/xbe/iatpad.asm: the import address table's 0x1C-byte tail, before the debug
        # directory)
        if os.path.exists('build/src/xbe/iatpad.obj'):
            objs = [o for o in objs if not src_of(o).endswith('src/xbe/iatpad.obj')] + ['build/src/xbe/iatpad.obj']
    if os.environ.get('M7NOINSERTED'):
        # (M7NOINSERTED=1, the image build: the sections imagebld inserts from files, $$XTIMAGE,
        # $$XSIMAGE and .XTLID, are its inputs (tools/session/m7xbe.py), not linked)
        objs = [o for o in objs if not src_of(o).replace(os.sep, '/').endswith('src/xbe/inserted_files.obj')]
    if standin_imports:
        # (the import table's pieces first: the image opens .rdata with it)
        objs = [standin_imports] + [o for o in objs if o != standin_imports]
    print(len(objs), 'objects linked flat')
cdz_map = {}        # a name inside a section made a COMDAT -> the name the order file gives it
cdz_of = {}         # the same per object (a row's own object's copy first)
if os.environ.get('M7ORDER'):
    # every object and library member linked gets its plain code sections packaged (COMDAT)
    # in the copy the link reads, so /ORDER can place all of .text (tools/session/comdatize.py)
    import comdatize  # noqa: E402
    import struct  # noqa: E402
    cdir = os.path.join(out, 'cdz')

    # (M7NOFOLDXDK=rows: also the packaged functions whose rows have an address of their own,
    # which the image keeps apart)
    _addr_names = collections.defaultdict(set)
    _row_obj = {}
    _row_addr = {}
    _row_xdk = {}
    for l in anonfix.lines('config/compiled.txt'):
        q = l.split()
        if len(q) >= 3 and q[0].startswith('0x') and int(q[0], 16) < 0x3CD300:
            _addr_names[int(q[0], 16)].add(q[2])
            _row_obj[q[2]] = os.path.basename(q[1]).lower()
            _row_addr[q[2]] = int(q[0], 16)
            _row_xdk[q[2]] = q[1].startswith('build/xdk/')
    distinct_names = frozenset(next(iter(v)) for v in _addr_names.values() if len(v) == 1)
    # (M7FORCEFOLD, default on: a function config/aliases.txt folds into a row's body is folded here, not
    # by link.exe, whose choice of the copy it keeps depends on its whole input: each object's
    # copy is disowned (comdatize) and /ALTERNATENAME sends the name to the row's)
    _fold_pairs = {}
    _bf = os.path.join(out, 'badfolds.txt')
    _badfolds = set(l.strip() for l in open(_bf)) if os.path.exists(_bf) else set()
    if os.environ.get('M7FORCEFOLD', '1') != '0':
        _row_at = {}
        for n_, a_ in _row_addr.items():
            _row_at.setdefault(a_, n_)
        for l in anonfix.lines('config/aliases.txt'):
            q = l.split()
            if len(q) >= 2 and q[1].startswith('0x'):
                try:
                    a_ = int(q[1], 16)
                except ValueError:
                    continue
                k_ = _row_at.get(a_)
                if k_ and k_ != q[0] and q[0] not in _row_addr and (a_ < 0x3CD300 or q[0].startswith('??_C@')) \
                        and k_[:1] in '?_' \
                        and not k_.startswith('__ehhandler$') and not k_.startswith('$') and q[0] not in _badfolds:
                    _fold_pairs[q[0]] = k_
    _frf =os.environ.get('M7FOLDROWS', 'config/m7foldrows.txt')
    if _frf and _frf != '0' and os.path.exists(_frf):
        # (M7FOLDROWS=FILE, config/m7foldrows.txt by default, 0 none: rows the image folds
        # other functions into, callcheck.py's targets, may fold)
        _fr = set(l.strip() for l in open(_frf) if l.strip() and not l.startswith('#'))
        distinct_names = frozenset(x for x in distinct_names if x not in _fr)
    if os.environ.get('M7FOLDALIASED'):
        # (M7FOLDALIASED=1, measuring: a row whose address config/aliases.txt also gives another
        # name (a body the image folded others into) may fold)
        _aliased = set()
        for l in anonfix.lines('config/aliases.txt'):
            q = l.split()
            if len(q) >= 2 and q[1].startswith('0x'):
                _aliased.add(int(q[1], 16))
        distinct_names = frozenset(next(iter(v)) for a, v in _addr_names.items() if len(v) == 1 and a not in _aliased)

    # (M7EHFOLD, default on: the EH handlers the image shares between functions of one object,
    # each function's `push offset __ehhandler$...` reaching the same address: one copy per
    # address is kept, the others folded into it by comdatize.ehfold, so the kept copies lie in
    # the image's order whatever link.exe's own folding would pick. A function folded into
    # another (config/aliases.txt, or sharing an address in the previous link's map) takes that
    # one's label: every copy of its group's handler goes, the kept one made standalone as well,
    # so the functions keep identical associative sections and still fold)
    _eh_t = collections.defaultdict(dict)
    _eh_name = {}
    _eh_obj = {}
    _eh_lab = {}
    if os.environ.get('M7EHFOLD', '1') != '0':
        sys.path.insert(0, os.path.join(os.path.dirname(os.path.abspath(__file__)), '..'))
        from xbe import Xbe  # noqa: E402
        import struct  # noqa: E402
        _eimg = Xbe(os.path.join('orig', 'Game_XboxMultiplayer.xbe'))
        _fn_lab = {}
        for l in anonfix.lines('config/compiled.txt'):
            q = l.split()
            if len(q) < 3 or not q[0].startswith('0x'):
                continue
            a = int(q[0], 16)
            # (M7EHFOLDLIB, default on: the libraries' objects too, libcpmt's _Xlen sharing _Xran's)
            _lib_ok = os.environ.get('M7EHFOLDLIB', '1') != '0' and q[1].startswith('build/xdk/')
            if (a < 0x22CB5B or _lib_ok) and (q[1].startswith('build/src/') or _lib_ok) and q[2][:1] in '?_':
                try:
                    b = _eimg.read(a, 10)
                except Exception:
                    continue
                t = None
                if b[:6] == bytes.fromhex('558bec6aff68'):
                    t = struct.unpack_from('<I', b, 6)[0]
                elif b[:1] == b'\xb8' and b[5:6] == b'\xe8':
                    # (mov eax, handler / call __EH_prolog: libcpmt's _Xran and _Xlen)
                    t = struct.unpack_from('<I', b, 1)[0]
                if t is not None:
                    _eh_t[os.path.basename(q[1]).lower()].setdefault('__ehhandler$' + q[2], t)
                    _fn_lab.setdefault(a, t)
                    _eh_name.setdefault(q[2], t)
            # (a handler's own row: its address)
            if q[2].startswith('__ehhandler$') and '>' not in q[2] and not re.search(r'-0x[0-9A-Fa-f]+$', q[2]) \
                    and (q[1].startswith('build/src/') or _lib_ok):
                _eh_t[os.path.basename(q[1]).lower()][q[2]] = a
                _eh_obj[a] = os.path.basename(q[1]).lower()
        for l in anonfix.lines('config/aliases.txt'):
            q = l.split()
            if len(q) >= 2 and q[1].startswith('0x') and int(q[1], 16) in _fn_lab:
                _eh_name[q[0]] = _fn_lab[int(q[1], 16)]   # (an alias: its target's label, over the map's)
        if os.environ.get('M7EHFOLDMAP', '1') != '0' and os.path.exists(_PREV_MAP):
            _at = collections.defaultdict(list)
            for l in anonfix.lines(_PREV_MAP, encoding=None, errors='replace'):
                q = l.split()
                if len(q) >= 4 and q[0].startswith('0001:') and not q[1].startswith('__ehhandler$') \
                        and not q[1].startswith('$'):
                    _at[q[2]].append(q[1])
            for v in _at.values():
                ls = set(_eh_name[x] for x in v if x in _eh_name)
                if len(v) > 1 and len(ls) == 1:
                    t = ls.pop()
                    for x in v:
                        _eh_name.setdefault(x, t)

    # (M7EHCROSS, default on: a handler the image shares between functions of different objects,
    # unit_18F3C0's and unit_192BE0's vf_000 instances: the object with the handler's row exports
    # its kept copy under external names, the others' copies are folded into it by
    # comdatize.eh_import; link.exe folds no handler across objects itself here)
    _eh_cross_imp = collections.defaultdict(list)
    _eh_cross_exp = collections.defaultdict(set)
    if os.environ.get('M7EHCROSS', '1') != '0':
        _by_t = collections.defaultdict(lambda: collections.defaultdict(list))
        for o_, hs_ in _eh_t.items():
            for h_, t_ in hs_.items():
                if h_[12:] in _eh_name:
                    _by_t[t_][o_].append(h_)
        for t_, objs_ in _by_t.items():
            k_ = _eh_obj.get(t_)
            if k_ in objs_ and len(objs_) > 1:
                _eh_cross_exp[k_].add(t_)
                for o_, hs_ in objs_.items():
                    if o_ != k_:
                        _eh_cross_imp[o_].extend((h_, t_) for h_ in hs_)

    def _eh_cross(dst, base, folded):
        gone = set(x for x, _ in folded)
        lab = _eh_lab.get(dst, {})
        for t_ in _eh_cross_exp.get(base, ()):
            h_ = next((h for h, v in sorted(lab.items()) if v == t_ and h not in gone), None)
            if h_:
                comdatize.eh_export(dst, h_, '%X' % t_)
        for h_, t_ in _eh_cross_imp.get(base, ()):
            comdatize.eh_import(dst, h_, '%X' % t_)

    def _eh_pairs(dst, base):
        """(dup, keep) handler pairs for the object DST (source BASE): its .text$x handlers in
        section order, each labelled by the image address of its function's push or its own
        row (or a function folded with that one's); the image's addresses in order matched
        greedily as a subsequence, the first copy matched kept per address."""
        if base not in _eh_t:
            return []       # (the game's objects only)
        lab = dict(_eh_t.get(base, {}))
        from coff import Coff  # noqa: E402
        try:
            c = Coff(dst)
        except ValueError:
            return []       # (an import library's member)
        hs = []
        for y in c.symbol_list:
            if y['section'] > 0 and y['name'].startswith('__ehhandler$') \
                    and c.sections[y['section'] - 1]['name'] == '.text$x':
                if y['name'] not in lab and y['name'][12:] in _eh_name:
                    lab[y['name']] = _eh_name[y['name'][12:]]
                if y['name'] in lab:
                    hs.append(y['name'])
        # (only the addresses whose handler row is this object's: a template instance's copy
        # whose image copy is another object's is left to the link)
        hs = [h for h in hs if _eh_obj.get(lab[h]) == base]
        _eh_lab[dst] = dict((h, lab[h]) for h in hs)
        if len(set(lab[h] for h in hs)) == len(hs):
            return []
        want = sorted(set(lab[h] for h in hs))
        keep, k = {}, 0
        for h in hs:
            if k < len(want) and lab[h] == want[k]:
                keep[want[k]] = h
                k += 1
        # (M7EHKEEPOWN, default on: the handler whose own row is the address kept, its body
        # loading its own funcinfo as the image's does: ~length_error's at 0x2FF7A8, which
        # ~logic_error also pushes, before it in section order)
        if os.environ.get('M7EHKEEPOWN', '1') != '0':
            for lb_ in list(keep):
                own_ = [x_ for x_ in hs if lab[x_] == lb_ and _row_addr.get(x_) == lb_]
                if own_:
                    keep[lb_] = own_[0]
        # (M7EHKEEPROW, default on: the kept handler a function of its own, not one config/
        # aliases.txt folds into another's body: that copy's handler goes with it)
        if os.environ.get('M7EHKEEPROW', '1') != '0':
            for lb_, h_ in list(keep.items()):
                if h_[len('__ehhandler$'):] in _fold_pairs:
                    alt_ = [x_ for x_ in hs if lab[x_] == lb_ and x_[len('__ehhandler$'):] not in _fold_pairs]
                    if alt_:
                        keep[lb_] = alt_[0]
        return [(h, keep[lab[h]]) for h in hs if lab[h] in keep and keep[lab[h]] != h]

    dst_src = {}

    def _eh_move(dst, folded):
        """(M7EHMOVE, default on; M7EHMOVE=0 keeps the objects' section order, which puts some
        catchable types in the image's order but leaves the moved _Tree families unordered) the
        object DST's kept labelled handlers in the image's order:
        each one's function family (or the handler itself, made standalone by ehfold) moved to
        the end of the section table in label order (comdatize.move_families)."""
        lab = _eh_lab.get(dst)
        if not lab or len(lab) < 2 or os.environ.get('M7EHMOVE', '1') == '0':
            return
        from coff import Coff  # noqa: E402
        import struct  # noqa: E402
        c = Coff(dst)
        symptr = struct.unpack_from('<I', c.data, 8)[0]
        gone = set(x for x, _ in folded)
        parent = {}
        for y in c.symbol_list:
            sn = y['section']
            if sn > 0 and y['class'] == 3 and y['value'] == 0 and y['name'] == c.sections[sn - 1]['name'] \
                    and c.sections[sn - 1]['chars'] & 0x1000 and c.data[symptr + y['index'] * 18 + 17]:
                ao = symptr + (y['index'] + 1) * 18
                if c.data[ao + 14] == 5:
                    parent.setdefault(sn, struct.unpack_from('<H', c.data, ao + 12)[0])
        units = []
        for y in c.symbol_list:
            if y['name'] in lab and y['name'] not in gone and y['section'] > 0:
                units.append((lab[y['name']], parent.get(y['section'], y['section'])))
        units = [u for _, u in sorted(set(units))]
        # (M7DISOWNLAST=1, measuring, off: worse, the copies then win the fold; the disowned copies (_cdzx_), moved after every kept
        # function: identical-function folding keeps the first in section order, which must be
        # the row's copy, /ORDER placing it; the copies fold into it, their EH tables kept)
        if os.environ.get('M7DISOWNLAST') == '1':
            _dl = [y['section'] for y in c.symbol_list if y['name'].startswith('_cdzx_') and y['section'] > 0
                   and c.sections[y['section'] - 1]['chars'] & 0x20 and y['section'] not in units]
            units = units + sorted(set(_dl), key=_dl.index)
        # (M7EHMOVEMIN=1 or an object regex, measuring, off: only the units from the first one out of section order on
        # move; the ones before keep their places, and their funcinfo and catchable types the
        # compiler's order: unit_0441B0's tables; all of them in an object with folded
        # template instances' handlers, whose identical functions fold into the first in
        # section order, which must be the image's row: unit_1FC320's _Tree instances)
        _mm = os.environ.get('M7EHMOVEMIN', '0')
        if _mm != '0' and not any('?$' in d_ for d_, _ in folded)                 and (_mm == '1' or re.search(_mm, dst_src.get(dst, ''))):
            k = 1
            while k < len(units) and units[k] > units[k - 1]:
                k += 1
            units = units[k:]
        if units:
            comdatize.move_families(dst, units)

    class _OwnStatic(object):
        def __init__(self, base, names):
            self.base = base
            self.names = names

        def __contains__(self, name):
            return name in self.names and _row_obj.get(name) == self.base

    class _Disown(object):
        def __init__(self, base):
            self.base = base

        def __bool__(self):
            return True

        def __contains__(self, name):
            o = _row_obj.get(name)
            return o is not None and o != self.base and not o.startswith('standin_') and o.endswith('.obj')                 and _row_addr.get(name, 1 << 32) < 0x3CD300 and _row_xdk.get(name, False)

    # (config/m7disown.txt: the game inlines M7DISOWNGAME's rule applies to when it is off)
    _m7disown = set(l.strip() for l in open('config/m7disown.txt', encoding='utf-8')
                    if l.strip() and not l.startswith('#')) if os.path.exists('config/m7disown.txt') else set()

    class _DisownGame(_Disown):
        def __contains__(self, name):
            if os.environ.get('M7DISOWNGAME', '0') == '0' and name not in _m7disown:
                return False
            o = _row_obj.get(name)
            return o is not None and o != self.base and o.endswith('.obj') and not o.startswith('standin_')                 and _row_addr.get(name, 1 << 32) < 0x3CD300 and not _row_xdk.get(name, False)

    class _FoldDisown(object):
        # (M7FORCEFOLD: the copies of a function the image folds into another's body too)
        def __init__(self, inner):
            self.inner = inner

        def __bool__(self):
            return True

        def __contains__(self, name):
            return name in _fold_pairs or name in self.inner

    # (M7BSS, default on: every .bss variable at its image address, build/m7/bssmap.txt from
    # tools/session/bssmap.py, through comdatize.bss_layout)
    _bss_static, _bss_ext, _bss_commons_done, _bss_ext_done, _bss_addr_done = {}, {}, set(), set(), set()
    if os.environ.get('M7BSS', '1') != '0':
        subprocess.run([sys.executable, os.path.join('tools', 'session', 'bssmap.py')], check=True,
                       capture_output=True)
        _bl = []
        for l in open(os.path.join(out, 'bssmap.txt')):
            q = l.split()
            if len(q) == 3:
                _bl.append((int(q[0], 16), q[1], q[2]))
        _addrs = sorted(set(a for a, o, n in _bl))
        from xbe import Xbe  # noqa: E402
        # (each variable runs to the next one's address or its section's end: the libraries'
        # uninitialized sections, D3D_URW, end inside their merged sections)
        _ends = sorted(s_['va'] + s_['vsize'] for s_ in Xbe(os.path.join('orig', 'Game_XboxMultiplayer.xbe')).sections)
        _nxt = {}
        for _i, _a in enumerate(_addrs):
            _e = _ends[bisect.bisect_right(_ends, _a)] if bisect.bisect_right(_ends, _a) < len(_ends) else _a + 4
            _nxt[_a] = min(_addrs[_i + 1], _e) if _i + 1 < len(_addrs) else _e
        for a, o, n in _bl:
            if o == '-':
                _bss_ext[n] = (a, _nxt[a] - a)
            else:
                _bss_static[('/'.join(o.split('/')[-2:]).lower(), n)] = (a, _nxt[a] - a)

    # (M7DATAADDR, default on: every data section in its image order, comdatize.data_layout: the object's
    # own rows, a stand-in piece's (repacked into a member), and for a COMDAT any unique row)
    _DATA_NAMES = frozenset(['.rdata', '.data', 'XON_RD', 'BINKDATA', 'DOLBY', '.data1', 'DSOUND_RD',
                             'DSOUND_RW', 'DSOUND_URW', 'XGRPH_RD', 'XGRPH_RW', 'WMADEC_RD', 'WMADEC_RW',
                             'D3D_RD', 'D3D_RW', 'D3D_URW', 'D3DX_RD', 'D3DX_RW', 'XNET_RD', '.CRT$XCU', '.XPP$Data', '.XPP$DATA']
                            + (['.text$x'] if os.environ.get('M7TEXTX', '1') != '0' else [])
                            + (['.xdata$x'] if os.environ.get('M7XDATAX', '1') != '0' else []))
    _DATA_NAMES = frozenset(_DATA_NAMES)
    _rows_by_tail = collections.defaultdict(dict)
    _row_unique = {}
    _row_piece = {}
    if os.environ.get('M7DATAADDR', '1') != '0':
        _cnt = collections.Counter()
        _all = []
        # (config/m7rows.txt: rows only the M7 link keys by, data the placement link keeps as a
        # stand-in piece because a name it shares cannot be placed twice there: storutil's
        # table, which points at unit_067B10's "" while RenderWare's "" lies elsewhere)
        for l in list(anonfix.lines('config/compiled.txt')) + (
                list(open('config/m7rows.txt', encoding='utf-8')) if os.path.exists('config/m7rows.txt') else []):
            q = l.split()
            if len(q) >= 3 and q[0].startswith('0x'):
                a_ = int(q[0], 16)
                _all.append((a_, q[1], q[2]))
                _cnt[q[2]] += 1
        for a_, o_, n_ in _all:
            _rows_by_tail['/'.join(o_.split('/')[-2:]).lower()].setdefault(n_, a_)
            if _cnt[n_] == 1:
                _row_unique[n_] = a_
                if o_.startswith('build/src/xdk/standin'):
                    _row_piece[n_] = a_

    _eh_img_c = []

    def _eh_img():
        if not _eh_img_c:
            sys.path.insert(0, os.path.join(os.path.dirname(os.path.abspath(__file__)), '..'))
            from xbe import Xbe  # noqa: E402
            _eh_img_c.append(Xbe(os.path.join('orig', 'Game_XboxMultiplayer.xbe')))
        return _eh_img_c[0]

    def _eh_table_rows(dst, ra):
        """The image addresses of the object DST's EH tables ($T statics in .xdata$x), from the
        rows named after their handlers: a handler __ehhandler$F's funcinfo is the row
        __ehhandler$F>1, a table a funcinfo names at offset N the row __ehhandler$F>1>N,
        and so on down (the try map's handler array, >1>16>16)."""
        from coff import Coff  # noqa: E402
        try:
            c = Coff(dst)
        except ValueError:
            return {}
        out_ = {}
        _tbl_addr = {}
        by_sec = collections.defaultdict(list)
        for y in c.symbol_list:
            if y['section'] > 0 and y['class'] in (2, 3):
                by_sec[y['section']].append(y)

        def walk(sym, name):
            sn = sym['section']
            s = c.sections[sn - 1]
            for va, si, t in s['relocs']:
                z = c.symbols.get(si)
                if z is None or z['section'] <= 0 or not c.sections[z['section'] - 1]['name'].startswith('.xdata$x'):
                    continue
                if not sym['value'] <= va or z['name'] in out_ or z['name'] == c.sections[z['section'] - 1]['name']:
                    continue
                n2 = '%s>%d' % (name, va - sym['value'])
                a2 = ra.get(n2) if n2 in ra else _row_unique.get(n2)
                if a2 is None and _tbl_addr.get(sym['name']) is not None:
                    # (no row by that name: the image's pointer in the parent table there)
                    try:
                        a2 = struct.unpack('<I', _eh_img().read(_tbl_addr[sym['name']] + va - sym['value'], 4))[0]
                        a2 -= struct.unpack_from('<i', s['data'], va)[0] if s['data'] else 0
                    except Exception:
                        a2 = None
                if a2 is None:
                    continue
                out_[z['name']] = a2
                _tbl_addr[z['name']] = a2
                walk(z, n2)
        for y in c.symbol_list:
            hn_ = y['name']
            m_ = re.match(r'^_cdzeh_([0-9A-F]+)_\d+$', hn_)
            if m_:
                # (a handler ehfold's cross-object fold renamed: its image address's row)
                hn_ = next((x_ for x_ in _addr_names.get(int(m_.group(1), 16), ()) if x_.startswith('__ehhandler$')), hn_)
            if hn_.startswith('__ehhandler$') and y['section'] > 0:
                y = dict(y, name=hn_)
                s = c.sections[y['section'] - 1]
                for va, si, t in s['relocs']:
                    z = c.symbols.get(si)
                    if z is None or z['section'] <= 0 or not c.sections[z['section'] - 1]['name'].startswith('.xdata$x'):
                        continue
                    n1 = y['name'] + '>1'
                    a1 = ra.get(n1) if n1 in ra else _row_unique.get(n1)
                    if a1 is None and _row_addr.get(y['name'][12:]) is not None:
                        # (no row by that name, the handler shared in the image: the function's
                        # push of its handler, and the handler's mov of its funcinfo, in the image)
                        try:
                            b_ = _eh_img().read(_row_addr[y['name'][12:]], 10)
                            if b_[:6] == bytes.fromhex('558bec6aff68'):
                                h_ = struct.unpack_from('<I', b_, 6)[0]
                                hb_ = _eh_img().read(h_, 5)
                                if hb_[:1] == bytes.fromhex('b8'):
                                    a1 = struct.unpack_from('<I', hb_, 1)[0]
                        except Exception:
                            a1 = None
                    if a1 is not None and z['name'] not in out_:
                        _tbl_addr[z['name']] = a1
                        out_[z['name']] = a1
                        walk(z, n1)
        return out_

    def _data(dst, sp):
        if not _rows_by_tail:
            return
        tail = '/'.join(sp.replace(os.sep, '/').split('/')[-2:]).lower()
        try:
            ra = dict(_row_piece)
            # (a stand-in member xdkrepack merged from both library versions: the 5849 copy's
            # rows too, under the installed one's)
            ra.update(_rows_by_tail.get('xdklib_' + tail, {}))
            ra.update(_rows_by_tail.get(tail, {}))
            # (.text$x, the EH funclets and handlers, by address only in the libraries' members and
            # the stand-ins: the game's follow their functions' /ORDER places, folded ones shared)
            _names = _DATA_NAMES
            if ('.text$x' in _DATA_NAMES or '.xdata$x' in _DATA_NAMES) and not ('/xdk/' in sp.replace(os.sep, '/') or '/standin' in sp.replace(os.sep, '/')
                                                 or '/cdz/lib' in sp.replace(os.sep, '/')):
                # (M7XDATAGAME, default on: the game's .xdata$x by address too, its $T tables named by the
                # rows of their handlers (_eh_table_rows); keyed names within eight suffix characters)
                _names = _DATA_NAMES - ({'.text$x'} if os.environ.get('M7XDATAGAME', '1') != '0'
                                        else {'.text$x', '.xdata$x'})
            # (every object's $T tables by their handlers' rows: a library member's or stand-in's
            # copy of a COMDAT handler the link takes too)
            if '.xdata$x' in _names:
                ra.update((k_, v_) for k_, v_ in _eh_table_rows(dst, ra).items() if k_ not in ra)
            comdatize.data_layout(dst, ra, _names, _row_unique)
        except ValueError:
            pass

    def _bss(dst, sp):
        if not _bss_ext and not _bss_static:
            return
        from coff import Coff  # noqa: E402
        try:
            c = Coff(dst)
        except ValueError:
            return
        tail = '/'.join(sp.replace(os.sep, '/').split('/')[-2:]).lower()
        placed, commons = {}, set()
        for y in c.symbol_list:
            if y['section'] > 0:
                s = c.sections[y['section'] - 1]
                if not (s['chars'] & 0x80) or y['name'] == s['name']:
                    continue
                v = _bss_static.get((tail, y['name'])) or _bss_static.get(('xdklib_' + tail, y['name']))                     or _bss_ext.get(y['name'])
            elif y['section'] == 0 and y['class'] == 2 and y['value'] > 0 and y['name'] not in _bss_commons_done:
                v = _bss_ext.get(y['name'])
                if v:
                    commons.add(y['name'])
            else:
                continue
            if v:
                # (an external another object placed already, a duplicate definition the link
                # ignores: its copy takes no room)
                # (and a second name at one address, two recovered declarations of one variable:
                # the first takes the room)
                if (y['class'] == 2 and y['name'] in _bss_ext_done) or v[0] in _bss_addr_done:
                    v = (v[0], 0)
                else:
                    _bss_addr_done.add(v[0])
                placed[y['name']] = v
        _bss_ext_done.update(n for n, v in placed.items() if n in _bss_ext and v[1])
        if any((s['chars'] & 0x80) and (s['name'].startswith('.bss') or s['name'].split('$')[0].endswith('_URW'))
               for s in c.sections) or commons:
            comdatize.bss_layout(dst, placed, commons)
            _bss_commons_done.update(commons)

    # (M7STATICFOLD, default on: a file-local function the image folds into another object's
    # copy, build/m7/staticfolds.txt from staticfold.py, is sent there through an alias name
    # the image's copy gets: link.exe keeps the image's copy, whichever it meets first)
    _static_cache = {}

    def _is_static(path, name):
        if path not in _static_cache:
            from coff import Coff  # noqa: E402
            try:
                _static_cache[path] = set(y['name'] for y in Coff(path).symbol_list if y['class'] == 3 and y['section'] > 0)
            except Exception:
                _static_cache[path] = set()
        return name in _static_cache[path]

    def _sf_tail(p):
        q = p.replace(os.sep, '/').lower().split('/')
        return (q[-2][len('xdklib_'):] if q[-2].startswith('xdklib_') else q[-2]) + '/' + q[-1] if len(q) > 1 else q[-1]
    _sf_defs = collections.defaultdict(dict)
    _sf_refs = collections.defaultdict(dict)
    _sff = os.path.join(out, 'staticfolds.txt')
    if os.environ.get('M7STATICFOLD', '1') != '0' and (not os.path.exists(_sff) or
                                                       os.path.getmtime(_sff) < os.path.getmtime('config/compiled.txt')):
        subprocess.run([sys.executable, 'tools/session/staticfold.py'], check=True, capture_output=True)
    if os.environ.get('M7STATICFOLD', '1') != '0' and os.path.exists(_sff):
        import hashlib
        _linked = set(_sf_tail(src_of(o)) for o in objs)
        for l in open(_sff, encoding='utf-8'):
            q = l.split()
            if len(q) != 4:
                continue
            a_, t_ = _sf_tail(q[0]), _sf_tail(q[2])
            if a_ != t_ and a_ in _linked and q[2].startswith('build/src/xdk/standin_') and t_ not in _linked:
                # (a stand-in piece: a public name of the stand-in objects, referred to directly)
                _sf_refs[a_][q[1]] = q[3]
                continue
            if a_ == t_ or a_ not in _linked or t_ not in _linked:
                continue
            al = '__sfold_' + hashlib.md5((t_ + ' ' + q[3]).encode('latin-1')).hexdigest()[:16]
            _sf_defs[t_][q[3]] = al
            _sf_refs[a_][q[1]] = al
        # (a forced fold into a file-local function, BP_ResetTransform: /ALTERNATENAME cannot name
        # a static, so the target's object defines an alias name at it, and the fold goes there)
        _row_path = {}
        for l in anonfix.lines('config/compiled.txt'):
            q = l.split()
            if len(q) >= 3 and q[0].startswith('0x'):
                _row_path.setdefault(q[2], q[1])
        for n_, k_ in list(_fold_pairs.items()):
            t_ = _sf_tail(_row_path.get(k_, ''))
            if t_ in _linked and _row_path.get(k_, '').startswith('build/xdk/') and _is_static(_row_path[k_], k_):
                al = '__sfold_' + hashlib.md5((t_ + ' ' + k_).encode('latin-1')).hexdigest()[:16]
                _sf_defs[t_][k_] = al
                _fold_pairs[n_] = al
    # (build/m7/standin/static_targets.txt, xdkrepack.py: a binarized member's references to
    # another object's file-local function go to that alias name too)
    _stf = os.path.join(out, 'standin', 'static_targets.txt')
    if os.environ.get('M7STATICFOLD', '1') != '0' and os.path.exists(_stf):
        import hashlib
        for l in open(_stf, encoding='utf-8'):
            q = l.split()
            if len(q) == 2:
                t_ = _sf_tail(q[0])
                _sf_defs[t_][q[1]] = '__sfold_' + hashlib.md5((t_ + ' ' + q[1]).encode('latin-1')).hexdigest()[:16]
    staticfold_added = [0]
    # (config/m7drop.txt: stand-in pieces holding imagebld's output, left out of the probe)
    _m7drop = set()
    if os.path.exists('config/m7drop.txt'):
        _m7drop = set(l.split()[0] for l in open('config/m7drop.txt', encoding='utf-8')
                      if l.split() and not l.startswith('#'))
    _m7tls = dict(l.split()[:2] for l in open('config/m7tls.txt', encoding='utf-8')
                  if len(l.split()) >= 2 and not l.startswith('#')) if os.path.exists('config/m7tls.txt') else {}
    # (config/m7bssrw.txt: NAME, an uninitialized variable placed under its section's _RW name)
    if os.path.exists('config/m7bssrw.txt'):
        comdatize.BSS_RW.update(l.split()[0] for l in open('config/m7bssrw.txt', encoding='utf-8')
                                if l.split() and not l.startswith('#'))
    _m7static = [l.split() for l in open('config/m7static.txt', encoding='utf-8')
                 if len(l.split()) in (2, 3) and not l.startswith('#')] if os.path.exists('config/m7static.txt') else []
    # (config/m7align.txt: NAME ALIGN, a section's alignment the image's layout needs)
    _m7align = {}
    if os.path.exists('config/m7align.txt'):
        for l in open('config/m7align.txt', encoding='utf-8'):
            q = l.split()
            if len(q) == 2 and not q[0].startswith('#'):
                _m7align[q[0]] = int(q[1])

    # (the image's library table: name -> (rank, 16-byte record), for comdatize.xbld_fix)
    _xbld_table = {}
    with open(os.path.join('orig', 'Game_XboxMultiplayer.xbe'), 'rb') as f_:
        _xd = f_.read()
    _xbase = struct.unpack_from('<I', _xd, 0x104)[0]
    _xn, _xa = struct.unpack_from('<II', _xd, 0x160)
    for _i in range(_xn):
        _rec = _xd[_xa - _xbase + 16 * _i:_xa - _xbase + 16 * _i + 16]
        _xbld_table[_rec[:8].rstrip(b'\0').decode('latin-1')] = (_i, _rec)

    def cdz_file(src, dst, tag):
        # M7CDZ_SKIPXDK=1: the XDK's members (and their stand-ins) keep their plain sections,
        # which the original link could not fold or reorder either
        sp = src.replace(os.sep, '/')
        if os.environ.get('M7CDZ_SKIPXDK') and ('/xdk/' in sp or '/standin/' in sp or '/lib' in sp and '/cdz/' in sp
                                                or os.path.basename(os.path.dirname(sp)).startswith('lib')):
            os.makedirs(os.path.dirname(dst), exist_ok=True)
            open(dst, 'wb').write(open(src, 'rb').read())
            return dst
        os.makedirs(os.path.dirname(dst), exist_ok=True)
        key = src.replace(os.sep, '/')
        pre = os.path.join(out, 'obj').replace(os.sep, '/') + '/'
        key = key[len(pre):] if key.startswith(pre) else key
        cdz_of.setdefault(key, {})
        nofold = os.environ.get('M7NOFOLDXDK', 'rows') if ('/xdk/' in sp or '/standin/' in sp or '/cdz/lib' in sp) else os.environ.get('M7NOFOLDGAME')
        nofold = 'all' if nofold == 'all' else (distinct_names if nofold == 'rows' else bool(nofold))
        # (M7DISOWN, default on: in an XDK object, a packaged function whose row is another
        # object's (a header inline both define) is left to that object, so the link takes
        # the image's copy whichever object it meets first: dsound's XMOAcceptPacket, which
        # xvoice's hawk2 also has)
        disown = frozenset()
        if os.environ.get('M7DISOWN', '1') != '0' and ('/xdk/' in sp or '/standin/' in sp):
            disown = _Disown(os.path.basename(sp).lower())
        elif (os.environ.get('M7DISOWNGAME', '0') != '0' or _m7disown) and sp.replace(os.sep, '/').startswith('build/src/'):
            # (M7DISOWNGAME=1, measuring, off: worse, the _Tree folds lose their order; in a game object too, a header inline whose row is
            # another game object's: unit_0B9EA0's length_error copy constructor has an EH
            # frame, unit_042F40's, the image's, none)
            disown = _DisownGame(os.path.basename(sp).lower())
        if _fold_pairs:
            disown = _FoldDisown(disown)
        # (a static's row keeps only the row's own object's copy apart: M7NOFOLDSTATIC=0 off)
        nfs = None
        if isinstance(nofold, frozenset) and os.environ.get('M7NOFOLDSTATIC', '1') != '0':
            nfs = _OwnStatic(os.path.basename(sp).lower(), nofold)
        _t = _sf_tail(key)
        if _t in _sf_defs or _t in _sf_refs:
            staticfold_added[0] += comdatize.staticfold(src, dst + '.sf', _sf_defs.get(_t, {}), _sf_refs.get(_t, {}))
            src = dst + '.sf'
        # (M7FOLDWEAK, default on: a fold no object defines, a weak external such as a vector
        # deleting destructor defaulting to the scalar one, defaults to the fold's target instead;
        # before convert, which appends relocation tables after the string table)
        if _fold_pairs and os.environ.get('M7FOLDWEAK', '1') != '0' and comdatize.weak_names(src) & set(_fold_pairs):
            open(dst + '.wf', 'wb').write(open(src, 'rb').read())
            comdatize.weak_retarget(dst + '.wf', _fold_pairs)
            src = dst + '.wf'
        for name, inner in comdatize.convert(src, dst, tag, nofold, disown, nfs):
            for x in inner:
                cdz_map.setdefault(x, name)
                cdz_of.setdefault(key, {}).setdefault(x, name)
        if _m7align:
            comdatize.set_align(dst, _m7align)
        if _m7drop:
            comdatize.drop_defs(dst, _m7drop)
        # (config/m7tls.txt: NAME SECTION, a thread-local variable's section in the image's order)
        if _m7tls:
            comdatize.set_section_names(dst, _m7tls)
        # (M7ZAPTEXT, default on: empty plain code sections byte-aligned, comdatize.zap_empty_code)
        if os.environ.get('M7ZAPTEXT', '1') != '0':
            comdatize.zap_empty_code(dst)
        # (config/m7static.txt: OBJECT-SUFFIX NAME, a COMDAT literal made the object's own)
        _st = dict((q_[1], int(q_[2]) if len(q_) > 2 else None) for q_ in _m7static
                   if sp.replace(os.sep, '/').endswith(q_[0]))
        if _st:
            comdatize.static_comdat(dst, _st)
        # (M7SELFCALLS, default on: a stand-in piece's raw recursive call gets a relocation, so
        # identical recursive pieces stay apart as in the image)
        if os.environ.get('M7SELFCALLS', '1') != '0':
            selfcalls_added[0] += comdatize.selfcalls(dst)
        # (M7XDATAPLAIN=1, measuring: the game's EH tables plain, kept with folded functions)
        if os.environ.get('M7XDATAPLAIN') == '1' and sp.replace(os.sep, '/').startswith('build/src/'):
            comdatize.xdata_plain(dst)
        # (M7FOLDTABLES=1, measuring, off: keeps the folded function's funclets too; a function folded into another's body (_fold_pairs) keeps
        # its EH tables when the image has their rows: list<type_1D3C80>'s destructor)
        if os.environ.get('M7FOLDTABLES') == '1' and _fold_pairs:
            _fh = set('__ehhandler$' + n_ for n_ in _fold_pairs if ('__ehhandler$' + n_ + '>1') in _row_unique)
            if _fh:
                comdatize.keep_tables(dst, _fh)
        _ep = _eh_pairs(dst, os.path.basename(sp).lower())
        _done = comdatize.ehfold(dst, _ep) if _ep else []
        for dup_, keep_ in _done:
            eh_folded.append((key, dup_, keep_))
        dst_src[dst] = sp
        _eh_move(dst, _done)
        _eh_cross(dst, os.path.basename(sp).lower(), _done)
        _bss(dst, sp)
        _data(dst, sp)
        # (M7XBLD, default on: the library version records the image's, in its order)
        if os.environ.get('M7XBLD', '1') != '0':
            comdatize.xbld_fix(dst, _xbld_table)
        return dst

    # (build/m7/ehfolds.txt, for shiftcount.py: OBJECT DUP KEEP per handler folded by ehfold)
    eh_folded = []
    selfcalls_added = [0]
    # (build/m7/cdz/objects.txt: which object each numbered copy is)
    os.makedirs(os.path.join(cdir, 'obj'), exist_ok=True)
    with open(os.path.join(cdir, 'objects.txt'), 'w') as f:
        for i, o in enumerate(objs):
            f.write('%04d.obj %s\n' % (i, o.replace(os.sep, '/')))
    _objs_named = list(objs)
    # (the dynamic initializers' and terminators' bodies, .text$yc/.text$yd file-local functions,
    # that more than one object has: comdatize pads those, so made external they still never
    # fold, as the original link's statics did not)
    from coff import Coff  # noqa: E402
    _ybodies = collections.Counter()
    _defcount = collections.Counter()
    for o in objs:
        try:
            c_ = Coff(o)
        except Exception:
            continue
        # (the external functions each object defines: comdatize.ehfold keeps a folded
        # handler's funcinfo only for a function no other object defines too)
        for y_ in c_.symbol_list:
            if y_['class'] == 2 and y_['section'] > 0 and c_.sections[y_['section'] - 1]['chars'] & 0x20:
                _defcount[y_['name']] += 1
        for s_ in c_.sections:
            if s_['name'].startswith('.text$y') and s_['chars'] & 0x1000:
                # (the bytes with what each relocation names: only a true twin folds)
                _ybodies[(bytes(s_['data']), tuple((va_, c_.symbols[si_]['name'] if c_.symbols[si_]['class'] == 2 else '', t_)
                                                   for va_, si_, t_ in s_['relocs']))] += 1
    comdatize.PAD_BODIES = set(b_[0] for b_, n_ in _ybodies.items() if n_ > 1 and not b_[1])
    comdatize.LOOSE_OK = set(_fold_pairs)
    comdatize.REMOVE_OK = set(_fold_pairs)
    comdatize.MULTI_DEFINED = set(n_ for n_, k_ in _defcount.items() if k_ > 1)
    objs = [cdz_file(o, os.path.join(cdir, 'obj', '%04d.obj' % i), 'o%04d' % i) for i, o in enumerate(objs)]
    # (M7XDATADEDUP=1, measuring, off: worse, the functions then keep their tables and stop folding; a folded handler's funcinfo ehfold made plain whose keyed name
    # another object's COMDAT copy has too, a header inline's table that copy keeps: the plain
    # one is associative again, or the image's one table would be there twice)
    if os.environ.get('M7XDATADEDUP') == '1':
        _xk = collections.defaultdict(list)
        for o_ in objs:
            try:
                c_ = Coff(o_)
            except Exception:
                continue
            for sn_, s_ in enumerate(c_.sections, 1):
                if s_['name'].startswith('.xdata$x') and s_['size']:
                    _xk[s_['name']].append((o_, sn_, bool(s_['chars'] & 0x1000)))
        _fix = collections.defaultdict(list)
        for nm_, lst_ in _xk.items():
            if nm_.endswith('zzzzzzz') or not any(c for _, _, c in lst_) or all(c for _, _, c in lst_):
                continue
            for o_, sn_, c_ in lst_:
                if not c_:
                    _fix[o_].append(sn_)
        for o_, sns_ in _fix.items():
            d_ = bytearray(open(o_, 'rb').read())
            opt_ = struct.unpack_from('<H', d_, 16)[0]
            for sn_ in sns_:
                h_ = 20 + opt_ + (sn_ - 1) * 40 + 36
                struct.pack_into('<I', d_, h_, struct.unpack_from('<I', d_, h_)[0] | 0x1000)
            open(o_, 'wb').write(bytes(d_))
        print('%d plain EH tables associative again (another object keeps the table)' % sum(map(len, _fix.values())))
    with open(os.path.join(out, 'ehfolds.txt'), 'w') as f:
        for k_, d_, kp_ in eh_folded:
            f.write('%s %s %s\n' % (k_, d_, kp_))
    print('%d recursive calls given relocations (selfcalls), %d static-fold symbols'
          % (selfcalls_added[0], staticfold_added[0]))
    new_libs = []
    for k, x in enumerate(libs):
        path = x.strip('"')
        if not os.path.isabs(path):
            path = os.path.join(XDK, 'xbox', 'lib', path)
        if os.path.basename(path).lower() == 'xboxkrnl.lib':
            new_libs.append(x)      # an import library: no code to package
            continue
        d = open(path, 'rb').read()
        work = os.path.join(cdir, 'lib%02d' % k)
        os.makedirs(work, exist_ok=True)
        pos, n, files = 8, 0, []
        while pos + 60 <= len(d):
            hdr = d[pos:pos + 60]
            name = hdr[:16].decode('latin-1').strip()
            size = int(hdr[48:58].decode().strip())
            body = d[pos + 60:pos + 60 + size]
            if name not in ('/', '//'):
                src = os.path.join(work, 'raw%04d.obj' % n)
                open(src, 'wb').write(body)
                files.append(cdz_file(src, os.path.join(work, 'm%04d.obj' % n), 'l%02d_%04d' % (k, n)))
                n += 1
            pos += 60 + size + (size & 1)
        lrsp = os.path.join(work, 'members.rsp')
        open(lrsp, 'w').write('\n'.join('"%s"' % os.path.abspath(f) for f in files) + '\n')
        target = os.path.abspath(os.path.join(cdir, os.path.basename(path)))
        if os.path.exists(target):
            os.replace(target, target + '.old')
        r = subprocess.run([os.path.join(VC, 'lib.exe'), '/nologo', '/OUT:' + target, '@' + lrsp],
                           capture_output=True, text=True)
        if r.returncode:
            raise SystemExit('lib %s: %s' % (path, r.stdout[-400:]))
        # (M7LIBINDEX, default on: the rebuilt archive's symbol index names the members the
        # input's does: a symbol every member defines, d3dx8's _D3DX8BuildNumber, otherwise
        # loads the last member, whose data the image lacks)
        _li = os.environ.get('M7LIBINDEX', 'd3dx8.lib,libcmt.lib')
        if _li != '0' and (_li == 'all' or os.path.basename(path).lower() in _li.lower().split(',')):
            import libindex  # noqa: E402
            libindex.fix(target, path)
        new_libs.append('"%s"' % target)
    libs = new_libs
keep = []
if os.environ.get('M7ORDER') and os.environ.get('M7KEEPPLAIN', '1') != '0':
    # a packaged section that was plain and holds a function the image has (a row): the
    # original link kept it with its object, referenced or not (/OPT:REF drops COMDATs only),
    # so the link is told to include it (M7KEEPPLAIN=0 off): IPP's psdp16sa6as.obj
    # (when another linked object defines one of its names too, only the row's own object's
    # section: the include would otherwise pick a member's copy over the stand-in piece the
    # row names; and none whose name an object's static has: its callers use that copy, and
    # the plain one is a transcription beside it, Bink's expand_asm simpmergesort; nor Bink's
    # *_asm.obj transcriptions at all, which sit beside unmatched C (yuv's setevenodd)
    _pre = os.path.join(out, 'obj').replace(os.sep, '/') + '/'
    _okeys = set(o.replace(os.sep, '/')[len(_pre):] if o.replace(os.sep, '/').startswith(_pre) else o.replace(os.sep, '/')
                 for o in _objs_named)
    _definers = collections.Counter(x for k_, names_ in cdz_of.items() if k_ in _okeys for x in names_)
    _tag_obj = dict(('o%04d' % i, os.path.basename(o).lower()) for i, o in enumerate(_objs_named))
    _tag_path = dict(('o%04d' % i, o.replace(os.sep, '/')) for i, o in enumerate(_objs_named))
    _keepskip = os.environ.get('M7KEEPSKIP')     # a measuring aid: objects (regex) left out
    # (M7KEEPCRT=0: nor a section of the CRT's (libcmt) holding stand-in pieces only, as
    # before coveredpieces.py dropped the pieces that repeated a member section's tail;
    # nor a stand-in piece among the EH handlers and initializers, .text$x and the $E
    # functions, which the order file does not place: the XGRAPHICS handler thunks)
    # (only .text's: library $E functions in their own named sections, DSOUND's and XPP's, are
    # not that run)
    _ehrows = [a for n_, a in _row_addr.items() if (n_.startswith('__ehhandler$') or n_.startswith('_$E'))
               and sec_range['.text'][0] <= a < sec_range['.text'][1]]
    _ehlo, _ehhi = min(_ehrows), max(_ehrows)
    keep = sorted(set(n for tag, n, inner in comdatize.PLAIN if tag.startswith('o') and any(x in distinct_names for x in inner)
                      and all(_definers[x] <= 1 or _row_obj.get(x) == _tag_obj.get(tag) for x in inner)
                      and not any(x in comdatize.STATIC_NAMES for x in inner)
                      and not _tag_obj.get(tag, '').endswith('_asm.obj')
                      and not (_keepskip and re.search(_keepskip, _tag_path.get(tag, '')))
                      and not any(_ehlo <= _row_addr.get(x, 0) <= _ehhi for x in inner)
                      and (os.environ.get('M7KEEPCRT', '1') != '0' or '/libcmt/' not in _tag_path.get(tag, '') or any(_row_obj.get(x) == _tag_obj.get(tag) for x in inner))))
    # (build/m7/keepplain.txt: every row-holding plain section, whether kept, its object and
    # the other definers' count)
    with open(os.path.join(out, 'keepplain.txt'), 'w') as f:
        for tag, n, inner in comdatize.PLAIN:
            if tag.startswith('o') and any(x in distinct_names for x in inner):
                f.write('%s %s %s %s %s\n' % ('KEEP' if n in keep else 'skip', tag, _tag_obj.get(tag), n,
                                              ' '.join('%s:%d:%s' % (x, _definers[x], _row_obj.get(x)) for x in inner)))
# (M7FORCEFOLD: what the disowned copies referred to, the image's rows among them, stays)
_fold_keep = sorted(n for n in comdatize.DISOWN_REFS if _fold_pairs and (n in _row_addr or n.lstrip('_') in _row_addr)
                    and n not in set(keep if 'keep' in dir() else ()))
# (config/m7kthunks.txt: the kernel imports in the image's thunk table order, /INCLUDEd first)
_kth = [l.strip() for l in open('config/m7kthunks.txt') if l.strip() and not l.startswith('#')] \
    if os.path.exists('config/m7kthunks.txt') and os.environ.get('M7KTHUNKS', '1') != '0' else []
# (M7KTHUNKS_EXTRA: the image's table ends at 0x3CD564 and the debug directory starts at
# 0x3CD580, 0x10 past the 16-byte boundary, as in COD's single-player default.xbe; the
# original import table was 7 slots longer, zeros in the image. What made them zeros is
# not known (imagebld writes extra, duplicate-ordinal and xbdm imports as they are): until
# it is, 7 unused kernel imports hold the room, 28 bytes differing)
_kth += [n for n in os.environ.get('M7KTHUNKS_EXTRA', '_NtWriteFileGather@32,_NtUserIoApcDispatcher@12,'
         '_NtSignalAndWaitForSingleObjectEx@20,_NtSetTimerEx@32,_NtSetIoCompletion@20,'
         '_NtRemoveIoCompletion@20,_NtReadFileScatter@32').split(',') if n]
libs = libs + [l_ for l_ in os.environ.get('M7EXTRALIBS', '').split(',') if l_]
open(rsp, 'w').write(''.join('/INCLUDE:__imp_%s\n' % n for n in _kth)
                     + '\n'.join('"%s"' % os.path.abspath(o) for o in objs) + '\n' + '\n'.join(libs) + '\n'
                     + ''.join('/INCLUDE:%s\n' % n for n in keep + keep_extra)
                     + ''.join('/ALTERNATENAME:%s=%s\n' % (n, _fold_pairs[n]) for n in sorted(set(comdatize.DISOWNED))
                               if n in _fold_pairs)
                     + ''.join('/INCLUDE:%s\n' % n for n in _fold_keep)
                     # (config/m7alt.txt: NAME TARGET, a name the M7 link resolves to another's
                     # definition, /ALTERNATENAME: a second declaration of one variable)
                     + ''.join('/ALTERNATENAME:%s=%s\n' % tuple(l.split()[:2]) for l in (
                         open('config/m7alt.txt', encoding='utf-8') if os.path.exists('config/m7alt.txt') else [])
                         if len(l.split()) >= 2 and not l.startswith('#'))
                     # (bssmap.py's gap-filled externals: an unreferenced COMDAT variable keeps its room)
                     + ''.join('/INCLUDE:%s\n' % l.strip() for l in (
                         open(os.path.join(out, 'bssfill.txt')) if os.path.exists(os.path.join(out, 'bssfill.txt'))
                         and os.environ.get('M7BSSFILLKEEP', '1') != '0' else []) if l.strip()))
env = dict(os.environ)
env['PATH'] = VC + os.pathsep + BIN + os.pathsep + env['PATH']
env['LIB'] = os.path.join(XDK, 'xbox', 'lib')
def _pdbpath():
    """A PDB path as long as the image's, so the RSDS record has its size."""
    want = len(r's:\COD\Game\GameCode\bin\Xbox_ReleaseMP\obj\Game_XboxReleaseMP.pdb')
    stem = os.path.abspath(out) + os.sep
    pad = want - len(stem) - len('Game_XboxReleaseMP.pdb') - 1
    d_ = os.path.join(out, 'p' * pad)
    os.makedirs(d_, exist_ok=True)
    return os.path.join(d_, 'Game_XboxReleaseMP.pdb')


cmd = [os.path.join(VC, 'Link.Exe'), '/nologo', '/MACHINE:I386', '/SUBSYSTEM:XBOX', '/FIXED:NO', '/INCREMENTAL:NO',
       # no /OPT:ICF: link 7.10's default folding (with /OPT:REF) folds identical functions
       # only, as the image's are; an explicit /OPT:ICF also folds identical read-only data
       # (vtables, EH tables), which the image keeps apart (type_3DFB28/34/40's vtables)
       ('/OPT:NOREF' if os.environ.get('M7NOREF') else '/OPT:REF'),
       ] + (['/OPT:NOICF'] if os.environ.get('M7NOICF') else []) + (
       # (M7NOLIBC, default on: RW, RW Audio and Bink were built /ML and name LIBC; the image's
       # CRT is libcmt's throughout, its rows, so LIBC is not searched)
       ['/NODEFAULTLIB:LIBC'] if os.environ.get('M7NOLIBC', '1') != '0' else []) + [
       ] + (
       # (M7LINKDEBUG, default on: the image's .rdata keeps the link's debug directory and its
       # CodeView RSDS record, s:\COD\Game\GameCode\bin\Xbox_ReleaseMP\obj\Game_XboxReleaseMP.pdb;
       # a PDB path of that length, the record's contents set by m7xbe.py)
       ['/DEBUG', '/PDB:' + _pdbpath()] if os.environ.get('M7LINKDEBUG', '1') != '0' else []) + [
       '/FORCE:MULTIPLE,UNRESOLVED', '/MAP:' + os.path.join(out, 'game.map'),
       '/OUT:' + os.path.join(out, 'game.exe'), '@' + rsp]
if os.environ.get('M7ORDER'):
    # M7ORDER=1 (a measuring aid, off by default; the original build need not have used it):
    # an /ORDER file of every code row's function in image order, so the link lays the
    # packaged functions out as the image has them
    import struct  # noqa: E402
    obj_syms = {}

    _statics = {}
    _repack = {}        # a member's path -> its repacked stand-in's (build/m7/standin/members.txt)
    if os.path.exists(os.path.join('build', 'm7', 'standin', 'members.txt')):
        for l_ in open(os.path.join('build', 'm7', 'standin', 'members.txt')):
            q_ = l_.split()
            if len(q_) == 3 and q_[0] not in ('REST', 'IMPORTS'):
                _repack[q_[1]] = q_[2].replace(os.sep, '/')

    def static_names(o):
        """The file-local function names an object defines."""
        if o not in _statics:
            try:
                c_ = Coff(o)
                _statics[o] = set(x['name'] for x in c_.symbol_list
                                  if x['section'] > 0 and x['class'] == 3 and x['type'] == 0x20)
            except Exception:
                _statics[o] = set()
        return _statics[o]

    def external_names(o):
        """The external names an object defines (short row names resolve against them)."""
        if o not in obj_syms:
            s = set()
            try:
                d = open(o, 'rb').read()
                _, _, _, sp, ns, _, _ = struct.unpack_from('<HHIIIHH', d, 0)
                st = sp + ns * 18
                i = 0
                while i < ns:
                    raw = d[sp + i * 18:sp + i * 18 + 8]
                    v, sec, t, c, na = struct.unpack_from('<IhHBB', d, sp + i * 18 + 8)
                    if sec > 0 and (c == 2 or (c == 3 and t == 0x20)):
                        if raw[:4] == b'\0\0\0\0':
                            so = struct.unpack_from('<I', raw, 4)[0]
                            s.add(d[st + so:d.index(b'\0', st + so)].decode('latin-1'))
                        else:
                            s.add(raw.rstrip(b'\0').decode('latin-1'))
                    i += 1 + na
            except OSError:
                pass
            obj_syms[o] = s
        return obj_syms[o]

    # the explicit objects' code (the game's, before the first library member, xapilib's at
    # 0x22CB5B): unlisted sections go after the listed ones, so the libraries' members,
    # many of them unpackaged, keep their pull order behind
    ORDER_END = int(os.environ.get("M7ORDER_END", "0x22CB5B"), 16)
    seen, names = set(), []
    row_order_name = {}
    folded = collections.defaultdict(list)
    import glob as _glob  # noqa: E402
    for sp in _glob.glob('src/**/*.c*', recursive=True):
        try:
            for line in open(sp, encoding='utf-8', errors='replace'):
                fm = re.match(r'^// (\S+) \(folded into 0x([0-9A-Fa-f]+)\)', line) or                     re.match(r'^// symbol: (\S+) = 0x([0-9A-Fa-f]+)', line)
                if fm and int(fm.group(2), 16) < ORDER_END:
                    folded[int(fm.group(2), 16)].append(anonfix.translate(fm.group(1)))
        except OSError:
            pass
    # the names our objects call or point at for each address: every matched function is the
    # image's bytes, so a relocation at an offset of it names, in our link, whatever the image
    # has at the address its instruction there reaches (an identical template instance, a
    # folded twin): that name goes in the order file at that address too
    from coff import Coff  # noqa: E402
    sys.path.insert(0, os.path.join(os.path.dirname(os.path.abspath(__file__)), '..'))
    from xbe import Xbe  # noqa: E402
    _img = Xbe(os.path.join('orig', 'Game_XboxMultiplayer.xbe'))
    _text = [s for s in _img.sections if s['name'] == '.text'][0]
    _tb = _img.read(_text['va'], _text['vsize'])
    _tlo, _thi = _text['va'], _text['va'] + _text['vsize']
    _by_obj = collections.defaultdict(list)
    by_reloc = collections.defaultdict(list)
    for l in anonfix.lines('config/compiled.txt'):
        q = l.split()
        if len(q) >= 3 and q[0].startswith('0x') and q[1].startswith('build/src/') and \
                int(q[0], 16) < ORDER_END and not q[2].startswith('$') and '>' not in q[2]:
            _by_obj[q[1]].append((int(q[0], 16), q[2]))
    for o, fns in _by_obj.items():
        try:
            c = Coff(o)
        except Exception:
            continue
        bynm = dict((s['name'], s) for s in c.symbol_list if s['section'] > 0)
        for fa, fn in fns:
            s = bynm.get(fn)
            if s is None or not (_tlo <= fa < _thi):
                continue
            try:
                code, rel = c.function_bytes(s)
            except Exception:
                continue
            for off, tn, rt in rel:
                p = fa - _tlo + off
                if p + 4 > len(_tb):
                    continue
                if rt == 20:
                    tgt = fa + off + 4 + struct.unpack_from('<i', _tb, p)[0]
                elif rt == 6:
                    tgt = struct.unpack_from('<I', _tb, p)[0]
                else:
                    continue
                if _tlo <= tgt < ORDER_END and tn not in by_reloc[tgt] and not tn.startswith('$') \
                        and not tn.startswith('.') and not tn.startswith('__real@'):
                    by_reloc[tgt].append(tn)
    # the same from the data rows (M7VTSLOTS=1, a measuring option, off: most slot twins are
    # stand-in pieces or nofold sections, which fold with nothing, and it cost shifts): a function a placed vtable or table
    # points at is, in the image, whatever its dword there reaches (a folded twin of the row
    # there, UIX's and XHV's one-instruction virtuals), so that name goes in the order file at
    # that address too, whether or not the row's own function was in the previous link
    by_slot = collections.defaultdict(list)
    if os.environ.get('M7VTSLOTS', '0') != '0':
        _code = [(s['va'], s['va'] + s['vsize']) for s in _img.sections if s['va'] < ORDER_END]
        _drows = collections.defaultdict(list)
        _rownames = set()       # (a name with a row of its own is ordered by it)
        _rowobj = {}
        for l in anonfix.lines('config/compiled.txt'):
            q = l.split()
            if len(q) >= 3 and q[0].startswith('0x'):
                _rownames.add(q[2])
                _rownames.add('_' + q[2])
                _rowobj[int(q[0], 16)] = q[1]
                if int(q[0], 16) >= ORDER_END:
                    _drows[q[1]].append((int(q[0], 16), q[2]))
        for o, ds in _drows.items():
            try:
                c = Coff(o)
            except Exception:
                continue
            bynm = dict((s['name'], s) for s in c.symbol_list if s['section'] > 0)
            for da, dn in ds:
                s = bynm.get(dn)
                if s is None:
                    continue
                sec = c.sections[s['section'] - 1]
                if sec['chars'] & 0x20:
                    continue
                later = [y['value'] for y in c.symbol_list if y['section'] == s['section'] and y['value'] > s['value']]
                end = min(later) if later else len(sec['data'] or b'')
                for va, si, t in sec['relocs']:
                    if t != 6 or not s['value'] <= va < end:
                        continue
                    tn = c.symbols[si]['name']
                    ts = c.symbols[si]
                    if ts['section'] > 0 and not (c.sections[ts['section'] - 1]['chars'] & 0x20):
                        continue        # (not a function: data or a literal)
                    if tn.startswith('$') or tn.startswith('.') or tn.startswith('??_C@'):
                        continue
                    try:
                        tgt = struct.unpack('<I', _img.read(da + va - s['value'], 4))[0]
                    except Exception:
                        continue
                    if not any(lo <= tgt < hi for lo, hi in _code) or tn in by_slot[tgt] \
                            or tn in _rownames or ts['section'] <= 0:
                        continue
                    # (a stand-in piece there folds with nothing: its name would add a copy)
                    if _rowobj.get(tgt, 'build/src/xdk/standin').startswith('build/src/xdk/standin'):
                        continue
                    # (only a twin: its body in this object is the image's bytes there,
                    # relocation fields aside)
                    try:
                        code, rel = c.function_bytes(ts)
                        im = _img.read(tgt, len(code))
                    except Exception:
                        continue
                    mask = set()
                    for roff, _rn, _rt in rel:
                        mask.update(range(roff, roff + 4))
                    if len(code) and all(code[j] == im[j] for j in range(len(code)) if j not in mask):
                        by_slot[tgt].append(tn)
    # (only where the row's own function was not in the previous link: a name it dropped)
    prev_map_names = set()
    if os.path.exists(_PREV_MAP):
        for l in anonfix.lines(_PREV_MAP, encoding=None, errors='replace'):
            m = re.match(r'^\s*0001:[0-9a-f]{8}\s+(\S+)\s+[0-9a-f]{8}', l)
            if m:
                prev_map_names.add(m.group(1))
    for a, o, n in sorted((int(q[0], 16), q[1], q[2]) for q in
                          (l.split() for l in anonfix.lines('config/compiled.txt'))
                          if len(q) >= 3 and q[0].startswith('0x')):
        if a < ORDER_END and not n.startswith('__ehhandler$') and not n.startswith('$') \
                and not re.search(r'(-0x[0-9A-Fa-f]+|>\d.*)$', n):
            if n[:1] not in '_?@':
                cand = [x for x in external_names(o) if x == '_' + n or x.startswith('?' + n + '@')]
                if len(cand) != 1:
                    continue
                n = cand[0]
            elif n not in external_names(o) and n not in cdz_map:
                continue        # a static or another object's copy: not orderable by name
            # inside a section made a COMDAT: the section's name (the row's object's section,
            # when that object packaged it; another object may hold a copy too)
            _static = n in static_names(o)
            # (a member linked as its repacked stand-in: that copy's packaged names)
            if o not in cdz_of and _repack.get(o) in cdz_of:
                n = cdz_of[_repack[o]].get(n, n)
            elif o in cdz_of:
                n = cdz_of[o].get(n, n)
            else:
                n = cdz_map.get(n, n)
            if _static:
                row_order_name[a] = n
            if n not in seen:
                seen.add(n)
                names.append(n)
            # the functions /OPT:ICF folds into this one (the sources' `// NAME (folded into
            # 0xADDR)` and `// symbol: NAME = 0xADDR` lines): next to it, so whichever copy the
            # link keeps sits where the image has the body
            for f in folded.get(a, ()):
                # (the row's own object's definition when it has one: memoryhandler's
                # operator new[], not a CRT member's packaged copy of the name)
                if f in external_names(o) and not o.endswith('_asm.obj'):
                    f = cdz_of[o].get(f, f) if o in cdz_of else f
                else:
                    f = cdz_map.get(f, f)
                if f not in seen:
                    seen.add(f)
                    names.append(f)
            for f in by_reloc.get(a, ()):
                f = cdz_map.get(f, f)
                if f not in seen and n not in prev_map_names:
                    seen.add(f)
                    names.append(f)
            for f in by_slot.get(a, ()):
                f = cdz_map.get(f, f)
                if f not in seen:
                    seen.add(f)
                    names.append(f)
    # /OPT:ICF groups (symbols sharing an address in the previous link's map): every member next
    # to the listed one, so whichever copy the link keeps sits where the image has the group
    # (a library member's too: _XMemFree@8, xapilib's, folds with xmem.obj's XMemFreeDefault)
    groups = collections.defaultdict(list)
    mp = _PREV_MAP
    if os.path.exists(mp):
        for l in anonfix.lines(mp, encoding=None, errors='replace'):
            m = re.match(r'^\s*[0-9a-f]{4}:[0-9a-f]{8}\s+(\S+)\s+([0-9a-f]{8})\s+(.*)$', l)
            if m:
                groups[int(m.group(2), 16)].append(m.group(1))
    member_of = {}
    for a, ms in groups.items():
        if len(ms) > 1:
            for x in ms:
                member_of[x] = ms
    full = []
    for n in names:
        for x in member_of.get(n, [n]):
            x = x if x == n else cdz_map.get(x, x)
            if x not in seen or x == n:
                seen.add(x)
                full.append(x)
    names = list(dict.fromkeys(full))
    # (each row's name in the order file, for shiftcount.py: a static's packaged name)
    with open(os.path.join(out, 'ordernames.txt'), 'w') as f_:
        for a_, n_ in sorted(row_order_name.items()):
            f_.write('0x%08X %s\n' % (a_, n_))
    of = os.path.join(out, 'order.txt')
    # link adds the C prefix itself: a C name is listed without its leading underscore
    open(of, 'w').write('\n'.join(n[1:] if n.startswith('_') else n for n in names) + '\n')
    cmd.insert(-1, '/ORDER:@' + of)
if os.environ.get('M7VERBOSE'):
    cmd.insert(-1, '/VERBOSE')
r = subprocess.run(cmd, env=env, capture_output=True, text=True)
txt = r.stdout + r.stderr
open(os.path.join(out, 'link.log'), 'w').write(txt)
print(collections.Counter(re.findall(r'(LNK\d+)', txt)).most_common(10))
names = set()
for l in txt.splitlines():
    m = re.search(r'unresolved external symbol (.*?)(?: referenced in function .*)?$', l)
    if m:
        s = m.group(1).strip()
        d = re.findall(r'\((\S+)\)$', s)
        names.add(d[-1] if d else s)
open(os.path.join(out, 'unresolved.txt'), 'w').write('\n'.join(sorted(names)) + '\n')
print(len(names), 'unique unresolved (build/m7/unresolved.txt)')
# (a forced fold whose name came out unresolved, its target defined nowhere outside its object:
# left to link.exe next time, build/m7/badfolds.txt)
_bad = set(n for n in names if n in _fold_pairs)
if _bad:
    _bfp = os.path.join(out, 'badfolds.txt')
    _old = set(l.strip() for l in open(_bfp)) if os.path.exists(_bfp) else set()
    open(_bfp, 'w').write('\n'.join(sorted(_old | _bad)) + '\n')
