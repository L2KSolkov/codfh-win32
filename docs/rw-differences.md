# RenderWare: the image vs. the 3.7.2 source tree

The image links **RenderWare 3.6.0.3 for Xbox**, with a few additions of the game's
own. The source in `D:\RW_372_src` is **RenderWare 3.7.2 with a third party's edits**
throughout. This file lists every difference found so far, the evidence for each, and
where the in-project copy (`src/rw`, `include/rw/sdk`) now follows the image. The image
is always the arbiter; nothing here was changed without bytes to show for it.

## Build configuration (all fixed in the headers)

| Difference | Image | 3.7.2 tree | Evidence | Fixed in |
|---|---|---|---|---|
| Library version | `0x36003` (3.6.0.3), base `0x34000` | `0x37002`, base `0x35000` | chunk readers compare `0x34000`/`0x36003` (`RwStreamFindChunk`); writers stamp `0x36003` | `rwversion.h` (both copies) |
| Build number | `0xFFFF` | `45` | `RpGeometryStreamWrite` pushes `0xffff` | `rwversion.h` |
| Matrix / frame alignment | 16 (`RWALIGN` = `__declspec(align(x))`) | 4, `RWALIGN` empty (Windows `ostypes.h`) | `_rwMatrixOpen`, `_rwFrameOpen`, `_rpLightOpen` pass `0x10` as free-list alignment; `Rt2dGlobals` matrices sit on 16-byte offsets | `rwplcore.h`, `os/win/ostypes.h` |
| Square root | SSE: `rwSqrt` is an `__m128` `_mm_set_ss`/`_mm_sqrt_ss`/`_mm_store_ss` block (16-aligned frame) | `_rwSqrt` call | `RpAtomicGetWorldBoundingSphere` (`movaps`/`sqrtss`/`movss`) | `rwplcore.h`, `plcore/bavector.h` |
| `RwFastRealToUInt32` | the Xbox ostypes.h helper: `__asm cvttss2si eax, x` (inlined as `movss [mem], xmm; cvttss2si eax, [mem]`) | the Win32 FLD/FISTP `__asm` (os/win/ostypes.h) | Godfather debug PDB `RwFastRealToUInt32Inline` (0xB78AE0); `InstanceWeightsAndIndices` (0x2D3340) | `rwplcore.h` (`_XBOX` branch) |
| Point/vector transforms and matrix multiply | SSE `__asm` overloads of `RwV3dTransformPointMacro`, `RwV3dTransformVectorMacro`, `RwMatrixMultiplyMacro` (the flags ANDed inside) | the generic function-pointer / C macros | Godfather debug PDB (the same blocks unoptimised); `RwMatrixMultiply` 0x2A58B0 | `bavector.c`, `bamatrix.c` (`_XBOX`) |
| Light cone limit | `rpLIGHTMAXCONEANGLE` is pi/2 (the source's Xbox value) | pi under the null driver model we compile with | `RpLightSetConeAngle` compares with 1.5708 (0x3DAEB8) | `rpworld.h`, `world/balight.h` (`|| defined(_XBOX)`) |
| Delta morph platform pipelines | `PLATFORM_PIPELINES` defined (the Xbox build's; `DMorphClose` destroys the pipelines with the last instance) | not defined for the null driver | `DMorphClose` calls `_rpDMorphPipelinesDestroy` | flags rule `src/rw/plugin/dmorph/*` |
| PTank colour packing and constant flags (`plugin/ptank/ptank.c`) | the Xbox branch: `RGBATOCOLOR` packs ARGB (a D3DCOLOR) and `CONSTANTFLAGS` is 0 | the null driver model's branch (colours copied as RGBA, constant flags set) | `rpPTankGENInsColorPP`/`PV`/`PVC`/`PPC` (0x2ECFF0 on) shift alpha to the top byte; `_rpPTankGENInstance` never tests the constant flags | `ptank.c` (`|| defined(_XBOX)` on the Xbox branch) |
| Delta morph platform data (`plugin/dmorph`) | `PLATFORM_DATA` and `PLATFORM_GEOM_DTOR` defined: `rpDMorphGeometryData` carries the Xbox vertex buffer, stride and geometry flags (0x18 bytes) and the geometry destructor calls the platform destructor | neither defined for the null driver | `RpDMorphGeometryCreateDMorphTargets` allocates 0x18 and clears three more fields; `DMorphGeometryDtor` calls `_rpDMorphGeometryDtor` (0x2F2830) | `dmphgeom.h` (under `_XBOX`), `dmorphdata.h` |
| PTank `SinCos` (`plugin/ptank/ptank.c`) | the tree's inline `fsincos` asm (its `WIN32` branch) | the `RwSin`/`RwCos` macro for non-Win32 builds | the rotating position inserters and `rpPTankGENInsSetup` (0x2EBE40 on) spill the angle and run `fsincos`; C gives separate `fsin`/`fcos` | `ptank.c` (`|| defined(_XBOX)`); the one inline asm kept, by the owner's exception |
| Anisotropy offset hook (`plugin/anisot/rpanisot.c`, `anispriv.h`) | `RpAnisotPluginAttach` passes the texture offset to the Xbox driver (`_rwXboxSetTextureAnisotropyOffset`) | the null driver model compiles no hook | the attach (0x2FCA60) calls 0x2AFA90 after the stream registration | `rpanisot.c`, `anispriv.h` (`|| defined(_XBOX)`) |
| Immediate-mode 3D vertex (`RwIm3DVertex`, `rwcore.h`) | the Xbox driver's `RxObjSpace3DVertex`: position, normal, packed D3DCOLOR `color` at +0x18, u, v; `RwIm3DVertexSetRGBA` packs ARGB, `RwIm3DVertexSetPos` stores the fields directly (the D3D8 driver's pip2model.h macros; Godfather PDB's type) | the null driver's (colour union at +0xC before the normal, set through temporaries) | `DefaultPathStroke2d`, `rt2dFontShowBitmap` write the colour dword at +0x18 | `include/rw/sdk/rwcore.h` |
| `pow` and float-to-int | `_CIpow` intrinsic, `__ftol2` | `#pragma function(pow, …)`, inline-asm `fnstcw/fistp` `int32fromreal` | `RwImageSetGamma`; no RW function in the image uses the asm form | `rwplcore.h`, `os/win/ostypes.h` (guarded off for `_XBOX`) |
| `RwGlobals` | no `debugLogFunc`; 3.6's `RwFileFunctions fileFuncs` (11 pointers, `rwfexist` … `rwftell`) after `dirtyFrameList` | third party's `debugLogFunc`; no file functions | relocations: `stdFunc` at +0x48, `strcmp` slot `0x5201F4`, `rwmalloc` `0x520214`; `RwOsGetFileInterface` (0x2AB6C0) returns `0x5201A4`; RenderWare Studio's framework sets the 11 slots in this order | `rwplcore.h`, `plcore/balibtyp.h` |

## Third-party edits in the 3.7.2 tree (not in the image)

The tree carries an MMO developer's changes (comments signed DDonSS, Jaewon, gemani,
Nonstopdj, burumal; `Agcd*` types). RenderWare Studio's SDK headers
(`C:\rwstudio\Graphics\rwsdk\include\null`) are unmodified and give the stock definitions.

| Edit | Effect | Evidence | Status |
|---|---|---|---|
| `USE_THREADSAFE_*` switches (DDonSS) | a critical section in `RwFreeList` (and others) | image `RwFreeList` is 0x24 bytes (`_FreeListCreate`) | switches commented out |
| `CS_GLOBAL_GEOMETRY_*` (DDonSS) | only defined with the geometry switch on, so they compiled as function calls | `RpAtomicSetGeometry` has no call | defined empty |
| `THREADSAFE_CHECK_ISCALLEDMAIN()` | undefined off WIN32, so it compiled as a function call | `_rpWorldRegisterWorld` / `_rpWorldUnregisterWorld` have no call | defined empty |
| `RpClump`, `RpAtomic` extra fields; clump atomic list made a singly linked pointer (gemani, Jaewon) | struct layouts | stock headers | stock structs restored |
| `RwTexDictionary` 512-bucket hash table + last-texture pointer (gemani, Nonstopdj) | layout and all dictionary code | image `RwTexDictionaryCreate` initialises one list at +8, `lInInstance` at +0x10 | stock struct; `batextur.c` dictionary code rewritten |
| `RwTextureSetName` re-adding to the dictionary; `RwTextureDictionaryGetLastTexture` | extra code | image `RwTextureSetName` is `RWSTRNSTORE` only | removed |
| `RwTextureRead` without the `"(null)"` error; burumal's unlock/relock pairs | missing / extra code | image passes `aNull_1` to `_rwerror` | restored |
| Jaewon's `debugLogFunc` traps (`badevice.c`, `baclump.c`), atomic/clump names and ids | code on removed fields | — | removed |
| `baclump.c`: the clump's atomic list as a circular `prev`/`next` chain (gemani) in `GeometryListInitialize`, `RpClumpRender`, `RpClumpForAllAtomics`, `RpAtomicCreate`, `RpClumpCreate`, `RpClumpAddAtomic`/`RemoveAtomic` | code | 37 functions match once the stock `RwLinkList` code (kept commented out by gemani) is back | reverted |
| `_rpClumpClose` guarding each free list (gemani); `_rpAtomicResyncInterpolatedSphere`'s "stop-gap" `else if (geom->morphTarget)` (Jaewon) | changed code | image `_rpClumpClose` walks and destroys both lists unconditionally; its resync has the stock `if`/`else` | reverted |
| `RwGlobals.bLockSpecial1` (gemani, "For Radeon 7000~7500"), set in `_rwResHeapInit`-side code | extra field and store | not in the image | removed |
| `RwResourcesFreeResEntry`: Jaewon's commented `IsBad*Ptr` guards and `#include <Windows.h>`; DDonSS widened the release-inline `#if` with `USE_THREADSAFE_RESARENA` | noise / condition | — | reverted (`baresour.c`) |
| `_rwResourcesClose` (plcore/baresour.c) | code | the image closes and frees the resources heap without checking it exists (3.7.2 checks `memHeap != NULL`); `_rwResHeapClose` is folded into 0x2B8CB0 | applied |
| `RpGeometryDestroy` clearing `repEntry` (gemani); `RpMaterialStreamWrite`/`WorldSectorStreamWrite` zeroing their chunk structs first (gemani) | extra stores | — | removed |
| `RwFrameRemoveChild` tolerating a parentless child and a broken sibling list; `_rwFrameSyncHierarchyLTM`'s recursion checking matrix pointers (Nonstopdj) | extra checks | — | removed (stock code restored) |
| LOD atomic stream callbacks: `LODAtomicCallBackReadChunk` skipping `RpGeometryAddRef` for a null geometry (Jaewon); `LODAtomicCallBackWriteChunk` writing a copy of the cache with its callbacks cleared and its geometry pointers set to 1, byte-swapped (gemani, DDonSS) | extra code | image 0x2E8A30 adds the reference unconditionally; 0x2E8B30 writes the cache itself | removed |
| `RpAtomicSetId`/`GetId`, `RpAtomicSetName`/`GetName`, `RpClumpSetName`/`GetName` declarations and the local lights hook `RpWorldSetGetAtomicLocalLightsCallBack` (Jaewon) | extra API | not in the image | removed |
| `rwSetHierarchyRoot` returning early when the frame's child is the root ("blocking infinity loop", Nonstopdj) | an extra compare | image 0x2A3F10 has no such test | removed |
| `_rwFrameSyncDirty` breaking out of "infinite loops"; `RwFrameDestroy` calling a frame-remove callback; `_rwObjectHasFrameReleaseFrame` probing its links with `IsBadReadPtr` (Nonstopdj) | extra code | — | removed |
| `_rwFrameInternalDeInit`, `rwFrameInternalInit` | not static in 3.6 (callers push its argument; 3.7.2's static copy is called with registers) | 0x2A4540 and 0x2A3FA0; the image's callers push their argument | made extern |
| Resource heap (`resmem.c`): gemani's `isdynamicalloc` block flag, malloc fallback when the heap is full, and early-out free | extra field and code | image `_rwResHeapAlloc` returns NULL when full | reverted |
| `rwResHeapBlockHeader` padding | `pad[3]` (0x20-byte header, as its comment says) | 3.7.2 has `pad[2]` (0x1C) | image `splitBlock`/`_rwResHeapInit`/`_rwResHeapFree` use 0x20 | `resmem.c` |
| `RpHAnimHierarchyDestroy` clearing `numNodes` (Jaewon) | extra store | — | removed |
| `rpAtomicBinary` with `renderType`, `blendMode` (gemani) and `id` (Jaewon) | stream format | stock 16-byte struct | reverted |
| `RpAtomicCreate`/`RpClumpCreate` initialising `Agcd*` fields; `RpAtomicDestroy` freeing `stType` and clearing `repEntry`; `RpAtomicClone` copying render info; `RpAtomicRemoveDirtyFrameList[Ex]` | extra code | stock structs have no such fields | removed |
| `RwEngineInit(memFuncs, lockFuncs, openFlags, resArenaSize)` (DDonSS) | extra parameter | image reads `openFlags` at `[esp+8]` | parameter removed (`badevice.c`, prototypes) |
| `RWSRCGLOBAL(debugLogFunc) = NULL` in `RwEngineInit` (Jaewon) | extra store | — | removed |
| `RPLODATOMICMAXLOD` 20 | LOD tables | `LODAtomicSelectLOD` clamps to 9 | set to 10 |
| `rtpitexdImage2TextureRead`'s two mip-level loops (tool/pitexd/rtpitexd.c, a Korean-commented edit dated 2005-06-03) | loop bound `min(rasterMipLevels, numMipLevels)` (a `cmovge`) | image loops to `rasterMipLevels` (`cmp edi, ebx; jl`) at 0x2F59F4 and 0x2F5AC6 | stock loops restored; matched |

## RenderWare 3.6 code that 3.7.2 changed

| Function | 3.6 (image) | Status |
|---|---|---|
| File functions (`RwOsGetFileInterface`, default `rwfexist`, the call filling the table with the C library's `fopen` … `ftell`) | 3.6 only; `RwEngineInit` opens them after `_rwMemoryOpen` and closes them (an empty function, folded into `nullsub_1`) on failure, as `RwEngineTerm` does | matched (`plcore/unit_2AB6C0.c`, `badevice.c`) |
| File access (`RwFexist`, `RwFopen`, …) | macros over `RWSRCGLOBAL(fileFuncs)` (`plcore/fsys36.h`, used by `bastream.c`, `baimage.c`, `tool/2d/font.c`) | 3.7.2 calls the RtFS toolkit | `ImageAttempRead`, `ImageDetermineExtender`, the streams call through 0x5201A4… | matched |
| `RwEngineInit` | the image's is `src/badevice.c`'s (with `_rwFreeListEnable`), not `plcore/baplcore.c`'s; the other engine functions are identical in both | matched |
| 2D fonts (`tool/2d/font.c`) | `AttemptToOpenFont` and `FontDefaultRead` get the file table from `RwOsGetFileInterface` (the default reader returns NULL without `rwfexist` and `rwfgets`) and pass it to `FontReadMetrics2d1`/`2`/`3`, which read through it; `Rt2dFontShow` returns the font, not the callback's result; the metrics reader's buffer top-up has one branch (the 3.7.2 tree's extra full-buffer branch, which left the original unreachable, is a third-party edit) | `_rt2dFontOpen` clears the extra word after `Rt2dGlobals.fontReadFunc` (0x51ED9C) | matched; `FontDefaultRead` tests the file table and its two functions in three separate ifs (the tree has one) |
| Build stamp (`src/badevice.c`) | only 3.6's written-out stamp ("Core built at Sep 21 2004 14:41:55", `unk_416240`) | 3.7.2's `_rwBuildDateTime` from `__DATE__`/`__TIME__` as well | `_rwBuildDateTime` under `#if 0` (its 40 bytes were the M7 probe's .rdata shift after `bamatrix`, 2026-10-04) |
| Animation free-list parameters (`tool/anim/rtanim.c`, `tool/2danim/gstate.c`) | none: `RtAnimAnimationFreeListCreateParams` and `Rt2dAnimSetFreeListCreateParams` and their `.data` variables are not in the image (plain `.data` is never dropped, and the image has no room for them: the 2D toolkit's free-list sizes follow `unit_250B20`'s table and the message table follows them) | 3.7.2's initialized statics and setters | `rtanim.c` takes the defaults as constants (`AnimOpen` is not in the image either); both setters under `#if 0` (M7 probe, 2026-10-04) |
| 2D animation message queue (`tool/2danim/message.h`, `message.c`) | `Rt2dMessageQueue` holds its 64 messages (0x408 bytes, the free list size in `Rt2dAnimOpen`); destroying it only clears the counters | 3.7.2 allocates the messages with a size field and `Rt2dMessageQueueSetDefaultSize` | matched (`_rt2dMaestroDestroyMessageQueue`, `Rt2dAnimOpen`); the setter and its `_rwDefaultMessageQueueSize` variable under `#if 0` (the image's message table is followed directly by Bink's popmal statics) |
| `RwTextureStreamRead` | honours `rwTEXTURESTREAMFLAGSUSERMIPMAPS` (the tree's "2005.2.28 gemani UserMipMap Disable" comment-out is a third-party edit); sets the filtering only for a texture just loaded, restores the mipmap state, then reads the extension chunks for every texture (3.7.2 skips them for an already loaded one) | matched |
| RtFS (`tool/fsyst/rtfsyst.c`) | `_rtFSIsEOF` compares the 32-bit halves (the tree's `WIN32` branch, now also taken for `_XBOX`); `_rtFSInit` checks and copies the device name itself (3.7.2 calls `RtFileSystemSetDeviceName` after clearing it) | matched (RtFS is built with VC7.0: docs/toolchain.md) |
| `_rwImageGammaUnCorrectArrayOfRGBA` | reads `gammaTable`, not `invGammaTable` | matched |
| Streams (`bastream.c`) | 3.6 keeps `RwStream.position` (+8): the initialisers set it to 0 and read/write/skip advance it; file access goes through `RWSRCGLOBAL(fileFuncs)` (`rwfopen`, `rwfseek`, `rwfeof`, …), not the RtFS toolkit | initialisers, `RwStreamRead` (which keeps the `E_RW_ENDOFSTREAM` error Nonstopdj commented out), `RwStreamWrite` and `RwStreamClose` matched; `RwStreamSkip` matched with the Godfather file-branch retVal/single-return structure (docs/questions.md) |
| `LODAtomicCallBackRender` | static, and calls the saved render callback unconditionally (Jaewon made it extern with a NULL check) | reverted |
| `UserDataObjectCopy` | no NULL check on the lists (burumal's) | reverted |
| `RpGeometryStreamRead` | still reads 3.4 geometries: below 0x34001 the header is followed by surface properties, set as the default for the materials read with `_rpMaterialSetDefaultSurfaceProperties` (and reset to NULL after) | matched |
| `PlaneSectorStreamRead` | returns NULL at once when the left plane sector's chunk is missing | matched |
| `RpWorldStreamRead` | still reads 3.4's `rpWorldChunkInfo34000` header (version < `0x34001`) and computes the bounding box for < `0x34003` | written, one scheduling difference left (docs/questions.md) |
| `RpMaterialUVAnimApplyUpdate`, `UVAnimCopy`, `CreateDummyAnim`, `ParamKeyFrameDataInitFromMatrix` | `UVAnimCopy` is 3.6's: the extension copied whole, then a reference added to each slot's animation (no interpolator copies, no failure cleanup); the other three are 3.7.2's code, unplaced only for want of annotations; `UVAnimWrite` matched once the version and headers were fixed | matched (`plugin/uvanim/rpuvanim.c`, `param.c`) |
| `RwFrameTranslate`, `RpPrtStdEClassStreamRead`, `MatFXAtomicStreamRead`, `RpPrtStdEClassGet` | the image has second copies at other addresses (0x2A42B0, 0x2EEF80, 0x2F6EF0, …) reading other globals or calling other targets | open |
| `RpSkin` | the Xbox platform data is 0x810 bytes (split data at 0x82C, `unaligned` at 0x844; 0x848 in all), fields not yet worked out | `SkinCreate`, `SkinCreateSkinData` matched |
| User data (`plugin/userdata/rpusrdat.c`) | `UserDataDestruct` frees the name and data without clearing the pointers; `UserDataListGetSize` counts the count's word whenever the list has elements; `UserDataListStreamWrite` writes the count even when no element has a format; `UserDataStreamRead`/`Write` read and write int and real data one element at a time (3.7.2: one call for the whole array) | all matched |
| Collision line iterators (`RpSectorLineIt`, `RpCollSectorLineIt`; plugin/collis `ctquery.h`, `rpcollis.h`) | no `padding` field (`RpSectorLineIt` is start, delta, recip, 65 stack entries, `curr` at +0x330; `RpCollSectorLineIt` is tree, start, delta, recip, the dummy sector, 33 entries, `curr` at +0x1BC); `RpSectorLineItInit`/`RpCollSectorLineItInit` take no padding argument; the first node's parameters are fattened by `rpCOLLISION_LINE_EPS` (1e-5: -1e-5 to 1.00001) and each clip in the step macro adds (end) or subtracts (start) it; `RpCollSectorLineItInit` clips the line against the tree's box first with its own interval test on the line's ends (a direct `start == end` check, `1/(end - start)` computed there), clamping with `RwRealMax2`/`RwRealMin2` | matched: both far clips, both find-next functions, `RpSectorLineItInit`, and the collision queries `WorldForAllSectorsIntsecLine`, `WorldForAllAtomicsIntsecLine`, `RpWorldForAllAtomicIntersections`; `RpCollSectorLineItInit` and `GeometryForAllTriIntsecLine` also match (2026-10-01): compute clipped endpoints inside each sign branch, with inf before sup in both branches; negative r therefore assigns hi before lo |
| `RpPrtStdEClassGet`, `RpPrtStdEClassGetByPropTab`, `RpPrtStdEClassStreamRead` second copies (0x2EEF20, 0x2EEF50, 0x2EEF80) reading `_rpPrtStdGlobals`+4 | a second compiled copy the database names with `_0` suffixes | open |
| 2D animation globals (`tool/2danim/gstate.h`) | pointers to free lists that `Rt2dAnimOpen` creates with `RwFreeListCreate(size, 20, 16, hint)` (3.7.2 embeds the lists and preallocates) | `Rt2dAnimClose`, `Rt2dKeyFrameListDestroy` matched; `Rt2dAnimOpen` open |
| `SkinGeometryRead` (skin2/rpskin.c, 0x2D1440) | still reads pre-3.5 skins: when the packed max-weights byte is 0 it creates the skin with every bone used and 4 weights, skips the used-bone list, reads a skipped int and a matrix per bone, then finds the weights and used bones itself; otherwise it stores the max weights and reads the matrices and split data as 3.7.2 does | matched |
| `Rt2dMaestro` | 4 bytes bigger (0x15C); position after `scene` unknown | open |
| `Rt2dMessageQueue` | 0x408 bytes (a fixed queue) against 3.7.2's 0x10 | open |
| The Xbox driver (`_rwXb…`, 0x2AC710 on) | not in the 3.7.2 tree (its nearest relative is `driver/d3d8`); written from the image in `src/rw/driver/xbox/`; the type, field and global names come from the Godfather (ears_godfather_r.xbe) PDB's copy of the same driver (`RwXboxRasterExtension`, `_rxXboxDriverGlobals`, `RwXboxDeviceConfig`, `_rwXbStateCache`, `RwXbStateCache`/`RwXbTextureCache` without the underscore) (`xbraster.c`: the raster extension of 0x18 bytes under `rwID_DEVICEMODULE`, free lists of the textures' and palettes' D3D headers) | matched: `xbraster.c` (plugin attach, open, close, size, mip levels, sub-raster, texture raster) and `xbconvrt.c` (28: the pixel converters both ways, `_rwXbRGBToPixel`, `_rwXbPixelToRGB`, raster to image, image to raster, palettising) and `xbrendst.c` (16 so far: the render, texture stage and texture state caches sent to D3D by `_rwXbFlushCacheBuffer` before each draw, a dirty list rather than 3.7.2 d3d8's `RwD3D8SetRenderState` straight calls; the stencil setters through RenderWare-to-D3D tables; the vertex and pixel shader setters, the pixel shader refreshing the cached `D3DRS_PSTEXTUREMODES`; the state cache open, get and set, the fog/address/filter/Z/blend/shade/vertex-alpha/cull setters, `RwXboxRenderStateSetTexture`, the texture stage raster, its purge, the texture release and `_rwXbCacheInit`, which seeds every D3D render and texture stage state and picks the swap filter and multisample modes from the device configuration's multisample type; its loop shapes follow the Godfather debug build (ears_godfather_d.xbe)). Unlike 3.7.2 d3d8's render states: every state goes through the dirty-list cache and none checks RenderWare's own cached value first (except the fog type, blends, shade and cull modes); texture addressing, filtering and anisotropy are applied per stage by `RwXboxRenderStateSetTexture`, the filter table gaining anisotropic entries (mode | 8) when an anisotropy plugin offset is set; getting the stencil states returns FALSE after writing the value; the texture raster purge and a NULL texture clear stage 0 inline. IDA took seven static setters (0x2AFF60-0x2B0380, `XbRenderStateZTestEnable` to `XbRenderStateCullMode`, named after the image's `XbRenderState*` statics and d3d8's `rwD3D8RenderState*`) for chunks of `_rwXbSetRenderState`; they are named in config/symbols.txt and splits.txt by hand, and the database's `_RwXbFilterModeConvTable` label is 4 bytes into the table (0x416800). Unlike 3.7.2's d3d8 driver: the luminance converter has no alpha scaling; A4R4G4B4 unpacking has no full-alpha special case; the unconverter table also maps `rwRASTERFORMAT32`; raster-to-image uses the generic unconvert-function loops; 8-bit palettes are stored BGRA (red and blue swapped on the way out, packed ARGB on the way in, only at mip level 0); sub-raster locks and conversions read the parent raster's extension. The raster lock and unlock (`_rwXbRasterLock`, `XbRasterLockMipLevel`, `_rwXbRasterUnlock`) and the palette lock and unlock are matched. The XDK's `D3DTexture_UnlockRect`, `D3DSurface_UnlockRect` and `D3DPalette_Unlock` are empty inlines, so the image cannot show whether this version unlocked on the lock's failure paths as Godfather's 3.7 driver does; the palette functions check the raster type with a switch (normal, texture, camera texture). `_rwXbGetRasterFormat` and its `_rwRasterConvTable` (swizzled and linear D3D formats per RenderWare pixel format) are matched; unlike Godfather's 3.7 it reports no error for mipmapped or palettised normal rasters, palettised camera rasters or odd camera texture formats, and takes any given camera texture format's depth from the Z buffer unchecked. Raster create and destroy (with `XBoxTextureCreate`, `XBoxPaletteRelease`, `TextureRasterCreate`, `ZRasterCreate`, the native and cube native creates) are matched; unlike 3.7 this version sets no pitch for linear textures (its `XGSetTextureHeader` pitch is 0 and the size is the whole mip chain), and does not warn about non-power-of-two textures or oversized rasters. The files follow the debug build's layout (xb2drend.c, xbcache.c, xbconvrt.c, xbdevice.c, xbdxttex.c, xbmemory.c, xbraster.c, xbrendst.c, xbsprite.c, xbtexdic.c): the caches, their flush and init, the draw wrappers, the render target and the texture release are in `xbcache.c`. `xbdxttex.c` (the DXT1 alpha scan and the DDS reader, `RwXboxDDSTextureRead`) is matched: the alpha scan is d3d9dxttex.c's; the reader (`XboxDXTTextureRead`, the database's `rwD3D9DXTTextureRead`) is Godfather's without its palettised DDS support, tests the pixel format flags with an if chain, and swaps 24-bit texels as `((c & 0xFF) << 16) | ((c >> 8) & 0xFFFF)`. `xbmemory.c` (the physical memory manager and dynamic vertex buffers, 13 functions) is matched; against Godfather's 3.7 copy it has no allocation counters, and a few branches are laid out the other way round (the allocator's header and shrink branches, the dynamic lock's create path first, the free's size update in both branches). The image format finders (`XbImageFindFormat`, `_rwXbImageFindRasterFormat`) are matched too. `xbdevice.c` (18 functions: the surface properties, the format finders, the device open, start and standards, the plugin registration, the default render target, the current device getter, the camera begin and end update, clear and show raster, the render-target helper, `XbSystem` and `_rwDeviceGetHandle`) is matched. Its top-raster helper `XbGetTopRaster` is a static function (as in Godfather's debug build), inlined here; `XbSystem` sets a result in each case and returns it once, its cases in the debug build's source order except close and focus, which share the device-ID case's TRUE tail as the image's jump table has them (the debug build's static `XbDeviceSystemClose` releases Direct3D, an empty inline in the XDK, so it is TRUE alone; the stop inlined), and `XbDeviceSystemStart` fills the present parameters in the debug build's order; the device open calls the XDK's `Direct3DCreate8` (0x31D4C0, a stub returning 1); the clear draws a push-buffer quad and sets Z-write in an if/else. The stub driver's `driver/stub/sbdevice.c`, placed earlier at `_rwDeviceGetHandle` only because both compile to the same six bytes, is removed. `xb2drend.c` (the 2D shaders' open and close, `_rwXbIm2DRenderSetVertexShader`, `XbIm2DRenderSetup`, line, triangle and primitive) is matched, with its shader microcode, declarations and `RwXbPrimConvTable` defined from the image; the 2D vertex is Godfather's `rwXBOXVERTEX` (0x1C bytes). Unlike Godfather's 3.7 copy, this version defines `XbIm2DRenderSetup` before the line renderer and takes the vertex shader's scale constant from `D3DDevice_GetBackBufferScale` (3.7 sets it to 1). `_rwXbIm2DRenderIndexedPrimitive` copies the vertices with an inline-assembly MMX loop (fixed `esi`/`edi`/`ecx`, `prefetchnta`, `movntq`, `emms`, and an `ebp` frame, the same in Godfather's debug build), so it stays binary under the no-`__asm` rule. `xbtexdic.c` (native texture size, write and read, after 3.7.2's `d3d8texdic.c`, with Godfather's `_rwXbNativeTexture`/`_rwXbNativeRaster` records and its read's `convTable`) is matched: sizes and writes cover every cube face and pad the pixel data to four bytes. Unlike Godfather's 3.7 copy, the read accepts streams from 0x34000 (3.7 wants 0x35000): below 0x34001 it reads an older 16-byte raster header (no cube flag or data size) and then each level's size and pixels; a plain (not cube, not DXT) raster is made by `RwRasterCreate` alone rather than `_rwXbRasterCreateWithMipMaps`. `xbsprite.c` (raster render, copy and clear: `XbRasterRenderQuad`, `XbRasterCopyQuad`, `XbRasterRenderGeneric`, the render, fast and scaled entry points, `_rwXbRasterClearGeneric`, clear, clear rect and `_rwXbSetRasterContext`) is matched, after 3.7.2's d3d8raster.c sprite functions. Unlike Godfather's 3.7 copy, `RwXbCurrentRasterTarget` is static here (only this file uses it, and the loops keep it in a register across pixel stores), and the render quad neither begins nor ends a scene. The Xbox Im3D pipelines (`src/pipe/p2/xbox/im3dpipe.c`, not in the 3.7.2 tree) are d3d8's `im3dpipe.c` with the Xbox nodes and without its Im3D renderer open and close calls; its nodes (`nodeXBoxSubmitNoLight.c`: `XbSubmitNode`, `XbImmInstanceNode` and the two node definitions) are matched. Unlike Godfather's 3.7 copy, the submit node skips the world matrix copy for an LTM flagged `rwMATRIXINTERNALIDENTITY`, and the pool pointer is static. These files compile with `src/rw/driver/xbox` on the include path (their own config/flags.txt rule) |

## The game's own additions inside RenderWare

| Addition | Where | Status |
|---|---|---|
| Texture lock: `_csTexture` (a `CRITICAL_SECTION *` the game sets through `sub_2A7870`), taken in dictionary create/destroy/iterate and `TextureDefaultFind` | `batextur.c` | matched |
| Xbox square roots: besides `rwSqrtMacro`, the Xbox build's `rwInvSqrtMacro` and `rwSqrtInvSqrtMacro` are SSE too (`_mm_sqrt_ss`, the root zeroed unless positive by an `_mm_cmpgt_ss` mask, then `1 / root` when above zero); the 3.7.2 tree uses its reciprocal-sqrt table there. Found from `RwV3dNormalize` and the collision triangle normals | `bavector.h` (and `rwplcore.h`) | matched: `_rwV3dNormalize`, `RwV3dNormalize`, the camera clip planes and sync, the matrix rotations, the collision triangle queries, `RtIntersectionSphereTriangle` |
| The Xbox world pipelines (`world/pipe/p2/xbox/`: xbvtxfmt.c, xbpipe.c, wrldpipe.c, native.c, xbpixelshader.c, the all-in-one nodes; 0x2DCB70-0x2E2720) | not in the 3.7.2 tree; written from the image with the Godfather PDB's names and types (`RpXboxVtxFmt`, `RxXboxResEntryHeader`, `RxXboxInstanceData`); they compile with `src/rw/driver/xbox` on the include path (their own config/flags.txt rule) | `xbvtxfmt.c`: the vertex format array create and destroy, size and stride, colour instancing, the plugin's copy, open, close, size, write, reads and attach, the geometry and world getters, `RpXboxVtxFmtInit`, the V3d and V2d un-instancers and `RxXboxGetVertexFormatShader` (with `BinaryFindVertexFormat`, which /OPT:ICF folded into the skin plugin's identical `SkinBinaryFindVertexFormat` at 0x2D43D0) are matched. Unlike Godfather's 3.7 copy, the vertex format array and its counts are static; the plugin constructor and destructor that only return the object were folded by /OPT:ICF into colldata.c's `CollisionDataConstructor` (aliased); the V3d, compressed-normal V3d, morph V3d and V2d instancers are matched with RenderWare's Xbox `RwFastRealToUInt32` asm helper and the V3d instancer's own MMX `movntq` copy `__asm` (both in the Godfather debug PDB); the BNT instancers are near misses (docs/questions.md). The lights (`xblights.c`, named by the image's own RCS id string; Godfather keeps no file name for them): `_rwXBLightsGlobalEnable` (the ambient colour packed with the asm helper), `_rxXBLightLocalEnable` and `RwXboxLightsEnable` are matched. `xbpipe.c`: `XBMeshGetNumVerticesMinIndex`, the resource entry destroy, `SortTriangles` and `_rxXBInstance` are matched; unlike Godfather's 3.7 copy, the instancer clears only the header and instance data (3.7 clears the whole entry) |
| World arena allocator: `sub_2DAAF0` swaps RW's malloc/realloc/calloc for 32-byte aligned arena allocation (`sub_2DA220`, `sub_2DAA70`, `sub_2DA260`), `sub_2DA2F0`/`sub_2DA2D0` make free skip the arena's bounds (`dword_50F250`–`dword_50F254`), `sub_2DA340` restores | `babinwor.c` | matched |
| Arena users: `_rwFreeListAllocReal` parks the arena while it mallocs a block; `_rwFreeListFreeReal`, `TextureAnnihilate`, `RpMaterialDestroy`, `RwRasterDestroy` skip frees inside it; `RwTextureCreate` allocates from it when the arena malloc is installed; `RpMaterialCreate` likewise; `RwRasterCreate` too, and then frees a failed raster to its free list only when it did not come from the arena; `_rpMaterialListStreamRead` calls the arena malloc directly for its index array; `_rpMaterialListSetSize` and `_rpMaterialListAppendMaterial` grow the list by allocating from the arena and copying (the new size's worth) instead of realloc, and Append allocates a new list with plain `RwMalloc` | `bamemory.c`, `batextur.c`, `bamateri.c`, `baraster.c` | matched |
| `RwTexDictionaryCreate_Internal` (arena-allocated dictionary) | `batextur.c` | matched |
| `RwTexDictionaryStreamRead(stream, arena)` and `RpWorldStreamRead(stream, arena)` take the arena as a second argument; they and `WorldSectorStreamRead`/`PlaneSectorStreamRead` give up when the arena's abort flag (`*dword_50F24C`) is raised | `babintex.c`, `babinwor.c` | matched except `RpWorldStreamRead` |
| `j__RpWorldDestroy`, a forwarder `RpWorldStreamRead` uses when an arena load fails | `baworld.c` | matched |
| `RwTexDictionaryCreate` and others call `RwOsGetMemoryInterface()` and discard the result | several | matched |

## Build and linking notes

- The RtFS toolkit (`tool/fsyst/rtfsmgr.c`, `rtfsyst.c` and the Xbox file system `xbox/rtfsxxbx.c`, 0x257AB0-0x258B20)
  is built with VC7.0, which pads between functions with `nop`s (0x90) inside each function's own section, so the
  compiled pieces fill their whole `config/splits.txt` ranges. `xbox/fsystplatform.h`, `xbox/rtfsxxbx.c` and `.h` are
  not in the 3.7.2 tree: the platform header is written from the image (a critical section as on Windows); the file
  system is the tree's `win/rtfswin.c` with the Xbox changes the Godfather debug build shows (asynchronous reads and
  writes ask `XGetDiskSectorSizeA` for the device root's sector size through a static `dev` buffer instead of keeping a
  sector size per file system; sync closes the operation's event handle; init clears each file's event handle and does
  not check the allocation; open does not store the last error). Its layouts are Godfather's (`RtXboxFile` 96 bytes,
  `RtXboxFileSystem` 92). VC7.0 defers `TkXboxFSystemFOpen` (it inlines the later `TkXboxFSystemSetPosition`) to after
  `TkXboxFSystemFileExists`, as in the image.
- The static `lastSeenRightsPluginId` / `lastSeenExtraData` in `bamateri.c` are the database's `_0`
  copies (`0x50F1B8`, `0x50F1C4`); `baclump.c`'s come first.
- Calls the image makes to ICF-folded copies are aliased in `config/aliases.txt`
  (for example `_rpDestroyPlatformMaterialPipelines` and `_rwPipeInitForCamera` → `nullsub_1`).
- `_rwDeviceRegisterPlugin` is the Xbox driver's jump to `_rwXbRasterPluginAttach` (0x2B3970); `_rwStringClose` is
  empty and folded into `nullsub_1`; `_rwMemoryClose` is a jump to `_rwFreeListModuleClose` (0x2A9A30).
- The database calls 0x2E4840/0x2E4870 `RwFrameGetUserDataArrayCount`/`RwFrameGetUserDataArray`, but they read
  `userDataGeometryOffset`: they are `RpGeometryGetUserDataArrayCount`/`RpGeometryGetUserDataArray`.
- The database missed `_rt2dPickRegionDestruct` (0x256D20) and `_rt2dShapeDestruct` (0x256DC0), treating them as tail
  chunks of `_rt2dObjectDestruct`, which jumps to them; they are now in config/symbols.txt and config/splits.txt.
- The database's `_rt2dObjectDestroy` (0x256CB0) is `Rt2dSceneDestroy`.
- Particle names are shifted in the database: its `RpPrtStdEClassGet` (0x2EEA60) is `RpPrtStdEClassCreate` and its
  `RpPrtStdEClassGet_0` (0x2EEBE0) is `RpPrtStdEClassGet`; `RpPrtStdEmitterCreate` (0x2EF0E0) is `_rpPrtStdEmitterCtor`,
  `__rpPrtStdEmitterDtor_1` (0x2EF9A0) is `_rpPrtStdEmitterDtor` and `__rpPrtStdEmitterDtor` (0x2EF080) is
  `_rpPrtStdParticleBatchDtor`.
- Skin names are shifted in the database: its `SkinAtomicSetup` (0x2D0CA0) is `SkinAtomicAttachBestPipeForAttachedPlugins`,
  and its `SkinAtomicAttachBestPipeForAttachedPlugins` (0x2D1830) is the Xbox `_rpSkinPipelinesAttach`.
- More database misnamings, placed by their unique byte matches: `CountNodes` = `CountLeafs` (0x2B6460), `StatsSub` =
  `LeafCalcStats` (0x2B53B0), `_RpCollisionWorldForAllIntersections` = `RpWorldForAllWorldSectorIntersections` (0x2C2320),
  `_RpHAnimHierarchyAttachFrameIndex` = `RpHAnimHierarchyAttach` (0x2E6630), `_RpPVSWorldSectorVisible` = `RpPVSQuery`
  (0x2E7D00), `PVSFindDiagonalSizeOfBBox` = `RwV3dLength` (0x2A3C70), `RtQuatQueryRotate` = `RtQuatTransformVectors`
  (0x2E52F0), `RaySphereIntersect` = `RtLineSphereIntersectionTest` (0x23B640, `tool/ray/rtray.c`); unnamed:
  `MultiTextureOpen` (0x2FC3B0), `RpMatFXMaterialGetEffects` (0x2F6730), `_rwStringStreamGetSize` (0x2B50A0).
- The database's `_Rt2dFontTexDictionaryGet` (0x255220) is `Rt2dFontTexDictionarySet` (it stores its argument in
  `Rt2dGlobals.currFontTexDictionary`); its `_RpSectorLineItSetFarClip` (0x2C2FC0) is `RpCollSectorLineItSetFarClip`, its
  `_RpSectorLineItSetFarClip_0` (0x2C2AB0) `RpSectorLineItSetFarClip`, its `Collision_LineClipBBox` (0x2C2B20)
  `RpCollSectorLineItInit` and its `Collision_StepSphereQuery` (0x2C2DD0) `RpCollSectorLineItFindNextEntries`.
- Found by their bytes: the database's `RpMatFXWorldSectorEnableEffects` (0x2FC140) is the Xbox
  `_rpMatFXPipelineWorldSectorSetup`, `MatFXAtomicStreamRead_0` (0x2F6EF0) `MatFXWorldSectorStreamRead`,
  `RpPrtStdEClassGet_0_0`/`GetByPropTab_0`/`StreamRead_0` (0x2EEF20-0x2EEF80) the `RpPrtStdPClass` versions,
  `__rpPrtStdPTankStreamRead_0` (0x2F2750) `_rpPrtStdPTankStreamWrite`, `_RwFrameTranslate_0` (0x2A42B0) `RwFrameTransform`,
  `_Rt2dDeviceSetFlat_0` (0x256350) `Rt2dDeviceSetLayerDepth`, `Rt2dMaestroDestroy_0` (0x257990) `Rt2dCelListDestroy`,
  `SubPathEmpty2d` (0x2AB840) `_rwSListEmpty`, `_RpAtomicGetGeometry` (0x2D12E0) `RpSkinGeometryGetSkin`; the unnamed
  `sub_2D12C0` is `RpSkinAtomicSetHAnimHierarchy`, `sub_2E48A0` `RpUserDataArrayGetInt` (with `GetString` folded in),
  `sub_2FC3C0` `MultiTextureClose`, `sub_2EDE70` `_rpPTankGENInsEnding`, `sub_2FC160`
  `RpDMorphTargetGetBoundingSphere`.
- The database names `RwEngineGetPluginOffset` (0x2A6540) `MatfxPluginIsAttached`.
- The C library's `fread` and `fwrite` are swapped in the database's names (`_fread_0` is `fread`, `_fread` is `fwrite`).
- History: each hand-edited RenderWare file is first committed exactly as in the 3.7.2 tree, then edited in the
  next commit, so `git log -p` on the file shows its differences (`baclump.c`, `badevice.c` from 2026-09-30 on).
| The Xbox material effects and multi-texture pipelines (`plugin/matfx/xbox/`: effectPipesXbox.c, multitexxbox.c; 0x2F7CA0-0x2FC3A0) | not in the 3.7.2 tree; written from the image with the Godfather PDB's names (`RpMatFXXboxMaterial` 0x18 bytes, 0x88-byte stages); `MatFXBumpMapData` gains the Xbox `vbStride`, `tex2` and `bumpVertexShader` fields | all matched. Unlike Godfather's 3.7: the render callback has no black-environment path; the bump-environment renderer picks the frame-buffer-alpha pixel shaders; the multi-texture path sets up with `_rpMatFXMTRenderStateSetUp` (no separate MT render); the old blend (`MatFXMTOldSrcBlend`/`DestBlend`) is global; the cached-state helpers have no misc-state function |
| The Xbox PTank platform files (`plugin/ptank/xbox/`: ptankxbox.c, ptankxboxopt.c; 0x2E9B20-0x2EB1E0) | not in the 3.7.2 tree (only D3D8/D3D9/OpenGL) or the Godfather PDB; written from the image following `ptankd3d8.c` | all matched. Constant texture coordinates that fit 0..1 are packed as bytes (`rpPTankXboxInsUV2C`/`UV4C`, flag `rpPTankXboxPackedUVs`); normals are packed (`rpPTankXboxInsNormals`); the render callback builds an `RpXboxVtxFmt` and takes its vertex shader from `RxXboxGetVertexFormatShader`; `platFlags` 1 selects a point-sprite path (ptankxboxopt.c) that reads its stride and constant-colour flag from `userData` |
| RCS id strings | every RenderWare object keeps 3.6's `static const char rcsid[]` (`"@@(#)$Id: //RenderWare/RW36Active/rwsdk/...c#n $"`, some `@@@@(#)`) first in its .rdata; uvanim's stdkey.c, param.c and linear.c keep hanim's dev-branch stdkey.c id, 2danim's gstate.c keeps fast2d's 2d/gstate.c id; the collis files' ids are empty (`"@@@@(#)$ $"`, ctquery.c's `"@@@@(#)$Id:  $"`) except ctbuild.c's; 3.6's plcore/bafsys.c is unit_2AB6C0.c, os/xbox/osintf.c the tree's os/win copy; rt2d.c, fill.c, 2danim's handler.c and rt2danim.c, chrprint.c, ctbuild.c and collbuild.c keep only data (their code is unreferenced), so they are imported for it; badevice.c also keeps 3.6's build stamp `"
| badevice.c and plcore/baplcore.c | one object, badevice.c (its RCS id), whose 17 engine functions, the plugin registry (`engineTKList`, its maximum 0x4000) and `_rwMsbBit` sit in one address run (0x2A63E0-0x2A6C00) | two build variants of the same file (the platform core library's copy in plcore/) | the functions alternate between the two files' versions by address; `RWGLOBALSIZE` 0x4000 matches every RenderWare unit | badevice.c defines all of them (baplcore.c's versions of 12 functions moved in); baplcore.c is left empty; config/flags.txt `/DRWGLOBALSIZE=0x4000` |
| 2danim message.c's `_rwDefaultMessageQueueSize` | not after `_rt2dMessageDescripTable` (0x4310B0-0x43117C, then popmal's data); its functions are not in the image | a `.data` global (64) after the table | the image's .data around the table | open: the placement link takes the table alone; for M7 the variable (and `Rt2dMessageQueueSetDefaultSize`) has to go or move |
| prtstd pptank.c's `RpPrtStdEmitterCreatePTank` | the game's own (0xEFBC0, unit_0EFBC0) | defined in pptank.c | the game unit's function is the one placed; a second definition cannot link | under `#if 0` in pptank.c |
Core built at Sep 21 2004 14:41:55
"` after its id (`unk_416240`, the date written out) | no rcsid strings | the strings at their objects' .rdata starts, in link order (0x3EB06C-0x41ABF8) | the files' definitions after their includes (tools/session/rcsid.py); effectPipesXbox.c also defines the three unreferenced tables between the bump map tables and `rxXbTexTrxTable` (`unk_41A7B4`, `unk_41A7CC`, `unk_41A7F4`, each under 64 bytes), unnamed in Godfather too |
- `bamatrix.c`: the image's `RwMatrixOrthoNormalize` (0x2A59A0) tail-jumps to the static
  `MatrixOrthoNormalize` (0x2A48C0) with its register convention instead of inlining it (3.6 has
  another caller, or the helper was not inlinable); the copy here marks the helper
  `__declspec(noinline)` to keep the call (2026-10-01). The helper's own body is still a near miss.

- `xbpipe.c`, `_rxXbDefaultRenderCallback` (0x2E02A0, 2026-10-01): the image's
  texture-stage writes require typed inline parameters for the force operation.
  `_rwXbTextureStageForceInline` in xbcache.h has exactly the existing macro's
  cache comparison, cache write, and D3DDevice_SetTextureStageState call. Using
  that inline in the callback fixes both remaining scheduling differences;
  the whole function matches (1240 bytes, 116 relocations).


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

### Delta-morph callback source context (2026-10-01; still unmatched)

Godfather debug 0x11348D0 records a signed position size local and uses
D3DVertexBuffer_Lock with vbSize. Restoring these details allows the original
indexed counting loop to emit the game's pointer traversal under VC7.1.
An unsigned numTexCoordSets initialized by a signed conditional expression
also changes later copy-call scheduling. The draft improves from 894 to 495
normalized lines; stack placement and prelight-copy differences remain.
Use dmorph_instance_reference_followup.c, not the previous distance draft.

## Resolved: Xbox delta-morph callback and helper (2026-10-01)

XboxDMorphAddBlock and XboxDmorphAtomicInstanceCallback now match in
dmorphpipeg.c (109 / 5,740 bytes; callback 93 relocations and 160 table bytes).
The previous draft's remaining allocation differences came from separate
locals for each attribute pass. Share currentBlock, j, l, target/RLE pointers,
scale and delta pointers across passes; keep k, m and maxl in their narrower
scopes. Initialize j before k/m. This reproduces the game's stack lifetimes,
final color-channel conversion and copy-call scheduling under VC7.1.
No compiler or header changes were required. Production supersedes the drafts.
