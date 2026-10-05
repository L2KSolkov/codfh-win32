exec(open('docs/drafts/rwa_wma_defaults_shape_trials.py').read())
VS={}
for n in range(16):
 b=body
 if n&1:b=b.replace('params->unk04 = 1;', '*(volatile RwUInt32 *)&params->unk04 = 1;')
 if n&2:b=b.replace('params->fileType = 1;', '*(volatile RwInt32 *)&params->fileType = 1;')
 if n&4:b=b.replace('params->unk00 = 0;', '*(volatile RwUInt32 *)&params->unk00 = 0;')
 if n&8:b=b.replace('rwaWmaSource *obj,', 'rwaWmaSource *volatile input,').replace('{\n', '{\n    rwaWmaSource *obj = input;\n',1)
 add('access_%d'%n,b)
