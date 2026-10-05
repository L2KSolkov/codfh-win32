"""standinmatch.py [--apply]: XDK stand-in code pieces that are an installed or 5849 library member's
function after all (PLAN M7: a stand-in piece under a made-up name is unreferenced in the real
link, which /OPT:REF drops, while the member's copy under the name its callers use lands
unordered elsewhere).

For every .text row of build/src/xdk/standin_*.obj, the piece's bytes (config/compiled.txt row to
the next row) are compared with every function of the extracted library members (build/xdk/**),
relocation fields masked on both sides; a candidate counts when its length and bytes match and
each relocation sits at the same offset. Candidates from the members whose rows neighbour the
piece are preferred. Prints `ADDR stand-in-name -> object name` (several candidates: all, `?`).
With --apply the unique matches' rows are renamed in config/compiled.txt (the stand-in sources
are left for a hand edit: their pieces go, and with them any EXTERNs only those used)."""
import bisect
import collections
import glob
import os
import re
import sys

sys.path.insert(0, os.path.join(os.path.dirname(os.path.abspath(__file__)), '..'))
from coff import Coff  # noqa: E402
from match import resolve_name  # noqa: E402

ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
apply = '--apply' in sys.argv
real = '--real' in sys.argv
need = {}
rows = []
for l in open(os.path.join(ROOT, 'config', 'compiled.txt'), encoding='utf-8'):
    q = l.split()
    if len(q) >= 3 and q[0].startswith('0x') and int(q[0], 16) < 0x3CD300:
        rows.append((int(q[0], 16), q[1], q[2]))
rows.sort()
starts = [r[0] for r in rows]


def masked(code, rel):
    b = bytearray(code)
    for off, _, _ in rel:
        b[off:off + 4] = b'\0\0\0\0'
    return bytes(b), tuple(sorted(off for off, _, _ in rel))


# every library function: (masked bytes, reloc offsets) -> [(object, name)]
lib = collections.defaultdict(list)
for p in glob.glob(os.path.join(ROOT, 'build', 'xdk', '**', '*.obj'), recursive=True):
    try:
        c = Coff(p)
    except Exception:
        continue
    rel_p = os.path.relpath(p, ROOT).replace(os.sep, '/')
    for s in c.symbol_list:
        if s['section'] > 0 and (s['type'] >> 4) == 2 and s['class'] in (2, 3):
            try:
                code, rel = c.function_bytes(s)
            except Exception:
                continue
            # only one whose references are all external or code: an object-local literal or
            # static datum would have to land where the image's (stand-in) data has it
            local = {x['name'] for x in c.symbol_list if x['section'] > 0 and
                     ((x['class'] == 3 and (x['type'] >> 4) != 2) or x['name'].startswith(('??_C@', '$SG')))}
            if any(tn in local for _, tn, _ in rel):
                continue
            statics = {x['name'] for x in c.symbol_list if x['section'] > 0 and x['class'] == 3}
            # a static callee is named with its object (it must be that object's row)
            lib[masked(code, rel)].append((rel_p, s['name'], tuple(
                (off, (rel_p + '|' + tn) if tn in statics else tn) for off, tn, _ in sorted(rel))))
placed = {r[2] for r in rows}
row_objs = {r[1] for r in rows}
aliases = {}
for l in open(os.path.join(ROOT, 'config', 'aliases.txt'), encoding='utf-8'):
    q = l.split()
    if len(q) >= 2 and not l.startswith('#') and q[1].startswith('0x'):
        aliases[q[0]] = int(q[1], 16)
# names the stand-in sources use (a piece another piece calls keeps its name)
used = set()
for p in glob.glob(os.path.join(ROOT, 'src', 'xdk', 'standin_*.asm')):
    for l in open(p, encoding='utf-8', errors='replace'):
        if not l.lstrip().startswith((';', 'PUBLIC', 'EXTERN')) and ':' not in l.split(';')[0][-2:]:
            used.update(w for w in l.split(';')[0].replace(',', ' ').split() if w.startswith('_'))
