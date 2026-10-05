"""staticpieces.py [--apply]: stand-in pieces named after a member's static (PLAN M7).

A stand-in piece row (src/xdk/standin_*.asm) whose name is a file-local function or datum an
installed or 5849 XDK member defines with the same bytes (relocation fields aside) at that
address is that member's static: only the member's own code reaches it, so its callers bind the
member's copy and the piece, unreferenced, drops out of the link (hrtf.obj's FloatToLong). The
row names the member and the piece leaves the asm. Prints the plan; --apply edits."""
import glob
import os
import re
import sys

sys.path.insert(0, os.path.join(os.path.dirname(os.path.abspath(__file__)), '..'))
from coff import Coff  # noqa: E402
from xbe import Xbe  # noqa: E402

ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
apply = '--apply' in sys.argv
img = Xbe(os.path.join(ROOT, 'orig', 'Game_XboxMultiplayer.xbe'))
MADE = re.compile(r'^_?(sub|unk|loc|off|dword|byte|word|stru|flt|dbl|asc|a)_[0-9A-F]+$')
statics = {}
for p in glob.glob(os.path.join(ROOT, 'build', 'xdk', '*', '*.obj')):
    rel = os.path.relpath(p, ROOT).replace(os.sep, '/')
    try:
        c = Coff(p)
    except Exception:
        continue
    for x in c.symbol_list:
        if x['section'] > 0 and x['class'] == 3 and x['name'][:1] in '_?' \
                and x['name'] != c.sections[x['section'] - 1]['name']:
            statics.setdefault(x['name'], []).append((rel, c, x))
plan = {}
for l in open(os.path.join(ROOT, 'config', 'compiled.txt'), encoding='utf-8'):
    q = l.split()
    if len(q) < 3 or not q[1].startswith('build/src/xdk/standin_') or MADE.match(q[2]) or q[2] not in statics:
        continue
    a = int(q[0], 16)
    for rel, c, x in sorted(statics[q[2]], key=lambda r: ('/xdklib_' not in r[0], r[0])):
        s = c.sections[x['section'] - 1]
        d = bytes(s['data'])[x['value']:]
        later = sorted(y['value'] for y in c.symbol_list if y['section'] == x['section'] and y['value'] > x['value'])
        if later:
            d = d[:later[0] - x['value']]
        if not d:
            continue
        ra = set()
        for va, si, t in s['relocs']:
            ra.update(range(va - x['value'], va - x['value'] + 4))
        try:
            i = img.read(a, len(d))
        except Exception:
            continue
        if all(d[j] == i[j] for j in range(len(d)) if j not in ra):
            plan[a] = (q[2], rel)
            break
for a, (n, rel) in sorted(plan.items()):
    print('0x%08X %s -> %s' % (a, n[:60], rel))
print(len(plan), 'pieces')
if not apply:
    sys.exit(0)
cp = os.path.join(ROOT, 'config', 'compiled.txt')
lines = open(cp, encoding='utf-8').read().split('\n')
for k, l in enumerate(lines):
    q = l.split()
    if len(q) >= 3 and q[0].startswith('0x') and int(q[0], 16) in plan and q[1].startswith('build/src/xdk/standin_'):
        lines[k] = '%s %s %s' % (q[0], plan[int(q[0], 16)][1], q[2])
open(cp, 'w', encoding='utf-8', newline='\n').write('\n'.join(lines))
for p in glob.glob(os.path.join(ROOT, 'src', 'xdk', 'standin_*.asm')):
    raw = open(p, 'rb').read().decode('utf-8')
    nl = '\r\n' if '\r\n' in raw else '\n'
    L = raw.replace('\r\n', '\n').split('\n')
    out, i, changed = [], 0, False
    while i < len(L):
        m = re.match(r'^; // match: (\S+) @ 0x([0-9A-F]{8})$', L[i])
        if m and int(m.group(2), 16) in plan and plan[int(m.group(2), 16)][0] == m.group(1):
            j = i + 1
            while j < len(L) and not L[j].startswith('; // match: ') and not re.match(r'^\w+ ENDS$', L[j]):
                j += 1
            i, changed = j, True
            continue
        out.append(L[i])
        i += 1
    if changed:
        t = '\n'.join(out)
        for a, (n, rel) in plan.items():
            t = re.sub(r'^PUBLIC %s\n' % re.escape(n), '', t, flags=re.M)
        t = re.sub(r'\n(\w+) SEGMENT [^\n]*\n\s*\n\1 ENDS\n', '\n', t)
        open(p, 'wb').write(t.replace('\n', nl).encode('utf-8'))
