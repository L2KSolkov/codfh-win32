---
name: unexpanded-inline-frame
description: "A caller with unused frame bytes equal to a callee's locals, where the callee sits after its caller, means the callee is an inline VC7.1 declined to expand"
metadata:
  node_type: memory
  type: feedback
  originSessionId: 81642346-cc05-4535-a5bd-fffa4a408d89
  modified: 2026-09-29T07:46:08.242Z
---

When a function's frame has a block of never-touched bytes the same size as a callee's locals, and that callee is called out of line and placed after its caller, the callee is an inline member. VC7.1 reserved its frame in the caller but kept it out of line as a COMDAT. The example is sub_1FB250, which calls type_1FB3C0::sub_1FB3C0: 0x50 unused bytes, matching once sub_1FB3C0 was defined inline in the header.

**Why:** Found 2026-09-29 in unit_1FA6E0. No local or check spelling produced the 0x50 bytes.

**How to apply:** Define the callee inline in its header. Keep a bodiless match line for its out-of-line copy (not the file's last line). Related: [[block-scoped-locals-below-arrays]]. Also from that unit: vector operators returning by value give per-component temps, z first; a named local per intermediate vector reproduces "temps" that sit in the named region; plain `x*b.x + y*b.y + z*b.z` pushes z, y, x (right operand first).

Committing (2026-09-29, sub_15F590): when a callee moves into its class, pass the out-of-line copy's address to cmf too (`cmf.py -m ... CALLER COPY...`). Otherwise the header commit's build (caller left out) emits no COMDAT copy and fails with "no function symbol". If the moved callee is a constructor, also list what only it referenced: the class's in-class destructor and deleting destructor (through the vtable) and in-class member constructors (sub_14C820 needed 0x14C930, 0x14CEF0, 0x14CF20 and 0x14D000). Restore config/compiled.txt with git checkout after a failed cmf run.

Frame larger than the image by a declined inline's reservation (sub_14C820): later inline expansions in the caller trim it; three uses of a coordinate accessor (`trigger_pos`) in the warning matched the image's 12 dwords.
- 8 unused bytes before `this` in a long ctor: a no-code inline just before the LAST statement fixed it; natural form = the last statement's object through an inline member accessor (`get_unk_198()->add(...)`, sub_1FC320). Scan nop positions first to find where.
- A declined inline (e.g. type_1A5EA0(const char*) member init not expanded) keeps its reserved slots until a LATER inline call in the function; any no-code inline after it releases them (sub_1E5280: 32 bytes). Find a natural accessor for a later statement.
