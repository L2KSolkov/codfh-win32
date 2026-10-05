---
name: voice-channel-shapes
description: "unit_1DDBE0 lessons — time results src-first via since()/zero(), B0 named local, /GS block scope by decl order, by-value inline param slots, greedy check() search"
metadata:
  node_type: memory
  type: feedback
  originSessionId: 81642346-cc05-4535-a5bd-fffa4a408d89
  modified: 2026-09-29T01:34:39.080Z
---

Shapes found matching unit_1DDBE0 (voice channel, 2026-09-28):
- A type_1CCA10 member assigned with the *source* loaded before `this` = the value came back from an inline returning a time: `type_1CCA10::zero()`, `a.since(b)`. Plain `x = 0` / `x = a - b` loads dest first.
- `mov [ebp-N], addr` of a packet's time before a subtract = `arg - p->t.ref_unk_00()` (reference temp), not a local.
- Getter chains `unk_04->get_unk_04()->unk_B0` whose B0 slot sits among the named locals (high) = a named function-level local holding B0; the getter's inline `r` lands late.
- A word temp before storing a read value into a mask = inline by-value setter (`bits(RwUInt16)`): call results passed to by-value inline params get a slot; constants don't.
- /GS frames: scalars above the cookie vs below arrays depend on declaration order too (`var_1; var_18[16]; var_2;` put both bytes above); inner-block locals go below.
- Whole classes can need compiled-out checks nearly everywhere (voice channel's inline `check()`); a greedy search that maps the first differing byte to its source line via /FAsc and inserts 1 or 2 `check();` lines solves most; it stalls on jump displacements and unbraced if-bodies — handle those by hand (add braces). `while` vs `for` matters (for adds a jmp).

**Why:** each of these cost hours of trial before the pattern was clear.
**How to apply:** try these before brute-forcing names; related [[empty-if-register-shift]], [[getter-and-bool-shapes]], [[block-scoped-locals-below-arrays]].
