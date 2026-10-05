# Handoff: the matching decompilation of `Game_XboxMultiplayer.xbe`

**BINK C/C++ RESTORATION ACTIVE - 2026-10-02.** The owner now wants the
Bink functions that were originally C/C++ restored from the temporary assembly
transcriptions. This supersedes the earlier "asm the rest of bink" permission.
Keep genuine original assembly (the library's MASM units and original low-level
RAD helpers). Use the existing VC7.1 flags. All code pushes use tools/cmf.py.
RADTimerRead (344990) is restored in C: 276 bytes / 28 relocations. Its elapsed
subtraction belongs inside the drift-correction branch. DirectSound Open
(345E40) is also restored in C++: 642 bytes / 21 relocations, all 17 unit
annotations exact. Remaining work starts from BinkOpen (one naked function) plus
6 generated MASM transcriptions. All pushed-allocation functions are now C
(pushmalloc: 213 bytes / 17 relocations). ReadBPLossless is restored in C (2308 bytes / 10 relocations).
ReadBPLossyWithMotion is restored in C (813 bytes / one relocation). ReadHuffTable is restored in C (1673 bytes /
15 relocations). Eight reader routines are now restored in C;
only BinkOpen remains naked in the player. ExpandPlane now matches in C (7876 bytes / 118 relocations), retaining
its original inline copy primitives. ExpandBink matches in C (398 bytes /
5 relocations). Six expander bundle readers now match
in C, including the original inline radmemset16 helper. The generic masked YUV blitter (2484 bytes / 144 relocations) and fourteen
YUV helpers/wrappers now match in C++; only setup, the normal generic
blitter, and init remain in MASM. All seven audio decoder functions are restored
in binkacd.c (Open: 547 bytes / 15 relocations). All five DCT functions are restored in
dct.c; library table provenance corrects 34CAD0 to FastIDCT8x8. Agents are
working on player, expander and YUV drafts under build/tooltmp; root owns
bit-plane restoration and integration.

**RWA COMPLETE.** All 762 split ranges in the main and tail RWA regions are
placed; zero RWA functions remain. RW also has zero tracked functions left.
Final RWA gate: 18,167 pieces / 3,499,204 bytes, SHA-1
`d3ec0b089647081fd733b1bf53c63136f1a95387`, byte-identical PASS.
Historical parked RWA notes below are superseded by that result.

This document is written for an agent that has **never seen this project** and that should be
able to continue the work **without asking anyone anything**. It is long on purpose. Read all of
it once before touching anything. When this document and your instincts disagree, follow this
document: almost every rule here exists because breaking it once cost hours.

Status as of **2026-10-01** (end of the session that wrote this).

RwStreamSkip now matches with VC7.1: 292 bytes, 13 relocations and 18
bytes of jump tables. Recover the file-branch retVal and single return
from Godfather debug 0xBB6760; this fixes the memory-branch LEA encoding.
The skin node now also matches: 986 bytes and 36 relocations. Combine
shader-constant pointer advancement with indexed bone batches, and pass
resEntry + 1 directly to the render callback (Godfather debug 0x11568D0).
The default instancer now matches too (669 bytes, 18 relocations):
Godfather debug 0xB7B540 records a signed int size local. Both position
paths assign that local before the common pointer advance.
The delta-morph helper and callback now also match: 109 bytes and
5,740 bytes respectively (callback: 93 relocations, 160 jump-table bytes).
Share currentBlock, j, l and target/RLE locals across the attribute passes;
keep k, m and maxl inside their passes. The tracked RW work list is complete.
Continue with the parked game functions, then RenderWare Audio.

Custom entity setup `sub_9B0B0` now matches (520 bytes, 13 relocations).
Keep only the two setter values as named locals; the handle struct return,
zero_v3d and script getters then occupy the original remaining slots.
All functions in unit_09AD40.cpp are now matched.

Distance Scheduler `sub_35AA0`, `sub_35FD0` and `sub_362F0` also match
(369 / 674 / 675 bytes, including the first function's 32-byte jump table).
Named handle copies and receiver pointers recover the grouped local slots;
the filter retains inline serial getters and short-circuit evaluation.
All functions in unit_034FA0.cpp are now matched.

Fire-and-movement selection `sub_39AA0` and enrollment `sub_3A450` now
match too (1,039 / 849 bytes, plus the selection's cleanup/EH pieces).
Use the handle-returning getter in selection and named handle/receiver
copies in enrollment. All functions in unit_0390D0.cpp are now matched.

CDebugScript attributes `sub_43200` now match (586 bytes including the
56-byte jump table, 48 relocations). Command 11 uses GetCommandData into
a named local and the documented two-load compiled-out-check effect.
All functions in unit_042F40.cpp are now matched.

AIManeuverManager factory `sub_3CE20` and update `sub_3D150` now match
(643 / 388 bytes, plus factory cleanup/EH pieces). A small registration
inline defers its union temporary until after the pool-size getter; the
update uses named handle copies. All unit_03CA10.cpp functions now match.

Projectile-generator factories `sub_122410` and `sub_1224F0` now match
(213 bytes and 12 relocations each, plus shared cleanup/EH). The inline
id getter returns the existing index/serial record from a typed member,
placing its temporary before the list getter's inline local. All functions
in unit_11EE20.cpp are now matched.

Squad factory `sub_3EEE0` now matches (194 bytes, 14 relocations, plus
cleanup/EH). A normal list getter places the head copy correctly; global
placement new/delete are declaration-only here to retain the original
calls. All functions in unit_03DF30.cpp are now matched.

Pause-menu loader `sub_21BD60` now matches (1,143 bytes including the
32-byte jump table, 55 relocations, plus cleanup/EH). Restore ordinary
local scopes and keep one unused inline slot inside the map branch;
the original number conversion calls atoi. All unit_21A5E0.cpp functions
now match, with no look-constructor or shared-header change.

Objective hint `sub_1C5350` now matches (933 bytes, 50 relocations, plus
88-byte cleanup and 10-byte handler). Two existing text diagnostics and
eight unused inline locals in a separate final-return scope preserve the
original 0x140 frame and earlier temporary placement. Exact discarded
expressions remain unknown; the source records this. All functions in
unit_1C3D20.cpp are now matched.

CCESS pick `sub_8AFF0` now matches (392 bytes, one relocation).
The inclusive-range count expression `(count - 1) + 1` preserves the
ECX divisor load. Restored local-name order also reproduces its frame.
Production unit_08AB60.cpp supersedes the saved draft.

SplinePath destructor `sub_BA030` now matches (73 bytes, six relocations),
with its 8-byte unwind and 10-byte handler. VC7.1 `/EHa` for unit_0B9EA0
preserves EH state 0 around the empty body; all 15 existing annotations
also match. The earlier `/EHsc` source trials are superseded.

Six remaining shutdown thunks are now matched: the five registrar exits at
`30DF60/30DF70/30DF80/30DF90/30E0C0` and CMemHandler's singleton exit at `30E680`.
Their existing compiled bodies were missing placement annotations. Each was
identified through its initializer's atexit argument and receiver address.
The two local string exits at `30EA80/30EA90` now also match (15 bytes each).
They are now generated naturally in `unit_1A8B20.cpp`: the local strings
are type_1A5EA0, as is the return from sub_E3970. The separate callback bodies
have been retired; `unit_30EA80.cpp` is retained as a history note.
All eight exits are placed.

Scoreboard showing `sub_21FB60` now matches (1,909 bytes, 88 relocations),
plus 156-byte cleanup and 10-byte EH-handler pieces. A free team-count
accessor removes the misplaced receiver-expansion slots. Seven no-code
text diagnostics and two unused inline locals at the branch end preserve
the remaining inline budget and frame. `sub_1C5350` is now declared to
return type_1CB670; its own body now also matches (see above).

Localization lookup `sub_1CAF30` now matches (208 bytes, eight relocations).
Its result and sub_E3970's are type_1A5EA0. Constructor sub_1CB6B0 belongs to
type_1CB670 and initializes that base directly from the returned object.
All existing localization callers retain their matches.

Packet copy constructors `sub_1D43B0`/`sub_1D4320` now match (138/134 bytes).
Const and mutable mask-copy overloads preserve their different register steps;
the voice helper selects the mutable overload. `sub_1D4290` now also
matches (144 bytes, two relocations), placed from unit_1D4290.cpp.
The packet-only instantiation avoids the HUD header's unrelated $S1
singleton guard, which shifted its generated array-loop local names.

Voice update `sub_1AA380` now matches (1,962 bytes, 14 relocations).
A checked value-returning mask copy reproduces the setter argument's
construction without changing the shared mask copy constructor.
Only `sub_1AB440` remains binary in the multiplayer manager's main range.

The kill-cam state change `sub_1ABC00` and respawn `sub_1AED80` now match.
Both need a checked network-player accessor: its index check preserves the
register step between the interface conversion and argument push. See
`game/netplayer.h` and `unit_1A8B20.cpp` (547/865 bytes, 12/22 relocations).

The network message decoder `sub_1A8990` now matches, including its EH
pieces: the original buffer is 128 bytes, correcting the draft's frame.
`unit_1A6140.cpp` has no remaining parked function bodies.

Game follow-up: `sub_1A65B0` and `sub_1A7480` now match (1,977/1,490
bytes, 12/32 relocations). Both use the recovered const-reference angle
conversion and its declined normalization inline. The following update also
keeps both interpolation calls' declined-inline stack slots.
See `include/game/netplayer.h` and `src/recovered/unit_1A6140.cpp`.

Latest splitter follow-up: constructor `sub_24CFF0` is now matched (448 bytes,
six relocations), with a typed allocation inline and cached callback pointer.
See `docs/questions.md` for the remaining status/read attempts and trial paths.

Symbol-table add/remove `244650`/`244690` now match: the old void return
was wrong. The reference header and final EAX both support returning table.
Check reference declarations before tuning register allocation in old drafts.

Core callback `23E680` now matches too: it returns allocated storage from
an advancing byte cursor. The old void accumulator draft hid that return;
the caller chain through `23F9F0`/`243FF0` confirms the pointer semantics.

Source creation callback `241230` now has a two-line near miss in
`docs/drafts/rwa_streamsource_followup.c`: argument-home reuse fixes the
extra stack slot; only final EAX/EDI reload order remains. Still parked.

Source pump `248410` and request helper `2475D0` now match (416 bytes).
Preserving the second look-ahead index read fixes the pump; its static
helper matches with the caller present and the original EAX argument ABI.

Read loop `248520` has a new parked draft, `rwa_source_read_followup.c`:
137 to 103 normalized diff lines after control-flow corrections. Remaining
work includes EBX save placement and semaphore-release exit layout.

Wrap-count `247F20` has a new parked draft, `rwa_source_wrap_followup.c`
(89 to 61 normalized lines). Register selection and stack homes remain;
reproduction paths and the exact remaining differences are in questions.md.

Source setup `249160` is now a two-line near miss in
`rwa_source_setup_followup.c`: only the buffer-size load position differs.
Moving it with a local changes later registers; see the saved setup trials.

Command entry initializer `246D70` now matches (256 bytes). A typed
per-entry inline preserves store grouping and fixes register allocation.
The command value setter `246ED0` remains parked.

IMA sample decoder `24BDE0` now matches (128 bytes, two relocations).
Direct predictor updates and post-store index tests fix the old draft;
the encoder `24BD30` remains parked.

PCM follow-up: 24A260 still differs by one address-encoding byte;
24A740 has an improved parked caller draft (58 to 54 normalized lines).
See questions.md and rwa_pcm_*_trials.py for reproducible attempts.

RW skin vertex-format shader 2D4440 now matches (688 bytes, 42 relocations).
A typed tail inline fixes the final index scaling; its historical drafts
are superseded by src/rw/plugin/skin2/xbox/skinxboxformat.c.

RW MatrixOrthoNormalize 2A48C0 now matches (1,468 bytes, four relocations).
Local vector-macro variants preserve the observed component read order;
all other functions in bamatrix.c retain their matches.

RW compressed BNT 2DE0F0 now matches (1,459 bytes, 13 relocations).
Ordinary BNT 2DDB50 now also matches (1,425 bytes, 10 relocations).
A two-vector-pointer z-component inline preserves both normal reads.
All 27 annotated functions in xbvtxfmt.c match; prior BNT drafts are superseded.

Companion documents (read them when this file points at them):

| File | What it holds |
|---|---|
| `docs/PLAN.md` | The project's rules and milestones (M0–M7) plus "Amendments" (owner decisions). The goal is defined there. |
| `docs/units.md` | One section per source unit: what it holds, what is matched, what is "still binary" and why. |
| `docs/questions.md` | Open questions for the owner, every near miss with what was tried, and resolved decisions. |
| `docs/toolchain.md` | Compiler-behaviour findings with their evidence (the "why" behind tricks). |
| `docs/rw-differences.md` | Every place where the image's RenderWare differs from the 3.7.2 source tree. |
| `docs/libraries.md` | Which library code is linked/transcribed and why. |
| `docs/drafts/` | Drafts of functions that do not match yet (reference only, never compiled). |
| `docs/session-memory/` | One file per lesson learned by earlier sessions (start with `MEMORY.md`). |

---

## 0. The first 30 minutes (do exactly this)

1. `cd C:/codfh-match` (the repository root; every command below runs from here).
2. `git status --short` — expect only `?? src/recovered/_ln.cxx` and `?? xdklib/` (both must stay
   untracked; never `git add` them). If anything else is modified, a previous session died
   mid-edit: look at the diff, and if it is not a finished, matching change, `git checkout -- FILE`.
3. `git log --oneline -5` and `git fetch && git status` — you must be on `master`, level with
   `origin/master`.
4. Run the full gate once so you know the tree is green:
   ```
   python tools/build.py > build/tooltmp/full.txt 2>&1
   grep -n "== PASS\|== FAIL\|AUDIT\|^DIFF" build/tooltmp/full.txt | tail
   ```
   You must see `== PASS`. (It takes about a minute. Never judge it through `| tail` alone: the
   pipe hides the exit status; always grep the saved log.)
5. `python tools/session/left.py | tail -30` — the list of functions that are still not placed.
6. Read section 9 (work list) and pick the first item in the owner's priority order:
   **RenderWare functions first, then game functions, then RenderWare Audio.**

---

## 1. The goal and the owner's standing instructions (verbatim where quoted)

- **Goal:** "You are not finished until this entire document is done. @docs/PLAN.md".
  Every function of the XBE must be rebuilt **byte-identical**. The game, the RenderWare Studio
  runtime (RWS) and the RenderWare code built into the game are *decompiled* (C/C++ source);
  RenderWare Audio (RWA) and Bink are decompiled; XDK code is *linked* (real XDK libraries, or
  stand-ins repacked from the image).
- **Run unattended.** Do not stop to ask. Questions for the owner go into `docs/questions.md`
  under "Open" with a *Meanwhile:* line saying what you did instead.
- **Current stopping condition (owner, 2026-10-02):** "Stop once you have finished all RWA functions."
  Finish the remaining RWA functions, verify their placements and the full image, then stop.
- **Priority (owner, 2026-10-01):** "focus on the renderware functions, then game funcs, then rw
  audio".
- **"finish each one you encounter - no skipping"** and "work faster". In practice: give each
  function a real attempt (draft, compile, diff, iterate). If it is genuinely stuck after a solid
  attempt, park it *properly* (section 6.9) and move on; do not leave half-edited files.
- **"dont edit the ida db - if a function exists that isnt picked up by ida, make note of it and
  create the function in code."** IDA is read-only. Never call IDA tools that write (rename,
  set_type, define_func, patch, make_data, set_comments, declare_type, ...). Never run
  `tools/export_symbols.py` or `tools/splits.py` (they regenerate config from IDA and would wipe
  hand edits). Functions IDA missed are added to `config/symbols.txt` / `config/splits.txt` by hand
  (`tools/addfn.py`).
- **"no more rm please"** — never run `rm` (or `del`, `Remove-Item`) on anything, not even scratch
  files. Use fresh, unique file names instead of deleting old ones.
- **Inline assembly:** "If a Renderware function originally used __asm, that is acceptable. Do
  not invent __asm that did not exist in Renderware." and "for the remaining items, no __asm
  unless the function originally had it." So: `__asm` only where the original code had it (see
  6.7). Bink is the one exception ("asm the rest of bink", already done).
