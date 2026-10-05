"""cvtry.py FILE SYM ADDR VARFILE: C-unit variant trials. VARFILE holds variants
separated by lines '#####'; each variant is srep blocks (old / ----- / new /
=====). Each variant is compiled to its own object in a copy beside FILE (so
includes resolve) and scored with ncmp.score; FILE itself is never touched."""
import os as _os_repo
_REPO = _os_repo.path.dirname(_os_repo.path.dirname(_os_repo.path.abspath(__file__)))  # the repository root, from this file's location
import fnmatch
import os
import sys
from concurrent.futures import ThreadPoolExecutor

sys.path.insert(0, _os_repo.path.join(_REPO, r'tools'))
S = os.path.dirname(os.path.abspath(__file__))
W = os.path.join(os.path.dirname(S), 'build', 'tooltmp')  # work files
os.makedirs(W, exist_ok=True)

sys.path.insert(0, S)
os.chdir(_REPO)
from build_probes import compile_unit  # noqa: E402
import ncmp  # noqa: E402

src, sym, addr, varf = sys.argv[1], sys.argv[2], int(sys.argv[3], 16), sys.argv[4]
text = open(src, encoding='utf-8').read().replace('\r\n', '\n')
rules = []
for l in open('config/flags.txt'):
    if ':' in l and not l.startswith('#'):
        pat, fl = l.split(':', 1)
        rules.append((pat.strip(), fl.split()))
fl = [f for p, f in rules if fnmatch.fnmatch(src, p)][0]
i = next(k for k, f in enumerate(fl) if f.startswith('/I'))
fl = fl[:i] + ['/I' + os.path.abspath(os.path.dirname(src))] + fl[i:]
out = os.path.join(W, 'cvtry')
os.makedirs(out, exist_ok=True)
variants = [v for v in open(varf, encoding='utf-8').read().split('#####\n')]


def run(k):
    t = text
    for blk in variants[k].split('=====\n'):
        if '-----\n' not in blk:
            continue
        a, b = blk.split('-----\n', 1)
        if a not in t:
            return k, 'NOT FOUND ' + a[:40].replace('\n', '|')
        t = t.replace(a, b, 1)
    ext = os.path.splitext(src)[1]
    cx = os.path.join(out, 'v%d%s' % (k, ext))
    ob = os.path.join(out, 'v%d.obj' % k)
    open(cx, 'w', encoding='utf-8').write(t)
    msgs = []
    if not compile_unit(cx, ob, fl, out=msgs):
        return k, 'COMPILE ERROR ' + ' '.join(l for l in msgs if 'error' in l)[:300]
    return k, ncmp.score(ob, sym, addr)


with ThreadPoolExecutor(8) as ex:
    for k, r in ex.map(run, range(len(variants))):
        print(k, r, flush=True)
