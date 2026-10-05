from pathlib import Path
s=Path('src/rwa/xbox/unit_250B20.c').read_text()
d=Path('docs/drafts/rwa_wma_draft.c').read_text()
d=d[d.index('// match: _sub_2516E0'):].replace('static rwaWmaSource *','rwaWmaSource *')
anchor='// match: _sub_251CE0 @'
VS={'wmcr_00':[(anchor,d+anchor)]}
