"""standinalign.py [--apply]: give XDK stand-in code pieces the names of the member functions they
are the image's version of (PLAN M7: the authentic link reaches a library function by its name, so
the image's version of it must carry that name; a made-up _sub_ name is unreferenced and dropped).

A member's functions keep their object's order in the image. Between two of its rows (functions
the installed copy matches), the image holds the member's functions in between; where the only
rows there are stand-in pieces, they are those functions: as many pieces as unplaced functions
pair up in order, and one piece as long as several functions together (sizes as in the installed
copy, each boundary right after a ret) is split at their boundaries. Only external functions are
named (a static is reached through its own object's symbol). Prints the plan; with --apply the
rows (config/compiled.txt) and the stand-in sources (src/xdk/standin_*.asm: label, PUBLIC, match
line, every reference) take the names, split pieces getting labels of their own."""
import collections
import glob
import os
import re
import sys

sys.path.insert(0, os.path.join(os.path.dirname(os.path.abspath(__file__)), '..'))
from coff import Coff  # noqa: E402
from xbe import Xbe  # noqa: E402

ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
apply = '--apply' in sys.argv
image = Xbe(os.path.join(ROOT, 'orig', 'Game_XboxMultiplayer.xbe'))
rows = []
for l in open(os.path.join(ROOT, 'config', 'compiled.txt'), encoding='utf-8'):
    q = l.split()
    if len(q) >= 3 and q[0].startswith('0x') and int(q[0], 16) < 0x3CD300:
        rows.append((int(q[0], 16), q[1], q[2]))
rows.sort()
named = {(r[1], r[2]) for r in rows}
all_names = {r[2] for r in rows}


def is_standin(o):
    return o.startswith('build/src/xdk/standin_') and not o.startswith('build/src/xdk/standin_data')


def size_of(i):
    return rows[i + 1][0] - rows[i][0] if i + 1 < len(rows) else 0


def masked_at(data, p, f):
    """Whether the image bytes at p are function f's (its relocation fields aside)."""
    code, rel = f[3], f[4]
    if p + len(code) > len(data):
        return False
    seg = bytearray(data[p:p + len(code)])
    ref = bytearray(code)
    for o_ in rel:
        seg[o_:o_ + 4] = ref[o_:o_ + 4] = bytes(4)
    return seg == ref


def starts_as(data, q, f, n=8):
    """Whether the image bytes at q start as function f does (its first n bytes, relocation
    fields aside)."""
    code, rel = f[3], f[4]
    for k in range(min(n, len(code))):
        if any(o_ <= k < o_ + 4 for o_ in rel):
            continue
        if q + k >= len(data) or data[q + k] != code[k]:
            return False
    return True


def ret_before(data, q):
    return data[q - 1] == 0xC3 or (q >= 3 and data[q - 3] == 0xC2 and data[q - 1] == 0)


def seq_split(data, fs):
    """[(offset, name)] for the functions fs laid in the piece data in order, or None."""
    cuts, p, k = [], 0, 0
    while k < len(fs):
        # a function whose bytes are here whole (the ones before it absent from the image)
        whole = next((j for j in range(k, min(k + 3, len(fs))) if masked_at(data, p, fs[j])), None)
        if whole is not None:
            cuts.append((p, fs[whole][0]))
            p += fs[whole][1]
            k = whole + 1
            continue
        f = fs[k]
        if not starts_as(data, p, f):
            # absent from the image (dropped): the next one starts here
            if k + 1 < len(fs) and starts_as(data, p, fs[k + 1]):
                k += 1
                continue
            return None
        cuts.append((p, f[0]))
        if masked_at(data, p, f) and (p + f[1] == len(data) or k + 1 == len(fs) or
                                       any(starts_as(data, p + f[1], g) for g in fs[k + 1:k + 3])):
            p += f[1]
        elif k + 1 == len(fs):
            p = len(data)
        else:
            nxt = fs[k + 1:k + 3]
            q = next((q for q in range(p + 1, len(data)) if ret_before(data, q) and
                      any(starts_as(data, q, g) for g in nxt)), None)
            if q is None:
                return None
            p = q
        k += 1
    return cuts if p == len(data) and len(cuts) > 1 else None


