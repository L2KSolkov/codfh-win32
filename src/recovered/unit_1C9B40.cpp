// Reading a DDS texture from a kujuUI file (game/ddsload.h).

#include <string.h>

#include "game/ddsload.h"

// Its data definitions (PLAN M5), in the image's address order.
// 0x004FEAB4
RwFileFunctions dword_4FEAB4;
// 0x004FEAE0
const RwChar *dword_4FEAE0;
// 0x004FEAE4
kujuUI::cFileIn *dword_4FEAE4;
// 0x004FEAE8
bool byte_4FEAE8;
// End of its data definitions.


// Its data (PLAN M5): literals, constants and tables where the image has them.
// match: ??_C@_04LIKELABK@?4dds?$AA@ @ 0x003E3C84

// match: ?sub_1C9B40@@YAPAURwTexture@@PBD@Z @ 0x001C9B40

// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
RwTexture *sub_1C9B40(const RwChar *arg_0)
{
    RwTexture *var_8;
    kujuUI::cFileIn *l4;

    l4 = 0;
    kujuUI::sub_1C8CA0(arg_0, &l4);
    dword_4FEAE4 = l4;
    sub_1C9C20(".dds");
    var_8 = 0;
    var_8 = RwXboxDDSTextureRead(arg_0, 0);
    if (1)
        sub_1C9CC0();
    delete l4;
    return var_8;
}

// match: ?sub_1C9BE0@@YAXPAURwTexture@@@Z @ 0x001C9BE0
void sub_1C9BE0(RwTexture *arg_0)
{
    RwTexDictionary *var_4;

    var_4 = arg_0->dict;
    if (var_4)
        RwTexDictionaryDestroy(var_4);
    else
        RwTextureDestroy(arg_0);
}

// match: ?sub_1C9C20@@YA_NPBD@Z @ 0x001C9C20
bool sub_1C9C20(const RwChar *arg_0)
{
    RwFileFunctions *var_4;

    if (byte_4FEAE8 == true)
        return false;
    if (0)
        return false;
    var_4 = RwOsGetFileInterface();
    memcpy(&dword_4FEAB4, var_4, sizeof(RwFileFunctions));
    memset(var_4, 0, sizeof(RwFileFunctions));
    var_4->rwfexist = sub_1C9D10;
    var_4->rwfopen = (void *(*)(const RwChar *, const RwChar *))sub_1C9D10;
    var_4->rwfread = sub_1C9D40;
    var_4->rwfclose = sub_31DB0;
    var_4->rwfeof = sub_1C9E80;
    var_4->rwfseek = sub_1C9DC0;
    dword_4FEAE0 = arg_0;
    byte_4FEAE8 = true;
    return byte_4FEAE8;
}

// match: ?sub_1C9CC0@@YA_NXZ @ 0x001C9CC0
bool sub_1C9CC0()
{
    RwFileFunctions *var_4;

    if (byte_4FEAE8 == true)
    {
        var_4 = RwOsGetFileInterface();
        memcpy(var_4, &dword_4FEAB4, sizeof(RwFileFunctions));
        dword_4FEAE0 = 0;
        dword_4FEAE4 = 0;
        byte_4FEAE8 = false;
        return true;
    }
    return false;
}

// match: ?sub_1C9D10@@YAHPBD@Z @ 0x001C9D10
RwBool sub_1C9D10(const RwChar *arg_0)
{
    if (strstr(arg_0, dword_4FEAE0))
        return 1;
    return 0;
}

// match: ?sub_1C9D40@@YAIPAXII0@Z @ 0x001C9D40
size_t sub_1C9D40(void *arg_0, size_t arg_4, size_t arg_8, void *arg_C)
{
    RwFileFunctions var_2C;
    size_t var_30;

    memcpy(&var_2C, RwOsGetFileInterface(), sizeof(RwFileFunctions));
    memcpy(RwOsGetFileInterface(), &dword_4FEAB4, sizeof(RwFileFunctions));
    var_30 = 0;
    if (dword_4FEAE4->sub_1C8BA0(arg_0, arg_4 * arg_8))
        var_30 = arg_4 * arg_8;
    memcpy(RwOsGetFileInterface(), &var_2C, sizeof(RwFileFunctions));
    return var_30;
}

// match: ?sub_1C9DC0@@YAHPAXJH@Z @ 0x001C9DC0
RwInt32 sub_1C9DC0(void *arg_0, RwFileSeekOffset arg_4, RwInt32 arg_8)
{
    RwFileFunctions lv_2C;
    RwChar var_130[0x100];
    RwUInt32 frm_134;
    RwUInt32 var_138;

    memcpy(&lv_2C, RwOsGetFileInterface(), sizeof(RwFileFunctions));
    memcpy(RwOsGetFileInterface(), &dword_4FEAB4, sizeof(RwFileFunctions));
    frm_134 = arg_4;
    while (frm_134)
    {
        var_138 = 0x100;
        if (frm_134 < 0x100)
            var_138 = frm_134;
        dword_4FEAE4->sub_1C8BA0(var_130, var_138);
        frm_134 -= var_138;
    }
    memcpy(RwOsGetFileInterface(), &lv_2C, sizeof(RwFileFunctions));
    return 0;
}

// match: ?sub_1C9E80@@YAHPAX@Z @ 0x001C9E80
RwInt32 sub_1C9E80(void *arg_0)
{
    if (dword_4FEAE4->sub_1C8DC0())
        return 1;
    return 0;
}
