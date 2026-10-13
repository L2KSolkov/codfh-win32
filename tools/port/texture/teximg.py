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


def read_png(path):
    """An 8-bit RGB or RGBA, non-interlaced PNG: (w, h, [(r, g, b, a), ...])."""
    d = open(path, 'rb').read()
    assert d[:8] == b'\x89PNG\r\n\x1a\n'
    pos, idat, w = 8, b'', 0
    while pos < len(d):
        n = struct.unpack('>I', d[pos:pos + 4])[0]
        t = d[pos + 4:pos + 8]
        body = d[pos + 8:pos + 8 + n]
        if t == b'IHDR':
            w, h, depth, ctype, _, _, inter = struct.unpack('>IIBBBBB', body)
            assert depth == 8 and ctype in (2, 6) and inter == 0, (depth, ctype, inter)
        elif t == b'IDAT':
            idat += body
        pos += 12 + n
    bpp = 4 if ctype == 6 else 3
    raw = zlib.decompress(idat)
    stride = w * bpp
    prev = bytearray(stride)
    px = []
    o = 0
    for y in range(h):
        f = raw[o]
        line = bytearray(raw[o + 1:o + 1 + stride])
        o += 1 + stride
        if f == 1:
            for i in range(bpp, stride):
                line[i] = (line[i] + line[i - bpp]) & 0xFF
        elif f == 2:
            for i in range(stride):
                line[i] = (line[i] + prev[i]) & 0xFF
        elif f == 3:
            for i in range(stride):
                left = line[i - bpp] if i >= bpp else 0
                line[i] = (line[i] + ((left + prev[i]) >> 1)) & 0xFF
        elif f == 4:
            for i in range(stride):
                a = line[i - bpp] if i >= bpp else 0
                b = prev[i]
                c = prev[i - bpp] if i >= bpp else 0
                p = a + b - c
                pa, pb, pc = abs(p - a), abs(p - b), abs(p - c)
                pr = a if pa <= pb and pa <= pc else b if pb <= pc else c
                line[i] = (line[i] + pr) & 0xFF
        for x in range(w):
            k = x * bpp
            px.append((line[k], line[k + 1], line[k + 2], line[k + 3] if bpp == 4 else 255))
        prev = line
    return w, h, px
