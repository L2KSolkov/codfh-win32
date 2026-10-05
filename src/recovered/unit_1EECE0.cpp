/*
 * kujuUI's texture (game/kujufont.h): an RwImage over a 32-bit image, a
 * raster made from one, or a texture read from a .bin; and the loaders
 * from a .tga and a .bin.
 */
#include "game/kujufont.h"
#include "game/ddsload.h"
#include "rw/baimage.h"
#include "rw/batextur.h"

// Its data (PLAN M5): literals, constants and tables where the image has them.
// match: __ehhandler$?sub_1EEDA0@@YAXPAUtype_1E6B50@@PAPAUtype_1EEEE0@@@Z>1>8 @ 0x0042091C
// match: __ehhandler$?sub_1EEDA0@@YAXPAUtype_1E6B50@@PAPAUtype_1EEEE0@@@Z>1 @ 0x0042092C
// match: __ehhandler$?sub_1EEFB0@@YAXPBDPAPAUtype_1EEEE0@@@Z>1>8 @ 0x00420948
// match: __ehhandler$?sub_1EEFB0@@YAXPBDPAPAUtype_1EEEE0@@@Z>1 @ 0x00420950

// match: ??0type_1EECE0@@QAE@PAUtype_1E6B50@@@Z @ 0x001EECE0

type_1EECE0::type_1EECE0(type_1E6B50 *arg_0)
{
    unk_00 = RwImageCreate(arg_0->get_unk_00(), arg_0->get_unk_04(), 32);
    set_stride(32, arg_0->get_unk_00());
    RwUInt32 *bp_4 = arg_0->unk_08;
    RwUInt8 *var_8 = (RwUInt8 *)bp_4;
    var_8[0] = 0x40;
    var_8[1] = 0x80;
    var_8[2] = 0xC0;
    var_8[3] = 0xE0;
    unk_00 = RwImageSetPixels(unk_00, var_8);
}

// match: ??1type_1EECE0@@QAE@XZ @ 0x001EED80
type_1EECE0::~type_1EECE0()
{
    RwImageDestroy(unk_00);
}

// match: ?sub_1EEDA0@@YAXPAUtype_1E6B50@@PAPAUtype_1EEEE0@@@Z @ 0x001EEDA0
// match: __ehhandler$?sub_1EEDA0@@YAXPAUtype_1E6B50@@PAPAUtype_1EEEE0@@@Z-0x13 @ 0x00304070
// match: __ehhandler$?sub_1EEDA0@@YAXPAUtype_1E6B50@@PAPAUtype_1EEEE0@@@Z @ 0x00304083
void sub_1EEDA0(type_1E6B50 *arg_0, type_1EEEE0 **arg_4)
{
    type_1EECE0 var_10(arg_0);
    *arg_4 = new type_1EEEE0(var_10);
}

// match: ??0type_1EEEE0@@QAE@ABUtype_1EECE0@@@Z @ 0x001EEE30
type_1EEEE0::type_1EEEE0(const type_1EECE0 &arg_0) : unk_00(0), unk_04(0)
{
    RwImage *bp_4 = arg_0.unk_00;
    RwInt32 lv_C = RwImageGetWidth(bp_4);
    RwInt32 var_8 = RwImageGetHeight(bp_4);
    const RwInt32 var_10 = 8;
    unk_00 = RwRasterCreate(lv_C, var_8, var_10, rwRASTERTYPETEXTURE);
    unk_00 = RwRasterSetFromImage(unk_00, bp_4);
}

// match: ??0type_1EEEE0@@QAE@PAURwTexture@@@Z @ 0x001EEEB0
type_1EEEE0::type_1EEEE0(RwTexture *arg_0)
{
    unk_04 = arg_0;
    unk_00 = RwTextureGetRaster(arg_0);
}

// match: ??1type_1EEEE0@@QAE@XZ @ 0x001EEEE0
type_1EEEE0::~type_1EEEE0()
{
    if (unk_04)
    {
        sub_1C9BE0(unk_04);
        unk_00 = 0;
    }
    else
        RwRasterDestroy(unk_00);
}

// match: ?sub_1EEF20@@YAXPBDPAPAUtype_1EEEE0@@@Z @ 0x001EEF20
void sub_1EEF20(const RwChar *arg_0, type_1EEEE0 **arg_4)
{
    type_1E6B50 *var_4 = 0;
    sub_1E6CD0(arg_0, &var_4);
    if (var_4)
    {
        sub_1EEDA0(var_4, arg_4);
        delete var_4;
    }
    else
        *arg_4 = 0;
}

// match: ?sub_1EEFB0@@YAXPBDPAPAUtype_1EEEE0@@@Z @ 0x001EEFB0
// match: __ehhandler$?sub_1EEFB0@@YAXPBDPAPAUtype_1EEEE0@@@Z-0xB @ 0x00304090
// match: __ehhandler$?sub_1EEFB0@@YAXPBDPAPAUtype_1EEEE0@@@Z @ 0x0030409B
void sub_1EEFB0(const RwChar *arg_0, type_1EEEE0 **arg_4)
{
    RwTexture *var_10 = sub_1C9B40(arg_0);
    if (var_10)
        *arg_4 = new type_1EEEE0(var_10);
    else
        *arg_4 = 0;
}
