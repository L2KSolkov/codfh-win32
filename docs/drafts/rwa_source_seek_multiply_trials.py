exec(open('docs/drafts/rwa_source_seek_result_trials.py').read());old=VS;VS={}
for k in range(4):
 for n in range(3):
  u=old['sk_fix%d'%k][0][1]
  expr=['((block + skip - 1) / block) * t->unk1A * channels','t->unk1A * ((block + skip - 1) / block) * channels','((block + skip - 1) / block) * (channels * t->unk1A)'][n]
  u=u.replace('channels * t->unk1A * ((block + skip - 1) / block)',expr)
  VS['sm_%d_%d'%(k,n)]=[(s,u)]
