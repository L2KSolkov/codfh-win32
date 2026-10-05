# Matching Decompilation Plan — byte-identical rebuild of `Game_XboxMultiplayer.xbe`

## Context

The existing CODFH work is a Win32 port. Its source is shaped for a different target (namespaces,
shims, a D3D9 renderer, invented seams) and **cannot be used here**. This plan is a separate,
clean-room effort with a single objective: source that, compiled with the original toolchain and
linked with the original Xbox libraries, reproduces `orig/Game_XboxMultiplayer.xbe` **byte for
byte**.

The arbiter of every function is the compiled bytes. A function is matched when the object code the
original compiler produces from our source is identical to the original bytes at that address,
relocations aside; nothing else counts as done.

The method is the established matching-decompilation one: delink the original binary into
relocatable objects so the whole XBE rebuilds byte-identically on day one, then replace those
binary objects with compiled source one function at a time until none remain.

### Rules

1. **Xbox libraries are linked, never decompiled.** Every library Microsoft ships in the XDK —
   CRT, STL, XAPI, D3D8, D3DX8, DSOUND (with its WMA and Dolby code), XONLINE, XNET, XGRAPHICS,
   XPP, UIX, voice, the kernel import library — is linked as a library.
   - Installed `C:\XDK` libraries are linked wherever their members are byte-identical to the image.
   - **D3D8, DSOUND and XONLINES** are installed at later QFEs than the image used, so they link
     from stand-in libraries **repacked permanently from the image's own library code** — extracted
     byte-for-byte, never decompiled. Any other member that fails the byte check gets the same
     treatment.
2. **Everything else is decompiled to match, byte for byte**: the game, the RenderWare Studio
   runtime, the RenderWare sources compiled in-project, and the prebuilt third-party libraries
   **RenderWare Audio and Bink** (its C and its hand-written assembly). The **RenderWare 3.6 core**
   library may instead be linked, under Rule 6. Binary objects are only the scaffold for code not
   yet matched; they are never a final state outside the XDK stand-ins and verified RenderWare
   library code.
3. **Names need evidence.** By default a function keeps exactly the name it has in the original
   IDA database (`sub_XXXXXX` stays `sub_XXXXXX`, and a function the database already names keeps
   that name), and data keeps its database name (`dword_`, `byte_`, `flt_`, `off_`, `unk_`, or its
   existing name). A function, struct or member **may be given a real name when proper evidence for
   it is found**, and every renamed item keeps a comment recording its original database name,
   address or offset, and type (see Source conventions). A name is never invented to describe what
   code appears to do.
4. **A new repository, `C:\codfh-match`.** The port's `src/` is not used. The IDA database, the IDA
   client and disassembly scripts (`tools/ida_client.py`, `tools/asm.py`) and the port's derived
   facts (`docs/class-registry.md`, `docs/sdk-boundary.md`, `docs/callgraph.json`) may be consulted
   as analysis inputs — evidence to check, not source to copy.
   - **RenderWare Studio** is in `C:\rwstudio`.
   - **RenderWare source** is in `D:\RW_372_src`. It is **RenderWare 3.7.2, a newer version** than
     the 3.6 core linked into the image, so its code, headers and struct layouts are evidence to
     check against the bytes, never assumed to match them.
   - Unlike the port, these two trees **may be copied from**: code and headers are copied into this
     repository as needed to reproduce the original's functionality, then edited until they match
     the bytes. They are used for reference and as source to copy only. **Nothing is linked from
     them except RenderWare libraries under Rule 6**; the build never includes or compiles a file
     in place from `C:\rwstudio` or `D:\RW_372_src`, and only the copies inside this repository are
     built.
5. **A placement linker is the working gate**; reproducing the image with the real `link.exe` and
   `imagebld.exe` is the final milestone.
6. **RenderWare libraries may be linked from the RenderWare sources**: a prebuilt RenderWare
   library from `C:\rwstudio` or `D:\RW_372_src`, or one built from that source. The condition:
   **every RenderWare function the game calls is verified to be the same code as the image's
   function** at the address the game calls, byte for byte with relocations aside. Those functions
   and their status are tracked in `config/rw_calls.txt` (address, database name, the library and
   member that supplies it, and verified or differs). A function that differs is not taken from
   that library; it is matched from copied and edited source (M6) instead.

