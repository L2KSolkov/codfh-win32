from pathlib import Path
s=Path('src/rwa/rwaobj.c').read_text();d=Path('docs/drafts/rwa_obj_exec_draft.c').read_text();a=d.index('// match: _sub_23F140');d=d[:a]+d[:a].replace('_sub_23F0D0','_sub_23F140').replace('sub_23F0D0','sub_23F140').replace('unk2C','unk30').replace('0x0023F0D0','0x0023F140')
VS={'oe_base':[(s,s+'\n'+d)],'oe_obj':[(s,s+'\n'+d.replace('status = ok;', 'status = (RwBool)obj;'))]}
