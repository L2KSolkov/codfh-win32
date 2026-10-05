# Xbox SDK API inventory (game sources -> SDK libraries)

Every UNDEF external symbol in the objects of the plain link (build/plain/link.rsp, 637 game objects) that an SDK library defines, resolved through build/plain/game.map ("lib:object" column), falling back to the libraries' linker members. Symbols defined by our own objects are excluded. Users are source files; `src/recovered/` is left off unit names. The last plain link was a `--devnet` one, so the online libraries are xonline.lib/xnet.lib; the default build uses xonlines.lib/xnets.lib, which export the same names (the XNet/Winsock functions resolved to xonline.lib members `xnet.obj`/`sock.obj`, so they are listed under xonline). References kept even when the referencing function is dropped by /OPT:REF.

## Summary

| library | distinct symbols | using source files |
|---|---:|---:|
| d3d8 | 106 | 35 |
| xapilib | 52 | 27 |
| dsound | 41 | 5 |
| xonline | 41 | 9 |
| uix | 26 | 3 |
| xvoice | 18 | 1 |
| xgraphics | 17 | 6 |
| binkxbox | 11 | 2 |
| xboxkrnl | 3 | 9 |
| d3dx8 | 3 | 3 |
| libcpmt | 2 | 132 |
| libcmt | 86 | 499 |
| **all SDK libs except CRT** | 318 | 70 |

Using files by tree (non-CRT): src/recovered (game units) 33, src/rw 27, src/rwa 8, src/rws 2.

## d3d8 (106 symbols, 35 files)

### API functions

