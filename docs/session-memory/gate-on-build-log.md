---
name: gate-on-build-log
description: "Gate commits on tools/build.py's own output, never on `build.py | tail` (the pipe hides failures)"
metadata:
  node_type: memory
  type: feedback
  originSessionId: 81642346-cc05-4535-a5bd-fffa4a408d89
  modified: 2026-09-25T12:28:22.782Z
---

Gate every commit/push on `python tools/build.py > log; grep -q "== PASS" log`, not on
`python tools/build.py | tail -1 && ...`: the pipe's exit status is tail's, so a FAIL (e.g. a source
audit complaint like "struct defined in a source file") still let commits and a push through once
(2026-09-25).

**Why:** the per-commit gate must hold (`== PASS` required before each commit, pushed after, see
[[push-after-commit]]).
**How to apply:** check the log for `== PASS` before running replayf.py / git commit / git push.
Chain the whole sequence with `&&` (replayf.py && build > log && grep -q PASS log && push), never
`;` — on 2026-09-25 replayf.py crashed on a locked compiled.txt mid-run and a `;` let the build and
push run anyway, leaving the unit file truncated in the working tree (rebuilt from the scratch
trial copy). replayf.py now retries its writes.
