"""constslast.py SRC...: define a unit's .rdata constants after its other data (PLAN M7).

VC7.1 emits a unit's data definitions in reverse definition order, so its constants' .rdata
section comes before the texts of its data initializers (a table of strings) only when the
constants are defined after those initializers. Where the image has an object's constants
first, this moves each `// 0xADDR` + definition whose address is in .rdata (0x3CD300-0x426D40)
from the unit's data definitions block to its end (before `// End of its data definitions.`,
or the first blank line), keeping their order."""
import re
import sys

NOTE = ("// (Defined after the data: VC7.1 emits a unit's data definitions in reverse order, and\n"
        "// the image has these constants before the data's texts.)\n")
HEAD = "// Its data definitions (PLAN M5), in the image's address order.\n"


def rd(p):
    raw = open(p, 'rb').read().decode('utf-8')
    return raw.replace('\r\n', '\n'), ('\r\n' if '\r\n' in raw else '\n')


for p in sys.argv[1:]:
    t, nl = rd(p)
    if HEAD not in t:
        print(p, 'no data block')
        continue
    k = t.index(HEAD) + len(HEAD)
    e = t.find("// End of its data definitions.\n", k)
    b = t.find('\n\n', k)
    if e < 0 or (0 <= b < e):
        e = b + 1
    block = t[k:e]
    items = re.findall(r'// 0x[0-9A-F]{8}\n(?:(?!// 0x[0-9A-F]{8}\n).*\n)*?(?=// 0x[0-9A-F]{8}\n|\Z)', block)
    if ''.join(items) != block:
        print(p, 'block not all address items; skipped')
        continue
    consts = [x for x in items if 0x3CD300 <= int(x[5:13], 16) < 0x426D40]
    rest = [x for x in items if x not in consts]
    if not consts or not rest or items == rest + consts:
        print(p, 'nothing to move')
        continue
    t = t[:k] + ''.join(rest) + NOTE + ''.join(consts) + t[e:]
    open(p, 'wb').write(t.replace('\n', nl).encode('utf-8'))
    print(p, '%d constants after %d other definitions' % (len(consts), len(rest)))
