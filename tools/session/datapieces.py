"""datapieces.py [--apply] OBJ ADDR=SYMBOL ...: place compiled data pieces (M5).

For each piece: check it with match.py's compare, give it its own placement
range in config/splits.txt (ADDR .. ADDR + size, cut out of the section's
binary range: rows are inserted in address order), and (with --apply)
add its config/compiled.txt row too, so a full build can be tried before
committing. Without --apply it only compares and prints the rows it would
add. Commit afterwards through cmf.py with `// match: SYMBOL @ ADDR` lines in
the unit (cmf adds the compiled.txt rows itself; pass -m so the splits.txt
rows go into the header commit)."""
import os
import sys

sys.path.insert(0, os.path.join(os.path.dirname(os.path.abspath(__file__)), '..'))
from coff import Coff  # noqa: E402
from match import compare, section_kind  # noqa: E402
from xbe import Xbe  # noqa: E402

ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))


def insert_row(path, row, address):
    lines = open(path, encoding='utf-8').read().splitlines(True)
    for i, line in enumerate(lines):
        if line.startswith('0x') and int(line.split()[0], 16) > address:
            lines.insert(i, row)
            break
    else:
        lines.append(row)
    open(path, 'w', encoding='utf-8', newline='\n').writelines(lines)


def add_aliases(obj, symbol, name, address, image):
    """Alias rows for the piece's relocation targets the link cannot resolve
    (not placed, not named in symbols.txt/aliases.txt): the address the
    image's data holds there is the evidence (a vtable slot points at the
    function)."""
    import struct
    from match import resolve_name
    placed = set(l.split(None, 2)[2].strip() for l in open(os.path.join(ROOT, 'config', 'compiled.txt'))
                 if l.startswith('0x'))
    aliases = os.path.join(ROOT, 'config', 'aliases.txt')
    known = set(l.split()[0] for l in open(aliases, encoding='utf-8') if l.strip() and not l.startswith('#'))
    data, relocs = obj.function_bytes(symbol)
    original = image.read(address, len(data))
    out = []
    for offset, target, rtype in relocs:
        if target in placed or target in known or resolve_name(target, {}) is not None:
            continue
        if any(s['name'] == target and s['section'] > 0 for s in obj.symbol_list):
            continue  # defined in the object itself
        value = struct.unpack_from('<I', original, offset)[0]
        out.append('%-40s 0x%08X  slot +0x%X of %s at 0x%08X in the image points there\n'
                   % (target, value, offset, name, address))
        known.add(target)
    if out:
        open(aliases, 'a', encoding='utf-8', newline='\n').writelines(out)
        print('  %d alias rows' % len(out))


def main():
    args = sys.argv[1:]
    apply = '--apply' in args
    if apply:
        args.remove('--apply')
    obj_path, pairs = args[0], args[1:]
    obj = Coff(os.path.join(ROOT, obj_path))
    image = Xbe(os.path.join(ROOT, 'orig', 'Game_XboxMultiplayer.xbe'))
    splits = os.path.join(ROOT, 'config', 'splits.txt')
    compiled = os.path.join(ROOT, 'config', 'compiled.txt')
    have = set(int(l.split()[0], 16) for l in open(splits) if l.startswith('0x'))
    for pair in pairs:
        address, name = pair.split('=', 1)
        address = int(address, 16)
        ok, msg = compare(obj, name, address, image)
        print(msg)
        if not ok:
            continue
        symbol = obj.find_function(name)
        data, _ = obj.function_bytes(symbol)
        kind = section_kind(obj.sections[symbol['section'] - 1]['name'])
        row = '0x%08X 0x%08X %-10s %s\n' % (address, address + len(data), kind, name)
        print('  split', row.strip())
        if apply:
            add_aliases(obj, symbol, name, address, image)
            if address not in have:
                insert_row(splits, row, address)
            insert_row(compiled, '0x%08X %s %s\n' % (address, obj_path.replace('\\', '/'), name), address)


if __name__ == '__main__':
    main()
