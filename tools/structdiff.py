import os
"""structdiff.py SOURCE ADDR: diff a function against the image with frame
slots, immediates and relocated operands masked."""
import subprocess, sys, re, difflib
S = os.path.dirname(os.path.abspath(__file__))
W = os.path.join(os.path.dirname(S), 'build', 'tooltmp')  # work files
os.makedirs(W, exist_ok=True)

out = subprocess.run(['python', S + r'\trial.py', sys.argv[1], sys.argv[2], 'x'],
                     capture_output=True, text=True).stdout


def norm(s):
    s = re.sub(r'ebp - (0x[0-9a-f]+|\d+)', 'ebp-?', s)
    s = re.sub(r'\[(\w+\*\d) \+ 0x[0-9a-f]+\]', r'[\1]', s)
    s = re.sub(r'0x[0-9a-f]+', 'N', s)
    s = re.sub(r'\[0\]', '[N]', s)
    s = re.sub(r', 0$', ', N', s)
    s = re.sub(r'^push 0$', 'push N', s)
    s = re.sub(r'^call \d+$', 'call N', s)
    return s


A, B = [], []
for l in out.splitlines()[3:]:
    if l.startswith('@@'):
        continue
    n = norm(l[1:])
    if l.startswith('-'):
        A.append(n)
    elif l.startswith('+'):
        B.append(n)
    else:
        A.append(n)
        B.append(n)
d = list(difflib.unified_diff(A, B, lineterm='', n=2))
print('\n'.join(d[:80]) if d else 'only slots differ')
