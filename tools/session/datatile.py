"""datatile.py [--apply] [ADDR...]: XDK data stand-in pieces that are several member data in a
row (PLAN M7).

A data piece the transcription cut as one block (DSOUND's ??_7CDirectSound piece holds the
CDirectSound, CDirectSoundVoiceSettings, CDirectSoundVoice and CDirectSoundBuffer vtables) is
tiled with installed or 5849 member data symbols: at each offset a symbol whose bytes match the
image (relocation fields aside) and whose relocations name the rows (or aliases) at the image's
values. A piece tiled exactly (up to 3 bytes of padding between) becomes rows of those members'
data, and leaves the asm. Prints the plan; --apply edits."""
import bisect
import collections
import glob
import os
import re
import struct
import sys

sys.path.insert(0, os.path.join(os.path.dirname(os.path.abspath(__file__)), '..'))
from coff import Coff  # noqa: E402
from xbe import Xbe  # noqa: E402

ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
apply = '--apply' in sys.argv
# (DT_ANY=1: code stand-ins' pieces too, data a library merges into its code section)
_dirs = 'build/src/xdk/standin' if os.environ.get('DT_ANY') == '1' else 'build/src/xdk/standin_data'
only = set(int(x, 16) for x in sys.argv[1:] if x.startswith('0x'))
img = Xbe(os.path.join(ROOT, 'orig', 'Game_XboxMultiplayer.xbe'))


def _zero(va):
    """The image byte at VA is zero (an address past its section's end is not)."""
    try:
        return img.read(va, 1) == bytes(1)
    except ValueError:
        return False


rows = []
for l in open(os.path.join(ROOT, 'config', 'compiled.txt'), encoding='utf-8'):
    q = l.split()
    if len(q) >= 3 and q[0].startswith('0x'):
        rows.append((int(q[0], 16), q[1], q[2]))
rows.sort()
ad = [r[0] for r in rows]
at = collections.defaultdict(set)
for a, o, n in rows:
    at[a].add(n)
alias = {}
for l in open(os.path.join(ROOT, 'config', 'aliases.txt'), encoding='utf-8'):
    q = l.split()
    if len(q) >= 2 and q[1].startswith('0x'):
        alias[q[0]] = int(q[1], 16)
syms = collections.defaultdict(list)       # first 4 masked-bytes key -> candidates
cands = []
for p in glob.glob(os.path.join(ROOT, 'build', 'xdk', '*', '*.obj')):
    rel = os.path.relpath(p, ROOT).replace(os.sep, '/')
    try:
        c = Coff(p)
    except Exception:
        continue
    idx = dict((x['index'], x) for x in c.symbol_list)
    for x in c.symbol_list:
        if x['section'] <= 0 or x['class'] not in (2, 3) or x['name'].startswith('$') or x['name'].startswith('.'):
            continue
        s = c.sections[x['section'] - 1]
        if s['chars'] & 0x20 or s['name'].startswith('.debug') or s['name'] == '.drectve' or x['name'] == s['name']:
            continue
        later = sorted(y['value'] for y in c.symbol_list if y['section'] == x['section'] and y['value'] > x['value'])
        end = later[0] if later else len(s['data'])
        d = bytes(s['data'][x['value']:end])
        if not d:
            continue
        rel_ = [(va - x['value'], idx[si]['name'], t) for va, si, t in s['relocs'] if x['value'] <= va < end]
        cands.append((rel, x['name'], d, rel_))


FUNCS = {}          # a function name -> its masked bodies (the XDK members' definitions)


def masked_body(c, x):
    try:
        code, rel = c.function_bytes(x)
    except Exception:
        return None
    b = bytearray(code)
    for o, n_, ty in rel:
        b[o:o + 4] = b'\0\0\0\0'
    return bytes(b)


for p_ in glob.glob(os.path.join(ROOT, 'build', 'xdk', '*', '*.obj')):
    try:
        c_ = Coff(p_)
    except Exception:
        continue
    for x_ in c_.symbol_list:
        if x_['section'] > 0 and x_['class'] == 2 and c_.sections[x_['section'] - 1]['chars'] & 0x20:
            b_ = masked_body(c_, x_)
            if b_:
                FUNCS.setdefault(x_['name'], set()).add(b_)
