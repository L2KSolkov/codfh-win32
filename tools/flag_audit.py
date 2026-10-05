"""flag_audit.py

Rebuilds every probe under variants of the probe flag set — each flag
removed, and plausible alternatives added — and reports which probes each
variant breaks. A flag is proven only when removing or replacing it breaks at
least one probe; a variant that breaks nothing means the probes do not yet
distinguish it."""
import glob
import os
import sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
from build_probes import MATCH_RE, ROOT, compile_unit, flags_for, load_flags  # noqa: E402
from match import compare  # noqa: E402
from xbe import Xbe  # noqa: E402

# Flags that only change diagnostics or bookkeeping, never code.
NON_CODEGEN = set(['/c', '/nologo', '/W3'])

ALTERNATIVES = [
    ('add /arch:SSE', ['/arch:SSE']),
    ('add /Ob1', ['/Ob1']),
    ('add /Oy-', ['/Oy-']),
    ('add /GR', ['/GR']),
    ('add /O2', ['/O2']),
    ('add /G5', ['/G5']),
]


def run(flags, probes, image):
    broken = []
    out_dir = os.path.join(ROOT, 'build', 'audit')
    if not os.path.isdir(out_dir):
        os.makedirs(out_dir)
    for source in probes:
        obj = os.path.join(out_dir, os.path.splitext(os.path.basename(source))[0] + '.obj')
        if os.path.exists(obj):
            os.remove(obj)
        if not compile_unit(source, obj, flags):
            broken.append(os.path.basename(source) + ' (compile)')
            continue
        for name, address in MATCH_RE.findall(open(source).read()):
            ok, _ = compare(obj, name, int(address, 16), image)
            if not ok:
                broken.append('%s:%s' % (os.path.basename(source), name))
    return broken


def main():
    image = Xbe(os.path.join(ROOT, 'orig', 'Game_XboxMultiplayer.xbe'))
    probes = sorted(glob.glob(os.path.join(ROOT, 'probes', '*.cpp')))
    base = flags_for('probes/x.cpp', load_flags())
    variants = [('baseline', base)]
    for flag in base:
        if flag not in NON_CODEGEN:
            variants.append(('drop ' + flag, [f for f in base if f != flag]))
    variants.append(('/EHsc -> /GX', [('/GX' if f == '/EHsc' else f) for f in base]))
    variants.append(('/G6 -> /G7', [('/G7' if f == '/G6' else f) for f in base]))
    for label, extra in ALTERNATIVES:
        variants.append((label, base + extra))
    for label, flags in variants:
        broken = run(flags, probes, image)
        print('%-16s %s' % (label, ('breaks: ' + ', '.join(broken)) if broken else 'no probe changes'))


if __name__ == '__main__':
    main()
