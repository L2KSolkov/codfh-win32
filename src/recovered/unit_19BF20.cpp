// The Xbox Live manager (game/xboxlive.h): its sign-in and friends
// features through the UIX engine, and the font renderer and audio plugin
// it hands the engine.

#include <string.h>

#include "game/xboxlive.h"
#include "game/gameloop.h"
#include "game/waitscreen.h"
#include "game/functions.h"
#include "game/data.h"
#include "types/type_10F710.h"
#include "types/type_3DD948.h"
#include "game/savestate.h"
#include "types/type_DC400.h"

// Its data definitions (PLAN M5), in the image's address order.
// 0x003E03F0
extern const RwReal flt_3E03F0 = 16.666666f;
// 0x004B8738
RwInt32 dword_4B8738;
// 0x004F312C
D3DSurface *dword_4F312C;
#ifdef CODFH_SP // single player's own Live front end state (.bss)
// SP 0x003B66AC
RwInt32 sp_dword_3B66AC;                // set: the engine gets no pad input and draws nothing
// SP 0x003EAE58
UIX_LOGON_PARAMS sp_dword_3EAE58;       // the sign-in's parameters
// SP 0x003EB75C
HRESULT sp_dword_3EB75C;                // and its result
#endif
// End of its data definitions.


// The manager itself, built by its dynamic initializer and destroyed at exit.
type_4F3130 dword_4F3130;
#ifdef CODFH_SP
// Single player's voice manager, initialised right after the manager (SP 0x21DF90:
// its constructor and atexit; SP 0x21EDD0 destroys it).
CXHVVoiceManager sp_dword_3EB728;
#endif

// Vtables (.rdata, PLAN M5): each in its own placement range (config/splits.txt).
// match: ?flt_3E03F0@@3MB @ 0x003E03F0
// match: __real@3ee66666 @ 0x003E03F4
// match: ??_7type_3E03F8@@6B@ @ 0x003E03F8
// match: ??_7type_3E0404@@6B@ @ 0x003E0404
// match: ??_7type_4F3130@@6B@ @ 0x003E0418
// match: _$E2 @ 0x0030C0F0
// match: _$E3 @ 0x0030EA10
// match: .CRT$XCU+0 @ 0x0042719C
// sp-match: _$E2 @ 0x0021DF70
// sp-match: _$E3 @ 0x0021EDE0

// Not in the image: a stand-in for a function the original object held first, which
// the link dropped (/OPT:REF) but whose literal stayed: 0.45f sits after this
// object's 16.666666 and before its vtables (0x3E03F4), though its only reader is
// the voice library (xvoice's voicing.obj, linked later; a same-named literal is the
// first object's). Unreferenced.
RwReal dropped_3E03F4(RwReal arg_0)
{
    return arg_0 * 0.45f;
}

// match: ?sub_19BF20@type_4F3130@@QAEXJ@Z @ 0x0019BF20
// sp-match: ?sub_19BF20@type_4F3130@@QAEXJ@Z @ 0x0012B670
// Takes a feature's result: signed in, or the reason it failed (some close
// what is showing, 0x80151004 signs out, 0x80151080 retries while the shell
// asks for Live).
void type_4F3130::sub_19BF20(HRESULT arg_0)
{
    switch (arg_0)
    {
    case 0:
        unk_764 = 1;
        break;
    case 0x80151080:
        unk_764 = 4;
        if (dword_4F45F8->unk_40)
            sub_19C160();
        break;
    case 0x80151081:
        unk_764 = 4;
        break;
    case 0x80151082:
        unk_764 = 6;
        break;
    case 0x80151200:
        unk_764 = 4;
        unk_38 = 0;
        sub_19C6D0(1);
        break;
    case 0x80151005:
        unk_764 = 4;
        if (unk_24)
        {
            unk_38 = 0;
            sub_19C2C0(1);
        }
        else
            unk_38 = 7;
        break;
    case 0x80150008:
        unk_764 = 4;
        unk_38 = 0;
        sub_19C6D0(1);
        break;
    case 0x80150009:
        unk_764 = 4;
        unk_38 = 0;
        sub_19C6D0(1);
        break;
    case 0x80151000:
    case 0x80151001:
    case 0x80151002:
    case 0x80151003:
    case 0x80151006:
    case 0x80151101:
    case 0x80151102:
        unk_764 = 4;
        unk_38 = 0;
        sub_19C6D0(1);
        break;
    case 0x80151004:
        sub_19C310();
        break;
    default:
        unk_764 = 4;
        unk_38 = 0;
    }
}

// match: ?sub_19C160@type_4F3130@@QAEJXZ @ 0x0019C160
// sp-match: ?sub_19C160@type_4F3130@@QAEJXZ @ 0x0012B7B0
// Starts the sign-in feature for one user (services 8 and 6) unless the
// manager is already online or offline.
HRESULT type_4F3130::sub_19C160()
{
    HRESULT var_4;
    UIX_LOGON_PARAMS var_60;

    var_4 = 0;
    if (!dword_4F3130.sub_19C500())
    {
        memset(&var_60, 0, 0x54);
        var_60.StructSize = 0x54;
        var_60.LogonType = (UIX_LOGON_TYPE)0;
        var_60.LogonUserCount = 1;
        var_60.LogonServiceIDs[0] = 8;
        var_60.LogonServiceIDs[1] = 6;
        var_4 = unk_04->StartFeature(UIX_LOGON_FEATURE, &var_60);
        sub_19BF20(var_4);
        unk_24 = 0;
    }
    return var_4;
}

// match: ?sub_19C200@type_4F3130@@QAEJXZ @ 0x0019C200
// sp-match: ?sub_19C200@type_4F3130@@QAEJXZ @ 0x0012AFE0
// Starts the friends feature for the signed-in user.
HRESULT type_4F3130::sub_19C200()
{
    HRESULT var_4;
    UIX_FRIENDS_PARAMS var_1C;

    memset(&var_1C, 0, 0x18);
    var_1C.StructSize = 0x18;
    var_1C.UserPort = sub_19C740();
    var_1C.SelectedFriendXUID.qwUserID = 0;
    var_4 = unk_04->StartFeature(UIX_FRIENDS_FEATURE, &var_1C);
    if (var_4 >= 0)
    {
        unk_20 = 1;
        unk_28 = 1;
    }
    return var_4;
}

// match: ?sub_19C280@type_4F3130@@QAEJXZ @ 0x0019C280
// sp-match: ?sub_19C280@type_4F3130@@QAEJXZ @ 0x0012A8E0
HRESULT type_4F3130::sub_19C280()
{
    HRESULT var_4;

    var_4 = unk_04->EndFeature();
    unk_20 = 0;
    unk_28 = 0;
    return var_4;
}

