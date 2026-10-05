"""lib_scan.py [LIB ...]

Locates every member of the installed XDK libraries in the original image.
Each member section with bytes (code, read-only and initialized data) becomes
a pattern with its relocation fields wildcarded; the pattern is anchored on
its longest literal run, and every exact masked match at the section's
alignment is recorded. A section found exactly once is located; one found
several times is ambiguous; one not found either was stripped by /OPT:REF or
differs from the image (a later QFE).

Writes build/libscan/<lib>.json and prints a per-library summary."""
import json
import os
import sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
from coff import Coff, RELOC_WIDTH  # noqa: E402
from lib import Library  # noqa: E402
from xbe import Xbe  # noqa: E402

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
XDK_LIB = os.path.join(os.environ.get('XDK', r'C:\XDK'), 'xbox', 'lib')


def lib_path(lib):
    """A library name: a file in XDK/xbox/lib, or (with a slash) a path in
    the worktree, e.g. xdklib/dsound.lib (the XDK 5849 copies whose members
    match the image where the installed XDK's do not)."""
    return os.path.join(ROOT, lib) if '/' in lib else os.path.join(XDK_LIB, lib)

# The release libraries whose version stamps appear in the image, plus
# xnets.lib, which supplies the XNET section inside XONLINES.
LIBRARIES = ['libcmt.lib', 'libcpmt.lib', 'xapilib.lib', 'xboxkrnl.lib', 'd3d8.lib',
             'd3dx8.lib', 'dsound.lib', 'xonlines.lib', 'xnets.lib', 'xgraphics.lib',
             'xvoice.lib', 'uix.lib']

SKIP_PREFIXES = ('.debug', '.drectve', '.XBLD', '.bss', '.sxdata')
MIN_ANCHOR = 6


def alignment(chars):
    code = (chars >> 20) & 0xF
    return 1 << (code - 1) if code else 16


def masked(section):
    data = section['data']
    mask = bytearray(len(data))
    for offset, _sym, rtype in section['relocs']:
        for k in range(RELOC_WIDTH.get(rtype, 4)):
            if offset + k < len(mask):
                mask[offset + k] = 1
    return data, mask


def literal_runs(mask):
    """(start, end) spans of bytes outside relocation fields."""
    runs = []
    start = None
    for i in range(len(mask) + 1):
        if i < len(mask) and not mask[i]:
            if start is None:
                start = i
        elif start is not None:
            runs.append((start, i))
            start = None
    return runs


def anchor(runs):
    best = (0, 0)
    for run in runs:
        if run[1] - run[0] > best[1] - best[0]:
            best = run
    return best


class Image(object):
    def __init__(self, path):
        self.xbe = Xbe(path)
        self.data = self.xbe.data
        self.ranges = [(s['raw'], s['raw'] + s['rsize'], s) for s in self.xbe.sections]

    def va(self, offset):
        for lo, hi, s in self.ranges:
            if lo <= offset < hi:
                return s['va'] + offset - lo, s['name']
        return None, None

    def find(self, data, mask, align):
        runs = literal_runs(mask)
        lo, hi = anchor(runs)
        if hi - lo < MIN_ANCHOR:
            return None
        key = bytes(data[lo:hi])
        hits = []
        pos = self.data.find(key)
        while pos >= 0:
            start = pos - lo
            if start >= 0 and start + len(data) <= len(self.data):
                va, sname = self.va(start)
                if va is not None and va % align == 0:
                    image = self.data
                    if all(image[start + s:start + e] == data[s:e] for s, e in runs):
                        hits.append((va, sname))
            pos = self.data.find(key, pos + 1)
        return hits


def scan(library_name, image):
    library = Library(lib_path(library_name))
    members = []
    for member_name, body in library.members:
        if body[:2] != b'\x4c\x01':
            continue  # import/archive stubs rather than COFF objects
        try:
            obj = Coff(member_name, body)
        except ValueError:
            continue
        sections = []
        for section in obj.sections:
            if section['name'].startswith(SKIP_PREFIXES) or section['size'] == 0:
                continue
            data, mask = masked(section)
            hits = image.find(data, mask, alignment(section['chars']))
            symbols = [s['name'] for s in obj.symbol_list
                       if s['section'] == section['index'] and s['class'] == 2]
            sections.append({
                'section': section['name'], 'size': section['size'],
                'symbols': symbols,
                'hits': ['0x%08X %s' % h for h in hits] if hits is not None else None,
            })
        members.append({'member': member_name, 'sections': sections})
    return members


def summarize(name, members):
    located = ambiguous = missing = unanchored = 0
    for member in members:
        for s in member['sections']:
            if s['hits'] is None:
                unanchored += 1
            elif len(s['hits']) == 1:
                located += 1
            elif s['hits']:
                ambiguous += 1
            else:
                missing += 1
    touched = sum(1 for m in members if any(s['hits'] and len(s['hits']) == 1
                                            for s in m['sections']))
    print('%-14s members %4d (%4d located)  sections: located %5d  ambiguous %4d  '
          'absent %5d  too short %4d' % (name, len(members), touched, located, ambiguous,
                                         missing, unanchored))


def main(argv):
    image = Image(os.path.join(ROOT, 'orig', 'Game_XboxMultiplayer.xbe'))
    out = os.path.join(ROOT, 'build', 'libscan')
    if not os.path.isdir(out):
        os.makedirs(out)
    for name in argv[1:] or LIBRARIES:
        members = scan(name, image)
        json.dump(members, open(os.path.join(out, name + '.json'), 'w'), indent=1)
        summarize(name, members)


if __name__ == '__main__':
    main(sys.argv)
