# Deferred questions

Questions that need the owner's decision, written down instead of asked so the work can run
unattended. Each records what was done in the meantime. Answer inline; resolved questions move to
the end with the answer.

## Open

- **An `AGENTS.md` shown to the session contradicts the plan.** Rules attributed to
  `AGENTS.md` appeared in the session context. They forbid all naming and all `__asm`, and they
  make `sNetGameEP.cpp` the target. They also cite files this repository does not have
  (`attic/`, `config/quarantine.txt`, `tools/audit_matches.py`, `config/units.txt`). No
  `AGENTS.md` exists in the tree or its history. *Meanwhile:* `docs/PLAN.md` and the owner's
  instructions in the session are followed. Those instructions allow names with evidence and
  the two-instruction guard `__asm`, and they skip `sNetGameEP`.

- **Float "variables" that are probably pooled literals.** `include/game/data.h` declares
  `flt_3CD8E0` (1.0), `flt_3CD8E4` (5.0), `flt_3CDB50` (30.0), `flt_3CDB54` (120.0) and
  `flt_3CDB74` (0.9) as `extern const` variables, because `sub_12B20`, `sub_17AB0` and
  `sub_18BB0` subtract or compare them at run time where VC7.1 folds literals. But `0x3CD8E0`
  is referenced by 432 functions across the image, which only a pooled `/GF` literal
  (`__real@3f800000`) explains, so the "variable" reading is probably wrong and the unfolded
  arithmetic has another cause not yet found. The bytes match either way (the relocations resolve
  to the exact addresses); an authentic link (M7) would not, since no symbols by these names
  exist. *Meanwhile:* left as declared; revisit before M5/M7.

- **`0x2A3C70`: `RwV3dLength` or `PVSFindDiagonalSizeOfBBox`?** The database names the
  function `PVSFindDiagonalSizeOfBBox`, but that is a `static` in RenderWare's `rppvs.c` (not
  callable from game code) that subtracts two box corners, while the body at `0x2A3C70` returns
  the length of the one vector it is given. Game code calls it as `RwV3dLength`, linked through
  `config/aliases.txt`. *Meanwhile:* the database name is left as it is; the alias records the
  evidence.

- **Pushing** (resolved). On the user's instruction `master` was force-pushed over
  `origin/master` on 2026-09-24; the pre-reset history survives locally as
  `backup/pre-reset-2026-09-24`. Commits are now pushed as they are made.
- **The first unit's end.** `src/recovered/unit_012000.cpp` continues past the AI object's
  constructor on the evidence in `docs/units.md`, which fits one unit but does not prove it.
  *Meanwhile:* functions are added in address order; a boundary found later only moves source.
- **The two performance lookups.** `dword_4B92D4` (`type_ECDA0`) and `dword_4B92FC`
  (`type_ED340`) are both 0xC-byte objects built by `sub_1EE9E0`, loaded by different readers
  (`sub_EC750`, `sub_ED030`) and queried by different methods (`sub_ECDA0`, `sub_ED340`), which
  could be one class or two sharing a constructor (identical code folded by `/OPT:ICF`).
  The scene lookup `dword_4B9300` (`type_ED850`) is the same question.
  *Meanwhile:* they are separate placeholders in `game/data.h`; merge them if a shared method or
  vtable turns up.
- **The live IDA database has drifted from `config/symbols.txt`** (found 2026-09-26). A fresh
  `tools/export_symbols.py` run drops functions the committed table has (among them `sub_80300`,
  and several 8-byte stubs such as `sub_A02C0`), turns `sub_7FFD0` into `sub_80008`, and changes
  about 130 split ranges. The committed tables were kept; the only change made was defining
  `sub_D0760` (vf_214) in the database (an edit made before the instruction not to touch it;
  it was left in place rather than undone) and adding its line to `symbols.txt` and `splits.txt`
  by hand. *Question:* which is authoritative, should the database be brought back in line, and
  should the `sub_D0760` definition be removed from it? *Meanwhile:* the database is not edited;
  a function it misses is added to `symbols.txt` and `splits.txt` by hand.
- **`CSystemCommands::UpdateFrame`'s signature.** The database names 0x12DC20
  `?UpdateFrame@CSystemCommands@RWS@@SAXAAURwFrame@@PBURwMatrixTag@@@Z` (the Studio
  sources' matrix overload), but its only caller (`sub_1330B0`) passes the command
  from `CAttributeCommandIterator::operator->`, and it copies the matrix from the
  argument's +8 (the command's data), so it is written as the command overload
  (`...ABVCAttributeCommand@2@@Z`). The database's decorated names are signature
  matches (as at 0x1EE9D0), not the build's.
  *Meanwhile:* `src/rws/framework/core/attributehandler/csystemcommands.cpp` uses
  the command overload; say if the database name should win.
- **sub_1AB440's float argument (2026-10-01 retry).** The image passes `dword_4FB9E0.unk_08.unk_2C`
  as `fld dword; push ecx; fstp [esp]`. Tried: unary `+`, `-(-x)`, comma, conditional, `*1`,
  `(RwReal &)`, `*(RwReal *)&`, `const`/`volatile` casts, member and free inline getters (direct,
  through `r`, `__forceinline`), `(RwDouble)x` and `(RwReal)(RwDouble)x` (both add an `fst` to a
  temporary). Every other form passes it with `mov`/`push`.
  Current-header follow-up: removing the eight historical `unused_slot()` calls
  restores the original 0xB8 frame and stack offsets. The float mismatch remains.
  Double getters, float/double conversion operators, functional casts, double
  multiply/divide by one, and forwarding inlines still add rounding stores or
  pass through integer registers. Best current draft: `view_state_followup.cpp`.
  All follow-up trials keep VC7.1 fixed.
  2026-10-02: the callee at 1B6DE0 confirms a single four-byte argument,
  copied directly into the countdown. Const/volatile qualifiers on its
  parameter and the argument cast leave the caller identical to baseline
  (all 16 combinations). Arithmetic identities force FPU evaluation but
  retain the add/subtract/multiply/divide; double conversions retain the
  extra rounding slot. Explicit /Op and /Op- do not resolve either form.
  A scan of game code 0x12000-0x22B000 found this is the only FLD immediately
  followed by PUSH register / FSTP [esp]. It has no matched peer supplying
  that exact source shape. Reproduce with docs/drafts/view_state_identity_trials.py,
  view_state_precision_check.py and view_state_qualified_calls.py. Still parked.

## Resolved

- **Localization return chain (2026-10-01).** `sub_1CAF30` now matches
  (208 bytes, eight relocations). It and `sub_E3970` return `type_1A5EA0`;
  `sub_1CB6B0` is the constructor of `type_1CB670`, initializing that exact
  base type from the returned object. The previous std::string declarations
  arose from assigning the constructor body to the wrong class. One
  compiled-out language check fixes the register step after lookup.
  Axis/Allies local statics in `sub_1AFBB0` use the same returned type. Their
  generated shutdown thunks now match too, replacing the separate ABI
  callback reconstruction described below; `unit_30EA80.cpp` is retained
  as a history note. Existing localized temporary declarations of the base
  type retain a compatible binding to the same constructor entry.
  All seven direct caller units pass their existing match annotations.
  Reproduction: `build/tooltmp/localized_return_context.py` and
  `localized_return_callers.py`.


- **Shutdown thunk placements (2026-10-01).** Existing generated source
  already reproduces `30DF60/30DF70/30DF80/30DF90/30E0C0/30E680` (15 bytes,
  two relocations each). The first five are registrar exits in units 09AD40,
  0A02D0 and 0A9980; the sixth is CMemHandler's local singleton exit. Receiver
  addresses and the matched initializers' atexit arguments establish the exact
  mapping; instruction shape alone cannot distinguish registrar exits.
  Historical first reconstruction (superseded by the corrected return chain
  above): `30EA80/30EA90` matched as C++ callbacks in `unit_30EA80.cpp`.
  They call the existing destructor through its observed ECX-only interface:
  a one-argument fastcall declaration is ABI-equivalent here (no stack args).
  The receiver addresses and the original atexit registrations establish both
  local-object bindings. The generated std::string exits inline _Tidy; depth
  pragmas do not restore the calls, extern template leaves them unchanged,
  and a destructor specialization is rejected as already instantiated. Explicit
  destructor expressions also differ: /Ob0 calls the scalar deleting destructor
  with a flags argument. No compiler/header change is needed for the callbacks.

- **Packet array copy (resolved 2026-10-02).** `sub_1D4290` now matches
  all 144 bytes and two relocations in unit_1D4290.cpp. An explicit
  instantiation of the existing packet-list append emits the copy from
  game/netqueue.h alone; the append also matches its existing 133-byte
  body. No new runtime helper, type or compiler setting is needed.
  The HUD header introduces CLinearMemoryManager::Instance's $S1 guard.
  This advances the compiler's generated array locals from $S1/$S2/$S3
  to $S2/$S3/$S4 and swaps the count/destination slots. Replacing only
  that inline body with a declaration in a scratch overlay fixes the
  full unit, with every existing annotation still exact. Early explicit
  instantiation before the HUD include does not bypass the guard.
  Production instead uses a separate packet-only instantiation unit.
  Reproduce with docs/drafts/packet_copy_context_matrix.py and
  packet_guard_context_trials.py.
  Historical trials below preceded the include-context diagnosis. /FAsc identifies them
  as `$S2` and `$S3`, with source pointer `$S4`; source local renaming cannot
  reach them. Root copy-constructor declarations, mutable time-copy overload,
  member initialization versus assignment, out-of-class inline definition,
  default scalar argument, throw(), typedef array and enum extent leave the
  difference unchanged. A volatile copy source, reference default argument,
  and empty time destructor change frame/control-flow shape. Explicit array
  member copy initialization is rejected by VC7.1. Scratch reproductions:
  `build/tooltmp/packet_array_context.py`, `packet_array_initializers.py`,
  `packet_array_more.py`. No production type change from these trials.


- **Packet mask copies (2026-10-01).** `sub_1D43B0` and `sub_1D4320`
  match with separate mutable and const mask-copy overloads. The const overload
  carries two compiled-out word checks, giving the required register step
  inside the implicit packet constructors; mutable copies remain unchecked.
  `voice_mask_copy` takes a mutable reference and keeps its existing own check.
  A scratch scan of recovered units found only that voice helper needed changing.
  `sub_1D4290` is now also matched through the packet-only instantiation
  described above.


- **May the remaining parked near misses be transcribed like Bink? (2026-10-01)** Bink is
  done (C plus `tools/img2masm.py` MASM units) and the XDK leftovers are stand-ins repacked from
  the image (`src/xdk/`). What remains unplaced is decompilation work that earlier sessions
  parked after many variants: about 120 RenderWare Audio functions (`0x23C490`–`0x2516E0`,
  `0x2FD5D0`–`0x2FEC00`), about 25 RenderWare 3.6 functions (the 2D toolkit, the Xbox skin
  and vertex-format code, `RpWorldStreamRead`, `RwStreamSkip`; each listed below), about 45
  game functions with 128 EH chunks that follow them; `sNetGameEP.cpp` is matched (2026-10-01). Should RenderWare Audio (third-party and prebuilt, like Bink) get the same MASM
  transcription? For RenderWare, your rule allows `__asm` only where RenderWare itself used it,
  so its near misses stay C work unless you say otherwise.
  *Answered (2026-10-01):* "for the remaining items, no __asm unless the function originally had
  it." RenderWare Audio, RenderWare 3.6 and the game stay C work.

- **The fade's reciprocal depth** (resolved by evidence). `sub_125060` loads the near plane
  first because its source uses RenderWare's `RwCameraGetNearClipPlane` macro: the
  parenthesised `((camera)->nearPlane)` it expands to makes VC7.1 load the field first and
  divide with `fdivr`, where a bare `camera->nearPlane` loads 1.0 first. The main render's
  screen quad (`sub_1288F0`) has the same form.

- **`/Zi` for the units** (approved 2026-09-26). It reproduces the image's realigned `ebx`
  prologue and keeps every match; `config/flags.txt` now has it (`docs/toolchain.md`).

- **`double` for a CRT call** (resolved by evidence, not by a rule change). `sub_1DF60` and
  others call the CRT's `_fabs` on a float widened to double. Writing that needed a bare
  `double`, which the audit forbids. The build turned out to use `/Ob1`
  (`docs/toolchain.md`), and under it plain `fabs(v)` on a float expands to exactly that code,
  so no `double` is needed.
- **Functions the database misses, added by hand (2026-09-27).** `sub_181F60` (0x181F60, the gimp
  vehicle of type 1's vf_254) and `sub_182990` (called from it) sat inside `sub_181F40`'s and
  `sub_182960`'s ranges; the 25 functions from 0x18B700 to 0x18CE40 (the message texts' openers after
  `sub_18B6F0`) sat inside `sub_18B6F0`'s. The 20 after them (0x18CFA0 to 0x18F330, more message openers
  and their callbacks) sat inside `sub_18CE90`'s, `sub_18D7C0`'s and their neighbours' ranges. Each now has its own line in `symbols.txt` and
  `splits.txt` (sizes to its last `ret`); the database was not edited. *Question:* should they be
  defined in the database too?
  On 2026-09-28 the same was done for `sub_1A2580` (0x1A2580, the damaged-profile box's opener,
  message 0x2D in `off_42B518`), which sat inside `sub_1A24D0`'s range.
  Also 27 functions from 0x1A3020 to 0x1A3B40. They are singleton getters and their neighbours:
  function-local statics built on first use with three vtable stores, then a call on them. They sat
  inside the ranges of `sub_1A2E40`, `sub_1A3190`, `sub_1A3240`, `sub_1A3330` and `sub_1A3550`.
  And 24 more from 0x1ACAB0 to 0x1AF5D0: the multiplayer manager's message handlers (its table at
  0x42C850 lists them). One of them, 0x1AF320, directly follows a `ret 4` with no padding.

## Inline assembly for the FPU control word (2026-09-27)

sub_19D290 and sub_19D2D0 (unit_19CB20) set and restore the FPU control word with inline
assembly in the original: `fstcw word_4F39EC`, the 16-bit `mov ax, word_4F39EC; and ax, 0xF0FF;
or ax, 0xC00; mov var, ax`, then `fldcw var` (and `fldcw word_4F39EC` after a call). Both match
byte for byte with an `__asm` block, but tools/audit_sources.py allows no inline assembly except
the debug guard. They are parked ("Not yet matched") until it is decided whether the audit should
allow an FPU control-word block (fstcw, fnstcw, fldcw and 16-bit register arithmetic on locals and
globals). *Resolved 2026-10-01:* the owner allows `__asm` where the function originally had it
(docs/PLAN.md amendment); both are matched.

## Names for inlines that have no address (2026-09-28)

Rule 3 says a name is never invented to describe what code appears to do. Inline functions compile
away, so they have no database name. Earlier sessions named such inlines by field
(`get_unk_310`) or by what they do (`type_1DDE20_mask::add`, `clear`, `test`, each with an
"Evidence:" comment). While matching the players (unit_1CCC00) and the peer-mask helpers
(unit_1D48B0), these were added in the second style:
- `type_1DDE20_mask::insert`/`remove` (the reference-taking forms of add/clear);
- `type_4F8054_B0::joiner`, `self`, `self2` (the unk_3C/unk_08 getters that carry compiled-out
  checks) and `in_game` (a test of unk_0C after two checks);
- the enum `type_1DDE20_mask_fill` (the argument of the out-of-line constructor sub_1D48B0).

*Question:* should inlines with no address keep descriptive names like these, or take field and
address based ones only (for example `get_unk_3C_2`, `test_unk_0C`)? The names change no code,
so switching later only means a rename.

## String expansions reserve more frame here than in the image (2026-09-28)

The font's constructor (`sub_1E5280`) matched once its last glyph went through an inline (the name's
declined `type_1A5EA0(const char *)` constructor keeps its slots reserved until an inline call releases them).
(The integer value's display, `sub_1E7A80`, parked for 16 bytes, matched once its first append went through
the `add_text` inline, which the image's reference slot shows.) The difference may come from the
image's `xstring` (its default constructor is out of line too, `sub_E87E0`, where the XDK's is
inline).

*Question:* is there another copy of the XDK's STL headers (or a define that changes
`basic_string`'s inlines) that the game was built with?

The image library's constructor (`sub_1ECBD0`, unit_1ECBD0) matched once its raster reads went through an
inline accessor (`type_1EEEE0::get_unk_00`, the image's two temporaries): with the missing inline in
place, the unused slots before it came out as the image's too.

## The selectable widget's first argument is a look, typed as a string (2026-09-28)

The selectable widget's constructor (`type_3E76B4`, `sub_1EFDA0`) passes its first argument straight to the
look's constructor (`type_1E37A0(type_1E3BA0 *)`), and its third interface's slot (`pvf_000`) passes its
argument to the look's setter (`sub_1E3A00(type_1E3BA0 *)`). Both are declared with other types (`const
char *`, `RwInt32`), as are the callers that pass them on (the button, caret and combobox constructors and
`sub_1F7D80`, whose result the button's creator passes). unit_1EFDA0 casts. Retyping them changes the mangled
names of committed functions (the caret's constructor among them).

*Question:* retype the chain to `type_1E3BA0 *` now, or leave it until the creators' lookups
(`sub_1F7D80`) are matched and show what they return?

## The log's debug display (sub_1B00F0, 2026-09-29; resolved 2026-10-01)

`type_4F84B8::sub_1B00F0` begins with `return;`; the 5.6 KB after it is still emitted (a `for` loop's label
keeps it reachable). It is now down to two instructions (the copy of the peers mask into its local, `cx`
where the image has `dx`); every slot, the frame and all other code match. What it took:

- The frame: the vector's construction leaves 3 unused dwords in the image, 20 in ours, because the
  image spends its inlining budget on later inlines. Three conditional lines through an inline `show()`
  (the display flags test, game/startup.h) and the coordinates passed as ints (sub_16BB00 takes
  `RwInt32`s: its word stores read the same) give the image's frame.
- The names: bsolve for the function scope; the peers mask declared mid-function needs a name in a later
  bucket than its neighbours (it comes first in its bucket), and the voice block's five locals likewise.
- Registers: the player line's mask test is a checked inline (`bit()`), the latency accessor has a
  compiled-out member check, one before the voice status calls, and a member check at the end of an
  `unk_B0` accessor variant fixes `others()`'s entry. Checks on locals do not move registers; checks on
  members move the next load one on; three in a row cancel.

Resolved 2026-10-01: `get_unk_B0_checked()->others_checked()` (the check before the copy out moves
the copy one load on), the voice loop's test through `bit()`, and the compiled-out `unk_34F4` check that
had compensated after the statement removed. The unit's initializers became `_$E2`/`_$E3` with the
added includes.

## A vote's confirmation's question (sub_221A80, resolved 2026-09-29)

Matched: the kick case's name pointer sits in a nested block, the returned text is named `text` and the
case blocks' names are `var_1A4`/`bp_188`, `var_1C0`/`var1DC` (slot order). The frame needed one more
inline expansion after the formatting: a compiled-out debug print of the buffer (`debug_text(local_164)`).
A discarded `text.size()` gives the same frame; an empty `if` there changes the registers instead. When a
frame is short by leftover slots and nothing else differs, try such a no-code inline call taking a
variable just built.

## Unused frame slots come from inline destructor chains (resolved 2026-09-29)

The session list's join (sub_20CFB0) compiled with an 8-byte larger frame whatever its call looked like.
The unused slots are left by the inline expansions this compiler attempts: a temporary's destructor chain
leaves a few dwords per temporary (`type_1CB670` -> `type_1A5EA0` -> `std::string`, down to `_Tidy`), and
the compiler packs those leftovers with the live temporaries, so one extra level can change the total
anywhere in the function. The image's literal texts are `type_1A5EA0("...", 0)` temporaries (the
constructor at 0x1CB6B0 is shared through /OPT:ICF with `type_1CB670`'s): written so, the join matches.
`#pragma inline_depth` moves the same slots (depth 4 and below leaves fewer), which is how this was found.

The compiler also skips the attempt once a function's inline budget is spent. The host options' read (sub_201890) had no room for its text's leftovers: with its settings reads written through eight free inline accessors (game/uiglue.h; member accessors leave leftovers of their own) it matches. So when an image frame is smaller than ours by exactly such leftovers, look for inlines that emit no code of their own (accessors, empty checks) in the original.

## Resolved: the CCESS pick's random index (sub_8AFF0, 2026-10-02)

Now matched: 392 bytes and one relocation in unit_08AB60.cpp. The
inclusive upper-bound/count expression `RpRandom() % (count - 1 + 1)`
retains `mov ecx,[ebp-4]; xor edx,edx; div ecx` after the constant
operations disappear. The equivalent `(count - 1) - 0 + 1` also matches.
Restoring the local-name order from the saved draft reproduces the
0x1AC frame and every stack offset without changing its 100-entry array.
The production function supersedes draft_8aff0_keep.cpp.

Earlier forms that still divided directly by the stack slot:
a comma expression, `+ 0`, `| 0`, `*&`, casts through long, unsigned long, pointers, references, enums and
int64, volatile and register counts, counts declared long, int or unsigned, and inline helpers (by value, by
reference, with a local, returning the pick). Only a conversion that emits code (bool, RwUInt16, float)
or a full-width bitfield puts the count in `ecx`. A bitfield also turns the count's plain stores into
read-modify-writes, which the image does not have. Only four sites in the image have this shape.

## Resolved: pause-menu loading sub_21BD60 (2026-10-02)

The loader now matches 1,143 bytes (including its 32-byte jump table) and
55 relocations, with the 55-byte cleanup at 307DF0 and 10-byte handler at
307E27. All functions in unit_21A5E0.cpp are matched.

Restore the ordinary locals to function scope, with the map string kept
inside its branch; use level_at's two existing LEVELS_CHECK expansions.
The image retains one unwritten inline slot at -0xCC before the second
name read's this slot at -0xD0. One existing unused_slot() call inside the
map branch, immediately before look construction, preserves the original
0x118 allocation and all later slots. Its discarded source expression is
not known; the production comment records that limit. Empty no-local
calls cannot supply this slot. Moving the unused local before the map
branch loses the required scope placement.

The historical draft's atol call was also wrong: the image calls 2C6F9B,
the already-identified atoi tail jump. Both localized temporaries use
type_1CB670. No constructor exposure or shared-header change is needed.
With current headers, making the look constructor visible as an inline
actually expands its loop; noinline suppresses the missing slot as well.
Those constructor attempts are superseded by the matching source.

Scratch reproduction: pause_scope_visibility.py, pause_localized_visibility.py,
pause_inclass_visibility.py, pause_missing_slot.py, pause_loader_followup.cpp
in build/tooltmp. The saved blk21bd60 drafts are historical.

## The scoreboard's showing (sub_21FB60, resolved 2026-10-01)

Now matched with all cleanup and EH pieces. The last three wrong result slots
were caused by a member team-count accessor: a free accessor puts them at
0x1E4/0x1E8/0x1FC. It removes eight bytes from the frame; two unused inline
locals after those accesses restore the correct this/temporary slots. Seven
no-code text diagnostics at the end of the same branch preserve the inline
budget that expands the string destructions. Production uses the existing
debug_text/unused_slot helpers. `sub_1C5350` is declared returning type_1CB670;
the HUD caller still matches. Historical blk21fb60 drafts are superseded by
unit_21EB30.cpp. Scratch reproductions: scoreboard_context.py,
scoreboard_scope_context.py, scoreboard_tail_context.py and
scoreboard_debug_context.py under build/tooltmp.

Hint follow-up resolved 2026-10-02: sub_1C5350 now matches. Its missing
unused inline locals belong in a separate final-return scope; see the
resolved entry below. The old localization/constructor trials are superseded.

## RpWorldStreamRead (0x2DAB30) — one scheduling difference left

src/rw/world/babinwor.c has the image's 3.6 version (3.4 header conversion, world arena,
FindBBox for pre-34003). The image pushes `size` for RwStreamRead before the
`worldVersion < 0x34001` branch (shared by both reads) and puts the 3.4 header buffer 4
bytes higher; every shape tried (branch order, block/function-scope buffer, `= {0}`,
memset in the argument) keeps the push inside the branch. Left without a match line.
Follow-up 2026-10-01: tested extracting the entire version-specific read and old-header
conversion into a static inline helper with three parameter orders, each with ordinary
inline and forceinline. All six are worse: 300-347 normalized diff lines versus 107
for the current body. The current diff includes copy scheduling and register changes
downstream of the unhoisted size push; it is not literally a single-instruction diff.
Keep the existing source shape; no helper was added to production.

## Resolved: RwStreamSkip (0x2A7210) — file-branch return context

