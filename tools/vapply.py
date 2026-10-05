"""vapply.py VARS.py NAME SRC [OUT]: apply variant NAME of a ptry VARS file
to SRC (first occurrence of each old string) and write OUT (default SRC), so
the variant can be inspected with unitcheck/ncmp -v or kept."""
import sys

varf, name, src = sys.argv[1:4]
out = sys.argv[4] if len(sys.argv) > 4 else src
g = {}
exec(open(varf, encoding='utf-8').read(), g)
try:
    enc = 'utf-8'
    t = open(src, encoding=enc).read()
except UnicodeDecodeError:
    enc = 'latin-1'
    t = open(src, encoding=enc).read()
for old, new in g['VS'][name]:
    if old not in t:
        sys.exit('missing: %r' % old[:60])
    t = t.replace(old, new, 1)
open(out, 'w', encoding=enc).write(t)
