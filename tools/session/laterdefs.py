"""laterdefs.py OBJ...: the calls a VC7.0 unit makes to functions it defines further down (PLAN M7:
VC7.0 emits a function calling one defined later, and its callers, at the unit's end, so the
image having them in place means the callee was in another object, or defined first).

For each function of OBJ (config/compiled.txt rows): the relocations to functions the same
object defines at a higher image address."""
import os
import sys

sys.path.insert(0, os.path.join(os.path.dirname(os.path.abspath(__file__)), '..'))
from coff import Coff  # noqa: E402

ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
for path in sys.argv[1:]:
    rel = os.path.relpath(os.path.abspath(path), ROOT).replace(os.sep, '/')
    addr = {}
    for l in open(os.path.join(ROOT, 'config', 'compiled.txt'), encoding='utf-8'):
        q = l.split()
        if len(q) >= 3 and q[1] == rel:
            addr[q[2]] = int(q[0], 16)
    c = Coff(path)
    for sym in c.symbol_list:
        if sym['type'] != 0x20 or sym['section'] <= 0 or sym['name'] not in addr:
            continue
        data, relocs = c.function_bytes(sym)
        later = sorted(set(t for off, t, ty in relocs if t in addr and addr[sym['name']] < addr[t] < 0x3C0000))
        if later:
            print('%s 0x%06X %s -> %s' % (os.path.basename(path), addr[sym['name']], sym['name'],
                                          ', '.join('%s (0x%06X)' % (t, addr[t]) for t in later)))
