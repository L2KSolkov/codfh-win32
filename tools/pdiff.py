import re, sys, subprocess, os
S = os.path.dirname(os.path.abspath(__file__))
W = os.path.join(os.path.dirname(S), 'build', 'tooltmp')  # work files
os.makedirs(W, exist_ok=True)

src, a, b = sys.argv[1], sys.argv[2], sys.argv[3]
lim = int(sys.argv[4]) if len(sys.argv) > 4 else 40
t = subprocess.run([sys.executable, S + r'\adiffb.py', src, a, b], capture_output=True, text=True).stdout
open(W + r'\last_diff.txt', 'w').write(t)
hunks = t.split('== ')[1:]
noise = re.compile(r'^ [-+] (mov e.x, (A|0|8)|push (sub_FCD90|K|A|a\w+)|add byte ptr \[eax\], al|add ecx, (A|0))$')


def canon(l):
    # a relocated displacement shows as + A in the image and nothing in ours
    return re.sub(r' \+ A\]', ']', l)
n = 0
for h in hunks:
    lines = h.splitlines()
    body = [re.sub(r'^ ([-+]) [0-9a-f]+ ', r' \1 ', l) for l in lines[1:] if l.startswith(' -') or l.startswith(' +')]
    body = [canon(l) for l in body]
    minus = sorted(l[3:] for l in body if l.startswith(' -'))
    plus = sorted(l[3:] for l in body if l.startswith(' +'))
    if minus == plus:
        continue
    real = [l for l in body if not noise.match(l)]
    if real:
        n += 1
        if n <= lim:
            print('== ' + lines[0]); print('\n'.join(real[:16]))
print('real hunks', n)
