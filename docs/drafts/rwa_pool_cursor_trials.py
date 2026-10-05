from pathlib import Path
s=Path('src/rwa/unit_244220.c').read_text();d=Path('docs/drafts/rwa_pool_draft.c').read_text();VS={'pool_base':[(s,s+'\n'+d)]}
