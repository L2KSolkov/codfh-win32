exec(open('docs/drafts/rwa_pcm_load_trials.py').read())
import itertools
VS={}
old='((RwInt16 *)dest)[i] = (RwInt16)(((const RwUInt16 *)src)[i] - 32768.0f);'
for k,order in enumerate(itertools.permutations(['p','q','n'])):
 for j,expr in enumerate(['((const RwUInt16 *)p)[n]','*(const RwUInt16 *)(p+n*2)']):
  types={'p':'const RwUInt8 *p','q':'RwUInt8 *q','n':'RwUInt32 n'}
  args={'p':'src','q':'dest','n':'i'}
  fn='static __forceinline void pcmConvert('+', '.join(types[v] for v in order)+') { ((RwInt16 *)q)[n] = (RwInt16)('+expr+' - 32768.0f); }\n'
  b=base.replace('extern void *sub_2421C0',fn+'extern void *sub_2421C0',1).replace(old,'pcmConvert('+', '.join(args[v] for v in order)+');')
  VS['pcme_%d%d'%(k,j)]=[(s,b)]
for k,itype in enumerate(['RwInt32','RwUInt16','RwInt16','volatile RwUInt32']):
 b=base.replace(old,'((RwInt16 *)dest)[j] = (RwInt16)(((const RwUInt16 *)src)[j] - 32768.0f);')
 pos=b.index('((RwInt16 *)dest)[j]')
 st=b.rfind('                for (i',0,pos)
 end=b.index('            return total;',pos)
 region=b[st:end].replace('for (i = 0; i < count; i++)','for (j = 0; j < count; j++)')
 b=b[:st]+'                '+itype+' j;\n'+region+b[end:]
 VS['pcme_counter%d'%k]=[(s,b)]
