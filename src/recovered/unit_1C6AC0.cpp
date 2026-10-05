// Split from unit_1C60A0.cpp at 0x1C6AC0, where the image starts another object (the voice
// chat, type_3E3884, its constructor first): its .rdata begins at 0x3E3878 with its own
// constants (0.01, 0.01, 16.666666, the block game objects start theirs with) before its
// vtable (PLAN M7).

#include "game/liveservice.h"
#include <string.h>
#include "game/voice.h"
#include "game/gameloop.h"
#include "game/waitscreen.h"
#include "game/startup.h"

// Its data definitions (PLAN M5), in the image's address order.
// 0x003E3878
extern const RwReal flt_3E3878 = 0.01f;
// 0x003E387C
extern const RwReal flt_3E387C = 0.01f;
// 0x003E3880
extern const RwReal flt_3E3880 = 16.666666f;

// match: ?flt_3E3878@@3MB @ 0x003E3878
// match: ?flt_3E387C@@3MB @ 0x003E387C
// match: ?flt_3E3880@@3MB @ 0x003E3880


// match: __ehhandler$?sub_1C6EC0@type_3E3884@@QAEXXZ>1>8 @ 0x0041F598
// match: __ehhandler$?sub_1C6EC0@type_3E3884@@QAEXXZ>1 @ 0x0041F5A0
// match: __ehhandler$?CommunicatorStatusUpdate@type_3E3884@@UAGJKW4_XHV_VOICE_COMMUNICATOR_STATUS@@@Z>1>8 @ 0x0041F5BC
// match: __ehhandler$?CommunicatorStatusUpdate@type_3E3884@@UAGJKW4_XHV_VOICE_COMMUNICATOR_STATUS@@@Z>1 @ 0x0041F5C4
// match: __ehhandler$?sub_1C7840@type_3E3884@@QAE_NHPAUtype_3E0F54@@H@Z>1>8 @ 0x0041F5E0
// match: __ehhandler$?sub_1C7840@type_3E3884@@QAE_NHPAUtype_3E0F54@@H@Z>1 @ 0x0041F5E8
// match: __ehhandler$?sub_1C7C70@type_3E3884@@QAE_NH_N@Z>1>8 @ 0x0041F604
// match: __ehhandler$?sub_1C7C70@type_3E3884@@QAE_NH_N@Z>1 @ 0x0041F60C
// match: ?MicrophoneRawDataReady@ITitleXHV@@UAGJKKPAXPAH@Z @ 0x001C7810
// match: ??_7type_3E3884@@6B@ @ 0x003E3884
// match: ??_C@_0CP@FJOBOPHJ@microphoneBitMask?5?$DN?5?$CFx?0?5headphon@ @ 0x003E38A0
// match: ??_C@_0BK@EJPLNCKD@Player?5?$CFd?5has?5unmuted?5me?6?$AA@ @ 0x003E38D0
// match: ??_C@_0BI@NGFOGLAM@Player?5?$CFd?5has?5muted?5me?6?$AA@ @ 0x003E38EC
// match: ??_C@_0BL@KEKPDIC@Player?5?$CFd?5has?5NO?5speakers?6?$AA@ @ 0x003E3904
// match: ??_C@_0BI@JAGEHHFJ@Player?5?$CFd?5has?5speakers?6?$AA@ @ 0x003E3920
// match: ??_C@_0BK@LOCEHIJN@Player?5?$CFd?5has?5NO?5headset?6?$AA@ @ 0x003E3938
// match: ??_C@_0BH@CPBDBFBM@Player?5?$CFd?5has?5headset?6?$AA@ @ 0x003E3954
// match: ??_C@_0BJ@BIBGIACD@Player?5?$CFd?5to?5be?5unmuted?6?$AA@ @ 0x003E396C
// match: ??_C@_0BH@KCJCFKGP@Player?5?$CFd?5to?5be?5muted?6?$AA@ @ 0x003E3988

