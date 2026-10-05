from pathlib import Path
s=Path('src/rwa/unit_243670.c').read_text();d=Path('docs/drafts/rwa_freelist_draft.c').read_text();d=d[d.index('// match: _sub_2437A0'):];VS={'flf_base':[(s,s+'\n'+d)]}