// match: ?sub_19C2C0@type_4F3130@@QAEXH@Z @ 0x0019C2C0
// sp-match: ?sub_19C2C0@type_4F3130@@QAEXH@Z @ 0x0012B050
// Ends the feature and resumes (arg_0: signed out).
void type_4F3130::sub_19C2C0(RwInt32 arg_0)
{
    sub_19C280();
    unk_38 = 0;
    sub_19C380(0);
    if (arg_0)
        unk_764 = 4;
    sub_19C6D0(0);
#ifdef CODFH_SP // single player also stops the voice it started (SP 0x12B050)
    if (sp_dword_3EB728.GetXHVEngine())
    {
        unk_04->SetProperty(UIX_PROPERTY_VOICE_MAIL_ENGINE, 0);
        sp_dword_3EB728.Shutdown();
        unk_74C = 0;
    }
#endif
}

// match: ?sub_19C310@type_4F3130@@QAEXXZ @ 0x0019C310
// sp-match: ?sub_19C310@type_4F3130@@QAEXXZ @ 0x0012B0C0
// Signed out elsewhere: ends the feature, closes its messages, and in the
// game pauses (or, paused already, opens the message).
void type_4F3130::sub_19C310()
{
    sub_19C280();
    sub_19C380(0);
    unk_38 = 0;
    unk_764 = 4;
    sub_19C790();
    if (dword_4B86F8 & 1)
    {
        if (!(dword_4B86F8 & 0x10))
            sub_19C620();
        else
        {
            sub_187040();
            sub_186E70(0, 0, 0);
        }
    }
#ifdef CODFH_SP // single player also stops the voice it started (SP 0x12B0C0)
    if (sp_dword_3EB728.GetXHVEngine())
    {
        unk_04->SetProperty(UIX_PROPERTY_VOICE_MAIL_ENGINE, 0);
        sp_dword_3EB728.Shutdown();
        unk_74C = 0;
    }
#endif
}

// match: ?sub_19C380@type_4F3130@@QAEXM@Z @ 0x0019C380
// sp-match: ?sub_19C380@type_4F3130@@QAEXM@Z @ 0x0012A9F0
void type_4F3130::sub_19C380(RwReal arg_0)
{
    unk_758 = arg_0;
}

// match: ?sub_19C3A0@type_4F3130@@QAEXXZ @ 0x0019C3A0
// sp-match: ?sub_19C3A0@type_4F3130@@QAEXXZ @ 0x0012BEA0
// Appears offline.
void type_4F3130::sub_19C3A0()
{
    dword_4B88AC = 0;
    sub_186F80(0x28, 1);
    sub_19C530();
    unk_38 = 0;
    if (!unk_34)
        sub_186E70(0, 0, 0);
}

// match: ?sub_19C3F0@type_4F3130@@QAEXXZ @ 0x0019C3F0
// sp-match: ?sub_19C3F0@type_4F3130@@QAEXXZ @ 0x0012BEE0
// Appears online.
void type_4F3130::sub_19C3F0()
{
    dword_4B88AC = 0;
    sub_186F80(0x29, 1);
    sub_19C560();
    unk_38 = 0;
    if (!unk_34)
        sub_186E70(0, 0, 0);
}

// match: ?sub_19C440@type_4F3130@@QAEXXZ @ 0x0019C440
// sp-match: ?sub_19C440@type_4F3130@@QAEXXZ @ 0x0012B3E0
// Shows the friends list.
void type_4F3130::sub_19C440()
{
    HRESULT var_4;

    dword_4B88AC = 0;
    sub_186F80(unk_40, 1);
    var_4 = sub_19C200();
    sub_19C380(1.0f);
    unk_38 = 2;
}

// match: ?sub_19C490@type_4F3130@@QAEXXZ @ 0x0019C490
// sp-match: ?sub_19C490@type_4F3130@@QAEXXZ @ 0x0012BAC0
// Signs in.
void type_4F3130::sub_19C490()
{
    dword_4B88AC = 0;
    sub_186F80(0x2A, 1);
    unk_38 = 0;
    sub_19C160();
    unk_38 = 5;
}

// match: ?sub_19C4D0@type_4F3130@@QAEXXZ @ 0x0019C4D0
// sp-match: ?sub_19C4D0@type_4F3130@@QAEXXZ @ 0x0012B420
// Signs out.
void type_4F3130::sub_19C4D0()
{
    dword_4B88AC = 0;
    sub_187040();
    sub_19C2C0(1);
}

// match: ?sub_19C500@type_4F3130@@QAEHXZ @ 0x0019C500
// sp-match: ?sub_19C500@type_4F3130@@QAEHXZ @ 0x0012AA90
// Whether it is online or appears offline.
RwInt32 type_4F3130::sub_19C500()
{
    if (unk_764 == 2 || unk_764 == 3)
        return 1;
    return 0;
}

// match: ?sub_19C530@type_4F3130@@QAEXXZ @ 0x0019C530
// sp-match: ?sub_19C530@type_4F3130@@QAEXXZ @ 0x0012BCF0
void type_4F3130::sub_19C530()
{
    unk_764 = 3;
    sub_19C590(0);
}

// match: ?sub_19C560@type_4F3130@@QAEXXZ @ 0x0019C560
// sp-match: ?sub_19C560@type_4F3130@@QAEXXZ @ 0x0012BD10
void type_4F3130::sub_19C560()
{
    unk_764 = 2;
    sub_19C590(1);
}

// match: ?sub_19C590@type_4F3130@@QAEJH@Z @ 0x0019C590
// sp-match: ?sub_19C590@type_4F3130@@QAEJH@Z @ 0x0012BAF0
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
// Tells the engine the user's online state (arg_0: online).
HRESULT type_4F3130::sub_19C590(RwInt32 arg_0)
{
    HRESULT var_18;
    DWORD var_14;
    XNKID ebp_10;
    DWORD l4;

    l4 = 0;
    var_14 = sub_19C740();
#ifdef CODFH_SP // single player also flags voice when the port's user can talk (SP 0x12BAF0)
    if (sp_sub_12B600(var_14))
        l4 = 8;
#endif
    if (arg_0)
        l4 |= 1;
    memset(&ebp_10, 0, 8);
    var_18 = unk_04->NotificationSetState(var_14, l4, ebp_10, 0, 0);
    return var_18;
}

// match: ?sub_19C620@type_4F3130@@QAEHXZ @ 0x0019C620
// sp-match: ?sub_19C620@type_4F3130@@QAEHXZ @ 0x0012AC80
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
// Pauses the game for the sign-out message, unless there is no player or
// its camera is in mode 1 (then later); whether it did.
RwInt32 type_4F3130::sub_19C620()
{
    type_10F710 *var_8;
    type_3DD948 *l4;

    var_8 = (type_10F710 *)sub_1745A0(0);
    if (!var_8)
    {
        unk_874 = 1;
        return 0;
    }
    l4 = (type_3DD948 *)var_8->unk_2110.sub_D4910();
    if (l4 && l4->get_unk_414() == 1)
    {
        unk_874 = 1;
        return 0;
    }
    if (dword_4B86F8 & 1)
    {
        dword_4B86F8 |= 0x10;
        sub_D7EA0();
        dword_4B9190->sub_E0DD0();
        unk_874 = 0;
        return 1;
    }
    return 0;
}

