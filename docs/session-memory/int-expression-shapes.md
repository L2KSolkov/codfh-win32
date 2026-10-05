---
name: int-expression-shapes
description: "VC7.1 /Od integer/control idioms: neg-sbb-neg = p ? 1 : 0; if-else-break vs early break; if/else into a local vs ternary"
metadata:
  node_type: memory
  type: project
  originSessionId: 81642346-cc05-4535-a5bd-fffa4a408d89
  modified: 2026-09-27T23:05:39.590Z
---

Found 2026-09-26 (sub_41B20 in unit_040720, sub_8E330 in unit_08AB60):
- `neg eax; sbb eax,eax; neg eax` storing a 0/1 = `p ? 1 : 0`. `(bool)p`, `!!p` and `p != 0` all give `test; setne`.
- `test flag; je <break>` right before the body = `if (flag) {...} else { break; }`. Writing `if (!flag) break;` first gives `jne; jmp`, which is 2 bytes longer.
- A value chosen by `cmp; jne; mov local, a; jmp; mov local, b` and then read straight from that slot = `if (...) local = a; else local = b;`. A ternary into a named local adds a temp slot plus a copy.

- A temporary that first takes a copy of an uninitialised slot, then the real value (a switch temporary, a ternary's result) = an inline getter returning the field directly (`return unk_X;`, no local); its return slot is the uninitialised one (type_3DBC78::get_unk_1188 in sub_10F900; get_unk_538 in sub_DEC40).
- In a unit whose comments say "Local names state their slots", get the names from `tools/local_names.py` on a scratch `src/recovered/_ln.cxx` copy (it needs a path under src/); guessing bp_/slot_ names fails.
- A virtual call on a member pointer read twice, `mov edx,[ecx]; mov ecx,eax; call [edx+N]` (vtable from the FIRST load), = `local = unk_568->vf_008();` as a statement. Chaining an inline onto it (`unk_568->vf_008()->get_x()`) gives `mov edx,[eax]` and makes local_names fail on every combination (AIData::sub_404A0). The inline's `this` then reuses the named local's slot.
- A units.md "differs by one copy / other compiler build" verdict can be wrong. sub_404A0's real difference was the call shape above.
- `xor edx,edx; neg; sbb; neg; or` (a zero put in a register, then bool-normalised) = an inline setter `void set_x(bool on) { f = (f & ~1) | (on ? 1 : 0); }` called with `false`. Every constant form (`0 != 0`, `(bool)0`, `false ? 1 : 0`, a static const) folds away (type_78AC0::set_unk_12_0 in sub_6D5A0/sub_6DF90).
- An int field pushed as a whole dword to a callee that reads a word = the callee's parameter is `int`, narrowed in its body. A short parameter makes this compiler load `mov cx, word ptr`, whatever the cast (sub_6CF50, sub_72AC0 retyped).
- Repeated blocks whose locals the image groups by kind (all five animation pointers, then all four players) = function-scope locals, one per use, laid out by name. Block-scoped locals take slots in source order and interleave (type_3D2CD0::sub_6D5A0, sub_6DF90). Scratchpad `hoist.py FRAG A,B.. P,Q..` rewrites the block locals.
- A handle stored with its value loaded before `this` (`mov ecx,[t]; mov edx,[this]; mov [edx+X],ecx`) = `*(type_439E78_00 *)&field = obj->get_unk_04_h();`: a struct copy through a getter's return temporary. A named local, an inline setter or a 4-byte union copy all load `this` first (type_3D5658::sub_9C6E0's unk_4D8).
- The image's compiler groups inline temporaries by callee in reverse definition order (type_3D51C0::vf_234: both set_unk_3D4, then the handle, zero_v3d, then both get_unk_18). This compiler numbers them in expansion order, with parse-time struct-return temporaries first. Named function-scope locals reproduce the grouping only when no inline temporary sits between them.
- Scratchpad `fulldiff.py FILE SYMBOL START END` gives a full normalised diff (nd.py/trial `d` only show hunks, which misalign). `slotmap.py` (same args) maps our frame slots to the image's.
- Scratchpad `probe.py SRC.cxx FUNC...` compiles a small file under src/ and prints disassembly; use it to test idioms in isolation (about 1s).
- A function that jumps straight to its epilogue, with code after it that nothing reaches (a loop starting at its increment) = `return;` followed by dead code. VC7.1 /Od still emits it, dropping only the unreachable loop initialisation (sub_85D60, sub_860E0).
- A call to pDtor (0x1E41C0) looking like a destructor call may be an empty out-of-line method: declare `void pDtor();` in the class and alias `?pDtor@T@@QAEXXZ` to 0x1E41C0. A trial "identical ... unverified: X" can hide a wrong call target; cm's stripped build then fails (sub_857B0).
- `xor edx,edx; je else` followed by a live second test = `if (always_0() && ...)` with an inline `bool always_0() { return 0; }`. A literal `0 &&`/`false &&`/`sizeof` form keeps the xor but deletes the second operand (sub_119480).
- `(x != 0) != 0` gives `xor ecx,ecx; cmp; setne cl; test ecx,ecx`; plain `x != 0` and `(bool)x` give `cmp; je` (sub_117460).
- An inline member called on the implicit `this` gets no `this` temporary; called on a pointer (`p->inl()`) it does (unit_116310).
- `p->arr[p->idx]->field` read with the INDEX loaded first (p reloaded after) = `p->arr[p->idx]->get_field()`, an inline getter on the element returning the field directly (no temp when assigned to a local). Plain `->field`, pointer arithmetic, reversed subscripts and player-side inlines all load the array first (sub_119830, type_3DA5A0::vf_030).
- Slots between the named locals and `this` holding the same pointer reloaded (`var = unk_42C; var->arr[var->idx]->f()`) = named locals copied just before each use, not inline `this` temps; an inline returning the element adds a return temp (type_3DA5A0::vf_030).

