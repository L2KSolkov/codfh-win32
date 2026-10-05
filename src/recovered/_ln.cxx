/*
 * The UIX audio plugin and players list items the late service hands the
 * Live engine (game/uixfont.h).
 */
#include <string.h>
#include <stdio.h>

#include "game/uixfont.h"
#include "game/frontend.h"

// match: ??0type_22AE00@@QAE@XZ @ 0x0022AE00
type_22AE00::type_22AE00()
{
}

// match: ??1type_22AE00@@QAE@XZ @ 0x0022AE20
type_22AE00::~type_22AE00()
{
}

// match: ?PlaySound@type_22AE00@@UAGJPBD@Z @ 0x0022AE40
HRESULT type_22AE00::PlaySound(LPCSTR arg_0)
{
    RwInt32 var_4 = -1;

    if (!strcmp(arg_0, "MenuItemSelect"))
        var_4 = 1;
    if (!strcmp(arg_0, "Popup"))
        var_4 = 0;
    if (!strcmp(arg_0, "PressA"))
        var_4 = 2;
    if (!strcmp(arg_0, "PressB"))
        var_4 = 2;
    if (!strcmp(arg_0, "PasscodeEntry"))
        var_4 = 1;
    if (!strcmp(arg_0, "Notification"))
        var_4 = 1;
    if (!strcmp(arg_0, "Error"))
        var_4 = 1;
    if (var_4 == -1)
        var_4 = 1;
    if (dword_504378)
        dword_504378->vf_04(var_4);
    return 0;
}

// match: ??0type_22AF50@@QAE@IU_XUID@@PBDH@Z @ 0x0022AF50
type_22AF50::type_22AF50(RwUInt32 arg_0, XUID arg_4, const RwChar *arg_10, RwInt32 arg_14)
{
    unk_04 = arg_4;
    unk_48 = arg_14;
    _snwprintf(unk_10, 0x1A, L"%S", arg_10);
    unk_10[0x19] = 0;
    unk_44 = 1;
    unk_4C = arg_0;
}

// match: ?GetName@type_22AF50@@UBGPBGXZ @ 0x0022AFC0
CONST WCHAR *type_22AF50::GetName() CONST
{
    return unk_10;
}

// match: ?GetXUID@type_22AF50@@UBGPBU_XUID@@XZ @ 0x0022AFD0
CONST XUID *type_22AF50::GetXUID() CONST
{
    return &unk_04;
}

// match: ?GetVoiceStatus@type_22AF50@@UBG?AW4_UIX_VOICE_STATUS_TYPE@@XZ @ 0x0022AFE0
UIX_VOICE_STATUS_TYPE type_22AF50::GetVoiceStatus() CONST
{
    if (get_dword_4F8180()->unk_3060.sub_22B040(unk_4C))
        return (UIX_VOICE_STATUS_TYPE)0;
    if (get_dword_4F8180()->unk_3060.sub_22B0C0(unk_4C))
        return (UIX_VOICE_STATUS_TYPE)1;
    return (UIX_VOICE_STATUS_TYPE)2;
}

// match: ?sub_22B040@type_3E3884@@QAEHH@Z @ 0x0022B040
// match: ?sub_22B0C0@type_3E3884@@QAEHH@Z @ 0x0022B0C0

// match: ?IsTalking@type_22AF50@@UBGHXZ @ 0x0022B130
BOOL type_22AF50::IsTalking() CONST
{
    return get_dword_4F8180()->unk_3060.sub_1C7E30(unk_4C);
}

// match: ?GetBitflags@type_22AF50@@UBGKXZ @ 0x0022B160
DWORD type_22AF50::GetBitflags() CONST
{
    return unk_44;
}

// match: ?Compare@type_22AF50@@UBGHPBUITitlePlayersListItem@@@Z @ 0x0022B170
INT type_22AF50::Compare(CONST ITitlePlayersListItem *arg_0) CONST
{
    const type_22AF50 *var_4 = (const type_22AF50 *)arg_0;

    if (unk_4C < var_4->unk_4C)
        return 1;
    if (unk_4C == var_4->unk_4C)
        return 0;
    return -1;
}
