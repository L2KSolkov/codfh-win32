/*
 * kujuUI's on-screen keyboard (game/kujuui.h): a text field over a grid of
 * keys built from its layout table, the pad moving the focus between them and
 * typing, and its two action templates' instances.
 */
#include "game/kujuui.h"
#include "game/frontend.h"

// Its data definitions (PLAN M5), in the image's address order.
// 0x003E7CB0
extern const RwReal flt_3E7CB0 = 320.0f;
// 0x0042D0E8
namespace kujuUI
{
const RwChar *unk_42D0E8[11] = { " ", "Done", "Shift", "Caps Lock", "Accent", "Symbol", "Alphabet", "Space", "Backspace", "<", ">" };
}
// 0x0042D114
namespace kujuUI
{
RwInt32 unk_42D114[11] = { 1, 106, 106, 106, 106, 106, 106, 217, 143, 32, 32 };
}
// 0x0042D140
namespace kujuUI
{
RwUInt8 unk_42D140[5][5][11] = {
    { { 1, 49, 50, 51, 52, 53, 54, 55, 56, 57, 48 }, { 2, 97, 98, 99, 100, 101, 102, 103, 104, 105, 106 }, { 3, 107, 108, 109, 110, 111, 112, 113, 114, 115, 116 }, { 4, 117, 118, 119, 120, 121, 122, 44, 46, 9, 10 }, { 5, 7, 7, 7, 7, 7, 7, 8, 8, 8, 8 } },
    { { 1, 49, 50, 51, 52, 53, 54, 55, 56, 57, 48 }, { 2, 65, 66, 67, 68, 69, 70, 71, 72, 73, 74 }, { 3, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84 }, { 4, 85, 86, 87, 88, 89, 90, 44, 46, 9, 10 }, { 5, 7, 7, 7, 7, 7, 7, 8, 8, 8, 8 } },
    { { 1, 40, 41, 38, 95, 94, 37, 92, 47, 64, 35 }, { 2, 91, 93, 36, 163, 165, 128, 59, 58, 39, 34 }, { 3, 60, 62, 63, 33, 191, 161, 45, 42, 43, 61 }, { 4, 123, 125, 171, 187, 0, 0, 44, 46, 9, 10 }, { 6, 7, 7, 7, 7, 7, 7, 8, 8, 8, 8 } },
    { { 1, 49, 50, 51, 52, 53, 54, 55, 56, 57, 48 }, { 2, 224, 225, 226, 228, 231, 232, 233, 234, 235, 236 }, { 3, 237, 238, 239, 241, 242, 243, 244, 245, 246, 223 }, { 6, 249, 250, 251, 252, 253, 255, 44, 46, 9, 10 }, { 5, 7, 7, 7, 7, 7, 7, 8, 8, 8, 8 } },
    { { 1, 49, 50, 51, 52, 53, 54, 55, 56, 57, 48 }, { 2, 192, 193, 194, 196, 199, 200, 201, 202, 203, 204 }, { 3, 205, 206, 207, 209, 210, 211, 212, 213, 214, 223 }, { 6, 217, 218, 219, 220, 221, 159, 44, 46, 9, 10 }, { 5, 7, 7, 7, 7, 7, 7, 8, 8, 8, 8 } },
};
}
// End of its data definitions.


using namespace kujuUI;

// The screen's centre line (x = 320).
extern const RwReal flt_3E7CB0;

// arg_0 centred on the screen's centre line, arg_4 either side, from arg_8
// down to arg_C: an inline with no address, named for what it does.
// Evidence: the constructor works out the left and right edges in place
// from the centre line and half-width, and only the bottom through a
// temporary.
inline void set_centred(type_1E0330_rect &arg_0, RwReal arg_4, RwReal arg_8, RwReal arg_C)
{
    arg_0.unk_00 = flt_3E7CB0 - arg_4;
    arg_0.unk_04 = arg_8;
    arg_0.unk_08 = flt_3E7CB0 + arg_4;
    arg_0.unk_0C = arg_C;
}

