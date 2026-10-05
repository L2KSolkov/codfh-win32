from pathlib import Path
from concurrent.futures import ThreadPoolExecutor
import sys
sys.path.insert(0,'tools')
from build_probes import compile_unit,flags_for,load_flags
from match import compare
from xbe import Xbe
from coff import Coff
import capstone
g={}
exec(Path('docs/drafts/view_state_identity_trials.py').read_text(),g)
root=Path('build/tooltmp/view_qualified');root.mkdir(exist_ok=True)
data=Path('include/game/data.h').read_text(encoding='latin1')
decl='void sub_1B6DE0(RwReal arg_0);'
assert data.count(decl)==1
x=Xbe('orig/Game_XboxMultiplayer.xbe')
sym='?sub_1AB440@type_4F7EB8@@QAEXXZ'
forms=[('plain',g['x']),('const','(const RwReal)'+g['x']),
       ('volatile','(volatile RwReal)'+g['x']),('constvolatile','(const volatile RwReal)'+g['x'])]
work=[(i,q,n,e) for i,q in enumerate(['RwReal','const RwReal','volatile RwReal','const volatile RwReal']) for n,e in forms]
def run(item):
    i,q,n,e=item
    tag=str(i)+'_'+n
    d=root/tag;inc=d/'game';inc.mkdir(parents=True,exist_ok=True)
    (inc/'data.h').write_text(data.replace(decl,'void sub_1B6DE0('+q+' arg_0);'),encoding='latin1')
    s=d/'trial.cpp';o=d/'trial.obj'
    s.write_text(g['src'].replace(g['old'],g['body'].replace(g['x'],e)))
    msgs=[]
    flags=['/I'+str(d),'/Iinclude']+flags_for('src/recovered/unit_1A8B20.cpp',load_flags())
    if not compile_unit(str(s),str(o),flags,msgs):return tag,str(msgs)
    c=Coff(str(o));code,rels=c.function_bytes(c.find_function(sym))
    return tag,compare(str(o),sym,0x1AB440,x,{})[1].splitlines()[0],len(code)
with ThreadPoolExecutor(4) as pool:
    for result in pool.map(run,work):print(*result)
