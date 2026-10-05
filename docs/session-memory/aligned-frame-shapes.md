---
name: aligned-frame-shapes
description: "player step (0x101550) lessons - aligned-frame slot order, float operand order via (RwDouble), named float consts, switch/if order"
metadata:
  node_type: memory
  type: feedback
  originSessionId: 81642346-cc05-4535-a5bd-fffa4a408d89
  modified: 2026-09-29T18:17:02.248Z
---

Found 2026-09-29 while matching type_10F710::vf_03C (0x101550, 12 KB, ebx-aligned frame):

- In the aligned (ebx) prologue, `this` is at -4. Every local and temporary then takes a slot at first use, in code order. Names don't matter there, so skip bsolve.
- `field[i] * local` always compiles as `fld local; fmul field`. The image's `fld field; fmul local` is `(RwDouble)field * local`. If a float constant follows (`fmul dword [const]`), it is a named `extern const RwReal flt_X`; a literal would be a qword.
- For `index first, fld v, fchs, fmul field`, write `field * -v`.
- Loads: `x != 0.0f` loads the constant first. `0.0f == x` loads x first.
- The image may put the else branch's body first, e.g. `v = 0` before the call. Invert the condition so that branch comes first in the source.
- For `v = 0` / `v = 1` stored directly with no temporary, write if/else, not `v = a && b`.
- `ja`/`jbe` against 0 on a signed field needs `(RwUInt32)field <= 0`. An accessor adds a temporary.
- A one-step register shift before an else-if gets its compiled-out dword check by rewriting it as `else { if (!member) {} if (...) }`.

**Why:** a first draft of 150 diff hunks came down to zero with these.
**How to apply:** use tools/pdiff.py, which is adiffb with relocation and register noise filtered, and asmtest.py to test expression shapes. Related: [[fpu-expression-shapes]], [[empty-if-register-shift]], [[scratch-include-overlay]].

More, from sub_10C7B0 and sub_1116A0 (the same day):
- `fld b; fchs; fld a; fchs; fdivrp` (the divisor loaded first) comes from an inline `ratio(y, x) { return y / x; }`, because an inline's arguments are evaluated right to left. No plain `/` form reproduces it.
- An `fld; fld; fucompp` with no `fnstsw` is an empty `if (v != 0.0f) {}`.
- For an inline whose parameter copy comes before its result slot, use returns in each branch, not a local `r`.
- Check a float literal's bits: 57.29578f is 0x42652EE1, the image's is 0x42652EE2 (57.295784f).
- `RtQuatMultiplyMacro(&r, &kf[i], &q)`: in the cross product, the first factor shows which quaternion is qp. Write the result back to a pointer one component at a time when the image reloads the pointer for each store.

- A class with a vtable and an `RwMatrix` member: the aligned typedef pads the vtable pointer to 16, so every field after it moves by 0xC-0x10 (writes to +0xE8 where the image has +0xD8). Declare embedded matrices as `RwMatrixTag` (type_4F7EB8_27C, 2026-09-29).
- In a 16-aligned frame, named locals also get slots at first use, so a pointer local computed right before a call (a victim name at -0x164 below the string temps) is a named local, not a temp (sub_1ADD90).
- The grenade step (0x161FC0, 8.8 KB, 2026-09-30) matched from a straight asm-only draft in three rounds: a matrix copied to `[temp]` via `mov edi,[slot]` = a named pointer (`RwMatrix *p = RwFrameGetMatrix(f); *p = m;`), which also fixed later register choices; one register step in a final if-body = `if (member) {}` as the body's first statement. `v161f.py` (variants file of (old,new) replacements, pdiff hunk count) is the reusable loop.