// Vtables (.rdata, PLAN M5): each in its own placement range (config/splits.txt).
// Its data (PLAN M5): literals, constants and tables where the image has them.
// match: ??_C@_01MNNFJEPP@?$DM?$AA@ @ 0x003E7C60
// match: ??_C@_09LPBCIPOJ@Backspace?$AA@ @ 0x003E7C64
// match: ??_C@_05OMHELODH@Space?$AA@ @ 0x003E7C70
// match: ??_C@_08GPKGMALB@Alphabet?$AA@ @ 0x003E7C78
// match: ??_C@_06CGMNKLGA@Symbol?$AA@ @ 0x003E7C84
// match: ??_C@_06NFPPHDMM@Accent?$AA@ @ 0x003E7C8C
// match: ??_C@_09GGECHFNF@Caps?5Lock?$AA@ @ 0x003E7C94
// match: ??_C@_05CMECKLGA@Shift?$AA@ @ 0x003E7CA0
// match: ??_C@_04KNCIGIPG@Done?$AA@ @ 0x003E7CA8
// match: ?flt_3E7CB0@@3MB @ 0x003E7CB0
// match: ??_7type_1F5D70@kujuUI@@6B@ @ 0x003E7CB4
// match: ??_7?$type_3E7CE8@Utype_1F5D70@kujuUI@@@kujuUI@@6B@ @ 0x003E7CE8
// match: ??_7?$type_3E7264@Utype_1F5D70@kujuUI@@@kujuUI@@6B@ @ 0x003E7CF8
// match: __ehhandler$??0type_1F5D70@kujuUI@@QAE@PBD00IIPBUtype_1E0330_rect@1@1HPAUtype_1ED670_object@1@PAUtype_3E7D08@1@@Z>1>8 @ 0x004212C8
// match: __ehhandler$??0type_1F5D70@kujuUI@@QAE@PBD00IIPBUtype_1E0330_rect@1@1HPAUtype_1ED670_object@1@PAUtype_3E7D08@1@@Z>1 @ 0x00421350
// match: __ehhandler$??1type_1F5D70@kujuUI@@UAE@XZ>1>8 @ 0x0042136C
// match: __ehhandler$??1type_1F5D70@kujuUI@@UAE@XZ>1 @ 0x004213A4
// match: __ehhandler$?sub_1F6FF0@type_1F5D70@kujuUI@@QAEXXZ>1>8 @ 0x004213C0
// match: __ehhandler$?sub_1F6FF0@type_1F5D70@kujuUI@@QAEXXZ>1 @ 0x004213D8
// match: ?unk_42D0E8@kujuUI@@3PAPBDA @ 0x0042D0E8
// match: ?unk_42D114@kujuUI@@3PAHA @ 0x0042D114
// match: ?unk_42D140@kujuUI@@3PAY14L@EA @ 0x0042D140

// match: ??0type_1F5D70@kujuUI@@QAE@PBD00IIPBUtype_1E0330_rect@1@1HPAUtype_1ED670_object@1@PAUtype_3E7D08@1@@Z @ 0x001F5D70
// match: __ehhandler$??0type_1F5D70@kujuUI@@QAE@PBD00IIPBUtype_1E0330_rect@1@1HPAUtype_1ED670_object@1@PAUtype_3E7D08@1@@Z-0xDD @ 0x00304910
// match: __ehhandler$??0type_1F5D70@kujuUI@@QAE@PBD00IIPBUtype_1E0330_rect@1@1HPAUtype_1ED670_object@1@PAUtype_3E7D08@1@@Z @ 0x003049ED

