from pathlib import Path
s=Path('src/rwa/unit_244220.c').read_text()
d=Path('docs/drafts/rwa_pool_draft.c').read_text()
a=d.index('                if (!found)'); b=d.index('                return found + 1;')+len('                return found + 1;')
insert=d[a:b]
VS={}
for n in range(8):
 u=d.replace('    rwaPoolChunk   *chunk = block->chunks;', '    rwaPoolChunk   *chunk = block->chunks;\n    rwaPoolChunk *found;').replace('            rwaPoolChunk   *found;','')
 u=u.replace(insert,'                goto foundEntry;')
 u=u.replace('    return NULL;\n}', '    return NULL;\nfoundEntry:\n'+insert+'\n}')
 if n&1:u=u.replace('    RwUInt32        needed = size + sizeof(rwaPoolChunk);','    RwUInt32 needed;').replace('    do\n','    needed = size + sizeof(rwaPoolChunk);\n    do\n')
 if n&2:u=u.replace('            RwUInt32        used = (RwUInt32)chunk + chunk->size;', '            RwUInt8 *used = (RwUInt8 *)chunk + chunk->size;').replace('(RwUInt32)found >= used + sizeof(rwaPoolChunk)', '(RwUInt8 *)found >= used + sizeof(rwaPoolChunk)')
 if n&4:u=u.replace('RwUInt32 alignment)', 'RwUInt32 inputAlignment)').replace('    RwUInt32        needed', '    RwUInt32 alignment = inputAlignment;\n    RwUInt32        needed').replace('    RwUInt32 needed;', '    RwUInt32 alignment = inputAlignment;\n    RwUInt32 needed;')
 VS['poolflow_%d'%n]=[(s,s+'\n'+u)]
