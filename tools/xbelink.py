"""xbelink.py

The placement linker. Rebuilds the XBE from units placed at their original
addresses and compares the result with the original.

- config/splits.txt partitions every section's file-backed bytes into ranges.
- config/compiled.txt lists compiled pieces: `0xADDRESS  OBJECT  NAME`
  (NAME as match.py takes it: a symbol, or `.section+OFFSET`). Every other
  range is a binary unit: the original bytes of that range, the scaffold for
  code not yet matched.
- A compiled piece's relocations are applied against the addresses its
  targets denote (compiled pieces of the same object, IDA address suffixes,
  config/symbols.txt, config/aliases.txt, then any compiled piece); a target defined only inside its own object — a
  literal or EH table not yet compiled as data — resolves to the address the
  original encodes at that site, after checking it lands in the same kind of
  section.
- After a compiled piece, the bytes up to the next range boundary are
  generated fill (0xCC in code, 0x00 in data and after an .asm unit), never copied from the original,
  so a compiled piece shorter than the original shows up as a difference.
- The header region is copied from the original: it holds Microsoft's
  certificate and signature and imagebld's output, restored rather than
  compiled until M7.

Writes build/Game_XboxMultiplayer.xbe, checks every section digest in the
header against the rebuilt bytes, and compares the whole file. Exit status 0
means every digest verifies and the image is byte-identical."""
import hashlib
import os
import struct
import sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
from coff import Coff, IMAGE_REL_I386_DIR32, IMAGE_REL_I386_REL32  # noqa: E402
from match import original_kind, resolve_name, section_kind  # noqa: E402
from xbe import Xbe  # noqa: E402

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
ORIGINAL = os.path.join(ROOT, 'orig', 'Game_XboxMultiplayer.xbe')
OUTPUT = os.path.join(ROOT, 'build', 'Game_XboxMultiplayer.xbe')


def rows(name, columns):
    path = os.path.join(ROOT, 'config', name)
    if not os.path.exists(path):
        return []
    out = []
    for line in open(path):
        line = line.split('#', 1)[0].strip() if not line.startswith('0x') else line.strip()
        if line and not line.startswith('#'):
            out.append(line.split(None, columns - 1))
    return out


class LinkError(Exception):
    pass


def load_compiled(image):
    pieces = {}
    objects = {}
    for address, obj_path, name in rows('compiled.txt', 3):
        address = int(address, 16)
        path = os.path.join(ROOT, obj_path)
        if path not in objects:
            objects[path] = Coff(path)
        obj = objects[path]
        symbol = obj.find_function(name.strip())
        if symbol is None:
            raise LinkError('%s: no symbol %s' % (obj_path, name))
        code, relocs = obj.function_bytes(symbol)
        pieces[address] = {'obj': obj, 'path': obj_path, 'symbol': symbol,
                           'code': bytearray(code), 'relocs': relocs}
    # Addresses of compiled symbols, so compiled pieces can reference each other.
    placed = {}
    for address, piece in pieces.items():
        placed[(piece['path'], piece['symbol']['name'])] = address
    # Like a linker, an external name another object's placed piece defines
    # resolves to that piece (base-class methods compiled in their own unit).
    # Static symbols (storage class 3, such as the compiler's `_$E` exit
    # thunks) are local to their object, so two objects may each have one.
    for address, piece in pieces.items():
        name = piece['symbol']['name']
        if piece['symbol']['class'] in (3, 6):  # static, or an assembler member's local label
            continue
        if placed.setdefault((None, name), address) != address:
            raise LinkError('%s is placed twice' % name)
    for address, piece in pieces.items():
        apply_relocations(address, piece, placed, image)
    return pieces


_masm = {}


def is_masm(path):
    """Whether a placed object was assembled from a MASM unit (src/...asm)."""
    if path not in _masm:
        _masm[path] = path.lower().endswith('.obj') and os.path.exists(
            os.path.join(ROOT, 'src', os.path.relpath(
                os.path.splitext(os.path.join(ROOT, path))[0],
                os.path.join(ROOT, 'build', 'src')) + '.asm'))
    return _masm[path]


def object_statics(obj):
    """Names of the static symbols an object defines (computed once per object)."""
    statics = getattr(obj, '_statics', None)
    if statics is None:
        statics = obj._statics = {s['name'] for s in obj.symbol_list if s['section'] > 0 and s['class'] == 3}
    return statics


