"""objlist.py OBJ [SYM...]: disassemble every function of an object (or the
named ones), in section order, with each relocation's target symbol shown
after the instruction that holds it. Used to read RAD's Bink library members
(docs/reference/Bink) for their names, sections and code."""
import os as _os_repo
_REPO = _os_repo.path.dirname(_os_repo.path.dirname(_os_repo.path.abspath(__file__)))  # the repository root, from this file's location
import struct
import sys

import capstone

sys.path.insert(0, _os_repo.path.join(_REPO, r'tools'))
from coff import Coff  # noqa: E402


def main():
    c = Coff(sys.argv[1])
    want = set(sys.argv[2:])
    md = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)
    funcs = [s for s in c.symbol_list
             if s['section'] > 0 and (s['type'] >> 4) == 2
             and (not want or s['name'] in want)]
    funcs.sort(key=lambda s: (s['section'], s['value']))
    for s in funcs:
        sec = c.sections[s['section'] - 1]
        code, rels = c.function_bytes(s)
        print('== %s  [%s] %s size 0x%X' % (s['name'], sec['name'],
                                           'static' if s['class'] == 3 else 'global', len(code)))
        for i in md.disasm(bytes(code), 0):
            notes = []
            for off, name, t in rels:
                if i.address <= off < i.address + i.size:
                    add = struct.unpack_from('<i', code, off)[0]
                    notes.append('%s%s' % (name, ('+0x%X' % add) if add and t != 0x14 else ''))
            print('%4x  %-40s %s' % (i.address, i.mnemonic + ' ' + i.op_str,
                                     ('; ' + ', '.join(notes)) if notes else ''))


if __name__ == '__main__':
    main()
