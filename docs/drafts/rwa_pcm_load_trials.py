from pathlib import Path
s=Path('src/rwa/unit_249490.c').read_text()
d=Path('docs/drafts/rwa_pcm_draft.c').read_text()
a=d.index('extern void *sub_2421C0')
b=d.index('/* PCM conversion:')
helper=d[a:b]
caller=d[b:]
marker='// match: _sub_24A660'
base=s.replace(marker,helper+'\n'+marker,1)+'\n'+caller
VS={'pcm_base':[(s,base)]}
old='((const RwUInt16 *)src)[i] - 32768.0f'
forms=['*(const RwUInt16 *)(src + i * 2) - 32768.0f','((const RwUInt16 *)(i * 2 + src))[0] - 32768.0f','((const volatile RwUInt16 *)src)[i] - 32768.0f','(RwUInt16)((const RwInt16 *)src)[i] - 32768.0f']
for k,f in enumerate(forms): VS['pcm_load%d'%k]=[(s,base.replace(old,f))]
for k,params in enumerate(['const RwUInt8 *p, RwUInt32 n','RwUInt32 n, const RwUInt8 *p']):
 for j,expr in enumerate(['((const RwUInt16 *)p)[n]','*(const RwUInt16 *)(p+n*2)']):
  fn='static __forceinline RwUInt16 pcmRead('+params+') { return '+expr+'; }\n'
  args='src, i' if k==0 else 'i, src'
  VS['pcm_helper%d%d'%(k,j)]=[(s,base.replace('extern void *sub_2421C0',fn+'extern void *sub_2421C0',1).replace(old,'pcmRead('+args+') - 32768.0f'))]
