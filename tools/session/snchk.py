"""snchk.py SRC "FUNC HEADER LINE START" SYM ADDR [CAND ...]: greedy compiled-out check insertion.
Each round tries every single insertion of each candidate check before each statement line of the
function (ptry -m), applies the best if it improves the score, and repeats."""
import os as _os_repo
_REPO = _os_repo.path.dirname(_os_repo.path.dirname(_os_repo.path.dirname(_os_repo.path.abspath(__file__))))  # the repository root, from this file's location
import os, re, subprocess, sys
ROOT = _REPO
src, head, sym, addr = sys.argv[1:5]
cands = sys.argv[5:] or ['if (!unk_00) { }', 'if (!unk_00) { } if (!unk_00) { }', 'if (!(arg_4 & 1)) { }',
                         'if (!this) { }']
VF = os.path.join(os.path.dirname(os.path.abspath(__file__)), 'snchk_vars.py')


def run(text):
    a = text.index(head)
    b = text.index('\n}\n', a)
    lines = text[a:b].split('\n')
    VS = {'base': []}
    for k in range(2, len(lines)):
        st = lines[k].strip()
        prev = lines[k - 1].strip()
        if not st or st.startswith(('{', '}', '#', '//', 'else')) or (prev.startswith('#line') and k >= 2 and re.match(r'^(if|for|while).*[^;{}]$', lines[k - 2].strip())) or re.match(r'^(else\s+)?(if|for|while)\b.*[^;{}]$', prev) or prev == 'else':
            continue
        ind = re.match(r'^(\s*)', lines[k]).group(1)
        at = k - 1 if prev.startswith('#line') else k
        for ci, c in enumerate(cands):
            new = lines[:at] + [ind + c] + lines[at:]
            VS['p%d_%d' % (k, ci)] = [(text[a:b], '\n'.join(new))]
    open(VF, 'w').write('VS = %r\n' % VS)
    out = subprocess.run([sys.executable, ROOT + '/tools/ptry.py', VF, sym, addr, src, '-m', '-j', '16'],
                         capture_output=True, text=True, cwd=ROOT).stdout.strip().split('\n')
    res = []
    for l in out:
        p = l.split(None, 2)
        if len(p) >= 2 and p[0].isdigit():
            res.append((int(p[0]), p[1]))
    return VS, res


text = open(os.path.join(ROOT, src), encoding='utf-8').read()
for rnd in range(12):
    VS, res = run(text)
    base = dict((n, s) for s, n in res).get('base', 1 << 30)
    best = min(res)
    print('round', rnd, 'base', base, 'best', best)
    if best[0] >= base:
        break
    (o, n), = VS[best[1]]
    text = text.replace(o, n, 1)
    open(os.path.join(ROOT, src), 'w', encoding='utf-8', newline='\n').write(text)
    if best[0] == 0:
        break
