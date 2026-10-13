"""Usage: python esrgan_remaster.py <dumped.tga> <out_dir> [scale: 4, 8 or 16; default 8]

A tiling texture remastered with Real-ESRGAN (realesrgan-ncnn-vulkan, model realesrgan-x4plus,
in build/tools/realesrgan_dl), kept seamless: each pass is given the texture padded with its
own wrapped edges and the padding is cropped off after, so the edges meet as they did. 4x is
one pass; 8x is two (16x) box-filtered down by 2; 16x is two.

Writes <name>_esrgan.tga (the model alone) and <name>_esrgan_relief.tga (it, plus a light
relief from its own luminance lit from the top left, darker joints and fine tiling grain),
with .png previews of each.
"""
import math
import os
import random
import subprocess
import sys
import time

sys.path.insert(0, os.path.dirname(__file__))
from teximg import read_tga, read_png, write_tga, write_png  # noqa: E402

HERE = os.path.dirname(os.path.abspath(__file__))
EXE = os.path.normpath(os.path.join(HERE, '..', '..', '..', 'build', 'tools', 'realesrgan_dl', 'realesrgan-ncnn-vulkan.exe'))
src, out_dir = sys.argv[1], sys.argv[2]
scale = int(sys.argv[3]) if len(sys.argv) > 3 else 8
name = os.path.splitext(os.path.basename(src))[0]
os.makedirs(out_dir, exist_ok=True)
t0 = time.time()


def log(msg):
    print('%6.1fs  %s' % (time.time() - t0, msg))


def wrap_pad(w, h, px, m):
    W, H = w + 2 * m, h + 2 * m
    return W, H, [px[((y - m) % h) * w + ((x - m) % w)] for y in range(H) for x in range(W)]


def crop(w, h, px, m):
    W, H = w - 2 * m, h - 2 * m
    return W, H, [px[(y + m) * w + x + m] for y in range(H) for x in range(W)]


def esrgan_x4(w, h, px, margin, tag):
    """One Real-ESRGAN x4 pass with a wrapped margin of `margin` pixels, cropped back."""
    pw, ph, pp = wrap_pad(w, h, px, margin)
    fin = os.path.join(out_dir, '%s_%s_in.png' % (name, tag))
    fout = os.path.join(out_dir, '%s_%s_out.png' % (name, tag))
    write_png(fin, pw, ph, pp)
    r = subprocess.run([EXE, '-i', fin, '-o', fout, '-n', 'realesrgan-x4plus', '-s', '4', '-t', '256'],
                       capture_output=True, text=True)
    if r.returncode != 0 or not os.path.exists(fout):
        sys.exit('realesrgan failed: %s %s' % (r.stdout[-500:], r.stderr[-500:]))
    ow, oh, op = read_png(fout)
    assert (ow, oh) == (pw * 4, ph * 4), (ow, oh, pw, ph)
    return crop(ow, oh, op, margin * 4)


def half(w, h, px):
    W, H = w // 2, h // 2
    out = []
    for y in range(H):
        for x in range(W):
            s = [0, 0, 0, 0]
            for k in (px[(2 * y) * w + 2 * x], px[(2 * y) * w + 2 * x + 1], px[(2 * y + 1) * w + 2 * x],
                      px[(2 * y + 1) * w + 2 * x + 1]):
                for c in range(4):
                    s[c] += k[c]
            out.append(tuple((v + 2) // 4 for v in s))
    return W, H, out


w, h, px = read_tga(src)
log('%s: %dx%d' % (name, w, h))
W, H, P = esrgan_x4(w, h, px, max(16, min(w, h) // 4), 'p1')
log('pass 1: %dx%d' % (W, H))
if scale >= 8:
    W, H, P = esrgan_x4(W, H, P, 64, 'p2')
    log('pass 2: %dx%d' % (W, H))
    if scale == 8:
        W, H, P = half(W, H, P)
        log('down to %dx%d' % (W, H))
alpha = [p[3] for p in P]
plain = os.path.join(out_dir, name + '_esrgan')
write_tga(plain + '.tga', W, H, P)
write_png(plain + '.png', W, H, P)
log('wrote ' + plain + '.tga')

# the relief: the luminance blurred into a height, its slope against the light from the top
# left; the darkest parts (joints) a little darker; fine grain (tiling value noise)
N = W * H
L = [0.299 * p[0] + 0.587 * p[1] + 0.114 * p[2] for p in P]


def box(a, r):
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


k = max(1, W // 512)
height = box(box(L, 2 * k), 2 * k)
mean = box(L, 12 * k)
rnd = random.Random(1943)
nx, ny = max(1, W // 4), max(1, H // 4)
lat = [rnd.random() * 2.0 - 1.0 for _ in range(nx * ny)]
log('relief maps')
out = []
for y in range(H):
    fy = y * ny / H
    iy = int(fy)
    ty = fy - iy
    for x in range(W):
        i = y * W + x
        gx = height[y * W + (x + 1) % W] - height[y * W + (x - 1) % W]
        gy = height[((y + 1) % H) * W + x] - height[((y - 1) % H) * W + x]
        shade = 1.0 - (gx + gy) * 0.010 / k
        m = mean[i] if mean[i] > 1.0 else 1.0
        dark = L[i] / m
        joint = 1.0 if dark > 0.85 else 0.85 + 0.15 * (dark / 0.85)
        fx = x * nx / W
        ix = int(fx)
        tx = fx - ix
        a, b = lat[(iy % ny) * nx + ix % nx], lat[(iy % ny) * nx + (ix + 1) % nx]
        c, d = lat[((iy + 1) % ny) * nx + ix % nx], lat[((iy + 1) % ny) * nx + (ix + 1) % nx]
        g = (a + (b - a) * tx) * (1 - ty) + (c + (d - c) * tx) * ty
        f = shade * joint * (1.0 + 0.04 * g)
        p = P[i]
        out.append((max(0, min(255, int(p[0] * f + 0.5))), max(0, min(255, int(p[1] * f + 0.5))),
                    max(0, min(255, int(p[2] * f + 0.5))), alpha[i]))
relief = os.path.join(out_dir, name + '_esrgan_relief')
write_tga(relief + '.tga', W, H, out)
write_png(relief + '.png', W, H, out)
log('wrote ' + relief + '.tga')
