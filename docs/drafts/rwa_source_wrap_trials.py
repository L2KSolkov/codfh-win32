from pathlib import Path
s=Path('src/rwa/unit_247430.c').read_text();d=Path('docs/drafts/rwa_source_draft.c').read_text();d=d[d.index('// match: _sub_247F20'):d.index('// match: _sub_247FE0')];VS={'wrap_base':[(s,s+'\n'+d)]}
