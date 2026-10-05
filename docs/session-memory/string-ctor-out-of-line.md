---
name: string-ctor-out-of-line
description: "sub_E87E0 = type_1CB670's out-of-line default ctor (aliased, ICF); declare text objects as type_1CB670 where the image calls it; sub_43900 funclets = aliased implicit ~type_1A5EA0"
metadata:
  node_type: memory
  type: project
  originSessionId: 81642346-cc05-4535-a5bd-fffa4a408d89
  modified: 2026-09-29T23:26:45.423Z
---

Solved 2026-09-29. sub_E87E0 is not std::string's own constructor. It is a string type's default constructor defined out of line, and /OPT:ICF folded identical copies: any `X::X() {}` over std::string compiles to exactly its bytes (a `_Tidy(0,0)` call in a 0x1C frame). type_1A5EA0's default ctor stays inline, because matched code expands it: sub_1C8110, sub_1A34A0, type_1F5D70. `type_1CB670();` is declared out of line (include/game/loc.h) with the alias `??0type_1CB670@@QAE@XZ 0x000E87E0`. The full build stays clean with it. sub_1AFBB0 matched with `type_1CB670 text;`.

**How to apply:** where the image does `lea ecx,[obj]; call sub_E87E0`, declare that object (local, member or temp) as type_1CB670. Callers still to retry include sub_1A8B20, sub_1F2790, sub_1F1420, sub_1E2C40, sub_1FB7B0, sub_1FC320, sub_200B90, sub_20EC00, the votes' questions, sub_21D5A0, sub_21EB30, sub_221A80, sub_223D00 and the HUD globals' initializers. Changing a member's type can break matched users, so check with a full build (tools/build_sources.py, about 30 s).

The static strings' exit thunks (sub_1AFBB0's 0x30EA80/0x30EA90) call sub_43900 out of line; they stay binary. The funclets' sub_43900 jumps are the aliased implicit ~type_1A5EA0. sub_1C5700 (solved 2026-09-30) is std::string's own `const char *` constructor COMDAT: `type_1A5EA0(p)` inline ctors in sub_1FB5A0 call it out of line; placed with `// match: ??0?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@QAE@PBD@Z @ 0x001C5700` in unit_1FB520 (a unit may place a COMDAT outside its range). Retry sub_21BD60 with the same.
