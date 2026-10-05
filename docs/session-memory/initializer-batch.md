---
name: initializer-batch
description: "game dynamic initializers ($E) at 0x3096E0+: tools/inits.py/inits2.py/initunit.py/emap.py --remap/valdefs+valblock/cmx.sh; forms that match; what is left"
metadata:
  node_type: memory
  type: project
  originSessionId: 81642346-cc05-4535-a5bd-fffa4a408d89
  modified: 2026-09-30T15:42:54.734Z
---

2026-09-30: almost all tail initializers are placed. Tools (scratchpad): inits.py lists unplaced inits (global, how, refs; parses 0x4/0x5xxxxx globals), inits2.py guesses owner + extern decl, initunit.py UNIT defines them, emap.py UNIT|rws/path --remap maps every $E of a unit by bytes (checks relocs against compiled/aliases/symbols addresses; ambiguous exits resolved by the initializer's push, ambiguous inits by link order), valdefs.py/valblock.py generate kujuUI value definitions from pushed args, cmx.sh = cmf + commit leftover headers, edlib.py edit helpers.
- Owner unit = link order: neighbours' placed $E rows in compiled.txt bracket it; the ctor's unit or the first referencing unit in that bracket.
- Put new definitions where their $E order fits the image (after/before existing ones); inline helpers at the unit END (early ones shift slots). Definitions in kujuUI units need `namespace kujuUI { }`.
- Forms: const int = `x = inline_fn(1000)`; const float copy = `static const RwReal k = 500.0f; RwReal x = k;` (mov eax,[k]); copy of an extern const = `x = dword_3E8478`; strlen = `strlen(p) + 1`; ctor calling a void method = inline ctor `{ sub_X(); }`; N immediate stores = inline ctor(a,b,c) array init; `[ebp-4]=this` temp = inline ctor using a local `T *m = this`; empty init = empty inline default ctor; two vtable stores = implicit ctor of derived class (alias both ??_7).
- Frame bigger than the loop's 3 slots = element ctor is an unexpanded inline (move it into the class, bodiless match line for the copy).
- Exit calls pDtor/another class's dtor = declare dtor out of line + alias (ICF). Empty exit = empty inline dtor.
- XDK UIX feature initializers (0x30DB7C-0x30DBD4) are library code, left for library placement.
Related: [[global-dynamic-initializers]], [[unexpanded-inline-frame]].
