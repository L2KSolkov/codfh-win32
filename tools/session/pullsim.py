"""pullsim.py [RSP]: simulate link 7.10's library pulls for a response file (default
build/m7/link.rsp, m7probe's) and print each library's members in pull order, next to the
order build/m7/game.map shows (PLAN M7: fit the original library order).

Model (pulltest.py, pulltest2.py): the undefined externals form one queue, the explicit
objects' first (link order; within an object, symbol-table order). Each library in turn walks
the queue from the start: an unresolved name the library defines pulls its member, whose
defined names resolve and whose undefined names join the end of the queue. After the last
library the libraries are searched again while that pulls anything."""
import collections
import os
import re
import struct
import sys

ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
LIBDIR = r'C:\XDK\xbox\lib'


def coff_syms(d):
    """(defined, undefined) external names of a COFF object, in symbol-table order."""
    machine, nsec, _, symptr, nsyms, _, _ = struct.unpack_from('<HHIIIHH', d, 0)
    if machine != 0x14C or symptr == 0:
        return [], []
    strtab = symptr + nsyms * 18
    dfn, und = [], []
    i = 0
    while i < nsyms:
        o = symptr + i * 18
        raw = d[o:o + 8]
        value, secno, typ, cls, naux = struct.unpack_from('<IhHBB', d, o + 8)
        if cls == 2 or cls == 105:
            if raw[:4] == b'\0\0\0\0':
                so = struct.unpack_from('<I', raw, 4)[0]
                n = d[strtab + so:d.index(b'\0', strtab + so)].decode('latin-1')
            else:
                n = raw.rstrip(b'\0').decode('latin-1')
            if secno > 0 or (secno == 0 and value > 0):
                dfn.append(n)
            elif secno == 0:
                und.append(n)
        i += 1 + naux
    return dfn, und


def archive(path):
    """[(member name, defined, undefined)] of a .lib, in archive order."""
    d = open(path, 'rb').read()
    assert d[:8] == b'!<arch>\n', path
    pos, out, longnames = 8, [], b''
    while pos + 60 <= len(d):
        hdr = d[pos:pos + 60]
        name = hdr[:16].decode('latin-1').strip()
        size = int(hdr[48:58].decode().strip())
        body = d[pos + 60:pos + 60 + size]
        if name == '//':
            longnames = body
        elif name != '/':
            if name.startswith('/') and name[1:].isdigit():
                k = int(name[1:])
                name = longnames[k:longnames.index(b'\0' if b'\0' in longnames[k:] else b'\n', k)].decode('latin-1')
            name = name.rstrip('/')
            if len(body) >= 20 and struct.unpack_from('<H', body, 0)[0] == 0x14C:
                dfn, und = coff_syms(body)
                out.append((name, dfn, und))
        pos += 60 + size + (size & 1)
    return out


