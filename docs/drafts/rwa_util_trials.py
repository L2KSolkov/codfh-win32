from pathlib import Path
s=Path('src/rwa/unit_241F90.c').read_text();d=Path('docs/drafts/rwa_util_draft.c').read_text();h=d[d.index('extern const'):d.index('// match: _sub_241F90')];d=d[d.index('// match: _sub_241FD0'):];VS={'ut_base':[(s,s+'\n'+h+d)]}
