---
name: free-inline-arg-first
description: "literal stored before a member's address, both in slots after the temporaries = free inline with its own locals (r, then pointer m)"
metadata:
  node_type: memory
  type: feedback
  originSessionId: 81642346-cc05-4535-a5bd-fffa4a408d89
  modified: 2026-09-29T13:37:57.843Z
---

When a member-mask op stores its literal argument *before* the member's address, and both slots sit after the function's temporaries, it is a free inline with locals of its own, not a member inline. Member inlines store the `this` temporary at entry, before any local; const-ref literals get ordinary temporaries in order.

Example: `take_out_peer(unk_340, 0)` in include/types/type_1DDE20_mask.h does `RwInt32 r = arg_4; type_1DDE20_mask *m = &arg_0; m->unk_00 &= ~(1 << r);`. It matched the player vote's fill, sub_222D20. The local names decide the order of the two slots: "r m" worked, while "r p" and "i p" did not.

**Why:** unset(), reset(), remove() and clear() all put the address first or put the literal in the wrong slot. The free inline was the only form that matched the order, the slots and the registers.

**How to apply:** first get the slot set identical, then fix the store order this way. Search the names with a small loop over pairs. See [[inline-return-slot-order]] and [[empty-if-register-shift]].

2026-09-29: an append whose argument (a call's result) goes through one extra temp before the push = `add_text(a, b)` (types/type_505188.h), a free inline with a reference parameter. Used by sub_20EB30 and sub_21E3E0. Several "unwinds through sub_43900" functions now match as plain code: sub_43900 is aliased, and type_1CB670(const RwChar *, RwInt32) is declared out of line (aliased to sub_1CB6B0).
