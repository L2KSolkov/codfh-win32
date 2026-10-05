"""ibuild.py: tools/build.py's gate with incremental source compiles.

Runs the same four steps (source audit, probes, sources, placement link) and
prints the same `== PASS` / `== FAIL` line, but a source unit is recompiled
only when something it was built from changed: its text, its flags, the
compiler, a header it read (as /showIncludes listed on its last compile here),
or its object file itself (for instance rebuilt by tools/build.py since). Every
annotated function is still matched against the image on every run, so the
check is as complete as tools/build.py's; only the compiles are skipped.

State lives beside each object as NAME.ibuild (json: key, deps, the object's
size and mtime). IBUILD_CLEAN=1 recompiles everything. BUILD_JOBS sets the
workers (default: the processor count)."""
import os as _os_repo
_REPO = _os_repo.path.dirname(_os_repo.path.dirname(_os_repo.path.abspath(__file__)))  # the repository root, from this file's location
import glob
import hashlib
import json
import os
import subprocess
import sys
from concurrent.futures import ProcessPoolExecutor

ROOT = _REPO
TOOLS = os.path.join(ROOT, 'tools')
sys.path.insert(0, TOOLS)
from build_probes import CL, MATCH_RE, XDK, aliases_in, compile_unit, flags_for, load_flags, split_compiler  # noqa: E402
from coff import Coff  # noqa: E402
from match import compare  # noqa: E402
from xbe import Xbe  # noqa: E402

import match  # noqa: E402

NOTE = 'Note: including file:'
# what a unit's matches depend on besides its object and text
MATCH_INPUTS = [os.path.join(TOOLS, n) for n in ('match.py', 'coff.py', 'xbe.py', 'build_probes.py')] + \
    [os.path.join(ROOT, 'config', n) for n in ('symbols.txt', 'aliases.txt')]


class _Probe(object):
    """The placement range starts, recording each lookup's answer."""

    def __init__(self, base):
        self.base = base
        self.log = {}

    def __contains__(self, address):
        hit = address in self.base
        self.log[address] = hit
        return hit
_image = None
_hashes = {}


def object_for(source):
    rel = os.path.relpath(source, os.path.join(ROOT, 'src'))
    return os.path.join(ROOT, 'build', 'src', os.path.splitext(rel)[0] + '.obj')


def file_hash(path):
    h = _hashes.get(path)
    if h is None:
        try:
            h = hashlib.sha1(open(path, 'rb').read()).hexdigest()
        except OSError:
            h = 'missing'
        _hashes[path] = h
    return h


def unit_key(source, flags, deps):
    h = hashlib.sha1()
    h.update(CL.encode())
    h.update('\0'.join(flags).encode())
    h.update(file_hash(source).encode())
    for dep in deps:
        h.update(dep.lower().encode())
        h.update(file_hash(dep).encode())
    return h.hexdigest()


def obj_stamp(obj):
    st = os.stat(obj)
    return [st.st_size, st.st_mtime_ns]


def compile_with_deps(source, obj, flags, out):
    if source.lower().endswith('.asm'):
        # MASM stand-ins and Bink's assembly: no includes to follow
        return [] if compile_unit(source, obj, flags, out) else None
    cl, flags = split_compiler(flags)
    env = dict(os.environ)
    env['PATH'] = os.path.dirname(cl) + os.pathsep + env.get('PATH', '')
    env['INCLUDE'] = os.path.join(XDK, 'xbox', 'include')
    if '/Zi' in flags and not any(f.startswith('/Fd') for f in flags):
        flags = flags + ['/Fd' + os.path.splitext(obj)[0] + '.pdb']
    result = subprocess.run([cl] + flags + ['/showIncludes', '/Fo' + obj, source],
                            env=env, capture_output=True, text=True)
    deps, kept = [], []
    for line in result.stdout.splitlines(True):
        if line.startswith(NOTE):
            deps.append(os.path.normpath(line[len(NOTE):].strip()))
        else:
            kept.append(line)
    if result.returncode != 0:
        out.append((''.join(kept) + result.stderr).rstrip('\n'))
        return None
    return sorted(set(deps))


