---
name: cm-one-at-a-time
description: "Run one cm.py at a time and wait for its task notification (it builds and pushes after printing \"committed\"); trial files must not be *.cpp in src/"
metadata:
  node_type: memory
  type: feedback
  originSessionId: 81642346-cc05-4535-a5bd-fffa4a408d89
  modified: 2026-09-28T23:32:06.038Z
---

Found 2026-09-26: two overlapping tools/cm.py runs emptied config/compiled.txt and left a
half-made commit; cm.py prints "committed N" before its final build and push, so starting the next
one on that line overlaps them. Also tools/build.py globs src/**/*.cpp, so a trial's
src/recovered/_trial.cpp compiled into a concurrent build and failed it.

Found 2026-09-26: a `until grep -q "pushed\|FAIL\|rror"` wait loop never saw cm.py's "Build failed:" (an AUDIT stop) and kept waiting after cm had exited. The user saw it as slow. Don't poll cm's log. Run cm with run_in_background and wait for the task notification, which arrives on success and on failure. Run `python tools/audit_sources.py` (1s) before cm: a struct defined in a .cpp, a raw byte offset or an untagged address-like constant fails the audit only after cm's pre-state build.

Found 2026-09-26: pass cm.py only the function's address, never its EH funclet/handler addresses. cm finds the `// match: __ehhandler$...` lines under the function by itself. Passing them too made strip() assert on the already-removed block, and the failed run left unit_0441B0.cpp EMPTY (0 lines). Nothing was committed; `git checkout -- <unit>` restored it. After any cm failure, check `git diff --stat` for a gutted unit before retrying. It happened again on 2026-09-28 with unit_1A26F0: the handler addresses were passed, and 184 lines were lost. Copy the unit to the scratchpad before any cm run that has EH lines.

Found 2026-09-27 (twice): appending drafts to the unit and header while seqcm/cm ran. seqcm reads the unit once at start and rewrites it block by block, and cm resets it on a DIFF, so the drafts were lost or broke the run's build. Killing seqcm mid-run left the unit with only the blocks written so far. Draft next functions in a scratchpad file (u*.cpp) and append them only after the notification.

Found 2026-09-27: the user found seqcm.py slow. It runs cm.py once per function, which is 2-3 full builds each (about 5 minutes a function). cm.py takes several addresses in one run: one checking build, an optional header commit, replayf.py (one commit per function), one final build and a push. Batch a unit's matched functions into a single `CMUNIT=unit_X python tools/cm.py -m "msg" A B C ...`. Blocks can sit anywhere in the file.

Found 2026-09-27 (twice): passing cm.py an address that is ALREADY in compiled.txt (to re-commit a source tweak, or a retyped signature) fails its stripped build with "no symbol". List only new addresses; the tweak rides along in the commit. If the symbol's name changed, delete its old compiled.txt row first. Also: a class's destructor/deleting destructor (defined in the class) can't be committed until the vf_230 it calls is matched, and their `// match:` lines fail the build ("no function symbol") until the vtable is emitted, so leave them as plain comments until then.

Found 2026-09-28: when a header change makes an already-committed function call a symbol that this batch introduces, `cm -m`'s header-commit build fails. It strips the batch, so the committed function's link fails ("cannot resolve"). Fix it by hand. Add that symbol's compiled.txt row, run `tools/build.py` to `== PASS`, and commit the headers, the unit and that row together as "match: recover X". Then run cm on the rest without `-m`. This happened with sub_1A3550 and type_4F6B00::vf_004.

Found 2026-09-28 (unit_1CCC00): cm without `-m` commits only the unit and compiled.txt, and header, alias and other-unit edits stay uncommitted. The pushed commits then don't build until a follow-up commit. When a batch comes with header or config edits, always pass `-m "types: ..."`. Check `git status` after every cm run.

Found 2026-09-28 (addPacket): `cm -m` strips the listed functions for the header commit. If an unmatched body of a listed function is the only code that instantiates members that other functions already commit (implicit ctors/dtors, template appends), that stripped build fails with "no function symbol". Run `cm.py -H -m ...`: the header commit then uses HEAD's unit, which still has the old unmatched body. The user asked whether the function itself should be fixed. It was already byte-identical, and this is only a tooling issue.

Found 2026-09-28: the placement linker (tools/xbelink.py) used to reject a second `_$E<n>` exit thunk as "placed twice". It now keeps static (class 3) symbols per object. cm's header commit also stages tools/xbelink.py.

**Why:** the build and commit replay rewrite shared files (compiled.txt, the units).
**How to apply:** start the next cm.py only after the background task's completion notification;
don't edit headers or units while one runs. The tools/trial tools now write _trial.cxx
(outside the glob). If a run breaks, `git checkout -- config/compiled.txt`, reset unpushed
half-commits with `git reset --soft origin/master`, rebuild, and push.

Don't `git checkout config/compiled.txt` before cm when this change renames a matched symbol (a retyped signature). cm reads the rows as they stand, and the checkout silently undoes the manual rename (pvf_020, 2026-09-29).
