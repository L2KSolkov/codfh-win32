---
name: godfather-only-for-missing-source
description: Use the Godfather IDA builds only for RenderWare code whose source is NOT in the RW tree (the Xbox driver); tree files are matched from the tree source + image
metadata:
  node_type: memory
  type: feedback
  originSessionId: 81642346-cc05-4535-a5bd-fffa4a408d89
  modified: 2026-09-30T18:08:04.706Z
---

Only consult the Godfather builds (ports 13339/13340) when the source is not present in the RW tree (D:\RW_372_src / src/rw imported files) — in practice the Xbox driver (driver/xbox). For RW files that exist in the tree (e.g. plcore/baresour.c), work from the tree's source and the image only.

**Why:** the user said so (2026-09-30) after I looked up `_rwResourcesClose` in the debug build; the tree source is the reference for those files and the image decides the differences.

**How to apply:** before querying gf.py/gfpy.py, check `git ls-files src/rw` / D:\RW_372_src for the function's file; if it is there, don't use Godfather. Related: [[godfather-ida-reference]], [[rw-import-then-edit]].
