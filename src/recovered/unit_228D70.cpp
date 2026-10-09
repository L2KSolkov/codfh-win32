/*
 * The UI plugin the late service hands the Live engine (game/uixfont.h):
 * its objects (textboxes, listboxes and backgrounds) drawn with the Live
 * engine's font renderer and the skin's images.
 */
#include "game/liveservice.h"
#include <string.h>
#include <math.h>

#include "game/uixfont.h"
#include "game/kujuui.h"
#include "game/startup.h"
#include "game/fileio.h"
#include "rw/rwxbox.h"

using namespace kujuUI;

// Its data (PLAN M5): literals, constants and tables where the image has them.
// match: ??_C@_0CO@IPDFKNOL@CUITextBoxObject?3?5Failed?5to?5get?5@ @ 0x003EAEAC
// match: ??_C@_13HOIJIPNN@?$AA?5?$AA?$AA@ @ 0x003EAEDC
// match: ??_7type_229A90@@6B@ @ 0x003EAEE0
// match: ??_7CUITextBoxObject@@6B@ @ 0x003EAF04
// match: ??_7type_22A630@@6B@ @ 0x003EAF28
// match: ??_C@_0DP@NKLKHGHG@Failed?5to?5find?5UIX?5resource?5ID?5?$CF@ @ 0x003EAF64
// match: ??_7type_229930@@6B@ @ 0x003EAFA4
// match: ??_7type_228D70@@6B@ @ 0x003EAFC8
// match: __ehhandler$?sub_22A460@type_229A90@@QAEXPAUD3DTexture@@MMMM@Z>1>8 @ 0x0042608C
// match: __ehhandler$?sub_22A460@type_229A90@@QAEXPAUD3DTexture@@MMMM@Z>1 @ 0x00426094

// match: ?vf_000@type_228D70@@UAEJXZ @ 0x00228D70

HRESULT type_228D70::vf_000()
{
    unk_04 = UIX_OBJECT_BACKGROUND;
    unk_1C = 0;
    if (unk_10->ImageOffset != -1)
    {
        if (FAILED(unk_0C->unk_19C->GetScreenImage(unk_14, unk_10->ImageOffset, &unk_1C)))
            return E_FAIL;
    }
    return 0;
}

// match: ?vf_01C@type_228D70@@UAEJMM@Z @ 0x00228DF0
HRESULT type_228D70::vf_01C(RwReal arg_0, RwReal arg_4)
{
    RwReal l8 = unk_10->Width;
    RwReal var_4 = unk_10->Height;

    sub_22A460(unk_1C, arg_0, arg_4, l8, var_4);
    return 0;
}

// match: ?vf_000@CUITextBoxObject@@UAEJXZ @ 0x00228E50
HRESULT CUITextBoxObject::vf_000()
{
    unk_04 = UIX_OBJECT_TEXTBOX;
    unk_1C = 0;
    unk_20 = 0;
    unk_24 = 0;
    unk_28 = 0;
    unk_2C = 0;
    unk_30 = 0;
    return 0;
}

// match: ?vf_004@CUITextBoxObject@@UAEXXZ @ 0x00228EB0
void CUITextBoxObject::vf_004()
{
    if (unk_30)
        delete unk_30;
    if (unk_28)
        delete unk_28;
    unk_30 = 0;
    unk_28 = 0;
    unk_2C = 0;
}

// match: ?vf_010@CUITextBoxObject@@UAEJKW4_UIX_OBJSTATE_TYPE@@K@Z @ 0x00228F20
HRESULT CUITextBoxObject::vf_010(DWORD arg_0, UIX_OBJSTATE_TYPE arg_4, DWORD arg_8)
{
    switch (arg_4)
    {
    case UIX_OBJSTATE_WORD_WRAP:
        unk_24 = 1;
        break;
    default:
        return E_NOTIMPL;
    }
    return 0;
}