type_1F5D70::type_1F5D70(const RwChar *arg_0, const RwChar *arg_4, const RwChar *arg_8, RwUInt32 arg_C, RwUInt32 arg_10,
                         const type_1E0330_rect *arg_14, const type_1E0330_rect *arg_18, RwInt32 arg_1C,
                         type_1ED670_object *arg_20, type_3E7D08 *arg_24)
    : type_3E7584(arg_24), unk_38(arg_0), unk_3C(arg_4), unk_40(arg_8), unk_44(this, &type_1F5D70::sub_1F6BF0),
      unk_50(this, &type_1F5D70::sub_1F6BC0, &type_1F5D70::sub_1F6EF0),
      unk_60(this, &type_1F5D70::pDtor, &type_1F5D70::sub_1F6E50),
      unk_70(this, &type_1F5D70::pDtor, &type_1F5D70::sub_1F6E90),
      unk_80(this, &type_1F5D70::pDtor, &type_1F5D70::sub_1F6ED0), unk_94(arg_20)
{
    RwUInt8 bp_D;
    type_3E79B4 *u14;
    unk_178 = -1;
    unk_17C = -1;
    unk_180 = false;
    unk_181 = false;
    unk_184 = 0;
    unk_188 = 1;
    memset(unk_9C, 0, sizeof(unk_9C));
    RwReal u48 = (arg_14->unk_08 - arg_14->unk_00) / 2.0f;
    type_1E0330_rect lcl_44;
    set_centred(lcl_44, u48, 100.0f, arg_14->unk_0C - arg_14->unk_04 + 100.0f);
    type_1E0330_rect l34(0.0f, 0.0f, arg_18->unk_08 - arg_18->unk_00, arg_18->unk_0C - arg_18->unk_04);
    unk_98 = new type_3E7BCC(unk_3C, unk_40, arg_10, &lcl_44, &l34, arg_1C, &unk_50, &unk_44, this);
    sub_1ED9D0(unk_98);
    type_1E0330_rect w24;
    w24.unk_00 = 87.0f;
    w24.unk_04 = 150.0f;
    for (RwInt32 ebp_4C = 0; ebp_4C < 5; ++ebp_4C)
    {
        w24.unk_00 = 100.0f;
        for (RwInt32 var_50 = 0; var_50 < 11; ++var_50)
        {
            bp_D = unk_42D140[unk_184][ebp_4C][var_50];
            if (bp_D < 11)
            {
                if (var_50 > 1 && bp_D == key_at(ebp_4C, var_50 - 1))
                {
                    unk_9C[ebp_4C][var_50] = unk_9C[ebp_4C][var_50 - 1];
                }
                else
                {
                    w24.unk_08 = unk_42D114[bp_D] + w24.unk_00;
                    w24.unk_0C = w24.unk_04 + 32.0f;
                    type_1ED670_object *bp_54;
                    switch (bp_D)
                    {
                    case 1:
                        bp_54 = &unk_50;
                        break;
                    case 8:
                    case 9:
                        bp_54 = &unk_80;
                        break;
                    case 10:
                        bp_54 = &unk_70;
                        break;
                    case 7:
                        bp_54 = &unk_60;
                    default:
                        bp_54 = 0;
                    }
                    u14 = new type_3E7C30(unk_38, &w24, type_1CB670(unk_42D0E8[bp_D], 0), arg_C, bp_54, this);
                    sub_1ED9D0(u14);
                    unk_9C[ebp_4C][var_50] = u14;
                }
            }
            else
            {
                w24.unk_08 = w24.unk_00 + 32.0f;
                w24.unk_0C = w24.unk_04 + 32.0f;
                type_1A5EA0 var_74;
                var_74.sub_1C8300(0, bp_D);
                u14 = new type_3E7C30(unk_38, &w24, sub_1CB720(var_74.c_str()), arg_C, &unk_60, this);
                sub_1ED9D0(u14);
                unk_9C[ebp_4C][var_50] = u14;
            }
            w24.unk_00 = w24.unk_08 + 5.0f;
        }
        w24.unk_04 = w24.unk_0C + 5.0f;
    }
}

// match: ??_Gtype_1F5D70@kujuUI@@UAEPAXI@Z @ 0x001F6500

// match: ??1type_1F5D70@kujuUI@@UAE@XZ @ 0x001F6530
// match: __ehhandler$??1type_1F5D70@kujuUI@@UAE@XZ-0x4D @ 0x00304A00
// match: __ehhandler$??1type_1F5D70@kujuUI@@UAE@XZ @ 0x00304A4D
type_1F5D70::~type_1F5D70()
{
    type_3E79B4 *var_10 = 0;
    for (RwInt32 var_14 = 0; var_14 != 5; ++var_14)
    {
        for (RwInt32 var_18 = 0; var_18 != 11; ++var_18)
        {
            type_3E79B4 *var_1C = unk_9C[var_14][var_18];
            if (var_1C != var_10)
            {
                var_10 = var_1C;
                delete var_1C;
            }
        }
    }
    delete unk_98;
}

