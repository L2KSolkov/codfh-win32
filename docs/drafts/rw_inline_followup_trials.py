"""Reproduce the 2026-10-01 typed-inline follow-up trials.

Set RW_TRIAL to bnt (default), bntcomp, or stream and run pscore.py with:
 bnt: __rpXboxVtxFmtInstBNT 0x2DDB50 src/rw/world/pipe/p2/xbox/xbvtxfmt.c
 bntcomp: __rpXboxVtxFmtInstBNTComp 0x2DE0F0 (same source)
 stream: _RwStreamSkip 0x2A7210 src/rw/src/plcore/bastream.c

No candidate matches. Baselines remain 14, 53, and 18 normalized lines;
the stream score includes jump-table artifacts. match.py is authoritative.
"""
import os
mode = os.environ.get('RW_TRIAL', 'bnt')
if mode == 'bnt':
    from pathlib import Path
    d=Path('docs/drafts/rw_xbvtxfmt_bnt_followup.c').read_text();body=d[d.index('#define SMALL_FLOAT'):];anchor='// match: __rpXboxVtxFmtUnInstV3d @ 0x002DD7F0'
    s=Path('src/rw/world/pipe/p2/xbox/xbvtxfmt.c').read_text()
    import re
    anchor=re.search(r'// match: __rpXboxVtxFmtUnInstV3d[^\n]*',s)[0]
    VS={'bi_base':[(anchor,body+anchor)]}
    for n in range(8):
     params='RwV3d *dst, const RwV3d *a, const RwV3d *b'
     expr='RwV3dCrossProduct(dst, a, b);'
     if n&1:params='const RwV3d *a, const RwV3d *b, RwV3d *dst'
     if n&2:expr='dst->x = a->y * b->z - a->z * b->y; dst->y = a->z * b->x - a->x * b->z; dst->z = a->x * b->y - a->y * b->x;'
     if n&4:expr=expr.replace('a->y * b->x','b->x * a->y')
     h='static __forceinline void CrossTrial('+params+') { '+expr+' }\n'
     args='currentBinormal, currentTangent, currentNormal' if not n&1 else 'currentTangent, currentNormal, currentBinormal'
     t=body.replace('RwV3dCrossProduct(currentBinormal, currentTangent, currentNormal);','CrossTrial('+args+');')
     VS['bi_cross%d'%n]=[(anchor,h+t+anchor)]
    for n in range(4):
     h='static __forceinline RwReal DotTrial(const RwV3d *a, const RwV3d *b) { return '+('a->x * b->x + a->y * b->y + a->z * b->z' if not n&1 else 'a->z * b->z + (a->x * b->x + a->y * b->y)')+'; }\n'
     t=body.replace('RwV3dDotProductMacro(currentBinormal, currentBinormal)','DotTrial(currentBinormal, currentBinormal)')
     if n&2:t=t.replace('_rwV3dNormalizeMacro(unused, currentTangent, currentTangent);','{ RwReal length2 = DotTrial(currentTangent, currentTangent); rwInvSqrtMacro(&unused, length2); RwV3dScale(currentTangent, currentTangent, unused); }')
     VS['bi_dot%d'%n]=[(anchor,h+t+anchor)]

