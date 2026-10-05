"""pulltest2.py: does link 7.10 pull a library member's own references before the rest of the
undefined symbols (depth first) or after them (queue)? (PLAN M7)

Members: a (fa calls fc), b (fb), c (fc), d (fd, calls fe), e (fe); main references fa, fb, fd
in that order (one reference each). Prints the members' order in the output."""
import os
import re
import subprocess

ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
VC = r'C:\XDK\xbox\bin\vc71'
OUT = os.path.join(ROOT, 'build', 'tooltmp', 'pulltest2')
os.makedirs(OUT, exist_ok=True)
env = dict(os.environ)
env['PATH'] = VC + os.pathsep + env['PATH']


def cc(name, text):
    src = os.path.join(OUT, name + '.c')
    open(src, 'w').write(text)
    subprocess.run([os.path.join(VC, 'cl.exe'), '/c', '/nologo', '/Od', '/Gy', '/Fo' + os.path.join(OUT, name + '.obj'), src],
                   env=env, capture_output=True, check=True)


cc('a', 'int fc(void);\nint fa(void) { return fc() + 1; }\n')
cc('b', 'int fb(void) { return 2; }\n')
cc('c', 'int fc(void) { return 3; }\n')
cc('d', 'int fe(void);\nint fd(void) { return fe() + 4; }\n')
cc('e', 'int fe(void) { return 5; }\n')
refs = os.environ.get('REFS', 'a b d').split()
cc('main', 'int fa(void); int fb(void); int fd(void);\nint main(void) { return 0'
   + ''.join(' + f%s()' % r for r in refs) + '; }\n')
lib = os.path.join(OUT, 't.lib')
if os.path.exists(lib):
    os.replace(lib, lib + '.old')
subprocess.run([os.path.join(VC, 'lib.exe'), '/nologo', '/OUT:t.lib', 'a.obj', 'b.obj', 'c.obj', 'd.obj', 'e.obj'],
               cwd=OUT, env=env, capture_output=True, check=True)
r = subprocess.run([os.path.join(VC, 'link.exe'), '/nologo', '/MACHINE:I386', '/SUBSYSTEM:CONSOLE', '/ENTRY:main',
                    '/NODEFAULTLIB', '/MAP:t.map', '/OUT:t.exe', 'main.obj', 't.lib'], cwd=OUT, env=env,
                   capture_output=True, text=True)
if r.returncode:
    print(r.stdout)
rows = []
for l in open(os.path.join(OUT, 't.map')):
    m = re.match(r'^\s*0001:([0-9a-f]{8})\s+_f([a-e])\s', l)
    if m:
        rows.append((int(m.group(1), 16), m.group(2)))
print('refs', refs, '-> out', [x for a, x in sorted(rows)])
