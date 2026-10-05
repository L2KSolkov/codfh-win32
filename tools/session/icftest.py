"""icftest.py N [order...]: where link 7.10 /OPT:ICF places a group of identical functions (PLAN M7).

Compiles N objects o0..oN-1, each with a marker function before and after its copy of an
identical function f_i, links them (in the given order of indices, default 0..N-1) with an
entry that calls every f_i, and prints which object's slot the group's code sits in."""
import os
import re
import subprocess
import sys

ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
VC = r'C:\XDK\xbox\bin\vc71'
OUT = os.path.join(ROOT, 'build', 'tooltmp', 'icftest')
os.makedirs(OUT, exist_ok=True)
env = dict(os.environ)
env['PATH'] = VC + os.pathsep + r'C:\XDK\xbox\bin' + os.pathsep + env['PATH']
env['INCLUDE'] = r'C:\XDK\xbox\include'
n = int(sys.argv[1])
order = [int(x) for x in sys.argv[2:]] or list(range(n))
SIZE = os.environ.get('SIZE', '')    # per-object extra (comma list of ints) to vary sizes
sizes = [int(x) for x in SIZE.split(',')] if SIZE else [0] * n
refs = [int(x) for x in os.environ['REFS'].split(',')] if os.environ.get('REFS') else list(range(n))
objs = []
for i in range(n):
    src = os.path.join(OUT, 'o%d.cpp' % i)
    pad = ''.join('    g += %d;\n' % k for k in range(sizes[i]))
    # EXTRA: that many more distinct (referenced) functions in o0
    extra = int(os.environ.get('EXTRA', '0')) if i == 0 else 0
    xs = ''.join('int x%d_%d() { return %d; }\n' % (i, k, 1000 + k) for k in range(extra))
    calls = ''.join(' g += x%d_%d();' % (i, k) for k in range(extra))
    open(src, 'w').write('extern int g;\n' + xs + 'void m%d_a() { g = %d;\n%s}\nint f%d(int x) { return 0; }\n'
                         'void m%d_b() { g = %d;%s }\n' % (i, 100 + i, pad, i, i, 200 + i, calls))
    obj = os.path.join(OUT, 'o%d.obj' % i)
    subprocess.run([os.path.join(VC, 'cl.exe'), '/c', '/nologo', '/Od', '/Gy', '/Fo' + obj, src],
                   env=env, capture_output=True, check=True)
    objs.append(obj)
main = os.path.join(OUT, 'main.cpp')
open(main, 'w').write(''.join('int f%d(int); void m%d_a(); void m%d_b();\n' % (i, i, i) for i in range(n))
                      + 'int g;\nint main() { int s = 0;\n' + ''.join('s += f%d(%d); m%d_a(); m%d_b();\n' % (i, i, i, i)
                                                             for i in range(n)) + 'return s; }\n')
subprocess.run([os.path.join(VC, 'cl.exe'), '/c', '/nologo', '/Od', '/Gy', '/Fo' + os.path.join(OUT, 'main.obj'), main],
               env=env, capture_output=True, check=True)
mp = os.path.join(OUT, 't.map')
r = subprocess.run([os.path.join(VC, 'link.exe'), '/nologo', '/MACHINE:I386', '/SUBSYSTEM:CONSOLE', '/ENTRY:main',
                    '/NODEFAULTLIB', '/OPT:REF', '/OPT:ICF', '/MAP:' + mp, '/OUT:' + os.path.join(OUT, 't.exe'),
                    os.path.join(OUT, 'main.obj')] + [objs[i] for i in order], env=env, capture_output=True, text=True)
if r.returncode:
    print(r.stdout, r.stderr)
    sys.exit(1)
rows = []
for l in open(mp):
    m = re.match(r'^\s*0001:([0-9a-f]{8})\s+(\S+)\s+([0-9a-f]{8})', l)
    if m:
        rows.append((int(m.group(3), 16), m.group(2)))
rows.sort()
fa = next(a for a, s in rows if s.startswith('?f0@'))
prev = [s for a, s in rows if a < fa][-1]
print('order', order, 'group after', prev, '->', 'o' + re.search(r'm(\d+)_a', prev).group(1) if 'm' in prev else prev)
