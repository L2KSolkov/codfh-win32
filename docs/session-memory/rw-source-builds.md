---
name: rw-source-builds
description: "RenderWare code in the image compiles byte-exact from D:\\RW_372_src with /O2 /Ob2 /G6 /Gy /arch:SSE /DRWGLOBALSIZE; units live in src/rw, headers in include/rw/sdk"
metadata:
  node_type: memory
  type: project
  originSessionId: 81642346-cc05-4535-a5bd-fffa4a408d89
  modified: 2026-09-30T10:23:13.498Z
---

2026-09-30: the in-project RenderWare (rtdict 0x22B1B0, uvanim 0x22B5D0–0x22CB5B) matched straight from RenderWare 3.7.2's own sources (47 functions). Flags rule `src/rw/*` in config/flags.txt: `/O2 /Ob2 /G6 /Gy /arch:SSE /W3 /D_XBOX /DNDEBUG /DRWGLOBALSIZE=0x1000 /Iinclude/rw/sdk`.

- Headers: the SDK's generated null-target headers (D:\RW_372_src\RWSDK\build\noasm\include\null) vendored in include/rw/sdk; RwGlobals edited: drop the third party's `debugLogFunc`, add 0x2C unknown bytes before stringFuncs (image: strcmp slot 0x5201F4, rwmalloc 0x520214, ourGlobals 0x5200E0 = alias `_ourGlobals`).
- Sources: copy RW's .c (and the source dir's local .h like rpplugin.h) into src/rw/<same path>, add `// match: _Name @ 0x...` above each definition (tools/rwannot.py), rows via rwrows.py, build, then rwlinkfix.py --apply aliases calls the image makes to ICF-folded copies. Commit per RW source unit.
- Probe first with tools/rwall.py SRC.c LO HI flags (use MSYS_NO_PATHCONV=1).
- The drop is a third party's edited 3.7.2; the image is 3.6 Xbox: functions that differ need editing toward 3.6 (M6).

**How to apply:** try this on the RenderWare core library region next (RW 3.6 core 1,507 functions, D:\RW_372_src\RWSDK\src). See [[icf-placement]].

2026-09-30 later: the image is RW 3.6.0.3 (version 0x36003, base 0x34000, build 0xffff), Xbox layout: RWALIGN = __declspec(align(x)), rwMATRIXALIGNMENT/rwFRAMEALIGNMENT 16, no `#pragma function(pow...)`, no asm int32fromreal (image uses _CIpow/__ftol2). The 3.7.2 tree carries Archlord-style third-party edits (DDonSS thread-safety, Jaewon, gemani, Nonstopdj, burumal, Agcd* struct fields); C:\rwstudio\Graphics\rwsdk\include\null has STOCK headers — restore structs with scratchpad stockstruct.py (done: RpClump, RpAtomic, RwTexDictionary). The image has its own Spark additions: a texture critical section (_csTexture, sub_2A7870) and a world arena allocator (babinwor.c sub_2DA220..sub_2DAAF0, bounds dword_50F250/54) used by freelists, RpMaterialDestroy, RwRasterDestroy and the stream readers. Hand-write those from the image; rwsweep.py compiles from an overlay (scratchpad rwov = RW tree + src/rw + include/rw/sdk), rwnear.py ranks near misses, rwd.py diffs obj vs image, rwredo.py/rwproc.py place.