| symbol | users | note |
|---|---|---|
| `D3DCubeTexture_GetCubeMapSurface2` | src/rw/driver/xbox/xbdevice.c, src/rw/driver/xbox/xbsprite.c | cube face surface |
| `D3DCubeTexture_LockRect` | src/rw/driver/xbox/xbraster.c | cube texture lock |
| `D3DDevice_BlockUntilVerticalBlank` | unit_19CB20.cpp | vsync wait (movie playback) |
| `D3DDevice_Clear` | src/rw/driver/xbox/xbdevice.c, src/rw/driver/xbox/xbsprite.c | clear targets |
| `D3DDevice_CopyRects` | src/rw/driver/xbox/xbsprite.c | surface copy |
| `D3DDevice_CreatePixelShader` | src/rw/plugin/matfx/xbox/effectPipesXbox.c | pixel shader |
| `D3DDevice_CreateSurface2` | src/rw/driver/xbox/xbraster.c | raster creation |
| `D3DDevice_CreateTexture2` | src/rw/driver/xbox/xbraster.c | raster creation |
| `D3DDevice_CreateVertexShader` | unit_19E500.cpp, src/rw/driver/xbox/xb2drend.c, src/rw/plugin/dmorph/xbox/dmorphpipeg.c, src/rw/plugin/matfx/xbox/effectPipesXbox.c, src/rw/plugin/skin2/xbox/skinxboxformat.c, src/rw/world/pipe/p2/xbox/xbvtxfmt.c | vertex shader |
| `D3DDevice_DeletePixelShader` | src/rw/plugin/matfx/xbox/effectPipesXbox.c, src/rw/world/pipe/p2/xbox/xbpixelshader.c | pixel shader |
| `D3DDevice_DeleteVertexShader` | unit_122FB0.cpp, unit_19E500.cpp, src/rw/driver/xbox/xb2drend.c, src/rw/plugin/matfx/xbox/effectPipesXbox.c, src/rw/plugin/skin2/xbox/skinxboxformat.c, src/rw/world/pipe/p2/xbox/xbvtxfmt.c | vertex shader |
| `D3DDevice_DrawIndexedVertices` | unit_122FB0.cpp, src/rw/driver/xbox/xb2drend.c, src/rw/driver/xbox/xbcache.c, src/rw/world/pipe/p2/xbox/xbpipe.c | draw |
| `D3DDevice_DrawVertices` | unit_19E500.cpp, src/rw/driver/xbox/xbcache.c | draw |
| `D3DDevice_DrawVerticesUP` | src/rw/driver/xbox/xb2drend.c, src/rw/driver/xbox/xbcache.c | draw from user memory |
| `D3DDevice_EnableOverlay` | unit_19CB20.cpp | YUV overlay (movies) |
| `D3DDevice_GetBackBuffer2` | unit_19B0F0.cpp, unit_19CD50.cpp, unit_2261C0.cpp | render target access |
| `D3DDevice_GetBackBufferScale` | src/rw/driver/xbox/xb2drend.c | back-buffer scaling |
| `D3DDevice_GetDepthStencilSurface2` | src/rw/driver/xbox/xbdevice.c | depth buffer access |
| `D3DDevice_GetRenderTarget2` | src/rw/driver/xbox/xbdevice.c, src/rw/driver/xbox/xbsprite.c | render target access |
| `D3DDevice_GetViewportOffsetAndScale` | src/rw/driver/xbox/xb2drend.c, src/rw/plugin/skin2/xbox/skinplatform.c | viewport transform for vertex shaders |
| `D3DDevice_IsFencePending` | src/rw/driver/xbox/xbmemory.c, src/rw/plugin/dmorph/xbox/dmorphpipeg.c, src/rw/plugin/skin2/xbox/skinxboxinstance.c, src/rw/world/pipe/p2/xbox/nodeXBoxAtomicAllInOne.c, src/rw/world/pipe/p2/xbox/xbvtxfmt.c | GPU fence polling (resource reuse) |
| `D3DDevice_LightEnable` | src/rw/world/pipe/p2/xbox/xblights.c | fixed-function light |
| `D3DDevice_LoadVertexShaderProgram` | src/rw/plugin/skin2/xbox/skinxboxrender.c | load shader microcode |
| `D3DDevice_PersistDisplay` | unit_20AA10.cpp | keep last frame across XLaunchNewImage |
| `D3DDevice_Release` | src/rw/driver/xbox/xbdevice.c | device teardown |
| `D3DDevice_SelectVertexShader` | src/rw/plugin/skin2/xbox/skinxboxrender.c | select loaded shader slot |
| `D3DDevice_SetGammaRamp` | unit_19CD50.cpp | gamma |
| `D3DDevice_SetLight` | src/rw/world/pipe/p2/xbox/xblights.c | fixed-function light |
| `D3DDevice_SetMaterial` | src/rw/driver/xbox/xbdevice.c, src/rw/world/pipe/p2/xbox/xbpipe.c | fixed-function material |
| `D3DDevice_SetPalette` | src/rw/driver/xbox/xbraster.c, src/rw/driver/xbox/xbrendst.c | paletted textures |
| `D3DDevice_SetPixelShader` | src/rw/driver/xbox/xbdevice.c, src/rw/driver/xbox/xbrendst.c | pixel shader |
| `D3DDevice_SetPixelShaderConstant` | src/rw/plugin/matfx/xbox/effectPipesXbox.c | pixel shader constants |
| `D3DDevice_SetRenderTarget` | src/rw/driver/xbox/xbcache.c | render-to-texture |
| `D3DDevice_SetShaderConstantMode` | src/rw/plugin/skin2/xbox/skinxboxconstantmode.c | 192-constant mode |
| `D3DDevice_SetSoftDisplayFilter` | unit_19CD50.cpp | flicker filter |
| `D3DDevice_SetStreamSource` | unit_122FB0.cpp, unit_19E500.cpp, src/rw/driver/xbox/xbmemory.c, src/rw/plugin/dmorph/xbox/dmorphpipeg.c, src/rw/plugin/matfx/xbox/effectPipesXbox.c, src/rw/plugin/skin2/xbox/skinplatform.c, src/rw/world/pipe/p2/xbox/xbpipe.c | bind vertex buffer |
| `D3DDevice_SetTexture` | unit_19B0F0.cpp, src/rw/driver/xbox/xbcache.c | bind texture |
| `D3DDevice_SetTransform` | src/rw/driver/xbox/xbdevice.c, src/rw/plugin/dmorph/xbox/dmorphpipeg.c, src/rw/plugin/matfx/xbox/effectPipesXbox.c, src/rw/plugin/ptank/xbox/ptankxbox.c, src/rw/plugin/ptank/xbox/ptankxboxopt.c, src/rw/src/pipe/p2/xbox/nodeXboxSubmitNoLight.c, src/rw/world/pipe/p2/xbox/nodeXBoxAtomicAllInOne.c, src/rw/world/pipe/p2/xbox/nodeXBoxWorldSectorAllInOne.c | fixed-function matrices |
| `D3DDevice_SetVertexDataColor` | unit_225220.cpp | immediate-mode vertex colour |
| `D3DDevice_SetVertexShader` | unit_19B0F0.cpp, src/rw/driver/xbox/xbdevice.c, src/rw/driver/xbox/xbrendst.c, src/rw/plugin/skin2/xbox/skinplatform.c | vertex shader / FVF |
| `D3DDevice_SetViewport` | src/rw/driver/xbox/xbdevice.c, src/rw/driver/xbox/xbsprite.c | viewport |
| `D3DDevice_Swap` | src/rw/driver/xbox/xbdevice.c | present/flip |
| `D3DPalette_Lock2` | src/rw/driver/xbox/xbraster.c | palette lock |
| `D3DResource_BlockUntilNotBusy` | src/rw/driver/xbox/xbcache.c, src/rw/driver/xbox/xbmemory.c, src/rw/driver/xbox/xbraster.c | wait for GPU before touching resource |
| `D3DResource_Release` | unit_19B0F0.cpp, unit_19CD50.cpp, src/rw/driver/xbox/xbcache.c, src/rw/driver/xbox/xbdevice.c, src/rw/driver/xbox/xbmemory.c, src/rw/driver/xbox/xbraster.c, src/rw/driver/xbox/xbsprite.c | release texture/buffer |
| `D3DSurface_LockRect` | unit_19CD50.cpp, src/rw/driver/xbox/xbraster.c | surface lock |
| `D3DTexture_GetLevelDesc` | unit_228D70.cpp | mip level info |
| `D3DTexture_GetSurfaceLevel2` | src/rw/driver/xbox/xbdevice.c, src/rw/driver/xbox/xbsprite.c | mip surface |
| `D3DTexture_LockRect` | src/rw/driver/xbox/xbraster.c | texture lock |
| `D3DVertexBuffer_Lock2` | unit_122FB0.cpp, unit_19E500.cpp, src/rw/driver/xbox/xbmemory.c, src/rw/plugin/dmorph/xbox/dmorphpipeg.c, src/rw/plugin/matfx/xbox/effectPipesXbox.c, src/rw/plugin/skin2/xbox/skinxboxinstance.c, src/rw/world/pipe/p2/xbox/native.c, src/rw/world/pipe/p2/xbox/nodeXBoxAtomicAllInOne.c, +1 | vertex buffer lock |
| `Direct3DCreate8` | src/rw/driver/xbox/xbdevice.c | create the D3D object |
| `Direct3D_CreateDevice` | src/rw/driver/xbox/xbdevice.c | create the device |
| `Direct3D_EnumAdapterModes` | src/rw/driver/xbox/xbdevice.c | enumerate display modes |
| `Direct3D_GetAdapterModeCount` | src/rw/driver/xbox/xbdevice.c | display mode count |
| `Direct3D_SetPushBufferSize` | unit_0D99F0.cpp | push-buffer size before device creation |

