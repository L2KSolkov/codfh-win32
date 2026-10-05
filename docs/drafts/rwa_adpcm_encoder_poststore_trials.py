exec(open('docs/drafts/rwa_adpcm_encoder_trials.py').read());VS={}
for n in range(16):
 u=d
 if n&1:u=u.replace('RwInt32     diff = s - *predicted;', 'RwInt32 diff = *predicted;').replace('    if (diff < 0)', '    diff = s - diff;\n    if (diff < 0)')
 if n&2:u=u.replace('    *index += word_42FD18[code];','    { RwInt32 value = *index + word_42FD18[code];\n    *index = value;\n    }')
 if n&4:u=u.replace('    if (*predicted > 32767)', '    { RwInt32 value = *predicted;\n    if (value > 32767)').replace('else if (*predicted < -32768)', 'else if (value < -32768)').replace('    *index +=', '    }\n    *index +=').replace('    { RwInt32 value = *index', '    }\n    { RwInt32 value = *index')
 if n&8:u=u.replace('    if (code & 8)\n    {\n        *predicted = s - step + diff;\n    }\n    else\n    {\n        *predicted = step - diff + s;\n    }', '    if (!(code & 8))\n    {\n        *predicted = step - diff + s;\n    }\n    else\n    {\n        *predicted = s - step + diff;\n    }')
 VS['encpost_%d'%n]=[(s,s+'\n'+u)]