### Scope

| Code | Functions | Bytes | Already named in the IDB | Treatment |
|---|---:|---:|---:|---|
| Game, RWS runtime, in-project RenderWare | 8,695 | 2,105,125 | 348 | decompile |
| RenderWare 3.6 core library | 1,507 | 333,826 | 1,444 | link where verified (Rule 6), else decompile |
| RenderWare Audio library | 656 | 88,042 | 53 | decompile |
| Bink library (`.text` + `BINK*` sections) | 289 | 101,317 | 136 | decompile (C + assembly) |
| XDK libraries in `.text` | 2,073 | 354,989 | 1,423 | link |
| XDK named sections (D3D, DSOUND, XONLINE, XNET, XGRPH, WMADEC, XPP, …) | 2,815 | 506,604 | 2,340 | link |

**~11,150 functions to decompile, ~4,900 to link.**

## Build fingerprint (measured from the XBE)

| Fact | Value | Source |
|---|---|---|
| XDK | **5849** for all 12 libraries, non-debug | XBE library version table |
| Library QFE levels | XAPILIB, D3D8, D3DX8, DSOUND, XBOXKRNL, LIBCMT, LIBCPMT QFE 1; XONLINES, UIX, XGRAPHC QFE 9; XVOICE QFE 4; VOICMAIL flags `0x4804` | flag words |
| Original PE | `s:\COD\Game\GameCode\bin\xbox_releasemp\Game_XboxRelease_MP.exe` | XBE debug path |
| Build date | 2004-10-29 (`0x4181A886`) | XBE timestamp |
| Game optimization | **`/Od`** — 95.8% of 8,721 functions below `0x230000` open `push ebp; mov ebp,esp`; `this` spilled to the frame; `xor ecx,ecx; jz` for constant conditions | prologue scan |
| Library optimization | optimized — only 20.9% of 4,246 library-region functions keep a frame | prologue scan |
| Function placement | `/Gy`, 16-byte aligned, gaps filled with `0xCC` (11,460 aligned starts) | gap scan |
| Folding | `/OPT:ICF` — one body serving many vtable slots (`sub_2015D0` ×123) | xrefs |
| C++ EH | on — 924 `FuncInfo` records (`0x19930520`) | byte scan |
| RTTI | **off** for game code — the only 4 type descriptors are CRT/STL exceptions | byte scan |
| `/GS` | on — 282 game functions load `__security_cookie`, stored un-XORed (VC7.1 behavior) | xrefs |
| Surviving source paths | 12 game TUs via assert `__FILE__`, one RW `$Id:` (`plugin/uvanim/dict.c`) | string scan |
| Dynamic initializers | 404, grouped at `0x3096E0–0x30DBBE` in object order (2 descents), each constructing a TU global and `atexit`-registering its destructor | `_cinit` table `0x426D50–0x4273B4` |

## Layout of the image

```
.text 0x012000 - ~0x22B000   game objects (/Od); RWS runtime TUs at 0x129D60-0x132F80
      ~0x22B000 - 0x22F437   RenderWare sources compiled in-project
      0x22F4B6 - 0x30EFF0    prebuilt optimized libraries in link-pull order:
                             XDK (174) -> RW Audio (630) -> RW core (109) -> Bink (36)
                             -> XDK (1,223) -> RW core (575) -> CRT/STL (339) -> RW core (772)
      0x3096E0 - 0x30DBBE    dynamic initializers, object order; destructor thunks after
named sections               D3D, D3DX, DSOUND, BINK* (Bink), XONLINE, XNET, XGRPH, WMADEC, XPP
data                         .rdata, .data (0x11F4C raw of 0xFD960 virtual), DOLBY, BINKDATA,
                             XON_RD, .data1, $$XTIMAGE, $$XSIMAGE, .XTLID
```

## Toolchain (`C:\XDK`, build 5849, QFEs up to .17, Japanese release)

