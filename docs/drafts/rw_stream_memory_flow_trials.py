"""RwStreamSkip probes: pscore _RwStreamSkip 0x2A7210
src/rw/src/plcore/bastream.c. No exact match.
"""
exec(open('docs/drafts/rw_stream_memory_block_trials.py').read())
VS={}
needle='                if (smpMem->position + offset > smpMem->nSize)'
start=chunk.index(needle);errstart=chunk.index('                {',start);errend=chunk.index('\n                }',errstart)
error=chunk[errstart+18:errend]
success=chunk[errend+18:]
for n in range(4):
 c=chunk[:start]
 if n==0:c+='                if (smpMem->position + offset <= smpMem->nSize)\n                {\n'+success+'\n                }\n'+error
 if n==1:c+='                if (smpMem->position + offset > smpMem->nSize) goto memoryEnd;\n'+success+'\nmemoryEnd:\n'+error
 if n==2:c+='                if (smpMem->position + offset <= smpMem->nSize) goto memorySuccess;\n'+error+'\nmemorySuccess:\n'+success
 if n==3:c=chunk.replace('if (smpMem->position + offset > smpMem->nSize)','if (!(smpMem->nSize >= offset + smpMem->position))')
 VS['sc_%d'%n]=[(d,d.replace(chunk,c))]