// match: ?processEvent@type_1F5D70@kujuUI@@UAE?AW4eEventWasHandled@2@ABVcStateChange@2@@Z @ 0x001F66A0
eEventWasHandled type_1F5D70::processEvent(const cStateChange &arg_0)
{
    RwInt32 var_10 = unk_17C;
    RwInt32 var_C = unk_178;
    type_3E79B4 *var_8 = sub_1F72D0(var_C, var_10);
    RwInt16 var_4;
    if (arg_0.get_unk_04() == 0)
    {
        switch (arg_0.get_unk_00())
        {
        case 7:
            if (dword_504378)
                dword_504378->vf_04(3);
            return (eEventWasHandled)0;
        case 4:
            if (dword_504378)
                dword_504378->vf_04(2);
            if (var_8)
            {
                var_4 = key_at(unk_17C, unk_178);
                if (var_4 > 11)
                {
                    unk_98->sub_1F52C0(var_4);
                    sub_1F6C50();
                    break;
                }
                switch (var_4)
                {
                case 2:
                    sub_1F6C10();
                    break;
                case 3:
                    sub_1F6C80();
                    unk_180 = false;
                    break;
                case 4:
                    sub_1F6D70();
                    unk_180 = false;
                    break;
                case 5:
                    sub_1F6DB0();
                    unk_180 = false;
                    break;
                case 6:
                    sub_1F6DE0();
                    unk_180 = false;
                    break;
                case 7:
                    unk_98->sub_1F52C0(' ');
                    break;
                case 8:
                    unk_98->sub_1F52C0(0x10000);
                    break;
                case 9:
                    unk_98->sub_1F52C0(0x22B2);
                    break;
                case 10:
                    unk_98->sub_1F52C0(0x22B3);
                }
            }
            return (eEventWasHandled)0;
        case 3:
            if (++var_10 >= 5)
                var_10 = 0;
            sub_1F7200(var_C, var_10);
            if (dword_504378)
                dword_504378->vf_04(1);
            return (eEventWasHandled)0;
        case 2:
            if (--var_10 < 0)
                var_10 = 4;
            sub_1F7200(var_C, var_10);
            if (dword_504378)
                dword_504378->vf_04(1);
            return (eEventWasHandled)0;
        case 9:
            unk_98->sub_1F52C0(0x22B3);
            if (dword_504378)
                dword_504378->vf_04(1);
            return (eEventWasHandled)0;
        case 8:
            unk_98->sub_1F52C0(0x22B2);
            if (dword_504378)
                dword_504378->vf_04(1);
            return (eEventWasHandled)0;
        case 1:
            while (sub_1F72D0(var_C, var_10) == var_8)
            {
                if (++var_C >= 11)
                    var_C = 0;
            }
            sub_1F7200(var_C, var_10);
            if (dword_504378)
                dword_504378->vf_04(1);
            return (eEventWasHandled)0;
        case 0:
            while (sub_1F72D0(var_C, var_10) == var_8)
            {
                if (--var_C < 0)
                    var_C = 10;
            }
            sub_1F7200(var_C, var_10);
            if (dword_504378)
                dword_504378->vf_04(1);
            return (eEventWasHandled)0;
        default:
            return (eEventWasHandled)1;
        }
    }
    else
    {
        switch (arg_0.get_unk_00())
        {
        case 7:
            sub_1F6BF0();
        case 4:
            if (var_8)
            {
                var_4 = key_at(unk_17C, unk_178);
                switch (var_4)
                {
                case 1:
                    sub_1F6BC0();
                }
            }
        case 0:
        case 1:
        case 2:
        case 3:
        case 8:
        case 9:
            return (eEventWasHandled)0;
        default:
            return (eEventWasHandled)1;
        }
    }
    return (eEventWasHandled)1;
}

// match: ?givenFocus@type_1F5D70@kujuUI@@UAEXXZ @ 0x001F6B50
void type_1F5D70::givenFocus()
{
    unk_188 = 0;
    sub_1F7200(1, 1);
}