// match: ?vf_020@CUITextBoxObject@@UAEJKPBGKPBU_UIX_SKIN_ICON_INFO@@@Z @ 0x00228F60
HRESULT CUITextBoxObject::vf_020(DWORD arg_0, LPCWSTR arg_4, DWORD arg_8, const UIX_SKIN_ICON_INFO *arg_C)
{
    DWORD var_4 = unk_2C;

    unk_2C = arg_8;
    if (unk_2C)
    {
        // A compiled-out check (it shifts the registers).
        if (!unk_28)
        {
        }
        if (var_4 != unk_2C)
        {
            delete unk_28;
            unk_28 = new type_229170_icon[unk_2C];
        }
        for (DWORD var_8 = 0; var_8 < unk_2C; var_8++)
        {
            D3DSURFACE_DESC var_24;

            if (FAILED(unk_0C->unk_19C->GetImage(arg_C[var_8].IconResID, &unk_28[var_8].unk_00)))
            {
                if (0)
                    sub_1C8A30("CUITextBoxObject: Failed to get icon texture\n");
            }
            unk_28[var_8].unk_00->GetLevelDesc(0, &var_24);
            unk_28[var_8].unk_04 = (RwReal)var_24.Width;
            unk_28[var_8].unk_08 = (RwReal)var_24.Width;
            unk_28[var_8].unk_0C = arg_C[var_8].InsertPosInText;
            unk_28[var_8].unk_10 = arg_C[var_8].Flags;
        }
    }
    else
    {
        // A compiled-out check (it shifts the registers).
        if (!unk_28)
        {
        }
        delete unk_28;
        unk_28 = 0;
    }
    if (arg_4)
    {
        delete unk_30;
        unk_30 = new WCHAR[wcslen(arg_4) + 1];
        wcscpy(unk_30, arg_4);
        if (unk_24)
            sub_22A250();
    }
    return 0;
}

