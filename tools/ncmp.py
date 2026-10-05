"""ncmp.py: normalised instruction comparison of an object's function against
the image. score(objpath, sym, addr) -> number of differing instructions
after masking relocated operands, absolute addresses and jump targets.
As a script: ncmp.py OBJ SYM ADDR [-v]."""
import os as _os_repo
_REPO = _os_repo.path.dirname(_os_repo.path.dirname(_os_repo.path.abspath(__file__)))  # the repository root, from this file's location
import difflib
import re
import sys

import capstone

sys.path.insert(0, _os_repo.path.join(_REPO, r'tools'))
from coff import Coff  # noqa: E402
from xbe import Xbe  # noqa: E402

_x = None
_md = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)
_sizes = None
ADDR = r'0x[2-5][0-9a-f]{5}'


def _img():
    global _x, _sizes
    if _x is None:
        _x = Xbe(_os_repo.path.join(_REPO, r'orig\Game_XboxMultiplayer.xbe'))
        _sizes = {}
        for l in open(_os_repo.path.join(_REPO, r'config\symbols.txt')):
            p = l.split()
            if len(p) >= 5 and p[0].startswith('0x'):
                _sizes[int(p[0], 16)] = int(p[2], 16)
    return _x


def _canon(s):
    """Absolute addresses: inside brackets dropped, elsewhere R."""
    s = re.sub(r'\[' + ADDR + r'\]', '[R]', s)
    s = re.sub(r' \+ ' + ADDR + r'\]', ']', s)
    s = re.sub(r'\b' + ADDR + r'\b', 'R', s)
    return s


def _norm(code, base, relocs, ours):
    out = []
    for i in _md.disasm(code, base):
        s = '%s %s' % (i.mnemonic, i.op_str)
        if i.mnemonic.startswith('j') or i.mnemonic == 'call':
            out.append(i.mnemonic + ' T')
            continue
        if ours and any(i.address <= base + r < i.address + i.size for r in relocs):
            # a relocated displacement of 0 is not printed; a relocated
            # absolute operand prints as 0
            s = re.sub(r'\[(0x[0-9a-f]+|\d+)\]', '[R]', s)
            s = re.sub(r'(\[(?!esp|ebp)[^\]]*) \+ (0x[0-9a-f]+|\d+)\]', r'\1]', s)
            if '[' not in s:
                s = re.sub(r', 0$', ', R', s)
            s = re.sub(r'^push 0$', 'push R', s)
        out.append(_canon(s))
    return out


def listings(obj, sym, addr):
    x = _img()
    c = Coff(obj)
    s = [v for v in c.symbols.values() if v['name'] == sym and v.get('section', 0) > 0]
    if not s:
        return None, None
    code, rels = c.function_bytes(s[0])
    code = bytes(code)
    ours = _norm(code, 0, [o for o, _, _ in rels], True)
    size = _sizes.get(addr, len(code))
    img = x.read(addr, size)
    theirs = _norm(img, addr, [], False)
    # VC7.0 objects (RenderWare Audio, RtFS) carry their nop alignment
    # padding inside the function; it is not code
    while ours and ours[-1].strip() == 'nop':
        ours.pop()
    while theirs and theirs[-1].strip() == 'nop':
        theirs.pop()
    return ours, theirs


def score(obj, sym, addr):
    ours, theirs = listings(obj, sym, addr)
    if ours is None:
        return None
    sm = difflib.SequenceMatcher(None, ours, theirs, autojunk=False)
    n = 0
    for tag, i1, i2, j1, j2 in sm.get_opcodes():
        if tag != 'equal':
            n += max(i2 - i1, j2 - j1)
    return n


if __name__ == '__main__':
    obj, sym, addr = sys.argv[1], sys.argv[2], int(sys.argv[3], 16)
    ours, theirs = listings(obj, sym, addr)
    if ours is None:
        print('NOT EMITTED')
        sys.exit(1)
    print(score(obj, sym, addr))
    if '-v' in sys.argv:
        for l in difflib.unified_diff(ours, theirs, 'ours', 'image', lineterm='', n=1):
            print(l)
