"""xdk_members.py [--check]: extract the installed XDK library members that
config/compiled.txt places (PLAN M3) into build/xdk/, from the manifest
config/xdk_members.txt (`OBJECT LIB MEMBER`, OBJECT relative to the root,
LIB a file in XDK\\xbox\\lib).

With --check, also match every placed function with tools/match.py (the
build's gate for them, like build_sources.py for the compiled units)."""
import os
import sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
from lib import Library  # noqa: E402
from lib_scan import lib_path  # noqa: E402

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
XDK_LIB = os.path.join(os.environ.get('XDK', r'C:\XDK'), 'xbox', 'lib')
MANIFEST = os.path.join(ROOT, 'config', 'xdk_members.txt')


def manifest():
    rows = []
    if not os.path.exists(MANIFEST):
        return rows
    for line in open(MANIFEST, encoding='utf-8'):
        line = line.strip()
        if line and not line.startswith('#'):
            obj, lib, member = line.split(None, 2)
            rows.append((obj, lib, member))
    return rows


def extract():
    libs = {}
    count = 0
    for obj, lib, member in manifest():
        path = os.path.join(ROOT, obj)
        if lib not in libs:
            libs[lib] = Library(lib_path(lib)).members
        name, _, nth = member.partition('#')
        data = [d for m, d in libs[lib] if m == name][int(nth or 0)]
        if os.path.exists(path) and open(path, 'rb').read() == data:
            continue
        os.makedirs(os.path.dirname(path), exist_ok=True)
        open(path, 'wb').write(data)
        count += 1
    return count


def check(failed=None):
    import match
    from xbe import Xbe
    image = Xbe(match.ORIGINAL)
    objs = set(o for o, _, _ in manifest())
    failures = 0
    cache = {}
    rows = []
    for line in open(os.path.join(ROOT, 'config', 'compiled.txt'), encoding='utf-8'):
        if line.startswith('0x'):
            addr, obj, name = line.split(None, 2)
            if obj in objs:
                rows.append((addr, obj, name.strip()))
    # names resolve to the placed pieces first, as in the placement linker:
    # the object's own pieces, then other objects' public ones (an assembler
    # member's local labels and static tables are its own)
    placed = {}
    own = {}
    for addr, obj, name in rows:
        if obj not in cache:
            cache[obj] = match.Coff(os.path.join(ROOT, obj))
        own.setdefault(obj, {})[name] = int(addr, 16)
        sym = cache[obj].find_function(name)
        if sym is None or sym['class'] not in (3, 6):
            placed.setdefault(name, int(addr, 16))
    for addr, obj, name in rows:
        names = dict(placed)
        names.update(own[obj])
        ok, message = match.compare(cache[obj], name, int(addr, 16), image, names)
        if not ok:
            print('DIFF ' + message)
            failures += 1
            if failed is not None:
                failed.append(int(addr, 16))
    print('xdk members: %d placed functions, %d differ' % (sum(1 for l in open(os.path.join(ROOT, 'config', 'compiled.txt'))
                                                               if l.split()[1:2] and l.split()[1] in objs), failures))
    return failures


if __name__ == '__main__':
    extract()
    sys.exit(1 if '--check' in sys.argv and check() else 0)
