"""foldsweep.py: every definition the sources mark `// NAME (folded into 0xADDR)` (aliasdefs.py's)
against the image's function at ADDR: its bytes with the relocation fields aside, and each
relocation's target (by name through compiled.txt, aliases.txt and symbols.txt) against the
address the image's field encodes. Both must agree for /OPT:ICF to fold it there (PLAN M7).
Prints the ones that differ and a count."""
import os
import re
import struct
import sys

sys.path.insert(0, os.path.join(os.path.dirname(os.path.abspath(__file__)), '..'))
from coff import Coff  # noqa: E402
from xbe import Xbe  # noqa: E402

ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
image = Xbe(os.path.join(ROOT, 'orig', 'Game_XboxMultiplayer.xbe'))
addr_of = {}
for fn in ('symbols.txt', 'aliases.txt', 'compiled.txt'):     # later ones win
    for l in open(os.path.join(ROOT, 'config', fn), encoding='utf-8', errors='replace'):
        q = l.split()
        if fn == 'symbols.txt' and len(q) >= 5 and q[0].startswith('0x'):
            addr_of[q[4]] = int(q[0], 16)
        elif fn == 'aliases.txt' and len(q) >= 2 and q[1].startswith('0x') and not l.startswith('#'):
            addr_of[q[0]] = int(q[1], 16)
        elif fn == 'compiled.txt' and len(q) >= 3 and q[0].startswith('0x'):
            addr_of[q[2]] = int(q[0], 16)


def check(c, s, addr):
    """None when it folds, else why not."""
    code, rel = c.function_bytes(s)
    code = bytearray(code)
    img = bytearray(image.read(addr, len(code)))
    for off, tgt, typ in rel:
        field = struct.unpack('<I', bytes(img[off:off + 4]))[0]
        addend = struct.unpack('<i', bytes(code[off:off + 4]))[0]
        if typ == 0x14:                 # REL32
            want = (addr + off + 4 + field) & 0xFFFFFFFF
            have = addr_of.get(tgt)
            if have is not None and (have + addend) & 0xFFFFFFFF != want:
                return 'relocation +0x%X to %s: 0x%X, the image calls 0x%X' % (off, tgt[:40], have, want)
        elif typ == 0x06:               # DIR32
            have = addr_of.get(tgt)
            if have is not None and (have + addend) & 0xFFFFFFFF != field:
                return 'relocation +0x%X to %s: 0x%X, the image has 0x%X' % (off, tgt[:40], have + addend, field)
        code[off:off + 4] = img[off:off + 4]
    if code != img:
        return 'bytes differ at +0x%X' % next(i for i in range(len(code)) if code[i] != img[i])
    return None


same = differ = missing = 0
for dp, _dn, fs in os.walk(os.path.join(ROOT, 'src')):
    for f in fs:
        if not f.endswith(('.c', '.cpp')):
            continue
        p = os.path.join(dp, f)
        t = open(p, encoding='utf-8', errors='replace').read()
        items = re.findall(r'^// (\S+) \(folded into 0x([0-9A-F]+)\)$', t, re.M)
        if not items:
            continue
        obj = os.path.join(ROOT, 'build', os.path.relpath(os.path.splitext(p)[0], ROOT) + '.obj')
        if not os.path.exists(obj):
            continue
        c = Coff(obj)
        byname = dict((s['name'], s) for s in c.symbol_list if s.get('section', 0) > 0)
        for name, addr in items:
            s = byname.get(name)
            if s is None:
                missing += 1
                print('missing  %-60s %s' % (name[:60], f))
                continue
            why = check(c, s, int(addr, 16))
            if why is None:
                same += 1
            else:
                differ += 1
                print('DIFFERS  %-55s %s: %s' % (name[:55], f, why))
print('%d identical, %d differ, %d missing' % (same, differ, missing))
