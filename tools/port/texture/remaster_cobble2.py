"""Usage: python remaster_cobble2.py <dumped.tga> <out.tga> <preview.png> [scale, default 8]

A cobblestone (paving, brick) remaster that rebuilds the stones rather than only shading the
upscale, in pure Python, wrapping everywhere so the result still tiles:
  1. a bicubic upscale for the colour;
  2. the stones against the joints, by luminance against the local mean; dark specks inside a
     stone filled back in (joint pieces too small to be joints), stone crumbs dropped, and the
     outlines smoothed so the joints come out crisp and even;
  3. each stone labelled, its height its distance from the nearest joint (a dome from its edge),
     lit from the top left, with the joints' occlusion;
  4. each stone's own slight brightness, so the pattern reads as single stones;
  5. fine grain and small pits on the faces, darker grainy mortar in the joints.
"""
import math
import os
import random
import sys
import time
from collections import deque

sys.path.insert(0, os.path.dirname(__file__))
from teximg import read_tga, write_tga, write_png  # noqa: E402

src, dst, preview = sys.argv[1], sys.argv[2], sys.argv[3]
S = int(sys.argv[4]) if len(sys.argv) > 4 else 8
t0 = time.time()
rnd = random.Random(1943)
w, h, px = read_tga(src)
W, H = w * S, h * S
N = W * H


def log(msg):
    print('%6.1fs  %s' % (time.time() - t0, msg))


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
    out = [0.0] * N
    for y in range(H):
        idx, wt = ty[y]
        r0, r1, r2, r3 = idx[0] * W, idx[1] * W, idx[2] * W, idx[3] * W
        o = y * W
        for x in range(W):
            out[o + x] = mid[r0 + x] * wt[0] + mid[r1 + x] * wt[1] + mid[r2 + x] * wt[2] + mid[r3 + x] * wt[3]
    return out


def box(a, r):
    """A (2r+1)-wide box blur, wrapping, through running sums."""
    if r <= 0:
        return list(a)
    tmp = [0.0] * N
    n = 2 * r + 1
    for y in range(H):
        o = y * W
        s = sum(a[o + (x % W)] for x in range(-r, r + 1))
        for x in range(W):
            tmp[o + x] = s / n
            s += a[o + (x + r + 1) % W] - a[o + (x - r) % W]
    out = [0.0] * N
    for x in range(W):
        s = sum(tmp[(y % H) * W + x] for y in range(-r, r + 1))
        for y in range(H):
            out[y * W + x] = s / n
            s += tmp[((y + r + 1) % H) * W + x] - tmp[((y - r) % H) * W + x]
    return out


def neighbours(i):
    x, y = i % W, i // W
    return (y * W + (x + 1) % W, y * W + (x - 1) % W, ((y + 1) % H) * W + x, ((y - 1) % H) * W + x)


def label(mask, value):
    """4-connected components of the pixels where mask[i] == value (wrapping): labels (-1 elsewhere), sizes."""
    lab = [-1] * N
    sizes = []
    for start in range(N):
        if mask[start] != value or lab[start] >= 0:
            continue
        k = len(sizes)
        lab[start] = k
        q = deque([start])
        n = 0
        while q:
            i = q.popleft()
            n += 1
            for j in neighbours(i):
                if mask[j] == value and lab[j] < 0:
                    lab[j] = k
                    q.append(j)
        sizes.append(n)
    return lab, sizes


R = [p[0] for p in px]
G = [p[1] for p in px]
B = [p[2] for p in px]
UR, UG, UB = upscale(R), upscale(G), upscale(B)
L = [0.299 * UR[i] + 0.587 * UG[i] + 0.114 * UB[i] for i in range(N)]
log('upscaled %dx%d' % (W, H))

