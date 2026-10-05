"""movedata.py SRC DST NAME...: move data definitions from unit SRC to unit DST (PLAN M7: a split
unit's data belongs to the original object whose functions it sits with in the image).

For each NAME (the C++ name, e.g. flt_3CDE08): its `// 0xADDR` comment and definition (one line,
or through the closing `};`) leave SRC and go, in the given order, under DST's data comment (made
after its #include lines when it has none); its `// match:` line moves to the match lines after DST's definitions;
config/compiled.txt rows of the name get DST's object."""
import os
import re
import sys

ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
HEAD = "// Its data definitions (PLAN M5), in the image's address order.\n"


def rd(p):
    raw = open(p, 'rb').read().decode('utf-8')
    return raw.replace('\r\n', '\n'), ('\r\n' if '\r\n' in raw else '\n')


def wr(p, t, nl):
    open(p, 'wb').write(t.replace('\n', nl).encode('utf-8'))


src, dst = sys.argv[1:3]
names = sys.argv[3:]
s, snl = rd(src)
d, dnl = rd(dst)
defs, matches, mangled = [], [], []
for n in names:
    m = re.search(r'^(// 0x[0-9A-F]{8}\n)?((?:extern |static )?(?:const )?[\w:<> ]+?[ *]%s\b[^\n]*\n)' % re.escape(n), s, re.M)
    if not m:
        raise SystemExit('no definition of %s' % n)
    start, end = m.start(), m.end()
    if m.group(2).rstrip().endswith('{') or ('{' in m.group(2) and '}' not in m.group(2)):
        end = s.index('\n};\n', end) + 4
    defs.append(s[start:end])
    s = s[:start] + s[end:]
    mm = re.search(r'^// match: (\S*\b%s\b\S*) @ 0x[0-9A-F]{8}\n' % re.escape(n), s, re.M)
    if mm:
        matches.append(mm.group(0))
        mangled.append(mm.group(1))
        s = s[:mm.start()] + s[mm.end():]
if HEAD not in d:
    k = [m.end() for m in re.finditer(r'^#include [^\n]*\n', d, re.M)][-1]
    d = d[:k] + '\n' + HEAD + '\n' + d[k:]
k = d.index(HEAD) + len(HEAD)
# among the definitions already there (up to the first blank line), in address order
blank = d.find('\n\n', k)
end = k if blank < 0 or d[k:k + 1] == '\n' else blank + 1
first_addr = int(re.match(r'// 0x([0-9A-F]{8})', defs[0]).group(1), 16) if defs[0].startswith('// 0x') else 1 << 32
for m in re.finditer(r'^// (?:0x([0-9A-F]{8})|End of its data definitions\.)\n', d[k:end], re.M):
    if m.group(1) is None or int(m.group(1), 16) > first_addr:
        end = k + m.start()
        break
k = end
d = d[:k] + ''.join(defs) + d[k:]
# match lines: right after the definitions
k = d.index(''.join(defs)) + len(''.join(defs))
nxt = re.match(r'(?:// match: \S+ @ 0x[0-9A-F]{8}\n)*', d[k + 1:]) if d[k:k + 1] == '\n' else None
if nxt and nxt.group(0):
    k = k + 1 + nxt.end()
    d = d[:k] + ''.join(matches) + d[k:]
else:
    d = d[:k] + '\n' + ''.join(matches) + d[k:]
wr(src, s, snl)
wr(dst, d, dnl)
so = 'build/' + os.path.splitext(src.replace(os.sep, '/'))[0] + '.obj'
do = 'build/' + os.path.splitext(dst.replace(os.sep, '/'))[0] + '.obj'
path = os.path.join(ROOT, 'config', 'compiled.txt')
lines = open(path, encoding='utf-8').read().split('\n')
n = 0
for i, l in enumerate(lines):
    q = l.split()
    if len(q) >= 3 and q[1] == so and q[2] in mangled:
        q[1] = do
        lines[i] = ' '.join(q)
        n += 1
open(path, 'w', encoding='utf-8', newline='\n').write('\n'.join(lines))
print('%d definitions, %d match lines, %d rows' % (len(defs), len(matches), n))
