"""rwd.py OBJ SYMBOL ADDR: side-by-side diff of an object function against
the image function at ADDR (relocation operands shown as symbol names on our
side, addresses/names on the image side)."""
import os as _os_repo
_REPO = _os_repo.path.dirname(_os_repo.path.dirname(_os_repo.path.abspath(__file__)))  # the repository root, from this file's location
import difflib
import re
import sys

import capstone

sys.path.insert(0, _os_repo.path.join(_REPO, r'tools'))
from coff import Coff
from xbe import Xbe

sym = {}
size = {}
for l in open(_os_repo.path.join(_REPO, r'config\symbols.txt')):
    if l.startswith('0x'):
        p = l.split()
        sym[int(p[0], 16)] = p[-1]
        size[int(p[0], 16)] = int(p[2], 16)
obj, name, addr = sys.argv[1], sys.argv[2], int(sys.argv[3], 16)
c = Coff(obj)
s = [x for x in c.symbols.values() if x['name'] == name and x.get('section', 0) > 0][0]
code, rels = c.function_bytes(s)
code = bytes(code)
x = Xbe(_os_repo.path.join(_REPO, r'orig\Game_XboxMultiplayer.xbe'))
b = x.read(addr, size[addr])
md = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)
relat = {}
for off, si, _ in rels:
    relat[off] = si if isinstance(si, str) else '?'


def ours():
    out = []
    for i in md.disasm(code, 0):
        t = '%s %s' % (i.mnemonic, i.op_str)
        for off in range(i.address, i.address + i.size):
            if off in relat:
                t += '  ; ' + relat[off]
        t = re.sub(r'0x[0-9a-f]+(?=\s*$|\s*;)', '', t) if ';' in t else t
        out.append(t)
    return out


def image():
    out = []
    for i in md.disasm(b, 0):
        t = '%s %s' % (i.mnemonic, i.op_str)
        if i.mnemonic == 'call' and i.op_str.startswith('0x'):
            tgt = (int(i.op_str, 16) + addr) & 0xFFFFFFFF
            t = 'call   ; ' + sym.get(tgt, hex(tgt))
        t = re.sub(r'0x([0-9a-f]{5,6})\b', lambda m: sym.get(int(m.group(1), 16), m.group(0)), t)
        out.append(t)
    return out


A, B = ours(), image()
for l in difflib.unified_diff(A, B, 'ours', 'image', n=2, lineterm=''):
    print(l)