row_obj = dict((a_, o_) for a_, o_, n_ in rows)


def folds(n, v):
    """Whether a member's body of n is the body of the row at v (an /OPT:ICF fold)."""
    mine = FUNCS.get(n)
    if not mine:
        return False
    for nm_ in at.get(v, ()):
        if nm_ in FUNCS and FUNCS[nm_] & mine:
            return True
    # (or the image's bytes there, the relocation fields aside: the row there is a function
    # built from source, a game or RenderWare one, not a member)
    for b_ in mine:
        try:
            im_ = img.read(v, len(b_))
        except Exception:
            continue
        if len(b_) and all(b_[j] == im_[j] or b_[j] == 0 for j in range(len(b_))):
            return True
    return False


def fits(a, d, rel_):
    global last_alias
    last_alias = {}
    try:
        i = img.read(a, len(d))
    except Exception:
        return False
    ra = set()
    for o, n, t in rel_:
        ra.update(range(o, o + 4))
    if any(d[j] != i[j] for j in range(len(d)) if j not in ra):
        return False
    # every absolute relocation names what the image's value is
    for o, n, t in rel_:
        if t != 6:
            continue
        v = struct.unpack_from('<I', i, o)[0] - struct.unpack_from('<i', d, o)[0]
        v &= 0xFFFFFFFF
        if alias.get(n) == v or n in at.get(v, ()):
            continue
        # a vtable's ??_E slot where the image has the class's ??_G (the weak external's
        # default), or a name no row has at all where the image has another row (an /OPT:ICF
        # fold): accepted, with an alias the placement link resolves it by
        if v in at and ((n.startswith('??_E') and ('??_G' + n[4:] in at[v] or folds('??_G' + n[4:], v))) or (n not in rownames and n not in alias and folds(n, v))):
            last_alias[n] = v
            continue
        if os.environ.get('DT_DEBUG'):
            print('  no fit at 0x%X: %s -> 0x%X' % (a, n, v))
        return False
    return True


rownames = set(r[2] for r in rows)
new_alias = {}
hit_alias = {}
last_alias = {}
bylen = collections.defaultdict(list)
for cnd in cands:
    bylen[len(cnd[2])].append(cnd)
plan = {}
for k, (a, o, n) in enumerate(rows):
    if not o.startswith(_dirs) or (only and a not in only) or a >= 0x541000:
        continue
    end = ad[k + 1] if k + 1 < len(ad) else a
    pos, tiles = a, []
    while pos < end:
        hit = None
        # every datum that fits here; the first tile's object first (one member's data in a
        # row), then the piece's own name at its start, then the 5849 copy, then the longest
        # (the first tile's object, else the object of the row before the piece: COMDAT data
        # several members define sit with the one whose block they are in)
        first_rel = tiles[0][1] if tiles else (rows[k - 1][1] if k and rows[k - 1][1].startswith('build/xdk/') else None)
        fit = []
        for L in bylen:
            if L > end - pos:
                continue
            for rel, nm, d, rel_ in bylen[L]:
                # (all zeros and nothing relocated: it matches any fill, padding first)
                if not any(d) and not rel_:
                    continue
                # (a name another row already places is not this datum)
                if nm in rownames and nm != n:
                    continue
                if fits(pos, d, rel_):
                    fit.append((rel, nm, L, dict(last_alias)))
        if fit:
            fit.sort(key=lambda f: (f[0] != first_rel if first_rel else 0, not (pos == a and f[1] == n),
                                    '/xdklib_' not in f[0], -f[2]))
            hit = (pos,) + fit[0][:3]
            hit_alias[(pos, fit[0][1])] = fit[0][3]
        if hit is None:
            # alignment padding (zeros) up to 3 bytes
            pad = 0
            while pad < 3 and pos + pad < end and _zero(pos + pad):
                pad += 1
            # (at the piece's start too: a member's aligned datum after the previous one's fill)
            if pad:
                pos += pad
                continue
            tiles = None
            break
        tiles.append(hit)
        pos += hit[3]
    if os.environ.get('DT_DEBUG'):
        print('tiles for 0x%X:' % a, [(hex(x[0]), x[1], x[2][:40], x[3]) for x in tiles] if tiles else tiles)
        if tiles:
            print('  aliases', [hit_alias.get((x[0], x[2]), {}) for x in tiles])
    # (only a tiling from one object, each name once and no tile under 4 bytes: zeros and
    # small constants match anything)
    if tiles and (len(tiles) > 1 or os.environ.get("DT_SINGLE")) and (len(set(x[1] for x in tiles)) == 1 or (os.environ.get('DT_MULTI') and all(x[3] >= 8 or x[2].startswith('??_7') for x in tiles) and not any(x[2].startswith('??_C@') or x[2].startswith('__real@') for x in tiles))) and not any(
            n_.startswith('??_C@') or n_.startswith('__real@') for x in tiles for n_ in hit_alias.get((x[0], x[2]), {}))              and len(set(x[2] for x in tiles)) == len(tiles) and min(x[3] for x in tiles) >= 4:
        plan[a] = (n, tiles)
        for x in tiles:
            new_alias.update(hit_alias.get((x[0], x[2]), {}))
