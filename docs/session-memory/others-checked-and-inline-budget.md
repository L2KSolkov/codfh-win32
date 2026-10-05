---
name: others-checked-and-inline-budget
description: others() register step solved with others_checked/get_unk_B0_checked/has_checked/test_checked; frame +8 fixed by show_message+hosting inlines; pscore.py for optimized RW variants
metadata:
  node_type: memory
  type: project
  originSessionId: 81642346-cc05-4535-a5bd-fffa4a408d89
  modified: 2026-10-01T14:57:38.173Z
---

2026-10-01: sub_1C32B0, sub_1C3520, sub_1C7840, sub_1A2A80, sub_1ACBA0 matched.
- `type_4F8054_B0::others_checked()` (discard + `if (!r.unk_00) {}` before return) with `type_4F8054::get_unk_B0_checked()` fixes the "others() register step" (the old blocker said checks stop inlining; this pair stays inlined).
- `mask.has_checked()` / `test_checked()` carry an `!(arg_0 & 1)` check (+1 load) — voice status sub_1C7840.
- Frame 8 too big after message texts in sub_1ACBA0/sub_1AD750 = two inline expansions near the end: `show_message()` (functions.h, sub_EACA0(t,0,0)) and `hosting()` (mpgame.h). Same pair fixed both = evidence.
- A named mask local in the wrong slot (0x12C vs 0x12A): pass the call result straight to the send, no local.
- sub_1AD750 parked: last block one step behind at several statements; checks there grow the frame.
- tools/session/pscore.py VARS SYM ADDR SRC: parallel variant ranking by normalized diff lines (works for .c). Used on the dmorph instance callback (parked, ~1310 lines, register allocation; draft docs/drafts/dmorph_instance_draft.c). XboxDMorphAddBlock matches beside it.

**Why:** these were the long-standing blockers listed in HANDOFF.
**How to apply:** try these variants first for any remaining others()/mask rotation or +8 frame issue. Related: [[empty-if-register-shift]], [[text-temp-type]].
