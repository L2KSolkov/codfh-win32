"""bulkvt.py LIST UNIT [MAX]: place the byte-identical vtables LIST (vtscan.py output) names
for build/src/recovered/UNIT.obj (at most MAX): datapieces.py --apply (splits.txt ranges and
alias rows for unplaced slot functions), `// match:` lines before the unit's first one, then
config/compiled.txt restored, so `CMUNIT=UNIT python tools/cmf.py -m "..." ADDRS` (printed)
commits them."""
import os
import subprocess
import sys

ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
listing, unit = sys.argv[1], sys.argv[2]
limit = int(sys.argv[3]) if len(sys.argv) > 3 else 1000
obj = 'build/src/recovered/%s.obj' % unit
items = []
for line in open(listing, encoding='utf-8'):
    p = line.split()
    if len(p) >= 3 and p[0].startswith('0x') and p[2] == obj:
        items.append((int(p[0], 16), p[1]))
items = items[:limit]
if not items:
    sys.exit('nothing for ' + unit)
compiled = os.path.join(ROOT, 'config', 'compiled.txt')
saved = open(compiled, encoding='utf-8').read()
r = subprocess.run([sys.executable, os.path.join(ROOT, 'tools', 'session', 'datapieces.py'), '--apply', obj]
                   + ['0x%X=%s' % (a, n) for a, n in items], cwd=ROOT, capture_output=True, text=True)
ok = [l for l in r.stdout.splitlines() if ' identical ' in l]
if len(ok) != len(items):
    print(r.stdout + r.stderr)
    sys.exit('not all identical')
open(compiled, 'w', encoding='utf-8', newline='\n').write(saved)
src = os.path.join(ROOT, 'src', 'recovered', unit + '.cpp')
t = open(src, encoding='utf-8').read()
i = t.index('// match: ')
block = ('// Vtables (.rdata, PLAN M5): each in its own placement range (config/splits.txt).\n'
         + ''.join('// match: %s @ 0x%08X\n' % (n, a) for a, n in items) + '\n')
t = t[:i] + block + t[i:]
open(src, 'w', encoding='utf-8', newline='\n').write(t)
print(' '.join('0x%X' % a for a, _ in items))