Now matched: restore the file-branch retVal and single return from Godfather
debug 0xBB6760. Production bastream.c is authoritative; the notes below are historical.

src/rw/src/plcore/bastream.c has the 3.6 version (stream->position kept, fileFuncs seek/eof).
Only the memory case's `lea edx,[ecx+eax]` differs from the image's `[eax+ecx]`; operand
swaps, locals, comparison forms and direct `stream->Type.memory` access did not move it.
Follow-up 2026-10-01: byte comparison confirms the sole code mismatch at +0x87.
Signed-add casts and subtraction-of-negation forms retain it. Updating offset in place
and retaining the memory position in a separate local changes earlier instructions,
as does reusing a separately computed sum for the final store. No match. Reproducible
arithmetic and parameter-update trials: `docs/drafts/rw_matrix_stream_trials.py`
with `RW_TRIAL=stream`; the source is unchanged.

## Rt2dAnimOpen (0x2573B0) — waits on 3.6's Rt2dMessageQueue

src/rw/tool/2danim/gstate.c creates the free lists as the image does, but the image's
Rt2dMessageQueue is 0x408 bytes (a fixed queue) where 3.7.2's is 0x10, and Rt2dMaestro is
4 bytes bigger (an unknown word, provisionally at the end of maestro.h's struct). The queue
code in message.c needs rewriting from the image before this can match.

## The dynamic initializers (0x3096E0-0x30F0F4), 2026-09-30

Every game initializer and exit function is placed except the XDK UIX library's five feature
objects (0x30DB7C-0x30DBD4 and their exits, optimized library code left for the library
placement). The database split `sub_30B4C0` (0x19 bytes, a key's two stores) at 0x30B4D0 into a
bogus `sub_30B4D0`; `config/symbols.txt` and `config/splits.txt` were corrected by hand (the
database itself is unchanged). Globals with no references were named after their addresses:
the keys at 0x4B8B40-0x4B8B48 and 0x4B8EB8-0x4B8EE0 (their values are two-word hashes whose
names are not known), the event id at 0x4B8758 (the database calls it "Id"), the record at
0x4F2940, and three event ids in render.cpp, which take the stock framework's names.

## Resolved: RpCollSectorLineItInit (0x2C2B20), 2026-10-01

Rebuilt from the image as 3.6's (the line clipped against the tree's box
first, `src/rw/plugin/collis/ctquery.h`, `_rpCollLineEndsIntervalTestMacro`).
Every instruction matches except the SSE register numbers: the image keeps
the constants 0 and 1 in xmm3 and xmm4 and the clipped parameters in xmm6
and xmm5, ours 0 and 1 in xmm4 and xmm5 and the parameters in xmm3 and
xmm6. Declaration orders, ternaries, the else branch's order and computing
`hi` first did not move them (scratchpad ivar2.py, ivar3.py).
GeometryForAllTriIntsecLine (0x2C07F0), which inlines the same macro, has
the same renaming and nothing else. Also tried (scratchpad ivperm.py,
paperm.py): all 32 combinations of the interval test's declaration and
assignment orders, and seven shapes of the caller's `pa`/`pb`/`result`
declarations (separate, assigned later, `pb` first, typed constants): none
moves them.

Resolved by computing `(bound - start) * r` inside each direction branch.
For positive r, assign lo from inf then hi from sup; for negative r, assign hi
from inf then lo from sup. Both branches therefore evaluate inf first. Moving
the arithmetic into the branches fixes the SSE allocation; the asymmetric
lo/hi assignment order fixes the three remaining loads. Verified exact matches:
`RpCollSectorLineItInit` (680 bytes, 2 relocations) and its inlined copy in
`GeometryForAllTriIntsecLine` (2316 bytes, 10 relocations). All already annotated
functions in both collision units also pass. The source is in ctquery.h.

## Other RenderWare near misses, 2026-09-30

- `MatrixOrthoNormalize` (0x2A48C0): the second cross product and the in-place
  scale of the normalize load their operands in another order (the image
  stores the scaled x before z). `RwMatrixOrthoNormalize` (0x2A59A0) now matches
  with the existing noinline helper (see rw-differences.md).
  Follow-up 2026-10-01: first byte mismatch is +0x397, in the first cross product.
  Tested 310 variants: all 64 multiply-operand swaps and all 64 per-product RwReal
  cast masks for each cross product; all six scale-store orders with four expression/
  temporary forms; all 24 vector and six pointer declaration orders. No improvement
  over the baseline. The other differences remain the first normalize's x/z scale
  scheduling and the second cross product's loads. Reproducible search:
  `docs/drafts/rw_matrix_stream_trials.py`; source remains unchanged.
- Resolved 2026-09-30: `RpSplineFindPosition` (0x2E2F10) matches with the Xbox asm helper (the interpolation order followed from it).
- `_rpXboxDefaultInstance` (0x2DED60, xbvtxfmt.c): within 6 instructions
  (draft: scratchpad xbvtxfmt_definst_draft.c: the create path first, a
  `vbSize` local, the positions size added directly). The image loads the
  format pointer and adds the positions' size separately on each of the
  inlined `_rpXboxVtxFmtGetSize` paths; ours joins them. If/else, ternary,
  per-branch `size` and uncast forms did not split them.
- `_rxXbDefaultRenderCallback` (0x2E02A0, xbpipe.c): within 4 instructions
  (draft: scratchpad xbpipe_drc_draft.c, the Godfather debug build's shape
  with the TFACTOR branch first and `RwXboxSetCurrentVertexShader(mesh->vertexShader)`).
  Both differences are register scheduling inside the inlined
  `D3DDevice_SetTextureStageState` writes: the image loads `esi = 0x800`
  before the last stage-0 compare and reloads `eax = 1` in the stage-1
  disable path. Local order and scope, compare order, `~tFactor` placement
  and a `textured` local did not change them.
- `rwXBInstanceDataMorphUpdate` (0x2E2080, nodeXBoxAtomicAllInOne.c) and
  its only caller `_rxXBAtomicDefaultReinstanceCallback` (0x2E2380): the
  static takes the geometry in `esi` (the compiler's own register
  convention), so the caller matches only beside it. Within 22 lines
  (draft: scratchpad nodeatomic_draft.c): the single-target path, the
  prelight call and the texture loop load `format`/`vertexData` in another
  order. A texture-set count local fixed the convention; declaration order,
  argument casts, `&vertexData[offset]`, `D3DVertexBuffer_Lock2` and a
  hoisted `numVertices` did not fix the rest.
- `_rpXboxVtxFmtInstBNT` (0x2DDB50, xbvtxfmt.c): within 21 lines (draft:
  scratchpad xbvtxfmt_bnt_draft.c, shaped on 3.7's D3D9
  `_rpD3D9VertexDeclarationInstTangent` without the remapping pass). The
  triangle loop matches; the binormal pass differs: the image multiplies
  the binormal's x term as tangent-first and scales the binormal as
  `length * b`, where the tangent is scaled `t * length`. Explicit cross
  products, pointer locals and `RwV3dScale` did not reproduce both. Rechecked
  2026-09-30 with the Xbox asm helper in place (not the blocker): still
  21 lines. Scalar-first scaling, a local cross product, index forms and a
  split loop did not help; the image multiplies the tangent's z term by
  memory (`mulss xmm1, [n.y]`) where ours reloads the normal first.
  `_rpXboxVtxFmtInstBNTComp` (0x2DE0F0) shares the pass and waits on it.
  Improved 2026-10-01: a local `currentNormal = normal + n` together with an
  explicit final reciprocal-square-root and scalar stores reduces the current-unit
  BNT draft from 51 to 14 normalized diff lines. First actual byte mismatch is
  +0x478: the last cross-product term loads tangent.y before normal.x; the squared
  length then has different SSE registers/scheduling. The end-of-loop scale and
  counter now match. Saved insertion fragment: `docs/drafts/rw_xbvtxfmt_bnt_followup.c`.
  Tried cross-product operand masks, cached normal components, local pointer forms,
  scalar operand order, pre/post increments, and dot-product permutations/casts/
  association (including original macro parentheses). No exact match. BNTComp was
  not reconstructed in this trial; its status is unchanged.
  BNTComp follow-up (2026-10-01): reconstructed the complete function in
  `docs/drafts/rw_xbvtxfmt_bntcomp_draft.c`. Its input normals are RpVertexNormal
  (signed-byte xyz in four-byte records), converted with 1/128, verified at
  0x40B904. The fabs threshold is a double at 0x4193B8 containing the widened
  float 1e-12f, not the nearest double to decimal 1e-12. Current best: 53
  normalized diff lines, first instruction difference 239 in the normalization
  loop; first actual byte difference +0x354 is the forward-branch displacement.
  The triangle accumulation instructions agree after correcting that constant's
  type. Tested six unpack assignment orders, three scaling forms, packed-normal
  pointer local, and explicit first/final normalization. Remaining differences
  concern SSE allocation and scheduling in the final loop. Still binary.
- `_rpSkinXboxGetVertexFormatShader` (0x2D4440, skinxboxformat.c):
  within 82 lines (draft: scratchpad skinxboxformat_draft.c, with its
  register tables, the dummy shader program and the ICF-folded
  `SkinBinaryFindVertexFormat`). The image keeps `desc` in `esi` and copies
  it into `ebx` for the search's register convention, then holds byte 3
  (prelit/weights/BNT) in `bl`; ours keeps `desc` in `ebx` and re-reads
  the byte. Const-ness, a texture-set local, argument order and moving the
  search after the caller did not change it.
  Improved 2026-10-01: preserving the packed prelit/weights/BNT byte across the
  texture-coordinate loop, then extracting weights into a RwUInt32 before its test,
  fixes those registers and flag reloads. Current best matches through +0x22A;
  first byte difference +0x22B is `shl esi,3`. The compiler scales the insertion
  index once, then uses unscaled addresses for the format store, handle output
  pointer, and return handle; the image uses esi*8 at all three accesses.
  Saved complete current-header draft: `docs/drafts/rw_skinxboxformat_followup.c`.
  Cached-field subsets/types, whole-struct copy versus flag-field assignments,
  typed weight locals, index signedness/pointer expressions, memcpy versus aggregate
  store, increment order, and separate insertion-index local were tested. None fixes
  the final scaling. /G5 and /G6 with /O2 or /Ox retain +0x22B; /G7 first differs at
  +0x45 and /O1 at entry. No production flags or sources changed.
  Further 2026-10-01 trials: item packing 1/2/4/8/16, DWORD/RwUInt32/RwInt32 handle
  declarations, and a named HRESULT result all retain the final scaling mismatch.
  Bitwise-complement insertion-index spelling does not match either. The shared
  header and XDK CreateVertexShader declaration were checked against the current
  matching world vertex-format function; no declaration fix was established.
- `_rpSkinXboxRenderCallback` (0x2D4220, skinxboxplain.c; 3.7 keeps it in
  skinxboxrender.h): within 14 lines (draft: scratchpad
  skinxboxplain_draft.c). Only registers differ: the image loads the atomic
  into `eax` after pushing the material and reads the primitive type last;
  ours loads the atomic into `ecx` first. Loop forms, local placement,
  `pass` type and const-ness did not change it. Until it matches,
  skinxboxplain.c reaches it through its plain symbol.
  Follow-up 2026-10-01: pointer-parameter volatility (atomic/header/mesh combinations),
  pre/post pass increments and increments before the draw or in the loop condition
  did not improve the current 18-line normalized diff. Baseline first differing
  instruction remains the material-setup argument scheduling; no source change.
- `XBoxSkinAtomicAllInOneNode` (0x2D46F0, skinplatform.c): within 2 spots
  (draft: scratchpad skinplatform_draft.c). The bone remap read encodes as
  `[esi+eax]` (Godfather's 3.7 build and ours give `[eax+esi]` for every
  source form tried), and after the bone loop the image reloads the header
  before the mesh. Everything else matches, including the 3.6 split-data
  batches and the 16-aligned viewport scale. The node definition reaches it
  through an alias.
  Follow-up 2026-10-01: verified both real differences in current-unit context.
  Explicit pointer-addition/remap-index casts and RwInt32 bone index leave them
  unchanged. Narrower bone types and alternate mesh-loop conditions worsen the
  result. The later mismatch is the order of reloading the header (esp+0x3C)
  and mesh (esp+0x30) at 0x2D4A31, after the batch loop. Draft remains unchanged.
- Resolved 2026-09-30 (matched with the Xbox asm helper; the default instancer indexes the BNT texture set by `numTexCoordSets - 1`). The skin instance callback chain (skinxboxinstance.c): the static
  `InstanceWeightsAndIndices` (0x2D3340) packs the weights with the
  `RwFastRealToUInt32` asm helper (a `cvttss2si` from the stored float), so
  it stays binary; `_rpSkinXboxInstanceCallback` (0x2D37C0) calls it and
  the static `rpSkinXboxDefaultInstance` (0x2D3610) with the compiler's
  register conventions, so both wait on the same answer. A draft of the
  default instancer (the 3.7 shape, no BNT tangent checks) is in scratchpad
  skinxboxinstance_draft.c.
- Resolved 2026-09-30 (`LastVertexShaderDesc = &VertexShaderCache[index];` first, its three stores through it, then `NumShadersInCache++`). `_rpSkinXboxGetShader` (0x2D3180, skinxboxrender.c) with its static
  `BinaryFindVertexShader` (0x2D3110, which matches alone): within 5 lines
  (draft: scratchpad skinxboxrender_draft.c). On a new insert the image
  forms the entry pointer once (`lea ecx, [ecx*4 + VertexShaderCache]`)
  and stores through it; ours keeps `index*12` in `eax` for the byte code
  store. Pointer locals and every store order made it worse.
- Resolved 2026-09-30 (`*radiusBlock++ =` in both radius branches, an if/else for the prelit constants, a `surfProps` pointer in SetMaterialColor). skinxboxrender.c's lights and material colour (draft: scratchpad
  skinxboxrender_draft2.c, with `_rpSkinXboxAmbientLight` static: only this
  file touches it, and FindLights needs the no-alias caching that gives):
  the static `FindLights` (0x2D1D30) is within 15 lines, all stack slots
  (the image shares the directional list end's slot with the point radius
  block, ours with the point count; declaration order and block scoping do
  not move them); `_rpSkinXboxEnumerateLights` (0x2D2130), its only caller,
  is within 2 (the prelight test loads the constants pointer before its
  branch); `_rpSkinXboxSetMaterialColor` (0x2D24F0) is within 4 (the image
  loads the material before the push-buffer space check).
- `_rpSkinXboxMatrixUpdate` (0x2D2230, skinxboxrender.c) with its static
  `D3DMATRIXFromRwMatrix` (0x2D21C0, which matches alone): within 78 lines
  (draft: scratchpad skinxboxrender_draft3.c, block-scoped matrices per
  hierarchy case, which put the three matrices where the image has them).
  The rest is the hierarchy's matrix array and node info taking each
  other's stack slots, and the registers that follow from it.
  Rechecked 2026-09-30: the Godfather debug PDB names the locals
  (`atomicData`, `hierarchy`, `numNodes`, `matrixArray`, `skinToBone`,
  `frameInfo`, `frame`, `ltm`, `inverseLtm`, `iNode`, `srcMat`,
  `prodMatrix`, `result`, `i`, `tempMatrix`) and indexes the constants as
  `&shaderConstants[i * 3]` like D3D9's `_rpD3D9SkinVertexShaderMatrixUpdate`;
  that shape (draft: scratchpad mu_gf.c) is within 75-83. The image packs
  `matrixArray` with `frameInfo` (the local-space branch's `i` one slot
  higher); ours packs it with the first branch's constants pointer.
  Follow-up 2026-10-01: current-unit insertion of draft3 scores 121 normalized diff
  lines and the Godfather-shaped draft 133 (relocation addends and padding contribute
  to these scores). All eight indexed/stepped constants combinations were tried,
  along with separate loop scopes and pre/post increments. Best current-context form:
  indexed constants in the first two branches, stepped constants in the third, 100
  lines. Saved with the matching 100-byte static helper in
  `docs/drafts/rw_skin_matrix_followup.c`. Actual first byte difference +0x1E is
  a branch displacement; the matrix-array spill and later scheduling still differ.
- Resolved 2026-09-30 (RenderWare's own asm, allowed): `RwV3dTransformPoint`/`RwV3dTransformVector` (0x2A3D20/0x2A3DC0) and
  `RwMatrixMultiply` (0x2A58B0) are matched with Xbox overloads of their macros in
  bavector.c/bamatrix.c; the Godfather debug PDB keeps the same SSE blocks verbatim.

- `XboxDMorphAddBlock` (0x2F2860) and `XboxDmorphAtomicInstanceCallback` (0x2F28D0),
  dmorph/xbox/dmorphpipeg.c, 2026-10-01: drafted from the Godfather debug build (port 13340,
  0x11348D0) without its 3.7 asserts (docs/drafts/dmorph_instance_draft.c). The static
  block merger matches byte for byte, but only beside its caller (eax/esi/ebx register
  convention). The callback has every section in place (call offsets within a few bytes;
  the geometry extension holds a pointer, `*RPDMORPHGEOMETRYGETDATA`), but its register
  allocation differs throughout: about 1310 normalized diff lines. Declaration orders,
  local types and `RpGeometryFlag` flags moved it only slightly (tools/session/pscore.py).
  The image keeps zero in `edi` and the geometry in `ebp` from the prologue on.

## The Xbox raster lock (`_rwXbRasterLock`, 0x2AC830), 2026-09-30

Resolved 2026-09-30: matched from the Godfather debug build's structure (ears_godfather_d.xbe): no raster-type local (the texture case re-masks `raster->cType`), `lockFlags |=` updates, the helper takes the (unused) raster first, `lockedRect` and the texture case's width/height are block-scoped, and `XGUnswizzleRect` needs `<xgraphics.h>` (it is `__stdcall`). The note below is kept for the record.

Drafted from the image with its helper `XbRasterLockMipLevel` (0x2AC7E0,
register arguments: the extension on the stack, the level in dl, the D3D
flags in ecx, the bits and pitch outputs in edi and esi); the draft is
scratchpad xb/lock_draft_best.c. Its logic and block order match (cases in
the order normal, texture, camera, default; the raster type kept in a local);
134 diff lines remain, all register choices: the image keeps the flags in edi
and the raster's cType in ecx, re-masking it in the texture case. Tried: the
type unmasked (byte or dword), the flags initialised at their declaration, the
flags chosen by if/else or a ternary, the mip level masked. Not in the tree
(no parked code); `src/rw/driver/xbox/xbdevice.h` keeps the device globals it
needs.

## The Xbox image format finders (`XbImageFindFormat` 0x2B89D0, `_rwXbImageFindRasterFormat` 0x2B8AC0), 2026-09-30

Resolved 2026-09-30: matched in the Godfather debug build's shape: the palettised branch first, block-scoped locals per branch (`width`, `height`, `cpIn`, `rpPal`, `y`, `cpInCur`, `x`; `rpInCur` for 32-bit images), one `format` local set by if/else before each return, and the mipmap flags ORed into the texture format before the shift. The note below is kept for the record.

Drafted (scratchpad xbc/fr2_full_draft.c): `_rwXbImageFindRasterFormat` is
within 23 instructions (it calls `XbImageFindFormat` with the image in ecx,
ours passes it in edx, and one `shr` is scheduled differently);
`XbImageFindFormat` differs in register allocation throughout (the image
keeps the palettised loop's pixel pointer and column counter apart and spills
the row counter and depth). Not in the tree (no parked code).

## Question: RenderWare's Xbox `RwFastRealToUInt32` is inline asm (2026-09-30)

Resolved 2026-09-30: answered ("If a Renderware function originally used __asm, that is acceptable. Do not invent __asm that did not exist in Renderware."). include/rw/sdk/rwplcore.h carries the helper under `_XBOX` as the Godfather PDB shows it; `InstanceWeightsAndIndices`, `rpSkinXboxDefaultInstance` and `_rpSkinXboxInstanceCallback` are matched with it. The note below is kept for the record.

Godfather's debug build keeps `RwFastRealToUInt32Inline` as a function
(0xB78AE0): `push ebp; mov ebp, esp; cvttss2si eax, [ebp+x]; pop ebp; ret`,
an `__asm cvttss2si eax, x` body returning in eax. Inlined in release it is the
image's `movss [mem], xmm; cvttss2si eax, [mem]`, which no intrinsic form
reproduces. It is RenderWare's own header code (3.6's Xbox ostypes.h, the
counterpart of the Win32 FLD/FISTP `RwFastRealToUInt32Inline`), not ours.
Under the no-`__asm` rule every function that uses it stays binary:
`RpSplineFindPosition` and most of the Xbox vertex format instancers
(`_rpXboxVtxFmtInstV3d` and its relatives in xbvtxfmt.c, which also carry
MMX `movntq` copy loops like `_rwXbIm2DRenderIndexedPrimitive`). May the Xbox
headers carry this one asm helper, as the original did?

## Small RenderWare near misses, 2026-09-30

- `RwStreamSkip` (0x2A7210, bastream.c): one instruction. The memory case's
  `position + offset` is `lea edx, [eax + ecx]` in the image (offset as the
  base) and `[ecx + eax]` in ours for every operand order, cast, local and
  store form tried. It is the same base/index swap as
  `XBoxSkinAtomicAllInOneNode`'s `[esi+eax]`.
- Resolved 2026-09-30 (VC7.0). `_rtFSManagerFOpenOnFS` (0x257EB0, rtfsmgr.c): within 2 lines with the
  loop as `for (; index < ...)` (the declaration's `index = 0` live). The
  image pushes `ebx` in the prologue, as that does, but zeroes it after
  entering the critical section, as the tree's `for (index = 0; ...)` does
  (which shrink-wraps the push instead).
- Resolved 2026-09-30 (VC7.0, both matched). The RtFS toolkit (rtfsmgr.c, rtfsyst.c) may come from another compiler
  build. It is the only RenderWare code padded with `nop` rather than `int3`.
  Its functions also push every callee-saved register in the prologue:
  `_rtFSInit` (0x258240, 3.6 shape in rtfsyst.c, 14 lines off) and
  `_rtFSManagerFOpenOnFS` push before the first call or early return, where
  VC7.1 3077 delays the pushes past them. No /O, /G, /Z or /Gy variant
  changes it. If VC7.0 (13.00.9466) can be obtained, try these two with it.

## RenderWare Audio near misses (VC7.0 codegen?), 2026-09-30

- `sub_23C490` (0x23C490, the wave dictionary file load), retried under
  VC7.0 with static module globals: 51 lines off (draft: scratchpad
  rwa_23C490_draft.c). The frame is now 0x1C, with the read buffer moved to
  a `newBuffer` block local, `params` in its own block and the saved list
  as separate `next`/`prev`. The remaining differences are the saved
  fields' stack slots (the image puts `unk04` in the dead `buffer` slot and
  `unk00` lowest) and an `eax` temporary in `dict = buffer + unk0C`.
  Declaration order and block scope do not change VC7.0's slot choice.
  The dictionary destroy (0x23CAA0) and `sub_23C970` match: the destroy
  releases an unused wave twice when no dictionary is loaded.
- The voice manager's priority update `sub_23E980` (a static taking `ecx`),
  60 lines off under VC7.0 (draft: build/tooltmp/vm_full.c). The image
  loads each position component from the sound and `fsubr`s the listener's,
  squares in y, x, z order, and keeps the constant 1 in `ebx` for its flag
  tests. VC7.0 13.00.9466 gives the same x87 sequence for every sum order,
  sign form, struct or pointer temporary and `*=` form tried, and no
  /O1, /Os, /Ox, /G5, /G7, /Op or /Ob2 build is closer (tools/flagtry.py).
  It may be another VC7.0 build. Its callers `sub_23EE70` and
  `SoundStopper_Transition`, and `sub_23E8E0`, match but wait for it, since
  the statics share its translation unit. The min/max distances are copied
  as integers (`RwUInt32` locals), and the near case is
  `if (distance < min) volume = 1`.
- rwaobj.c `sub_23F0D0` / `sub_23F140` are resolved (2026-10-02):
  112 bytes each, including NOP fill. The fallback is the incoming object
  pointer, and qualified parameter reads preserve the two reloads. The
  original qualifiers remain unknown; callback pointer returns are supported
  by RwaObjExecuteFunc and the installed callback definitions. See below.
- rwaobject.c's parameter dispatchers `Behavior_DispatchCallback`
  (0x23F8B0, set) and `sub_23F8E0` (get): 10 and 4 lines off (draft:
  scratchpad rwa_object_dispatch_draft.c). The image loads the instance
  before the data argument (the set keeps the data in `edi`), where VC7.0
  pushes the data first. Struct-pointer, table-index and local-copy forms
  do not change the order.
