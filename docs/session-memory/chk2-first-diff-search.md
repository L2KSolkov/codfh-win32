---
name: chk2-first-diff-search
description: For long /Od functions whose only differences are register rotation, scratchpad chk2.py (first-difference -> /FAsc source line -> try checks/inline swaps) converges where line-count greedy searches stall
metadata:
  type: feedback
---

sub_1CE650 (0x10C6-byte message switch) went from 734 diff lines to a match on 2026-10-01 with scratchpad chk2.py: each step finds the first differing normalized instruction, maps it to a source line via /FAsc, tries candidate empty-if checks before that line, the two statements above, and before the closing braces above it (an else's registers follow the end of the then-branch), plus inline swaps (drop->discard/clear, include->admit/add); keeps the variant whose first difference is furthest.

**Why:** odiff line-count greedy (snchk2) stalls because fixing one spot shifts later ones; also odiff.py reloads the XBE each call (minutes per round) — score in-process instead.
**How to apply:** fix slots/shapes first (names by block with sn_n5 SNC/SNP; a ptry copy is a snapshot — never cp one back after other edits; name regexes also rewrite string literals, check them), then run chk2.py SRC SYM ADDR STEPS 'if (!unk_04) { }' ... ; when stuck, try the inline-variant swaps by hand. Wrap the result in a PLAYERS_CHECK-style macro defined before the first match line. Related: [[empty-if-register-shift]], [[snetgameep-unit]].
