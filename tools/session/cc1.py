"""cc1.py SOURCE...: compile sources alone (their build flags) into build/tooltmp and print the errors."""
import os
import sys

sys.path.insert(0, os.path.join(os.path.dirname(os.path.abspath(__file__)), '..'))
from build_probes import flags_for, load_flags  # noqa: E402
from ibuild import compile_with_deps  # noqa: E402

ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
rules = load_flags()
for src in sys.argv[1:]:
    src = os.path.abspath(src)
    rel = os.path.relpath(src, ROOT).replace(os.sep, '/')
    out = []
    obj = os.path.join(ROOT, 'build', 'tooltmp', 'cc1.obj')
    os.makedirs(os.path.dirname(obj), exist_ok=True)
    ok = compile_with_deps(src, obj, flags_for(rel, rules) + ['/I' + os.path.join(ROOT, 'include')], out) is not None
    print('==', rel, 'ok' if ok else 'FAILED')
    for l in '\n'.join(out).splitlines():
        if 'error' in l:
            print('  ', l.strip()[:220])
