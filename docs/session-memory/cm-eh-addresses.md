---
name: cm-eh-addresses
description: Pass cm.py only function addresses; __ehhandler lines ride with their function. Add EH lines before the first cm run.
metadata:
  node_type: memory
  type: feedback
  originSessionId: 81642346-cc05-4535-a5bd-fffa4a408d89
  modified: 2026-09-29T16:22:54.629Z
---

Pass cm.py only the functions' own addresses. The `__ehhandler` match lines under a function commit with it. Passing a handler's address on its own made strip() assert, and the old cm.py had already truncated the unit to empty (2026-09-28). The file was rebuilt from the conversation, and the keyboard unit was restored from HEAD.

A function with two or more unwind funclets gets only TWO lines: the first funclet (`-0x16` for two) and the handler. Its funclets are one compiled piece up to the handler. Listing the second one (`-0xE`) passes build.py but fails cm's placement link with "overruns" (PlayerTrigger, 2026-09-29).

**Why:** strip() removes a function's block together with the handler lines that follow it. Later lookups of those handler addresses then fail.

**How to apply:** Add the EH lines (p_eh.py, using the chunk_of_X entry in splits.txt and SEH_X in symbols.txt) before the unit's first cm run. trialm skips handlers unless you pass their addresses. If you add them later, re-run cm with the owning functions' addresses. cm.py now computes the stripped text before opening the unit, and it drops listed handler addresses. Related: [[cm-one-at-a-time]].
