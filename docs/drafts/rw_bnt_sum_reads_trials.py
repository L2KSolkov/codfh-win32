"""Ordinary BNT follow-up. pscore: __rpXboxVtxFmtInstBNT 0x2DDB50
src/rw/world/pipe/p2/xbox/xbvtxfmt.c. Best four normalized lines, not exact.
"""
exec(open('docs/drafts/rw_bnt_eachread_trials.py').read())
old='RwReal length2 = RwV3dDotProductMacro(currentBinormal, currentBinormal);'
new='RwReal length2 = currentBinormal->y * currentBinormal->y; length2 += currentBinormal->x * currentBinormal->x; length2 += currentBinormal->z * currentBinormal->z;'
VS={'bt_'+name:[(a,b.replace(old,new)) for a,b in edits] for name,edits in VS.items()}
