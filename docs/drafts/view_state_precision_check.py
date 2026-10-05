from pathlib import Path
import sys
sys.path.insert(0,'tools')
from build_probes import compile_unit,flags_for,load_flags
from match import compare
from xbe import Xbe
from coff import Coff
import capstone

g={}
exec(Path('docs/drafts/view_state_identity_trials.py').read_text(),g)
flags=flags_for('src/recovered/unit_1A8B20.cpp',load_flags())+['/Iinclude']
root=Path('build/tooltmp/view_precision');root.mkdir(exist_ok=True)
sym='?sub_1AB440@type_4F7EB8@@QAEXXZ'
md=capstone.Cs(capstone.CS_ARCH_X86,capstone.CS_MODE_32)
x=Xbe('orig/Game_XboxMultiplayer.xbe')
for option in ['/Op','/Op-']:
    for name,expr in [('plain',g['x']),('cast','(RwReal)(RwDouble)'+g['x']),('multiply',g['x']+' * 1.0f')]:
        tag=name+('_precise' if option=='/Op' else '_fast')
        s=root/(tag+'.cpp');o=root/(tag+'.obj')
        s.write_text(g['src'].replace(g['old'],g['body'].replace(g['x'],expr)))
        msgs=[]
        if not compile_unit(str(s),str(o),flags+[option],msgs):
            print(tag,'ERROR',msgs);continue
        print(tag,compare(str(o),sym,0x1AB440,x,{})[1].splitlines()[0])
        c=Coff(str(o));code,rels=c.function_bytes(c.find_function(sym))
        for off,n,t in rels:
            if n=='?sub_1B6DE0@type_4FB9E0@@QAEXM@Z' and off>0x100:
                print('; '.join(i.mnemonic+' '+i.op_str for i in md.disasm(bytes(code[off-25:off+4]),off-25)))
