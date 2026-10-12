r"""course.py: the speedrun movement course for make_flat.py's floor (--no-course leaves it out).

Built behind the player start (turn round to see it), in rows across the view, each row's pieces
going back from 10 m behind the start; units are the game's (centimetres; the PlayerTrigger's
point is the eye, 120 above the feet). Every piece is a convex solid, both collision (the floor
section's collision world, split into a tree by make_flat.coll_tree) and drawn (prelit, a colour
a row, the sides darker). The findings named are docs/speedrun/findings.md's.

  steps      (row 1, from the left) 2 m square blocks: 10, 20, 30, 40, 50, 60, 80, 100, 120 and 150
             cm high, green to red: the highest a walk takes, a jump reaches, a mantle climbs
  ramps      (row 2) 2 m wide wedges rising 1.5 m away from the start at 10, 20, 30, 40, 50 and 60
             degrees: where walking slows, where sliding starts
  walls      (row 3) 3 m long, 3 m high walls 1, 5, 10, 20 and 50 cm thick: what clips through
  corners    (row 4) two 20 cm walls meeting at 90 and at 45 degrees, the open side towards the
             start: corner clips and wedging
  long jump  (row 5) a 2 m wide lane from a start line, stripes every metre to 20 m, every fifth
             metre a long stripe: jump, sprint-jump and fall distances (drawn only)
  creep      (row 6) 3 m wide blocks at K1's edge heights: 38 (the nominal step), 42, 48, 54, 60,
             66, 72 and 78 cm: run (diagonally, crouched, at 30 fps) into them for the creep
             step-up
  slopes     (row 7) ramps either side of K2's 69.4 degree walkable limit: 65, 68, 69, 70, 72, 75
  gaps       (row 8) pairs of 50 cm platforms with gaps of 20, 28, 34, 40 and 60 cm between them,
             each twice: across world z (Z, the left one) and across world x (X): K2's floor
             probe is world-fixed, a gap under 34 (z) or 28 (x) holds the player
  roofs      (row 9) 2 x 3 m slabs, 10 cm thick, their undersides 60, 80, 100, 120 and 140 cm up:
             crawl or crouch under, stand up (K7)
  drop       (row 0, left of the steps) 2 m square towers 3, 5, 10, 15 and 20 m high (the debug
             tools' teleport to the top): fall damage and the fall timer (K5, O2)
  teleport   (beside the start, 2.5 m to the side) a 2 m pad, its box drawn in cyan: make_flat.py's
             teleport trigger on it puts you on the 20 m tower's top
  ladders    (row -1, left of the drops) 2 m square towers 6 and 12 m high, a ladder (rails and
             rungs, drawn) up the face towards the start: make_flat.py puts a LadderTrigger's
             volume there (self.ladders). Climb times, grabs from a fall into the top (M3, O3)

The artillery zone (zone(), make_flat.py's --no-artillery leaves it out) is ahead of the start,
beyond the vehicles: a painted 12 m square and its name; the artillery generators aim at its
centre.

Labels, painted on the floor (drawn only, a 3x5 pixel font, upright to a player facing the
course from the start): each row's name in front of it (with its unit), and each piece's size
in the gap before it; the lane's metres beside its long stripes.
"""
import math

