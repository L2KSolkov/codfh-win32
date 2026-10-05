"""aggregate.py SRC LO HI ["comment"]: fold a unit's data globals [LO, HI) into one object (PLAN M5).

A standalone zero global compiles into .bss, so a zero dword the image has in .data next to a
unit's globals is a member of an aggregate: a referenced global followed by zeros (or a run with
zeros in it) is one object. This folds the scalar definitions of SRC's m5defs block in [LO, HI)
into `type_LO unk_LO = { ... }` (members unk_OO typed as the globals were), declares the struct
where the first global's extern was (else in include/game/data.h), rewrites every use of the old
names in src/ and include/ to `unk_LO.unk_OO`, and updates the match lines, config/compiled.txt
(the old rows go; cmf adds the new one) and config/splits.txt (one range)."""
import glob
import os
import re
import sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import m5defs  # noqa: E402

ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
src, lo, hi = sys.argv[1], int(sys.argv[2], 16), int(sys.argv[3], 16)
note = sys.argv[4] if len(sys.argv) > 4 else 'one .data object: a lone zero global would be in .bss'
text = open(src, encoding='utf-8').read()
before, items, after = m5defs._split(text)
inside = [(a, d) for a, d in items if lo <= a < hi]
members = []
for a, d in inside:
    m = re.search(r'^(?:extern )?((?:const )?\w+) (\w+) = ([^;{]+);$', d.strip().splitlines()[-1])
    assert m, 'not a scalar definition at 0x%X: %r' % (a, d)
    members.append((a - lo, m.group(1), m.group(2), m.group(3)))
stype, obj = 'type_%06X' % lo, 'unk_%06X' % lo
struct = 'struct %s\n{\n%s};\n' % (stype, ''.join('    %s unk_%02X;\n' % (t, off) for off, t, _, _ in members))
items = [it for it in items if not lo <= it[0] < hi] + [
    (lo, '%s %s = { %s };\n' % (stype, obj, ', '.join(v for _, _, _, v in members)))]
text = m5defs._join(before, items, after)
for off, _, name, _ in members:
    text = re.sub(r'^// match: \S+ @ 0x%08X\n' % (lo + off), '', text, flags=re.M)
hdr = "// Its data (PLAN M5): literals, constants and tables where the image has them.\n"
text = text.replace(hdr, hdr + '// match: ?%s@@3U%s@@A @ 0x%08X\n' % (obj, stype, lo), 1)
open(src, 'w', encoding='utf-8', newline='\n').write(text)

# the struct goes where the first referenced global was declared
names = {name: 'unk_%06X.unk_%02X' % (lo, off) for off, _, name, _ in members}
home = None
for h in sorted(glob.glob(os.path.join(ROOT, 'include', '**', '*.h'), recursive=True)):
    t = open(h, encoding='utf-8', errors='replace').read()
    for name in names:
        if re.search(r'^extern [^;\n]*\b%s;' % name, t, re.M):
            home = home or h
home = home or os.path.join(ROOT, 'include', 'game', 'data.h')
for f in glob.glob(os.path.join(ROOT, 'src', '**', '*.c*'), recursive=True) + \
        glob.glob(os.path.join(ROOT, 'include', '**', '*.h'), recursive=True):
    t = open(f, encoding='utf-8', errors='replace').read()
    if f != home and not any(n in t for n in names):
        continue
    new = t
    if f == home:
        decl = '// %s (%s).\n%sextern %s %s;\n' % (obj, note, struct, stype, obj)
        first = True
        for name in names:
            m = re.search(r'^extern [^;\n]*\b%s;\n' % name, new, re.M)
            if m:
                new = new[:m.start()] + (decl if first else '') + new[m.end():]
                first = False
        if first:
            # before the include guard's #endif
            k = new.rstrip().rfind('#endif')
            new = new[:k] + decl + '\n' + new[k:] if k >= 0 else new.rstrip('\n') + '\n\n' + decl
    else:
        for name in names:
            new = re.sub(r'^extern [^;\n]*\b%s;\n' % name, '', new, flags=re.M)
    lines = new.split('\n')
    for k, l in enumerate(lines):
        if l.startswith('// match:') or l.startswith('// 0x'):
            continue
        for name, ref in names.items():
            l = re.sub(r'\b%s\b' % name, ref, l)
        lines[k] = l
    new = '\n'.join(lines)
    if new != t:
        open(f, 'w', encoding='utf-8', newline='\n').write(new)
        print('updated', os.path.relpath(f, ROOT))

cfg = os.path.join(ROOT, 'config', 'compiled.txt')
rows = open(cfg, encoding='utf-8').read().split('\n')
open(cfg, 'w', encoding='utf-8', newline='\n').write('\n'.join(
    r for r in rows if not (r.startswith('0x') and lo <= int(r.split()[0], 16) < hi)))
sp = os.path.join(ROOT, 'config', 'splits.txt')
lines = open(sp, encoding='utf-8').read().split('\n')
ks = [i for i, l in enumerate(lines) if l.startswith('0x') and lo <= int(l.split()[0], 16) < hi]
end = int(lines[ks[-1]].split()[1], 16)   # the last range may carry padding past HI
assert int(lines[ks[0]].split()[0], 16) == lo and end >= hi, (lines[ks[0]], lines[ks[-1]])
lines[ks[0]:ks[-1] + 1] = ['0x%08X 0x%08X %-10s ?%s@@3U%s@@A' % (lo, end, lines[ks[0]].split()[2], obj, stype)]
open(sp, 'w', encoding='utf-8', newline='\n').write('\n'.join(lines))
print('folded', len(members), 'globals into', obj)
