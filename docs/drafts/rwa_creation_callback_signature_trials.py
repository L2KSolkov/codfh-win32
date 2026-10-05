from pathlib import Path
src=Path('src/rwa/rwastreamsourceobj.c').read_text()
body=Path('docs/drafts/rwa_streamsource_followup.c').read_text()
anchor='// match: _sub_2412F0 @'
assert anchor in src
old='extern void sub_2472E0(rwaQueue *queue, rwaQueueItem *items, RwUInt32 count);'
VS={}
for bits in range(4):
    new=old
    if bits&1:new=new.replace('extern void ', 'extern rwaQueue *')
    if bits&2:new=new.replace('RwUInt32 count','RwUInt8 count')
    VS['crsig_%d'%bits]=[(anchor,body+anchor),(old,new)]
