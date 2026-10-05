---
name: push-after-commit
description: User wants commits pushed to origin/master; history was force-pushed once on 2026-09-24
metadata:
  node_type: memory
  type: feedback
  originSessionId: 81642346-cc05-4535-a5bd-fffa4a408d89
  modified: 2026-09-25T05:57:47.496Z
---

Push `master` to `origin` after committing. On 2026-09-24 the user said "no just force push to main" (the branch is `master`), so the reset history replaced `origin/master`; the old history is kept locally as `backup/pre-reset-2026-09-24`.

**Why:** The user wants the remote to follow local progress.
**How to apply:** After each commit (with `== PASS`), run `git push origin master`. Normal pushes are fast-forwards now, so don't force-push again unless the user asks.
