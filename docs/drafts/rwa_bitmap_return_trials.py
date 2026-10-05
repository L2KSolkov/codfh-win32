exec(open('docs/drafts/rwa_bitmap_flow_trials.py').read())
prior=VS;VS={}
for k in range(8):
 for n in range(4):
  u=prior['bitmapflow_%d'%k][0][1]
  start=u.index('// match: _sub_2FD5D0');head=u[:start];body=u[start:]
  body=body.replace('return NULL;', 'goto failure;')
  end=body.rfind('}')
  body=body[:end]+'failure:\n    return NULL;\n'+body[end:]
  if n&1:body=body.replace('RwUInt8     shift;', 'RwUInt32 shift;')
  if n&2:body=body.replace('    shift = (RwUInt8)(rwaLog2U(rounded) + 1);', '    shift = (RwUInt8)rwaLog2U(rounded);\n    shift++;')
  VS['bitmapret_%d_%d'%(k,n)]=[(s,head+body)]
