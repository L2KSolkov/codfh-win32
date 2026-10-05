/*
 * kujuUI's quad helpers and the pad's event mapper (game/kujuui.h): the
 * start of \COD\SHARED\UI\ (its data, off_3E6CE4 on, follows the voice
 * channel's).
 */
#include <string.h>

#include "game/kujuui.h"
#include "game/frontend.h"
#include "game/parsedfile.h"
#include "types/type_4D1DB8.h"

// Its data definitions (PLAN M5), in the image's address order.
// 0x003E6CE0
extern const RwReal flt_3E6CE0 = 1.0f;
// End of its data definitions.


// Globals with constructors defined here (their initializers and exit
// functions at the end of .text).
kujuUI::type_1E0330_rect kujuUI::unk_503308;
// Vtables (.rdata, PLAN M5): each in its own placement range (config/splits.txt).
// Its data (PLAN M5): literals, constants and tables where the image has them.
// match: ?flt_3E6CE0@@3MB @ 0x003E6CE0
// match: ??_7type_3E6CE4@kujuUI@@6B@ @ 0x003E6CE4
// match: ??_7type_3E6CEC@kujuUI@@6B@ @ 0x003E6CEC
// match: .CRT$XCU+0 @ 0x00427238

// match: _$E1 @ 0x0030C9E0

namespace kujuUI {

// match: ?sub_1DFBB0@kujuUI@@YAXMMMMMMIPAURwD3D8Vertex@@@Z @ 0x001DFBB0
void sub_1DFBB0(RwReal arg_0, RwReal arg_4, RwReal arg_8, RwReal arg_C, RwReal arg_10, RwReal arg_14,
                RwUInt32 arg_18, RwIm2DVertex *arg_1C)
{
    RwIm2DVertexSetScreenX(arg_1C, arg_0 * flt_3E6CE0);
    RwIm2DVertexSetScreenY(arg_1C, arg_4);
    RwIm2DVertexSetScreenZ(arg_1C, arg_8);
    RwIm2DVertexSetRecipCameraZ(arg_1C, arg_C);
    RwIm2DVertexSetU(arg_1C, arg_10, arg_C);
    RwIm2DVertexSetV(arg_1C, arg_14, arg_C);
    RwIm2DVertexSetIntRGBA(arg_1C, arg_18 & 0xFF, (arg_18 >> 8) & 0xFF, (arg_18 >> 16) & 0xFF, (arg_18 >> 24) & 0xFF);
}

// match: ?sub_1DFC30@kujuUI@@YAXPBMMM0PAURwD3D8Vertex@@I@Z @ 0x001DFC30
void sub_1DFC30(const RwReal *arg_0, RwReal arg_4, RwReal arg_8, const RwReal *arg_C, RwIm2DVertex *arg_10,
                RwUInt32 arg_14)
{
    sub_1DFBB0(arg_0[0], arg_0[1], arg_4, arg_8, arg_C[0], arg_C[1], arg_14, &arg_10[0]);
    sub_1DFBB0(arg_0[0], arg_0[3], arg_4, arg_8, arg_C[0], arg_C[3], arg_14, &arg_10[1]);
    sub_1DFBB0(arg_0[2], arg_0[1], arg_4, arg_8, arg_C[2], arg_C[1], arg_14, &arg_10[2]);
    sub_1DFBB0(arg_0[0], arg_0[3], arg_4, arg_8, arg_C[0], arg_C[3], arg_14, &arg_10[3]);
    sub_1DFBB0(arg_0[2], arg_0[1], arg_4, arg_8, arg_C[2], arg_C[1], arg_14, &arg_10[5]);
    sub_1DFBB0(arg_0[2], arg_0[3], arg_4, arg_8, arg_C[2], arg_C[3], arg_14, &arg_10[4]);
}

// match: ?sub_1DFD80@kujuUI@@YAMPBURwD3D8Vertex@@@Z @ 0x001DFD80
RwReal sub_1DFD80(const RwIm2DVertex *arg_0)
{
    return arg_0->x / flt_3E6CE0;
}

// match: ?sub_1DFD90@kujuUI@@YAMPBURwD3D8Vertex@@@Z @ 0x001DFD90
RwReal sub_1DFD90(const RwIm2DVertex *arg_0)
{
    return arg_0->y;
}

// match: ?sub_1DFDA0@kujuUI@@YAXMMPAURwD3D8Vertex@@@Z @ 0x001DFDA0
void sub_1DFDA0(RwReal arg_0, RwReal arg_4, RwIm2DVertex *arg_8)
{
    RwIm2DVertexSetScreenX(arg_8, arg_0 * flt_3E6CE0);
    RwIm2DVertexSetScreenY(arg_8, arg_4);
}

// match: ??1type_3E6CEC@kujuUI@@UAE@XZ @ 0x001DFDC0
type_3E6CEC::~type_3E6CEC()
{
}

// match: ??_Gtype_3E6CEC@kujuUI@@UAEPAXI@Z @ 0x001DFDE0

// match: ??0type_3E6CEC@kujuUI@@QAE@XZ @ 0x001DFE10
type_3E6CEC::type_3E6CEC()
{
    unk_38 = 14;
    memset(unk_04, 0, sizeof(unk_04));
}

// match: ?sub_1DFE50@type_3E6CEC@kujuUI@@QAEXHPAUtype_1DFE80_target@2@@Z @ 0x001DFE50
void type_3E6CEC::sub_1DFE50(RwInt32 arg_0, type_1DFE80_target *arg_4)
{
    RwInt32 var_4 = arg_0;

    unk_04[var_4] = arg_4;
}

// match: ?processEvent@type_3E6CEC@kujuUI@@UAE?AW4eEventWasHandled@2@ABVcStateChange@2@@Z @ 0x001DFE80
eEventWasHandled type_3E6CEC::processEvent(const cStateChange &arg_0)
{
    RwInt32 var_4 = arg_0.get_unk_00();
    RwInt32 var_8 = var_4;
    type_1DFE80_target *var_C = unk_04[var_8];

    if (var_C)
    {
        if (arg_0.get_unk_04() == 0 && var_C->vf_00C())
            unk_38 = arg_0.get_unk_00();
        if (arg_0.get_unk_04() == 1 && var_C->vf_00C() && arg_0.get_unk_00() == unk_38)
        {
            var_C->vf_008();
            if (dword_504378)
                dword_504378->vf_04(3);
        }
        return (eEventWasHandled)0;
    }
    return (eEventWasHandled)1;
}














}
