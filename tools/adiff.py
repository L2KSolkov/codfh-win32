"""adiff.py FILE ADDR END: aligned diff of our compile against the image, with
frame offsets, call/jump targets and absolute operands blanked; prints each
differing hunk with the image's addresses."""
import sys, re, subprocess, difflib, os
S = os.path.dirname(os.path.abspath(__file__))
W = os.path.join(os.path.dirname(S), 'build', 'tooltmp')  # work files
os.makedirs(W, exist_ok=True)

src, addr, end = sys.argv[1], sys.argv[2], sys.argv[3]
ours = subprocess.run([sys.executable, S + r'\ourdis.py', src, addr], capture_output=True, text=True).stdout.splitlines()
orig = subprocess.run([sys.executable, S + r'\xdis.py', addr, end], capture_output=True, text=True).stdout.splitlines()


def norm(l):
    p = l.split(None, 1)
    ins = p[1] if len(p) > 1 else ''
    ins = re.sub(r'\[ebp - 0x[0-9a-f]+\]', '[ebp-N]', ins)
    ins = re.sub(r'\[ebp - \d+\]', '[ebp-N]', ins)
    ins = re.sub(r'^(call|jmp|j\w+) .*', r'\1 X', ins)
    ins = re.sub(r'0x[0-9a-f]{5,}', 'A', ins)
    ins = re.sub(r'\[A\]|\[0\]', '[G]', ins)
    ins = re.sub(r'(push|mov dword ptr \[e\w\w(?: \+ 0x[0-9a-f]+)?\],) (A|0)$', r'\1 K', ins)
    return ins


o = [norm(l) for l in orig if not l.split(None, 1)[-1].startswith('int3')]
oa = [l.split()[0] for l in orig if not l.split(None, 1)[-1].startswith('int3')]
u = [norm(l) for l in ours]
sm = difflib.SequenceMatcher(None, o, u, autojunk=False)
for tag, i1, i2, j1, j2 in sm.get_opcodes():
    if tag == 'equal':
        continue
    print('== %s image %s..%s' % (tag, oa[i1] if i1 < len(oa) else '?', oa[i2 - 1] if i2 - 1 < len(oa) and i2 > i1 else ''))
    for k in range(max(0, i1 - 3), i1):
        print('   ', oa[k], o[k])
    for k in range(i1, i2):
        print(' -', oa[k], o[k])
    for k in range(j1, j2):
        print(' +', u[k])
