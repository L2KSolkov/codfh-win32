/*
 * The UIX audio plugin and players list items the late service hands the
 * Live engine (game/uixfont.h).
 */
#include <string.h>
#include <stdio.h>

#include "game/uixfont.h"
#include "game/frontend.h"

// Its data definitions (PLAN M5), in the image's address order.
// End of its data definitions.


// Its data (PLAN M5): literals, constants and tables where the image has them.
// match: ??_7type_22AE00@@6B@ @ 0x003EAFEC
// match: ??_C@_05NAOIJFC@Error?$AA@ @ 0x003EAFF8
// match: ??_C@_0N@OFINCEFP@Notification?$AA@ @ 0x003EB000
// match: ??_C@_0O@OOFJAODE@PasscodeEntry?$AA@ @ 0x003EB010
// match: ??_C@_06LLAMGJDN@PressB?$AA@ @ 0x003EB020
// match: ??_C@_06JACBDKPO@PressA?$AA@ @ 0x003EB028
// match: ??_C@_05EPOLMFOG@Popup?$AA@ @ 0x003EB030
// match: ??_C@_0P@EKBKHOBL@MenuItemSelect?$AA@ @ 0x003EB038
// match: ?GetName@type_22AF50@@UBGPBGXZ @ 0x0022AFC0
// match: ?GetXUID@type_22AF50@@UBGPBU_XUID@@XZ @ 0x0022AFD0
// match: ?sub_22B040@type_3E3884@@QAEHH@Z @ 0x0022B040
// match: ?sub_22B0C0@type_3E3884@@QAEHH@Z @ 0x0022B0C0
// match: ?GetVoiceStatus@type_22AF50@@UBG?AW4_UIX_VOICE_STATUS_TYPE@@XZ @ 0x0022AFE0
// match: ?IsTalking@type_22AF50@@UBGHXZ @ 0x0022B130
// match: ?GetBitflags@type_22AF50@@UBGKXZ @ 0x0022B160
// match: ?Compare@type_22AF50@@UBGHPBUITitlePlayersListItem@@@Z @ 0x0022B170

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


CONST WCHAR *type_22AF50::GetName() CONST
{
    return unk_10;
}

CONST XUID *type_22AF50::GetXUID() CONST
{
    return &unk_04;
}


UIX_VOICE_STATUS_TYPE type_22AF50::GetVoiceStatus() CONST
{
    if (get_dword_4F8180()->unk_3060.sub_22B040(unk_4C))
        return (UIX_VOICE_STATUS_TYPE)0;
    if (get_dword_4F8180()->unk_3060.sub_22B0C0(unk_4C))
        return (UIX_VOICE_STATUS_TYPE)1;
    return (UIX_VOICE_STATUS_TYPE)2;
}

BOOL type_22AF50::IsTalking() CONST
{
    return get_dword_4F8180()->unk_3060.sub_1C7E30(unk_4C);
}

DWORD type_22AF50::GetBitflags() CONST
{
    return unk_44;
}

INT type_22AF50::Compare(CONST ITitlePlayersListItem *arg_0) CONST
{
    const type_22AF50 *var_4 = (const type_22AF50 *)arg_0;

    if (unk_4C < var_4->unk_4C)
        return 1;
    if (unk_4C == var_4->unk_4C)
        return 0;
    return -1;
}

// Functions /OPT:ICF folded into another body (config/aliases.txt), defined here for the
// authentic link (PLAN M7) with that body; the placement link takes the folded one.

// ?DoWork@type_22AE00@@UAGJXZ (folded into 0x19C820)
HRESULT type_22AE00::DoWork()
{
    return 0;
}

// ?Release@type_22AE00@@UAGKXZ (folded into 0x19C830)
ULONG type_22AE00::Release()
{
    unk_04 = unk_04 - 1;
    return unk_04;
}