# 2. the stones (1) and joints (0)
mean = box(L, 3 * S)
small = box(L, max(1, S // 3))
joint_cut = 0.80
mask = [1 if small[i] > joint_cut * (mean[i] if mean[i] > 1.0 else 1.0) else 0 for i in range(N)]
# (joint pieces smaller than about a third of a source pixel's square at this scale are specks
# on a stone: stone; stone pieces smaller than a source pixel are crumbs: joint)
lab, sizes = label(mask, 0)
speck = S * S // 3 + 4
for i in range(N):
    if lab[i] >= 0 and sizes[lab[i]] < speck * 6:
        mask[i] = 1
lab, sizes = label(mask, 1)
for i in range(N):
    if lab[i] >= 0 and sizes[lab[i]] < S * S:
        mask[i] = 0
log('stones told from joints')
# the outlines smoothed: the mask blurred and cut again at its middle (a softened edge kept for
# anti-aliasing)
soft = box(box([float(m) for m in mask], max(1, S // 3)), max(1, S // 3))
edge = [0.0] * N
for i in range(N):
    v = (soft[i] - 0.38) / 0.24
    edge[i] = 0.0 if v < 0.0 else 1.0 if v > 1.0 else v * v * (3.0 - 2.0 * v)
mask = [1 if e > 0.5 else 0 for e in edge]
log('outlines smoothed')

# 3. each stone, and its distance from the joints (a chamfer transform, run twice around for
# the wrap)
lab, sizes = label(mask, 1)
BIG = 1e9
dist = [0.0 if m == 0 else BIG for m in mask]
a1, a2 = 1.0, 1.4142
for _ in range(2):
    for y in range(H):
        o, om = y * W, ((y - 1) % H) * W
        for x in range(W):
            i = o + x
            if dist[i] == 0.0:
                continue
            xl, xr = (x - 1) % W, (x + 1) % W
            d = dist[i]
            v = dist[o + xl] + a1
            d = v if v < d else d
            v = dist[om + x] + a1
            d = v if v < d else d
            v = dist[om + xl] + a2
            d = v if v < d else d
            v = dist[om + xr] + a2
            d = v if v < d else d
            dist[i] = d
    for y in range(H - 1, -1, -1):
        o, op = y * W, ((y + 1) % H) * W
        for x in range(W - 1, -1, -1):
            i = o + x
            if dist[i] == 0.0:
                continue
            xl, xr = (x - 1) % W, (x + 1) % W
            d = dist[i]
            v = dist[o + xr] + a1
            d = v if v < d else d
            v = dist[op + x] + a1
            d = v if v < d else d
            v = dist[op + xr] + a2
            d = v if v < d else d
            v = dist[op + xl] + a2
            d = v if v < d else d
            dist[i] = d
log('%d stones; their distances' % len(sizes))
# the dome: rising over the first DOME pixels from the joint, flat beyond (a quarter circle)
DOME = 2.2 * S
height = [0.0] * N
for i in range(N):
    t = dist[i] / DOME
    if t >= 1.0:
        height[i] = 1.0
    elif t > 0.0:
        height[i] = math.sqrt(1.0 - (1.0 - t) * (1.0 - t))
height = box(height, 1)

# 4. each stone's own brightness
tone = [rnd.uniform(0.90, 1.10) for _ in sizes]

# 5. the detail: fine grain (tiling value-noise fBm) and pits


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
grain = fbm([(m // 2, 0.45), (m // 4, 0.30), (m // 8, 0.15), (m // 32, 0.10)])
log('grain')
pits = [0.0] * N
for k in range(N // 300):
    cx, cy = rnd.random() * W, rnd.random() * H
    r = rnd.choice((0.8, 1.0, 1.3, 1.6, 2.0)) * S / 8.0 * 2.0
    e = int(r + 2)
    for dy in range(-e, e + 1):
        for dx in range(-e, e + 1):
            px_, py_ = int(cx) + dx, int(cy) + dy
            ox, oy = px_ + 0.5 - cx, py_ + 0.5 - cy
            d = math.sqrt(ox * ox + oy * oy)
            if d < r:
                i = (py_ % H) * W + (px_ % W)
                # a pit: dark, its lower-right rim catching the light from the top left
                pits[i] += -0.22 * (1.0 - d / r) + 0.10 * max(0.0, (ox + oy) / (r * 1.4)) * (d / r)
log('pits')

# the light from the top left and above
lx, ly, lz = -0.55, -0.55, 0.63
STRENGTH = 3.0 * S / 8.0 * 2.0
LB = box(L, 1)
out = []
for y in range(H):
    for x in range(W):
        i = y * W + x
        gx = (height[y * W + (x + 1) % W] - height[y * W + (x - 1) % W]) * STRENGTH
        gy = (height[((y + 1) % H) * W + x] - height[((y - 1) % H) * W + x]) * STRENGTH
        nl = math.sqrt(gx * gx + gy * gy + 1.0)
        shade = (-gx * lx - gy * ly + lz) / nl / lz            # 1 for a flat face
        s = edge[i]
        st = tone[lab[i]] if lab[i] >= 0 else 1.0
        ao = 0.70 + 0.30 * height[i]
        l = L[i] if L[i] > 1.0 else 1.0
        sharp = (l + 0.6 * (L[i] - LB[i])) / l
        face = st * (1.0 + 0.08 * grain[i] + pits[i])
        mortar = 0.72 * (1.0 + 0.16 * grain[i])
        f = sharp * (face * s + mortar * (1.0 - s)) * (shade * s + (1.0 - s)) * ao
        out.append((max(0, min(255, int(UR[i] * f + 0.5))), max(0, min(255, int(UG[i] * f + 0.5))),
                    max(0, min(255, int(UB[i] * f + 0.5))), 255))
write_tga(dst, W, H, out)
write_png(preview, W, H, out)
log('done: %s (%dx%d)' % (dst, W, H))
