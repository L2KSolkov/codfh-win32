exec(open('docs/drafts/rwa_adpcm_encoder_poststore_trials.py').read());v=VS['encpost_8'][0][1][len(s)+1:];VS={}
a=v.index('    if (diff < 0)');b=v.index('    if (!(code & 8))',a);chunk=v[a:b]
import re
for n in range(4):
 h='static __forceinline RwUInt8 quantize('+('RwInt32 *stepPtr, RwInt32 *diffPtr' if n&1 else 'RwInt32 *diffPtr, RwInt32 *stepPtr')+') { RwUInt8 code = 0;\n'+re.sub(r'\bstep\b','(*stepPtr)',re.sub(r'\bdiff\b','(*diffPtr)',chunk))+'return code;\n}\n'
 if n&2:h=h.replace('RwUInt8 quantize','void quantize').replace(') { RwUInt8 code = 0;', ', RwUInt8 *codePtr) { RwUInt8 code = 0;').replace('return code;', '*codePtr = code;')
 call=('quantize(' if n&2 else 'code = quantize(')+('&step, &diff' if n&1 else '&diff, &step')+(', &code' if n&2 else '')+');\n'
 u=v[:a]+'    '+call+v[b:]
 VS['encquant_%d'%n]=[(s,s+'\n'+h+u)]