// match: ?vf_01C@CUITextBoxObject@@UAEJMM@Z @ 0x00229170
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
HRESULT CUITextBoxObject::vf_01C(RwReal arg_0, RwReal arg_4)
{
    RwUInt32 r34;
    RwReal lv_30;
    RwReal fp_2C;
    RwUInt32 q28;
    const WCHAR *frm_24;
    RwReal t20;
    DWORD l1C;
    RwInt32 m_18;
    RwUInt32 ebp_14;
    D3DCOLOR lv_10;
    type_225220 *slot_C;
    RwUInt32 bp_8;
    RwReal bp_4;

    slot_C = unk_0C->unk_198;
    bp_4 = 4.0f;

    if (!unk_30)
        return 1;
    if (unk_1C)
        lv_10 = unk_10->DisabledTextColor;
    else if (unk_20)
        lv_10 = unk_10->HighlightedTextColor;
    else
        lv_10 = unk_10->TextColor;
    t20 = arg_0 + bp_4;
    fp_2C = arg_4;
    m_18 = 0;
    if (!unk_2C)
    {
        RwReal lcl_38 = 0;

        if (unk_10->Flags & 2)
        {
            t20 = arg_0 - unk_10->XOffset + unk_10->Width - unk_10->XOffset;
            m_18 = 2;
        }
        if (unk_10->Flags & 1)
        {
            t20 = arg_0 - unk_10->XOffset + unk_10->Width / 2.0f;
            m_18 = 1;
        }
        slot_C->sub_225A10(m_18);
        slot_C->SetColor(lv_10);
        slot_C->SetHeight(unk_10->FontHeight);
        slot_C->DrawText(unk_30, (RwInt32)t20, (RwInt32)fp_2C, (RwInt32)(640.0f - t20));
    }
    else
    {
        DWORD loc50;
        DWORD x4C;
        RwReal w48;
        RwReal loc44;
        WCHAR *fp_40;
        DWORD ebp_3C;

        w48 = 0;
        if (unk_28->unk_08 > slot_C->sub_225B60())
            w48 = (unk_28->unk_08 - slot_C->sub_225B60()) / 2.0f;
        loc44 = (RwReal)slot_C->sub_225AD0(L" ", -1);
        loc50 = 0;

        for (DWORD l54 = 0; l54 < unk_2C; l54++)
        {
            if (unk_28[l54].unk_10 != 2)
                loc50 += (RwInt32)(RwReal)ceil(unk_28[l54].unk_04 / loc44);
        }
        fp_40 = new WCHAR[wcslen(unk_30) + loc50 + 1];

        if (*unk_30)
            sub_227560()->set_unk_1120(true);
        ebp_3C = 0;
        x4C = 0;

        for (DWORD slot_58 = 0; slot_58 < unk_2C; slot_58++)
        {
            if (unk_28[slot_58].unk_10 != 2)
            {
                DWORD stk_60;
                DWORD y5C = (RwInt32)(RwReal)ceil(unk_28[slot_58].unk_04 / loc44);

                stk_60 = unk_28[slot_58].unk_0C - x4C;

                wcsncpy(&fp_40[ebp_3C], &unk_30[x4C], stk_60);
                ebp_3C += stk_60;
                x4C += stk_60;
                for (DWORD var_64 = 0; var_64 < y5C; var_64++)
                    fp_40[ebp_3C++] = ' ';
                fp_40[ebp_3C] = 0;
            }
        }
        wcscpy(&fp_40[ebp_3C], &unk_30[x4C]);
        bp_8 = slot_C->sub_225AD0(fp_40, -1);

        if (unk_10->Flags & 1)
            t20 = arg_0 + (RwReal)((unk_10->Width - bp_8) >> 1);
        else if (unk_10->Flags & 2)
            t20 = arg_0 + unk_10->Width - unk_10->XOffset - (RwReal)bp_8;
        slot_C->sub_225A10(m_18);
        slot_C->SetColor(lv_10);
        slot_C->SetHeight(unk_10->FontHeight);
        slot_C->DrawText(fp_40, (RwInt32)t20, (RwInt32)(fp_2C + w48), (RwInt32)(640.0f - t20));
        delete fp_40;
        lv_30 = unk_10->Width + arg_0;
        frm_24 = unk_30;
        l1C = 0;

        for (DWORD q68 = 0; q68 < unk_2C; q68++)
        {
            if (unk_28[q68].unk_10 == 1)
            {
                if (r34 = unk_28[q68].unk_0C - l1C)
                    slot_C->sub_225A30(frm_24, &ebp_14, &q28, r34);
                else
                {
                    ebp_14 = 0;
                    q28 = 0;
                }
                frm_24 += r34;
                t20 += (RwReal)ebp_14;
                sub_22A460(unk_28[q68].unk_00, t20, fp_2C, unk_28[q68].unk_04, unk_28[q68].unk_08);
                t20 += unk_28[q68].unk_04;
            }
            else
                lv_30 -= unk_28[q68].unk_04;
        }
        for (DWORD m_6C = 0; m_6C < unk_2C; m_6C++)
        {
            if (unk_28[m_6C].unk_10 == 2)
            {
                sub_22A460(unk_28[m_6C].unk_00, lv_30, fp_2C, unk_28[m_6C].unk_04, unk_28[m_6C].unk_08);
                lv_30 += unk_28[m_6C].unk_04;
            }
        }
    }
    return 0;
}

// match: ?vf_000@type_229930@@UAEJXZ @ 0x00229930
HRESULT type_229930::vf_000()
{
    unk_04 = UIX_OBJECT_LISTBOX;
    unk_1C = 0;
    unk_20 = 0;
    unk_24 = unk_10->CustomParam ? unk_10->CustomParam : 5;
    unk_1BC = 0;
    memset(unk_2C, 0, sizeof(unk_2C));
    return 0;
}

// match: ?vf_004@type_229930@@UAEXXZ @ 0x002299B0
void type_229930::vf_004()
{
    if (unk_1BC > 0)
        sub_2299D0();
}

// match: ?sub_2299D0@type_229930@@QAEXXZ @ 0x002299D0
void type_229930::sub_2299D0()
{
    for (DWORD var_4 = 0; var_4 < unk_1BC; var_4++)
    {
        unk_2C[var_4]->vf_004();
        delete unk_2C[var_4];
    }
    memset(unk_2C, 0, sizeof(unk_2C));
    unk_1BC = 0;
}

// The textbox's destructor (the compiler's), out of line for the listbox's
// items.
// match: ??1CUITextBoxObject@@QAE@XZ @ 0x00229A90

// match: ?vf_000@type_229A90@@UAEJXZ @ 0x00229AB0
HRESULT type_229A90::vf_000()
{
    return E_NOTIMPL;
}

void type_229A90::vf_004()
{
}