# A 3x5 pixel font: each glyph five rows of three, '#' set.
FONT = {
    '0': ['###', '#.#', '#.#', '#.#', '###'], '1': ['.#.', '##.', '.#.', '.#.', '###'],
    '2': ['###', '..#', '###', '#..', '###'], '3': ['###', '..#', '.##', '..#', '###'],
    '4': ['#.#', '#.#', '###', '..#', '..#'], '5': ['###', '#..', '###', '..#', '###'],
    '6': ['###', '#..', '###', '#.#', '###'], '7': ['###', '..#', '.#.', '.#.', '.#.'],
    '8': ['###', '#.#', '###', '#.#', '###'], '9': ['###', '#.#', '###', '..#', '###'],
    'A': ['.#.', '#.#', '###', '#.#', '#.#'], 'C': ['###', '#..', '#..', '#..', '###'],
    'E': ['###', '#..', '##.', '#..', '###'], 'J': ['..#', '..#', '..#', '#.#', '###'],
    'L': ['#..', '#..', '#..', '#..', '###'], 'M': ['#.#', '###', '###', '#.#', '#.#'],
    'N': ['##.', '#.#', '#.#', '#.#', '#.#'], 'O': ['###', '#.#', '#.#', '#.#', '###'],
    'P': ['###', '#.#', '###', '#..', '#..'], 'R': ['##.', '#.#', '##.', '#.#', '#.#'],
    'S': ['###', '#..', '###', '..#', '###'], 'T': ['###', '.#.', '.#.', '.#.', '.#.'],
    'U': ['#.#', '#.#', '#.#', '#.#', '###'], 'W': ['#.#', '#.#', '###', '###', '#.#'],
    'D': ['##.', '#.#', '#.#', '#.#', '##.'], 'F': ['###', '#..', '##.', '#..', '#..'],
    'G': ['###', '#..', '#.#', '#.#', '###'], 'X': ['#.#', '#.#', '.#.', '#.#', '#.#'],
    'Z': ['###', '..#', '.#.', '#..', '###'],
    'I': ['###', '.#.', '.#.', '.#.', '###'], 'Y': ['#.#', '#.#', '.#.', '.#.', '.#.'],
    'B': ['##.', '#.#', '##.', '#.#', '##.'], 'H': ['#.#', '#.#', '###', '#.#', '#.#'],
    'K': ['#.#', '#.#', '##.', '#.#', '#.#'], 'V': ['#.#', '#.#', '#.#', '#.#', '.#.'],
    "'": ['##.', '##.', '...', '...', '...'],    # the degree sign
    ' ': ['...', '...', '...', '...', '...'],
}
LABEL = (240, 240, 240, 255)

STEPS = [10, 20, 30, 40, 50, 60, 80, 100, 120, 150]
RAMPS = [10, 20, 30, 40, 50, 60]
RAMP_HEIGHT = 150.0
WALLS = [1, 5, 10, 20, 50]
CORNERS = [90, 45]
ROW_U = [-2000.0, -1000.0, 0.0, 1000.0, 2000.0]     # the rows' centres across the view, 10 m apart
CREEP = [38, 42, 48, 54, 60, 66, 72, 78]
SLOPES = [65, 68, 69, 70, 72, 75]
GAPS = [20, 28, 34, 40, 60]
GAP_HEIGHT = 50.0
ROOFS = [60, 80, 100, 120, 140]
DROPS = [3, 5, 10, 15, 20]
ROW2_U = [3000.0, 4000.0, 5000.0, 6000.0]          # creep, slopes, gaps, roofs
DROP_U = -3000.0
LADDERS = [6, 12]
PAD_U, PAD_V = 250.0, 100.0                          # the teleport pad: 2.5 m beside the start
FLY_U, FLY_V, FLY_SOLDIER_V = 0.0, 300.0, 550.0      # the fly pad 3 m ahead, its soldier 5.5 m ahead
LADDER_U = -4000.0
START_V = -1000.0                                    # where each row starts, behind the start


def _sub(a, b):
    return (a[0] - b[0], a[1] - b[1], a[2] - b[2])


def _cross(a, b):
    return (a[1] * b[2] - a[2] * b[1], a[2] * b[0] - a[0] * b[2], a[0] * b[1] - a[1] * b[0])


def _dot(a, b):
    return a[0] * b[0] + a[1] * b[1] + a[2] * b[2]


def _mean(ps):
    n = float(len(ps))
    return (sum(p[0] for p in ps) / n, sum(p[1] for p in ps) / n, sum(p[2] for p in ps) / n)


