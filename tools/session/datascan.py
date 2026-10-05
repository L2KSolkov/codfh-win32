import glob, sys
sys.path.insert(0, 'tools')
from coff import Coff
from match import compare, resolve_name, section_kind, original_kind
from xbe import Xbe
img = Xbe('orig/Game_XboxMultiplayer.xbe')
placed = set(int(l.split()[0], 16) for l in open('config/compiled.txt') if l.startswith('0x'))
res = []
for obj in glob.glob('build/src/recovered/*.obj'):
    c = Coff(obj)
    for s in c.symbol_list:
        if s['section'] <= 0 or s['name'].startswith(('??_7', '??_C', '__real', '$', '.', '??_R')):
            continue
        kind = section_kind(c.sections[s['section'] - 1]['name'])
        if kind not in ('.data', '.rdata'):
            continue
        a = resolve_name(s['name'], {})
        if a is None or a in placed:
            continue
        ok, msg = compare(c, s['name'], a, img)
        res.append((a, s['name'], obj.replace('\\', '/'), ok, original_kind(img, a), msg[:90]))
res.sort()
for r in res:
    print('%#x %-30s %-40s %s %s %s' % r)
