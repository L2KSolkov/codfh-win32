"""rawcmp.py OBJ SYM ADDR: compare our function with the image instruction by
instruction at the same offsets, branch targets made function-relative (ncmp
masks them). Prints mismatching lines; operands that are relocations in either
side (names, or small object addends) are shown but only mnemonic/offset/branch
differences count."""
import os
import re
import subprocess
import sys

S = os.path.dirname(os.path.abspath(__file__))
W = os.path.join(os.path.dirname(S), 'build', 'tooltmp')  # work files
os.makedirs(W, exist_ok=True)

obj, sym, addr = sys.argv[1], sys.argv[2], int(sys.argv[3], 16)
b = subprocess.run([sys.executable, os.path.join(S, 'objdis.py'), obj, sym], capture_output=True, text=True).stdout
ours = []
for l in b.splitlines():
    m = re.match(r'\s*([0-9a-f]+)\s+(.*)$', l)
    if m:
        ours.append((int(m.group(1), 16), m.group(2).strip()))
end = ours[-1][0] + 16 if ours else 0x100
a = subprocess.run([sys.executable, os.path.join(S, 'xdis.py'), '%X' % addr, '%X' % (addr + end)],
                   capture_output=True, text=True).stdout
img = []
for l in a.splitlines():
    m = re.match(r'([0-9a-f]+)\s+(.*)$', l)
    if m:
        img.append((int(m.group(1), 16) - addr, m.group(2).strip()))
imgd = dict(img)
bad = 0
for off, txt in ours:
    it = imgd.get(off)
    if it is None:
        print('%4x %-45s | (no image instruction here)' % (off, txt))
        bad += 1
        continue
    mo, mi = txt.split()[0], it.split()[0]
    jo = re.match(r'(j\w+|call|loop\w*) 0x([0-9a-f]+)$', txt)
    ji = re.match(r'(j\w+|call|loop\w*) 0x([0-9a-f]+)$', it)
    diff = mo != mi
    if mo.startswith('j') and mo != 'jmp' or mo == 'jmp' and jo:
        if jo and ji and int(jo.group(2), 16) != int(ji.group(2), 16) - addr:
            diff = True
        if jo and not ji and not re.search(r'(def|loc)_', it):
            diff = True
    if diff:
        bad += 1
        print('%4x %-45s | %s' % (off, txt, it))
print('mismatches:', bad)
