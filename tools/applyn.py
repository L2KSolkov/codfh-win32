"""applyn.py SOURCE ADDR 'S=name ...': rename var_S in the function at ADDR and
put its function-scope declarations of those names highest slot first."""
import sys, re
src, addr, pairs = sys.argv[1], int(sys.argv[2], 16), sys.argv[3].split()
t = open(src, encoding='utf-8').read()
m = re.search(r'^// match: \S+ @ 0x0*%X\n' % addr, t, re.M)
e = t.find('\n// match: ', m.end())
e = len(t) if e < 0 else e + 1
blk = t[m.start():e]
mp = dict(p.split('=') for p in pairs)
for s, n in mp.items():
    blk = re.sub(r'\bvar_%s\b' % s, n, blk)
# reorder the declaration lines at function scope (4-space indent, before first blank line after '{')
a = blk.index('{\n') + 2
z = blk.index('\n\n', a)
lines = blk[a:z].split('\n')
names = set(mp.values())
def slot(l):
    mm = re.search(r'(\w+);$', l)
    n = mm.group(1) if mm else ''
    for s, v in mp.items():
        if v == n: return int(s, 16)
    return None
dec = [l for l in lines if slot(l) is not None]
rest = [l for l in lines if slot(l) is None]
dec.sort(key=lambda l: -slot(l))
blk = blk[:a] + '\n'.join(rest + dec) + blk[z:]
NOTE = '// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).' + chr(10)
hl = blk.index(chr(10)) + 1
if not blk[hl:].startswith(NOTE):
    blk = blk[:hl] + NOTE + blk[hl:]
t = t[:m.start()] + blk + t[e:]
open(src, 'w', encoding='utf-8', newline='\n').write(t)
