exec(open('docs/drafts/rwa_nv_trials.py').read());VS={}
a=d.index('    if (!dword_51DE60.size');b=d.index('    if (!RwaUUIDCompare',a);block=d[a:b]
for n in range(6):
 u=d;helper=''
 if n&1:u=u.replace('wave->deviceFormat.length','((volatile RwaWave *)wave)->deviceFormat.length')
 if n>=2:
  helper='static __forceinline '+('RwaWave *' if n&2 else 'void')+' InitMemory(rwaStreamedMemory *memory, RwaWave *wave) {\n'+block+('return wave;' if n&2 else '')+'\n}\n'
  u=u.replace(block,'    '+('wave = ' if n&2 else '')+'InitMemory(memory, wave);\n')
  u=u.replace('// match: _sub_24DBA0',helper+'\n// match: _sub_24DBA0')
 VS['ni_%d'%n]=[(s,s+'\n'+u)]
