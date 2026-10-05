"""emap.py UNIT: map the unit object's unplaced $E functions to unplaced
initializer/exit functions in the image's tail (0x3096E0-0x30F0F4) by bytes
(relocations masked), requiring every DIR32 relocation whose target name
carries an address (dword_4B1F24, ?dword_4B1F24@@...) to match the image's
encoded value. Prints "SYM ADDR" for unique matches, and adds the match
lines after the unit's globals block (or before the first match line) with
--apply."""
import os as _os_repo
_REPO = _os_repo.path.dirname(_os_repo.path.dirname(_os_repo.path.abspath(__file__)))  # the repository root, from this file's location
import os
import re
import struct
import sys

sys.path.insert(0, _os_repo.path.join(_REPO, r'tools'))
from coff import Coff, IMAGE_REL_I386_DIR32, IMAGE_REL_I386_REL32
from xbe import Xbe

ROOT = _REPO
unit = sys.argv[1]
apply = '--apply' in sys.argv
x = Xbe(os.path.join(ROOT, 'orig', 'Game_XboxMultiplayer.xbe'))
remap = '--remap' in sys.argv
REL = unit if '/' in unit else 'recovered/' + unit
OBJREL = 'build/src/%s.obj' % REL
own = {}
placed = set()
for l in open(os.path.join(ROOT, 'config', 'compiled.txt')):
    if l.startswith('0x'):
        p = l.split()
        a = int(p[0], 16)
        if remap and p[1] == OBJREL and re.match(r'_\$E\d+$', p[2]):
            own[a] = p[2]
            continue
        placed.add(a)
known = {}
for l in open(os.path.join(ROOT, 'config', 'compiled.txt')):
    if l.startswith('0x'):
        p = l.split()
        known.setdefault(p[2], int(p[0], 16))
for l in open(os.path.join(ROOT, 'config', 'aliases.txt')):
    p = l.split()
    if len(p) >= 2 and not l.startswith('#') and p[1].startswith('0x'):
        known.setdefault(p[0], int(p[1], 16))
for l in open(os.path.join(ROOT, 'config', 'symbols.txt')):
    p = l.split()
    if len(p) >= 5 and p[0].startswith('0x'):
        known.setdefault(p[-1], int(p[0], 16))
known = dict((k, v) for k, v in known.items() if not re.match(r'_\$E\d+$', k))
funcs = []
for l in open(os.path.join(ROOT, 'config', 'symbols.txt')):
    p = l.split()
    if len(p) >= 5 and p[1] == 'function' and p[0].startswith('0x'):
        a = int(p[0], 16)
        if 0x3096E0 <= a < 0x30F0F4 and a not in placed:
            funcs.append((a, int(p[2], 16)))
src = os.path.join(ROOT, 'src', *(REL + '.cpp').split('/'))
text = open(src, encoding='utf-8').read()
c = Coff(os.path.join(ROOT, *OBJREL.split('/')))
out = []
used = set()
for s in sorted((s for s in c.symbols.values() if re.match(r'_\$E\d+$', s['name']) and s.get('section', 0) > 0),
                key=lambda s: int(s['name'][3:])):
    n = s['name']
    if '// match: %s @' % n in text and not remap:
        continue
    code, rels = c.function_bytes(s)
    code = bytes(code)
    mask = set()
    need = []
    rneed = []
    for off, sym, typ in rels:
        mask.update(range(off, off + 4))
        m = re.search(r'(?:dword|flt|unk|byte|word|off|stru|dbl)_([0-9A-F]{6})\b', sym or '')
        if m and typ == IMAGE_REL_I386_DIR32:
            need.append((off, int(m.group(1), 16), struct.unpack_from('<I', code, off)[0]))
        elif sym in known and typ == IMAGE_REL_I386_DIR32:
            need.append((off, known[sym], struct.unpack_from('<I', code, off)[0]))
        elif sym in known and typ == IMAGE_REL_I386_REL32:
            rneed.append((off, known[sym]))
    hits = []
    for a, size in funcs:
        if a in used or size != len(code):
            continue
        b = x.read(a, size)
        if any(code[k] != b[k] for k in range(size) if k not in mask):
            continue
        if any(struct.unpack_from('<I', b, off)[0] != g + add for off, g, add in need):
            continue
        if any((a + off + 4 + struct.unpack_from('<i', b, off)[0]) & 0xFFFFFFFF != g for off, g in rneed):
            continue
        hits.append(a)
    if len(hits) > 1 and out:
        # an exit function: the one the previous initializer registers (push imm32)
        pa = out[-1][1]
        pb = x.read(pa, 0x80)
        reg = [h for h in hits if b'h' + struct.pack('<I', h) in pb]
        if len(reg) == 1:
            hits = reg
    if len(hits) > 1:
        # in link order: the first candidate after the unit's previous one
        # in the same region (initializers below 0x30DBF0, exits above)
        reg = [h for h in hits if (h < 0x30DBF0) == (hits[0] < 0x30DBF0)]
        prev = [q for _, q in out if (q < 0x30DBF0) == (hits[0] < 0x30DBF0)]
        if len(reg) == len(hits) and prev:
            nxt = [h for h in hits if h > prev[-1]]
            if nxt:
                hits = [min(nxt)]
    if len(hits) == 1:
        used.add(hits[0])
        out.append((n, hits[0]))
        print(n, '0x%06X' % hits[0])
    else:
        print(n, 'ambiguous' if hits else 'no match', ' '.join('%06X' % h for h in hits[:6]))
if remap and out:
    # rewrite every $E match line of the unit and its rows from the byte map
    t = open(src, encoding='utf-8', newline='').read()
    nl = chr(13) + chr(10) if chr(13) + chr(10) in t else chr(10)
    lines = [l for l in t.split(nl) if not re.match(r'// match: _\$E\d+ @ ', l)]
    k = None
    for i, l in enumerate(lines):
        if l.startswith('// Globals with constructors defined here'):
            k = i
            while lines[k].strip():
                k += 1
    if k is None:
        k = max(i for i, l in enumerate(lines) if l.startswith('#include')) + 1
    lines[k:k] = ['// match: %s @ 0x%08X' % (n, a) for n, a in out]
    open(src, 'w', encoding='utf-8', newline='').write(nl.join(lines))
    cfgp = os.path.join(ROOT, 'config', 'compiled.txt')
    cfg = open(cfgp, encoding='utf-8').read().split('\n')
    newname = dict((a, n) for n, a in out)
    res = []
    for l in cfg:
        p = l.split()
        if l.startswith('0x') and p[1] == OBJREL and re.match(r'_\$E\d+$', p[2]):
            a = int(p[0], 16)
            if a in newname:
                l = '%s %s %s' % (p[0], p[1], newname[a])
            else:
                continue
        res.append(l)
    open(cfgp, 'w', encoding='utf-8', newline='\n').write('\n'.join(res))
    print('ADDRS', ' '.join('%06X' % a for n, a in out if a not in own))
elif apply and out:
    t = open(src, encoding='utf-8', newline='').read()
    nl = '\r\n' if '\r\n' in t else '\n'
    lines = t.split(nl)
    try:
        k = max(i for i, l in enumerate(lines) if l.startswith('// Globals with constructors defined here'))
        while lines[k].strip():
            k += 1
    except ValueError:
        k = max(i for i, l in enumerate(lines) if l.startswith('#include')) + 1
    lines[k:k] = ['// match: %s @ 0x%08X' % (n, a) for n, a in out]
    open(src, 'w', encoding='utf-8', newline='').write(nl.join(lines))
    print('ADDRS', ' '.join('%06X' % a for _, a in out))
