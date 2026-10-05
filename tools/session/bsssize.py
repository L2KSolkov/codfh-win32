"""bsssize.py [--apply]: give the unsized array definitions their size (PLAN M5/M7).

bssdefs.py copied `T name[];` declarations into definitions; at file scope that is a tentative
definition of an incomplete array, which VC7.1 emits as a zero-size communal, i.e. an unresolved
external in the real link. Each such definition (under its `// 0xADDR` comment) gets the extent up
to the next known address (config/symbols.txt, or the next item of its data block), in elements
of its type. Godfather's debug build gives a few sizes directly (SIZES). Prints what it could not
size."""
import bisect
import os
import re
import sys

ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
apply = '--apply' in sys.argv
ELEM = {'RwChar': 1, 'RwUInt8': 1, 'RwInt8': 1, 'char': 1, 'BYTE': 1, 'RwInt16': 2, 'RwUInt16': 2, 'WORD': 2,
        'RwInt32': 4, 'RwUInt32': 4, 'RwReal': 4, 'RwBool': 4, 'DWORD': 4, 'int': 4, 'float': 4,
        'RwV3d': 12, 'RwV4d': 16}
# sizes the Godfather debug build's types state (its names, same library)
SIZES = {'TextArray': 2048, '_rpSkinXboxPerAtomicConstants': 1024}
known = []
for l in open(os.path.join(ROOT, 'config', 'symbols.txt'), encoding='utf-8', errors='replace'):
    q = l.split()
    if q and q[0].startswith('0x'):
        known.append(int(q[0], 16))
# IDA's labels (build/ida_data_names.txt, dumped from the database) name more than symbols.txt
ida = os.path.join(ROOT, 'build', 'ida_data_names.txt')
if os.path.exists(ida):
    for l in open(ida, encoding='utf-8', errors='replace'):
        q = l.split()
        if q and q[0].startswith('0x'):
            known.append(int(q[0], 16))
known = sorted(set(known))
todo, skipped = [], []
for top in ('src',):
    for dp, _dn, fs in os.walk(os.path.join(ROOT, top)):
        for f in fs:
            if not f.endswith(('.c', '.cpp')):
                continue
            p = os.path.join(dp, f)
            lines = open(p, encoding='utf-8', errors='replace').read().split('\n')
            for i, l in enumerate(lines):
                m = re.match(r'^((?:static\s+)?([\w ]+?)\s+(\w+))\[(\d*)\];\s*$', l)
                if m and m.group(4) and '--check' not in sys.argv:
                    continue
                if not m or m.group(1).startswith('extern') or i == 0:
                    continue
                am = re.match(r'^// 0x([0-9A-F]{8})$', lines[i - 1])
                if not am:
                    skipped.append((p, m.group(3), 'no address'))
                    continue
                a = int(am.group(1), 16)
                nxt = known[bisect.bisect_right(known, a)] if bisect.bisect_right(known, a) < len(known) else None
                for l2 in lines[i + 1:]:
                    m2 = re.match(r'^// 0x([0-9A-F]{8})$', l2)
                    if m2:
                        nxt = min(nxt, int(m2.group(1), 16)) if nxt else int(m2.group(1), 16)
                        break
                    if l2.startswith('// End of its data'):
                        break
                t, n = m.group(2).split()[-1], m.group(3)
                if n in SIZES:
                    cnt = SIZES[n]
                elif t in ELEM and nxt and (nxt - a) % ELEM[t] == 0:
                    cnt = (nxt - a) // ELEM[t]
                else:
                    skipped.append((p, n, t))
                    continue
                if m.group(4):
                    # --check: an explicit size reaching past the next label (a label inside an
                    # array is possible: reported, and shrunk only with --apply)
                    if int(m.group(4)) <= cnt or n in SIZES:
                        continue
                    print('oversized %s %s [%s] > [%d]' % (os.path.relpath(p, ROOT), n, m.group(4), cnt))
                todo.append((p, i, n, cnt))
for p, i, n, c in todo:
    print('%-45s %-24s [%d]' % (os.path.relpath(p, ROOT), n, c))
print(len(todo), 'sized;', len(skipped), 'skipped')
for s in skipped:
    print('  skip', os.path.relpath(s[0], ROOT), s[1], s[2])
if apply:
    by = {}
    for p, i, n, c in todo:
        by.setdefault(p, []).append((i, c))
    for p, items in by.items():
        raw = open(p, 'rb').read().decode('utf-8')
        nl = '\r\n' if '\r\n' in raw else '\n'
        lines = raw.split(nl)
        for i, c in items:
            lines[i] = re.sub(r'\[\d*\];', '[%d];' % c, lines[i])
        open(p, 'wb').write(nl.join(lines).encode('utf-8'))
    print('applied')
