"""m5defs.py: keep a unit's data definitions (PLAN M5) in one block, in address order.

VC7.1 lays a unit's .data/.rdata out in definition order (arrays of 64 bytes or more 8-aligned),
so definitions must follow the image's addresses. Each definition is preceded by a line
`// 0xADDRESS` (its image address); insert() adds one and keeps the block sorted.

    python tools/session/m5defs.py --resort SRC   re-sort an existing block (after hand edits)"""
import os
import re
import sys

BEGIN = '// Its data definitions (PLAN M5), in the image\'s address order.\n'
END = '// End of its data definitions.\n'


def _split(text):
    """(before, [(addr, definition text)], after) or None when the unit has no block."""
    i = text.find(BEGIN)
    if i < 0:
        return None
    j = text.find(END, i)
    body = text[i + len(BEGIN):j]
    items = []
    for m in re.finditer(r'^// (0x[0-9A-Fa-f]+)\n(.*?)(?=^// 0x[0-9A-Fa-f]+\n|\Z)', body, re.M | re.S):
        items.append((int(m.group(1), 16), m.group(2).strip('\n') + '\n'))
    # text before the first address (a typedef the definitions use): kept, above the block
    first = re.search(r'^// 0x[0-9A-Fa-f]+\n', body, re.M)
    lead = body[:first.start()] if first else body
    return text[:i] + lead, items, text[j + len(END):]


def _join(before, items, after):
    body = ''.join('// 0x%08X\n%s' % (a, d) for a, d in sorted(items))
    return before + BEGIN + body + END + after


def insert(src, addr, definition):
    text = open(src, encoding='utf-8').read()
    parts = _split(text)
    if parts is None:
        incs = list(re.finditer(r'^#include .*\n', text, re.M))
        pos = incs[-1].end() if incs else 0
        before, items, after = text[:pos] + '\n', [], '\n' + text[pos:]
    else:
        before, items, after = parts
    items = [it for it in items if it[0] != addr] + [(addr, definition.strip('\n') + '\n')]
    open(src, 'w', encoding='utf-8', newline='\n').write(_join(before, items, after))


def take_existing(src, name):
    """Removes a top-level definition of NAME outside the block (with the comment lines just
    above it) and returns its text, or None when there is none."""
    text = open(src, encoding='utf-8').read()
    parts = _split(text)
    lo, hi = (len(parts[0]), len(text) - len(parts[2])) if parts else (0, 0)
    for m in re.finditer(r'^(?!extern)(?:static )?[A-Za-z_][^\n;(]*\b%s\b(\[[^\]]*\])?\s*=\s*(\{.*?\n\};|[^\n]*;)\n'
                         % re.escape(name), text, re.M | re.S):
        if lo <= m.start() < hi:
            continue
        start = m.start()
        while True:
            prev = text.rfind('\n', 0, start - 1) + 1
            if start > 0 and text[prev:start].startswith('//') and not text[prev:start].startswith('// match:'):
                start = prev
            else:
                break
        found = text[start:m.end()]
        open(src, 'w', encoding='utf-8', newline='\n').write(text[:start] + text[m.end():])
        return found
    return None


def resort(src):
    text = open(src, encoding='utf-8').read()
    parts = _split(text)
    if parts:
        open(src, 'w', encoding='utf-8', newline='\n').write(_join(*parts))


if __name__ == '__main__' and len(sys.argv) > 2 and sys.argv[1] == '--resort':
    for s in sys.argv[2:]:
        resort(s)