HRESULT type_229A90::vf_008(UIX_INPUT_TYPE arg_0)
{
    return 1;
}

// match: ?vf_00C@type_229A90@@UAEJKW4_UIX_OBJSTATE_TYPE@@PAK@Z @ 0x00229AC0
HRESULT type_229A90::vf_00C(DWORD arg_0, UIX_OBJSTATE_TYPE arg_4, DWORD *arg_8)
{
    return E_NOTIMPL;
}

// sp-match: ?vf_010@type_229A90@@UAEJKW4_UIX_OBJSTATE_TYPE@@K@Z @ 0x0012AF00
HRESULT type_229A90::vf_010(DWORD arg_0, UIX_OBJSTATE_TYPE arg_4, DWORD arg_8)
{
    return E_NOTIMPL;
}

// match: ?vf_014@type_229A90@@UAEJH@Z @ 0x00229AE0
HRESULT type_229A90::vf_014(BOOL arg_0)
{
    return E_NOTIMPL;
}

// match: ?vf_018@type_229A90@@UAEJKPAK@Z @ 0x00229B00
HRESULT type_229A90::vf_018(DWORD arg_0, DWORD *arg_4)
{
    return E_NOTIMPL;
}

// match: ?vf_020@type_229A90@@UAEJKPBGKPBU_UIX_SKIN_ICON_INFO@@@Z @ 0x00229B20
HRESULT type_229A90::vf_020(DWORD arg_0, LPCWSTR arg_4, DWORD arg_8, const UIX_SKIN_ICON_INFO *arg_C)
{
    return E_NOTIMPL;
}

// match: ?vf_018@type_229930@@UAEJKPAK@Z @ 0x00229B40
HRESULT type_229930::vf_018(DWORD arg_0, DWORD *arg_4)
{
    HRESULT var_4;

    if (arg_0 >= unk_1BC || arg_0 == -1)
        arg_0 = unk_1BC;
    unk_2C[arg_0] = new CUITextBoxObject;
    unk_2C[arg_0]->unk_0C = unk_0C;
    unk_2C[arg_0]->unk_10 = unk_10;
    var_4 = unk_2C[arg_0]->vf_000();
    if (FAILED(var_4))
    {
        unk_2C[arg_0]->vf_004();
        delete (type_229A90 *)unk_2C[arg_0];
        unk_2C[arg_0] = 0;
        return var_4;
    }
    unk_1BC++;
    if (arg_4)
        *arg_4 = arg_0;
    return 0;
}

// match: ?vf_014@type_229930@@UAEJH@Z @ 0x00229CA0
HRESULT type_229930::vf_014(BOOL arg_0)
{
    sub_2299D0();
    if (arg_0)
    {
        unk_1C = 0;
        unk_20 = 0;
    }
    return 0;
}

// match: ?vf_010@type_229930@@UAEJKW4_UIX_OBJSTATE_TYPE@@K@Z @ 0x00229CE0
HRESULT type_229930::vf_010(DWORD arg_0, UIX_OBJSTATE_TYPE arg_4, DWORD arg_8)
{
    switch (arg_4)
    {
    case UIX_OBJSTATE_LIST_SELECTION_INDEX:
        if (arg_8 && arg_8 >= unk_1BC)
            return E_INVALIDARG;
        unk_1C = arg_8;
        if (unk_1C < unk_20)
            unk_20 = unk_1C;
        if (unk_1C >= unk_20 + unk_24)
            unk_20 = unk_1C - (unk_24 - 1);
        break;
    case UIX_OBJSTATE_LIST_ITEM_GREYED:
        if (arg_0 >= unk_1BC)
            return E_INVALIDARG;
        unk_2C[arg_0]->unk_1C = arg_8;
        break;
    case UIX_OBJSTATE_LIST_ITEM_HIGHLIGHTED:
        if (arg_0 >= unk_1BC)
            return E_INVALIDARG;
        unk_2C[arg_0]->unk_20 = arg_8;
        break;
    default:
        return E_NOTIMPL;
    }
    return 0;
}

