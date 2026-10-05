---
name: rw-import-then-edit
description: new RW source with differences: commit the untouched 3.7.2 file first, then the edits in a separate commit
metadata:
  type: feedback
---

When a RenderWare file that is not yet in the tree needs changes to match the image, first commit it exactly as in D:\RW_372_src (an "import" commit, even if it does not build), then commit the edits separately so the diff shows every difference.

**Why:** the user asked (2026-09-30) that the differences be visible in history.
**How to apply:** before hand-editing a newly vendored file (destock.py, cfix.py rewrites), `cp` the pristine file, commit "rw: import X as in the 3.7.2 tree", then apply edits and commit with the match. Files rwbatch vendors unchanged (only `// match:` lines) need no split. Also log each difference in docs/rw-differences.md ([[rw-differences-doc]]).
