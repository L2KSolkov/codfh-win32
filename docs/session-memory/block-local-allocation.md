---
name: block-local-allocation
description: "Frames that interleave named slots with temporaries: nested-block locals are allocated at first use; a variable reused across sibling cases is declared in the enclosing block"
metadata:
  node_type: memory
  type: project
  originSessionId: 81642346-cc05-4535-a5bd-fffa4a408d89
  modified: 2026-09-28T00:14:40.206Z
---

Found 2026-09-27 (unit_15F1B0, unit_166990): VC7.1 /Od gives function-top locals their slots by name (the climb), but a local declared in a nested block gets its slot when first used in code order, after any temporaries met before it. A declaration with an initializer allocates the initializer's temporaries first, then the variable.

- A frame whose named slots interleave with temporaries = nested blocks; declare each local at (or in the block of) its first use.
- One slot used in two sibling `case`/`if` branches = one variable declared in the enclosing block (allocated at its first use in the first branch), not one per branch.
- A statement inside or after a block changes only jump targets; if the byte length matches but a `jne`/`je` target differs, move the trailing statement into the block.

- Don't brute-force names for nested-block slots: renaming/permuting doesn't move them. Move declarations between enclosing blocks instead (camera vf_03C 0x1752E0: tangent and matrix in the `else if` block, position in the inner `if`, the script object in the innermost `if` — matched after name searches failed).

**Why:** the base projectile step (0x1608F0), the model step (0x164620) and the mounted weapon's vf_04C (0x168300) only matched once declarations mirrored this.
**How to apply:** before climbing names, lay out declarations by first use; see [[local-names-first]] and [[inline-reserve-and-placement-delete]].

Refinement (2026-09-28): slots come in this order. First the named locals (block-local ones at first use), then front-end temporaries (return values, literals bound to `const &`), then inline expansions' locals, in code order. So a literal whose slot comes after later statements' temps is an inline's own local. The mask's `put(RwInt32 a) { RwInt32 r = a; unk_00 |= 1 << r; }` and `just()` fixed sub_1B1B00, sub_1A7D80 and sub_1B4F40 (long parked). A by-value parameter with a constant argument gets no slot, and a `const &` literal is allocated early.

Seen 2026-09-29 (in-game pages): locals in an outer scope sit nearer ebp than an inner scope's (a for-loop counter deeper than locals declared before the loop means those locals are in the enclosing block, not the loop body); within one scope the order follows the names (hash), so rename to move a slot (scratchpad namefit.py tried name forms per slot). An inline's own local (`RwInt32 r = arg_0;`) is allocated after the function's ordinary temporaries, while a by-reference parameter's temporary is allocated in code order: two otherwise identical call sites can need different inline variants (type_1DDE20_mask::unset vs reset).

2026-09-29 (sub_2016A0): values passed to `const T &` params that sit after a text temporary (value stored first, slot below the text) are literal arguments, not block `var_N` locals; local_names then says "probably not the names". Rewriting `RwUInt32 v = 0; f(v, text)` as `f(0, text)` matched. Trials (trialb.py) take ~0.65 s, so try variants directly instead of long name searches.

2026-09-29 (host options ctor, 0x200B90): two named texts in one loop body came out swapped (ours put the second above the first). Wrapping the second (`type_1CB670 text = sub_1CB7B0(...); add(i, text);`) in its own `{ }` block inside the loop body put it below the first and matched. A return value landing straight in a slot (no copy) and destroyed before an earlier local = a named local initialised from the call, not a temporary.
