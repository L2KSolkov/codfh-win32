---
name: global-dynamic-initializers
description: An unplaced $E initializer/exit pair (0x30Bxxx/0x30Exxx) and an out-of-line implicit ctor = define the global in the owning unit; alias its folded dtor to pDtor
metadata:
  type: project
---

Found 2026-09-29 (sub_F7BA0's alarm table, dword_4C194C's sub_115470).
- A global whose class has a constructor gets a dynamic initializer (`_$E<n>` at 0x30Bxxx) and an exit function (0x30Exxx). The compiler emits both only if the unit *defines* the global. Define it (e.g. `type_4C01A0 dword_4C01A0[0x80];`) in the unit that owns the ctor's address range, then add `// match: _$E2 @ …` and `// match: _$E3 @ …`. The numbering follows the unit's initializers; list the obj's symbols to confirm.
- An out-of-line constructor copy used by the initializer can still be defined *in the class*: an inline ctor lets other functions expand it (sub_F7BA0), and the initializer still gets the COMDAT copy.
- The implicit destructor of a struct whose only non-trivial member is `type_D48D0` is empty and folded into pDtor (0x1E41C0). Alias `??1<type>@@QAE@XZ 0x001E41C0` in config/aliases.txt.
- Keep such bodiless match lines near the top of the unit, not at its end (cm's strip).

**How to apply:** grep the image for `push <ctor address>` or `call <ctor>` to find the initializer. Related: [[cm-strip-trailing-lines]].
