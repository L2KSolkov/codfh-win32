---
name: kujuui-library
description: "kujuUI widget library (0x1DFBB0–0x1FA180) — namespace kujuUI, header game/kujuui.h, widget/creator/selectable-base layout, per-file units, cm/climb fixes"
metadata:
  node_type: memory
  type: project
  originSessionId: 81642346-cc05-4535-a5bd-fffa4a408d89
  modified: 2026-09-29T02:14:31.551Z
---

kujuUI (\COD\SHARED\UI\) runs 0x1DFBB0–0x1FA180, started 2026-09-28. Everything is in `namespace kujuUI` (parsedfile.h already was; cCaret's trace names kujuUI::cCaret, cStateChange, eEventWasHandled); declarations live in include/game/kujuui.h.

- Widget base type_3E7D08 (out of line ctor 0x1F76E0 / dtor 0x1F7740): parent +4, focus +8; 12 slots (4 processEvent, 0x18 draw, 0x20 rect by hidden ptr, 0x28/0x2C focus in/out).
- Selectable base type_3E76B4 = widget + type_3E75E8 (+0xC: rect, hidden; pvf_ names) + type_3E76E4 (+0x10), look type_1E37A0* at +0x14, hidden +0x18; ctor 0x1EFDA0, dtor 0x1EFEA0 (its own file ~0x1EFD70–0x1F0080).
- Each widget type has a creator (base type_3E7D94, ctor/dtor 0x1F7A20/0x1F7A40): name string, create(scope, arg_4, arg_8, registry type_1ED670*, parent, out), keys(validator).
- Units so far: unit_1DFBB0 (helpers, event mapper, border), unit_1E0670 (button, ends 0x1E0D93); cCaret's file starts 0x1E0DA0.
- Distinct same-valued float constants (two 3.0s) = file-static `static const RwReal unk_ADDR`; literal floats pool into one __real symbol and mismatch.
- Scratchpad cm.py strip() and replayf.py block() keep a namespace's closing brace after the last function (bodiless thunk/instance lines too; before 2026-09-28 19:10 the replay dropped it, so earlier kujuUI intermediate commits don't compile alone — the user noticed on c2848ef8); tools/climb_names.py closes open namespaces and puts its note after EH annotations (cm's listed() needs EH lines right after the match line).

**Why:** the library is large and its conventions are easy to rediscover wrongly.
**How to apply:** new kujuUI units go in the namespace; declare bases once in kujuui.h; alias out-of-line base ctors/dtors and vtables. Related [[mi-part-interfaces]], [[mi-thunk-splits]], [[voice-channel-shapes]].
