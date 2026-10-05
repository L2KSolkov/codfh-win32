"""objalias.py OBJ OUT: copy the object OBJ to OUT with the extra external symbols
config/objaliases.txt gives it (PLAN M7 link).

Bink's transcribed functions call the C file's statics, whose VC7.0 register conventions
hold only while no assembly names them, so the transcriptions call them by other names
(config/aliases.txt). For the link each such name becomes an external symbol at its
static's place: config/objaliases.txt lines are `OBJ NAME TARGET` (TARGET a static of
OBJ; NAME may equal it). Prints the copies' names; exits 1 when a target is missing."""
import os
import struct
import sys

ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))


def aliases_for(obj):
    rel = os.path.relpath(os.path.abspath(obj), ROOT).replace(os.sep, '/')
    out = []
    for l in open(os.path.join(ROOT, 'config', 'objaliases.txt'), encoding='utf-8'):
        q = l.split('#')[0].split()
        if len(q) == 3 and q[0] == rel:
            out.append((q[1], q[2]))
    return out


def patch(obj, out, pairs):
    d = open(obj, 'rb').read()
    machine, nsec, stamp, symptr, nsyms, optsize, chars = struct.unpack_from('<HHIIIHH', d, 0)
    strtab = symptr + nsyms * 18
    strsize = struct.unpack_from('<I', d, strtab)[0]
    strings = bytearray(d[strtab + 4:strtab + strsize])

    def name_of(raw):
        if raw[:4] == b'\0\0\0\0':
            o = struct.unpack_from('<I', raw, 4)[0] - 4
            return bytes(strings[o:strings.index(b'\0', o)]).decode('latin-1')
        return raw.rstrip(b'\0').decode('latin-1')

    statics, externs = {}, set()
    i = 0
    while i < nsyms:
        raw = d[symptr + i * 18:symptr + i * 18 + 8]
        value, secno, typ, cls, naux = struct.unpack_from('<IhHBB', d, symptr + i * 18 + 8)
        n = name_of(raw)
        if cls == 3 and secno > 0:
            statics[n] = (value, secno, typ)
        elif cls == 2 and secno > 0:
            externs.add(n)
        i += 1 + naux
    new = b''
    for name, target in pairs:
        if name in externs:
            continue
        if target not in statics:
            print('%s: no static %s' % (obj, target))
            return False
        value, secno, typ = statics[target]
        enc = name.encode('latin-1')
        if len(enc) <= 8:
            raw = enc.ljust(8, b'\0')
        else:
            raw = struct.pack('<II', 0, len(strings) + 4)
            strings += enc + b'\0'
        new += raw + struct.pack('<IhHBB', value, secno, typ, 2, 0)
    head = struct.pack('<HHIIIHH', machine, nsec, stamp, symptr, nsyms + len(new) // 18, optsize, chars)
    body = head + d[20:strtab] + new + struct.pack('<I', len(strings) + 4) + bytes(strings)
    os.makedirs(os.path.dirname(out), exist_ok=True)
    open(out, 'wb').write(body)
    return True


if __name__ == '__main__':
    obj, out = sys.argv[1:3]
    sys.exit(0 if patch(obj, out, aliases_for(obj)) else 1)
