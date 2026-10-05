"""xdkplace.py [LIB ...]: place installed XDK library members' functions
(PLAN M3). For every code section of every member that lib_scan's pattern
search finds exactly once in the image, each function symbol in it is
matched with tools/match.py against its address; the external names its
relocations use are resolved from the image's encodings (consistently across
every site) and the missing ones are added to config/aliases.txt. Placed
functions are written to config/compiled.txt and their objects to
config/xdk_members.txt (tools/xdk_members.py extracts them into build/xdk/).

Prints per library: sections located, functions placed, and why the rest
were not."""
import collections
import os
import re
import struct
import sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import match  # noqa: E402
from coff import Coff, IMAGE_REL_I386_DIR32, IMAGE_REL_I386_REL32  # noqa: E402
from lib import Library  # noqa: E402
from lib_scan import Image, LIBRARIES, XDK_LIB, alignment, lib_path, masked  # noqa: E402
from xbe import Xbe  # noqa: E402

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
CFG = os.path.join(ROOT, 'config', 'compiled.txt')
ALIASES = os.path.join(ROOT, 'config', 'aliases.txt')
MANIFEST = os.path.join(ROOT, 'config', 'xdk_members.txt')
CODE = 0x20


def flat(member):
    return re.sub(r'[\\/:]', '_', member)


def main(argv):
    libs = argv[1:] or LIBRARIES
    image = Image(match.ORIGINAL)
    xbe = Xbe(match.ORIGINAL)
    placed = set(int(l.split()[0], 16) for l in open(CFG, encoding='utf-8') if l.startswith('0x'))
    rows, members, aliases = [], {}, {}
    alias_evidence = {}
    conflicts = set()
    for lib in libs:
        stat = collections.Counter()
        lb = Library(lib_path(lib))
        seen = collections.Counter()
        for member, data in lb.members:
            nth = seen[member]
            seen[member] += 1
            if data[:2] != b'L':
                continue
            try:
                c = Coff(member, data)
            except ValueError:
                continue
            spec = member + ('#%d' % nth if nth else '')
            objpath = 'build/xdk/%s/%s' % (os.path.splitext(flat(lib))[0], flat(spec))
            for k, sec in enumerate(c.sections):
                if not (sec['chars'] & CODE) or not sec['data']:
                    continue
                d, mask = masked(sec)
                hits = image.find(d, mask, alignment(sec['chars']))
                if hits is not None and len(hits) == 1:
                    stat['located'] += 1
                    base = hits[0][0]
                elif hits == []:
                    stat['absent'] += 1
                    continue
                else:
                    # too short to anchor, or found several times: the
                    # address the image's symbols give a function of the
                    # section's name decides (match.py then checks it)
                    base = None
                    for s in c.symbol_list:
                        if s['section'] == k + 1 and (s['type'] >> 4) == 2 and s['class'] == 2:
                            a = match.resolve_name(s['name'], {})
                            if a is not None:
                                base = a - s['value']
                                break
                    if base is None or (hits and base not in [h[0] for h in hits]):
                        stat['too short' if hits is None else 'ambiguous'] += 1
                        continue
                    stat['by name'] += 1
                # functions, and the labels (and static jump tables) inside assembler members' functions
                # (function_bytes stops at them): each piece is placed and
                # checked on its own, and together they cover the function
                syms = [s for s in c.symbol_list if s['section'] == k + 1 and not s['name'].startswith(('$', '.'))
                        and s['class'] in (2, 3, 6)]
                for s in syms:
                    addr = base + s['value']
                    if addr in placed:
                        stat['already'] += 1
                        continue
                    code, rels = c.function_bytes(s)
                    if xbe.section_at(addr) is None or xbe.section_at(addr + len(code) - 1) is None:
                        stat['outside'] += 1
                        continue
                    # the names its relocations need, from the image's encodings
                    need = {}
                    for off, name, rtype in rels:
                        site = addr + off
                        field = struct.unpack('<I', xbe.read(site, 4))[0]
                        addend = struct.unpack_from('<i', code, off)[0]
                        if rtype == IMAGE_REL_I386_REL32:
                            enc = (site + 4 + struct.unpack('<i', struct.pack('<I', field))[0] - addend) & 0xFFFFFFFF
                        elif rtype == IMAGE_REL_I386_DIR32:
                            enc = (field - addend) & 0xFFFFFFFF
                        else:
                            continue
                        defined = [x for x in c.symbol_list if x['name'] == name and x['section'] > 0]
                        if defined:
                            continue  # object-local: the linker uses the original's encoding
                        have = match.resolve_name(name, {})
                        if have is None:
                            have = aliases.get(name)
                        if have is None:
                            need[name] = enc
                        elif have != enc:
                            need[name] = None  # a conflict: leave the function binary
                    if any(v is None for v in need.values()):
                        stat['relocation conflict'] += 1
                        continue
                    for name, enc in need.items():
                        if name in aliases and aliases[name] != enc:
                            conflicts.add(name)
                        aliases.setdefault(name, enc)
                        alias_evidence.setdefault(name, '%s %s references it from %s' % (lib, member, s['name']))
                    ok, msg = match.compare(c, s['name'], addr, xbe, dict((n, aliases[n]) for n in need))
                    if not ok:
                        stat['differs'] += 1
                        continue
                    rows.append((addr, objpath, s['name']))
                    members[objpath] = (lib, spec)
                    placed.add(addr)
                    stat['placed'] += 1
        print(lib, dict(stat))
    for n in conflicts:
        aliases.pop(n, None)
    rows = [r for r in rows if True]
    # write
    have_alias = set(l.split()[0] for l in open(ALIASES, encoding='utf-8') if l.strip() and not l.startswith('#'))
    with open(ALIASES, 'a', encoding='utf-8') as f:
        for name in sorted(aliases):
            if name in have_alias:
                continue
            f.write('%-29s 0x%08X  installed %s (M3)\n' % (name, aliases[name], alias_evidence[name]))
    lines = open(CFG, encoding='utf-8').read().rstrip('\n').split('\n')
    for addr, obj, name in sorted(rows):
        lines.append('0x%08X %s %s' % (addr, obj, name))
    open(CFG, 'w', encoding='utf-8').write('\n'.join(lines) + '\n')
    old = open(MANIFEST, encoding='utf-8').read() if os.path.exists(MANIFEST) else \
        '# XDK library members placed by config/compiled.txt (PLAN M3): OBJECT LIB MEMBER\n'
    have_obj = set(l.split()[0] for l in old.split('\n') if l and not l.startswith('#'))
    with open(MANIFEST, 'w', encoding='utf-8') as f:
        f.write(old.rstrip('\n') + '\n')
        for obj in sorted(members):
            if obj not in have_obj:
                f.write('%s %s %s\n' % (obj, members[obj][0], members[obj][1]))
    # the post-check: a function whose relocations another placement's alias
    # contradicts (an alias two members disagree on) is left binary
    import xdk_members
    xdk_members.extract()
    failed = []
    while True:
        more = []
        xdk_members.check(more)
        if not more:
            break
        failed += more
        bad = set(more)
        lines = [l for l in open(CFG, encoding='utf-8').read().rstrip('\n').split('\n')
                 if not (l.startswith('0x') and 'build/xdk/' in l and int(l.split()[0], 16) in bad)]
        open(CFG, 'w', encoding='utf-8').write('\n'.join(lines) + '\n')
    print('placed %d functions (%d dropped by the post-check), %d aliases' % (len(rows) - len(failed), len(failed), len(aliases)))


if __name__ == '__main__':
    main(sys.argv)