### Globals (D3D internals referenced by d3d8.h inline code)

| symbol | users | note |
|---|---|---|
| `D3D__Device *(data)*` | src/rw/plugin/skin2/xbox/skinxboxrender.c | the CDevice object itself (inline pusher access) |
| `D3D__DirtyFlags *(data)*` | unit_125490.cpp, unit_19E500.cpp, src/rw/driver/xbox/xb2drend.c, src/rw/driver/xbox/xbdevice.c, src/rw/driver/xbox/xbsprite.c, src/rw/plugin/dmorph/xbox/dmorphpipeg.c, src/rw/src/pipe/p2/xbox/nodeXboxSubmitNoLight.c, src/rw/world/pipe/p2/xbox/nodeXBoxAtomicAllInOne.c, +3 | lazy-state dirty bits set by the inline setters |
| `D3D__RenderState *(data)*` | unit_125490.cpp, unit_19E500.cpp, src/rw/driver/xbox/xbcache.c, src/rw/driver/xbox/xbdevice.c, src/rw/driver/xbox/xbrendst.c, src/rw/plugin/dmorph/xbox/dmorphpipeg.c, src/rw/src/pipe/p2/xbox/nodeXboxSubmitNoLight.c, src/rw/world/pipe/p2/xbox/nodeXBoxAtomicAllInOne.c, +3 | render-state shadow array read/written by the inline SetRenderState/GetRenderState |
| `D3D__TextureState *(data)*` | unit_19E500.cpp, src/rw/driver/xbox/xb2drend.c, src/rw/driver/xbox/xbcache.c, src/rw/driver/xbox/xbdevice.c, src/rw/driver/xbox/xbsprite.c, src/rw/src/pipe/p2/xbox/nodeXboxSubmitNoLight.c, src/rw/world/pipe/p2/xbox/xbpipe.c | texture-stage-state shadow array (inline SetTextureStageState) |
| `D3D__pDevice *(data)*` | unit_19B0F0.cpp, unit_19CD50.cpp | g_pDevice: the CDevice pointer (push-buffer put/threshold via inline code) |

### Inline-expanded push-buffer / state helpers

Out-of-line pieces that d3d8.h's inline wrappers call. The 30 `SetRenderState_*` and 4 `SetTextureState_*` functions all appear in the same 9 / 6 files because the inline `D3DDevice_SetRenderState` / `SetTextureStageState` switch names every complex-state handler whenever the state index is not a compile-time constant; a port only needs the states actually set.

| symbol | users | note |
|---|---|---|
| `D3DDevice_BeginPush` | src/rw/driver/xbox/xbdevice.c, src/rw/driver/xbox/xbsprite.c, src/rw/src/pipe/p2/xbox/nodeXboxSubmitNoLight.c | raw push-buffer write (game/RW writes NV2A methods itself) |
| `D3DDevice_BeginStateBig` | src/rw/plugin/skin2/xbox/skinxboxrender.c | large raw state block (skinning constants) |
| `D3DDevice_EndPush` | src/rw/driver/xbox/xbdevice.c, src/rw/driver/xbox/xbsprite.c, src/rw/src/pipe/p2/xbox/nodeXboxSubmitNoLight.c | raw push-buffer write |
| `D3DDevice_MakeSpace` | src/rw/plugin/skin2/xbox/skinxboxrender.c | push-buffer overflow path of the inline pusher |
| `D3DDevice_SetRenderStateNotInline` | src/rw/driver/xbox/xbcache.c | out-of-line SetRenderState (non-constant state index) |
| `D3DDevice_SetRenderState_Simple` | unit_125490.cpp, unit_19E500.cpp, src/rw/driver/xbox/xbdevice.c, src/rw/plugin/dmorph/xbox/dmorphpipeg.c, src/rw/src/pipe/p2/xbox/nodeXboxSubmitNoLight.c, src/rw/world/pipe/p2/xbox/nodeXBoxAtomicAllInOne.c, src/rw/world/pipe/p2/xbox/nodeXBoxWorldSectorAllInOne.c, src/rw/world/pipe/p2/xbox/xblights.c, +1 | inline D3DDevice_SetRenderState for "simple" states (method/value pair into push buffer) |
| `D3DDevice_SetTextureStageStateNotInline` | src/rw/driver/xbox/xbcache.c | out-of-line SetTextureStageState (non-constant) |
| `D3DDevice_SetVertexShaderConstant1` | unit_122FB0.cpp | inline SetVertexShaderConstant (1 register) |
| `D3DDevice_SetVertexShaderConstant1Fast` | unit_19E500.cpp, src/rw/driver/xbox/xb2drend.c, src/rw/plugin/skin2/xbox/skinplatform.c | inline SetVertexShaderConstantFast (1 register) |
| `D3DDevice_SetVertexShaderConstant4` | unit_122FB0.cpp | inline SetVertexShaderConstant (4 registers) |
| `D3DDevice_SetVertexShaderConstantNotInline` | unit_122FB0.cpp | out-of-line SetVertexShaderConstant |
| `D3DDevice_SetVertexShaderConstantNotInlineFast` | unit_19E500.cpp, src/rw/driver/xbox/xb2drend.c, src/rw/plugin/skin2/xbox/skinplatform.c | out-of-line SetVertexShaderConstantFast |

