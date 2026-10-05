"""plainbuild.py [--with-standins] [--devnet] [--define NAME]... [LINKOPT...]: the game built without any of the M7 tooling:
the compiled sources (build/src, as tools/ibuild.py leaves them) linked with plain options against
the installed XDK libraries, then imagebld. No /ORDER, no forced imports, no section keying, no
object or library rewriting, no fill pieces, no /FORCE. Output in build/plain: game.exe,
game.map, link.log and, when the link succeeds, game.xbe.

The XDK stand-ins (src/xdk: library code the image holds in a version the installed libraries
lack) are left out by default: they replace library members only for byte-identity, which this
build does not aim at; --with-standins links them too (they then clash with the installed
members and refer to image addresses, which only the M7 tooling resolves). Bink is RAD's
binkxbox.lib (docs/reference/Bink, an older Bink than the image's) in place of src/bink, whose
naked BinkOpen transcription needs the M7 probe's alias names. src/xbe's pieces are M7-only
and never linked. link.exe's one warning, LNK4098 (RenderWare and RenderWare Audio were built
/ML and name LIBC), is left: libcmt.lib serves them. The result is not byte-identical to the original (that is
tools/session/m7probe.py, m7xbe.py and m7retail.py); it is what the sources and the SDK make.

Plain builds define CODFH_PLAIN: every unit whose source or included headers mention it (the
include lists tools/ibuild.py records) is recompiled with /DCODFH_PLAIN into build/plain/obj and
linked in place of its build/src object. It covers what only the placement link otherwise gets
right, such as names the source declares as globals that are fields of a larger object in the
image (the multiplayer manager's, unit_1A8B20). --define NAME adds research switches the same
way (e.g. --define CODFH_DRAW_TRIGGERS), and compiles and links research/**/*.cpp too. Objects
newer than their source, headers and flags are reused. --devnet links the devkit network
libraries (xnet.lib, xonline.lib) for the secure ones, so XNET_STARTUP_BYPASS_SECURITY works."""
import concurrent.futures
import glob
import json
import os
import subprocess
import sys

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
os.chdir(ROOT)
OUT = os.path.join(ROOT, 'build', 'plain')
os.makedirs(OUT, exist_ok=True)
XDK = os.environ.get('XDK', r'C:\XDK')
BIN = os.path.join(XDK, 'xbox', 'bin')
VC = os.path.join(BIN, 'vc71')
env = dict(os.environ)
env['PATH'] = VC + os.pathsep + BIN + os.pathsep + env['PATH']
env['LIB'] = os.path.join(XDK, 'xbox', 'lib')

STANDINS = '--with-standins' in sys.argv[1:]
args = sys.argv[1:]
skip = set(i + 1 for i, a in enumerate(args) if a == '--define')
DEFINES = ['CODFH_PLAIN'] + [args[i] for i in sorted(skip) if i < len(args)]
extra = [a for i, a in enumerate(args) if not a.startswith('--') and i not in skip]

sys.path.insert(0, os.path.join(ROOT, 'tools'))
from build_probes import compile_unit, flags_for, load_flags  # noqa: E402
rules = load_flags()
_mentions = {}


def mentions(path):
    """Whether the file names one of the defines (cached per file)."""
    if path not in _mentions:
        try:
            text = open(path, encoding='utf-8', errors='replace').read()
        except OSError:
            text = ''
        _mentions[path] = any(d in text for d in DEFINES)
    return _mentions[path]


def unit_deps(rel):
    """The headers tools/ibuild.py recorded for the unit (none when it has not built it)."""
    try:
        return json.load(open(os.path.join('build', rel + '.ibuild')))['deps']
    except (OSError, ValueError, KeyError):
        return []


jobs = []           # (source, object, flags, inputs)
for src in sorted(glob.glob('src/**/*.c', recursive=True) + glob.glob('src/**/*.cpp', recursive=True)
                  + glob.glob('research/**/*.cpp', recursive=True)):
    src = src.replace(os.sep, '/')
    rel = os.path.splitext(src)[0]
    deps = unit_deps(rel)
    if not src.startswith('research/') and not (mentions(src) or any(mentions(d) for d in deps)):
        continue
    flags = flags_for(src if src.startswith('src/') else 'src/' + src, rules)
    flags = flags + ['/I' + os.path.join(ROOT, 'include')] + ['/D' + d for d in DEFINES]
    jobs.append((src, os.path.join(OUT, 'obj', rel + '.obj'), flags, [src] + deps))


