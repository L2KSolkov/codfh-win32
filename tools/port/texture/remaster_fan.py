"""Usage: python remaster_fan.py <dumped.tga> <out.tga> <preview.png> [scale, default 8] [fans across, default 2]

Rebuilds a fan (fish-scale) cobble texture at a higher resolution instead of upscaling it: the
original only gives the layout's proportions and the colours. Fans of radius R in rows R/2 apart
and 2R across, alternate rows offset by R, the arcs bulging up and each row laid over the one
above; inside a fan three courses and a key stone, cut into stones about as long as a course
is wide, with a hand-laid jitter. Joints from exact distances to the stones' edges; each stone
domed from its edge and chipped, lit from the top left with the joints'
occlusion; its colour the original's stone colour with the original's large light and dark
patches, its own brightness and hue, fine grain and pits; the mortar the original's darkest.
Everything repeats with the texture, so it tiles.
"""
import math
import os
import random
import sys
import time

sys.path.insert(0, os.path.dirname(__file__))
from teximg import read_tga, write_tga, write_png  # noqa: E402

src, dst, preview = sys.argv[1], sys.argv[2], sys.argv[3]
S = int(sys.argv[4]) if len(sys.argv) > 4 else 8
FANS = int(sys.argv[5]) if len(sys.argv) > 5 else 2
t0 = time.time()


def log(m):
    print('%6.1fs  %s' % (time.time() - t0, m))


w, h, px = read_tga(src)
W, H = w * S, h * S
N = W * H
P = W / FANS                 # fan spacing across
R = P / 2.0                  # fan radius, and the rows' spacing
Q = R / 2.0                  # the rows' spacing: half a radius, so a fan's centre lies under the fans below
ROWS = int(round(H / Q))     # rows in the texture (even, for the alternate offset to tile)
assert ROWS % 2 == 0, 'the rows must be even to tile: %d' % ROWS
NC = 3                       # courses per fan
CW = R * 0.27                # a course's width
KEY = R - NC * CW            # the key stone's radius
JW = 0.045 * CW              # half a joint's width
BEVEL = 0.22 * CW            # how far in from its edge a stone's dome rises
log('%dx%d: R %.0f, %d rows, courses %.0f wide, key %.0f' % (W, H, R, ROWS, CW, KEY))


def hrand(*k):
    """A repeatable random number in [0, 1) for the key k."""
    x = 0x9E3779B1
    for v in k:
        x = (x ^ (int(v) & 0xFFFFFFFF)) * 0x85EBCA6B & 0xFFFFFFFF
        x ^= x >> 13
        x = x * 0xC2B2AE35 & 0xFFFFFFFF
        x ^= x >> 16
    return x / 4294967296.0


