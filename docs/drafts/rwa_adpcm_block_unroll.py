exec(open('docs/drafts/rwa_adpcm_block_lifetime.py').read())
prior=VS;VS={}
for n in range(8):
 u=prior['adpcmblock_%d'%(n&3)][0][1]
 a=u.index('            for (j = 0; j < 2; j++)');b=u.index('            src++;',a)
 inner=u[u.index('                t =',a):u.index('            }',a)]
 text=inner.replace('j * 4','0')+inner.replace('j * 4','4')
 u=u[:a]+text+u[b:]
 if n&4:u=u.replace('s1 * (RwInt32)blocks + s2 * k1','s2 * k1 + s1 * (RwInt32)blocks').replace('s1 * k0 + s2 * k1','s2 * k1 + s1 * k0')
 VS['adpcmunroll_%d'%n]=[(s,u)]