// match: ?vf_014@type_1F5D70@kujuUI@@UAEXM@Z @ 0x001F6B80
void type_1F5D70::vf_014(RwReal arg_0)
{
    type_3E7584::vf_014(arg_0);
}

// match: ?vf_018@type_1F5D70@kujuUI@@UAEXPAUtype_1E4130@2@@Z @ 0x001F6BA0
void type_1F5D70::vf_018(type_1E4130 *arg_0)
{
    type_3E7584::vf_018(arg_0);
}

// match: ?sub_1F6BC0@type_1F5D70@kujuUI@@QAEXXZ @ 0x001F6BC0
void type_1F5D70::sub_1F6BC0()
{
    if (sub_1F6EF0())
        unk_188 = 2;
}

// match: ?sub_1F6BF0@type_1F5D70@kujuUI@@QAEXXZ @ 0x001F6BF0
void type_1F5D70::sub_1F6BF0()
{
    unk_188 = 1;
}

// match: ?sub_1F6C10@type_1F5D70@kujuUI@@QAEXXZ @ 0x001F6C10
void type_1F5D70::sub_1F6C10()
{
    if (!unk_180)
    {
        unk_180 = true;
        sub_1F6C80();
    }
    else
    {
        unk_180 = false;
        sub_1F6C80();
    }
}

// match: ?sub_1F6C50@type_1F5D70@kujuUI@@QAEXXZ @ 0x001F6C50
void type_1F5D70::sub_1F6C50()
{
    if (unk_180)
    {
        unk_180 = false;
        sub_1F6C80();
    }
}

// match: ?sub_1F6C80@type_1F5D70@kujuUI@@QAEXXZ @ 0x001F6C80
void type_1F5D70::sub_1F6C80()
{
    unk_181 = !unk_181;
    switch (unk_184)
    {
    case 0:
        if (sub_1F6E20(1))
            sub_1F6FF0();
        break;
    case 1:
        if (sub_1F6E20(0))
            sub_1F6FF0();
        break;
    case 2:
        if (sub_1F6E20(unk_181 ? 1 : 0))
            sub_1F6FF0();
        break;
    case 3:
        if (sub_1F6E20(4))
            sub_1F6FF0();
    case 4:
        if (sub_1F6E20(3))
            sub_1F6FF0();
    }
}

// match: ?sub_1F6D70@type_1F5D70@kujuUI@@QAEXXZ @ 0x001F6D70
void type_1F5D70::sub_1F6D70()
{
    if (sub_1F6E20((unk_181 ? 1 : 0) + 3))
        sub_1F6FF0();
}

// match: ?sub_1F6DB0@type_1F5D70@kujuUI@@QAEXXZ @ 0x001F6DB0
void type_1F5D70::sub_1F6DB0()
{
    if (sub_1F6E20(2))
        sub_1F6FF0();
}

// match: ?sub_1F6DE0@type_1F5D70@kujuUI@@QAEXXZ @ 0x001F6DE0
void type_1F5D70::sub_1F6DE0()
{
    if (sub_1F6E20(unk_181 ? 1 : 0))
        sub_1F6FF0();
}

// match: ?sub_1F6E20@type_1F5D70@kujuUI@@QAE_NH@Z @ 0x001F6E20
bool type_1F5D70::sub_1F6E20(RwInt32 arg_0)
{
    if (unk_184 != arg_0)
    {
        unk_184 = arg_0;
        return true;
    }
    return false;
}

// match: ?sub_1F6E50@type_1F5D70@kujuUI@@QAE_NXZ @ 0x001F6E50
bool type_1F5D70::sub_1F6E50()
{
    return unk_98->sub_1F5230().size() != unk_98->sub_1F5840();
}

// match: ?sub_1F6E90@type_1F5D70@kujuUI@@QAE_NXZ @ 0x001F6E90
bool type_1F5D70::sub_1F6E90()
{
    return unk_98->sub_CB0A0() != unk_98->sub_1F5840();
}

// match: ?sub_1F6ED0@type_1F5D70@kujuUI@@QAE_NXZ @ 0x001F6ED0
bool type_1F5D70::sub_1F6ED0()
{
    return unk_98->sub_CB0A0() ? 1 : 0;
}