| symbol group | users | note |
|---|---|---|
| `D3DDevice_SetRenderState_{BackFillMode,CullMode,DoNotCullUncompressed,Dxt1NoiseEnable,EdgeAntiAlias,FillMode,FogColor,FrontFace,LineWidth,LogicOp,MultiSampleAntiAlias,MultiSampleMask,MultiSampleMode,MultiSampleRenderTargetMode,NormalizeNormals,OcclusionCullEnable,PSTextureModes,RopZCmpAlwaysRead,RopZRead,SampleAlpha,ShadowFunc,StencilCullEnable,StencilEnable,StencilFail,TextureFactor,TwoSidedLighting,VertexBlend,YuvEnable,ZBias,ZEnable}` (30) | unit_125490.cpp, unit_19E500.cpp, src/rw/driver/xbox/xbdevice.c, src/rw/plugin/dmorph/xbox/dmorphpipeg.c, src/rw/src/pipe/p2/xbox/nodeXboxSubmitNoLight.c, src/rw/world/pipe/p2/xbox/nodeXBoxAtomicAllInOne.c, src/rw/world/pipe/p2/xbox/nodeXBoxWorldSectorAllInOne.c, src/rw/world/pipe/p2/xbox/xblights.c, src/rw/world/pipe/p2/xbox/xbpipe.c | complex render-state handlers from the inline switch |
| `D3DDevice_SetTextureState_{BorderColor,BumpEnv,ColorKeyColor,TexCoordIndex}` (4) | unit_19E500.cpp, src/rw/driver/xbox/xb2drend.c, src/rw/driver/xbox/xbdevice.c, src/rw/driver/xbox/xbsprite.c, src/rw/src/pipe/p2/xbox/nodeXboxSubmitNoLight.c, src/rw/world/pipe/p2/xbox/xbpipe.c | complex texture-state handlers from the inline switch |

## xapilib (52 symbols, 27 files)

| symbol | users | note |
|---|---|---|
| `CloseHandle` | unit_19CD50.cpp, unit_19E500.cpp, unit_1A16D0.cpp, src/rw/tool/fsyst/xbox/rtfsxxbx.c, src/rwa/unit_23FAD0.c, src/rwa/unit_2449C0.c, src/rwa/unit_247430.c, src/rwa/unit_24D4C0.c, +1 | handles |
| `CopyFileA` | unit_1A16D0.cpp | file copy |
| `CreateEventA` | src/rw/tool/fsyst/xbox/rtfsxxbx.c | sync |
| `CreateFileA` | unit_19CD50.cpp, unit_19E500.cpp, unit_1A16D0.cpp, src/rw/tool/fsyst/xbox/rtfsxxbx.c | file I/O |
| `CreateSemaphoreA` | src/rwa/unit_2416D0.c | sync |
| `CreateThread` | unit_0811C0.cpp, unit_1B18E0.cpp, src/rwa/unit_2416D0.c | threads |
| `ExitThread` | unit_0811C0.cpp, unit_1B18E0.cpp | threads |
| `GetFileAttributesA` | src/rw/tool/fsyst/xbox/rtfsxxbx.c | file exists |
| `GetFileSize` | unit_19CD50.cpp, unit_19E500.cpp, unit_1A16D0.cpp, src/rw/tool/fsyst/xbox/rtfsxxbx.c | file I/O |
| `GetLastError` | unit_1A16D0.cpp, src/rw/tool/fsyst/xbox/rtfsxxbx.c | errors |
| `GetOverlappedResult` | src/rw/tool/fsyst/xbox/rtfsxxbx.c | async file I/O |
| `GetTickCount` | unit_1DC6C0.cpp, src/rws/framework/toolkits/time/gftime.cpp | time |
| `OutputDebugStringA` | unit_1C8A30.cpp, unit_1D5D30.cpp | debug output |
| `QueryPerformanceCounter` | unit_19B0F0.cpp, unit_1CBC80.cpp | timer |
| `QueryPerformanceFrequency` | unit_19B0F0.cpp, unit_1CBC80.cpp | timer |
| `ReadFile` | unit_19CD50.cpp, unit_19E500.cpp, unit_1A16D0.cpp, src/rw/tool/fsyst/xbox/rtfsxxbx.c | file I/O |
| `ReleaseSemaphore` | src/rwa/unit_23FAD0.c, src/rwa/unit_2416D0.c, src/rwa/unit_2449C0.c, src/rwa/unit_247430.c, src/rwa/unit_24D4C0.c, src/rwa/xbox/unit_250B20.c | sync |
| `ResumeThread` | unit_0811C0.cpp, unit_125490.cpp, unit_1B18E0.cpp | threads |
| `SetFilePointer` | src/rw/tool/fsyst/xbox/rtfsxxbx.c | file I/O |
| `SetThreadPriority` | unit_0811C0.cpp, unit_1B18E0.cpp, src/rwa/unit_2416D0.c | threads |
| `Sleep` | unit_19D920.cpp, unit_1A16D0.cpp, unit_1B18E0.cpp, unit_2261C0.cpp, src/rwa/unit_23FAD0.c, src/rwa/unit_2416D0.c, src/rwa/xbox/unit_24EC60.c, src/rwa/xbox/unit_250B20.c | sync |
| `SuspendThread` | unit_125490.cpp | threads |
| `WaitForSingleObject` | src/rwa/unit_23FAD0.c, src/rwa/unit_2416D0.c, src/rwa/unit_2449C0.c, src/rwa/unit_247430.c, src/rwa/unit_24D4C0.c, src/rwa/xbox/unit_250B20.c | sync |
| `WideCharToMultiByte` | src/rwa/xbox/unit_250B20.c | string conversion |
| `WriteFile` | unit_1A16D0.cpp, src/rw/tool/fsyst/xbox/rtfsxxbx.c | file I/O |
| `XCalculateSignatureBegin` | unit_1A16D0.cpp | save signing |
| `XCalculateSignatureEnd` | unit_1A16D0.cpp | save signing |
| `XCalculateSignatureUpdate` | unit_1A16D0.cpp | save signing |
| `XCreateSaveGame` | unit_1A16D0.cpp | saves |
| `XDEVICE_TYPE_GAMEPAD_TABLE *(data)*` | unit_19D920.cpp | data behind XDEVICE_TYPE_GAMEPAD macro |
| `XDeleteSaveGame` | unit_1A16D0.cpp | saves |
| `XFindClose` | unit_1A16D0.cpp | saves |
| `XFindFirstSaveGame` | unit_1A16D0.cpp | saves |
| `XFindNextSaveGame` | unit_1A16D0.cpp | saves |
| `XGetAudioFlags` | unit_19CD50.cpp, src/rwa/xbox/unit_24DF20.c | Dolby/stereo settings |
| `XGetDeviceChanges` | unit_19D920.cpp | hot-plug |
| `XGetDevices` | unit_19D920.cpp, unit_1C6AC0.cpp | controller/MU presence |
| `XGetDiskSectorSizeA` | src/rw/tool/fsyst/xbox/rtfsxxbx.c | sector size for unbuffered I/O |
| `XGetLaunchInfo` | unit_19CD50.cpp | launch data (dashboard/cross-title) |
| `XGetVideoFlags` | unit_19CD50.cpp | widescreen/480p/720p |
| `XGetVideoStandard` | unit_19CD50.cpp | NTSC/PAL |
| `XInitDevices` | unit_19CD50.cpp | peripheral init |
| `XInputClose` | unit_19D920.cpp | controller |
| `XInputGetCapabilities` | unit_19D920.cpp | controller caps |
| `XInputGetState` | unit_19D920.cpp | controller read |
| `XInputOpen` | unit_19D920.cpp | controller |
| `XInputSetState` | unit_19D920.cpp | rumble |
| `XLaunchNewImageA` | unit_18AF40.cpp, unit_20AA10.cpp | reboot to dashboard / relaunch |
| `XPhysicalAlloc` | src/rw/driver/xbox/xbmemory.c | contiguous GPU memory |
| `XPhysicalFree` | src/rw/driver/xbox/xbmemory.c | contiguous GPU memory |
| `lstrcatA` | unit_1A16D0.cpp | strings |
| `lstrcpynA` | unit_1A16D0.cpp | strings |

