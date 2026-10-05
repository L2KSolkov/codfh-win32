# Toolchain identity (M0)

Compiler: `C:\XDK\xbox\bin\vc71\CL.Exe` **13.10.3077** (VS.NET 2003 RTM), invoked by
`tools/build_probes.py` with `INCLUDE=C:\XDK\xbox\include`.

A second compiler, **VC7.0 13.00.9466** (`C:\XDK\xbox\bin\vc70\CL.Exe`, with its `C1.Dll`,
`C1xx.Dll`, `C2.Dll`, `MSPdb70.Dll` and `msvcr70.Dll`, copied from the June 2002 XDK 4627's
`xbox\bin\vc7`), built **RenderWare Audio** (`src/rwa/`) and RenderWare's **RtFS** toolkit
(`src/rw/tool/fsyst/`). A `config/flags.txt` rule selects it with the pseudo-flag
`/compiler:vc70` (read by `tools/build_probes.py` and `tools/ibuild.py`, never passed to the
compiler). The evidence: these libraries are padded with `nop` (VC7.0 pads inside each function's
section; the linker pads VC7.1 objects with `int3`), encode `[esp]` operands with an explicit zero
displacement, never delay callee-saved pushes, and schedule stack adjustments as VC7.0 does; every
function VC7.1 had matched in them also matches under VC7.0, and functions VC7.1 could not match
(`_rtFSInit`, `_rtFSManagerFOpenOnFS`, ...) match under it. Their `config/splits.txt` ranges run to
the next function, since the padding now comes from the object.

Every game flag must be proven — either by a probe that breaks without it, or by evidence in the
image itself. `python tools/flag_audit.py` re-derives the probe column.

## Flags

| Flag | Status | Proof |
|---|---|---|
| `/Od` | **proven (probe)** | adding `/O2` breaks p01–p05 |
| `/GS` | **proven (probe)** | dropping it breaks p02 (`sub_72990`) and p05 (`sub_E0220`) |
| `/EHsc` (≡ `/GX`) | **proven (probe)** | dropping it breaks p03's destructor, funclet and handler; `/GX` is identical |
| no `/arch:SSE` | **proven (probe)** | adding it breaks p04 (`sub_FD980`) — unlike the XDK samples, the game did not use it |
| not `/G7` | **proven (probe)** | `/G7` breaks p04 |
| `/GF` | **proven (image)** | without `/GF` VC7.1 still emits read-only literals, but as plain per-object sections (`$SG628`); with it they are mergeable COMDATs (`??_C@…`). The image has exactly one `"%s"` (`0x3D4A88`), shared by 14 functions from `0x87250` to `0x21BA50` — cross-object pooling. Aligned text literals in `.rdata` never repeat |
| `/Gy` | **proven (image)** | 11,460 functions start 16-aligned with `0xCC` fill; `/OPT:ICF` folding needs COMDATs |
| `/GR-` | **proven (image)** | the image holds only 4 type descriptors, all CRT/STL exceptions |
| `/MT` | **proven (image)** | the XBE library table lists LIBCMT and LIBCPMT, and real LIBCMT members match (below) |
| `/D_XBOX` | required to compile | XDK headers gate declarations on it (`DSound.h` speaker constants and `mmtime`, `XGraphics.h` `XGSetPaletteHeader`, `uix.h`); it changes no code |
| `/DNDEBUG` | consistent (image) | only the CRT's `Assert.h` reads it, and LIBCMT's `assert.obj` is absent from the image (none of its strings occur), so no CRT assert survived |
| `/G6` | no observable effect at `/Od` | `/G5` and the default produce identical probe bytes; kept from the XDK samples' Release settings |

## The in-project RenderWare (rtdict, UV animation)

RenderWare code the game built itself (0x22B1B0–0x22CB5B: RenderWare 3.7.2's `tool/dict/rtdict.c` and
`plugin/uvanim/*.c`) compiles to the image's bytes with RenderWare's own release flags, not the game's:
`/O2 /Ob2 /G6 /Gy /arch:SSE` (the float zeros are `xorps`/`movss` stores) with `RWGLOBALSIZE` defined (0x4000: the engine plugin registry's maximum in the image),
which makes `RwEngineInstance` the static `ourGlobals` array (0x5200E0) read directly (`call [0x520218]`)
instead of through a pointer. The SDK's generated `null`-target headers from `D:\RW_372_src` serve,
vendored in `include/rw/sdk` with two changes to `RwGlobals`: the drop's added `debugLogFunc` (a third
party's "Jaewon 20050603" edit) is left out, and 0x2C unknown bytes precede `stringFuncs`, where the
image's 3.6 Xbox layout has them. Proven by 47 functions (config/flags.txt `src/rw/*`).

## Bink: RAD's Xbox library (docs/reference/Bink)

The user supplied RAD's `binkxbox.lib` with `BINK.H`, `BINK2.H`, `rad3d.h`, `radbase.h` and
`radmem.h`. The library has 35 members (`D:/Devel/Projects/bink/Build/temps/Xlib/*.obj`). Their
symbol tables name every function, static ones included, and give the original unit split. In a
first comparison by name, 75 of 112 functions are byte-identical to the image after relocation
masking; the rest are drift or name mismatches still to check. The `@comp.id` records give the
toolchain:

- C units: `0x1C` build 9466, VC7.0 13.00.9466 (`/compiler:vc70`).
- C++ units `binkds` and `yuv`: `0x1D` build 9466.
- The colour converters (`rgb*`, `yuy2*`, `yuv32`): `0x12` build 8444, MASM 6.15.8444. These are
  the hand-written assembly units.

Extract the members with `Lib.Exe -list` / `-extract` (C:/XDK/xbox/bin/vc71). Names taken from the
library are evidence for renaming the database's `sub_` functions.

The image does not link this library build. Its Bink is a later release: no version string
survives (only the 1994-2002 copyright banner, which 1.5s has too), but its structure layouts are
BINK2.H's (Bink 1.6c, 2004-01-20; `rad3d.h` in the folder is a copy of it), with
`BINKSND.NoThreadService`, `BINK.rtindex` and `BINK.skipcount`/`toofewskipstomask`, and its code
has 1.6 changes (a signed handler priority in `RADCB_allocate_handler`, `SetThreadPriority` in
`request_free`, null checks in `my_wait_for_2`, table lookups for the audio band scales). Whether it
is 1.6c itself or an earlier release with the same layouts is not known; "1.6" below means that. The library still names the functions and gives
their order and shape; `tools/objlist.py` lists a member with its relocation targets.

The image's Bink compiles with **VC7.1** (13.10.3077, the default compiler) and
`/O2 /QIfist /Gy` (`src/bink/*` in `config/flags.txt`):

- VC7.0 reproduces neither `checksound`'s register-passed parameter nor its loop shapes; VC7.1 does.
- `/QIfist`: the float-to-integer conversions are inline `fistp qword` with no `__ftol2` call (the
  library has the same), in `BinkOpen`'s sound-rate scaling.
- `/O2` (with its `/Ob2`): the static helpers called once are inlined (`add_sorted`,
  `remove_cb_from_list`, `conv16to8`); `/Os` and `/O1` are further off.

RAD's `mult64anddiv`/`mult64andshift` are `__inline` functions of inline assembly (`mul`, then
`div` or `shrd`): compiled that way they give the library's stand-alone copies byte for byte, and
inlined they give the image's pattern of spilling the operands to the stack and reloading them.
`src/bink/binkint.h` keeps them as `__asm`, which the audit allows for Bink only (see
`tools/audit_sources.py`).