- The stream object (src/rwa/unit_23FAD0.c): `sub_23FC00` (the unlink
  callback, 8 lines off) and `sub_23FEE0` (the position query, 2 lines
  off; draft: scratchpad rwa_stream_draft.c). The first decrements the
  stream count before loading `hSemaphore` where VC7.0 loads both first
  (volatile and non-static forms tried). The second's unsigned-to-float
  temporary goes to the `out` parameter's slot in the image and the
  `stream` slot here.
- rwastreamsourceobj.c `sub_241230` (the node creation callback that fills
  the play queue's items): 13 lines off (draft: scratchpad
  rwa_streamsource_draft.c). The image keeps the item count and the item
  array in the dead `failed` and `obj` parameter slots; VC7.0 gives the
  array a new stack slot and the count the `obj` slot. Declaration and
  assignment orders do not change this.
- src/rwa/unit_241F90.c's byte-swapping copy `sub_241FD0` (7 lines off) and
  vector length `sub_242050` (9; draft: scratchpad rwa_util_draft.c). The
  copy's 32-bit swap builds `((v << 16) | (v & 0xFF00)) << 8` with `v` in
  `edi`, and the 16-bit swap loads `src[1]` with `movzx dx` before
  `mov dh, src[0]`. VC7.0 picks the other register, and every operand
  order compiles alike. The length squares y, then x (reusing y's x87
  slot), then z (spilled to the parameter slot): the same order as the
  voice manager's `sub_23E980`, so it may be one macro neither reproduces.
- src/rwa/unit_2422B0.c: `sub_242570` is resolved (2026-10-02): the
  reference header declares RwaWaveDefUploadBusyFunc with no arguments.
  Correcting the shared callback type and calling busy() matches all 32
  bytes, including NOP padding. Upload `sub_242810` is also resolved:
  assign a separate uploadOffset local in both branches before the common
  callback call. This restores the no-conversion path's load order and
  matches 256 bytes / 11 relocations. Both old wave drafts are superseded.
- src/rwa/unit_243670.c's allocation and release are resolved (2026-10-02):
  243670 is 304 bytes / one relocation; 2437A0 is 224 bytes / one relocation.
  The old allocation draft omitted its alignment helper and incorrectly reused
  hint for the remaining count. The image keeps hint at esp+1C and reuses the
  freeList argument home at esp+18 for a separate checkEntries local. Restore
  the alignment inline, use heap[i] for the bitmap read and OR store, and put
  the entry-found test after both bitmap branches. That common test retains
  the out-of-line full-byte path. No compiler flags changed (core VC7.0).
  Repros: rwa_alloc_pointer_trials.py, rwa_alloc_alignment_trials.py,
  rwa_alloc_exit_trials.py (flexit_05 exact). Release uses the same named
  bitmap pointer for clearing and summing. All seven annotations match.
- src/rwa/unit_243AE0.c's three parked functions are resolved (2026-10-02):
  243BC0 compatibility (272 bytes / two relocations), 243E20 definition
  create (128 / seven), and 243FF0 instance create (560 / four). Allocation
  inlines recover branch placement; separate counters and qualified table
  pointer reads recover the remaining address encodings. Original qualifier
  forms are unknown and documented in source. All 12 annotations match.
- More RW Audio near misses from 2026-10-01, with drafts in the scratchpad.
  - The pool chunk allocation `sub_2442D0` (63, rwa_pool_draft.c): the image
    keeps the alignment in `ebp` and the needed size in `ebx`, where VC7.0
    swaps them.
  - Symbol-table add/remove `244650`/`244690` are resolved: both return
    RwaSymbolTable *, not void. Both are placed in rwasymboltable.c and
    config/compiled.txt. The old rwa_symtab_draft.c and symbol trial mode
    are superseded and must not be used with current declarations.
  - The timer's elapsed ticks `sub_244980` (11, rwa_timer_draft.c): the
    image computes the wrap as `0xFFFFFFFF - start + now` (`or -1; sub;
    add`). VC7.0 folds it to `now - start - 1` in every 32- and 64-bit form.
  - The time stamp reads `sub_244930` and `sub_244940` are `__asm rdtsc`:
    original assembly, matched since the owner's 2026-10-01 rule.
- The listener (src/rwa/unit_23CC10.c): its up and at setters (0x23D2A0,
  0x23D320) rebuild `right` as a cross product, and its set-up (0x23CC70)
  copies zero and unit vectors through a stack temporary. The image's x87
  operand order differs between the two setters for the same products, and
  the set-up reloads the temporary's components. VC7.1 orders the products
  the same way whatever the source order, casts or parentheses, and drops
  the temporary. These are more VC7.0 codegen cases. Drafts: scratchpad
  rwa_listener_orient_draft.c.
- rwaobjdef.c: the definition tree search `sub_23D970`, the parameter-table
  release `sub_23DAA0` (a static taking `ebx`), `sub_23DB30` (a static taking
  `eax`) and the definition destroy `sub_23DB90` are written (draft:
  scratchpad rwa_objdef_draft.c). The image hands the statics their
  argument in other registers and schedules the searched definition's
  store and reload differently. More VC7.0 register allocation.
