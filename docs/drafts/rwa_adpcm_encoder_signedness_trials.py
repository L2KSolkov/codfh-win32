exec(open('docs/drafts/rwa_adpcm_encoder_poststore_trials.py').read());v=VS['encpost_8'][0][1][len(s)+1:];VS={}
for n in range(8):
 u=v
 if n&1:u=u.replace('RwInt32     step =','RwUInt32 step =').replace('diff >= step', 'diff >= (RwInt32)step').replace('step >>= 1;', 'step = (RwInt32)step >> 1;')
 if n&2:u=u.replace('RwInt32     diff =', 'RwUInt32 diff =').replace('if (diff < 0)', 'if ((RwInt32)diff < 0)').replace('if (diff >=', 'if ((RwInt32)diff >=')
 if n&4:u=u.replace('RwUInt8     code = 0;', 'RwUInt32 code = 0;')
 VS['enctype_%d'%n]=[(s,s+'\n'+u)]
