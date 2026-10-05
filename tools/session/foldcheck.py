"""foldcheck.py OBJ SYM ADDR...: whether an unplaced definition is byte-identical to the image's
function at ADDR, relocation fields aside (what /OPT:ICF needs to fold it there; PLAN M7)."""
import os
import sys

sys.path.insert(0, os.path.join(os.path.dirname(os.path.abspath(__file__)), '..'))
from coff import Coff  # noqa: E402
from xbe import Xbe  # noqa: E402

ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
image = Xbe(os.path.join(ROOT, 'orig', 'Game_XboxMultiplayer.xbe'))
args = sys.argv[1:]
c = Coff(args[0])
for sym, addr in zip(args[1::2], args[2::2]):
    s = next((x for x in c.symbol_list if x['name'] == sym), None)
    if s is None:
        print('%-60s missing' % sym)
        continue
    code, rel = c.function_bytes(s)
    code = bytearray(code)
    img = bytearray(image.read(int(addr, 16), len(code)))
    for off, _t, _r in rel:
        code[off:off + 4] = img[off:off + 4]
    # trailing int3/nop padding of the image is not the function's
    same = code == img
    print('%-60s %s (%d bytes)' % (sym, 'identical' if same else 'DIFFERS at +0x%X' % next(i for i in range(len(code)) if code[i] != img[i]), len(code)))
