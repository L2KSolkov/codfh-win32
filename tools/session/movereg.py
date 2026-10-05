"""movereg.py OLD NEW XCU_ADDR INIT_ADDR EXIT_ADDR: after unitsplit.py, move one global's
initializer pair and .CRT$XCU slot from unit OLD to unit NEW (sources and config/compiled.txt).

The moved $E lines become NEW's next numbers (VC7.1 numbers $E per object: a registrar's
initializer and exit thunk take two consecutive numbers after the ones before it, from 2) and
the .CRT$XCU line NEW's next offset; OLD's remaining ones keep their names (move the last
registrations first). Checked by the build (a wrong guess fails the placement link)."""
import os
import re
import sys

ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
E_LINE = re.compile(r'^// match: (_\$E\d+|\.CRT\$XCU\+\d+) @ 0x([0-9A-F]+)$')


def src_of(unit):
    for ext in ('.cpp', '.c'):
        p = os.path.join(ROOT, 'src', 'recovered', unit + ext)
        if os.path.exists(p):
            return p
    raise SystemExit('no source for ' + unit)


def read(p):
    raw = open(p, 'rb').read().decode('utf-8', errors='surrogateescape')
    return ('\r\n' if '\r\n' in raw else '\n'), raw.replace('\r\n', '\n')


def write(p, nl, t):
    open(p, 'wb').write(t.replace('\n', nl).encode('utf-8', errors='surrogateescape'))


old, new = sys.argv[1], sys.argv[2]
xcu, init, exit_ = (int(a, 16) for a in sys.argv[3:6])
po, pn = src_of(old), src_of(new)
nlo, to = read(po)
nln, tn = read(pn)
entries = {old: [], new: []}            # (address, kind) per unit
kept = {}                               # OLD's remaining entries keep their names
lines_o = []
for l in to.split('\n'):
    m = E_LINE.match(l)
    if m:
        a = int(m.group(2), 16)
        kind = 'xcu' if m.group(1).startswith('.CRT') else 'e'
        if a in (xcu, init, exit_):
            entries[new].append((a, kind))
        else:
            kept[a] = m.group(1)
        continue
    lines_o.append(l)
lines_n = [l for l in tn.split('\n') if not E_LINE.match(l)]
for l in tn.split('\n'):
    m = E_LINE.match(l)
    if m:
        entries[new].append((int(m.group(2), 16), 'xcu' if m.group(1).startswith('.CRT') else 'e'))


def names(ents):
    """Address -> name: XCU slots in address order; $E as initializer/exit pairs in initializer order."""
    out = {}
    x = sorted(a for a, k in ents if k == 'xcu')
    for i, a in enumerate(x):
        out[a] = '.CRT$XCU+%d' % (4 * i)
    es = sorted(a for a, k in ents if k == 'e')
    inits = [a for a in es if a < 0x30DBF0]
    exits = [a for a in es if a >= 0x30DBF0]
    n = 2
    for i, a in enumerate(inits):
        out[a] = '_$E%d' % n
        if i < len(exits):
            out[exits[i]] = '_$E%d' % (n + 1)
        n += 3 if i < len(exits) else 1
    return out


name_o, name_n = kept, names(entries[new])


def block(nm):
    xs = ['// match: %s @ 0x%08X' % (nm[a], a) for a in sorted(nm) if nm[a].startswith('.CRT')]
    es = ['// match: %s @ 0x%08X' % (nm[a], a)
          for a in sorted((a for a in nm if nm[a].startswith('_$E')), key=lambda a: int(nm[a][3:]))]
    return xs, es


def insert(lines, nm, anchor_hint):
    xs, es = block(nm)
    at = next((i for i, l in enumerate(lines) if l.startswith('// match: ?p') and 'ClassID@' in l), None)
    if at is None:
        at = max(i for i, l in enumerate(lines) if l.startswith('#include'))
    lines[at + 1:at + 1] = xs + ([''] + es if es else [])
    return lines


write(po, nlo, '\n'.join(insert(lines_o, name_o, None)))
write(pn, nln, '\n'.join(insert(lines_n, name_n, None)))
objo = 'build/src/recovered/%s.obj' % old
objn = 'build/src/recovered/%s.obj' % new
cfg = os.path.join(ROOT, 'config', 'compiled.txt')
rows = open(cfg, encoding='utf-8').read().split('\n')
for j, l in enumerate(rows):
    q = l.split()
    if len(q) >= 3 and q[1] in (objo, objn) and (q[2].startswith('_$E') or q[2].startswith('.CRT$XCU')):
        a = int(q[0], 16)
        if a in name_n:
            rows[j] = '%s %s %s' % (q[0], objn, name_n[a])
        elif a in name_o:
            rows[j] = '%s %s %s' % (q[0], objo, name_o[a])
open(cfg, 'w', encoding='utf-8', newline='\n').write('\n'.join(rows))
print(old, sorted((v, '%X' % k) for k, v in name_o.items()))
print(new, sorted((v, '%X' % k) for k, v in name_n.items()))
