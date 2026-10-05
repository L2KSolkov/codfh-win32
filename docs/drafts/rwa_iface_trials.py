from pathlib import Path
s=Path('src/rwa/unit_243AE0.c').read_text();d=Path('docs/drafts/rwa_iface_draft.c').read_text();VS={'if_base':[(s,s+'\n'+d)]}
