"""literalpieces.py [--apply] OBJ SYMBOL ADDR: the string literals (??_C@...) a placed data
piece or function SYMBOL (at ADDR) points at, as data pieces: prints ADDR=NAME pairs for
datapieces.py (each literal's address is the one the original encodes at the relocation),
and with --apply runs datapieces.py --apply on them."""
import os
import struct
import subprocess
import sys

sys.path.insert(0, os.path.join(os.path.dirname(os.path.abspath(__file__)), '..'))
from coff import Coff  # noqa: E402
from xbe import Xbe  # noqa: E402

ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
args = sys.argv[1:]
apply = '--apply' in args
if apply:
    args.remove('--apply')
obj_path, sym, addr = args[0], args[1], int(args[2], 16)
obj = Coff(os.path.join(ROOT, obj_path))
image = Xbe(os.path.join(ROOT, 'orig', 'Game_XboxMultiplayer.xbe'))
symbol = obj.find_function(sym)
data, relocs = obj.function_bytes(symbol)
original = image.read(addr, len(data))
pairs = []
seen = set()
for offset, target, rtype in relocs:
    if not target.startswith('??_C@') or target in seen:
        continue
    seen.add(target)
    addend = struct.unpack_from('<i', data, offset)[0]
    value = struct.unpack_from('<I', original, offset)[0] - addend
    pairs.append('0x%X=%s' % (value, target))
pairs.sort(key=lambda p: int(p.split('=')[0], 16))
print('\n'.join(pairs))
if apply and pairs:
    subprocess.run([sys.executable, os.path.join(os.path.dirname(os.path.abspath(__file__)), 'datapieces.py'),
                    '--apply', obj_path] + pairs, cwd=ROOT)
