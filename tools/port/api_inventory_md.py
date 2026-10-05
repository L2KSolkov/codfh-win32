"""api_inventory_md.py: docs/WIN32_PORT_API.md from build/port/inv.json (tools/port/api_inventory.py)."""
import json, os, re
from collections import defaultdict, Counter

ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
HERE = os.path.join(ROOT, 'build', 'port')
d = json.load(open(os.path.join(HERE, 'inv.json')))
R = d['result']
stale = sorted(set(u for r in R for u in r['users'] if u.endswith('.?')))
for r in R:
    r['users'] = [u for u in r['users'] if not u.endswith('.?')]
R = [r for r in R if r['users']]
NOBJ = sum(1 for l in open(os.path.join(ROOT, 'build', 'plain', 'link.rsp'))
           if l.strip().endswith('.obj"') and '\\research\\' not in l)

def short(u):
    return u[len('src/recovered/'):] if u.startswith('src/recovered/') else u

def users_str(us, n=8):
    us = sorted(us, key=lambda u: (not u.startswith('src/recovered/'), u))
    s = ', '.join(short(u) for u in us[:n])
    if len(us) > n:
        s += ', +%d' % (len(us) - n)
    return s

NOTES = {
 # d3d8
 'Direct3DCreate8': 'create the D3D object', 'Direct3D_CreateDevice': 'create the device',
 'Direct3D_EnumAdapterModes': 'enumerate display modes', 'Direct3D_GetAdapterModeCount': 'display mode count',
 'Direct3D_SetPushBufferSize': 'push-buffer size before device creation',
 'D3DDevice_BlockUntilVerticalBlank': 'vsync wait (movie playback)', 'D3DDevice_Clear': 'clear targets',
 'D3DDevice_CopyRects': 'surface copy', 'D3DDevice_Swap': 'present/flip', 'D3DDevice_PersistDisplay': 'keep last frame across XLaunchNewImage',
 'D3DDevice_EnableOverlay': 'YUV overlay (movies)', 'D3DDevice_SetGammaRamp': 'gamma', 'D3DDevice_SetSoftDisplayFilter': 'flicker filter',
 'D3DDevice_GetBackBufferScale': 'back-buffer scaling', 'D3DDevice_Release': 'device teardown',
 'D3DDevice_SetVertexDataColor': 'immediate-mode vertex colour', 'D3DDevice_SetLight': 'fixed-function light',
 'D3DDevice_LightEnable': 'fixed-function light', 'D3DDevice_SetMaterial': 'fixed-function material',
 'D3DDevice_SetTransform': 'fixed-function matrices', 'D3DDevice_SetViewport': 'viewport',
 'D3DDevice_GetViewportOffsetAndScale': 'viewport transform for vertex shaders',
 'D3DDevice_IsFencePending': 'GPU fence polling (resource reuse)', 'D3DResource_BlockUntilNotBusy': 'wait for GPU before touching resource',
 'D3DResource_Release': 'release texture/buffer', 'D3DVertexBuffer_Lock2': 'vertex buffer lock',
 'D3DPalette_Lock2': 'palette lock', 'D3DSurface_LockRect': 'surface lock', 'D3DTexture_LockRect': 'texture lock',
 'D3DCubeTexture_LockRect': 'cube texture lock', 'D3DTexture_GetLevelDesc': 'mip level info',
 'D3DTexture_GetSurfaceLevel2': 'mip surface', 'D3DCubeTexture_GetCubeMapSurface2': 'cube face surface',
 'D3DDevice_CreateTexture2': 'raster creation', 'D3DDevice_CreateSurface2': 'raster creation',
 'D3DDevice_GetBackBuffer2': 'render target access', 'D3DDevice_GetRenderTarget2': 'render target access',
 'D3DDevice_GetDepthStencilSurface2': 'depth buffer access', 'D3DDevice_SetRenderTarget': 'render-to-texture',
 'D3DDevice_SetPalette': 'paletted textures', 'D3DDevice_SetTexture': 'bind texture',
 'D3DDevice_SetStreamSource': 'bind vertex buffer', 'D3DDevice_DrawIndexedVertices': 'draw', 'D3DDevice_DrawVertices': 'draw',
 'D3DDevice_DrawVerticesUP': 'draw from user memory', 'D3DDevice_CreateVertexShader': 'vertex shader', 'D3DDevice_DeleteVertexShader': 'vertex shader',
 'D3DDevice_SetVertexShader': 'vertex shader / FVF', 'D3DDevice_SelectVertexShader': 'select loaded shader slot',
 'D3DDevice_LoadVertexShaderProgram': 'load shader microcode', 'D3DDevice_SetShaderConstantMode': '192-constant mode',
 'D3DDevice_CreatePixelShader': 'pixel shader', 'D3DDevice_DeletePixelShader': 'pixel shader', 'D3DDevice_SetPixelShader': 'pixel shader',
 'D3DDevice_SetPixelShaderConstant': 'pixel shader constants',
 # d3dx8
 'D3DXMatrixLookAtRH': 'camera matrix', 'D3DXMatrixMultiply': 'matrix multiply', 'D3DXMatrixPerspectiveFovRH': 'projection matrix',
 # dsound
 'DirectSoundCreate': 'create DirectSound', 'DirectSoundDoWork': 'per-frame DSound pump', 'DirectSoundUseFullHRTF': '3D HRTF tables',
 'WmaCreateDecoderEx': 'WMA decoder (streamed music)', 'IDirectSound_DownloadEffectsImage': 'load DSP effects image (dsstdfx)',
 'IDirectSound_SetEffectData': 'DSP effect parameters', 'IDirectSound_GetEffectData': 'DSP effect parameters',
 'IDirectSound_CommitEffectData': 'DSP effect parameters', 'IDirectSound_SetI3DL2Listener': 'reverb',
 'IDirectSoundBuffer_SetI3DL2Source': 'per-voice reverb', 'IDirectSound_GetSpeakerConfig': 'stereo/surround config',
 'IDirectSound_EnableHeadphones': 'headphone mode', 'IDirectSound_GetOutputLevels': 'output metering',
 'IDirectSoundBuffer_SetOutputBuffer': 'route voice into submix buffer', 'IDirectSoundBuffer_SetMixBins': 'speaker routing',
 'IDirectSoundBuffer_SetMixBinVolumes': 'speaker routing', 'IDirectSound_SetMixBinHeadroom': 'mixbin headroom',
 'IDirectSoundBuffer_SetAllParameters': '3D voice parameters', 'IDirectSoundBuffer_SetRolloffCurve': '3D attenuation curve',
 # uix
 'UIXCreateLiveEngine': 'create Xbox Live UI engine (UIX)', 'LiveEngine_StartFeature': 'open a Live UI feature (friends, logon...)',
 'LiveEngine_Render': 'draw Live UI', 'LiveEngine_DoWork': 'pump Live UI', 'LiveEngine_SetUIPlugin': 'game-skinned UI callbacks',
 'LiveEngine_SetAudioPlugin': 'UI sound callbacks', 'PluginSupport_GetImage': 'UI plugin helpers', 'PluginSupport_GetLayout': 'UI plugin helpers',
 'PluginSupport_GetScreenImage': 'UI plugin helpers', 'PluginSupport_GetWordLength': 'UI plugin text wrap',
 '_uix_friends_feature': 'feature descriptor', '_uix_logon_feature': 'feature descriptor', '_uix_players_feature': 'feature descriptor',
 '_uix_voice_mail': 'feature descriptor',
 # xapilib
 'XCreateSaveGame': 'saves', 'XDeleteSaveGame': 'saves', 'XFindFirstSaveGame': 'saves', 'XFindNextSaveGame': 'saves', 'XFindClose': 'saves',
 'XCalculateSignatureBegin': 'save signing', 'XCalculateSignatureUpdate': 'save signing', 'XCalculateSignatureEnd': 'save signing',
 'XInitDevices': 'peripheral init', 'XGetDevices': 'controller/MU presence', 'XGetDeviceChanges': 'hot-plug',
 'XInputOpen': 'controller', 'XInputClose': 'controller', 'XInputGetState': 'controller read', 'XInputSetState': 'rumble',
 'XInputGetCapabilities': 'controller caps', 'XDEVICE_TYPE_GAMEPAD_TABLE': 'data behind XDEVICE_TYPE_GAMEPAD macro',
 'XGetLaunchInfo': 'launch data (dashboard/cross-title)', 'XLaunchNewImageA': 'reboot to dashboard / relaunch',
 'XGetVideoFlags': 'widescreen/480p/720p', 'XGetVideoStandard': 'NTSC/PAL', 'XGetAudioFlags': 'Dolby/stereo settings',
 'XGetDiskSectorSizeA': 'sector size for unbuffered I/O', 'XPhysicalAlloc': 'contiguous GPU memory', 'XPhysicalFree': 'contiguous GPU memory',
 'CreateThread': 'threads', 'ExitThread': 'threads', 'SetThreadPriority': 'threads', 'SuspendThread': 'threads', 'ResumeThread': 'threads',
 'CreateEventA': 'sync', 'CreateSemaphoreA': 'sync', 'ReleaseSemaphore': 'sync', 'WaitForSingleObject': 'sync', 'Sleep': 'sync', 'CloseHandle': 'handles',
 'CreateFileA': 'file I/O', 'ReadFile': 'file I/O', 'WriteFile': 'file I/O', 'GetFileSize': 'file I/O', 'SetFilePointer': 'file I/O',
 'GetFileAttributesA': 'file exists', 'CopyFileA': 'file copy', 'GetOverlappedResult': 'async file I/O', 'GetLastError': 'errors',
 'GetTickCount': 'time', 'QueryPerformanceCounter': 'timer', 'QueryPerformanceFrequency': 'timer', 'GlobalMemoryStatus': 'free memory',
 'OutputDebugStringA': 'debug output', 'WideCharToMultiByte': 'string conversion', 'lstrcatA': 'strings', 'lstrcpynA': 'strings',
 # xboxkrnl
 'RtlEnterCriticalSection': 'critical sections (via __imp_)', 'RtlLeaveCriticalSection': 'critical sections (via __imp_)',
 'RtlInitializeCriticalSection': 'critical sections (via __imp_)',
 '_Xlen': 'std::string length_error throw (inline basic_string code)', '_Xran': 'std::string out_of_range throw (inline basic_string code)',
 # xgraphics
 'XFONT_OpenDefaultFont': 'debug/system font', 'XFONT_TextOut': 'debug/system font', 'XFONT_GetTextExtent': 'debug/system font',
 'XFONT_GetTextHeight': 'debug/system font', 'XFONT_SetTextColor': 'debug/system font', 'XFONT_SetTextHeight': 'debug/system font',
 'XFONT_Release': 'debug/system font', 'XGAssembleShader': 'runtime shader assembly', 'XGSpliceVertexShaders': 'combine shader fragments',
 'XGBuffer_GetBufferPointer': 'assembler output', 'XGBuffer_Release': 'assembler output', 'XGMatrixMultiply': 'math', 'XGMatrixTranspose': 'shader constant upload',
 'XGSetTextureHeader': 'build texture header in place', 'XGSetPaletteHeader': 'build palette header in place',
 'XGSwizzleRect': 'texture swizzle', 'XGUnswizzleRect': 'texture unswizzle',
 # xonline / xnet
 'XOnlineStartup': 'Live startup', 'XOnlineTaskContinue': 'pump async Live task', 'XOnlineTaskClose': 'close Live task',
 'XOnlineGetLogonUsers': 'signed-in users', 'XOnlineLogonTaskGetResults': 'logon', 'XOnlineSaveLogonState': 'logon persisted across reboot',
 'XOnlineRetrieveLogonState': 'logon persisted across reboot', 'XOnlineFriendsGetAcceptedGameInvite': 'invite join',
 'XOnlineMatchSearch': 'matchmaking (optimatch)', 'XOnlineMatchSearchGetResults': 'matchmaking', 'XOnlineMatchSearchParse': 'matchmaking',
 'XOnlineMatchSearchResultsLen': 'matchmaking', 'XOnlineMatchSessionCreate': 'host advertise session', 'XOnlineMatchSessionUpdate': 'host advertise session',
 'XOnlineMatchSessionDelete': 'host advertise session', 'XOnlineMatchSessionFindFromID': 'join by session id', 'XOnlineMatchSessionGetInfo': 'session info',
 'XOnlineMutelistStartup': 'voice mute list', 'XOnlineMutelistGet': 'voice mute list',
 'XNetStartup': 'network stack start', 'WSAStartup': 'Winsock start', 'XNetCreateKey': 'system-link/host session key',
 'XNetRegisterKey': 'session key', 'XNetUnregisterKey': 'session key', 'XNetGetTitleXnAddr': 'own XNADDR', 'XNetGetEthernetLinkStatus': 'cable check',
 'XNetXnAddrToInAddr': 'peer address resolution', 'XNetInAddrToXnAddr': 'peer address resolution', 'XNetRandom': 'random bytes/nonces',
 'XNetQosListen': 'QoS probe responder (host)', 'XNetQosLookup': 'QoS probes (client)', 'XNetQosRelease': 'QoS probes',
 # xvoice
 'XHVEngineCreate': 'voice chat engine', 'XHVEngine_SubmitIncomingVoicePacket': 'network voice in',
 'XHVEngine_RegisterRemoteTalker': 'talkers', 'XHVEngine_UnregisterRemoteTalker': 'talkers', 'XHVEngine_RegisterLocalTalker': 'talkers',
 'XHVEngine_UnregisterLocalTalker': 'talkers', 'XHVEngine_IsTalking': 'talking indicator', 'XHVEngine_SetPlaybackPriority': 'mute/priority',
 '_xhv_voicechat_mode': 'processing-mode descriptor', '_xhv_loopback_mode': 'processing-mode descriptor', '_xhv_voicemail_mode': 'processing-mode descriptor',
 'XDEVICE_TYPE_VOICE_HEADPHONE_TABLE': 'headset device type data', 'XDEVICE_TYPE_VOICE_MICROPHONE_TABLE': 'headset device type data',
 # bink
 'BinkOpen': 'open movie', 'BinkClose': 'close movie', 'BinkDoFrame': 'decode frame', 'BinkNextFrame': 'advance', 'BinkWait': 'frame pacing',
 'BinkCopyToBuffer': 'blit frame to texture', 'BinkPause': 'pause', 'BinkGetError': 'error text', 'BinkSetSoundTrack': 'audio track select',
 'BinkGetTrackID': 'audio track', 'BinkSetVolume': 'volume',
}

