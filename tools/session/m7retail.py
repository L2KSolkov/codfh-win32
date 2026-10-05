"""m7retail.py [--no-env] [--no-import-pad] [XBE]: the M7 rebuild's retail post-processing and the final comparison (PLAN M7,
Verification: the SHA-1 of the rebuilt, retail-post-processed XBE equals the original's).

The input is imagebld's output from the M7 link (build/m7/game.xbe, tools/session/m7xbe.py).
What the post-processing takes from the original, as Microsoft's or the build machine's, never
the compiler's:

- the retail header: the certificate, the RSA signature, the header layout Microsoft's signing
  writes (header size 0x1008), the retail XOR encoding of the entry point and kernel thunk
  address (the plain addresses must equal the rebuild's), and the build-environment fields
  (timestamps, debug path strings);
- inside .rdata, the link's build-environment values: the debug directory's timestamp and the
  CodeView record's GUID, age and PDB path (the owner's 2026-10-04 decision).

--no-env (or M7RETAILENV=0) leaves the build-environment values out: the .rdata ones stay the
rebuild's, so the comparison shows what the toolchain alone produces.

- the kernel import table's seven filler slots: the image has seven zero dwords after the
  table's terminator, which the M7 link holds with seven unused kernel imports (m7probe.py
  M7KTHUNKS_EXTRA); what made the original's zeros is not known (docs/questions.md). They are
  zeroed only when the slots are exactly those imports (the owner's 2026-10-04 decision, an
  unexplained difference). --no-import-pad (or M7RETAILPAD=0) leaves them.

Everything else is the rebuild's: every section's bytes at the original's file offsets. Each
section's SHA-1 digest in the original header is checked against the rebuild's bytes, and the
header fields the link and imagebld set are checked against the rebuild's header. Writes
build/m7/game_retail.xbe and prints the result; exit status 1 when the images differ."""
import hashlib
import os
import struct
import sys

sys.path.insert(0, os.path.join(os.path.dirname(os.path.abspath(__file__)), '..'))
from xbe import Xbe  # noqa: E402

ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
ORIG = os.path.join(ROOT, 'orig', 'Game_XboxMultiplayer.xbe')
args = [a for a in sys.argv[1:] if not a.startswith('--')]
ENV = '--no-env' not in sys.argv[1:] and os.environ.get('M7RETAILENV', '1') != '0'
# (--no-import-pad / M7RETAILPAD=0: the kernel import table's seven filler slots left as built)
PAD = '--no-import-pad' not in sys.argv[1:] and os.environ.get('M7RETAILPAD', '1') != '0'
# the seven unused kernel imports the M7 link holds the image's zero slots after the thunk table
# with (m7probe.py M7KTHUNKS_EXTRA, in that order): NtWriteFileGather, NtUserIoApcDispatcher,
# NtSignalAndWaitForSingleObjectEx, NtSetTimerEx, NtSetIoCompletion, NtRemoveIoCompletion,
# NtReadFileScatter
PAD_ORDINALS = [0x800000ED, 0x800000E8, 0x800000E6, 0x800000E5, 0x800000E3, 0x800000DF, 0x800000DC]
src = args[0] if args else os.path.join(ROOT, 'build', 'm7', 'game.xbe')
dst = os.path.join(os.path.dirname(src), 'game_retail.xbe')

# XOR keys of the entry point and kernel thunk address: debug (imagebld) and retail
ENTRY_DEBUG, ENTRY_RETAIL = 0x94859D4B, 0xA8FC57AB
THUNK_DEBUG, THUNK_RETAIL = 0xEFB1F152, 0x5B6D40B6

o = open(ORIG, 'rb').read()
d = open(src, 'rb').read()
img_o, img_d = Xbe(ORIG), Xbe(src)
problems = []


def u32(b, off):
    return struct.unpack_from('<I', b, off)[0]


base = u32(o, 0x104)
# -- header fields the link and imagebld set, which must agree with the rebuild's
for off, name, key in ((0x128, 'entry point', (ENTRY_RETAIL, ENTRY_DEBUG)),
                       (0x158, 'kernel thunk address', (THUNK_RETAIL, THUNK_DEBUG))):
    plain_o, plain_d = u32(o, off) ^ key[0], u32(d, off) ^ key[1]
    if plain_o != plain_d:
        problems.append('%s: original 0x%08X, rebuild 0x%08X' % (name, plain_o, plain_d))
for off, name in ((0x10C, 'image size'), (0x11C, 'section count'), (0x124, 'init flags'), (0x12C, 'TLS'),
                  (0x130, 'stack commit'), (0x134, 'heap reserve'), (0x138, 'heap commit'), (0x13C, 'PE base'),
                  (0x15C, 'non-kernel imports'), (0x160, 'library count')):
    if u32(o, off) != u32(d, off):
        problems.append('%s: original 0x%X, rebuild 0x%X' % (name, u32(o, off), u32(d, off)))
