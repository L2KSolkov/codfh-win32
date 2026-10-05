"""rcsid.py [--apply] [LO HI]: define RenderWare's RCS id strings where the image keeps them (PLAN M5).

RenderWare 3.6 sources open with `static const char rcsid[] __RWUNUSED__ = "@@(#)$Id: ... $";`
(the 3.7.2 tree has none), and VC7.1 keeps them. Each uncovered id string in .rdata names its
file (`//RenderWare/RW36Active/rwsdk/src/baframe.c#1`), which maps to src/rw/<path below rwsdk>.
With --apply the definition goes after the file's includes, its `// match: _rcsid` line into the
file's data block and the range into config/splits.txt. Ids whose file is missing, unplaced or
already has an rcsid are listed and left."""
import os
import re
import sys

sys.path.insert(0, os.path.join(os.path.dirname(os.path.abspath(__file__)), '..'))
from xbe import Xbe  # noqa: E402

ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
args = sys.argv[1:]
apply = '--apply' in args
args = [a for a in args if a != '--apply']
LO, HI = (int(args[0], 16), int(args[1], 16)) if args else (0, 1 << 32)
image = Xbe(os.path.join(ROOT, 'orig', 'Game_XboxMultiplayer.xbe'))
splits = open(os.path.join(ROOT, 'config', 'splits.txt'), encoding='utf-8').read().split('\n')
free = []
for l in splits:
    p = l.split()
    if len(p) >= 4 and p[0].startswith('0x') and p[2] == '.rdata' and p[3] == '-':
        free.append((int(p[0], 16), int(p[1], 16)))
placed = set()
for l in open(os.path.join(ROOT, 'config', 'compiled.txt'), encoding='utf-8'):
    q = l.split()
    if len(q) >= 3 and q[0].startswith('0x'):
        placed.add(q[1])
HDR = "// Its data (PLAN M5): literals, constants and tables where the image has them.\n"
sec = next(s for s in image.sections if s['name'] == '.rdata')
data = bytes(image.read(sec['va'], sec['vsize']))
# files that kept another file's id: uvanim's keyframe files were copied from hanim's stdkey.c
# (the three follow rpuvanim's data in link order), and 2danim's gstate.c from fast2d's 2d one
OWN = {0x3EB10C: 'src/rw/plugin/uvanim/stdkey.c', 0x3EB14C: 'src/rw/plugin/uvanim/param.c',
       0x3EB190: 'src/rw/plugin/uvanim/linear.c', 0x3EE558: 'src/rw/tool/2danim/gstate.c',
       # 3.6's plcore/bafsys.c is unit_2AB6C0 (between bacamera and balist); os/xbox/osintf.c is
       # the tree's os/win copy; the collis files' ids are empty ("$ $"), in link order
       0x416458: 'src/rw/src/plcore/unit_2AB6C0.c', 0x4170FC: 'src/rw/os/win/osintf.c',
       0x4174F4: 'src/rw/plugin/collis/collquery.c', 0x417508: 'src/rw/plugin/collis/ctquery.c',
       0x417518: 'src/rw/plugin/collis/colldata.c', 0x417524: 'src/rw/plugin/collis/ctdata.c',
       0x41ABEC: 'src/rw/plugin/collis/collbuild.c',
       # the dev branch's plugin/uvanim/dict.c is the tree's tool/dict (linked just before rpuvanim)
       0x3EB06C: 'src/rw/tool/dict/rtdict.c'}
plan, seen = [], set()
for m in re.finditer(rb'@+\(#\)\$[^\x00]*\x00', data):
    a, e = sec['va'] + m.start(), sec['va'] + m.end()
    # the ids are 4-aligned: a leading '@' before that is the previous item's last byte (0x40)
    while a % 4 and data[a - sec['va']:a - sec['va'] + 1] == b'@':
        a += 1
    if not LO <= a < HI or not any(s <= a and e <= f for s, f in free):
        continue
    text = data[a - sec['va']:e - sec['va'] - 1].decode('latin-1')
    pm = re.search(r'//RenderWare/\S*?/rwsdk/(\S+?\.c)#\d+ \$$', text)
    src = OWN.get(a) or ('src/rw/' + pm.group(1) if pm else None)
    why = None
    if src is None:
        why = 'no file name'
    elif not os.path.exists(os.path.join(ROOT, src)):
        why = 'not in the tree'
    elif 'build/' + src[:-2] + '.obj' not in placed and not os.path.exists(os.path.join(ROOT, 'build', src[:-2] + '.obj')):
        why = 'object not placed'
    elif src in seen or re.search(r'\brcsid\b', open(os.path.join(ROOT, src), encoding='utf-8',
                                                      errors='replace').read()):
        why = 'has an rcsid'
    if src:
        seen.add(src)
    plan.append((a, e, text, src, why))
for a, e, text, src, why in plan:
    print('0x%06X %3X %-45s %s' % (a, e - a, src or '-', why or 'ok'), '' if src else text)
if not apply:
    sys.exit(0)
for a, e, text, src, why in plan:
    if why:
        continue
    full = os.path.join(ROOT, src)
    raw = open(full, 'rb').read()
    try:
        t, enc = raw.decode('utf-8'), 'utf-8'
    except UnicodeDecodeError:
        t, enc = raw.decode('latin-1'), 'latin-1'
    nl = '\r\n' if '\r\n' in t else '\n'
    t = t.replace('\r\n', '\n')
    first = re.search(r'^\{', t, re.M)
    # after the last #include outside any #if
    pos, depth, off = 0, 0, 0
    for line in t[:first.start() if first else len(t)].split('\n'):
        off += len(line) + 1
        d0 = re.match(r'\s*#\s*(\w+)', line)
        if d0 and d0.group(1) in ('if', 'ifdef', 'ifndef'):
            depth += 1
        elif d0 and d0.group(1) == 'endif':
            depth -= 1
        elif d0 and d0.group(1) == 'include' and depth == 0:
            pos = off
    d = ('\n/* RenderWare 3.6\'s RCS id string, which the image keeps (the 3.7.2 tree has none) */\n'
         'static const char rcsid[] = "%s";\n' % text.replace('\\', '\\\\').replace('"', '\\"'))
    t = t[:pos] + d + t[pos:]
    ml = '// match: _rcsid @ 0x%08X\n' % a
    if HDR in t:
        t = t.replace(HDR, HDR + ml, 1)
    else:
        mm = re.search(r'^// match: ', t, re.M)
        if mm:
            t = t[:mm.start()] + HDR + ml + '\n' + t[mm.start():]
        else:
            # a file without placed code: after the definition
            k = t.index(d) + len(d)
            t = t[:k] + '\n' + HDR + ml + t[k:]
    open(full, 'w', encoding=enc, newline=nl).write(t)
    res = []
    for l in splits:
        p = l.split()
        if len(p) >= 4 and p[0].startswith('0x') and p[3] == '-' and int(p[0], 16) <= a < int(p[1], 16):
            s0, e0, sc = int(p[0], 16), int(p[1], 16), p[2]
            if a > s0:
                res.append('0x%08X 0x%08X %-10s -' % (s0, a, sc))
            res.append('0x%08X 0x%08X %-10s _rcsid' % (a, e, sc))
            if e < e0:
                res.append('0x%08X 0x%08X %-10s -' % (e, e0, sc))
        else:
            res.append(l)
    splits = res
open(os.path.join(ROOT, 'config', 'splits.txt'), 'w', encoding='utf-8', newline='\n').write('\n'.join(splits))
