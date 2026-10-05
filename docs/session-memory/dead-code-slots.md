---
name: dead-code-slots
description: Unused frame slots plus a shifted register rotation = unreachable code after a break; switch temp pre-loaded from a garbage slot = switch on a direct-return inline getter
metadata:
  node_type: memory
  type: project
  originSessionId: 81642346-cc05-4535-a5bd-fffa4a408d89
  modified: 2026-09-27T09:29:38.271Z
---

Found 2026-09-27 on the soldier (unit_1340D0):
- A frame gap no code touches, with the next statement's register off by one in the eax/ecx/edx cycle: unreachable statements after a `break;` (type_3DAFC8::vf_170, case 0x76C). VC7.1 /Od emits nothing for them, but their locals keep slots and each register load still advances the rotation. Pick the local count to fill the gap and the number of register loads so the next case starts on the image's register (next = loads mod 3: 1 -> ecx, 2 -> edx, 0 -> eax). Unused locals with no code are dropped entirely, so they do not work.
- `mov r,[garbage slot]; mov [t],r; mov r,[field]; mov [t],r; cmp [t],...` = `switch (obj.get_x())` where get_x is an inline `{ return x; }` (a direct return, no local); the garbage slot is the inline's return slot (sub_138760 with type_15CCE0::get_unk_04). Empty switches, commas and block locals do not reproduce it.

- Code after an unconditional `return;` (a plain `jmp` to the epilogue): VC7.1 /Od drops the dead statements until the first label, such as a MACRO_START do-loop's head. It emits everything from that label on, and the dropped statements still advance the register rotation. A body the image emits after the `jmp`, whose registers start mid-rotation, = `return;`, then N dropped single-load statements, then the macro (type_4D51C0::sub_15B5D0, 2026-09-27). With no label at all, nothing is emitted, but the dead locals keep their slots (sub_15B720). `goto end;` and `if (0)` don't reproduce it (`if (0)` emits `xor eax,eax; je`).

**How to apply:** try these before declaring a switch or frame-size mismatch unsolvable. Related: [[inline-return-slot-order]].

2026-09-29: an empty function with a local above `this` and one below (sub_E09D0, frame 0xC) = `RwInt32 var_4; return;` followed by dead code whose switch temporary keeps its slot. Handle copies with ret-temp + copy slot = by-value inline setter (type_3D96F0_14::set_h); a zero temp nearest ebp in the else = named default-constructed local in the else block (sub_FB910 family).
Disabled function whose dead body is STILL emitted (jmp to epilogue, code after) = `goto end;` + body + `end: ;` — a plain `return;` makes VC7.1 drop the body (sub_1B540, 2026-09-29). Unused locals there keep slots; a register step in the first macro = `{ if (0) { } }` before it.
- A function that returns (or `goto end`s) before a loop still emits the loop body; only the loop's init is dropped. Write the set-up after the jump or return. It emits nothing but keeps its locals' slots, so name them with bprobe4 (sub_D34B0, sub_D9490, 2026-09-29).
- Headers game/render.h and game/worldmgr.h pull in DSound or the Windows headers and break some units. Re-declare the one function or global you need in a lighter header.
- Insert a draft before the match line of the *next address*, not the next file position: units are not sorted.

Dead retry loops after `return` (sub_185D50, sub_186140, 2026-09-30): `const RwInt32 f = 1; while (f)` declared after the return still takes a slot, placed by its name's bucket (within a bucket, later declarations sit nearer ebp: declare a local after the const to put it above it). The loop's `mov reg,1` one register off = `if (byte_global) {}` right after the return (a dword global did nothing). A /GS cookie in the wrong place = the char buffer and the scalars below it belong in the inner block that uses them. When cmf's header commit fails with "identifier not found", the stripped function needs a declaration in the header.
