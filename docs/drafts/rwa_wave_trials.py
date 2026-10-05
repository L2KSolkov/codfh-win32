from pathlib import Path
s=Path('src/rwa/unit_2422B0.c').read_text();d='RwaWave *dword_506FFC;\nRwUInt32 dword_507000;\n'+Path('docs/drafts/rwa_wave_draft.c').read_text();VS={'wv_base':[(s,s+'\n'+d)]}
