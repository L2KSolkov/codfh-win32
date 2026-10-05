exec(open('docs/drafts/rwa_streamcache_param_trials.py').read())
best=VS['sp_024'][0][1][len(s)+1:]
VS={}
# Put error cleanup in first status branch, with failed seek jumping back.
a=best.index('    client->header[0] = 0;');b=best.index('\n}',a)
cleanup=best[a:b]
u=best[:a]+best[b:]
u=u.replace('        client->mode = 0;\n    }\n    else', '        client->mode = 0;\n      failed:\n'+cleanup+'\n        return;\n    }\n    else',1).replace('        if (position >= 0)','        if (position < 0) goto failed;\n        if (position >= 0)',1)
VS['sh_move']=[(s,s+'\n'+u)]
for i,order in enumerate(permutations(range(3))):
 start=best.index('        case 1:',best.index('sub_245060(void'))
 end=best.index('\n    }',start)
 cases=best[start:end];parts=[cases[cases.index('        case %d:'%v):cases.index('        case %d:'%(v+1))] if v<3 else cases[cases.index('        case 3:'):] for v in [1,2,3]]
 x=best[:start]+''.join(parts[k] for k in order)+best[end:]
 VS['sh_case%d'%i]=[(s,s+'\n'+x)]
