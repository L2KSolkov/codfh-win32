"""rawptrs.py [--apply]: stand-in data pieces' raw dwords that are a row's address (PLAN M7).

A pointer whose target's name is too long for MASM (a 250-character template instance) stayed
`db b0, b1, b2, b3` in src/xdk/standin_*.asm, so it carries no relocation: the link sees no
reference, /OPT:REF drops the function, and the slot is not relocated. Each such line becomes
`dd _sub_XXXXXX` (an address name match.py, xbelink and xdkrepack resolve to the row there);
prints the plan; --apply edits (adding the EXTERN)."""
import glob
import os
import re
import sys

ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
rows = {}
for l in open(os.path.join(ROOT, 'config', 'compiled.txt'), encoding='utf-8'):
    q = l.split()
    if len(q) >= 3 and q[0].startswith('0x'):
        rows.setdefault(int(q[0], 16), q[2])
n = 0
for p in sorted(glob.glob(os.path.join(ROOT, 'src', 'xdk', 'standin_*.asm'))):
    raw = open(p, 'rb').read().decode('utf-8')
    nl = '\r\n' if '\r\n' in raw else '\n'
    L = raw.replace('\r\n', '\n').split('\n')
    seg_data = False
    new_ext = set()
    out = []
    for l in L:
        if re.match(r'^\w+ SEGMENT ', l):
            seg_data = "'DATA'" in l
        m = re.match(r"^(\s+)db 0([0-9A-F]{2})h, 0([0-9A-F]{2})h, 0([0-9A-F]{2})h, 0([0-9A-F]{2})h\s*$", l)
        if seg_data and m:
            v = int(m.group(5) + m.group(4) + m.group(3) + m.group(2), 16)
            if v in rows and len(rows[v]) > 240:
                nm = '_sub_%06X' % v
                print('%s: %s -> %s (%s...)' % (os.path.basename(p), l.strip(), nm, rows[v][:50]))
                l = '%sdd %s' % (m.group(1), nm)
                new_ext.add(nm)
                n += 1
        out.append(l)
    if new_ext and '--apply' in sys.argv:
        t = '\n'.join(out)
        for nm in sorted(new_ext):
            if not re.search(r'^(EXTERN|PUBLIC) %s\b' % nm, t, re.M) and not re.search(r'^%s\b' % nm, t, re.M):
                first = re.search(r'^EXTERN ', t, re.M)
                pos = first.start() if first else t.index('\n') + 1
                t = t[:pos] + 'EXTERN %s:BYTE\n' % nm + t[pos:]
        open(p, 'wb').write(t.replace('\n', nl).encode('utf-8'))
print(n, 'raw pointers')
