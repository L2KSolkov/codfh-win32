from pathlib import Path
s=Path('src/rwa/rwastreamsourceobj.c').read_text();d=Path('docs/drafts/rwa_streamsource_draft.c').read_text();VS={'src_base':[(s,s+'\n'+d)]}
