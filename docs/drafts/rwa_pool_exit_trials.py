exec(open('docs/drafts/rwa_pool_cursor_trials.py').read());VS={}
a=d.index('                if (!found)');b=d.index('                return found + 1;')+len('                return found + 1;');chunk=d[a:b]
for n in range(8):
 u=d.replace('    rwaPoolChunk   *chunk = block->chunks;', '    rwaPoolChunk   *chunk = block->chunks;\n    rwaPoolChunk *found;').replace('            rwaPoolChunk   *found;','')
 u=u.replace(chunk,'                goto allocate;')
 u=u.replace('    return NULL;\n}', '    return NULL;\nallocate:\n'+chunk+'\n}')
 if n&1:u=u.replace('found->prev = chunk;\n                found->next = chunk->next;', 'found->next = chunk->next;\n                found->prev = chunk;')
 if n&2:u=u.replace('    RwUInt32        needed = size + sizeof(rwaPoolChunk);','    RwUInt32 needed;').replace('    do\n','    needed = size + sizeof(rwaPoolChunk);\n    do\n')
 if n&4:u=u.replace('                if (!found)\n                {\n                    return NULL;\n                }','                if (!found) goto fail;').replace('    return NULL;\nallocate:', 'fail:\n    return NULL;\nallocate:')
 VS['pool_exit%d'%n]=[(s,s+'\n'+u)]