def apply_relocations(address, piece, placed, image):
    code = piece['code']
    original = image.read(address, len(code))
    for offset, target, rtype in piece['relocs']:
        if rtype == 0xB:
            # SECREL (an XDK member's thread-local variable: its offset in
            # .tls, which the original's layout fixes) keeps the original's
            # field until the data is placed (M5)
            code[offset:offset + 4] = original[offset:offset + 4]
            continue
        if rtype not in (IMAGE_REL_I386_DIR32, IMAGE_REL_I386_REL32):
            raise LinkError('0x%08X: unsupported relocation type 0x%X' % (address, rtype))
        addend = struct.unpack_from('<i', code, offset)[0]
        site = address + offset
        resolved = placed.get((piece['path'], target))
        # A library member's own static (XGraphics' per-object operator new and
        # delete) is local to it: /OPT:ICF may have folded it anywhere, so the
        # global name's alias does not apply; resolve it as object-local below.
        local_static = piece['path'].replace('\\', '/').startswith('build/xdk/') and \
            target in object_statics(piece['obj'])
        if resolved is None and not local_static:
            resolved = resolve_name(target, {})
        if resolved is None and not local_static:
            resolved = placed.get((None, target))
        if resolved is None:
            defined = [s for s in piece['obj'].symbol_list
                       if s['name'] == target and s['section'] > 0]
            if not defined:
                raise LinkError('0x%08X+0x%X: cannot resolve %s' % (address, offset, target))
            field = struct.unpack_from('<I', original, offset)[0]
            if rtype == IMAGE_REL_I386_REL32:
                encoded = site + 4 + struct.unpack('<i', struct.pack('<I', field))[0]
            else:
                encoded = field
            encoded = (encoded - addend) & 0xFFFFFFFF
            kind = section_kind(piece['obj'].sections[defined[0]['section'] - 1]['name'])
            if kind is None or kind != original_kind(image, encoded):
                raise LinkError('0x%08X+0x%X: object-local %s does not land in %s data'
                                % (address, offset, target, kind))
            resolved = encoded
        if rtype == IMAGE_REL_I386_DIR32:
            value = (resolved + addend) & 0xFFFFFFFF
        else:
            value = (resolved + addend - (site + 4)) & 0xFFFFFFFF
        struct.pack_into('<I', code, offset, value)


def main():
    image = Xbe(ORIGINAL)
    original = image.data
    pieces = load_compiled(image)
    # sections whose generated fill is int3 (the image's data sections pad with zeros, however
    # many of their pieces have ranges of their own)
    data_sections = {'.rdata', '.data', '.data1', 'DOLBY', 'BINKDATA', 'XON_RD',
                     '$$XTIMAGE', '$$XSIMAGE', '.XTLID'}
    code_sections = set(row[2].strip().split()[0] for row in rows('splits.txt', 4)
                        if row[3].strip() != '-') - data_sections
    boundaries = {}
    for start, end, section, _name in rows('splits.txt', 4):
        boundaries.setdefault(section, []).append((int(start, 16), int(end, 16)))

    out = bytearray(len(original))
    header_size = image.field('size_of_headers')
    out[:header_size] = original[:header_size]
    compiled_bytes = 0
    for section in image.sections:
        lo, hi = section['va'], section['va'] + section['rsize']
        points = set([lo, hi])
        for start, end in boundaries.get(section['name'], []):
            if lo <= start < hi:
                points.add(start)
                points.add(end)
        for address in pieces:
            if lo <= address < hi:
                points.add(address)
        points = sorted(points)
        fill = 0xCC if section['name'] in code_sections else 0x00
        raw = bytearray()
        for start, end in zip(points, points[1:]):
            piece = pieces.get(start)
            if piece is None:
                raw += original[section['raw'] + start - lo:section['raw'] + end - lo]
                continue
            code = piece['code']
            if end == hi and len(code) > end - start and not any(code[end - start:]):
                # The section's file-backed bytes stop before the piece's
                # trailing zeros (a MASM unit's last `ret 4` ends in 00 00);
                # the loader supplies them from the virtual size.
                code = code[:end - start]
            if len(code) > end - start:
                raise LinkError('compiled %s (%d bytes) overruns 0x%08X-0x%08X'
                                % (piece['symbol']['name'], len(code), start, end))
            # MASM units (Bink's hand-written assembly) are padded with zeros
            # in their sections, not with the compiler's 0xCC.
            pad = 0x00 if is_masm(piece['path']) else fill
            raw += code + bytes([pad]) * (end - start - len(code))
            compiled_bytes += len(code)
        out[section['raw']:section['raw'] + section['rsize']] = raw

    digest_failures = 0
    table = image.field('section_headers') - image.base
    for i, section in enumerate(image.sections):
        stored = original[table + i * 56 + 0x24:table + i * 56 + 0x38]
        body = bytes(out[section['raw']:section['raw'] + section['rsize']])
        computed = hashlib.sha1(struct.pack('<I', section['rsize']) + body).digest()
        if computed != stored:
            digest_failures += 1
            print('digest mismatch: %s' % section['name'])

    if not os.path.isdir(os.path.dirname(OUTPUT)):
        os.makedirs(os.path.dirname(OUTPUT))
    open(OUTPUT, 'wb').write(out)
    same = bytes(out) == original
    print('compiled pieces %d (%d bytes); section digests %s; image %s'
          % (len(pieces), compiled_bytes,
             'all match' if not digest_failures else '%d differ' % digest_failures,
             'BYTE-IDENTICAL' if same else 'DIFFERS'))
    if not same:
        for i in range(len(original)):
            if out[i] != original[i]:
                where = next((s for s in image.sections
                              if s['raw'] <= i < s['raw'] + s['rsize']), None)
                va = where['va'] + i - where['raw'] if where else None
                print('first difference at file offset 0x%X%s' % (
                    i, ' (%s 0x%08X)' % (where['name'], va) if where else ''))
                break
    print('sha1 %s' % hashlib.sha1(out).hexdigest())
    return 0 if same and not digest_failures else 1


if __name__ == '__main__':
    try:
        sys.exit(main())
    except LinkError as error:
        print('link error: %s' % error)
        sys.exit(2)
