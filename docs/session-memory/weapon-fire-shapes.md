---
name: weapon-fire-shapes
description: "weapon fire (0x1176F0 family) lessons - index-first subscripts, preloaded FPU addresses, rand/fabs inlines, literal vs named float order"
metadata:
  node_type: memory
  type: feedback
  originSessionId: 81642346-cc05-4535-a5bd-fffa4a408d89
  modified: 2026-09-29T19:59:22.947Z
---

Found 2026-09-29 matching the weapon copies' fire functions (unit_116310) and the player's leftovers:

- `p->arr[p->idx]` loads the base first. The image loading the index first (then reloading `p`) means an inline is called on the element, e.g. `unk_42C->unk_1A48[unk_42C->unk_1AE4]->get_unk_458()` or `...->unk_420.get_unk_08()`. The accessor's `r` can be the only slot, with no named local.
- An element ADDRESS passed as an argument (`f(&d->arr[i])`) with the index loaded before `d` = a free direct-return inline `get_x(d, i) { return &d->arr[i]; }` (inline arguments evaluate right to left). A local-returning version breaks it (sub_15B2A0, 2026-09-29).
- An FPU expression whose operand addresses are all loaded first (it uses esi/edi) is `B * (x / A) + x`, not `x / A * B + x`.
- `field + flt_named` loads the global first. `field + 5.0f` (a literal) loads the field first.
- For `fst r; fdiv; fst r` around `rand()`, use `crand()` in game/frand.h. For a copy to a temporary before `fabs` plus a result temporary, use `fabs_ref` in game/mathutil.h (a const reference argument).
- An inline's arguments evaluate right to left. `frand_range(-x, x)` copies x first; `frand_range(0.0f, x)` folds the 0.
- A `(c1 || c2 ...) ? 1 : 0` inside an if gives a jump-stored temporary that is then tested. A named bool local adds a copy.
- `return v != 0;` on a call gives neg/sbb. `return v;` (int to bool) gives test/setne on a call, or cmp/setne on a local.
- A 16-aligned four-float local (the frame gap before it) is type_140490 (types/vec4.h).
- A new virtual override needs a temporary alias in config/aliases.txt for the -m commit (built without its body). Remove the alias in the next -m commit.

**Why:** these took 3 to 6 retries each to find. Once applied, each function matched on the first trial.
**How to apply:** check pdiff hunks against these before trying random variants. Related: [[aligned-frame-shapes]], [[fpu-expression-shapes]], [[getter-and-bool-shapes]].
