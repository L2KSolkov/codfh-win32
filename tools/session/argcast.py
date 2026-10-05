"""argcast.py SRC...: cast the arguments VC7.1 cannot convert (C2664) to the parameter's type
(PLAN M7: readers brought to a definition's prototype; the full build decides whether the
calls still compile to the same bytes).

Compiles SRC (cc1's way), takes every "error C2664: 'F' : cannot convert parameter N from 'X' to
'T'", finds the call F( on that line (or the lines it continues on), and wraps argument N in
(T). Repeats until SRC compiles or nothing changes."""
import os
import re
import sys

sys.path.insert(0, os.path.join(os.path.dirname(os.path.abspath(__file__)), '..'))
from build_probes import flags_for, load_flags  # noqa: E402
from ibuild import compile_with_deps  # noqa: E402

ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
ERR = re.compile(r"\((\d+)\) : error C2664: '(\w+)' : cannot convert parameter (\d+) from '[^']*' to '([^']*)'")
rules = load_flags()


def errors(src):
    rel = os.path.relpath(os.path.abspath(src), ROOT).replace(os.sep, '/')
    obj = os.path.join(ROOT, 'build', 'tooltmp', 'argcast.obj')
    out = []
    ok = compile_with_deps(os.path.abspath(src), obj, flags_for(rel, rules) + ['/I' + os.path.join(ROOT, 'include')], out) is not None
    return ok, [(int(m.group(1)), m.group(2), int(m.group(3)), m.group(4)) for m in ERR.finditer('\n'.join(out))], out


def args_span(t, start):
    """[(begin, end)] of the top-level arguments of the call whose '(' is at start."""
    depth, i, spans, b = 0, start, [], start + 1
    while i < len(t):
        c = t[i]
        if c in '([':
            depth += 1
        elif c in ')]':
            depth -= 1
            if depth == 0:
                spans.append((b, i))
                return spans
        elif c == ',' and depth == 1:
            spans.append((b, i))
            b = i + 1
        i += 1
    return None


def fix(src):
    for _ in range(10):
        ok, errs, out = errors(src)
        if ok:
            print('%s: ok' % src)
            return True
        if not errs:
            print('%s: other errors' % src)
            print('\n'.join(l for l in out if 'error' in l)[:1500])
            return False
        raw = open(src, 'rb').read().decode('utf-8', errors='surrogateescape')
        nl = '\r\n' if '\r\n' in raw else '\n'
        t = raw.replace('\r\n', '\n')
        lines = t.split('\n')
        # apply bottom-up so offsets stay valid
        for line, fn, n, ty in sorted(set(errs), reverse=True):
            off = sum(len(l) + 1 for l in lines[:line - 1])
            m = re.compile(r'\b%s\s*\(' % re.escape(fn)).search(t, off)
            if not m:
                continue
            spans = args_span(t, m.end() - 1)
            if not spans or n > len(spans):
                continue
            b, e = spans[n - 1]
            arg = t[b:e]
            lead = len(arg) - len(arg.lstrip())
            core = arg.strip()
            # a simple operand takes the cast as it is; anything else is parenthesized
            simple = re.match(r'^&?\w+((\.|->)\w+|\[[^\]]*\])*$', core)
            cast = '(%s)%s' % (ty, core if simple else '(%s)' % core)
            t = t[:b] + arg[:lead] + cast + arg[lead + len(core):] + t[e:]
            lines = t.split('\n')
        open(src, 'wb').write(t.replace('\n', nl).encode('utf-8', errors='surrogateescape'))
    return False


ok = [fix(s) for s in sys.argv[1:]]
sys.exit(0 if all(ok) else 1)
