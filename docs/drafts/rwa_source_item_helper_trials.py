from pathlib import Path
import itertools
s=Path('src/rwa/rwastreamsourceobj.c').read_text();d=Path('docs/drafts/rwa_streamsource_followup.c').read_text();a=d.index('            ((rwaQueueItem *)arg)[i].flags');b=d.index('\n        }',a);chunk=d[a:b].replace('((rwaQueueItem *)arg)[i].','item->').replace('&positions[i]','position').replace('positions[i].','position->');VS={}
args={'item':'rwaQueueItem *item','position':'rwaStreamPosition *position','obj':'rwaDecoder *obj','state':'rwaDecoderState *state','callback':'rwaQueueCallback *callback'}; vals={'item':'&((rwaQueueItem *)arg)[i]','position':'&positions[i]','obj':'obj','state':'state','callback':'callback'}
for k,p in enumerate(itertools.permutations(args)):
 h='static __forceinline void initSourceItem('+', '.join(args[x] for x in p)+') {\n'+chunk+'\n}\n'
 u=d[:a]+'            initSourceItem('+', '.join(vals[x] for x in p)+');'+d[b:]
 VS['itemhelp_%d'%k]=[(s,s+'\n'+h+u)]