- **"snetgamep shoulsnt be skipped"** — `sNetGameEP.cpp` is in scope (it is fully matched now).
- **Commits:** one commit per function (or per unit for transcriptions), made with
  `tools/cmf.py`. Messages end with the attribution line the harness gives you (this session used
  `Co-Authored-By: Claude Opus 5.5 <noreply@anthropic.com>`). **Push to origin after every
  commit.** The build must say `== PASS` before every commit.
- **Code pushes (owner reminder, 2026-10-02):** all code pushes must use `cmf.py`,
  including supporting header changes. Stage an explicit supporting header before
  cmf's header commit when it is outside the harness's automatic paths.
- **No unmatched code in committed sources** (owner rule). A function that does not match stays
  *binary* (not in the source), with its draft in `docs/drafts/`. (A few old "Not yet matched"
  bodies still exist in committed units, e.g. `sub_1AB440` in
  `unit_1A8B20.cpp`; do not add new ones; remove them by
  matching them.)
- **Names need evidence** (PLAN Rule 3). See 6.3.
- Keep `docs/units.md`, `docs/questions.md`, `docs/rw-differences.md`, `docs/libraries.md` current
  as you work (same commit as the change, through `cmf.py -m`).

---

## 2. Environment

| Thing | Where / what |
|---|---|
| Repository | `C:\codfh-match` (git, branch `master`, remote `origin`) |
| Reference image | `orig/Game_XboxMultiplayer.xbe` (never modify) |
| Shells | Git Bash (POSIX) and PowerShell 5.1. Python is `python` (3.14). |
| Compiler (main) | VC7.1 13.10.3077: `C:\XDK\xbox\bin\vc71\CL.Exe` (game, RW, Bink, RWA `xbox/` layer) |
| Compiler (old) | VC7.0 13.00.9466: `C:\XDK\xbox\bin\vc70`, selected by the pseudo-flag `/compiler:vc70` in `config/flags.txt` (RWA core, RW `tool/fsyst`). No other compiler builds exist on this machine (checked 2026-10-01: the 4627 and 5849 SDKs in Downloads carry the same two). |
| Assembler | `ml.exe` 14.51 for `.asm` units |
| XDK | `C:\XDK` (headers/libs). XDK 5849 libraries from `C:\Users\Jordan\Downloads\2003-12 - 5849 - RecoveryISO+EXE, SDK (stripped)\...\XDKSetup5849` sometimes match better; copies live in `xdklib/` (untracked). |
| RenderWare source | `D:\RW_372_src` (RW 3.7.2 tree). The image's RW is **3.6**; we copy 3.7.2 files into `src/rw/` and edit them to the image. |
| IDA (our game) | MCP tools `mcp__ida-pro-mcp__*` (port 13337). **Read-only use only.** |
| IDA (Godfather) | The Godfather (Xbox, same RW era) with PDB: port **13339** = release build, **13340** = DEBUG build. Reach them with `python tools/gf.py TOOL 'JSON' PORT` (read-only whitelist) and `tools/gfpy.py`. Use for RenderWare Xbox code shapes and real local names. |
| Scratch space | Use your session's scratchpad dir (given by the harness) or `build/tooltmp/` (ignored by git). |

Git Bash pitfalls:
- Heredocs **eat backslashes** (`\n`, `\\`). Any file content or Python with backslashes must be
  written with the Write tool, not `cat <<EOF` / `python - <<EOF`.
- Git Bash turns arguments like `/O2` into paths when passing them to Python: set
  `MSYS_NO_PATHCONV=1` if you pass compiler flags on a command line.
- `sed -i` with `\n` or quotes is fragile; prefer a small Python script written with Write.

---

## 3. Repository layout and file formats

| Path | What |
|---|---|
| `config/splits.txt` | Every placement range: `0xSTART 0xEND .section name` (IDA function starts plus `chunk_of_X` EH funclet ranges). |
| `config/symbols.txt` | IDA names: `0xADDR kind size section name` (kind = function/data). |
| `config/chunks.txt` | Tail chunks: `0xSTART SIZE OWNER`. |
| `config/aliases.txt` | `objectSymbol  0xADDR  evidence text` — tells the linker that an object-file name lives at an image address (ICF-folded copies, library functions, globals, vtables `??_7type_X@@6B@`). |
| `config/compiled.txt` | `0xADDR build/src/....obj SYMBOL` — one row per placed compiled piece. **Managed by cmf.py**; edit by hand only when told below. |
| `config/flags.txt` | `glob: flags` — compiler flags per source glob, **first matching rule wins** (specific rules above general ones). |
| `src/recovered/unit_XXXXXX.cpp` | Game units named by their start address. |
| `src/Source/...`, `src/COD/...` | Game units whose original path is known from `__FILE__` strings. |
| `src/rws/` | RenderWare Studio runtime. |
| `src/rw/` | RenderWare 3.6 as built into the game (C). |
| `src/rwa/` | RenderWare Audio (VC7.0 core, VC7.1 `xbox/` layer). |
| `src/bink/` | Bink (C, MASM, and `*_asm.asm` transcriptions). |
| `src/xdk/standin_*.asm` | XDK stand-ins repacked from the image. |
| `include/` | Shared headers: `game/*.h`, `types/type_XXXXXX.h`, `rw/sdk/` (RenderWare headers). |
| `tools/` | Build/match/commit tools (section 5). |
| `tools/session/` | Analysis helpers written by sessions (section 5.3). |
| `build/` | Objects and tool work files (`build/tooltmp/`). Not committed. |