- `sub_23DCA0` (0x23DCA0, find a definition by UUID) compiles to the same
  instructions, but the image encodes `mov [esp], ecx` as `89 4C 24 00`
  (an explicit zero displacement, as VC7.0's code generator does) where
  VC7.1 emits `89 0C 24`. A one-byte encoding difference no source change
  reaches.
- `_rwaObjDefSetupParams` (0x23DD00), `sub_23DE20`, `sub_23DF00` and the
  definition create `sub_23DFB0`: the image keeps the parameter counts in
  `bp` and the definition in `esi`/`ebx` where VC7.1 re-reads the stack.
  The create also needs the static `sub_23DB30`. Drafts: scratchpad
  rwa_objdef_draft.c.
- rwabase.c `sub_23E1C0` (0x23E1C0, the RenderWare engine start-up) and
  rwaobjdef.c `sub_23E0C0` (the module open): the first has the image's
  `lea ecx, [esp + 0]` zero-displacement encoding; the second schedules an
  `add esp` before a store. VC7.0 again (drafts: scratchpad
  rwa_base_draft.c, rwa_objdef_draft.c).

- The Xbox output destroy `sub_24E710` (0x24E710, VC7.1): after clearing the
  listener it stores zero into a 12-byte frame that nothing reads, then calls
  `sub_24DF00`. VC7.1 drops such stores for every plain, array, union, init,
  memset, loop, inline by-value/pointer, struct-return or dead-read form
  tried; a `volatile` array keeps them but schedules the first store before
  the call's `add esp`. Draft: scratchpad rwa_out_710_draft.c.

- The Xbox voice update `sub_250340` (0x250340, VC7.1): after calling the
  voice's own getters `sub_24F190`/`sub_24F160` (min/max distance) and
  `sub_24F0B0`/`sub_24F110` (position/velocity into a local), the image
  reloads the flags and `state.output`; our VC7.1 keeps them in registers
  because it knows those same-file getters write only the local. Declaring
  any of them extern (unknown) makes the image's reloads appear. Was the
  update calling identical copies in another object (folded by /OPT:ICF)?
  The wave set `sub_24F410` is a register-allocation near miss. Drafts:
  scratchpad rwa_voice_draft.c.

## Resolved 2026-09-30: a VC7.0 compiler for RenderWare Audio (and RtFS)

The owner supplied XDK 4627's VC7.0 13.00.9466 (docs/toolchain.md); both libraries now build with it, and `_rtFSInit`/`_rtFSManagerFOpenOnFS` match. The question as asked:

PLAN.md M6 says: if the codegen proves VC7.0 (13.00.9466), that compiler
has to be obtained. RenderWare Audio now shows it:
- functions padded with `nop` rather than `int3`;
- `[esp]` operands encoded with an explicit zero displacement
  (`89 4C 24 00`, `8D 4C 24 00`), which VC7.1 never emits;
- callee-saved pushes never delayed;
- products ordered and `add esp` scheduled in ways no source form gets
  from VC7.1.

About half of the library's non-trivial functions so far differ only in
these ways. Everything VC7.1 can match is matched; the rest are drafted and
listed above. If a VC7.0 (Visual Studio .NET 2002 / XDK compiler 13.00.9466)
`cl.exe`/`c1.dll`/`c2.dll` is available, placing it under `C:\XDK` (or
pointing me at it) would let these match. I won't download it myself.
- rwabase.c: the module open helper `sub_23E240` (a static whose open
  callback the image passes in `ebx`; VC7.1 puts the count there instead),
  hence `RwaCoreOpen` (0x23E510), and `sub_23E680` (`*total += amount`, the
  loads in the other order) are drafted in scratchpad rwa_base_draft.c.
- binkds.cpp `Open` (0x345E40) restored in C++ (2026-10-02):
  identical 642 bytes / 21 relocations; all 17 unit annotations match. An
  explicit if/else for the initial byte count fixes the old zero-EBP lifetime
  mismatch. Initialize wBitsPerSample before nSamplesPerSec to avoid the
  extra EAX clear. All original stores remain and no qualifiers were added.
- binkread.c: `BinkOpen`, `BinkWait`, `BinkSetSoundOnOff`, `BinkDoFrame` and
  `BinkNextFrame` are `__declspec(naked)` transcriptions for now (drafted by
  tools/img2asm.py; the C drafts are in the session notes). The C near misses:
  BinkOpen (sound-track loop base/index order, the 8-bit conversion test),
  BinkWait (`t - big_sound_skip_adj - start` operand order), BinkDoFrame
  (stack slots of an inlined mult64anddiv), BinkSetSoundOnOff (the
  SetOnOff-failed block placed after the epilogue, the loop not aligned).
  BinkNextFrame matches in C only beside a C BinkSetSoundOnOff (VC uses the
  callee's body), so it is transcribed with it. The statics only the
  transcriptions call (bpopmalloc, dosilence, high1secrate, GotoFrame) stay
  binary; the transcriptions call statics through `_binkread_*` aliases, and
  inittimer is `__declspec(noinline)` while BinkWait is transcribed.
- Bink assembly transcriptions (2026-10-01, owner: "asm the rest of bink"): the Bink
  functions not matched in C are MASM units drafted by tools/img2masm.py from the image
  (`src/bink/*_asm.asm`; exact bytes, symbols only for address fields). First:
  `expand_asm.asm` (13 functions), then binkread_asm (4), binkacd_asm (7), yuv_asm (18),
  dct_asm (5) and bitplane_asm (3). Their data references use `_unk_XXXXXX` address names,
  which only the placement linker resolves; naming those data objects is M5's work. The C near misses there: `simpmergesort` keeps the merge
  flags in `eax` and the count in `ebx` where the image swaps them (every loop form and
  declaration order tried); `ReadHuffTable` differs in the final fill loop's registers and the
  tail merging of the depth paths' last `VarBitsUse`.
- Bink's unmatched C binarized (2026-10-04, owner: "unmatched Bink may be binarized"): the
  C drafts of simpmergesort, CheckReadHuff4PairBundle, setevenodd and YUV_blit are gone, so a
  real link no longer carries them beside their transcriptions. Their callers that depend on
  their register conventions went binary with them (expand_asm: ReadHuffTable, ExpandPlane,
  ExpandBink; yuv_asm: YUV_blit_mask, the six YUV_blit_* entry points, and checkzoombufs and
  setdbls, which only setevenodd calls). ReadHuffTable and YUV_blit_mask are cdecl, so their C
  callers (StartReadHuff8Bundle, the masked entry points) stay C.
- wintimer.c `RADTimerRead` (0x344990) restored in C (2026-10-02):
  identical 276 bytes / 28 relocations with the existing VC7.1 flags. Keep
  `diff = time - lasttime` and a scoped `elapsed = rad - lastrad`; test
  `abs(diff - elapsed)` before assigning `diff -= elapsed` in the correction
  branch. This preserves the original two differences without inline assembly.
- popmal.c `pushmalloc` (0x258B20) is a `__declspec(naked)` transcription for
  now: in C, `(pushtot / 32 - amount / 32 + 1) & 31` gets `esi` and `edi`
  swapped against the image under every operand order, shift/divide form and
  temporary tried. Its `__asm` names the statics through `_popmal_*` aliases
  (naming the statics directly changes `popmalloc`'s code).
- RW 2D near misses (2026-10-01): `Flatten2d` (tool/2d/path.c, 0x2530C0) differs only in
  the second inlined `SubPathLineto2d`'s miter dot product: the image multiplies the y
  terms first (4 bytes); every operand order and argument order of `RwV2dDotProduct`
  compiles alike. Follow-up 2026-10-01: tested direct depth condition, early return,
  a separate flatness local, and separated decrement; none changes the mismatch.
  Tested 80 explicit dot-product variants (sum order, multiply operand order,
  per-product RwReal casts, separate reciprocal, product locals and declaration order).
  Best normalized diff decreases from 8 to 5 lines, but uses a memory-source multiply
  plus movaps instead of the image's separate load and register multiply. This shortens
  the body by one byte and first fails byte comparison at +0x1C8 (branch displacement),
  versus +0x308 for the original form. No exact match; source remains unchanged.
  For scratch compilation, put src/rw/tool/2d FIRST on the include path
  (`PSCORE_INC=C:/codfh-match/src/rw/tool/2d`): otherwise the wrong rpplugin.h is found
  and rwID_2DPLUGIN/rwID_2DPATH are undefined. `DefaultPathStroke2d` (stroke.c, 0x256E30; frame 0x48 against 0x68)
  and `rt2dFontShowBitmap` (font.c, 0x255230; 0x48 against 0x98) keep fewer locals than
  the 3.7.2 source: 3.6 restructured them.
- src/rwa/unit_2FD5D0.c's bitmap create `sub_2FD5D0` and allocation `sub_2FD880`
  (draft: scratchpad rwa_bitmap_draft.c). Both compile to the image's instructions with
  registers rotated: the create keeps the rounded size in `ebp` and the bitmap in `esi`
  (VC7.0 swaps them), the allocation keeps the byte index in `edx`, the run in `esi` and the
  bit in `eax` (VC7.0: `esi`, `eax`, `edx`). Declaration orders, types, loop forms
  (for, while, do-while), a copied bitmap argument and a single rounded variable all compile
  alike.
- RW Audio ADPCM recovery (2026-10-01): `sub_24C560`, `sub_24C620`, and `sub_24C700`
  match independently (mono decode/encode and stereo decode). `sub_24C840` and `sub_24C880`
  match with the interrupted `sub_24C8C0` draft present, but disappear when that caller is
  removed. External linkage changes their register calling conventions at byte zero, so
  these dispatchers stay binary with their caller. Saved all three in
  `docs/drafts/rwa_24C8C0_draft.c`; the caller first differs at +0xA (register versus stack
  result initialization) and has further slot, register, and loop-scheduling differences.
- src/rwa/unit_249490.c's sample converters (2026-10-01; docs/drafts/rwa_adpcm_draft.c): the size helpers
  `sub_249BF0`/`sub_249C90` match; the IMA ADPCM encoder `sub_24BD30` is down to its step and difference
  registers swapped (the sample through a widened local fixes the load order); the decoder, the block
  decoder (now matched as `sub_24C560`), the DSP decoder `sub_24B260` (index scaling and the first coefficient's register), the XA-style block decoder `sub_24BC50` (the older history and the second coefficient
  stay in registers in the image) and the channel conversion `sub_249D00` differ in register assignment.
- src/rwa/unit_249490.c's PCM converter `sub_24A260` and its caller `sub_24A740` (2026-10-01;
  docs/drafts/rwa_pcm_draft.c): the converter needs a return in each 8/16-bit case (the image
  repeats the epilogue; one shared return lengthens the branches and moves the loop padding) and
  then differs only in the last loop's address operand order (`[esi+edi]` against `[edi+esi]`;
  casts, pointer locals, a new counter, named constants and the other loops' forms leave it). The
  caller keeps `to` and the destination in ebx/ebp swapped and its result where the image keeps
  the saved destination (declaration orders do not change VC7.0 C slots).
- src/rwa/unit_2FDB00.c's update `sub_2FE290` (2026-10-01, body in the unit): the image keeps the
  entry index in `ebx` (reloading the object from its stack slot, including where an underrun takes
  the object itself as the entry) and constants as immediates; this build keeps the object in `ebx`
  and caches 2 and 3 there. Its status blocks (the 7 case laid out first, an inverted test) and the
  shared silence assignment (a goto) are in place; register assignment is left.
- src/rwa/unit_2452A0.c: resolved 2026-10-01 for `sub_246AD0` (a `failed` flag tested at the end;
  units.md) and the handlers it blocked. Still open there: `sub_2457A0`, `sub_246240`, `sub_246500`,
  `sub_246D70`, `sub_246ED0` (register assignment).

## Resolved: default Xbox render callback (2026-10-01)

`_rxXbDefaultRenderCallback` (0x2E02A0) now matches: 1240 bytes, 116 relocations.
The two texture-stage scheduling differences disappear when the existing
`_rwXbTextureStageForce` operation is expressed as a typed forceinline function
with DWORD stage/value and D3DTEXTURESTAGESTATETYPE type. Added the documented
`_rwXbTextureStageForceInline` variant in xbcache.h and used it in this callback.
The body and state-update order are the same as the macro. Local cached/value
temporaries and inverted comparison variants also matched, so the minimal
typed helper was chosen. Full unit comparison and source audit pass.

Default-instance follow-up (0x2DED60): six alternative source bodies for the
inlined `_rpXboxVtxFmtGetSize` were tested (else return, inverted condition,
ternary, result local, switch, parameter reuse). None reproduces the separate
position-size exits. Position-format locals and explicit branch/switch forms
also did not improve the existing 15-line normalized diff. Kept its draft.


## Resolved: Xbox atomic morph update (2026-10-01)

`rwXBInstanceDataMorphUpdate` (0x2E2080) now matches 612 bytes and 13
relocations; its caller `_rxXBAtomicDefaultReinstanceCallback` (0x2E2380)
matches 82 bytes and 2 relocations alongside it. The current-header baseline
had 30 normalized diff lines. A `const RwV3d *verts = morphTarget->verts`
local in the single-target branch fixes that branch (10 lines remaining).
A `const RwRGBA *color = geometry->preLitLum` local immediately before
prelight instancing fixes both the prelight call and subsequent texture-loop
format load. Typed call wrappers, count/stride/destination locals and texture
format expression variants did not improve the result. Both functions are
placed together so the static helper's compiler register convention is kept.


## Resolved: Xbox skin render callback (2026-10-01)

`_rpSkinXboxRenderCallback` (0x2D4220) matches 125 bytes and four relocations.
A block-local `const RpMaterial *material = mesh->material` immediately
before `_rpSkinXboxPlainMaterialSetUp` fixes the atomic argument's delayed
load into eax and the following draw-call register allocation. A typed
inline setup wrapper also matches, but the source-pointer local is simpler.
The source uses `rpSkinXboxRenderCallback`, retaining the binary symbol's
single leading underscore and the existing pipeline callback reference.


## Resolved: world stream reader (2026-10-01)

`RpWorldStreamRead` (0x2DAB30) matches 1423 bytes and 52 relocations.
A block-local `void *readBuffer = &w34000` before the old-header memset,
used as the subsequent RwStreamRead destination, makes the compiler hoist
the common size push before the version branch and allocate the original
header-buffer slot. A local readSize initialized before the memset also
matches, but the buffer-pointer version is used. Narrow typed wrappers
around either or both reads retain the baseline's 107 normalized diff
lines; no wrapper was added.

Skin-node follow-up (0x2D46F0): source/remap/material/flag locals, typed
inline remap or color-call wrappers, pointer-to-integer index expressions,
and parameter order changes leave the baseline unchanged. It remains
parked with the indexed-load base/index order and mesh-pointer reload
placement differences. The draft is still `rw_skinplatform_draft.c`.


## Resolved: Flatten2d (2026-10-01)

`Flatten2d` (0x2530C0) matches 1130 bytes and 12 relocations. The second
SubPathLineto2d expansion uses the documented `SubPathLineto2dInline`
variant of the existing macro. Typed path/point arguments plus a
`const RwV2d *normal` local for the previous node's normal reproduce the
miter dot product's load and multiply order. The first expansion retains
the macro: changing both calls or the shared macro changes other registers.
A pointer-argument dot-product forceinline also matches; the local normal
pointer avoids that extra helper. Ordinary __inline does not force expansion
and fails to match. The unit's existing annotations and source audit pass.

Default-instance follow-up (0x2DED60): position source/destination locals,
a shared size local followed by one buffer increment, per-branch size
locals, and typed instancing-call wrappers did not improve the 15-line
baseline. The compiler still merges the packed and unpacked position-size
exits. Kept `rw_xbvtxfmt_definst_draft.c` as the current draft.


## RW inline follow-up: BNT, compressed BNT, stream skip (2026-10-01)

Reproducible substitutions: `docs/drafts/rw_inline_followup_trials.py`.
No production changes; the current drafts remain the best candidates.

- BNT (0x2DDB50): typed cross-product helpers in both parameter orders,
  pointer-based dot helpers, and explicit cross terms do not improve the
  14-line baseline. Last-term scalar/pointer multiply helpers also retain
  it. Replacing the cached normal pointer with normal+n worsens scheduling.
- BNTComp (0x2DE0F0): typed unpack helpers in either parameter order retain
  53 normalized lines. A current-normal pointer increases this to 72;
  moving unpacking before tangent normalization introduces earlier register
  changes (144 or more). Keep unpacking after tangent normalization.
- RwStreamSkip (0x2A7210): typed sum helpers in both parameter orders,
  local position/offset/size values, and shared use of the sum helper do
  not fix the lea base/index order. Caching position for both the test and
  store instead changes additional registers. Baseline score is 18 because
  the ranking includes jump-table disassembly; this is still the known
  single real instruction mismatch.


## Delta-morph callback scope follow-up (2026-10-01)

Revalidated `dmorph_instance_draft.c` in the current unit: 1312 normalized
diff lines, first differing instruction 6. Typed atomic/geometry extension
accessors and initialization/nested-if forms leave it unchanged. Cached
initial-loop inputs can reduce the score to 1279 but introduce an earlier
first mismatch (instruction 2), so that shape was not retained.

Exhaustively tested the 255 nonempty subsets of separate local counters
for its eight i-indexed loops. Best score is 1261, still first instruction 6.
The retained minimal variant scopes counters in position, prelight and
texcoord deformation loops (mask 104). Saved the full candidate as
`docs/drafts/dmorph_instance_followup.c` and reproducible scope search as
`docs/drafts/dmorph_scope_trials.py`. This remains a register-allocation
near reconstruction, not a match; no production function was placed.
Exact comparison confirms the first callback byte difference at +0x1B.
`XboxDMorphAddBlock` still matches all 109 bytes with zero relocations
when compiled beside this candidate; it cannot be placed independently
without preserving that calling context.


## Resolved: Xbox skin matrix update (2026-10-01)

`_rpSkinXboxMatrixUpdate` (0x2D2230) matches 701 bytes and 16 relocations;
`D3DMATRIXFromRwMatrix` (0x2D21C0) matches 100 bytes without relocations
when compiled beside it. Starting from the 100-line follow-up draft:

- Cache the atomic frame before initialization/inversion: 90 lines.
- Cache the first branch's per-bone frame before its matrix call: 72 lines.
- Initialize the third branch's loop counter before matrix initialization:
  66 lines; index shaderConstants[i * 3] in all three branches: 14 lines.
- Give the first bone loop a separate local counter: exact byte match.
  This puts the matrix-array and second-loop counter into the original
  stack slots. Remaining score artifacts are relocation addends/padding.

Removed the now-unused stepped constants locals; exact comparison still
passes. The full unit's existing matched functions are checked as well.


## RW scope/accessor follow-up (2026-10-01)

Saved reproducible substitutions in `docs/drafts/rw_scope_accessor_trials.py`.
Production sources are unchanged; current parked drafts remain best.

- Skin pipeline node (0x2D46F0): a separate mesh-loop counter, separated
  initialization of bone/batch counters, and combinations do not fix either
  real mismatch. Separating the bone initialization moves a byte load and
  adds another difference; keep the original declaration initializer.
- MatrixOrthoNormalize (0x2A48C0): typed cross-product inlines in all six
  argument orders, on either or both calls, retain the 21-line baseline.
  Local input-pointer copies do not improve it.
- Skin vertex-format selector (0x2D4440): typed format-store, handle-address,
  and handle-return inlines, alone and in all combinations, retain the same
  68-line score and final index-scaling discrepancy. Existing packed-flags
  follow-up draft remains the best source.


## BNT expression-context follow-up (2026-10-01)

`docs/drafts/rw_bnt_expression_trials.py` preserves further rejected
variants against the current 14-line draft. Reversing multiply operands
in all 64 combinations while retaining the exact cross macro's parentheses
has no effect. Explicitly rewriting the arithmetic instead worsens code
allocation. Local normal.x/tangent.y/last-product temporaries in the final
cross component do not improve the result. A typed inline containing the
entire final basis calculation retains 14 lines in every parameter order;
an inline containing only cross-plus-binormal-normalization worsens it.
The compiler rejects __restrict with C4235, so it is not a supported path.
No production source or compiler flags changed; keep the existing draft.


## Default instancer and voice-copy follow-up (2026-10-01)

RW `_rpXboxDefaultInstance` (0x2DED60): per-branch format-pointer locals,
a separate format pointer for the remaining attributes, lock-mask locals,
and typed skip helpers returning buffer + size leave the 15-line baseline
unchanged. Explicit packed/unpacked branching inside the helper is worse.
No source changes were kept.

Resolved follow-up: `updateVoiceSubSystem` now matches (1,962 bytes,
14 relocations). `voice_mask_copy(const type_1DDE20_mask &)` checks its
source and returns it by value into `set_voice_peers`' argument slot.
Returning a reference retains the old mismatch; the value-returning form
reproduces the construction order. The shared constructor remains unchanged.
The constructor sweeps below are historical, superseded by production source.

Game `updateVoiceSubSystem` (0x1AA380): current headers reproduce its
six-line ranking (the two real differences are the copy destination lea
and its spill; other score lines are relocations). The old note claiming
two constructor checks fix it is not reproduced in this context: two
`if (!unk_00)` checks score 25 lines and first byte-differ at +0x26B.
Swept 0..3 constructor checks against 0..4 pre-call checks and combinations
of destination/source-member checks. None improves the baseline; source
member checks additionally change the frame. Production mask/accessor
headers were not edited, and no change to the matched sender is needed.
The standalone overlay test is `docs/drafts/voice_copy_followup_trials.py`.


## Resolved: RWA ADPCM converter and dispatchers (2026-10-01)

`sub_24C8C0` (0x24C8C0) now matches 896 bytes including padding and 11
relocations; `sub_24C840` and `sub_24C880` match 64 bytes each including
padding and two relocations each. All three compile together in unit_249490.

The baseline had 178 normalized differing lines. A shared result-return
label fixes result allocation and the prologue (107 lines). Declare the
source pointer before the destination in both split and merge loops and
advance the merge source before its destination (38 lines). Finally,
advance the destination parameter once before memset and pass that pointer
to the decoder: exact match. A volatile result was rejected because it
introduced reads absent from the original; production uses ordinary storage.


## RWA channel and IMA scalar converters: follow-up (2026-10-01)

Reproducible variants: `docs/drafts/rwa_converter_followup_trials.py`.
No production changes; existing reconstruction drafts remain parked.

- sub_249D00: baseline 170 normalized lines. A widened bitDepth local
  scores 156 but leaves the first real register mismatch unchanged.
  Cached channel/flag fields, shared exits, destination advancement and
  all 63 nonempty subsets of separate loop counters do not resolve the
  broad register allocation. No candidate is close enough to place.
- sub_24BD30: baseline 36 lines, mainly exchanged step/difference registers.
  Declaration-order permutations, cached predictor/index inputs, widened
  code and 25 equivalent predictor-expression orderings do not improve it.
- sub_24BDE0: baseline 55 lines. Separate step/value locals and signedness
  variants retain the baseline; no exact match.


## RWA allocation/list current-context follow-up (2026-10-01)

Reproduction: `docs/drafts/rwa_allocation_followup_trials.py`. No matches
or production changes. The historical scores used a different compilation
context; these are the current complete-unit baselines.

- Pool allocator 2442D0: 77 lines. Typed insertion helpers, initializer
  separation and return pointer casts do not improve it; negated-alignment
  form scores 78.
- Bitmap create 2FD5D0: 127 lines. Computing numBytes before shift scores
  87 but still differs at entry. Reusing the rounded local for its byte
  count scores 105 and fixes the first two instructions. VC7.0/VC7.1,
  O2 and the Xbox Og/Oi/Ot/Oy/Gs profile all still fail at entry with the
  baseline source. No production flags were changed.
- Symbol add 244650: 30 lines. A local head pointer scores 20; typed link
  initialization/insertion helpers and partial link-pointer substitutions
  do not match the image's table/type register assignment and write order.


## RWA stream-cache completion resolved (2026-10-01)

`sub_244B40` and static `sub_244AF0` match in unit_2449C0.c (640 and
80 bytes including padding, 36 and 3 relocations). The baseline handler
had one real register difference at the final ReleaseSemaphore: ECX vs
EAX for hHandle. Locals, typed inline wrappers, loop/return forms and
queue scopes did not fix it. Route the earlier release-and-return through
the final unlock label; VC7.0 then emits both original release sites and
selects EAX at the final site. No assembly or compiler flag changes.


## RWA remaining stream-cache clients follow-up (2026-10-01)

Reproduction: `docs/drafts/rwa_streamcache_*_trials.py`, using the shared
`rwa_streamcache_clients.py` loader. No remaining client was placed.
`rwa_streamcache_clients_followup.c` keeps the best tested caller form.

- sub_2449C0 matches (32 bytes) when emitted with sub_245060; keep the
  static helper with its caller until the bundle matches.
- sub_245060: 35 normalized lines initially. Reordering sub_244FA0's
  formal/call arguments to status, client, event, file, bytes reduces
  this to 8, including padding artifacts. The real remaining difference
  is ECX versus EDX for the mode decrement chain; all call setup matches.
  All 120 argument permutations and six switch-case orders tested.
- sub_244FA0: 18 normalized lines. Real differences remain in the final
  three zero stores and callback register sequence. Argument permutations,
  error-label layouts and a scoped header pointer do not resolve them.
- sub_2450C0: initialization/FOpen scheduling still differs. Typed forceinline
  initialization helpers (24 argument orders) and pointer-return helpers
  do not resolve the early callback/data loads and delayed argument pushes.


## RWA stream callback follow-up (2026-10-01)

The stream-cache dispatch caller `sub_245060` now matches (96 bytes,
2 relocations) with static `sub_2449C0` (32 bytes). The latter's formal
and call order is file, client, bytes, status, event. Combined with the
previous sub_244FA0 argument order, this fixes the mode register too.
Reproduction: `rwa_streamcache_smallparams.py`, candidate cp_024. The
updated `rwa_streamcache_clients_followup.c` preserves this result.
The bundle cannot yet be placed: the compiler needs the static
sub_244FA0 body to emit its private register calling convention, and
that body remains unmatched. Additional final-callback locals, zero-loop
forms, forceinline cleanup and branch-layout trials do not improve its
18-line baseline. A `position != -1` probe changes semantics for other
negative results and is explicitly not a placement candidate.

Stream-source creation `sub_241230` also remains parked. Reproduction:
`rwa_streamsource_*trials.py`. Current full-unit baseline is 22 normalized
lines, including an extra stack slot at entry. A scoped queue-callback
pointer fixes the callback.data base register (21). Declaration/load
permutations reach 17 but retain the extra slot. Success-path scopes,
explicit failure return, parameter count reuse and decrementing pointer
loops do not match. No production source or flags changed.


## RWA core startup/open resolved (2026-10-01)

`sub_23E1C0` now matches with the current VC7.0 toolchain (96 bytes,
7 relocations). `sub_23E240` matches (112 bytes): the old draft incorrectly
broke before incrementing i when the user open callback failed. The image
increments i first, then jumps to shared failure cleanup, so the just-opened
module is closed. Failed module.open jumps there without incrementing.
This source correction also gives the original private register ABI.
`RwaCoreOpen` matches (96 bytes, 10 relocations) with the success statements
inside `if (sub_23E240(...) == TRUE)` and FALSE returned at the end.


## RWA wave current-context follow-up (2026-10-01)

Resolved 2026-10-02: upload `sub_242810` matches 256 bytes / 11 relocations.
Declare uploadOffset inside the upload branch without initializing it, then
assign it in both the conversion and no-conversion paths. The prior local
copy probe initialized it before the format comparison, leaving the wrong
reload order. No qualifiers or compiler changes are required. Current
reproduction: rwa_upload_current_trials.py, upcur_01; earlier
rwa_wave_*trials.py results are historical.
Busy query `sub_242570` is now resolved (2026-10-02). The earlier probes
used the wrong callback signature: docs/reference/rwacore_ps2.h:2066
declares RwaWaveDefUploadBusyFunc(void). The corrected callback and no-arg
call reproduce the exact tail jump, with no compiler or qualifier change.
The extra-store probes are experiments, not proposed production changes.
No wave source or flags changed.


## RWA object-definition current-header follow-up (2026-10-01)

`rwaParamTables.inputs/outputs` are now rwaParamDef pointers. The historical
`rwa_objdef_draft.c` used byte-pointer arithmetic: adding count * 0x18 now
incorrectly advances by count * 576. Current-context trial loaders correct
this to typed pointer addition (and remove byte-pointer assignment casts
from SetupParams). Do not transplant the old draft unedited.

Reproduction: `docs/drafts/rwa_objdef_*trials.py`; best release bundle is
`rwa_objdef_release_followup.c`. No production changes.

- 23D970 search: 41 normalized lines. Cached list head, separate root/local
  definition and conditional initialization retain stack-home/reload differences.
- 23DAA0 release: use a 16-bit count test, then a 32-bit decrementing loop
  over typed 24-byte parameters. Best ol_3 is 24 lines; table/input loads
  still move below the test and the final free/clear registers differ.
  Typed forceinline helpers, argument orders and reverse-index loops do not
  resolve this. The corrected body gives static 23DB30 an exact match
  (96 bytes, 8 relocations), but its release dependency remains unmatched.
  Destroy 23DB90 also remains unmatched at its prologue.
- SetupParams 23DD00: corrected baseline 114 lines. Sharing NULL exits at a
  failed label reaches 86; separate loop counters and cached 16-bit counts
  do not resolve the register/frame differences. Wider counters score worse.


## RWA stream position query resolved (2026-10-01)

23FEE0 now matches (240 bytes, 9 relocations). Adapt the old draft to the
current rwaStreamQuery and marker name/uuid fields, then copy the query
parameter into a local `rwaStreamQuery *out = query`. This moves the rate
conversion temporary from the stream parameter slot to the query slot,
matching the image without any extra instructions. Rate locals and typed
inline getter/division helpers did not change the baseline slot choice.


## RWA numeric utility follow-up (2026-10-01)

Reproduction: `rwa_util_*trials.py`. No utility source changes. Byte swap
241FD0 retains its register/byte-load differences under factored 32-bit
expressions and 16-bit local, reversed-OR and union forms. Vector length
242050 baseline is 23 normalized lines; cached input ordering and typed
square helpers reach 21, but x87 lifetimes and the missing z spill remain.
Sequenced accumulator forms do not resolve them. These normalized counts
include neighboring padding and table-relocation artifacts.


## RWA parameter getter dispatcher resolved (2026-10-01)

`sub_23F8E0` now matches (48 bytes, no relocations). Copy getter->param,
a 16-bit field, into a RwUInt32 local before calling the getter. This
loads and widens the parameter number before loading data, matching the
image. A 16-bit local, copied access record and inline call wrappers
retain or worsen the differences. Production includes only the matched getter.

Setter `Behavior_DispatchCallback` remains parked: it lacks the image's
EDI save/data load and loads index too early. Equivalent table, handle,
data and widened-number locals do not match. Reproduction is in
`rwa_dispatch_*trials.py`; the loader excludes the now-placed getter
before appending trial definitions.

Stream unlink `sub_23FC00` also remains parked (33 normalized lines,
including neighbor/padding artifacts). Local stream/count pointers,
prefix decrement and typed inline decrement/lock wrappers retain the
semaphore-load ordering difference. Trial changes to global storage
and volatility do not match and were not applied to production.
The original caller passes an unused second argument to sub_245E90;
the trial prototype preserves that observed call ABI.


## RWA object-update fallback corrected (2026-10-01; resolved 2026-10-02)

Both execute walks now match 112 bytes / no relocations (101 code bytes
plus 11 NOP bytes). RwaObjExecuteFunc in the reference header and the
installed callback definitions establish pointer returns; shared unk2C/unk30
fields and registration casts now agree. Status is also an object pointer.
Qualifying the incoming pointer parameter and copying it into an ordinary
local preserves the fallback reloads from its argument home. Individual
qualified fallback reads also match. This establishes the access pattern,
not the original qualifier spelling; source comments state that limit.
A pointer status alone retains the 14-line mismatch, and reusing the
parameter as the mutable status worsens it to 37 lines. No flags changed.

The core wrappers had misattributed the pushed zero to sub_23F2F0. That
function is the no-argument top-level getter (its body and reference
RwaObjGetTopLevelObject prototype agree); zero is the enclosing execute
call's second argument. Correct prototypes and nested calls retain both
wrapper matches. All 20 rwaobj annotations and all 42 annotations in the
two directly corrected caller units match. Production supersedes both
old execute drafts. Reproduction: rwa_objexec_{reload,typed,param_status}
trials; oet_02 is the typed matching form.

Historical investigation:

The old 23F0D0/23F140 draft and near-miss explanation misidentified a
stack argument. After the three callee-saved pushes, [esp+0x10] is obj;
ok is [esp+0x14]. The original loads obj at 23F0F2/23F0FE (and at
23F162/23F16E), so the callback-absent/default status is the object
pointer, not the flag. This is a semantic correction, not a request
to suppress compiler propagation of a known zero.

`rwa_obj_exec_followup.c` preserves the corrected draft with an explicit
(RwBool)obj fallback and if(!ok) branch order. It remains unmatched:
VC7.0 uses the cached ESI object instead of reloading its parameter home;
branch/loop alignment also differs. Current corrected score is 14
normalized lines versus 20 for the old first draft. Separate pointer
locals, pointer-typed status and typed inline dispatch helpers do not
resolve it; early status initialization is worse (31). Reproduction:
`rwa_objexec_*trials.py`. No production changes.


## RWA interface current-context follow-up (2026-10-01; resolved 2026-10-02)

All three functions now pass exact checks; production unit_243AE0.c supersedes
the old rwa_iface_followup.c bundle. Compatibility 243BC0 is 272 bytes / two
relocations; instance create 243FF0 is 560 bytes / four relocations (both
sizes include NOP fill). Definition creator details are below.

The instance allocation/flag-selection inline reduces 45 normalized lines
to a single differing encoding byte at +0x18E. A separate RwUInt16 output
counter together with a qualified def->outputs read resolves it. Either
change alone moves differences to the table UUID/handler accesses. The
compatibility input pass needs the analogous combination: separate RwUInt32
counter and qualified def->inputs read. Original qualifiers are unknown;
source comments identify these as representations of observed operands.
No shared types or compiler flags changed. All 12 annotations match together.

UUID pointer arithmetic/casts, plain cached array pointers, comparison and
getter inlines, and qualified table-side reads did not match. Successful
reproducers: rwa_iface_instance_counter_access_trials.py (iicacc_01) and
rwa_iface_compat_access_trials.py (ica_06), with pscore.py and the respective
underscored C symbols/addresses in src/rwa/unit_243AE0.c. The saved allocator,
UUID, index, access and pointer probes record intermediate attempts.

Historical attempts:

- Compatibility 243BC0: current baseline 2 normalized lines, one real
  base/index encoding difference at +0x54. Separate output counters and
  cached UUID expressions do not fix it; cached UUID forms worsen register
  allocation. Signed inner-loop counter does not change the baseline.
- Definition create 243E20 is resolved (2026-10-02): 128 bytes including
  seven NOP bytes, seven relocations. Put allocation and flag selection in
  a pointer-returning inline, then test its result before the common
  initializer. This reproduces the original out-of-line existing-definition
  path after the normal return. Nested/duplicated initialization and switch
  forms do not match; the allocation inline is sufficient without qualifiers
  or compiler changes. All ten existing/new annotations match. Reproduce:
  rwa_iface_create_inline_trials.py, ifin_00, _sub_243E20, 243E20,
  src/rwa/unit_243AE0.c. The old creator draft is superseded.
- Instance create 243FF0: baseline 284 lines. RwUInt16 for both count and
  i fixes the prologue and most loops (51). Loading count before n and
  storing link.next before link.prev reaches 45. Separate output counters
  are worse. Explicit trailing allocation labels and shared early failure
  returns do not improve the 45-line candidate. Main remaining differences
  are the fallback allocation block/epilogue placement and one address
  base/index encoding. Counts include neighbor/padding artifacts; no exact
  match is claimed.


## RWA source chunk acquire resolved (2026-10-01)

247C50 matches (432 bytes, 5 relocations). Reorder the look-ahead branch
before normal regions; in that branch test state flag 0x2000 positively
before its region checks. Failure paths release the semaphore and return
NULL directly. These changes reduce 110 normalized lines to 4. Qualify
the two region flag reads through volatile region pointers: this preserves
their ordering before the state flag tests, with no added instructions,
and resolves the last differences. This does not establish that the
original declaration used volatile; it reproduces the observed reads.

Other source-reader trials remain parked: 247F20 baseline 89 lines,
reordering marker/info loads and using a pretested track loop reaches 75.
Changing high/count declaration order has no effect. 247E00 retains its
unsigned-divide scheduling and register differences in the current draft.
Node dispatchers 247220/247260 do not respond to widened parameter-number
locals as 23F8E0 did; the argument-load differences remain.


## RWA source chunk release resolved (2026-10-01)

247E00 matches (288 bytes including padding). Replace the early semaphore
release/return and the normal-path release with a shared unlock label at
function end. VC7.0 then emits the original separate release sites and
matches the previously different div setup, item-count registers and
look-ahead flag store. No volatile qualification or extra offset local
is needed. The full current source unit passes individual byte checks.


## RWA source track-position helper resolved (2026-10-01)

248360 matches (80 bytes, 2 relocations). Replace the old draft's
sub_2420D0 outputs into cast addresses of state/track parameters with
block-local RwUInt32 high and low variables; return high + base. The
compiler reuses the same stack homes but selects the original LEA
base/index order. Reversing operands, compound assignment, signed base
and pointer-add expressions alone did not fix the old draft.


## RWA source seek fallback draft corrected (2026-10-01)

247FE0 remains parked. The historical draft wrote the high multiply result
into position, then computed skip = position - track. The image preserves
the original position in EBX and subtracts the low result: 24801F is
`sub ebx,[esp+0x2c]`. Keep input position intact and use ordinary high/low
result locals. The corrected arithmetic is skip = position - low;
track then retains that initial skip for the following track-alignment loop.

Best current draft: `rwa_source_seek_followup.c`; reproduction:
`rwa_source_seek_*trials.py`. Current baseline is 165 normalized lines;
corrected high/low locals give 141. A shared unlock/result exit reduces
this to 125. Reordering multiplication operands and volatile-qualified
track-step reads do not improve it. Unsigned positive loop tests change
branch encodings but do not fix stack homes or the extra frame space.
No production code or compiler flags changed.


## RWA node dispatchers resolved (2026-10-01)

247220 and 247260 match (48 bytes each, no relocations). The inferred void
return type prevented a widened parameter-number local from reproducing
argument-load order. Returning the callback's RwBool value and storing its
16-bit parameter number in a RwUInt32 local gives both original bodies.
Returning a value alone retains the old mismatch. The image leaves the
callback result in EAX; this source signature preserves that result. All
existing unit functions still pass. The two local extern declarations now
agree with the definitions; callers that ignore the value are unchanged.

Stream-cache header 244FA0 revisit: volatile-qualified header/holder/data
accesses and chained zero assignments do not improve the 18-line baseline;
qualifying callback access worsens it. No stream-cache production change.


## RWA stream-description fix-up follow-up (2026-10-01)

24D670 remains parked. Current baseline: 111 normalized lines. Exhaustive
outer-loop counter-scope subsets reach 95 (mask 16, separate counter for
the cue UUID loop). Use a pointer to the track's format field instead of
a pointer to its enclosing track in the format loop; this reaches 67.
Best draft: `rwa_fixup_followup.c`. Reproduction: `rwa_fixup_*trials.py`.

The remaining differences include computing a marker address after loading
its name, exchanged inner/outer counter stack homes, and final track-loop
registers. Separate inner counters, counter declaration-order/signedness
changes and volatile marker-name reads do not improve the best candidate.
No production source or compiler flags changed.

The stream-cache header callback was also probed for a missing scalar
return. Returning explicit zero/status does not match and does not explain
the image's callback-result register; no signature change was retained.


## Xbox streamed-wave follow-up (2026-10-01; resolved 2026-10-02)

Both functions now pass exact checks: 24DBA0 is 182 bytes / 12 relocations,
and 24DAD0 is 58 bytes / three relocations. Copying a volatile-qualified
incoming wave pointer into an ordinary local forces its observed early
read, fixing the ESI/EDI lifetimes without changing flags or shared types.
The earlier qualified length reads remain. The original declaration forms
are not established; source comments distinguish that from the byte match.
All 18 annotations in unit_24DA70.c match. Production supersedes the draft;
reproduction is rwa_nv_live_pointer_trials.py, variant nvl_02.

Historical attempts:

Current draft 24DAD0 matches (58 bytes, 3 relocations) when emitted beside
24DBA0. Creator baseline is 34 normalized lines. Volatile-qualified reads
of wave->deviceFormat.length preserve the original reload after writing
unk48 and reduce the diff to 16. This establishes matching read behavior,
not the original source qualifier. Best bundle: `rwa_nv_followup.c`.

Remaining real differences are the prologue and initial memory setup:
the image keeps wave in ESI and memory in EDI, while the compiler reuses
ESI for memory and loads wave only after setup. Parameter-copy locals,
shared failure exits and typed inline memory initialization (including a
wave-returning form) do not resolve this. Counts include relocation and
padding artifacts; no creator match or production change is claimed.
Reproduction: `rwa_nv_*trials.py`.

### RWA splitter constructor follow-up (2026-10-01; resolved 24CFF0)

Constructor 24CFF0 matches 448 bytes / six relocations. A cached callback-array
pointer reduces duplicate address calculations; a typed force-inline allocator
wrapper evaluates the size before loading allocator fields. A volatile-qualified
tracks-pointer access preserves the original store address encoding. This is
compiler-output evidence, not proof of an original volatile declaration.
Trials: `build/tooltmp/splitter_{allocation,helper,index,final}_trials.py`.

Read 24CD50 remains two normalized lines apart: EAX is cleared after the
failure epilogue pops instead of before. Shared exits, result locals and
explicit success returns did not fix it. Status 24CC80 remains parked.

### RWA splitter tails and setter follow-up (2026-10-01; still parked)

With constructor 24CFF0 placed, rechecked the remaining splitter functions.
Status 24CC80: all 128 combinations of qualified status stores retain the
same instruction flow. A shared mode==1 label changes tail sharing (34
normalized lines versus 44 baseline, with jump-table artifacts), but loses
the original case-7 compare/store sequence. Typed inline case-7 wrappers,
switch spelling and condition reordering do not match.

Read 24CD50: typed failure helpers and 32 return-label/local variants do
not fix the EAX clear scheduled after the epilogue pops. Baseline remains
two normalized lines; joining both failure edges worsens allocation.

Setter 23F8B0: tested all six argument orders for typed call wrappers,
both boolean and handle returns, widened parameter locals and qualifier
combinations. No match: EDI save/data load is still missing and index is
loaded early. Baseline score 16 includes following-function artifacts;
this is not a regression in production. No unmatched bodies were placed.

Reproduce using `docs/drafts/rwa_splitter_{status,control,status_helper,
read_helper,return}_trials.py` and `rwa_dispatch_set_{helpers,qualifiers}.py`
with `tools/session/pscore.py`; each script loads the current production
unit. The full-image gate from constructor placement remains the last
production verification; this follow-up changes only notes/trial scripts.

### RWA symbol table mutations (2026-10-01; resolved)

Both sub_244650 and sub_244690 now match, 64 bytes each, no relocations.
The parked draft incorrectly declared them void. The reference header
`docs/reference/rwacore_ps2.h` lines 2702/2707 declares both mutations as
returning RwaSymbolTable*. Returning table also agrees with the EAX value
at each original return and fixes all register allocation differences.
The existing list operations need no reshaping. Caller declarations in
rwaparam.c now agree. Earlier local-pointer and inline-helper investigations
were based on the incorrect return type and are superseded.

### Core allocation cursor callback (2026-10-01; resolved 23E680)

sub_23E680 now matches all 16 bytes, no relocations. The old draft treated
it as a void accumulator. Original EAX preserves the previous cursor;
23E727 installs the function in handle parameters, 23F9F0 forwards it to
243FF0, and 244073-244082 calls it and initializes the returned storage.
The recovered signature is void *(RwUInt32 amount, void *data), with data
pointing to a byte cursor. Return the old pointer after advancing it.

Also rechecked free-list release 2437A0: the reference header confirms
void, and the draft differs only at three base/index address encodings.
64 byte-access/qualifier variants and eight typed access-wrapper variants
did not improve the six normalized diff lines. Resolved 2026-10-02: name
block->bitmap as heap before clearing the bit, then reuse heap in the sum
loop. The RenderWare bamemory.c free routine supports this pointer shape;
RWA retains its own void return and list/free policy. No qualifier or compiler
flag changes. See rwa_freelist_release_current_trials.py for the 6/2/0 progression.

### RWA source creation callback follow-up (2026-10-01; parked)

241230 improves from 22 to two normalized diff lines. Preserve the object
in a local and reuse its argument home for the items pointer; cache the
queue callback address. Load positions/count before assigning that reused
argument. This removes the extra stack allocation and reproduces the
original stores before the loop. Best: `rwa_streamsource_followup.c`.

Only the final reload order differs: the image reloads EAX (items) before
EDI (count); the compiler reloads EDI first. Typed queue-call wrappers,
argument order, qualified accesses and counter scopes do not resolve it.
Reproduce with `rwa_source_param{,_qualifier,_order}_trials.py` and
`rwa_source_queue_trials.py`. No production placement is claimed.

Pool allocation 2442D0 also rechecked: moving insertion outside the search
loop (shared labels) and typed search helpers do not match. Best remains
76/77 normalized lines, with register allocation differences throughout.
Trials: `rwa_pool_{cursor,exit,search}_trials.py`.

### RWA source loop and timer follow-up (2026-10-01; parked)

Source callback 241230: moving its item loop into typed force-inline helpers
(returning either the saved items pointer or count) retains the two-line
EAX/EDI reload-order difference. Countdown pointer loops worsen the diff
to 12-16 lines. The saved streamsource_followup draft remains best.
Reproduction: `rwa_source_loop_trials.py`, `rwa_source_loop_pointer_trials.py`.

Timer 244980: updated the old draft's start reference to the current
qword_507178 symbol, truncating it to 32 bits before widening as the original
load requires. Baseline is 23 normalized diff lines, including padding.
Typed subtraction helpers, operand ordering and width variants do not
recover the original OR -1 / SUB / ADD sequence. A trial 64-bit return
reduces the score to 21 but still differs and has no supporting signature
evidence; it is not accepted. Production remains unchanged.
Reproduction: `rwa_timer_wrap_trials.py`, `rwa_timer_return_trials.py`.

### RW skip and RWA command follow-up (2026-10-01; parked)

RwStreamSkip 2A7210: byte-pointer addition/address forms, widened integer
sums and signed forms all retain the sole real LEA base/index mismatch.
Qualified memory/argument reads introduce further differences. The baseline
18 normalized lines include jump-table/padding artifacts, not 18 code
errors. Trials: `rw_skip_{qualifier,pointer}_trials.py`.

RWA command setter 246ED0: baseline 84 normalized lines. Explicit integer
copy of the float bits scores 76; parameter-home reuse worsens allocation.
All 120 local declaration permutations, with the track sign check expressed
as a bit test, score at least 80. No exact match, no production edits.
Trials: `rwa_container_command{,_order}_trials.py`.

### RWA source pump and helper (2026-10-01; resolved)

sub_2475D0 matches 144 bytes / four relocations beside its caller, and
sub_248410 matches 272 bytes / three relocations. The old pump draft
cached the second look-ahead index calculation. Qualifying only the
state->unk174 access used for entries[index].unk0C preserves the original
reload at 2484AC and resolves the 47-line normalized diff. This establishes
observed access behavior, not an original volatile declaration. Static
helper keeps the original EAX parameter convention in the combined unit.

RW default instancer 2DED60 rechecked: qualified position-format reads
and position-size locals retain the 15-line diff; volatile size locals
worsen it. No RW production changes. Source-pump reproduction lives in
`rwa_source_pump_trials.py` and `rwa_source_pump_qualifier_trials.py`.

### RWA source read loop (2026-10-01; parked 248520)

Current-header baseline is 137 normalized lines. Invert the free-space
branch and marker-change branch to the original ordering; separate the
last-index decrement; process the empty-source seek/continue path before
the chunk-reading block. Best falls to 103 lines, saved as
`rwa_source_read_followup.c`. This is not an exact match.

Remaining differences include EBX saved at entry instead of at 248688,
merged/reordered semaphore-release exits, address-load order in the region
loop, and last-index arithmetic. Moving chunk work outside the loop with
a label, qualifier on the region-array read, result signedness, and local
initialization order do not resolve them. The second read failure correctly
keeps the first read's bytes for region updates; the original only returns
immediately on first-read failure. No production source changed.
Reproduce with `rwa_source_read{,_control,_outer,_split}_trials.py`.

### RWA source wrap count (2026-10-01; parked 247F20)

Current-header baseline is 89 normalized lines. Moving the marker load
before the info load and guarding the loop with noTracks > 0 (sharing the
final return) reduces this to 65. A typed force-inline arithmetic helper
reduces it to 61; saved in `rwa_source_wrap_followup.c`.

Still differs in register allocation and stack homes: the original keeps
result/largest/track in EBX/ESI/EBP and spills the chunk pointer; the compiler
keeps chunk in EDI and spills the track counter. The original also retains
an otherwise unused LEA of the marker-size element. Pointer-element forms,
array-index loop forms, declaration permutations and register hints do not
resolve these differences. No exact match or production placement.
Reproduce with `rwa_source_wrap{,_shape,_register,_helper,_array}_trials.py`.

### RWA source setup (2026-10-01; parked 249160)

Current-header baseline is seven normalized lines. A single-case switch
on params->values[5] reproduces MOV/DEC instead of CMP. Qualifying the
buffer-pointer store prevents its movement past the first index clears.
Together these leave two normalized lines, saved in
`rwa_source_setup_followup.c`.

The only real remaining difference is the params->values[10] load, which
the image performs before clearing the ring indexes. A cached local or
typed ring-initialization helper gets that load right but shifts register
choices through the rest of the routine (46 lines). Moving the bufferSize
assignment itself earlier only moves the mismatch to the store. Position,
qualification and existing-local reuse variants do not match. No production
placement. Reproduction: `rwa_source_setup*_trials.py`.

### RWA cache callback follow-up (2026-10-01; parked 248810)

Current-header callback baseline is 619 normalized lines. Reorder the
flag-0x10 branch to handle status==4 and notify/close/return first, with
successful registration afterward, matching the original block order.
Qualifying the region flag update preserves its load/OR/store sequence.
Together these reduce the diff to 535; draft in
`rwa_source_callback_followup.c`. No exact match is claimed. Remaining
work includes status register allocation, zero hoisting, initialization
and callback argument scheduling across the large state machine.
Reproduce with `rwa_source_callback{,_shape}_trials.py`.

Source setup 249160 remains a two-line near miss. Scoping the bufferSize
local through either its store or the ring initialization and qualifying
the following noEntries access retain the 46-line register shift. Reusing
the state/params argument homes is worse (70-89 lines). Reproduce with
`rwa_source_setup_scope_trials.py` and `rwa_source_setup_argument_trials.py`.
No production changes in this pass.

### RWA command entry initialization (2026-10-01; resolved 246D70)

sub_246D70 matches 256 bytes, no relocations. Direct repeated field
assignments let VC7 group channel stores and swap the info/offset registers
(54 normalized lines). Four calls to a typed force-inline entry initializer
preserve the original store grouping and resolve all differences. Every
argument-order permutation tested matches; no volatile access is needed.
Parameter-home reuse and loop-counter scope did not fix the baseline.
Full source-unit comparison is required because the inline is added to an
existing unit containing other matched functions.

### Typed helper follow-up after entry initializer match (2026-10-01)

The helper grouping that matched 246D70 does not resolve neighboring
value setter 246ED0. Tested all six argument orders for a three-argument
store helper, store order and integer bit-copy variants, then a whole
per-entry range-check helper in four argument orders. Best remains the
84-line baseline in this context; no production change.

Source creation callback 241230 retains its two-line final reload-order
difference with all 120 argument orders of a typed per-item initializer.
Using void, byte or queue-item pointer types for the reused third argument
also retains it. The saved streamsource_followup draft remains best.
Reproduction: `rwa_container_set_{helper,range}_trials.py` and
`rwa_source_item_{helper,type}_trials.py`.

### RWA IMA encoder follow-up (2026-10-01; parked 24BD30)

Current-header baseline remains 36 normalized lines, primarily the step
and difference registers exchanged (original ECX/EDX), with predictor
branch ordering also different. The sample already widens through a local.
Tested every valid ordering of step/sample/difference/code initializers;
typed predictor helpers in all six scalar argument orders, returning a
value or writing through the predictor pointer; and 16 explicit arithmetic
assignment forms. None improves the baseline. No production changes.
Reproduction: `rwa_adpcm_encoder{,_order,_helper,_predict}_trials.py`.

### RWA IMA sample decoder (2026-10-01; resolved 24BDE0)

sub_24BDE0 matches 128 bytes / two relocations. Update *predicted directly
in the sign branches, then load it for the sample clamp. For the index,
compute and store value, then compare *index rather than the old value
local. This reproduces the original ECX sum / EAX copy and all other bytes.
No signature change, helper or volatile qualifier is needed. Baseline was
55 normalized lines; direct predictor updates reduced it to 11 before the
index tests resolved it. A four-line normalized remainder is only table
relocation formatting: match.py verifies exact bytes.

### IMA encoder follow-up after decoder match (2026-10-01; parked)

24BD30 improves from 36 to 30 normalized lines by reversing the predictor
branch (positive-code case first). Best saved as
`rwa_adpcm_encoder_followup.c`. The step/difference register swap remains.
Unlike the decoder, cached-versus-pointer clamp tests and explicit index
value locals do not fix it. Unsigned intermediate storage with signed
comparison/shift casts and a typed quantization helper with step/difference
output pointers also fail to improve the new baseline. No production edits.
Reproduce: `rwa_adpcm_encoder_{poststore,signedness,quantizer}_trials.py`.

### RWA PCM follow-up (2026-10-01; parked 24A260/24A740)

24A260 still differs in the single SIB byte at +0x3A6: compiled 0x3E
([esi+edi]), original 0x37 ([edi+esi]). match.py confirms the mismatch.
Equivalent address expressions, volatile source loads, typed load helpers
in both argument orders, and per-element conversion helpers in all six
argument orders do not fix it. A signed loop counter leaves the same
difference; narrow or volatile counters worsen the output.

24A740 improves from 58 to 54 normalized diff lines by evaluating
sub_249BF0 into a size local before sub_2421C0. This restores call/push
ordering. Saved in rwa_pcm_caller_followup.c; destination/to registers and
result/saved-destination stack homes remain different (first byte +4).
Moving initializations, reusing the from parameter for the temporary
buffer, and retaining dest with a separate working pointer worsen output.
No production changes; both functions remain binary. Reproduce with
`rwa_pcm_{load,caller,element,schedule}_trials.py` using pscore.py against
`src/rwa/unit_249490.c` (load/element target 24A260, caller/schedule 24A740).

### RW tangent/binormal load-order follow-up (2026-10-01; parked 2DDB50)

Recompiled rw_xbvtxfmt_bnt_followup.c with current headers: still 14
normalized diff lines, first actual byte mismatch +0x478. Tested all 64
component-access qualifier masks in the final cross product, with the
original dot product and an explicit y/x/z sum. None improves baseline.
Then limited the qualifiers to the final cross-product term, preserving
the exact dot-product macro parentheses while testing all six component
orders (96 variants). Still 14 at best. Plain expanded sums were worse
(65 lines), so preserve the original macro expression tree in later probes.
These qualifiers are experiments, not evidence of original volatile types.
Reproduction: rwa-independent `rw_bnt_load_trials.py` and
`rw_bnt_lastmacro_trials.py` with pscore.py; function/source are in their
headers. No production edits. Incremental full-image gate passed before
these scratch-only trials.

## Resolved: Xbox skin vertex-format shader (2026-10-01)

`_rpSkinXboxGetVertexFormatShader` at 0x2D4440 now matches in
`src/rw/plugin/skin2/xbox/skinxboxformat.c`: 688 bytes, 42 relocations
(including 63 bytes of jump-table/padding data). Packed flag caching and
the widened weight local retain the earlier near-match improvements.
A typed forceinline containing the final format store, shader creation,
and handle return keeps the insertion index unscaled in ESI, matching
the three original scaled addresses. All six helper argument orders
matched those instructions; including the count increment also worked.
The helper is explicitly a local reconstruction, not a recovered symbol.

The skin texture-register table at 0x418FD4 is named unk_418FD4 here to
avoid resolving its local reference name to the distinct world table at
0x41939C. The existing create/destroy functions remain byte-identical.

### RW skin atomic node inline follow-up (2026-10-01; parked 2D46F0)

After matching the skin format shader, tested the same inline-boundary
approach on the node. Current-header baseline remains 16 normalized lines;
real differences are the remap load [eax+esi] versus [esi+eax] at +0x303
and the ESI mesh reload preceding the EDI header reload near +0x341.
The other normalized differences are relocation/padding artifacts.

Per-bone upload helpers and whole-run helpers (all six argument orders)
leave the baseline unchanged. A whole batch helper (24 orders) worsens it
to 39. Material/alpha-state helpers with mesh/header inputs retain 16;
passing material or vertexAlpha separately worsens it to 48/56. Qualified
remap pointer/data accesses substantially change register allocation (231),
and qualifying vertexAlpha alone changes neither real mismatch. The skin
node remains binary; no production edits. Reproduction is now durable in
`rw_skin_node_{trials,batch_trials,material_trials,access_trials}.py`.

### RW default-instance position-block follow-up (2026-10-01; parked 2DED60)

Current-header baseline remains 15 normalized lines. Original position
skip retains separate packed/unpacked exits and different fmt reloads
at 2DEE61/2DEE6E; the compiled code merges these paths. A forceinline
covering the whole position block was tested with 12 cyclic/reversed
argument orders and three pointer-return shapes (36 candidates). All
worsen the baseline; best is 63. A pointer-output version of the same
block, with the same 12 orders, retains 15 and the original mismatch.
No production edits. Reproduction: `rw_default_instance_trials.py`,
`rw_default_position_block_trials.py`, and
`rw_default_position_write_trials.py` in docs/drafts.

### RW stream skip branch follow-up (2026-10-01; parked 2A7210)

Current baseline still differs in the LEA SIB byte at +0x87: original
[eax+ecx], compiled [ecx+eax]. A typed inline covering the entire memory
branch, taking stream/offset in either order or adding the memory pointer
in all six orders, retains this mismatch. Explicit failure labels also
retain it. Success-first control flow is worse; reversed comparison
operands change CMP/JBE to CMP/JAE without fixing LEA. No production
edits. Reproduce with `rw_stream_memory_{block,flow}_trials.py`.
The 18-line normalized baseline includes decoded jump-table artifacts.

## Resolved: MatrixOrthoNormalize (2026-10-01)

`MatrixOrthoNormalize` at 0x2A48C0 now matches in
`src/rw/src/plcore/bamatrix.c`: 1,468 bytes, four relocations.
The 21-line baseline had cross-product operand-load differences and
first-axis normalization store scheduling differences. Local variants of
the existing vector macros preserve explicit reads: first cross product
reads a.y and b.x/y/z; first scale reads a.x; second cross product reads
a.z/a.x in the y expression and a.x in the z expression. These qualifiers
encode observed loads, not a claim about original volatile declarations.
The arithmetic and original reciprocal-square-root macro are unchanged.
Whole-unit byte comparisons pass, including the public wrapper.

Typed combined basis helpers alone retained 21 lines. Component-read
trials reduced this to 17, then four, then exact by restricting the second
cross-product reads to the individual expressions. No new assembly.

### RW BNT component-read follow-up after matrix match (2026-10-01)

The successful MatrixOrthoNormalize approach does not directly resolve
2DDB50. Tested 256 combinations of final cross-product term reads and
dot-product component reads, retaining the macro parentheses and both
x/y sum orders. Then tested 512 per-expression cross-product read masks
(first two component expressions independently, with the final normal.x
read either qualified or unchanged). Best remains 14 normalized lines.
No production edits; the existing BNT follow-up draft remains best.
Reproduce using `rw_bnt_{dotread,eachread}_trials.py`. Qualifiers are only
code-generation probes, not recovered source-type evidence.

### RW compressed BNT normalization follow-up (2026-10-01; parked 2DE0F0)

Current-header baseline 53 improves to 12 normalized lines in
`rw_xbvtxfmt_bntcomp_followup.c`. Cache tangent components into a local
vector (y, x, z assignment order), calculate the squared length with the
original dot macro, and retain an explicit y read in the scale macro.
The later normalization, packed-normal conversion, cross product and
loop tail now agree. The first tangent load and squared-length sum still
differ; literal relocations/padding also appear in odiff output.

512 dot/scale access combinations found an intermediate 25-line form;
96 cached-component forms found 12. A further 288 cache-mapping/order
probes did not improve it. No production changes. Reproduction:
`rw_bntcomp_normalize_reads.py`, `rw_bntcomp_cached_dot_trials.py`,
`rw_bntcomp_dot_mapping_trials.py` with pscore.py.

## Resolved: compressed-normal Xbox tangent/binormal conversion (2026-10-01)

`_rpXboxVtxFmtInstBNTComp` at 0x2DE0F0 now matches in
`src/rw/world/pipe/p2/xbox/xbvtxfmt.c`: 1,459 bytes, 13 relocations.
Starting from the 12-line follow-up, accumulate tangent squares in
separate statements: y squared, then x squared, then z squared. This
fixes the remaining loads and SSE sum registers. Keep the component copy
and explicit y read in the scale established by the previous trials.
Whole-unit comparisons retain all existing matches.

The same square-accumulation shape improves ordinary-normal 2DDB50
from 14 to four normalized lines; its final cross-product load/multiply
order still differs. New best is `rw_xbvtxfmt_bnt_sum_followup.c`.
512 individual-read probes did not resolve that last difference.
Reproduce the ordinary-normal work with `rw_bnt_sum_steps_trials.py`
and `rw_bnt_sum_reads_trials.py`.

### RW BNT final cross-product follow-up (2026-10-01; parked 2DDB50)

The four-line draft still differs at +0x478. Splitting z into a local
first product followed by -= and a final store fixes the second product
load order, but reverses the first product load/multiply at +0x46E. This
is an alternate four-line form, not an improvement or match. Eight
statement forms combined with 16 access masks, 100 parenthesis/operand
variants, and scalar-argument helpers (24 orders, three bodies) do not
resolve both products together. The earlier draft remains preferred.
Reproduce with `rw_bnt_z_{steps,group,scalar}_trials.py`. No production edits.

### Delta-morph initial counting loop (2026-10-01; parked 2F28D0)

A pointer-based initial traversal reduces the current best from 1261 to
949 normalized diff lines. Advance target, current-value and atomic-value
pointers with a remaining-target countdown; cache the RLE code pointer
and count for the nested loop. Saved as
`dmorph_instance_pointer_followup.c`. The callback still first differs
at +0x1B, with extensive register/stack differences. The private
XboxDMorphAddBlock helper remains exact (109 bytes, zero relocations)
when compiled beside it. Neither can be newly placed independently.

Before that, 48 typed count-phase inline forms (argument orders and
local-versus-output accumulation) failed to improve the old baseline.
Reproduce with `dmorph_count_{block,pointer}_trials.py`. No production edits.

### Delta-morph guarded initialization (2026-10-01; parked 2F28D0)

Guarding the three traversal pointers with remaining > 0 reduces the
949-line pointer draft to 900 normalized lines. Original code also tests
the target count before loading the traversal pointers. The callback's
first mismatch remains +0x1B, so this remains a partial reconstruction.
The block helper still matches 109 bytes beside the guarded candidate.
New best: `dmorph_instance_guarded_followup.c`.

Tested all 24 initial declaration orders, six guarded pointer orders
with for/do loops, and indexed-counter/count-load variants. A countdown
with the explicit unsigned > 0 guard is best. Reproduce with
`dmorph_initial_order_trials.py` and `dmorph_guard_index_trials.py`.
No production edits.

### Delta-morph guarded RLE follow-up (2026-10-01; parked)

The 900-line guarded draft remains best. Tested 32 combinations of
target-flag caching before/after the RLE scan, a cached code byte,
countdown code-pointer traversal, and delayed code-pointer loading.
None improves the baseline. Rechecked all 48 count-phase inline forms
against the guarded draft; best helper form is 955 lines.
Reproduce with `dmorph_rle_flag_trials.py` and
`dmorph_guarded_inline_trials.py`. No production edits.

### Delta-morph buffer setup follow-up (2026-10-01; parked)

The guarded 900-line candidate remains best. Tested all 63 nonempty
subsets of six buffer-pointer initializations moved either just after
format lookup or just before the buffer-creation branch (126 probes).
None improves it. Ternary normal/color/lock selection retains 900;
combining the duplicated texture-coordinate tests worsens it to 930.
The geometry register mismatch at +0x1B persists in these variants.
Reproduction: `dmorph_buffer_init_trials.py` and
`dmorph_attribute_setup_trials.py`. No production edits.

### Delta-morph remaining loop scopes (2026-10-01; parked)

Re-ran all 128 subsets of separate counter scopes for the seven remaining
i-indexed loops against the guarded draft. Best remains 900 normalized
lines; the prior scope choices still reach it. Then tested all 15 nonempty
subsets of pointer/countdown traversal in the four deformation loops.
Unlike initial counting, these worsen output (best 1035), often changing
the stack frame at byte zero. Keep the guarded 900-line candidate.
Reproduction: `dmorph_guard_scope_trials.py` and
`dmorph_deform_pointer_trials.py`. No production edits.

### Resolved: SplinePath empty-destructor EH (2026-10-02; BA030)

The empty destructor now matches with VC7.1 `/EHa` for unit_0B9EA0:
73 bytes and six relocations, plus its 8-byte unwind and 10-byte handler.
All 15 existing annotations in the unit still match. The compiler retains
base cleanup for asynchronous exceptions even though the body is empty.
The following historical source trials used `/EHsc` and are superseded.

Under `/EHsc`, the empty destructor was 14 normalized lines from the image.
Empty/typed exception specifications, __assume(true), __assume(this),
and an unevaluated sizeof(call) retain it. Function-try-blocks and an
empty body try/catch emit a different frame and catch machinery (35/37).
Declaring an empty inline before the class and defining it after the
class also retains 14, with inline/forceinline and zero/this arguments.
Thus late availability of the inline body does not preserve the needed
EH state 0 in this compiler. No production edits. Reproduce with
`spline_empty_eh_trials.py` and `spline_late_inline_trials.py`.

### Generator factory temporary follow-up (2026-10-01; parked 122410/1224F0)

Both factories retain eight normalized diff lines: the head/id temporary
slots are still exchanged. Constant-condition head expressions allocate
a late temporary but emit test/branch code and move the new-expression
temporary. Scalar casts/comma forms and a typed inline setter accepting
the head by const reference change the frame or register sequence; none
improves baseline. Verified all 13 baseline/candidate forms separately
for both factories with current headers. Reproduce using
`generator_head_temp_trials.py` and GF_FACTORY as described in its header.
No production edits.

## Resolved: flak vehicle constructor (2026-10-01)

`type_3DC378::type_3DC378(type_712B0 *)` at 0x15A8C0 now matches
134 bytes / 11 relocations, plus its 32-byte unwind funclet and 10-byte
handler at 0x301D00/0x301D20. The bare vehicle constructor definition is
inline in unit_155470.cpp. Three reference-returning trigger-coordinate
accessors in the tank factory warning preserve its 293-byte match while
allowing the flak constructor's larger frame. All existing unit matches
remain exact. No diagnostic no-op calls are retained.

The old attempt only tested inline-budget calls before new. Three calls
after new or later in the factory remove the excess frame; real coordinate
accessors provide those expansions without changing emitted instructions.
Returning coordinates by value changes code; const-reference returns match.

## Resolved: ordinary Xbox tangent/binormal conversion (2026-10-01)

`_rpXboxVtxFmtInstBNT` at 0x2DDB50 now matches in
`src/rw/world/pipe/p2/xbox/xbvtxfmt.c`: 1,425 bytes, 10 relocations.
A two-vector-pointer inline for the final cross-product z component,
with explicit normal x/y reads, fixes both multiply operand orders.
Keep the earlier y/x/z square accumulation and the x/y macro expressions.
The qualifiers record instruction order, not original volatile types.
All 27 annotated functions in the unit retain exact matches. No new assembly.

The earlier four-line draft and final-product probes are superseded.
Full-vector scheduling trials were worse (best 41 normalized lines).
Of the smaller pointer/read trials, `zp_ab_1_12` matches exactly; both
pointer argument orders work. Scalar-argument helpers alone had failed.
Reproduction: `rw_bnt_pointer_read_trials.py` with pscore, against the
pre-placement source at cc3f31efa; target `__rpXboxVtxFmtInstBNT`, 0x2DDB50.

### RW position-skip and skin-node follow-up (2026-10-01; parked)

Default instance 2DED60 retains 15 normalized lines. Eighty explicit
packed/unpacked branch and pointer-arithmetic combinations are worse
(best 105); returning the unchanged format pointer from an inline while
updating the buffer through an output parameter retains 15. Tested 72
whole-position/skip-only helper forms and argument orders. Neither keeps
the original separate position-size exits and format-pointer reloads.
Reproduce with `rw_default_split_size_trials.py` and
`rw_default_format_return_trials.py`.

Skin node 2D46F0 retains 16 normalized lines, including relocation
formatting. Pointer/index remap getters (byte versus word return, both
argument orders) and material helpers returning the header pointer leave
the two real differences unchanged: remap SIB base/index at +0x303 and
mesh/header reload order near +0x341. Explicit integer address sums,
subtraction of negative offsets, and address/index helpers also retain
16. Volatile remap reads worsen allocation to 228/231 lines. Reproduce
with `rw_skin_getter_return_trials.py` and `rw_skin_remap_address_trials.py`.
No production source or compiled placement changed.

### Delta-morph entry and counting outputs (2026-10-01; parked 2F28D0)

The saved guarded draft still scores 900 normalized lines, first real
byte difference at +0x1B: geometry uses EDI instead of original EBP.
The original also compares the target count in memory before loading it,
keeps the target base in EDX, and preserves the values/current delta in
EDI across the RLE loop. The candidate biases the target pointer by eight
and allocates these values differently. Frame size remains 0x44C.

108 combinations of outer declaration/zero-initialization order, cached
geometry reuse, and flags type retain 900 or worsen to 902. Separating
the count guard from the countdown initialization, including individual
qualified pointer/count reads, does not improve 900 (ordinary split 951).
Counting inlines returning each of the three outputs in turn or writing
all outputs through pointers are worse (best 955). Caching each deformation
loop's RLE byte with signed/unsigned byte or word types leaves 900, as do
62 combinations of typed target-flags/RLE/next-target accessors.

Durable reproduction: `dmorph_entry_order_trials.py`,
`dmorph_count_guard_reload_trials.py`, `dmorph_count_outputs_trials.py`,
`dmorph_deform_code_trials.py`, and `dmorph_target_access_trials.py`.
No production source or placement changes; keep the guarded draft.

### RW stream skip bounds-helper follow-up (2026-10-01; parked 2A7210)

Fifty-six typed bounds-check inline forms (memory pointer, scalar fields,
or pointers to fields; parameter permutations and four boolean-return
shapes) retain the single SIB mismatch at +0x87. C versus C++ compilation
of the current unit also yields exactly the same byte mismatch: 01 versus
original 08 in LEA. Twenty-four output-parameter sum helpers with either
initial operand and scalar/pointer increment arguments worsen allocation
(best 84 normalized lines, first instruction). The 18-line baseline score
includes jump-table artifacts; match.py confirms the real byte difference.
Reproduce with `rw_stream_end_helper_trials.py`,
`rw_stream_output_sum_trials.py`, and `rw_stream_language_probe.py`.
No production source, flags, or placements changed.

### RW default-instancer helper boundaries and flags (2026-10-01; parked)

2DED60 still has 15 normalized lines. Seventy-two size-helper variants
(enum/signed/unsigned type, signed/unsigned result, ordinary/inline/forced
inline, argument order, constant count and result-local forms) retain the
baseline. Ninety-six broader attribute helpers cover positions plus
normals, packed normals, or color. Output-pointer forms retain 15;
returning the updated buffer is worse. No helper boundary restores the
separate packed/unpacked exits.

Scratch compiler probes: /G5 and /Oi- retain 15; /Oa gives 202, /Ow and
/Oa /Ow give 98, /Os gives 329, /G7 gives 45, /Ob1 gives 71 (GetSize stops
inlining), and /Og- gives 611. C++ mode does not compile this trial unit
because its RwXbCreateVertexBuffer declaration is missing; that probe is
not match evidence. Keep the established /O2 /Ob2 /G6 configuration.

Reproduce with `rw_default_size_type_trials.py`,
`rw_default_attribute_block_trials.py` and `rw_default_flags_probe.py`.
All changes are scratch/draft experiments; production and placement stay
unchanged. The original draft remains preferred.

### RW skin alpha-address and bone-local follow-up (2026-10-01; parked)

2D46F0 remains at 16 normalized lines with the same two real differences.
Eighteen alpha-field address forms (address computed before bone batches,
before material setup, or after it; direct pointer, pointer getter, or
pointer plus read getter; ordinary versus volatile read) retain the same
header/mesh reload order. Thirty-six remap/vertex-map local variants
(one or both indices, both initialization orders, signed/unsigned words,
separate assignment and block scopes) also retain the baseline. Neither
changes the remap SIB byte at +0x303. Reproduction:
`rw_skin_alpha_address_trials.py`, `rw_skin_bone_index_locals_trials.py`.
No production or placement changes; keep rw_skinplatform_draft.c.

### RW skin-node compilation context (2026-10-01; parked)

The node is address-taken in the pipeline registration. Restoring static
linkage, adding explicit RwXboxLightsEnable/RwXboxGetCurrentVertexShader
prototypes, and forward declarations (16 combinations) all retain the
16-line baseline. Five equivalent for/while/guarded-do mesh loops also
produce the same differences.

The installed XDK D3D8.h helper calls
D3DDevice_SetVertexShaderConstantNotInlineFast(Register + 96, data,
4 * count) for count 3. Calling that target directly with the corresponding
register/count arguments, varying operand order and signed casts, retains
16 in all 16 call variants. Thus the Fast wrapper's constant arithmetic
is not responsible for the remap SIB difference. Selectively qualifying
the two mapping arrays and their source-pointer fields changes allocation
substantially (228-233 lines); no combination improves the baseline.

Reproduction: `rw_skin_linkage_trials.py`, `rw_skin_mesh_loop_trials.py`,
`rw_skin_constant_call_trials.py`, and `rw_skin_constant_read_trials.py`.
No production or placement edits. Keep the current skin-node draft.

### Delta-morph unsigned texture count (2026-10-01; improved, parked)

2F28D0 improves from 900 to 898 normalized diff lines. The original
clamps numTexCoordSets to four using JBE at 0x2F2A8E; the old signed
RwInt32 local emitted JLE. Declare numTexCoordSets as RwUInt32, which
also agrees with its unsigned iteration later in the function. Changing
numVertices to unsigned has no effect, so preserve its existing type.
The new best draft is `dmorph_instance_unsigned_followup.c`; the first
byte mismatch remains +0x1B and substantial register/stack work remains.
XboxDMorphAddBlock still verifies exactly beside it: 109 bytes, no relocs.

Before the type correction, 128 individual target-flag/RLE-read qualifier
combinations did not improve 900. Keep those probes as negative evidence,
not production qualifiers. Reproduction: `dmorph_initial_qualified_trials.py`
and `dmorph_count_type_trials.py` (tc_1 gives the new best). No production
or placement changes; the callback remains binary.

### Delta-morph buffer advances and mixed counting (2026-10-01; parked)

Starting from the unsigned-count draft (898 normalized lines), ninety
position/normal buffer-advance variants retain or worsen the baseline.
The variants cover static and dynamic paths: reversed addition, reuse of
the saved destination, scalar size temporaries, saved base-pointer locals,
and integer address addition. Introducing size/base locals often increases
register and stack differences; none restores the original static-path
LEA and reload sequence around 0x2F304D/0x2F306A.

Twenty-four mixed initial traversals independently index or advance the
target/current/value arrays, with countdown, cached-bound index, or
geometry-bound index loops. The all-pointer countdown retains 898;
all alternatives are worse (best 949). Keep the unsigned-count draft.
Reproduction: `dmorph_buffer_advance_trials.py` and
`dmorph_mixed_count_trials.py`. No production or placement changes.

### RW remaining-function audit and stream struct returns (2026-10-01)

Current splits/compiled manifests confirm five remaining RW functions:
2A7210 stream skip, 2D46F0 skin node, 2DED60 default instance, and
2F2860/2F28D0 delta-morph helper/callback. The nearby 2C7370 range is
a chunk of the XDK strchr; 2FD5D0, 2FD880 and 2FE290 belong to RWA.
No additional 2D toolkit function is left in the 0x251CE0-0x258000 range.
The handoff's old nine-function heading is corrected to five.

Sixteen stream position helpers returning a one-field struct (scalar or
memory-pointer inputs, both parameter orders, direct sum or accumulated
result) retain the baseline. match.py confirms the same sole +0x87 SIB
mismatch on sr_0_0_0. Reproduction:
`rw_stream_record_return_trials.py`. No production or placement changes.

### Delta-morph values/current address distance (2026-10-01; improved, parked)

2F28D0 improves from 898 to 894 normalized lines. Explicitly compute the
32-bit unsigned address difference between atomic values and current
values once, then compare through current-address + difference while
advancing current. The image similarly subtracts these addresses at
0x2F293E. This brings the initial values load into original EAX (896).
Initializing current before the target pointer further improves to 894.
Keep unsigned address arithmetic for the Xbox's 32-bit address space;
signed and pointer forms were diagnostic alternatives only.

The guard/count variants remain worse. New best:
`dmorph_instance_distance_followup.c`. First byte still differs at +0x1B;
large register/stack differences remain, so no production placement.
The companion XboxDMorphAddBlock verifies exact: 109 bytes, zero relocs.
Reproduction: `dmorph_value_distance_trials.py` and
`dmorph_distance_guard_trials.py`; winner vg_0_2_0. Earlier unsigned-count
draft is superseded but retained to reproduce its trials.

### Delta-morph target address and RLE guard (2026-10-01; parked)

The address-distance draft remains best at 894 normalized lines.
Eighteen explicit target-address traversals (integer, byte pointer or void
pointer; three equivalent increments; per-iteration typed local or casts)
produce the same code and retain the biased target pointer.

The original checks the RLE count before loading its code pointer.
An explicit count guard around a for loop introduces a redundant entry
check and worsens to 941. Guarded do loops remove that extra check; the
best 908-line variant initializes j before the unsigned count guard.
It is a useful alternate loop shape but does not improve overall register
allocation. Keep the 894-line draft as the current best. Reproduction:
`dmorph_target_address_trials.py`, `dmorph_inner_rle_guard_trials.py`,
and `dmorph_inner_rle_do_trials.py` (best alternate rd_0_0_1).
No production source or placement changes.

### Delta-morph RLE cache audit (2026-10-01; parked)

Sixteen combinations independently remove cached RLE count, code pointer,
and RLE-struct pointer, or cache target flags, from the 894-line distance
draft. None resolves the original traversal. rc_12 ranks 893, but comparing
it directly to rc_00 shows both are 5,724 bytes: its target pointer is
biased by 0x14 instead of 8 (the image uses the unadjusted target base),
with changed field displacements. A jump plus alignment LEA near +0x91B
becomes a different alignment LEA near +0x91C. This is an allocation and
alignment tradeoff, not a recovered original loop. Do not promote the
one-line heuristic gain; retain dmorph_instance_distance_followup.c.
Reproduce with `dmorph_uncached_rle_trials.py` (rc_00 versus rc_12).
No production or placement changes.

### RW stream skip processor/options audit (2026-10-01; parked)

Whole-unit scratch compilation with /G5, /GB, /Oa, /Ow, /Oi- and /Ob1
retains the +0x87 mismatch. /G7 first differs at +0x1A (ADD instead of
DEC), changes EDI save/restore and stream-position update scheduling,
and still emits the same wrong LEA base/index order in the memory case.
/Os and /Og- differ from entry. These options do not explain the last
address byte; retain the established /O2 /Ob2 /G6 flags. Exact byte
comparison used for each compiled candidate; no production flags changed.
Reproduce with `rw_stream_schedule_probe.py`.

### RW default-instancer format access (2026-10-01; parked)

The current RpXboxVtxFmt layout uses byte pos/norm bitfields, an unaligned
16-bit texCoord field, then a byte of flags. A scratch overlay using one
32-bit bitfield allocation unit preserves sizeof==4 but changes code from
+0xB; both RwUInt32 and unsigned int bases fail. Retain the existing layout
supported by the Godfather PDB. Production headers were not edited.

Eighteen position-only raw-read variants replace the pos bitfield at the
copy call, size call, or both. Byte reads masked with 15 retain the
15-line baseline, including the merged position-size exits. Wider word
reads do not fix it either. Reproduction:
`rw_default_bitfield_probe.py`, `rw_default_position_rawread_trials.py`.
No production or placement changes.


### RW delta-morph execution checks (2026-10-01)

Changed approach from source permutations to differential x86 execution.
The original and parked 2F28D0 callback agree in 100 complete existing-buffer
cases and 10 fresh-buffer cases: geometry arrays, current weights, vertex
buffer bytes, vertex alpha, shader declarations and allocation/lock events.
The actual original block merger and vertex converters execute; graphics and
allocation entry points use deterministic stubs. An additional scratch check
covered 400 initial-counting-loop cases, including NaNs and null data/values.
These checks do not prove byte identity, pending-fence paths, allocation-failure
handling, or real GPU behavior. The callback remains binary, first mismatch +1B.

Reproduce from the repository root:
`python -m pip install --target build/tooltmp/emulation_deps unicorn==2.1.4`
`python tools/session/dmorph_execution_build.py`
`python tools/session/dmorph_execute.py build/tooltmp/dmorph_trace_baseline.obj`
The second optional argument reduces the random case count; fresh cases always run.

Godfather debug frame 11348D0 confirms unsigned flags and numVertices; corrected
those types in dmorph_instance_distance_followup.c. The emitted callback bytes
remain unchanged (5724 bytes including local jump tables). No production placement.

### RW stream skip matched (VC7.1, 2026-10-01)

`RwStreamSkip` at 0x2A7210 now matches all 292 bytes, 13 relocations,
and 18 bytes of jump tables with the existing VC7.1 flags. The missing
source structure was in the file branch: Godfather debug `_RwStreamSkip`
at 0xBB6760 has a `RwStream *retVal`, assigns it in both seek outcomes,
then returns it once. Restoring that structure fixes the memory branch's
LEA base/index byte at +0x87; changing the addition itself was unnecessary.
Production `bastream.c` supersedes the stream-skip experiments.


### RW skin atomic node matched (VC7.1, 2026-10-01)

`XBoxSkinAtomicAllInOneNode` at 0x2D46F0 now matches all 986 bytes and
36 relocations. Godfather debug 0x11568D0 supplies three source details:

- Advance the shader-constant pointer through the viewport and matrix
  constants instead of spelling each array offset independently.
- Traverse bone batches with `firstBatch + currentBatch` indexing.
  These two changes together fix the remap SIB byte at +0x306; either
  change by itself retains the mismatch.
- Pass `(RxXboxResEntryHeader *)(resEntry + 1)` directly to the render
  callback. This fixes the EDI header reload before the ESI mesh reload.
  The reference's actual callback argument is visible at 0x1156F09.

The existing VC7.1 flags are unchanged. Production `skinplatform.c`
supersedes `rw_skinplatform_draft.c` and all skin-node probe candidates.


### RW default instancer matched (VC7.1, 2026-10-01)

`_rpXboxDefaultInstance` at 0x2DED60 now matches all 669 bytes and
18 relocations. Godfather debug 0xB7B540's frame identifies `size` at
-0x20 as signed `int`; the old draft incorrectly used RwUInt32. Store
both position paths' results in an RwInt32 size local, then advance the
buffer after the branch. This restores the separate packed/unpacked
exits, their format-pointer reloads and the downstream alignment.

The signed local without the common pointer advance still differs;
the common advance with an unsigned local also differs. Both changes
are required. Scoped signed attribute locals also match, confirming
that signedness and use determine the missing source structure.
No compiler flags or shared declarations changed. Production
`xbvtxfmt.c` supersedes the default-instancer drafts and probes.

### RW delta-morph reference structure (2026-10-01; improved, unmatched)

The new draft is dmorph_instance_reference_followup.c: 495 normalized diff
lines versus the distance draft's 894. First differing byte advances from
+0x1B to +0x33; the frame size already agrees at 0x44C. VC7.1 and flags stay
unchanged. The callback still needs stack placement and prelight-copy fixes.

Recovered from Godfather debug 0x11348D0 and checked against the game:

- The position copy/skip branches assign a signed RwInt32 size, then advance
  the buffer once. The reference frame records size at EBP-0x49C.
- Restore the original indexed target loop and shared i. With the size local
  corrected, VC7.1 naturally emits the original pointer-distance/countdown
  instructions. The manually rewritten distance loop and localIndex are gone.
- Use D3DVertexBuffer_Lock with vbSize and the output-pointer argument.
  The XDK inline emits Lock2, preserving the reference's source context.
- numTexCoordSets is unsigned, but its conditional initializer has signed
  operands: geometry->numTexCoordSets versus 0. Restoring that conditional
  fixes the later normals-copy instruction differences (532 to 495 lines).
- Raw 0x11368B0 stores each converted color delta in signed shift before
  adding its low byte. The Hex-Rays output hid that local. Restoring it
  emits the same optimized bytes as the direct byte cast, but keeps the
  source consistent with the reference.

After ignoring stack offsets and relocation/branch targets, and excluding
the eight switch tables, only 22 instruction-diff lines remain: prelight
copy-call scheduling near game 0x2F3B03/0x2F3B43 and downstream alignment.
This diagnostic is not an exact match: the global stack-slot permutation
still matters. Current callback is 5564 code bytes plus 160 table bytes;
the game has 5580 code bytes plus 160 table bytes.

Reproduce with dmorph_reference_trials.py and tools/session/pscore.py,
target _XboxDmorphAtomicInstanceCallback, 0x2F28D0, production dmorphpipeg.c.
The execution build helper now selects the new draft; dmorph_shape.py
reproduces the instruction-only diagnostic. All 100 random existing-buffer
and 10 fresh-buffer fixtures pass with this draft. They exclude pending
fences, allocation failures and real GPU behavior. The block helper and
all six previously placed functions in the unit retain exact matches.
The whole-image gate passes byte-identically (18,053 compiled pieces).
The helper and callback remain binary in production.

Rejected: signed copy strides, reversed index multiplication, pointer const
qualifiers, alternate position-size scopes, prelight OR operand order, and
expanded vector assignments. Common size locals for normals/texture copies
worsen normal-loop SSE scheduling. Retain the new draft as the starting point.

### RW delta-morph matched (VC7.1, 2026-10-01)

XboxDMorphAddBlock (0x2F2860) matches 109 bytes with no relocations.
XboxDmorphAtomicInstanceCallback (0x2F28D0) matches 5,740 bytes with
93 relocations, including 160 bytes of local jump tables. Both are now
in src/rw/plugin/dmorph/xbox/dmorphpipeg.c with the established VC7.1 flags.

The decisive evidence was a control-flow-aware stack map. In the game,
currentBlock repeatedly occupies +0x24, j +0x14, and the target pointer
+0x28 across all four attribute passes. Separate declarations in the old
draft allocated these values to different slots in every pass.

Share currentBlock, j, l, dMorphTarget, rle, scale and the delta pointers
in the enclosing deformation block. Keep k, m and maxl inside the passes.
Initialize each RLE loop with j first, then k and m (where used). Sharing
every counter fixed stack placement but changed final-alpha FPU scheduling;
restoring the narrower k/m/maxl scopes resolves that. Sharing l fixes the
remaining copy-call scheduling. Godfather debug 0x11348D0 supplies the
variable names and corroborates the loop initialization/increment order.

Scratch progression: shared locals 210 normalized lines; initializer order
208; narrower counters 157; shared l 137. That final heuristic score is
entirely jump-table disassembly artifacts: exact comparison passes and the
table-excluding instruction comparison reports zero differences.
Scratch reproduction: dmorph_shared_locals.py, dmorph_shared_scope_refine.py,
dmorph_shared_counters.py (dsk_02). These used pre-placement b7167fc7a.
Production source supersedes every delta-morph draft and trial.

The full unit's eight annotations match. No inline assembly, compiler-option
change, shared-header change or IDA database edit was needed. The prior
execution harness now builds production directly; exact bytes and the full
placement gate are the acceptance criteria. The tracked RW list is complete;
remaining manifests still include parked game/RWA work and XDK tail chunks.


### Resolved: custom entity setup sub_9B0B0 (2026-10-02)

type_3D51C0::vf_234 now matches 520 bytes and all 13 relocations with the
existing VC7.1 settings. The old all-inline draft put setter values after
the struct return, while making every inline local explicit moved that
return too far down the frame. Keep just the two setter values as named
locals at -0x1C/-0x20 and retain get_unk_04_h(), zero_v3d and get_unk_18().
The compiler places the return temporary at -0x24, then the vector pointer
and getter locals at -0x28/-0x2C/-0x30, with this at -0x34.
A scalar or struct named local at -0x24 copies destination-first; the
getter return preserves the original source-first copy. No shared header,
compiler flag or inline assembly change was needed. Production unit_09AD40.cpp
is the matching source; the earlier compiler-order question is resolved here.


### Resolved: Distance Scheduler temporary groups (2026-10-02)

sub_35AA0, sub_35FD0 and sub_362F0 now match in unit_034FA0.cpp with
unchanged VC7.1 flags and headers (369 / 674 / 675 bytes, 10 / 7 / 7
relocations; the first size includes its 32-byte jump table). The filter
uses three named handle values and retains three inline serial getters.
Its comma expressions evaluate the handle reads only when the preceding
pointer checks succeed, preserving both control flow and register order.
The in-range and out-of-range callbacks use named payloads, handle values
and virtual-call receiver copies for all slots in the original 0x58 frames.
There is no need to change how this compiler numbers inline expansions:
ordinary named locals provide the earlier slots. All unit functions match.


### Resolved: fire-and-movement selection and enrollment (2026-10-02)

sub_39AA0 now matches 1,039 bytes and 23 relocations, plus its 22-byte
cleanup and 10-byte handler. get_unk_574_h().unk_00 supplies the union
temporary at -0xE0 before the remaining getter locals. Its single compound
eligibility condition and while-loop advance reproduce the original jumps;
early continues in a for loop introduce extra jumps and rotate registers.
sub_3A450 matches 849 bytes and eight relocations with named handle values
and receiver pointers throughout its 0x44-byte frame. The second team
branch's distance write to unk_1C is retained from the image. No compiler
or header changes were needed. All functions in unit_0390D0.cpp now match.


### Resolved: CDebugScript command-11 value (2026-10-02)

HandleAttributes at 0x43200 matches 586 bytes including 56 jump-table
bytes, with 48 relocations. A named RwInt32 at -0xC receives command 11
through GetCommandData. A plain store then differs only in three
register operands: the image needs EDX/EAX where the compiler uses
EAX/ECX. The existing compiled-out-check idiom supplies two register
steps between the read and member store; a single member-bit check
or two member checks both match. DEBUGSCRIPT_CHECK records that its
condition is chosen for loads, not recovered assertion text. Chained
assignment, comma, unary-plus and destination-expression forms retain
the mismatch; self-assignment adds unwanted instructions. Production
unit_042F40.cpp supersedes the parked note; no shared header changed.


### Resolved: AIManeuverManager union temporaries (2026-10-02)

Both remaining unit_03CA10 functions now match with the existing VC7.1
flags and headers. sub_3CE20: 643 bytes including its 28-byte table,
31 relocations, plus 102-byte cleanup and 10-byte handler. A direct
registration call allocates its union-return temporary before the
pool-size getter's inline local, exchanging -0x4C/-0x50. Put that call
and handle store inside register_maneuver_handle: expansion now allocates
the return after the pool getter. Plain static inline with by-value
arguments matches; forceinline and reference arguments are unnecessary.
sub_3D150: 388 bytes, six relocations. Named handle copies occupy
-0x5C/-0x60 before the factory return at -0x64. The earlier hypothesis
that these require a different compiler is superseded.

### Resolved: projectile-generator factory temporaries (2026-10-02)

sub_122410 and sub_1224F0 now match 213 bytes and 12 relocations apiece
with unchanged VC7.1 flags and scalar factory signatures. Both generated
17-byte placement-delete cleanups and 10-byte EH handlers match the shared
original at 301560/301571; the second handler has an ICF alias.

The inline id getter must return the existing type_4CE900_00 index/serial
record from a typed member at +0x104. Its parse-time return temporary takes
-0x24; get_generator_list's inline local then takes -0x28, before the
constructor conditional result at -0x2C. The scalar member remains as a
union alias for the other methods. Moving the record declaration earlier
in its existing header allows the member without changing object layout.

A free helper returning a cast of the scalar member was insufficient: it
introduced another copy and slot at -0x2C, moving the constructor result
to -0x30. A real record member and member getter reproduce the one copy.
The factories still return the getter result's scalar unk_00 field.
Scratch reproduction: generator_phase_followup.py, generator_return_followup.py,
and generator_member_phase.py in build/tooltmp. Production source supersedes
the old generator_head_temp_trials.py and parked temporary-order question.

### Resolved: squad factory sub_3EEE0 (2026-10-02)

The factory matches 194 bytes and 14 relocations; its 17-byte placement-delete
cleanup and 10-byte EH handler also match 2FF6F0/2FF701. The list getter's
ordinary pointer local now occupies -0x20, before the constructor conditional
spill (-0x24) and the next-id post-increment spill (-0x28). The old note
requiring a parse-time head copy was too restrictive.

The remaining difference in the current-header draft was the global placement
new call: the transitive XDK <new> definition inlined it away. Suppress only
that header's scalar placement definitions with __PLACEMENT_NEW_INLINE and
supply the original declaration pair. This preserves the calls to 6CCF0 and
19A750, recorded as global operator aliases. A noinline redeclaration also
matched in scratch, but production uses declaration-only functions, as the
original call sites require. All existing annotations in the unit still match.
No compiler flag, shared-header or inline-assembly changes were required.
Scratch: squad_factory_phase_trials.py and squad_alloc_phase_trials.py;
production unit_03DF30.cpp supersedes the parked factory note.

### Resolved: objective-hint frame sub_1C5350 (2026-10-02)

sub_1C5350 now matches 933 bytes and 50 relocations with unchanged VC7.1
settings. Its generated cleanup is 88 bytes / seven relocations at 303170,
and the handler is ten bytes / two relocations at 3031C8. The two adjacent
old chunk_of_1C5350 splits were joined so the compiled cleanup supplies
all seven funclets as one piece.

The missing 0x20 bytes are reproduced by eight existing unused_slot()
expansions inside a separate final-return scope, after the formatted-return
branch and two existing debug_text() calls. The scope is decisive: eight
calls in the outer scope still leave the frame too small; twelve there
can match, but eight in the separate block match with the original earlier
temporary at -0xE8. Putting the calls before that branch moves its temporary.
The original discarded expressions are unknown; source comments state this
and the frame evidence. No arbitrary stack array or compiler flag is used.

The two text diagnostics preserve expansion of all five char constructors.
The formatted temporary uses the correct derived type_1CB670; its byte
match is unchanged. Every prior annotation in unit_1C3D20.cpp still matches.
Scratch reproduction: hint_scope_allocation.py, hint_scope_final.cpp and
hint_scope_final.obj in build/tooltmp. Production source supersedes the
parked draft_1C5350.cpp and all earlier hint-context experiments.


### Resolved: WMA position query sub_250D90 (2026-10-02)

The Xbox WMA query now matches 100 bytes and four relocations with the
existing VC7.1 flags. The image dispatches the requested unit with
`sub eax, 2`; the old draft used an if and emitted CMP with a different
state register. A switch with case 2 reproduces both the dispatch and
the ECX state pointer, including both unsigned-to-float conversions.
An explicit case 1 that only breaks also matches, but is unnecessary.
The entire production unit's 26 annotated functions still match.
Production src/rwa/xbox/unit_250B20.c supersedes the query in
docs/drafts/rwa_wma_draft.c. Scratch reproduction:
build/tooltmp/rwa_wma_position_trials.py.


### Resolved: Xbox voice update sub_250340 (2026-10-02)

The complete update matches 1,134 bytes and 29 relocations with unchanged
VC7.1 flags. All 102 annotations in unit_24EC60.c match. The current-header
old draft started at 284 normalized diff lines, including excessive saved
registers and a smaller frame. Moving the body before its getter definitions
did not help: VC7.1 still propagates their effects across this translation unit.

A local function pointer initialized to sub_24F110 preserves the call's
unknown-write boundary while compiling to the same direct call. This avoids
splitting the getter into another file or inventing an ICF alias. Direct casts
and an inline callback wrapper did not preserve that boundary. Qualified reads
of the first listener check and output gain retain the observed reload and x87
operand order. The exact original declaration forms remain unknown; production
source states that limitation instead of asserting shared volatile members.

The vector additions require source component first, listener component second
in C. The I3DL2 source assignments require the recovered order (rolloff, direct,
room, roomHF, obstruction ratio/value, occlusion ratio/value). A block-local
RwUInt32 position, assigned by the format branch then stored once, restores the
EBP save/pop positions and EAX result of the ADPCM division. A forceinline
value-returning helper also matched, but the named local is sufficient.
The source declares the existing spatialization call sub_23CD40 explicitly.
Production unit_24EC60.c supersedes the update in rwa_voice_draft.c.
Scratch reproduction: rwa_voice_update_*_trials.py and
rwa_voice_update_clean.py under build/tooltmp.

### WMA initializer current-header follow-up (2026-10-02; parked)

sub_250C10 still has eight normalized instruction differences: the stack
cleanup stays after the zero stores, and EAX rather than ECX holds one for
the next two stores. Correcting RwaStreamNodeGetParams to its real pointer
return does not change the result. Inline helpers for all/zero/tail stores,
ordinary local pointers, scopes, a local one constant, and chaining the one
stores retain the baseline; qualified output and chained zeros are worse.
Reproduction: docs/drafts/rwa_wma_defaults_shape_trials.py with pscore.py,
symbol _sub_250C10, address 250C10, src/rwa/xbox/unit_250B20.c. No initializer
or prototype change has been placed in production.


### RWA wave setter, destructor and listener follow-up (2026-10-02; parked)

No production function or placement changed in this batch. All probes use
the existing per-unit compiler flags: VC7.1 for the Xbox layer and VC7.0
for the core listener. Run each script with tools/session/pscore.py, its
underscored C symbol, hexadecimal address, and the production unit below.

* **24F410 / unit_24EC60:** current-header baseline was 247 normalized
  diff lines. Shared changed/created control flow (skip format setup when
  neither is true) and a named flags value around the initial wave clear
  reduce that to 115. The first 13 instructions match. The wave and is3D
  values still choose the wrong registers; the null-wave path, descriptor
  store scheduling and play-region argument evaluation also differ. A
  non-null outer if puts the stop path at the end but scores 121 and merges
  format-call tails differently. Pointer/local declaration variants,
  qualified wave reads, explicit pointer/offset temporaries, nested scopes,
  and format/play-region inlines do not resolve the remaining differences.
  Helpers 24EDC0 and 24F350 match 116 bytes / five relocations and 33 bytes /
  zero relocations, but remain coupled to the unplaced caller.
  Best bundle: rwa_voice_wave_followup.c. Reproduction: rwa_voice_wave_*
  trials (shape variant vws_12, plus the alternative vws_13).

* **24E710 / unit_24DF20:** the volatile integer-array probe remains two
  normalized lines away: its first zero store is scheduled before the
  setter call's stack cleanup. A forceinline store helper instead drops
  that first store entirely; exact object disassembly confirms this is a
  missing store, not a match. Local function-pointer calls, chained/comma
  forms, pointer-element types, scope changes and several inline pointer
  shapes do not fix it. sub_24DF00 traverses the NV wave definitions; it
  is not a parameter-UUID getter, so the discarded parameter-call theory
  is unsupported. Reproduction: rwa_output_destroy_*_trials.py.

* **23D2A0 / 23D320 / unit_23CC10:** current VC7.0 baselines differ by
  14 / 16 normalized lines. Reversing scalar product operands alone has
  no effect. Qualified individual reads reduce these to eight / six,
  with remaining x87 operand-order, pop/load and dirty-flag scheduling differences.
  Pointer-based whole-cross inlines, component inlines, and named scalar
  product temporaries remain unmatched. Best probes: lisr_01 for 23D2A0,
  lisr_11 for 23D320. No qualifiers have been applied to shared types.

* **23CC70 / unit_23CC10:** the old draft conflicts with the unit's
  placeholder callback declaration. The scratch build gives it its
  pointer return and casts it to the definition callback, as other units
  do. VC7.0 reproduces the initial temporary zero-vector copies. Chained
  assignments for the zero/one orientation values, and literal 0.0f in
  the cross product instead of the external flt_3CD84C object, reduce 57
  normalized lines to 18; the first 35 instructions match. Remaining
  work is x87 common-term use and scheduling after the up-vector copy.
  Full cross-product expressions retain the same mismatch. Best variant:
  lsetc_07_0; lsetc_10_0 and lsetc_20_0 have the same score/prefix.
  Best listener bodies: rwa_listener_current_followup.c. Reproduction:
  rwa_listener_*_trials.py; choose the matching symbol/address for each.

Scores are iteration aids and include padding effects. None of these
drafts passes the exact byte/relocation check; only production annotations
are evidence of placement.


### RWA creation callback signatures and loops (2026-10-02; parked)

241230 remains two normalized lines apart, solely the final EAX/EDI reload
order. The matched queue initializer 2472E0 returns rwaQueue* and accepts
an RwUInt8 count; the caller's old void/RwUInt32 prototype is inaccurate.
Correcting either or both does not change this mismatch. For/while forms,
a separate saved count and reuse of the failed parameter retain it; guarded
do/while forms worsen the result. No production change was made. Scripts:
rwa_creation_callback_signature_trials.py and rwa_creation_callback_loop_forms.py
with pscore.py, _sub_241230, 241230, src/rwa/rwastreamsourceobj.c.


### WMA source creator current-header follow-up (2026-10-02; parked)

2516E0 has a 246-line normalized baseline with the correct 0x354 frame and
first 52 instructions. A named track pointer for the description setup
reduces this to 211. Best clean draft: rwa_wma_create_followup.c. Qualifying
callback stores and the loop noPackets test reduces it to 209, but the
extra qualifiers are not retained in the saved body. Explicit failure
labels reach 227 independently and change early argument registers.

Local-name permutations, declaration order and scopes do not change the
compiled layout. Remaining differences include cleanup-branch sharing,
positions/content descriptor/string array slots, packet-loop base/index
encodings, and metadata store/read scheduling. No creator body is placed.
Reproduce with rwa_wma_create_{current,flow,local,members,scopes}_trials.py,
pscore.py, _sub_2516E0, 2516E0, src/rwa/xbox/unit_250B20.c. All variants
compiled successfully with the existing VC7.1 flags.

### RWA pool and bitmap allocation follow-up (2026-10-02; parked)

Current pool 2442D0 baseline is 77 normalized lines. Moving insertion to a
shared label, separating alignment initialization, using pointer arithmetic,
and naming chunk size/mask/end locals do not change it. Capturing chunk->next
before the insertion stores worsens it to 79. Register assignment remains
the first difference. See rwa_pool_flow_trials.py and rwa_pool_local_trials.py.

Bitmap creator 2FD5D0 still has no match. Current baseline is 127 lines;
the older early-numBytes assignment variant is 87. Shared failure returns
reduce the unchanged baseline to 97, but allocation inlines, wider shift
locals, and splitting its increment do not solve the register/branch layout.
See rwa_bitmap_flow_trials.py and rwa_bitmap_return_trials.py. These scores
include relocation/padding artifacts; no result was treated as a match.

### RWA setter dispatcher resolved (2026-10-02)

Behavior_DispatchCallback at 23F8B0 now matches 48 bytes, no relocations,
including two NOP bytes. Earlier parked notes and wrapper/qualifier probes
are superseded. Initialize obj = handle->obj before selecting setter, then
initialize value = data and widen setter->param into RwUInt32 param before
the callback. Object initialization order plus the widened parameter fixes
the extra EDI lifetime. No qualifiers, header edits or compiler changes.
Repro: rwa_setter_lifetimes.py; setlife_0_1 is exact.

### RWA stream unlink resolved (2026-10-02)

23FC00 matches 96 bytes / seven relocations. The earlier 33-line near miss
is superseded: an explicit count local plus qualified count accesses reduces
it to four lines; a qualified incoming stream pointer loaded before the count
decrement/store fixes the remaining schedule. The later lock/player/unlink/
unlock code is unchanged. The original qualifier declarations are unknown;
the source records the observed access-order constraint. Saved repros:
rwa_unlink_access_trials.py and rwa_unlink_order_trials.py (unlinkorder_1).

Adding the unlink definition also lets VC7.0 remove the creator 23FB40's
count reload. Preserve it as a named count loaded through a qualified read
after the wait and before relinking, then test count before releasing the
semaphore. Both functions match together; keep the final global increment.
The first whole-image attempt detected this regression and was not committed.

### RWA definition release helpers (2026-10-02; caller still parked)

23DAA0 now matches 144 bytes / three relocations, including three NOP bytes.
Read each parameter-table pointer through a qualified access before its
16-bit count test; this prevents VC7.0 from sinking that load into the loop.
The original qualifier form is unknown. The existing 23DB30 helper also
matches (96 bytes / eight relocations). Both depend on the unplaced 23DB90
caller to establish their compiler register ABI, so neither was placed.

Release caller 23DB90 still swaps ESI/EDI. A named child link removes the
extra child reload; separate scopes, typed list access, qualified argument,
and early-return labels do not fix register allocation (79 normalized lines).
Qualified list reads worsen it; a local release function pointer scores 78
but changes that call boundary, so is not retained. Saved access, loop,
scope, children and link-access scripts reproduce the trials. Best helper
combination: rwa_objdef_release_access.py, objrelaccess_3. The updated
rwa_objdef_release_followup.c preserves both exact helper bodies.

### RWA voice priority and swapping follow-up (2026-10-02; parked)

Current-header voice priority 23E980 probes are now reproducible from
rwa_voice_priority_draft.c instead of a scratch-only vm_full.c. Baseline
113 normalized lines; qualified position reads and integer distance copies
score 101, integer previous-priority copy scores 99. Explicit near/far
branches, a named one-bit mask and square-sum operand order do not improve
that result. The x87 schedule, EBX constant lifetime and list branches remain.
No compiler settings changed; no bodies placed. Scores include relocation
and padding artifacts. Scripts: rwa_voice_priority_current.py and shapes.py.

Byte-swap 241FD0 current factored baseline scores 10 normalized lines:
the 32-bit shifts/masks use swapped EAX/EDI, and the 16-bit path generates
xor/mov-high/mov-low instead of movzx/mov-high. Named temporaries, declaration
order, word-load forms and qualified byte accesses do not match. Saved
rwa_swap_lifetime_trials.py, operand_trials.py and word_trials.py preserve
these trials. Production source is unchanged.

### RWA stream-cache callback group resolved (2026-10-02)

244FA0 now matches 192 bytes / four relocations, including 12 NOP bytes.
The single shared failure tail's register rotation is fixed by writing the
same cleanup in the status==4 branch and the failed-tell branch. Both return
immediately; VC7.0 merges the duplicated cleanup into the original tail.
One duplicated branch alone worsens the result. Qualified header accesses,
named callback arguments and pointer-returning clear inlines did not help.
No qualifiers or compiler changes are needed in the placed result.

This unlocks 2449C0 (32 bytes / no relocations) and dispatcher 245060
(96 bytes / two relocations). Open 2450C0 remains unmatched. Repros:
rwa_cache_current.py and rwa_cache_duplicate_failure.py (cachedup_1 exact).

### RWA cache open and WMA defaults (2026-10-02; parked)

2450C0 was rechecked after placing the cache callbacks. Its current baseline
is 18 normalized lines: the client push is late and callback/data/name loads
use different registers. Qualified callback/data/name parameters, chained
state/mode assignments, and moving data beside callback do not change it.
A named request pointer worsens it to 22; a qualified client parameter copied
to a local worsens it to 46. Repros: rwa_cache_open_current.py,
rwa_cache_open_access.py and rwa_cache_open_request.py.

WMA defaults 250C10 remains eight lines apart: delayed caller stack cleanup,
and EAX instead of ECX for the two one-valued stores. Individually qualifying
the first zero store, either one-valued store, or the incoming object pointer
does not change it. Repro: rwa_wma_defaults_access.py. No production edits.

### RWA ADPCM lifetime follow-up (2026-10-02; parked)

IMA encoder 24BD30 remains 36 normalized lines apart, with step/diff in
swapped ECX/EDX. Explicit compound updates to sample/step in the predictor
branches and qualified step-table/predictor reads do not change that output.
Repro: rwa_ima_encode_update.py.

Block decoder 24BC50 has a current baseline of 68 normalized lines. The
image stores coefficient zero in the block-count argument home. Copying
blocks to a remaining local and reusing that parameter for the coefficient
scores 72; reversing coefficient loads scores 73. Countdown inner loops
do not improve either result. Writing the two nibble iterations explicitly
instead of letting the compiler unroll them scores 74 or worse. Repros:
rwa_adpcm_block_lifetime.py and rwa_adpcm_block_unroll.py. No exact match
or production edit; retain the original draft as the best current form.

### RWA search and splitter follow-up (2026-10-02; parked)

Search 23D970 remains unmatched. Reusing self for the child-list head and
using a separate root local retains 41 normalized lines; a qualified write
to the reused self argument scores 38 but does not recover the root load/
store sequence. Qualified root stores worsen allocation. Repros:
rwa_objdef_search_slots.py and rwa_objdef_search_store.py.

Splitter status 24CC80: a forward shared status-four label reaches 32
normalized lines (including jump-table artifacts), but duplicates mode-one
handling instead of sharing the image's tail. Explicit forward mode-one
sharing remains 34. All 24 case-group orders, with/without the early break,
fail; the original order stays best without extra labels. Read 24CD50's
explicit wrap-success return with shared failure/done labels scores 23,
worse than the existing two-line epilogue mismatch. Repros:
rwa_splitter_forward_tail.py, rwa_splitter_case_order.py and
rwa_splitter_read_tail.py. No production code changed.

### RWA instance-memory release resolved (2026-10-02)

23D8B0 now matches 144 bytes / four relocations, including 10 NOP bytes.
It recovers the allocation pointer from the word before the instance for
flag 8, or the pointer after the computed instance size for flag 0x10.
It then selects definition free-list/pool/heap release unless the caller's
custom-release path applies. sub_23F300's matched signature supplies the
size and writes a state offset. Keep that output in a separate unused local;
VC7.0 reuses the input argument home itself. Explicitly reusing the pointer
parameter instead hoists a flags address into EBX and produces 41 diff lines.
No qualifiers or compiler changes. The public signature retains the existing
void* callback interface and converts it to the two-argument release pointer
locally. Repro: rwa_instance_free_signature.py, instfreesig exact.

### RWA object-definition creator recovered in draft (2026-10-02)

Superseded by the resolved creation group below; retained as the trial history.

The current-header group is saved in `rwa_objdef_create_followup.c`; compile
it with `rwa_objdef_create_current.py`. `match.py` verifies 23DFB0 (272 bytes,
11 relocations), 23DAA0 (144 / three) and 23DB30 (96 / eight) in this context.
They remain unplaced because their static initializer dependencies still differ.

The creator's eight-byte list clear must be `memset(def->unk50, 0,
sizeof(rwaLink))`. Two member stores, even through a cached link pointer,
change register allocation across the whole function: the parent leaves EBP,
stack arguments change, and the failure epilogues differ. The memset restores
the original bytes without qualifiers in the creator. Repro:
`rwa_objdef_create_clear_trials.py`, createclear_0.

The old scratch initializer had incorrect fields, not just codegen differences:
clear unk54 at +0x54 rather than hint at +0x58, initialize waveDefs as its own
list, use paramsSize at +0x44, and clear the two execute callback members.
Use the declared tables->interfaces link rather than a byte offset. Corrected
23DF00 now differs only by the missing `or ecx, eax` at 23DF6E. The normalized
five-line score includes the table relocation and padding. Direct/masked
alignment assignment and a qualified initial zero store still omit the OR;
memset/indirect/qualified read-modify-write forms introduce extra loads.
Repro: `rwa_objdef_init_followup_trials.py`.

23DE20 is 19 normalized lines apart. An indexed forward loop restores the
typeIndex-based induction pointer; a 16-bit count guard restores the initial
count test, but an additional widened-count test remains. The type result
and io argument loads also have different ordering/registers. A qualified
input copied into a local recovers its static EAX argument ABI; the original
qualifier is unknown. Countdown pointer loops lose the typeIndex base, while
do-loop index forms retain extra induction/count work. These two initializer
helpers must match before placing the creator/release group. RWA remains 62.

SetupParams 23DD00 was also rechecked: factoring the two loops into an ordinary
inline emits real helper calls; forceinline returns to the same 86-line shared
failure baseline. Qualified count copies spill the input pointer and do not
recover the target's register lifetimes. Continue with the creator dependencies
before revisiting those count experiments. Production sources are unchanged.

### RWA definition creation group resolved (2026-10-02)

23DAA0, 23DB30, 23DE20, 23DF00 and 23DFB0 now match together in rwaobjdef.c:
144/96/160/176/272 bytes respectively, 848 bytes including NOP padding.
The group retains its original compiler-selected static register ABI.

The missing OR at 23DF6E came from the packed state-size/alignment word.
Clear its 28-bit stateSize and four-bit stateAlign separately, then invoke
the existing alignment macro. A whole-word zero lets VC7.0 remove the OR;
the two bitfield clears preserve it. The header's union exposes those fields
without changing the existing flags view or layout. Names are supported by
rwacore_ps2.h, while the Xbox bit widths follow 23F300's masks and the exact
23DF00 bytes. Repro: rwa_objdef_init_bitfields.py.

23DE20's counter is RwUInt16. A forward indexed loop produces the original
16-bit count test, typeIndex-based induction pointer, and widened decrementing
trip counter. Put tables inside each io branch: sharing one table pointer
across the branches changes the type-result and io-load scheduling. This
also recovers the static EAX argument ABI with an ordinary incoming pointer;
the earlier qualifier is unnecessary. Repro: rwa_objdef_defaults_recovery.py.

The creator retains the eight-byte memset established in the prior draft.
The release helpers retain their qualified parameter-table pointer reads;
original qualifiers there remain unknown. No compiler flags changed. All
rwaobjdef.c annotations match, and the full image gate remains byte-identical.
RWA has 57 unplaced functions after this group; RW has zero.

### RWA parameter-table setup resolved (2026-10-02)

_rwaObjDefSetupParams 23DD00 now matches 288 bytes / five relocations,
including seven NOP bytes. The allocating and supplied-table branches must
share a final return def: write them as if/else. An early allocation success
return changes register lifetimes throughout both validation loops. The
compiler reproduces the separate success epilogues from this shared source
return. Direct NULL returns also merge into the original shared failure tail;
no goto or qualifier is needed. The refresh callback declaration now agrees
with rwaparam.c's RwaParamTypeHandle* argument and return.

All existing rwaobjdef.c annotations retain their matches; the placement
gate passes with 18,111 pieces / 3,467,502 bytes and the original image SHA-1.
Repro: rwa_objdef_setup_return_trials.py. Historical setup trial loaders now
strip the placed body before appending their old forms. RWA remaining: 56.

### RWA search, destroy, listener and byte swap resolved (2026-10-02)

Six further functions are placed, reducing RWA to 50 (47 main, three tail);
RW remains zero. This supersedes the older near-miss entries for these addresses.

- Search 23D970: 176 bytes / two relocations. A separate root pointer handles
  fallback and the self callback; def's argument home is assigned root. Qualify
  only the callback parent read and parent-output read. Original qualifiers are
  unknown. The child-list head reuses the dead self argument home.
- Destroy 23DB90: 208 bytes / seven relocations. Load the first interface link
  before assigning the head pointer; retain a shared child link. Clear instances
  independently in free-list, pool and neither branches. Hoisting the clear swaps
  ESI/EDI throughout the body. Both container conversions use offsetof.
- Listener 23CC70/23D2A0/23D320: 208/96/96 bytes. Copy the complete original
  RW bavector.h cross-product macro, including all parentheses. Simplifying those
  expressions changes x87 scheduling. The initializer returns its listener pointer.
- Byte swap 241FD0: 128 bytes. The 16-bit path initializes from byte one and ORs
  a word load shifted by eight. In the 32-bit path, first shift/mask source reads
  stay direct; the right shift uses a saved value. This selects the original
  EAX/EDI lifetimes. Named byte-buffer pointers preserve exact byte indexing.

Production source is the reproducible final result in rwaobjdef.c, unit_23CC10.c
and unit_241F90.c; older drafts for these six are superseded. No compiler flags
changed. All six code commits and pushes used cmf.py. The full placement gate
passes with 18,117 pieces / 3,468,414 bytes and the original image SHA-1.

### RWA wave loading, spatialization and vector length resolved (2026-10-02)

23C490 now matches 624 bytes / 22 relocations. A RwaLLNode saved local with
individual prev/next/data reads recovers its original stack homes. Keep params
at function scope; store the computed dictionary address in state->unk00 before
assigning dict. The status 0x10 store precedes the second visitor call. Existing
Xbox fields represent the node, so this function needed no header changes.
All 29 rwawave.c annotations match.

23CD40 now matches 1,040 bytes / 49 relocations. The listener state pointer is
object+0x28; an anonymous-union header overlay preserves older direct members.
Copy complete RW Sub and Dot macros from bavector.h. Keep the at pointer between
rolloff and velocityScale declarations, and qualify both x reads in the first
subtraction. Their original qualifiers remain unknown; unqualified forms differ.
Clamps use their original branch/ternary shapes. The first argument is rwaInstance**,
matching the Xbox caller. All 24 listener annotations retain exact bytes.

242050 now matches 128 bytes / two relocations. The complete Dot macro's nested
parentheses immediately recover the y/x/z x87 schedule and z's parameter-home
spill. No qualifiers or signature change are needed. All five numeric helpers match.

Production source supersedes the drafts for these functions. All three functions
and the supporting listener header were pushed through cmf.py. Gate: 18,120 pieces
/ 3,470,206 bytes, SHA-1 d3ec0b089647081fd733b1bf53c63136f1a95387, byte-identical.
Remaining RWA: 47 (44 main plus three tail); RW: zero.

### RWA priority group and WMA defaults resolved (2026-10-02)

23E980 now matches 592 bytes / 21 relocations. Its dependent group also matches:
23E8E0 160/10, 23EE70 80/6, SoundStopper_Transition 64/3. Preserve original RW
Sub/Dot parentheses, initialize the integer min-distance copy before max-distance,
and share the unity-volume path between non-3D and near-distance cases. The weighted
gain path follows that shared assignment. Put the head insertion case before the
interior insertion case and use one final flags update: this restores EBX=1.
The previous priority remains an integer bit copy; a pointer comparison inline
recovers the scan's operand order. No new shared types or qualifiers were needed.
Production rwavoicemanager.c supersedes the priority drafts.

250C10 now matches 97 bytes / one relocation. Moving unk04=1 immediately after
unk00=0 keeps the zero and one values live simultaneously. Leave fileType=1 after
all zero stores. This fixes both EAX/ECX selection and caller stack cleanup;
the old eight-line near miss required no helper or qualifier. The declaration of
RwaStreamNodeGetParams was corrected to return rwaDecoder*. All 27 unit annotations
match. Production xbox/unit_250B20.c supersedes the old defaults drafts.

All five code commits and pushes used cmf.py. Gate: 18,125 pieces / 3,471,199 bytes,
original image SHA-1, byte-identical. RWA remaining: 42 (39 main, three tail).

### RWA PCM helper matched in scratch (2026-10-02; caller pending)

24A260 is now exact: 1,024 bytes / 29 relocations. From rwa_pcm_draft.c, remove
the function-wide i and declare RwUInt32 i immediately before each loop inside
its destination guard. This fixes the final load's base/index SIB byte. Ordinary
typed pointer locals and extra expression parentheses alone had no effect.
Repro currently build/tooltmp/root_pcm_scope_parens.py, rootpcmscope_1.
The helper remains unplaced because caller 24A740 determines its static register ABI.

Caller 24A740 remains unmatched. Keep the named allocation-size local from
rwa_pcm_caller_followup.c. Qualified incoming from copied to a normal local
reduces 54 to 48 normalized lines; two counts in an array reach 38 by forcing
the observed adjacent stack homes. This array is only a probe, not recovered
source evidence. Destination and to still use swapped EBP/EBX. Separate declaration
initializers, nested buffer/final scopes, qualifiers on other arguments/locals,
signed count types and shared-return allocation failure paths do not resolve it.
New repro scripts are build/tooltmp/root_pcm_caller_{scopes,access,local_access,
storage,flow}.py. Existing production sources were not changed for this pair.

Timer244980 new low-word alias and union probes reproduce its OR/SUB/ADD arithmetic
but still assign the start low word to ECX and a high zero to ESI, with an early
pop. Explicit start32 and reversed comparison variants also fail. Cache-open2450C0
comma-expression and split initializer/call-argument probes retain its18-line
baseline. No bodies or compiler changes were made for these two functions.

### RWA debug-reference batch resolved (2026-10-02)

Ten more functions were committed and pushed through cmf.py. All unit checks,
the source audit and the placement gate pass: 18,151 pieces / 3,486,335 bytes,
SHA-1 d3ec0b089647081fd733b1bf53c63136f1a95387, byte-identical. RWA remaining:
16 (14 main, two tail); RW remains zero. These results supersede older parked
entries for the addresses below.

- 247660: 1,520 bytes / 13 relocations. Debug _RwaStreamSourceReinterleave
  (rwad.dll 0x100B6FE1) recovers the pointer return, buffer direction, UInt16
  counters and UInt8 channel. The wide case copies two separate eight-byte pairs.
- 249160: 624/17. Debug __rwaStreamSourceCreate (0x100B29DA) recovers initialization
  order. A qualified unk174 reset preserves the final buffer-size load position;
  the original declaration is unknown. A typed union in rwaStreamSourceParams
  retains the existing values[15] layout. All 22 unit annotations match.
- 246ED0: 176/0. Initialize trackStart/kindStart/kindEnd before trackEnd;
  preserve the bit-31 mask ternary. The incoming UInt32 transports float bits.
  Debug _rwaStreamContainerCommandSetStreamGain is 0x100C04BA; all 50 unit
  annotations now match and are placed.
- 24CC80: 160/7. A separate incoming argument and typed obj local fixes the
  remaining register choice. Keep the case 4-6 else-if and case 7 independent
  conditions. Debug _RwaStreamFanOutStartExecute is 0x10067D61.
- 249D00: 496/2. Typed per-branch input/output arrays, separate indices and
  direct used reads recover channel duplication/averaging.
- 249EF0: 880/30. The helper 249C90 takes (from, srcSize, to), not the old
  declaration's order. This corrects argument-home reuse. Keep byte channels,
  separate previous/next arrays, scalar source index and the debug expression order.
- 24A260 and 24A740: 1,024/29 and 320/5. Per-destination loop index scopes fix
  the depth helper. The caller matches with the resampler definition in the same
  translation unit, with ordinary scalar locals and no new qualifiers.
- 24B260: 464/0. Debug GCN ADPCM decode (0x100B007E) uses flat coefficients,
  signed sample staging and an ordinary parity branch; byte-swap parentheses matter.
- 24BC50: 224/2. Debug VAG decode (0x100B13BB) separates persistent histories
  from per-block sample locals and decodes both nibbles explicitly.

All 25 wave-conversion unit annotations pass after these changes. Code and the
supporting rwaint.h changes were pushed only through cmf.py; compiler flags unchanged.

### RWA path, bitmap and format setup resolved (2026-10-02)

2494F0 now matches 688 bytes / 17 relocations. The debug DLL's
_RwaWaveConvFindPath (0x100AABAD) preserves a separate cache counter reused
for copying, a per-iteration validity flag, and increments/decrements the
recursive depth parameter. The Xbox version omits the debug DLL's unused
cache-step clearing loop. All 26 wave-conversion annotations pass.

2FD880 now matches 576 bytes / one relocation. _rwaAllocBitmapAlloc
(0x100BB929) uses direct bits[i] reads and an ordinary bit++ loop, naturally
unrolled by the compiler. Clamp run=count before breaking the outer loop;
use a failure-first final guard. All eight bitmap annotations are placed.

24D670 now matches 896 bytes / 23 relocations. _rwaStreamFormatCreateFromPack
(0x10069E30) shares UUID/name locals across header and marker loops. Cue loops
have separate inner indices and ID locals. Use direct format-field indexing
and final track-ID reads. All four stream-description annotations are placed.

All three were committed and pushed with cmf.py, with no header or compiler
changes. Audit: 723 files, zero problems. Full gate: 18,154 pieces / 3,488,495
bytes, SHA-1 d3ec0b089647081fd733b1bf53c63136f1a95387, byte-identical.
Remaining RWA: 13 (12 main, one tail). RW: zero.

### RWA encoding, renderer and Xbox wave batch resolved (2026-10-02)

Seven more functions are placed and pushed through cmf.py. Full gate: 18,161
pieces / 3,494,497 bytes, original SHA-1 d3ec0b089647081fd733b1bf53c63136f1a95387,
byte-identical. Audit: 723 files, zero problems. RWA remaining: six, all main.

- 24AB90 / 24BEF0: GCN ADPCM encoder and caller, 1,744/30 and 832/9. Debug
  _RwaWaveConvGCNADPCMEncode (0x100AF723) recovers signed histories, staged
  residuals and the 32767.0f residual scale. Keep the asymmetric parentheses
  around the first prediction product. Caller retains the existing byte swap.
  All 28 conversion annotations pass; VAG encoder group remains unplaced.
- 2FE290: renderer update, 1,264/23. A separate remaining counter walks played
  entries; preserve the source assignment order and positive silence branch.
  The old explicit obj fallback for current on underrun was an inference that
  changed register allocation. Leaving current unassigned on that path produces
  the exact Xbox bytes, including reuse of the argument's stack home. Later
  rwad.dll FinishExecute (0x10072BAC) clamps the count and assigns a valid entry.
  The source records this release behavior. All 27 unit annotations pass.
- 251210: Xbox WMA worker, 1,046/19. Keep next as the loop iterator and advance
  it after recovering obj/state. Initialize packetState, size, ok, looped,
  loopedAt and newPosition in that order; newPosition last restores EBX.
  All 28 WMA annotations pass. No qualifiers or helper changes were required.
- 24F410: Xbox wave setup, 967/24. Cache format before buffer work; initialize
  created before is3D. Preserve descriptor field order and a named play offset
  before the final fresh format pointer. The static mix helper 24ECC0 takes
  (state, is3D); its existing caller was adjusted and retains identical bytes.
  Dependent helpers 24EDC0 (116/5) and 24F350 (33/0) are placed with it.
  All 105 unit annotations pass; no new qualifiers or shared types.

Only 23E690, 24B510, 24BB00, 24C230, 24E710 and 2516E0 remain. VAG wrapper
24BB00 and caller 24C230 are exact in scratch but await their block encoder.


### RWA output destructor and WMA creator resolved (2026-10-02)

24E710 now matches 84 bytes / four relocations. A nonvolatile RwaUniqueID
zero temporary, with its flags-guarded empty cleanup, preserves the three dead
stores after stack cleanup. The source explicitly records that the original
temporary type and cleanup expression are unknown. All 37 unit annotations pass.

2516E0 now matches 1,535 bytes / 37 relocations. Put both header and content
description in one metadata scope lasting through the final return. Keep the
three strings in one array; initialize title pointer, three lengths, decoder
cache/string clears, then author/description pointers and unused fields. This
recovers all descriptor scheduling and the last header bitrate load. No new
qualifiers or helper functions were needed. All 29 unit annotations pass.
The decorated WmaCreateDecoderEx alias points to 0x3ABC81, verified from the
original call at 0x251991; all relocations are now resolved and checked.

Both functions and the supporting alias were pushed through cmf.py. Audit:
723 files, zero problems. Full gate: 18,163 pieces / 3,496,116 bytes, SHA-1
d3ec0b089647081fd733b1bf53c63136f1a95387, byte-identical. RWA remaining: four
(all main), RW: zero. Creator 23E690 still reverses two count loads; VAG block
24B510 still reverses the first final-pass prediction products. Its wrapper
24BB00 and caller 24C230 are exact in scratch and await that block.


### RWA completion: creator and VAG group resolved (2026-10-02)

23E690 matches 416 bytes / 22 relocations. Reuse the final size local for the
initial output-interface input count, form outputSize from that count and the
ordinary noOutputs read, then overwrite size with the allocation total. This
fixes the first two load instructions without a helper or extra operation.
The voice-interface noOutputs read retains its qualified access; the original
qualification remains unknown and is recorded in the source.

24B510 matches 1,520 bytes / 14 relocations. Preserve selectedFilter for the
coefficient/residual rows, introduce both coefficient pointer locals inside the
final loop, and reuse the original filter local for the packed header byte.
These ordinary local lifetimes resolve both the first x87 product order and
header CL/DL allocation. Wrappers 24BB00 (336/1) and 24C230 (816/8) are placed
with it. All 31 conversion annotations pass. No new types, helpers, qualifiers,
assembly or compiler settings were needed for the VAG group.

Final code commits: 7a16949e4, 288b021b2, 1e8125f0a, 04992f76f. Every code
push used cmf.py. Final gate: 18,167 pieces / 3,499,204 bytes, original SHA-1
d3ec0b089647081fd733b1bf53c63136f1a95387, BYTE-IDENTICAL / PASS. Audit: 723
files, zero problems. Split-minus-placement count: 762 of 762 RWA ranges
placed, zero unplaced in both 23B750-252000 and 2FD5D0-2FEC60. RW: zero left.

RWA is finished. Work stopped at the owner's requested boundary; earlier
RWA near-miss notes and draft status counts are historical.

## Bink C restoration: DCT, 2026-10-02

All five generated DCT transcriptions are now C in src/bink/dct.c, with the
existing VC7.1 flags: fastidct8x8 (34C400, 811/0), fastidct8x8d (34C730,
924/0), FastIDCT8x8 (34CAD0, 38/2), FastIDCT8x8d (34CB00, 35/2), and
FastmIDCT8x8WithMotion (34CB30, 912/1), bytes/relocations respectively.
The generated dct_asm.asm is retained as a history note with no code.
The supplied library proves the two 4096-byte quantization tables at 3EEF40
and 3EFF60 byte-for-byte. This corrects the old 34CAD0 name: it uses
ifiquantlevels8, so it is FastIDCT8x8, not the library's FastmIDCT8x8.
The expander's call names and aliases now record that evidence.


## Bink C restoration: audio decoder, 2026-10-02

Six audio functions are restored in src/bink/binkacd.c with the existing
VC7.1 flags: quanttos16s (344AB0, 78/0), quanttos16chans2 (344B00, 128/0),
read_rle_samples (344B80, 752/3), Unquant (344E70, 948/13),
BinkAudioDecompress (345460, 205/1), and Close (345530, 5/1),
bytes/relocations. Their C matches hold with Open left in binkacd_asm.asm.
All four tables (16, 100, 1024, and 96 bytes) are byte-identical to the image.
The run-length reader uses a dynamic right-shift mask and branch-local output
postincrements. Unquant retains quants[26], the signed packed-float helper,
and ordinary loops that VC7.1 unrolls. A small copyoverlap helper with four
scalar arguments preserves the wrapper's field-load order. Open's remaining
mismatch is register allocation of the cached flags bit across pushmalloc;
its saved draft remains in build/tooltmp/binkaudioagent_best.c.


## Bink C restoration: YUV helpers and wrappers, 2026-10-02

Fourteen YUV functions are restored in yuv.cpp: checkzoombufs (34A2B0,
74 bytes / 8 relocations), setdbls (34A7B0, 141/19), all six ordinary format
wrappers (80/2 each except YUY2 126/2), and all six masked wrappers (91/2).
All 120 annotated functions match. The generic setup/blitters/init C drafts
remain unannotated to retain the original compiler context and calling
conventions; their four assembly placements remain while matching continues.
Preserve the original destination pitch for S.out0, and reuse ywidth for the
row skip after copying its working width. Those lifetimes recover all six
ordinary wrapper ABIs. The original low-level checkrdtsc assembly is retained.


## Bink C restoration: six expander readers, 2026-10-02

expand.c now restores CheckReadRLEHuff4Bundle (3468E0, 635 bytes / 1
relocation), CheckReadHuff8Bundle (346B60, 716/0), NewCheckReadHuff8Bundle
(346E30, 703/0), CheckReadHuff4Bundle (3470F0, 513/0),
CheckReadHuff4SBundle (347500, 634/0), and CheckReadDelta16Bundle
(347780, 797/0). Both existing annotations also remain exact.

The cross-word bit-read macro caches the word, shifts that temporary, then
updates bitlen and cur before assigning bits. A separate output cursor in
the decode branch and an unsigned byte before signed Huffman conversion
recover the other reader schedules. Delta uses S16 delta and the original
signed-first branch. Its radmemset16 inline assembly is genuine RAD code,
verified against the named helper in the supplied library; it is retained.
The four-byte RLE table {4,8,12,32} matches the image. Unmatched merge-sort,
table reader, and pair-reader C bodies remain unannotated for compiler
context. Five expander assembly placements remain while matching continues.


## Bink C restoration: ExpandBink, 2026-10-02

ExpandBink (349A10) is restored in C: 398 bytes / 5 relocations. All eight
existing expander annotations also remain exact. The original Plane argument
order puts data and mask after flags, with skipped last; data and mask retain
the EAX/EDX custom convention. In the chroma setup, advance both Y cursors,
round width, halve yheight, then round height. This restores the exact caller.
The pending Plane C body is retained without a match annotation for compiler
context, and its original assembly placement remains active. Its four inline
copy primitives match genuine RAD assembly in the reference library. Four
expander transcriptions remain. Overall 34 of 56 C/C++ restorations are done.


## Bink C restoration: eight player routines, 2026-10-02

bpopmalloc (341480, 28 bytes / 2 relocations), dosilence (3414E0, 140/0),
GotoFrame (341860, 214/3), high1secrate (341990, 164/0), BinkWait
(3433C0, 499/8), BinkSetSoundOnOff (343730, 307/5), BinkDoFrame
(3438B0, 1497/19), and BinkNextFrame (343E90, 413/13) are restored in C.
All 30 player annotations match. binkread_asm.asm is now empty and retained
as history. Only BinkOpen remains a naked transcription in this unit. Its
near-matching C body is retained unannotated as BinkOpen_pending to preserve
the original helper call graph. The pending assembly accesses cb_bink_IO
through a separate alias: marking the original C static as assembly-used
changes BinkNextFrame's increment scheduling and loop alignment.

BinkWait reuses diff for adjustread. BinkDoFrame reuses the address-taken amt
for the frame-rate denominator. BinkSetSoundOnOff keeps callback result and
three independent outcome tests. These restore the original callers too.
Overall 42 of 56 restorations are complete; 14 temporary assembly routines
remain (BinkOpen, pushmalloc, audio Open, four expander, four YUV, three
bit-plane). All code is committed and pushed through tools/cmf.py.


## Bink C restoration: ReadHuffTable, 2026-10-02

ReadHuffTable (3461E0) now matches in C: 1673 bytes / 15 relocations.
All nine existing annotations remain exact. Mask each VarBitsPeek branch
before the merge call; the final output counter is initialized before the
separate cursor declaration. The pending merge-sort retains the original
custom ABI used by this matched caller. Its C body still needs matching.
All macros are defined before the pending helpers and match annotations.
Three expander assembly placements remain: merge-sort, pair reader, Plane.
Overall 43 of 56 restorations are complete, with 13 remaining.


## Bink C restoration: ReadBPLossyWithMotion, 2026-10-02

ReadBPLossyWithMotion (34DCB0) matches in C: 813 bytes / one verified
call relocation to readlossy (34D7D0). The coefficient storage is an S8
array, cleared as the first eight bytes followed by the remaining 56.
Using a U32/U64 backing array changes register allocation. Each output
row adds the matching row of the motion block to the reordered residuals.
44 of 56 restorations are complete; 12 remain (two naked, ten MASM).


## Bink C restoration: audio Open, 2026-10-02

BinkAudioDecompressOpen (345230) matches in C: 547 bytes / 15 relocations.
All seven audio decoder functions are now restored. Reuse i for the band
search and final band initialization, assigning bands after the first loop.
Keep the input frequency formal and transform rate local distinct; that
recovers the original temporary for integer-to-float conversion. The field
initialization order preserves the original scheduling and conditional EDI
save around initialization. binkacd_asm.asm remains as an empty history file.
45 of 56 restorations are complete; 11 remain (two naked, nine MASM).


## Bink C restoration: pushmalloc, 2026-10-02

pushmalloc (258B20) matches in ordinary C: 213 bytes / 17 relocations.
All three pushed-allocation routines match with the existing VC7.1 flags.
Mask the total and request cache-line indices separately before subtracting,
then mask their difference and convert back to bytes. VC7.1 removes the
redundant inner masks while recovering the original ESI/EDI assignments.
The naked body and its unused alias declarations are retired.
46 of 56 restorations are complete; ten remain (BinkOpen and nine MASM).


## Bink C restoration: ReadBPLossless, 2026-10-02

ReadBPLossless (34CEC0) matches in C: 2308 bytes / 10 relocations,
including 33 bytes of jump tables. All three bitplane.c annotations match.
The bit refill uses a distinct fetched-word local; the final plane has its
own coefficient-index local. Both switches explicitly send their default
case to the shared node increment. Keep the 64 U16 coefficients and the
used U32 bit result together in BINKLOSSLESSWORK; this reproduces the
original stack allocation without unused padding or a larger array. The
workspace grouping is reconstructed from the compiler result, not a claim
that the original private type name is known.
47 of 56 restorations are complete; 9 remain (one naked, eight MASM).


## Bink C restoration: ExpandPlane, 2026-10-02

ExpandPlane (347B40) matches in C: 7876 bytes / 118 verified relocations,
including 68 bytes of jump tables. All eleven expand.c annotations match.
The scaled solid fill must be a count-up loop of eight two-row iterations:
compute the following row before storing the current row. VC7.1 fully
unrolls this into the target instruction sequence; explicitly repeating
all sixteen rows leaves one address-materialization scheduling difference.
RLE one-bit reads use a distinct fetched-word local. Direct color reads,
two-row pointer updates, and the common row footer preserve the remaining
register lifetimes. Original assembly copy primitives remain unchanged.
The bit-length, RLE-pattern and mask table aliases have each been checked
against the original image; they are not approximate relocation matches.
48 of 56 restorations are complete; 8 remain (one naked, seven MASM).


## Bink C restoration: masked YUV blitter, 2026-10-02

YUV_blit_mask (34B150) matches in C++: 2484 bytes / 144 relocations.
All 121 yuv.cpp annotations pass with production normal/setup/init context
retained. Group the used row pointer, width, skips and end coordinates in
BINKYUVMASKWORK. Its layout restores the original stack homes and final LEA
encoding without unused padding. Initialize lastx=x+31 only inside the
guarded 32-pixel loop. secondmask tracks m+maskextra, while maskbias keeps
first-row second-byte access relative to that pointer. Retain the direct
m[maskextra+1] access for the second row's second byte. These are inferred
private source names; the original assembly and all relocations are exact.
49 of 56 restorations are complete; 7 remain (one naked, six MASM).


## M7: the seven zero dwords after the kernel thunk table, 2026-10-04

The image's kernel thunk table ends with its terminator at 0x3CD560; seven zero dwords follow,
and the link's debug directory (CodeView) starts at 0x3CD580. Our link puts the directory right
after the terminator, 16-aligned (0x3CD570), so the original import area was 13-28 bytes longer
and zero in the image. Tried through imagebld 5849.4, none of which gives zeros there: kernel
imports by name (IM1013, refused), an ordinal the kernel lacks (written as is), a second kernel
module spelling (XBOXKRNL.EXE: its table first, written as is), xbdm imports (a non-kernel
import directory; the image's is 0), an import descriptor with no imports (also a non-kernel
directory), and /DEBUGTYPE:CV,FIXUP (a second debug entry, another layout). Nothing in the image
refers to 0x3CD564-0x3CD57F. The M7 link holds the room with seven unused kernel imports
(m7probe.py M7KTHUNKS_EXTRA), the XBE's only remaining difference after m7retail.py.
Also tried since: empty import descriptors (link discards them, LNK4089), an import used only
by code /OPT:REF drops (no slot), /DEBUGTYPE:CV,COFF (ignored), a plain .rdata fill (the debug
directory stays first in its group), /MERGE:.idata=.rdata (LNK1272). Owner's decision
(2026-10-04): m7retail.py zeroes the seven filler slots, checked to be exactly those imports, as a
noted unexplained difference (--no-import-pad leaves them); the SHA-1 then equals the original's.
