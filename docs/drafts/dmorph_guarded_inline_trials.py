"""Guarded delta-morph follow-up probes. pscore target
_XboxDmorphAtomicInstanceCallback 0x2F28D0
src/rw/plugin/dmorph/xbox/dmorphpipeg.c. No exact candidate.
"""
from pathlib import Path
p=Path('docs/drafts/dmorph_count_block_trials.py').read_text()
exec(p.replace('dmorph_instance_followup.c','dmorph_instance_guarded_followup.c'))
