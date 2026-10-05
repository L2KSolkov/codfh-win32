"""Delta-morph probes: _XboxDmorphAtomicInstanceCallback 0x2F28D0
src/rw/plugin/dmorph/xbox/dmorphpipeg.c via pscore.py. See questions.md.
"""
exec(open('docs/drafts/dmorph_entry_order_trials.py').read())
VS={}
for mask in range(8):
 t=body
 if mask&1:t=t.replace('RwInt32             numTexCoordSets;','RwUInt32            numTexCoordSets;')
 if mask&2:t=t.replace('RwInt32             numVertices;','RwUInt32            numVertices;')
 if mask&4:t=t.replace('numTexCoordSets > 4','(RwUInt32)numTexCoordSets > 4')
 VS['tc_%d'%mask]=[(anchor,t+anchor),inc]