// match: ?sub_19C6D0@type_4F3130@@QAEXH@Z @ 0x0019C6D0
// sp-match: ?sub_19C6D0@type_4F3130@@QAEXH@Z @ 0x0012ACF0
// Leaves the pause it made (arg_0: and the message).
void type_4F3130::sub_19C6D0(RwInt32 arg_0)
{
    if (((type_4B86F8 *)&dword_4B86F8)->unk_00_4)
    {
        sub_D7EE0();
        sub_187040();
        dword_4B8738 = 0;
        dword_4B86F8 &= ~0x10;
        dword_4B9190->sub_E0E00();
        dword_4B88AC = 0;
    }
    if (arg_0)
        dword_4B88AC = 0;
}

#ifdef CODFH_SP
// sp-match: ?sp_sub_12AD50@type_4F3130@@QAEHXZ @ 0x0012AD50
RwInt32 type_4F3130::sp_sub_12AD50()
{
    if (sp_dword_3B66AC)
        return 0;
    else if (unk_38 == 3)
        return 0;
    else if (unk_38 == 6)
        return 0;
    else if (unk_75C)
        return 0;
    else
        return unk_868 != 0;
}
#endif

// match: ?sub_19C740@type_4F3130@@QAEHXZ @ 0x0019C740
// sp-match: ?sub_19C740@type_4F3130@@QAEHXZ @ 0x0012AD90
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
// The port of the first signed-in user (0 for none).
RwInt32 type_4F3130::sub_19C740()
{
    RwInt32 var_8;
    XONLINE_USER *l4;

    l4 = XOnlineGetLogonUsers();
    if (l4)
    {
        for (var_8 = 0; var_8 < 4; var_8++)
        {
            if (l4[var_8].szGamertag[0])
                return var_8;
        }
    }
    return 0;
}

// match: ?sub_19C790@type_4F3130@@QAEXXZ @ 0x0019C790
// sp-match: ?sub_19C790@type_4F3130@@QAEXXZ @ 0x0012ADC0
// Closes the Live messages (0x24 to 0x2B) that are open.
void type_4F3130::sub_19C790()
{
    RwInt32 var_20[8] = {0x24, 0x25, 0x26, 0x27, 0x28, 0x29, 0x2A, 0x2B};
    RwInt32 var_24;

    for (var_24 = 0; var_24 < 8; var_24++)
    {
        if (sub_186F20(var_20[var_24]))
            sub_186F80(var_20[var_24], 1);
    }
    dword_4B88AC = 0;
}

// match: ?DoWork@type_3E03F8@@UAGJXZ @ 0x0019C820
HRESULT type_3E03F8::DoWork()
{
    return 0;
}

// match: ?Release@type_3E03F8@@UAGKXZ @ 0x0019C830
// sp-match: ?Release@type_3E03F8@@UAGKXZ @ 0x0012AE60
ULONG type_3E03F8::Release()
{
    unk_04 = unk_04 - 1;
    return unk_04;
}

// match: ??0type_4F3130@@QAE@XZ @ 0x0019C850
// sp-match: ??0type_4F3130@@QAE@XZ @ 0x0012AE90
type_4F3130::type_4F3130()
{
    unk_764 = 0;
    unk_20 = 0;
    unk_754 = 0;
    unk_758 = 0;
    unk_750 = 0;
    unk_86C = 0;
    unk_38 = 0;
    unk_74C = 0;
    unk_75C = 0;
    unk_760 = 0;
    unk_1C = 0;
    unk_868 = 0;
    unk_24 = 0;
    unk_28 = 0;
    unk_870 = 0;
    unk_874 = 0;
}

// match: ?vf_000@type_4F3130@@UAGJKKK@Z @ 0x0019C970
// sp-match: ?vf_000@type_4F3130@@UAGJKKK@Z @ 0x0012AF20
HRESULT type_4F3130::vf_000(DWORD arg_0, DWORD arg_4, DWORD arg_8)
{
    return E_NOTIMPL;
}

// match: ?vf_004@type_4F3130@@UAGJKK@Z @ 0x0019C980
// sp-match: ?vf_004@type_4F3130@@UAGJKK@Z @ 0x0012AF00
HRESULT type_4F3130::vf_004(DWORD arg_0, DWORD arg_4)
{
    return E_NOTIMPL;
}

HRESULT type_4F3130::vf_008(DWORD arg_0, DWORD arg_4, DWORD arg_8)
{
    return E_NOTIMPL;
}

// sp-match: ?vf_00C@type_4F3130@@UAGJKKKK@Z @ 0x0012AF10
HRESULT type_4F3130::vf_00C(DWORD arg_0, DWORD arg_4, DWORD arg_8, DWORD arg_C)
{
    return E_NOTIMPL;
}

HRESULT type_4F3130::vf_010(DWORD arg_0, DWORD arg_4, DWORD arg_8)
{
    return E_NOTIMPL;
}

// match: ?vf_014@type_4F3130@@UAGJK@Z @ 0x0019C990
// sp-match: ?vf_014@type_4F3130@@UAGJK@Z @ 0x0012AF30
HRESULT type_4F3130::vf_014(DWORD arg_0)
{
    return E_NOTIMPL;
}

// match: ?Release@type_3E0404@@UAGKXZ @ 0x0019C9A0
#ifdef CODFH_SP // shape: single player defines Release in the class (game/xboxlive.h), so it calls the
                // destructor's out-of-line copy (SP 0x12A770) where ~type_4F3130 (SP 0x12A820) expands it
// sp-match: ?Release@type_3E0404@@UAGKXZ @ 0x0012AE70
// sp-match: ??1type_3E0404@@QAE@XZ @ 0x0012A770
#else
ULONG type_3E0404::Release()
{
    delete this;
    return 0;
}
#endif

// match: ?DrawText@type_3E0404@@UAGJPBGKKK@Z @ 0x0019CA10
// sp-match: ?DrawText@type_3E0404@@UAGJPBGKKK@Z @ 0x0012A790
HRESULT type_3E0404::DrawText(LPCWSTR arg_0, DWORD arg_4, DWORD arg_8, DWORD arg_C)
{
    return unk_04->TextOut(dword_4F312C, arg_0, -1, arg_4, arg_8);
}

// match: ?GetTextSize@type_3E0404@@UAGJPBGPAK1@Z @ 0x0019CA50
// sp-match: ?GetTextSize@type_3E0404@@UAGJPBGPAK1@Z @ 0x0012A7C0
HRESULT type_3E0404::GetTextSize(LPCWSTR arg_0, DWORD *arg_4, DWORD *arg_8)
{
    *arg_8 = unk_04->GetTextHeight();
    return unk_04->GetTextExtent(arg_0, -1, (RwUInt32 *)arg_4);
}