// match: ?vf_00C@type_229930@@UAEJKW4_UIX_OBJSTATE_TYPE@@PAK@Z @ 0x00229DE0
HRESULT type_229930::vf_00C(DWORD arg_0, UIX_OBJSTATE_TYPE arg_4, DWORD *arg_8)
{
    switch (arg_4)
    {
    case UIX_OBJSTATE_LIST_SELECTION_INDEX:
        *arg_8 = unk_1C;
        break;
    case UIX_OBJSTATE_LIST_ITEM_GREYED:
        if (arg_0 >= unk_1BC)
            return E_INVALIDARG;
        *arg_8 = unk_2C[arg_0]->unk_1C;
        break;
    case UIX_OBJSTATE_LIST_ITEM_HIGHLIGHTED:
        if (arg_0 >= unk_1BC)
            return E_INVALIDARG;
        *arg_8 = unk_2C[arg_0]->unk_20;
        break;
    default:
        return E_NOTIMPL;
    }
    return 0;
}

// match: ?vf_020@type_229930@@UAEJKPBGKPBU_UIX_SKIN_ICON_INFO@@@Z @ 0x00229E80
HRESULT type_229930::vf_020(DWORD arg_0, LPCWSTR arg_4, DWORD arg_8, const UIX_SKIN_ICON_INFO *arg_C)
{
    if (arg_0 >= unk_1BC)
        return E_INVALIDARG;
    unk_2C[arg_0]->vf_020(arg_0, arg_4, arg_8, arg_C);
    return 0;
}

// match: ?vf_008@type_229930@@UAEJW4_UIX_INPUT_TYPE@@@Z @ 0x00229ED0
HRESULT type_229930::vf_008(UIX_INPUT_TYPE arg_0)
{
    switch (arg_0)
    {
    case UIX_INPUT_UP:
    case UIX_INPUT_DPAD_UP:
        if (unk_1C > 0)
        {
            unk_1C--;
            if (unk_1C < unk_20)
                unk_20 = unk_1C;
            return 0;
        }
        break;
    case UIX_INPUT_DOWN:
    case UIX_INPUT_DPAD_DOWN:
        if (unk_1C + 1 < unk_1BC)
        {
            unk_1C++;
            if (unk_1C > unk_20 + unk_24 - 1)
                unk_20++;
            return 0;
        }
        break;
    }
    return 1;
}

// match: ?vf_01C@type_229930@@UAEJMM@Z @ 0x00229FB0
HRESULT type_229930::vf_01C(RwReal arg_0, RwReal arg_4)
{
    RwReal l4;
    DWORD var_8;
    DWORD lv_C;
    RwReal var_10;

    if (!unk_1BC)
        return 1;
    lv_C = unk_10->Height;
    lv_C -= unk_0C->unk_1A0.unk_08;
    lv_C -= unk_0C->unk_1AC.unk_08;
    var_10 = (RwReal)lv_C / (RwReal)unk_24;
    var_8 = unk_1BC - 1;
    l4 = arg_4;
    if (unk_20)
        sub_22A460(unk_0C->unk_1A0.unk_00, arg_0 + (RwReal)((unk_10->Width - unk_0C->unk_1A0.unk_04) >> 1), l4,
                   (RwReal)unk_0C->unk_1A0.unk_04, (RwReal)unk_0C->unk_1A0.unk_08);
    l4 += (RwReal)unk_0C->unk_1A0.unk_08;
    for (DWORD var_14 = 0; var_14 < unk_24; var_14++)
    {
        CUITextBoxObject *var_18 = unk_2C[unk_20 + var_14];

        if (unk_20 + var_14 == unk_1C)
            sub_22A460(unk_0C->unk_1B8.unk_00, arg_0, l4, (RwReal)unk_10->Width, var_10);
        var_18->vf_01C(arg_0 + unk_10->XOffset, l4 + unk_10->YOffset);
        l4 += var_10;
        if (unk_20 + var_14 >= var_8)
            return 0;
    }
    sub_22A460(unk_0C->unk_1AC.unk_00, arg_0 + (RwReal)((unk_10->Width - unk_0C->unk_1AC.unk_04) >> 1), l4,
               (RwReal)unk_0C->unk_1AC.unk_04, (RwReal)unk_0C->unk_1AC.unk_08);
    return 0;
}

