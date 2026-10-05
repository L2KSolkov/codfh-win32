"""rehome.py SRC...: after unitsplit.py, each `// match:` line to the unit whose object defines it.

Compiles every SRC alone (cc1's way); a match line whose symbol its own unit's object does not
define but exactly one other SRC's object does moves to that unit (to the end of its first
block of match lines, or after its includes), and its config/compiled.txt row gets that object.
Section-offset names (.CRT$XCU+N) and $E lines are left for tools/emap.py --remap and by hand."""
import os
import re
import sys

sys.path.insert(0, os.path.join(os.path.dirname(os.path.abspath(__file__)), '..'))
from build_probes import flags_for, load_flags  # noqa: E402
from coff import Coff  # noqa: E402
from ibuild import compile_with_deps  # noqa: E402

ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
LINE = re.compile(r'^//\s*match:\s*(\S+)\s*@\s*0x([0-9A-Fa-f]+)\s*$')
rules = load_flags()


def defined(src, k):
    rel = os.path.relpath(src, ROOT).replace(os.sep, '/')
    obj = os.path.join(ROOT, 'build', 'tooltmp', 'rehome%d.obj' % k)
    out = []
    if compile_with_deps(os.path.abspath(src), obj, flags_for(rel, rules) + ['/I' + os.path.join(ROOT, 'include')], out) is None:
        print('\n'.join(l for l in out if 'error' in l)[:3000])
        raise SystemExit('%s does not compile' % src)
    return set(s['name'] for s in Coff(obj).symbol_list if s['section'] > 0)


def objname(src):
    return 'build/' + os.path.relpath(os.path.splitext(src)[0], ROOT).replace(os.sep, '/') + '.obj'


srcs = [os.path.abspath(s) for s in sys.argv[1:]]
defs = [defined(s, k) for k, s in enumerate(srcs)]
texts = []
for s in srcs:
    raw = open(s, 'rb').read().decode('utf-8', errors='surrogateescape')
    texts.append(['\r\n' if '\r\n' in raw else '\n', raw.replace('\r\n', '\n').split('\n')])
moves = {}                                   # name -> destination index
arriving = [[] for _ in srcs]
for k, (nl, lines) in enumerate(texts):
    keep = []
    for l in lines:
        m = LINE.match(l)
        if m and not m.group(1).startswith(('.', '_$E')) and m.group(1) not in defs[k]:
            dest = [j for j in range(len(srcs)) if j != k and m.group(1) in defs[j]]
            if len(dest) == 1:
                moves[m.group(1)] = dest[0]
                arriving[dest[0]].append(l)
                continue
        keep.append(l)
    texts[k][1] = keep
for k, (nl, lines) in enumerate(texts):
    extra = arriving[k]
    if extra:
        # after the first block of match lines, else after the last #include
        at = next((i for i in range(len(lines)) if LINE.match(lines[i]) and
                   (i + 1 == len(lines) or not LINE.match(lines[i + 1]))), None)
        if at is None:
            at = max(i for i, l in enumerate(lines) if l.startswith('#include'))
        lines[at + 1:at + 1] = extra
    open(srcs[k], 'wb').write('\n'.join(lines).replace('\n', nl).encode('utf-8', errors='surrogateescape'))
cfg = os.path.join(ROOT, 'config', 'compiled.txt')
rows = open(cfg, encoding='utf-8').read().split('\n')
objs = [objname(s) for s in srcs]
n = 0
for j, l in enumerate(rows):
    q = l.split()
    if len(q) >= 3 and q[2] in moves and q[1] in objs:
        rows[j] = l.replace(q[1], objs[moves[q[2]]], 1)
        n += 1
open(cfg, 'w', encoding='utf-8', newline='\n').write('\n'.join(rows))
print('%d match lines moved, %d compiled.txt rows' % (len(moves), n))