def check(source, rules):
    """(report lines, failures, compiled?) for one unit."""
    global _image
    if _image is None:
        _image = Xbe(os.path.join(ROOT, 'orig', 'Game_XboxMultiplayer.xbe'))
    rel = os.path.relpath(source, ROOT).replace(os.sep, '/')
    obj = object_for(source)
    state_path = os.path.splitext(obj)[0] + '.ibuild'
    os.makedirs(os.path.dirname(obj), exist_ok=True)
    flags = flags_for(rel, rules) + ['/I' + os.path.join(ROOT, 'include')]
    fresh = False
    if not os.environ.get('IBUILD_CLEAN') and os.path.exists(obj) and os.path.exists(state_path):
        try:
            state = json.load(open(state_path))
            fresh = (state['stamp'] == obj_stamp(obj)
                     and state['key'] == unit_key(source, flags, state['deps']))
        except (ValueError, KeyError, OSError):
            fresh = False
    lines = []
    if not fresh:
        if os.path.exists(state_path):
            os.remove(state_path)
        deps = compile_with_deps(source, obj, flags, lines)
        if deps is None:
            lines.append('FAIL %s: compile error' % rel)
            return lines, 1, True
        json.dump({'key': unit_key(source, flags, deps), 'deps': deps, 'stamp': obj_stamp(obj)},
                  open(state_path, 'w'))
    text = open(source).read()
    # The matches are reused while the object, the unit's text, the matching
    # tools and the names they read are unchanged and every placement range
    # start the checks looked up is still (or still not) one.
    mkey = hashlib.sha1('\0'.join([file_hash(source), json.dumps(obj_stamp(obj))]
                                  + [file_hash(p) for p in MATCH_INPUTS]).encode()).hexdigest()
    if fresh and state.get('match', {}).get('key') == mkey:
        starts = match.split_starts()
        cached = state['match']
        if all((a in starts) == hit for a, hit in cached['probes']):
            return lines + cached['lines'], cached['failures'], False
    aliases = aliases_in(text)
    coff = Coff(obj)
    failures = 0
    probe = _Probe(match.split_starts())
    match._split_starts = probe
    try:
        for name, address in MATCH_RE.findall(text):
            ok, message = compare(coff, name, int(address, 16), _image, aliases)
            lines.append(('OK   ' if ok else 'DIFF ') + message)
            failures += 0 if ok else 1
    finally:
        match._split_starts = probe.base
    state = json.load(open(state_path))
    state['match'] = {'key': mkey, 'lines': lines, 'failures': failures,
                      'probes': sorted(probe.log.items())}
    json.dump(state, open(state_path, 'w'))
    return lines, failures, not fresh


def sources_step():
    rules = load_flags()
    sources = sorted(glob.glob(os.path.join(ROOT, 'src', '**', '*.cpp'), recursive=True)
                     + glob.glob(os.path.join(ROOT, 'src', '**', '*.c'), recursive=True)
                     + glob.glob(os.path.join(ROOT, 'src', '**', '*.asm'), recursive=True))
    jobs = int(os.environ.get('BUILD_JOBS') or os.cpu_count() or 1)
    failures = compiled = 0
    with ProcessPoolExecutor(max_workers=jobs) as pool:
        for lines, failed, built in pool.map(check, sources, [rules] * len(sources)):
            if lines:
                print('\n'.join(lines))
            failures += failed
            compiled += built
    print('-- %d of %d units compiled' % (compiled, len(sources)))
    return 1 if failures else 0


def step(label, script):
    print('== %s' % label, flush=True)
    return subprocess.call([sys.executable, os.path.join(TOOLS, script)], cwd=ROOT)


def main():
    failures = 0
    failures += step('source audit', 'audit_sources.py') != 0
    failures += step('probes: compile and match', 'build_probes.py') != 0
    print('== sources: compile (changed only) and match', flush=True)
    failures += sources_step() != 0
    sys.stdout.flush()
    failures += step('placement link', 'xbelink.py') != 0
    print('== %s' % ('PASS' if not failures else 'FAIL'))
    return 1 if failures else 0


if __name__ == '__main__':
    sys.exit(main())
