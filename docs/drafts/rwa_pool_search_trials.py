exec(open('docs/drafts/rwa_pool_exit_trials.py').read());u=VS['pool_exit0'][0][1][len(s)+1:];VS={}
a=u.index('    RwUInt32');b=u.index('allocate:');search=u[a:b].replace('goto allocate;','return found;'); tail=u[b+len('allocate:'):];search=search.replace('    rwaPoolChunk   *chunk = block->chunks;','    rwaPoolChunk *chunk = *cursor;').replace('return found;', '*cursor = chunk; return found;')
for n in range(8):
 params='rwaPoolBlock *block, RwUInt32 size, RwUInt32 alignment, rwaPoolChunk **cursor'
 args='block, size, alignment, &chunk'
 if n&1:params='RwUInt32 size, RwUInt32 alignment, rwaPoolBlock *block, rwaPoolChunk **cursor';args='size, alignment, block, &chunk'
 h='static __forceinline rwaPoolChunk *findChunk('+params+') {\n'+search+'}\n'
 body='''// match: _sub_2442D0 @ 0x002442D0
void *sub_2442D0(rwaPoolBlock *block, RwUInt32 size, RwUInt32 alignment) {
 rwaPoolChunk *chunk = block->chunks;
 rwaPoolChunk *found = findChunk('''+args+');\n'+tail
 if n&2:h=h.replace('RwUInt32        needed = size + sizeof(rwaPoolChunk);','RwUInt32 needed = size;');body=body.replace('findChunk('+args+')','findChunk('+args.replace('size,','size + sizeof(rwaPoolChunk),',1)+')')
 if n&4:body=body.replace('found->prev = chunk;\n                found->next = chunk->next;', 'found->next = chunk->next;\n                found->prev = chunk;')
 VS['pool_search%d'%n]=[(s,s+'\n'+h+body)]
