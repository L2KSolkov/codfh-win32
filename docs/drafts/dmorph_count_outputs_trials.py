"""Parked delta-morph callback probes: _XboxDmorphAtomicInstanceCallback
0x2F28D0 src/rw/plugin/dmorph/xbox/dmorphpipeg.c. Run with pscore.py.
No candidate improves the saved 900-line baseline.
"""
exec(open('docs/drafts/dmorph_entry_order_trials.py').read())
a=body.index('    if (geometryData && atomicData->values)');b=body.index('    if (dmorphLockedSinceLastInst ||',a);chunk=body[a:b]
VS={}
outs=['numBlocks','dmorphLockedSinceLastInst','dmorphFlags']
for result in range(4):
 for local in range(2):
  names=['geometryData','atomicData']+[x for j,x in enumerate(outs) if j!=result]
  types=['rpDMorphGeometryData *geometryData','rpDMorphAtomicData *atomicData']+['RwUInt32 *out'+str(j) for j,x in enumerate(outs) if j!=result]
  for k in range(len(names)*2):
   order=list(range(len(names)));order=order[k%len(names):]+order[:k%len(names)]
   if k>=len(names):order.reverse()
   c=chunk;decl='RwUInt32 i;';tail=''
   for j,name in enumerate(outs):
    if j==result or local:
     decl+=' RwUInt32 '+name+' = 0;'
     if j!=result:tail+=' *out'+str(j)+' = '+name+';'
    else:c=c.replace(name,'(*out'+str(j)+')')
   if result<3:tail+=' return '+outs[result]+';'
   fn='static __forceinline '+('RwUInt32' if result<3 else 'void')+' CountOutputsTrial('+', '.join(types[i] for i in order)+') { '+decl+'\n'+c+tail+' }\n'
   args=', '.join(('&' if i>=2 else '')+names[i] for i in order)
   call='    '+(outs[result]+' = ' if result<3 else '')+'CountOutputsTrial('+args+');\n'
   VS['co_%d_%d_%d'%(result,local,k)]=[(anchor,fn+body[:a]+call+body[b:]+anchor),inc]
