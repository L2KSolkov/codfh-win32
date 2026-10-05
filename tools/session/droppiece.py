"""droppiece.py NAME...: drop stand-in pieces that are only alignment padding (PLAN M7).

Each NAME is a data stand-in piece (src/xdk/standin_*.asm) whose bytes are zeros the link lays
down itself between aligned contributions (the fill after a literal before the next 4-aligned
one): its block and its config/compiled.txt row go; config/splits.txt keeps the range (the
placement build fills it from the image)."""
import os
import re
import sys

sys.path.insert(0, os.path.join(os.path.dirname(os.path.abspath(__file__)), '..'))
from xbe import Xbe  # noqa: E402

ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
img = Xbe(os.path.join(ROOT, 'orig', 'Game_XboxMultiplayer.xbe'))
cp = os.path.join(ROOT, 'config', 'compiled.txt')
lines = open(cp, encoding='utf-8').read().split('\n')
for name in sys.argv[1:]:
    row = next(l for l in lines if len(l.split()) >= 3 and l.split()[2] == name)
    a = int(row.split()[0], 16)
    nxt = min(int(l.split()[0], 16) for l in lines if len(l.split()) >= 3 and l.startswith('0x') and int(l.split()[0], 16) > a)
    assert nxt - a < 16 and not any(img.read(a, nxt - a)), '%s is not short zero fill' % name
    for f in os.listdir(os.path.join(ROOT, 'src', 'xdk')):
        if not (f.startswith('standin_') and f.endswith('.asm')):
            continue
        p = os.path.join(ROOT, 'src', 'xdk', f)
        raw = open(p, 'rb').read().decode('utf-8')
        nl = '\r\n' if '\r\n' in raw else '\n'
        L = raw.replace('\r\n', '\n').split('\n')
        key = '; // match: %s @ 0x%08X' % (name, a)
        if key not in L:
            continue
        i = L.index(key)
        j = i + 1
        while not L[j].startswith('; // match: ') and not re.match(r'^\w+ ENDS$', L[j]):
            j += 1
        del L[i:j]
        open(p, 'wb').write('\n'.join(L).replace('\n', nl).encode('utf-8'))
        break
    else:
        raise SystemExit('no block for ' + name)
    lines.remove(row)
    print('dropped', name, '(%d bytes)' % (nxt - a))
open(cp, 'w', encoding='utf-8', newline='\n').write('\n'.join(lines))
