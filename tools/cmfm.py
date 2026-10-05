"""cmfm.py: cmf.py for several units at once (one gate build for the batch).

    python tools/cmfm.py [-m "header commit message"] UNIT:ADDR[,ADDR...] ...

UNIT is as for cmf's CMUNIT (unit_0DC400, or a path under src/ without its
extension). Builds the whole tree with every listed function placed; with -m,
then commits everything else (each unit without its listed functions) after a
passing build; then replays one commit per function, unit by unit in the
order given, builds again only if the tree differs from the one that passed,
and pushes once. Stops at the first failure (nonzero exit)."""
import os
import re
import subprocess
import sys
import time

S = os.path.dirname(os.path.abspath(__file__))
sys_args = list(sys.argv)
sys.argv = [sys.argv[0], '0']  # cmf's helpers only; its main() is not run
os.environ.setdefault('CMUNIT', 'unit_0441B0')
_src = open(os.path.join(S, 'cmf.py'), encoding='utf-8').read().rsplit('\nmain()', 1)[0]
cmf = {'__file__': os.path.join(S, 'cmf.py'), '__name__': 'cmf'}
exec(compile(_src, os.path.join(S, 'cmf.py'), 'exec'), cmf)
ROOT, CFG, TRAILER = cmf['ROOT'], cmf['CFG'], cmf['TRAILER']
run, build, strip = cmf['run'], cmf['build'], cmf['strip']



def write_retry(path, text, enc=None):
    """Writes PATH, retrying while another process (an indexer) holds it (Errno 22/13)."""
    for attempt in range(80):
        try:
            open(path, 'w', encoding=enc, newline='\n').write(text)
            return
        except OSError:
            time.sleep(0.25)
    open(path, 'w', encoding=enc, newline='\n').write(text)


class Unit(object):
    def __init__(self, name, addrs):
        self.rel = name if '/' in name else 'recovered/' + name
        self.ext = '.c' if os.path.exists(os.path.join(ROOT, 'src', *(self.rel + '.c').split('/'))) else '.cpp'
        self.path = os.path.join(ROOT, 'src', *(self.rel + self.ext).split('/'))
        try:
            self.full = open(self.path, encoding='utf-8').read()
            self.enc = 'utf-8'
        except UnicodeDecodeError:
            self.full = open(self.path, encoding='latin-1').read()
            self.enc = 'latin-1'
        addrs = [a.upper()[2:] if a.upper().startswith('0X') else a.upper() for a in addrs]
        self.addrs = [a for a in addrs
                      if not re.search(r'^// match: __ehhandler\S* @ 0x0*%s\n' % a, self.full, re.M)]
        for a in self.addrs:
            assert re.search(r'^// match: \S+ @ 0x0*%s\n' % a, self.full, re.M), \
                'no match line for %s in %s' % (a, self.rel)

    def write(self, text):
        write_retry(self.path, text, self.enc)

    def with_rows(self, cfg):
        cmf['REL'] = self.rel
        return cmf['with_rows'](cfg, self.full, self.addrs)

    def without(self, cfg):
        return cmf['without'](cfg, self.full, self.addrs)


def main():
    args = sys_args[1:]
    msg = None
    if args and args[0] == '-m':
        msg, args = args[1], args[2:]
    units = []
    for a in args:
        name, addrs = a.split(':', 1)
        units.append(Unit(name, addrs.split(',')))
    cfg0 = open(CFG).read()
    cfg = cfg0.splitlines(True)
    for u in units:
        cfg = u.with_rows(cfg)
    rows0 = ''.join(cfg)
    write_retry(CFG, rows0)
    try:
        build()
    finally:
        write_retry(CFG, cfg0)
    if msg:
        cfg = cfg0.splitlines(True)
        for u in units:
            u.write(strip(u.full, u.addrs))
            cfg = u.without(cfg)
        write_retry(CFG, ''.join(cfg))
        try:
            build()
            run('git add tools/xbelink.py tools/climb_names.py include docs config/aliases.txt '
                'config/splits.txt config/symbols.txt config/compiled.txt src/recovered/*.cpp '
                'src/Source src/rws src/rw src/rwa src/COD src/xdk src/bink src/xbe include/rw/sdk')
            run(['git', 'commit', '-q', '-m', msg + TRAILER])
        finally:
            for u in units:
                u.write(u.full)
    # replay unit by unit: the units not yet replayed are held at their
    # committed text (and rows) so each commit holds one function
    cfg = open(CFG).read().splitlines(True)
    for k, u in enumerate(units):
        cfg = u.with_rows(cfg)
        write_retry(CFG, ''.join(cfg))
        held = units[k + 1:]
        for h in held:
            h.write(strip(h.full, h.addrs))
        try:
            replay = [a for a in u.addrs
                      if not re.search(r'^// match: \?\?_G\S* @ 0x0*%s\n' % a, u.full, re.M)]
            run(['python', os.path.join(S, 'replayf.py'), 'src/%s%s' % (u.rel, u.ext)] + replay)
        finally:
            for h in held:
                h.write(h.full)
    if (open(CFG).read() != rows0
            or any(open(u.path, encoding=u.enc).read() != u.full for u in units)
            or subprocess.run(['git', 'status', '--porcelain', '--untracked-files=no', '--',
                               'src', 'include', 'config'],
                              cwd=ROOT, capture_output=True, text=True).stdout.strip()):
        build()
    run('git push -q origin master')
    print('pushed', ' '.join('%s:%s' % (u.rel.split('/')[-1], ','.join(u.addrs)) for u in units))


main()
