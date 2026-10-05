exec(open('docs/drafts/rwa_adpcm_encoder_trials.py').read());VS={}
neg=['*predicted = s - step + diff;', 's -= step; s += diff; *predicted = s;', 'diff -= step; *predicted = s + diff;', '*predicted = s - step; *predicted += diff;']
pos=['*predicted = step - diff + s;', 'step -= diff; step += s; *predicted = step;', 's += step; s -= diff; *predicted = s;', '*predicted = step - diff; *predicted += s;']
for n in range(16):
 u=d.replace('*predicted = s - step + diff;',neg[n%4]).replace('*predicted = step - diff + s;',pos[n//4])
 VS['encp_%d'%n]=[(s,s+'\n'+u)]
