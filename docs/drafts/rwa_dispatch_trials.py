from pathlib import Path
s=Path('src/rwa/rwaobject.c').read_text();base=s[:s.index('// match: _sub_23F8E0')];d=Path('docs/drafts/rwa_object_dispatch_draft.c').read_text();VS={'dp_base':[(s,base+'\n'+d)]}