def note(n):
    for k in ('_Xlen', '_Xran'):
        if k + '(' in n:
            return NOTES[k]
    if n in NOTES:
        return NOTES[n]
    if n.startswith('IDirectSoundBuffer_'):
        return 'voice control'
    if n.startswith('IDirectSound_Set'):
        return '3D listener / global'
    if n.startswith('IDirectSound_'):
        return 'DirectSound object'
    if n.startswith('LiveEngine_'):
        return 'Live UI engine'
    if n.startswith('XHVEngine_'):
        return 'voice engine'
    if n in ('accept', 'bind', 'closesocket', 'htons', 'ioctlsocket', 'listen', 'recv', 'recvfrom', 'select', 'send', 'sendto',
             'setsockopt', 'shutdown', 'socket', 'WSAGetLastError'):
        return 'Winsock (XNet)'
    return ''

D3D_GLOBALS = {'D3D__Device', 'D3D__DirtyFlags', 'D3D__RenderState', 'D3D__TextureState', 'D3D__pDevice'}
def d3d_helper(n):
    return (n.startswith('D3DDevice_SetRenderState_') or n.startswith('D3DDevice_SetTextureState_') or n.endswith('NotInline')
            or n.endswith('NotInlineFast') or n in ('D3DDevice_MakeSpace', 'D3DDevice_BeginPush', 'D3DDevice_EndPush',
            'D3DDevice_BeginStateBig', 'D3DDevice_SetVertexShaderConstant1', 'D3DDevice_SetVertexShaderConstant1Fast',
            'D3DDevice_SetVertexShaderConstant4'))