plan = []       # (address, old name, new name, standin obj)
splits = []     # (piece address, old name, [(offset, new name)], standin obj)
objs = sorted({r[1] for r in rows if r[1].startswith('build/xdk/')})
for o in objs:
    try:
        c = Coff(os.path.join(ROOT, o))
    except Exception:
        continue
    funcs = []
    for s in sorted((s for s in c.symbol_list if s['section'] > 0 and (s['type'] >> 4) == 2 and s['class'] in (2, 3)),
                    key=lambda s: (s['section'], s['value'])):
        try:
            code, _ = c.function_bytes(s)
        except Exception:
            continue
        _, rel_ = c.function_bytes(s)
        funcs.append((s['name'], len(code), s['class'], code, tuple(r[0] for r in rel_)))
    index = dict((f[0], k) for k, f in enumerate(funcs))
    anchors = [(i, index[r[2]]) for i, r in enumerate(rows) if r[1] == o and r[2] in index]
    for (i1, k1), (i2, k2) in zip(anchors, anchors[1:]):
        if k2 <= k1 + 1 or i2 <= i1 + 1:
            continue
        between = list(range(i1 + 1, i2))
        if not all(is_standin(rows[i][1]) for i in between):
            continue
        fs = [f for f in funcs[k1 + 1:k2] if (o, f[0]) not in named]
        if not fs:
            continue
        if len(between) == len(fs):
            for i, f in zip(between, fs):
                if f[2] == 2 and f[0] not in all_names and len(f[0]) < 240:
                    plan.append((rows[i][0], rows[i][2], f[0], rows[i][1]))
        elif len(between) == 1 and len(fs) > 1 and sum(f[1] for f in fs) == size_of(between[0]):
            i = between[0]
            a = rows[i][0]
            data = image.read(a, size_of(i))
            offs, ok, off = [], True, 0
            for f in fs:
                if off:
                    tail = data[:off]
                    if not (tail.endswith(b'\xc3') or (len(tail) >= 3 and tail[-3] == 0xC2)):
                        ok = False
                offs.append(off)
                off += f[1]
            # (MASM takes identifiers up to 247 characters)
            if ok and all(f[2] == 2 and f[0] not in all_names and len(f[0]) < 240 for f in fs):
                splits.append((a, rows[i][2], list(zip(offs, [f[0] for f in fs])), rows[i][1]))
        elif len(between) == 1 and len(fs) > 1:
            # sizes differ (another version, or a function the image dropped): walk the piece,
            # a function whose bytes match whole taking its size, else ending at the first ret
            # followed by bytes that start as the next function does
            i = between[0]
            a = rows[i][0]
            data = image.read(a, size_of(i))
            cuts = seq_split(data, fs)
            if cuts and all(nm not in all_names and len(nm) < 240 for _, nm in cuts) and                     all(f[2] == 2 for f in fs if f[0] in dict((n_, 1) for _, n_ in cuts)):
                splits.append((a, rows[i][2], cuts, rows[i][1]))
# every reference a placed row makes to a new name must reach, in the image, the piece's address
target = {}
for p in plan:
    target[p[2]] = p[0]
for s in splits:
    for o_, nm in s[2]:
        target[nm] = s[0] + o_
wrong = set()
cache = {}
every = []
for l in open(os.path.join(ROOT, 'config', 'compiled.txt'), encoding='utf-8'):
    q = l.split()
    if len(q) >= 3 and q[0].startswith('0x'):
        every.append((int(q[0], 16), q[1], q[2]))
for a, o, n in every:
    if is_standin(o) or o.startswith('build/src/xdk/standin_data'):
        continue
    if o not in cache:
        try:
            cache[o] = Coff(os.path.join(ROOT, o))
        except Exception:
            cache[o] = None
    c = cache[o]
    if c is None:
        continue
    s = next((x for x in c.symbol_list if x['section'] > 0 and x['name'] == n), None)
    if s is None:
        continue
    try:
        code, rel = c.function_bytes(s)
    except Exception:
        continue
    for off, tn, rt in rel:
        if tn not in target:
            continue
        field = image.read(a + off, 4)
        v = int.from_bytes(field, 'little')
        if rt == 20:
            v = (a + off + 4 + v) & 0xFFFFFFFF
        add = int.from_bytes(code[off:off + 4], 'little') if rt == 6 else 0
        if v != target[tn] + add:
            wrong.add(tn)
plan = [p for p in plan if p[2] not in wrong]
splits = [s for s in splits if not any(nm in wrong for _, nm in s[2])]
print('%d names reached elsewhere in the image (left alone)' % len(wrong))
# a name the piece's own stand-in file already references (or the old name, referenced there
# besides its definition) stays: MASM would resolve the reference within the file, as a
# section-relative relocation the per-piece check reads differently
texts = {}
for f in glob.glob(os.path.join(ROOT, 'src', 'xdk', 'standin_*.asm')):
    texts[os.path.basename(f)[:-4]] = open(f, encoding='utf-8', errors='replace').read()


