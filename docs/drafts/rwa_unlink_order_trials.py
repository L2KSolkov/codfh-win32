exec(open('docs/drafts/rwa_unlink_access_trials.py').read())
base=VS['unlinkaccess_13'][0][1];VS={}
for n in range(8):
 u=base.replace('    stream = input;\n','')
 target='    count--;' if n&1 else '    *(volatile RwInt32 *)&dword_506B38 = count;'
 u=u.replace(target,'    stream = input;\n'+target)
 if n&2:u=u.replace('*(volatile RwInt32 *)&dword_506B38 = count;', 'dword_506B38 = count;')
 if n&4:u=u.replace('RwInt32 count = *(volatile RwInt32 *)&dword_506B38;', 'RwInt32 count = dword_506B38;')
 VS['unlinkorder_%d'%n]=[(s,u)]
