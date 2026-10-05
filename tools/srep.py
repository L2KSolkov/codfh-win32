"""srep.py FILE EDITS: apply exact replacements to a CRLF-or-LF file. EDITS is
a text file of blocks separated by lines '=====' (old) and '-----' (new):
old text
-----
new text
=====
..."""
import sys
p, e = sys.argv[1], sys.argv[2]
raw = open(p, encoding='utf-8', newline='').read()
crlf = '\r\n' in raw
t = raw.replace('\r\n', '\n')
for blk in open(e, encoding='utf-8').read().split('=====\n'):
    if not blk.strip():
        continue
    old, new = blk.split('-----\n')
    if old not in t:
        sys.exit('NOT FOUND:\n' + old)
    t = t.replace(old, new, 1)
if crlf:
    t = t.replace('\n', '\r\n')
open(p, 'w', encoding='utf-8', newline='').write(t)
print('ok')
