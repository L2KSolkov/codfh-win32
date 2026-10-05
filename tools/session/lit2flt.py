"""lit2flt.py [--apply]: pooled literals the sources read through address-named externs (PLAN M7).

Some units declare `extern const RwReal flt_ADDR;` for an address that is a pooled `__real@`
literal (placed from another unit); the real link has no such symbol. Each such use becomes the
literal itself (the shortest text that rounds to the same float); the extern declarations go.
The build decides: a unit whose functions stop matching is reported for a manual look."""
import os
import re
import struct
import sys

sys.path.insert(0, os.path.join(os.path.dirname(os.path.abspath(__file__)), '..'))
from xbe import Xbe  # noqa: E402

ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
apply = '--apply' in sys.argv
image = Xbe(os.path.join(ROOT, 'orig', 'Game_XboxMultiplayer.xbe'))
lits = {}
for l in open(os.path.join(ROOT, 'config', 'compiled.txt'), encoding='utf-8'):
    q = l.split()
    if len(q) >= 3 and q[0].startswith('0x') and q[2].startswith('__real@') and len(q[2]) == 15:
        lits[int(q[0], 16)] = q[2]
unres = set(l.strip() for l in open(os.path.join(ROOT, 'build', 'm7', 'unresolved.txt')) if l.strip())
want = {}
for n in unres:
    m = re.match(r'^\?flt_([0-9A-F]{6})@@3MB$', n)
    if m and int(m.group(1), 16) in lits:
        want['flt_' + m.group(1)] = struct.unpack('<f', bytes(image.read(int(m.group(1), 16), 4)))[0]


def lit(v):
    for d in range(1, 10):
        t = '%.*f' % (d, v)
        if struct.pack('<f', float(t)) == struct.pack('<f', v):
            return t + 'f'
    for d in range(1, 10):
        t = '%.*e' % (d, v)
        if struct.pack('<f', float(t)) == struct.pack('<f', v):
            return t + 'f'
    return repr(v) + 'f'


changed = []
for top in ('src', 'include'):
    for dp, _dn, fs in os.walk(os.path.join(ROOT, top)):
        for f in fs:
            if not f.endswith(('.c', '.cpp')):
                continue
            p = os.path.join(dp, f)
            t = open(p, encoding='utf-8', errors='replace').read()
            t2 = t
            for nm, v in want.items():
                if nm not in t2:
                    continue
                L = lit(v)
                # the uses, not the declarations (a unit put back still reads the name)
                out = []
                for line in t2.split('\n'):
                    if re.match(r'^\s*extern\b', line) or line.lstrip().startswith('//'):
                        out.append(line)
                        continue
                    out.append(re.sub(r'\b%s\b' % nm, '(%s)' % L if L.startswith('-') else L, line))
                t2 = '\n'.join(out)
            if t2 != t:
                changed.append(p)
                if apply:
                    open(p, 'w', encoding='utf-8', newline='\n').write(t2)
print(len(want), 'names;', len(changed), 'files')
for p in changed:
    print(' ', os.path.relpath(p, ROOT))
