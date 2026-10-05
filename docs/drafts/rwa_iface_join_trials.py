exec(open('docs/drafts/rwa_iface_trials.py').read());VS={}
a=d.index('// match: _sub_243E20');b=d.index('// match: _sub_243FF0');f=d[a:b];p=f.index('    def->noInputs');q=f.index('    return def;',p);init=f[p:q]
for n in range(4):
 head=f[:f.index('    if (!def)')]
 alloc='def = (RwaObjInterfaceDef *)sub_243670(unk_50708C, rwaMEMHINTDUR_EVENT | rwaID_80A);'
 if n==0:body='    if (!def) { '+alloc+' if (def) def->flags=0; } else def->flags=2;\n    if (def) {\n'+init+'    }\n    return def;\n}\n'
 if n==1:body='    if (def) def->flags=2;\n    else { '+alloc+' if (!def) goto done; def->flags=0; }\n'+init+'done:\n    return def;\n}\n'
 if n==2:body='    if (!def) { '+alloc+' if (!def) goto done; def->flags=0; }\n    else def->flags=2;\n'+init+'done:\n    return def;\n}\n'
 if n==3:body='    if (!def) { '+alloc+' if (!def) return def; def->flags=0; }\n    else { def->flags=2; goto initialize; }\ninitialize:\n'+init+'    return def;\n}\n'
 VS['ij_%d'%n]=[(s,s+'\n'+d[:a]+head+body)]
