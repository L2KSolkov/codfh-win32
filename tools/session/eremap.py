"""eremap.py SRC...: name a unit's $E and .CRT$XCU match lines after its object (PLAN M7).

VC7.1 numbers a translation unit's dynamic initializers ($E in .text$yc) and their exit thunks
($E in .text$yd) in source order, and fills .CRT$XCU with one slot per initializer. After a
split (unitsplit.py) the numbers change. This compiles SRC (cc1's way), pairs its initializers
in number order with the image addresses its `_$E` match lines give below 0x30DBF0 (in address
order), its exits likewise above, and its .CRT$XCU slots (+0, +4, ...) with its .CRT$XCU
lines' addresses; then rewrites those match lines and their config/compiled.txt rows (rows for
those addresses move to SRC's object)."""
import os
import re
import sys

sys.path.insert(0, os.path.join(os.path.dirname(os.path.abspath(__file__)), '..'))
from build_probes import flags_for, load_flags  # noqa: E402
from coff import Coff  # noqa: E402
from ibuild import compile_with_deps  # noqa: E402

ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
LINE = re.compile(r'^// match: (_\$E\d+|\.CRT\$XCU\+\d+) @ 0x([0-9A-Fa-f]+)$')
SPLIT = 0x30DBF0                        # initializers below, exit thunks above
rules = load_flags()


def fix(src):
    rel = os.path.relpath(os.path.abspath(src), ROOT).replace(os.sep, '/')
    obj = os.path.join(ROOT, 'build', 'tooltmp', 'eremap.obj')
    out = []
    if compile_with_deps(os.path.abspath(src), obj, flags_for(rel, rules) + ['/I' + os.path.join(ROOT, 'include')], out) is None:
        raise SystemExit('%s does not compile' % src)
    c = Coff(obj)
    inits, exits, xcu = [], [], 0
    for s in c.symbol_list:
        if s['section'] > 0 and re.match(r'_\$E\d+$', s['name']):
            sec = c.sections[s['section'] - 1]['name']
            (inits if sec == '.text$yc' else exits).append(s['name'])
    for sec in c.sections:
        if sec['name'] == '.CRT$XCU':
            xcu += sec['size'] // 4
    inits.sort(key=lambda n: int(n[3:]))
    exits.sort(key=lambda n: int(n[3:]))
    raw = open(src, 'rb').read().decode('utf-8', errors='surrogateescape')
    nl = '\r\n' if '\r\n' in raw else '\n'
    lines = raw.replace('\r\n', '\n').split('\n')
    ia, ea, xa = [], [], []
    for l in lines:
        m = LINE.match(l)
        if m:
            a = int(m.group(2), 16)
            (xa if m.group(1).startswith('.CRT') else ia if a < SPLIT else ea).append(a)
    ia.sort()
    ea.sort()
    xa.sort()
    if (len(ia), len(ea), len(xa)) != (len(inits), len(exits), xcu):
        raise SystemExit('%s: the object has %d initializers, %d exits, %d .CRT$XCU slots; the lines give %d, %d, %d'
                         % (src, len(inits), len(exits), xcu, len(ia), len(ea), len(xa)))
    name = dict(zip(ia, inits))
    name.update(zip(ea, exits))
    name.update((a, '.CRT$XCU+%d' % (4 * i)) for i, a in enumerate(xa))
    for k, l in enumerate(lines):
        m = LINE.match(l)
        if m:
            lines[k] = '// match: %s @ 0x%s' % (name[int(m.group(2), 16)], m.group(2))
    open(src, 'wb').write('\n'.join(lines).replace('\n', nl).encode('utf-8', errors='surrogateescape'))
    objname = 'build/' + os.path.splitext(rel)[0] + '.obj'
    cfg = os.path.join(ROOT, 'config', 'compiled.txt')
    rows = open(cfg, encoding='utf-8').read().split('\n')
    for j, l in enumerate(rows):
        q = l.split()
        if len(q) >= 3 and q[0].startswith('0x') and int(q[0], 16) in name and \
                (q[2].startswith('_$E') or q[2].startswith('.CRT$XCU')):
            rows[j] = '%s %s %s' % (q[0], objname, name[int(q[0], 16)])
    open(cfg, 'w', encoding='utf-8', newline='\n').write('\n'.join(rows))
    print('%s: %d initializers, %d exits, %d slots' % (src, len(inits), len(exits), xcu))


for s in sys.argv[1:]:
    fix(s)