// match: ?SetColor@type_3E0404@@UAGJK@Z @ 0x0019CA90
// sp-match: ?SetColor@type_3E0404@@UAGJK@Z @ 0x0012A7F0
HRESULT type_3E0404::SetColor(D3DCOLOR arg_0)
{
    unk_04->SetTextColor(arg_0);
    return 0;
}

// match: ?SetHeight@type_3E0404@@UAGJK@Z @ 0x0019CAC0
// sp-match: ?SetHeight@type_3E0404@@UAGJK@Z @ 0x0012A810
HRESULT type_3E0404::SetHeight(DWORD arg_0)
{
    return unk_04->SetTextHeight(arg_0);
}

// match: ??1type_4F3130@@QAE@XZ @ 0x0019CAE0
// sp-match: ??1type_4F3130@@QAE@XZ @ 0x0012A820
// (Implicit: it destroys the font renderer only, without storing the
// manager's vtable again, as a declared destructor would.)

#ifdef CODFH_SP
// Single player's own Live front end (SP 0x12A840-0x12C230, no MP twins), in
// its address order: callees before their callers.
#include <stdio.h>
#include "game/platform.h"
#include "game/padlib.h"
#include "game/movie.h"         // dword_4B8EA4 (SP .bss 0x3B581C): stops the playing movie
#include "types/soundbank.h"
#include "types/type_3DF8D8.h"
#include "rw/rwxbox.h"

// Single player's front-end draws (unit_19B0F0) and its launch of the other
// image (SP 0xAE9E0) and profile pick (SP 0x12F570).
void sp_sub_129C90(RwCamera *arg_0, RwReal arg_4);
void sp_sub_129DC0(RwV2d *arg_0, const RwChar *arg_4, RwReal arg_8, RwRGBA *arg_C, RwReal arg_10);
void sp_sub_129E50(RwV2d *arg_0, const RwChar *arg_4, RwReal arg_8);
void sp_sub_AE9E0(RwCamera *arg_0, RwInt32 arg_4);
void sp_sub_12F570();
// The language for the engine (unit_19B0F0, game/liveservice.h).
RwInt32 sub_19BEA0();
// xfont.h declares it only with XFONT_TRUETYPE.
extern "C" HRESULT __stdcall XFONT_OpenTrueTypeFont(LPCWSTR wszFileName, RwUInt32 uCacheSize, XFONT **ppFont);
// The disc error's titles and texts (unit_19CB20, SP .data 0x329494): [5] is the Live engine's
// layout, "d:\\Media\\codlayout.uix" (SP 0x3294A8).
extern const RwChar *off_42C5A4[13];

// sp-match: ?sp_sub_12A840@type_4F3130@@QAEJXZ @ 0x0012A840
// Opens the font and hands the engine the UI plugin made over it.
HRESULT type_4F3130::sp_sub_12A840()
{
    HRESULT var_4;

    if (!sub_19CDE0("d:\\media\\arialuni.ttf"))
        return -1;
    var_4 = XFONT_OpenTrueTypeFont(L"d:\\media\\arialuni.ttf", 0x10000, &unk_08.unk_04);
    if (var_4 >= 0)
    {
        ((ITitleFontRenderer *)&unk_08)->SetColor(0xFFFFFFFF);
        var_4 = UIXCreateUIPlugin(&unk_08, (ITitleUIPlugin **)unk_10);
        if (var_4 >= 0)
            var_4 = unk_04->SetUIPlugin(*(ITitleUIPlugin **)unk_10);
    }
    return var_4;
}
#endif

#ifdef CODFH_SP
// sp-match: ?sp_sub_12A8A0@type_4F3130@@QAEJXZ @ 0x0012A8A0
HRESULT type_4F3130::sp_sub_12A8A0()
{
    return unk_04->SetAudioPlugin(&unk_14);
}
#endif

#ifdef CODFH_SP
// sp-match: ?sp_sub_12A8B0@type_4F3130@@QAEJXZ @ 0x0012A8B0
// Enables the sign-in and friends features.
HRESULT type_4F3130::sp_sub_12A8B0()
{
    HRESULT var_4;

    var_4 = unk_04->EnableFeature(UIX_LOGON_FEATURE);
    if (var_4 >= 0)
        var_4 = unk_04->EnableFeature(UIX_FRIENDS_FEATURE);
    return var_4;
}
#endif

#ifdef CODFH_SP
// sp-match: ?sp_sub_12A900@type_4F3130@@QAEXMM@Z @ 0x0012A900
// Puts message 0x2B up (in the front end) and draws its text at (arg_0, arg_4).
void type_4F3130::sp_sub_12A900(RwReal arg_0, RwReal arg_4)
{
    RwV2d var_8;

    if (!unk_34 && sub_188350() != 0x2B)
        sub_186E70(0x2B, 0, 0);
    var_8.x = arg_0;
    var_8.y = arg_4;
    sp_sub_129DC0(&var_8, dword_4F6178[28], 1.4f, 0, 1.3f);
}
#endif

#ifdef CODFH_SP
// sp-match: ?sp_sub_12A960@type_4F3130@@QAEXXZ @ 0x0012A960
void type_4F3130::sp_sub_12A960()
{
    sp_sub_AE9E0(unk_30, 1);
}
#endif

#ifdef CODFH_SP
// sp-match: ?sp_sub_12A970@type_4F3130@@QAEXXZ @ 0x0012A970
// Renders the engine over the back buffer (unless signing in) while it shows something.
void type_4F3130::sp_sub_12A970()
{
    if (unk_764 != 5 && unk_750)
    {
        unk_2C = 1;
        _rwXbFlushCacheBuffer();
        ((ITitleFontRenderer *)&unk_08)->SetColor(0xFF0000FF);
        unk_04->Render(dword_4F312C);
        _rwXbFlushCacheBuffer();
    }
}
#endif

#ifdef CODFH_SP
// sp-match: ?sp_sub_12A9C0@type_4F3130@@QAEXPAURwCamera@@@Z @ 0x0012A9C0
// Fades the camera arg_0's view while the friends list is up and the game is not paused.
void type_4F3130::sp_sub_12A9C0(RwCamera *arg_0)
{
    if (unk_20 && arg_0 && !((type_4B86F8 *)&dword_4B86F8)->unk_00_4)
        sp_sub_129C90(arg_0, unk_754);
}
#endif

#ifdef CODFH_SP
// sp-match: ?sp_sub_12AA00@type_4F3130@@QAEXH@Z @ 0x0012AA00
// Opens message arg_0, remembering the step to go back to.
void type_4F3130::sp_sub_12AA00(RwInt32 arg_0)
{
    sub_187040();
    sub_186E70(arg_0, 0, 0);
    unk_40 = arg_0;
    dword_4B88AC = 1;
    unk_3C = unk_38;
    unk_38 = 1;
}
#endif

