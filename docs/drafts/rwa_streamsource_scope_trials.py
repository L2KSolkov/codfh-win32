exec(open('docs/drafts/rwa_streamsource_trials.py').read())
VS={}
decls=d[d.index('    RwUInt32            count;'):d.index('    if (failed)')]
for mask in range(16):
 t=d
 if mask&1:t=t.replace(decls,'').replace('    else\n    {','    else\n    {\n'+decls)
 if mask&2:t=t.replace('        obj->state.callback.func = sub_240E20;\n        obj->state.callback.data = obj;', '        { rwaQueueCallback *callback = &obj->state.callback;\n        callback->func = sub_240E20;\n        callback->data = obj; }')
 if mask&4:t=t.replace('    RwUInt32            i;','').replace('        for (i = 0; i < count; i++)','        { RwUInt32 i;\n        for (i = 0; i < count; i++)').replace('        sub_2472E0','        }\n        sub_2472E0')
 if mask&8:t=t.replace('        obj->status = 1;','        obj->status = 1;\n        _RwaStreamNodeCreationComplete(obj);\n        return;')
 VS['src_m%d'%mask]=[(s,s+'\n'+t)]