Example rows:
```
config/splits.txt    0x001ACBA0 0x001ACEB0 .text      sub_1ACBA0
config/splits.txt    0x00302AE0 0x00302B00 .text      chunk_of_1ACBA0
config/symbols.txt   0x00302AEB data     0x0      .text      SEH_1ACBA0
config/compiled.txt  0x001ACBA0 build/src/recovered/unit_1A8B20.obj ?sub_1ACBA0@@YAXHPAUtype_3DA434@@@Z
config/aliases.txt   ___security_cookie   0x00435810  libcmt.lib seccook.obj .data ... identical to the image
config/flags.txt     src/*: /c /nologo /Od /Ob1 /Gy /GS /EHsc /GR- /G6 /GF /MT /W3 /Zi /D_XBOX /DNDEBUG
```

Compiler flags in short: **game** `/Od /Ob1 /GS /Zi` (unoptimized; register *rotation* rules apply);
**RenderWare** `/O2 /Ob2 /G6 /Gy /arch:SSE` with RW include dirs (optimized; register *allocation*
rules apply); **RWA** `/compiler:vc70 /O2 /Ob1` (core) and `/Og /Oi /Ot /Oy /Ob1` (xbox layer);
**Bink** `/O2 /QIfist`.

---

## 4. Building, matching, committing

### 4.1 Commands

```
python tools/build_sources.py SRC              # compile ONE unit and check every "// match:" line in it
python tools/match.py OBJ SYMBOL 0xADDR        # one function: OK identical / DIFF first differing byte
python tools/audit_sources.py                  # source conventions (1 s; run before every commit)
python tools/build.py > LOG 2>&1               # the full gate; grep LOG for "== PASS"
python tools/ibuild.py                         # same gate, incremental (what cmf uses)
CMUNIT=unit_1A8B20 python tools/cmf.py -m "msg" 0xADDR [0xADDR ...]   # commit + push (see 4.3)
```

`build_sources.py` output: one line per match line, `OK ...` or `DIFF ...`. Only the DIFF lines and
compile errors matter. **A compile error leaves the old .obj in place**; always grep the output
for ` error ` before believing a result.

`match.py` output:
- `OK   SYM @ 0xADDR identical (N bytes, R relocations)` — done. `unverified: X` after it just
  means a callee resolved through an alias; fine.
- `DIFF SYM @ 0xADDR differs at +0xOFF` with compiled/original byte rows — code differs.
- `DIFF ... relocation at +0xOFF to X: the literal is b'...', but the original holds b'...'` —
  a string literal differs (fix the text; e.g. "has no headset" vs "has NO headset").

### 4.2 Source annotation (how the build knows what to check)

Every matched function is preceded by one or more lines of this exact form:
```
// match: ?sub_1ACBA0@@YAXHPAUtype_3DA434@@@Z @ 0x001ACBA0
// match: __ehhandler$?sub_1ACBA0@@YAXHPAUtype_3DA434@@@Z-0xB @ 0x00302AE0
// match: __ehhandler$?sub_1ACBA0@@YAXHPAUtype_3DA434@@@Z @ 0x00302AEB
void sub_1ACBA0(RwInt32 arg_0, type_3DA434 *arg_4)
{
```
- The symbol is the **decorated object-file name** (C++ mangled, or `_name` for C). Find it with
  `python tools/objlist.py OBJ | grep NAME` or from an existing `compiled.txt` row.
- **EH lines** (functions with C++ objects that need unwinding): the image has a `chunk_of_X`
  range in `config/splits.txt` holding the unwind funclets and the `__ehhandler`. Write exactly
  two lines: the funclets piece as `__ehhandler$SYM-0xN @ chunkStart` where N = handler address
  minus chunk start, and the handler as `__ehhandler$SYM @ handlerAddress`. The handler address is
  where `mov eax, FuncInfo; jmp ___CxxFrameHandler` starts (disassemble the chunk with
  `tools/xdis.py`; `SEH_X` in symbols.txt is often, not always, the handler). Two funclets still
  get only these two lines. Example: chunk 0x3027E0, handler at 0x3027F0 → `-0x10 @ 0x003027E0`
  and `@ 0x003027F0`.
- Put all `#define`s of a unit **before its first `// match:` line** (cmf strips function blocks
  by match lines; a define between blocks goes missing in intermediate commits).
- Do not end a global-scope unit with bodiless match lines (cmf strip bug); keep them above the
  last real function.
- Units are not sorted by address. Insert a new function before the match line of the *next
  address* that exists in the unit (or where its neighbours are).

### 4.3 Committing with cmf.py (the only way to commit matches)

```
CMUNIT=unit_1A8B20 timeout 900 python tools/cmf.py -m "match: <what it is> sub_XXXXXX

Co-Authored-By: Claude Opus 5.5 <noreply@anthropic.com>" 0x1ACBA0 > build/tooltmp/cmf_out.txt 2>&1
tail -5 build/tooltmp/cmf_out.txt         # expect "committed N" and "pushed ADDR ..."
git status --short                        # expect only the two untracked paths
```
- `CMUNIT` is the unit path relative to `src/` **without extension**: `unit_1A8B20` (means
  `src/recovered/unit_1A8B20.cpp`), `rw/plugin/dmorph/xbox/dmorphpipeg` (a `.c` is detected),
  `COD/SHARED/network/knet/sNetGameEP`.
- Pass **only function addresses** (never the EH handler/chunk addresses; those ride along).
- Pass **only addresses not yet in `compiled.txt`**.
- What it does: builds the tree with the functions placed (must PASS), with `-m` first commits
  everything else (headers, docs, config, other units) as a "types/docs" commit, then one commit
  per function, builds, pushes. It stops at the first failure.
- Use `-m` whenever headers, docs or config changed. If cmf says "nothing added to commit" with
  `-m` (only the unit changed), rerun without `-m`.
- `-m` does not stage `src/rwa/*.h`, `src/bink/*.h` or `tools/`: stage required code
  files explicitly before running cmf. All code pushes still go through cmf.
  Review untracked drafts before using `-m`, since it stages all of docs/.
- Run one cmf at a time. Do not edit any file while cmf runs (it rewrites the unit and
  `compiled.txt`).
- If cmf fails: read `build/tooltmp/blog.txt` (the build log) and `cmf_out.txt`; check
  `git diff --stat` for a gutted unit (restore with `git checkout -- FILE` if so);
  `git checkout -- config/compiled.txt` unless your change renamed a committed symbol; if
  half-commits were made but not pushed, `git reset --soft origin/master` and redo.
- A function that only changed because a **callee's signature changed** (e.g. `vf_048` now
  returns `RwInt32`) needs its existing `compiled.txt` row's symbol updated by hand in the same
  commit.
- Non-match commits (docs, tools, drafts) are plain git:
  `git add FILES && git commit -m "docs: ..." && git push -q origin master`.

### 4.4 Committing `.asm` units
cmf cannot handle `.asm`. Add the `compiled.txt` rows (`tools/session/addrows.py SRC`), run the
full `tools/build.py` to `== PASS`, then commit unit + rows by hand and push. (Only Bink and XDK
stand-ins are `.asm`; you should not need this.)

---

## 5. Tools (what each one is for, how to call it, what it prints)

### 5.1 Disassembly and comparison
- `python tools/xdis.py 0xLO 0xHI` — image disassembly with names. **Start every function here.**
  (Dump big ones to a file: `> build/tooltmp/x.asm`.)
- `python tools/objlist.py OBJ SYMBOL` — our compiled function, with relocation names.
- `python tools/session/odiff.py OBJ SYMBOL 0xADDR` — aligned instruction diff vs the image
  (`-` image, `+` ours; addresses normalized to `A`). `grep -c "^ [-+]"` gives a size score. It
  reloads the XBE each call (slow-ish).
- `python tools/session/slots.py`-style comparisons: there is no general slot tool in tools/;
  the scratch script pattern used this session: collect `[ebp - 0xN]` / `[esp + 0xN]` operands in
  first-use order for both and print side by side (see `tools/session/ceslots.py`, hard-coded to
  one function: copy and adapt it).
- `python tools/session/left.py [LO HI]` — unplaced functions (no compiled piece), by bucket.
- `python tools/session/ehchunks.py [--apply] [LO HI]` — EH chunks (`chunk_of_X` in splits.txt)
  left unplaced although X is matched: prints (and with `--apply` inserts directly under X's match
  line, plus compiled.txt rows) the funclet and handler match lines. EH lines separated from the
  match line by a comment are not picked up by cmf: keep them directly under it. Check the build
  afterwards; revert owners matched under undecorated names (`sub_4AB90`) and chunks holding more
  than one funclet (sub_15F590).

### 5.2 Variant search (the main productivity tools)
- `python tools/session/pscore.py VARS.py SYMBOL 0xADDR SRC [-j N]` (new 2026-10-01; `PSCORE_INC=DIR`
  puts an overlay include directory first, for trial header edits) — compiles
  every variant in parallel and ranks by normalized diff lines (lower is better) plus the first
  differing instruction index. `VARS.py` defines `VS = {'name': [(old, new), ...]}`; each `old`
  is replaced at its first occurrence in SRC. Works for `.c` and `.cpp`. Nothing in SRC changes.
  Use it for **optimized** code (RenderWare, RWA, Bink) where you search declaration orders,
  types, expression forms.
- `python tools/ptry.py VARS.py SYM ADDR SRC [-m] [-j N]` — older parallel variant compiler
  (scores by ncmp or match.py). **Its `build/tooltmp/ptry/p_*.cpp` files are snapshots: never copy
  one back over SRC after other edits** (silently reverts them).
- `python tools/session/chk2.py SRC SYM ADDR MAXSTEPS 'CAND1' 'CAND2' ...` — for **long /Od game
  functions** whose differences are register rotation. Each step: find the first differing
  instruction, map it to a source line through a `/FAsc` listing, try each candidate (an empty
  check such as `'if (!unk_04) { }'`) before that line, before the statements above it and before
  closing braces above it, plus inline swaps (`.drop(`→`.discard(`/`.clear(`, `.include(`→
  `.admit(`/`.add(`); keep the variant whose first difference moves furthest. **It writes SRC.**
  Save a copy of SRC first. Run it in the background for big functions.
