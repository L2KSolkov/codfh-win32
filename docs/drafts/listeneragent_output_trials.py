exec(open('docs/drafts/listeneragent_baseline.py').read())
VS={}
for mask in range(32):
    b=base
    for bit,field in enumerate(['right.x','right.y','right.z']):
        if mask&(1<<bit):b=b.replace('listener->'+field+' =','*(volatile RwReal *)&listener->'+field+' =')
    if mask&8:b=b.replace('listener->dirty |=','*(volatile RwUInt32 *)&listener->dirty |=')
    for productmode in range(8):
        c=b
        for bit,term in enumerate(['at.y','at.x','up.x']):
            if productmode&(1<<bit):
                c=c.replace(' * listener->'+term,' * *(const volatile RwReal *)&listener->'+term)
        if mask&16:c=c.replace('listener->right.', 'listener->right.') .replace('listener->dirty |=','listener->dirty = *(const volatile RwUInt32 *)&listener->dirty |')
        VS['listeneragent_out_%02d_%d'%(mask,productmode)]=[(src,c)]