def make_where(choice):
    keep = [r for i, r in enumerate(rows) if i not in choice]
    addr = {}
    seen_at = collections.defaultdict(set)
    for r in keep:
        seen_at[r[2]].add(r[0])
        addr[r[1] + '|' + r[2]] = r[0]
    for i, x in choice.items():
        seen_at[x[1]].add(rows[i][0])
        addr[x[0] + '|' + x[1]] = rows[i][0]
    for r in rows:
        addr.setdefault(r[1] + '|' + r[2], r[0])
    # a name rows place at several addresses (two library copies) resolves to neither
    anyrow = dict((n, next(iter(s)) if len(s) == 1 else None) for n, s in seen_at.items())

    def where(n):
        # as the placement link resolves it (tools/xbelink.py): the same object's rows, then
        # match.resolve_name (aliases, database names), then any row
        if n in addr:
            return addr[n]
        bare = n.split('|', 1)[-1]
        if real and anyrow.get(bare) is not None:
            # --real: the name's own row first (as link.exe resolves it); the placement link
            # needs an alias where it would read the name otherwise
            r = resolve_name(bare, {})
            if r != anyrow[bare] and bare in aliases:
                return None     # an alias says otherwise: the placement link would follow it
            if r != anyrow[bare]:
                need[bare] = anyrow[bare]
            return anyrow[bare]
        r = resolve_name(bare, {})
        if r is not None:
            return r
        return anyrow.get(bare)
    return where


where0 = make_where({})
standins = {}
choice = {}
for i, (a, obj, name) in enumerate(rows):
    if not obj.startswith('build/src/xdk/standin_') or obj.startswith('build/src/xdk/standin_data'):
        continue
    if name in used:
        continue
    if obj not in standins:
        standins[obj] = Coff(os.path.join(ROOT, obj))
    c = standins[obj]
    s = next((x for x in c.symbol_list if x['section'] > 0 and x['name'] == name), None)
    if s is None:
        continue
    code, rel = c.function_bytes(s)
    nxt = rows[i + 1][0] if i + 1 < len(rows) else a + len(code)
    code = code[:nxt - a]
    rel = [r for r in rel if r[0] < len(code)]
    cands = lib.get(masked(code, rel), [])
    # not a function that has a row of its own (the image's other copy)
    cands = [x for x in cands if x[1] not in placed]
    if not cands:
        continue
    # a member's functions sit together: its object neighbours the piece, or has no rows yet
    near = {rows[j][1] for j in range(max(0, i - 3), min(len(rows), i + 4))}
    pref = [x for x in cands if x[0] in near] or [x for x in cands if x[0] not in row_objs]
    if not pref:
        continue
    if len(pref) > 1:
        image_t = [(off, where0(obj + '|' + tn)) for off, tn, _ in sorted(rel)]
        if all(v is not None for _, v in image_t):
            pref = [x for x in pref if [(off, where0(n)) for off, n in x[2]] == image_t] or pref
    tag = '' if len(pref) == 1 else ' ?'
    print('0x%08X %s -> %s%s' % (a, name, ', '.join('%s %s' % x[:2] for x in pref[:4]), tag))
    if len(pref) == 1:
        choice[i] = pref[0] + (tuple(sorted((off, (obj + '|' + tn)) for off, tn, _ in rel)),)
# one row per function, and every reference resolvable (a row, an alias or another choice)
seen = collections.Counter(x[1] for x in choice.values())
choice = dict((i, x) for i, x in choice.items() if seen[x[1]] == 1)
while True:
    where = make_where(choice)
    bad = []
    need.clear()
    for i, x in choice.items():
        mine = [(off, where(n)) for off, n in x[2]]
        image = [(off, where(n)) for off, n in x[3]]
        if any(v is None for _, v in mine) or mine != image:
            bad.append(i)
    if not bad:
        break
    for i in bad:
        del choice[i]
print(len(choice), 'unique, resolvable')
for n, a in sorted(need.items(), key=lambda x: x[1]):
    print('alias needed: %s 0x%08X' % (n, a))
if apply and need:
    path = os.path.join(ROOT, 'config', 'aliases.txt')
    raw = open(path, 'rb').read().decode('utf-8')
    nl = '\r\n' if '\r\n' in raw else '\n'
    add = ''.join('%-29s 0x%08X  the library function its row places there: the placement link would read the '
                  'undecorated name from the database instead (an XDK stand-in piece matched to its member, '
                  'tools/session/standinmatch.py --real)%s' % (n, a, nl) for n, a in sorted(need.items(), key=lambda x: x[1]))
    if not raw.endswith(nl):
        raw += nl
    open(path, 'wb').write((raw + add).encode('utf-8'))
if apply:
    for i, x in choice.items():
        rows[i] = (rows[i][0], x[0], x[1])
if apply:
    path = os.path.join(ROOT, 'config', 'compiled.txt')
    new = dict((r[0], r) for r in rows)
    out = []
    for l in open(path, encoding='utf-8').read().split('\n'):
        q = l.split()
        if len(q) >= 3 and q[0].startswith('0x') and q[1].startswith('build/src/xdk/standin_'):
            r = new.get(int(q[0], 16))
            if r and r[1] != q[1]:
                l = '%s %s %s' % (q[0], r[1], r[2])
        out.append(l)
    open(path, 'w', encoding='utf-8', newline='\n').write('\n'.join(out))
