---
name: rw36-structural-near-misses
description: "RW tree near misses blamed on \"registers\" were often 3.6-vs-3.7.2 structure; read the image's control flow against the source before register tuning; tools/rwrank.py lists them"
metadata:
  node_type: memory
  type: project
  originSessionId: 81642346-cc05-4535-a5bd-fffa4a408d89
  modified: 2026-10-01T00:19:46.685Z
---

On 2026-09-30, several RenderWare tree functions listed as "register differences" turned out to be structural differences between 3.6 and 3.7.2 (or third-party edits in the tree). Each matched once the image's xdis was read side by side with the source:
- rpusrdat.c: `UserDataStreamRead`/`Write` read and write int/real data one element at a time. Their static callees' custom calling conventions then matched too.
- tool/2d/font.c: `RwOsGetFileInterface()` file table passed as a parameter to `FontReadMetrics2d1/2/3`; `Rt2dFontShow` returns the font; a duplicated `else if` in the tree was a third-party edit.
- rpanisot.c: the Xbox hook is behind `XBOX_DRVMODEL_H`, so it needs `|| defined(_XBOX)` (the build uses the null driver model).
- A database name can be wrong: 0x2A6540 "MatfxPluginIsAttached" was `RwEngineGetPluginOffset`.

**Why:** rwmissed/rwrank pair image functions by name and report diff counts, which hides an extra loop or call.

**How to apply:** for each `tools/rwrank.py` entry, run `tools/rwd.py build/src/...obj SYM ADDR` and `tools/xdis.py`. Look for missing or extra calls, loops and arguments first; only then try register and slot variants with `tools/ptry.py`. Log every change in docs/rw-differences.md. Related: [[rw-differences-doc]], [[c-block-layout-and-slots]].
