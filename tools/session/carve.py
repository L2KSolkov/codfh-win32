"""carve.py ASM LABEL...: cut XDK data stand-in labels down to what is still binary (PLAN M5).

A data stand-in (src/xdk/standin_data_*.asm) transcribes a whole .data gap; once compiled pieces
are placed inside it (config/splits.txt names them), its label overlaps them. For each LABEL
(its address from config/compiled.txt, its size from its bytes), the label's segment is replaced
by one segment per `-` range of config/splits.txt left inside it, labelled `_unk_ADDR` with the
image's bytes, and its compiled.txt row by theirs."""
import os
import re
import sys

sys.path.insert(0, os.path.join(os.path.dirname(os.path.abspath(__file__)), '..'))
from xbe import Xbe  # noqa: E402

ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
asm, labels = sys.argv[1], sys.argv[2:]
image = Xbe(os.path.join(ROOT, 'orig', 'Game_XboxMultiplayer.xbe'))
text = open(asm, encoding='utf-8').read()
cfg_path = os.path.join(ROOT, 'config', 'compiled.txt')
cfg = open(cfg_path, encoding='utf-8').read().split('\n')
obj = 'build/' + os.path.splitext(os.path.relpath(asm, ROOT).replace(os.sep, '/'))[0] + '.obj'
ranges = []
for l in open(os.path.join(ROOT, 'config', 'splits.txt'), encoding='utf-8'):
    q = l.split()
    if len(q) >= 4 and q[0].startswith('0x') and q[3] == '-':
        ranges.append((int(q[0], 16), int(q[1], 16)))


def segment(name, addr, data, alias):
    lines = ['%s SEGMENT BYTE PUBLIC ALIAS(\'%s\') \'DATA\'' % (name, alias),
             '; // match: _unk_%06X @ 0x%08X' % (addr, addr), 'PUBLIC _unk_%06X' % addr,
             '_unk_%06X LABEL BYTE' % addr]
    for k in range(0, len(data), 16):
        lines.append('        db ' + ', '.join('0%02Xh' % b for b in data[k:k + 16]))
    lines.append('%s ENDS' % name)
    return '\n'.join(lines) + '\n'


for label in labels:
    m = re.search(r'^(\w+) SEGMENT BYTE PUBLIC ALIAS\(\'([^\']+)\'\) \'DATA\'\n; // match: %s @ 0x([0-9A-F]+)\n'
                  r'.*?^\1 ENDS\n' % re.escape(label), text, re.M | re.S)
    assert m, label
    seg, alias, start = m.group(1), m.group(2), int(m.group(3), 16)
    size = sum(len(re.findall(r'0[0-9A-F]{2}h', l)) for l in m.group(0).split('\n') if l.strip().startswith('db '))
    end = start + size
    keep = [(max(a, start), min(b, end)) for a, b in ranges if a < end and b > start]
    new = ''.join(segment('%s_%d' % (seg, k), a, bytes(image.read(a, b - a)), alias) for k, (a, b) in enumerate(keep))
    text = text[:m.start()] + new + text[m.end():]
    row = next(i for i, l in enumerate(cfg) if l.startswith('0x%08X %s %s' % (start, obj, label)))
    cfg[row:row + 1] = ['0x%08X %s _unk_%06X' % (a, obj, a) for a, b in keep]
    print('%s 0x%X-0x%X: %d ranges kept, %d bytes' % (label, start, end, len(keep), sum(b - a for a, b in keep)))
open(asm, 'w', encoding='utf-8', newline='\n').write(text)
open(cfg_path, 'w', encoding='utf-8', newline='\n').write('\n'.join(cfg))