## dsound (41 symbols, 5 files)

| symbol | users | note |
|---|---|---|
| `DirectSoundCreate` | src/rwa/xbox/unit_24DF20.c | create DirectSound |
| `DirectSoundDoWork` | src/rwa/xbox/unit_24DF20.c | per-frame DSound pump |
| `DirectSoundUseFullHRTF` | src/rwa/xbox/unit_24DF20.c | 3D HRTF tables |
| `IDirectSoundBuffer_GetCurrentPosition` | src/rwa/xbox/unit_24EC60.c | voice control |
| `IDirectSoundBuffer_GetStatus` | src/rwa/xbox/unit_24EC60.c | voice control |
| `IDirectSoundBuffer_Play` | src/rwa/xbox/unit_24EC60.c | voice control |
| `IDirectSoundBuffer_Release` | src/rwa/xbox/unit_24EC60.c | voice control |
| `IDirectSoundBuffer_SetAllParameters` | src/rwa/xbox/unit_24EC60.c | 3D voice parameters |
| `IDirectSoundBuffer_SetBufferData` | src/rwa/xbox/unit_24EC60.c | voice control |
| `IDirectSoundBuffer_SetCurrentPosition` | src/rwa/xbox/unit_24EC60.c | voice control |
| `IDirectSoundBuffer_SetFormat` | src/rwa/xbox/unit_24EC60.c | voice control |
| `IDirectSoundBuffer_SetFrequency` | src/rwa/xbox/unit_24EC60.c | voice control |
| `IDirectSoundBuffer_SetHeadroom` | src/rwa/xbox/unit_24EC60.c | voice control |
| `IDirectSoundBuffer_SetI3DL2Source` | src/rwa/xbox/unit_24EC60.c | per-voice reverb |
| `IDirectSoundBuffer_SetLoopRegion` | src/rwa/xbox/unit_24EC60.c | voice control |
| `IDirectSoundBuffer_SetMixBinVolumes` | src/rwa/xbox/unit_24EC60.c | speaker routing |
| `IDirectSoundBuffer_SetMixBins` | src/rwa/xbox/unit_24EC60.c | speaker routing |
| `IDirectSoundBuffer_SetOutputBuffer` | src/rwa/xbox/unit_24EC60.c | route voice into submix buffer |
| `IDirectSoundBuffer_SetPlayRegion` | src/rwa/xbox/unit_24EC60.c | voice control |
| `IDirectSoundBuffer_SetRolloffCurve` | src/rwa/xbox/unit_24EC60.c | 3D attenuation curve |
| `IDirectSoundBuffer_SetVolume` | src/rwa/xbox/unit_24EC60.c | voice control |
| `IDirectSoundBuffer_StopEx` | src/rwa/xbox/unit_24EC60.c | voice control |
| `IDirectSound_CommitDeferredSettings` | src/rwa/xbox/unit_24DF20.c | DirectSound object |
| `IDirectSound_CommitEffectData` | src/rwa/xbox/unit_24DF20.c | DSP effect parameters |
| `IDirectSound_CreateSoundBuffer` | src/rwa/xbox/unit_24EC60.c | DirectSound object |
| `IDirectSound_DownloadEffectsImage` | src/rwa/xbox/unit_24DF20.c | load DSP effects image (dsstdfx) |
| `IDirectSound_EnableHeadphones` | src/rwa/xbox/unit_24DF20.c | headphone mode |
| `IDirectSound_GetEffectData` | src/rwa/xbox/unit_24DF20.c | DSP effect parameters |
| `IDirectSound_GetOutputLevels` | src/rwa/xbox/unit_24DF20.c | output metering |
| `IDirectSound_GetSpeakerConfig` | src/rwa/xbox/unit_24DF20.c | stereo/surround config |
| `IDirectSound_Release` | src/rwa/xbox/unit_24DF20.c | DirectSound object |
| `IDirectSound_SetDistanceFactor` | src/rwa/xbox/unit_24DF20.c | 3D listener / global |
| `IDirectSound_SetDopplerFactor` | src/rwa/xbox/unit_24DF20.c | 3D listener / global |
| `IDirectSound_SetEffectData` | unit_1C6AC0.cpp, src/rwa/xbox/unit_24DF20.c | DSP effect parameters |
| `IDirectSound_SetI3DL2Listener` | src/rwa/xbox/unit_24DF20.c | reverb |
| `IDirectSound_SetMixBinHeadroom` | unit_0824A0.cpp | mixbin headroom |
| `IDirectSound_SetOrientation` | src/rwa/xbox/unit_24DF20.c | 3D listener / global |
| `IDirectSound_SetPosition` | src/rwa/xbox/unit_24DF20.c | 3D listener / global |
| `IDirectSound_SetRolloffFactor` | src/rwa/xbox/unit_24DF20.c | 3D listener / global |
| `IDirectSound_SetVelocity` | src/rwa/xbox/unit_24DF20.c | 3D listener / global |
| `WmaCreateDecoderEx` | src/rwa/xbox/unit_250B20.c | WMA decoder (streamed music) |

