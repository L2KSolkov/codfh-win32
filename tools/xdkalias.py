"""xdkalias.py DECORATED... : add config/aliases.txt rows for XDK library
functions (e.g. _D3DPalette_Lock2@8) at the address symbols.txt gives their
undecorated name. With --scan OBJ: alias every undefined _Name@N the object
references that symbols.txt knows and aliases.txt lacks."""
import os as _os_repo
_REPO = _os_repo.path.dirname(_os_repo.path.dirname(_os_repo.path.abspath(__file__)))  # the repository root, from this file's location
import re
import sys

sys.path.insert(0, _os_repo.path.join(_REPO, r'tools'))
ROOT = _REPO
syms = {}
for l in open(ROOT + r'\config\symbols.txt', encoding='utf-8'):
    p = l.split()
    if len(p) >= 5 and p[1] == 'function':
        syms.setdefault(p[4], (p[0], p[3]))
araw = open(ROOT + r'\config\aliases.txt', 'rb').read().decode('utf-8')
have = set(l.split()[0] for l in araw.splitlines() if l.strip() and not l.startswith('#'))
names = sys.argv[1:]
if names[:1] == ['--scan']:
    from coff import Coff
    c = Coff(names[1])
    names = sorted(set(v['name'] for v in c.symbols.values()
                       if v.get('section', 0) == 0 and re.match(r'^[_@]\w+@\d+$', v['name'])))
    names = [n for n in names if n not in have]
add = []
for d in names:
    m = re.match(r'^[_@](\w+)@\d+$', d)
    if not m or d in have:
        continue
    base = m.group(1)
    if base not in syms:
        print('unknown', d)
        continue
    addr, lib = syms[base]
    add.append('%-50s %s  %s: the database\'s %s (RenderWare\'s Xbox driver calls it)\r\n'
               % (d, addr, 'd3d8.lib' if lib == 'D3D' else lib, base))
    print('alias', d, addr)
if add:
    if not araw.endswith('\r\n'):
        araw += '\r\n'
    open(ROOT + r'\config\aliases.txt', 'wb').write((araw + ''.join(add)).encode('utf-8'))
