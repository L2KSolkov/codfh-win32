"""splitdoc.py OLD NEW 'TITLE' 'TEXT': after unitsplit.py, give the new unit its head comment and
a docs/units.md section after OLD's (PLAN M7).

The head comment replaces unitsplit's generic one: TITLE, then where it was split from."""
import os
import re
import sys

ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
old, new, title, text = sys.argv[1:5]
addr = int(new.split('_')[-1], 16)
src = next(os.path.join(ROOT, 'src', 'recovered', new + e) for e in ('.cpp', '.c')
           if os.path.exists(os.path.join(ROOT, 'src', 'recovered', new + e)))
raw = open(src, 'rb').read().decode('utf-8', errors='surrogateescape')
nl = '\r\n' if '\r\n' in raw else '\n'
t = raw.replace('\r\n', '\n')
generic = re.match(r'// (Split from|[^\n]*: split from) [^\n]*\n(// [^\n]*\n)*?// [^\n]*PLAN M7\)\.\n', t)
words, lines, cur = (title + ': split from %s.cpp at 0x%06X, an original object boundary '
                     '(docs/units.md; PLAN M7).' % (old, addr)).split(), [], '//'
for w in words:
    if len(cur) + 1 + len(w) > 99:
        lines.append(cur)
        cur = '//'
    cur += ' ' + w
lines.append(cur)
if generic:
    t = '\n'.join(lines) + '\n' + t[generic.end():]
    open(src, 'wb').write(t.replace('\n', nl).encode('utf-8', errors='surrogateescape'))
p = os.path.join(ROOT, 'docs', 'units.md')
d = open(p, encoding='utf-8').read()
m = re.search(r'\n## [^\n]*`src/recovered/%s\.c(pp)?`[^\n]*\n' % old, d)
nxt = d.find('\n## ', m.end())
nxt = len(d) if nxt < 0 else nxt
d = d[:nxt].rstrip('\n') + '\n\n## `src/recovered/%s%s`, %s, `0x%X`–\n\n%s\n' % (
    new, os.path.splitext(src)[1], title, addr, text) + d[nxt:]
open(p, 'w', encoding='utf-8', newline='\n').write(d)
print('ok')
