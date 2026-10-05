"""sigdiff.py: unresolved code names (PLAN M7) beside the name placed at their address.

A reader that declares a function under another signature than its definition's references a
name nothing defines. For each address-named unresolved function: the decorated names the
compiled rows place there, both undecorated, and the readers (from the probe's link log)."""
import collections
import ctypes
import os
import re

ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
d = ctypes.windll.dbghelp
d.UnDecorateSymbolName.argtypes = [ctypes.c_char_p, ctypes.c_char_p, ctypes.c_uint, ctypes.c_uint]


def und(n):
    b = ctypes.create_string_buffer(4096)
    d.UnDecorateSymbolName(n.encode(), b, 4096, 0)
    return b.value.decode(errors='replace')


rows = collections.defaultdict(list)
for l in open(os.path.join(ROOT, 'config', 'compiled.txt'), encoding='utf-8'):
    q = l.split()
    if len(q) >= 3 and q[0].startswith('0x'):
        rows[int(q[0], 16)].append(q[2])
readers = collections.defaultdict(set)
for l in open(os.path.join(ROOT, 'build', 'm7', 'link.log'), errors='replace'):
    m = re.match(r'^(\S+)\.obj : error LNK20\d\d: unresolved external symbol (?:"[^"]*" \((\S+)\)|(\S+))', l)
    if m:
        readers[m.group(2) or m.group(3)].add(m.group(1))
for n in (l.strip() for l in open(os.path.join(ROOT, 'build', 'm7', 'unresolved.txt'))):
    m = re.match(r'^\?(?:sub|nullsub)_([0-9A-F]+)@', n)
    if not m:
        continue
    a = int(m.group(1), 16)
    print('0x%06X %s  [%s]' % (a, und(n), ','.join(sorted(readers[n]))))
    for r in rows.get(a, []):
        print('         = %s' % und(r))
