exec(open('docs/drafts/rwa_wave_trials.py').read())
VS={}
for n in range(16):
 t=d
 if n&1:t=t.replace('            buffer = converted;','            buffer = converted;\n        }\n        else\n        {\n            dword_507000 = offset;').replace('        dword_507000 = offset;\n        result', '        dword_507000 = offset;\n        result')
 if n&2:t=t.replace('        RwaWave    *result;', '        RwaWave    *result;\n        void *uploadBuffer;').replace('        dword_506FFC = wave;', '        uploadBuffer = buffer;\n        dword_506FFC = wave;').replace('result = upload(wave, offset, buffer, size);','result = upload(wave, offset, uploadBuffer, size);')
 if n&4:t=t.replace('        dword_506FFC = wave;\n        dword_507000 = offset;','        dword_507000 = offset;\n        dword_506FFC = wave;')
 if n&8:t=t.replace('    void           *converted = NULL;','    void           *converted;').replace('        RwaWave    *result;','        RwaWave    *result;').replace('        if (!sub_2429D0(source, target))','        converted = NULL;\n        if (!sub_2429D0(source, target))')
 VS['wu_%d'%n]=[(s,s+'\n'+t)]
