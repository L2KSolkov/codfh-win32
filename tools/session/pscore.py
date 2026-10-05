"""pscore.py VARS.py SYM ADDR SRC [-j N]: compile variants of SRC in parallel and rank them by
normalized instruction diff lines against the image (lower is better), with the first
differing offset. VARS.py defines VS = {name: [(old, new), ...]} (first occurrence each);
a variant whose old string is missing is reported and skipped. Nothing in SRC is changed.
PSCORE_INC=DIR puts DIR first on the include path (trial header edits)."""
import difflib
import os
import re
import sys
from concurrent.futures import ThreadPoolExecutor

S = os.path.dirname(os.path.abspath(__file__))
ROOT = os.path.dirname(os.path.dirname(S))
sys.path.insert(0, os.path.join(ROOT, 'tools'))
from build_probes import compile_unit, flags_for, load_flags  # noqa: E402
from coff import Coff  # noqa: E402
from xbe import Xbe  # noqa: E402
import capstone  # noqa: E402

MD = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)
W = os.path.join(ROOT, 'build', 'tooltmp', 'pscore')
os.makedirs(W, exist_ok=True)


def norm(i):
    s = '%s %s' % (i.mnemonic, i.op_str)
    s = re.sub(r'^(call|jmp|j\w+) .*', r'\1 X', s)
    s = re.sub(r'0x[0-9a-f]{5,}', 'A', s)
    s = re.sub(r'\[0\]', '[A]', s)
    s = re.sub(r'\[0x[0-9a-f]+\]', '[A]', s)
    s = re.sub(r'(\*4 \+ |\*8 \+ |\+ )0x[0-9a-f]{3,}\]', r'\1A]', s)
    s = re.sub(r'(push|, ) ?0$', r'\1 A', s)
    return s.replace(' ', '')


def main():
    args = sys.argv[1:]
    jobs = 12
    if '-j' in args:
        k = args.index('-j')
        jobs = int(args[k + 1])
        del args[k:k + 2]
    varf, sym, addr, src = args[0], args[1], int(args[2], 16), args[3]
    g = {}
    exec(open(varf, encoding='utf-8').read(), g)
    vs = g['VS']
    text = open(os.path.join(ROOT, src), encoding='utf-8').read()
    rel = src.replace(os.sep, '/')
    # PSCORE_INC: an overlay include directory searched first (trial header edits).
    overlay = ['/I' + os.environ['PSCORE_INC']] if os.environ.get('PSCORE_INC') else []
    flags = overlay + flags_for(rel, load_flags()) + ['/I' + os.path.join(ROOT, os.path.dirname(src)),
                                            '/I' + os.path.join(ROOT, 'include')]
    ext = os.path.splitext(src)[1]
    x = Xbe(os.path.join(ROOT, 'orig', 'Game_XboxMultiplayer.xbe'))
    cache = {}

    def run(item):
        name, edits = item
        t = text
        for old, new in edits:
            if old not in t:
                return (None, name, 'missing: %r' % old[:50])
            t = t.replace(old, new, 1)
        p = os.path.join(W, 'v_%s%s' % (name, ext))
        open(p, 'w', encoding='utf-8', newline='\n').write(t)
        obj = os.path.join(W, 'v_%s.obj' % name)
        out = []
        if not compile_unit(p, obj, flags, out):
            return (None, name, 'compile error %s' % [l for l in out if 'error' in l][:1])
        c = Coff(obj)
        code, _ = c.function_bytes(c.find_function(sym))
        n = len(code)
        if n not in cache:
            cache[n] = [norm(i) for i in MD.disasm(bytes(x.read(addr, n)), addr)]
        o = cache[n]
        u = [norm(i) for i in MD.disasm(bytes(code), 0)]
        first = next((k for k in range(min(len(o), len(u))) if o[k] != u[k]), min(len(o), len(u)))
        sm = difflib.SequenceMatcher(None, o, u, autojunk=False)
        lines = sum((i2 - i1) + (j2 - j1) for tg, i1, i2, j1, j2 in sm.get_opcodes() if tg != 'equal')
        return (lines, name, 'first insn %d' % first)

    with ThreadPoolExecutor(jobs) as ex:
        res = list(ex.map(run, sorted(vs.items())))
    for r in sorted(res, key=lambda r: (r[0] is None, r[0] or 0)):
        print(r[0], r[1], r[2])


if __name__ == '__main__':
    main()