RAD's hand-written colour converters (`rgb*`, `yuy2*`) are `.asm` units in `src/bink/`, built with
the installed `ml.exe` 14.51 (`ML` in `tools/build_probes.py`; the unit's cl flags do not apply)
and annotated `; // match:` like C. Two differences from MASM 6.15 are handled:

- **Alignment fill.** `ALIGN 16` in ml 14 pads code with `jmp`/`int3`; MASM 6.15 used no-op
  instructions. `src/bink/masm6.inc`'s `ALIGN16 segstart` emits MASM 6's fill (7 bytes
  `lea esp,[esp+0]`, 6 `lea ebx,[ebx+0]`, 5 `add eax,0`, 4 `lea esp,[esp+0]`, 3 `lea ecx,[ecx+0]`,
  2 `mov edi,edi`, 1 `nop`, longest first), as measured in the image.
- **Zero padding.** The linker pads these sections with 0x00, not 0xCC: `tools/match.py` accepts a
  zero tail up to the next 16-byte boundary, and `tools/xbelink.py` fills after a piece from an
  `.asm` unit with zeros. Where a section's file-backed bytes stop inside a unit's trailing
  `ret 4` (`00 00`), the linker drops the zero bytes the loader supplies from the virtual size.

`tools/asmgen.py LIBOBJ SECTION ADDRESS` drafts such a unit from the library member's symbols and
relocations and the image's bytes (they must be the same instruction sequence); its stderr gives
each data symbol's image address for `config/aliases.txt`.

The library's `binkds.obj` and `binkread.obj` carry `@comp.id` build 9466 (VC7.0), but VC7.0 gives
the same results as VC7.1 on the functions tried (and worse on several), so `src/bink/*` stays on
VC7.1.

## Probes

| Probe | Original | What it pins |
|---|---|---|
| `p01_empty_thiscall.cpp` | `sub_73D80` | `/Od` frame, `this` spill, `retn 0Ch` |
| `p02_gs_cookie.cpp` | `sub_72990` | `/GS` cookie stored un-XORed, checked through `ecx` |
| `p03_eh_destructor.cpp` | `sub_78B40`, funclet `0x2FF9F0`, handler `0x2FF9F8` | `/EHsc` frame, state stores, `.text$x` funclet and thunk |
| `p04_float_to_int.cpp` | `sub_FD980` | x87 arithmetic and `__ftol2`; excludes `/arch:SSE` and `/G7` |
| `p05_string_pooling.cpp` | `sub_E0220` | read-only `.rdata` literal, `sprintf` through the XDK's `<stdio.h>`, 16-byte `/GS` buffer |

`tools/match.py` verifies every relocation, not just the bytes around it: each resolves to the
exact address the original encodes, through its IDA address suffix, `config/symbols.txt`, a proven
entry in `config/aliases.txt`, or — for literals and EH tables defined in the object — the kind of
original section it lands in. All probe relocations verify.

## XDK library members matched so far (M3 evidence)

| Member | Symbol | Address | Result |
|---|---|---|---|
| `libcmt.lib` `obj\i386\secchk.obj` | `@__security_check_cookie@4` | `0x2C624C` | identical, relocations included |
| `libcmt.lib` `obj\i386\seccook.obj` | `___security_cookie` (`.data`, `4EE640BB`) | `0x435810` | identical |
| `libcmt.lib` `obj\i386\ftol2.obj` | `__ftol2` | `0x2C62A4` | identical (117 bytes) |

These fix the first entries of `config/aliases.txt` and support the plan's expectation that the
installed LIBCMT (QFE .1) is the image's.

## Facts learned along the way

- VC7.1 names EH unwind funclets with compiler-numbered local labels (`$L301`), not VC8's
  `__unwindfunclet$`; probes address them as `.text$x+OFFSET`.
  Each EH function gets a `.text$x` COMDAT of its own, so in an object with more than one,
  a funclet is named from its handler thunk instead: `__ehhandler$<function>-8`.
- EH funclets and `__ehhandler$` thunks are packed back to back in `.text$x`, which the linker
  groups at the end of `.text` (around `0x2FF9F0`), not beside their functions.
- Destructors are written as destructors: a `sub_` address that is a destructor becomes `~type()`
  with the address kept in a comment, because only a real destructor produces the EH state
  machine and the implicit base-destructor call.
- Hand-written library assembly (`__ftol2`) is packed without 16-byte padding, so a function's end
  is checked against the size the IDA database records rather than against alignment fill.

## What link.exe and imagebld.exe write (M0 step 3)

`python tools/build_trivial_xbe.py` builds `probes/xbe/trivial.cpp` into an XBE with the game's
flags, `link.exe /SUBSYSTEM:XBOX /FIXED:NO /OPT:REF /OPT:ICF` and
`imagebld.exe /STACK:0x10000 /TESTID:0x4156002A /DEBUG`, then compares its header with the original
(`tools/xbe_dump.py A B`).

| Field | Original | Trivial build | Class |
|---|---|---|---|
| base, certificate `0x10184`, section headers `0x10370`, image header size `0x184` | — | same | toolchain, reproduced |
| heap reserve `0x100000`, heap commit `0x1000`, stack `0x10000` | — | same | toolchain, reproduced |
| `init_flags` | 1 | 1 | toolchain default — the game did not pass `/DONTMOUNTUD` |
| logo bitmap size | `0x2B2` | `0x2B2` | toolchain default |
| debug path / file | `s:\COD\Game\GameCode\bin\xbox_releasemp\Game_XboxRelease_MP.exe` | the `/IN:` path | **build environment** — imagebld records the input path verbatim, so the authentic link needs that path to exist (`subst S:`) |
| XBE / PE timestamps | `0x4181A886` / `0x4181A881` (PE linked 5 s before imagebld) | wall clock | **build environment** — restored after the build |
| entry-point and kernel-thunk XOR | retail keys | debug keys | **retail artifact** |
| certificate media / region / ratings / version | `0x202` / `7` / `3` / `1` | `0x207` / `0x80000007` / `0xFFFFFFFF` / `0` | **retail artifact** (certification) |
| certificate LAN / signature keys, timestamp `0x4182A987` | real keys | `TESTTEST…` | **retail artifact** |
| `$$XTIMAGE`, `$$XSIMAGE` | inserted files (flags `0x28`, `0x38`) | absent | build input: `/TITLEIMAGE:`, `/DEFAULTSAVEIMAGE:` — the image files are recovered from the original |
| `.XTLID` | `0x950` bytes | `0xF0` bytes | toolchain — grows with the libraries linked |
| library version records | 12 | 3 (XAPILIB, XBOXKRNL, LIBCMT) | toolchain — one per library contributing a `.XBLD$V` stamp |
| section head/tail read-only flags | e.g. `.text` `0x16` | `.text` `0x36` | toolchain — computed from page sharing between adjacent sections |

`/SUBSYSTEM:XBOX` is required (imagebld error IM1012 without it); the VS.NET 2003 Xbox integration
adds it, the sample projects do not show it.

Decoded with the retail keys, the original's entry point is `0x0022F303` and its kernel thunk table
is `0x003CD300`, the first bytes of `.rdata`.

## The disabled debug print's guard (open)

The game's debug prints were disabled by a badly coded debug `#ifdef` that still compiles a
constant-false test: `xor reg, reg; jz` over a call through `off_42CD14`. In `sub_1D6550`
(`sNetGameEP.cpp`, 104 bytes) the original's guard is `33 c9` (`xor ecx, ecx`); every C spelling
tried compiles to the same 104 bytes with `33 c0` (`xor eax, eax`).

Ruled out, each compiled with the game flags and compared to the guard register and size:

- **Guard spellings:** `if (0)`, `if (false)`, `static const int`/`const bool`/enum/global
  `const` flags, `flag > 1`, `flag >= 1`, `sizeof(int) == 0`, `!1`, `(bool)0`, `(char)0`, `0L`,
  `(void *)0` - all `eax`. `0.0`/`0.0f` change the code.
- **Macro shapes:** `if (0) ...; else;`, `do { if (0) ... } while (0)`, `while (0)`, `for (;0;)`,
  `0 ? (void)call : (void)0` - all `eax`; `1 ? (void)0 : call`, `1 ? 0 : call`, `switch (0)` and
  `false ? call : 0` change the size.
- **Address tests** (`!&off_42CD14`, `!&global`, `!function`, `!__FILE__`, `!"str"`, `!this`,
  `!&local`, `!&member`) - all change the size.
- **Code-free dead expressions** before the outer `if`, before the guard or after it (`0 && call`,
  `1 || call`, `0 && 0`, `(void)(0 && call)`, `0;`, `"str";`, `off_42CD14;`) - no code, still `eax`.
- **Callee return type** (`int`, `unsigned`, `long`, `unsigned long`, pointer) against local type
  (`int`, `unsigned`, `long`, `unsigned long`) - all `eax`.
- **Literals:** a real format literal and `__FILE__` instead of `extern` arrays - `eax`.
- **Preceding functions in the same file:** no carry-over; the register is chosen per function.
- **Flags** added to the game set: `/Zi /Z7 /ZI /J /Ob1 /Ob2 /Oi /Oy- /Gs /Ge /Gh /Zp1 /Zp2 /Zp4
  /Za /Op /Gd /G5 /G7 /arch:SSE /Gf /GX /GR /Gz /Gr /vd0 /vmg /Zc:wchar_t /Zc:forScope /D_DEBUG
  /Ow /Oa /Oy /Os /Ot` - all `eax` or a different size. (From Git Bash, run with
  `MSYS_NO_PATHCONV=1`, or MSYS rewrites every `/flag` into a path and the compiler never sees it.)

**Untried lead:** a constant passed through an inline function is loaded rather than folded (see
"Constant arguments of inline functions are not folded" below); a guard spelled as an inline
predicate called with a constant (`if (enabled(0))`) may pick another register.

**The guard is not the whole gap.** The same function also differs after the guard: the original
loads `this` into `edx` for the byte store and `ecx` for the dword store (`8b 55 f8 / 88 02`,
`8b 4d f8 / 89 41 04`); VC7.1 uses `ecx` then `edx`. That is 5 differing bytes, not 1. It does not
depend on the guard: the code after the guard is the same whether the guard is compiled C or the
two inline instructions `docs/PLAN.md` allows. So the plan's guard exception fixes the guard, and
the stores after it are still an open register-choice difference.

Further ruled out (the stores after the guard follow the same rotation, so a fix has to shift it by
exactly one step at the guard with no code): the reader passed by reference or as a derived type;
its parameter types; the compare's constant type and form (`13u`, `(char)13`, enum, `static
const`, casts on the local, `!!(...)`, `0xD`); `this->`; members in a base class; `register` or
`volatile` locals; `__noop`, `__assume`, labels, empty statements, `goto` to the next line; the
unused parameter's type; line layout, with or without `/Zi`; a zero-initialised debug flag whose
assignment is compiled out (adds a stack slot and a store). `C:\XDK` holds only `C2.dll`
13.10.3077.

**Resolved (2026-10-01).** It was the register rotation after all: a compiled-out assertion
(an empty `if (!x) { }`) emits no code but moves VC7.1's register rotation on by the loads its
condition would make, and the unit has them throughout. With `SNET_ASSERT` checks placed by a
greedy search (and `arg_0 = arg_0;` in the checks), all 31 functions match from plain C, the
guards included; no `__asm` guard is needed.

## Local names decide stack slots

At `/Od` VC7.1 lays out a function's locals by name, not by declaration order. In `sub_12070`
two locals named `var_4` (pointer) and `var_8` (int) land at `ebp-8` and `ebp-4`, the reverse of
the original, whichever is declared first; named `local_4`/`local_8`, `v4`/`v8`, `var4`/`var8` or
`l4`/`l8` they land right, while `var_04`/`var_08`, `loc_4`/`loc_8` and `s4`/`s8` land reversed.
Declaration order has no effect. Measured with three `int` locals: `a`/`b`/`c` take `-4`/`-8`/`-0xC`,
`var_4`/`var_8`/`var_C` take `-0xC`/`-8`/`-4`; twelve `var_N` locals come out in the order
`var_20, var_C, var_28, var_14, var_24, var_8, var_4, var_18, var_2C, var_1C, var_10, var_30`.
No simple string hash modulo a table size (sum, multiplicative, shift-xor, rotate, for sizes up
to 600) reproduces that order, so names are found by search rather than computed:
`tools/local_names.py` tries the slot-stating forms `docs/PLAN.md` lists until the function
matches.

The same constant guard compiles faithfully elsewhere. In the first unit, `sub_14520` and
`sub_14930` (`if (0) { ... }`, guard `xor edx, edx`) and `sub_14600` (`if (1) { ... }`, `mov edx, 1;
test edx, edx`) match from plain C, register included. So the guard itself is not the problem;
what differs in `sNetGameEP.cpp` is specific to that unit.

The order is a fixed ranking of names, even though no simple hash computes it: compiling one
function that holds every candidate name as an `int` local gives each name a frame offset, and any
subset of those names then takes slots in that same relative order. `tools/local_names.py` uses
one such probe to pick names (verified against every function picked by exhaustive search so
far) and confirms the pick with a real compile, so six locals take under a second instead of up to
117,649 compiles.

The ranking breaks down with many locals, and the reason is now measured: the compiler walks a
16-bucket hash table, and locals in the same bucket come out in reverse declaration order. With
eleven `var_N` locals, `var_20`/`var_C`, `var_28`/`var_14` and `var_24`/`var_8` share buckets and
swap when the declarations are reversed; use order has no effect. `tools/local_names.py` measures
each candidate name's bucket with two probes (declared forwards and backwards), declares the
locals from the highest slot down, and picks forms whose buckets never decrease with the slots.
`sub_12B20`'s eleven locals needed the extra forms `ebp_N`, `stk_N` and `slot_N` to find a
combination at all.

## Realigned frames: `/Zi` gives the image's 8-byte reserve

A function with a 16-aligned local gets an `ebx` frame: `push ebx; mov ebx, esp; sub esp, K;
and esp, -16; add esp, 4; push ebp; ...`. In the image K is 8 in every one of the 253 such
functions (`53 8b dc 83 ec 08 83 e4 f0`). Without debug information CL 13.10.3077 reserves 4, as
`push ecx` (`53 8b dc 51 83 e4 f0`), whatever the alignment, types, `/G5`/`/G7`, `/GS-`,
`/arch:SSE`, or `/Zp` setting. With `/Zi` (or `/Z7`) it reserves 8 exactly as the image does, and
nothing else in the code changes: every existing match survived the switch. So the game was built
with debug information on, and `config/flags.txt` gives `src/*` `/Zi`
(`tools/build_probes.py` adds a per-object `/Fd`).

What the alignment does establish: the local is 16-aligned. For `sub_19F90` that local is an
`RwMatrix` copied from `RwFrameGetLTM`. So the Xbox RenderWare build aligns `RwMatrix` to 16, and
`include/rw/ostypes.h` defines `RWALIGN` that way.

## A test on a materialised `||`

`sub_205E0` computes `a || b` into a compiler temporary (`mov t, 0` / `mov t, 1` on the two
branches), then tests that temporary with `cmp t, 0; jz` and stores 1 or 0 into a named local.
`if ((a != 0.0f || b != 0.0f) != 0) v = 1; else v = 0;` compiles to exactly that; `!= false` does
too. These do not: `v = (a || b) ? 1 : 0`, `!!(a || b)` and `(int)(a || b)`, which all copy the
temporary across; `((a || b) != 0) ? 1 : 0`, which uses `setne`; and a plain `if (a || b)`, which
branches without a temporary.

## `/Ob1`: inline functions are expanded

The game code is built with inline expansion on (`/Od /Ob1`), not the `/Ob0` that `/Od` implies.
There are two independent pieces of evidence:

- **An accessor's temporary.** `sub_19CA0`, `sub_1FDF0` and `sub_21A90` load an entity's `+0x340`
  frame pointer into a temporary and copy that into their own local:
  `mov edx, [ecx+340h]; mov [t], edx; mov eax, [t]; mov [frame], eax`. `t` always sits in the
  lowest slot just above `this`, where compiler temporaries go, not where a named local's hash
  puts it. Under `/Ob1`, an inline function that keeps its result in a local,
  `RwFrame *f = unk_340; return f;`, expands to exactly that. A trivial `return unk_340;` stores
  straight into the caller's local, and without `/Ob1` the call stays a call.
  `type_3D3548::get_unk_340` models it, and `sub_19CA0` and `sub_1FDF0` match with it.
- **`fabs` on a float.** `sub_1DF60`, `sub_1B710`, `sub_1A950` and `sub_213B0` call the CRT's
  `_fabs` on a float widened to double. In C++ the XDK's `math.h` resolves `fabs(float)` to an
  inline overload (`fabsf`, then `(float)fabs((double)_X)`). Under `/Ob1` that expands to
  exactly the image's code; under `/Ob0` it stays a call to `?fabs@@YAMM@Z`.

How inline expansion orders its temporaries, which the frame then shows (read them from a `/FAs`
listing: `$T` temporaries and inline locals sit above `this`, `tv` spill temporaries below):

- They go in the order they are created, and an inline's argument copies are created as it is
  expanded, callee after arguments: `h(fabs(x))` gives `fabs`'s argument, then `h`'s.
- A `const &` argument's temporary is created while parsing, so every such temporary in the
  function comes before every expansion temporary, not interleaved call by call.
- A boolean an inline function returns sits among the `$T`s when it returns `1`/`0` from
  branches, but is a `tv` below `this` for `return a < b;`.
- `sub_29FC0`'s helper, `abs_lt_150`, shows all three: per call, its local holding `fabs`'s
  result, its argument, its result.

Two switch facts from `sub_17BF0`:

- An empty case (`case 6: break;`, or with `{}` or `;`) is folded into the switch's exit: the jump
  table points past the switch. A case whose body is a call to an empty inline function keeps a
  label and a `jmp` of its own, which is what the image has for states 6, 38 and 42.
- An inline member's `this` goes into a temporary only when it is not a plain load: called on a
  field loaded from a call's result (`vf_008()->unk_610->get_unk_04()`), it takes the temporary,
  and that expansion is evaluated before the other operand of the expression.
  A sum passed to it comes out with every operand loaded before any add:
  `fabs(RwV3dDotProduct(&d, &d))` is `z*z, y*y, x*x, faddp, faddp` (`sub_2AC00`). The same macro
  anywhere else is `x*x, y*y, faddp, z*z, faddp`, so the load order does not reveal how the
  source ordered the terms.

Every previously matched function is unchanged under `/Ob1`, since none calls an inline
function. `config/flags.txt` now has `/Ob1` for `src/*`.

## `/GS` and byte arrays in local structs

`/GS` adds a security cookie to any function with a local "string buffer", and to VC7.1 that
includes a local struct that merely contains a byte array. A placeholder struct padded with
`RwUInt8 unk_NN[k]` therefore gives a function a cookie the image does not have, as with
`sub_28470`'s local node-search request. Pad such types with dword or word arrays when they are
used as locals. The image's own byte arrays in locals (real `char` buffers) do get the cookie.

The cookie (`__$ArrayPad$`) goes directly above the buffer, and the buffer keeps its place in
the locals' hash order, 8-aligned: a buffer that sorts first leaves a 4-byte gap between the
cookie and the frame top, while one named local sorting before it fills that gap and puts the
cookie at `ebp-8` ("EfuncPlaySound", `sub_5E880`, and "EfuncPlaySoundOnNamedEntity",
`sub_5EC30`, which need the key pointer's name to sort ahead of the buffer's).

## Two more `/Od` shapes

- `v.y == 1.0f` compiles to an integer compare, `cmp dword ptr [v.y], 3F800000h; jnz`, while a
  compare with `0.0f` uses `fucompp`. So a raw bit-pattern compare in the image is plain float
  equality in the source (`sub_1CFE0`).
- A difference of two call results comes out two ways. Written out per component,
  `a.x = e->p()->x - f->p()->x` keeps the first result in `esi` (saved in the prologue) and loads
  both floats after the second call. Through the `RwV3dSub` macro, the first float is loaded at
  once and spilled to a temporary across the second call (`fstp t` … `fsubr t`). So `esi` there
  means explicit statements, and a spilled temporary plus the macro's `xor; jnz` means
  `RwV3dSub`.

## Switch jump tables

M0's switch case is proven by a game function rather than a probe: `type_154C0::sub_17A20`
(`switch` on `unk_578`, 20 cases sharing one body) compiles to the original's code followed by its
two tables (a 4-byte address table and a byte index table) in the same section, 30 bytes past the
end IDA records, with every table entry's relocation resolving to the original label.
`tools/match.py` accepts a piece longer than IDA's function size only when no other function starts
in the extra bytes, and reports the table bytes it compared.

## Local structs take a multiple of 8 bytes

A local struct whose size is not a multiple of 8 still occupies the next multiple of 8 in the
frame: a 100-byte struct between two ints leaves a 4-byte hole. So a frame gap next to a struct
local usually means the struct is modelled too large. The node search request was first modelled
as 0x64 bytes (the gap between AIData's members allows it); `sub_27EB0` and `sub_28470` only match
with 0x60, which is also all `sub_F8970` touches.

Declarations with initialisers (`RwInt32 n = 32; request r; graph *g = &unk_4C00E8;`) fix those
locals' declaration order, since the initialisers run in it. The others can still move, and a
bucket walk that forbids a tie between two locals declared in the wrong order finds names for the
rest.

`tools/scope_names.py` does that walk: it takes the slots of each scope as a group (block-scoped
locals come out after the function-scope ones, each scope in its own bucket order) and a
`--strict A:B` for each pair whose declaration order is pinned the wrong way round.

Scopes are laid out in order too: the function's own locals, then block-scoped ones, a shallower
scope's before a deeper one's and sibling scopes in source order, each scope in its bucket order.
`sub_1C4F0` runs the same line test twice, each time with two initialised locals; the second pair
lands nearer `ebp` than the first, which only fits if the first pair is in braces of its own
(inside an `if`) while the second is declared in the middle of the enclosing block (C++ allows
it).

## A temporary copied into a default-constructed member

`T(0)` then `T(const T &)` on the member then `~T()` on the temporary, with the temporary's
address taken by `lea` (no return-value slot), is a default-constructed member whose only
default constructor is the copy constructor with a default argument: `T(const T &a = 0)`, the 0
converted through `T(P *)`. This compiler elides every spelled-out form (`m(T(0))`, `T v = 0`,
casts, reference casts) and binds a converting or derived temporary through the constructor's
return value. The class's `default constructor closure` is then the same three calls in a
function returning nothing (kujuUI's pointer, `type_E8780`; `type_DC400`'s constructor).

## An inline's `this` copy

An inline member copies a non-constant `this` (an array element, a call's result) into a slot of
its own only when its body uses `this` more than once: `std::string::c_str` does (`_Myres` and
`_Bx`), the XDK's `operator=` (`return assign(_Right);`, then `assign(_Right, 0, npos)` out of line)
does not, and a constant address (a global) is always substituted. The HUD's build
(`type_DC400::sub_E0E90`) assigns its objective texts through a copy, so their element type's
assignment is `{ assign(s); return *this; }` (`type_4B89B0`).

## A global's `this` copy and a class local constructed mid-block

A member inline called on a global pointer (`g->get()`) substitutes the global and takes no
slot for `this`. A copy of the global in an inline slot of its own, then the member's result,
is a static inline getter with a result local (`T::get()->get_x()`: the HUD's scoreboard,
`type_DC400::sub_E7EF0`, through `type_4F8054::get`).

A member inline *setter* on a global pointer whose argument is itself a global is different:
`g->set(v)` copies `v` into a slot, then `g` into the next, then stores
(`mov edx, [v]; mov [t1], edx; mov eax, [g]; mov [t2], eax; mov ecx, [t2]; mov edx, [t1]`).
A free inline doing `T *h = g; h->f = arg;` gives the same code with the two slots swapped
(the pause menu's options, `sub_18E380`, `type_DC400::set_unk_1A020`). A free inline setter
`g->f = arg` stores through one slot, the argument's (`set_4F28F0_unk_14`).

A class-type local constructed in the middle of an `if` block (a `std::vector`, after other
statements) takes its slot among the block's locals, which all follow the function's own: in
`sub_E7EF0` the counters are the function's and the colour, buffer, place and name are the
block's, declared before the vector. An early `return` instead of the block gives the right
slots but `jne; jmp` for the image's `je`.

## Constant arguments of inline functions are not folded

The front end folds every constant index (`a[0]`, `a[!1]`, `a[(int)(void *)0]`, `a[1 ? 0 : 1]`,
`a[0 * x]`): the store is `mov [reg+0x364], v`. A constant passed to an inline function is
substituted after that, so `void set(RwInt32 i, RwInt32 v) { a[i] = v; }` called as `set(0, v)`
loads it: `xor ecx, ecx; shl ecx, 2; mov [edx+ecx+0x364], v` ("DetachProp",
`type_3D3548::set_unk_364`). A constant argument gets no slot of its own.

The exception is a parameter narrowed by a cast where a signed type is involved: with
`RwInt32 c`, `*p = (RwChar)((RwUInt8)c & 0xFF)` stores a constant argument into a slot first,
where `RwUInt32 c` substitutes it (`xor ecx, ecx; and ecx, 0xFF`) and still reads a variable
argument's low byte (`movzx ecx, byte ptr [v]`); the font's `FONT_PUT`, `type_DA580::sub_DBB80`.
A shift count is the same: a signed `RwInt32` count parameter is stored into a slot and shifted
by `cl`, an unsigned one is substituted, and a zero count then survives as `shl ecx, 0` (a
literal, enum or `const` zero is folded away whatever its type). The kind-0x2E GodAsset's
handler (sub_195F40) shows it through `get_ref_low`.
Inline parameters and result locals take their slots in source order, all before `this`, so two
slots there that no code uses are two `unused_slot()` expansions after the last inline.

Within one inline, though, its locals' slots follow their names the way a function's named locals
do, not their declaration order: `get_ref_kind` and `get_ref_kind_direct`
(types/type_3DF8D8.h) only match once their locals are renamed (a search over names, as
tools/climb_names.py does for a function's own locals; sub_190900, sub_191300).

## When inline arguments and `this` copies get their temporaries

For `e->vs()->set(t->get())` with `get` holding its result in a local (`r`) and `set` taking
`const unsigned &`, this compiler copies `r` into a `$T` for the reference and the call result into
a second `$T` for the setter's `this`: the image's instruction sequence exactly. But it numbers the
reference's `$T` while parsing, before the inline expansion creates `r`, so that `$T` takes the
slot nearer `ebp`; the `this` copy is numbered at expansion. A by-value `set` gets no copy at all
(the argument is substituted), and one that writes its parameter gets the order right but adds a
store. `type_3CE5E8::sub_3A450` needs the copies in source order and stays binary.

## Flag bits to `bool`

`b = (x & m) != 0` compiles to `and; neg; sbb; neg` (for a `bool` or an `int` destination), while
`(bool)(x & 1)` folds to a bare `and` and `(bool)(x & 2)` gives `setne`. The same test returned by
an inline `bool` function gives `and; neg; sbb; neg` too, and widening that return to an `int` adds
`movzx`, which is how the script VM's call opcodes (`sub_69770`) store their flags. The inline
takes no frame slots for its arguments.

## A short packed after the locals

A named `short` local takes a four-byte slot of its own, and a cast written in place takes none.
The `short` an inline function returns is kept in a temporary packed two bytes below the last local
(`ebp-6` after a pointer at `ebp-4`), written where the inline expands and read where it is used,
so an index computed that way is stored before a call and loaded after it (`get_operand` in the
script VM's local opcodes, `sub_69CF0`). An inline's `short` parameter packs the same way but is
loaded before the call.

## Value before destination

`p->f = e` loads `p` before the value for a named local, a result-local inline, an inline setter or
a chained assignment alike. An inline that returns a four-byte struct with no local
(`H get() { return h; }`) copies it into a return temporary and stores that value before loading
`p`, so the image's value-first stores of a handle (`sub_6B9A0`, `type_67620::get_unk_04_h`) come
from a struct copy.

## A copy of an uninitialised temporary

In a conditional's arm, an inline with no result local (`T *get() { return p; }`) first copies its
return temporary, not yet written, into the conditional's temporary, then stores the value there:
`mov ecx, [t1]; mov [t2], ecx; mov eax, [x+off]; mov [t2], eax` (`sub_6C5A0`,
`type_4CFE30::get_unk_AC`). The read of a slot nothing wrote is that inline.

## A ternary arm that is a plain float is copied with `mov`

`c ? -x : x` with `x` a float field stores the second arm into the ternary's temporary with
integer moves; the image's `sub_74A30` loads and stores it through the FPU (`fld x; fstp t`).
A cast on that arm, `c ? -x : (RwReal)(x)`, gives the FPU copy. The same function's macro leaves
its argument unparenthesised where it negates it (`ABS(a - b)` gives `fld a; fchs; fsub b`), so
the image's magnitude macro is `((x) < 0 ? -x : (RwReal)(x))`.

Separate locals whose slots run on without a gap next to a 12-byte vector are one struct local:
`sub_74A30`'s nine "locals" from −0x34 to −0x5 (two vectors among them) are a 48-byte struct
whose members it passes one by one; modelled as separate locals, no names order them.

## /GS takes plain `char` arrays only

`sub_76290`'s ten-byte flag array (read with `movsx`) only gets its cookie (`__$ArrayPad$`, just
above the array) as `char`; as `signed char` (`RwInt8`) the function has no cookie. In the frame
the array keeps its place in its scope's bucket order, rounded to 12 bytes with the cookie above
it. A key struct zeroed mid-function among function-scope slots cannot have a constructor (the
constructor would run at the declaration): it is plain data zeroed by statements.

## An aligned member pads the vtable pointer

In a class with its own vtable pointer, a `__declspec(align(16))` member (the aligned `RwMatrix`)
makes the compiler pad the pointer to 16 bytes, so every field moves by 12. The animation player
(`type_7C8D0`, 0x1C0 bytes) has two matrices at +0x100 and +0x140 and its first field at +4, so its
matrices are declared as the unaligned `RwMatrixTag`; with `RwMatrix` it grows to 0x1D0.

## Inline functions that are not inlined, and placement delete

VC7.1 at /Ob1 does not inline an in-class function (or a class's in-class destructor) that
deletes. It emits the body as a COMDAT and calls it. The caller's frame still keeps the
temporaries the expansion would have used, 8 bytes for such a destructor, and these nest. A
function whose frame is a little larger than its locals and temporaries account for, next to
such a call, is showing this. unit_0824A0: `~type_837D0` is defined in its class, and its
callers `sub_83760` and `sub_85730` each have 8 spare bytes; `~type_4B1CA0` calls the in-class
`sub_83760` and has 16. An `inline` function that news something is not inlined either.
`__forceinline` inlines it.

When a placement `operator delete` matching the `operator new` is declared, VC copies the
result of each `new (args) T` through one extra temporary: `p = $T2 = ($T1 ? ctor($T1) : 0)`.
This happens even when the constructor cannot throw and no EH state is set up. So when the
image shows that extra copy, declare the matching delete: `void operator delete(void *,
RwUInt32)` for the game's `operator new(size_t, RwUInt32)` (include/types/soundbank.h).

## Products through RenderWare's vector macros

`RwV3dDotProductMacro(&plane, (RwV3d *)point)` puts the memory operand first in its y and z
products (`fld [ecx+4]; fmul local`) and the local first in its x product. The same sum
written out as `plane.x * p->x + p->y * plane.y + ...` always puts the local first. That holds
in every operand order, with `(&plane)->` spelled out, and with array access. `sub_8F3E0`
matched only through the macro. `sub_92620`'s cross and dot products show the same split.
When a product of a local and a pointed-to float comes out in the wrong order, try the
RenderWare macro that would have produced it.

## Findings from the RWS behaviours (0xA2000 to 0xB0200)

- **Float equality with a constant.** `if (flt_429190 == 10.0f)` on a global `RwReal` compiles
  to `cmp dword ptr [0x429190], 0x41200000; jne` with no FPU (SectionInfo's `sub_AFE00`).
- **An argument copied into a temporary before an FPU load** (`fstp var; mov edx, var; mov
  [t], edx; fld [t]`) comes from an inline that takes a `const RwReal &`. `tanf(var)` substitutes
  the argument (CMountedWeaponBehavior's `sub_A4B00`; `tan_ref`, include/game/mathutil.h).
  A member or array element (`this->a[0].x`) binds to the reference with no copy, and a cast to
  its own type does not help (this compiler keeps it an lvalue); `f(+a[0].x)` makes the rvalue that
  gets the `$T` (the message box's layout, `type_4EBE00::sub_1889C0`, `scale_screen_x`).
- **Default first.** A switch whose default body comes before the case bodies, with no jump to
  it (`cmp; je case; <default>`), has `default:` written first (RenderTrigger's `sub_AF270`).
- **Stores before the member constructors** are mem-initializers
  (`: Trigger(attr), unk_C0(1), ...`; MountedWeaponTrigger's `sub_A53E0`).
- **Locals declared in the case blocks** of a big attribute switch take their slots in the
  blocks' source order, after the function's own locals (ProjectileGeneratorTrigger's
  `sub_AD730` matched without tuning once each case declared its own).
- **A struct of arrays** whose compiler-written constructor has loops is not expanded: it gets
  its own function (CustomTrigger's `type_A2F70`, `sub_A2F70`). An array of structs with a key
  member is constructed inline, in a counted loop (`sub 1; js`; ParticleTrigger).
- **ICF folds identical EH handlers.** When a constructor and destructor have the same unwind
  (just `~Trigger`), one handler serves both. Annotate the one kept and alias the other
  (PickupTrigger).
- **IDA's `chunk_of_<fn>` ranges in .text$x** can also swallow the next function's funclets
  (see the placement-link note on MI thunks).
- **A float copied through the FPU** (`mov [t], edx; fld [t]; ... fstp [dst]`) where a plain
  `dst = attrIt->GetAs_RwReal()` is two dword moves: only `(RwReal)(RwDouble)` reproduces it
  (CWeaponBehavior's `sub_C12C0`, 30 of its commands).
- **A destination computed before the command** (`lea`, then `operator->`, with the value's
  temporary created first) is an inline member of `CAttributeCommand` taking the destination by
  reference: its body's temporaries come first, then its arguments right to left
  (`GetCommandData(bool &)`, include/rws/cattributehandler.h).
- **A byte from `!= 0`** is `(bool)v` when there is no `xor` before the `setne` (and `movzx`
  when the field is a dword); `v != 0` clears the register first.
- **Five MakeNews sharing one EH handler** (0x30067F) mark one source file: CWeaponBehavior's
  and the four classes after it, whose this-adjusting thunks follow CGrenadeBehavior's
  functions.
- **An unused local keeps a slot** at the place its name sorts to, so a gap in the frame can be a
  local nothing reads (the entity's vf_208, `l20`).
- **A struct returned by value** is built in a temporary and then copied (PulseZoneTrigger's
  `type_17E3A0`).
- **Written-out vector components or the RenderWare macro**: when the image lacks the macro's
  `xor; jne` tail the components were written out (the entity's vf_0C0); when it has it, the
  macro (vf_048, vf_080).

## Findings from the entity base (0xCC8A0 to 0xD48D0)

- **A member subtracted from a local** comes out `fld local; fsub [member]`. The image's
  `fld [member]; fsubr local` comes from `local -= (RwDouble)member` (vf_070); a named
  accessor adds a `this` temporary instead.
- **Code after a `return`** is dropped only up to the next label. A `for` loop after it keeps
  its body, increment and test but loses its set-up. The frame still keeps slots for the locals
  only the dropped set-up used, so no names place them (vf_000, `sub_D34B0`, stays binary).
- **A local with a constructor** runs it where it is declared. When the image stores other
  locals first, declare it after those statements, in the middle of the block (`sub_D42D0`'s
  `type_93DF0`).
- **Three equality tests kept in a byte-tested temporary** (`mov [t], 1` / `mov [t], 0`, then
  `movzx`) are an inline `bool` function's result (`equal_v3d`, include/game/vecutil.h).
- **A subscript loads its index before the array.** The image loading the array first is an
  inline accessor taking the index by value (`type_4C00E8::get_unk_3C`).
- **A pointer local then a dereferenced copy** ahead of an inline constructor
  (`lea; mov [p]; mov [p] -> [v]`) are two named block locals. A plain argument expression folds
  into the constructor's own copy (vf_1D0's link list).
- **`acosf` and `atanf`** are `<math.h>` inlines over `acos` and `atan`: the float result goes
  through a temporary. The CRT's `_acos` and `_atan` are aliased (config/aliases.txt).
- **Slots below the temporaries with no code** come from inlines that expand to nothing but
  declare a local. Named locals, even unused ones in nested blocks, always sort above the
  temporaries (the game loop's module shutdown `sub_D7040`, `unused_slot`).
- **`!b` materialised** (`movzx; neg; sbb; inc`, then a test) is `(RwInt32)!b` inside a
  condition; a plain `!b` tests the byte directly (`sub_D56D0`).
- **`delete p` through a virtual destructor** is the null test, then the call through slot +4
  with 1 and its result kept in a temporary (`sub_D5AD0`).
- **An explicit destructor call** (`p->~T()`) adds a `this` temporary and a flags test; a call to
  pDtor (0x1E41C0) on an object with no such code is an ordinary empty method, folded by
  /OPT:ICF (`type_4B85F8::pDtor`, `type_4F2B68::pDtor`).
- **A handle copied value first**: `h = e->get()` where `get` returns a 4-byte struct by value
  (no result local) stores through a return temporary and loads it before the destination; an
  `operator=(int)` taking the value does not (`type_D48D0::sub_D48D0`).
- **`x * 2.0f`** compiles to `fadd st(0), st(0)`; `x + x` to `fadd [x]` (`sub_D4C80`).
- **A random-range macro with the low bound first** (`(lo) + rand() % 1000 * ((hi) - (lo)) *
  0.001f`) spills a computed `lo` across the `rand` call and adds it last; with two constants the
  front end folds `hi - lo` (`sub_D4950`, `sub_D4B70`).

## Findings from the movie player and the shell manager (0xE8800 to 0xEAA60)

- **An implicit constructor out of line**: a base class with no constructor of its own but
  members that have inline constructors gets a compiler-generated constructor that /Ob1 does
  not inline. It is emitted as a function of its own (`??0type_E8F90@@QAE@XZ`, 54 key members
  each zeroed through a `this` temporary), and the derived class's constructor that calls it
  still reserves the frame those temporaries would need (`sub_E8F40`'s 0xDC bytes for one
  `this` slot).
- **Locals above the /GS cookie**: in a function with a cookie, the cookie sits directly above
  the char arrays, and locals whose names sort before the arrays land above the cookie
  (`sub_E8910`'s camera at -4, cookie at -8). Names alone order them, but the declaration order
  counts too: with the declarations written highest slot first the depth-first name search
  finds `sub_E9CA0`'s layout, which no name set gives with them written in source order.
- **An unused `RwRGBA` cleared by one chained assignment** (`c.alpha = c.red = c.green =
  c.blue = 0`) gives the byte stores in the order blue, green, red, alpha, each copied from the
  last (`sub_E8AC0`).
- **`new (4) T`** is the game's `operator new(size_t, RwUInt32)` (0x12F0E0, in the image's
  symbols as `??2@YAPAXII@Z`); `delete p` with a non-virtual destructor expands the scalar
  deleting destructor inline (`mov eax, 1; and eax, 1`), with `this` and result temporaries
  (`sub_E99E0`).
- **A float kept by `?:` through `fld; fstp`** into the conditional's temporary (not `mov eax;
  mov`) is a converted value: `x < 1.0f ? (RwReal)(RwDouble)x : 1.0f` (sub_19B270's clamps). A cast
  to its own type, a unary plus or a named local all copy it as an integer.
- **One vtable store in a constructor** of a class whose base is an interface = the base is
  `__declspec(novtable)` (as the XDK's `DECLARE_INTERFACE` interfaces are); a plain abstract base
  stores its own vtable first (the Live manager's type_3E0418, sub_19C850).
- **A destructor that destroys members without storing the class's vtable again** is implicitly
  defined: a declared one, even empty, stores it first. It is emitted where the global is defined
  (the Live manager's `??1`, sub_19CAE0, with `dword_4F3130` defined in its unit).

## Matching workflow tools

Moved in from the working scratchpad (2026-09-30). Work files (build logs, probe
objects, variant sources, the `inc` include overlay) go to `build/tooltmp/`.

- `cmf.py` / `cm.py`: commit matched functions of a unit (`CMUNIT=<path under src/, no
  extension> python tools/cmf.py [-m "header message"] ADDR...`). cmf builds incrementally
  with `ibuild.py`, checks `== PASS`, then commits one function per commit and pushes.
  `replayf.py` replays the per-function commits.
- `fdiff.py FILE AS_SRC SYM:ADDR... [-v SYM]`: compile a file with another source's flags and
  count each symbol's differing lines; `ncmp.py OBJ SYM ADDR [-v]` (normalised compare) and
  `rawcmp.py OBJ SYM ADDR` (byte-level; misses register-only differences) verify.
- `vtry.py VARS.py SYM ADDR SRC`: try source variants (`VS = {name: [(old, new), ...]}`).
- `xdis.py START END` / `xfn.py ADDR...`: image disassembly with symbol names;
  `objdis.py`, `odis.py`, `ourdis.py`, `adiff.py`: our side and side-by-side.
- `annot.py SRC NAME:SYM:ADDR...`: add `// match:` lines.
- `xdkalias.py DECORATED... | --scan OBJ`: alias XDK library functions.
- `gf.py`, `gfpy.py`, `gfd.py`: read-only queries of the Godfather IDA instances
  (13339 release, 13340 debug); `gfpy.py` refuses writing snippets.
- `bsolve.py`, `bprobe2-4.py`, `applyn.py`, `applyb.py`, `slotmap.py`, `diffall.py`,
  `structdiff.py`, `trial.py`: stack-slot and local-name solving.
- `emap.py`, `inits.py`, `initunit.py`: `$E` dynamic initializer placement.
- `rwd.py`, `ctry.py`, `rwbybytes.py`, `rwrank.py`, `rwmissed.py`: RenderWare compile-and-compare
  and ranking of unmatched RW functions.
- `sdiff.py`, `vva.py`, `pdiff.py`, `adiffb.py`, `lens.py`, `shapes.py`: aligned diffs and
  variant runs for big near misses; `asmtest.py`: test an expression's shape.
- `srep.py FILE EDITS` (old/-----/new/===== blocks, CRLF-safe), `fnedit.py`, `insfn.py`:
  source edits; `cvtry.py`, `macvar.py`: parallel C variant trials.
- `bsolve2.py`, `bsolve_decl.py`, `pnames.py`, `ranks.py`, `slim.py`, `scopenames.py`:
  more stack-slot solving; `inits2.py`: initializer owners; `rwall.py`, `rwannot.py`:
  RenderWare source probes and match lines.

## SplinePath asynchronous exception handling (2026-10-02)

`SplinePath::~SplinePath` (`sub_BA030`) has an empty body but registers
base cleanup and writes EH states 0 then -1. VC7.1 `/EHsc` removes that
cleanup; `/EHa` reproduces all 73 bytes and six relocations, including
the vtable store. The 8-byte unwind at 0x300430 and 10-byte handler at
0x300438 also match. All 15 previously annotated pieces in unit_0B9EA0
remain identical with `/EHa`; no source-body or header changes are needed.

`config/flags.txt` therefore has a specific `/EHa` rule for that unit.
Keep `/EHsc` as the game default. An empty destructor with otherwise
unexplained cleanup can be evidence of a different exception model.
Earlier source-only SplinePath trials are historical and do not explain
the image's empty EH region.

## Inclusive-range integer remainder (2026-10-02)

VC7.1 `/Od` compiles `RpRandom() % count` as a divide by the local's
memory slot. `RpRandom() % (count - 1 + 1)` retains a divisor register
load after the constant operations disappear. This matches sub_8AFF0's
`mov ecx,[ebp-4]; xor edx,edx; div ecx`, including the register rotation
afterward (392 bytes, one relocation). `(count - 1) - 0 + 1` gives the
same match. Simple `+ 0`, `* 1` and `/ 1` forms do not retain the load.
The local-name order restores the 0x1AC frame with a 100-entry array;
the unused word above the array does not require enlarging it.

## Header static guards affect generated local names (2026-10-02)

The implicit packet copy constructor at 0x1D4290 needs count at ebp-8,
destination at ebp-4 and source at ebp-C. Including only game/netqueue.h
produces $S1/$S2/$S3 and the exact 144-byte function. Including the broad
type_DC400.h instead produces $S2/$S3/$S4 and exchanges count/destination.

The consumed $S1 is CLinearMemoryManager::Instance's local-static guard.
A scratch overlay changing only its inline body to a declaration fixes
the full packet unit and preserves every existing annotation. Adding an
early explicit instantiation before the broad include does not fix it:
the guard is still parsed before the implicit copy is emitted.

Production places the copy from a packet-only instantiation unit. An
explicit instantiation of the existing type_1FA230_list<type_3E4E58>
append emits it without a new runtime helper. The append itself matches
133 bytes / six relocations in either context. Array dimensions [1][16]
and [16][1] do not affect the isolated copy; a containing wrapper changes
its frame and is unnecessary. The original class layout and flags remain.


## Named locals before a struct return and inline locals (2026-10-02)

sub_9B0B0 (type_3D51C0::vf_234) matches with a mixture of explicit locals
and inline calls. Its six ordinary locals occupy -0x04 through -0x18;
two named setter values occupy -0x1C/-0x20. The parser-created handle
return temporary follows at -0x24, before the expansion locals from
zero_v3d and the two get_unk_18 calls at -0x28/-0x2C/-0x30.
Making all four latter values explicit is unnecessary: a named handle
copies destination-first, while the getter return copies source-first.
When a return temporary appears between groups in the original frame,
test whether the preceding group consists of named locals and the
following group comes from inline expansion. This recovers the exact
520-byte body and 0x34-byte frame without another compiler build.


## Grouped getter results as named locals (2026-10-02)

The Distance Scheduler confirms the sub_9B0B0 result in three more
functions. sub_35AA0 groups three handle values before three serial
values, although calls appear interleaved. Keep handle values as named
locals and serial values as inline getter results. A comma expression
such as `(slot = object->unk_04, slot == registration->unk_10)` inside
a short-circuit condition keeps the original read, store and comparison.
sub_35FD0 and sub_362F0 match with all payloads, values and receiver
pointers declared explicitly, ordered by their name buckets. Grouped
slots alone do not establish a different inline-expansion algorithm.


## A handle-return temporary before later getters (2026-10-02)

sub_39AA0 uses get_unk_574_h().unk_00, whose four-byte union return is
allocated during parsing at -0xE0. The scalar getter is not equivalent
for layout: the context getter and later scalar getters expand into
slots -0xEC through -0xFC. Existing headers already provide both forms.
The while loop with one compound eligibility condition then matches
all 1,039 code bytes; for/continue changes the jump placement and loads.
Its companion sub_3A450 needs explicit named handle and receiver copies
to reproduce its interleaved slots. Both use the existing VC7.1 settings.


## Explicit command value plus a compiled-out check (2026-10-02)

CDebugScript::HandleAttributes (sub_43200), command 11, stores its
command value at -0xC before loading this. GetCommandData into a named
local gives that slot; ordinary assignment then uses EAX/ECX instead
of the image's EDX/EAX. A compiled-out member-bit check contributes
the two missing register steps without emitted instructions. The unit
uses the same documented idiom as PLAYERS_CHECK: the condition is chosen
for its loads; original assertion text is not known. Whole function:
586 bytes with its 56-byte jump table, all 48 relocations identical.


## Deferring a union return into inline expansion (2026-10-02)

The AIManeuverManager factory sub_3CE20 needs its pool-size getter
local at -0x4C and registration union return at -0x50. Calling
sub_3D2E0 directly creates the union temporary during parsing, before
the getter expands, and swaps those slots. A void inline containing
the call and handle assignment creates no outer return temporary;
its inner union return is allocated during expansion after the getter.
Plain static inline and by-value pointer/integer arguments match all
643 bytes and the cleanup pieces. Its updater sub_3D150 instead needs
named handle copies before its final union return. These are distinct
source-layout solutions to the same apparent temporary-order mismatch.
