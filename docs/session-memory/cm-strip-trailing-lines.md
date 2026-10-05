---
name: cm-strip-trailing-lines
description: "bodiless match lines (template instances) must not end a global-scope unit; cm's strip splices the file from offset 2"
metadata:
  node_type: memory
  type: feedback
  originSessionId: 81642346-cc05-4535-a5bd-fffa4a408d89
  modified: 2026-09-29T04:37:14.878Z
---

In a unit at global scope (no namespace), never leave bodiless `// match:` lines (instance rows, EH rows) as the file's last lines: cm.py's strip, stripping the last one, finds no `\n}\n` after it and keeps `text[2:]`, dropping the opening `/*` — the build then fails with "newline in constant" / "'*/' found outside of comment" although build_sources on the real file compiles. Put the instance block before the last function with a body (or inside a namespace before its `}`). Simulate strip over every prefix of addresses before running cm.

Also keep the aliases of functions other compiled units call (e.g. a base constructor) when the unit defining them is committed: cm's baseline build strips every listed function first, and without the alias the link fails ("cannot resolve").

**Why:** cost two failed cm runs on unit_1ED730 (2026-09-28).
**How to apply:** see [[cm-one-at-a-time]]; also keep namespace-closing braces out of the gaps between match blocks.
