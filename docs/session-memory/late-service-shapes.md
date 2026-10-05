---
name: late-service-shapes
description: "unit_2261C0 (late service): unused call result = empty switch temp; `this` sorts after named+inline slots, before temps; XDK header split; $E renumbering"
metadata:
  node_type: memory
  type: feedback
  originSessionId: 81642346-cc05-4535-a5bd-fffa4a408d89
  modified: 2026-09-29T16:44:41.078Z
---

Learned on the late service (unit_2261C0, type_5051E8), 2026-09-29:

- An unused call result stored to a slot *after* the function's `this` slot is a compiler temporary. `switch (f()) {}` reproduces it. A named local, `(void)`, `f() == 0;` and an empty inline taking the value do not. If the registers after it are one step behind, add a compiled-out `if (!member) {}` check (sub_2279D0, sub_226DD0).
- Slot order: named locals (all scopes), then inline locals and inline `this` slots, then the function's own `this`, then compiler temporaries (switch, `new`, ternary). A getter's return slot (`if (!(p->get_x() & 4))`) is a temporary, not a named local.
- In a `/GS` function, a scalar placed below the arrays is block-scoped. A local placed after `this` is a temporary.
- Two identical-register mask ops that are two steps off = an inline with ONE compiled-out word check. `discard()` and `admit()` were added to type_1DDE20_mask.h. A check on a local does not shift the registers; a check on a member does.
- `it != v.end()` gives the double `neg/sbb/inc` + `movzx` pair; `!(it == end)` gives a single one.
- The audit allows one definition per struct, so there is no second, XDK-free view. startup.h forward-declares type_5051E8; game/liveservice.h has the typed layout. Units that call the service include liveservice.h first, before startup.h: startup.h's own Direct3D_SetPushBufferSize declaration clashes with D3D8.h otherwise.
- Including the XDK headers can renumber a unit's `_$E` exit thunks (unit_1FF250 went from _$E2 to _$E3). Update both the match line and the committed config/compiled.txt row, and do not `git checkout` compiled.txt before that cm run.
- A value stored into a temporary right after its source's temporary, with nothing reading it = the argument of an inline with a by-value parameter and an empty body. The discarded read `skip_value(it->GetAs_RwInt32())` fixed PlayerTrigger's command 111. A plain discarded call emits nothing. A block local is allocated among the named locals. A `const &` parameter adds a copy.
- For float math through a slot, use `tan_ref`/`cos_ref` (game/mathutil.h): `tanf`/`cosf` here take no slot. An RWS read straight into a local is `GetCommandData(local)`; `x = GetAs_*()` adds a value temporary.
- tools/adiff.py FILE ADDR END` gives an aligned diff with the image's addresses, which is better than nd.py for big functions. `gen_plt_ha.py` generates RWS attribute switches, with hand-written `plt_case_N.txt` overrides.
- Use tools/ranks.py SOURCE REF SLOT` to pick a name whose bucket ranks at or above another name's. Use `fnedit.py` (written with the Write tool) for edits inside one function.

**Why:** these took many trial rounds to find; see [[local-names-first]], [[empty-if-register-shift]], [[getter-and-bool-shapes]].
**How to apply:** the parked sub_2270E0, sub_227660, sub_227CA0 and sub_226DD0 drafts are in the scratchpad at parked_2261C0.cpp; try these shapes first.