elif mode == 'bntcomp':
    from pathlib import Path
    d=Path('docs/drafts/rw_xbvtxfmt_bntcomp_draft.c').read_text();body=d[d.index('#define SMALL_FLOAT'):];anchor='// match: __rpXboxVtxFmtUnInstV3d @ 0x002DE6B0';VS={'cu_base':[(anchor,body+anchor)]}
    start=body.index('        unpacked.x =');end=body.index('        RwV3dCrossProduct',start);chunk=body[start:end]
    for n in range(8):
     params='RwV3d *dst, const RpVertexNormal *src' if not n&1 else 'const RpVertexNormal *src, RwV3d *dst'
     h='static __forceinline void UnpackTrial('+params+') { '+chunk.replace('unpacked.','dst->').replace('normal[n].','src->')+' }\n'
     args='&unpacked, normal + n' if not n&1 else 'normal + n, &unpacked'
     t=body.replace(chunk,'        UnpackTrial('+args+');\n')
     if n&2:t=t.replace('RwV3d unpacked;','RwV3d unpacked;\n        const RpVertexNormal *currentNormal = normal + n;').replace('UnpackTrial('+args+');','UnpackTrial('+args.replace('normal + n','currentNormal')+');')
     if n&4:
      t=t.replace('        UnpackTrial('+args.replace('normal + n','currentNormal' if n&2 else 'normal + n')+');\n','')
      t=t.replace('        _rwV3dNormalizeMacro','        UnpackTrial('+args.replace('normal + n','currentNormal' if n&2 else 'normal + n')+');\n        _rwV3dNormalizeMacro')
     VS['cu_unpack%d'%n]=[(anchor,h+t+anchor)]
    for n in range(4):
     t=body.replace('RwV3d unpacked;','RwV3d unpacked;\n        const RpVertexNormal *currentNormal = normal + n;').replace('normal[n].','currentNormal->')
     if n&1:t=t.replace(chunk.replace('normal[n].','currentNormal->'),'').replace('        _rwV3dNormalizeMacro',chunk.replace('normal[n].','currentNormal->')+'        _rwV3dNormalizeMacro')
     if n&2:t=t.replace('        RwV3dCrossProduct(currentBinormal, currentTangent, &unpacked);','        { const RwV3d *unpackedNormal = &unpacked; RwV3dCrossProduct(currentBinormal, currentTangent, unpackedNormal); }')
     VS['cu_local%d'%n]=[(anchor,t+anchor)]

elif mode == 'stream':
    from pathlib import Path
    s=Path('src/rw/src/plcore/bastream.c').read_text();a=s.index('RwStreamSkip(RwStream *stream, RwUInt32 offset)');b=s.index('\n}\n',a)+3;body=s[a:b];VS={'ss_base':[]}
    for n in range(8):
     params='RwUInt32 position, RwUInt32 offset' if not n&1 else 'RwUInt32 offset, RwUInt32 position'
     h='static __forceinline RwUInt32 SkipSumTrial('+params+') { return position + offset; }\n'
     args='smpMem->position, offset' if not n&1 else 'offset, smpMem->position'
     t=body.replace('smpMem->position + offset','SkipSumTrial('+args+')')
     if n&2:t=t.replace('smpMem->position += offset;','smpMem->position = SkipSumTrial('+args+');')
     if n&4:t=t.replace('RwStreamMemory     *smpMem = &stream->Type.memory;','RwStreamMemory *smpMem = &stream->Type.memory;\n                RwUInt32 position = smpMem->position;').replace('SkipSumTrial('+args+')','SkipSumTrial('+args.replace('smpMem->position','position')+')')
     VS['ss_inline%d'%n]=[('RwStream *\n'+body,h+'RwStream *\n'+t)] if 'RwStream *\n'+body in s else [(body,t),(s[:a].rsplit('\n',2)[0]+'\n',h+s[:a].rsplit('\n',2)[0]+'\n')]
    for n in range(6):
     decl=['RwUInt32 position = smpMem->position;','RwUInt32 skip = offset;','RwUInt32 size = smpMem->nSize;'][n%3]
     t=body.replace('RwStreamMemory     *smpMem = &stream->Type.memory;','RwStreamMemory *smpMem = &stream->Type.memory;\n                '+decl)
     if n%3==0:t=t.replace('if (smpMem->position + offset','if (position + offset')
     if n%3==1:t=t.replace('if (smpMem->position + offset','if (smpMem->position + skip')
     if n%3==2:t=t.replace('> smpMem->nSize)', '> size)')
     if n>=3:t=t.replace('smpMem->position += offset;', 'smpMem->position = '+('position + offset' if n%3==0 else 'smpMem->position + skip' if n%3==1 else 'smpMem->position + offset')+';')
     VS['ss_local%d'%n]=[(body,t)]

