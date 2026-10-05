exec(open('docs/drafts/rwa_swap_lifetime_trials.py').read())
base=VS['swaplife_0'][0][1];VS={}
forms=['(word >> 8) | (word << 8)', '(word << 8) | (word >> 8)', '(word >> 8) + (word << 8)', '(word >> 8) | (((const RwUInt8 *)src)[0] << 8)']
for k,f in enumerate(forms):
 for n in range(4):
  u=base
  u=u.replace('            RwUInt16 value = ((const RwUInt8 *)src)[1];\n            value |= ((const RwUInt8 *)src)[0] << 8;', '            RwUInt16 word = *(const RwUInt16 *)src;\n            RwUInt16 value = (RwUInt16)('+f+');')
  if n&1:u=u.replace('RwUInt16 word =', 'RwUInt32 word =')
  if n&2:u=u.replace('            *(RwUInt32 *)dst =', '            RwUInt32 top = value << 16;\n            *(RwUInt32 *)dst =').replace('(value << 16) | (value & 0xFF00)', 'top | (value & 0xFF00)')
  VS['swapword_%d_%d'%(k,n)]=[(s,u)]
