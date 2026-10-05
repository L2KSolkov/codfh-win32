---
name: sse-sqrt-form
description: "The image's movss/movaps/sqrtss square-root blocks are an __m128 do/while with _mm_set_ss/_mm_sqrt_ss/_mm_store_ss; needs /Zi for the aligned frame"
metadata:
  node_type: memory
  type: project
  originSessionId: 81642346-cc05-4535-a5bd-fffa4a408d89
  modified: 2026-09-26T18:30:59.748Z
---

Found 2026-09-26 (AIData::sub_21610, sub_21790, sub_21910 in unit_012000, all first try):
a square root shown as `fld v; fstp t; movss xmm0,t; movaps a; ... sqrtss; ... movss [out]`
inside a do/while(0) is

```
do
{
    __m128 a = _mm_set_ss(v);
    __m128 b = _mm_sqrt_ss(a);
    _mm_store_ss(out, b);
} while (0);
```

with `#include <xmmintrin.h>`. The __m128 locals make the frame 16-aligned, so these only match
since /Zi went into config/flags.txt.

**How to apply:** any function with this block (docs/units.md lists many as "16-aligned") can now
be written directly. Related: [[fpu-expression-shapes]].

2026-09-30 RenderWare: the Xbox 3.6 build's rwInvSqrtMacro / rwSqrtInvSqrtMacro are SSE too
(sqrtss, then `xorps; cmpltss zero,root` spilled = `_mm_cmpgt_ss(root, _mm_setzero_ps())`,
`andps`, store, `if (r > 0) r = 1/r`). Now in src/rw/src/plcore/bavector.h and
include/rw/sdk/rwplcore.h; it unblocked RwV3dNormalize, bamatrix rotations, camera clip planes,
the collision triangle queries and RtIntersectionSphereTriangle (about 20 functions). An
unplaced RW function with a 16-aligned frame and this block = check these macros first.
Scratchpad unplaced_in.py SRC... scores every unplaced function defined in a source.
