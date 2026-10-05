from pathlib import Path
s=Path('src/rwa/unit_24CC50.c').read_text();d=Path('docs/drafts/rwa_splitter_draft.c').read_text();f=d[d.index('// match: _sub_24CD50'):d.index('// match: _sub_24CFF0')];VS={}
start=f.index('    if (++*index >= obj->state.noBuffers)')
for n in range(8):
 u=f[:start]+'''    ++*index;
    if (*index >= obj->state.noBuffers)
    {
        *index = 0;
        return item;
    }
    goto done;
failed:
    item = NULL;
done:
    return item;
}
'''
 u=u.replace('            return NULL;', '            goto failed;').replace('    if (!(obj->state.masks[*index] & (1 << track)))\n    {\n        return NULL;', '    if (!(obj->state.masks[*index] & (1 << track)))\n    {\n        goto failed;')
 if n&1:u=u.replace('    ++*index;\n    if (*index >= obj->state.noBuffers)', '    if (++*index >= obj->state.noBuffers)')
 if n&2:u=u.replace('    goto done;\nfailed:\n    item = NULL;\ndone:\n    return item;', '    return item;\nfailed:\n    return NULL;')
 if n&4:u=u.replace('    rwaQueueItem *item;', '    rwaQueueItem *item = NULL;')
 VS['splitreadtail_%d'%n]=[(s,s+'\n'+u)]
