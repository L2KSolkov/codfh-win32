from pathlib import Path
s=Path('src/rwa/unit_2449C0.c').read_text()
d=Path('docs/drafts/rwa_streamcache_clients_followup.c').read_text();d=d[d.index('// match: _sub_2450C0'):]
VS={'cacheopen_base':[(s,s+'\n'+d)]}
