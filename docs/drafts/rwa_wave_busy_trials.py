exec(open('docs/drafts/rwa_wave_trials.py').read())
VS={};a=d.index('RwBool\nsub_242570');e=d.index('// match: _sub_242810');old=d[a:e]
forms=[
'''    if (wave->waveDef->busy) return wave->waveDef->busy(wave); return FALSE;''',
'''    RwaWaveDef *def = wave->waveDef; if (def->busy) return def->busy(wave); return FALSE;''',
'''    return wave->waveDef->busy ? wave->waveDef->busy(wave) : FALSE;''',
'''    RwBool result = FALSE; if (wave->waveDef->busy) result = wave->waveDef->busy(wave); return result;''',
'''    RwBool (*busy)(RwaWave *) = wave->waveDef->busy; if (busy) { return busy(wave); } else { return FALSE; }''',
]
for n,f in enumerate(forms):VS['wb_%d'%n]=[(s,s+'\n'+d[:a]+'RwBool\nsub_242570(RwaWave *wave)\n{\n'+f+'\n}\n\n'+d[e:])]