## xonline (41 symbols, 9 files)

| symbol | users | note |
|---|---|---|
| `WSAGetLastError` | unit_1DBF50.cpp | Winsock (XNet) |
| `XNetCreateKey` | unit_1D8370.cpp | system-link/host session key |
| `XNetGetEthernetLinkStatus` | unit_1D5190.cpp | cable check |
| `XNetGetTitleXnAddr` | unit_1D8370.cpp | own XNADDR |
| `XNetInAddrToXnAddr` | unit_1D8370.cpp | peer address resolution |
| `XNetQosListen` | unit_1DC6C0.cpp | QoS probe responder (host) |
| `XNetQosLookup` | unit_1DC6C0.cpp | QoS probes (client) |
| `XNetQosRelease` | unit_1DC6C0.cpp | QoS probes |
| `XNetRandom` | unit_1D7CE0.cpp, unit_1D8370.cpp | random bytes/nonces |
| `XNetRegisterKey` | unit_1D8370.cpp, unit_1DC6C0.cpp | session key |
| `XNetUnregisterKey` | unit_1D8370.cpp, unit_1DC6C0.cpp | session key |
| `XNetXnAddrToInAddr` | unit_1D8370.cpp | peer address resolution |
| `XOnlineFriendsGetAcceptedGameInvite` | unit_2261C0.cpp | invite join |
| `XOnlineGetLogonUsers` | unit_19BF20.cpp, unit_1D8370.cpp, unit_2049D0.cpp, unit_2261C0.cpp | signed-in users |
| `XOnlineLogonTaskGetResults` | unit_1D8370.cpp | logon |
| `XOnlineMatchSearch` | unit_1DC6C0.cpp | matchmaking (optimatch) |
| `XOnlineMatchSearchGetResults` | unit_1DC6C0.cpp, unit_2261C0.cpp | matchmaking |
| `XOnlineMatchSearchParse` | unit_1DC6C0.cpp | matchmaking |
| `XOnlineMatchSearchResultsLen` | unit_1DC6C0.cpp | matchmaking |
| `XOnlineMatchSessionCreate` | unit_1DC6C0.cpp | host advertise session |
| `XOnlineMatchSessionDelete` | unit_1DC6C0.cpp | host advertise session |
| `XOnlineMatchSessionFindFromID` | unit_2261C0.cpp | join by session id |
| `XOnlineMatchSessionGetInfo` | unit_1DC6C0.cpp | session info |
| `XOnlineMatchSessionUpdate` | unit_1DC6C0.cpp | host advertise session |
| `XOnlineMutelistGet` | unit_2261C0.cpp | voice mute list |
| `XOnlineMutelistStartup` | unit_2261C0.cpp | voice mute list |
| `XOnlineRetrieveLogonState` | unit_2261C0.cpp | logon persisted across reboot |
| `XOnlineSaveLogonState` | unit_20AA10.cpp | logon persisted across reboot |
| `XOnlineStartup` | unit_1D8370.cpp | Live startup |
| `XOnlineTaskClose` | unit_1DC6C0.cpp, unit_2261C0.cpp | close Live task |
| `XOnlineTaskContinue` | unit_1D8370.cpp, unit_1DC6C0.cpp, unit_2261C0.cpp | pump async Live task |
| `bind` | unit_1DBF50.cpp | Winsock (XNet) |
| `closesocket` | unit_1DBF50.cpp | Winsock (XNet) |
| `htons` | unit_1D8370.cpp, unit_1DBF50.cpp | Winsock (XNet) |
| `ioctlsocket` | unit_1DBF50.cpp | Winsock (XNet) |
| `recv` | unit_1DBF50.cpp | Winsock (XNet) |
| `recvfrom` | unit_1DBF50.cpp | Winsock (XNet) |
| `select` | unit_1DBF50.cpp | Winsock (XNet) |
| `sendto` | unit_1DBF50.cpp | Winsock (XNet) |
| `setsockopt` | unit_1DBF50.cpp | Winsock (XNet) |
| `socket` | unit_1DBF50.cpp | Winsock (XNet) |

