"""unpad.py ADDR...: a zero slot defined as a global is really padding (PLAN M5).

A standalone zero global compiles into .bss, never .data: a zero dword the image has in .data
between units is the alignment padding before the next unit's data (8-aligned when that unit has
an array of 64 bytes or more). For each ADDR: removes its definition from its unit's m5defs
block, its match line and config/compiled.txt row, and merges its config/splits.txt range into
the range before it (the piece's trailing padding)."""
import glob
import os
import re
import sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import m5defs  # noqa: E402

ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
for arg in sys.argv[1:]:
    addr = int(arg, 16)
    done = False
    for src in glob.glob(os.path.join(ROOT, 'src', '**', '*.c*'), recursive=True):
        text = open(src, encoding='utf-8', errors='replace').read()
        parts = m5defs._split(text)
        if not parts or addr not in [a for a, _ in parts[1]]:
            continue
        before, items, after = parts
        text = m5defs._join(before, [it for it in items if it[0] != addr], after)
        text = re.sub(r'^// match: \S+ @ 0x%08X\n' % addr, '', text, flags=re.M)
        open(src, 'w', encoding='utf-8', newline='\n').write(text)
        done = True
        print('%s: removed 0x%X' % (os.path.relpath(src, ROOT), addr))
    if not done:
        sys.exit('no definition at 0x%X' % addr)
    cfg = os.path.join(ROOT, 'config', 'compiled.txt')
    rows = open(cfg, encoding='utf-8').read().split('\n')
    open(cfg, 'w', encoding='utf-8', newline='\n').write(
        '\n'.join(r for r in rows if not r.startswith('0x%08X ' % addr)))
    sp = os.path.join(ROOT, 'config', 'splits.txt')
    lines = open(sp, encoding='utf-8').read().split('\n')
    k = next(i for i, l in enumerate(lines) if l.startswith('0x%08X ' % addr))
    prev = lines[k - 1].split()
    assert prev[1] == '0x%08X' % addr, lines[k - 1]
    end = lines[k].split()[1]
    lines[k - 1] = '%s %s %-10s %s' % (prev[0], end, prev[2], prev[3])
    del lines[k]
    open(sp, 'w', encoding='utf-8', newline='\n').write('\n'.join(lines))
