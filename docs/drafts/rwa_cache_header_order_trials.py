from pathlib import Path
s=Path('src/rwa/unit_2449C0.c').read_text();d=Path('docs/drafts/rwa_streamcache_clients_followup.c').read_text();VS={}
for n in range(16):
 u=d
 a=u.index('    client->header[0] = 0;');b=u.index('\n}',a);tail=u[a:b]
 if n&1:tail=tail.replace('client->header','((volatile rwaCacheClient *)client)->header')
 if n&2:tail=tail.replace('client->holder','((volatile rwaCacheClient *)client)->holder')
 if n&4:tail=tail.replace('client->data','((volatile rwaCacheClient *)client)->data')
 if n&8:tail=tail.replace('client->callback','((volatile rwaCacheClient *)client)->callback')
 u=u[:a]+tail+u[b:];VS['hv_%d'%n]=[(s,s+'\n'+u)]
