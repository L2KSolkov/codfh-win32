exec(open('docs/drafts/rwa_nv_trials.py').read());VS={}
for n in range(8):
 u=d
 if n&1:u=u.replace('sub_24DBA0(RwaWave *wave,','sub_24DBA0(RwaWave *input,').replace('    rwaStreamedMemory *memory', '    RwaWave *wave = input;\n    rwaStreamedMemory *memory')
 if n&2:u=u.replace('    return wave->buffer ? wave : NULL;', '    if (!wave->buffer) return NULL;\n    return wave;')
 if n&4:u=u.replace('        return NULL;', '        goto failed;').replace('    return wave->buffer ? wave : NULL;', '    if (wave->buffer) return wave;\nfailed:\n    return NULL;') if not n&2 else u.replace('        return NULL;', '        goto failed;').replace('    if (!wave->buffer) return NULL;\n    return wave;', '    if (wave->buffer) return wave;\nfailed:\n    return NULL;')
 VS['nc_%d'%n]=[(s,s+'\n'+u)]
