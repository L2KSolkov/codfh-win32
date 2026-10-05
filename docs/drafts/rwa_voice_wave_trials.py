from pathlib import Path

src = Path('src/rwa/xbox/unit_24EC60.c').read_text()
draft = Path('docs/drafts/rwa_voice_draft.c').read_text()
body = draft[:draft.index('/* Applies what changed:')]
stop = draft[draft.index('/* Stops the buffer,'):draft.index('/* Whether the buffer must change format.')]
fmt = draft[draft.index('/* Whether the buffer must change format.'):]
base = src.replace('// match: _sub_24EE40 @', stop+'// match: _sub_24EE40 @')
base = base.replace('/* The default mix bins of a 3D buffer', fmt+'/* The default mix bins of a 3D buffer')
base = base.replace('// match: _sub_24F7E0 @', body+'// match: _sub_24F7E0 @')
VS = {'vw_base': [(src, base)]}
