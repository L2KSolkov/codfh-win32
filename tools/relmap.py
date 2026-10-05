"""relmap.py LIBOBJ SYMBOL ADDRESS [SYMBOL ADDRESS ...]: map a library
member's relocation targets to the image's addresses by disassembling the
member's function beside the image's copy (they must have the same
instruction sequence up to each relocation). Prints `NAME 0xADDRESS` for
each data target (target minus the member's addend), for config/aliases.txt
evidence; stops a function at the first differing mnemonic."""
import os as _os_repo
_REPO = _os_repo.path.dirname(_os_repo.path.dirname(_os_repo.path.abspath(__file__)))  # the repository root, from this file's location
import struct
import sys

import capstone

sys.path.insert(0, _os_repo.path.join(_REPO, r'tools'))
from coff import Coff  # noqa: E402
from xbe import Xbe  # noqa: E402


def main():
    c = Coff(sys.argv[1])
    img = Xbe(_os_repo.path.join(_REPO, r'orig\Game_XboxMultiplayer.xbe'))
    md = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)
    found = {}
    args = sys.argv[2:]
    for k in range(0, len(args), 2):
        sym = c.find_function(args[k])
        if sym is None:
            sys.stderr.write('no %s\n' % args[k])
            continue
        code, rels = c.function_bytes(sym)
        addr = int(args[k + 1], 16)
        icode = img.read(addr, len(code) + 64)
        li = list(md.disasm(bytes(code), 0))
        ii = list(md.disasm(bytes(icode), addr))
        for a, b in zip(li, ii):
            if a.mnemonic != b.mnemonic:
                sys.stderr.write('%s: differs at +0x%X (%s / %s)\n' % (args[k], a.address, a.mnemonic, b.mnemonic))
                break
            for off, name, t in rels:
                if a.address <= off < a.address + a.size and t != 0x14:
                    add = struct.unpack_from('<i', code, off)[0]
                    val = struct.unpack_from('<I', bytes(b.bytes), off - a.address)[0]
                    base = (val - add) & 0xFFFFFFFF
                    if name in found and found[name] != base:
                        sys.stderr.write('%s: %s at 0x%08X here, 0x%08X before\n' % (args[k], name, base, found[name]))
                    found.setdefault(name, base)
    for name, base in sorted(found.items()):
        print('%-24s 0x%08X' % (name, base))


if __name__ == '__main__':
    main()
