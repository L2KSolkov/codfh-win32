---
name: trial-misses-reloc-targets
description: trial passes but link fails - call bound to another symbol (class operator delete), or an "unverified" XDK import needing a _Name@N alias
metadata:
  type: feedback
---

Found 2026-09-26 (type_F2FF0::sub_F3B50): trial.py reported the function identical, but cm.py's build failed with "digest mismatch ... first difference" inside it. Inside a member of a class that declares its own `operator delete`, a plain `operator delete(p)` binds to the class's one, not the global `??3@YAXPAX@Z`. trial only compares bytes and relocation positions, not their targets.

**Why:** cost one failed cm.py run; the byte diff pointed at the call's rel32.
**How to apply:** when the placement link fails at an address inside a function that trial passed, check which symbol each call there resolves to. Write `::operator delete(p)` in members of classes with their own delete. Related: [[mi-thunk-splits]], [[inline-reserve-and-placement-delete]].

Also, from 2026-09-29 (sub_226DD0): if trial says "identical (... unverified: _XOnlineMutelistGet@24)", the link will fail with "cannot resolve". XDK imports need a decorated alias in config/aliases.txt, in the form `_Name@N 0xADDR  xonline: ...`. Take the address from the undecorated row in symbols.txt. Add the alias before running cm.
