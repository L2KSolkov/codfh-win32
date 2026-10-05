---
name: no-rm
description: Never run rm (or other deletion) — not even on build/tooltmp scratch dirs; use unique variant names / specific globs instead
metadata:
  node_type: memory
  type: feedback
  originSessionId: 81642346-cc05-4535-a5bd-fffa4a408d89
  modified: 2026-10-01T10:51:12.728Z
---

Do not run `rm` (the user said "no more rm please", 2026-10-01, after I cleared build/tooltmp/ptry with `rm -f`).

**Why:** the user does not want files deleted by me, even generated scratch files.

**How to apply:** to rank fresh ptry variants, give them a unique prefix and glob that (e.g. odscore.py with "p_w7*.obj"), never clear directories. Moving drafts to the scratchpad by writing new files is fine.
