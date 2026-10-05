---
name: xbox-driver-from-asm
description: "RW 3.6 Xbox driver (_rwXb*, 0x2AC710 on) is rebuilt from the image in src/rw/driver/xbox/ (xbraster.c/.h); d3d8 driver is only a structural guide"
metadata:
  node_type: memory
  type: project
  originSessionId: 81642346-cc05-4535-a5bd-fffa4a408d89
  modified: 2026-09-30T16:20:16.125Z
---

Started 2026-09-30. The image's Xbox driver (`_rwXbRasterPluginAttach` etc., ~233 functions from 0x2AC710) has no source in D:\RW_372_src (only d3d8/d3d9/null/opengl). New files go in `src/rw/driver/xbox/` (compiled by the `src/rw/*` flags rule; `<xtl.h>` works there, so `sizeof(D3DTexture)`/`D3DPalette` are available). Names come from the database; unknown struct fields as unk_XX.

- Place with `// match: __rwXbFoo @ 0x...` lines plus hand-added compiled.txt rows (rwann.py skips already-annotated names).
- Test single functions with tools/ctry.py FILE AS_SRC SYM ADDR (it now prints COMPILE ERROR; never trust a bare 0 diff count).
- Log each finding in docs/rw-differences.md (the "Xbox driver" row).

Related tools this session: rwbybytes.py (unplaced RW functions matched by bytes + known relocs), rwrank.py (near misses by diff size), nopsplit.py (RtFS nop padding), coll36*.py.
Related: [[rw-source-builds]], [[rw-differences-doc]].

2026-09-30 xbconvrt.c (28 matched). Shapes that mattered:
- Compare with tools/ncmp.py OBJ SYM ADDR [-v] (normalises jumps/relocs; trailing jump-table lines are noise). The real build still catches table *contents* (a missing `case 24:`) and jump-threading.
- Increment order in loops: the image bumps dst before src; `*d = *s; s++; d++;` differs from `*d++ = *s++`.
- A value tested twice (format PAL then LUM8) = a local assigned inside the case.
- Ternary over whole constants folds to `and/add` (`(d==4) ? (PAL4|888) : (PAL8|888)`), not `?: then |`.
- Our compiler threaded a jump past a later test of the same local; the image didn't -> test the expression (`format & mask`) there instead of the local.
- Static helpers get register args chosen by the compiler; the choice follows the callee's and callers' allocation, not declaration tweaks.

2026-09-30 xbrendst.c (33 matched). Lessons:
- Static functions' match lines use the object's name WITH the C underscore (`// match: _XbRenderStateFogType`), else ncmp says NOT EMITTED.
- Cache macros store dirty flag first, then list entry, then count++ (checked across all callers with tools/macvar.py).
- IDA "chunk_of_X" tail-jump targets are real static functions: name them in symbols.txt/splits.txt by hand.
- A switch returning `mov eax,1` hoisted above `ja default` = `RwBool result = TRUE;` + every inline case `result = TRUE; break;` + calls `result = f(); break;` + `default: result = FALSE;` + `return result;` (d3d8's setter shape).
- A hand-written copy of a static's body (NULL-raster paths) appears where the image repeats code the compiler did not inline.
- tools/srep.py FILE EDITS (old/-----/new/===== blocks) edits CRLF files safely.

2026-09-30 xbdevice.c (18 matched). Lessons:
- ncmp's 0 is not enough: it masks branch targets and relocation addends. Run tools/rawcmp.py OBJ SYM ADDR (function-relative jumps) before cmf; the build caught a wrong field read (`present` fill order) and a switch whose conditional jump went to another shared `return TRUE`.
- A switch with one tail return that conditional jumps reach from far away = Godfather's `result = X; break;` in every case and `return result` (plus `default: result = FALSE`).
- Godfather debug helpers that show as calls (`XbGetTopRaster`) are static functions, not macros; a debug local (`zRasterExt`) fixes register choice.
- `-(a * b)` vs `-a * b` changes SSE load order.
- Parallel C variant trials: tools/cvtry.py FILE SYM ADDR VARFILE (srep blocks, variants split by #####).
