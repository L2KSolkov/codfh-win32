---
name: entity-destructors
description: "type_3D3548-derived destructors — virtual inline base dtor, derived `~X() { vf_230(); }`, empty class operator delete aliased to sub_19A750"
metadata:
  node_type: memory
  type: project
  originSessionId: 81642346-cc05-4535-a5bd-fffa4a408d89
  modified: 2026-09-26T22:24:53.971Z
---

Settled 2026-09-26 (commits e8997567 onward):
- `~type_3D3548` is `virtual` (slot +0x004) and defined in the class, calling `vf_230()`. It is not expanded. Its out-of-line copy is sub_73850 (unit_073710), and each derived destructor reserves 20 frame bytes for the members' inline-destructor `this` temporaries. That was the "20 bytes larger" puzzle.
- A derived destructor is `~X() { vf_230(); }`, defined out of line in the class's unit. The mangled name is `??1X@@UAE@XZ` (virtual: `U`, not `Q`).
- The scalar deleting destructor `??_GX@@UAEPAXI@Z` is compiler-written: give it a comment-only match line. It calls a class `static void operator delete(void *)`, declared (never defined) and aliased in config/aliases.txt to 0x19A750 (empty, ICF-folded). A class with a placement `operator delete(void *, void *)` hides the base's, so it needs its own plain one.
- A deleting destructor is emitted only where the vtable is (the constructor's unit). Trial it on the FULL unit, not a slim copy.
- Match the header inlines' out-of-line copies (holder destructors) with comment-only match lines.
- Done: unit_073710 (3D3548, 3D32F8), unit_09AD40 (3D51C0, 3D5400, 3D5658). Pending: type_3DAFC8's sub_135310 / ??_G 0x1352E0, in a unit not yet started (0x134C50 onward).

**Why:** the pattern repeats for every type_3D3548 subclass.
**How to apply:** for any entity class destructor, copy this shape. Scratchpad `place.py UNIT FRAG` inserts comment-only match groups by address. Related: [[mi-thunk-splits]], [[inline-reserve-and-placement-delete]].
