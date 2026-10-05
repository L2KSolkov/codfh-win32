exec(open('docs/drafts/rwa_source_seek_result_trials.py').read());b=VS['sk_fix3'][0][1];VS={}
for n in range(4):
 u=b
 if n&1:u=u.replace('        ReleaseSemaphore(state->semaphore, 1, NULL);\n        return FALSE;', '        goto failed;').replace('    return TRUE;\n}', '    return TRUE;\nfailed:\n    ReleaseSemaphore(state->semaphore, 1, NULL);\n    return FALSE;\n}')
 if n&2:u=u.replace('    RwUInt32 high, low;', '    RwUInt32 high, low;\n    RwBool result = FALSE;').replace('        ReleaseSemaphore(state->semaphore, 1, NULL);\n        return FALSE;', '        goto unlock;').replace('    ReleaseSemaphore(state->semaphore, 1, NULL);\n    return TRUE;', '    result = TRUE;\nunlock:\n    ReleaseSemaphore(state->semaphore, 1, NULL);\n    return result;')
 VS['se_%d'%n]=[(s,u)]
