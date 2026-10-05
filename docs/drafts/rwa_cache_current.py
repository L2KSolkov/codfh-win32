from pathlib import Path
s=Path('src/rwa/unit_2449C0.c').read_text()
base=s
if '// match: _sub_2449C0' in base:
 base=base[:base.index('// match: _sub_2449C0')]
d=Path('docs/drafts/rwa_streamcache_clients_followup.c').read_text()
VS={'cachecurrent':[(s,base+'\n'+d)]}
