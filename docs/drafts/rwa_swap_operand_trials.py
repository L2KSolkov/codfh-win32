exec(open('docs/drafts/rwa_swap_lifetime_trials.py').read())
base=VS['swaplife_0'][0][1];VS={}
for n in range(16):
 u=base
 if n&1:u=u.replace('(value << 16) | (value & 0xFF00)', '(value & 0xFF00) | (value << 16)')
 if n&2:u=u.replace('RwUInt16 value = ((const RwUInt8 *)src)[1];', 'RwUInt16 value = ((const volatile RwUInt8 *)src)[1];')
 if n&4:u=u.replace('value |= ((const RwUInt8 *)src)[0] << 8;', 'value += ((const RwUInt8 *)src)[0] << 8;')
 if n&8:u=u.replace('value |= ((const RwUInt8 *)src)[0] << 8;', 'value |= ((const volatile RwUInt8 *)src)[0] << 8;').replace('value += ((const RwUInt8 *)src)[0] << 8;', 'value += ((const volatile RwUInt8 *)src)[0] << 8;')
 VS['swapoperand_%d'%n]=[(s,u)]
