"""sdiff.py SRC ADDR [N]: compile SRC and align the function at ADDR with the
image's by instruction shape (frame offsets, call targets and addresses
blanked; difflib), then print the first N differing blocks (ours | image)
and the count of differing instructions."""
import os as _os_repo
_REPO = _os_repo.path.dirname(_os_repo.path.dirname(_os_repo.path.abspath(__file__)))  # the repository root, from this file's location
import difflib, os, re, sys
import capstone
sys.path.insert(0, _os_repo.path.join(_REPO, r'tools'))
from build_probes import ROOT, compile_unit, flags_for, load_flags
from coff import Coff
from xbe import Xbe

src, addr = sys.argv[1], int(sys.argv[2], 16)
N = int(sys.argv[3]) if len(sys.argv) > 3 else 20
S = os.path.dirname(os.path.abspath(__file__))
W = os.path.join(os.path.dirname(S), 'build', 'tooltmp')  # work files
os.makedirs(W, exist_ok=True)

text = open(src, encoding='utf-8').read()
name = re.search(r'^// match: (\S+) @ 0x0*%X$' % addr, text, re.M).group(1)
size = None
for l in open(os.path.join(ROOT, 'config', 'symbols.txt')):
    if l.startswith('0x') and int(l.split()[0], 16) == addr:
        size = int(l.split()[2], 16)
        break
out = os.path.join(ROOT, 'build', 'diffall')
os.makedirs(out, exist_ok=True)
cx = os.path.join(out, 's%d.cxx' % os.getpid()); ob = os.path.join(out, 's%d.obj' % os.getpid())
open(cx, 'w', encoding='utf-8').write(text)
flags = (['/I' + os.path.join(W, 'inc')] + flags_for('src/recovered/unit_03FA10.cpp', load_flags())
         + ['/I' + os.path.join(ROOT, 'include')])
if not compile_unit(cx, ob, flags, out=[]):
    sys.exit('compile failed')
c = Coff(ob)
code, rel = c.function_bytes(c.find_function(name))
code = bytes(code)
img = bytes(Xbe(os.path.join(ROOT, 'orig', 'Game_XboxMultiplayer.xbe')).read(addr, size or len(code)))
md = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)


def norm(i):
    s = '%s %s' % (i.mnemonic, i.op_str)
    s = re.sub(r'\[ebp - 0x[0-9a-f]+\]', '[ebp-X]', s)
    if i.mnemonic in ('call', 'jmp') or i.mnemonic.startswith('j'):
        s = i.mnemonic
    s = re.sub(r'0x[0-9a-f]{4,}', 'A', s)
    return s


A = list(md.disasm(code, 0))
B = list(md.disasm(img, 0))
if os.environ.get('DUMP'):
    lo, hi = [int(x, 16) for x in os.environ['DUMP'].split(',')]
    for i in A:
        if lo <= i.address < hi:
            print('%5x  %s %s' % (i.address, i.mnemonic, i.op_str))
a = [norm(i) for i in A]
b = [norm(i) for i in B]
sm = difflib.SequenceMatcher(None, a, b, autojunk=False)
n = 0
shown = 0
for tag, i1, i2, j1, j2 in sm.get_opcodes():
    if tag == 'equal':
        continue
    n += max(i2 - i1, j2 - j1)
    if shown < N:
        shown += 1
        print('-- %s ours %x..%x image %x..%x' % (tag, A[i1].address if i1 < len(A) else len(code),
                                                   A[i2 - 1].address if i2 > i1 else 0,
                                                   B[j1].address if j1 < len(B) else len(img),
                                                   B[j2 - 1].address if j2 > j1 else 0))
        for k in range(max(i2 - i1, j2 - j1)):
            x = A[i1 + k] if i1 + k < i2 else None
            y = B[j1 + k] if j1 + k < j2 else None
            print('   %-44s | %s' % (('%s %s' % (x.mnemonic, x.op_str)) if x else '',
                                     ('%s %s' % (y.mnemonic, y.op_str)) if y else ''))
print('shape diffs', n, 'len ours %#x image %#x' % (len(code), len(img)))
