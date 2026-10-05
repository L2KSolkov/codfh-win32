"""unitcheck.py SRC: compile SRC with its config/flags.txt flags and compare
every `// match:` function with the image: the ncmp line count (0 = same
instructions after masking) and, when that is 0, rawcmp's byte check, which
also catches encoding differences ncmp's text hides (rawcmp also flags tail
jumps to external functions, which the placement build resolves; trust the
build for those). Prints only functions
that are not identical, then `bad N`."""
import os
import re
import subprocess
import sys

S = os.path.dirname(os.path.abspath(__file__))
ROOT = os.path.dirname(S)
sys.path.insert(0, S)
from build_probes import compile_unit, flags_for, load_flags  # noqa: E402

src = sys.argv[1].replace('\\', '/')
obj = os.path.join(ROOT, 'build', 'tooltmp', 'unitcheck.obj')
if not compile_unit(src, obj, flags_for(src, load_flags())):
    sys.exit(1)
try:
    t = open(src, encoding='utf-8').read()
except UnicodeDecodeError:
    t = open(src, encoding='latin-1').read()
bad = 0
for n, a in re.findall(r'// match: (\S+) @ (0x[0-9A-F]+)', t):
    r = subprocess.run([sys.executable, os.path.join(S, 'ncmp.py'), obj, n, a],
                       capture_output=True, text=True).stdout.split('\n')[0].strip()
    if r == '0':
        raw = subprocess.run([sys.executable, os.path.join(S, 'rawcmp.py'), obj, n, a],
                             capture_output=True, text=True).stdout
        m = re.search(r'mismatches: (\d+)', raw)
        if m and m.group(1) != '0':
            r = 'raw %s' % m.group(1)
    if r != '0':
        bad += 1
        print(n, a, r)
print('bad', bad)
