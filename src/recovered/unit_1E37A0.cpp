/*
 * kujuUI's looks and drawing (game/kujuui.h): a selectable widget's look
 * (its quad over the state's texture rectangle), the looks' states and the
 * filling of missing ones, the validator of a look's values, the pad's
 * buttons from its controls, and the render state the widgets draw with.
 */
#include <math.h>
#include "game/kujuui.h"
#include "game/parsedfile.h"
#include "game/gameloop.h"

// Its data definitions (PLAN M5), in the image's address order.
// 0x0042CE80
namespace kujuUI
{
type_42CE80 unk_42CE80[16] = {
    { 2, 19, 0, -1 },
    { 3, 20, 0, -1 },
    { 0, 21, 0, -1 },
    { 1, 22, 0, -1 },
    { 2, 0, 1, 2 },
    { 3, 0, 2, 2 },
    { 0, 2, 1, 0 },
    { 1, 2, 2, 0 },
    { 7, 24, 0, -1 },
    { 4, 23, 0, -1 },
    { 5, 25, 0, -1 },
    { 6, 39, 0, -1 },
    { 8, 35, 0, -1 },
    { 9, 36, 0, -1 },
    { 12, 38, 0, -1 },
    { 14, -1, 0, -1 },
};
}
// 0x00503C38
namespace kujuUI { cScopeValidator *dword_503C38; }
// 0x00503E8C
namespace kujuUI { type_1E3DB0 *unk_503E8C[81]; }
// End of its data definitions.

// Its data (PLAN M5): literals, constants and tables where the image has them.
// match: ??_C@_06EOIELIPE@filter?$AA@ @ 0x003E71FC
// match: __ehhandler$?sub_1E3F50@kujuUI@@YAHHPAPAUtype_1E3DB0@1@@Z>1>8 @ 0x0041FF10
// match: __ehhandler$?sub_1E3F50@kujuUI@@YAHHPAPAUtype_1E3DB0@1@@Z>1 @ 0x0041FF18
// match: __ehhandler$??0type_1E4130@kujuUI@@QAE@XZ>1>8 @ 0x0041FF34
// match: __ehhandler$??0type_1E4130@kujuUI@@QAE@XZ>1 @ 0x0041FF3C
// match: .CRT$XCU+0 @ 0x004272E4
// match: .CRT$XCU+4 @ 0x004272E8
// match: .CRT$XCU+8 @ 0x004272EC
// match: .CRT$XCU+12 @ 0x004272F0
// match: .CRT$XCU+16 @ 0x004272F4
// match: .CRT$XCU+20 @ 0x004272F8
// match: .CRT$XCU+24 @ 0x004272FC
// match: .CRT$XCU+28 @ 0x00427300
// match: ?unk_42CE80@kujuUI@@3PAUtype_42CE80@1@A @ 0x0042CE80

// match: _$E1 @ 0x0030D450
// match: _$E2 @ 0x0030EEB0
// match: _$E4 @ 0x0030D490
// match: _$E5 @ 0x0030EEC0
// match: _$E7 @ 0x0030D4D0
// match: _$E8 @ 0x0030EED0
// match: _$E10 @ 0x0030D510
// match: _$E11 @ 0x0030EEE0
// match: _$E13 @ 0x0030D550
// match: _$E14 @ 0x0030EEF0
// match: _$E16 @ 0x0030D590
// match: _$E17 @ 0x0030EF00
// match: _$E19 @ 0x0030D5D0
// match: _$E20 @ 0x0030EF10
// match: _$E22 @ 0x0030D610
// match: _$E23 @ 0x0030EF20

