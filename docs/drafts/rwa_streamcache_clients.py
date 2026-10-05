from pathlib import Path
s=Path('src/rwa/unit_2449C0.c').read_text();d=Path('docs/drafts/rwa_streamcache_draft.c').read_text()
t=d[:d.index('// match: _sub_244AF0')]+d[d.index('// match: _sub_244FA0'):]
VS={'sc_clients':[(s,s+'\n'+t)]}
