exec(open('docs/drafts/rwa_wave_trials.py').read())
from itertools import permutations
VS={}
params=['RwaWave *wave','RwUInt32 offset','void *buffer','RwUInt32 size','RwaWave *(*upload)(RwaWave *, RwUInt32, void *, RwUInt32)'];args=['wave','offset','buffer','size','upload']
for n,p in enumerate(permutations(range(5))):
 helper='static __forceinline RwaWave *WaveUpload('+', '.join(params[i] for i in p)+') { dword_506FFC=wave; dword_507000=offset; return upload(wave,offset,buffer,size); }\n'
 u=d.replace('// match: _sub_242810',helper+'\n// match: _sub_242810',1).replace('        dword_506FFC = wave;\n        dword_507000 = offset;\n        result = upload(wave, offset, buffer, size);','        result = WaveUpload('+', '.join(args[i] for i in p)+');')
 VS['wi_%03d'%n]=[(s,s+'\n'+u)]
