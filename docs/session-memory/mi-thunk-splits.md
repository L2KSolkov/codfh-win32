---
name: mi-thunk-splits
description: Placement link fails right after a matched function - an unsplit MI thunk or a neighbour's EH funclet inside its splits.txt range
metadata:
  type: project
---

Found 2026-09-25 (sub_A0280, commit e336dc15): a matched function can pass its own trial yet fail `xbelink` with "first difference" just past its end. The IDA range in config/splits.txt ran on over a multiple-inheritance adjustor thunk (`sub ecx, 0x18; jmp <deleting dtor>`) the database never made a function. Placing the compiled piece padded over it.

**Why:** splits come from IDA functions; MI thunks after a function are often not split out.
**How to apply:** if the build's placement link FAILs with no DIFF lines, run `python tools/xbelink.py` directly to get the offset, disassemble there, and give the thunk its own splits.txt/symbols.txt row (then commit config/splits.txt and config/symbols.txt too).

Also 2026-09-25 (XBOXPadMap, sub_A6C50): an IDA `chunk_of_<fn>` EH-funclet range in .text$x (0x2FFFD0-0x300010) also held the next behaviour's MakeNew funclet and handler; cm.py reported "build failed:" with no lines and blog.txt showed "digest mismatch ... first difference" at the neighbour. Fix: split the chunk row in two (`chunk_of_<next fn>` for the tail); chunks have no symbols.txt row.
