from pathlib import Path
s=Path('src/rwa/rwaobjdef.c').read_text();d=Path('docs/drafts/rwa_objdef_draft.c').read_text();d=d[:d.index('// match: _sub_23DCA0')]
VS={'od_base':[(s,s+'\n'+d)]}
