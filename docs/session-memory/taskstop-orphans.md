---
name: taskstop-orphans
description: TaskStop leaves the python child of a piped background command running; it keeps rewriting the unit. Kill it by command line, and run name searches on a .cxx copy
metadata:
  type: feedback
---

Found 2026-09-28 (unit_1CCC00): after TaskStop on a background `timeout N python brutenames2.py UNIT ... | tail`, the python process kept running and rewrote the unit (renamed locals such as `var_-4`) after I had restored it. Kill leftovers with PowerShell: `Get-CimInstance Win32_Process -Filter "Name='python.exe'"`, skip the `mcp_windbg` rows, `Stop-Process` the rest. Then restore the unit.

Run brutenames/local_names on a copy, `src/recovered/_bn.cxx` (flags still match `src/*`, and build.py globs only *.cpp). The unit then stays free for edits and cm. Put the found names into the unit by hand. brutenames and offs.py share build/local_names/offs.obj, so don't run offs.py while a name search runs. probe.py and trialm use their own files.

**Why:** a killed search that still writes corrupts the unit mid-edit.
**How to apply:** after any TaskStop, check for stray python processes before touching the file. Related: [[cm-one-at-a-time]], [[local-names-first]].
