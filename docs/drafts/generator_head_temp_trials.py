"""Generator head temporary probes. Set GF_FACTORY=sub_122410 (default)
or sub_1224F0, then pscore the corresponding YAHPAVProjectileGeneratorTrigger
symbol against src/recovered/unit_11EE20.cpp. No candidate matches.
"""
from pathlib import Path
import os
s=Path('src/recovered/unit_11EE20.cpp').read_text();a=s.index('RwInt32 '+os.environ.get('GF_FACTORY','sub_122410')+'(');b=s.index('\n}\n',a)+3;body=s[a:b]
VS={'gf_base':[]}
forms=['1 ? dword_4CE8F8 : 0','0 ? 0 : dword_4CE8F8','true ? dword_4CE8F8 : dword_4CE8F8','false ? dword_4CE8F8 : dword_4CE8F8','(type_1227C0 *)dword_4CE8F8','static_cast<type_1227C0 *>(dword_4CE8F8)','(0, dword_4CE8F8)','(1 ? get_generator_list() : 0)']
for k,f in enumerate(forms):VS['gf_expr%d'%k]=[(body,body.replace('get_generator_list()', '('+f+')'))]
for n in range(4):
 helper='static __forceinline void SetGeneratorHeadTrial(type_1227C0 *object, type_1227C0 * const &head) { object->unk_100 = head; }\n'
 expr=['dword_4CE8F8','(type_1227C0 *)dword_4CE8F8','get_generator_list()','1 ? dword_4CE8F8 : 0'][n]
 t=body.replace('var_14->unk_100 = get_generator_list();','SetGeneratorHeadTrial(var_14, '+expr+');')
 VS['gf_ref%d'%n]=[(body,helper+t)]
