exec(open('docs/drafts/rwa_alloc_alignment_trials.py').read())
base=VS['flalign_07'][0][1];VS={}
old='''
                if (entry)
                {
                    break;
                }
'''
for n in range(8):
 u=base
 if n&1:
  u=u.replace(old,'').replace('                checkEntries -= 8;\n            }', '                checkEntries -= 8;\n            }\n            if (entry)\n                break;')
 if n&2:
  u=u.replace('for (bit = 0; bit < 8; bit++, checkEntries--)', 'for (bit = 0; bit < 8 && checkEntries > 0; bit++, checkEntries--)').replace('                    if (checkEntries <= 0)\n                    {\n                        break;\n                    }\n\n','')
 if n&4:
  u=u.replace('    RwUInt32            entry = 0;', '    void *entry = NULL;').replace('entry = rwaFreeListBlockData(block, bitmapSize, freeList->alignment) +\n                                (bit + i * 8) * freeList->entrySize;', 'entry = (void *)(rwaFreeListBlockData(block, bitmapSize, freeList->alignment) +\n                                (bit + i * 8) * freeList->entrySize);')
 VS['flexit_%02d'%n]=[(s,u)]
