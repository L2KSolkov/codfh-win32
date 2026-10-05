"""slotmap.py SRC ADDR: compile SRC, align our function's instructions with
the image's (same instruction sequence assumed, offsets aside) and print each
of our frame offsets with the image offset(s) it pairs with, plus our /FA
name for it. Stops at the first opcode mismatch and reports it."""
import os as _os_repo
_REPO = _os_repo.path.dirname(_os_repo.path.dirname(_os_repo.path.abspath(__file__)))  # the repository root, from this file's location
import os, re, sys, subprocess
import capstone
sys.path.insert(0, _os_repo.path.join(_REPO, r'tools'))
from build_probes import ROOT, compile_unit, flags_for, load_flags
from coff import Coff
from xbe import Xbe

src, addr = sys.argv[1], int(sys.argv[2], 16)
S = os.path.dirname(os.path.abspath(__file__))
W = os.path.join(os.path.dirname(S), 'build', 'tooltmp')  # work files
os.makedirs(W, exist_ok=True)

text = open(src, encoding='utf-8').read()
name = re.search(r'^// match: (\S+) @ 0x0*%X$' % addr, text, re.M).group(1)
out = os.path.join(ROOT, 'build', 'slotmap')
os.makedirs(out, exist_ok=True)
asm = os.path.join(out, 'f%d.asm' % os.getpid())
flags = (['/I' + os.path.join(W, 'inc')] + flags_for('src/recovered/unit_03FA10.cpp', load_flags())
         + ['/I' + os.path.join(ROOT, 'include'), '/FA', '/Fa' + asm])
cx = os.path.join(out, 'f%d.cxx' % os.getpid()); ob = os.path.join(out, 'f%d.obj' % os.getpid())
open(cx, 'w', encoding='utf-8').write(text)
if not compile_unit(cx, ob, flags, out=[]):
    sys.exit('compile failed')
c = Coff(ob)
code, _ = c.function_bytes(c.find_function(name))
code = bytes(code)
img = bytes(Xbe(os.path.join(ROOT, 'orig', 'Game_XboxMultiplayer.xbe')).read(addr, len(code) + 0x400))
md = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)
A = list(md.disasm(code, 0))
B = list(md.disasm(img, 0))
# names from the listing
names = {}
lines = open(asm, errors='replace').read().split('\n')
for i, l in enumerate(lines):
    if l.startswith(name + '\tPROC') or l.startswith(name + ' PROC'):
        j = i - 1
        while j >= 0 and re.search(r'= -?\d+', lines[j]):
            mm = re.match(r'(\S+)\s*=\s*(-?\d+)', lines[j])
            if mm and int(mm.group(2)) < 0:
                names.setdefault(-int(mm.group(2)), []).append(mm.group(1))
            j -= 1
        break
pairs = {}
rx = re.compile(r'\[ebp - (0x[0-9a-f]+|\d+)\]')
for k, (x, y) in enumerate(zip(A, B)):
    if x.mnemonic != y.mnemonic:
        print('opcode mismatch at ours+0x%x: %s %s | image+0x%x: %s %s' % (x.address, x.mnemonic, x.op_str, y.address, y.mnemonic, y.op_str))
        break
    ox = [int(v, 0) for v in rx.findall(x.op_str)]
    oy = [int(v, 0) for v in rx.findall(y.op_str)]
    for p, q in zip(ox, oy):
        pairs.setdefault(p, {}).setdefault(q, 0)
        pairs[p][q] += 1
fr = re.search(rb'\x81\xec(....)', code[:48], re.S)
print('ours frame', hex(int.from_bytes(fr.group(1), 'little')) if fr else '?')
for p in sorted(pairs):
    tag = '' if len(pairs[p]) == 1 and p in pairs[p] else ' *'
    print('%5x -> %-20s %s%s' % (p, ' '.join('%x' % q for q in sorted(pairs[p])), ','.join(names.get(p, [])), tag))
