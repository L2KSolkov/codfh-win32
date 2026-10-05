from pathlib import Path
s=Path('src/rwa/xbox/unit_24DA70.c').read_text();d=Path('docs/drafts/rwa_nv_draft.c').read_text();d=d[d.index('// match: _sub_24DAD0'):d.index('// match: _sub_24DB10')]+d[d.index('// match: _sub_24DBA0'):d.index('// match: _sub_24DC60')];VS={'nv_base':[(s,s+'\n'+d)]}