- `cmp [x], 0; setne cl; mov [b], cl` with no `xor ecx, ecx` first = `b = (bool)x`; `b = x != 0` adds the `xor` (type_15CCE0::sub_15E9E0).

- `xor ecx,ecx; shl ecx,10h; add ecx,1` = an inline `make(a, b) { return (a << 16) + b; }` called with constants: /Ob1 substitutes them but does not fold an operation on them. `xor eax,eax; <load>; cmp eax,edx; jne` = an inline doing `if (arg == expr)` whose substituted 0 is a 16-bit parameter (RwInt16); an int parameter, a literal `0 ==`, `false ==`, a bool-returning inline and a constant-returning inline all fold it (the weapon banks, sub_16F460, 2026-09-27).
- A store whose element address is computed before a division on the right = an inline setter taking the value as an argument (`set_x(i, v) { a[i].f = v; }`); written directly, the division comes first (sub_16FF00).

**How to apply:** when a diff is just a jump shape or one extra copy, try these first. Related: [[fpu-expression-shapes]], [[inline-return-slot-order]].

Compare operand order (2026-09-29, sub_1608F0 and sub_11CF50): `mov eax, A; mov edx, B; cmp edx, eax` (A loaded first, compared second) = `!(get_x(b) == A)`, a free direct-return inline on the LEFT, e.g. `get_unk_2C_side(e)` in types/type_3D3548.h. Swapped operands, bitfields and casts all fail. An `and eax, ecx` whose right operand was computed first = a free inline `and_sides(a, b) { return a & b; }` (arguments right to left).
- `xor; test; setne; inc` into a ternary temp = `p ? 2 : 1` (constant arms fold branchless); `(p != 0) + 1` gives neg/sbb/neg + add (sub_1E2C40).
- `xor eax,eax; shl eax,2; mov r,[base+eax+off]` = an inline accessor called with a constant index (`p->get_colour(0)`); a plain `[0]` folds (sub_1F15C0).
