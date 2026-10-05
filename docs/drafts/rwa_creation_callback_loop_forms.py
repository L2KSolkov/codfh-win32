exec(open('docs/drafts/rwa_creation_callback_signature_trials.py').read())
VS={}
for kind in range(6):
    b=body
    head='        for (i = 0; i < count; i++)\n        {'
    tail='            positions[i].unit = 2;\n        }'
    if kind==1:
        b=b.replace(head,'        i = 0;\n        while (i < count)\n        {').replace(tail,'            positions[i].unit = 2;\n            ++i;\n        }')
    if kind==2:
        b=b.replace(head,'        i = 0;\n        if (count > 0)\n        {\n        do\n        {').replace(tail,'            positions[i].unit = 2;\n        } while (++i < count);\n        }')
    if kind==3:
        b=b.replace(head,'        i = 0;\n        if (count != 0)\n        {\n        do\n        {').replace(tail,'            positions[i].unit = 2;\n        } while (++i != count);\n        }')
    if kind==4:
        b=b.replace(head,'        i = 0;\n        if (count > 0)\n        {\n        for (;;)\n        {').replace(tail,'            positions[i].unit = 2;\n            if (++i == count) break;\n        }\n        }')
    if kind==5:
        b=b.replace(head,'        for (i = 0; i != count; ++i)\n        {')
    for save in range(3):
        c=b
        if save==1:c=c.replace('    RwUInt32 count;\n','').replace('count = obj->state.noItems;', 'failed = obj->state.noItems;').replace('count','((RwUInt32)failed)')
        if save==2:c=c.replace('    RwUInt32 count;', '    RwUInt32 count;\n    RwUInt32 savedCount;').replace('count = obj->state.noItems;', 'count = obj->state.noItems;\n        savedCount = count;').replace('(rwaQueueItem *)arg, count);','(rwaQueueItem *)arg, savedCount);')
        VS['crloop_%d_%d'%(kind,save)]=[(anchor,c+anchor),(old,old.replace('extern void ','extern rwaQueue *').replace('RwUInt32 count','RwUInt8 count'))]