namespace kujuUI {

// match: ??0type_1E37A0@kujuUI@@QAE@PAUtype_1E3BA0@1@@Z @ 0x001E37A0
type_1E37A0::type_1E37A0(type_1E3BA0 *arg_0)
{
    unk_B0 = arg_0;
    unk_B4 = 0;
    unk_C8 = true;
}

// match: ?sub_1E37E0@type_1E37A0@kujuUI@@QAEXPAUtype_1E4130@2@@Z @ 0x001E37E0
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void type_1E37A0::sub_1E37E0(type_1E4130 *arg_0)
{
    type_1ECCE0 *frm_24;
    type_1E0330_rect var_20;
    RwReal lv_10;
    RwReal var_C;
    RwReal bp_8;
    RwReal bp_4;

    lv_10 = RwIm2DGetFarScreenZ();
    bp_8 = arg_0->sub_1E41F0();
    type_1E0330_rect var_34(0, 0, unk_B8.width(), unk_B8.height());
    var_20 = unk_B0->sub_1E3BF0(unk_B4)->get_unk_2C();
    frm_24 = unk_B0->sub_1E3BF0(unk_B4)->get_unk_3C();
    bp_4 = frm_24->unk_38;
    var_C = frm_24->unk_3C;
    if (unk_B0->get_unk_18() == 1)
    {
        var_20.unk_00 += 2.0f * bp_4;
        var_20.unk_04 += 2.0f * var_C;
    }
    else
    {
        var_20.unk_00 += bp_4;
        var_20.unk_08 += bp_4;
        var_20.unk_04 += var_C;
        var_20.unk_0C += var_C;
    }
    unk_00.sub_1EEB00();
    unk_00.sub_1EEB80(0, 0);
    unk_00.sub_1EEC20(&var_34, lv_10, bp_8, &var_20, 0xFFFFFFFF);
    unk_C8 = false;
}

// match: ?sub_1E3950@type_1E37A0@kujuUI@@QAEXPAUtype_1E4130@2@@Z @ 0x001E3950
void type_1E37A0::sub_1E3950(type_1E4130 *arg_0)
{
    if (unk_C8)
    {
        sub_1E37E0(arg_0);
        unk_00.sub_1EEB80(unk_B8.unk_00, unk_B8.unk_04);
    }
    arg_0->sub_1E4130(unk_B0->sub_1E3BF0(unk_B4)->get_unk_3C()->sub_1ED650());
    arg_0->sub_1E4160(unk_B0->get_unk_18() != 0);
    unk_00.sub_1EEB60();
}

// match: ?sub_1E3A00@type_1E37A0@kujuUI@@QAEXPAUtype_1E3BA0@2@@Z @ 0x001E3A00
void type_1E37A0::sub_1E3A00(type_1E3BA0 *arg_0)
{
    unk_B0 = arg_0;
    unk_C8 = true;
}

// match: ?sub_1E3A30@type_1E37A0@kujuUI@@QAEXPBUtype_1E0330_rect@2@@Z @ 0x001E3A30
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void type_1E37A0::sub_1E3A30(const type_1E0330_rect *arg_0)
{
    RwReal var_10 = arg_0->unk_00;
    RwReal local_C = arg_0->unk_04;
    RwReal bp_4 = arg_0->width();
    RwReal var_8 = arg_0->height();
    if (unk_B8.width() != bp_4 || unk_B8.height() != var_8)
        unk_C8 = true;
    else if (unk_B8.unk_00 != var_10 || unk_B8.unk_04 != local_C)
        unk_00.sub_1EEB80(var_10, local_C);
    unk_B8 = *arg_0;
}

// match: ?sub_1E3B20@type_1E37A0@kujuUI@@QAEXH@Z @ 0x001E3B20
void type_1E37A0::sub_1E3B20(RwInt32 arg_0)
{
    if (arg_0 != unk_B4)
    {
        unk_C8 = true;
        unk_B4 = arg_0;
    }
}

// match: ?sub_1E3B60@type_1E37A0@kujuUI@@QAEPBUtype_1E0330_rect@2@XZ @ 0x001E3B60
const type_1E0330_rect *type_1E37A0::sub_1E3B60()
{
    return &unk_B8;
}

// match: ?sub_1E3B80@type_1E37A0@kujuUI@@QAEHXZ @ 0x001E3B80
RwInt32 type_1E37A0::sub_1E3B80()
{
    return unk_B4;
}

// match: ??0type_1E3BA0@kujuUI@@QAE@PBQAUtype_1E3BA0_state@1@H@Z @ 0x001E3BA0
type_1E3BA0::type_1E3BA0(type_1E3BA0_state *const *arg_0, RwInt32 arg_4)
{
    unk_18 = arg_4;
    for (RwInt32 var_4 = 0; var_4 != 6; ++var_4)
        unk_00[var_4] = arg_0[var_4];
}

// match: ?sub_1E3BF0@type_1E3BA0@kujuUI@@QAEPAUtype_1E3BA0_state@2@H@Z @ 0x001E3BF0
type_1E3BA0_state *type_1E3BA0::sub_1E3BF0(RwInt32 arg_0)
{
    return unk_00[arg_0];
}

// match: ?sub_1E3C10@kujuUI@@YAXPAPAUtype_1E3BA0_state@1@@Z @ 0x001E3C10
void sub_1E3C10(type_1E3BA0_state **arg_0)
{
    arg_0[3] = sub_1E3D70(arg_0[3], arg_0[0], 0, 0, 0);
    arg_0[4] = sub_1E3D70(arg_0[4], arg_0[3], 0, 0, 0);
    arg_0[1] = sub_1E3D70(arg_0[1], arg_0[0], 0, 0, 0);
    arg_0[2] = sub_1E3D70(arg_0[2], arg_0[1], 0, 0, 0);
    arg_0[5] = sub_1E3D70(arg_0[5], arg_0[1], arg_0[0], 0, 0);
}

extern type_1C9590 unk_503DDC;
extern type_1C9590 unk_503DB0;
extern type_1C9590 unk_503E08;
extern type_1C9590 unk_503C3C;
extern type_1C9590 unk_503E34;
extern type_1C9590 unk_503C68;
extern type_1C9590 unk_503E60;
extern cScopeValidator unk_503C98;
extern cScopeValidator *dword_503C38;

// match: ?sub_1E3CD0@kujuUI@@YAPBVcScopeValidator@1@XZ @ 0x001E3CD0
const cScopeValidator *sub_1E3CD0()
{
    if (!dword_503C38)
    {
        unk_503C98.sub_1C9F50(&unk_503DDC);
        unk_503C98.sub_1C9F50(&unk_503DB0);
        unk_503C98.sub_1C9F50(&unk_503E08);
        unk_503C98.sub_1C9F50(&unk_503C3C);
        unk_503C98.sub_1C9F50(&unk_503E34);
        unk_503C98.sub_1C9F50(&unk_503C68);
        unk_503C98.sub_1C9F50(&unk_503E60);
        dword_503C38 = &unk_503C98;
    }
    return dword_503C38;
}

// match: ?sub_1E3D60@kujuUI@@YAPAUtype_1C9590@1@XZ @ 0x001E3D60
type_1C9590 *sub_1E3D60()
{
    return &unk_503E60;
}

// match: ?sub_1E3D70@kujuUI@@YAPAUtype_1E3BA0_state@1@PAU21@0000@Z @ 0x001E3D70
type_1E3BA0_state *sub_1E3D70(type_1E3BA0_state *arg_0, type_1E3BA0_state *arg_4, type_1E3BA0_state *arg_8,
                              type_1E3BA0_state *arg_C, type_1E3BA0_state *arg_10)
{
    if (arg_0)
        return arg_0;
    if (arg_4)
        return arg_4;
    if (arg_8)
        return arg_8;
    if (arg_C)
        return arg_C;
    if (arg_10)
        return arg_10;
    return 0;
}

extern type_1E3DB0 *unk_503E8C[];

// match: ??1type_1E3DB0@kujuUI@@QAE@XZ @ 0x001E3DB0
type_1E3DB0::~type_1E3DB0()
{
    unk_503E8C[unk_00] = 0;
}

// match: ?sub_1E3DD0@type_1E3DB0@kujuUI@@QAE?AUtype_1EE900@2@XZ @ 0x001E3DD0
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
type_1EE900 type_1E3DB0::sub_1E3DD0()
{
    RwUInt32 l4 = 0;
    const type_42CE80 *var_8 = unk_42CE80;
    while (var_8->unk_00 != 14)
    {
        RwReal var_C = 0.0f;
        RwReal var_10 = 0.0f;
        var_C = unk_4B9308.sub_EE9A0(unk_00, var_8->unk_04);
        switch (var_8->unk_08)
        {
        case 0:
            if (var_C > 0.0f)
                l4 |= sub_1EE930(var_8->unk_00);
            break;
        case 1:
            if (var_C > 0.5f)
            {
                var_10 = unk_4B9308.sub_EE9A0(unk_00, var_8->unk_0C);
                if ((RwReal)fabs(var_10) < 0.5)
                    l4 |= sub_1EE930(var_8->unk_00);
            }
            break;
        case 2:
            if (var_C < -0.5f)
            {
                var_10 = unk_4B9308.sub_EE9A0(unk_00, var_8->unk_0C);
                if ((RwReal)fabs(var_10) < 0.5)
                    l4 |= sub_1EE930(var_8->unk_00);
            }
            break;
        }
        ++var_8;
    }
    return type_1EE900(l4);
}

// match: ?sub_1E3F50@kujuUI@@YAHHPAPAUtype_1E3DB0@1@@Z @ 0x001E3F50
// match: __ehhandler$?sub_1E3F50@kujuUI@@YAHHPAPAUtype_1E3DB0@1@@Z-0xB @ 0x00303970
// match: __ehhandler$?sub_1E3F50@kujuUI@@YAHHPAPAUtype_1E3DB0@1@@Z @ 0x0030397B
RwInt32 sub_1E3F50(RwInt32 arg_0, type_1E3DB0 **arg_4)
{
    RwInt32 var_10 = 0;
    if (!unk_503E8C[arg_0])
    {
        *arg_4 = new type_1E3DB0(arg_0);
    }
    else
    {
        *arg_4 = 0;
        var_10 = 2;
    }
    return var_10;
}

// match: ??0type_1E4130@kujuUI@@QAE@XZ @ 0x001E3FF0
// match: __ehhandler$??0type_1E4130@kujuUI@@QAE@XZ-0xB @ 0x00303990
// match: __ehhandler$??0type_1E4130@kujuUI@@QAE@XZ @ 0x0030399B
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
type_1E4130::type_1E4130() : unk_00(0), unk_04(0)
{
    RwRenderStateSet(rwRENDERSTATESHADEMODE, (void *)rwSHADEMODEGOURAUD);
    RwRenderStateSet(rwRENDERSTATETEXTUREFILTER, (void *)rwFILTERNEAREST);
    RwRenderStateSet(rwRENDERSTATESRCBLEND, (void *)rwBLENDSRCALPHA);
    RwRenderStateSet(rwRENDERSTATEDESTBLEND, (void *)rwBLENDINVSRCALPHA);
    RwRenderStateSet(rwRENDERSTATEVERTEXALPHAENABLE, (void *)TRUE);
    RwRenderStateSet(rwRENDERSTATEZTESTENABLE, (void *)FALSE);
    RwRenderStateSet(rwRENDERSTATEZWRITEENABLE, (void *)TRUE);
    RwRenderStateSet(rwRENDERSTATECULLMODE, (void *)rwCULLMODECULLNONE);
    RwRenderStateSet(rwRENDERSTATEFOGENABLE, (void *)FALSE);
    type_1E0330_rect var_2C(0, 0, 640.0f, 576.0f);
    type_1E0330_rect l1C(0, 0, 0, 0);
    unk_08.sub_1EEC20(&var_2C, RwIm2DGetFarScreenZ(), sub_1E41F0(), &l1C, 0xA0000000);
}

// match: ?sub_1E4130@type_1E4130@kujuUI@@QAEXH@Z @ 0x001E4130
void type_1E4130::sub_1E4130(RwInt32 arg_0)
{
    if (unk_00 != arg_0)
    {
        unk_00 = arg_0;
        RwRenderStateSet(rwRENDERSTATETEXTURERASTER, (void *)arg_0);
    }
}

// match: ?sub_1E4160@type_1E4130@kujuUI@@QAEXH@Z @ 0x001E4160
void type_1E4130::sub_1E4160(RwInt32 arg_0)
{
    if (unk_04 != arg_0)
    {
        RwInt32 var_4;
        switch (arg_0)
        {
        case 0:
            var_4 = rwFILTERNEAREST;
            break;
        case 1:
            var_4 = rwFILTERLINEAR;
            break;
        default:
            var_4 = 0;
            break;
        }
        RwRenderStateSet(rwRENDERSTATETEXTUREFILTER, (void *)var_4);
        unk_04 = arg_0;
    }
}

// The look's destructor: empty and out of line (/OPT:ICF folds the other
// empty functions into it, config/aliases.txt).
// match: ??1type_1E3BA0@kujuUI@@QAE@XZ @ 0x001E41C0
type_1E3BA0::~type_1E3BA0()
{
}

// match: ?sub_1E41D0@type_1E4130@kujuUI@@QAEXXZ @ 0x001E41D0
void type_1E4130::sub_1E41D0()
{
    sub_1E4130(0);
}

// match: ?sub_1E41F0@type_1E4130@kujuUI@@QAEMXZ @ 0x001E41F0
RwReal type_1E4130::sub_1E41F0()
{
    return 20.0f;
}

// match: ?sub_1E4210@type_1E4130@kujuUI@@QAEXI@Z @ 0x001E4210
void type_1E4130::sub_1E4210(RwUInt32 arg_0)
{
    RwRenderStateSet(rwRENDERSTATETEXTURERASTER, (void *)0);
    unk_08.sub_1EEC50(arg_0);
    unk_08.sub_1EEB60();
    unk_00 = 0;
}
}

