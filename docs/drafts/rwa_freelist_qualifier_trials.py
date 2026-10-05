exec(open('docs/drafts/rwa_freelist_free_trials.py').read());VS={}
forms=['block->bitmap[byte]', '((volatile rwaFreeListBlock *)block)->bitmap[byte]', '((volatile RwUInt8 *)block->bitmap)[byte]', 'byte[block->bitmap]', '*(block->bitmap + byte)', '*((RwUInt8 *)block + byte + 8)', '*(byte + (RwUInt8 *)block + 8)', '*(RwUInt8 *)((RwUInt32)block + byte + 8)']
iforms=['block->bitmap[i]', '((volatile rwaFreeListBlock *)block)->bitmap[i]', '((volatile RwUInt8 *)block->bitmap)[i]', 'i[block->bitmap]', '*(block->bitmap + i)', '*((RwUInt8 *)block + i + 8)', '*(i + (RwUInt8 *)block + 8)', '*(RwUInt8 *)((RwUInt32)block + i + 8)']
for n in range(64):
 u=d.replace('block->bitmap[byte]',forms[n%8]).replace('block->bitmap[i]',iforms[n//8])
 VS['flq_%d'%n]=[(s,s+'\n'+u)]
