---
name: icf-placement
description: "Placing /OPT:ICF-shared or library COMDAT functions (pDtor, placement new, std::string ctor, ??_H): define one aliased owner, match line may sit in any unit whose obj emits it"
metadata:
  node_type: memory
  type: project
  originSessionId: 81642346-cc05-4535-a5bd-fffa4a408d89
  modified: 2026-09-30T09:42:08.006Z
---

Small unmatched functions that aliases.txt maps many names to (pDtor 0x1E41C0, pCtor 0x22C60, placement new 0x6CCF0, return-1 0x115460, text default ctor 0xE87E0) are placed by defining ONE of the aliased functions out of line in a unit and adding its `// match:` line (2026-09-30). Keep the alias lines: cmf's prerequisite build strips the function and needs them.

Library COMDATs (std::string(const char*) 0x1C5700, `??_H` vector ctor iterator 0x12000) are placed by a match line in any unit whose object already emits them; the address may lie outside that unit's range. Check with tools/coff.py `Coff(obj).find_function(name)` on build/src/recovered/*.obj.

Explicit instantiation places template members: `template T<X>::T();` or an existing `template struct T<X>;` plus a match line.

0x1C5740 (listed as ~type_1E7CF0) has no vtable store, so it is not a polymorphic destructor as written; unresolved.

**How to apply:** before calling a tiny function "binary", look up its aliases and emitting objects. tools/cmf.py handles rows below the lowest compiled row now. See [[string-ctor-out-of-line]].
