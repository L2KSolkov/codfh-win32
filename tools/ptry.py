"""ptry.py VARS.py SYM ADDR SRC [-j N] [-m]: like vtry.py, but compiles the variants
in parallel (N workers, default 8) and prints them sorted by ncmp score.
With -m the score is match.py's instead: 0 for identical, else the bytes
from the first difference (byte or relocation target) to the end, which
ncmp's masking cannot see (which global or field an operand names).

VARS.py defines VS = {name: [(old, new), ...]}; each variant is applied to a
copy of SRC (first occurrence of each old string) and compiled with SRC's
flags."""
import os
import subprocess
import sys
import tempfile
from concurrent.futures import ThreadPoolExecutor

S = os.path.dirname(os.path.abspath(__file__))
ROOT = os.path.dirname(S)
sys.path.insert(0, S)
from build_probes import compile_unit, flags_for, load_flags  # noqa: E402
import ncmp  # noqa: E402

W = os.path.join(ROOT, 'build', 'tooltmp', 'ptry')
os.makedirs(W, exist_ok=True)


def main():
    args = sys.argv[1:]
    jobs = 8
    use_match = '-m' in args
    if use_match:
        args.remove('-m')
    if '-j' in args:
        i = args.index('-j')
        jobs = int(args[i + 1])
        del args[i:i + 2]
    varf, sym, addr, src = args[0], args[1], int(args[2], 16), args[3]
    g = {}
    exec(open(varf, encoding='utf-8').read(), g)  # VARS files read their sources themselves
    try:
        enc = 'utf-8'
        base = open(os.path.join(ROOT, src), encoding=enc).read()
    except UnicodeDecodeError:
        enc = 'latin-1'
        base = open(os.path.join(ROOT, src), encoding=enc).read()
    fl = flags_for(src.replace('\\', '/'), load_flags())
    k = next((n for n, f in enumerate(fl) if f.startswith('/I')), len(fl))
    fl = fl[:k] + ['/I' + os.path.join(ROOT, os.path.dirname(src))] + fl[k:]
    if not any(f.startswith('/I') and f.rstrip('/' + chr(92)).endswith('include') for f in fl):
        fl = fl + ['/I' + os.path.join(ROOT, 'include')]  # the game's units (build_sources adds it)
    ext = os.path.splitext(src)[1]

    def run(item):
        name, reps = item
        t = base
        for o, n in reps:
            if o not in t:
                return (10 ** 9, name, 'MISSING')
            t = t.replace(o, n, 1)
        p = os.path.join(W, 'p_%s%s' % (name, ext))
        open(p, 'w', encoding=enc).write(t)
        obj = os.path.join(W, 'p_%s.obj' % name)
        out = []
        if not compile_unit(p, obj, fl + ['/c'] if '/c' not in fl else fl, out):
            return (10 ** 9, name, 'COMPILE ERROR')
        if use_match:
            import re as _re
            import match as _match
            ok, msg = _match.compare(obj, sym, addr, image)
            if ok:
                return (0, name, '')
            m = _re.search(r'at \+0x([0-9A-Fa-f]+)', msg)
            code = _match.Coff(obj).function_bytes(_match.Coff(obj).find_function(sym))[0]
            return ((len(code) - int(m.group(1), 16)) if m else 10 ** 6, name, msg.split(': ', 1)[-1][:60])
        return (ncmp.score(obj, sym, addr), name, '')

    ncmp._img()  # load the image and symbol sizes once, before the workers
    image = None
    if use_match:
        import match as _match
        image = _match.Xbe(_match.ORIGINAL)
    with ThreadPoolExecutor(jobs) as ex:
        res = sorted(ex.map(run, g['VS'].items()))
    for sc, name, note in res[:40]:
        print(sc, name, note)


if __name__ == '__main__':
    main()
