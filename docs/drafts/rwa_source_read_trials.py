from pathlib import Path
s=Path('src/rwa/unit_247430.c').read_text();d=Path('docs/drafts/rwa_source_draft.c').read_text();d=d[d.index('// match: _sub_248520'):d.index('// match: _sub_248810')];prefix='extern RwBool sub_247FE0(rwaDecoderState *, RwUInt32, RwUInt32);\n';VS={'read_base':[(s,s+'\n'+prefix+d)]}
