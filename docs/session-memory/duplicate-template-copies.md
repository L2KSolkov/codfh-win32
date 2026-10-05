---
name: duplicate-template-copies
description: "is placed twice" for an STL template = the image keeps byte-identical copies under different element types; pick another 4-byte type (RwUInt32)
metadata:
  type: project
---

The image holds several byte-identical copies of std::vector<4-byte>::_Insert_n (0x12D4A0, 0x1716E0, 0x1B3DC0, 0x1EB680, 0x1EE0A0, 0x228670). /OPT:ICF can't fold them, because each has its own EH handler and FuncInfo. The linker keeps one COMDAT per name, so each copy must be a different instantiation.

If a link fails with "X is placed twice", give the second user another element type with identical code. The shared helpers (_Xlen, _Uninit_copy) are ICF-folded, so any of those names can take the folded address.

Bare `long` fails the source audit, so use RwUInt32 (mangled I) when nothing compares the elements with sign. Found 2026-09-28: the scores' sub_1B3480 and the scoreboard's var_28 are std::vector<RwUInt32>; sub_1708E0 keeps std::vector<RwInt32>.

**How to apply:** the first function (the one with no alias) in a unit claims the name; the later copies need a distinct type. Check `grep vector@HV config/compiled.txt` before choosing. Related: [[cm-replay-limits]].
