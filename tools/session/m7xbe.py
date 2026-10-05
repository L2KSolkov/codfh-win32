"""m7xbe.py [EXE]: the M7 probe's link output (build/m7/game.exe) through imagebld.exe 5849.4 into
build/m7/game.xbe, then compared with the original section by section (PLAN M7: after retail
post-processing the output must be byte-identical). Per section: the virtual address and size
each image gives it, the first differing offset and the number of differing bytes. The header
(certificate, signature, XOR keys, timestamps) is retail post-processing's and is not
compared here."""
import os
import subprocess
import sys

sys.path.insert(0, os.path.join(os.path.dirname(os.path.abspath(__file__)), '..'))
from xbe import Xbe  # noqa: E402

ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
XDK = os.environ.get('XDK', r'C:\XDK')
BIN = os.path.join(XDK, 'xbox', 'bin')
exe = sys.argv[1] if len(sys.argv) > 1 else os.path.join(ROOT, 'build', 'm7', 'game.exe')
xbe = os.path.splitext(exe)[0] + '.xbe'
env = dict(os.environ)
env['PATH'] = os.path.join(BIN, 'vc71') + os.pathsep + BIN + os.pathsep + env.get('PATH', '')
# the files imagebld inserts (the probe links without them, M7NOINSERTED=1): the title image and
# the default save image, taken from the original's sections
orig = Xbe(os.path.join(ROOT, 'orig', 'Game_XboxMultiplayer.xbe'))
inputs = []
for sec, opt, fn in (('$$XTIMAGE', '/TITLEIMAGE:', 'titleimage.xpr'), ('$$XSIMAGE', '/DEFAULTSAVEIMAGE:', 'saveimage.xpr')):
    s = next((x for x in orig.sections if x['name'] == sec), None)
    if s is not None:
        p = os.path.join(os.path.dirname(exe), fn)
        open(p, 'wb').write(orig.read(s['va'], s['vsize']))
        inputs.append(opt + p)
r = subprocess.run([os.path.join(BIN, 'imagebld.exe'), '/NOLOGO', '/IN:' + exe, '/OUT:' + xbe,
                    '/STACK:0x10000', '/TESTID:0x4156002A', '/TESTNAME:Call of Duty Finest Hour', '/DEBUG'] + inputs,
                   env=env, capture_output=True, text=True)
sys.stdout.write(r.stdout + r.stderr)
if r.returncode != 0 or not os.path.exists(xbe):
    raise SystemExit('imagebld failed')
ours = Xbe(xbe)
# (sections of one name, BINKYUY2's four, paired in order)
os_ = set(s['name'] for s in orig.sections)
us_ = set(s['name'] for s in ours.sections)
ours_by = {}
for s in sorted(ours.sections, key=lambda s: s['va']):
    ours_by.setdefault(s['name'], []).append(s)
total = 0
for s in orig.sections:
    n = s['name']
    u = ours_by[n].pop(0) if ours_by.get(n) else None
    if u is None:
        print('%-10s missing in ours' % n)
        continue
    a = orig.read(s['va'], s['vsize'])
    try:
        b = ours.read(u['va'], u['vsize'])
    except Exception:
        b = b''
    m = min(len(a), len(b))
    diff = sum(1 for k in range(m) if a[k] != b[k]) + abs(len(a) - len(b))
    first = next((k for k in range(m) if a[k] != b[k]), None if len(a) == len(b) else m)
    total += diff
    print('%-10s va %08X/%08X size %06X/%06X  %s' % (
        n, s['va'], u['va'], s['vsize'], u['vsize'],
        'identical' if not diff else 'first diff +0x%X (0x%08X), %d bytes differ' % (first, s['va'] + first, diff)))
for n in us_:
    if n not in os_:
        print('%-10s only in ours' % n)
print('total differing bytes', total)
