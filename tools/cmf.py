"""cmf.py: cm.py with incremental builds (ibuild.py), and without the final
rebuild when the tree is byte-identical to the one the first build passed.

cm.py [-m "header commit message"] ADDR...: commit matched functions of
the unit CMUNIT (default unit_0441B0). First builds the whole tree with the
listed functions placed (their compiled.txt rows added), so the audit and the
placement link must pass before anything is committed. With -m, then commits
everything else (include/, docs/, aliases and the unit without the listed
functions) after a passing build. Then adds the rows in address order,
replays one commit per function, builds again, and pushes. Stops at the
first failure (nonzero exit)."""
import os as _os_repo
_REPO = _os_repo.path.dirname(_os_repo.path.dirname(_os_repo.path.abspath(__file__)))  # the repository root, from this file's location
import os
import re
import subprocess
import sys

ROOT = _REPO
UNITN = os.environ.get('CMUNIT', 'unit_0441B0')
REL = UNITN if '/' in UNITN else 'recovered/' + UNITN
EXT = '.c' if os.path.exists(os.path.join(ROOT, 'src', *(REL + '.c').split('/'))) else '.cpp'
UNIT = os.path.join(ROOT, 'src', *(REL + EXT).split('/'))
CFG = ROOT + r'\config\compiled.txt'
try:
    open(UNIT, encoding='utf-8').read()
    UENC = 'utf-8'
except UnicodeDecodeError:
    UENC = 'latin-1'
S = os.path.dirname(os.path.abspath(__file__))
W = os.path.join(os.path.dirname(S), 'build', 'tooltmp')  # work files
os.makedirs(W, exist_ok=True)

TRAILER = '\n\nCo-Authored-By: Claude Opus 5.5 <noreply@anthropic.com>'


def run(cmd, **kw):
    r = subprocess.run(cmd, cwd=ROOT, shell=isinstance(cmd, str), **kw)
    if r.returncode:
        sys.exit('failed: %s' % cmd)


def build():
    with open(W + r'\blog.txt', 'w') as f:
        subprocess.run(['python', S + r'\ibuild.py'], cwd=ROOT, stdout=f, stderr=subprocess.STDOUT)
    log = open(W + r'\blog.txt').read()
    if '== PASS' not in log:
        bad = [l for l in log.splitlines()
               if l.startswith(('DIFF', 'AUDIT', 'FAIL', 'ERROR', 'link error'))]
        sys.exit('build failed:\n' + '\n'.join(bad[:20] or log.splitlines()[-15:]))


def strip(text, addrs):
    for a in addrs:
        m = re.search(r'^// match: \S+ @ 0x0*%s\n' % a, text, re.M)
        assert m, a
        if text.startswith(('\n', '// match: '), m.end()):
            # a bodiless piece (data, an initializer): just its line
            text = text[:m.start()] + text[m.end():]
            continue
        n = text.find('\n// match: ', m.end() - 1)
        while n >= 0 and text.startswith('\n// match: __ehhandler', n):
            n = text.find('\n// match: ', n + 1)
        if n < 0:
            # the last function: keep what follows its body (a namespace's
            # closing brace); a bodiless annotation (a thunk) is just dropped
            k = m.end()
            while text.startswith('// match: ', k):
                k = text.index('\n', k) + 1
            if re.match(r'\s*\}?\s*$', text[k:]):
                text = text[:m.start()] + text[k:].lstrip('\n')
            else:
                e = text.find('\n}\n', k)
                text = text[:m.start()] + text[e + 3:].lstrip('\n')
        else:
            text = text[:m.start()] + text[n + 1:]
    return text


def insert_row(cfg, row, v):
    lower = [l for l in cfg if l.startswith('0x') and int(l.split()[0], 16) < v]
    if not lower:
        first = next(l for l in cfg if l.startswith('0x'))
        cfg.insert(cfg.index(first), row)
        return
    after = max(lower, key=lambda l: int(l.split()[0], 16))
    cfg.insert(cfg.index(after) + 1, row)


def listed(full, addrs):
    # the listed functions' addresses, with the EH pieces annotated under them
    out = []
    for a in addrs:
        m = re.search(r'^// match: \S+ @ 0x0*%s\n((?:// match: __ehhandler\S* @ 0x\w+\n)*)' % a,
                      full, re.M)
        out.append(int(a, 16))
        out += [int(ad, 16) for ad in re.findall(r'@ 0x(\w+)', m.group(1))]
    return out


