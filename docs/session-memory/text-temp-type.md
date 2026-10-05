---
name: text-temp-type
description: Frame too big only by unused slots around text temporaries = write literal texts as type_1A5EA0("...", 0), not type_1CB670("...", 0)
metadata:
  type: project
---

Found 2026-09-29 (sub_20CFB0, parked for an 8-byte frame): unused frame slots are leftovers of the inline expansions VC7.1 attempts, mostly a temporary's destructor chain (type_1CB670 -> type_1A5EA0 -> std::string -> _Tidy). They are packed with the live temporaries, so the total changes chaotically. The image's literal texts are type_1A5EA0("...", 0) temporaries: the constructor at 0x1CB6B0 is shared (ICF) with type_1CB670's, so the code is identical but the destructor chain is one level shorter. Empty texts (sub_E87E0) stay type_1CB670().

**Why:** the user said it was not a compiler difference; `#pragma inline_depth(N)` moving the frame showed the slots are inline leftovers.
**How to apply:** for any parked "frame N bytes larger" function with text temporaries, retry with type_1A5EA0 temporaries (per text, all combinations if needed). Probe with `#pragma inline_depth` to confirm inline leftovers. See [[block-local-allocation]], [[string-ctor-out-of-line]].

Same day, more cases: sub_1E7A80 (16 bytes) matched once its first append went through the `add_text` inline (the image's extra reference slot beside the text temporary); sub_1ECBD0 (16 bytes) matched once its raster reads went through an inline accessor (`type_1EEEE0::get_unk_00`, two value temporaries the draft lacked). Rule: before blaming frame reservations, make the slot map's *temporaries* identical (every inline accessor and helper the image shows); the unused-slot packing then usually follows.

Inline budget (sub_201890, 2026-09-29): identical code, image frame smaller by exactly the text's 16 leftover bytes. `#pragma inline_depth(3)` reproduced it, and padding with no-code inline calls shrank ours: the compiler skips the _Tidy attempt once the function's inline budget is spent. Fix: eight free inline accessors for the global's fields (uiglue.h get_4FDBB0_unk_XX); member accessors made it worse (0x6C, `this` leftovers). Probe with inline_depth 1-8: if a low depth gives the image frame AND trial passes, look for missing no-code inlines (accessors, checks), free-function form first.

No-code inline call (sub_221A80, 2026-09-29): frame short by leftover groups, everything else equal = one more inline expansion the original had. Find the position with a placeholder (`x.size();`, slotset.py/combsearch), then look for a natural no-code inline there: a compiled-out debug print of the buffer just built (`inline void debug_text(const RwChar *) {}` after the sprintf) matched. Empty `if` checks change registers; getters with discarded results don't count. Also: text slot order depends on the NAME (`text` put the returned text at -0x48; var_/lv_ forms never did) — try plain word names when pnames fails.

Frame too LARGE with string leftovers (sub_1A4B40, 2026-09-30): no-code inline calls placed at the END of the function shrink it (at the top they grow it). Probe with k copies of `nop_()` before the closing brace; the k that gives the image's frame says how many expansions the source has there. Then find a natural inline used that often near the end (here a free direct-return accessor for `&unk_00[i].unk_04->unk_28`, `flag_objective`, which also produced the one result slot the image has).
