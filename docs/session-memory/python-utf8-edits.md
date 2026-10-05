---
name: python-utf8-edits
description: "Python edit scripts on this Windows box must pass encoding='utf-8', and must not carry backslash-continued macro text"
metadata:
  node_type: memory
  type: feedback
  originSessionId: 81642346-cc05-4535-a5bd-fffa4a408d89
  modified: 2026-09-25T21:50:41.282Z
---

When editing repo files from Python (heredoc scripts), open them with `encoding='utf-8'` for both read and write.

**Why:** the default codec here is cp1252; an edit that inserted "–" wrote byte 0x96 into docs/units.md (fixed 2026-09-25 with a per-line re-decode). Separately, a `\\` + newline inside a normal Python string in a heredoc collapsed a multi-line C macro onto one line (bavector.h's RwV3dIncrementScaledMacro, 2026-09-25).

**How to apply:** use `open(p, encoding='utf-8')` / `open(p, 'w', encoding='utf-8', newline='\n')`, or keep inserted text ASCII. For text with line-continuation backslashes (C macros), use the Write/Edit tools instead of a Python string. After doc edits, a quick UTF-8 decode scan of `git ls-files` catches regressions. Related: [[gate-on-build-log]].

2026-09-29: core.autocrlf=true, so docs and configs are CRLF in the working tree. Multi-line `old` strings then fail to match when a file is read with newline=''. Use the scratchpad ed.py (edit/cut_bullet/append): it normalizes to \n, matches, and writes back in the file's own style. Chain cm after edits with `&&`, not `;`, so a failed edit stops the commit.

2026-09-30: never write `open(p,'w').writelines(l for l in open(p) ...)` — the 'w' open runs first and truncates the file before it is read (emptied config/compiled.txt in commit 704461875; an empty compiled.txt still builds "== PASS"). Read into a list first. After any compiled.txt edit, check the build's "compiled pieces N" count as well as == PASS.
