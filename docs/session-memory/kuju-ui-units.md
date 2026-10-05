---
name: kuju-ui-units
description: Where the 0x1C7EE0-0x1CBC80 units stand (file IO, parsed files, loc text, pools) and naming traps met there
metadata:
  type: project
---

Done 2026-09-28: unit_1C7EE0 (assert report), 1C8110 (type_1A5EA0 editing + std::string COMDATs), 1C8A30 (debug print, kujuUI::cFileIn), 1C8DF0 (kujuUI::cParsedFile, scopes, cScopeValidator), 1C9B40 (DDS via file hooks), 1CA890 (localised text: dictionary, tables, manager unk_4FEB0C = type_1CAC10). Next: cNetGame (type_4F8054, ctor 0x1CBC80, vtable 0x3E3DA8, 34 slots, 19 pure).

Network game progress (2026-09-28): cNetGame (unit_1CBC80) is done. Its players, cNetGameSessionManagement (type_4F8054_B0, unit_1CCC00), are done except the message handler sub_1CE650 (a 14-way switch; jump table at 0x1CF716). The peer-mask helpers (unit_1D48B0) are done. type_1D0100 is cPacketEngine: the trace path "\COD\SHARED\network\knet\cPacketEngine.cpp" and addPacket (sub_1D0F60). It lives in unit_1D0100 with game/netqueue.h, which holds the message classes (vtables 0x3E4E30/34/40/4C/58/84) and the list template type_1FA230_list<T> over the pooled list (unit_1FA180, game/poollist.h). Folded template instances need alias rows. Parked: the destructor 0x1D0390 (frame slots), addPacket (frame +0x30) and the copy constructors 0x1D4290/0x1D43B0. Not yet written: 1D1A30-1D2CC0, 1D3610-1D3C80, 1D35C0/F0, 1D4150, 1D4320. Next after that: type_1D4AB0 (0x1D4AB0+). Skip sNetGameEP.cpp (0x1D5DC0-0x1D7A48); its message classes (type_1D5DC0, type_1D6230, ...) are declared as local structs in type_DC400.h.
- Scratchpad tryn.py (TRYN_FILE=unit "fn sig" old=off,... candidates ADDR) and bsolve2 with every slot STRICT are the fast slot namers. bsolve2 strict gives distinct buckets, so declaration order stops mattering.

Traps:
- An assert's __FUNCSIG__ string gives real class names and class-vs-struct (V vs U in mangling). The scope class was first named cParsedFile, which was wrong; the 18 renamed functions had to be re-committed (drop their compiled.txt rows first).
- ICF-folded getters/ctors (0x1EE9D0, 0x12A1B0, 0xED650, 0x204960) serve unrelated classes: declare a method with the address name, or alias ??0 names.
- sub_1CBC30..70 return memory pools (type_1F8BF0, game/pool.h), not texts.
- Scratchpad tools: trychecks2/3 (greedy check insertion), seqchecks.py (walks statements, fulldiff-driven), trynames/trynames5, brutenames2 (4000 tries).

**Why:** a later session resumes here without re-deriving the class map.
**How to apply:** read game/parsedfile.h, loc.h and pool.h first; check names against assert strings before committing a class. Related: [[empty-if-register-shift]], [[local-names-first]].