// match: ?sub_22A250@CUITextBoxObject@@QAEXXZ @ 0x0022A250
void CUITextBoxObject::sub_22A250()
{
    RwReal var_C = (RwReal)unk_10->FontHeight / unk_0C->unk_198->sub_225B60();
    WCHAR *bp_8 = unk_30;
    WCHAR *bp_4 = bp_8;

    while (*bp_8)
    {
        while (*bp_8 == ' ' || *bp_8 == '\n')
        {
            if (*bp_8 == '\n')
            {
                bp_8++;
                bp_4 = bp_8;
            }
            else
                bp_8++;
        }
        DWORD var_1C;

        unk_0C->unk_19C->GetWordLength(bp_8, &var_1C);
        if (bp_8[var_1C - 1] == ' ')
            var_1C--;
        WCHAR lv_10 = bp_8[var_1C];
        RwUInt32 var_14;
        RwUInt32 var_18;

        bp_8[var_1C] = 0;
        unk_0C->unk_198->sub_225A30(bp_4, &var_14, &var_18, -1);
        bp_8[var_1C] = lv_10;
        if ((RwReal)var_14 > (RwReal)(unk_10->Width - unk_10->XOffset))
        {
            WCHAR *var_20 = new WCHAR[wcslen(unk_30) + 2];
            DWORD var_24 = bp_8 - unk_30;

            wcsncpy(var_20, unk_30, var_24);
            var_20[var_24] = '\n';
            wcscpy(&var_20[var_24 + 1], &unk_30[var_24]);
            bp_8 = &var_20[var_24 + 1];
            bp_4 = bp_8;
            delete unk_30;
            unk_30 = var_20;
        }
        else
            bp_8 += var_1C;
    }
}

// match: ?sub_22A460@type_229A90@@QAEXPAUD3DTexture@@MMMM@Z @ 0x0022A460
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void type_229A90::sub_22A460(IDirect3DTexture8 *arg_0, RwReal arg_4, RwReal arg_8, RwReal arg_C, RwReal arg_10)
{
    RwRaster *lcl_FC;
    RwRaster *uF8;
    RwReal locF4;
    RwReal ebp_F0;
    IDirect3DTexture8 **yEC;
    type_1E0330_rect ebp_E8;
    IDirect3DTexture8 *lD8;
    type_1EEAD0 lcl_D4;
    type_1E0330_rect t20;
    RwUInt32 lv_10;

    lcl_FC = sub_1EF040();
    ebp_F0 = arg_0 && arg_0->Size ? arg_C : 1.0f;
    locF4 = arg_0 && arg_0->Size ? arg_10 : 1.0f;
    t20.unk_00 = arg_4;
    t20.unk_04 = arg_8;
    t20.unk_08 = arg_4 + arg_C;
    t20.unk_0C = arg_8 + arg_10;
    ebp_E8.unk_00 = 0;
    ebp_E8.unk_04 = 0;
    ebp_E8.unk_08 = ebp_F0;
    ebp_E8.unk_0C = locF4;
    RwRenderStateGet(rwRENDERSTATETEXTURERASTER, &uF8);
    yEC = (IDirect3DTexture8 **)RASTEREXTFROMRASTER(lcl_FC);
    lD8 = *yEC;
    *yEC = arg_0;
    RwRenderStateSet(rwRENDERSTATETEXTURERASTER, lcl_FC);
    lv_10 = arg_0 ? 0xFFFFFFFF : 0x80808080;
    lcl_D4.sub_1EEC20(&t20, 1.0f, 1.0f, &ebp_E8, lv_10);
    lcl_D4.sub_1EEB60();
    *yEC = lD8;
    RwRenderStateSet(rwRENDERSTATETEXTURERASTER, uF8);
}

// match: ??0type_22A630@@QAE@XZ @ 0x0022A630
type_22A630::type_22A630()
{
    memset(unk_08, 0, 0x190);
}

// match: ??1type_22A630@@QAE@XZ @ 0x0022A660
type_22A630::~type_22A630()
{
    delete unk_198;
}

// match: ?sub_22A6C0@type_22A630@@QAEJPAUtype_225220@@@Z @ 0x0022A6C0
HRESULT type_22A630::sub_22A6C0(type_225220 *arg_0)
{
    unk_198 = arg_0;
    unk_04++;
    return 0;
}

