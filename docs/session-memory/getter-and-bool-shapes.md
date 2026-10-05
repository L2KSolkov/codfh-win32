---
name: getter-and-bool-shapes
description: "Shapes from the front end's net glue (unit_1C3D20): garbage-slot vcalls through manager getters, one-load stand-in checks, bool returns, mask tests, /GS on named strings"
metadata:
  node_type: memory
  type: project
  originSessionId: 81642346-cc05-4535-a5bd-fffa4a408d89
  modified: 2026-09-28T21:47:44.665Z
---

Found 2026-09-28 (unit_1C3D20, unit_1C2440, unit_1C3120):

- A virtual call through a pointer global that copies a never-written slot into a temp first means a direct-return getter that is a non-static member called on a global object. A free inline or a static member gives no slot. dword_4F805C, dword_4F8054 and dword_4F8058 are unk_4F7EB8's unk_1A4, unk_19C and unk_1A0; use `unk_4F7EB8.get_unk_1A4_direct()`.
- A register rotation one step late with no candidate field: `if (!dword_4F28F0->unk_00) {}` is a one-load stand-in check. A check on a global compared in memory is +0. A float compare emits code.
- For a `bool` return, `(bool)x` gives `cmp; setne al`, and `(bool)(a == b)` gives `sete al`. Plain `x != 0` adds `xor eax,eax`, and `a == -1` gives neg/sbb/inc. Storing into a byte field with `xor` + sete means `(RwInt32)(a == 0)`.
- `mov edx,1; shl; movzx eax,[mask]; and eax,edx` is `mask.test(i)`. `(1 << i) & mask.unk_00` puts the result in the shift register instead.
- A /GS cookie with no char array means a named local std::string (type_1A5EA0). A temporary string does not trigger it.
- A struct copy loading esi before ecx and edi means assignment from an inline returning a const reference (`get_unk_40()`).
- Inline expansions with added empty ifs can stop being inlined at all (others() variants). Look for the check elsewhere.
- `test eax,eax; setne al; movzx ecx,al; cmp ecx,1` is `(bool)f() == true`. A `||` whose 0/1 result lands in a byte temp (`mov byte ptr [t], 0/1`) is `(bool)(a || b)`; without the cast the temp is a dword (sub_204E50, 2026-09-29).
- A call result stored to a slot before `sub_1FC310()->m(...)` is a named local, not the argument temp: passing the call directly pushes eax with no slot (type_2049D0::vf_014).
- cm's audit rejects struct definitions in .cpp files; put them in a header (game/uiglue.h).

**How to apply:** try these before parking; see [[empty-if-register-shift]] and [[dead-code-slots]].
- Getter's this-temp and result slots swapped (this should sit nearer ebp): make it a FREE inline taking the pointer, plain return (sub_1FFE80 get_unk_1120).
- Frame 8 too large with no leftover code: wrap a trailing call (e.g. a global's virtual) in a free inline taking the local's address; beats a nop_ filler (sub_1FFE80 show_legend).
- `call f; mov [tmp],eax` BEFORE a member call's pushes, then `mov ecx,[tmp]` = the object came from a free inline wrapping f (`widget_factory()->g(...)`); plain `f()->g(...)` calls f last. Per-use `this` slots on a returned object = inline member getters (sub_1F3510).
- A dword handle copied through TWO temps (getter's, then a setter's param copy), getter temps numbered before setter temps = the field is a type_365A0 union member read/written by value through inline getters/setters (`get_unk_14()`, `set_unk_14(type_365A0)`); the assignment `unk_2A8_h = p->get_unk_18()` loads the value before `this` (sub_3E2C0/3E3B0).
