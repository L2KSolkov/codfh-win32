---
name: draft-diff-workflow
description: Fast loop for writing unmatched functions: draft from xdis, scratch slotmap.py (opcode alignment + slot pairs) and diffall.py (all byte diffs, relocs masked)
metadata:
  type: feedback
---

Writing a binary function from scratch (2026-09-29, sub_26A80/2C220/2D5C0 each matched in one or two tries):
1. `xdis.py ADDR END` for the image; copy idioms from matched siblings in the same unit (RwV3dSub macro vs explicit components, fabs(dot) > K, atan2(...)*57.295776f, RWS::DegAngDiff = sub_1326C0).
2. Insert the draft into a copy `src/recovered/_ln.cxx` (in-repo path for includes), then scratch `slotmap.py FILE ADDR` (first opcode mismatch + our->image slot pairs) and `diffall.py FILE ADDR N` (every differing instruction, relocations masked; "diffs 0" = done).
3. Names: scratch `bsolve.py FILE ADDR slots` + `applyb.py` (names must be lv_<slot>); check mid-function declarations were not hoisted.
fucompp: `test ah,0x44; jp skip` means the body runs when EQUAL.
**Why:** far faster than trial-and-error with trialb's first-difference only.
**How to apply:** use for every never-attempted function; parallel runs need the pid-suffixed build files (ourdisb/slotmap/diffall already do).
- Nested-block locals: tools/climb_names.py can't reorder them (it sorts the first paragraph's lines). Use tools/bsolve_decl.py SRC SLOTS DECLIDX: buckets per slot with the declaration-order tie rule (sub_1F15C0).
- Big near-miss functions: tools/sdiff.py SRC ADDR N aligns by instruction shape (frame offsets blanked; DUMP=lo,hi prints ours). vva.py UNIT BLK ADDR VARIANTS.py runs variant dicts (VTOOL=sdiff.py for shape counts).