#ifdef CODFH_SP
// sp-match: ?sp_sub_12AA40@type_4F3130@@QAEXXZ @ 0x0012AA40
// Goes to the dashboard's account management.
void type_4F3130::sp_sub_12AA40()
{
    LD_LAUNCH_DASHBOARD var_C00;

    memset(&var_C00, 0, sizeof(var_C00));
    var_C00.dwReason = XLD_LAUNCH_DASHBOARD_ACCOUNT_MANAGEMENT;
    XLaunchNewImage(0, (PLAUNCH_DATA)&var_C00);
}
#endif

#ifdef CODFH_SP
// sp-match: ?sp_sub_12AAB0@type_4F3130@@QAEHXZ @ 0x0012AAB0
// Whether it is signed out (4 or 6).
RwInt32 type_4F3130::sp_sub_12AAB0()
{
    if (unk_764 == 4 || unk_764 == 6)
        return 1;
    return 0;
}
#endif

#ifdef CODFH_SP
// sp-match: ?sp_sub_12AAD0@type_4F3130@@QAEHXZ @ 0x0012AAD0
RwInt32 type_4F3130::sp_sub_12AAD0()
{
    if (unk_20)
        return 1;
    else if (unk_75C)
        return 1;
    else if (unk_760)
        return 1;
    else if (unk_868)
        return 1;
    else if (unk_38 == 1)
        return 1;
    else
        return unk_38 == 5;
}
#endif

#ifdef CODFH_SP
// sp-match: ?sp_sub_12AB10@type_4F3130@@QAEPADXZ @ 0x0012AB10
// The signed-in user's gamertag (0 while not signed in).
RwChar *type_4F3130::sp_sub_12AB10()
{
    if (unk_764 == 1 || unk_764 == 2 || unk_764 == 3)
        return unk_48[unk_86C].szGamertag;
    return 0;
}
#endif

#ifdef CODFH_SP
// sp-match: ?sp_sub_12AB40@type_4F3130@@QAEXH@Z @ 0x0012AB40
// Once: registers the four ports' talkers, chatting (arg_0) or not, through the speakers.
void type_4F3130::sp_sub_12AB40(RwInt32 arg_0)
{
    RwInt32 var_4;

    if (!unk_74C)
    {
        for (var_4 = 0; var_4 < 4; var_4++)
        {
            sp_dword_3EB728.RegisterLocalTalker(var_4);
            if (arg_0)
                sp_dword_3EB728.GetXHVEngine()->SetProcessingMode(var_4, XHV_VOICECHAT_MODE);
            else
                sp_dword_3EB728.GetXHVEngine()->SetProcessingMode(var_4, XHV_INACTIVE_MODE);
            sp_dword_3EB728.SetVoiceThroughSpeakers(var_4, TRUE);
        }
    }
    unk_74C = 1;
}
#endif

#ifdef CODFH_SP
// sp-match: ?sp_sub_12ABB0@type_4F3130@@QAEHXZ @ 0x0012ABB0
// Whether it is at a step of its own (all but 0 and 5).
RwInt32 type_4F3130::sp_sub_12ABB0()
{
    switch (unk_38)
    {
    case 1:
    case 2:
    case 3:
    case 4:
    case 6:
    case 7:
        return 1;
    }
    return 0;
}
#endif

#ifdef CODFH_SP
// sp-match: ?sp_sub_12ABF0@type_4F3130@@QAEHH@Z @ 0x0012ABF0
// Takes the state arg_0 unless it is a signed-in one (1 to 3); whether it did.
RwInt32 type_4F3130::sp_sub_12ABF0(RwInt32 arg_0)
{
    if (arg_0 > 0 && arg_0 <= 3)
        return 0;
    unk_764 = arg_0;
    return 1;
}
#endif

#ifdef CODFH_SP
// sp-match: ?sp_sub_12AC10@type_4F3130@@QAEJXZ @ 0x0012AC10
// Reads the users (once the devices are enumerated) and puts the first signed-in one first.
HRESULT type_4F3130::sp_sub_12AC10()
{
    HRESULT var_8;
    XONLINE_USER *var_4;
    RwInt32 i;

    unk_86C = 0;
    while (XGetDeviceEnumerationStatus() == XDEVICE_ENUMERATION_BUSY)
        ;
    var_8 = XOnlineGetUsers(unk_48, &unk_748);
    var_4 = XOnlineGetLogonUsers();
    if (var_4)
    {
        for (i = 0; i < 4; i++)
        {
            if (var_4[i].szGamertag[0])
            {
                unk_48[0] = var_4[i];
                break;
            }
        }
    }
    else
        unk_48[0].szGamertag[0] = 0;
    return var_8;
}
#endif

#ifdef CODFH_SP
// sp-match: ?sp_sub_12AF40@type_4F3130@@QAEJXZ @ 0x0012AF40
// Starts the sign-in for one user (services 8 and 6): with the shell's logon
// state when Live was chosen, else silently; unless online already.
HRESULT type_4F3130::sp_sub_12AF40()
{
    if (!dword_4F3130.sub_19C500())
    {
        memset(&sp_dword_3EAE58, 0, 0x54);
        sp_dword_3EAE58.StructSize = 0x54;
        if (dword_4F45F8->unk_40)
        {
            sp_dword_3EAE58.LogonType = UIX_LOGON_TYPE_RETRIEVED_STATE;
            sp_dword_3EAE58.pLogonState = (XONLINE_LOGON_STATE *)dword_4F45F8->unk_48A;
            unk_24 = 0;
        }
        else
        {
            sp_dword_3EAE58.LogonType = UIX_LOGON_TYPE_SILENT;
            unk_24 = 1;
        }
        sp_dword_3EAE58.LogonUserCount = 1;
        sp_dword_3EAE58.LogonServiceIDs[0] = 8;
        sp_dword_3EAE58.LogonServiceIDs[1] = 6;
        sp_dword_3EB75C = unk_04->StartFeature(UIX_LOGON_FEATURE, &sp_dword_3EAE58);
    }
    return sp_dword_3EB75C;
}
#endif

#ifdef CODFH_SP
// sp-match: ?sp_sub_12B140@type_4F3130@@QAEXXZ @ 0x0012B140
// Step 1: keeps its message up; on the button (0x18, or 0xB in the front end) goes back.
void type_4F3130::sp_sub_12B140()
{
    RwReal var_4;

    if (sub_188350() != unk_40)
    {
        sub_187040();
        sub_186E70(unk_40, 0, 0);
    }
    if (!unk_34)
        var_4 = unk_4B9308.sub_EE9A0(0, 0xB);
    else
        var_4 = unk_4B9308.sub_EE9A0(0, 0x18);
    if (var_4 != 0.0f)
    {
        dword_4B88AC = 0;
        unk_38 = unk_3C;
        if (!unk_34)
            sub_19C6D0(1);
        sub_187040();
    }
}
#endif

