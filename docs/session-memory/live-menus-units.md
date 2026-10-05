---
name: live-menus-units
description: "Front-end, Live menu and in-game page units 0x1FC320-0x2251F0 done; patterns for menus, pages, hooks, selectors"
metadata:
  node_type: memory
  type: project
  originSessionId: 81642346-cc05-4535-a5bd-fffa4a408d89
  modified: 2026-09-29T09:54:07.967Z
---

State 2026-09-29 (later): the in-game pages 0x215500-0x2251F0 are matched and pushed, parked string functions aside: pause menu unit_21A5E0 with its page builder, scoreboards (21D470 rows, 21DFE0 options, 21EB30 base, 2207A0), votes (221780, 2220E0, 222350, 2225E0, 222960), use-now 221590, weapon selection 223280 with its selector instance. Next up is 0x225220, a COM-style font object built by type_5051E8::sub_226360 (the Live UI toolkit service).

Patterns:
- Each in-game menu gets its real class in livemenu.h; delete its placeholder from ingamepages.h and cast `(type_1FBDA0_menu *)new X()` in unit_204020.
- Action hooks are kujuUI templates: type_3E7264<T> (run+check), type_3E7CE8<T> (run), type_3E88C4<T> (run with a word). Repeat their member definitions in each unit; alias vtables, ??_E, and pvf_008 to 0x219F10 (single-base owner) or 0x20E600/0x20E620 (MI owner).
- Template member names resolve by their sub_ name: alias instances whose code lives elsewhere (C's pick 0x2023E0, the level key's pick 0x201E10).
- Funclets jumping to sub_43900 (out-of-line ~string) = park that function (see [[string-ctor-out-of-line]]).
- A ??_G match line must sit directly above its ??1 line for cm's replay.
- list::sort() with an out-of-line member operator< that compares with `>` = descending sort.

**Why:** these units share one class family; keeping the layout knowledge saves re-deriving it.
- cm stages every src/recovered/*.cpp: hold a second new unit aside (scratchpad) while the first unit's cm runs; cm without -m when no header changed.
- cXboxLive.h must be included first (xtl.h before RW headers); state tests are bool inlines (voice_running, unk_2918_is_1).

- XDK imports called by a matched function need `_Name@N` aliases (trial says "unverified"; cm's link fails otherwise).
- Trial slot swaps: tools/climb_names.py SRC 0xADDR 4,8 --apply.

- Selector template instances: probe a draft that explicitly instantiates `template struct type_1FCDC0<T>;` (all member bodies repeated), compile, and compare every compiled .text symbol against each address to get the mangled names; ambiguous hits are identical enum instances (use the one named for T) or a derived ??_G.
- The level key (type_211860_key) compares by const reference through get_unk_00() and copies through a getter-based copy constructor: a by-value operand with a destructor stops VC7.1 inlining operator< (then std::less isn't inlined either).
- An implicit destructor's ??_G (0x212C40, 0x214C00, 0x20EDD0) is emitted only with the vtable, i.e. with the parked constructor.
- Never create files in src/recovered while cm runs (cm stages src/recovered/*.cpp).

- In-game pages derive from type_21CB10 (game/ingamepages.h; over type_20E850 now in game/livebase.h to break the hostoptions/uiglue/ingamepages include cycle). Pointer-to-virtual actions use the compiler's vcall thunks, matched as `??_9@$BEA@AE` (class-less names, offset in hex letters). An inline virtual's COMDAT copy lands in the first unit that emits a vtable using it (type_21CB10::vf_024 at 0x215B70).
- Page units: grep the pause menu constructor (sub_21ADB0) for each page's layout string and allocation size; labels are often lower-case in the binary ("yes", "kill", "continue").

**How to apply:** next is 0x2179E0 onward (more pause-menu pages, the pause menu type_21A5E0 itself at 0x21A5E0..0x21B8C7, and type_219FE0's MI pages).
- The page base (type_21CB10) sizes come from the pause menu's builder: pad a class to its `new` size when the builder allocates more (a derived class's first field may really be the base's array element).
- Unaliased `sub_XXXXXX` members and `off_/dword_` globals resolve by address; aliases are only needed for other names (vtables, ??_E, ICF'd names, parked constructors).
