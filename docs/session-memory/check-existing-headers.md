---
name: check-existing-headers
description: "Before copying a drafted header into include/, check it does not already exist (git ls-files); merge instead of overwriting"
metadata:
  node_type: memory
  type: feedback
  originSessionId: 81642346-cc05-4535-a5bd-fffa4a408d89
  modified: 2026-09-28T07:07:09.107Z
---

Before `cp draft.h include/...`, run `git ls-files include/<path>`; many `types/type_XXXX.h` headers already exist from callers' units (type_3DAC58.h did, with members unit_0441B0 used). Merge the new members into the existing file instead.

**Why:** overwriting type_3DAC58.h (2026-09-27) broke unit_0441B0 and cost a failed cm.py build.

Also before writing a new *topic* header (game/particles.h was overwritten on 2026-09-28 the same way): `ls include/game/<name>.h` first. A Write result saying "updated" instead of "created" means an existing file was replaced: restore it from git at once.

**How to apply:** every new class header for an entity/type found by address; also check `grep -rn "struct type_XXXX" include`.
