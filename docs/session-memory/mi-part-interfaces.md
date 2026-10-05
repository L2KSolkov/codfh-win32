---
name: mi-part-interfaces
description: "Classes with an all-_purecall second-base interface: name its slots pvf_XXX, a shared-name slot gives an adjustor thunk, empty/0 overrides are ICF aliases; check who really calls before assuming an ODR mismatch"
metadata:
  node_type: memory
  type: project
  originSessionId: 81642346-cc05-4535-a5bd-fffa4a408d89
  modified: 2026-09-28T20:24:28.215Z
---

Found 2026-09-28 in unit_1B7B20 (the network players, type_17DBD0_player : type_10F710, type_3E24E8; type_1BABA0 : type_10F710, type_4F6B00_120):
- A second base whose vtable is all `_purecall` is a pure interface; its inline ctor stores that vtable before the derived one (vptr order: interface, main, derived part). Name its slots `pvf_XXX` (the entity's own vf_ names collide: same name + no params = one function overriding both slots, or a return-type error).
- A part slot that jumps through `sub ecx, N; jmp X` is a this-adjusting thunk: the interface slot shares its NAME with the main-base slot (e.g. `vf_05C`); the thunk symbol looks like `?vf_05C@type_1BABA0@@WCCGA@AEXXZ` (get it from the obj's symbols) and needs its own split row if it sits inside another function's range.
- Empty or `return 0` overrides folded into sub_15FB30 / pDtor / sub_32260 / sub_73D90: define them in the class and alias the mangled names.
- Callers that seemed to pass the wrong argument count were calling the OTHER class: always check which object a pointer really holds (unk_124 was the second player, not the local one) before inventing views.
- A class whose ctor is compiler-generated-looking but with no vtable stores in the dtor = no user dtor (compiler-written).

**Why:** cost hours on a fake ODR theory and view types that had to be removed.
**How to apply:** see [[mi-thunk-splits]], [[inline-reserve-and-placement-delete]].
