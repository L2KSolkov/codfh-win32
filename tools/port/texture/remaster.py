"""Usage: python remaster.py <dumped.tga> <out.tga> <preview.png>

Remaster a tiling ground texture 4x in pure Python: bicubic upscale (wrapping), unsharp mask,
fine luminance grain (tiling fBm), and shaded pebbles drawn with wrap-around."""
import math
import random
import sys
import time

sys.path.insert(0, __import__('os').path.dirname(__file__))
from teximg import read_tga, write_tga, write_png  # noqa: E402

src, dst, preview = sys.argv[1], sys.argv[2], sys.argv[3]
S = 4
t0 = time.time()
w, h, px = read_tga(src)
W, H = w * S, h * S
R = [p[0] for p in px]
G = [p[1] for p in px]
B = [p[2] for p in px]
A = [p[3] for p in px]


def cubic_weights(t):
    # Catmull-Rom
    t2, t3 = t * t, t * t * t
    return (-0.5 * t3 + t2 - 0.5 * t, 1.5 * t3 - 2.5 * t2 + 1.0, -1.5 * t3 + 2.0 * t2 + 0.5 * t, 0.5 * t3 - 0.5 * t2)


taps = []
for i in range(W):
    f = (i + 0.5) / S - 0.5
    x0 = math.floor(f)
    wts = cubic_weights(f - x0)
    taps.append(([(x0 - 1 + k) % w for k in range(4)], wts))


def upscale(ch):
    # rows: w -> W
    mid = [0.0] * (W * h)
    for y in range(h):
        row = ch[y * w:(y + 1) * w]
        o = y * W
        for x in range(W):
            idx, wt = taps[x]
            mid[o + x] = row[idx[0]] * wt[0] + row[idx[1]] * wt[1] + row[idx[2]] * wt[2] + row[idx[3]] * wt[3]
    # columns: h -> H (h == w here; taps reused when square)
    out = [0.0] * (W * H)
    for y in range(H):
        idx, wt = taps[y] if H == W else taps[y]
        r0, r1, r2, r3 = idx[0] * W, idx[1] * W, idx[2] * W, idx[3] * W
        o = y * W
        for x in range(W):
            out[o + x] = mid[r0 + x] * wt[0] + mid[r1 + x] * wt[1] + mid[r2 + x] * wt[2] + mid[r3 + x] * wt[3]
    return out


UR, UG, UB = upscale(R), upscale(G), upscale(B)
print('upscaled %dx%d in %.1fs' % (W, H, time.time() - t0))

# luminance of the upscale, and a 3x3 box blur of it (wrapping) for the unsharp mask
L = [0.299 * UR[i] + 0.587 * UG[i] + 0.114 * UB[i] for i in range(W * H)]


def box3(a):
    tmp = [0.0] * (W * H)
    for y in range(H):
        o = y * W
        for x in range(W):
            tmp[o + x] = (a[o + (x - 1) % W] + a[o + x] + a[o + (x + 1) % W]) / 3.0
    out = [0.0] * (W * H)
    for y in range(H):
        o, om, op = y * W, ((y - 1) % H) * W, ((y + 1) % H) * W
        for x in range(W):
            out[o + x] = (tmp[om + x] + tmp[o + x] + tmp[op + x]) / 3.0
    return out


LB = box3(L)
print('blurred in %.1fs' % (time.time() - t0))

# tiling value-noise fBm (periods that divide W)
rnd = random.Random(1944)


def make_lattice(n):
    return [rnd.random() * 2.0 - 1.0 for _ in range(n * n)]


octaves = [(128, 0.45), (64, 0.30), (32, 0.18), (16, 0.10), (8, 0.06)]  # cells across W, amplitude
lattices = [(n, amp, make_lattice(n)) for n, amp in octaves]
noise = [0.0] * (W * H)
for n, amp, lat in lattices:
    cell = W / n
    sx = []
    for x in range(W):
        fx = x / cell
        ix = int(fx)
        tx = fx - ix
        tx = tx * tx * (3 - 2 * tx)
        sx.append((ix % n, (ix + 1) % n, tx))
    for y in range(H):
        fy = y / cell
        iy = int(fy)
        ty = fy - iy
        ty = ty * ty * (3 - 2 * ty)
        r0, r1 = (iy % n) * n, ((iy + 1) % n) * n
        o = y * W
        for x in range(W):
            a, b, tx = sx[x]
            v0 = lat[r0 + a] + (lat[r0 + b] - lat[r0 + a]) * tx
            v1 = lat[r1 + a] + (lat[r1 + b] - lat[r1 + a]) * tx
            noise[o + x] += amp * (v0 + (v1 - v0) * ty)
print('noise in %.1fs' % (time.time() - t0))

# the final luminance factor per pixel: unsharp mask and grain (multiplying RGB keeps the hue)
fac = [1.0] * (W * H)
for i in range(W * H):
    l = L[i] if L[i] > 1.0 else 1.0
    sharp = l + 0.9 * (L[i] - LB[i])
    fac[i] = sharp / l * (1.0 + 0.10 * noise[i])

# pebbles: soft discs, lit from the top left (a light rim up-left, a dark rim down-right), plus
# a faint contact shadow; drawn into a factor map with wrap-around
peb = [0.0] * (W * H)
for k in range(3200):
    cx, cy = rnd.random() * W, rnd.random() * H
    r = rnd.choice((1.2, 1.5, 1.8, 2.2, 2.6, 3.2, 4.0))
    tone = rnd.uniform(-0.18, 0.10)
    ext = int(r + 3)
    for dy in range(-ext, ext + 1):
        for dx in range(-ext, ext + 1):
            px_ = int(cx) + dx
            py_ = int(cy) + dy
            ox, oy = px_ + 0.5 - cx, py_ + 0.5 - cy
            d = math.sqrt(ox * ox + oy * oy)
            i = (py_ % H) * W + (px_ % W)
            if d < r:
                # the stone: its tone, shaded by the light from the top left
                nx, ny = ox / r, oy / r
                shade = -(nx + ny) * 0.16
                edge = d / r
                peb[i] += (tone + shade) * (1.0 - edge * edge * 0.5)
            elif d < r + 1.6 and ox + oy > 0:
                # its shadow on the ground, down-right
                peb[i] -= 0.10 * (1.0 - (d - r) / 1.6)
print('pebbles in %.1fs' % (time.time() - t0))

out = []
for i in range(W * H):
    f = fac[i] * (1.0 + peb[i])
    out.append((max(0, min(255, int(UR[i] * f + 0.5))), max(0, min(255, int(UG[i] * f + 0.5))),
                max(0, min(255, int(UB[i] * f + 0.5))), 255))
write_tga(dst, W, H, out)
write_png(preview, W, H, out)
print('done in %.1fs: %s' % (time.time() - t0, dst))