HELPNOTE = {
 'D3DDevice_SetRenderState_Simple': 'inline D3DDevice_SetRenderState for "simple" states (method/value pair into push buffer)',
 'D3DDevice_SetRenderStateNotInline': 'out-of-line SetRenderState (non-constant state index)',
 'D3DDevice_SetTextureStageStateNotInline': 'out-of-line SetTextureStageState (non-constant)',
 'D3DDevice_MakeSpace': 'push-buffer overflow path of the inline pusher',
 'D3DDevice_BeginPush': 'raw push-buffer write (game/RW writes NV2A methods itself)', 'D3DDevice_EndPush': 'raw push-buffer write',
 'D3DDevice_BeginStateBig': 'large raw state block (skinning constants)',
 'D3DDevice_SetVertexShaderConstant1': 'inline SetVertexShaderConstant (1 register)',
 'D3DDevice_SetVertexShaderConstant1Fast': 'inline SetVertexShaderConstantFast (1 register)',
 'D3DDevice_SetVertexShaderConstant4': 'inline SetVertexShaderConstant (4 registers)',
 'D3DDevice_SetVertexShaderConstantNotInline': 'out-of-line SetVertexShaderConstant',
 'D3DDevice_SetVertexShaderConstantNotInlineFast': 'out-of-line SetVertexShaderConstantFast',
}
GLOBNOTE = {
 'D3D__RenderState': 'render-state shadow array read/written by the inline SetRenderState/GetRenderState',
 'D3D__DirtyFlags': 'lazy-state dirty bits set by the inline setters',
 'D3D__TextureState': 'texture-stage-state shadow array (inline SetTextureStageState)',
 'D3D__pDevice': 'g_pDevice: the CDevice pointer (push-buffer put/threshold via inline code)',
 'D3D__Device': 'the CDevice object itself (inline pusher access)',
}