- Header-variant trial pattern (this session's `hv2.py`, in the scratchpad; easy to recreate): a
  script that applies a list of (file, old, new) edits to *real files*, runs
  `tools/build_sources.py UNIT`, scores the function, and restores the files in a `finally:`.
  Useful when the variable is a **header** inline (pscore only edits SRC). Give it an `ANCHOR`
  string so replacements happen inside the right function, not at the first occurrence in the
  file.

### 5.3 Names and slots (game code, /Od)
- At /Od VC7.1 lays function-scope locals out by a hash of their **names**. Wrong names = wrong
  stack slots. Tools: `tools/bprobe4.py SLOTS` (solves names for a slot list, ~2 s) then
  `tools/applyb.py SRC ADDR "S=name ..."`; `tools/climb_names.py`; `tools/bsolve.py`;
  `tools/session/sn_n5.py` (permute names; it also rewrites string literals that contain the
  names — check literals afterwards). Never run `tools/local_names.py` (takes minutes).
- Draft locals as `lv_<slot>` (e.g. `lv_114`) so the name tools can work on them.

### 5.4 Other tools
- `tools/img2masm.py` — MASM transcription of image bytes (Bink/XDK only; never for other code).
- `tools/addfn.py` — add a function IDA missed to symbols/splits.
- `tools/gf.py TOOL 'JSON' PORT` — read-only Godfather IDA queries, e.g.
  `python tools/gf.py lookup_funcs '{"queries":["XboxDMorphAddBlock"]}' 13340`,
  `python tools/gf.py decompile '{"addr":"0x1136fe0"}' 13340`,
  `python tools/gf.py stack_frame '{"addrs":"0x1136fe0"}' 13340` (real local names).
  Long outputs are truncated with a `curl -o ... http://127.0.0.1:13340/output/<id>.json` hint:
  run that curl into `build/tooltmp/` and extract the text with Python.
- `tools/session/vc70try.py SRC SYM ADDR` — compile one unit with VC7.1 / VC7.0 / VC7.0+SSE and
  match a function (quick compiler-version check).
- `tools/session/decdump.py LO HI OUT` — IDA decompile dump of our game (read-only).
- `tools/session/addrows.py` — compiled.txt rows from match lines (for `.asm` units).

---

## 6. How to work on a function (procedures)

### 6.1 General loop (every function)
1. Find it: `python tools/session/left.py LO HI`, then read its notes: `grep -n sub_XXXXXX
   docs/units.md docs/questions.md src -r` and `ls docs/drafts | grep -i XXXXXX`.
2. Read the image: `python tools/xdis.py 0xSTART 0xEND > build/tooltmp/f.asm`.
3. Find its unit: the unit whose placed range contains the address (`docs/units.md` lists
   "Placed range ..." per unit; or grep neighbours' addresses in `src/`).
4. Draft it in the unit (or take the draft from `docs/drafts/`), with its `// match:` lines.
5. `python tools/build_sources.py SRC 2>&1 | grep -v "^OK"` — fix compile errors first.
6. `python tools/match.py OBJ SYM 0xADDR`; if DIFF, `python tools/session/odiff.py OBJ SYM 0xADDR`.
7. Fix in this order: **shape** (control flow, calls, frame size), then **slots** (names,
   scopes, temporaries), then **registers**. Never chase registers while the frame size differs.
8. When `OK identical`: run `python tools/audit_sources.py`, update docs (units.md: remove it from
   "still binary"; questions.md: remove/resolve its entry), commit with cmf (4.3).
9. If stuck after a real effort: park it (6.9).

### 6.2 Game code (/Od) — the tricks that actually work
Unoptimized code is deterministic once you know the rules. The decompiler output from IDA is a
starting point only; the assembly is the truth.

**Register rotation.** VC7.1 /Od picks registers in a rotation eax→ecx→edx→eax. Every register
*load* advances it, including loads made for code that is then not emitted. Consequences:
- An empty `if (cond) { }` emits **no code** but advances the rotation by the loads `cond` would
  make. This is how compiled-out asserts look in the original. Load counts:
  `if (!dwordMember) {}` = 1 (loads `this`); `if (!wordMember) {}` = 2 (this + movzx);
  `if (!p->x) {}` = 3 (= no visible change, mod 3); `if (!arg_0) {}` = 0 (compared in memory);
  `if (!(arg_0 & 1)) {}` = 1 (value must be computed in a register); a check on a global = 0.
- So when everything from some point on uses "the next" register compared with the image (ours
  `mov edx` where the image has `mov eax`: one step short), insert checks there whose loads mod 3
  make up the difference. **Prefer an existing inline variant that carries checks** over a raw
  check in the function body:
  - `type_1DDE20_mask` (include/types/type_1DDE20_mask.h): `add/insert/assign/clear` carry two
    checks; `admit/discard/reset` one; `include/drop/merge` none. `has()` vs `has_checked()`,
    `test()` vs `test_checked()` (an `!(arg_0 & 1)` check). `mark()` (two checks then an `r`
    local).
  - `type_4F8054_B0` (include/types/type_DC400.h): `others()` vs `others_checked()` (discard +
    a check before the copy out). `type_4F8054::get_unk_B0()` vs `get_unk_B0_checked()`.
  - Unit macros wrap raw checks: `SNET_CHECK/SNET_ASSERT` (sNetGameEP), `PLAYERS_CHECK`
    (unit_1CCC00), `BITSTREAM_CHECK`, `NETQUEUE_CHECK`, `SCRIPT_CHECK`.
  - New inline variants are fine **with an `Evidence:` comment** naming the function whose code
    shows them (follow the existing comments' style exactly).
- An `else` branch's registers continue from the end of its then-branch. A join after an `if`
  continues from whichever branch the compiler laid out last.
- Long functions: use `chk2.py` (5.2). Greedy "fewest diff lines" searches stall.
- Worked examples this session: `sub_1C32B0`/`sub_1C3520` (vote calls) matched with
  `get_unk_B0_checked()->others_checked()` and `mask.mark()`; `sub_1C7840` (voice status) with
  `has_checked()` on the second/third tests and `test_checked()` in the loop; `sub_1A2A80` and
  `sub_1ACBA0` with `get_unk_B0_checked()->others_checked()`.

**Stack slots and temporaries.**
- Function-scope locals: slot order by **name hash**. Fix with the name tools (5.3).
- Block-scoped locals take slots at **first use, in source order**, after the temporaries met
  before them. A frame whose named slots interleave with temporaries = nested blocks: declare
  each local in the block of its first use.
- An inline getter written `RwInt32 r = x; return r;` gives a result slot; `return x;` gives
  none. A by-value inline parameter given a computed value gets a slot; a constant argument does
  not. `set_x(const T&)` stores source-first; an implicit conversion `t = f()` stores
  destination-first.
- A value passed straight to a call needs no named local: `f(&m, g()->h())` vs
  `T v = g()->h(); f(&m, v);` gives a different slot (`sub_1ACBA0`: the image had no named mask
  local).
- `arg_0 = arg_0;` produces the parameter self-copy `mov eax,[ebp+8]; mov [ebp+8],eax`.

**Frame too big / too small with identical code = inline budget.** VC7.1 reserves frame space for
inline expansions it attempts. Frame **too large** by leftover string temporaries: no-code inline
calls placed **near the end** shrink it. Probe with `inline void nop_x() {}` and k calls at
various positions; once you know how many expansions and where, find natural ones. Example:
`sub_1ACBA0`/`sub_1AD750` got the image's frame with `show_message()` (game/functions.h, an inline
for `sub_EACA0(text, 0, 0)`) and `hosting()` (game/mpgame.h, `unk_4F61F8.unk_104`): the same pair
fixed both functions, which is the evidence. Frame too small: the original has one more inline
expansion somewhere (a getter, a debug-print inline).

**FPU, bool and int shapes** (full lists in `docs/session-memory/fpu-expression-shapes.md`,
`int-expression-shapes.md`, `getter-and-bool-shapes.md`, `paren-cast-temp.md`):
- `fld [p+X]; fdivr [a]` (divisor first) = `a / (p->x)` (parentheses flip load order).
- One `fst` temp after `call _fabs` = `(RwReal)fabs((RwDouble)x)`.
- `(bool)x` = `cmp; setne al`; `x != 0` adds `xor eax,eax`; `p ? 1 : 0` = neg/sbb/neg.
- `if (0) off_42CD14("...");` = disabled debug print (still emits `xor reg,reg; je`).
- Code after a `return;` is dropped but its loads still advance the rotation.

**Strings.** Check every literal against the image (match.py tells you). `#line N
"\\path\\file.cpp"` pins `__LINE__`/`__FILE__` where asserts embed them.

### 6.3 Naming (evidence rules)
- Placeholders: functions `sub_XXXXXX`, globals `dword_/unk_/byte_XXXXXX`, types `type_XXXXXX`
  (the address of something identifying, usually the vtable), fields `unk_OFFSET`, virtuals
  `vf_OFFSET`, params `arg_N`.
- A real name needs evidence: a string in the image (assert/print text, RTTI, `__FILE__`), a
  library symbol, the Godfather PDB (RenderWare), a known public source (RW 3.7.2 tree, dlmalloc,
  Ooura FFT, Bink headers). Renamed items keep a comment with their placeholder/address.
- Inline helpers have no address, so they are named "for what they do" with a comment:
  `// <what>: an inline with no address, named for what it does. Evidence: <function> (sub_X)
  shows <what in the code>.` Copy the style of the neighbouring helpers.

### 6.4 RenderWare code (optimized C, `src/rw/`)
- The image's RW is **3.6** (Xbox). Our base is the **3.7.2** tree at `D:\RW_372_src`; Xbox-
  specific code (driver, `world/pipe/p2/xbox`, `plugin/*/xbox`) is absent from that tree and was
  rebuilt from the image using the **Godfather debug build** (port 13340) as a template.
- Rules: 1) a file that exists in the tree: copy it **pristine** first (one commit), then edit
  to the image in later commits; log every difference in `docs/rw-differences.md`. 2) code absent
  from the tree: write it from the image, shaped on Godfather's (3.7) version, minus 3.7-only
  checks/asserts.
- Godfather workflow: `gf.py lookup_funcs` (find address by name, port 13340), `gf.py decompile`,
  `gf.py stack_frame` (real local names and every local), `gf.py disasm`. Debug-build block order
  = source order (Hex-Rays may flip polarity; trust the debug asm).
- At /O2 local **names do not matter**; slots and registers follow first use, lifetimes,
  declaration order (sometimes), types (signed/unsigned), expression shape and statement order.
  Search those with `pscore.py`.
