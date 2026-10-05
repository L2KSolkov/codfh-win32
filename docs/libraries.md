# XDK libraries against the image (M1/M3)

`python tools/lib_scan.py` locates every member section of the installed XDK libraries in the
original image. Each section's bytes become a pattern with relocation fields wildcarded, anchored on
its longest literal run, matched at the section's alignment. Results go to
`build/libscan/<lib>.json`.

| Library | Members | Members with a located section | Sections located | ambiguous | absent | too short to anchor |
|---|---:|---:|---:|---:|---:|---:|
| libcmt | 622 | 257 | 630 | 170 | 1,091 | 342 |
| libcpmt | 76 | 32 | 113 | 627 | 2,244 | 2,488 |
| xapilib | 106 | 73 | 525 | 34 | 564 | 90 |
| xboxkrnl | 4 | 0 | 0 | 2 | 1 | 2 |
| d3d8 (installed QFE .15, image QFE 1) | 42 | 33 | 349 | 22 | 1,288 | 329 |
| d3dx8 | 118 | 35 | 113 | 74 | 2,992 | 586 |
| dsound (installed .11, image 1) | 42 | 38 | 705 | 172 | 560 | 316 |
| xonlines (installed .17, image 9) | 81 | 61 | 1,248 | 58 | 1,539 | 642 |
| xnets | 19 | 14 | 194 | 18 | 471 | 168 |
| xgraphics | 76 | 47 | 1,450 | 331 | 2,484 | 986 |
| xvoice | 464 | 185 | 1,305 | 146 | 3,703 | 853 |
| uix | 17 | 14 | 432 | 32 | 229 | 267 |

"Absent" mixes members the game never pulled in with members that differ from the image; telling
them apart is the next step of M3.

## Coverage of the image's XDK sections by exact matches

| Section | Bytes covered | of | Share |
|---|---:|---:|---:|
| D3D | 63,517 | 66,480 | 95.5% |
| D3DX | 976 | 976 | 100% |
| DSOUND | 118,974 | 123,044 | 96.7% |
| XONLINE | 125,352 | 134,064 | 93.5% |
| XNET | 75,953 | 77,168 | 98.4% |
| XGRPH | 125,152 | 132,828 | 94.2% |
| WMADEC | 103,241 | 103,724 | 99.5% |
| XPP | 35,783 | 36,480 | 98.1% |
| DOLBY | 29,036 | 29,036 | 100% |
| XON_RD | 5,053 | 5,608 | 90.1% |
| `.text` library region `0x22F4B6–0x30F0F4` | 376,519 | 916,542 | 41.1% (the rest is RenderWare, RenderWare Audio and Bink) |

Even D3D8, DSOUND and XONLINES — installed at later QFEs than the image used — match 93–97% of
their sections exactly. The plan still links those three from stand-ins repacked from the image,
which is exact by construction; these numbers say how little of them the later QFEs changed.

## Placing the installed members (M3)

`python tools/xdkplace.py [LIB ...]` places installed library members' functions in
`config/compiled.txt`, pointing at the member objects `tools/xdk_members.py` extracts into
`build/xdk/` (a build step; `config/xdk_members.txt` lists them, `MEMBER#N` for a repeated member
name). A function is placed where lib_scan finds its section exactly once, or, for sections too
short to anchor or found several times, at the address the image's symbols give its name;
`tools/match.py` must find it identical, relocations included. External names its relocations use
are aliased from the image's encodings (`installed LIB MEMBER references it from FUNCTION (M3)` in
`config/aliases.txt`); the post-check resolves names through the placed pieces as the placement
linker does and drops any function a twin's placement contradicts. `tools/xdksplit.py` then splits a
range where IDA left code after a placed function and grows one a placed function runs past.
An assembler member's function with labels inside it (local `_gu_return`, public `__NLG_Return2`) is
placed as one piece per label-delimited part: each is compared on its own, `match.py` accepts a piece
that ends at such a label short of the database's size, and the placement linker does not count local
labels as duplicate names.

Placed so far: 4,231 functions (xapilib, libcmt, libcpmt, d3d8, d3dx8, dsound, xonlines, xnets,
xgraphics, xvoice, uix).

### The XDK 5849 libraries

The December 2003 XDK 5849 (`XDKSetup5849/XDK/xbox/lib` in the user's SDK download) differs
from the installed XDK in d3d8, dsound, uix, xacteng, xgraphics, xonline* and xvoice. lib_scan
locates a few more of the image's sections with its d3d8.lib (+4) and dsound.lib (+2) and fewer
with its uix, xvoice and xonlines; so those two are copied into the worktree as
`xdklib/d3d8.lib` and `xdklib/dsound.lib` (untracked, like the installed XDK). A library name
with a slash is a worktree path in `tools/lib_scan.py`'s `lib_path` (xdkplace, xdk_members);
`xdkplace.py xdklib/d3d8.lib xdklib/dsound.lib` placed 25 more functions (3 d3d8, 22 dsound),
whose manifest rows name those copies. The other differing 5849 libraries (uix, xvoice,
xonlines, xgraphics, xnets) are copied there too: run over them, xdkplace placed four more
(three of uix's CFriendsScreen/CFriendsList, xonlines' `CXnIp::IpLogoff`). The members the image holds in another version (later QFEs, `differs` and
`absent` in the tool's summary) stay binary; the plan links them from the stand-ins repacked from
the image (M7). Library sections the linker merges are mapped in `XDK_MERGES` (`tools/match.py`);
SECREL relocations (thread-local variables) keep the original's field.

### Stand-ins repacked from the image (`src/xdk/standin_*.asm`)

The XDK code no installed or 5849 library member places (later QFEs, members absent from the
libraries, IDA ranges around placed members) is repacked from the image as PLAN M3 asks:
`tools/img2masm.py --addrnames` writes each contiguous run of it as a MASM unit holding the
image's bytes, with symbols only for address fields (`_sub_/_unk_XXXXXX`, resolved by address),
every piece named `_sub_XXXXXX` after its address and cut where a placed member starts. 184
pieces in six files (the TrueType interpreter, crypto thunks, UIX and XHV, IPP, the CRT, the
EH handlers and UIX initializers). `tools/match.py` accepts such a label piece ending at a
placement boundary (a splits.txt range or a compiled piece). The member granularity the
authentic link needs (M7) is still to be recovered for these.


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
