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
// End of its data definitions.


// The manager itself, built by its dynamic initializer and destroyed at exit.
type_4F3130 dword_4F3130;

// Vtables (.rdata, PLAN M5): each in its own placement range (config/splits.txt).
// match: ?flt_3E03F0@@3MB @ 0x003E03F0
// match: __real@3ee66666 @ 0x003E03F4
// match: ??_7type_3E03F8@@6B@ @ 0x003E03F8
// match: ??_7type_3E0404@@6B@ @ 0x003E0404
// match: ??_7type_4F3130@@6B@ @ 0x003E0418
// match: _$E2 @ 0x0030C0F0
// match: _$E3 @ 0x0030EA10
// match: .CRT$XCU+0 @ 0x0042719C

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
HRESULT type_4F3130::sub_19C280()
{
    HRESULT var_4;

    var_4 = unk_04->EndFeature();
    unk_20 = 0;
    unk_28 = 0;
    return var_4;
}

// match: ?sub_19C2C0@type_4F3130@@QAEXH@Z @ 0x0019C2C0
// Ends the feature and resumes (arg_0: signed out).
void type_4F3130::sub_19C2C0(RwInt32 arg_0)
{
    sub_19C280();
    unk_38 = 0;
    sub_19C380(0);
    if (arg_0)
        unk_764 = 4;
    sub_19C6D0(0);
}

// match: ?sub_19C310@type_4F3130@@QAEXXZ @ 0x0019C310
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
}

// match: ?sub_19C380@type_4F3130@@QAEXM@Z @ 0x0019C380
void type_4F3130::sub_19C380(RwReal arg_0)
{
    unk_758 = arg_0;
}

// match: ?sub_19C3A0@type_4F3130@@QAEXXZ @ 0x0019C3A0
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
// Signs out.
void type_4F3130::sub_19C4D0()
{
    dword_4B88AC = 0;
    sub_187040();
    sub_19C2C0(1);
}

// match: ?sub_19C500@type_4F3130@@QAEHXZ @ 0x0019C500
// Whether it is online or appears offline.
RwInt32 type_4F3130::sub_19C500()
{
    if (unk_764 == 2 || unk_764 == 3)
        return 1;
    return 0;
}

// match: ?sub_19C530@type_4F3130@@QAEXXZ @ 0x0019C530
void type_4F3130::sub_19C530()
{
    unk_764 = 3;
    sub_19C590(0);
}

// match: ?sub_19C560@type_4F3130@@QAEXXZ @ 0x0019C560
void type_4F3130::sub_19C560()
{
    unk_764 = 2;
    sub_19C590(1);
}

// match: ?sub_19C590@type_4F3130@@QAEJH@Z @ 0x0019C590
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
    if (arg_0)
        l4 |= 1;
    memset(&ebp_10, 0, 8);
    var_18 = unk_04->NotificationSetState(var_14, l4, ebp_10, 0, 0);
    return var_18;
}

// match: ?sub_19C620@type_4F3130@@QAEHXZ @ 0x0019C620
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

// match: ?sub_19C740@type_4F3130@@QAEHXZ @ 0x0019C740
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
ULONG type_3E03F8::Release()
{
    unk_04 = unk_04 - 1;
    return unk_04;
}

// match: ??0type_4F3130@@QAE@XZ @ 0x0019C850
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
HRESULT type_4F3130::vf_000(DWORD arg_0, DWORD arg_4, DWORD arg_8)
{
    return E_NOTIMPL;
}

// match: ?vf_004@type_4F3130@@UAGJKK@Z @ 0x0019C980
HRESULT type_4F3130::vf_004(DWORD arg_0, DWORD arg_4)
{
    return E_NOTIMPL;
}

HRESULT type_4F3130::vf_008(DWORD arg_0, DWORD arg_4, DWORD arg_8)
{
    return E_NOTIMPL;
}

HRESULT type_4F3130::vf_00C(DWORD arg_0, DWORD arg_4, DWORD arg_8, DWORD arg_C)
{
    return E_NOTIMPL;
}

HRESULT type_4F3130::vf_010(DWORD arg_0, DWORD arg_4, DWORD arg_8)
{
    return E_NOTIMPL;
}

// match: ?vf_014@type_4F3130@@UAGJK@Z @ 0x0019C990
HRESULT type_4F3130::vf_014(DWORD arg_0)
{
    return E_NOTIMPL;
}

// match: ?Release@type_3E0404@@UAGKXZ @ 0x0019C9A0
ULONG type_3E0404::Release()
{
    delete this;
    return 0;
}

// match: ?DrawText@type_3E0404@@UAGJPBGKKK@Z @ 0x0019CA10
HRESULT type_3E0404::DrawText(LPCWSTR arg_0, DWORD arg_4, DWORD arg_8, DWORD arg_C)
{
    return unk_04->TextOut(dword_4F312C, arg_0, -1, arg_4, arg_8);
}

// match: ?GetTextSize@type_3E0404@@UAGJPBGPAK1@Z @ 0x0019CA50
HRESULT type_3E0404::GetTextSize(LPCWSTR arg_0, DWORD *arg_4, DWORD *arg_8)
{
    *arg_8 = unk_04->GetTextHeight();
    return unk_04->GetTextExtent(arg_0, -1, (RwUInt32 *)arg_4);
}

// match: ?SetColor@type_3E0404@@UAGJK@Z @ 0x0019CA90
HRESULT type_3E0404::SetColor(D3DCOLOR arg_0)
{
    unk_04->SetTextColor(arg_0);
    return 0;
}

// match: ?SetHeight@type_3E0404@@UAGJK@Z @ 0x0019CAC0
HRESULT type_3E0404::SetHeight(DWORD arg_0)
{
    return unk_04->SetTextHeight(arg_0);
}

// match: ??1type_4F3130@@QAE@XZ @ 0x0019CAE0
// (Implicit: it destroys the font renderer only, without storing the
// manager's vtable again, as a declared destructor would.)

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
