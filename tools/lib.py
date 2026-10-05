"""Reader for MSVC .lib archives (COFF archive format).

lib.py LIB                 list members
lib.py LIB MEMBER OUT      extract one member (matched by full or base name)"""
import os
import sys


class Library(object):
    def __init__(self, path):
        self.path = path
        data = open(path, 'rb').read()
        if data[:8] != b'!<arch>\n':
            raise ValueError('%s is not an archive' % path)
        self.members = []
        longnames = b''
        offset = 8
        while offset + 60 <= len(data):
            header = data[offset:offset + 60]
            name = header[:16].decode('latin1').rstrip()
            size = int(header[48:58].decode('latin1').strip())
            body = data[offset + 60:offset + 60 + size]
            if name == '//':
                longnames = body
            elif name == '/':
                pass  # the two linker members (symbol indexes)
            elif name.startswith('/') and name[1:].isdigit():
                start = int(name[1:])
                end = longnames.index(b'\0', start)
                self.members.append((longnames[start:end].decode('latin1'), body))
            else:
                self.members.append((name.rstrip('/'), body))
            offset += 60 + size + (size & 1)

    def find(self, name):
        wanted = name.replace('/', '\\').lower()
        for member, body in self.members:
            full = member.replace('/', '\\').lower()
            if full == wanted or os.path.basename(full) == wanted:
                return member, body
        return None, None


def main(argv):
    if len(argv) == 2:
        for member, body in Library(argv[1]).members:
            print('%8d  %s' % (len(body), member))
        return 0
    if len(argv) == 4:
        member, body = Library(argv[1]).find(argv[2])
        if member is None:
            print('no member %s' % argv[2])
            return 1
        open(argv[3], 'wb').write(body)
        print('%s -> %s (%d bytes)' % (member, argv[3], len(body)))
        return 0
    print(__doc__)
    return 2


if __name__ == '__main__':
    sys.exit(main(sys.argv))