// match: ??0type_3E3884@@QAE@XZ @ 0x001C6AC0
type_3E3884::type_3E3884()
    : unk_04(0), unk_08(0), unk_0C(0), unk_10(0), unk_20(0), unk_24(0), unk_E8(0), unk_EC(0), unk_F0(0), unk_F4(0)
{
    memset(unk_28, 0, sizeof(unk_28));
}
// match: ??1type_3E3884@@QAE@XZ @ 0x001C6BE0
type_3E3884::~type_3E3884()
{
}
// match: ?sub_1C6C00@type_3E3884@@QAEXIH@Z @ 0x001C6C00
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void type_3E3884::sub_1C6C00(RwUInt32 arg_0, RwInt32 arg_4)
{
    RwReal w38;
    RwInt32 ebp_34;
    DWORD var_30;
    DWORD v2C;
    XHV_RUNTIME_PARAMS lcl_28;
    HRESULT l4;

    // A compiled-out check: the registers after it are one load on
    // (docs/toolchain.md).
    if (!unk_0C)
    {
    }
    // A compiled-out check: the registers after it are one load on
    // (docs/toolchain.md).
    if (!unk_0C)
    {
    }
    unk_10 = arg_4;
    unk_E8 = arg_0;
    lcl_28.bCustomVADProvided = FALSE;
    lcl_28.bHeadphoneAlwaysOn = FALSE;
    lcl_28.dwEffectsStartIndex = 5;
    lcl_28.dwFlags = 0;
    lcl_28.dwMaxCompressedBuffers = 10;
    lcl_28.dwMaxLocalTalkers = 4;
    lcl_28.dwMaxRemoteTalkers = 4;
    lcl_28.dwOutOfSyncThreshold = 40;
    lcl_28.pEffectImageDesc = unk_04;
    l4 = XHVEngineCreate(&lcl_28, &unk_0C);
    // A compiled-out check: the registers after it are one load on
    // (docs/toolchain.md).
    if (!unk_0C)
    {
    }
    // A compiled-out check: the registers after it are one load on
    // (docs/toolchain.md).
    if (!unk_0C)
    {
    }
    if (arg_4)
        l4 = unk_0C->EnableProcessingMode(XHV_LOOPBACK_MODE);
    // A compiled-out check: the registers after it are one load on
    // (docs/toolchain.md).
    if (!unk_0C)
    {
    }
    l4 = unk_0C->EnableProcessingMode(XHV_VOICECHAT_MODE);
    // A compiled-out check: the registers after it are one load on
    // (docs/toolchain.md).
    if (!unk_0C)
    {
    }
    l4 = unk_0C->EnableProcessingMode(XHV_VOICEMAIL_MODE);
    // A compiled-out check: the registers after it are one load on
    // (docs/toolchain.md).
    if (!unk_0C)
    {
    }
    l4 = unk_0C->SetCallbackInterface(this);
    // A compiled-out check: the registers after it are one load on
    // (docs/toolchain.md).
    if (!unk_0C)
    {
    }
    l4 = unk_0C->RegisterLocalTalker(unk_E8);
    v2C = XGetDevices(XDEVICE_TYPE_VOICE_MICROPHONE);
    var_30 = XGetDevices(XDEVICE_TYPE_VOICE_HEADPHONE);
    if (!unk_0C)
    {
    }
    if (0)
        sub_1C8A30("microphoneBitMask = %x, headphoneBitMask = %x\n", v2C, var_30);
    if (((1 << unk_E8) & v2C) && ((1 << unk_E8) & var_30) ||
        ((1 << (unk_E8 + 16)) & v2C) && ((1 << (unk_E8 + 16)) & var_30))
        unk_F0 = 0;
    else
        unk_F0 = 1;
    w38 = 1.0f;
    ebp_34 = (RwInt32)(w38 * 8388607.0f);
    unk_08->SetEffectData(1, 0x20, &ebp_34, 4, DSFX_IMMEDIATE);
    if (arg_4)
        l4 = unk_0C->SetProcessingMode(unk_E8, XHV_LOOPBACK_MODE);
    else
        l4 = unk_0C->SetProcessingMode(unk_E8, XHV_VOICECHAT_MODE);
}
// match: ?sub_1C6E70@type_3E3884@@QAEXXZ @ 0x001C6E70
void type_3E3884::sub_1C6E70()
{
    HRESULT var_4;

    var_4 = unk_0C->UnregisterLocalTalker(unk_E8);
    // A compiled-out check: the registers after it are one load on
    // (docs/toolchain.md).
    if (!unk_0C)
    {
    }
    unk_0C->Release();
    unk_0C = 0;
}
// match: ?sub_1C6EC0@type_3E3884@@QAEXXZ @ 0x001C6EC0
// match: __ehhandler$?sub_1C6EC0@type_3E3884@@QAEXXZ-0x8 @ 0x00303220
// match: __ehhandler$?sub_1C6EC0@type_3E3884@@QAEXXZ @ 0x00303228
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void type_3E3884::sub_1C6EC0()
{
    RwInt32 var_18;
    RwUInt32 var_14;
    HRESULT lv_10;

    // A compiled-out check: the registers after it are one load on
    // (docs/toolchain.md).
    if (!unk_0C)
    {
    }
    // A compiled-out check: the registers after it are one load on
    // (docs/toolchain.md).
    if (!unk_0C)
    {
    }
    // Two compiled-out checks: the registers after them are two loads on
    // (docs/toolchain.md).
    if (!unk_0C)
    {
    }
    if (!unk_0C)
    {
    }
    if (has_dword_4B9E50())
    {
        var_14 = get_dword_4B9E50();
        if (unk_E8 != var_14)
        {
            sub_227560()->sub_228040();
            sub_227560()->sub_227F70();
            for (var_18 = 0; var_18 < 16; var_18++)
            {
                if (unk_16.test(var_18))
                {
                    unk_0C->RegisterRemoteTalker(unk_28[var_18]);
                    sub_1C74A0(var_18);
                }
            }
        }
    }
    if (sub_1C4C00())
    {
        type_1CCA10 var_1C = type_4F8054::get()->unk_7C;

        // A block of its own: the elapsed time takes its slot below the
        // time's (docs/toolchain.md).
        {
            type_1CCA10 var_20 = var_1C - unk_F8;

            if (var_20 > 1000)
            {
                type_3E0F54 var_30;

                unk_F8 = var_1C;
                var_30.set_unk_04(sub_1C73F0() != 0);
                var_30.set_unk_08(!sub_1D8810()->sub_1D9230() && unk_F0);
                sub_1C7840(unk_4F7EB8.sub_1AEC70(), &var_30, 1);
            }
        }
    }
    lv_10 = unk_0C->DoWork();
}
// match: ?sub_1C70D0@type_3E3884@@QAEXH@Z @ 0x001C70D0
void type_3E3884::sub_1C70D0(RwInt32 arg_0)
{
    // A compiled-out check: the registers after it are one load on
    // (docs/toolchain.md).
    if (!unk_0C)
    {
    }
    // A compiled-out check: the registers after it are one load on
    // (docs/toolchain.md).
    if (!unk_0C)
    {
    }
    unk_14.add(arg_0);
    if (sub_1D8810()->sub_1DBD60(arg_0, &unk_28[arg_0], 1) && unk_20 < 4)
    {
        unk_16.add(arg_0);
        unk_20++;
        unk_F4 = 1;
        unk_0C->RegisterRemoteTalker(unk_28[arg_0]);
        sub_1C74A0(arg_0);
    }
}
// match: ?sub_1C71D0@type_3E3884@@QAEXXZ @ 0x001C71D0
void type_3E3884::sub_1C71D0()
{
    RwInt32 var_4;

    for (var_4 = 0; var_4 < 16; var_4++)
        sub_1C7230(var_4);
    unk_F4 = 0;
    unk_16.unk_00 = 0;
    unk_14.unk_00 = 0;
}
// match: ?sub_1C7230@type_3E3884@@QAEXH@Z @ 0x001C7230
void type_3E3884::sub_1C7230(RwInt32 arg_0)
{
    // A compiled-out check: the registers after it are one load on
    // (docs/toolchain.md).
    if (!unk_0C)
    {
    }
    // A compiled-out check: the registers after it are one load on
    // (docs/toolchain.md).
    if (!unk_0C)
    {
    }
    if (unk_16.test(arg_0))
    {
        // A compiled-out check: the registers after it are one load on
        // (docs/toolchain.md).
        if (!unk_0C)
        {
        }
        unk_16.clear(arg_0);
        unk_20--;
        if (!unk_20)
            unk_F4 = 0;
        if (unk_0C)
            unk_0C->UnregisterRemoteTalker(unk_28[arg_0]);
    }
    memset(&unk_28[arg_0], 0, sizeof(XUID));
    unk_14.clear(arg_0);
}
// match: ?sub_1C7330@type_3E3884@@QAEXHPAEI@Z @ 0x001C7330
void type_3E3884::sub_1C7330(RwInt32 arg_0, RwUInt8 *arg_4, RwUInt32 arg_8)
{
    XUID var_C;
    RwUInt32 var_10;
    RwUInt32 lv_14;

    // A compiled-out check: the registers after it are one load on
    // (docs/toolchain.md).
    if (!unk_0C)
    {
    }
    if (sub_1D8810()->sub_1D9230())
        return;
    if (sub_1D8810()->sub_1DBD60(arg_0, &var_C, 1))
    {
        lv_14 = arg_8 / 10;
        for (var_10 = 0; var_10 < lv_14; var_10++)
        {
            unk_0C->SubmitIncomingVoicePacket(var_C, arg_4, 10);
            arg_4 += 10;
        }
    }
}
// match: ?sub_1C73F0@type_3E3884@@QAEHXZ @ 0x001C73F0
RwInt32 type_3E3884::sub_1C73F0()
{
    if (sub_1D8810()->sub_1D9230())
        return 0;
    return unk_EC;
}
// match: ?sub_1C7420@type_3E3884@@QAEXH@Z @ 0x001C7420
void type_3E3884::sub_1C7420(RwInt32 arg_0)
{
    RwUInt32 var_4;
    RwInt32 l8;

    l8 = unk_F0;
    unk_F0 = arg_0;
    if (unk_F0 != l8)
    {
        sub_227560()->sub_228000();
        for (var_4 = 0; var_4 < 16; var_4++)
        {
            if (unk_16.test(var_4))
                sub_1C74A0(var_4);
        }
    }
}
// match: ?sub_1C74A0@type_3E3884@@QAEXH@Z @ 0x001C74A0
void type_3E3884::sub_1C74A0(RwInt32 arg_0)
{
    if (unk_0C)
    {
        if (!unk_18.test(arg_0))
        {
            // A compiled-out check: the registers after it are one load on
            // (docs/toolchain.md).
            if (!unk_0C)
            {
            }
            if (!unk_1A.test(arg_0) && !sub_1D8810()->sub_1D9230())
            {
                unk_0C->SetPlaybackPriority(unk_28[arg_0], unk_E8,
                                            unk_F0 ? XHV_PLAYBACK_PRIORITY_NEVER : XHV_PLAYBACK_PRIORITY_MAX);
                unk_0C->SetPlaybackPriority(unk_28[arg_0], XHV_PLAYBACK_TO_SPEAKERS,
                                            unk_F0 ? XHV_PLAYBACK_PRIORITY_MAX : XHV_PLAYBACK_PRIORITY_NEVER);
                return;
            }
        }
        unk_0C->SetPlaybackPriority(unk_28[arg_0], unk_E8, XHV_PLAYBACK_PRIORITY_NEVER);
        unk_0C->SetPlaybackPriority(unk_28[arg_0], XHV_PLAYBACK_TO_SPEAKERS, XHV_PLAYBACK_PRIORITY_NEVER);
    }
}
// match: ?CommunicatorStatusUpdate@type_3E3884@@UAGJKW4_XHV_VOICE_COMMUNICATOR_STATUS@@@Z @ 0x001C7680
// match: __ehhandler$?CommunicatorStatusUpdate@type_3E3884@@UAGJKW4_XHV_VOICE_COMMUNICATOR_STATUS@@@Z-0x8 @ 0x00303240
// match: __ehhandler$?CommunicatorStatusUpdate@type_3E3884@@UAGJKW4_XHV_VOICE_COMMUNICATOR_STATUS@@@Z @ 0x00303248
HRESULT type_3E3884::CommunicatorStatusUpdate(DWORD dwLocalPort, XHV_VOICE_COMMUNICATOR_STATUS communicatorStatus)
{
    RwInt32 var_10;

    // A compiled-out check: the registers after it are one load on
    // (docs/toolchain.md).
    if (!unk_0C)
    {
    }
    var_10 = unk_EC;
    unk_EC = communicatorStatus == XHV_VOICE_COMMUNICATOR_STATUS_INSERTED;
    if (var_10 != unk_EC)
        sub_1C7420(unk_EC == 0);
    if (unk_F4)
    {
        type_3E0F54 var_20;

        var_20.set_unk_04(sub_1C73F0() != 0);
        var_20.set_unk_08(!sub_1D8810()->sub_1D9230() && unk_F0);
        sub_1C7840(type_4F8054::get()->get_unk_B0()->sub_1CFF90(), &var_20, 0);
    }
    return S_OK;
}
// match: ?LocalChatDataReady@type_3E3884@@UAGJKKPAX@Z @ 0x001C77C0
HRESULT type_3E3884::LocalChatDataReady(DWORD dwLocalPort, DWORD dwSize, VOID *pData)
{
    if (sub_1D8810()->sub_1D9230())
        return S_OK;
    if (unk_F4)
        unk_24->vf_000((RwUInt8 *)pData, dwSize);
    return S_OK;
}
// The speech and the voice mail's data are ignored (one body, folded by
// /OPT:ICF).
// match: ?SpeechRecognized@type_3E3884@@UAGJKPAU_XHV_SR_ITEM@@K@Z @ 0x001C7820
// symbol: ?VoiceMailDataReady@type_3E3884@@UAGJKKK@Z = 0x001C7820
HRESULT type_3E3884::SpeechRecognized(DWORD dwLocalPort, XHV_SR_ITEM *pSRArray, DWORD dwSRItemsCount)
{
    return S_OK;
}

