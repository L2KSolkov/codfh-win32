"""defglobals.py [--apply] UNIT LO-HI [LO-HI ...]: define the scalar globals of binary data ranges
in a unit, with the image's values (PLAN M5).

Each 4-byte slot in LO-HI becomes a definition in address order: the type and name of an
existing `extern` declaration of `<prefix>_<ADDR>` (include/ and src/), else `RwReal flt_ADDR`
when the bytes read as a plausible float and `RwInt32 dword_ADDR` otherwise. Floats are written
with the shortest literal that gives the same bits. The definitions go after the unit's
includes, their match lines into its data block. Prints the definitions; --apply writes them."""
import os
import re
import struct
import subprocess
import sys

sys.path.insert(0, os.path.join(os.path.dirname(os.path.abspath(__file__)), '..'))
from xbe import Xbe  # noqa: E402

ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
args = sys.argv[1:]
apply = '--apply' in args
args = [a for a in args if a != '--apply']
unit = args[0]
src = unit if os.path.exists(unit) else os.path.join('src', 'recovered', unit + '.cpp')
runs = [tuple(int(x, 16) for x in a.split('-')) for a in args[1:]]
img = Xbe(os.path.join(ROOT, 'orig', 'Game_XboxMultiplayer.xbe'))


def f32(v):
    return struct.unpack('<f', struct.pack('<f', v))[0]


def float_lit(bits):
    v = struct.unpack('<f', struct.pack('<I', bits))[0]
    if abs(v) < 1e7:
        for k in range(0, 10):
            s = '%.*f' % (k, v)
            if struct.pack('<f', float(s)) == struct.pack('<I', bits):
                return (s if '.' in s else s + '.0') + 'f'
    for d in range(1, 10):
        s = '%.*g' % (d, v)
        if struct.pack('<f', float(s)) == struct.pack('<I', bits):
            if 'e' not in s and '.' not in s:
                s += '.0'
            return s + 'f'
    return repr(v) + 'f'


def declared(name):
    r = subprocess.run(['git', 'grep', '-h', '-E', r'extern\s+[^;(]*\b%s\b\s*;' % name, '--', 'include', 'src'],
                       cwd=ROOT, capture_output=True, text=True)
    for l in r.stdout.splitlines():
        m = re.search(r'extern\s+([^;(]*?)\s*\b%s\b\s*;' % name, l)
        if m:
            return m.group(1).strip()
    return None


defs, matches = [], []
for lo, hi in runs:
    a = lo
    while a < hi:
        bits = struct.unpack('<I', bytes(img.read(a, 4)))[0]
        name = None
        ctype = None
        for prefix in ('flt', 'dword', 'unk', 'off'):
            n = '%s_%06X' % (prefix, a)
            t = declared(n)
            if t:
                name, ctype = n, t
                break
        if name is None:
            v = struct.unpack('<f', struct.pack('<I', bits))[0]
            plausible = bits == 0 or (1e-6 < abs(v) < 1e7)
            name, ctype = ('flt_%06X' % a, 'RwReal') if plausible and bits != 0 else ('dword_%06X' % a, 'RwInt32')
        if 'RwReal' in ctype or 'float' in ctype:
            value = float_lit(bits)
            mangled = '?%s@@3MA' % name
        else:
            value = '%d' % struct.unpack('<i', struct.pack('<I', bits))[0]
            mangled = '?%s@@3HA' % name
        defs.append('%s %s = %s;' % (ctype, name, value))
        matches.append('// match: %s @ 0x%08X' % (mangled, a))
        a += 4
print('\n'.join(defs))
if apply:
    full = os.path.join(ROOT, src)
    text = open(full, encoding='utf-8').read()
    incs = list(re.finditer(r'^#include .*\n', text, re.M))
    pos = incs[-1].end() if incs else 0
    block = '\n// Its .data (PLAN M5), in the image\'s order.\n' + '\n'.join(defs) + '\n'
    text = text[:pos] + block + text[pos:]
    hdr = "// Its data (PLAN M5): literals, constants and tables where the image has them.\n"
    if hdr in text:
        text = text.replace(hdr, hdr + '\n'.join(matches) + '\n', 1)
    else:
        m = re.search(r'^// match: ', text, re.M)
        text = text[:m.start()] + hdr + '\n'.join(matches) + '\n\n' + text[m.start():]
    open(full, 'w', encoding='utf-8', newline='\n').write(text)
    subprocess.run([sys.executable, os.path.join(ROOT, 'tools', 'session', 'datablocks.py')], cwd=ROOT)