#ifdef CODFH_SP
// sp-match: ?sp_sub_12B1C0@type_4F3130@@QAEXXZ @ 0x0012B1C0
// Step 3: its message; 0x17 goes on to step 4, 0x18 cancels.
void type_4F3130::sp_sub_12B1C0()
{
    sp_sub_12A900(260.0f, 320.0f);
    if (unk_4B9308.sub_EE9A0(0, 0x17) != 0.0f)
    {
        sub_187040();
        unk_38 = 4;
        dword_4B88AC = 0;
    }
    if (unk_4B9308.sub_EE9A0(0, 0x18) != 0.0f)
    {
        sub_187040();
        sub_19C6D0(1);
        unk_38 = 0;
        dword_4B88AC = 0;
        unk_75C = 0;
    }
}
#endif

#ifdef CODFH_SP
// sp-match: ?sp_sub_12B240@type_4F3130@@QAEXXZ @ 0x0012B240
// Step 6: its message; 0x17 reboots the engine, 0x18 signs out.
void type_4F3130::sp_sub_12B240()
{
    unk_750 = 0;
    sp_sub_12A900(260.0f, 320.0f);
    if (unk_4B9308.sub_EE9A0(0, 0x17) != 0.0f)
        unk_04->Reboot(dword_4F4628);
    if (unk_4B9308.sub_EE9A0(0, 0x18) != 0.0f)
    {
        sub_19C280();
        sub_187040();
        sub_19C6D0(1);
        unk_38 = 0;
        unk_764 = 4;
        dword_4B88AC = 0;
    }
}
#endif

#ifdef CODFH_SP
// sp-match: ?sp_sub_12B2E0@type_4F3130@@QAEXXZ @ 0x0012B2E0
// Step 7: signs out unless the engine has the input.
void type_4F3130::sp_sub_12B2E0()
{
    if (!unk_868)
    {
        unk_764 = 4;
        unk_38 = 0;
        sub_19C2C0(1);
        sub_19C790();
    }
}
#endif

#ifdef CODFH_SP
// sp-match: ?sp_sub_12B310@type_4F3130@@QAEXXZ @ 0x0012B310
// Online or appearing offline: button 0x23 opens the other's message (0x28, 0x29).
void type_4F3130::sp_sub_12B310()
{
    RwReal var_4;

    if (!unk_20)
    {
        var_4 = unk_4B9308.sub_EE9A0(0, 0x23);
        if ((unk_34 || !(flt_4B8984 < 0.45f)) && var_4 != 0.0f)
        {
            switch (unk_764)
            {
            case 2:
                sp_sub_12AA00(0x28);
                break;
            case 3:
                sp_sub_12AA00(0x29);
                break;
            }
        }
    }
}
#endif

#ifdef CODFH_SP
// sp-match: ?sp_sub_12B380@type_4F3130@@QAEXXZ @ 0x0012B380
// Signed out: button 0x23 opens the sign-in message (0x2A).
void type_4F3130::sp_sub_12B380()
{
    RwReal var_4;

    if (!unk_20)
    {
        var_4 = unk_4B9308.sub_EE9A0(0, 0x23);
        if ((unk_34 || !(flt_4B8984 < 0.45f)) && var_4 != 0.0f)
            sp_sub_12AA00(0x2A);
    }
}

// sp-match: ?sp_sub_12B440@type_4F3130@@QAEXPAUtype_4F3130_texts@@@Z @ 0x0012B440
// The status texts for the state (two lines in the front end: the label, then the gamertag).
void type_4F3130::sp_sub_12B440(type_4F3130_texts *arg_0)
{
    RwInt32 count;

    arg_0->unk_08 = 0;
    switch (unk_764)
    {
    case 1:
        sprintf(unk_768, "%s", dword_4F6178[18]);
        count = arg_0->unk_08 + 1;
        break;
    case 2:
    case 3:
        if (!unk_34)
        {
            sprintf(unk_768, "%s:", dword_4F6178[10]);
            sprintf(unk_7E8, "%s", sp_sub_12AB10());
            count = arg_0->unk_08 + 2;
        }
        else
        {
            sprintf(unk_768, "%s: %s", dword_4F6178[10], sp_sub_12AB10());
            count = arg_0->unk_08 + 1;
        }
        break;
    case 6:
    case 7:
        if (!unk_34)
        {
            sprintf(unk_768, "%s:", dword_4F6178[13]);
            sprintf(unk_7E8, "%s", dword_4F6178[12]);
            count = arg_0->unk_08 + 2;
        }
        else
        {
            sprintf(unk_768, "%s: %s", dword_4F6178[13], dword_4F6178[12]);
            count = arg_0->unk_08 + 1;
        }
        break;
    case 4:
        strcpy(unk_768, dword_4F6178[13]);
        count = arg_0->unk_08 + 1;
        break;
    case 5:
        strcpy(unk_768, dword_4F6178[11]);
        count = arg_0->unk_08 + 1;
        break;
    default:
        strcpy(unk_768, dword_4F6178[11]);
        count = arg_0->unk_08 + 1;
        break;
    }
    arg_0->unk_00[1] = unk_7E8;
    arg_0->unk_00[0] = unk_768;
    arg_0->unk_08 = count;
}
#endif

#ifdef CODFH_SP
// sp-match: ?sp_sub_12B600@type_4F3130@@QAEHH@Z @ 0x0012B600
// Whether port arg_0's user may talk and has a microphone and headphone; the
// voice is set up for chat accordingly.
RwInt32 type_4F3130::sp_sub_12B600(RwInt32 arg_0)
{
    DWORD var_8;
    DWORD var_4;
    RwInt32 var_C;

    var_8 = XGetDevices(XDEVICE_TYPE_VOICE_MICROPHONE);
    var_4 = XGetDevices(XDEVICE_TYPE_VOICE_HEADPHONE);
    if (XOnlineIsUserVoiceAllowed(unk_48[arg_0].xuid.dwUserFlags)
        && (var_8 & (1 << arg_0)) && (var_4 & (1 << arg_0)))
        var_C = 1;
    else
        var_C = 0;
    sp_sub_12AB40(var_C);
    return var_C;
}
#endif

#ifdef CODFH_SP
// sp-match: ?sp_sub_12B830@type_4F3130@@QAEXXZ @ 0x0012B830
// Step 0: the state's button handling.
void type_4F3130::sp_sub_12B830()
{
    unk_28 = 0;
    switch (unk_764)
    {
    case 2:
    case 3:
        sp_sub_12B310();
        break;
    case 4:
    case 6:
        sp_sub_12B380();
        break;
    }
}
#endif

