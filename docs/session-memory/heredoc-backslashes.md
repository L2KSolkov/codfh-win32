---
name: heredoc-backslashes
description: Bash heredocs here drop backslash escapes; write C string literals with \\ or \n through the Write tool
metadata:
  node_type: memory
  type: feedback
  originSessionId: 81642346-cc05-4535-a5bd-fffa4a408d89
  modified: 2026-09-26T08:01:40.375Z
---

In this environment, text passed through a Bash heredoc (even `<<'EOF'`) loses backslash escapes: `\\` becomes `\`, and `\n` inside a Python string written that way turns into a real newline. C string literals like `"LEVELS\\%s"` or `"...\n"` came out wrong several times.

**Why:** the Bash tool's input processing collapses the escapes before the shell sees them.

**How to apply:** when an edit contains backslashes (C escapes, Windows paths, regexes), write the Python edit script or the file itself with the Write tool, then run it; keep heredocs for backslash-free text. Check the result with grep. Related: [[gate-on-build-log]].