| Tool | Path | Version |
|---|---|---|
| Compiler | `C:\XDK\xbox\bin\vc71\CL.Exe` (+ `C1.Dll`, `C1xx.Dll`, `C2.Dll`) | **13.10.3077** — VS.NET 2003 RTM |
| Linker / librarian | `C:\XDK\xbox\bin\vc71\Link.Exe`, `Lib.Exe` | 7.10.3077 |
| PDB/object support | `MSPdb71.Dll`, `MSObj71.Dll` | 7.10.3077 |
| XBE builder | `C:\XDK\xbox\bin\imagebld.exe` | 1.00.5849.4 |
| Headers | `C:\XDK\xbox\include` — `XTL.h` (`_XTL_VER 5849`), D3D8, DSound, xonline, XGraphics, full CRT, Dinkumware STL (`_CPPLIB_VER 313`) | 5849 |
| Libraries | `C:\XDK\xbox\lib` | 1.0.5849.x |
| Assembler | not in the XDK; `ml.exe` 14.51 ships with the installed Visual Studio 18 | modern |

**13.10.3077 is the game's compiler.** VS.NET 2003 SP1 (13.10.6030) did not ship until 2006, so a
build dated 2004-10-29 used RTM — the same build that compiled the installed XDK libraries. Visual
Studio .NET 2003 itself is not installed; builds run from the command line, which is all a matching
build needs. The prebuilt third-party libraries are a separate question — Criterion and RAD may
have used VC7.0 (13.00.9466), which is not installed — settled by M6's probes.

**XDK library disposition:**

| Library | Image QFE | Installed | Linked from |
|---|---|---|---|
| LIBCMT, LIBCPMT, XAPILIB | 1 | .1 | installed library, after per-member byte check |
| XGRAPHC | 9 | .9 | installed library, after per-member byte check |
| XVOICE | 4 | .4 | installed library, after per-member byte check |
| D3DX8, UIX, XBOXKRNL, VOICMAIL, XNET | 1 / 9 / 1 / `0x4804` / — | stamp to confirm | installed if identical, else repacked |
| **D3D8** | 1 | **.15** | **stand-in repacked from the image**, permanently |
| **DSOUND** (incl. WMADEC, DOLBY) | 1 | **.11** | **stand-in repacked from the image**, permanently |
| **XONLINES** (incl. XON_RD) | 9 | **.17** | **stand-in repacked from the image**, permanently |

