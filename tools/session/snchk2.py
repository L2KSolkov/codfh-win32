"""snchk2.py SRC "FUNC HEADER(" SYM ADDR WINDOW CAND...: windowed greedy compiled-out check insertion
for long functions. Metric: odiff changed-line count. Each round tries each candidate before each
statement line in a window of WINDOW statement lines starting at the cursor; applies the best if it
improves, moving the cursor to it; if nothing improves, the window slides on by half its size."""
import os as _os_repo
_REPO = _os_repo.path.dirname(_os_repo.path.dirname(_os_repo.path.dirname(_os_repo.path.abspath(__file__))))  # the repository root, from this file's location
import glob, os, re, subprocess, sys
ROOT = _REPO
HERE = os.path.dirname(os.path.abspath(__file__))
src, head, sym, addr, window = sys.argv[1:6]
window = int(window)
cands = sys.argv[6:]
VF = os.path.join(HERE, 'snchk2_vars.py')
PFX = 'w2'


sys.path.insert(0, ROOT + '/tools')
import difflib, capstone
from coff import Coff
from xbe import Xbe
_X = Xbe(ROOT + '/orig/Game_XboxMultiplayer.xbe')
_MD = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)
_ORIG = {}


def _norm(i):
    s = '%s %s' % (i.mnemonic, i.op_str)
    s = re.sub(r'^(call|jmp|j\w+) .*', r'\1 X', s)
    s = re.sub(r'0x[0-9a-f]{5,}', 'A', s)
    s = re.sub(r'dword ptr \[0\]', 'dword ptr [A]', s)
    s = re.sub(r'(push|, ) ?0$', r'\1 A', s)
    return s


def score(obj):
    try:
        c = Coff(obj)
        code, _ = c.function_bytes(c.find_function(sym))
    except Exception:
        return 1 << 30
    a0 = int(addr, 16)
    n = len(code) + 16
    if n not in _ORIG:
        _ORIG[n] = [_norm(i) for i in _MD.disasm(bytes(_X.read(a0, n)), a0)]
    o = _ORIG[n]
    u = [_norm(i) for i in _MD.disasm(bytes(code), 0)]
    sm = difflib.SequenceMatcher(None, o, u, autojunk=False)
    lines = sum((i2 - i1) + (j2 - j1) for tag, i1, i2, j1, j2 in sm.get_opcodes() if tag != 'equal')
    if os.environ.get('FIRSTDIFF'):
        first = len(o)
        for k in range(min(len(o), len(u))):
            if o[k] != u[k]:
                first = k
                break
        return (-first) * 100000 + lines
    return lines


def positions(text):
    a = text.index(head)
    b = text.index('\n}\n', a)
    lines = text[a:b].split('\n')
    res = []
    for k in range(2, len(lines)):
        st = lines[k].strip()
        prev = lines[k - 1].strip()
        if not st or st.startswith(('{', '}', '#', '//', 'else', 'case ', 'default')):
            continue
        if re.match(r'^(else\s+)?(if|for|while)\b.*[^;{}]$', prev) or prev == 'else' or prev.endswith(','):
            continue
        if prev.startswith('#line'):
            continue
        res.append(k)
    return a, b, lines, res


text = open(os.path.join(ROOT, src), encoding='utf-8').read()
cursor = 0
if os.environ.get('START'):
    _a, _b, _lines, _pos = positions(text)
    _hits = [i for i, p in enumerate(_pos) if os.environ['START'] in _lines[p]]
    cursor = max(0, _hits[int(os.environ.get('STARTN', '0'))] - 2)
rnd = 0
while True:
    a, b, lines, pos = positions(text)
    if cursor >= len(pos):
        break
    win = pos[cursor:cursor + window]
    VS = {'base': []}
    for k in win:
        ind = re.match(r'^(\s*)', lines[k]).group(1)
        for ci, c in enumerate(cands):
            new = lines[:k] + [ind + c] + lines[k:]
            VS['%s_%d_%d' % (PFX, k, ci)] = [(text[a:b], '\n'.join(new))]
    open(VF, 'w').write('VS = %r\n' % VS)
    subprocess.run([sys.executable, ROOT + '/tools/ptry.py', VF, sym, addr, src, '-j', '16'],
                   capture_output=True, text=True, cwd=ROOT)
    res = []
    for name in VS:
        obj = os.path.join(ROOT, 'build', 'tooltmp', 'ptry', 'p_%s.obj' % name)
        if os.path.exists(obj):
            res.append((score(obj), name))
    base = dict((n, s) for s, n in res).get('base', 1 << 30)
    best = min(res)
    rnd += 1
    print('round', rnd, 'cursor', cursor, 'base', base, 'best', best, flush=True)
    if best[0] < base:
        (o, n), = VS[best[1]]
        text = text.replace(o, n, 1)
        open(os.path.join(ROOT, src), 'w', encoding='utf-8', newline='\n').write(text)
        k = int(best[1].split('_')[1])
        a, b, lines, pos = positions(text)
        cursor = max(0, max(i for i, p in enumerate(pos) if p <= k + 1) - 1)
        if best[0] == 0:
            break
    else:
        cursor += max(1, window // 2)
