"""samedefs.py [CATEGORY]: unresolved address-named data whose address a unit already defines under
another decorated name (another name, type or scope) (PLAN M7): the readers' and the definer's
names, undecorated."""
import ctypes
import os
import re
import sys

sys.path.insert(0, os.path.join(os.path.dirname(os.path.abspath(__file__)), '..'))
from coff import Coff  # noqa: E402

ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
d = ctypes.windll.dbghelp
d.UnDecorateSymbolName.argtypes = [ctypes.c_char_p, ctypes.c_char_p, ctypes.c_uint, ctypes.c_uint]


def und(n):
    b = ctypes.create_string_buffer(4096)
    d.UnDecorateSymbolName(n.encode(), b, 4096, 0)
    return b.value.decode(errors='replace')


defs = {}                           # address -> [(obj, decorated name)]
for dp, _dn, fs in os.walk(os.path.join(ROOT, 'src')):
    for f in fs:
        if not f.endswith(('.c', '.cpp')):
            continue
        p = os.path.join(dp, f)
        t = open(p, encoding='utf-8', errors='replace').read()
        addrs = [int(a, 16) for a in re.findall(r'^// 0x([0-9A-F]{8})\n(?!extern)[A-Za-z_]', t, re.M)]
        if not addrs:
            continue
        obj = os.path.join(ROOT, 'build', os.path.relpath(os.path.splitext(p)[0], ROOT) + '.obj')
        if not os.path.exists(obj):
            continue
        c = Coff(obj)
        for a in addrs:
            tag = '%06X' % a
            for s in c.symbol_list:
                if s.get('section', 0) > 0 and tag in s['name'] and s['name'].endswith(('A', 'B')) or \
                        (s.get('section', 0) > 0 and re.match(r'^_\w*%s$' % tag, s['name'])):
                    defs.setdefault(a, []).append((os.path.basename(obj), s['name']))
n = 0
for l in open(os.path.join(ROOT, 'build', 'm7', 'unresolved.txt')):
    u = l.strip()
    m = re.search(r'_([0-9A-F]{6})(?:@|$)', u)
    if not m:
        continue
    a = int(m.group(1), 16)
    if a in defs and u not in [x[1] for x in defs[a]]:
        n += 1
        print('0x%06X %-60s' % (a, und(u)[:60]))
        for o, s in defs[a]:
            print('         = %s  (%s)' % (und(s)[:70], o))
print(n)
