from pathlib import Path
s=Path('src/rwa/unit_24D9F0.c').read_text();d=Path('docs/drafts/rwa_fixup_draft.c').read_text();d=d[d.index('extern RwaUniqueID'):d.index('// match: _sub_24D9F0')];VS={'fx_base':[(s,s+'\n'+d)]}
