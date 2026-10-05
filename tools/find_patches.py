"""find_patches.py [LIB ...]

The image's .text digest does not match its bytes, so .text was modified after
the XBE was signed. This locates candidates: for every code section of the
installed XDK libraries, it finds the address of the section's public symbol
through the IDA database's names, compares the section there with relocation
fields masked, and reports sections that differ in only a few bytes — code
that is otherwise identical to the library, i.e. patched."""
import os
import re
import sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
from coff import Coff, RELOC_WIDTH  # noqa: E402
from lib import Library  # noqa: E402
from lib_scan import LIBRARIES, XDK_LIB  # noqa: E402
from match import symbol_table  # noqa: E402
from xbe import Xbe  # noqa: E402

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
MAX_DIFF = 24


def candidates(name):
    out = [name]
    bare = name.lstrip('_@')
    out.append(bare)
    out.append(re.sub(r'@\d+$', '', bare))
    out.append('_' + re.sub(r'@\d+$', '', bare))
    return out


def main(argv):
    image = Xbe(os.path.join(ROOT, 'orig', 'Game_XboxMultiplayer.xbe'))
    table = symbol_table()
    for library_name in argv[1:] or LIBRARIES:
        library = Library(os.path.join(XDK_LIB, library_name))
        for member_name, body in library.members:
            if body[:2] != b'\x4c\x01':
                continue
            obj = Coff(member_name, body)
            for section in obj.sections:
                if not (section['chars'] & 0x20) or section['size'] < 4:
                    continue  # code sections only
                publics = [s for s in obj.symbol_list
                           if s['section'] == section['index'] and s['value'] == 0
                           and s['class'] == 2]
                address = None
                for symbol in publics:
                    for candidate in candidates(symbol['name']):
                        if candidate in table:
                            address = table[candidate]
                            break
                    if address:
                        break
                if address is None:
                    continue
                data = section['data']
                mask = bytearray(len(data))
                for offset, _s, rtype in section['relocs']:
                    for k in range(RELOC_WIDTH.get(rtype, 4)):
                        if offset + k < len(mask):
                            mask[offset + k] = 1
                try:
                    here = image.read(address, len(data))
                except ValueError:
                    continue
                diffs = [i for i in range(len(data)) if not mask[i] and data[i] != here[i]]
                if 0 < len(diffs) <= MAX_DIFF:
                    first = diffs[0]
                    print('%-12s %-28s %-36s 0x%08X  %d bytes differ, first at +0x%X: '
                          'lib %s / image %s' % (
                              library_name, os.path.basename(member_name), publics[0]['name'],
                              address, len(diffs), first,
                              data[first:first + 6].hex(' '), here[first:first + 6].hex(' ')))


if __name__ == '__main__':
    main(sys.argv)
