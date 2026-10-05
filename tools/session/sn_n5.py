import os as _os_repo
_REPO = _os_repo.path.dirname(_os_repo.path.dirname(_os_repo.path.dirname(_os_repo.path.abspath(__file__))))  # the repository root, from this file's location
import itertools, re, os
FN, VARS = os.environ['SNFN'], os.environ['SNV'].split(',')
src = open(os.environ.get('SNSRC', _os_repo.path.join(_REPO, 'src/COD/SHARED/network/knet/sNetGameEP.cpp'))).read()
a = src.index(FN); b = src.index('\n}\n', a) + 3
body = src[a:b]
cands = os.environ.get('SNC', 'a,b,c,var_4,var_8,var_C,v4,v8,l4,l8,x,y,z,n,k,p').split(',')
VS = {}
for combo in itertools.permutations(cands, len(VARS)):
    nb = body
    for i, v in enumerate(VARS):
        nb = re.sub(r'\b%s\b' % v, 'QZ%d' % i, nb)
    for i, c in enumerate(combo):
        nb = nb.replace('QZ%d' % i, c)
    VS[os.environ.get('SNP', 'q') + '_' + '_'.join(combo)] = [(body, nb)]