by = defaultdict(list)
for r in R:
    by[r['lib']].append(r)

ORDER = ['d3d8', 'xapilib', 'dsound', 'xonline', 'uix', 'xvoice', 'xgraphics', 'binkxbox', 'xboxkrnl', 'd3dx8', 'libcpmt', 'libcmt']
out = []
w = out.append
w('# Xbox SDK API inventory (game sources -> SDK libraries)\n')
w('Every UNDEF external symbol in the objects of the plain link (build/plain/link.rsp, %d game objects) that an SDK '
  'library defines, resolved through build/plain/game.map ("lib:object" column), falling back to the libraries\' '
  'linker members. Symbols defined by our own objects are excluded. Users are source files; `src/recovered/` is '
  'left off unit names. The last plain link was a `--devnet` one, so the online libraries are xonline.lib/xnet.lib; '
  'the default build uses xonlines.lib/xnets.lib, which export the same names (the XNet/Winsock functions resolved '
  'to xonline.lib members `xnet.obj`/`sock.obj`, so they are listed under xonline). References kept even when the '
  'referencing function is dropped by /OPT:REF.\n' % NOBJ)
w('## Summary\n')
w('| library | distinct symbols | using source files |')
w('|---|---:|---:|')
summ = []
for lib in ORDER:
    v = by.get(lib, [])
    us = set(u for r in v for u in r['users'])
    summ.append((lib, len(v), len(us)))
    w('| %s | %d | %d |' % (lib, len(v), len(us)))
