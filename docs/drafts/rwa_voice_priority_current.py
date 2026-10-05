from pathlib import Path
s=Path('src/rwa/rwavoicemanager.c').read_text()
d=Path('docs/drafts/rwa_voice_priority_draft.c').read_text()
d=d[d.index('// match: _sub_23E8E0'):]
VS={}
for n in range(8):
 u=d
 if n&1:
  u=u.replace('RwReal  maxDistance = rwaReal(sound->unk74);', 'RwUInt32 maxDistanceBits = sound->unk74;').replace('RwReal  minDistance = rwaReal(sound->unk70);', 'RwUInt32 minDistanceBits = sound->unk70;').replace('maxDistance * maxDistance', 'rwaReal(maxDistanceBits) * rwaReal(maxDistanceBits)').replace('distance > minDistance', 'distance > rwaReal(minDistanceBits)').replace('distance - minDistance', 'distance - rwaReal(minDistanceBits)').replace('maxDistance - minDistance', 'rwaReal(maxDistanceBits) - rwaReal(minDistanceBits)')
 if n&2:u=u.replace('if (distance > '+('rwaReal(minDistanceBits)' if n&1 else 'minDistance')+')', 'if (!(distance < '+('rwaReal(minDistanceBits)' if n&1 else 'minDistance')+'))')
 if n&4:u=u.replace('dword_5069EC.x - sound->unk58.x', 'dword_5069EC.x - *(volatile RwReal *)&sound->unk58.x').replace('dword_5069EC.y - sound->unk58.y', 'dword_5069EC.y - *(volatile RwReal *)&sound->unk58.y').replace('dword_5069EC.z - sound->unk58.z', 'dword_5069EC.z - *(volatile RwReal *)&sound->unk58.z')
 VS['vmcurrent_%d'%n]=[(s,s+'\n'+u)]