// match: ?sub_1F6EF0@type_1F5D70@kujuUI@@QAE_NXZ @ 0x001F6EF0
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
bool type_1F5D70::sub_1F6EF0()
{
    const type_1A5EA0 &var_4 = unk_98->sub_1F5230();
    bool local_5 = false;
    for (std::string::const_iterator varC = var_4.begin(); varC != var_4.end(); ++varC)
    {
        if (*varC != ' ')
        {
            local_5 = true;
            break;
        }
    }
    return local_5 && (unk_94 ? unk_94->pvf_00C() : true);
}

// match: ?sub_1F6FF0@type_1F5D70@kujuUI@@QAEXXZ @ 0x001F6FF0
// match: __ehhandler$?sub_1F6FF0@type_1F5D70@kujuUI@@QAEXXZ-0x18 @ 0x00304A60
// match: __ehhandler$?sub_1F6FF0@type_1F5D70@kujuUI@@QAEXXZ @ 0x00304A78
void type_1F5D70::sub_1F6FF0()
{
    RwUInt8 var_D;
    for (RwInt32 var_14 = 0; var_14 < 5; ++var_14)
    {
        for (RwInt32 var_18 = 0; var_18 < 11; ++var_18)
        {
            var_D = unk_42D140[unk_184][var_14][var_18];
            if (var_D > 11)
            {
                type_1A5EA0 var_38;
                var_38.sub_1C8300(0, var_D);
                unk_9C[var_14][var_18]->pvf_008(sub_1CB720(var_38.c_str()));
            }
            else
            {
                unk_9C[var_14][var_18]->pvf_008(type_1CB670(unk_42D0E8[var_D], 0));
            }
        }
    }
}

// match: ?sub_1F7200@type_1F5D70@kujuUI@@QAEXHH@Z @ 0x001F7200
void type_1F5D70::sub_1F7200(RwInt32 arg_0, RwInt32 arg_4)
{
    if (unk_178 != arg_0 || unk_17C != arg_4)
    {
        type_3E79B4 *var_4 = sub_1F72D0(unk_178, unk_17C);
        if (var_4)
        {
            var_4->sub_1F77B0();
            var_4->pvf_004(0);
        }
        unk_178 = arg_0;
        unk_17C = arg_4;
        var_4 = sub_1F72D0(unk_178, unk_17C);
        if (var_4)
        {
            var_4->sub_1F7790();
            var_4->pvf_004(1);
        }
    }
}

// match: ?sub_1F72D0@type_1F5D70@kujuUI@@QAEPAUtype_3E79B4@2@HH@Z @ 0x001F72D0
type_3E79B4 *type_1F5D70::sub_1F72D0(RwInt32 arg_0, RwInt32 arg_4)
{
    if (arg_0 >= 0 && arg_4 >= 0 && arg_0 < 11 && arg_4 < 5)
        return unk_9C[arg_4][arg_0];
    return 0;
}

// match: ?sub_1F7310@type_1F5D70@kujuUI@@QAE?AUtype_1A5EA0@@XZ @ 0x001F7310
type_1A5EA0 type_1F5D70::sub_1F7310()
{
    return unk_98->sub_1F5230();
}

// match: ?sub_1F7370@type_1F5D70@kujuUI@@QAEXPBD@Z @ 0x001F7370
void type_1F5D70::sub_1F7370(const RwChar *arg_0)
{
    unk_98->sub_1F51B0(arg_0);
}

// match: ?sub_1F7390@type_1F5D70@kujuUI@@QAEXH@Z @ 0x001F7390
void type_1F5D70::sub_1F7390(RwInt32 arg_0)
{
    unk_98->sub_1F5250(arg_0);
}

// match: ?sub_1F73B0@type_1F5D70@kujuUI@@QAEHXZ @ 0x001F73B0
RwInt32 type_1F5D70::sub_1F73B0()
{
    return unk_98->sub_CB0A0();
}

