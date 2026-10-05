from pathlib import Path
s=Path('src/rwa/unit_243670.c').read_text()
base=s
if '/* Reconstructed alignment expression' in base:
 start=base.index('/* Reconstructed alignment expression')
 end=base.index('// match: _sub_2437A0', start)
 base=base[:start]+base[end:]
d=Path('docs/drafts/rwa_freelist_draft.c').read_text().split('// match: _sub_2437A0')[0]
VS={}
for n in range(16):
 u=d
 if n&1:
  u=u.replace('    RwUInt32            entry = 0;', '    RwUInt32            entry = 0;\n    RwUInt32 checkEntries;')
  u=u.replace('hint = freeList->entriesPerBlock;', 'checkEntries = freeList->entriesPerBlock;').replace('hint--', 'checkEntries--').replace('hint <= 0', 'checkEntries <= 0').replace('hint -= 8', 'checkEntries -= 8')
 if n&2:
  u=u.replace('        RwUInt32    i;', '        RwUInt32    i;\n        RwUInt8 *heap = block->bitmap;').replace('block->bitmap[i]', 'heap[i]')
 if n&4:
  u=u.replace('bits | mask', '(RwUInt8)(block->bitmap[i] | mask)' if not n&2 else '(RwUInt8)(heap[i] | mask)')
 if n&8:
  u=u.replace('while (&block->link != head)', 'while (&block->link != head && !entry)').replace('        if (entry)\n        {\n            return (void *)entry;\n        }\n\n','')
 VS['flalloc_%02d'%n]=[(s,base+'\n'+u)]
