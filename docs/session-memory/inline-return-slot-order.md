---
name: inline-return-slot-order
description: Inlining quirks - 1/0 temp before an arg temp = inline with if/return pairs; static inline may not inline; ctors with destructible members never inline
metadata:
  node_type: memory
  type: feedback
  originSessionId: 81642346-cc05-4535-a5bd-fffa4a408d89
  modified: 2026-09-27T00:52:53.459Z
---

Found 2026-09-26 (sub_F93D0, the path-node filters): the image stored 1 or 0 into a temporary that sits *before* the float-cast temporary of the expression it tests (`fst [-0x10]` cast, `mov [-0xC], 1/0`). A ternary `x < K ? 1 : 0` allocates its temporary last. An inline predicate written with an if/return pair (`if (x < 150.0f) return 1; return 0;`) gets its return slot at expansion, before the argument's temps, and matches.

Also (sub_F1720): a file-scope `static inline` helper was not inlined at /Ob1 while the same helper declared plain `inline` was.

And (2026-09-26, sub_FB800): a constructor is never inlined at /Ob1 (even __forceinline, even implicit) when the class has a member whose type has a user-declared destructor (e.g. type_D48D0). If the image expands such a constructor, the member's type has no destructor there.

Also (2026-09-26, the inventory's sub_1159C0): a float "table entry or 1.0" whose temp sits before the inline getters' temps and gets both stores directly (no copy) = an inline with `if (...) return tbl[i]; return 1.0f;`. A ternary, even inside an inline, allocates its temp after `this` and the switch temps; assigning it to a local adds a copy.

Also (2026-09-26, Trigger's sub_BDC90): two byte temps (the old value of `x++` copied below the new value read back) = nested inlines `post_inc() { return x++; }` called from `inc() { post_inc(); return x; }`. The outer return temp is allocated first. An inline's own named local always lands above its return temp, whatever its name.

**Why:** hours of ternary/cast variants failed; the slot order was the only clue.
- A conditional (`c ? a : b`) keeps its result in a compiler temporary allocated below `this`. A slot holding both branches above `this` (among the inline temporaries) is an inline with a result local assigned by if/else (`r = a; else r = b; return r;`); returning the conditional or initialising the local with it gets it wrong (type_3DC9B0::sub_166FA0, 2026-09-27).

**How to apply:** when temps are right but in the wrong order, think about which inline expansion allocates them first; try if/return inlines for 1/0 results. Declare helpers `inline`, not `static inline`. Related: [[local-names-first]].

Found 2026-09-28 (voice chat):
- setne or 1/0 into a byte temporary, then movzx into a dword field = an inline setter taking bool (type_3E0F54::set_unk_04).
- A value built in place on the stack via esp for a by-value argument = an inline copy ctor on the class (type_1DDE20_mask).
- Two temporaries of one expression in swapped slots, where no names fix it = an inner block around the second local.
