exec(open('docs/drafts/rwa_wma_create_current_trials.py').read())
VS={}
early='''        sub_243B80(obj->state.objInterface);
        sub_247120((rwaDecoder *)obj, NULL, NULL);
        return NULL;'''
mem='''        sub_250B30();
        sub_243B80(state->objInterface);
        sub_247120((rwaDecoder *)obj, NULL, NULL);
        return NULL;'''
cleanup='''        state->decoder->vtbl->release(state->decoder);
        CloseHandle(state->semaphore);
        sub_2421B0(state->items);
        sub_250B30();
        sub_243B80(state->objInterface);
        sub_247120((rwaDecoder *)obj, NULL, NULL);
        return NULL;'''
for n in range(8):
 u=d
 if n&1:
  u=u.replace('    rwaWmaPosition *positions;', '    void *failedInterface;\n    rwaWmaPosition *positions;')
  u=u.replace(early,'        failedInterface = obj->state.objInterface;\n        goto early_failed;')
  u=u.replace(mem,mem.replace('        sub_243B80(state->objInterface);','        failedInterface = state->objInterface;\nearly_failed:\n        sub_243B80(failedInterface);'),1)
 if n&2:
  start=u.index('    if (state->decoder->vtbl->getLength')
  u=u[:start]+u[start:].replace(cleanup,'        goto length_failed;',1)
  u=u.rstrip()[:-1]+'\nlength_failed:\n'+cleanup+'\n}\n'
 if n&4:
  chunk='''        sub_2421B0(state->items);
        sub_250B30();
        sub_243B80(state->objInterface);
        sub_247120((rwaDecoder *)obj, NULL, NULL);
        return NULL;'''
  start=u.index('    if (!sub_2416D0(&state->semaphore')
  u=u[:start]+u[start:].replace(chunk, '        goto semaphore_failed;',1)
  if n&2:
   k=u.index('length_failed:\n')
   u=u[:k]+u[k:].replace('        sub_2421B0(state->items);','semaphore_failed:\n        sub_2421B0(state->items);',1)
  else:
   u=u.rstrip()[:-1]+'\nsemaphore_failed:\n'+chunk+'\n}\n'
 VS['wmcf_%02d'%n]=[(anchor,u+anchor)]
