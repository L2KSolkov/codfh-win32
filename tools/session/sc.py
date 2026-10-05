"""sc.py SYM ADDR GLOB: fast in-process odiff line counts for ptry objects."""
import os as _os_repo
_REPO = _os_repo.path.dirname(_os_repo.path.dirname(_os_repo.path.dirname(_os_repo.path.abspath(__file__))))  # the repository root, from this file's location
import sys, glob, os, re
sym, addr, pat = sys.argv[1:4]
S = os.path.dirname(os.path.abspath(__file__))
src = open(S + '/snchk2.py').read()
src = src[src.index('sys.path.insert'):src.index('def positions')]
ROOT = _REPO
exec(src)
res = sorted((score(f), os.path.basename(f)) for f in glob.glob(ROOT + '/build/tooltmp/ptry/' + pat))
for r in res[:8]:
    print(*r)
