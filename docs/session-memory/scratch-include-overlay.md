---
name: scratch-include-overlay
description: trial header changes while cm runs - compile in build/ with a scratch include dir first on /I
metadata:
  node_type: memory
  type: feedback
  originSessionId: 81642346-cc05-4535-a5bd-fffa4a408d89
  modified: 2026-09-29T17:23:00.291Z
---

While a cm run (or the cm_inits loop) is running, never write under src/ (trialm's src/recovered/_trial.cxx shows as untracked and stops the loop) and never edit include/. Instead copy the headers to change into build/tooltmp/inc/<same path>, edit them there, and compile in build/ (gitignored) with `/I build/tooltmp/inc` put before the project flags. Variants of the tools made this way: trialb.py, ourdisb.py/adiffb.py, showoffsb.py. After cm finishes, copy the verified header edits back into include/.

**Why:** cm_inits checks `git status -- src config include docs` after each unit and stops on anything dirty. Stopping the work until it finished would waste about an hour.

**How to apply:** Also trial every committed unit that uses the changed headers (for example unit_0DC400 for type_DC400.h) against the overlay before committing. Related: [[cm-one-at-a-time]].