## uix (26 symbols, 3 files)

| symbol | users | note |
|---|---|---|
| `LiveEngine_ClearInput` | unit_2261C0.cpp | Live UI engine |
| `LiveEngine_DoWork` | unit_2261C0.cpp | pump Live UI |
| `LiveEngine_EnableFeature` | unit_2261C0.cpp | Live UI engine |
| `LiveEngine_EndFeature` | unit_19BF20.cpp, unit_2261C0.cpp | Live UI engine |
| `LiveEngine_GetExitInfo` | unit_2261C0.cpp | Live UI engine |
| `LiveEngine_GetFeatureInterface` | unit_2261C0.cpp | Live UI engine |
| `LiveEngine_GetNotifications` | unit_2261C0.cpp | Live UI engine |
| `LiveEngine_LogOff` | unit_2261C0.cpp | Live UI engine |
| `LiveEngine_NotificationSetState` | unit_19BF20.cpp, unit_2261C0.cpp | Live UI engine |
| `LiveEngine_Reboot` | unit_2261C0.cpp | Live UI engine |
| `LiveEngine_Render` | unit_2261C0.cpp | draw Live UI |
| `LiveEngine_SetAudioPlugin` | unit_2261C0.cpp | UI sound callbacks |
| `LiveEngine_SetInput` | unit_2261C0.cpp | Live UI engine |
| `LiveEngine_SetProperty` | unit_2261C0.cpp | Live UI engine |
| `LiveEngine_SetUIPlugin` | unit_2261C0.cpp | game-skinned UI callbacks |
| `LiveEngine_StartFeature` | unit_19BF20.cpp, unit_2261C0.cpp | open a Live UI feature (friends, logon...) |
| `LiveEngine_UseVoiceMail` | unit_2261C0.cpp | Live UI engine |
| `PluginSupport_GetImage` | unit_228D70.cpp | UI plugin helpers |
| `PluginSupport_GetLayout` | unit_228D70.cpp | UI plugin helpers |
| `PluginSupport_GetScreenImage` | unit_228D70.cpp | UI plugin helpers |
| `PluginSupport_GetWordLength` | unit_228D70.cpp | UI plugin text wrap |
| `UIXCreateLiveEngine` | unit_2261C0.cpp | create Xbox Live UI engine (UIX) |
| `_uix_friends_feature *(data)*` | unit_19BF20.cpp, unit_2261C0.cpp | feature descriptor |
| `_uix_logon_feature *(data)*` | unit_19BF20.cpp, unit_2261C0.cpp | feature descriptor |
| `_uix_players_feature *(data)*` | unit_2261C0.cpp | feature descriptor |
| `_uix_voice_mail *(data)*` | unit_2261C0.cpp | feature descriptor |

## xvoice (18 symbols, 1 files)

| symbol | users | note |
|---|---|---|
| `XDEVICE_TYPE_VOICE_HEADPHONE_TABLE *(data)*` | unit_1C6AC0.cpp | headset device type data |
| `XDEVICE_TYPE_VOICE_MICROPHONE_TABLE *(data)*` | unit_1C6AC0.cpp | headset device type data |
| `XHVEngineCreate` | unit_1C6AC0.cpp | voice chat engine |
| `XHVEngine_DoWork` | unit_1C6AC0.cpp | voice engine |
| `XHVEngine_EnableProcessingMode` | unit_1C6AC0.cpp | voice engine |
| `XHVEngine_IsTalking` | unit_1C6AC0.cpp | talking indicator |
| `XHVEngine_RegisterLocalTalker` | unit_1C6AC0.cpp | talkers |
| `XHVEngine_RegisterRemoteTalker` | unit_1C6AC0.cpp | talkers |
| `XHVEngine_Release` | unit_1C6AC0.cpp | voice engine |
| `XHVEngine_SetCallbackInterface` | unit_1C6AC0.cpp | voice engine |
| `XHVEngine_SetPlaybackPriority` | unit_1C6AC0.cpp | mute/priority |
| `XHVEngine_SetProcessingMode` | unit_1C6AC0.cpp | voice engine |
| `XHVEngine_SubmitIncomingVoicePacket` | unit_1C6AC0.cpp | network voice in |
| `XHVEngine_UnregisterLocalTalker` | unit_1C6AC0.cpp | talkers |
| `XHVEngine_UnregisterRemoteTalker` | unit_1C6AC0.cpp | talkers |
| `_xhv_loopback_mode *(data)*` | unit_1C6AC0.cpp | processing-mode descriptor |
| `_xhv_voicechat_mode *(data)*` | unit_1C6AC0.cpp | processing-mode descriptor |
| `_xhv_voicemail_mode *(data)*` | unit_1C6AC0.cpp | processing-mode descriptor |

## xgraphics (17 symbols, 6 files)