def main():
    rsp = sys.argv[1] if len(sys.argv) > 1 else os.path.join(ROOT, 'build', 'm7', 'link.rsp')
    objs, libs = [], []
    for l in open(rsp):
        l = l.strip().strip('"')
        if not l:
            continue
        if l.lower().endswith('.lib'):
            libs.append(l if os.path.isabs(l) else os.path.join(LIBDIR, l))
        else:
            objs.append(l)
    defined = set()
    queue = []
    origin = {}
    for o in objs:
        dfn, und = coff_syms(open(o, 'rb').read())
        defined.update(dfn)
        queue.extend(und)
        for s in und:
            origin.setdefault(s, os.path.basename(o))
    why = os.environ.get('WHY', '').lower()
    members = [archive(l) for l in libs]
    index = []
    for ms in members:
        idx = {}
        for k, (n, dfn, und) in enumerate(ms):
            for s in dfn:
                idx.setdefault(s, k)
        index.append(idx)
    pulled = [[] for _ in libs]
    taken = [set() for _ in libs]
    changed = True
    while changed:
        changed = False
        for li in range(len(libs)):
            i = 0
            while i < len(queue):
                s = queue[i]
                if s not in defined and s in index[li]:
                    k = index[li][s]
                    if k not in taken[li]:
                        taken[li].add(k)
                        pulled[li].append(members[li][k][0])
                        defined.update(members[li][k][1])
                        queue.extend(members[li][k][2])
                        for x in members[li][k][2]:
                            origin.setdefault(x, os.path.basename(libs[li]) + ':' + os.path.basename(members[li][k][0]))
                        changed = True
                        if why and why in os.path.basename(libs[li]).lower():
                            print('  pull %-14s by %s (queue %d, from %s)' % (os.path.basename(members[li][k][0]), s, i, origin.get(s)))
                i += 1
    # the map's order per library
    seen = collections.defaultdict(list)
    for l in open(os.path.join(ROOT, 'build', 'm7', 'game.map'), errors='replace'):
        m = re.match(r'^\s*([0-9a-f]{4}):([0-9a-f]{8})\s+(\S+)\s+([0-9a-f]{8})\s+(.*)$', l)
        if m and ':' in m.group(5).split()[-1]:
            lib, mem = m.group(5).split()[-1].split(':', 1)
            seen[lib.lower()].append((int(m.group(1), 16), int(m.group(4), 16), mem.lower()))
    if os.environ.get('IMG'):
        # IMG=1: the image's order instead of the map's: compiled.txt rows of the library's
        # members (build/xdk/LIB/obj_i386_M.obj, xdklib_LIB, or ours by the library m7probe
        # builds), by section and median address
        secs = [(0, 0x2F0000), (0x2F0000, 0x3C0000), (0x3C0000, 1 << 32)]
        seen = collections.defaultdict(list)
        ours = {}
        for l in libs:
            rspf = os.path.splitext(l)[0] + '.rsp'
            if os.path.exists(rspf):
                for x in open(rspf):
                    ours[os.path.basename(x.strip().strip('"')).lower()] = os.path.splitext(os.path.basename(l))[0].lower()
        for l in open(os.path.join(ROOT, 'config', 'compiled.txt'), encoding='utf-8'):
            q = l.split()
            if len(q) < 3 or not q[0].startswith('0x'):
                continue
            a = int(q[0], 16)
            base = os.path.basename(q[1]).lower()
            if q[1].startswith('build/xdk/'):
                lib = q[1].split('/')[2].replace('xdklib_', '')
                mem = base[len('obj_i386_'):] if base.startswith('obj_i386_') else base
            elif base in ours:
                lib, mem = ours[base], base
            else:
                continue
            # image sections: .text up to the library sections, which each sort apart
            sec = next(k for k, (lo, hi) in enumerate(secs) if lo <= a < hi)
            seen[lib].append((sec, a, mem))
    for li, l in enumerate(libs):
        stem = os.path.splitext(os.path.basename(l))[0].lower()
        sim = [os.path.splitext(os.path.basename(p.replace('\\', '/')))[0].lower() for p in pulled[li]]
        # a member's place: the median of its addresses in its first section (members laid
        # out in other sections, XPP's or D3D's, sort by section, and an /OPT:ICF survivor
        # placed at another member's copy would drag a minimum)
        addrs = collections.defaultdict(list)
        for sec, a, mem in seen.get(stem, []):
            addrs[os.path.splitext(os.path.basename(mem.replace('\\', '/')))[0]].append((sec, a))
        first = {}
        for m_, v in addrs.items():
            sec0 = min(v)[0]
            w = sorted(a for s, a in v if s == sec0)
            first[m_] = (sec0, w[len(w) // 2])
        mp = [m for m, a in sorted(first.items(), key=lambda x: x[1])]
        ok = [m for m in sim if m in first] == mp
        print('== %s: %d pulled%s' % (stem, len(sim), '' if ok else ' (map differs)'))
        if not ok or os.environ.get('V'):
            print('   sim:', ' '.join(sim[:60]))
            print('   map:', ' '.join(mp[:60]))


main()