# the colours: the stone colour (the original's lighter pixels' mean), the mortar's (its darkest),
# and its large light and dark patches (its luminance blurred, against its mean)
L0 = [0.299 * p[0] + 0.587 * p[1] + 0.114 * p[2] for p in px]
order = sorted(range(w * h), key=lambda i: L0[i])
dark = order[:len(order) // 10]
light = order[len(order) // 3:]
mortar = [sum(px[i][c] for i in dark) / len(dark) for c in range(3)]
stonec = [sum(px[i][c] for i in light) / len(light) for c in range(3)]
meanL = sum(L0) / len(L0)
r6 = 6
blur = [0.0] * (w * h)
for y in range(h):
    for x in range(w):
        s = 0.0
        for dy in range(-r6, r6 + 1, 2):
            for dx in range(-r6, r6 + 1, 2):
                s += L0[((y + dy) % h) * w + (x + dx) % w]
        blur[y * w + x] = s / ((r6 + 1) ** 2) / meanL
log('colours: stone %s, mortar %s' % ([int(v) for v in stonec], [int(v) for v in mortar]))


def patch(X, Y):
    """The original's large-scale brightness at output pixel (X, Y), bilinear and wrapping."""
    fx, fy = X / S - 0.5, Y / S - 0.5
    x0, y0 = math.floor(fx), math.floor(fy)
    tx, ty = fx - x0, fy - y0
    a = blur[(y0 % h) * w + x0 % w]
    b = blur[(y0 % h) * w + (x0 + 1) % w]
    c = blur[((y0 + 1) % h) * w + x0 % w]
    d = blur[((y0 + 1) % h) * w + (x0 + 1) % w]
    return (a + (b - a) * tx) * (1 - ty) + (c + (d - c) * tx) * ty


def ring_wobble(fan, k, th):
    """A course's edge radius wobbles a little along its length, hand-laid."""
    return CW * 0.06 * (math.sin(th * 3.0 + hrand(fan, k, 1) * 6.28) + 0.5 * math.sin(th * 7.0 + hrand(fan, k, 2) * 6.28))


def cell(X, Y):
    """The stone at (X, Y): (its key, the distance to the nearest joint); key None in a joint."""
    best = None
    for row in range(-3, ROWS + 4):
        cy = row * Q
        if cy < Y - R - 0.01 or cy > Y + R + 0.01:
            continue
        off = (row % 2) * R
        k = math.floor((X - off) / P + 0.5)
        for kk in (k - 1, k, k + 1):
            cx = off + kk * P
            dx, dy = X - cx, Y - cy
            r = math.hypot(dx, dy)
            if r <= R and (best is None or cy > best[1]):
                best = (cx, cy, r, dx, dy, row, kk)
    if best is None:
        return None, 0.0
    cx, cy, r, dx, dy, row, kk = best
    fan = (row % ROWS) * 64 + (kk % FANS)
    # the edge of the fan itself and of the fans laid over it (the next row down, either side)
    dmin = R - r
    for drow in (1, 2, 3):
        row2 = row + drow
        cy2 = row2 * Q
        off2 = (row2 % 2) * R
        for kk2 in range(math.floor((X - off2) / P) - 1, math.floor((X - off2) / P) + 3):
            d2 = math.hypot(X - (off2 + kk2 * P), Y - cy2) - R
            if d2 < dmin:
                dmin = d2
    th = math.atan2(dx, -dy)         # from straight up, -pi .. pi
    # the course, its edges wobbling
    depth = R - r
    if r < KEY:
        k = NC
        d_r = KEY - r
        n = 4
        a = (th + math.pi) / (2 * math.pi) * n
        j = int(math.floor(a))
        da = min(a - j, j + 1 - a) * 2 * math.pi / n * max(r, 1.0)
        return (fan, k, j % n), min(dmin, d_r, da)
    k = int(depth // CW)
    k = min(k, NC - 1)
    inner = R - (k + 1) * CW + (ring_wobble(fan, k + 1, th) if k + 1 < NC else 0.0)
    outer = R - k * CW + (ring_wobble(fan, k, th) if k > 0 else 0.0)
    if r > outer and k > 0:
        k -= 1
        inner, outer = outer, R - k * CW + (ring_wobble(fan, k, th) if k > 0 else 0.0)
    elif r < inner and k + 1 < NC:
        k += 1
        outer = inner
        inner = R - (k + 1) * CW + (ring_wobble(fan, k + 1, th) if k + 1 < NC else 0.0)
    d_r = min(r - max(inner, KEY), outer - r) if k < NC else r
    # the stones along the course: about as long as the course is wide, cut with a jitter, each
    # course's cuts shifted half a stone from the last
    rm = R - (k + 0.5) * CW
    n = max(3, int(round(2 * math.pi * rm / (CW * 1.05))))
    a = (th + math.pi) / (2 * math.pi) * n + 0.5 * (k % 2)
    j = int(math.floor(a))
    jit = lambda q: (hrand(fan, k, q) - 0.5) * 0.30
    lo, hi = j + jit(j), j + 1 + jit(j + 1)
    if a < lo:
        j -= 1
        lo, hi = j + jit(j), lo
    elif a > hi:
        j += 1
        lo, hi = hi, j + 1 + jit(j + 1)
    da = min(a - lo, hi - a) * 2 * math.pi / n * r
    return (fan, k, j % n), min(dmin, d_r, da)


# the height (a dome from each stone's edge, chipped by noise), the stones' keys
height = [0.0] * N
keys = [None] * N
dists = [0.0] * N
for Y in range(H):
    for X in range(W):
        key, d = cell(X + 0.5, Y + 0.5)
        i = Y * W + X
        if key is None:
            continue
        d -= JW
        dists[i] = d
        if d > 0:
            keys[i] = key
            t = d / (BEVEL * (0.8 + 0.4 * hrand(key[0], key[1], key[2], 7)))
            hgt = 1.0 if t >= 1.0 else 1.0 - (1.0 - t) * (1.0 - t)
            height[i] = hgt
    if Y % 256 == 0:
        log('row %d of %d' % (Y, H))
log('stones laid')

rnd = random.Random(1943)


def fbm(octaves):
    out = [0.0] * N
    for n, amp in octaves:
        nx, ny = max(1, round(n * W / max(W, H))), max(1, round(n * H / max(W, H)))
        lat = [rnd.random() * 2.0 - 1.0 for _ in range(nx * ny)]
        cx, cy = W / nx, H / ny
        sx = []
        for x in range(W):
            f = x / cx
            ix = int(f)
            t = f - ix
            sx.append((ix % nx, (ix + 1) % nx, t * t * (3 - 2 * t)))
        for y in range(H):
            f = y / cy
            iy = int(f)
            t = f - iy
            t = t * t * (3 - 2 * t)
            r0, r1 = (iy % ny) * nx, ((iy + 1) % ny) * nx
            o = y * W
            for x in range(W):
                a, b, u = sx[x]
                v0 = lat[r0 + a] + (lat[r0 + b] - lat[r0 + a]) * u
                v1 = lat[r1 + a] + (lat[r1 + b] - lat[r1 + a]) * u
                out[o + x] += amp * (v0 + (v1 - v0) * t)
    return out


m = max(W, H)
grain = fbm([(m // 3, 0.40), (m // 6, 0.30), (m // 12, 0.20), (m // 40, 0.10)])
log('grain')
# pits on the faces
pits = [0.0] * N
for _ in range(N // 220):
    cx, cy = rnd.random() * W, rnd.random() * H
    rr = rnd.choice((0.8, 1.0, 1.3, 1.7, 2.2)) * S / 4.0
    e = int(rr + 2)
    for dy in range(-e, e + 1):
        for dx in range(-e, e + 1):
            X, Y = int(cx) + dx, int(cy) + dy
            ox, oy = X + 0.5 - cx, Y + 0.5 - cy
            d = math.hypot(ox, oy)
            if d < rr:
                pits[(Y % H) * W + (X % W)] += -0.20 * (1.0 - d / rr) + 0.08 * max(0.0, (ox + oy) / (rr * 1.4)) * (d / rr)
log('pits')

# the light from the top left and above
lx, ly, lz = -0.5, -0.6, 0.62
ln = math.sqrt(lx * lx + ly * ly + lz * lz)
lx, ly, lz = lx / ln, ly / ln, lz / ln
SLOPE = 0.55 * BEVEL / 4.0
out = []
for Y in range(H):
    for X in range(W):
        i = Y * W + X
        key = keys[i]
        g = grain[i]
        if key is None:
            # the mortar: dark, sandy, deeper away from the stones' edges
            dd = -dists[i]
            f = 0.85 + 0.25 * g
            occl = 0.75 + 0.25 * min(1.0, dd / max(JW, 1.0))
            out.append(tuple(max(0, min(255, int(mortar[c] * f * occl))) for c in range(3)) + (255,))
            continue
        hx = height[Y * W + (X + 1) % W] - height[Y * W + (X - 1) % W]
        hy = height[((Y + 1) % H) * W + X] - height[((Y - 1) % H) * W + X]
        nx_, ny_ = -hx * SLOPE, -hy * SLOPE
        nl = math.sqrt(nx_ * nx_ + ny_ * ny_ + 1.0)
        shade = 1.0 + 0.7 * ((nx_ * lx + ny_ * ly + lz) / nl / lz - 1.0)
        ao = 0.80 + 0.20 * min(1.0, height[i])
        tone = 0.86 + 0.26 * hrand(key[0], key[1], key[2], 5)
        hue = (hrand(key[0], key[1], key[2], 6) - 0.5) * 0.06
        big = patch(X, Y) ** 1.25
        face = tone * big * (1.0 + 0.13 * g + pits[i]) * shade * ao
        col = (stonec[0] * (1 + hue), stonec[1], stonec[2] * (1 - hue))
        out.append(tuple(max(0, min(255, int(col[c] * face + 0.5))) for c in range(3)) + (255,))
write_tga(dst, W, H, out)
write_png(preview, W, H, out)
log('done: %s (%dx%d)' % (dst, W, H))
