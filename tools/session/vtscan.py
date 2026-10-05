"""Scan: vtables aliased in config/aliases.txt that a game object defines; compare each."""
import glob, os, sys
sys.path.insert(0, 'tools')
from coff import Coff
from match import compare
from xbe import Xbe

img = Xbe('orig/Game_XboxMultiplayer.xbe')
vt = {}
for l in open('config/aliases.txt', encoding='utf-8'):
    p = l.split()
    if len(p) >= 2 and p[0].startswith('??_7') and p[1].startswith('0x'):
        vt[p[0]] = int(p[1], 16)
placed = set(int(l.split()[0], 16) for l in open('config/compiled.txt') if l.startswith('0x'))
found = {}
for obj in glob.glob('build/src/recovered/*.obj') + glob.glob('build/src/Source/**/*.obj', recursive=True) + glob.glob('build/src/COD/**/*.obj', recursive=True) + glob.glob('build/src/rws/**/*.obj', recursive=True):
    try:
        c = Coff(obj)
    except Exception:
        continue
    names = set(s['name'] for s in c.symbol_list if s['section'] > 0)
    for n in names & set(vt):
        if n in found:
            continue
        ok, msg = compare(c, n, vt[n], img)
        found[n] = (obj, ok, msg)
good = [(vt[n], n, o, m) for n, (o, ok, m) in found.items() if ok and vt[n] not in placed]
good.sort()
print('aliased vtables', len(vt), 'defined', len(found), 'identical', len(good))
for a, n, o, m in good:
    print(hex(a), n, o.replace('\\', '/'), m.split('identical')[1][:80])
bad = [(n, m) for n, (o, ok, m) in found.items() if not ok]
for n, m in bad[:10]:
    print('BAD', m[:160])