// match: ?sub_1F73D0@type_1F5D70@kujuUI@@QAEXH@Z @ 0x001F73D0
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void type_1F5D70::sub_1F73D0(RwInt32 arg_0)
{
    if (arg_0)
    {
        RwInt32 var_4;
        RwInt32 v8;
        RwInt32 varC = sub_1F7450(arg_0, unk_184, &var_4, &v8);
        if (sub_1F6E20(varC))
            sub_1F6FF0();
        if (var_4 >= 0 && v8 >= 0)
            sub_1F7200(var_4, v8);
        unk_98->sub_1F52C0(arg_0);
    }
}

// match: ?sub_1F7450@type_1F5D70@kujuUI@@QAEHIHPAH0@Z @ 0x001F7450
RwInt32 type_1F5D70::sub_1F7450(RwUInt32 arg_0, RwInt32 arg_4, RwInt32 *arg_8, RwInt32 *arg_C)
{
    switch (arg_0)
    {
    case ' ':
        arg_0 = 7;
        break;
    case 0x10000:
        arg_0 = 8;
        break;
    case 0x22B2:
        arg_0 = 9;
        break;
    case 0x22B3:
        arg_0 = 10;
        break;
    }
    if (sub_1F7530(arg_0, arg_4, arg_8, arg_C))
        return arg_4;
    for (RwInt32 var_4 = 0; var_4 < 5; ++var_4)
    {
        if (sub_1F7530(arg_0, var_4, arg_8, arg_C))
            return var_4;
    }
    *arg_8 = -1;
    *arg_C = -1;
    return arg_4;
}

// match: ?sub_1F7530@type_1F5D70@kujuUI@@QAE_NHHPAH0@Z @ 0x001F7530
bool type_1F5D70::sub_1F7530(RwInt32 arg_0, RwInt32 arg_4, RwInt32 *arg_8, RwInt32 *arg_C)
{
    for (RwInt32 var_4 = 0; var_4 < 5; ++var_4)
    {
        for (RwInt32 var_8 = 0; var_8 < 11; ++var_8)
        {
            if (unk_42D140[arg_4][var_4][var_8] == arg_0)
            {
                *arg_C = var_4;
                *arg_8 = var_8;
                return true;
            }
        }
    }
    return false;
}

// match: ??0?$type_3E7CE8@Utype_1F5D70@kujuUI@@@kujuUI@@QAE@PAUtype_1F5D70@1@P821@AEXXZ@Z @ 0x001F75B0
template <class T> type_3E7CE8<T>::type_3E7CE8(T *arg_0, void (T::*arg_4)())
{
    unk_04 = arg_0;
    unk_08 = arg_4;
}

// match: ??1?$type_3E7CE8@Utype_1F5D70@kujuUI@@@kujuUI@@UAE@XZ @ 0x001F75F0
template <class T> type_3E7CE8<T>::~type_3E7CE8()
{
}

template <class T> void type_3E7CE8<T>::pvf_008()
{
    (unk_04->*unk_08)();
}

template struct type_3E7CE8<type_1F5D70>;

// match: ??0?$type_3E7264@Utype_1F5D70@kujuUI@@@kujuUI@@QAE@PAUtype_1F5D70@1@P821@AEXXZP821@AE_NXZ@Z @ 0x001F7610
template <class T> type_3E7264<T>::type_3E7264(T *arg_0, void (T::*arg_4)(), bool (T::*arg_C)())
{
    unk_04 = arg_0;
    unk_08 = arg_4;
    unk_10 = arg_C;
}

// The actions' deleting destructors.
// match: ??_G?$type_3E7CE8@Utype_1F5D70@kujuUI@@@kujuUI@@UAEPAXI@Z @ 0x001F7680
// match: ??_G?$type_3E7264@Utype_1F5D70@kujuUI@@@kujuUI@@UAEPAXI@Z @ 0x001F76B0

// match: ??1?$type_3E7264@Utype_1F5D70@kujuUI@@@kujuUI@@UAE@XZ @ 0x001F7660
template <class T> type_3E7264<T>::~type_3E7264()
{
}

template <class T> void type_3E7264<T>::pvf_008()
{
    (unk_04->*unk_08)();
}

template <class T> bool type_3E7264<T>::pvf_00C()
{
    return (unk_04->*unk_10)();
}

template struct type_3E7264<type_1F5D70>;