- Static helpers inlined in our build but called in the image: `static __declspec(noinline)`
  (log in rw-differences.md). Statics called with the compiler's own register convention
  (args in eax/esi/ebx...) only match when compiled in the same file as their caller, and only if
  they modify a parameter (e.g. `numBlocks++`).
- Original RW inline asm exists in a few places (Xbox `RwFastRealToUInt32` = `cvttss2si`, MMX
  copy loops in the instancers, `RwV3dTransformPoint`'s SSE blocks); those are allowed (6.7).
- Macros matter: use RW's accessor macros (`RpAtomicGetGeometry`, `RpGeometryGetFlags`,
  `RPDMORPHGEOMETRYGETDATA` — note this one yields a **pointer to the pointer**, dereference
  it) because their parentheses change load order.
- Flags per directory are in `config/flags.txt`; a new directory needs a rule above `src/rw/*`
  with the right `/I` dirs (copy a sibling rule).

### 6.5 RenderWare Audio (`src/rwa/`, VC7.0 core)
- Complete as of 2026-10-02: zero unplaced ranges in `0x23B750-0x252000`
  and `0x2FD5D0-0x2FEC60`. All 762 ranges are placed; the full image passes.
- No source exists; drafts are written from the image. Use `pscore.py` to search statement order,
  declaration order, temporaries, loop forms. There is no empty-if trick in optimized code.
- RWA quirks (docs/session-memory/rwa-quirks.md): `/O2 /Ob1` x87, nop padding (`addfn --trim`),
  table handlers, `volatile float` = fld/fstp, structs in headers.

### 6.6 Adding a function IDA missed
Add a `function` row to `config/symbols.txt` and a range to `config/splits.txt` by hand (or
`tools/addfn.py`), keeping address order. Never edit the IDA database.

### 6.7 Inline asm (only where the original had it)
Evidence that the original used asm: instructions no compiler emits for C (rdtsc, `ror bx,8`
byte swaps, fstcw/fldcw sequences, a lone `cvttss2si` helper, ebx use at /Od), or the Godfather
PDB showing asm labels. Then write it between:
```
// begin original __asm (evidence: <why you know the original was asm>)
    __asm { ... }
// end original __asm
```
The audit rejects any `__asm` outside such regions (except `src/bink/`).

### 6.8 ICF folding and aliases
Identical functions folded by the linker (`/OPT:ICF`) share one address. Declare the member and
add an alias row `objSymbol 0xSHAREDADDR evidence` to `config/aliases.txt`. Vtables need
`??_7type_X@@6B@ 0xADDR` rows. Library functions resolve through aliases too.

### 6.9 Parking a function that will not match
1. Copy your best draft into `docs/drafts/<name>_draft.c(pp)` with a header comment: what it is,
   where it goes (unit, insertion point, includes), how far it is (diff lines, first diff), and
   what you tried.
2. Remove the draft from the unit (`git checkout -- UNIT` if nothing else changed).
3. Add/extend its entry in `docs/questions.md` (near-miss sections) or its unit's section in
   `docs/units.md`: what differs and every idea tried, so nobody repeats them.
4. Commit docs + draft (plain git) and push.

---

## 7. Code conventions (the audit enforces part of this; imitate neighbouring code)

- RenderWare scalar types only: `RwInt32`, `RwUInt32`, `RwInt16`, `RwUInt8`, `RwReal`,
  `RwDouble`, `RwChar`, `RwBool`. No bare `int/unsigned/short/long/char/float/double`. Bink uses
  RAD's `S32/U32/F32`. No `auto`.
- Structs/classes are defined once, in a header (`include/types/type_XXXXXX.h` or
  `include/game/*.h`), never in a `.cpp` (audit failure). Before creating a header run
  `git ls-files include/<path>` and `grep -rn "struct type_X\b" include` — merge, never overwrite.
- Never write an image address as a number: declare the global and use its name. A constant
  that happens to look like an address needs `// not an address` on its line.
- No raw byte offsets (`((RwUInt8 *)p)[0x1C]`): add the field to the struct.
- Locals in game code carry their slot in the name; add the comment
  `// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).` above
  such functions (as the existing units do).
- Compiled-out checks: inside an inline variant or a unit macro, with a comment saying the
  condition is chosen for its loads (`(docs/toolchain.md)`).
- Header inline helpers: `Evidence:` comments (6.3).
- C++ classes for game types; C for RenderWare/RWA/Bink.

---

## 8. Hard-won pitfalls (read before you run anything)

1. **Never pipe the build into `tail` to decide pass/fail.** Save to a file, grep `== PASS`.
2. **Compile errors leave stale objects.** A trial that "changes nothing" may not have compiled.
3. **ptry snapshot files revert edits** if copied back.
4. **Name-permutation regexes rewrite string literals** too ("kick" → "a"); re-check literals.
5. **Header edits affect every unit including that header.** After changing an inline used
   elsewhere, rebuild the other units (cmf's build does it; a failing other unit = your change
   broke a matched function). Prefer adding a new variant over changing an existing inline.
6. **cmf with EH addresses** passed explicitly once emptied a unit. Pass function addresses only.
7. **Two tools writing the same files** (two cmf runs, or chk2 + an edit) corrupt them. One at
   a time.
