from pathlib import Path
body = Path('docs/drafts/rwa_streamsource_followup.c').read_text()
anchor = '// match: _sub_2412F0 @'
old = 'extern void sub_2472E0(rwaQueue *queue, rwaQueueItem *items, RwUInt32 count);'
proto = old.replace('extern void ', 'extern rwaQueue *').replace('RwUInt32 count', 'RwUInt8 count')
VS = {'smallagent_sourcebase': [(anchor, body + anchor), (old, proto)]}
