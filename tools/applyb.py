"""applyb.py SRC ADDR 'S=name ...': in the function matched at ADDR, rename
lv_S to name for each pair and rewrite its function-scope declarations of
those names (lines `    TYPE lv_S;` or with arrays) farthest slot first,
right after the opening brace. Writes SRC in place."""
import re
import sys

src, addr, pairs = sys.argv[1], int(sys.argv[2], 16), sys.argv[3].split()
t = open(src, encoding='utf-8').read()
m = re.search(r'^// match: \S+ @ 0x0*%X\n' % addr, t, re.M)
a = t.index('\n{\n', m.end()) + 3
z = t.index('\n}\n', a)
body = t[a:z]
mp = dict(p.split('=') for p in pairs)
decls = []
for s in mp:
    d = re.search(r'^    ([^\n;=()]*?)\blv_%s\b(\[[^\]]*\])?;\n' % s, body, re.M)
    if d:
        decls.append((int(s, 16), '    %slv_%s%s;\n' % (d.group(1), s, d.group(2) or '')))
        body = body[:d.start()] + body[d.end():]
decls.sort(reverse=True)
body = ''.join(x[1] for x in decls) + body
for s, n in mp.items():
    body = re.sub(r'\blv_%s\b' % s, n, body)
t = t[:a] + body + t[z:]
open(src, 'w', encoding='utf-8', newline='\n').write(t)
print('ok', len(decls), 'declarations reordered')
