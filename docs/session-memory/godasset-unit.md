---
name: godasset-unit
description: "unit_18F3C0 (GodAssets, 0x18F3C0 on): base is type_3DF8D8_base (0x10 bytes); a kind's +0x10 part built before its vptr = a second base; vtables need ??_7 aliases"
metadata:
  node_type: memory
  type: project
  originSessionId: 81642346-cc05-4535-a5bd-fffa4a408d89
  modified: 2026-09-28T04:53:23.120Z
---

unit_18F3C0.cpp holds the GodAsset kinds (keyed objects read from streams), started 2026-09-28.
- The true base is `type_3DF8D8_base` (vptr, key unk_04, words unk_0C/0E; ctor sub_18F3C0). `type_3DF8D8` is only the shared view (+0x10 fields) the rest of the game uses.
- A kind whose +0x10 block is initialised *before* its vptr store derives from a second base there (`type_3DF8F0_10`), e.g. type_3DF8F0, type_3DF9C4, type_3DFABC. Members proper are constructed after the vptr.
- Each class's vtable needs a `??_7type_XXXX@@6B@ 0x00XXXX` line in config/aliases.txt; renaming a committed function also means fixing config/compiled.txt.
- `get_ref_kind`/`get_ref_kind_direct` inlines only match with their current local names (inline locals hash like named locals).
- Sound kinds sit on `type_3DFB6C` (pure vf_00C play, vf_010); their classes live in types/soundbank.h and types/musicplayer.h.
- Parked: sub_190640 (kind 3's handler: an unused slot at -8 before the ref array).

**Why:** these took several attempts to discover; the unit has ~250 functions to go.
**How to apply:** new kinds follow the same pattern: class in the header, ctor + handler + kind, alias the vtable, climb names.
