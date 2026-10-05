"""data2member.py [--apply]: stand-in data pieces that are their member's own datum become member
rows (PLAN M7).

A data stand-in (src/xdk/standin_data_*.asm row) under a real name (a vtable ??_7..., a table)
that an installed or 5849 XDK member (build/xdk/<lib>/*.obj) defines with the same bytes
(relocation fields aside) at the piece's length, the datum alone in its section or followed by
the next row, is that member's datum: the row names the member's object and the piece leaves the
asm (its match block; an emptied segment goes). Prints the plan; --apply edits."""
import collections
import glob
import os
import re
import struct
import sys

sys.path.insert(0, os.path.join(os.path.dirname(os.path.abspath(__file__)), '..'))
from coff import Coff  # noqa: E402
from xbe import Xbe  # noqa: E402

ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
apply = '--apply' in sys.argv
# D2M_SKIP: addresses (comma-separated) left as pieces (the placement link refused them)
skip = set(int(x, 16) for x in os.environ.get('D2M_SKIP', '').split(',') if x)
only = set(int(x, 16) for x in sys.argv[1:] if x.startswith('0x'))
img = Xbe(os.path.join(ROOT, 'orig', 'Game_XboxMultiplayer.xbe'))
MADE = re.compile(r'^_?(sub|unk|loc|off|dword|byte|word|stru|flt|dbl|asc|a)_[0-9A-F]+$')
rows = []
for l in open(os.path.join(ROOT, 'config', 'compiled.txt'), encoding='utf-8'):
    q = l.split()
    if len(q) >= 3 and q[0].startswith('0x'):
        rows.append((int(q[0], 16), q[1], q[2]))
rows.sort()
ad = [r[0] for r in rows]
rownames = set(r[2] for r in rows)
# every XDK member's data symbols: name -> [(path, section, value)]
defs = collections.defaultdict(list)
cache = {}
for p in glob.glob(os.path.join(ROOT, 'build', 'xdk', '*', '*.obj')):
    rel = os.path.relpath(p, ROOT).replace(os.sep, '/')
    try:
        c = Coff(p)
    except Exception:
        continue
    cache[rel] = c
    for x in c.symbol_list:
        if x['section'] > 0 and x['class'] in (2, 3):
            s = c.sections[x['section'] - 1]
            if not (s['chars'] & 0x20) and not s['name'].startswith('.debug') and s['name'] != '.drectve':
                defs[x['name']].append((rel, x['section'], x['value']))
alias_names = set()
for l in open(os.path.join(ROOT, 'config', 'aliases.txt'), encoding='utf-8'):
    q = l.split()
    if q:
        alias_names.add(q[0])
row_at = dict((r[0], r[2]) for r in rows)
new_alias = {}
add_alias = {}
plan = {}
for k, (a, o, n) in enumerate(rows):
    if not o.startswith('build/src/xdk/standin_data') or MADE.match(n) or n not in defs or a in skip or (only and a not in only):
        continue
    nxt = ad[k + 1] if k + 1 < len(ad) else a + 4
    cands = []
    for rel, sn, v in defs[n]:
        if '/xdklib_' in rel and any(not r.startswith('build/xdk/xdklib_') for r, _, _ in defs[n]) and False:
            continue
        c = cache[rel]
        s = c.sections[sn - 1]
        d = bytes(s['data'])[v:]
        # its extent: to the next symbol in the section, or the section's end
        later = sorted(x['value'] for x in c.symbol_list if x['section'] == sn and x['value'] > v)
        if later:
            d = d[:later[0] - v]
        if not d or len(d) > nxt - a or nxt - a - len(d) > 3:
            continue
        ra = set()
        for va, si, t in s['relocs']:
            ra.update(range(va - v, va - v + 4))
        i = img.read(a, len(d))
        if all(d[j] == i[j] for j in range(len(d)) if j not in ra):
            cands.append(rel)
            # names its relocations use that nothing resolves (a vtable's ??_E, a weak external
            # defaulting to the scalar deleting destructor) whose image value is a row
            for va, si, ty in s['relocs']:
                if not (v <= va < v + len(d)) or ty != 6:
                    continue
                tn = next((y['name'] for y in c.symbol_list if y['index'] == si), None)
                if tn is None or tn in rownames or tn in alias_names:
                    continue
                val = struct.unpack('<I', img.read(a + va - v, 4))[0]
                if val in row_at:
                    new_alias.setdefault(rel, {})[tn] = (val, row_at[val])
    objs = sorted(set(cands))
    pref = [r for r in objs if '/xdklib_' in r] or objs
    if len(pref) == 1:
        plan[a] = (n, pref[0])
        for tn, (val, rn) in new_alias.get(pref[0], {}).items():
            add_alias[tn] = (val, rn)
for a, (n, rel) in sorted(plan.items()):
    print('0x%08X %s -> %s' % (a, n[:60], rel))
print(len(plan), 'data pieces;', len(add_alias), 'aliases')
if not apply:
    sys.exit(0)
if add_alias:
    with open(os.path.join(ROOT, 'config', 'aliases.txt'), 'a', encoding='utf-8', newline='\n') as f:
        for tn, (val, rn) in sorted(add_alias.items()):
            f.write('%s 0x%08X  a member datum names it (a weak external, its default %s there; data2member.py)\n' % (tn, val, rn))
for p in sorted(glob.glob(os.path.join(ROOT, 'src', 'xdk', 'standin_*.asm'))):
    raw = open(p, 'rb').read().decode('utf-8')
    nl = '\r\n' if '\r\n' in raw else '\n'
    L = raw.replace('\r\n', '\n').split('\n')
    out = []
    i = 0
    changed = False
    while i < len(L):
        m = re.match(r'^; // match: (\S+) @ 0x([0-9A-F]{8})$', L[i])
        if m and int(m.group(2), 16) in plan and plan[int(m.group(2), 16)][0] == m.group(1):
            j = i + 1
            while j < len(L) and not L[j].startswith('; // match: ') and not re.match(r'^\w+ ENDS$', L[j]):
                j += 1
            i = j
            changed = True
            continue
        out.append(L[i])
        i += 1
    if not changed:
        continue
    t = '\n'.join(out)
    t = re.sub(r'\n(\w+) SEGMENT [^\n]*\n\s*\n\1 ENDS\n', '\n', t)
    t = re.sub(r'\n(\w+) SEGMENT [^\n]*\n\1 ENDS\n', '\n', t)
    for a, (n, rel) in plan.items():
        t = re.sub(r'^PUBLIC %s\n' % re.escape(n), '', t, flags=re.M)
        if re.search(r'(?<![\w@$?])%s(?![\w@$?])' % re.escape(n), t) and not re.search(r'^EXTERN %s:' % re.escape(n), t, re.M):
            first = re.search(r'^EXTERN ', t, re.M)
            pos = first.start() if first else t.index('\n') + 1
            t = t[:pos] + 'EXTERN %s:BYTE\n' % n + t[pos:]
    open(p, 'wb').write(t.replace('\n', nl).encode('utf-8'))
cp = os.path.join(ROOT, 'config', 'compiled.txt')
out = []
for l in open(cp, encoding='utf-8').read().split('\n'):
    q = l.split()
    if len(q) >= 3 and q[0].startswith('0x') and int(q[0], 16) in plan and q[1].startswith('build/src/xdk/standin_data') \
            and q[2] == plan[int(q[0], 16)][0]:
        l = '%s %s %s' % (q[0], plan[int(q[0], 16)][1], q[2])
    out.append(l)
open(cp, 'w', encoding='utf-8', newline='\n').write('\n'.join(out))