The image links **LIBCMT/LIBCPMT** (`/MT`), not the `/ML` LIBC the XDK samples use. The samples'
Release settings are the starting hypothesis — `/G6 /arch:SSE /GF /Gy`, link
`/OPT:REF /OPT:ICF /FIXED:NO`, imagebld `/STACK:0x10000` (the image's stack size is `0x10000`) —
with optimization overridden to `/Od` as the prologue scan shows. The image's init flags are `1`
(utility drive mounted), so the game did not pass `/DONTMOUNTUD`.

## Architecture

```
C:\codfh-match\
  orig\            Game_XboxMultiplayer.xbe (gitignored; its SHA-1 is committed)
  config\          splits.txt  symbols.txt  flags.txt (per-unit compiler and flags)
  src\Source\GameCore\...    game units, by original path where known
  src\COD\SHARED\...         shared UI / fileIO / network units
  src\rws\...                RenderWare Studio runtime units
  src\rwsdk\...              RenderWare units: in-project sources and the 3.6 core library
  src\rwa\...                RenderWare Audio library units
  src\bink\...               Bink library units (C and .asm)
  include\                   game headers; RenderWare 3.6-compatible headers
  xdklib\                    stand-in d3d8 / dsound / xonlines libraries repacked from the image
  probes\                    toolchain probe units, rebuilt on every build
  tools\                     delink, repack, placement link, retail, match, progress, build driver
  build\                     objects and the rebuilt image (gitignored)
```

The original build root was `s:\COD\Game\GameCode`; source paths follow the 12 assert paths
(`Source/GameCore/ai/astarscheduler.cpp`, `COD/SHARED/UI/cCaret.cpp`, …), the RWS framework's and
RenderWare's own file names, and recovered units otherwise. The build driver invokes the unit's
compiler directly with `INCLUDE` pointed at `C:\XDK\xbox\include`, with that unit's flags from
`config/flags.txt`.

| Component | Job |
|---|---|
| `config/splits.txt` | Every original unit (translation unit or library member): its address ranges in each section, in link order |
| `config/symbols.txt` | Every address: its IDA database name, kind, size, section — names are copied from the database, never invented |
| delinker | Emits one relocatable COFF object per unit from the XBE bytes plus recovered relocations and symbols |
| repacker | Builds the permanent stand-in XDK libraries from the image's own library objects, with the original member granularity |
| placement linker | Places every section of every unit at its original address, resolves relocations, writes the PE image and XBE — layout fixed by `splits.txt` |
| retail post-processor | Re-encodes entry-point and kernel-thunk XOR keys to retail values and restores the certificate and RSA signature, which are Microsoft's, not compiler output |
| comparator | `tools/match.py`: compares each compiled function with the original bytes at its address, masking only relocation fields, and reports the first differing instruction; `objdiff` (x86 COFF) optional for side-by-side views |
| progress | Bytes and functions matched per unit, per library, whole image |

The placement linker is what makes per-function progress possible: the game was built `/Gy`, so
every function is its own COMDAT section, and a unit can mix compiled and binary functions.

## Milestones

### M0 — Toolchain identity (game)

1. Build probe units with `CL.Exe` 13.10.3077 and match each against a chosen original — an empty
   thiscall (`sub_73D80`, `retn 0Ch`), a `/GS` function with a stack buffer (`sub_32F70`), an EH
   function with a local destructor, a `switch` with a jump table, float math, and a float-to-int
   conversion.
2. Pin each flag by the probe that decides it: `/Od` (frame and spills), `/Gy`, `/GS` (un-XORed
   cookie), `/EHsc` vs `/GX` (EH state machine), `/GR-`, `/arch:SSE` and `/G6` (`__ftol` call versus
   `cvttss2si`), `/Ob` (header inlines called or expanded), `/GF`, `/MT`, `/Zp`, and the
   `_XBOX`/`NDEBUG` defines.
3. Produce a trivial XBE through `link.exe` + `imagebld.exe` to learn exactly which header fields,
   section flags, TLS and library-version records the toolchain writes.

*Exit:* every probe matches; each flag is recorded with the probe that proved it.

### M1 — Units and link order

Recover `splits.txt` from evidence the binary carries:

- the 404 grouped **dynamic initializers**: object order, and each names its TU's globals and
  constructors;
- **function adjacency**, 16-byte alignment and `0xCC` fill: unit boundaries fall between functions;
- **per-unit data runs**: vtables beside their methods, string literals and `__real@` constants in
  first-object order, EH `FuncInfo`/unwind tables per function;
- the **12 assert paths** and their `__LINE__` immediates;
- **RenderWare**: the 149 `$Id:` strings (one per RW object), RW 3.7.2 source file structure at
  `D:\RW_372_src`, and the Godfather oracle's RW symbols; **RWS**: `C:\rwstudio` file layout;
- **XDK members**: exact boundaries by matching each installed library object's bytes against the
  image;
- **Bink**: its named sections (`BINK`, `BINK32`, `BINK16`, `BINKYUY2`, …) and its `.text` run.

*Exit:* every byte of every section belongs to exactly one unit.

### M2 — Delink and rebuild byte-identically from binary objects

XBEs carry no relocation table, so relocations are recovered from analysis: every operand IDA
resolves to an image address (direct `call`/`jmp` targets as REL32, absolute references as DIR32),
jump tables, vtables, function-pointer tables and pointer-typed data. The delinker consumes an
export of that analysis pulled through `tools/ida_client.py`, regenerated whenever the IDB changes,
and emits one COFF object per unit with its real section names, symbols and relocations.

*Exit:* the placement linker rebuilds the whole image from binary objects alone, and after retail
post-processing it is **byte-identical** to the original. From here on the image never stops being
byte-identical — every later change is a like-for-like swap.

### M3 — Link the Xbox libraries

Compare each XDK member identified in M1 with the corresponding member of the installed library.
Identical members link from `C:\XDK\xbox\lib`. D3D8, DSOUND and XONLINES — and any other member that
differs — link from stand-in libraries the repacker builds in `xdklib\`, preserving the original
member granularity so the link pulls them in the same order.

*Exit:* every XDK byte comes from a linked library — installed or repacked — and none is a
decompilation target.

### M4 — Match the game, RWS and in-project RenderWare (`/Od`)

Per function, in address order within a unit:

1. Read the original disassembly.
2. Write source in the unit's file in original definition order — `/Gy` places functions in
   definition order, so source order *is* address order.
3. Compile with the M0 flags; `tools/match.py` against the original bytes.
4. Iterate until identical. For `/Od` code the levers are mostly declaration order, types and
   expression shape; for asserts, `#line` pins `__LINE__`.
5. Swap the function from binary to compiled by listing it in `config/compiled.txt` (see the M2
   amendment); rebuild; the image must still be byte-identical.
6. Commit.

STL template instantiations inside game objects come from the XDK's Dinkumware headers, so they
match by instantiating the same templates, not by writing them out.

### M5 — Data

`.rdata`, `.data` and `.bss` matched per unit: pooled string literals, float constants, vtables,
jump tables, EH tables, initialized globals and their order, the grouped initializers and `atexit`
thunks. Data is matched when the compiled unit emits it in place of the binary object's data.

### M6 — Match the third-party libraries (optimized)

A separate track that can run beside M4 once M2 is done. Each library first gets its own toolchain
identity, because Criterion and RAD built them, not Spark:

1. **Compiler and flags per library** by probes against its own functions — VC7.1 3077 is
   available; if the codegen proves VC7.0 (13.00.9466), that compiler has to be obtained, since
   only its PDB/object DLLs are in the XDK. Optimization level, inlining, frame-pointer omission,
   `/G6`/`/arch:SSE`, calling conventions.
2. **RenderWare 3.6 core** (1,507 functions): link a RenderWare library under Rule 6 wherever
   `config/rw_calls.txt` verifies the called functions; for any that differ, start from the RW
   3.7.2 source and edit the function until it compiles to 3.6's bytes. The Godfather oracle's
   3.6-era types and symbols locate the drift.
3. **RenderWare Audio** (656 functions): no source exists; decompiled from the disassembly alone.
   **Complete 2026-10-02:** all 762 subsequently identified main/tail split ranges
   are placed, zero remaining. Final cmf.py gate is byte-identical (18,167 pieces /
   3,499,204 bytes, original SHA-1). The owner requested stopping when RWA finished;
   no subsequent milestone was started.
4. **Bink** (289 functions): C compiled with RAD's flags, and hand-written assembly reproduced as
   MASM source whose assembled bytes match. `ml.exe` 14.51 is available; if its encoding choices
   differ from the original assembler's, a period MASM (6.1x/7.10) has to be obtained.

*Exit:* no binary object remains outside the XDK stand-ins.

### M7 — Authentic link

Rebuild with the real `link.exe` 7.10.3077 and `imagebld.exe` 5849.4: recovered object order,
original library order (installed and repacked), `/OPT:REF` (without `/OPT:ICF`; see Amendments), and whatever section
directives the evidence requires. After retail post-processing the output must be byte-identical.

*Status (2026-10-04):* `tools/session/m7probe.py`, `m7xbe.py` and `m7retail.py` rebuild the XBE
end to end, and after retail post-processing its SHA-1 equals the original's
(d3ec0b089647081fd733b1bf53c63136f1a95387). The post-processing takes from the original: the
retail header, the build-environment values (timestamps, PDB GUID, age and path; `--no-env`
leaves them), and, as an unexplained difference the owner chose to restore (`--no-import-pad`
leaves it), seven zero dwords after the kernel thunk table at 0x3CD564, which the M7 link holds
with seven unused kernel imports. Name imports (IM1013), unknown ordinals, a second kernel
module spelling, xbdm imports, empty import descriptors, imports of discarded code,
/DEBUGTYPE:CV,FIXUP or CV,COFF and plain .rdata fills do not produce the original's zeros
(docs/questions.md).

## Source conventions

- **Names come from the IDA database unless evidence names them.** `sub_1C5220` is written
  `sub_1C5220`; a function the database names keeps that name verbatim, and a database name
  qualified with a class (`RWS::CAttributePacket::GetCommand`) defines that class and member. Data
  keeps its database name.
- **Evidence-based names.** A function, struct or member may be renamed only when the name is
  *recorded* somewhere the original build left it, not inferred from behaviour. Proper evidence is:
  a string in the image that names it (an assert or debug message such as
  `"cXboxLiveNetGame::stateServerTakeUp ..."`, a `__FILE__` path, a registration or type-name
  string); a matching symbol or declaration in the RenderWare or RenderWare Studio sources
  (`D:\RW_372_src`, `C:\rwstudio`) whose code agrees with the bytes; or an XDK header or library
  symbol. The evidence is cited in the comment. Every renamed item carries a comment giving its
  original database name, its address (functions, data) or offset (members), and its type:

  ```
  // sub_1D52E0 @ 0x1D52E0 - "cXboxLiveNetGame::stateServerTakeUp" (string 0x3E5068)
  int cXboxLiveNetGame::stateServerTakeUp()

  struct cXboxLiveNetGame {   // type_XXXXXX: vtable off_XXXXXX; name from string 0x3E5068
      RwInt32 mState;         // unk_XX (+0xXX, RwInt32): "mState = eStateNone" (0x3E5050)
  };
  ```

  (The struct lines are illustrative: its anchor and the member's offset are placeholders until the
  bytes establish them.)
- **Types still need spellings.** A thiscall function can only be written as a member function in
  VC7.1, so each object type gets a placeholder named after its anchoring address — its vtable or
  constructor (`struct type_3E66D4`) — unless the database already names it. An object with neither
  a vtable nor a constructor is anchored at its lowest-address member function (the bitstream
  whose methods start at `sub_1F8520` is `struct type_1F8520`). A data-only type with no vtable,
  constructor or methods is anchored at its first instance in the image (the 12-byte records of the
  table at `0x427408` are `struct type_427408`). A type whose only constructor was folded by
  `/OPT:ICF` into one body shared with other types (`pCtor` at `0x22C60` serves 16) is named after
  its first container and offset: the 32-byte records at `type_154C0 + 0x80` are
  `struct type_154C0_80`. Plain data created at run time with no constructor, vtable, methods or
  image instance is named after the function that creates its instances: the path nodes
  `sub_F8350` reads from a RenderWare stream are `struct type_F8350`. Members are
  `unk_XX` by offset. These are placeholders; any of them may take a real name under the
  evidence rule above.
- **No hand-transcribed `__asm`.** Matched code is C or C++ that the compiler turns into the
  original bytes. `__declspec(naked)` functions and inline `__asm` blocks that copy the disassembly
  are not decompilation and never count as matched. There are exactly two exceptions:
  - **Bink's own hand-written assembly** (M6), reproduced as MASM in its own `.asm` unit.
  - **The disabled debug print's guard.** The game's debug prints were switched off by a badly
    coded debug `#ifdef` that still compiles a constant-false test: `xor reg, reg` then `jz` over
    the print. VC7.1 picks that register differently from the original, whatever the spelling (see
    `docs/toolchain.md`). This guard, and nothing else, may be written as exactly those two inline
    instructions, jumping to a C label:

    ```
    __asm xor ecx, ecx
    __asm jz dead_476
    off_42CD14("sNetGameEP:: broken packet %s:%d\n", __FILE__, __LINE__);
    dead_476:
    ```

    The print call, its arguments and every other statement stay C or C++. No other inline
    `__asm` is allowed anywhere, for any reason.

  A function that will not come out as C or C++ within these exceptions stays binary.
- **No duplicated structs.** Each object type has exactly one placeholder, defined once and shared
  by every method of that object and every file that uses it. Never create one struct per function,
  and never create a second struct for an object that already has one: a method found on an
  existing object is added to that object's placeholder. A struct is declared in one header and
  included wherever it is needed, never redeclared per file.
- **RenderWare types.** Fields, locals, parameters and return values use RenderWare's own typedefs
  (`RwInt8`, `RwUInt8`, `RwInt16`, `RwUInt16`, `RwInt32`, `RwUInt32`, `RwReal`, `RwBool`, `RwChar`)
  from the RenderWare headers, not bare `int`, `unsigned`, `short`, `char` or `float`. The typedef
  must match the width and signedness in the bytes (`movsx` against `movzx`, `jl` against `jb`,
  `fld` against `mov`).
- **No raw offsets.** Every access to an object's contents goes through a declared member at its
  real offset. Never reach into memory by number: no `*(int *)((char *)this + 0xB0)`, no
  `((char *)p)[0x1C]` and no pointer arithmetic that stands in for a field. Unknown space before a
  known field is spelled as an `unk_XX` member, not left to a cast.
- **Locals are named for their frame slot.** VC7.1 at `/Od` walks its symbol table's 16 hash
  buckets to lay out a function's locals, and locals sharing a bucket come out in reverse
  declaration order, so a local's name (and, within a bucket, its declaration order) decides its
  stack slot. A local is `var_N`, IDA's name for the slot N bytes below `ebp`. When those names
  put locals in the wrong slots, each local instead takes one of the slot-stating forms `var_N`,
  `local_N`, `vN`, `lN`, `varN`, `lv_N`, `locN`, `ebp_N`, `stk_N`, `slot_N`, `bp_N`, `fp_N`,
  `lcl_N` or `frm_N`, in a combination
  (and declaration order) that reproduces the layout; `tools/local_names.py` finds one. Every
  form states the slot the local really occupies. Names already matched stay as they are.
- The dialect is whatever VC7.1 accepts: C++98 with its quirks. No `static_assert`, `nullptr`,
  `<cstdint>`, `noexcept`, `auto`, lambdas or range-for. Size checks use the negative-array-typedef
  idiom.
- XDK and RenderWare headers are included as the original did; boundary types come from them.
- Dead code is kept — it is in the bytes, so it is in the source.
- One commit per matched function or per matched unit.

## Verification

- **Image:** SHA-1 of the rebuilt, retail-post-processed XBE equals the original's. Run on every
  commit; any difference fails the build and names the first differing section and offset.
- **Unit:** `tools/match.py` reports every function marked compiled as identical, and its data
  sections identical once marked compiled.
- **Libraries:** every installed XDK member linked is byte-identical to its image counterpart; every
  repacked member is extracted byte-for-byte.
- **Source:** `tools/audit_sources.py` runs first on every build and fails it on anything the
  byte comparison cannot see: inline `__asm` outside the debug-guard idiom, `__declspec(naked)`, an
  image address written as a number, a raw offset through a byte-pointer cast, a struct defined
  outside a header or defined twice, a bare C scalar type instead of a RenderWare typedef, and
  `auto`.
- **RenderWare:** every RenderWare function the game calls is listed in `config/rw_calls.txt`, and
  a linked RenderWare library supplies only the ones verified byte-identical to the image.
- **Toolchain:** the probes stay in the tree and re-run on every build, so a changed compiler or
  flag is caught immediately.
- **Progress:** bytes and functions matched by compiled source, per unit, per library and overall.

## Risks

- **Flag identity.** The game's compiler is settled; its flag set is not. The XDK samples compile
  Release at `/O2`, while `xbox_releasemp` is `/Od` with `/GS` and EH — a customized configuration,
  so every flag is proven by probe.
- **Optimized third-party code** is far harder to match than `/Od` code: register allocation,
  scheduling and inlining all depend on source shape, and RenderWare Audio has no source at all.
  M6 is the project's long pole.
- **Missing period tools.** A VC7.0 compiler or period MASM may be required for the third-party
  libraries; neither is installed.
- **RenderWare 3.6 versus 3.7.2.** Both the core library and every game use of RW macros depend on
  3.6-accurate headers and source; the drift is found function by function.
- **`/Od` register and stack-slot choices** — the main iteration cost per game function.
- **Inline COMDAT placement.** Header inlines land in the first object that emits them; each unit's
  function list must reproduce which inlines it instantiates.
- **ICF survivor choice.** When bodies fold, the linker keeps one address; the placement linker must
  mirror that and the authentic link must reproduce it.
- **Relocation recovery.** Under the placement linker a missed relocation is harmless while a unit
  is still binary; under the authentic link every relocation must be right. M7 is where recovery
  errors surface.
- **Retail artifacts.** The certificate, signature and retail XOR keys cannot be regenerated; they
  are restored, and are not compiler output.
- **RenderWare Studio source.** `C:\rwstudio` is a different version from the one compiled
  in; its code may be copied into this repository as a starting point (Rule 4), but the RWS units
  are edited until they match the binary, and nothing from it is linked.

## Amendments

- **M2, binary units are raw bytes.** Under the placement linker every unit sits at its original
  address, so a unit still in binary form is exactly its original bytes and needs no relocations to
  be byte-identical. `tools/xbelink.py` places raw ranges from `config/splits.txt` and compiled
  pieces from `config/compiled.txt`; compiled pieces are relocated against the addresses their
  targets denote. Relocation recovery for binary units is needed only when layout is left to
  `link.exe`, so it moves to M7. The bytes after a compiled piece up to the next range boundary are
  generated alignment fill, never copied, so a compiled piece shorter than the original shows up.
- **Placement ranges are not translation units.** `config/splits.txt` cuts code at every IDA
  function start and tail chunk so any function can be swapped alone; grouping ranges into
  translation units (M1) continues from the evidence in `docs/units.md` and feeds M4/M5 and M7.
- **The reference is the image as signed** (see `docs/image.md`). The first dump's `.text` carried
  one modification (`sub_19A750`, the debug print, redirected to `DbgPrint`); it was replaced by
  the signed image, and every stored section digest now has to verify against the rebuilt bytes.
- **Original inline assembly (owner, 2026-10-01).** "For the remaining items, no __asm unless the
  function originally had it." A function whose original code used inline assembly (the game's FPU
  control-word setters `sub_19D290`/`sub_19D2D0`, the bit stream's byte swaps `sub_1F81E0`/
  `sub_1F8300`) keeps it, between `// begin original __asm` and `// end original __asm` lines that
  `tools/audit_sources.py` accepts; nothing else may be transcribed. (Bink's remaining code was
  transcribed by the owner's earlier "asm the rest of bink".)
- **M7, function order through `/ORDER` (owner's decision, 2026-10-03).** Where the evidence does
  not yet explain why the compiler and linker lay functions out as the image has them (mostly the
  order VC7.1 emits template members in, and library members' pull order), the M7 link passes an
  `/ORDER` file generated from `config/compiled.txt` (every code row in image order, each `/OPT:ICF`
  group's members together, and the few static functions made external in the linked copy of
  their object only). The original build probably did not use `/ORDER`; nothing in the sources
  depends on it, and a port to another platform simply leaves it out. Evidence-based fixes
  (object splits, statics, inline members, emission order) continue where they are clear.
  *To revisit it:* run `tools/session/m7probe.py` without `M7ORDER=1` and `tools/session/m7layout.py`
  with `ORDER=1` to see what the compiler and linker order on their own;
  `tools/session/objorder.py` lists each object's functions out of emission order;
  `tools/session/gpattern.py` + `inlinevfs.py` (inline virtuals before `??_G`),
  `strorder.py`/`litctx.py` (literal order: globals, statics, object boundaries),
  `laterdefs.py` (VC7.0 `/O2` deferral: callers of later-defined functions),
  `pullsim.py` (library pull order) and `icfrename.py`/`literalowner.py` (row names and owners)
  are the tools; the rules they rest on are in the `m7-layout-order` notes. Then drop the
  `/ORDER` option once nothing is left out of order.
- **M7, no explicit `/OPT:ICF` (evidence, 2026-10-03).** link 7.10.3077 with `/OPT:REF` alone (or no
  `/OPT` at all) still folds identical functions, but keeps identical read-only data apart; an
  explicit `/OPT:ICF` also folds identical data COMDATs (vtables, EH tables). The image never
  folds data: identical vtables sit at their own addresses (type_3DFB28/34/40 at 0x3DFB28-0x3DFB4B,
  the all-`_purecall` type_3E83F4/type_3E7D94), and no game function is duplicated. So the
  original link passed `/OPT:REF` without `/OPT:ICF`; the M7 link does the same (probe in
  `tools/session/m7probe.py`; a 3-class test in a scratch directory reproduces both behaviours).
  The "Folding" row under Toolchain evidence means this default function folding.
- **M7, section order (2026-10-04).** link 7.10 creates an output section where it first meets a
  contribution of that name and characteristics, empty ones included. The original met them in its
  objects' order; since the M7 link places code and data with `/ORDER` and an object order of its
  own, `src/xbe/secorder.asm` (no bytes, only an empty section of each name in the image's order)
  is linked first. The sections imagebld inserts from files (`$$XTIMAGE`, `$$XSIMAGE`, `.XTLID`)
  are imagebld's inputs (`/TITLEIMAGE`, `/DEFAULTSAVEIMAGE`), not linked; `tools/session/m7xbe.py`
  builds and compares the XBE.
