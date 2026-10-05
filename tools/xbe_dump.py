"""xbe_dump.py XBE [XBE2]

Prints an XBE's header, certificate, library versions and sections. With two
files, prints them side by side and marks every field that differs."""
import sys
import os

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
from xbe import Xbe  # noqa: E402


def describe(x):
    rows = []
    for name, value in x.header():
        rows.append(('header.' + name, '0x%08X' % value))
    for name in ('debug_path', 'debug_file'):
        address = x.field(name)
        rows.append(('string.' + name, x.string(address) if address else '-'))
    for name, value in x.certificate():
        rows.append(('cert.' + name, value if isinstance(value, str) else '0x%08X' % value))
    for name, major, minor, build, flags in x.library_versions():
        rows.append(('lib.' + name, '%d.%d.%d flags 0x%04X' % (major, minor, build, flags)))
    for i, s in enumerate(x.sections):
        rows.append(('section.%02d' % i, '%-10s va 0x%08X vsize 0x%08X rsize 0x%08X flags 0x%X'
                     % (s['name'], s['va'], s['vsize'], s['rsize'], s['flags'])))
    return rows


def main(argv):
    if len(argv) == 2:
        for key, value in describe(Xbe(argv[1])):
            print('%-28s %s' % (key, value))
        return 0
    if len(argv) == 3:
        a = dict(describe(Xbe(argv[1])))
        b = dict(describe(Xbe(argv[2])))
        for key in sorted(set(a) | set(b)):
            mark = '  ' if a.get(key) == b.get(key) else '* '
            print('%s%-26s %-44s %s' % (mark, key, a.get(key, '-'), b.get(key, '-')))
        return 0
    print(__doc__)
    return 2


if __name__ == '__main__':
    sys.exit(main(sys.argv))
