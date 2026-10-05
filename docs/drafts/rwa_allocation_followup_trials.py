"""RWA allocation/list trials, 2026-10-01. Run with pscore.py:
 RWA_TRIAL=pool: _sub_2442D0 0x2442D0 src/rwa/unit_244220.c
 RWA_TRIAL=bitmap: _sub_2FD5D0 0x2FD5D0 src/rwa/unit_2FD5D0.c
 RWA_TRIAL=symbol (default): _sub_244650 0x244650 src/rwa/rwasymboltable.c
No exact matches; normalized scores are diagnostic only.
"""
import os
mode = os.environ.get('RWA_TRIAL', 'symbol')
if mode == 'pool':
    from pathlib import Path
    s=Path('src/rwa/unit_244220.c').read_text();body=Path('docs/drafts/rwa_pool_draft.c').read_text();VS={'pa_base':[(s,s+'\n'+body)]}

    VS={'ph_base':VS['pa_base']}
    a=body.index('                if (!found)');b=body.index('                return found + 1;')+len('                return found + 1;');chunk=body[a:b]
    for n in range(4):
     params='rwaPoolBlock *block, rwaPoolChunk *found, rwaPoolChunk *chunk, RwUInt32 size' if not n&1 else 'rwaPoolChunk *found, rwaPoolChunk *chunk, RwUInt32 size, rwaPoolBlock *block'
     args='block, found, chunk, size' if not n&1 else 'found, chunk, size, block'
     h='static __forceinline void *InsertTrial('+params+') {\n'+chunk+'\n}\n'
     t=body[:a]+'return InsertTrial('+args+');'+body[b:]
     if n&2:h=h.replace('found->next = chunk->next;', 'found->next = chunk->next;') .replace('rwaPoolChunk *found,','rwaPoolChunk * const found,')
     VS['ph_%d'%n]=[(s,s+'\n'+h+t)]
    for n in range(8):
     t=body
     if n&1:t=t.replace('RwUInt32        needed = size + sizeof(rwaPoolChunk);','RwUInt32 needed;').replace('    do\n','    needed = size + sizeof(rwaPoolChunk);\n    do\n',1)
     if n&2:t=t.replace('~(alignment - 1)','(0U - alignment)')
     if n&4:t=t.replace('return found + 1;','return (RwUInt8 *)found + sizeof(rwaPoolChunk);')
     VS['ph_shape%d'%n]=[(s,s+'\n'+t)]

elif mode == 'bitmap':
    from pathlib import Path
    s=Path('src/rwa/unit_2FD5D0.c').read_text();d=Path('docs/drafts/rwa_bitmap_draft.c').read_text();b=d.index('/* Allocates a run');body=d[:b];VS={'bc_base':[(s,s+'\n'+body)]}
    for n in range(8):
     t=body
     if n&1:t=t.replace('    RwUInt32    rounded = (numUnits + 7) & ~7;','').replace('    shift =','    numUnits = (numUnits + 7) & ~7;\n    shift =',1).replace('rounded','numUnits')
     if n&2:t=t.replace('RwUInt8     flags = 0;','RwUInt32 flags = 0;')
     if n&4:t=t.replace('    shift = (RwUInt8)(rwaLog2U('+('numUnits' if n&1 else 'rounded')+') + 1);\n    numBytes = '+('numUnits' if n&1 else 'rounded')+' >> 3;','    numBytes = '+('numUnits' if n&1 else 'rounded')+' >> 3;\n    shift = (RwUInt8)(rwaLog2U('+('numUnits' if n&1 else 'rounded')+') + 1);')
     VS['bc_life%d'%n]=[(s,s+'\n'+t)]

    saved = dict(VS)
    VS={}
    for n in range(4):
     t=body.replace('    RwUInt32    numBytes;\n','').replace('    numBytes = rounded >> 3;','    rounded >>= 3;').replace('numBytes','rounded')
     if n&1:t=t.replace('    RwUInt32    rounded = (numUnits + 7) & ~7;','').replace('    shift =','    numUnits = (numUnits + 7) & ~7;\n    shift =',1).replace('rounded','numUnits')
     # Restore the actual struct member name after local substitutions.
     t=t.replace('bitmap->rounded','bitmap->numBytes').replace('bitmap->numUnits','bitmap->numBytes')
     if n&2:t=t.replace('bitmap->shift = shift;','bitmap->shift = shift;').replace('shift = (RwUInt8)(rwaLog2U('+('numUnits' if n&1 else 'rounded')+') + 1);','shift = (RwUInt8)(rwaLog2U('+('numUnits' if n&1 else 'rounded')+'));\n    shift++;')
     VS['bu_%d'%n]=[(s,s+'\n'+t)]

    VS.update(saved)

