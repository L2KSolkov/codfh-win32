"""macvar.py: try store orders of RwXboxSetCachedRenderState; score each
annotated function in xbrendst.c per variant; restore the header."""
import os as _os_repo
_REPO = _os_repo.path.dirname(_os_repo.path.dirname(_os_repo.path.abspath(__file__)))  # the repository root, from this file's location
import os
import re
import subprocess
import sys

S = os.path.dirname(os.path.abspath(__file__))
W = os.path.join(os.path.dirname(S), 'build', 'tooltmp')  # work files
os.makedirs(W, exist_ok=True)

H = _os_repo.path.join(_REPO, r'src\rw\driver\xbox\xbrendst.h')
F = 'src/rw/driver/xbox/xbrendst.c'
sys.path.insert(0, S)
import ncmp  # noqa: E402

orig = open(H, encoding='utf-8', newline='').read()
L = '        _RwXbRenderStateCacheList[_RwXbRenderStateCacheCount] = (state);    \\\r\n'
D = '        _RwXbRenderStateCacheDirty[(state)] = TRUE;                         \\\r\n'
C = '        _RwXbRenderStateCacheCount++;                                       \\\r\n'
LC = '        _RwXbRenderStateCacheList[_RwXbRenderStateCacheCount++] = (state);  \\\r\n'
base = L + D + C
assert base in orig
variants = {'LDC': base, 'DLC': D + L + C, 'D(LC)': D + LC, '(LC)D': LC + D, 'LCD': L + C + D}
src = open(os.path.join(_REPO, F), encoding='utf-8').read()
rows = re.findall(r'// match: (\S+) @ 0x00(\w+)', src)
os.chdir(_REPO)
try:
    for name, body in variants.items():
        open(H, 'w', encoding='utf-8', newline='').write(orig.replace(base, body))
        r = subprocess.run([sys.executable, os.path.join(S, 'fdiff.py'), F, F] +
                           ['%s:%s' % (s, a) for s, a in rows], capture_output=True, text=True)
        out = []
        for s, a in rows:
            n = ncmp.score(os.path.join(W, 'fdiff.obj'), s, int(a, 16))
            if n:
                out.append('%s=%s' % (s, n))
        print(name, ' '.join(out))
finally:
    open(H, 'w', encoding='utf-8', newline='').write(orig)
