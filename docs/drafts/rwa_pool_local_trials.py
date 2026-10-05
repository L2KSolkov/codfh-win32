exec(open('docs/drafts/rwa_pool_flow_trials.py').read())
VS={}
for n in range(32):
 u=d
 if n&1:u=u.replace('        rwaPoolChunk   *next = chunk->next;', '        rwaPoolChunk   *next = chunk->next;\n        RwUInt32 chunkSize = chunk->size;').replace('next - chunk->size', 'next - chunkSize').replace('chunk + chunk->size', 'chunk + chunkSize')
 if n&2:u=u.replace('    RwUInt32        needed = size + sizeof(rwaPoolChunk);', '    RwUInt32 needed = size;').replace('    do\n', '    needed += sizeof(rwaPoolChunk);\n    do\n')
 if n&4:u=u.replace('            rwaPoolChunk   *found;', '            rwaPoolChunk   *found;\n            RwUInt32 mask = ~(alignment - 1);').replace('& ~(alignment - 1)', '& mask')
 if n&8:u=u.replace('        chunk = next;', '        { rwaPoolChunk *end = block->end;\n        chunk = next;\n        if (chunk == end) break; }').replace('while (chunk != block->end);', 'while (1);')
 if n&16:u=u.replace('                found->prev = chunk;\n                found->next = chunk->next;', '                { rwaPoolChunk *after = chunk->next;\n                found->prev = chunk;\n                found->next = after; }')
 VS['poollocal_%02d'%n]=[(s,s+'\n'+u)]