#ifdef CODFH_SP
// sp-match: ?sp_sub_12B870@type_4F3130@@QAEXPAURwCamera@@PAURwV2d@@HPAURwRGBA@@1H2@Z @ 0x0012B870
// Draws the status texts at arg_4 (plain with arg_8, else in the colour
// arg_C) and, signed in or out, the button prompt at arg_10; at step 1 in the
// front end, the pause prompt.
void type_4F3130::sp_sub_12B870(RwCamera *arg_0, RwV2d *arg_4, RwInt32 arg_8, RwRGBA *arg_C,
                                RwV2d *arg_10, RwInt32 arg_14, RwRGBA *arg_18)
{
    RwChar var_100[0x100];
    RwV2d var_8;
    type_4F3130_texts var_14;
    RwInt32 i;

    switch (unk_38)
    {
    case 0:
        var_8 = *arg_4;
        sp_sub_12B440(&var_14);
        if (!arg_8)
        {
            if (!unk_34 && var_14.unk_08 == 1)
                var_8.y += 18.0f;
            for (i = 0; i < var_14.unk_08; i++)
            {
                sp_sub_129DC0(&var_8, var_14.unk_00[i], 1.0f, arg_C, 1.0f);
                var_8.y += 18.0f;
            }
        }
        else
        {
            if (!unk_34 && var_14.unk_08 == 1)
                var_8.y += 18.0f;
            for (i = 0; i < var_14.unk_08; i++)
            {
                sp_sub_129E50(&var_8, var_14.unk_00[i], 1.0f);
                var_8.y += 18.0f;
            }
        }
        if (sub_19C500() || sp_sub_12AAB0())
        {
            RwV2d var_10;

            var_10 = *arg_10;
            if (!unk_34 && dword_4F28F0->unk_1C == 1)
            {
                var_10.x += 25.0f;
                sprintf(var_100, "$he$ %s", dword_4F6178[6]);
            }
            else
                sprintf(var_100, "$pu$ %s", dword_4F6178[6]);
            if (!arg_14)
                sp_sub_129DC0(&var_10, var_100, 1.3f, arg_18, 1.0f);
            else
                sp_sub_129E50(&var_10, var_100, 1.3f);
        }
        break;
    case 1:
        if (!unk_34)
        {
            RwV2d var_10;
            type_3DF8D8 *var_C;
            const RwChar *var_4;

            sprintf(var_100, "$pa$ %s", dword_4F6178[14]);
            sp_sub_129DC0(arg_10, var_100, 1.3f, 0, 1.0f);
            var_C = sub_198880("COD_InGameText+Event_MenuAction");
            var_4 = var_C->sub_197550(0, 0);
            var_10.x = 60.0f;
            var_10.y = arg_10->y;
            sp_sub_129E50(&var_10, var_4, 1.3f);
        }
        break;
    }
}
#endif

#ifdef CODFH_SP
// sp-match: ?sp_sub_12BB50@type_4F3130@@QAEJHH@Z @ 0x0012BB50
// Sets up Live: the back buffer, the network, then (unless a game invite
// was accepted: then the other image is launched) the engine with its font,
// plugins and features; with arg_0 it takes the state arg_4, else (or if
// that is a signed-in one) it signs in.
HRESULT type_4F3130::sp_sub_12BB50(RwInt32 arg_0, RwInt32 arg_4)
{
    HRESULT var_4;

    dword_4F312C = D3DDevice_GetBackBuffer2(0);
    XOnlineStartup(NULL);
    unk_2C = 0;
    if (XOnlineFriendsGetAcceptedGameInvite((XONLINE_ACCEPTED_GAMEINVITE *)dword_4F45F8->unk_398) == S_OK)
    {
        if (!unk_30)
            unk_30 = dword_4B88B0;
        sp_sub_12F570();
        sp_sub_AE9E0(unk_30, 2);
        return 0;
    }
    if (!sub_19CDE0(off_42C5A4[5]))
        return 0;
    var_4 = UIXCreateLiveEngine(off_42C5A4[5], sub_19BEA0(), &unk_04);
    if (var_4 >= 0)
    {
        if (sp_sub_12A840())
            return 0;
        sp_sub_12A8A0();
        sp_sub_12A8B0();
        if (!arg_0 || !sp_sub_12ABF0(arg_4))
        {
            var_4 = dword_4F3130.sp_sub_12AF40();
            sub_19BF20(var_4);
        }
    }
    return var_4;
}
#endif

#ifdef CODFH_SP
// sp-match: ?sp_sub_12BC30@type_4F3130@@QAEHXZ @ 0x0012BC30
// Its update: the fade follows its target while the friends list is up or
// signing in; closes a lost message; runs the step.
RwInt32 type_4F3130::sp_sub_12BC30()
{
    if (unk_20 || unk_764 == 1)
        unk_754 = unk_758;
    if (unk_38 && !sub_188350())
        sub_186F80(0, 1);
    switch (unk_38)
    {
    case 0:
        sp_sub_12B830();
        break;
    case 1:
        sp_sub_12B140();
        break;
    case 3:
        sp_sub_12B1C0();
        break;
    case 4:
        sp_sub_12A960();
        break;
    case 6:
        sp_sub_12B240();
        break;
    case 7:
        sp_sub_12B2E0();
        break;
    }
    return 1;
}
#endif

#ifdef CODFH_SP
// sp-match: ?sp_sub_12BD30@type_4F3130@@QAEJPAU_UIX_EXIT_INFO@@@Z @ 0x0012BD30
// Signed in: reads the users, starts the voice (30 remote and 4 local
// talkers) and its voice mail, and goes online.
HRESULT type_4F3130::sp_sub_12BD30(UIX_EXIT_INFO *arg_0)
{
    HRESULT var_28;

    sub_19C280();
    sp_sub_12AC10();
    unk_38 = 0;
    unk_1C = 1;
    if (!unk_24)
        sub_19C6D0(1);
    type_44E8B0 *var_2C = dword_44E8B0;
    XHV_RUNTIME_PARAMS var_24 = {0};
    var_24.dwMaxLocalTalkers = 4;
    var_24.dwMaxRemoteTalkers = 30;
    var_24.dwMaxCompressedBuffers = 4;
    var_24.dwFlags = 0;
    var_24.pEffectImageDesc = (DSEFFECTIMAGEDESC *)var_2C->unk_88;
    var_24.dwEffectsStartIndex = 5;
    var_24.dwOutOfSyncThreshold = 10;
    sp_dword_3EB728.Initialize((LPDIRECTSOUND8)var_2C->unk_6C, &var_24, (ITitleXHV *)(type_3E0418 *)this);
    unk_04->UseVoiceMail(UIX_VOICE_MAIL);
    PXHVENGINE var_30 = sp_dword_3EB728.GetXHVEngine();
    var_28 = unk_04->SetProperty(UIX_PROPERTY_VOICE_MAIL_ENGINE, (DWORD)var_30);
    sp_dword_3EB728.GetXHVEngine()->SetMaxPlaybackStreamsCount(2);
    unk_04->SetProperty(UIX_PROPERTY_VOICE_MAIL_TO_SPEAKERS, 1);
    unk_04->SetProperty(UIX_PROPERTY_DISPLAY_CONNECTION_ERRORS, 1);
    sub_19C560();
    return var_28;
}
#endif