| symbol | users | note |
|---|---|---|
| `XFONT_GetTextExtent` | unit_19BF20.cpp | debug/system font |
| `XFONT_GetTextHeight` | unit_19BF20.cpp | debug/system font |
| `XFONT_OpenDefaultFont` | unit_19CD50.cpp | debug/system font |
| `XFONT_Release` | unit_19BF20.cpp | debug/system font |
| `XFONT_SetTextColor` | unit_19BF20.cpp | debug/system font |
| `XFONT_SetTextHeight` | unit_19BF20.cpp | debug/system font |
| `XFONT_TextOut` | unit_19BF20.cpp | debug/system font |
| `XGAssembleShader` | src/rw/plugin/skin2/xbox/skinxboxrender.c | runtime shader assembly |
| `XGBuffer_GetBufferPointer` | src/rw/plugin/skin2/xbox/skinxboxrender.c | assembler output |
| `XGBuffer_Release` | src/rw/plugin/skin2/xbox/skinxboxrender.c | assembler output |
| `XGMatrixMultiply` | unit_122FB0.cpp, unit_19E500.cpp | math |
| `XGMatrixTranspose` | unit_122FB0.cpp, unit_19E500.cpp | shader constant upload |
| `XGSetPaletteHeader` | src/rw/driver/xbox/xbraster.c | build palette header in place |
| `XGSetTextureHeader` | src/rw/driver/xbox/xbraster.c | build texture header in place |
| `XGSpliceVertexShaders` | src/rw/plugin/skin2/xbox/skinxboxrender.c | combine shader fragments |
| `XGSwizzleRect` | src/rw/driver/xbox/xbraster.c | texture swizzle |
| `XGUnswizzleRect` | src/rw/driver/xbox/xbraster.c | texture unswizzle |

## binkxbox (11 symbols, 2 files)

| symbol | users | note |
|---|---|---|
| `BinkClose` | unit_19CB20.cpp | close movie |
| `BinkCopyToBuffer` | unit_19CD50.cpp | blit frame to texture |
| `BinkDoFrame` | unit_19CD50.cpp | decode frame |
| `BinkGetError` | unit_19CD50.cpp | error text |
| `BinkGetTrackID` | unit_19CB20.cpp | audio track |
| `BinkNextFrame` | unit_19CD50.cpp | advance |
| `BinkOpen` | unit_19CB20.cpp | open movie |
| `BinkPause` | unit_19CD50.cpp | pause |
| `BinkSetSoundTrack` | unit_19CB20.cpp | audio track select |
| `BinkSetVolume` | unit_19CB20.cpp, unit_19CD50.cpp | volume |
| `BinkWait` | unit_19CD50.cpp | frame pacing |

## xboxkrnl (3 symbols, 9 files)

| symbol | users | note |
|---|---|---|
| `RtlEnterCriticalSection *(import thunk __imp_)*` | unit_06B3B0.cpp, unit_0811C0.cpp, unit_16E9C0.cpp, unit_16F2C0.cpp, unit_171DC0.cpp, unit_18F3C0.cpp, src/rw/src/batextur.c, src/rw/tool/fsyst/rtfsmgr.c, +1 | critical sections (via __imp_) |
| `RtlInitializeCriticalSection *(import thunk __imp_)*` | unit_0811C0.cpp, src/rw/tool/fsyst/rtfsmgr.c, src/rws/framework/core/memoryhandler/memoryhandler.cpp | critical sections (via __imp_) |
| `RtlLeaveCriticalSection *(import thunk __imp_)*` | unit_06B3B0.cpp, unit_0811C0.cpp, unit_16E9C0.cpp, unit_16F2C0.cpp, unit_171DC0.cpp, unit_18F3C0.cpp, src/rw/src/batextur.c, src/rw/tool/fsyst/rtfsmgr.c, +1 | critical sections (via __imp_) |

## d3dx8 (3 symbols, 3 files)

| symbol | users | note |
|---|---|---|
| `D3DXMatrixLookAtRH` | unit_122FB0.cpp, unit_19E500.cpp | camera matrix |
| `D3DXMatrixMultiply` | src/rw/plugin/skin2/xbox/skinxboxrender.c | matrix multiply |
| `D3DXMatrixPerspectiveFovRH` | unit_122FB0.cpp, unit_19E500.cpp | projection matrix |

## libcpmt (2 symbols, 132 files)

| symbol | users | note |
|---|---|---|
| `public: void __thiscall std::_String_base::_Xlen(void)const ` | unit_042F40.cpp, unit_09DD80.cpp, unit_09F130.cpp, unit_0A02D0.cpp, unit_0A0A50.cpp, unit_0A11E0.cpp, unit_0A1690.cpp, unit_0A1CA0.cpp, +124 | std::string length_error throw (inline basic_string code) |
| `public: void __thiscall std::_String_base::_Xran(void)const ` | unit_042F40.cpp, unit_09DD80.cpp, unit_09F130.cpp, unit_0A02D0.cpp, unit_0A0A50.cpp, unit_0A11E0.cpp, unit_0A1690.cpp, unit_0A1CA0.cpp, +124 | std::string out_of_range throw (inline basic_string code) |

## libcmt (count only)

86 distinct symbols used by 499 source files. Most used:

`_fltused` (341), `__CxxFrameHandler` (272), `_except_list` (272), `memcpy` (196), `atexit` (146), `strlen` (140), `memmove` (136), `_CxxThrowException` (132), `__security_cookie` (127), `__security_check_cookie` (127), `_purecall` (123), `public: __thiscall exception::exception(class exception const &)` (104), `const type_info::`vftable'` (104), `public: virtual __thiscall exception::~exception(void)` (104), `public: __thiscall exception::exception(void)` (104).

## Excluded

- Stale objects in link.rsp whose sources no longer exist (from an earlier `--define` run): research/trigdraw, research/trigweb. Research-only symbols they pulled (XNetStartup, WSAStartup, accept/listen/send/shutdown, GlobalMemoryStatus, _InterlockedExchange) are not counted.
- Unresolved-to-a-library references that our own objects satisfy via COMDAT/const folding: `?flt_3CE7F4@@3MB`, `?flt_3CD84C@@3MB`, `?flt_3CD8E0@@3MB`, `?flt_3D7118@@3MB`, `??0type_1A5EA0@@QAE@PBDH@Z`.
