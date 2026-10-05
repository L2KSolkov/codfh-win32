---
name: rw-xbox-header-shapes
description: RW near misses can come from the null-driver headers (vertex layout/macros) or third-party edits in D:\RW_372_src; check those before register searches
metadata:
  node_type: memory
  type: project
  originSessionId: 81642346-cc05-4535-a5bd-fffa4a408d89
  modified: 2026-10-01T15:29:36.852Z
---

2026-10-01: DefaultPathStroke2d and rt2dFontShowBitmap (frames 0x20 too big) matched once include/rw/sdk/rwcore.h used the Xbox RxObjSpace3DVertex (pos, normal, RwUInt32 color at +0x18, u, v) with the D3D8 pip2model.h macros (packed ARGB RwIm3DVertexSetRGBA, direct-field RwIm3DVertexSetPos). The Godfather PDB gives the Xbox type layouts (gfpy.py + ida_typeinf print). rtpitexdImage2TextureRead matched after removing a Korean-commented 2005 edit (min() loop bound) from the tree's copy.

**Why:** our rw/sdk headers are the null driver's; the image was built against the Xbox driver's, and D:\RW_372_src carries a third party's edits (DDonSS, gemani, Korean comments).
**How to apply:** for an RW near miss, first diff the offsets/macros the function touches against the Godfather type and the D3D8/xbox header shapes, and grep the function for non-ASCII comments or editor names. Then use tools/session/pscore.py for statement/declaration forms. Related: [[rw-differences-doc]], [[others-checked-and-inline-budget]].
