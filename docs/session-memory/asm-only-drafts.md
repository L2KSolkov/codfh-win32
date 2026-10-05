---
name: asm-only-drafts
description: Draft functions from the assembly (xdis.py) only, not IDA's decompiler; big aligned-frame functions go fast that way
metadata:
  type: feedback
---

User, 2026-09-29: "use assembly only". Don't call the IDA decompile tool when drafting. Read `tools/xdis.py START END`. (The decompiler also silently drops code under `if (0)`.)

Lessons from sub_7A580 (0x1B0C bytes, matched in about 10 compiles):
- In aligned (ebx) frames, slots come in first-use order, so names never matter. Temporaries interleave with the named locals.
- A pointer copied into a slot right before a `mov ecx,[t]; mov edx,[t]; mov eax,[ecx+X]; or eax,[edx+X+4]` test is the compiler's own temporary for a 64-bit `if (p->mask)`. It is not a named copy.
- `xor reg,reg; je far` over a big block is `if (0) { ... }`, and the block is still emitted.
- A struct local holding a byte array gets a /GS cookie; split the padding into scalars.
- A for loop whose increment is a call can be a `while` with the call at the body's end. The image jumps back to the compare.

**Why:** the user asked; the asm is the ground truth.
**How to apply:** every draft. Related: [[draft-diff-workflow]], [[aligned-frame-shapes]].
