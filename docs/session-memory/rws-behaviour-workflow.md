---
name: rws-behaviour-workflow
description: "How each RWS behaviour class (docs/behaviours.md order) gets recovered - pieces, splits, aliases, generators"
metadata:
  node_type: memory
  type: project
  originSessionId: 81642346-cc05-4535-a5bd-fffa4a408d89
  modified: 2026-09-27T01:01:50.207Z
---

Per behaviour (2026-09-25, 0xA23F0 to 0xB9EA0 done; PlayerTrigger 0xA9980 and CShellBehaviorClass's 25 KB HandleAttributes 0xB0980 deferred):

- Pieces in address order: MakeNew (+ `__ehhandler$...-0xF` funclet and handler from SEH_<MakeNew> in symbols.txt), ctor, own constants/vf, ??_G, dtor (EH lines if it has SEH), HandleAttributes, other methods, then the MI thunk `??_E<Class>@@WBI@AEPAXI@Z` (sub ecx,0x18; jmp ??_G).
- The thunk is usually inside the previous function's splits.txt range: give it its own splits.txt + symbols.txt row, and alias `??_E<Class>@@UAEPAXI@Z` to the ??_G address. See [[mi-thunk-splits]].
- Vtable slots that point elsewhere are ICF folds: alias them (HandleEvents -> 0xA2BF0 or empty 0x15FB30; kinds -> sub_9E000/sub_36780/...).
- Big attribute switches: dump with tools/shapes.py (jump table after `ret 4`), generate cases with a gen_*.py script, give named locals their own case blocks (slots follow source order), then tools/climb_names.py for the rest.
- In a HandleAttributes case, a value temporary (`mov [t], edx` from `[cmd+8]`, then the store) = `field = attrIt->GetAs_RwInt32()` (or `GetAs_RwReal`, also moved as an int). A direct store (`this` loaded first, no temporary) = `attrIt->GetCommandData(field)`. A case whose code has no trailing `jmp` falls through (a missing `break`). Case order in source = the case code's address order (dump the jump table). Two command loops = a first iterator in its own block, then the function's own. AddTaskTrigger (19 cases) and AnimatedBGTrigger (43) matched with no slot tuning (2026-09-26).
- A trigger class that the scripts read through `type_712B0` still derives from `Trigger` with its own fields at the right size (MakeNew allocates sizeof). Pass it to type_712B0 code via `static_cast<type_712B0 *>(static_cast<Trigger *>(this))`.
- Two command loops whose case-block locals sit below BOTH iterators = both iterators at function scope with different names (attrIt1, attrIt), not the first in a block (the base Trigger's HandleAttributes, 2026-09-27). Block nesting allocates depth-first.
- `attrIt->GetCommandData(p->field)` also explains a field's address held in a temp before the operator-> call (the reference parameter).
- When a class stops being binary (e.g. SoldierTrigger), keep its old aliases: cm.py's header-only commit strips the new functions, so derived classes still need them to link.

**Why:** this pattern repeated ~25 times; each deviation cost a failed build.
**How to apply:** follow it for the remaining behaviours (SplinePath 0xB9EA0 onward in docs/behaviours.md).
