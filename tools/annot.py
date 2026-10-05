"""annot.py SRC NAME:SYM:ADDR ...: put '// match: SYM @ ADDR' above NAME's definition
(the line before 'NAME(' at column 0, i.e. above its return type line)."""
import sys
src = sys.argv[1]
raw = open(src, 'rb').read()
try:
    t = raw.decode('utf-8'); enc = 'utf-8'
except UnicodeDecodeError:
    t = raw.decode('latin-1'); enc = 'latin-1'
lines = t.split('\n')
for spec in sys.argv[2:]:
    name, sym, addr = spec.split(':')
    idx = None
    for i, l in enumerate(lines):
        if l.startswith(name + '(') and not l.rstrip().endswith(';'):
            idx = i
            break
    if idx is None:
        sys.exit('no definition for ' + name)
    # the return type line(s) above
    j = idx - 1
    while j > 0 and lines[j].strip() and not lines[j].strip().startswith(('*/', '}', '//')) and not lines[j].startswith(' *'):
        j -= 1
    ins = j + 1
    tag = '// match: %s @ 0x%08X' % (sym, int(addr, 16))
    if lines[ins - 1].startswith('// match:'):
        continue
    lines.insert(ins, tag)
open(src, 'wb').write('\n'.join(lines).encode(enc))
print('ok')
