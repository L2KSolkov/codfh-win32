from pathlib import Path
s=Path('src/rwa/unit_23FAD0.c').read_text();d=Path('docs/drafts/rwa_stream_draft.c').read_text().split('// match: _sub_23FEE0')[0]
h='/* Original caller passes a second argument unused by 245E90. */\nextern void sub_245E90(rwaStreamPlayer *player, const void *unusedSet);\n'
VS={'su_base':[(s,s+'\n'+h+d)]}
