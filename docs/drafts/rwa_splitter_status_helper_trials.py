exec(open('docs/drafts/rwa_splitter_status_trials.py').read());VS={}
a=d.index('                if (!obj->state.starved');b=d.index('                break;',a);body=d[a:b]
for n in range(16):
 helper='static __forceinline '+('rwaSplitter *' if n&2 else 'void')+' splitStatus('+('RwInt32 mode, rwaSplitter *obj' if n&1 else 'rwaSplitter *obj, RwInt32 mode')+') {\n'+body+ ('return obj;\n' if n&2 else '')+'}\n'
 u=d[:a]+('                obj = ' if n&2 else '                ')+ 'splitStatus('+('mode, obj' if n&1 else 'obj, mode')+');\n'+d[b:]
 if n&4:helper=helper.replace('if (mode == 3)','switch (mode) { case 3:').replace('                if (mode == 1)', '                break; }\n                if (mode == 1)')
 if n&8:helper=helper.replace('                if (mode == 1)\n                {\n                    obj->state.node.status = 3;\n                }','');u=u.replace(');\n                break;\n            case 8:',');\n                if (mode == 1) obj->state.node.status = 3;\n                break;\n            case 8:')
 VS['ssh_%d'%n]=[(s,s+'\n'+helper+u)]
