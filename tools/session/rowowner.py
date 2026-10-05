"""rowowner.py OLD NEW...: compiled.txt rows of object OLD whose name OLD's compiled object no longer
defines but one of the NEW objects does get that object (PLAN M7: after a unit split, the
literals and strings only the moved functions use). Objects are build/... .obj paths."""
import os
import re
import sys

sys.path.insert(0, os.path.join(os.path.dirname(os.path.abspath(__file__)), '..'))
from coff import Coff  # noqa: E402

ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))


def defined(o):
    return set(s['name'] for s in Coff(os.path.join(ROOT, o)).symbol_list if s['section'] > 0)


old = sys.argv[1]
new = sys.argv[2:]
have = defined(old)
others = [(o, defined(o)) for o in new]
path = os.path.join(ROOT, 'config', 'compiled.txt')
lines = open(path, encoding='utf-8').read().split('\n')
n = 0
for i, l in enumerate(lines):
    q = l.split()
    if len(q) >= 3 and q[1] == old and q[2] not in have:
        # an EH piece (__ehhandler$NAME-0x.., >1, >1>8) goes with its function
        key = q[2]
        if key.startswith('__ehhandler$'):
            key = re.split(r'(?:-0x[0-9A-Fa-f]+|-\d+|>\d.*)$', key[len('__ehhandler$'):])[0]
            if key in have:
                continue
        for o, names in others:
            if key in names:
                q[1] = o
                lines[i] = ' '.join(q)
                n += 1
                break
        else:
            print('nowhere: %s %s' % (q[0], q[2]))
open(path, 'w', encoding='utf-8', newline='\n').write('\n'.join(lines))
print(n, 'rows')