elif mode == 'symbol':
    from pathlib import Path
    s=Path('src/rwa/rwasymboltable.c').read_text();d=Path('docs/drafts/rwa_symtab_draft.c').read_text();a=d.index('// match: _sub_244690');add=d[:a];remove=d[a:];VS={'st_base':[(s,s+'\n'+d)]}
    for mask in range(1,8):
     t=add
     if mask&1:t=t.replace('    paramType->link.prev = NULL;','    rwaLink *link = &paramType->link;\n    paramType->link.prev = NULL;',1).replace('paramType->link.','link->').replace('&paramType->link;','link;') .replace('rwaLink *link = link;','rwaLink *link = &paramType->link;')
     if mask&2:t=t.replace('    table->noParamTypes++;','    table->noParamTypes++;') .replace('{\n','{\n    rwaLink *head = &table->list;\n',1).replace('table->list.next','head->next').replace('&table->list;','head;').replace('rwaLink *head = head;','rwaLink *head = &table->list;')
     if mask&4:t=t.replace('    paramType->link.prev = NULL;\n    paramType->link.next = NULL;','').replace('    link->prev = NULL;\n    link->next = NULL;','')
     VS['st_%d'%mask]=[(s,s+'\n'+t+remove)]

    saved = dict(VS)
    VS={}
    init='    paramType->link.prev = NULL;\n    paramType->link.next = NULL;'
    seq='''    paramType->link.next = table->list.next;
        paramType->link.prev = &table->list;
        table->list.next->prev = &paramType->link;
        table->list.next = &paramType->link;'''
    for mask in range(8):
     h='';t=add
     if mask&1:
      h+='static __forceinline void InitTrial(rwaLink *p) { p->prev = NULL; p->next = NULL; }\n'
      t=t.replace(init,'    InitTrial(&paramType->link);')
     if mask&2:
      h+='static __forceinline void AddTrial(rwaLink *head, rwaLink *p) { p->next = head->next; p->prev = head; head->next->prev = p; head->next = p; }\n'
      t=t.replace(seq,'    AddTrial(&table->list, &paramType->link);')
     if mask&4:t=t.replace('    table->noParamTypes++;','    ++table->noParamTypes;')
     VS['sh_%d'%mask]=[(s,s+'\n'+h+t+remove)]

    saved.update(VS)
    VS={}
    for mask in range(16):
     t=add
     if mask&1:t=t.replace('{\n','{\n    rwaLink *link = &paramType->link;\n',1).replace('paramType->link.next','link->next')
     if mask&2:t=t.replace('paramType->link.prev','link->prev') if mask&1 else t
     if mask&4:t=t.replace('    paramType->link.prev = &table->list;','    paramType->link.prev = head;').replace('    link->prev = &table->list;','    link->prev = head;').replace('    table->list.next->prev','    head->next->prev').replace('    table->list.next =','    head->next =').replace('= table->list.next;','= head->next;')
     if mask&4:
      point='    '+('link->next' if mask&1 else 'paramType->link.next')+' = head->next;'
      t=t.replace(point,'    { rwaLink *head = &table->list;\n'+point).replace('    table->noParamTypes++;','    }\n    table->noParamTypes++;')
     if mask&8:t=t.replace('&paramType->link;','link;').replace('rwaLink *link = link;','rwaLink *link = &paramType->link;') if mask&1 else t
     VS['sl_%02d'%mask]=[(s,s+'\n'+t+remove)]

    VS.update(saved)

