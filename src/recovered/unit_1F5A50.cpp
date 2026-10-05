/*
 * kujuUI's text page (game/kujufont.h): a growing array of Im2D vertices, the
 * quads of one texture page of a laid-out string, placed, drawn and emptied.
 */
#include "game/kujufont.h"
#include "game/kujuui.h"

using namespace kujuUI;

// match: ??0type_1F5A50@@QAE@XZ @ 0x001F5A50
type_1F5A50::type_1F5A50()
{
    unk_00 = 0;
    unk_04 = 0;
    unk_08 = 0;
    unk_0C = 0;
    unk_10 = 0;
}

// match: ??0type_1F5A50@@QAE@I@Z @ 0x001F5A90
type_1F5A50::type_1F5A50(RwUInt32 arg_0)
{
    unk_00 = new RwIm2DVertex[arg_0];
    unk_04 = 0;
    unk_08 = arg_0;
    unk_0C = 0;
    unk_10 = 0;
}

// match: ??1type_1F5A50@@QAE@XZ @ 0x001F5AF0
type_1F5A50::~type_1F5A50()
{
    if (unk_08 > 0)
        delete unk_00;
}

// match: ?sub_1F5B20@type_1F5A50@@QAEXI@Z @ 0x001F5B20
void type_1F5A50::sub_1F5B20(RwUInt32 arg_0)
{
    unk_08 = arg_0;
    RwIm2DVertex *var_4 = new RwIm2DVertex[arg_0];
    if (unk_04 > 0)
        memcpy(var_4, unk_00, unk_04 * sizeof(RwIm2DVertex));
    delete unk_00;
    unk_00 = var_4;
}

// match: ?sub_1F5BA0@type_1F5A50@@QAEXXZ @ 0x001F5BA0
void type_1F5A50::sub_1F5BA0()
{
    unk_04 = 0;
    unk_0C = 0;
    unk_10 = 0;
    unk_08 = 0;
    delete unk_00;
    unk_00 = 0;
}

// match: ?sub_1F5C00@type_1F5A50@@QAEXXZ @ 0x001F5C00
void type_1F5A50::sub_1F5C00()
{
    RwIm2DRenderPrimitive(rwPRIMTYPETRILIST, unk_00, unk_04);
}

// match: ?sub_1F5C30@type_1F5A50@@QAEXPBUtype_1E0330_rect@kujuUI@@MM0I@Z @ 0x001F5C30
void type_1F5A50::sub_1F5C30(const type_1E0330_rect *arg_0, RwReal arg_4, RwReal arg_8, const type_1E0330_rect *arg_C,
                             RwUInt32 arg_10)
{
    if (unk_08 == 0)
    {
        unk_00 = new RwIm2DVertex[6];
        unk_08 = 6;
    }
    else
    {
        while (unk_08 < unk_04 + 6)
            sub_1F5B20(unk_08 * 2);
    }
    sub_1DFC30(&arg_0->unk_00, arg_4, arg_8, &arg_C->unk_00, &unk_00[unk_04], arg_10);
    unk_04 += 6;
}

// match: ?sub_1F5CD0@type_1F5A50@@QAEXMM@Z @ 0x001F5CD0
void type_1F5A50::sub_1F5CD0(RwReal arg_0, RwReal arg_4)
{
    RwReal var_C = arg_0 - unk_0C;
    RwReal bp_8 = arg_4 - unk_10;
    RwIm2DVertex *bp_4 = unk_00;
    RwIm2DVertex *var_10 = &unk_00[unk_04];
    while (bp_4 != var_10)
    {
        sub_1DFDA0(sub_1DFD80(bp_4) + var_C, sub_1DFD90(bp_4) + bp_8, bp_4);
        ++bp_4;
    }
    unk_0C = arg_0;
    unk_10 = arg_4;
}
