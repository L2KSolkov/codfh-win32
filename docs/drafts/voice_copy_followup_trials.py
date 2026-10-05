# Historical: sub_1AA380 is now matched in unit_1A8B20.cpp.
# The checked value-returning voice_mask_copy supersedes these sweeps.
"""Reproduce current-header voice-copy checks (2026-10-01).
Run directly from the repository root. Uses a scratch include overlay;
never modifies production headers. Results are pscore rankings, not matches.
The original voice update remains best at six normalized lines.
"""
from pathlib import Path
Path('build/tooltmp/voice_overlay/types').mkdir(parents=True, exist_ok=True)
from pathlib import Path
import subprocess,os
old='        if (!lv_120.unk_00)\n        {\n        }\n        set_voice_peers(lv_120);'
h=Path('include/types/type_1DDE20_mask.h').read_text()
for count in range(4):
 p=Path('build/tooltmp/voice_overlay/types/type_1DDE20_mask.h');p.write_text(h.replace('type_1DDE20_mask(const type_1DDE20_mask &arg_0)\n    {','type_1DDE20_mask(const type_1DDE20_mask &arg_0)\n    {\n'+'        if (!unk_00) {}\n'*count))
 vs={}
 for c in range(5):vs['vg_%d%d'%(count,c)]=[(old,'        if (!lv_120.unk_00) {}\n'*c+'        set_voice_peers(lv_120);')]
 Path('build/tooltmp/voice_grid_variants.py').write_text('VS='+repr(vs)+'\n')
 env=dict(os.environ);env['PSCORE_INC']='C:/codfh-match/build/tooltmp/voice_overlay'
 subprocess.run(['python','tools/session/pscore.py','build/tooltmp/voice_grid_variants.py','?updateVoiceSubSystem@type_4F7EB8@@QAEXXZ','0x1AA380','src/recovered/unit_1A8B20.cpp','-j','6'],env=env,check=True)

from pathlib import Path
import subprocess,os
h=Path('include/types/type_1DDE20_mask.h').read_text()
for dest in range(3):
 for source in range(3):
  if dest==source==0:continue
  code='        if (!unk_00) {}\n'*dest+'        if (!arg_0.unk_00) {}\n'*source
  Path('build/tooltmp/voice_overlay/types/type_1DDE20_mask.h').write_text(h.replace('type_1DDE20_mask(const type_1DDE20_mask &arg_0)\n    {','type_1DDE20_mask(const type_1DDE20_mask &arg_0)\n    {\n'+code))
  Path('build/tooltmp/voice_source_variants.py').write_text('VS='+repr({'vs_%d%d'%(dest,source):[]})+'\n')
  env=dict(os.environ);env['PSCORE_INC']='C:/codfh-match/build/tooltmp/voice_overlay'
  subprocess.run(['python','tools/session/pscore.py','build/tooltmp/voice_source_variants.py','?updateVoiceSubSystem@type_4F7EB8@@QAEXXZ','0x1AA380','src/recovered/unit_1A8B20.cpp'],env=env,check=True)
