"""BNT follow-up trials, 2026-10-01. Run through pscore.py with
__rpXboxVtxFmtInstBNT 0x2DDB50 src/rw/world/pipe/p2/xbox/xbvtxfmt.c.
Select BNT_TRIAL=macro (default), component, or basis. Best remains 14
normalized lines; byte comparison, not this score, determines a match.
"""
import os
from pathlib import Path
body = Path('docs/drafts/rw_xbvtxfmt_bnt_followup.c').read_text()
body = body[body.index('#define SMALL_FLOAT'):]
anchor = '// match: __rpXboxVtxFmtUnInstV3d @ 0x002DE6B0'
h=Path('include/rw/sdk/rwplcore.h').read_text();a=h.index('#define RwV3dCrossProductMacro');b=h.index('\n\n',a);macro=h[a:b].replace('RwV3dCrossProductMacro','CrossTrialMacro')
if os.environ.get('BNT_TRIAL', 'macro') == 'macro':
    VS={}
    for mask in range(64):
     m=macro
     for j,(u,v) in enumerate([('y','z'),('z','x'),('x','y')]):
      for k,(c,e) in enumerate([(u,v),(v,u)]):
       if mask&(1<<(2*j+k)):
        old='(((a)->'+c+') * ( (b)->'+e+'))';new='(((b)->'+e+') * ( (a)->'+c+'))';assert old in m;m=m.replace(old,new)
     t=body.replace('RwV3dCrossProduct(currentBinormal, currentTangent, currentNormal);','CrossTrialMacro(currentBinormal, currentTangent, currentNormal);')
     VS['cm_%02d'%mask]=[(anchor,m+'\n'+t+anchor)]

elif os.environ.get('BNT_TRIAL', 'macro') == 'component':
    VS={}
    needle='    (o)->z ='
    for n in range(16):
     m=macro
     decl=[]
     if n&1:decl.append('RwReal nx = (b)->x;')
     if n&2:decl.append('RwReal ty = (a)->y;')
     if n&4:decl.reverse()
     a=m.index(needle);tail=m[a:]
     if n&1:tail=tail.replace('( (b)->x)','( nx)')
     if n&2:tail=tail.replace('((a)->y)','(ty)')
     if n&8:
      decl.append('RwReal last = '+('nx' if n&1 else '(b)->x')+' * '+('ty' if n&2 else '(a)->y')+';')
      tail=tail.replace('(((a)->y) * ( (b)->x))','(last)').replace('((ty) * ( (b)->x))','(last)').replace('(((a)->y) * ( nx))','(last)').replace('((ty) * ( nx))','(last)')
     tail=tail.replace('}                                                               \\', '} }                                                             \\')
     m=m[:a]+'    { '+' '.join(decl)+' \\\n'+tail
     t=body.replace('RwV3dCrossProduct(currentBinormal, currentTangent, currentNormal);','CrossTrialMacro(currentBinormal, currentTangent, currentNormal);')
     VS['cl_%02d'%n]=[(anchor,m+'\n'+t+anchor)]

elif os.environ.get('BNT_TRIAL', 'macro') == 'basis':
    from itertools import permutations
    VS={}
    a=body.index('        _rwV3dNormalizeMacro(unused, currentTangent, currentTangent);');b=body.index('\n    }',a);chunk=body[a:b]
    for start in range(2):
     c=chunk if not start else chunk[chunk.index('        RwV3dCrossProduct'):]
     for order in permutations(['normal','tangent','binormal']):
      h='static __forceinline void BasisTrial('+', '.join(('const RwV3d *' if x=='normal' else 'RwV3d *')+x for x in order)+') { RwReal unused;\n'+c.replace('currentTangent','tangent').replace('currentBinormal','binormal').replace('currentNormal','normal')+'\n}\n'
      args=dict(normal='currentNormal',tangent='currentTangent',binormal='currentBinormal')
      t=body.replace(c,'BasisTrial('+', '.join(args[x] for x in order)+');')
      VS['bh_%d_'%start+''.join(x[0] for x in order)]=[(anchor,h+t+anchor)]

