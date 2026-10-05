exec(open('docs/drafts/rwa_source_seek_result_trials.py').read());old=VS;VS={}
for k in range(4):
 b=old['sk_fix%d'%k][0][1][len(s)+1:]
 for n in range(4):
  u=b
  if n&1:u=u.replace('t->unk1A','((volatile rwaStreamTrack *)t)->unk1A')
  if n&2:u=u.replace('if (info->noTracks)', 'if (info->noTracks > 0)').replace('while (--n);','while (--n > 0);')
  VS['sr_%d_%d'%(k,n)]=[(s,s+'\n'+u)]