8. **Write tool vs heredoc:** heredocs drop backslashes; use Write for any file with `\`.
9. **`replace first occurrence` helpers** hit the wrong function when the same text appears
   earlier in the unit; anchor replacements to the function header.
10. **A header member signature change** (`void` → `RwInt32`) renames the mangled symbol of
    already committed callers: fix their `compiled.txt` rows in the same commit.
11. **IDA decompiles hide code under `if (0)`** and reorder things; read the asm.
12. **Do not delete files** (no rm). Make new scratch names instead.
13. Make sure `git status` is clean (except the two untracked paths) after every commit.

---

## 9. Status and work list (2026-10-01)

`python tools/session/left.py` reports 347 unplaced ranges in total; that number includes 128
`chunk_of_*` EH ranges belonging to unplaced game functions (they go in with their owners) and
data. Functions, by area, in the owner's priority order:

### 9.1 RenderWare (all tracked functions matched)
Collision follow-up: `GeometryForAllTriIntsecLine` and `RpCollSectorLineItInit`
(the database names the latter `Collision_LineClipBBox`) now match. Compute
`(bound - start) * r` inside each direction branch, with inf before sup in both
branches; the negative branch assigns hi before lo. This fixes both register
allocation and the remaining per-axis load order.

Default-render follow-up: `_rxXbDefaultRenderCallback` (0x2E02A0) matches
with a typed inline variant of the existing texture-stage force macro
(`_rwXbTextureStageForceInline` in xbcache.h). It fixes both scheduling spots.

Morph-update follow-up: `rwXBInstanceDataMorphUpdate` (0x2E2080) and its
caller `_rxXBAtomicDefaultReinstanceCallback` (0x2E2380) now match. Explicit
`const RwV3d *verts` and `const RwRGBA *color` source-pointer locals fix the
single-target and prelight scheduling, including the later texture loop.

Skin-render follow-up: `_rpSkinXboxRenderCallback` (0x2D4220) now matches
with a block-local `const RpMaterial *material = mesh->material` before
material setup. This fixes the atomic argument load and subsequent draw call.

World-read follow-up: `RpWorldStreamRead` (0x2DAB30) now matches with a
local `void *readBuffer = &w34000` before clearing the old-version header.
Using that local in RwStreamRead fixes the size push and header-buffer slot.

Flatten follow-up: `Flatten2d` (0x2530C0) now matches. Its second
line-segment expansion uses a typed forceinline variant with a previous-normal
pointer local. The first expansion retains the macro.

Skin-matrix follow-up: `D3DMATRIXFromRwMatrix` (0x2D21C0) and
`_rpSkinXboxMatrixUpdate` (0x2D2230) now match. Cache frame pointers, index
shaderConstants in all three branches, initialize the third loop counter
before matrix setup, and give the first bone loop its own counter.

Matched 2026-10-01 (examples of what works): `SkinAtomicGetSize` 0x2D12B0 and
`_rt2dMessageStreamReadDefaultCallBack` 0x2577B0 (ICF-folded one-liners: match line on the owner
whose address range holds the copy, aliases for the folded names), `rtpitexdImage2TextureRead`
0x2F5740 (the 3.7.2 tree's third-party `min()` edit removed), `_rpSkinXboxComputeProjViewWorld`
0x2D18D0 and `_rpSkinXboxGenerateShader` 0x2D26B0 (written from the image, tuned with
`pscore.py`: scaled locals, zero stores inside both branches, `count = 4; if (n - i < count)` for
`cmovb`, block-local loop counters, `(i + j) * 2` instead of a stepped variable),
`XBoxDmorphAtomicAllInOneNode` 0x2F3F40 (Godfather shape; two `_rxXBInstance` calls in an
if/else, not a ternary), `DefaultPathStroke2d` and `rt2dFontShowBitmap` (rwcore.h now has the
Xbox immediate-mode vertex: check header shapes against the Godfather PDB's types first).

| Address | Name | File (src/rw/...) | State / where the notes are |
|---|---|---|---|
| 0x2A48C0 | MatrixOrthoNormalize | src/plcore/bamatrix.c | Matched: 1,468 bytes, four relocations; production source supersedes drafts |
| 0x2A7210 | RwStreamSkip | src/plcore/bastream.c | Matched: 292 bytes, 13 relocations and 18 jump-table bytes; file-branch retVal from Godfather debug |
| 0x2D4440 | _rpSkinXboxGetVertexFormatShader | skinxboxformat.c | Matched: 688 bytes, 42 relocations; production source supersedes drafts |
| 0x2D46F0 | XBoxSkinAtomicAllInOneNode | skinplatform.c | Matched: 986 bytes, 36 relocations; shader pointer advancement, indexed batches and direct callback resource address |
| 0x2DDB50/0x2DE0F0 | _rpXboxVtxFmtInstBNT / ...BNTComp | xbvtxfmt.c | Both matched: 1,425/1,459 bytes and 10/13 relocations; production source supersedes drafts |
| 0x2DED60 | _rpXboxDefaultInstance | xbvtxfmt.c | Matched: 669 bytes, 18 relocations; signed size local and common position-pointer advance |
| 0x2F2860/0x2F28D0 | XboxDMorphAddBlock / XboxDmorphAtomicInstanceCallback | plugin/dmorph/xbox/dmorphpipeg.c | Both matched: 109 / 5,740 bytes; callback has 93 relocations and 160 jump-table bytes. Shared pass locals restore stack lifetimes; production source supersedes drafts |

Follow-up trial harness: `docs/drafts/rw_inline_followup_trials.py` records
rejected typed-inline/local-pointer variants for BNT, BNTComp and RwStreamSkip.
Historical trials below predate the matched table rows; use production source for those rows.

Scope/accessor follow-up trials for the skin node, MatrixOrthoNormalize
and skin format selector are in `docs/drafts/rw_scope_accessor_trials.py`;
none improved the listed drafts.

BNT expression-context trials are preserved in
`docs/drafts/rw_bnt_expression_trials.py`; BNT is now matched and those drafts are superseded.

### 9.2 Game (30)
Matched 2026-10-01 besides those in section 6.2: `sub_22B040`/`sub_22B0C0` (a FREE inline
`peer_in(&mask, i)` with an `!(i & 1)` check: a member inline with a check adds a `this` slot),
the spawn picks `sub_1C16B0`/`1C1820`/`1C1A40` (`type_1F8560_v::len()`, an in-class copy of
`sub_1BF590` that VC7.1 declines, ICF-folded and aliased: a never-written slot in a caller = a
declined inline's local).

| Address | Notes (grep these places) |
|---|---|
| 35AA0 35FD0 362F0 | Matched: named handle values and receiver pointers reproduce the grouped temporary slots |
| 39AA0 3A450 | Matched: handle-returning getter and original loop shape; named handle copies and receivers |
| 3CE20 3D150 | Matched: inline registration defers the union temporary; named handle copies fix the updater |
| 3EEE0 | Matched: list getter plus declaration-only global placement new/delete |
| 43200 | Matched: command 11 uses a named value and a two-load compiled-out check before the member store |
| 8AFF0 | Matched: inclusive-range count expression preserves the register divisor |
| 9B0B0 | Matched: two named setter values put the struct-return temporary before the remaining inline locals |
| BA030 | Matched: unit-specific `/EHa` retains the empty destructor's EH state and base cleanup |
| 122410 1224F0 | Matched: id record return allocates before the list getter's local |
| 15A8C0 | RESOLVED: constructor and EH match; inline base constructor plus three reference-returning coordinate accessors preserve the tank factory frame. |
| 1AB440 | float argument passed as `fld; push ecx; fstp [esp]`; long list of tried forms in questions.md |
| 1C5350 | Matched: text diagnostics plus eight unused inline locals in a separate final-return scope |
| 1CAF30 | Matched: type_1A5EA0 return chain through sub_E3970 to type_1CB670's localized constructor |
| 1D4290 | Matched: packet-only instantiation avoids the unrelated HUD singleton guard and restores generated local names |
| 21BD60 | Matched: restored local scopes, one unused inline slot in the map branch, and the original atoi call |
| 21F1C0 | scoreboard text builder remains parked; 21FB60 and its unwind pieces now match in unit_21EB30 |
The last 2 dynamic-initializer destructor thunks at 0x30EA80–0x30EA90 (`sub_30EA80` and `sub_30EA90`) are now generated and matched in `unit_1A8B20.cpp`.
See docs/session-memory/global-dynamic-initializers.md and initializer-batch.md.

### 9.3 RenderWare Audio (complete, verified 2026-10-02)

Final gates place creator 23E690 (416 bytes / 22 relocations), VAG block
24B510 (1,520/14), wrapper 24BB00 (336/1), and caller 24C230 (816/8), all
through cmf.py. Full image PASS: 18,167 pieces / 3,499,204 bytes, original
SHA-1, byte-identical. All 762 RWA split ranges are placed; zero remain.
Creator reuses the total-size local for the first input count. VAG keeps the
selected filter index while reusing the original filter local for its header;
two coefficient pointer locals inside the final loop preserve x87 scheduling.
All 31 wave-conversion annotations pass. No compiler changes or inline asm.
The owner requested a stop when RWA finished, so no other work was started.

The following batch and near-miss notes are historical, superseded above.

Previous gates place Xbox output destructor 24E710 (84 bytes / four relocations)
and WMA creator 2516E0 (1,535/37), pushed only through cmf.py. Full image
PASS: 18,163 pieces / 3,496,116 bytes, original SHA-1, byte-identical. WMA
header/description share a nested lifetime; the destructor retains an ordinary
three-word zero temporary with folded cleanup (original type remains unknown).

Previous seven-function gate places 24AB90, 24BEF0, 2FE290, 251210, 24EDC0,
24F350 and 24F410, all through cmf.py. Full image PASS: 18,161 pieces /
3,494,497 bytes, original SHA-1. See the latest batch in questions.md for
the decoder/source scopes, uninitialized release fallback and helper signature.

Previous gate places path search 2494F0 (688 bytes), bitmap allocation 2FD880
(576) and format setup 24D670 (896), all through cmf.py. Full image PASS:
18,154 pieces / 3,488,495 bytes, original SHA-1, byte-identical. Debug source
recovers the recursive depth updates, ordinary bit loop and shared ID locals.

Previous completed batch: 247660, 249160, 246ED0, 24CC80, 249D00, 249EF0,
24A260, 24A740, 24B260 and 24BC50. All pushed through cmf.py; the full image
passes byte-identically with 18,151 pieces / 3,486,335 bytes and original SHA-1.
This supersedes the older parked PCM, setup, gain and splitter-status notes below.
See the latest debug-reference batch in questions.md for source-shape evidence.

Remaining: none. Production sources supersede all parked RWA drafts.

**Use the debug reference now:** C:/rwstudio/shared/OpenExport/bin/rwad.dll
has 1,889 exports, including internal routines, and debug code that preserves
source locals, expressions and control flow. The release sibling is rwa.dll.
Read-only helper build/tooltmp/smallagent_rwa_dll.py supports `exports REGEX`,
`strings REGEX`, `refs VA_OR_EXPORT`, and `disasm VA_OR_EXPORT --bytes N`.
Source-shape evidence from this DLL resolved several long-standing near misses.
Treat platform/version differences as evidence to check against Xbox bytes.

Newly placed: cache open 2450C0 (112 bytes), source read 248520 (752), bitmap
creator 2FD5D0 (240), IMA encoder 24BD30 (176), timer stop 244980 (48), chain
preinstancing 246240 (624), chain creation 246500 (1,488), and source callback
248810 (2,384). All were committed/pushed through cmf.py. Latest full gate:
18,141 pieces / 3,480,447 bytes; SHA-1 d3ec0b089647081fd733b1bf53c63136f1a95387,
byte-identical. RW is complete; 26 RWA remain.

Cache open moves state=1 between the link and offset clears; callback is a
qualified incoming argument copied to a normal local. Source read uses a
typed inline batch helper and distinct release/return paths. Bitmap creation
uses positive bitmap/bits guards, reuses rounded for byte count, and shares
its bitmap return. Encoder uses the incoming Int16 sample directly and puts
the last step shift inside each predictor expression. Timer compares and
updates a UInt32 elapsed against repeated masked UInt64 start expressions.
Chain preinstancing uses do/while(def && !found); chain creation preserves
the debug temporary/alias lifetimes and original graph loops. Callback takes
void *data and creates a typed state local, resolving its last two SIB bytes.

PCM follow-up: 24A740 and static helper 24A260 both match once the external
249EF0 resampler definition is present in the same unit. Missing callee
context caused the old EBX/EBP mismatch. Repro smallagent_pcm_context_clean.py
key0. Resampler debug reference is 0x100AC936..0x100AD2A5; its body is under
active recovery, so the group is not placed yet.

Source callback 241230, source selection 2457A0, seek 247FE0 and splitter
read 24CD50 now match (192 / 704 / 512 / 288 bytes). Callback keeps a
separate obj local and typed items pointer, with positions/count/items loaded
in that order. Selection caches source->name, initializes each inner-loop
index, and scopes each case's list iterator separately. Seek scopes multiply
outputs, uses separate unlock returns, and builds offset in sequence; its
last info->unk24 read is qualified with an evidence comment. Splitter read
puts the successful read inside a positive mask guard, then returns NULL.
This restores the original failure-epilogue XOR order without qualifiers.
All four were pushed through cmf.py. Full gate: 18,133 pieces / 3,474,623
bytes, original SHA-1, byte-identical. RW is complete; 34 RWA remain.

Voice update 23EBD0, pool allocation 2442D0, stream wrap 247F20 and conversion
chain 249920 now match (672 / 144 / 192 / 720 bytes). Update initializes the
used counter after listener updates and uses the original while guard for
position wrapping. The pool keeps allocation and result as separate locals;
its gap test uses `(found + 1) + size`, and it reads the end before advancing.
The wrapper caches tracks before its guard, keeps count at function scope,
and puts the one-to-minus-one correction inside the track-count guard.
The conversion chain initializes output locals after the same-format return,
updates source size before its format/buffer swaps, and uses a separate final
result-size local. All four were pushed through cmf.py. Full gate: 18,129
pieces / 3,472,927 bytes, original SHA-1, byte-identical.

Voice priority 23E980 and its static group 23E8E0/23EE70/SoundStopper_Transition
now match (896 bytes total). Use the complete RW Sub/Dot macros, initialize
min before max, share the unity-volume path, and put the list-head insertion
case first. One final flags update preserves the EBX one-valued constant.
Integer min/max/previous-priority copies and a pointer comparison inline keep
the existing header layout; no new qualifiers or types were needed.

WMA defaults 250C10 now matches (97 bytes / one relocation): place unk04=1
immediately after unk00=0, leaving fileType=1 after the zero stores. This
preserves simultaneous zero/one register values and restores stack cleanup.
Both units retain all existing matches. All five were pushed through cmf.py;
gate: 18,125 pieces / 3,471,199 bytes, original SHA-1, byte-identical.

PCM helper 24A260 now matches in scratch (1,024 bytes / 29 relocations): each
conversion loop has its own RwUInt32 i inside its destination guard. This
fixes the final SIB byte. It still needs caller 24A740 to establish its static
register ABI, so it remains unplaced. The caller's clean scalar draft is now
34 normalized lines with every stack home correct; only EBX/EBP allocation
differs. Initializing result/spare/buffer/final before copying the format fixes
the stack homes. A chained malloc assignment gets to six lines but assigns
the destination before the null guard, unlike the original. See
build/tooltmp/smallagent_pcm_followup.py and smallagent_pcm_notes.txt.

Wave-dictionary loader 23C490, listener spatialization 23CD40 and vector
length 242050 now match (624 / 1,040 / 128 bytes). The loader saves the three
list-node fields through an RwaLLNode local and stores the dictionary address
to state before loading the local pointer. Spatialization addresses listener
state at object +0x28 through a typed overlay; the at pointer is declared
between rolloff and velocityScale. Both vector routines preserve the original
RW subtraction/dot-product macro parentheses. Two qualified x-component reads
retain spatialization's initial load order; original qualifiers are unknown.
All code and the supporting header were committed/pushed through cmf.py.
Gate: 18,120 pieces / 3,470,206 bytes, original image SHA-1, byte-identical.

Search 23D970 and destroy 23DB90 now match (176 / 208 bytes). Search keeps
the root separately and qualifies two reads of the def argument home.
Destroy loads the first interface before its list-head assignment and clears
instances separately in all three allocator branches. Original qualifiers
are unknown; source comments record this. All rwaobjdef.c functions are placed.

Listener initializer 23CC70 and setters 23D2A0/23D320 now match (208 / 96 /
96 bytes). Preserve every parenthesis of the original RW cross-product macro
from RWSDK/src/plcore/bavector.h; algebraically simplified forms reschedule
the x87 instructions. Spatialization 23CD40 is now placed (see above).

Byte swap 241FD0 now matches (128 bytes): the 16-bit path shifts a word
load, and the 32-bit path keeps its first two source reads direct while
using a saved value for the right shift. Named byte-buffer pointers retain
the byte accesses and pass the audit. Vector length 242050 is now placed.
All six were pushed through cmf.py; full gate: 18,117 pieces / 3,468,414 bytes,
byte-identical, SHA-1 d3ec0b089647081fd733b1bf53c63136f1a95387.

SetupParams 23DD00 now matches (288 bytes / five relocations). Put the
existing-table loops in the allocation condition's else branch and share
one final return def. Keep direct NULL failure returns; VC7.0 merges them.
No qualifiers or compiler changes. Repro: rwa_objdef_setup_return_trials.py.

Definition creation group 23DAA0/23DB30/23DE20/23DF00/23DFB0 now matches
(848 bytes total). The creator's eight-byte memset for unk50 fixes register
lifetimes. Defaults initializer 23DE20 uses a 16-bit loop counter and tables
declared inside each input/output branch; no input qualifier is needed.
Initializer 23DF00 clears stateSize and stateAlign bitfields separately, then
uses the existing alignment macro. This retains its original OR instruction.
The shared header exposes the packed word at +0x40 through an anonymous union.
Repros: rwa_objdef_create_current.py, rwa_objdef_defaults_recovery.py and
rwa_objdef_init_bitfields.py. Destroy 23DB90 is now placed (see above).

Instance-memory release 23D8B0 now matches (144 bytes / four relocations).
Use a separate unused state-offset local for sub_23F300; the compiler places
it in the input argument home. Reusing the parameter explicitly adds an
unwanted saved register. No qualifiers or compiler changes. Repro:
rwa_instance_free_signature.py.

Free-list release 2437A0 now matches (224 bytes / one relocation, including
11 NOP bytes). Reusing a named bitmap pointer for the bit clear and sum loop
fixes all three address encodings. Allocator 243670 now also matches (304
bytes / one relocation, including 13 NOP bytes). Restore the missing alignment
helper, use a separate checkEntries counter, and share the entry-found test
after both bitmap branches. All seven unit_243670 annotations match. Repros:
rwa_freelist_release_current_trials.py and rwa_alloc_exit_trials.py.

Wave busy query 242570 now matches (32 bytes including NOP padding).
The callback is RwaWaveDefUploadBusyFunc(void), as declared by the reference
header; the old wave argument caused the extra stack store. Shared
rwaint.h and the call now agree. Upload 242810 also matches (256 bytes,
11 relocations) with a separate uploadOffset local assigned in both branches.
All 34 annotations in unit_2422B0 now match. Its old wave draft is superseded.

WMA creator 2516E0 has a current draft in rwa_wma_create_followup.c.
A named track pointer reduces 246 normalized lines to 211; local names,
declaration permutations and nested scopes do not fix its stack placement.
Cleanup tail sharing and descriptor/packet initialization still differ.

Latest parked follow-up: wave setter 24F410 improves from 247 to 115
normalized diff lines; use rwa_voice_wave_followup.c and its saved trial
scripts. Helpers 24EDC0/24F350 still match only beside that unplaced caller.
The output destructor 24E710 remains a two-line scheduling near miss.
Core listener initializer and setters are now placed; production source
supersedes rwa_listener_current_followup.c for those three functions.

Xbox voice update `sub_250340` now matches (1,134 bytes, 29 relocations).
Keep the velocity getter in a local function pointer, qualified listener/gain
reads, a named position result, and the recovered vector/I3DL2 operand order.
All 102 annotations in unit_24EC60.c match with unchanged VC7.1 flags and
headers. Original declaration forms are unknown; source comments record this.
The old update draft is superseded. WMA initializer `sub_250C10` now matches;
current-header return/grouping trials are in rwa_wma_defaults_shape_trials.py.

WMA play-position query `sub_250D90` now matches (100 bytes, four relocations)
with the existing VC7.1 flags. A switch on the position unit preserves the
original SUB dispatch and restores the ECX state pointer. All 26 annotations
in unit_250B20.c match; the old position draft is superseded.
Follow-up 2026-10-01: recovered the interrupted unit_249490 edit and placed
`sub_24C560`, `sub_24C620`, and `sub_24C700` (736 bytes including padding), with a
passing whole-image gate. The converter `sub_24C8C0` and its static dispatchers
`sub_24C840`/`sub_24C880` now also match (1024 bytes including padding).
The converter uses a shared result-return path, source-first pointer
initialization in the split/merge loops, and advances dest once before
clearing/decoding. Both dispatchers retain their compiler register ABI.
The stream-cache callback `sub_244B40` and helper `sub_244AF0` also match
(720 bytes including padding): share the handler exits through one unlock label.

Verified against splits.txt minus compiled.txt: 39 unplaced functions in
`0x23B750–0x252000`, plus three in `0x2FD5D0–0x2FEC60`. Exclude chunk_of_*
ranges when counting functions. RW has zero tracked functions left. The 42
RWA count includes helpers that match only with unplaced callers. Notes: questions.md
"RenderWare Audio near misses"; drafts `docs/drafts/rwa_*_draft.c`.

RWA converter follow-up trials for 249D00/24BD30/24BDE0 are preserved in
`docs/drafts/rwa_converter_followup_trials.py`; none matched.

Allocation trial baselines are in `rwa_allocation_followup_trials.py`
(2442D0 and 2FD5D0). Its symbol mode is superseded: 244650/244690 are placed
with pointer returns, and their old void drafts fail to compile. New pool
flow/local and bitmap flow/return trials are saved as `rwa_pool_*_trials.py`
and `rwa_bitmap_*_trials.py`. Neither allocator matched in this follow-up.

Remaining stream-cache client trials are in `docs/drafts/rwa_streamcache_*_trials.py`;
`rwa_streamcache_clients_followup.c` is superseded for header callback
244FA0, dispatcher 245060 and small helper 2449C0: all three now match
(320 bytes total). Duplicate the failure cleanup in both failure branches;
the compiler merges it into the original register sequence. Repro:
rwa_cache_duplicate_failure.py, cachedup_1. Open 2450C0 remains parked.
Stream-source callback 241230 trials are in `rwa_streamsource_*trials.py`; still parked.

Core startup 23E1C0, module-open helper 23E240 and RwaCoreOpen 23E510 now match
(304 bytes including padding). Increment the opened count before testing the user
callback result, then share failure cleanup; keep CoreOpen success inside its if.

Object-definition release helpers 23DAA0 (144 bytes / three relocations)
and 23DB30 (96 / eight) are now placed with the definition creator. Qualified
input/output pointer reads keep loads before the count tests; original
qualifiers are unknown. Their old release draft is superseded for those
helpers and the now-placed 23DB90 destroy body.

Stream position query 23FEE0 now matches (240 bytes including padding): copy the
query parameter into a local out pointer to select the original conversion slot.

Parameter getter dispatcher 23F8E0 now matches (48 bytes): widen getter->param
to a RwUInt32 local before invoking the callback. Setter 23F8B0 now also
matches (48 bytes / no relocations): initialize the object local before the
setter local, then copy data and widen param. Repro: rwa_setter_lifetimes.py
(setlife_0_1). Stream unlink 23FC00 also now matches (96 bytes / seven
relocations). Load the count, then the input pointer, then decrement/store
count before waiting. Qualified accesses preserve this order; original
qualifiers are unknown. Repro: rwa_unlink_order_trials.py, unlinkorder_1.

Object-update 23F0D0/23F140 now match (112 bytes each including NOP fill).
Use pointer callback/status returns and a qualified incoming pointer copied
to an ordinary local; this preserves the two fallback parameter reloads.
Original qualification is unknown and recorded in source. All 20 rwaobj.c
annotations match. Callback registrations now use the correct pointer return.
Core wrappers retain their matches with sub_23F2F0(void) nested inside the
execute call whose second argument is FALSE. The old draft is superseded.

Interface definition creator 243E20 now matches (128 bytes including NOP fill,
seven relocations). Its allocation/flag-selection inline returns the definition
to the shared initializer; this places the existing-definition branch after
the normal return. No compiler or shared type changes were needed.

Interface instance 243FF0 now matches (560 bytes / four relocations): its
allocation inline fixes the fallback branch, and a separate output counter
plus qualified definition-table read fixes the address operands. Compatibility
243BC0 also matches (272 bytes / two relocations) with a separate input counter
and qualified definition-table read. Original qualifier forms are unknown.
All 12 unit_243AE0 annotations now match; old interface drafts are superseded.

Source chunk acquire 247C50 now matches (432 bytes). Put look-ahead first,
use explicit failure returns, and preserve region-flag read ordering.

Source chunk release 247E00 now matches (288 bytes): route both exits through
a shared semaphore-release label. This resolves the arithmetic/register scheduling.

Track-position helper 248360 now matches (80 bytes): use local high/low
multiply results instead of casting addresses of the input parameters.

Source seek 247FE0: `rwa_source_seek_followup.c` corrects the overwritten-position
error and improves 165 to 125 normalized lines with shared unlock. Still parked.

Node dispatchers 247220 and 247260 now match (96 bytes total). Return the
callback RwBool result and widen its parameter number to a RwUInt32 local.

Stream-description fix-up 24D670 improved from 111 to 67 normalized lines.
Best draft `rwa_fixup_followup.c`; loop-scope and format-field pointer trials
are in `rwa_fixup_*trials.py`. Still parked.

Xbox streamed-wave creator 24DBA0 and its static allocator 24DAD0 now match
(182 / 58 bytes; 12 / three relocations). Copy the qualified incoming wave
pointer into the ordinary local before loading memory; this fixes the early
ESI save and EDI memory pointer. Keep the qualified length reloads. Original
qualifier declarations remain unknown and are identified as such in source.
All 18 annotations in unit_24DA70.c match with unchanged VC7.1 flags.

### 9.4 Data (PLAN M5) — the base setup (2026-10-01)

How data is placed (same machinery as code):
- A data item is a compiled piece: a symbol in a unit's object (`??_7type_X@@6B@` vtables, address-
  named globals such as `flt_3DAEE8`, `static` constants, function-local statics). Its `// match:`
  line goes immediately before the next existing `// match:` line after its definition (a block of
  its own, so cmf's strip and replay handle it; function-local statics too).
- Each piece needs its own placement range in `config/splits.txt` (`0xSTART 0xEND .rdata NAME`),
  cut out of the section's big binary range. Without it the linker fills everything from the
  piece to the next boundary with zeros.
- `tools/match.py` checks data pieces like code (bytes and every relocation) but skips the code
  end check (0xCC fill / IDA size): the piece's own range is its extent.
- `python tools/session/datapieces.py [--apply] OBJ ADDR=SYMBOL ...` compares each piece, and with
  `--apply` adds its splits.txt range, a compiled.txt row and alias rows for relocation targets the
  link cannot resolve (a vtable slot naming a function that is not placed: the address the image's
  slot holds is the evidence). Use `--apply` to try the full link (`python tools/xbelink.py`), then
  restore config/compiled.txt from your backup (cmf adds those rows), add the match lines and
  commit with `CMUNIT=... python tools/cmf.py -m "data: ..." ADDR...` (the -m header commit stages
  splits.txt and aliases.txt).
- `.bss` (the `.data` section's tail past its file size) has no file bytes: nothing to place.
  It is matched when every reference resolves to the right address, which the code pieces'
  relocation checks already do.

Done so far: 15 GodAsset vtables (unit_18F3C0, 0x3DF8D8–0x3DFAEC), the float tables
`flt_3DAEE8`/`flt_3DAF58` and `flt_429C90` (unit_1340D0), six constants `unk_3E6CF4`–`unk_3E6D08`
(unit_1DFBB0), `unk_3E6E04` (unit_1E0DA0), the function-local `unk_42CD18` (unit_1D7CE0).

The input events table (`dword_429498`, 45 `{number, setting, name}` rows, unit_0EE540) and its
45 `"ePE_..."` names are placed too: the table as a `.data` piece defined with its initializer,
the names with `python tools/session/literalpieces.py [--apply] OBJ SYMBOL ADDR`, which takes
each `??_C@` literal's address from the piece's relocations and places it as its own `.rdata`
piece (VC7.1 emits a unit's literals in reverse order; the zero padding between them stays
binary). Other text tables like it: grep the image for runs of literals, find the pointer table
(a scan for their addresses in .data), and the code that indexes it gives the unit.

Next, easy and many: about 290 more vtables are already byte-identical in our objects (list them
with `python tools/session/vtscan.py` (and `tools/session/datascan.py` for address-named data): for each `??_7...` alias row, find the object defining
it and run match.compare). ~10 fail (a slot's function differs, e.g. `vf_214` resolving to
0xD0760); fix the class declarations or leave them. Then string literals (`??_C@...`, /GF pooled:
one piece per literal, placed where the image has it), `__real@` float constants, EH tables
(`__ehfuncinfo$...`, `__unwindtable$...`), and the RW/RWA/Bink data.

#### Placing the vtables in bulk (how it was done, 2026-10-01)

Placed so far: 61 vtables (all of unit_18F3C0's GodAsset kinds, unit_012000's and
unit_033520's). About 230 more are byte-identical in our objects and waiting. The procedure:

1. List the candidates (one line per vtable: address, symbol, object, the check's result):
   ```
   python tools/session/vtscan.py > build/tooltmp/vt_all.txt
   ```
   It takes every `??_7...` row of config/aliases.txt, finds the game object that defines that
   vtable, runs match.py's compare on it, and lists the identical ones not yet placed. A few
   (about 10) fail because a slot names the wrong function (the class declaration is wrong);
   leave those or fix the class.
2. For one unit at a time:
   ```
   ADDRS=$(python tools/session/bulkvt.py build/tooltmp/vt_all.txt unit_XXXXXX)
   CMUNIT=unit_XXXXXX python tools/cmf.py -m "data: unit_XXXXXX's vtables in their own .rdata ranges (M5)

   Co-Authored-By: ..." $ADDRS
   ```
   bulkvt.py runs datapieces.py --apply (a splits.txt range per vtable, alias rows for slot
   functions that are not placed yet, with the image's slot value as the address), restores
   config/compiled.txt (cmf adds the rows), and inserts the `// match: ??_7... @ 0x...` lines in a
   block before the unit's first `// match:` line. cmf's -m header commit takes splits.txt and
   aliases.txt; then one commit per vtable.
3. To do all units unattended, loop over the units in vt_all.txt (one cmf at a time, never two):
   ```
   for u in $(grep "^0x" build/tooltmp/vt_all.txt | awk '{print $3}' | sort -u | sed 's|build/src/recovered/||; s|\.obj||'); do
     ADDRS=$(python tools/session/bulkvt.py build/tooltmp/vt_all.txt $u) || continue
     CMUNIT=$u python tools/cmf.py -m "data: $u's vtables (M5)" $ADDRS > build/tooltmp/cmf_$u.txt 2>&1
     grep -q "^pushed" build/tooltmp/cmf_$u.txt || { echo FAIL $u; git checkout -- src/recovered/$u.cpp config; }
   done
   ```
   Each unit takes a few minutes (cmf's builds). Re-run vtscan.py first if code changed since
   the listing (it skips already placed addresses).

#### XDK EH funclets (2026-10-02)
The XGraphics/D3DX/libcpmt members' EH unwind funclets sit in `.text` at 0x309000–0x3096E0 (each
member function's own `.text$x` COMDAT: funclets, then its `__ehhandler$`). 58 are placed from the
build/xdk objects by `tools/session/xdkeh.py` (prints `PIECE ADDR OBJ NAME` rows; picks among
byte-identical sections by the chunk's owner, cuts the range at a handler that has no range of its
own). The rest print `NONE`/`AMB`: their section is not a whole range (the IDA chunk spans several
members' funclets) or the owner is not a placed function; extend the script for those.

#### Bulk data placement (2026-10-02)
`.rdata` went from 1.4% to ~85% placed and `.data` (file-backed) is about half done, with these
tools (each reruns safely; loop them until they place nothing, then `tools/build.py`):
- `tools/session/datafind.py` — every data symbol our objects define that placed code (or placed
  data) references: the image address comes from the reference's encoding; each piece is checked
  with match.compare and with xbelink's own resolution order. Writes build/tooltmp/datafind.txt.
  Compiler-numbered labels in source objects get stable names `BASE>OFFSET` (coff.find_function:
  the symbol the relocation at OFFSET inside BASE targets; `__ehhandler$F>1` is F's funcinfo).
- `tools/session/dataplace.py --src|--xdk [--apply]` — one owner per address, a range cut out of
  the binary range, compiled rows, and for source objects a `// match:` block before the unit's
  first match line. Names several objects reference at different addresses (duplicate `__real@`
  copies in the image) are skipped.
- `tools/session/slotalias.py --apply` — alias rows for names data pieces cannot resolve (declared
  virtuals placed under database names, folded deleting destructors), from the image's encoding,
  only when every reference agrees.
- `tools/session/xdkdata.py --apply` — library data by name: the member that defines a referenced
  external, extracted and placed (xvoice codebooks, CRT tables).
- `tools/session/datapad.py` — all-zero gaps after placed data join the piece before them.
- `tools/img2data.py` — library data the libraries do not hold (DOLBY, XON_RD, D3D tables) as MASM
  data stand-ins (src/xdk/standin_data_*.asm).
- `tools/session/datarefs.py MIN` — who references each remaining binary data range.
Left (2026-10-02, ~190 KB): Bink's BINKDATA tables (`_S`, `_YUVTables`, ... defined nowhere),
game `.data` globals and tables declared `extern` but never defined (script command tables,
`dword_428A30`...; each unit's data is contiguous in link order, so the owner is the referencing
unit that fits between its neighbours' placed data), `.rdata` constants likewise (`flt_`/`stru_`),
~70 vtables that differ (a slot's function or a class declaration), the RW/RWA globals, the
three XBE inserted-file sections, and the strings those tables point at.

### 9.5 After that
PLAN M7 (authentic link: library member granularity for the XDK stand-ins, real names for the
`_unk_XXXXXX` address externs in the `.asm` transcriptions). Read PLAN.md for its definition.

---

## 10. A complete worked example (sub_1ACBA0, matched 2026-10-01)

1. Notes said: frame 8 bytes larger, and `others()` register step. It sat in
   `src/recovered/unit_1A8B20.cpp` as a "Not yet matched" body.
2. Swapped `get_unk_B0()->others()` for `get_unk_B0_checked()->others_checked()` (existing
   variants from the vote calls) → registers fixed, frame still `sub esp, 0x1AC` vs `0x1A4`.
3. Inline-budget probe: added `inline void nop_x() {}` and k calls before the closing brace:
   k=2 gave `0x1A4`. Probed positions: any position after the message texts worked.
4. Tried natural inlines in pairs: `show_message(l114)` for `sub_EACA0(l114, 0, 0)` and
   `hosting()` for `unk_4F61F8.unk_104` gave the frame — and the same pair fixed the sibling
   `sub_1AD750`'s frame: evidence enough. Added both to headers with Evidence comments.
5. One slot left: the mask local `ebp_12A` sat at -0x12C. No name moved it; passing the call
   result straight into `sub_1DDDB0(&lcl_128, ...)` (no local) matched.
6. Added EH lines from `chunk_of_1ACBA0` (0x302AE0) and the handler (0x302AEB), checked with
   `match.py`, updated units.md, committed with
   `CMUNIT=unit_1A8B20 python tools/cmf.py -m "match: ..." 0x1ACBA0`.

## 11. Commit message style
- `match: <short description> sub_XXXXXX` (one function), e.g. `match: the network update sub_1A2A80`.
- `match: recover type_X::sub_Y` (cmf's per-function replay commits use this form).
- `docs: <what>` for notes/drafts, `types: <what>` for header-only commits.
Always end with the attribution trailer.

## 12. Memory notes
Earlier sessions' lessons live in `docs/session-memory/` (copy of
`C:\Users\Jordan\.claude\projects\C--codfh-match\memory\`). `MEMORY.md` is the index; every
entry is one lesson with **Why** and **How to apply**. When a function behaves strangely, grep
that directory for the instruction pattern or the concept (e.g. `grep -ril "fdivr" docs/session-memory`).
