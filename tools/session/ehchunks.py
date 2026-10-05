"""ehchunks.py [--apply] [--skip SUB1,SUB2] [LO HI]: EH chunks (config/splits.txt chunk_of_X rows) that are not
placed although their function X is matched: prints the `// match: __ehhandler$...` lines each
needs (the funclet at the chunk's start, named from the handler's offset, and the handler, the
chunk's `mov eax, FUNCINFO; jmp ___CxxFrameHandler`). With --apply, inserts them under the
function's match line and adds their config/compiled.txt rows (next to the function's)."""
import os
import re
import sys

sys.path.insert(0, os.path.join(os.path.dirname(os.path.abspath(__file__)), '..'))
from xbe import Xbe  # noqa: E402

ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
args = sys.argv[1:]
apply = '--apply' in args
if apply:
    args.remove('--apply')
skip = []
if '--skip' in args:
    k = args.index('--skip')
    skip = args[k + 1].split(',')
    del args[k:k + 2]
lo, hi = (int(args[0], 16), int(args[1], 16)) if len(args) == 2 else (0, 1 << 32)

image = Xbe(os.path.join(ROOT, 'orig', 'Game_XboxMultiplayer.xbe'))
compiled = open(os.path.join(ROOT, 'config', 'compiled.txt'), encoding='utf-8').read()
placed = {int(l.split()[0], 16) for l in compiled.splitlines() if l.startswith('0x')}

# every function match line: address -> (unit path, symbol)
matches = {}
src_dir = os.path.join(ROOT, 'src', 'recovered')
for fn in os.listdir(src_dir):
    if not fn.endswith('.cpp'):
        continue
    for m in re.finditer(r'^// match: (\S+) @ 0x([0-9A-Fa-f]+)$',
                         open(os.path.join(src_dir, fn), encoding='utf-8').read(), re.M):
        matches[int(m.group(2), 16)] = (os.path.join(src_dir, fn), m.group(1))

todo = []
for line in open(os.path.join(ROOT, 'config', 'splits.txt'), encoding='utf-8'):
    p = line.split()
    if len(p) < 4 or not p[3].startswith('chunk_of_'):
        continue
    start, end = int(p[0], 16), int(p[1], 16)
    if not lo <= start < hi or start in placed:
        continue
    owner = int(p[3][len('chunk_of_'):], 16)
    if owner not in matches or owner not in placed:
        continue
    data = image.read(start, end - start)
    handler = None
    for k in range(len(data) - 9):
        if data[k] == 0xB8 and data[k + 5] == 0xE9:
            handler = start + k
            break
    if handler is None:
        print('no handler in chunk', hex(start), file=sys.stderr)
        continue
    path, sym = matches[owner]
    if any(s in sym for s in skip):
        continue
    lines = []
    if handler > start:
        lines.append('// match: __ehhandler$%s-0x%X @ 0x%08X' % (sym, handler - start, start))
    lines.append('// match: __ehhandler$%s @ 0x%08X' % (sym, handler))
    todo.append((owner, path, sym, lines, start, handler))
    print(os.path.basename(path), '\n'.join(lines))

if apply:
    by_file = {}
    for item in todo:
        by_file.setdefault(item[1], []).append(item)
    for path, items in by_file.items():
        text = open(path, encoding='utf-8').read()
        for owner, _, sym, lines, start, handler in items:
            head = '// match: %s @ 0x%08X\n' % (sym, owner)
            assert text.count(head) == 1, head
            text = text.replace(head, head + ''.join(l + '\n' for l in lines), 1)
        open(path, 'w', encoding='utf-8', newline='\n').write(text)
    rows = compiled.splitlines()
    for owner, path, sym, lines, start, handler in todo:
        obj = 'build/src/recovered/%s.obj' % os.path.splitext(os.path.basename(path))[0]
        k = next(n for n, r in enumerate(rows) if r.startswith('0x%08X ' % owner))
        new = []
        for l in lines:
            m = re.match(r'// match: (\S+) @ 0x([0-9A-F]+)', l)
            new.append('0x%08X %s %s' % (int(m.group(2), 16), obj, m.group(1)))
        rows[k + 1:k + 1] = new
    open(os.path.join(ROOT, 'config', 'compiled.txt'), 'w', encoding='utf-8', newline='\n').write(
        '\n'.join(rows) + '\n')
