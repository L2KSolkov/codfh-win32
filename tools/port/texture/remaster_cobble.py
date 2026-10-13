"""Usage: python remaster_cobble.py <dumped.tga> <out.tga> <preview.png> [scale]

Remaster a tiling cobblestone (or brick, paving) texture in pure Python: a wrapping bicubic
upscale; the stones told from their mortar joints by their luminance against the local mean;
a height map from that, blurred, lit from the top left to bevel each stone; fine grain on the
stones' faces and darker, grainier joints; a light sharpening. Multiplying the colour by one
factor keeps the original's hues.
"""
import math
import os
import random
import sys
import time

sys.path.insert(0, os.path.dirname(__file__))
from teximg import read_tga, write_tga, write_png  # noqa: E402

src, dst, preview = sys.argv[1], sys.argv[2], sys.argv[3]
S = int(sys.argv[4]) if len(sys.argv) > 4 else 4
t0 = time.time()
w, h, px = read_tga(src)
W, H = w * S, h * S
R = [p[0] for p in px]
G = [p[1] for p in px]
B = [p[2] for p in px]


def cubic_weights(t):
    t2, t3 = t * t, t * t * t
    return (-0.5 * t3 + t2 - 0.5 * t, 1.5 * t3 - 2.5 * t2 + 1.0, -1.5 * t3 + 2.0 * t2 + 0.5 * t, 0.5 * t3 - 0.5 * t2)


def make_taps(n_out, n_in):
    taps = []
    for i in range(n_out):
        f = (i + 0.5) / S - 0.5
        x0 = math.floor(f)
        taps.append(([(x0 - 1 + k) % n_in for k in range(4)], cubic_weights(f - x0)))
    return taps


tx, ty = make_taps(W, w), make_taps(H, h)


def upscale(ch):
    mid = [0.0] * (W * h)
    for y in range(h):
        row = ch[y * w:(y + 1) * w]
        o = y * W
        for x in range(W):
            idx, wt = tx[x]
            mid[o + x] = row[idx[0]] * wt[0] + row[idx[1]] * wt[1] + row[idx[2]] * wt[2] + row[idx[3]] * wt[3]
    out = [0.0] * (W * H)
    for y in range(H):
        idx, wt = ty[y]
        r0, r1, r2, r3 = idx[0] * W, idx[1] * W, idx[2] * W, idx[3] * W
        o = y * W
        for x in range(W):
            out[o + x] = mid[r0 + x] * wt[0] + mid[r1 + x] * wt[1] + mid[r2 + x] * wt[2] + mid[r3 + x] * wt[3]
    return out


def box(a, r):
    """A (2r+1)-wide box blur, wrapping, through running sums."""
    tmp = [0.0] * (W * H)
    n = 2 * r + 1
    for y in range(H):
        o = y * W
        s = sum(a[o + (x % W)] for x in range(-r, r + 1))
        for x in range(W):
            tmp[o + x] = s / n
            s += a[o + (x + r + 1) % W] - a[o + (x - r) % W]
    out = [0.0] * (W * H)
    for x in range(W):
        s = sum(tmp[(y % H) * W + x] for y in range(-r, r + 1))
        for y in range(H):
            out[y * W + x] = s / n
            s += tmp[((y + r + 1) % H) * W + x] - tmp[((y - r) % H) * W + x]
    return out


UR, UG, UB = upscale(R), upscale(G), upscale(B)
L = [0.299 * UR[i] + 0.587 * UG[i] + 0.114 * UB[i] for i in range(W * H)]
print('upscaled %dx%d in %.1fs' % (W, H, time.time() - t0))

# the stones against the joints: luminance above a darker share of the local mean (a joint is a
# thin dark line, so a mean over a few joints' widths sees mostly stone)
mean = box(L, 3 * S)
small = box(L, S // 2 or 1)
stone = [0.0] * (W * H)
for i in range(W * H):
    m = mean[i] if mean[i] > 1.0 else 1.0
    v = (small[i] / m - 0.72) / 0.18     # 0.72 of the mean or less: joint; 0.90 or more: stone
    v = 0.0 if v < 0.0 else 1.0 if v > 1.0 else v
    stone[i] = v * v * (3.0 - 2.0 * v)
# the height: the stone mask rounded (blurred twice), so each stone domes from its edges
height = box(box(stone, S), S)
print('stones and height in %.1fs' % (time.time() - t0))

rnd = random.Random(1943)


def fbm(octaves):
    out = [0.0] * (W * H)
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


grain = fbm([(256, 0.55), (128, 0.30), (64, 0.15)])
print('grain in %.1fs' % (time.time() - t0))

LB = box(L, 1)
out = []
for y in range(H):
    for x in range(W):
        i = y * W + x
        # the bevel: the height's slope against the light from the top left
        gx = height[y * W + (x + 1) % W] - height[y * W + (x - 1) % W]
        gy = height[((y + 1) % H) * W + x] - height[((y - 1) % H) * W + x]
        light = 1.0 - 1.3 * (gx + gy)          # facing up-left: lighter; down-right: darker
        s = stone[i]
        l = L[i] if L[i] > 1.0 else 1.0
        sharp = (l + 0.8 * (L[i] - LB[i])) / l
        tex = 1.0 + grain[i] * (0.07 * s + 0.12 * (1.0 - s))
        joint = 1.0 - 0.18 * (1.0 - s)
        f = sharp * tex * joint * light
        out.append((max(0, min(255, int(UR[i] * f + 0.5))), max(0, min(255, int(UG[i] * f + 0.5))),
                    max(0, min(255, int(UB[i] * f + 0.5))), 255))
write_tga(dst, W, H, out)
write_png(preview, W, H, out)
print('done in %.1fs: %s' % (time.time() - t0, dst))
