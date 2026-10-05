"""asmlabels.py [--apply] FILE.asm: public labels inside a transcribed data unit's pieces (PLAN M7).

The data transcriptions (src/bink/binkdata.asm) label each placed piece at its start, but the
assembly units that read them (the transcribed expand_asm, yuv_asm...) name addresses inside a
piece (`_unk_52F780` inside `_unk_52F750`); the real link needs those names. For every unresolved
C name `_unk_/_dword_/_byte_/_word_/_off_/_stru_ADDR` (build/m7/unresolved.txt) whose address
falls inside one of FILE's pieces, the `db` row holding it is split there and a PUBLIC label goes
in. No byte changes."""
import os
import re
import sys

ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
apply = '--apply' in sys.argv
path = [a for a in sys.argv[1:] if not a.startswith('--')][0]
raw = open(path, 'rb').read().decode('latin-1')
nl = '\r\n' if '\r\n' in raw else '\n'
lines = raw.replace('\r\n', '\n').split('\n')
unres = set(l.strip() for l in open(os.path.join(ROOT, 'build', 'm7', 'unresolved.txt')) if l.strip())
want = {}
for n in unres:
    m = re.match(r'^_(?:unk|dword|byte|word|off|stru|asc|flt|dbl|qword)_([0-9A-F]{6})$', n)
    if m:
        want[int(m.group(1), 16)] = n
# C names config/aliases.txt maps to an address (Bink's own data names: _pmemw16, _YUVTables)
for l in open(os.path.join(ROOT, 'config', 'aliases.txt'), encoding='utf-8'):
    q = l.split()
    if len(q) >= 2 and q[0] in unres and q[0].startswith('_') and q[1].startswith('0x'):
        want.setdefault(int(q[1], 16), q[0])
# the pieces: a `; // match: NAME @ 0xADDR` line, its label, then db rows
pos = {}                            # line index of a db row -> (address of its first byte, byte count)
addr = None
for i, l in enumerate(lines):
    m = re.match(r'^; // match: (\S+) @ 0x([0-9A-F]+)$', l)
    if m:
        addr = int(m.group(2), 16)
        continue
    if re.match(r'^\w+ (?:SEGMENT|ENDS)\b', l):
        addr = None
        continue
    m = re.match(r'^\s+db\s+(.*)$', l)
    if m and addr is not None:
        n = len([x for x in m.group(1).split(',') if x.strip()])
        pos[i] = (addr, n)
        addr += n
    elif m:
        pass
    elif re.match(r'^\s+(dw|dd|dq)\b', l) and addr is not None:
        addr = None                 # other directives: not followed
existing = set(re.findall(r'^PUBLIC (\S+)', raw, re.M))
todo = {}
for i, (a, n) in pos.items():
    for t, name in want.items():
        if a <= t < a + n and name not in existing:
            todo.setdefault(i, []).append((t - a, name))
print(len(todo), 'rows;', sum(len(v) for v in todo.values()), 'labels')
for i in sorted(todo)[:10]:
    print(' ', i + 1, todo[i])
if not apply:
    sys.exit(0)
out = []
for i, l in enumerate(lines):
    if i not in todo:
        out.append(l)
        continue
    indent, vals = re.match(r'^(\s+db\s+)(.*)$', l).groups()
    vals = [x.strip() for x in vals.split(',') if x.strip()]
    cuts = sorted(todo[i])
    k = 0
    for off, name in cuts:
        if off > k:
            out.append(indent + ', '.join(vals[k:off]))
        out.append('PUBLIC %s' % name)
        out.append('%s LABEL BYTE' % name)
        k = off
    out.append(indent + ', '.join(vals[k:]))
open(path, 'wb').write(nl.join(out).encode('latin-1'))
print('applied')

# placement rows for the labels inside a piece (a label at a piece's start shares its address
# and needs none): the placement linker ends a piece at the next symbol
obj = 'build/' + os.path.splitext(os.path.relpath(os.path.abspath(path), ROOT).replace(os.sep, '/'))[0] + '.obj'
starts = set(int(a, 16) for a in re.findall(r'^; // match: \S+ @ 0x([0-9A-F]+)$', raw, re.M))
new = sorted((pos[i][0] + off, name) for i, v in todo.items() for off, name in v if pos[i][0] + off not in starts)
cfg = open(os.path.join(ROOT, 'config', 'compiled.txt'), encoding='utf-8').read().split('\n')
have = set(l.split()[2] for l in cfg if len(l.split()) >= 3)
for a, name in new:
    if name in have:
        continue
    best = None
    for i, l in enumerate(cfg):
        q = l.split()
        if len(q) >= 3 and q[1] == obj and int(q[0], 16) < a:
            best = i
    cfg.insert(best + 1, '0x%08X %s %s' % (a, obj, name))
    have.add(name)
open(os.path.join(ROOT, 'config', 'compiled.txt'), 'w', encoding='utf-8', newline='\n').write('\n'.join(cfg))
print(len(new), 'rows')
