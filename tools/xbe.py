"""Read-only access to the original XBE: header fields, sections, and bytes by
virtual address."""
import struct


class Xbe(object):
    def __init__(self, path):
        self.data = open(path, 'rb').read()
        d = self.data
        if d[:4] != b'XBEH':
            raise ValueError('%s is not an XBE' % path)
        self.base = struct.unpack_from('<I', d, 0x104)[0]
        count, table = struct.unpack_from('<II', d, 0x11C)
        self.sections = []
        for i in range(count):
            fields = struct.unpack_from('<IIIIII', d, table - self.base + i * 56)
            flags, va, vsize, raw, rsize, name_addr = fields
            self.sections.append({
                'name': self.string(name_addr), 'flags': flags, 'va': va,
                'vsize': vsize, 'raw': raw, 'rsize': rsize,
            })

    def string(self, va):
        offset = va - self.base
        end = self.data.index(b'\0', offset)
        return self.data[offset:end].decode('latin1')

    def section_at(self, va):
        for section in self.sections:
            if section['va'] <= va < section['va'] + section['vsize']:
                return section
        return None

    HEADER_FIELDS = [
        (0x104, 'base_address'), (0x108, 'size_of_headers'), (0x10C, 'size_of_image'),
        (0x110, 'size_of_image_header'), (0x114, 'timestamp'), (0x118, 'certificate'),
        (0x11C, 'section_count'), (0x120, 'section_headers'), (0x124, 'init_flags'),
        (0x128, 'entry_point_xor'), (0x12C, 'tls'), (0x130, 'stack_commit'),
        (0x134, 'heap_reserve'), (0x138, 'heap_commit'), (0x13C, 'pe_base'),
        (0x140, 'pe_size_of_image'), (0x144, 'pe_checksum'), (0x148, 'pe_timestamp'),
        (0x14C, 'debug_path'), (0x150, 'debug_file'), (0x154, 'debug_unicode_file'),
        (0x158, 'kernel_thunk_xor'), (0x15C, 'nonkernel_imports'),
        (0x160, 'library_version_count'), (0x164, 'library_versions'),
        (0x168, 'kernel_library_version'), (0x16C, 'xapi_library_version'),
        (0x170, 'logo_bitmap'), (0x174, 'logo_bitmap_size'),
    ]

    def header(self):
        out = []
        for offset, name in self.HEADER_FIELDS:
            out.append((name, struct.unpack_from('<I', self.data, offset)[0]))
        return out

    def field(self, name):
        return dict(self.header())[name]

    def certificate(self):
        c = self.field('certificate') - self.base
        d = self.data
        u = lambda o: struct.unpack_from('<I', d, c + o)[0]
        return [
            ('size', u(0x0)), ('timestamp', u(0x4)), ('title_id', u(0x8)),
            ('title_name', d[c + 0xC:c + 0x5C].decode('utf-16-le').rstrip('\0')),
            ('allowed_media', u(0x9C)), ('game_region', u(0xA0)), ('game_ratings', u(0xA4)),
            ('disk_number', u(0xA8)), ('version', u(0xAC)),
            ('lan_key', d[c + 0xB0:c + 0xC0].hex()), ('signature_key', d[c + 0xC0:c + 0xD0].hex()),
        ]

    def library_versions(self):
        out = []
        start = self.field('library_versions') - self.base
        for i in range(self.field('library_version_count')):
            name, major, minor, build, flags = struct.unpack_from('<8sHHHH', self.data, start + i * 16)
            out.append((name.rstrip(b'\0').decode('latin1'), major, minor, build, flags))
        return out

    def read(self, va, size):
        """Bytes at [va, va+size). Virtual-only tails (BSS) read as zero."""
        section = self.section_at(va)
        if section is None:
            raise ValueError('0x%08X is not inside any section' % va)
        delta = va - section['va']
        have = max(0, min(size, section['rsize'] - delta))
        out = bytes(self.data[section['raw'] + delta:section['raw'] + delta + have])
        return out + bytes(size - have)
