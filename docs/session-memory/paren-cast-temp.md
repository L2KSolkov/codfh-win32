---
name: paren-cast-temp
description: fst temp + fstp var after a double call = parenthesised cast ((RwReal)f(...)); a double-typed divisor gives a qword constant
metadata:
  node_type: memory
  type: feedback
  originSessionId: 81642346-cc05-4535-a5bd-fffa4a408d89
  modified: 2026-09-28T02:31:38.556Z
---

A double-returning call (fmod, fabs...) whose result the image stores to a temporary (`fst [tmp]`) and then to the variable (`fstp [var]`) is written with an extra pair of parentheses around the cast: `v = ((RwReal)fmod(a, b));`, typically via an inline `return ((RwReal)fmod(...));` or inside a ternary branch `? ((RwReal)fmod(...)) :`. The unparenthesised `(RwReal)fmod(...)` stores straight to the variable. A divisor loaded as a qword float-widened constant (e.g. 6.283180236816406) is `(RwDouble)6.28318f`; a plain `6.28318f` through fmodf loads a dword.

**Why:** found matching the debug menu (unit_183130: sub_183840, sub_184100) after many variants.

**How to apply:** when a frame is short by exactly the fst temporaries around libm calls, add the parentheses before restructuring anything else. See [[fpu-expression-shapes]].
