---
name: block-scoped-locals-below-arrays
description: "Locals below a /GS array = declared in a for/if block (VC7.1 for-scope leaks, so later reuse still compiles); climb_names before resizing the array"
metadata:
  node_type: memory
  type: feedback
  originSessionId: 81642346-cc05-4535-a5bd-fffa4a408d89
  modified: 2026-09-27T15:26:16.801Z
---

When the image has scalars below a /GS-protected array (sub_146770, sub_146CD0), those scalars are block-scoped: declare them in the `for` (`for (T *a = 0, *b = ...; ...)`, `for (RwInt32 i = 0; ...)`) or inside the `if` body. VC7.1 leaks for-scope names, so later loops can reuse them. Mid-function declarations at function scope don't do this; they stay above the array.

Get the slot names right with tools/climb_names.py (the function-scope slots plus the array, for example 4,8,C,10,58) before you judge an array's length. A wrong name order throws off the frame size too. sub_146770's buffer came out as RwInt16[32] only after the names were climbed.

**Why:** local_names gave up (too many combinations), and trying array sizes before the names were right gave misleading frame sizes.
**How to apply:** frame too big with a local array → move the scalars below it into block scope → climb_names → only then vary the array length. Related: [[local-names-first]], [[cm-one-at-a-time]].
