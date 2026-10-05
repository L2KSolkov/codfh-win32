exec(open('docs/drafts/rwa_pcm_load_trials.py').read())
import re,itertools
VS={}
for reuse in (False,True):
 for outlocal in (False,True):
  for order in itertools.permutations(['result','spare','buffer','final']):
   c=caller
   decl={'result':'    RwUInt32 result;','spare':'    RwUInt32 spare;','buffer':'    RwUInt8 *buffer;','final':'    RwUInt8 *final = dest;'}
   start=c.index('    RwUInt32    result;');end=c.index('    result = from->length;')
   c=c[:start]+'\n'.join(decl[v] for v in order)+'\n\n'+c[end:]
   c=c.replace('    spare = srcSize;','    spare = srcSize;\n    buffer = NULL;')
   if outlocal:
    c=c.replace('RwUInt8 *final = dest;','RwUInt8 *working = dest;')
    split=c.index('    if (format.bitDepth')
    tail=c[split:].replace('dest = final;','working = dest;')
    tail=re.sub(r'\bdest\b','working',tail).replace('working = working;','working = dest;')
    c=c[:split]+tail
   if reuse:
    c=c.replace('    RwUInt8 *buffer;','').replace('buffer = NULL;','from = NULL;').replace('buffer = (RwUInt8 *)','from = (const RwaWaveFormat *)')
    c=re.sub(r'\bbuffer\b','from',c).replace('dest = from;','dest = (RwUInt8 *)from;').replace('working = from;','working = (RwUInt8 *)from;').replace('src = from;','src = (const RwUInt8 *)from;').replace('sub_2421B0(from)','sub_2421B0((void *)from)')
   VS['pcmc_%d%d_%s'%(reuse,outlocal,''.join(v[0] for v in order))]=[(s,s.replace(marker,helper+'\n'+marker,1)+'\n'+c)]