def build(job):
    """Compiles one unit unless its object is newer than its inputs and has the same flags."""
    src, obj, flags, inputs = job
    stamp = obj + '.flags'
    key = ' '.join(flags)
    if (os.path.exists(obj) and os.path.exists(stamp) and open(stamp).read() == key
            and all(os.path.getmtime(i) < os.path.getmtime(obj) for i in inputs if os.path.exists(i))):
        return None
    os.makedirs(os.path.dirname(obj), exist_ok=True)
    out = []
    if not compile_unit(src, obj, flags, out):
        return '%s:\n%s' % (src, '\n'.join(out))
    open(stamp, 'w').write(key)
    return ''


with concurrent.futures.ThreadPoolExecutor(os.cpu_count() or 4) as pool:
    results = list(pool.map(build, jobs))
errors = [r for r in results if r]
print('%s: %d units, %d compiled' % (' '.join('/D' + d for d in DEFINES), len(jobs),
                                     sum(1 for r in results if r is not None)))
for e in errors[:10]:
    # (the error lines first: a unit's warnings can fill the excerpt)
    lines = e.split('\n')
    print('\n'.join([lines[0]] + [l for l in lines if ' error ' in l or 'fatal error' in l][:40]))
    print(e[:3000])
if errors:
    sys.exit('%d compiles failed' % len(errors))
replaced = dict((os.path.splitext(src)[0], obj) for src, obj, flags, inputs in jobs)

objs = []
for o in sorted(glob.glob('build/src/**/*.obj', recursive=True)):
    rel = os.path.relpath(o, 'build').replace(os.sep, '/')[:-4]
    if rel.startswith('src/xbe/') or (not STANDINS and rel.startswith('src/xdk/')):
        continue
    # (Bink: RAD's own library, docs/reference/Bink/binkxbox.lib, the owner's 2026-10-05 choice;
    # our BinkOpen is a naked transcription calling register-convention statics through alias
    # names only the M7 probe supplies)
    if rel.startswith('src/bink/'):
        continue
    # (an object whose source is gone is stale)
    if any(os.path.exists(rel + e) for e in ('.c', '.cpp', '.asm')):
        objs.append(replaced.pop(rel, o))
# (research units, which have no build/src object)
objs += [replaced[r] for r in sorted(replaced) if r.startswith('research/')]
# the image header's library table order
libs = ['xapilib.lib', 'd3d8.lib', 'd3dx8.lib', 'dsound.lib', 'xboxkrnl.lib', 'xonlines.lib', 'uix.lib',
        'xvoice.lib', 'libcpmt.lib', 'libcmt.lib', 'xgraphics.lib', 'xnets.lib',
        os.path.join(ROOT, 'docs', 'reference', 'Bink', 'binkxbox.lib')]
if '--devnet' in sys.argv[1:]:
    # (the devkit network libraries, which honour XNET_STARTUP_BYPASS_SECURITY so a PC can
    # connect, as research/trigweb.cpp's server needs; the secure ones ignore it)
    libs = [{'xonlines.lib': 'xonline.lib', 'xnets.lib': 'xnet.lib'}.get(l, l) for l in libs]
rsp = os.path.join(OUT, 'link.rsp')
open(rsp, 'w').write('\n'.join('"%s"' % os.path.abspath(o) for o in objs) + '\n' + '\n'.join(libs) + '\n')
exe = os.path.join(OUT, 'game.exe')
cmd = [os.path.join(VC, 'Link.Exe'), '/nologo', '/MACHINE:I386', '/SUBSYSTEM:XBOX', '/FIXED:NO',
       '/INCREMENTAL:NO', '/OPT:REF', '/MAP:' + os.path.join(OUT, 'game.map'), '/OUT:' + exe] + extra + ['@' + rsp]
r = subprocess.run(cmd, env=env, capture_output=True, text=True)
log = r.stdout + r.stderr
open(os.path.join(OUT, 'link.log'), 'w').write(' '.join(cmd) + '\n' + log)
errs = [l for l in log.split('\n') if ' error ' in l]
print('%d objects, %d libraries; link exit %d, %d errors (build/plain/link.log)' % (len(objs), len(libs), r.returncode, len(errs)))
for l in errs[:20]:
    print('  ' + l.strip()[:200])
if r.returncode:
    sys.exit(1)
xbe = os.path.join(OUT, 'game.xbe')
r = subprocess.run([os.path.join(BIN, 'imagebld.exe'), '/NOLOGO', '/IN:' + exe, '/OUT:' + xbe, '/STACK:0x10000',
                    '/TESTID:0x4156002A', '/TESTNAME:Call of Duty Finest Hour'], env=env, capture_output=True, text=True)
print('\n'.join(l for l in (r.stdout + r.stderr).split('\n') if ' error ' in l or 'fatal' in l))
print('imagebld exit %d -> %s' % (r.returncode, os.path.relpath(xbe, ROOT)))
sys.exit(r.returncode)