class Course:
    """The course's faces in world space: each a polygon (fanned into triangles), wound so that
    cross(b - a, c - a) is its outward normal (as the floor's triangles are), and a colour."""

    def __init__(self, x, y, z, fx, fz):
        self.o, self.f, self.r = (x, y, z), (fx, fz), (fz, -fx)
        self.faces = []     # (points, colour, solid)
        self.ladders = []
        self.drop_tops = []
        self.pad = None

    def w(self, u, v, h):
        """Local (u right, v forward, h up from the floor) to world."""
        (x, y, z), (fx, fz), (rx, rz) = self.o, self.f, self.r
        return (x + u * rx + v * fx, y + h, z + u * rz + v * fz)

    def solid(self, faces, colour):
        """A convex solid from its faces (local point lists), each wound outward."""
        faces = [[self.w(*p) for p in f] for f in faces]
        centre = _mean([p for f in faces for p in f])
        for f in faces:
            n = _cross(_sub(f[1], f[0]), _sub(f[2], f[0]))
            if _dot(n, _sub(_mean(f), centre)) < 0:
                f = f[::-1]
            shade = 1.0 if abs(n[1]) > 0.7 * math.sqrt(_dot(n, n)) else 0.7
            self.faces.append((f, tuple(int(c * shade) for c in colour[:3]) + (255,), True))

    def world_box(self, x0, x1, z0, z1, h0, h1, colour):
        """A solid box in world x and z (not the course's frame), h0 to h1 above the floor."""
        y = self.o[1]
        c = [(x0, z0), (x1, z0), (x1, z1), (x0, z1)]
        top = [(x, y + h1, z) for x, z in c]
        bottom = [(x, y + h0, z) for x, z in c]
        sides = [[(c[i][0], y + h0, c[i][1]), (c[(i + 1) % 4][0], y + h0, c[(i + 1) % 4][1]),
                  (c[(i + 1) % 4][0], y + h1, c[(i + 1) % 4][1]), (c[i][0], y + h1, c[i][1])] for i in range(4)]
        self._world_solid([top, bottom] + sides if h0 > 0 else [top] + sides, colour)

    def _world_solid(self, faces, colour):
        centre = _mean([p for f in faces for p in f])
        for f in faces:
            n = _cross(_sub(f[1], f[0]), _sub(f[2], f[0]))
            if _dot(n, _sub(_mean(f), centre)) < 0:
                f = f[::-1]
            shade = 1.0 if abs(n[1]) > 0.7 * math.sqrt(_dot(n, n)) else 0.7
            self.faces.append((f, tuple(int(c * shade) for c in colour[:3]) + (255,), True))

    def ramp(self, u, v, angle, height, colour):
        """A 2 m wide wedge from (u, v) rising height away from the start at angle; its far v."""
        run = height / math.tan(math.radians(angle))
        lo, hi = v, v - run
        slope = [(u - 100, lo, 0.0), (u + 100, lo, 0.0), (u + 100, hi, height), (u - 100, hi, height)]
        back = [(u - 100, hi, 0.0), (u - 100, hi, height), (u + 100, hi, height), (u + 100, hi, 0.0)]
        left = [(u - 100, lo, 0.0), (u - 100, hi, height), (u - 100, hi, 0.0)]
        right = [(u + 100, lo, 0.0), (u + 100, hi, 0.0), (u + 100, hi, height)]
        self.solid([slope, back, left, right], colour)
        return hi

    def prism(self, base, h0, h1, colour, bottom=False):
        """A solid from a convex footprint (local (u, v) points) between heights h0 and h1 (its
        underside a face too with bottom)."""
        top = [(u, v, h1) for u, v in base]
        sides = [[(base[i][0], base[i][1], h0), (base[(i + 1) % len(base)][0], base[(i + 1) % len(base)][1], h0),
                  (base[(i + 1) % len(base)][0], base[(i + 1) % len(base)][1], h1), (base[i][0], base[i][1], h1)]
                 for i in range(len(base))]
        self.solid([top] + sides + ([[(u, v, h0) for u, v in base]] if bottom else []), colour)

    def box(self, u0, u1, v0, v1, h, colour):
        self.prism([(u0, v0), (u1, v0), (u1, v1), (u0, v1)], 0.0, h, colour)

    def wall(self, ua, va, ub, vb, thick, h, colour):
        """A wall from (ua, va) to (ub, vb), thick wide."""
        du, dv = ub - ua, vb - va
        n = math.hypot(du, dv) or 1.0
        pu, pv = -dv / n * thick / 2, du / n * thick / 2
        self.prism([(ua + pu, va + pv), (ub + pu, vb + pv), (ub - pu, vb - pv), (ua - pu, va - pv)], 0.0, h, colour)

    def stripe(self, u0, u1, v0, v1, colour, h=1.0):
        """A drawn-only strip on the floor (h up)."""
        pts = [self.w(u0, v0, h), self.w(u0, v1, h), self.w(u1, v0, h), self.w(u1, v1, h)]
        f = [pts[0], pts[1], pts[3], pts[2]]
        n = _cross(_sub(f[1], f[0]), _sub(f[2], f[0]))
        if n[1] < 0:
            f = f[::-1]
        self.faces.append((f, colour, False))

    def deco_box(self, u0, u1, v0, v1, h0, h1, colour):
        """A drawn-only box (no collision): its four sides and top."""
        base = [(u0, v0), (u1, v0), (u1, v1), (u0, v1)]
        faces = [[(u, v, h1) for u, v in base]]
        faces += [[(base[i][0], base[i][1], h0), (base[(i + 1) % 4][0], base[(i + 1) % 4][1], h0),
                   (base[(i + 1) % 4][0], base[(i + 1) % 4][1], h1), (base[i][0], base[i][1], h1)] for i in range(4)]
        faces = [[self.w(*p) for p in f] for f in faces]
        centre = _mean([p for f in faces for p in f])
        for f in faces:
            n = _cross(_sub(f[1], f[0]), _sub(f[2], f[0]))
            if _dot(n, _sub(_mean(f), centre)) < 0:
                f = f[::-1]
            self.faces.append((f, colour, False))

    def zone(self, u, v, half=600.0, colour=(230, 200, 60, 255)):
        """The artillery zone at (u, v): a painted square half wide each way, a cross, its name;
        returns its centre in world space."""
        t = 15.0
        self.stripe(u - half, u + half, v - half, v - half + t, colour)
        self.stripe(u - half, u + half, v + half - t, v + half, colour)
        self.stripe(u - half, u - half + t, v - half, v + half, colour)
        self.stripe(u + half - t, u + half, v - half, v + half, colour)
        self.stripe(u - 100, u + 100, v - t / 2, v + t / 2, colour)
        self.stripe(u - t / 2, u + t / 2, v - 100, v + 100, colour)
        self.text(u, v - half - 60, 'ARTILLERY', 14.0, colour)
        return self.w(u, v, 0.0)

    def text(self, u, v, s, px=8.0, colour=LABEL):
        """s painted on the floor centred at u, its foot at v (towards the start), upright to a
        player facing the course from the start: its rows away from him (-v), its letters to his
        right (+u: the frame's right vector, (fz, -fx), is a viewer's left as he faces the start's
        way). Each set pixel a px square, 1.5 cm up."""
        left = u - (len(s) * 4 - 1) * px / 2
        for k, ch in enumerate(s.upper()):
            for r, row in enumerate(FONT[ch]):
                for c, bit in enumerate(row):
                    if bit == '#':
                        ua = left + (k * 4 + c) * px
                        va = v - (5 - r) * px
                        self.stripe(ua, ua + px, va, va + px, colour, 1.5)

    def build(self):
        for u, title in zip(ROW_U, ('STEPS CM', 'RAMPS', 'WALLS CM', 'CORNERS', 'JUMP M')):
            self.text(u, START_V + 250, title, 12.0)
        # steps: green to red
        u = ROW_U[0]
        for i, h in enumerate(STEPS):
            t = i / float(len(STEPS) - 1)
            v0 = START_V - i * 400.0
            self.box(u - 100, u + 100, v0 - 200, v0, h, (int(60 + 190 * t), int(200 - 150 * t), 60))
            self.text(u, v0 + 110, str(h))
        # ramps: rising away from the start (towards -v), RAMP_HEIGHT high
        u, v = ROW_U[1], START_V
        for a in RAMPS:
            self.text(u, v + 110, "%d'" % a)
            v = self.ramp(u, v, a, RAMP_HEIGHT, (70, 120, 210)) - 300.0
        # walls: 3 m along the row, 3 m high
        u = ROW_U[2]
        for i, t in enumerate(WALLS):
            v0 = START_V - i * 500.0
            self.wall(u, v0, u, v0 - 300, float(t), 300.0, (200, 180, 90))
            self.text(u, v0 + 110, str(t))
        # corners: two 3 m arms meeting behind, the open side towards the start
        u = ROW_U[3]
        for i, a in enumerate(CORNERS):
            tip_v = START_V - 400 - i * 900.0
            half = math.radians(a) / 2
            for s in (-1, 1):
                self.wall(u, tip_v, u + s * 300 * math.sin(half), tip_v + 300 * math.cos(half), 20.0, 300.0,
                          (180, 90, 180))
            self.text(u, tip_v + 300 * math.cos(half) + 110, "%d'" % a)
        # long jump lane: a start line, then stripes every metre to 20 m
        u = ROW_U[4]
        self.stripe(u - 150, u + 150, START_V - 10, START_V + 10, (240, 240, 240, 255))
        for m in range(1, 21):
            v = START_V - m * 100.0
            wide = 150 if m % 5 == 0 else 60
            col = (230, 60, 60, 255) if m % 5 == 0 else (230, 230, 230, 255)
            self.stripe(u - wide, u + wide, v - 3, v + 3, col)
            if m % 5 == 0:
                self.text(u + 260, v + 20, str(m))
        self.build_more()
        return self

    def build_more(self):
        for u, title in zip(ROW2_U + [DROP_U], ('CREEP CM', 'SLOPES', 'GAPS CM', 'ROOFS CM', 'DROP M')):
            self.text(u, START_V + 250, title, 12.0)
        # creep: 3 m wide blocks at K1's edge heights, orange
        u = ROW2_U[0]
        for i, h in enumerate(CREEP):
            v0 = START_V - i * 400.0
            self.box(u - 150, u + 150, v0 - 200, v0, float(h), (230, 140, 40))
            self.text(u, v0 + 110, str(h))
        # slopes: about the walkable limit, teal
        u, v = ROW2_U[1], START_V
        for a in SLOPES:
            self.text(u, v + 110, "%d'" % a)
            v = self.ramp(u, v, a, RAMP_HEIGHT, (40, 170, 160)) - 300.0
        # gaps: world-aligned platform pairs, Z on the left, X on the right
        u = ROW2_U[2]
        for i, g in enumerate(GAPS):
            v0 = START_V - 150 - i * 600.0
            for side, axis in ((-150, 'Z'), (150, 'X')):
                cx, _, cz = self.w(u + side, v0, 0.0)
                if axis == 'Z':
                    self.world_box(cx - 75, cx + 75, cz - g / 2.0 - 150, cz - g / 2.0, 0.0, GAP_HEIGHT, (120, 200, 90))
                    self.world_box(cx - 75, cx + 75, cz + g / 2.0, cz + g / 2.0 + 150, 0.0, GAP_HEIGHT, (120, 200, 90))
                else:
                    self.world_box(cx - g / 2.0 - 150, cx - g / 2.0, cz - 75, cz + 75, 0.0, GAP_HEIGHT, (90, 160, 200))
                    self.world_box(cx + g / 2.0, cx + g / 2.0 + 150, cz - 75, cz + 75, 0.0, GAP_HEIGHT, (90, 160, 200))
                self.text(u + side, v0 + 260, '%d%s' % (g, axis), 6.0)
        # roofs: floating slabs, grey
        u = ROW2_U[3]
        for i, h in enumerate(ROOFS):
            v0 = START_V - i * 500.0
            self.prism([(u - 100, v0), (u + 100, v0), (u + 100, v0 - 300), (u - 100, v0 - 300)], float(h),
                       float(h) + 10.0, (150, 150, 170), bottom=True)
            self.text(u, v0 + 110, str(h))
        # ladder towers: brown, a ladder up the face towards the start (rails and rungs drawn 5 cm
        # proud of it); each ladder's volume for make_flat.py: (its centre, the face's outward
        # direction, half its height)
        self.ladders = []
        u = LADDER_U
        self.text(u, START_V + 250, 'LADDER M', 12.0)
        for i, m in enumerate(LADDERS):
            v0 = START_V - i * 600.0
            h = m * 100.0
            self.box(u - 100, u + 100, v0 - 200, v0, h, (120, 90, 60))
            wood = (200, 170, 110, 255)
            for side in (-40, 35):
                self.deco_box(u + side, u + side + 5, v0, v0 + 5, 0.0, h + 90.0, wood)
            r = 30.0
            while r < h + 60.0:
                self.deco_box(u - 40, u + 40, v0, v0 + 5, r, r + 4, wood)
                r += 30.0
            self.text(u, v0 + 110, str(m))
            centre = self.w(u, v0 + 40.0, h / 2.0 + 25.0)
            self.ladders.append((centre, self.f, h / 2.0 + 25.0))
        # drop towers: dark red; each top's centre (world) for the teleport pad
        u = DROP_U
        self.drop_tops = []
        for i, m in enumerate(DROPS):
            v0 = START_V - i * 500.0
            self.box(u - 100, u + 100, v0 - 200, v0, m * 100.0, (150, 50, 50))
            self.text(u, v0 + 110, str(m))
            self.drop_tops.append(self.w(u, v0 - 100, m * 100.0))
        # the teleport pad, beside the player start (make_flat.py's teleport trigger stands on it):
        # stepping on it puts the player on the highest tower. Drawn (no collision): the floor
        # filled, posts at its corners and a frame at 2 m, the trigger box's edges, and its name
        self.pad = self.w(PAD_U, PAD_V, 0.0)
        self.pad_box(PAD_U, PAD_V, 'TELEPORT', (90, 220, 255, 255), (30, 110, 150, 255), 200.0)

    def pad_box(self, pu, pv, label, glow, dark, label_dv):
        """A 2 m trigger pad at (pu, pv), drawn (no collision): the floor filled, posts at its corners
        and a frame at 2 m, the trigger box's edges, and its label label_dv ahead of it."""
        self.stripe(pu - 100, pu + 100, pv - 100, pv + 100, dark)
        for a, b, c, d in ((-100, 100, -100, -85), (-100, 100, 85, 100), (-100, -85, -100, 100), (85, 100, -100, 100)):
            self.stripe(pu + a, pu + b, pv + c, pv + d, glow, 1.2)
        for cu in (-100, 95):
            for cv in (-100, 95):
                self.deco_box(pu + cu, pu + cu + 5, pv + cv, pv + cv + 5, 0.0, 200.0, glow)
        for a, b, c, d in ((-100, 100, -100, -95), (-100, 100, 95, 100), (-100, -95, -100, 100), (95, 100, -100, 100)):
            self.deco_box(pu + a, pu + b, pv + c, pv + d, 195.0, 200.0, glow)
        self.text(pu, pv + label_dv, label, 8.0, glow)

    def fly_pad(self):
        """The fly pad (make_flat.py's fly trigger stands on it, its soldier beyond it): drawn in
        orange, its label on the near side; (the pad's centre, the soldier's point), in world."""
        self.pad_box(FLY_U, FLY_V, 'FLY', (255, 150, 40, 255), (140, 70, 20, 255), -170.0)
        return self.w(FLY_U, FLY_V, 0.0), self.w(FLY_U, FLY_SOLDIER_V, 0.0)

    def collision(self):
        """(vertices, triangles) of the solid faces."""
        verts, tris = [], []
        for pts, colour, solid in self.faces:
            if not solid:
                continue
            b = len(verts)
            verts += pts
            tris += [(b, b + k, b + k + 1) for k in range(1, len(pts) - 1)]
        return verts, tris

    def drawn(self):
        """(vertices, triangles, normals, prelit) of every face."""
        verts, tris, normals, prelit = [], [], [], []
        for pts, colour, solid in self.faces:
            b = len(verts)
            n = _cross(_sub(pts[1], pts[0]), _sub(pts[2], pts[0]))
            ln = math.sqrt(_dot(n, n)) or 1.0
            nb = tuple(int(round(c / ln * 127)) for c in n)
            verts += pts
            normals += [nb] * len(pts)
            prelit += [colour] * len(pts)
            tris += [(b, b + k, b + k + 1) for k in range(1, len(pts) - 1)]
        return verts, tris, normals, prelit
