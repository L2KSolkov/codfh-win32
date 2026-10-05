"""build_probes.py [PROBE ...]

Compiles each toolchain probe in probes/ with the original compiler and the
flags config/flags.txt assigns it, then checks every `// match: NAME @ 0xADDR`
annotation in the probe against the original image. Exit status 0 means every
annotated function is identical."""
import fnmatch
import glob
import os
import re
import subprocess
import sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
from match import compare  # noqa: E402
from xbe import Xbe  # noqa: E402

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
XDK = os.environ.get('XDK', r'C:\XDK')
CL = os.path.join(XDK, 'xbox', 'bin', 'vc71', 'CL.Exe')
# `/compiler:NAME` in a config/flags.txt rule picks another compiler under
# XDK\xbox\bin (vc70: VC7.0 13.00.9466, from the June 2002 XDK 4627, which
# built RenderWare Audio and RtFS); it is never passed to the compiler.
COMPILERS = {'vc71': CL, 'vc70': os.path.join(XDK, 'xbox', 'bin', 'vc70', 'CL.Exe')}


def split_compiler(flags):
    """(compiler path, flags without the /compiler: pseudo-flag)."""
    cl = CL
    kept = []
    for f in flags:
        if f.startswith('/compiler:'):
            cl = COMPILERS[f.split(':', 1)[1]]
        else:
            kept.append(f)
    return cl, kept
MATCH_RE = re.compile(r'//\s*match:\s*(\S+)\s*@\s*(0x[0-9A-Fa-f]+)')
SYMBOL_RE = re.compile(r'//\s*symbol:\s*(\S+)\s*=\s*(0x[0-9A-Fa-f]+)')


def aliases_in(text):
    """`// symbol: NAME = 0xADDRESS` annotations: addresses for compiled names
    that carry none, such as constructors and destructors."""
    return dict((name, int(address, 16)) for name, address in SYMBOL_RE.findall(text))


def load_flags():
    rules = []
    for line in open(os.path.join(ROOT, 'config', 'flags.txt')):
        line = line.split('#', 1)[0].strip()
        if not line:
            continue
        pattern, flags = line.split(':', 1)
        rules.append((pattern.strip(), flags.split()))
    return rules


def flags_for(rel, rules):
    for pattern, flags in rules:
        if fnmatch.fnmatch(rel, pattern):
            return flags
    raise SystemExit('no flags rule matches %s' % rel)


# MASM for Bink's .asm units (PLAN M6: ml.exe 14.51)
ML = r'C:\Program Files\Microsoft Visual Studio\18\Enterprise\VC\Tools\MSVC\14.51.36231\bin\Hostx86\x86\ml.exe'


def compile_unit(source, obj, flags, out=None):
    """Compiles source to obj; the compiler's messages on failure go to
    stdout, or into the list out when given (build_sources' workers)."""
    if source.lower().endswith('.asm'):
        # Bink's hand-written assembly units (PLAN M6) go through MASM; the
        # unit's cl flags do not apply.
        command = [ML, '/c', '/nologo', '/Cp', '/Fo' + obj, source]
        result = subprocess.run(command, capture_output=True, text=True)
        if result.returncode != 0:
            message = (result.stdout + result.stderr).rstrip('\n')
            if out is None:
                sys.stdout.write(message + '\n')
            else:
                out.append(message)
            return False
        return True
    cl, flags = split_compiler(flags)
    env = dict(os.environ)
    env['PATH'] = os.path.dirname(cl) + os.pathsep + env.get('PATH', '')
    env['INCLUDE'] = os.path.join(XDK, 'xbox', 'include')
    if '/Zi' in flags and not any(f.startswith('/Fd') for f in flags):
        # One program database per object, beside it, so parallel compiles
        # never share one (VC7.1 has no /FS).
        flags = flags + ['/Fd' + os.path.splitext(obj)[0] + '.pdb']
    command = [cl] + flags + ['/Fo' + obj, source]
    result = subprocess.run(command, env=env, capture_output=True, text=True)
    if result.returncode != 0:
        if out is None:
            sys.stdout.write(result.stdout + result.stderr)
        else:
            out.append((result.stdout + result.stderr).rstrip('\n'))
        return False
    return True


def main(argv):
    rules = load_flags()
    out_dir = os.path.join(ROOT, 'build', 'probes')
    if not os.path.isdir(out_dir):
        os.makedirs(out_dir)
    probes = argv[1:] or sorted(glob.glob(os.path.join(ROOT, 'probes', '*.cpp')))
    image = Xbe(os.path.join(ROOT, 'orig', 'Game_XboxMultiplayer.xbe'))
    failures = 0
    for source in probes:
        rel = os.path.relpath(source, ROOT).replace('\\', '/')
        obj = os.path.join(out_dir, os.path.splitext(os.path.basename(source))[0] + '.obj')
        if not compile_unit(source, obj, flags_for(rel, rules)):
            print('FAIL %s: compile error' % rel)
            failures += 1
            continue
        text = open(source).read()
        aliases = aliases_in(text)
        for name, address in MATCH_RE.findall(text):
            ok, message = compare(obj, name, int(address, 16), image, aliases)
            print(('OK   ' if ok else 'DIFF ') + message)
            failures += 0 if ok else 1
    return 1 if failures else 0


if __name__ == '__main__':
    sys.exit(main(sys.argv))