# the library version table
no, ao = struct.unpack_from('<II', o, 0x160)
nd, ad = struct.unpack_from('<II', d, 0x160)
if o[ao - base:ao - base + 16 * no] != d[ad - base:ad - base + 16 * nd]:
    problems.append('library version table differs')

# -- the build-environment values inside .rdata, the original's
patched = {}
padded = []
rsds_o = o.find(b'RSDS')
rsds_d = d.find(b'RSDS')
if rsds_o < 0 or rsds_d < 0:
    problems.append('no CodeView record')
else:
    end_o = o.index(b'\0', rsds_o + 24) + 1
    rec_o = o[rsds_o:end_o]
    if d.index(b'\0', rsds_d + 24) + 1 - rsds_d != len(rec_o):
        problems.append('CodeView record length differs')

# -- the image: the original's header, the rebuild's section bytes at the original's offsets
nsec = u32(o, 0x11C)
sh_o = u32(o, 0x120) - base
sh_d = u32(d, 0x120) - base
out = bytearray(o)
secs_d = {}
for k in range(u32(d, 0x11C)):
    fl, va, vs, ra, rs = struct.unpack_from('<IIIII', d, sh_d + k * 56)
    secs_d.setdefault(va, (ra, rs, vs, fl))
for k in range(nsec):
    off = sh_o + k * 56
    fl, va, vs, ra, rs = struct.unpack_from('<IIIII', o, off)
    nm_addr = u32(o, off + 20)
    name = o[nm_addr - base:o.index(b'\0', nm_addr - base)].decode('latin-1')
    if va not in secs_d:
        problems.append('%s: no section at 0x%08X in the rebuild' % (name, va))
        continue
    ra_d, rs_d, vs_d, fl_d = secs_d[va]
    if (rs_d, vs_d) != (rs, vs):
        problems.append('%s: sizes raw 0x%X/0x%X virtual 0x%X/0x%X' % (name, rs, rs_d, vs, vs_d))
    data = bytearray(d[ra_d:ra_d + rs])
    if ENV and rsds_o >= 0 and rsds_d >= 0 and ra_d <= rsds_d < ra_d + rs_d:
        # the CodeView record: the original's GUID, age and PDB path
        p = rsds_d - ra_d
        data[p:p + len(rec_o)] = rec_o
        patched[name] = patched.get(name, 0) + 1
        # the debug directory's timestamp: the original's (the directory names the record)
        for q in range(0, len(data) - 28, 4):
            ch, ts, mj, mn, ty, sz, av, pr = struct.unpack_from('<IIHHIIII', data, q)
            if ty == 2 and sz == len(rec_o) and ch == 0:
                oq = ra + q
                struct.pack_into('<I', data, q, u32(o, oq))
                struct.pack_into('<I', data, q + 4, u32(o, oq + 4))
                patched[name] += 1
                break
    # the kernel import table's filler slots, zeros as in the image (the owner's 2026-10-04
    # decision: what made the original's zeros is not known, docs/questions.md); only when the
    # slots before the table's terminator are exactly the fillers
    thunk = u32(d, 0x158) ^ THUNK_DEBUG
    if PAD and va <= thunk < va + rs:
        q = thunk - va
        while q + 4 <= rs and u32(data, q):
            q += 4
        k0 = q - 4 * len(PAD_ORDINALS)
        if k0 >= thunk - va and [u32(data, k0 + 4 * i) for i in range(len(PAD_ORDINALS))] == PAD_ORDINALS:
            data[k0:q] = bytes(q - k0)
            padded.append('%s 0x%08X' % (name, va + k0))
        else:
            problems.append('%s: the kernel import table does not end with the filler imports' % name)
    digest = hashlib.sha1(struct.pack('<I', rs) + bytes(data)).digest()
    if digest != o[off + 36:off + 56]:
        problems.append('%s: section digest differs (first byte at 0x%08X)' % (
            name, va + next((i for i in range(rs) if data[i] != o[ra + i]), rs)))
    out[ra:ra + rs] = data

open(dst, 'wb').write(bytes(out))
print('kernel import filler slots:', ('zeroed at ' + ', '.join(padded)) if PAD else 'left as built (--no-import-pad)')
h_o, h_d = hashlib.sha1(o).hexdigest(), hashlib.sha1(bytes(out)).hexdigest()
for p in problems:
    print('  ' + p)
print('build-environment values:', ('patched ' + ', '.join('%s %d' % kv for kv in patched.items())) if ENV
      else 'left as built (--no-env)')
print('original %s\nrebuild  %s' % (h_o, h_d))
print('== IDENTICAL' if h_o == h_d and not problems else '== DIFFERS (%d problems)' % len(problems))
sys.exit(0 if h_o == h_d and not problems else 1)