// match: ?sub_22A6F0@type_22A630@@QAEJKPAUtype_22A6F0_image@@@Z @ 0x0022A6F0
HRESULT type_22A630::sub_22A6F0(DWORD arg_0, type_22A6F0_image *arg_4)
{
    D3DSURFACE_DESC var_1C;

    if (FAILED(unk_19C->GetImage(arg_0, &arg_4->unk_00)))
    {
        arg_4->unk_00 = 0;
        if (0)
            sub_1C8A30("Failed to find UIX resource ID %d - check skin is up-to-date.\n", arg_0);
        return E_FAIL;
    }
    arg_4->unk_00->GetLevelDesc(0, &var_1C);
    arg_4->unk_04 = var_1C.Width;
    arg_4->unk_08 = var_1C.Height;
    return 0;
}

// match: ?Release@type_22A630@@UAGKXZ @ 0x0022A770
ULONG type_22A630::Release()
{
    unk_04--;
    if (unk_04 > 0)
        return unk_04;
    delete this;
    return 0;
}

// match: ?SetPluginSupport@type_22A630@@UAGJPAUPluginSupport@@@Z @ 0x0022A7E0
HRESULT type_22A630::SetPluginSupport(IPluginSupport *arg_0)
{
    unk_19C = arg_0;
    sub_22A6F0(0x1C, &unk_1A0);
    sub_22A6F0(0x1D, &unk_1AC);
    sub_22A6F0(0x1E, &unk_1B8);
    return 0;
}

// match: ?CreateObject@type_22A630@@UAGJW4_UIX_OBJECT_TYPE@@KKKPAK@Z @ 0x0022A830
HRESULT type_22A630::CreateObject(UIX_OBJECT_TYPE arg_0, DWORD arg_4, DWORD arg_8, DWORD arg_C, DWORD *arg_10)
{
    UIX_SKIN_LAYOUT_INFO *l4;
    type_229A90 *var_8;
    HRESULT lv_C;
    DWORD var_10;

    lv_C = unk_19C->GetLayout(arg_8, arg_C, &l4);
    if (FAILED(lv_C))
        return lv_C;
    switch (arg_0)
    {
    case UIX_OBJECT_BACKGROUND:
        var_8 = new type_228D70;
        break;
    case UIX_OBJECT_LISTBOX:
        var_8 = new type_229930;
        break;
    case UIX_OBJECT_TEXTBOX:
        var_8 = new CUITextBoxObject;
        break;
    default:
        return E_NOTIMPL;
    }
    var_8->unk_0C = this;
    var_8->unk_10 = l4;
    var_8->unk_14 = (WORD)arg_8;
    var_8->unk_16 = (WORD)arg_C;
    var_8->unk_18 = arg_4;
    lv_C = var_8->vf_000();
    if (FAILED(lv_C))
    {
        delete var_8;
        return lv_C;
    }
    for (var_10 = 0; var_10 < 100; var_10++)
    {
        if (!unk_08[var_10])
            break;
    }
    unk_08[var_10] = var_8;
    *arg_10 = var_10;
    return 0;
}

// match: ?DestroyObject@type_22A630@@UAGJK@Z @ 0x0022AA30
HRESULT type_22A630::DestroyObject(DWORD arg_0)
{
    if (!unk_08[arg_0])
        return E_INVALIDARG;
    unk_08[arg_0]->vf_004();
    delete unk_08[arg_0];
    unk_08[arg_0] = 0;
    return 0;
}

// match: ?DestroyScreenObjects@type_22A630@@UAGJK@Z @ 0x0022AAD0
HRESULT type_22A630::DestroyScreenObjects(DWORD arg_0)
{
    for (DWORD var_4 = 0; var_4 < 100; var_4++)
    {
        if (unk_08[var_4] && unk_08[var_4]->unk_18 == arg_0)
        {
            unk_08[var_4]->vf_004();
            delete unk_08[var_4];
            unk_08[var_4] = 0;
        }
    }
    return 0;
}

