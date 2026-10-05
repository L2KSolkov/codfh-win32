/*
 * kujuUI's quad (game/kujuui.h): two triangles of Im2D vertices, put off
 * screen, drawn, moved, set from a rectangle and coloured.
 */
#include "game/kujuui.h"

using namespace kujuUI;

// match: ??0type_1EEAD0@kujuUI@@QAE@XZ @ 0x001EEAD0
type_1EEAD0::type_1EEAD0()
{
    unk_A8 = 0.0f;
    unk_AC = 0.0f;
}

// match: ?sub_1EEB00@type_1EEAD0@kujuUI@@QAEXXZ @ 0x001EEB00
void type_1EEAD0::sub_1EEB00()
{
    for (RwUInt32 var_4 = 0; var_4 != 6; ++var_4)
        sub_1DFBB0(-1000.0f, -1000.0f, 1.0f, 20.0f, 0.0f, 0.0f, 0, &unk_00[var_4]);
}

// match: ?sub_1EEB60@type_1EEAD0@kujuUI@@QAEXXZ @ 0x001EEB60
void type_1EEAD0::sub_1EEB60()
{
    RwIm2DRenderPrimitive(rwPRIMTYPETRILIST, unk_00, 6);
}

// match: ?sub_1EEB80@type_1EEAD0@kujuUI@@QAEXMM@Z @ 0x001EEB80
void type_1EEAD0::sub_1EEB80(RwReal arg_0, RwReal arg_4)
{
    RwReal var_C = arg_0 - unk_A8;
    RwReal bp_8 = arg_4 - unk_AC;
    RwIm2DVertex *bp_4 = unk_00;
    RwIm2DVertex *var_10 = &unk_00[6];
    while (bp_4 != var_10)
    {
        sub_1DFDA0(sub_1DFD80(bp_4) + var_C, sub_1DFD90(bp_4) + bp_8, bp_4);
        ++bp_4;
    }
    unk_A8 = arg_0;
    unk_AC = arg_4;
}

// match: ?sub_1EEC20@type_1EEAD0@kujuUI@@QAEXPBUtype_1E0330_rect@2@MM0I@Z @ 0x001EEC20
void type_1EEAD0::sub_1EEC20(const type_1E0330_rect *arg_0, RwReal arg_4, RwReal arg_8, const type_1E0330_rect *arg_C,
                             RwUInt32 arg_10)
{
    sub_1DFC30(&arg_0->unk_00, arg_4, arg_8, &arg_C->unk_00, unk_00, arg_10);
}

// match: ?sub_1EEC50@type_1EEAD0@kujuUI@@QAEXI@Z @ 0x001EEC50
void type_1EEAD0::sub_1EEC50(RwUInt32 arg_0)
{
    RwUInt32 var_10 = arg_0 & 0xFF;
    RwUInt32 var_C = arg_0 >> 8 & 0xFF;
    RwUInt32 bp_8 = arg_0 >> 16 & 0xFF;
    RwUInt32 bp_4 = arg_0 >> 24 & 0xFF;
    for (RwUInt32 var_14 = 0; var_14 != 6; ++var_14)
        unk_00[var_14].emissiveColor = bp_4 << 24 | var_10 << 16 | var_C << 8 | bp_8;
}

// Functions /OPT:ICF folded into another body (config/aliases.txt), defined here for the
// authentic link (PLAN M7) with that body; the placement link takes the folded one.

// ??1type_1EEAD0@kujuUI@@QAE@XZ (folded into 0x1E41C0)
kujuUI::type_1EEAD0::~type_1EEAD0()
{
}