def referenced(stem, name, old=None):
    t_ = texts.get(stem, '')
    n_ = 0
    for l in t_.split('\n'):
        if l.startswith(('; // match:', 'PUBLIC ')) or l.startswith(name + ':') or (old and l.startswith(old + ':')):
            continue
        if re.search(r'(?<![\w@$?])%s(?![\w@$?])' % re.escape(name), l):
            n_ += 1
    return n_ > 0


def stem_of(o):
    return os.path.basename(o)[:-4]


plan = [p for p in plan if not referenced(stem_of(p[3]), p[2]) and not referenced(stem_of(p[3]), p[1], p[1])]
splits = [s for s in splits if not any(referenced(stem_of(s[3]), nm) for _, nm in s[2])
          and not referenced(stem_of(s[3]), s[1], s[1])]
for p in plan:
    print('0x%08X %s -> %s' % p[:3])
for s in splits:
    print('0x%08X %s split: %s' % (s[0], s[1], ', '.join('+0x%X %s' % x for x in s[2])))
print('%d renames, %d splits' % (len(plan), len(splits)))
if not apply:
    sys.exit(0)

# the stand-in sources
LINE_BYTES = re.compile(r'^\s*(db|dd|dw)\s+(.*?)\s*(;.*)?$')


def line_size(l):
    m = LINE_BYTES.match(l)
    if m:
        n = len([x for x in m.group(2).split(',') if x.strip()])
        return n * {'db': 1, 'dw': 2, 'dd': 4}[m.group(1)]
    w = l.split(';')[0].split()
    if w and w[0] in ('call', 'jmp'):
        return 5
    if w and w[0].startswith('j'):
        return 6
    return 0


rename = dict((p[1], p[2]) for p in plan)
split_at = dict((s[1], s[2]) for s in splits)
for s in splits:
    rename[s[1]] = s[2][0][1]
for p in sorted(glob.glob(os.path.join(ROOT, 'src', 'xdk', 'standin_*.asm'))):
    raw = open(p, 'rb').read().decode('utf-8')
    nl = '\r\n' if '\r\n' in raw else '\n'
    L = raw.replace('\r\n', '\n').split('\n')
    out = []
    cur, off, pending = None, 0, []
    for l in L:
        m = re.match(r'^; // match: (\S+) @ 0x([0-9A-F]{8})$', l)
        if m:
            cur, off = m.group(1), 0
            pending = list(split_at.get(cur, [])[1:])
            base = int(m.group(2), 16)
        elif cur and pending and line_size(l) and off == pending[0][0]:
            o_, nm = pending.pop(0)
            out += ['; // match: %s @ 0x%08X' % (nm, base + o_), 'PUBLIC %s' % nm, '%s:' % nm]
        out.append(l)
        if cur:
            off += line_size(l)
        if re.match(r'^\w+ ENDS$', l):
            if pending:
                print('%s: %s not split (no line boundary at +0x%X)' % (os.path.basename(p), cur, pending[0][0]))
            cur, pending = None, []
    t = '\n'.join(out)
    for old, new in rename.items():
        t = re.sub(r'(?<![\w@$?])%s(?![\w@$?])' % re.escape(old), lambda _m: new, t)
    # an EXTERN of a name the file now defines goes
    defined = set(re.findall(r'^PUBLIC (\S+)$', t, re.M))
    t = '\n'.join(x for x in t.split('\n') if not (x.startswith('EXTERN ') and x.split()[1].split(':')[0] in defined))
    if t != raw.replace('\r\n', '\n'):
        open(p, 'wb').write(t.replace('\n', nl).encode('utf-8'))
path = os.path.join(ROOT, 'config', 'compiled.txt')
out = []
for l in open(path, encoding='utf-8').read().split('\n'):
    q = l.split()
    if len(q) >= 3 and q[0].startswith('0x') and is_standin(q[1]) and q[2] in rename:
        l = '%s %s %s' % (q[0], q[1], rename[q[2]])
        for o_, nm in split_at.get(q[2], [])[1:]:
            l += '\n0x%08X %s %s' % (int(q[0], 16) + o_, q[1], nm)
    out.append(l)
open(path, 'w', encoding='utf-8', newline='\n').write('\n'.join(out))