// match: ?RenderObject@type_22A630@@UAGJK@Z @ 0x0022AB90
HRESULT type_22A630::RenderObject(DWORD arg_0)
{
    if (!unk_08[arg_0])
        return E_INVALIDARG;
    return unk_08[arg_0]->vf_01C(unk_08[arg_0]->unk_10->X, unk_08[arg_0]->unk_10->Y);
}

// match: ?Clear@type_22A630@@UAGJKH@Z @ 0x0022AC00
HRESULT type_22A630::Clear(DWORD arg_0, BOOL arg_4)
{
    if (!unk_08[arg_0])
        return E_INVALIDARG;
    return unk_08[arg_0]->vf_014(arg_4);
}

// match: ?SetText@type_22A630@@UAGJKKPBGKPBU_UIX_SKIN_ICON_INFO@@@Z @ 0x0022AC40
HRESULT type_22A630::SetText(DWORD arg_0, DWORD arg_4, LPCWSTR arg_8, DWORD arg_C, const UIX_SKIN_ICON_INFO *arg_10)
{
    if (!unk_08[arg_0])
        return E_INVALIDARG;
    return unk_08[arg_0]->vf_020(arg_4, arg_8, arg_C, arg_10);
}

// match: ?InsertItem@type_22A630@@UAGJKKPAK@Z @ 0x0022AC90
HRESULT type_22A630::InsertItem(DWORD arg_0, DWORD arg_4, DWORD *arg_8)
{
    if (!unk_08[arg_0])
        return E_INVALIDARG;
    return unk_08[arg_0]->vf_018(arg_4, arg_8);
}

// match: ?GetObjectState@type_22A630@@UAGJKKW4_UIX_OBJSTATE_TYPE@@PAK@Z @ 0x0022ACD0
HRESULT type_22A630::GetObjectState(DWORD arg_0, DWORD arg_4, UIX_OBJSTATE_TYPE arg_8, DWORD *arg_C)
{
    if (!unk_08[arg_0])
        return E_INVALIDARG;
    return unk_08[arg_0]->vf_00C(arg_4, arg_8, arg_C);
}

// match: ?SetObjectState@type_22A630@@UAGJKKW4_UIX_OBJSTATE_TYPE@@K@Z @ 0x0022AD20
HRESULT type_22A630::SetObjectState(DWORD arg_0, DWORD arg_4, UIX_OBJSTATE_TYPE arg_8, DWORD arg_C)
{
    if (!unk_08[arg_0])
        return E_INVALIDARG;
    return unk_08[arg_0]->vf_010(arg_4, arg_8, arg_C);
}

// match: ?PassInputToObject@type_22A630@@UAGJKW4_UIX_INPUT_TYPE@@@Z @ 0x0022AD70
HRESULT type_22A630::PassInputToObject(DWORD arg_0, UIX_INPUT_TYPE arg_4)
{
    if (!unk_08[arg_0])
        return E_INVALIDARG;
    return unk_08[arg_0]->vf_008(arg_4);
}

// match: ?GetFont@type_22A630@@UAGJPAPAUITitleFontRenderer@@@Z @ 0x0022ADB0
HRESULT type_22A630::GetFont(ITitleFontRenderer **arg_0)
{
    *arg_0 = unk_198;
    return 0;
}

// match: ?SetRenderTarget@type_22A630@@UAGJPAUD3DSurface@@@Z @ 0x0022ADD0
HRESULT type_22A630::SetRenderTarget(IDirect3DSurface8 *arg_0)
{
    if (arg_0)
        return sub_32260(arg_0);
    return sub_115460();
}

HRESULT type_22A630::DoWork()
{
    return 0;
}

// Members /OPT:ICF folded into shared trivial bodies (config/aliases.txt): defined here for
// the authentic link (PLAN M7); the placement link takes the shared bodies.

// ?sub_32260@type_22A630@@QAEJPAUD3DSurface@@@Z (folded into `return 0` at 0x32260)
HRESULT type_22A630::sub_32260(IDirect3DSurface8 *arg_0)
{
    return 0;
}

// Functions /OPT:ICF folded into another body (config/aliases.txt), defined here for the
// authentic link (PLAN M7) with that body; the placement link takes the folded one.

// ?sub_115460@type_22A630@@QAEJXZ (folded into 0x115460)
HRESULT type_22A630::sub_115460()
{
    return 1;
}
