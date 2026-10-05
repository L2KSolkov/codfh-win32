"""v3dconsts.py [--apply]: the units' axis constants as RwV3d (PLAN M5/M7).

unitconsts.py defined each dword of the units' header constants as its own float, but the code
reads some as RwV3d (`extern const RwV3d stru_X;`): those three floats are one RwV3d. For each
RwV3d name the sources declare at an address whose first float the owner unit defines as
`flt_ADDR`, the three `flt_` definitions become `extern const RwV3d NAME = {x, y, z};`,
non-const declarations of NAME become const, and the match lines, config/splits.txt and
config/compiled.txt rows follow (one 12-byte piece)."""
import os
import re
import struct
import sys

sys.path.insert(0, os.path.join(os.path.dirname(os.path.abspath(__file__)), '..'))
from xbe import Xbe  # noqa: E402

ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
apply = '--apply' in sys.argv
image = Xbe(os.path.join(ROOT, 'orig', 'Game_XboxMultiplayer.xbe'))
texts = {}
for top in ('src', 'include'):
    for dp, _dn, fs in os.walk(os.path.join(ROOT, top)):
        for f in fs:
            if f.endswith(('.c', '.cpp', '.h')):
                texts[os.path.join(dp, f)] = open(os.path.join(dp, f), encoding='utf-8', errors='replace').read()
names = {}
for p, t in texts.items():
    for m in re.finditer(r'^extern\s+(const\s+)?RwV3d\s+((?:stru|unk)_([0-9A-F]{6}))\s*;', t, re.M):
        names[m.group(2)] = int(m.group(3), 16)
plan = []
for nm, a in sorted(names.items(), key=lambda x: x[1]):
    defs = [p for p, t in texts.items() if re.search(r'^extern const RwReal flt_%06X = ' % a, t, re.M)]
    if len(defs) != 1:
        continue
    t = texts[defs[0]]
    if not all(re.search(r'^extern const RwReal flt_%06X = ' % (a + k), t, re.M) for k in (4, 8)):
        continue
    plan.append((nm, a, defs[0]))
for nm, a, p in plan:
    print('0x%06X %-12s %s' % (a, nm, os.path.relpath(p, ROOT)))
print(len(plan))
if not apply:
    sys.exit(0)
cfg = open(os.path.join(ROOT, 'config', 'compiled.txt'), encoding='utf-8').read().split('\n')
sp = open(os.path.join(ROOT, 'config', 'splits.txt'), encoding='utf-8').read().split('\n')
for nm, a, p in plan:
    v = struct.unpack('<3f', bytes(image.read(a, 12)))
    fl = ', '.join(('%.1f' % x if x == int(x) else repr(x)) + 'f' for x in v)
    t = open(p, encoding='utf-8').read()
    for k in (0, 4, 8):
        t = re.sub(r'^// 0x%08X\nextern const RwReal flt_%06X = [^\n]*\n' % (a + k, a + k), '', t, flags=re.M)
        t = re.sub(r'^extern const RwReal flt_%06X = [^\n]*\n' % (a + k), '', t, flags=re.M)
    # the vector where its first float was (sorted block: insert before the next item)
    import importlib
    sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
    open(p, 'w', encoding='utf-8', newline='\n').write(t)
    import m5defs
    m5defs.insert(p, a, 'extern const RwV3d %s = { %s };' % (nm, fl))
    t = open(p, encoding='utf-8').read()
    t = t.replace('// match: ?flt_%06X@@3MB @ 0x%08X\n' % (a, a), '// match: ?%s@@3URwV3d@@B @ 0x%08X\n' % (nm, a))
    for k in (4, 8):
        t = t.replace('// match: ?flt_%06X@@3MB @ 0x%08X\n' % (a + k, a + k), '')
    open(p, 'w', encoding='utf-8', newline='\n').write(t)
    cfg = [l for l in cfg if not re.match(r'^0x%08X \S+ \?flt_%06X@@3MB$' % (a + 4, a + 4), l)
           and not re.match(r'^0x%08X \S+ \?flt_%06X@@3MB$' % (a + 8, a + 8), l)]
    cfg = [re.sub(r'^(0x%08X \S+ )\?flt_%06X@@3MB$' % (a, a), r'\g<1>?%s@@3URwV3d@@B' % nm, l) for l in cfg]
    out = []
    for l in sp:
        q = l.split()
        if len(q) >= 4 and q[0] == '0x%08X' % a and q[3] == '?flt_%06X@@3MB' % a:
            out.append('0x%08X 0x%08X %-10s ?%s@@3URwV3d@@B' % (a, a + 12, q[2], nm))
        elif len(q) >= 4 and q[0] in ('0x%08X' % (a + 4), '0x%08X' % (a + 8)) and q[3].startswith('?flt_'):
            continue
        else:
            out.append(l)
    sp = out
# non-const declarations of the vectors become const
for p in texts:
    t = open(p, encoding='utf-8', errors='replace').read()
    t2 = t
    for nm, a, _p in plan:
        t2 = re.sub(r'^extern\s+RwV3d\s+%s\s*;' % nm, 'extern const RwV3d %s;' % nm, t2, flags=re.M)
    if t2 != t:
        open(p, 'w', encoding='utf-8', newline='\n').write(t2)
open(os.path.join(ROOT, 'config', 'compiled.txt'), 'w', encoding='utf-8', newline='\n').write('\n'.join(cfg))
open(os.path.join(ROOT, 'config', 'splits.txt'), 'w', encoding='utf-8', newline='\n').write('\n'.join(sp))
print('applied')
