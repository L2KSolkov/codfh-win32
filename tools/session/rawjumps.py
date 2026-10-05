"""rawjumps.py [--apply]: stand-in pieces' raw call/jmp encodings whose targets are member rows
become symbolic (PLAN M7).

A piece transcribed with a raw `db 0E8h/0E9h, rel32` (a call or jump into a neighbouring piece of
the same segment) keeps its bytes in the placement link, but once the target is an installed
member's function (piece2member.py) the real link places the target elsewhere and nothing
relocates the field. Each such line whose target is a config/compiled.txt row of a build/xdk/
member becomes `call NAME` / `jmp NAME` (link.exe encodes both rel32 for an external), with an
EXTERN. Prints the plan; --apply edits src/xdk/standin_*.asm."""
import glob
import os
import re
import sys

ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
apply = '--apply' in sys.argv
rows = {}
for l in open(os.path.join(ROOT, 'config', 'compiled.txt'), encoding='utf-8'):
    q = l.split()
    if len(q) >= 3 and q[0].startswith('0x') and q[1].startswith('build/xdk/'):
        rows.setdefault(int(q[0], 16), q[2])
RAW = re.compile(r'^(\s+)db 0(E8|E9)h, 0[0-9A-F]{2}h, 0[0-9A-F]{2}h, 0[0-9A-F]{2}h, 0[0-9A-F]{2}h\s+; (call|jmp) 0x([0-9a-f]+)\s*$')
total = 0
for p in sorted(glob.glob(os.path.join(ROOT, 'src', 'xdk', 'standin_*.asm'))):
    raw = open(p, 'rb').read().decode('utf-8')
    nl = '\r\n' if '\r\n' in raw else '\n'
    L = raw.replace('\r\n', '\n').split('\n')
    need = set()
    n = 0
    for i, x in enumerate(L):
        m = RAW.match(x)
        if not m:
            continue
        t = int(m.group(4), 16)
        if t not in rows:
            continue
        name = rows[t]
        L[i] = '%s%s %s   ; 0x%X' % (m.group(1), m.group(3), name, t)
        need.add(name)
        n += 1
    if not n:
        continue
    total += n
    print('%s: %d' % (os.path.basename(p), n))
    t = '\n'.join(L)
    for name in sorted(need):
        if not re.search(r'^EXTERN %s:' % re.escape(name), t, re.M) and not re.search(r'^%s:' % re.escape(name), t, re.M):
            first = re.search(r'^EXTERN ', t, re.M)
            pos = first.start() if first else t.index('\n') + 1
            t = t[:pos] + 'EXTERN %s:NEAR\n' % name + t[pos:]
    if apply:
        open(p, 'wb').write(t.replace('\n', nl).encode('utf-8'))
print(total, 'lines')
