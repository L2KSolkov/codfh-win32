---
name: no-ida-edits
description: Never edit the IDA database; a function IDA misses is noted and added by hand in config/code
metadata:
  node_type: memory
  type: feedback
  originSessionId: 81642346-cc05-4535-a5bd-fffa4a408d89
  modified: 2026-09-26T20:24:05.942Z
---

Don't edit the IDA database (no define_func, rename, etc. through the IDA MCP tools). If a function exists that IDA hasn't picked up, note it (docs/questions.md or docs/units.md) and create it in code: add its line to config/symbols.txt and split its range in config/splits.txt by hand, then write the function.

**Why:** the user said so on 2026-09-26, after I had defined sub_D0760 in the database. Also, the live database has drifted from the committed symbols.txt, so re-exporting is unsafe.
**How to apply:** read-only IDA queries are fine. Never run tools/export_symbols.py or tools/splits.py to regenerate the tables; edit them by hand. Related: [[gate-on-build-log]].
