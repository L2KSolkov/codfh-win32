exec(open('docs/drafts/rwa_splitter_status_trials.py').read());VS={}
a=d.index('            case 7:');b=d.index('            case 8:');f=d[a:b]
for n in range(16):
 u=d
 if n&1:u=u.replace('                    break;\n                }\n                if (mode == 1)', '                }\n                if (mode == 1)')
 if n&2:u=u.replace('                if (mode == 1)','check_one:\n                if (mode == 1)',1); ix=u.index('            case 7:');u=u[:ix]+u[ix:].replace('                if (mode == 1)\n                {\n                    obj->state.node.status = 3;\n                }','                goto check_one;',1)
 if n&4:u=u.replace('                if (mode == 3)\n                {\n                    obj->state.node.status = 4;\n                }', '                switch (mode) { case 3: obj->state.node.status = 4; break; }')
 if n&8:u=u.replace('                if (!obj->state.starved && mode == 2)', '                if (mode == 2 && !obj->state.starved)')
 VS['scf_%d'%n]=[(s,s+'\n'+u)]
