"""replayf.py SOURCE ADDR... : commit the listed (already written, matched)
functions of SOURCE one per commit, in the order given. Everything else must
already be committed. A function's block runs from its `// match:` line to
the next function's, and annotations of generated pieces heading it
(EH funclets, handlers, a scalar deleting destructor) go with it."""
import os as _os_repo
_REPO = _os_repo.path.dirname(_os_repo.path.dirname(_os_repo.path.abspath(__file__)))  # the repository root, from this file's location
import re
import subprocess
import sys

CFG = _os_repo.path.join(_REPO, r'config\compiled.txt')
HEADER = re.compile(r'\n// match: (__ehhandler|\.text|\?\?_G)')


def block(text, a):
    m = re.search(r'^// match: \S+ @ 0x0*%s\n' % a, text, re.M)
    assert m, a
    start = m.start()
    # a scalar deleting destructor's annotation just above belongs here too
    while True:
        prev = text.rfind('\n// match: ??_G', 0, start - 1)
        if prev >= 0 and text[prev + 1:start].count('\n') == 1:
            start = prev + 1
        else:
            break
    n = text.find('\n// match: ', m.end() - 1)
    while n >= 0 and HEADER.match(text, n):
        n = text.find('\n// match: ', n + 1)
    if n >= 0:
        end = n + 1
    else:
        # the last function: its block ends with its own body (a
        # namespace's closing brace after it stays), or with its line when
        # it has none (a compiler-generated thunk)
        rest = text[m.end():]
        k = m.end()
        while text.startswith('// match: ', k):
            k = text.index('\n', k) + 1
        if re.match(r'\s*\}\s*$', text[k:]):
            end = k
        else:
            e = text.find('\n}\n', k)
            end = e + 3 if e >= 0 else len(text)
    return start, end


def drop(text, cfg, a):
    start, end = block(text, a)
    addrs = re.findall(r'^// match: \S+ @ 0x0*([0-9A-F]+)$', text[start:end], re.M)
    cfg = ''.join(l for l in cfg.splitlines(True)
                  if not any(re.match(r'0x0*%s ' % x, l) for x in addrs))
    return text[:start] + text[end:], cfg


def qual(text, a):
    # only within the function's own block: a bare match line (a function
    # defined in a header, or a library one) is named by its symbol
    start, end = block(text, a)
    blk = text[start:end]
    m = re.search(r'// match: \S+ @ 0x0*%s\n(?://[^\n]*\n)*[^\n(]*?(\w+)::(sub_%s|vf_\w+|~?\w+)\('
                  % (a, a), blk)
    if m:
        return m.group(1) + '::' + m.group(2)
    m = re.search(r'// match: (\S+) @ 0x0*%s\n(?://[^\n]*\n)*(\w[^\n(]*?(\w+)\()?' % a, blk)
    if m and m.group(3) and m.group(3) == 'sub_%s' % a:
        return m.group(3)
    return m.group(1) if m else 'sub_%s' % a


import time


def wr(path, text, enc='utf-8'):
    for attempt in range(20):
        try:
            open(path, 'w', encoding=enc, newline='').write(text)
            return
        except OSError:
            time.sleep(0.5)
    raise


def git(cmd):
    # another git process (an editor's status poll) may hold .git/index.lock a moment
    for attempt in range(40):
        r = subprocess.run(cmd, capture_output=True, text=True)
        if r.returncode == 0:
            return
        if 'index.lock' not in r.stderr:
            sys.stderr.write(r.stderr)
            raise subprocess.CalledProcessError(r.returncode, cmd)
        time.sleep(0.25)
    raise subprocess.CalledProcessError(r.returncode, cmd)


src = sys.argv[1]
addrs = [a.upper() for a in sys.argv[2:]]
try:
    full = open(src, encoding='utf-8').read()
    SENC = 'utf-8'
except UnicodeDecodeError:
    full = open(src, encoding='latin-1').read()
    SENC = 'latin-1'
fullc = open(CFG, encoding='utf-8').read()
for k, a in enumerate(addrs):
    s, c = full, fullc
    for later in addrs[k + 1:]:
        s, c = drop(s, c, later)
    s = s.rstrip('\n') + '\n'
    wr(src, s, SENC)
    wr(CFG, c)
    git(['git', 'add', src, CFG])
    git(['git', 'commit', '-q', '-m',
                           'match: recover %s\n\nCo-Authored-By: Claude Opus 5.5 '
                           '<noreply@anthropic.com>\n' % qual(full, a)])
assert open(src, encoding=SENC).read() == full.rstrip('\n') + '\n'
assert open(CFG, encoding='utf-8').read() == fullc
print('committed', len(addrs))
