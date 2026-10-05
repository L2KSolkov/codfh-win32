"""addrows.py SRC...: insert compiled.txt rows for each `// match: SYM @ ADDR` in the sources (sorted by address)."""
import os as _os_repo
_REPO = _os_repo.path.dirname(_os_repo.path.dirname(_os_repo.path.dirname(_os_repo.path.abspath(__file__))))  # the repository root, from this file's location
import re, sys, os
P = _os_repo.path.join(_REPO, 'config/compiled.txt')
lines = open(P, encoding='utf-8').read().split('\n')
have = set(l.split()[0] for l in lines if l.startswith('0x'))
new = []
for src in sys.argv[1:]:
    obj = 'build/' + os.path.splitext(src.replace(chr(92), '/'))[0] + '.obj'
    for m in re.finditer(r'// match: (\S+) @ (0x[0-9A-Fa-f]+)', open(src, encoding='utf-8').read()):
        a = '0x%08X' % int(m.group(2), 16)
        if a not in have:
            new.append((int(a, 16), '%s %s %s' % (a, obj, m.group(1))))
for a, row in sorted(new):
    idx = None
    for k, l in enumerate(lines):
        if l.startswith('0x') and int(l.split()[0], 16) > a:
            idx = k
            break
    if idx is None:
        idx = len(lines) - (1 if lines[-1] == '' else 0)
    lines.insert(idx, row)
    print(row)
open(P, 'w', encoding='utf-8', newline='\n').write('\n'.join(lines))
