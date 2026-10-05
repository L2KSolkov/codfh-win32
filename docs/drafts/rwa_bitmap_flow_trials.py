from pathlib import Path
s=Path('src/rwa/unit_2FD5D0.c').read_text()
d=Path('docs/drafts/rwa_bitmap_draft.c').read_text().split('/* Allocates a run')[0]
VS={}
for n in range(8):
 u=d
 if n&1:
  u=u.replace('    RwUInt32    rounded = (numUnits + 7) & ~7;', '    RwUInt32    rounded = (numUnits + 7) & ~7;').replace('    numBytes = rounded >> 3;', '    rounded >>= 3;').replace('numBytes,', 'rounded,').replace('0, numBytes)', '0, rounded)').replace('bitmap->numBytes = numBytes;', 'bitmap->numBytes = rounded;')
 if n&2:
  a=u.index('        if (!bits)');b=u.index('\n    bitmap->shift',a)
  u=u[:a]+'''    }
    if (!bits) goto failedBits;
'''+u[b:]
  u=u.replace('    return bitmap;','''    return bitmap;
failedBits:
    if (flags & 1) sub_2437A0(&unk_5125EC, bitmap);
    return NULL;''')
 if n&4:
  start=u.index('    if (!bitmap)');end=u.index('\n    if (!bits)',start)
  block=u[start:end]
  h='static __forceinline RwaAllocBitmap *allocateBitmap(RwaAllocBitmap *bitmap, RwUInt8 *flags) {\n'+block.replace('flags = 1;', '*flags = 1;')+'\nreturn bitmap;\n}\n'
  u=u[:start]+'    bitmap = allocateBitmap(bitmap, &flags);\n    if (!bitmap) return NULL;\n'+u[end:]
  u=u.replace('// match: _sub_2FD5D0',h+'\n// match: _sub_2FD5D0')
 VS['bitmapflow_%d'%n]=[(s,s+'\n'+u)]