HRESULT type_3E3884::VoiceMailDataReady(DWORD dwLocalPort, DWORD dwDuration, DWORD dwSize)
{
    return S_OK;
}
// match: ?VoiceMailStopped@type_3E3884@@UAGJK@Z @ 0x001C7830
HRESULT type_3E3884::VoiceMailStopped(DWORD dwLocalPort)
{
    return S_OK;
}
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
// match: ?sub_1C7840@type_3E3884@@QAE_NHPAUtype_3E0F54@@H@Z @ 0x001C7840
// match: __ehhandler$?sub_1C7840@type_3E3884@@QAE_NHPAUtype_3E0F54@@H@Z-0x8 @ 0x00303260
// match: __ehhandler$?sub_1C7840@type_3E3884@@QAE_NHPAUtype_3E0F54@@H@Z @ 0x00303268
bool type_3E3884::sub_1C7840(RwInt32 arg_0, type_3E0F54 *arg_4, RwInt32 arg_8)
{
    bool bp_D = arg_0 == type_4F8054::get()->get_unk_B0()->sub_1CFF90();
    bool lv_E = false;
    bool var_F = false;

    if (arg_4->get_unk_04() != unk_1C.has(arg_0))
    {
        lv_E = true;
        if (arg_4->get_unk_04())
        {
            if (0)
                sub_1C8A30("Player %d has headset\n", arg_0);
        }
        else
        {
            if (0)
                sub_1C8A30("Player %d has NO headset\n", arg_0);
        }
        unk_1C.assign(arg_0, arg_4->get_unk_04());
    }
    if (arg_4->get_unk_08() != unk_1E.has_checked(arg_0))
    {
        lv_E = true;
        if (arg_4->get_unk_08())
        {
            if (0)
                sub_1C8A30("Player %d has speakers\n", arg_0);
        }
        else
        {
            if (0)
                sub_1C8A30("Player %d has NO speakers\n", arg_0);
        }
        unk_1E.assign(arg_0, arg_4->get_unk_08());
    }
    if (arg_4->get_unk_0C() != unk_1A.has_checked(arg_0))
    {
        var_F = true;
        if (arg_4->get_unk_0C())
        {
            if (0)
                sub_1C8A30("Player %d has muted me\n", arg_0);
        }
        else
        {
            if (0)
                sub_1C8A30("Player %d has unmuted me\n", arg_0);
        }
        unk_1A.assign(arg_0, arg_4->get_unk_0C());
    }
    if ((lv_E || var_F) && !bp_D)
        sub_1C74A0(arg_0);
    if (lv_E || arg_8)
    {
        if (bp_D)
        {
            type_1DDE20_mask var_14 = type_4F8054::get()->get_unk_B0_checked()->others_checked();
            RwInt32 var_18;

            for (var_18 = 0; var_18 < 16; var_18++)
            {
                if (var_14.test(var_18))
                {
                    type_3E0F54 var_28;

                    var_28.set_unk_04(sub_1C73F0() != 0);
                    var_28.set_unk_08(!sub_1D8810()->sub_1D9230() && unk_F0);
                    var_28.set_unk_0C(unk_18.test_checked(var_18) != 0);
                    type_4F8058::get()->sub_1DDE20(&var_28, type_1DDE20_mask(1 << var_18));
                }
            }
        }
        else if (lv_E)
            sub_1C74A0(arg_0);
    }
    return lv_E;
}
// match: ?sub_1C7C70@type_3E3884@@QAE_NH_N@Z @ 0x001C7C70
// match: __ehhandler$?sub_1C7C70@type_3E3884@@QAE_NH_N@Z-0x8 @ 0x00303280
// match: __ehhandler$?sub_1C7C70@type_3E3884@@QAE_NH_N@Z @ 0x00303288
bool type_3E3884::sub_1C7C70(RwInt32 arg_0, bool arg_4)
{
    // A compiled-out check: the registers after it are one load on
    // (docs/toolchain.md).
    if (!unk_0C)
    {
    }
    // A compiled-out check: the registers after it are one load on
    // (docs/toolchain.md).
    if (!unk_0C)
    {
    }
    if (arg_4 != (bool)unk_18.has(arg_0))
    {
        type_3E0F54 var_1C;

        if (arg_4)
        {
            if (0)
                sub_1C8A30("Player %d to be muted\n", arg_0);
        }
        else
        {
            if (0)
                sub_1C8A30("Player %d to be unmuted\n", arg_0);
        }
        unk_18.assign(arg_0, arg_4);
        sub_1C74A0(arg_0);
        var_1C.set_unk_04(sub_1C73F0() != 0);
        var_1C.set_unk_08(!sub_1D8810()->sub_1D9230() && unk_F0);
        // A compiled-out check: the registers after it are one load on
        // (docs/toolchain.md).
        if (!unk_0C)
        {
        }
        var_1C.set_unk_0C(unk_18.test(arg_0) != 0);
        type_4F8058::get()->sub_1DDE20(&var_1C, type_1DDE20_mask(1 << arg_0));
        return true;
    }
    return false;
}
// match: ?sub_1C7E30@type_3E3884@@QAEHH@Z @ 0x001C7E30
RwInt32 type_3E3884::sub_1C7E30(RwInt32 arg_0)
{
    // A compiled-out check: the registers after it are one load on
    // (docs/toolchain.md).
    if (!unk_0C)
    {
    }
    if (unk_16.test(arg_0) && unk_0C && unk_0C->IsTalking(unk_28[arg_0]))
    {
        // A compiled-out check: the registers after it are one load on
        // (docs/toolchain.md).
        if (!unk_0C)
        {
        }
        if (!unk_18.test(arg_0))
        {
            // A compiled-out check: the registers after it are one load on
            // (docs/toolchain.md).
            if (!unk_0C)
            {
            }
            if (!unk_1A.test(arg_0))
                return 1;
        }
    }
    return 0;
}
