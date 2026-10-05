"""build_trivial_xbe.py

M0 step 3: compiles probes/xbe/trivial.cpp with the game's flags, links it with
the XDK's link.exe, runs imagebld.exe with the options the original's header
implies, and prints the header comparison against the original XBE."""
import os
import subprocess
import sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
from build_probes import compile_unit, flags_for, load_flags  # noqa: E402

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
XDK = os.environ.get('XDK', r'C:\XDK')
BIN = os.path.join(XDK, 'xbox', 'bin')
VC = os.path.join(BIN, 'vc71')


def run(command):
    env = dict(os.environ)
    env['PATH'] = VC + os.pathsep + BIN + os.pathsep + env.get('PATH', '')
    env['LIB'] = os.path.join(XDK, 'xbox', 'lib')
    result = subprocess.run(command, env=env, capture_output=True, text=True)
    sys.stdout.write(result.stdout + result.stderr)
    if result.returncode != 0:
        raise SystemExit('failed: %s' % ' '.join(command))


def main():
    out = os.path.join(ROOT, 'build', 'trivial')
    if not os.path.isdir(out):
        os.makedirs(out)
    source = os.path.join(ROOT, 'probes', 'xbe', 'trivial.cpp')
    obj = os.path.join(out, 'trivial.obj')
    if not compile_unit(source, obj, flags_for('probes/x.cpp', load_flags())):
        raise SystemExit('compile failed')
    exe = os.path.join(out, 'trivial.exe')
    # /SUBSYSTEM:XBOX is added by the VS.NET 2003 Xbox integration, not the
    # sample projects; imagebld refuses images linked without it (IM1012).
    run([os.path.join(VC, 'Link.Exe'), '/nologo', '/MACHINE:I386', '/SUBSYSTEM:XBOX', '/FIXED:NO',
         '/INCREMENTAL:NO', '/OPT:REF', '/OPT:ICF', '/DEBUG',
         '/MAP:' + os.path.join(out, 'trivial.map'), '/OUT:' + exe,
         obj, 'xapilib.lib', 'xboxkrnl.lib'])
    xbe = os.path.join(out, 'trivial.xbe')
    run([os.path.join(BIN, 'imagebld.exe'), '/NOLOGO', '/IN:' + exe, '/OUT:' + xbe,
         '/STACK:0x10000', '/TESTID:0x4156002A', '/TESTNAME:Call of Duty Finest Hour',
         '/DEBUG'])
    subprocess.call([sys.executable, os.path.join(ROOT, 'tools', 'xbe_dump.py'),
                     os.path.join(ROOT, 'orig', 'Game_XboxMultiplayer.xbe'), xbe])


if __name__ == '__main__':
    main()
