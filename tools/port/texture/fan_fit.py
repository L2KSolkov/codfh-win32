"""Usage: python fan_fit.py <dumped.tga> [fans across, default 2]

Fits a fan (fish-scale) cobble layout to a texture's dark joints: fans of radius R in rows R
apart, P = 2R across, alternate rows offset by R, each fan its upper (or lower) half-disk with
the next row drawn over it; inside a fan, concentric courses. Searches the phase, the arcs'
facing and the course width for the best match with the joints (luminance below 0.85 of the
local mean), and prints the parameters remaster_fan.py takes.
"""
import math
import os
import sys

sys.path.insert(0, os.path.dirname(__file__))
from teximg import read_tga  # noqa: E402

w, h, px = read_tga(sys.argv[1])
fans = int(sys.argv[2]) if len(sys.argv) > 2 else 2
P = w / fans
R = P / 2.0
L = [0.299 * p[0] + 0.587 * p[1] + 0.114 * p[2] for p in px]


def box(a, r):
    out = [0.0] * (w * h)
    for y in range(h):
        for x in range(w):
            s = 0.0
            for dy in range(-r, r + 1):
                row = ((y + dy) % h) * w
                for dx in range(-r, r + 1):
                    s += a[row + (x + dx) % w]
            out[y * w + x] = s / ((2 * r + 1) ** 2)
    return out


mean = box(L, 4)
joint = [1 if L[i] < 0.85 * mean[i] else 0 for i in range(w * h)]
jpix = [(i % w, i // w) for i in range(w * h) if joint[i]]
share = len(jpix) / (w * h)
print('%dx%d: %d fans across, R %.1f; joints %.0f%% of the pixels' % (w, h, fans, R, share * 100))


def owner(x, y, ox, oy, up):
    """The visible fan at (x, y): its centre and polar (r, angle); rows R apart, the lower rows
    over the upper (up: arcs bulge upward, centres below)."""
    best = None
    for row in range(-2, int(h / R) + 3):
        cy = oy + row * R
        if up and cy < y - 0.01:
            continue
        if not up and cy > y + 0.01:
            continue
        off = (row % 2) * R
        k = math.floor((x - ox - off) / P + 0.5)
        for kk in (k - 1, k, k + 1):
            cx = ox + off + kk * P
            dx, dy = x - cx, y - cy
            r = math.hypot(dx, dy)
            if r <= R:
                # (the lower row is laid over the upper: the visible fan is the lowest one with
                # the point above its centre, for arcs bulging up)
                if best is None or (up and cy > best[1]) or (not up and cy < best[1]):
                    best = (cx, cy, r, dx, dy)
    return best


def score(ox, oy, up, cw, sample):
    """The share of joint pixels lying on the layout's joints (a fan's edge or a course's)."""
    hit = 0
    for (x, y) in sample:
        best = None
        for X in (x, x - w, x + w):
            for Y in (y, y - h, y + h):
                o = owner(X + 0.5, Y + 0.5, ox, oy, up)
                if o:
                    best = o
                    break
            if best:
                break
        if not best:
            continue
        r = best[2]
        d_edge = R - r
        d_course = abs(((R - r) / cw) - round((R - r) / cw)) * cw if cw > 0 else 99
        if min(d_edge, d_course) < 1.2:
            hit += 1
    return hit / len(sample)


sample = jpix[::7]
best = (0, None)
for up in (True, False):
    for oy in range(0, int(R), 2):
        for ox in range(0, int(P), 2):
            s = score(ox, oy, up, 0, sample)
            if s > best[0]:
                best = (s, (ox, oy, up))
print('fan edges: best phase %s, %.0f%% of the joints on them' % (best[1], best[0] * 100))
ox, oy, up = best[1]
# refine the phase to the pixel, then the course width
for dx in (-1, 0, 1):
    for dy in (-1, 0, 1):
        s = score(ox + dx, oy + dy, up, 0, jpix[::3])
        if s > best[0]:
            best = (s, (ox + dx, oy + dy, up))
ox, oy, up = best[1]
cbest = (0, 0)
for cw10 in range(80, 200, 5):
    cw = cw10 / 10.0
    s = score(ox, oy, up, cw, jpix[::3])
    if s > cbest[0]:
        cbest = (s, cw)
print('courses: width %.1f, %.0f%% of the joints on a fan or course edge' % (cbest[1], cbest[0] * 100))
print('PARAMS fans=%d ox=%d oy=%d up=%d course=%.1f' % (fans, ox, oy, 1 if up else 0, cbest[1]))
