"""Show DMorph instruction differences without stack offsets or jump tables.

Run from the repository root with an optional callback object path.
This masks call/branch targets and absolute addresses as well as stack offsets.
It is a diagnostic only: use tools/match.py to establish byte identity.
"""
import difflib
import re
import sys

import capstone

sys.path.insert(0, 'tools')
from coff import Coff
from xbe import Xbe

path = sys.argv[1] if len(sys.argv) > 1 else 'build/tooltmp/dmorph_trace_baseline.obj'
obj = Coff(path)
code, _ = obj.function_bytes(obj.find_function('_XboxDmorphAtomicInstanceCallback'))
# Eight five-entry switch tables immediately follow the final RET.
assert code[-161] == 0xc3, 'unexpected callback/table boundary'
code = code[:-160]
image = Xbe('orig/Game_XboxMultiplayer.xbe')
original = image.read(0x2f28d0, 0x15cc)
disasm = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)


def normalize(insn):
    text = insn.mnemonic + ' ' + insn.op_str
    text = re.sub(r'^(call|jmp|j\w+) .*', r'\1 X', text)
    text = re.sub(r'\[esp(?: \+ 0x[0-9a-f]+| \+ [0-9]+)?\]', '[esp+S]', text)
    text = re.sub(r'0x[0-9a-f]{5,}', 'A', text)
    return re.sub(r'\[0\]', '[A]', text)


old = [(i.address, normalize(i)) for i in disasm.disasm(original, 0x2f28d0)]
new = [(i.address, normalize(i)) for i in disasm.disasm(bytes(code), 0)]
matcher = difflib.SequenceMatcher(None, [s for _, s in old], [s for _, s in new], autojunk=False)
print('Callback code bytes:', len(code), '(original:', len(original), ')')
score = 0
for tag, a, b, c, d in matcher.get_opcodes():
    if tag == 'equal':
        continue
    score += b - a + d - c
    print('==', tag)
    for addr, text in old[a:b]:
        print(' - %06x' % addr, text)
    for addr, text in new[c:d]:
        print(' + %04x' % addr, text)
print('Instruction-diff lines after masking:', score)
