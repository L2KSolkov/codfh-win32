exec(open('docs/drafts/rwa_wave_trials.py').read());VS={}
for n in range(16):
 t=d
 if n&1:t=t.replace('    void           *converted = NULL;', '    void           *converted = NULL;\n    void *output = buffer;').replace('            buffer = converted;', '            output = converted;').replace('upload(wave, offset, buffer, size);','upload(wave, offset, output, size);')
 if n&2:t=t.replace('    void           *converted = NULL;', '    void           *converted = NULL;\n    RwUInt32 uploadOffset = offset;').replace('            offset = sub_2498D0', '            uploadOffset = sub_2498D0').replace('dword_507000 = offset;', 'dword_507000 = uploadOffset;').replace('result = upload(wave, offset,', 'result = upload(wave, uploadOffset,')
 if n&4:t=t.replace('RwaWaveFormat  *source','const RwaWaveFormat  *source').replace('RwaWaveFormat  *target','const RwaWaveFormat  *target')
 if n&8:t=t.replace('            buffer = converted;', '            buffer = converted;\n        }\n        else\n        {\n            offset = dword_507000 = offset;')
 VS['wl_%d'%n]=[(s,s+'\n'+t)]
