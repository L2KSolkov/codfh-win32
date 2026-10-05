exec(open('docs/drafts/rwa_adpcm_encoder_trials.py').read());VS={}
import itertools
a=d.index('    if (code & 8)');b=d.index('    if (*predicted >',a);old=d[a:b]
args={'sample':'RwInt32 sample','step':'RwInt32 step','diff':'RwInt32 diff'}
for k,p in enumerate(itertools.permutations(args)):
 for n in range(4):
  h='static __forceinline RwInt32 predictValue('+', '.join(args[x] for x in p)+', RwUInt8 code) { if (code & 8) return sample - step + diff; return step - diff + sample; }\n'
  vals={'sample':'s','step':'step','diff':'diff'}
  u=d.replace(old,'    *predicted = predictValue('+', '.join(vals[x] for x in p)+', code);\n')
  if n&1:h=h.replace('RwInt32 predictValue','void predictValue').replace(', RwUInt8 code)',', RwUInt8 code, RwInt32 *predicted)').replace('if (code & 8) return sample - step + diff; return step - diff + sample;', 'if (code & 8) *predicted = sample - step + diff; else *predicted = step - diff + sample;');u=u.replace('*predicted = predictValue(', 'predictValue(').replace(', code);', ', code, predicted);')
  if n&2:h=h.replace('sample - step + diff','(sample - step) + diff').replace('step - diff + sample','sample + (step - diff)')
  VS['ench_%d_%d'%(k,n)]=[(s,s+'\n'+h+u)]