for a, (n, tiles) in sorted(plan.items()):
    print('0x%08X %s:' % (a, n[:50]))
    for pos, rel, nm, L in tiles:
        print('    0x%08X %4d %s %s' % (pos, L, rel.split('/')[-1], nm[:60]))
print(len(plan), 'pieces')
if not apply:
    sys.exit(0)
used = set()
for a, (n, tiles) in plan.items():
    for pos, rel, nm, L in tiles:
        used.add((rel, nm))
if new_alias:
    with open(os.path.join(ROOT, 'config', 'aliases.txt'), 'a', encoding='utf-8', newline='\n') as f:
        for n, v in sorted(new_alias.items()):
            f.write('%s 0x%08X  a member datum names it where the image has the row there (a weak '
                    'external default or an /OPT:ICF fold; datatile.py)\n' % (n, v))
cp = os.path.join(ROOT, 'config', 'compiled.txt')
out = []
for l in open(cp, encoding='utf-8').read().split('\n'):
    q = l.split()
    if len(q) >= 3 and q[0].startswith('0x') and int(q[0], 16) in plan and q[1].startswith(_dirs):
        for pos, rel, nm, L in plan[int(q[0], 16)][1]:
            out.append('0x%08X %s %s' % (pos, rel, nm))
        continue
    out.append(l)
open(cp, 'w', encoding='utf-8', newline='\n').write('\n'.join(out))
names = dict((a, n) for a, (n, t) in plan.items())
for p in glob.glob(os.path.join(ROOT, 'src', 'xdk', 'standin_*.asm')):
    raw = open(p, 'rb').read().decode('utf-8')
    nl = '\r\n' if '\r\n' in raw else '\n'
    L = raw.replace('\r\n', '\n').split('\n')
    res, i, changed = [], 0, False
    while i < len(L):
        m = re.match(r'^; // match: (\S+) @ 0x([0-9A-F]{8})$', L[i])
        if m and names.get(int(m.group(2), 16)) == m.group(1):
            j = i + 1
            while j < len(L) and not L[j].startswith('; // match: ') and not re.match(r'^\w+ ENDS$', L[j]):
                j += 1
            i, changed = j, True
            continue
        res.append(L[i])
        i += 1
    if changed:
        t = '\n'.join(res)
        for a, n in names.items():
            t = re.sub(r'^PUBLIC %s\n' % re.escape(n), '', t, flags=re.M)
            if re.search(r'(?<![\w@$?])%s(?![\w@$?])' % re.escape(n), t) and not re.search(r'^EXTERN %s:' % re.escape(n), t, re.M):
                first = re.search(r'^EXTERN ', t, re.M)
                pos = first.start() if first else t.index('\n') + 1
                t = t[:pos] + 'EXTERN %s:BYTE\n' % n + t[pos:]
        t = re.sub(r'\n(\w+) SEGMENT [^\n]*\n\s*\n\1 ENDS\n', '\n', t)
        open(p, 'wb').write(t.replace('\n', nl).encode('utf-8'))
