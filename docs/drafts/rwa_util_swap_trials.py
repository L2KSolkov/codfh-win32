exec(open('docs/drafts/rwa_util_trials.py').read());VS={}
old='(value << 24) | ((value & 0xFF00) << 8) |\n                               ((value >> 8) & 0xFF00) | ((const RwUInt8 *)src)[3]'
forms=['(((value << 16) | (value & 0xFF00)) << 8) | ((value >> 8) & 0xFF00) | ((const RwUInt8 *)src)[3]', '((value & 0xFF00) << 8) | (value << 24) | ((value >> 8) & 0xFF00) | ((const RwUInt8 *)src)[3]', '((value >> 8) & 0xFF00) | ((const RwUInt8 *)src)[3] | (value << 24) | ((value & 0xFF00) << 8)']
old16='            *(RwUInt16 *)dst = (RwUInt16)((((const RwUInt8 *)src)[0] << 8) | ((const RwUInt8 *)src)[1]);'
forms16=['            RwUInt16 value = ((const RwUInt8 *)src)[1];\n            value |= ((const RwUInt8 *)src)[0] << 8;\n            *(RwUInt16 *)dst = value;', '            *(RwUInt16 *)dst = (RwUInt16)(((const RwUInt8 *)src)[1] | (((const RwUInt8 *)src)[0] << 8));','            union { RwUInt16 word; RwUInt8 bytes[2]; } value;\n            value.bytes[0] = ((const RwUInt8 *)src)[1]; value.bytes[1] = ((const RwUInt8 *)src)[0];\n            *(RwUInt16 *)dst = value.word;']
for n,f in enumerate(forms):
 for m,g in enumerate(forms16):VS['ub_%d_%d'%(n,m)]=[(s,s+'\n'+h+d.replace(old,f).replace(old16,g))]
