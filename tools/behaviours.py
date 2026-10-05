"""behaviours.py

Lists the RenderWare Studio behaviours the image registers with the class
factory: for each call in the game's dynamic-initializer block
(0x3096E0-0x30DBBE) preceded by four pushes (UseLinearMemory, the size,
MakeNew and the class name), prints the call's address, the class name,
MakeNew and the size, and marks the MakeNew already matched
(config/compiled.txt). docs/behaviours.md is its output."""
import os
import sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
from xbe import Xbe  # noqa: E402

import capstone  # noqa: E402

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))


def main():
    image = Xbe(os.path.join(ROOT, 'orig', 'Game_XboxMultiplayer.xbe'))
    done = set()
    for line in open(os.path.join(ROOT, 'config', 'compiled.txt')):
        parts = line.split()
        if parts and parts[0].startswith('0x'):
            done.add(int(parts[0], 16))
    lo, hi = 0x3096E0, 0x30DBBE
    md = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)
    ins = list(md.disasm(image.read(lo, hi - lo), lo))
    for k, i in enumerate(ins):
        if i.mnemonic != 'call' or k < 5:
            continue
        pushes = [p for p in ins[k - 5:k] if p.mnemonic == 'push']
        if len(pushes) < 4:
            continue
        try:
            use, size, make_new, name = [int(p.op_str, 16) for p in pushes[-4:]]
        except ValueError:
            continue
        if 0x12000 <= make_new < 0x2C0000 and 0x3C0000 <= name < 0x440000:
            text = image.read(name, 64).split(b'\0')[0].decode(errors='replace')
            print('0x%x %s 0x%x 0x%x%s' % (i.address, text, make_new, size,
                                          ' DONE' if make_new in done else ''))


if __name__ == '__main__':
    main()
