from pathlib import Path
src=Path('src/rwa/unit_23CC10.c').read_text()
draft=Path('docs/drafts/listeneragent_spatial_draft.c').read_text()
base=src.replace('// match: _sub_23D150 @',draft+'\n// match: _sub_23D150 @')
VS={'listeneragent_spatial_base':[(src,base)]}
