"""xdk5849.py LIB [--apply]: members of the XDK 5849 copy of LIB (xdklib/LIB.lib) that match the
image's rows better than the installed copies (PLAN M7).

The image's libraries are not all the installed XDK's: some members are the 5849 SDK's
(config/xdk_members.txt already takes a few from xdklib/). For every member of xdklib/LIB.lib,
the rows of objects of that base name (any build/xdk/<lib>/ copy, and the xdklib_LIB copy) are
checked against the 5849 member's function of the row's name (bytes at the row's address,
relocation fields aside). A member whose 5849 copy matches every row the current copies match
and at least one more (or the same rows, from two installed copies: xnets/xonlines) is
switched: extracted to build/xdk/xdklib_LIB/, listed in config/xdk_members.txt, and its rows
point there. Prints, per member, `CURRENT -> 5849` matched counts; --apply switches."""
import collections
import os
import sys

sys.path.insert(0, os.path.join(os.path.dirname(os.path.abspath(__file__)), '..'))
from coff import Coff  # noqa: E402
from lib import Library  # noqa: E402
from xbe import Xbe  # noqa: E402

ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
lib = sys.argv[1]
apply = '--apply' in sys.argv
img = Xbe(os.path.join(ROOT, 'orig', 'Game_XboxMultiplayer.xbe'))


def obj_name(member):
    return member.replace('\\', '_').replace('/', '_').replace(':', '_').replace('.obj', '').lower() + '.obj'


def matches(c, name, a):
    x = next((s for s in c.symbol_list if s['section'] > 0 and s['name'] == name), None) if c else None
    if x is None:
        return False
    try:
        code, rel = c.function_bytes(x)
    except Exception:
        return False
    ra = set()
    for o, t, ty in rel:
        ra.update(range(o, o + 4))
    try:
        i = img.read(a, len(code))
    except Exception:
        return False
    return all(code[k] == i[k] for k in range(len(code)) if k not in ra)


rows = collections.defaultdict(list)     # base name -> [(line index, addr, obj, name)]
lines = open(os.path.join(ROOT, 'config', 'compiled.txt'), encoding='utf-8').read().split('\n')
for k, l in enumerate(lines):
    q = l.split()
    if len(q) >= 3 and q[0].startswith('0x') and q[1].startswith('build/xdk/') and int(q[0], 16) < 0x3CD300:
        rows[os.path.basename(q[1]).lower()].append((k, int(q[0], 16), q[1], q[2]))
manifest = open(os.path.join(ROOT, 'config', 'xdk_members.txt'), encoding='utf-8').read()
cache = {}


def coff(p):
    if p not in cache:
        try:
            cache[p] = Coff(os.path.join(ROOT, p))
        except Exception:
            cache[p] = None
    return cache[p]


os.makedirs(os.path.join(ROOT, 'build', 'tooltmp', 'x5849', lib), exist_ok=True)
switch = []
for member, data in Library(os.path.join(ROOT, 'xdklib', lib + '.lib')).members:
    base = obj_name(member)
    if base.startswith('obj_i386_') is False and 'obj_i386_' in base:
        base = base[base.index('obj_i386_'):]
    mine = rows.get(base)
    if not mine:
        continue
    tmp = os.path.join('build', 'tooltmp', 'x5849', lib, base)
    open(os.path.join(ROOT, tmp), 'wb').write(data)
    new = coff(tmp)
    cur = set(k for k, a, o, n in mine if matches(coff(o), n, a))
    nw = set(k for k, a, o, n in mine if matches(new, n, a))
    copies = set(o.split('/')[2] for k, a, o, n in mine)
    target = 'build/xdk/xdklib_%s/%s' % (lib, base)
    already = all(o == target for k, a, o, n in mine)
    good = not already and cur <= nw and (len(nw) > len(cur) or len(copies) > 1)
    print('%-40s %3d rows: %3d -> %3d %s%s' % (base, len(mine), len(cur), len(nw), ','.join(sorted(copies)),
                                              '  SWITCH' if good else ''))
    if good:
        switch.append((member, base, data, target, mine))
print(len(switch), 'members to switch')
if apply:
    add = []
    for member, base, data, target, mine in switch:
        os.makedirs(os.path.dirname(os.path.join(ROOT, target)), exist_ok=True)
        open(os.path.join(ROOT, target), 'wb').write(data)
        if target + ' ' not in manifest:
            add.append('%s xdklib/%s.lib %s' % (target, lib, member))
        for k, a, o, n in mine:
            q = lines[k].split()
            lines[k] = '%s %s %s' % (q[0], target, q[2])
    open(os.path.join(ROOT, 'config', 'compiled.txt'), 'w', encoding='utf-8', newline='\n').write('\n'.join(lines))
    if add:
        with open(os.path.join(ROOT, 'config', 'xdk_members.txt'), 'a', encoding='utf-8', newline='\n') as f:
            f.write('\n'.join(add) + '\n')
