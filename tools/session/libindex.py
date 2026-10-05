"""libindex.py LIB NAME...: which archive member a library's symbol index gives for each NAME
(PLAN M7). The linker loads that member to resolve NAME; a symbol many members define (a
COMDAT build-number variable, .XBLD$V) loads whichever one the index names, so a rebuilt
archive whose index names another member loads other data than the original link did.
Prints NAME, the member's offset, its position among the archive's members and its name."""
import re
import struct
import sys


def read(path):
    d = open(path, 'rb').read()
    assert d[:8] == b'!<arch>\n'
    pos = 8
    heads = []
    while pos + 60 <= len(d):
        name = d[pos:pos + 16].decode('latin-1').rstrip()
        size = int(d[pos + 48:pos + 58])
        heads.append((pos, name, size))
        pos += 60 + size + (size & 1)
    longnames = b''
    for p, n, s in heads[:3]:
        if n == '//':
            longnames = d[p + 60:p + 60 + s]
    # second linker member: member offsets, then (symbol count, member index (1-based), names)
    p2, n2, s2 = heads[1]
    body = d[p2 + 60:p2 + 60 + s2]
    nm = struct.unpack_from('<I', body, 0)[0]
    offs = struct.unpack_from('<%dI' % nm, body, 4)
    ns = struct.unpack_from('<I', body, 4 + 4 * nm)[0]
    idx = struct.unpack_from('<%dH' % ns, body, 8 + 4 * nm)
    names = body[8 + 4 * nm + 2 * ns:].split(b'\0')[:ns]
    # (positions in archive order: the offsets table need not be)
    order = {p: i for i, p in enumerate(p for p, n, s in heads if n not in ('/', '//'))}

    def member_name(off):
        n = d[off:off + 16].decode('latin-1').rstrip()
        if n.startswith('/') and n[1:].rstrip('/').isdigit():
            k = int(n[1:].rstrip('/'))
            return longnames[k:longnames.index(b'\0', k) if b'\0' in longnames[k:] else len(longnames)].decode(
                'latin-1').split('/\n')[0].rstrip('/')
        return n.rstrip('/')
    out = {}
    for s, i in zip(names, idx):
        off = offs[i - 1]
        out.setdefault(s.decode('latin-1'), []).append((off, order[off], member_name(off)))
    return out


def fix(target, original):
    """Rewrites the symbol index of the archive TARGET (rebuilt from ORIGINAL's members, in
    ORIGINAL's order) so each symbol names the member at the position ORIGINAL's index gives
    it (both linker members). Returns the count of symbols changed."""
    want = dict((n, v[0][1]) for n, v in read(original).items())
    d = bytearray(open(target, 'rb').read())
    pos = 8
    heads = []
    while pos + 60 <= len(d):
        name = d[pos:pos + 16].decode('latin-1').rstrip()
        size = int(d[pos + 48:pos + 58])
        heads.append((pos, name, size))
        pos += 60 + size + (size & 1)
    # (TARGET's members by their file names, mNNNN.obj: NNNN is the position in ORIGINAL;
    # lib.exe does not write them in the response file's order)
    longnames = b''
    for p, n, s in heads[:3]:
        if n == '//':
            longnames = bytes(d[p + 60:p + 60 + s])
    members = {}
    for p, n, s in heads:
        if n in ('/', '//'):
            continue
        if n.startswith('/') and n[1:].rstrip('/').isdigit():
            k = int(n[1:].rstrip('/'))
            e = longnames.find(b'\0', k)
            n = longnames[k:e if e >= 0 else len(longnames)].decode('latin-1')
        m = re.search(r'm(\d{4})\.obj', n, re.I)
        if m:
            members[int(m.group(1))] = p
    changed = 0
    # second linker member
    p2 = heads[1][0] + 60
    nm = struct.unpack_from('<I', d, p2)[0]
    offs = list(struct.unpack_from('<%dI' % nm, d, p2 + 4))
    ns = struct.unpack_from('<I', d, p2 + 4 + 4 * nm)[0]
    io = p2 + 8 + 4 * nm
    names = bytes(d[io + 2 * ns:io + 2 * ns + heads[1][2]]).split(b'\0')[:ns]
    newoff = {}
    for k, s in enumerate(names):
        s = s.decode('latin-1')
        if s in want and want[s] in members:
            cur = offs[struct.unpack_from('<H', d, io + 2 * k)[0] - 1]
            tgt = members[want[s]]
            if cur != tgt and tgt in offs:
                struct.pack_into('<H', d, io + 2 * k, offs.index(tgt) + 1)
                newoff[s] = tgt
                changed += 1
    # first linker member: big-endian offsets per symbol
    p1 = heads[0][0] + 60
    n1 = struct.unpack_from('>I', d, p1)[0]
    names1 = bytes(d[p1 + 4 + 4 * n1:p1 + heads[0][2]]).split(b'\0')[:n1]
    for k, s in enumerate(names1):
        s = s.decode('latin-1')
        if s in newoff:
            struct.pack_into('>I', d, p1 + 4 + 4 * k, newoff[s])
    if changed:
        open(target, 'wb').write(bytes(d))
    return changed


if __name__ == '__main__':
    t = read(sys.argv[1])
    for n in sys.argv[2:]:
        for off, i, mn in t.get(n, []):
            print(n, hex(off), i, mn)
