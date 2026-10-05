"""movematch.py SRC DST SYMBOL...: move `// match: SYMBOL @ 0xADDR` lines from unit SRC to unit DST
and give the symbols' config/compiled.txt rows DST's object (PLAN M7: a literal or table text that
follows its data or function into another unit). The lines go before DST's first match line
(its data block)."""
import os
import re
import sys

ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))


def rd(p):
    raw = open(p, 'rb').read().decode('utf-8')
    return raw.replace('\r\n', '\n'), ('\r\n' if '\r\n' in raw else '\n')


def wr(p, t, nl):
    open(p, 'wb').write(t.replace('\n', nl).encode('utf-8'))


src, dst = sys.argv[1:3]
names = sys.argv[3:]
s, snl = rd(src)
d, dnl = rd(dst)
moved = []
for n in names:
    m = re.search(r'^// match: %s @ 0x[0-9A-F]{8}\n' % re.escape(n), s, re.M)
    if not m:
        print('no match line for', n)
        continue
    moved.append(m.group(0))
    s = s[:m.start()] + s[m.end():]
first = re.search(r'^// match: ', d, re.M)
k = first.start() if first else len(d)
d = d[:k] + ''.join(moved) + d[k:]
wr(src, s, snl)
wr(dst, d, dnl)
so = 'build/' + os.path.splitext(src.replace(os.sep, '/'))[0] + '.obj'
do = 'build/' + os.path.splitext(dst.replace(os.sep, '/'))[0] + '.obj'
path = os.path.join(ROOT, 'config', 'compiled.txt')
lines = open(path, encoding='utf-8').read().split('\n')
n = 0
for i, l in enumerate(lines):
    q = l.split()
    if len(q) >= 3 and q[1] == so and q[2] in names:
        q[1] = do
        lines[i] = ' '.join(q)
        n += 1
open(path, 'w', encoding='utf-8', newline='\n').write('\n'.join(lines))
print('%d match lines, %d rows' % (len(moved), n))
