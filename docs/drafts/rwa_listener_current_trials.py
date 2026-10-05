from pathlib import Path
src=Path('src/rwa/unit_23CC10.c').read_text()
draft=Path('docs/drafts/rwa_listener_orient_draft.c').read_text()
up=draft[:draft.index('// match: _sub_23D320 @')]
at=draft[draft.index('// match: _sub_23D320 @'):draft.index('extern const RwReal')]
setup=draft[draft.index('extern const RwReal'):]
base=src.replace('// match: _sub_23D300 @',up+'// match: _sub_23D300 @').replace('// match: _sub_23D380 @',at+'// match: _sub_23D380 @')
VS={'lis_base':[(src,base)]}