allus = set(u for r in R if r['lib'] not in ('libcmt', 'libcpmt') for u in r['users'])
w('| **all SDK libs except CRT** | %d | %d |' % (sum(len(by[l]) for l in ORDER if l not in ('libcmt', 'libcpmt')), len(allus)))
w('')
# per area
area = Counter()
for u in allus:
    area['src/recovered (game units)' if u.startswith('src/recovered/') else '/'.join(u.split('/')[:2])] += 1
w('Using files by tree (non-CRT): ' + ', '.join('%s %d' % kv for kv in area.most_common()) + '.\n')

def table(rows, notef):
    w('| symbol | users | note |')
    w('|---|---|---|')
    for r in sorted(rows, key=lambda r: r['name']):
        nm = r['name'] + (' *(import thunk __imp_)*' if r['sym'].startswith('__imp_') else '' if r['isfunc'] else ' *(data)*')
        w('| `%s` | %s | %s |' % (nm, users_str(r['users']), notef(r['name'])))
    w('')

for lib in ORDER:
    v = by.get(lib, [])
    if lib == 'libcmt':
        us = set(u for r in v for u in r['users'])
        w('## libcmt (count only)\n')
        w('%d distinct symbols used by %d source files. Most used:\n' % (len(v), len(us)))
        top = sorted(v, key=lambda r: -len(r['users']))[:15]
        w(', '.join('`%s` (%d)' % (r['name'], len(r['users'])) for r in top) + '.\n')
        continue
    us = set(u for r in v for u in r['users'])
    w('## %s (%d symbols, %d files)\n' % (lib, len(v), len(us)))
    if lib == 'd3d8':
        g = [r for r in v if r['name'] in D3D_GLOBALS]
        h = [r for r in v if d3d_helper(r['name'])]
        rest = [r for r in v if r not in g and r not in h]
        w('### API functions\n')
        table(rest, note)
        w('### Globals (D3D internals referenced by d3d8.h inline code)\n')
        table(g, lambda n: GLOBNOTE.get(n, ''))
        w('### Inline-expanded push-buffer / state helpers\n')
        w('Out-of-line pieces that d3d8.h\'s inline wrappers call. The 30 `SetRenderState_*` and 4 `SetTextureState_*` '
          'functions all appear in the same 9 / 6 files because the inline `D3DDevice_SetRenderState` / '
          '`SetTextureStageState` switch names every complex-state handler whenever the state index is not a '
          'compile-time constant; a port only needs the states actually set.\n')
        rs = [r for r in h if r['name'].startswith('D3DDevice_SetRenderState_') and r['name'] != 'D3DDevice_SetRenderState_Simple']
        ts = [r for r in h if r['name'].startswith('D3DDevice_SetTextureState_')]
        other = [r for r in h if r not in rs and r not in ts]
        table(other, lambda n: HELPNOTE.get(n, ''))
        rsu = sorted(set(u for r in rs for u in r['users']))
        tsu = sorted(set(u for r in ts for u in r['users']))
        w('| symbol group | users | note |')
        w('|---|---|---|')
        w('| `D3DDevice_SetRenderState_{%s}` (%d) | %s | complex render-state handlers from the inline switch |'
          % (','.join(sorted(r['name'][len('D3DDevice_SetRenderState_'):] for r in rs)), len(rs), users_str(rsu, 20)))
        w('| `D3DDevice_SetTextureState_{%s}` (%d) | %s | complex texture-state handlers from the inline switch |'
          % (','.join(sorted(r['name'][len('D3DDevice_SetTextureState_'):] for r in ts)), len(ts), users_str(tsu, 20)))
        w('')
        continue
    table(v, note)

w('## Excluded\n')
w('- Stale objects in link.rsp whose sources no longer exist (from an earlier `--define` run): %s. Research-only '
  'symbols they pulled (XNetStartup, WSAStartup, accept/listen/send/shutdown, GlobalMemoryStatus, _InterlockedExchange) '
  'are not counted.' % ', '.join(s[:-2] for s in stale))
w('- Unresolved-to-a-library references that our own objects satisfy via COMDAT/const folding: %s.'
  % ', '.join('`%s`' % u[0] for u in d['unres']))
open(os.path.join(ROOT, 'docs', 'WIN32_PORT_API.md'), 'w', encoding='utf-8').write('\n'.join(out) + '\n')
for s in summ:
    print(s)
print(area)
