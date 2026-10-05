"""Final BNT cross-product probes. pscore target __rpXboxVtxFmtInstBNT
0x2DDB50 src/rw/world/pipe/p2/xbox/xbvtxfmt.c. Not exact.
"""
exec(open('docs/drafts/rw_bnt_z_steps_trials.py').read())
import itertools
VS={}
args={'tx':'(a)->x','ny':'(b)->y','ty':'(a)->y','nx':'(b)->x'}
for k,order in enumerate(itertools.permutations(args)):
 for f,expr in enumerate(['return tx * ny - ty * nx;','RwReal result = tx * ny; result -= ty * nx; return result;','RwReal first = tx * ny; RwReal second = ty * nx; return first - second;']):
  fn='static __forceinline RwReal CrossZTrial('+', '.join('RwReal '+v for v in order)+') { '+expr+' }\n'
  c='    (o)->z = CrossZTrial('+', '.join(args[v] for v in order)+'); \\\n'
  t=fn+body[:a]+c+body[b:]
  VS['zh_%d_%d'%(k,f)]=[(anchor,t+anchor)]
