---
name: rw-macro-operand-order
description: "Float products of a local and a pointed-to float in the wrong fld/fmul order — write them through RenderWare's vector macros (rw/bavector.h)"
metadata:
  node_type: memory
  type: project
  originSessionId: 81642346-cc05-4535-a5bd-fffa4a408d89
  modified: 2026-09-26T00:59:39.231Z
---

Found 2026-09-25 (sub_8F3E0, sub_92620; docs/toolchain.md "Products through RenderWare's vector macros"): a dot product written out by hand always compiles local-first. Through `RwV3dDotProductMacro(&local, (RwV3d *)ptr)` the y/z terms compile memory-first (`fld [ecx+4]; fmul local`), which the image has. Cross products likewise.

**Why:** no operand order, `(&x)->` spelling or array access reproduced it; only the macro did.
**How to apply:** when a vector-math function diffs only in fld/fmul operand order, rewrite it with RwV3dSubMacro/CrossProductMacro/DotProductMacro before trying anything else. Related: [[inline-reserve-and-placement-delete]].