def without(cfg, full, addrs):
    # drops existing rows at the listed addresses (a renamed symbol's old row)
    vs = set(listed(full, addrs))
    return [l for l in cfg if not (l.startswith('0x') and int(l.split()[0], 16) in vs)]


def with_rows(cfg, full, addrs):
    cfg = without(cfg, full, addrs)
    for a in addrs:
        nm = re.search(r'^// match: (\S+) @ 0x0*%s\n' % a, full, re.M).group(1)
        row = '0x%08X build/src/%s.obj %s\n' % (int(a, 16), REL, nm)
        if row not in cfg:
            insert_row(cfg, row, int(a, 16))
    # EH funclets and handlers annotated under each function's match line
    for a in addrs:
        m = re.search(r'^// match: \S+ @ 0x0*%s\n((?:// match: __ehhandler\S* @ 0x\w+\n)*)' % a,
                      full, re.M)
        for name, ad in re.findall(r'// match: (\S+) @ 0x(\w+)', m.group(1)):
            row = '0x%08X build/src/%s.obj %s\n' % (int(ad, 16), REL, name)
            if row not in cfg:
                insert_row(cfg, row, int(ad, 16))
    return cfg


def main():
    args = sys.argv[1:]
    msg = None
    head_unit = False
    if args[0] == '-H':
        head_unit, args = True, args[1:]
    if args[0] == '-m':
        msg, args = args[1], args[2:]
    addrs = [a.upper()[2:] if a.upper().startswith('0X') else a.upper() for a in args]
    full = open(UNIT, encoding=UENC).read()
    # EH pieces go with their function's match line: drop any listed on their own
    addrs = [a for a in addrs
             if not re.search(r'^// match: __ehhandler\S* @ 0x0*%s\n' % a, full, re.M)]
    for a in addrs:
        assert re.search(r'^// match: \S+ @ 0x0*%s\n' % a, full, re.M), 'no match line for ' + a
    cfg0 = open(CFG).read()
    rows0 = ''.join(with_rows(cfg0.splitlines(True), full, addrs))
    open(CFG, 'w', newline='\n').write(rows0)
    try:
        build()
    finally:
        open(CFG, 'w', newline='\n').write(cfg0)
    if msg:
        if head_unit:
            # the committed unit (its unmatched body of a listed function still
            # instantiates what other matched functions need)
            old = subprocess.run(['git', 'show', 'HEAD:src/%s%s' % (REL, EXT)], cwd=ROOT,
                                 capture_output=True).stdout
            # HEAD's bytes as they are (its encoding may differ from the working copy's)
            open(UNIT, 'wb').write(old)
        else:
            stripped = strip(full, addrs)
            open(UNIT, 'w', encoding=UENC, newline='\n').write(stripped)
        open(CFG, 'w', newline='\n').write(''.join(without(cfg0.splitlines(True), full, addrs)))
        try:
            build()
            run('git add tools/xbelink.py tools/climb_names.py include docs config/aliases.txt config/splits.txt config/symbols.txt config/compiled.txt src/recovered/*.cpp src/Source src/rws src/rw include/rw/sdk')
            run(['git', 'commit', '-q', '-m', msg + TRAILER])
        finally:
            open(UNIT, 'w', encoding=UENC, newline='\n').write(full)
    cfg = with_rows(open(CFG).read().splitlines(True), full, addrs)
    open(CFG, 'w', newline='\n').write(''.join(cfg))
    # a deleting destructor's annotation heads its destructor's block
    replay = [a for a in addrs
              if not re.search(r'^// match: \?\?_G\S* @ 0x0*%s\n' % a, full, re.M)]
    run(['python', S + r'\replayf.py', 'src/%s%s' % (REL, EXT)] + replay)
    # the first build passed exactly this tree: rebuild only if anything differs
    if (open(CFG).read() != rows0 or open(UNIT, encoding=UENC).read() != full
            or subprocess.run(['git', 'status', '--porcelain', '--untracked-files=no', '--',
                               'src', 'include', 'config'],
                              cwd=ROOT, capture_output=True, text=True).stdout.strip()):
        build()
    run('git push -q origin master')
    print('pushed', ' '.join(addrs))


main()
