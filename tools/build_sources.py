"""build_sources.py [SOURCE ...]

Compiles every source unit under src/ with the original compiler and the
flags config/flags.txt assigns it, with include/ on the include path, then
checks every `// match: NAME @ 0xADDR` annotation against the original image.
Objects land in build/src/ mirroring src/. Exit status 0 means every annotated
function is identical.

Units are compiled and checked in parallel, one per worker process (each
object has its own program database, so the compiles never share one); the
report is printed in source order, as a serial run prints it. BUILD_JOBS sets
the number of workers (default: the processor count; 1 runs serially)."""
import glob
import os
import sys
from concurrent.futures import ProcessPoolExecutor

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
from build_probes import MATCH_RE, ROOT, aliases_in, compile_unit, flags_for, load_flags  # noqa: E402
from coff import Coff  # noqa: E402
from match import compare  # noqa: E402
from xbe import Xbe  # noqa: E402

_image = None


def object_for(source):
    rel = os.path.relpath(source, os.path.join(ROOT, 'src'))
    return os.path.join(ROOT, 'build', 'src', os.path.splitext(rel)[0] + '.obj')


def check(source, rules):
    """Compiles one unit and checks its annotations: (report lines, failures)."""
    global _image
    if _image is None:
        _image = Xbe(os.path.join(ROOT, 'orig', 'Game_XboxMultiplayer.xbe'))
    rel = os.path.relpath(source, ROOT).replace(os.sep, '/')
    obj = object_for(source)
    if not os.path.isdir(os.path.dirname(obj)):
        os.makedirs(os.path.dirname(obj), exist_ok=True)
    flags = flags_for(rel, rules) + ['/I' + os.path.join(ROOT, 'include')]
    lines = []
    if not compile_unit(source, obj, flags, lines):
        lines.append('FAIL %s: compile error' % rel)
        return lines, 1
    text = open(source).read()
    aliases = aliases_in(text)
    coff = Coff(obj)
    failures = 0
    for name, address in MATCH_RE.findall(text):
        ok, message = compare(coff, name, int(address, 16), _image, aliases)
        lines.append(('OK   ' if ok else 'DIFF ') + message)
        failures += 0 if ok else 1
    return lines, failures


def main(argv):
    rules = load_flags()
    sources = argv[1:] or sorted(
        glob.glob(os.path.join(ROOT, 'src', '**', '*.cpp'), recursive=True)
        + glob.glob(os.path.join(ROOT, 'src', '**', '*.c'), recursive=True)
        + glob.glob(os.path.join(ROOT, 'src', '**', '*.asm'), recursive=True))
    # (src/sp is the single player's: never part of the multiplayer image; portbuild.py --sp
    # builds it, as ibuild.py's sources step leaves it out)
    if not argv[1:]:
        sp = os.path.join(ROOT, 'src', 'sp') + os.sep
        sources = [s for s in sources if not s.startswith(sp)]
    jobs = int(os.environ.get('BUILD_JOBS') or os.cpu_count() or 1)
    failures = 0
    if jobs <= 1 or len(sources) <= 1:
        results = (check(source, rules) for source in sources)
        for lines, failed in results:
            if lines:
                print('\n'.join(lines))
            failures += failed
        return 1 if failures else 0
    with ProcessPoolExecutor(max_workers=jobs) as pool:
        for lines, failed in pool.map(check, sources, [rules] * len(sources)):
            if lines:
                print('\n'.join(lines))
            failures += failed
    return 1 if failures else 0


if __name__ == '__main__':
    sys.exit(main(sys.argv))
