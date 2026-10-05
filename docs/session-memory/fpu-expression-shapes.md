---
name: fpu-expression-shapes
description: "VC7.1 /Od float idioms read off the player's vf_038 (unit_0FD730): fabs temps, jnp compares, operand order, compound-assign stores"
metadata:
  node_type: memory
  type: project
  originSessionId: 81642346-cc05-4535-a5bd-fffa4a408d89
  modified: 2026-09-27T22:11:18.405Z
---

Found 2026-09-26 matching type_10F710::vf_038 (0xFF990, 2156 bytes):
- `call _fabs` fed straight from memory with ONE `fst` float temp after = `(RwReal)fabs((RwDouble)x)`. Plain `fabs(x)` on a float picks the inline float overload: a param slot plus the result temp.
- `test ah,41h; jnp skip` (not `jne`) = `!(x <= c)`; `test ah,5; jnp body` inside `||` = `x < c`.
- A multiplier's index loaded before the division runs = `A * (B / C)`, not `B / C * A`.
- The store address recomputed with the index before the base pointer = compound assignment `a[i].x += v` / `-= v`.
- `a = a - expr` (lhs address loaded first, fsubr [lhs]) is written out, not `-=`.
- `call __acos_default; fst t; fstp v` with a ternary (clamp) argument = `v = acos(float_expr)` (the C++ float overload). `(RwReal)acos((RwDouble)x)` stores straight to v with no temp (sub_FCD90).
- A clamp compared `fld hi; fcomp x; test ah,41h; jne` = `hi > x ? x : hi` (the operands reversed from `x < hi`).
- Products loading a pointer arg between `fld` and `fmul` (z and y interleaved, x not; `[ebx+8]` args) = `fabs(RwV3dDotProductMacro(p, p))` (float fabs, param slot `fst`): the macro's parentheses set the load order; no hand-written form did (type_3D3548::vf_0D8).
- A plain float copy shown as `fld [src]; fstp [dst]` (not `mov`) = `(RwReal)(RwDouble)src` (type_DC400::sub_DEC40's clip planes; an inline float getter still gives `mov`).
- `p->y` loaded and spilled to a temp before a call, then `fadd temp` = RwV3dAddMacro(o, p, call()) with the call as the SECOND operand (x keeps the call first). Writing `p->y + call()->y` by hand hoists the call and gives no spill (sub_4D170).
- `fld [p+X]; fdivr [1.0f]` (divisor first) = `1.0f / (0, p->x)` (sub_929A0), OR, for the near plane, `1.0f / RwCameraGetNearClipPlane(cam)`: the macro's `((cam)->nearPlane)` gives fdivr where a bare `cam->nearPlane`, casts, `*&`, `(RwReal)1`, flt_3CD8E0, inline and __forceinline getters all give `fld 1.0; fdiv` (sub_125060, sub_1288F0, 2026-09-27). Try the RW accessor macro first for any RW field divisor.
- Three float slots whose order never follows their names (always first-assigned nearest ebp), where the image has x farthest = one RwV3d local (x at the lowest address) (sub_929A0's var_44).
- `fucompp; test ah,44h; jp body; jmp skip` = `if (x == 0.0f) {} else { body }` (`!= 0.0f` and `!(x == 0)` both give `jnp skip`). `v = t; v = v` after a ternary abs = `v = absref(v)`, an inline taking and returning `RwReal &` (Trigger's vf_028, vf_02C).
- Vector ops shown as three statements with no `xor; jne` after = written out by hand, not through a MACRO_START macro.

- `fld a; fld b; fcompp; test ah,5; jp else` then `fld b; fstp a` = `if ((RwDouble)a > (RwDouble)b) a = (RwReal)(RwDouble)b;` (the simple mechanism's path clamp, type_3DAC58::vf_03C, 2026-09-27); `a > b` on two fields gives `fcomp [mem]; test ah,41h; jne`.

- `fld [p+X]; fdivr [a]` (the divisor loaded first) = `a / (p->x)`: plain parentheses round the divisor flip VC7.1's load order (type_3DAFC8::vf_068, 2026-09-27); this is why `(0, p->x)` and RW accessor macros' parentheses worked before.
- `a*b + c*d` whose image loads c*d's operands first: swap the terms in the source (sub_134320's asin and atan2 arguments, 2026-09-27); a 2072-byte function matched once the three sums were swapped.
- `fild [a]; fild [b]; fdivp` (int/int as float) = `(RwReal)a / ((RwReal)b)`, the parenthesised divisor again; without them it is `fild; fidiv` (type_3DAFC8::vf_17C).

- `m->f * v` and `v * m->f` (a plain local v) both load v first; `fld [m+f]; fmul [v]` = `(m->f) * v`, the member in parentheses (unit_13F9E0's sub_141320, sub_1413E0, 2026-09-27).
- A member argument to a float `sin`/`cos` gets copied into a parameter slot; `fld [p+x]` straight into the call plus one float temp = `(RwReal)(RwDouble)(RwReal)sin((RwDouble)p->x)` (sub_141080).

- `fld [p]; fsub [q]` pushed straight to `_fabs` (no `fst` rounding store), both pointers loaded before the `fld` = `(RwReal)fabs((RwDouble)(p->a - q->b))`. `(RwDouble)p->a - q->b` interleaves the loads, and a plain float difference adds an `fst` (the tank's vf_03C, 2026-09-27).
- `fld [const]; fadd [member]` for adding a constant = `x = 360.0f + x`. Both `x += 360.0f` and `x = x + 360.0f` load the member first.

- `call _sqrt; fst [tmp]; fstp [x]` (one temporary) = `x = sqrtf(x)`, math.h's float inline; `(RwReal)sqrt((RwDouble)x)` gives only the `fstp` (type_15CCE0::sub_15DE60, 2026-09-27).
- A float ternary whose branches `fld [a]; fstp [tmp]` (tmp below `this`) = `c ? (RwReal)(RwDouble)a : (RwReal)(RwDouble)b`; plain operands, `(RwReal)a` and `+a` all copy with `mov`, and an if/return inline puts the temp above `this` (type_3DC9B0::sub_16B5C0, 2026-09-27).
- `fst [d]` inside a clamp's first compare = an assignment inside the expression: `acos(0.99999f > ((d = dot) > -0.99999f ? d : -0.99999f) ? (...) : 0.99999f)` (sub_16AAE0).

- `fld A; fld B; fucompp` loads the RIGHT operand first: `0.0f != global` gives `fld [global]; fld [0.0]` (the relocation check catches a swap as the literal's reloc in the global's place), and `field != local` gives `fld [local]; fld [field]` (type_DC400::sub_DD1C0, 2026-09-29).
- `fadd 180; fst [t]; fchs` = `-(t = f() + 180.0f)`, an assignment inside the negated argument. The cast form `-((RwReal)(...))` gives no `fst` (sub_DD1C0's damage markers).

- A pointer chain loaded into a register BEFORE `fld a; fsub b` (then `fmul [reg+f]`) = the chained member is the LEFT operand: `p->def->f * (a - b) * K` (sub_EF040, 2026-09-29). Parentheses round it, or `(a - b) * p->def->f`, load it after; an inline getter spills it to a slot.
- `frand_range(lo, hi)` with literal bounds takes no bound slots (only the qword and `r`); a computed bound gets a param slot, filled before RpRandom (sub_EF040's spin rate).

**How to apply:** when a float function's diff is only operand order or jump kind, try these before restructuring. Related: [[inline-return-slot-order]], [[rw-macro-operand-order]].
