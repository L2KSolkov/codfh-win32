"""slotpairs.py OBJ SYMBOL ADDR: pair our frame offsets with the image's, instruction by
instruction (for functions whose code already aligns: same length and shapes); prints each
pair that differs (ours -> image) with how often it occurs."""
import collections
import re
import sys

import capstone

sys.path.insert(0, __import__('os').path.join(__import__('os').path.dirname(__import__('os').path.abspath(__file__)), '..'))
from coff import Coff  # noqa: E402
from xbe import Xbe  # noqa: E402

c = Coff(sys.argv[1])
code, _ = c.function_bytes(c.find_function(sys.argv[2]))
addr = int(sys.argv[3], 16)
img = Xbe(__import__('os').path.join(__import__('os').path.dirname(__import__('os').path.dirname(__import__('os').path.dirname(__import__('os').path.abspath(__file__)))), 'orig', 'Game_XboxMultiplayer.xbe')).read(addr, len(code))
md = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)
a = list(md.disasm(bytes(code), 0))
b = list(md.disasm(img, addr))
pairs = collections.Counter()
for x, y in zip(a, b):
    ox = re.findall(r'ebp ([-+]) (0x[0-9a-f]+|\w+ \+ 0x[0-9a-f]+|[a-z]+ - 0x[0-9a-f]+)\]', x.op_str)
    oy = re.findall(r'ebp ([-+]) (0x[0-9a-f]+|\w+ \+ 0x[0-9a-f]+|[a-z]+ - 0x[0-9a-f]+)\]', y.op_str)
    fx = re.findall(r'- (0x[0-9a-f]+)\]', x.op_str)
    fy = re.findall(r'- (0x[0-9a-f]+)\]', y.op_str)
    for u, v in zip(fx, fy):
        if u != v:
            pairs[(u, v)] += 1
for (u, v), n in sorted(pairs.items(), key=lambda p: int(p[0][1], 16)):
    print('%6s -> %6s  x%d' % (u, v, n))
