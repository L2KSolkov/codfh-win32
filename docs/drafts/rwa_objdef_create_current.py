"""Replay the matched definition-creation group against current headers."""
from pathlib import Path
s = Path('src/rwa/rwaobjdef.c').read_text()
base = s
for addr in ['23DAA0', '23DB30', '23DE20', '23DF00', '23DFB0']:
    marker = '// match: _sub_' + addr + ' @ '
    if marker in base:
        a = base.index(marker)
        b = base.index('\n}\n', a) + 3
        base = base[:a] + base[b:]
d = Path('docs/drafts/rwa_objdef_create_followup.c').read_text()
VS = {'objcreate_current': [(s, base + '\n' + d)]}
