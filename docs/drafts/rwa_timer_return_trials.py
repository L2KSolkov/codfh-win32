exec(open('docs/drafts/rwa_timer_wrap_trials.py').read());VS={}
for n in range(8):
 u=d
 if n&1:u=u.replace('\nRwUInt32\n','\nRwUInt64\n')
 if n&2:u=u.replace('if (now < start)','if (start > now)')
 if n&4:u=u.replace('return (RwUInt32)(now + (0xFFFFFFFF - start));','return (RwUInt32)(0xFFFFFFFF - start) + now;')
 prefix=s.replace('extern RwUInt32 sub_244980(void);','extern '+('RwUInt64' if n&1 else 'RwUInt32')+' sub_244980(void);')
 VS['timer_r%d'%n]=[(s,prefix+'\n'+u)]
