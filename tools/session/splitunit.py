"""splitunit.py SRC ADDR [unitsplit options]: split a unit at an object boundary, end to end (PLAN M7).

Runs unitsplit.py, fwdfix.py on both units (the new one --from the old), rehome.py, rowsync.py, then hands the
$E and .CRT$XCU match lines out: the image groups initializers, exit thunks and .CRT$XCU slots
in object order, so the old object's (as many as it compiles to) are the lowest addresses and the
new one's the rest; eremap.py then names both. Build and check afterwards. --resume: only the
$E hand-out (after fixing a failed step by hand)."""
import os
import re
import subprocess
import sys

sys.path.insert(0, os.path.join(os.path.dirname(os.path.abspath(__file__)), '..'))
from build_probes import flags_for, load_flags  # noqa: E402
from coff import Coff  # noqa: E402
from ibuild import compile_with_deps  # noqa: E402

S = os.path.dirname(os.path.abspath(__file__))
ROOT = os.path.dirname(os.path.dirname(S))
LINE = re.compile(r'^// match: (_\$E\d+|\.CRT\$XCU\+\d+) @ 0x([0-9A-Fa-f]+)$')
SPLIT = 0x30DBF0


def run(*args):
    r = subprocess.run([sys.executable] + list(args), cwd=ROOT, capture_output=True, text=True)
    print((r.stdout + r.stderr).strip()[-1500:])
    if r.returncode:
        raise SystemExit('failed: ' + ' '.join(args))
    return r.stdout


def counts(src):
    rel = os.path.relpath(os.path.abspath(src), ROOT).replace(os.sep, '/')
    obj = os.path.join(ROOT, 'build', 'tooltmp', 'splitunit.obj')
    out = []
    if compile_with_deps(os.path.abspath(src), obj, flags_for(rel, load_flags()) + ['/I' + os.path.join(ROOT, 'include')], out) is None:
        raise SystemExit('%s does not compile' % src)
    c = Coff(obj)
    yc = sum(1 for s in c.symbol_list if s['section'] > 0 and re.match(r'_\$E\d+$', s['name'])
             and c.sections[s['section'] - 1]['name'] == '.text$yc')
    yd = sum(1 for s in c.symbol_list if s['section'] > 0 and re.match(r'_\$E\d+$', s['name'])
             and c.sections[s['section'] - 1]['name'] == '.text$yd')
    xcu = sum(sec['size'] // 4 for sec in c.sections if sec['name'] == '.CRT$XCU')
    return yc, yd, xcu


def rd(p):
    raw = open(p, 'rb').read().decode('utf-8', errors='surrogateescape')
    return ('\r\n' if '\r\n' in raw else '\n'), raw.replace('\r\n', '\n')


def wr(p, nl, t):
    open(p, 'wb').write(t.replace('\n', nl).encode('utf-8', errors='surrogateescape'))


src = sys.argv[1]
addr = int(sys.argv[2], 16)
new = os.path.join(os.path.dirname(src), 'unit_%06X%s' % (addr, os.path.splitext(src)[1]))
if '--resume' in sys.argv:
    # after a failed step was fixed by hand: hand out the $E lines only
    sys.argv.remove('--resume')
else:
    run(os.path.join(S, 'unitsplit.py'), *sys.argv[1:])
    run(os.path.join(S, 'fwdfix.py'), new, '--from', src)
    run(os.path.join(S, 'fwdfix.py'), src)
    run(os.path.join(S, 'rehome.py'), src, new)
    run(os.path.join(S, 'rowsync.py'), src, new)
nlo, to = rd(src)
entries = [(int(m.group(2), 16), m.group(0)) for m in (LINE.match(l) for l in to.split('\n')) if m]
if entries:
    yc, yd, xcu = counts(src)
    ia = sorted(a for a, l in entries if 'XCU' not in l and a < SPLIT)
    ea = sorted(a for a, l in entries if 'XCU' not in l and a >= SPLIT)
    xa = sorted(a for a, l in entries if 'XCU' in l)
    go = set(ia[yc:] + ea[yd:] + xa[xcu:])
    if go:
        lines = to.split('\n')
        moving = [l for l in lines if LINE.match(l) and int(LINE.match(l).group(2), 16) in go]
        nln, tn = rd(new)
        nlines = tn.split('\n')
        # after the head's includes and using lines (both files computed before either is written)
        at = max(i for i, l in enumerate(nlines) if l.startswith(('#include', 'using namespace')))
        nlines[at + 1:at + 1] = [''] + moving
        wr(src, nlo, '\n'.join(l for l in lines if l not in moving))
        wr(new, nln, '\n'.join(nlines))
        run(os.path.join(S, 'eremap.py'), new)
    run(os.path.join(S, 'eremap.py'), src)
print('split', src, '->', new)
