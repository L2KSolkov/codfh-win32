---
name: bink-library
description: docs/reference/Bink/binkxbox.lib is RAD's Xbox Bink lib, near-identical to the image; VC7.0 9466 C, MASM 6.15 asm; names every function
metadata:
  type: reference
---

The user supplied `docs/reference/Bink/` (2026-10-01): `binkxbox.lib` plus `BINK.H`, `BINK2.H`, `rad3d.h`, `radbase.h`, `radmem.h`.
- The 35 members carry every function name (statics too) and the unit split. Extract them with `Lib.Exe -nologo -extract:<member> -out:<file>`; PowerShell is needed, because Git Bash mangles `/nologo`. The extracted objects are in build/tooltmp/binklib/.
- 75 of 112 functions that match by name are byte-identical to the image (ncmp).
- @comp.id: C = VC7.0 13.00.9466 (`/compiler:vc70`), the C++ units binkds and yuv = VC7.0 C++, rgb*/yuy2*/yuv32 = MASM 6.15.8444 (hand-written asm units, per PLAN M6).
- The image's Bink is NEWER than the lib (1.5s). No version string in the image (only the 1994-2002 banner, which 1.5s has too); its layouts are BINK2.H's (1.6c, 2004-01-20; rad3d.h is a copy of it), so it is 1.6c or a release with the same layouts (user asked how I know; say this, not 'it is 1.6c'): BINKSND.NoThreadService at 0x60, BINK.rtindex, skipcount/toofewskipstomask after doresync. Use BINK2.H for struct layouts and names (user tip). The lib is still the code guide: same source shape, differences are small.
- Image code compiles with the default VC7.1 (`src/bink/*` rule in flags.txt, /O2 /Gy); static functions get register conventions (only if not address-taken). Image is tools/objlist.py-readable side by side with lib members (build/tooltmp/side.sh LIBSYM LO HI).
- Use the lib objects as the compare target and for names when starting Bink (PLAN: Bink is decompiled, not linked). Related: [[rwa-quirks]].
- Bink matching lessons (2026-09-30): a static helper is inlined only when it has ONE caller, so a unit commits whole (parking a caller changes inlining in matched code). A public function inlined in the image = declare it static (BinkSetSoundSystem). VC7.1 /O2 slot/register choices do NOT follow local names (tested). Library objects have no debug info. radcb done; binkread/binkacd/wintimer drafts in the session scratchpad (*_draft.c).
- Shapes that fixed binkfile (2026-09-30): RAD REUSES variables — a dead-param-slot store of a value = it shares a variable with an address-taken one (ReadFile's count `got` also holds the seek skip and the clamp temp); never pass a register variable's address (separate `got` from `amt`). `if (size) {...} else {...}` vs early break decides which block goes last. `x = ...; field = (x < y) ? x : y;` for the one-load clamp of volatile fields. Statement order permutations via ptry find register rotations. Declaration order and names do not matter at /O2.
- binkds done (2026-09-30, 17 fns): C++ — call DirectSound through dsound.h's C++ inline wrappers (in binkint.h; lib has their COMDATs); write `CH(bs)->` everywhere instead of a local `ch` (fixed 6 fns); one-off register swaps fixed by a REDUNDANT assignment (start_streaming: `moved = 0` again in the restart branch) — try adding redundant defs, ptry addl/ins/mv scratchpad generators. dB conversion: `F32 db = (F32)log10(...); v = (S32)(db * 3333.3333f)`, no helper fn.
- User OK'd (2026-09-30) `__declspec(naked)` __asm transcriptions in src/bink for stuck functions ("just __asm it and we will figure it out later"); audit allows it there; list each in docs/questions.md. Asm can't call custom-convention statics by name (breaks their convention) — call through extern "C" alias names (`_binkds_DS_clear`). cmf.py's -m commit does not stage src/bink/*.h or tools/ — commit those yourself.
- MASM units done (2026-10-01): 15 rgb*/yuy2* .asm in src/bink (23 entry points) via tools/asmgen.py LIBOBJ LIBSECTION ADDR (ASMSEG=image section) + masm6.inc ALIGN16; build supports .asm (ml 14.51), match/xbelink handle zero padding. cmf can't commit .asm: commit by hand, one unit per commit with its compiled.txt rows (write rows file-by-file carefully; a Windows write failure skipped two rows once). mmx.c (check_for_MMX, .text 0x25D910) done. Stuck C: expand simpmergesort (flags reg eax vs ebx), binkacd (draft in scratchpad).
- yuv.cpp (2026-10-01): BINK32 edge helpers committed via macros EDGEROW/EDGECOL. LIB ORACLE: compile a lib-shaped variant with /compiler:vc70 in build/tooltmp/libtest (run.py VARIANTS FN) and diff against the lib member — it found the `U32 i = x;` local-copy shape. Col helpers: `S32 col = x;` declared BEFORE `U32 i = n;` (decl order picks the spill slot!). cm/cmf strip needs: all #defines before the first `// match:`, and the LAST block a real function (not a one-line macro instantiation). Edge helpers are non-static (EDGEFN) until YUV_blit's tables are matched.
- VERIFY with `python tools/build_sources.py SRC` (match.py), not just unitcheck: ncmp masks relocation targets, so a wrong S field / table (e.g. S.y0 vs S.a0 load order) shows as 0 in unitcheck.
- binkread done (2026-10-01): 26 committed, 5 naked transcriptions (Open, Wait, SetSoundOnOff, DoFrame, NextFrame). Workflow: tools/img2asm.py START END [SYM=alias] [RAW=addrs] + a fix loop that adds RAW (`_emit`) for instructions inline asm encodes differently (7-byte lea fill, jump sizes). Caveats: a C caller's codegen depends on the CALLEE's C body in the same file (NextFrame vs BinkSetSoundOnOff) — transcribing a callee can break callers; statics whose only callers are transcribed must have their bodies dropped (stay binary); a static that loses its 2nd caller gets inlined → `__declspec(noinline)` stand-in. `#pragma code_seg("BINK")` puts switch tables in BINK (match.py section_kind handles named code sections).
- popmal.c and fft.c done (2026-10-01). fft.obj is Takuya Ooura's fftsg.c (1996-2001 version: cftrec1/2, cftexp1/2) in float; writing it from the algorithm + IDA decompile matched all 30 on the first build — for known public algorithms, reconstruct the original source directly. Bink sources must use RAD types (F32/S32), the audit rejects bare float/int.
- ALL Bink code placed (2026-10-01). User: "asm the rest of bink" -> tools/img2masm.py OUT.asm TITLE LO-HI... writes a MASM unit of exact image bytes (db), symbols only for address fields (`_sub_/_unk_XXXXXX` resolve by address in match.py/xbelink), jpt_ tables as `dd $L_x` ($-prefixed labels, else coff.function_bytes cuts the function at them), one SEGMENT ALIAS('<image section>') per contiguous run. Units: src/bink/{expand,binkread,binkacd,yuv,dct,bitplane}_asm.asm. Rows added with a compiled.txt inserter; one commit per unit by hand. Use it for any library code the owner says to transcribe.

## C/C++ restoration, 2026-10-02

The owner has now requested removal of the temporary assembly transcriptions
for originally C/C++ functions. This supersedes the earlier permission above;
preserve the original MASM units and genuine RAD low-level assembly helpers.
All code commits and pushes, including supporting files, must use cmf.py.
RADTimerRead now matches in C (276 bytes / 28 relocations): compute the two
elapsed differences separately, test their difference, then subtract the
second elapsed value from the existing diff only inside the correction branch.
Fixed VC7.1 /O2 /QIfist /Gy suffices; no compiler or flag change is needed.

DirectSound Open now matches in C++ (642 bytes / 21 relocations, all 17 unit
functions exact). The initial-byte-count fallback must be an explicit else;
an unconditional fallback assignment before the frame-rate condition creates
the old zero-EBP lifetime mismatch. Assign WAVEFORMATEX.wBitsPerSample before
nSamplesPerSec to preserve the original partial EAX load without an extra xor.

DCT restored fully in C: five image functions, no extra sibling wrappers.
Keep helper signature (out,pitch,in,quant), define the input cursor before
workspace initialization, and reuse row tmp2=w[4] in the sum and difference.
Doubled output repeats packed pixels into two rows. Both 4096-byte quantization
tables match the reference library. 34CAD0 is FastIDCT8x8 (ifiquantlevels8 at
3EEF40); 34CB00 is FastIDCT8x8d; 34CB30 is FastmIDCT8x8WithMotion (ifimquantlevels8
at3EFF60). The old IDA snapshot misnamed 34CAD0 FastmIDCT8x8; aliases and the
expander call sites correct the name without editing IDA.


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
