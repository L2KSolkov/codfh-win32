exec(open('docs/drafts/rwa_source_seek_trials.py').read());VS={}
for n in range(4):
 u=d
 if n<2:
  u=u.replace('    RwUInt32    offset;', '    RwUInt32    offset;\n    RwUInt32 originalPosition = position;').replace('    skip = position - track;', '    skip = originalPosition - track;')
  if n==1:u=u.replace('    RwUInt32 originalPosition = position;','    RwUInt32 high;').replace('sub_2420D0(chunk, unit, &position, &track);','sub_2420D0(chunk, unit, &high, &track);').replace('skip = originalPosition - track;', 'skip = position - track;')
 else:
  u=u.replace('    RwUInt32    offset;', '    RwUInt32    offset;\n    RwUInt32 high, low;').replace('sub_2420D0(chunk, unit, &position, &track);','sub_2420D0(chunk, unit, &high, &low);').replace('skip = position - track;', 'skip = position - low;')
  if n==3:u=u.replace('&position, &skip','&high, &skip')
 VS['sk_fix%d'%n]=[(s,s+'\n'+u)]
