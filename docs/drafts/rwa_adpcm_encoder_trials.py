from pathlib import Path
s=Path('src/rwa/unit_249490.c').read_text();d=Path('docs/drafts/rwa_adpcm_draft.c').read_text();d=d[d.index('RwUInt8'+chr(10)+'sub_24BD30'):d.index('// match: _sub_24BDE0')];VS={'enc_base':[(s,s+'\n'+d)]}

