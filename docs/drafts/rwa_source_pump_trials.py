from pathlib import Path
s=Path('src/rwa/unit_247430.c').read_text();base=s[:s.index('extern void sub_248810(void *')];d=Path('docs/drafts/rwa_source_draft.c').read_text()
def fn(a,b):return d[d.index('// match: _sub_'+a):d.index('// match: _sub_'+b)]
h=fn('2475D0','247660');f=fn('248410','248520');prefix='extern void sub_248810(void *, RwUInt32, RwInt32, RwInt32, rwaDecoderState *);\nextern void sub_247660(rwaDecoderState *);\n';VS={'srpump_base':[(s,base+'\n'+prefix+h+f)]}
