---
name: local-names-first
description: "Naming locals for slot order: which tool when (local_names, tools/bsolve/applyn, oclimb) and how to spot non-name diffs"
metadata:
  node_type: memory
  type: feedback
  originSessionId: 81642346-cc05-4535-a5bd-fffa4a408d89
  modified: 2026-09-29T15:02:56.386Z
---

Slot-order naming, in order of what worked (2026-09-25, unit_07CA20):
1. `tools/local_names.py SOURCE 0xADDR --apply` for flat functions (solved 7DCA0, 7DEB0, 801C0 where scope_names.py gave up after 3000 compiles).
2. Scratchpad `bsolve.py SOURCE ADDR slots` + `applyn.py SOURCE ADDR "S=name ..."`: bucket-rank greedy over extra name forms, declarations highest slot first. Solved 7E420 (12 locals plus block locals), 7EAB0, 7ECB0, 7EE30, 7F0E0.
3. `tools/climb_names.py SOURCE 0xADDR slots --apply` (was scratchpad oclimb.py): greedy on real /FA offsets. Solved 7CF40 when bsolve's ranks were wrong. Leave unused locals (no /FA equate) out of its slot list.
Before any of these, diff with slots masked (tools/structdiff.py SOURCE ADDR`). A real code difference usually shows there: a signed vs unsigned shift, a wrong pointer base, a pointer-to-array local declared out of order.

4. When bsolve gets every slot but an array (or struct) that sorts *last within its bucket*, rerun with tools/bsolve2.py SOURCE ADDR SLOTS STRICT` (STRICT = comma list of slots that must open a new bucket, e.g. the array and the slot after it). Solved sub_E9FB0 (25 locals, 4 byte slots) in one compile after local_names gave up.
Do NOT use a depth-first search over /FA offsets (scratchpad dfsn.py) on more than ~6 slots: on sub_E9FB0 it backtracked for 40+ minutes (2026-09-26) and the user saw it as stuck. In /GS functions declare highest slot first; that alone fixed sub_E9CA0.

5. When bsolve2 puts two locals in the same bucket the wrong way round, swap their declarations: within a bucket the one declared later usually lands nearer ebp (fixed F2B00, F2C30, F3070, F34C0 and F43B0 on 2026-09-26). An initialized declaration (`T x = v;`) can break the order; declare it plainly and assign on the first line.

6. Scratchpad `solve.sh FILE ADDR "SIGSUBSTR" SLOTS [STRICT]` chains bsolve2, renames var_<slot> (`ren.py`) and reorders the declarations farthest slot first (`reorder.py`, which also turns initializers into statements); it solved every slot problem in astarpathfinder.cpp (2026-09-26). A local that lands after `this` with no name is a temporary: `return &a[i++];` makes one (sub_F6400), and a pointer the original held in a named block local shows as a named slot between the others (sub_F6FC0's vf_008 results).

7. Speed (2026-09-26; the user found local_names runs on unit_0441B0 too slow): first build a trimmed copy with tools/slim.py UNIT FRAGMENT src/recovered/_ln.cxx`, which keeps the unit's preamble, its file-scope declarations and the one function (~100 lines, 1s per compile). Then run scratchpad `nd.py FILE ADDR`, which diffs with frame offsets and call/jump targets blanked. Run local_names only once nd.py shows nothing but relocations. If the code differs, local_names searches for minutes and can never succeed: sub_63110 hung until the real difference was fixed, then solved in 1s. Cap runs with `timeout 180` and `python -u`.

8. An unused gap in the frame (bytes no instruction touches) = an unused local. When local_names says "the difference is probably not the names", check the frame size first. If the gap sits below every named slot and just above the temporaries, declare the unused local in a nested block (block locals come after function-scope ones), then use solve.sh for the rest (sub_98200, 2026-09-26).

9. A local whose constructor runs after some statements is declared at that point, still at function scope. A nested block does not help: block locals interleave by bucket too. If solve.sh then puts it one slot early (it shares a bucket with an earlier-declared local), pass its slot as STRICT (the 5th argument) so its bucket must rise (sub_948A0's type_93DF0, 2026-09-26).

10. Two same-type locals (e.g. RwV3d) whose slots swap whatever the names, with climb_names "stuck" = one array or struct: the first-assigned one at the lower address is element 0 (type_3DAFC8::vf_244's direction and position, `RwV3d v[2]`, 2026-09-27). Likewise two slots that must be named locals although an inline would explain them (the raw result and its cast, the trigger held before use: vf_058).

11. Unexplained 4-12 byte gaps just above 16-byte locals in an aligned (ebx) frame, every such local at a 16-aligned offset = a `__declspec(align(16))` type (vec4.h's type_140490; sub_139620, 2026-09-27). Unused placeholder locals never fill such gaps: VC7.1 drops unused structs and puts unused ints in the padding.

12. Big flat functions (30+ locals): skip local_names. On sub_147B50 (33 slots) it searched for over 10 minutes with no output, and the user saw it as stuck (2026-09-27). Run `tools/climb_names.py` straight away with every named slot, nearest first, in the background under `timeout`, on a `.cxx` copy of the unit (not globbed by the build, so commits can run meanwhile). It solved that function in 400 compiles, about 2 minutes. "final True" means only the names are right; also trial the result, since a misplaced closing brace showed up only after the names were fixed.

13. climb_names takes a function's block to end at the next `// match:` line, so `__ehhandler$` annotations under the function make it fail ("substring not found"). Remove those lines for the climb and put them back afterwards. It only names function-scope slots. Block locals (a type_3CE1FC iterator, its list pointers) need names in the same forms a matched sibling used, shifted to the new offsets (type_3DBC78::vf_1D0 from type_3D3548::vf_1D0, 2026-09-27).

14. climb_names SLOTS are bare hex matching the var_ suffix (`4,8,C,1C`), never `0x4`: with the prefix it looks for var_0x4, finds nothing and prints "stuck at slot 0x4" at once (vf_2D8, 2026-09-27). When a climb is stuck, first check the slot list's format.

15. climb_names only renames locals already named `var_<slot>`: descriptive names (RW source's chHeight, rectQuad…) make it "stuck at slot 4" at once. Rename them to their slots first, then climb (sub_16BE20, 19 slots, 181 compiles, 2026-09-27).

16. An unused slot between used ones (image leaves -8 untouched) = an unused function-scope local; its name must rank between its neighbours. Brute-force its name paired with its neighbour's name (scratchpad v8b.py; type_3DF9C4::vf_000 needed `bp_4` + `x8`, 2026-09-27). A ref array whose construct loop sits after an early-return `if` is a function-scope declaration placed after that `if`, not an else block.

17. A frame gap between a scalar and an array can come from bucket order alone: climb the used slots first, and only then consider an unused local (sub_19B6D0 needed no extra local once climbed, 2026-09-27). Ad-hoc name-search scripts must rename inside the one function's block: a whole-file `re.sub` renamed committed siblings' locals and broke the build.

18. Frame size wrong before any naming = the sizes are wrong, not the names. Buffers are 8-aligned, so compare the frame size first. Check the gap above the top buffer: the image's buffer ended at -8 while it had to be WCHAR[0x40], not [0x42]. A struct holding a byte array (XCALCSIG_SIGNATURE) counts as a buffer, so keep it as dwords. Once the frame size matched, scope_names solved 18 slots in 3 scopes with declarations farthest-first. A mid-loop result local that sits right after the function scope belongs to the if/while block (sub_1A1820 and sub_1A1BB0, 2026-09-28).

19. climb_names compiles the unit only up to the function, but the functions after it change the slot order. Its "final True" failed in the whole-file trial for sub_1C58C0 (2026-09-28). Confirm with trialm; if they disagree, brutenames (whole file) settles it.

20. Reach for bsolve first. Never write a one-compile-per-candidate search: a name-pair search (pairfit.py over 46x46 forms, about 25 minutes) looked stuck to the user, who asked for it to be parked and for the faster script (2026-09-29). bsolve took 0.3 s on CUITextBoxObject::vf_01C (27 slots). After it, hoist every local whose image slot lies above the first block local to function scope; that fixed the rest.

**Why:** scope_names only walks the var_/local_ forms group by group, so it fails on big single scopes.
**How to apply:** use scope_names only for block-scoped layouts. The scratchpad tools are lost when the session ends; if they keep proving useful, port them into tools/. Related: [[gate-on-build-log]].

21. (2026-09-29, sub_21BA50) bsolve returns buckets all 0 when its bucket probe fails (e.g. a /GS frame); don't trust that. Then use tools/pnames.py SRC ADDR old1,old2 slot1,slot2`, which tries every FORMS combination for the listed locals on 10 threads, one compile per copy (196 combinations in 34 s). The user wants brute-force searches multithreaded, not serial. Also: /GS cookie directly above an array with scalars ABOVE the cookie = the array is declared in an inner block (function-scope scalars stay on top).