#ifdef CODFH_SP
// sp-match: ?sp_sub_12BE30@type_4F3130@@QAEXPAURwCamera@@PAURwV2d@@HPAURwRGBA@@1H2H@Z @ 0x0012BE30
// The HUD's and front end's Live: updates it and draws its texts on the
// camera arg_0 (arg_1C: in the game), then the fade.
void type_4F3130::sp_sub_12BE30(RwCamera *arg_0, RwV2d *arg_4, RwInt32 arg_8, RwRGBA *arg_C,
                                RwV2d *arg_10, RwInt32 arg_14, RwRGBA *arg_18, RwInt32 arg_1C)
{
    if (unk_04 && !sp_dword_3B66AC)
    {
        unk_870 = 1;
        unk_34 = arg_1C;
        unk_30 = arg_0;
        sp_sub_12BC30();
        sp_sub_12B870(arg_0, arg_4, arg_8, arg_C, arg_10, arg_14, arg_18);
        if (sub_19C500())
            sp_sub_12A9C0(arg_0);
    }
}
#endif

#ifdef CODFH_SP
// sp-match: ?sp_sub_12BF20@type_4F3130@@QAEXXZ @ 0x0012BF20
// A feature exited: takes its result (signed in, failed, left; the friends
// list closed, joining a friend's game, or signed out).
void type_4F3130::sp_sub_12BF20()
{
    UIX_EXIT_INFO var_10;

    unk_04->GetExitInfo(&var_10);
    switch (var_10.ExitCode)
    {
    case UIX_EXIT_LOGON_SUCCESSFUL:
        sp_sub_12BD30(&var_10);
        break;
    case UIX_EXIT_LOGON_FAILED:
        sub_19BF20(var_10.hr);
        break;
    case UIX_EXIT_LOGON_USER_EXIT:
        sub_19C2C0(1);
        break;
    case UIX_EXIT_FRIENDS_NORMAL_EXIT:
        sub_19C280();
        sub_19C380(0);
        unk_38 = 0;
        if (!unk_34)
            sub_186E70(0, 0, 0);
        break;
    case UIX_EXIT_FRIENDS_JOIN_GAME:
        sub_19C280();
        sub_19C380(0);
        unk_44 = 2;
        unk_38 = unk_34 ? 4 : 3;
        memcpy(dword_4F45F8->unk_434, var_10.pExitData, 0x56);
        break;
    case UIX_EXIT_FRIENDS_JOIN_GAME_CROSS_TITLE:
        sub_19C280();
        sub_19C380(0);
        unk_44 = 4;
        unk_38 = 0;
        sub_19C6D0(1);
        break;
#ifndef CODFH_WIN32
    case UIX_EXIT_FRIENDS_SIGNED_OUT:
        sub_19C280();
        sub_19C380(0);
        unk_44 = 4;
        if (sp_dword_3EB728.GetXHVEngine())
        {
            unk_04->SetProperty(UIX_PROPERTY_VOICE_MAIL_ENGINE, 0);
            sp_dword_3EB728.Shutdown();
            unk_74C = 0;
        }
        break;
#endif
    }
}
#endif

#ifdef CODFH_SP
// sp-match: ?sp_sub_12C090@type_4F3130@@QAEXXZ @ 0x0012C090
// Its frame (the pad manager's update ends with it): with the account message up
// only button 0x17 (to the dashboard) counts; else the engine runs with the
// player's input while it is drawn, the voice runs, and the engine's flags
// say whether it shows something, wants a reboot, a feature exited or it
// takes the input.
void type_4F3130::sp_sub_12C090()
{
    DWORD var_4;
    RwInt32 var_8;

    if (!unk_04)
        return;
    unk_870 = 0;
    if (unk_75C)
    {
        dword_4B8EA4 = 1;
        if (unk_4B9308.sub_EE9A0(0, 0x17) != 0.0f)
        {
            sp_sub_12AA40();
            for (;;)
                ;
        }
        return;
    }
    if (sp_dword_3B66AC || !unk_2C)
    {
        unk_04->SetInput(sub_19C740(), 0);
        unk_04->ClearInput();
    }
    unk_04->DoWork(&var_4);
    if (sp_dword_3B66AC || !unk_2C)
    {
        unk_04->SetInput(sub_19C740(), 0);
        unk_04->ClearInput();
    }
    unk_2C = 0;
    if (sp_dword_3EB728.GetXHVEngine())
        sp_dword_3EB728.GetXHVEngine()->DoWork();
    if (unk_874)
        sub_19C620();
    if ((var_4 & 1) && dword_4F312C)
        unk_750 = 1;
    else
        unk_750 = 0;
    if (sp_dword_3B66AC)
        unk_750 = 0;
    if (unk_874)
        unk_750 = 0;
    if (var_4 & 4)
    {
        dword_4F4628 = 0;
        if (!unk_34)
        {
            if (unk_20)
                sub_19C280();
            unk_38 = 6;
            unk_4B9308.sp_sub_B6890(0, 0x17);
        }
        else
            unk_04->Reboot(0);
    }
    if (var_4 & 8)
        sp_sub_12BF20();
    var_8 = sub_19C740();
    if (var_4 & 0x10)
    {
        unk_04->SetInput(var_8, &dword_4F4638[unk_4B9308.unk_B48].unk_00);
        unk_868 = 1;
    }
    else
    {
        unk_04->SetInput(var_8, 0);
        unk_868 = 0;
    }
}
#endif

// Functions /OPT:ICF folded into another body (config/aliases.txt), defined here for the
// authentic link (PLAN M7) with that body; the placement link takes the folded one.

// ?PlaySound@type_3E03F8@@UAGJPBD@Z (folded into 0x1C7830)
HRESULT type_3E03F8::PlaySound(RwChar const *dwLocalPort)
{
    return S_OK;
}


#ifdef CODFH_PLAIN
// Plain builds (tools/plainbuild.py): the variables below are a second name for this unit's
// variables' bytes in the image (tools/session/overlapvars.py --aliases); only the placement
// link gives them one storage, so any other link binds them here at the image offset.
// (bound at start-up: the library initialization area runs before every game constructor)
#pragma warning(disable: 4073)
#pragma init_seg(lib)
// 0x004F3168: dword_4F3130 + 0x38
RwInt32 &dword_4F3168 = *(RwInt32 *)((RwUInt8 *)&dword_4F3130 + 0x38);
#endif
