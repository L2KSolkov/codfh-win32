---
name: cm-replay-limits
description: "always commit through cm.py (never by hand); cm now handles renamed symbols; parked code is to be matched, not worked around"
metadata:
  node_type: memory
  type: feedback
  originSessionId: 81642346-cc05-4535-a5bd-fffa4a408d89
  modified: 2026-09-28T17:01:29.508Z
---

Commit matched functions only through tools/cm.py, one function per commit. Do not hand-commit batches with addrow.py.

- A renamed symbol (changed signature, return type or vf_ rename) is handled. As of 2026-09-28, cm.py drops the old compiled.txt row at a listed address in the types commit.
- Parked code breaks cm's blocks: it has no `// match:` line, so it is swallowed into the preceding function's block. The user said to match the parked ("Not yet matched") functions rather than patch cm around them. Do not leave new parked code behind.

**Why:** on 2026-09-28 the user asked "how are you committing? cm.py?", then said "go back through and fix code so cm.py works" and "fix the not yet matched code instead". Hand commit 2baae207 had batched 18 functions.

**How to apply:** write, trial and fix all slots and registers, then run `CMUNIT=unit_X cm.py -m "types: ..." ADDRS...`. If a function stays stubborn, keep working on it or leave it out of the unit (drafted in the scratchpad), not parked in the source. See [[cm-one-at-a-time]].
