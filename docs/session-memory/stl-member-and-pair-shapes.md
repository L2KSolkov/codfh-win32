---
name: stl-member-and-pair-shapes
description: map iterator member without a null store = const_iterator copy-initialised; insert temp with no ref slot = conversion from a std::pair local; copy ctor call = out-of-line copy ctor folded by ICF
metadata:
  node_type: memory
  type: feedback
  originSessionId: 81642346-cc05-4535-a5bd-fffa4a408d89
  modified: 2026-09-29T08:20:38.873Z
---

Shapes found matching the options page selectors (unit_1FC320, 2026-09-29):

- A map iterator member set from `end()` with no `_Ptr = 0` store first, and the map's ctor inlined (not called), is a `const_iterator` member copy-initialised in the mem-init list: `: unk_14(unk_08.end())`. A default-constructed `iterator` member adds the null store and stops the map ctor from inlining.
- `insert(value_type(a, b))` puts the temp's address in an extra pointer slot before pushing it. When the image does `lea; push` directly, the argument is a compiler conversion temp: a named `std::pair<T, U> var(arg_0, arg_4)` local passed to `insert(var)`.
- A copy of a class that calls out of line (to its ctor from a base or a string) means a declared, out-of-line copy constructor. Declare it and alias it to the function it was folded into (/OPT:ICF).
- A parameter whose caller passes a base-class temp may still be typed as the derived class when the derived ctor is inline and only calls the base ctor.

**Why:** these took many variants to find; the default forms differ only by one slot or store.
**How to apply:** check these shapes first when STL template code around maps and pairs is off by one slot. Related: [[duplicate-template-copies]], [[mi-part-interfaces]].
- One iterator copy short (frame 4 small) around `v.begin() + n` / `v.end()`: a free inline returning `iterator(v->begin() + n)` (row_at, kujuui.h), or an explicit `iterator(v.end())` copy (sub_1EA260/980/A50).
- 2 unused slots too many between an if's call temps and an inline string copy in its body: move the condition's call into an inline (`text_length()` = `sub_1F5230().size()`); its temps then share the copy's reservation (sub_1F52C0).
