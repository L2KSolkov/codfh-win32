"""pulltest.py: how link 7.10 orders the library members it pulls (PLAN M7).

A library of members m0..m3 (each defining f<i>), archived in ARC order (default 0 1 2 3);
main references them in REFS order (default 0 1 2 3), in one object or split over objects
(SPLIT=1: one object per reference). Prints the members' order in the output."""
import os
import re
import subprocess

ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
VC = r'C:\XDK\xbox\bin\vc71'
OUT = os.path.join(ROOT, 'build', 'tooltmp', 'pulltest')
os.makedirs(OUT, exist_ok=True)
env = dict(os.environ)
env['PATH'] = VC + os.pathsep + env['PATH']
arc = [int(x) for x in os.environ.get('ARC', '0 1 2 3').split()]
refs = [int(x) for x in os.environ.get('REFS', '0 1 2 3').split()]
split = os.environ.get('SPLIT')


def cc(name, text):
    src = os.path.join(OUT, name + '.c')
    open(src, 'w').write(text)
    subprocess.run([os.path.join(VC, 'cl.exe'), '/c', '/nologo', '/Od', '/Gy', '/Fo' + os.path.join(OUT, name + '.obj'), src],
                   env=env, capture_output=True, check=True)
    return name + '.obj'


for i in range(4):
    cc('m%d' % i, 'int g%d;\nint f%d(void) { return g%d + %d; }\n' % (i, i, i, i))
lib = os.path.join(OUT, 't.lib')
if os.path.exists(lib):
    os.replace(lib, lib + '.old')
subprocess.run([os.path.join(VC, 'lib.exe'), '/nologo', '/OUT:t.lib'] + ['m%d.obj' % i for i in arc], cwd=OUT,
               env=env, capture_output=True, check=True)
objs = []
if split:
    for k, i in enumerate(refs):
        objs.append(cc('u%d' % k, 'int f%d(void);\nint u%d(void) { return f%d(); }\n' % (i, k, i)))
    objs.append(cc('main', ''.join('int u%d(void);\n' % k for k in range(len(refs)))
                   + 'int main(void) { return 0' + ''.join(' + u%d()' % k for k in range(len(refs))) + '; }\n'))
    objs = [objs[-1]] + objs[:-1]
else:
    objs.append(cc('main', ''.join('int f%d(void);\n' % i for i in range(4))
                   + 'int main(void) { return 0' + ''.join(' + f%d()' % i for i in refs) + '; }\n'))
r = subprocess.run([os.path.join(VC, 'link.exe'), '/nologo', '/MACHINE:I386', '/SUBSYSTEM:CONSOLE', '/ENTRY:main',
                    '/NODEFAULTLIB', '/MAP:t.map', '/OUT:t.exe'] + objs + ['t.lib'], cwd=OUT, env=env,
                   capture_output=True, text=True)
if r.returncode:
    print(r.stdout)
rows = []
for l in open(os.path.join(OUT, 't.map')):
    m = re.match(r'^\s*0001:([0-9a-f]{8})\s+_f(\d)\s', l)
    if m:
        rows.append((int(m.group(1), 16), int(m.group(2))))
print('arc', arc, 'refs', refs, 'split' if split else '', '-> out', [i for a, i in sorted(rows)])
