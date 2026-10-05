exec(open('docs/drafts/rwa_splitter_read_helper_trials.py').read());VS={}
for n in range(32):
 u=f
 if n&1:u=u.replace('            return NULL;', '            goto fail;')
 if n&2:u=u.replace('    if (!(obj->state.masks[*index] & (1 << track)))\n    {\n        return NULL;', '    if (!(obj->state.masks[*index] & (1 << track)))\n    {\n        goto fail;')
 if n&4:u=u.replace('        *index = 0;', '        *index = 0;\n        return item;')
 if n&8:u=u.replace('    rwaQueueItem *item;', '    rwaQueueItem *item = NULL;')
 if n&16:u=u.replace('    return item;', '    goto done;')
 u=u.rstrip()[:-1]+'\nfail:\n    item = NULL;\ndone:\n    return item;\n}\n'
 VS['sret_%d'%n]=[(s,s+'\n'+u)]
