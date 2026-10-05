"""piecescan.py [--apply]: member data inside XDK data stand-in pieces (PLAN M7).

For every installed or 5849 member datum of at least 32 bytes (the bytes to the next symbol in
its section), search the image's data stand-in pieces (src/xdk/standin_data_*.asm rows) for its
bytes (relocation fields aside, the rest having at least 16 non-zero bytes): a single hit inside
one piece is that member's datum, cut out with cutpiece.py (--apply). Prints the plan."""
import bisect
import glob
import os
import subprocess
import sys

sys.path.insert(0, os.path.join(os.path.dirname(os.path.abspath(__file__)), '..'))
from coff import Coff  # noqa: E402
from xbe import Xbe  # noqa: E402

ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
apply = '--apply' in sys.argv
# (PS_MIN: the smallest datum searched, default 32; PS_SEC: only pieces in this image section)
MIN = int(os.environ.get('PS_MIN', '32'))
NZ = min(16, MIN // 2)
SEC = os.environ.get('PS_SEC')
SHORT = os.environ.get('PS_SHORT') == '1'
# (PS_LITONLY=1: only literal COMDATs, ??_C@ and __real@, each a section of its own)
LITONLY = os.environ.get('PS_LITONLY') == '1'
# (PS_SKIP=a.obj,b.obj: members never taken)
SKIP = set(x for x in os.environ.get('PS_SKIP', '').split(',') if x)
# (PS_ANY=1: code stand-ins' pieces too, data a library merges into its code section: dsound's
# WMADEC_RD, disassembled as code in standin_wmadec.asm)
ANY = os.environ.get('PS_ANY') == '1'
img = Xbe(os.path.join(ROOT, 'orig', 'Game_XboxMultiplayer.xbe'))
rows = []
for l in open(os.path.join(ROOT, 'config', 'compiled.txt'), encoding='utf-8'):
    q = l.split()
    if len(q) >= 3 and q[0].startswith('0x'):
        rows.append((int(q[0], 16), q[1], q[2]))
rows.sort()
ad = [r[0] for r in rows]
rownames = set(r[2] for r in rows)
pieces = []
for k, (a, o, n) in enumerate(rows):
    if (o.startswith('build/src/xdk/standin_data') or ANY and o.startswith('build/src/xdk/standin')) \
            and k + 1 < len(rows):
        pieces.append((a, rows[k + 1][0], n))
blobs = []
secs = [(s['va'], s['va'] + s['vsize'], s['name']) for s in img.sections]
for a, e, n in pieces:
    if SEC and not any(s0 <= a < s1 and sn == SEC for s0, s1, sn in secs):
        continue
    try:
        blobs.append((a, e, n, img.read(a, e - a)))
    except Exception:
        pass
def scan(p):
    """One member object's data found once in the pieces: ([(at, hit)], [multi lines])."""
    out, multi = [], []
    rel = os.path.relpath(p, ROOT).replace(os.sep, '/')
    if os.path.basename(p) in SKIP:
        return out, multi
    try:
        c = Coff(p)
    except Exception:
        return out, multi
    for x in c.symbol_list:
        if x['section'] <= 0 or x['class'] not in (2, 3) or x['name'] in rownames:
            continue
        if LITONLY and not x['name'].startswith(('??_C@', '__real@')):
            continue
        s = c.sections[x['section'] - 1]
        if s['chars'] & 0x20 or s['name'].startswith('.debug') or s['name'] == '.drectve' or x['name'] == s['name']:
            continue
        later = sorted(y['value'] for y in c.symbol_list if y['section'] == x['section'] and y['value'] > x['value'])
        d = bytes(s['data'][x['value']:(later[0] if later else len(s['data']))])
        if len(d) < MIN:
            continue
        ra = set()
        for va, si, t in s['relocs']:
            ra.update(range(va - x['value'], va - x['value'] + 4))
        if sum(1 for j in range(len(d)) if j not in ra and d[j]) < NZ:
            continue
        k0 = next((k for k in range(len(d) - 7) if all(j not in ra for j in range(k, k + 8))), None)
        w = 8
        if k0 is None:
            # (PS_SHORT=1: a literal shorter than the anchor, without relocations, is searched
            # whole, at 4-aligned addresses only)
            if not (SHORT and not ra and x['name'].startswith('??_C@')):
                continue
            k0, w = 0, len(d)
        found = []
        for a, e, n, b in blobs:
            j = b.find(d[k0:k0 + w])
            while j >= 0:
                st = j - k0
                if st >= 0 and st + len(d) <= len(b) and all(d[q] == b[st + q] for q in range(len(d)) if q not in ra)                         and (w == 8 or (a + st) % 4 == 0):
                    found.append((a, a + st, n))
                j = b.find(d[k0:k0 + w], j + 1)
        if len(found) == 1:
            out.append((found[0][1], (found[0][0], found[0][2], rel, x['name'], len(d))))
        elif len(found) > 1 and os.environ.get('PS_MULTI'):
            # (PS_MULTI=1: data found more than once, listed)
            multi.append('multi %s %s (%d): %s' % (rel.split('/')[-1], x['name'][:40], len(d),
                                                   ' '.join('0x%X' % f[1] for f in found[:6])))
    return out, multi


def main():
    # (the members scanned in parallel, one process per CPU)
    import concurrent.futures
    files = sorted(glob.glob(os.path.join(ROOT, 'build', 'xdk', '*', '*.obj')))
    hits = {}
    with concurrent.futures.ProcessPoolExecutor(max_workers=os.cpu_count()) as ex:
        for out, multi in ex.map(scan, files, chunksize=8):
            for at, h in out:
                hits.setdefault(at, []).append(h)
            for m in multi:
                print(m)
    plan = []
    for at, hs in sorted(hits.items()):
        objs = set(h[2].split('/')[-1] for h in hs)
        if len(objs) > 1:
            # (one literal COMDAT several members define: the image's copy is the object's whose
            # row comes last before it, the first definer in link order there)
            # (any datum of one name several members define, a header's selectany constant like
            # D3D's g_TextureFormat, too: COMDATs, one copy kept; without a neighbour among them,
            # the first member's)
            if len(set(h[3] for h in hs)) == 1:
                k = bisect.bisect_left(ad, at) - 1
                while k >= 0 and rows[k][1].startswith('build/src/xdk/standin'):
                    k -= 1
                prev = os.path.basename(rows[k][1]) if k >= 0 else None
                near = [h for h in hs if h[2].split('/')[-1] == prev]
                hs = near or sorted(hs, key=lambda h: h[2])[:1]
            else:
                continue
        hs.sort(key=lambda h: ('/xdklib_' not in h[2], h[2]))
        pa, pn, rel, nm, ln = hs[0]
        plan.append((pa, at, rel, nm, ln, pn))
    # (hits that overlap another, a datum measured to its next symbol running over its
    # neighbour's: neither is taken)
    plan.sort(key=lambda p_: p_[1])
    bad = set()
    for k in range(len(plan) - 1):
        if plan[k][1] + plan[k][4] > plan[k + 1][1]:
            bad.update((k, k + 1))
    plan = [p_ for k, p_ in enumerate(plan) if k not in bad]
    for pa, at, rel, nm, ln, pn in plan:
        print('0x%08X in %s (0x%08X): %s %s (%d)' % (at, pn, pa, rel.split('/')[-1], nm[:50], ln))
    print(len(plan), 'data')
    if apply:
        # every cut of a piece in one pass, the highest address first: the piece keeps its row
        # (and name) at its start, each cut ending it where the next one up begins
        # (a piece cutpiece refuses, code with an instruction cutpiece cannot size: its other
        # cuts are left too)
        failed = set()
        for pa, at, rel, nm, ln, pn in sorted(plan, key=lambda x: (x[0], -x[1])):
            if pa in failed:
                continue
            r = subprocess.run([sys.executable, os.path.join(ROOT, 'tools', 'session', 'cutpiece.py'),
                                '0x%X' % pa, '0x%X' % at, rel, nm], capture_output=True, text=True)
            print(r.stdout.strip() or r.stderr.strip().splitlines()[-1])
            if r.returncode:
                failed.add(pa)


if __name__ == '__main__':
    main()
