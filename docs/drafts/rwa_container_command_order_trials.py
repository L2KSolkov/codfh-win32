exec(open('docs/drafts/rwa_container_command_trials.py').read());VS={}
import itertools
lo=d.index('    RwInt32     trackEnd');hi=d.index('\n\n    if (track',lo);decl=d[lo:hi].splitlines()
for k,p in enumerate(itertools.permutations(decl)):
 u=d[:lo]+'\n'.join(p)+d[hi:];u=u.replace('if (index < 0)', 'if (index & 0x80000000)')
 VS['cmdord_%d'%k]=[(s,s[:a]+u+s[b:])]
