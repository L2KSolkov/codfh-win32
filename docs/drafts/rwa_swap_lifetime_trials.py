exec(open('docs/drafts/rwa_util_swap_trials.py').read())
base=VS['ub_0_0'][0][1];VS={}
for n in range(16):
 u=base
 if n&1:u=u.replace('            RwUInt8    *dst = *cursor;\n            RwUInt32    value = *(const RwUInt32 *)src;', '            RwUInt32 value = *(const RwUInt32 *)src;\n            RwUInt8 *dst = *cursor;')
 if n&2:u=u.replace('            RwUInt8    *dst = *cursor;\n\n            RwUInt16 value = ((const RwUInt8 *)src)[1];', '            RwUInt16 value = ((const RwUInt8 *)src)[1];\n            RwUInt8 *dst;').replace('            *(RwUInt16 *)dst = value;', '            dst = *cursor;\n            *(RwUInt16 *)dst = value;')
 if n&4:u=u.replace('*(const RwUInt32 *)src;', '*(const volatile RwUInt32 *)src;')
 if n&8:u=u.replace('((const RwUInt8 *)src)[3]', '((const volatile RwUInt8 *)src)[3]')
 VS['swaplife_%d'%n]=[(s,u)]