namespace kujuUI
{

// The value definitions and scope validators, built by their dynamic
// initializers (their exit functions call the out-of-line destructors).
type_1C9590 unk_503DDC(sub_1F80C0(), 1, 0, 0, 0, 0, 0, 0, 0);
type_1C9590 unk_503DB0(sub_1F80D0(), 1, 0, 0, 0, 0, 0, 0, 0);
type_1C9590 unk_503E08(sub_1F80E0(), 1, 0, 0, 0, 0, 0, 0, 0);
type_1C9590 unk_503C3C(sub_1F80F0(), 1, 0, 0, 0, 0, 0, 0, 0);
type_1C9590 unk_503E34(sub_1F8100(), 1, 0, 0, 0, 0, 0, 0, 0);
type_1C9590 unk_503C68(sub_1F8110(), 1, 0, 0, 0, 0, 0, 0, 0);
type_1C9590 unk_503E60("filter", 0, 0, 0, 0, 0, 0, 0, 0);
cScopeValidator unk_503C98("component", "end", 2);

}

// Functions /OPT:ICF folded into another body (config/aliases.txt), defined here for the
// authentic link (PLAN M7) with that body; the placement link takes the folded one.

// ??0type_1E3DB0@kujuUI@@QAE@H@Z (folded into 0x12A1B0)
kujuUI::type_1E3DB0::type_1E3DB0(RwInt32 arg_0) : unk_00(arg_0)
{
}

// ?pDtor@type_1E4130@kujuUI@@QAEXXZ (folded into 0x1E41C0)
void kujuUI::type_1E4130::pDtor()
{
}

// Functions /OPT:ICF folded into another body (config/aliases.txt), defined here for the
// authentic link (PLAN M7) with that body; the placement link takes the folded one.

// ?sub_2015D0@type_1E3DB0@kujuUI@@QAE_NXZ (folded into 0x2015D0)
bool kujuUI::type_1E3DB0::sub_2015D0()
{
    return true;
}
