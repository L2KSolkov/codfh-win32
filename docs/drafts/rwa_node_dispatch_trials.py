from pathlib import Path
s=Path('src/rwa/unit_246FD0.c').read_text();base=s[:s.index('// match: _sub_247220')].replace('extern RwBool sub_247220', 'extern void sub_247220').replace('extern RwBool sub_247260', 'extern void sub_247260');d=Path('docs/drafts/rwa_node_draft.c').read_text();d=d[d.index('// match: _sub_247220'):d.index('// match: _sub_247250')]+d[d.index('// match: _sub_247260'):d.index('// match: _sub_247290')]
VS={'nd_base':[(s,base+'\n'+d)]}
for n in range(3):
 u=d
 for name in ['setter','getter']:
  typ=['RwUInt32','RwUInt16','RwInt32'][n];u=u.replace('    '+name+'->func', '    '+typ+' param = '+name+'->param;\n    '+name+'->func').replace(name+'->param, value','param, value')
 VS['nd_%d'%n]=[(s,base+'\n'+u)]
