"""diffall.py SRC ADDR [N]: compile SRC, compare the function at ADDR with the
image byte for byte (relocation fields masked) and list the first N
instructions that differ (ours | image)."""
import os as _os_repo
_REPO = _os_repo.path.dirname(_os_repo.path.dirname(_os_repo.path.abspath(__file__)))  # the repository root, from this file's location
import os, re, sys
import capstone
sys.path.insert(0, _os_repo.path.join(_REPO, r'tools'))
from build_probes import ROOT, compile_unit, flags_for, load_flags
from coff import Coff
from xbe import Xbe

src, addr = sys.argv[1], int(sys.argv[2], 16)
N = int(sys.argv[3]) if len(sys.argv) > 3 else 10
S = os.path.dirname(os.path.abspath(__file__))
W = os.path.join(os.path.dirname(S), 'build', 'tooltmp')  # work files
os.makedirs(W, exist_ok=True)

text = open(src, encoding='utf-8').read()
name = re.search(r'^// match: (\S+) @ 0x0*%X$' % addr, text, re.M).group(1)
out = os.path.join(ROOT, 'build', 'diffall')
os.makedirs(out, exist_ok=True)
cx = os.path.join(out, 'd%d.cxx' % os.getpid()); ob = os.path.join(out, 'd%d.obj' % os.getpid())
open(cx, 'w', encoding='utf-8').write(text)
flags = (['/I' + os.path.join(W, 'inc')] + flags_for('src/recovered/unit_03FA10.cpp', load_flags())
         + ['/I' + os.path.join(ROOT, 'include')])
if not compile_unit(cx, ob, flags, out=[]):
    sys.exit('compile failed')
c = Coff(ob)
code, rel = c.function_bytes(c.find_function(name))
code = bytes(code)
img = bytes(Xbe(os.path.join(ROOT, 'orig', 'Game_XboxMultiplayer.xbe')).read(addr, len(code)))
mask = set()
for off, _, _ in rel:
    mask.update(range(off, off + 4))
md = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)
A = list(md.disasm(code, 0))
B = {i.address: i for i in md.disasm(img, 0)}
n = 0
for i in A:
    bad = any(code[k] != img[k] for k in range(i.address, i.address + i.size) if k not in mask and k < len(img))
    if bad:
        j = B.get(i.address)
        print('%5x  %-40s | %s' % (i.address, '%s %s' % (i.mnemonic, i.op_str), ('%s %s' % (j.mnemonic, j.op_str)) if j else '?'))
        n += 1
        if n >= N:
            break
print('diffs', n, 'len ours %#x' % len(code))
