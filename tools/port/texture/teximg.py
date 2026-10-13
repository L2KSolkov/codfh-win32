"""TGA read/write and PNG write in pure Python (zlib only), for the texture remaster."""
import struct
import zlib


def read_tga(path):
    d = open(path, 'rb').read()
    idlen, cmtype, itype = d[0], d[1], d[2]
    w, h = struct.unpack_from('<HH', d, 12)
    bpp, desc = d[16], d[17]
    assert itype == 2 and bpp in (24, 32), (itype, bpp)
    n = bpp // 8
    off = 18 + idlen
    top = desc & 0x20
    px = []
    for y in range(h):
        row = (y if top else h - 1 - y) * w * n + off
        for x in range(w):
            p = row + x * n
            b, g, r = d[p], d[p + 1], d[p + 2]
            a = d[p + 3] if n == 4 else 255
            px.append((r, g, b, a))
    return w, h, px


def write_tga(path, w, h, px):
    hd = bytearray(18)
    hd[2] = 2
    struct.pack_into('<HH', hd, 12, w, h)
    hd[16] = 32
    hd[17] = 0x28
    out = bytearray(hd)
    for (r, g, b, a) in px:
        out += bytes((b, g, r, a))
    open(path, 'wb').write(out)


def write_png(path, w, h, px, alpha=False):
    raw = bytearray()
    for y in range(h):
        raw.append(0)
        for x in range(w):
            r, g, b, a = px[y * w + x]
            raw += bytes((r, g, b, a) if alpha else (r, g, b))

    def chunk(t, data):
        c = struct.pack('>I', len(data)) + t + data
        return c + struct.pack('>I', zlib.crc32(t + data) & 0xFFFFFFFF)

    png = b'\x89PNG\r\n\x1a\n' + chunk(b'IHDR', struct.pack('>IIBBBBB', w, h, 8, 6 if alpha else 2, 0, 0, 0))
    png += chunk(b'IDAT', zlib.compress(bytes(raw), 6)) + chunk(b'IEND', b'')
    open(path, 'wb').write(png)
