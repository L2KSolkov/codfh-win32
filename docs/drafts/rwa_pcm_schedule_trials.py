exec(open('docs/drafts/rwa_pcm_load_trials.py').read())
VS={'pcms_base':[(s,base)]}
for mask in range(32):
 c=caller
 if mask&1:
  c=c.replace('        temp.sampleRate = to->sampleRate;','        RwUInt32 size;\n        temp.sampleRate = to->sampleRate;\n        size = sub_249BF0(&temp, to);').replace('sub_2421C0(sub_249BF0(&temp, to),','sub_2421C0(size,')
 if mask&2:
  c=c.replace('RwUInt8    *buffer = NULL;','RwUInt8    *buffer;').replace('    spare = srcSize;','    spare = srcSize;\n    buffer = NULL;')
 if mask&4:
  c=c.replace('RwUInt8    *final = dest;','RwUInt8    *final;').replace('    spare = srcSize;','    spare = srcSize;\n    final = dest;')
 if mask&8:
  c=c.replace('RwUInt8    *final = dest;','RwUInt8    *final;').replace('    result = from->length;','    final = dest;\n    result = from->length;')
 if mask&16:
  c=c.replace('format.length = result = sub_24A260','result = sub_24A260').replace('        format.bitDepth = to->bitDepth;','        format.length = result;\n        format.bitDepth = to->bitDepth;')
 VS['pcms_%02d'%mask]=[(s,s.replace(marker,helper+'\n'+marker,1)+'\n'+c)]
