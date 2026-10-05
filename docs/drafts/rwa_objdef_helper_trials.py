exec(open('docs/drafts/rwa_objdef_loop_trials.py').read());baseVS=VS;VS={}
for n in [4,5,6,7]:
 for m in range(3):
  v=baseVS['ol_%d'%n][0][1]
  a=v.index(' { RwUInt32 i; param += count;');b=v.index('\n',a)
  code=[' { if (count > 0) { RwUInt32 i; param += count; i=count; do { --param; sub_240C30(param); } while (--i > 0); } }', ' { if (count > 0) { RwUInt32 i = count; param += count; do { --param; sub_240C30(param); } while (--i > 0); } }', ' { if (count > 0) { RwUInt32 i; param += count; for(i=count;i>0;i--) { --param; sub_240C30(param); } } }'][m]
  v=v[:a]+code+v[b:]
  VS['oh_%d_%d'%(n,m)]=[(s,v)]
