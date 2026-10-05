---
name: snetgameep-unit
description: sNetGameEP.cpp matched 2026-10-01 (user un-skipped it); guard register = empty-if rotation, not compiler; snchk.py greedy search
metadata:
  type: project
---

User (2026-10-01): "snetgamep shoulsnt be skipped". All 31 functions (0x1D5DC0-0x1D7A48) now match in plain C at src/COD/SHARED/network/knet/sNetGameEP.cpp — the old "guard xor ecx vs eax" blocker was VC7.1's register rotation, fixed by SNET_ASSERT compiled-out checks ([[empty-if-register-shift]]); no __asm guard needed.

Shapes: `arg_0 = arg_0;` = the param self-copy (`mov eax,[ebp+8]; mov [ebp+8],eax`); type_1F8560_buf<bytes,bits> stack writer (RwUInt32 buffer, else /GS); B0->host() inline with its own check; mask single() returns through `if`; loop-scoped scalars below a /GS XNADDR; time stores dest-first = implicit int conversion (`t = r->read()`); folded-by-ICF member check = alias to the shared body.

Tools: scratchpad snchk.py SRC "HEADER(" SYM ADDR CANDS... (greedy ptry insertion of checks before each statement, moves above #line); sn_n5.py (env SNFN/SNV name permutations). PITFALL: never cp a ptry p_*.cpp back over the source after other edits — it is a copy of the source at that ptry's start (lost three fixes once).
