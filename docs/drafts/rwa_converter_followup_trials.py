"""2026-10-01 RWA converter follow-up. Use pscore.py with RWA_TRIAL:
 channel (default): _sub_249D00 0x249D00 src/rwa/unit_249490.c
 encoder: _sub_24BD30 0x24BD30 src/rwa/unit_249490.c
 decoder: _sub_24BDE0 0x24BDE0 src/rwa/unit_249490.c
No exact matches. Scores include relocation/padding artifacts.
"""
import os
mode = os.environ.get('RWA_TRIAL', 'channel')
if mode == 'channel':
    from pathlib import Path
    s=Path('src/rwa/unit_249490.c').read_text();a=s.index('RwUInt32\nsub_249D00(');b=s.index('\n}\n',a)+3;body=s[a:b];VS={'cc_base':[]}
    for mask in range(8):
     t=body
     if mask&1:
      i=t.rindex('    return size;');t=t[:i].replace('return size;','goto done;')+'done:\n'+t[i:]
     if mask&2:t=t.replace('    out = dest + offset;','    dest += offset;\n    out = dest;')
     if mask&4:t=t.replace('    RwUInt8     bitDepth;','    RwUInt32 bitDepth;')
     VS['cc_%d'%mask]=[(body,t)]

    saved = dict(VS)
    VS={}
    for mask in range(1,16):
     t=body;decl='';assign=''
     if mask&1:decl+='RwUInt8 channels;\n';assign+='channels = from->noChannels;\n'
     if mask&2:decl+='RwUInt8 flags;\n';assign+='flags = from->flags;\n'
     if mask&4:decl+='RwUInt8 targetChannels;\n';assign+='targetChannels = to->noChannels;\n'
     t=t.replace('    RwUInt32    i;','    RwUInt32 i;\n'+decl)
     idx=t.index('    if (from->noChannels == 1')
     tail=t[idx:]
     if mask&1:tail=tail.replace('from->noChannels','channels')
     if mask&2:tail=tail.replace('from->flags','flags')
     if mask&4:tail=tail.replace('to->noChannels','targetChannels')
     t=t[:idx]+assign+tail
     if mask&8:t=t.replace('RwUInt8 channels;','RwUInt32 channels;').replace('RwUInt8 flags;','RwUInt32 flags;').replace('RwUInt8 targetChannels;','RwUInt32 targetChannels;')
     VS['cv_%02d'%mask]=[(body,t)]

    saved.update(VS)
    import re
    loops=[]
    for m in re.finditer(r'for \(i = 0;',body):
     a=m.start();k=body.index('{',a);depth=1;e=k+1
     while depth:
      if body[e]=='{':depth+=1
      if body[e]=='}':depth-=1
      e+=1
     loops.append((a,e))
    VS={}
    for mask in range(1,1<<len(loops)):
     t=body
     for j,(a,b) in reversed(list(enumerate(loops))):
      if mask&(1<<j):t=t[:a]+'{ RwUInt32 loopIndex;\n'+re.sub(r'\bi\b','loopIndex',t[a:b])+'\n}'+t[b:]
     VS['cs_%02d'%mask]=[(body,t)]

    VS.update(saved)

elif mode == 'encoder':
    from pathlib import Path
    s=Path('src/rwa/unit_249490.c').read_text();d=Path('docs/drafts/rwa_adpcm_draft.c').read_text();a=d.index('RwUInt8\nsub_24BD30(');b=d.index('\n}\n',a)+3;body=d[a:b];VS={'ie_base':[(s,s+'\n'+body)]}
    from itertools import permutations
    old='''    RwInt32     step = word_42FD38[*index];
        RwInt32     s = sample;
        RwInt32     diff = s - *predicted;
        RwUInt8     code = 0;'''
    for n,order in enumerate(permutations(['step','s','diff','code'])):
     if order.index('s')>order.index('diff'):continue
     lines=dict(step='RwInt32 step = word_42FD38[*index];',s='RwInt32 s = sample;',diff='RwInt32 diff = s - *predicted;',code='RwUInt8 code = 0;')
     t=body.replace(old,'    '+'\n    '.join(lines[x] for x in order))
     VS['ie_order%02d'%n]=[(s,s+'\n'+t)]
    for mask in range(1,8):
     t=body
     if mask&1:t=t.replace('    RwInt32     step =','    RwInt32 oldIndex = *index;\n    RwInt32     step =').replace('word_42FD38[*index]','word_42FD38[oldIndex]')
     if mask&2:t=t.replace('    RwInt32     diff = s - *predicted;','    RwInt32 previous = *predicted;\n    RwInt32 diff = s - previous;')
     if mask&4:t=t.replace('RwUInt8     code = 0;','RwUInt32 code = 0;')
     VS['ie_local%d'%mask]=[(s,s+'\n'+t)]

    saved = dict(VS)
    VS={}
    neg=['s - step + diff','s + diff - step','diff - step + s','diff + s - step','s - (step - diff)']
    pos=['step - diff + s','s + step - diff','s - diff + step','step + s - diff','s - (diff - step)']
    for i,x in enumerate(neg):
     for j,y in enumerate(pos):
      t=body.replace('*predicted = s - step + diff;','*predicted = '+x+';').replace('*predicted = step - diff + s;','*predicted = '+y+';')
      VS['ip_%d%d'%(i,j)]=[(s,s+'\n'+t)]

    VS.update(saved)

elif mode == 'decoder':
    from pathlib import Path
    s=Path('src/rwa/unit_249490.c').read_text();d=Path('docs/drafts/rwa_adpcm_draft.c').read_text();a=d.index('// match: _sub_24BDE0');b=d.index('\n}\n',a)+3;body=d[a:b];VS={'id_base':[(s,s+'\n'+body)]}
    for n in range(8):
     t=body
     if n&1:t=t.replace('RwUInt32    diff =','RwInt32 diff =')
     if n&2:t=t.replace('RwInt32     value = *predicted;','RwInt32 value;\n    value = *predicted;')
     if n&4:t=t.replace('RwUInt32    diff = ((code & 7) * 2 + 1) * word_42FD38[*index] >> 3;','RwUInt32 step = word_42FD38[*index];\n    RwUInt32 diff = ((code & 7) * 2 + 1) * step >> 3;')
     VS['id_%d'%n]=[(s,s+'\n'+t)]

