exec(open('docs/drafts/rwa_adpcm_encoder_trials.py').read());VS={}
import itertools
old='''    RwInt32     step = word_42FD38[*index];
    RwInt32     s = sample;
    RwInt32     diff = s - *predicted;
    RwUInt8     code = 0;'''
for k,p in enumerate(itertools.permutations(['step','s','diff','code'])):
 if p.index('s')>p.index('diff'):continue
 lines={'step':'RwInt32 step = word_42FD38[*index];','s':'RwInt32 s = sample;','diff':'RwInt32 diff = s - *predicted;','code':'RwUInt8 code = 0;'}
 u=d.replace(old,'\n'.join('    '+lines[x] for x in p))
 VS['encord_%d'%k]=[(s,s+'\n'+u)]
