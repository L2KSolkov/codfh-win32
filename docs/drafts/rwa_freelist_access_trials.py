exec(open('docs/drafts/rwa_freelist_free_trials.py').read());VS={}
for n in range(8):
 h='static __forceinline RwUInt8 *bitmapByte('+('RwUInt32 index, rwaFreeListBlock *block' if n&1 else 'rwaFreeListBlock *block, RwUInt32 index')+') { return &block->bitmap[index]; }\n'
 u=d.replace('block->bitmap[byte]','*bitmapByte('+('byte, block' if n&1 else 'block, byte')+')')
 if n&2:u=u.replace('block->bitmap[i]','*bitmapByte('+('i, block' if n&1 else 'block, i')+')')
 if n&4:u=u.replace('            block->bitmap[byte]', '            block->bitmap[byte]').replace('            *bitmapByte', '            { RwUInt8 *p = bitmapByte('+('byte, block' if n&1 else 'block, byte')+');\n            *p').replace('*p('+('byte, block' if n&1 else 'block, byte')+')','*p').replace('            block->link.prev->next', '            }\n            block->link.prev->next')
 if n&8:u=u.replace('RwUInt32    byte = index >> 3;', 'RwUInt32    byte;\n            byte = index >> 3;')
 VS['flh_%d'%n]=[(s,s+'\n'+h+u)]
