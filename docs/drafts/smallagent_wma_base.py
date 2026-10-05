from pathlib import Path
body=Path('docs/drafts/rwa_wma_draft.c').read_text().split('/* The play position')[0]
anchor="/* The play queue's read:"
old='extern void RwaStreamNodeGetParams(rwaDecoder *obj, rwaStreamNodeParams *params);'
proto=old.replace('void ', 'rwaDecoder *', 1)
VS={'smallagent_wmabase':[(anchor,body+anchor),(old,proto)]}
