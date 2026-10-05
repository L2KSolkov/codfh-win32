"""chk2.py SRC SYM ADDR MAXSTEPS CAND...: sequential compiled-out check search for long functions.
Each step: find the first differing (normalized) instruction, map it to a source line through a
/FAsc listing, then try each candidate inserted before that line and the one or two statement lines
above it (plus inline swaps drop->discard/clear, include->admit/add on those lines), in parallel;
keep the variant whose first difference is furthest (ties: fewer diff lines). Writes SRC."""
import os as _os_repo
_REPO = _os_repo.path.dirname(_os_repo.path.dirname(_os_repo.path.dirname(_os_repo.path.abspath(__file__))))  # the repository root, from this file's location
import os, re, subprocess, sys, difflib
from concurrent.futures import ThreadPoolExecutor
sys.path.insert(0, _os_repo.path.join(_REPO, r'tools'))
from build_probes import ROOT, compile_unit, flags_for, load_flags
import capstone
from coff import Coff
from xbe import Xbe

S = os.path.dirname(os.path.abspath(__file__))
src, sym, addr, maxsteps = sys.argv[1], sys.argv[2], int(sys.argv[3], 16), int(sys.argv[4])
cands = sys.argv[5:]
rel = src.replace(os.sep, '/')
flags = flags_for(rel, load_flags()) + ['/I' + os.path.join(ROOT, 'include'), '/I' + os.path.join(ROOT, os.path.dirname(src))]
W = os.path.join(ROOT, 'build', 'chk2')
os.makedirs(W, exist_ok=True)
X = Xbe(os.path.join(ROOT, 'orig', 'Game_XboxMultiplayer.xbe'))
MD = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)


def norm(i):
    s = '%s %s' % (i.mnemonic, i.op_str)
    s = re.sub(r'^(call|jmp|j\w+) .*', r'\1 X', s)
    s = re.sub(r'0x[0-9a-f]{5,}', 'A', s)
    s = re.sub(r'dword ptr \[0\]', 'dword ptr [A]', s)
    s = re.sub(r'(push|, ) ?0$', r'\1 A', s)
    s = re.sub(r'\[0x[0-9a-f]+\]', '[A]', s)
    s = re.sub(r'(\*4 \+ |\+ )0x[0-9a-f]{3,}\]', r'\1A]', s)
    return s.replace(' ', '')


def measure(text, tag, listing=False):
    p = os.path.join(W, tag + '.cpp')
    open(p, 'w', encoding='utf-8', newline='\n').write(text)
    obj = os.path.join(W, tag + '.obj')
    fl = flags + (['/FAsc', '/Fa' + os.path.join(W, tag + '.asm')] if listing else [])
    if not compile_unit(p, obj, fl, []):
        return None
    try:
        c = Coff(obj)
        code, _ = c.function_bytes(c.find_function(sym))
    except Exception:
        return None
    o = [(i.address - addr, norm(i)) for i in MD.disasm(bytes(X.read(addr, len(code) + 16)), addr)]
    u = [(i.address, norm(i)) for i in MD.disasm(bytes(code), 0)]
    first = None
    for k in range(min(len(o), len(u))):
        if o[k][1] != u[k][1]:
            first = k
            break
    sm = difflib.SequenceMatcher(None, [a[1] for a in o], [a[1] for a in u], autojunk=False)
    lines = sum((i2 - i1) + (j2 - j1) for t, i1, i2, j1, j2 in sm.get_opcodes() if t != 'equal')
    if first is None:
        return (1 << 30, 0, None) if lines == 0 else (min(len(o), len(u)), lines, None)
    return (first, lines, u[first][0])


def src_line(tag, off):
    lst = open(os.path.join(W, tag + '.asm'), errors='replace').read().splitlines()
    i = next(k for k, l in enumerate(lst) if l.startswith(sym + '\tPROC') or l.startswith(sym + ' PROC'))
    cur = last = None
    for l in lst[i:]:
        if l.startswith(sym) and 'ENDP' in l:
            break
        m = re.match(r'^; (\d+)\s*:', l)
        if m:
            cur = int(m.group(1))
            continue
        m = re.match(r'^\s+([0-9a-f]{5})\s', l)
        if m:
            if int(m.group(1), 16) > off:
                return last
            last = cur
    return cur


def variants(text, ln):
    lines = text.split('\n')
    out = []
    # the line and the statement lines above it
    targets = []
    k = ln - 1
    while k >= 0 and len(targets) < 3:
        st = lines[k].strip()
        if st and not st.startswith(('{', '}', '//', '#', 'else', 'case ', 'default')):
            prev = lines[k - 1].strip() if k else ''
            if not (re.match(r'^(else\s+)?(if|for|while)\b.*[^;{}]$', prev) or prev == 'else'):
                targets.append(k)
        k -= 1
    # before closing braces just above the line (the end of a block before an else)
    k = ln - 2
    braces = 0
    while k >= 0 and braces < 3:
        st = lines[k].strip()
        if st == '}':
            ind = lines[k][:len(lines[k]) - len(lines[k].lstrip())] + '    '
            for c in cands:
                out.append(chr(10).join(lines[:k] + [ind + c] + lines[k:]))
            braces += 1
            k -= 1
            continue
        if st.startswith('else') or st.startswith('{'):
            k -= 1
            continue
        break
    for t in targets:
        ind = lines[t][:len(lines[t]) - len(lines[t].lstrip())]
        for c in cands:
            out.append('\n'.join(lines[:t] + [ind + c] + lines[t:]))
        for a, b in (('.drop(', '.discard('), ('.drop(', '.clear('), ('.discard(', '.clear('), ('.clear(', '.discard('), ('.include(', '.admit('), ('.include(', '.add('), ('.admit(', '.add('), ('.add(', '.admit(')):
            if a in lines[t]:
                out.append('\n'.join(lines[:t] + [lines[t].replace(a, b)] + lines[t + 1:]))
    return out


text = open(os.path.join(ROOT, src), encoding='utf-8').read()
cur = measure(text, 'base', True)
print('start', cur, flush=True)
for step in range(maxsteps):
    if cur is None or cur[0] >= 1 << 30:
        break
    ln = src_line('base', cur[2])
    if ln is None:
        print('no line'); break
    vs = variants(text, ln)
    with ThreadPoolExecutor(16) as ex:
        res = list(ex.map(lambda kv: (measure(kv[1], 'v%d' % kv[0]), kv[0]), enumerate(vs)))
    res = [(m, k) for m, k in res if m]
    if not res:
        print('no variants compiled at line', ln); break
    best = max(res, key=lambda r: (r[0][0], -r[0][1]))
    if (best[0][0], -best[0][1]) <= (cur[0], -cur[1]):
        print('stuck at line', ln, 'first', cur[0], flush=True)
        break
    text = vs[best[1]]
    open(os.path.join(ROOT, src), 'w', encoding='utf-8', newline='\n').write(text)
    cur = measure(text, 'base', True)
    print('step', step, 'line', ln, '->', cur[:2], flush=True)
