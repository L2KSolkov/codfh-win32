"""pieces2rows.py PIECE[,PIECE...]=ADDR:OBJ:NAME[,ADDR:OBJ:NAME...] ...: stand-in pieces that are
member functions (or data) the image holds whole (PLAN M7).

Each argument names the pieces (src/xdk/standin_*.asm rows) to remove and the member rows that
take their place. Every new row's bytes are checked against the image (relocation fields aside)
over the member symbol's extent (to the next symbol of its section, or the function's end), and
the new rows must cover the pieces' extents exactly. config/splits.txt keeps its ranges (the
placement build fills unnamed ones from the image)."""
import os
import re
import sys

sys.path.insert(0, os.path.join(os.path.dirname(os.path.abspath(__file__)), '..'))
from coff import Coff  # noqa: E402
from xbe import Xbe  # noqa: E402

def write(path, data):
    """Writes PATH (bytes), retrying while another process (an indexer) holds it."""
    import time
    for _ in range(50):
        try:
            open(path, 'wb').write(data)
            return
        except OSError:
            time.sleep(0.2)
    raise SystemExit('cannot write ' + path)


ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
img = Xbe(os.path.join(ROOT, 'orig', 'Game_XboxMultiplayer.xbe'))
cp = os.path.join(ROOT, 'config', 'compiled.txt')
lines = open(cp, encoding='utf-8').read().split('\n')
rowat = {}
for k, l in enumerate(lines):
    q = l.split()
    if len(q) >= 3 and q[0].startswith('0x'):
        rowat[q[2]] = (int(q[0], 16), k)
allrows = sorted(int(l.split()[0], 16) for l in lines if len(l.split()) >= 3 and l.startswith('0x'))


def extent(a):
    return min(x for x in allrows if x > a)


for arg in sys.argv[1:]:
    left, right = arg.split('=')
    pieces = left.split(',')
    news = [r.split(':', 2) for r in right.split(',')]
    lo = min(rowat[p][0] for p in pieces)
    hi = max(extent(rowat[p][0]) for p in pieces)
    covered = []
    for a, obj, name in news:
        a = int(a, 16)
        c = Coff(os.path.join(ROOT, obj))
        x = next(s for s in c.symbol_list if s['section'] > 0 and s['name'] == name)
        sec = c.sections[x['section'] - 1]
        later = sorted(y['value'] for y in c.symbol_list if y['section'] == x['section'] and y['value'] > x['value'] and not y['name'].startswith(('.', '$L')))
        e = later[0] if later else len(sec['data'])
        d = bytes(sec['data'][x['value']:e])
        ra = set()
        for va, si, t in sec['relocs']:
            ra.update(range(va - x['value'], va - x['value'] + 4))
        im = img.read(a, len(d))
        bad = [j for j in range(len(d)) if j not in ra and d[j] != im[j]]
        assert not bad, '%s differs at +0x%X' % (name, bad[0])
        covered.append((a, a + len(d)))
    covered.sort()
    assert covered[0][0] == lo, 'rows start at 0x%X, pieces at 0x%X' % (covered[0][0], lo)
    pos = lo
    for a, e in covered:
        assert a <= pos + 3, 'gap before 0x%X' % a
        pos = max(pos, e)
    assert pos >= hi - 15, 'rows end at 0x%X, pieces at 0x%X' % (pos, hi)
    # asm blocks
    for p in pieces:
        a = rowat[p][0]
        for f in os.listdir(os.path.join(ROOT, 'src', 'xdk')):
            if not (f.startswith('standin_') and f.endswith('.asm')):
                continue
            fp = os.path.join(ROOT, 'src', 'xdk', f)
            raw = open(fp, 'rb').read().decode('utf-8')
            nl = '\r\n' if '\r\n' in raw else '\n'
            L = raw.replace('\r\n', '\n').split('\n')
            key = '; // match: %s @ 0x%08X' % (p, a)
            if key not in L:
                continue
            i = L.index(key)
            j = i + 1
            while not L[j].startswith('; // match: ') and not re.match(r'^\w+ ENDS$', L[j]):
                j += 1
            del L[i:j]
            write(fp, '\n'.join(L).replace('\n', nl).encode('utf-8'))
            break
        else:
            raise SystemExit('no block for ' + p)
    drop = set(rowat[p][1] for p in pieces)
    first = min(drop)
    newl = ['0x%08X %s %s' % (int(a, 16), obj, name) for a, obj, name in news]
    lines = [l for k, l in enumerate(lines) if k not in drop or k == first]

    lines[first:first + 1] = newl
    rowat = {}
    for k2, l in enumerate(lines):
        q = l.split()
        if len(q) >= 3 and q[0].startswith('0x'):
            rowat[q[2]] = (int(q[0], 16), k2)
    allrows = sorted(int(l.split()[0], 16) for l in lines if len(l.split()) >= 3 and l.startswith('0x'))
    print('replaced', ', '.join(pieces), 'with', ', '.join(n for _, _, n in news))
write(cp, '\n'.join(lines).encode('utf-8'))
