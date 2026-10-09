// Split from unit_143CE0.cpp at 0x1442C0, where the image ends that object (its deferred
// functions come before the next out-of-line one; PLAN M7).

#include "rw/ostypes.h"
#include "rw/rpmaterial.h"
#include "types/type_143DC0.h"
#include "types/SplinePath.h"
#include "game/gameloop.h"
#include "rw/rt2d.h"
#include "game/functions.h"
#include "rw/babintex.h"
#include "types/type_141C10.h"
#include <string.h>

// match: __ehhandler$??0type_4E5CC8@@QAE@XZ>1>8 @ 0x0041DCB4
// match: __ehhandler$??0type_4E5CC8@@QAE@XZ>1 @ 0x0041DCBC
// match: __ehhandler$?sub_144330@type_4E5CC8@@QAEXXZ>1>8 @ 0x0041DCD8
// match: __ehhandler$?sub_144330@type_4E5CC8@@QAEXXZ>1 @ 0x0041DCE0
// match: __ehhandler$?sub_144420@type_4E5CC8@@QAEXXZ>1>8 @ 0x0041DCFC
// match: __ehhandler$?sub_144420@type_4E5CC8@@QAEXXZ>1 @ 0x0041DD04
// match: __ehhandler$?sub_1444B0@type_4E5CC8@@QAEXPAURpMaterial@@H@Z>1>8 @ 0x0041DD20
// match: __ehhandler$?sub_1444B0@type_4E5CC8@@QAEXPAURpMaterial@@H@Z>1 @ 0x0041DD28
// match: __ehhandler$?sub_144590@type_4E5CC8@@QAEXPAURpMaterial@@H@Z>1>8 @ 0x0041DD44
// match: __ehhandler$?sub_144590@type_4E5CC8@@QAEXPAURpMaterial@@H@Z>1 @ 0x0041DD4C
// match: ??_C@_0EK@INOCIAGB@TextureManager?3?5WARNING?3?5Texture@ @ 0x003DB998

// match: ??0type_4E5CC8@@QAE@XZ @ 0x001442C0
// match: __ehhandler$??0type_4E5CC8@@QAE@XZ-0x8 @ 0x00301A60
// match: __ehhandler$??0type_4E5CC8@@QAE@XZ @ 0x00301A68
// sp-match: ??0type_4E5CC8@@QAE@XZ @ 0x000EFC00
type_4E5CC8::type_4E5CC8()
{
    sub_144310();
}
// match: ?sub_144310@type_4E5CC8@@QAEXXZ @ 0x00144310
// sp-match: ?sub_144310@type_4E5CC8@@QAEXXZ @ 0x000EFA20
void type_4E5CC8::sub_144310()
{
    unk_00.sub_16B830();
    unk_0C = 0;
}
// match: ?sub_144330@type_4E5CC8@@QAEXXZ @ 0x00144330
// match: __ehhandler$?sub_144330@type_4E5CC8@@QAEXXZ-0x8 @ 0x00301A80
// match: __ehhandler$?sub_144330@type_4E5CC8@@QAEXXZ @ 0x00301A88
// sp-match: ?sub_144330@type_4E5CC8@@QAEXXZ @ 0x000EFC50
// Destroys its texture dictionary and deletes the animations.
void type_4E5CC8::sub_144330()
{
    if (unk_0C)
        RwTexDictionaryDestroy(unk_0C);
    for (type_16B900 var_14(&unk_00); var_14.sub_16B9D0(); var_14.sub_16BA10(0))
        delete (type_143DC0 *)var_14.sub_16B990();
}
// match: ?sub_144400@type_4E5CC8@@QAEXPAUtype_143DC0@@@Z @ 0x00144400
// sp-match: ?sub_144400@type_4E5CC8@@QAEXPAUtype_143DC0@@@Z @ 0x000EFA40
void type_4E5CC8::sub_144400(type_143DC0 *arg_0)
{
    unk_00.sub_16B8B0(arg_0);
}
// match: ?sub_144420@type_4E5CC8@@QAEXXZ @ 0x00144420
// sp-match: ?sub_144420@type_4E5CC8@@QAEXXZ @ 0x000EFA50
// Steps every animation, unless dword_4CFE24 holds them.
void type_4E5CC8::sub_144420()
{
    if (!dword_4CFE24)
    {
        for (type_16B900 var_14(&unk_00); var_14.sub_16B9D0(); var_14.sub_16BA10(0))
            ((type_143DC0 *)var_14.sub_1E3480())->sub_143F60();
    }
}
// match: ?sub_1444B0@type_4E5CC8@@QAEXPAURpMaterial@@H@Z @ 0x001444B0
// sp-match: ?sub_1444B0@type_4E5CC8@@QAEXPAURpMaterial@@H@Z @ 0x000EFD00
// Stops animating the material arg_0 (with arg_4): its entry in the first
// animation that has it is unlinked and deleted.
void type_4E5CC8::sub_1444B0(RpMaterial *arg_0, RwInt32 arg_4)
{
    for (type_16B900 var_14(&unk_00); var_14.sub_16B9D0(); var_14.sub_16BA10(0))
    {
        type_143D90 *var_18;

        var_18 = ((type_143DC0 *)var_14.sub_1E3480())->sub_1441A0(arg_0, arg_4);
        if (var_18)
        {
            var_18->sub_16BA30();
            delete var_18;
            break;
        }
    }
}
// match: ?sub_144590@type_4E5CC8@@QAEXPAURpMaterial@@H@Z @ 0x00144590
// match: __ehhandler$?sub_144590@type_4E5CC8@@QAEXPAURpMaterial@@H@Z-0x8 @ 0x00301AA0
// match: __ehhandler$?sub_144590@type_4E5CC8@@QAEXPAURpMaterial@@H@Z @ 0x00301AA8
// sp-match: ?sub_144590@type_4E5CC8@@QAEXPAURpMaterial@@H@Z @ 0x000EFAE0
// Animates the material arg_0 (with arg_4) by the animation named as its
// texture.
void type_4E5CC8::sub_144590(RpMaterial *arg_0, RwInt32 arg_4)
{
    RwTexture *var_10;

    var_10 = RpMaterialGetTexture(arg_0);
    if (var_10)
    {
        for (type_16B900 var_18(&unk_00); var_18.sub_16B9D0(); var_18.sub_16BA10(0))
        {
            type_143DC0 *var_1C;

            var_1C = (type_143DC0 *)var_18.sub_1E3480();
            if (strcmp(var_10->name, var_1C->unk_08))
                continue;
            ((type_143DC0 *)var_18.sub_1E3480())->sub_144110(arg_0, arg_4);
            break;
        }
    }
}
// match: ?sub_144650@type_4E5CC8@@QAEPAURwTexture@@PBD@Z @ 0x00144650
// sp-match: ?sub_144650@type_4E5CC8@@QAEPAURwTexture@@PBD@Z @ 0x000EFBD0
RwTexture *type_4E5CC8::sub_144650(const RwChar *arg_0)
{
    RwTexture *var_4;

    var_4 = 0;
    if (unk_0C)
        var_4 = RwTexDictionaryFindNamedTexture(unk_0C, arg_0);
    return var_4;
}
// match: ?sub_144690@type_4E5CC8@@QAEXPAURwTexDictionary@@@Z @ 0x00144690
// sp-match: ?sub_144690@type_4E5CC8@@QAEXPAURwTexDictionary@@@Z @ 0x000EFBF0
void type_4E5CC8::sub_144690(RwTexDictionary *arg_0)
{
    unk_0C = arg_0;
}
// match: sub_1446B0 @ 0x001446B0
// sp-match: sub_1446B0 @ 0x000EFDC0
// The shared texture dictionary (object).
void sub_1446B0()
{
    object = RwTexDictionaryCreate();
}
// match: sub_1446C0 @ 0x001446C0
// sp-match: sub_1446C0 @ 0x000EFFA0
void sub_1446C0()
{
    if (object)
    {
        RwTexDictionaryForAllTextures(object, fpCallBack, 0);
        RwTexDictionaryDestroy(object);
    }
}
// match: ?fpCallBack@@YAPAURwTexture@@PAU1@PAX@Z @ 0x00144700
// sp-match: ?fpCallBack@@YAPAURwTexture@@PAU1@PAX@Z @ 0x001C7590
// Destroys the texture arg_0, warning when something else still holds it.
RwTexture *fpCallBack(RwTexture *texture, void *pData)
{
#ifndef CODFH_SP // single player compiles the warning out: the body folds into destroyTexture
    if (texture->refCount > 2)
        sub_19A750("TextureManager: WARNING: Texture might not be destroyed! Ref count is: %d",
                   texture->refCount - 1);
#endif
    RwTextureDestroy(texture);
    return texture;
}
// match: sub_144740 @ 0x00144740
// sp-match: sub_144740 @ 0x000EFDD0
// RenderWare's RwTexDictionaryStreamRead (babintex.c) as the game adapted
// it: the textures go into the shared dictionary (object) instead of a new
// one, one it already holds is destroyed, and with arg_4 each kept texture
// gains a reference. Returns the dictionary, or 0.
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
RwTexDictionary *sub_144740(RwStream *arg_0, RwInt32 arg_4)
{
    RwUInt32 l4;
    RwUInt32 var_8;
    void *fp_C;
    RwUInt16 local_10;
    type_144740 stk_14;
    RwTexture *lcl_18;
    RwTexture *fp_1C;

    RwTexDictionarySetCurrent(object);
    if (!RwStreamFindChunk(arg_0, rwID_STRUCT, &l4, &var_8))
        return 0;
    if (var_8 >= rwLIBRARYBASEVERSION && var_8 <= rwLIBRARYCURRENTVERSION)
    {
        fp_C = &RWSRCGLOBAL(dOpenDevice);
        memset(&stk_14, 0, sizeof(stk_14));
        if (RwStreamRead(arg_0, &stk_14, l4) != l4)
            return 0;
        local_10 = 0;
        _rwDeviceSystemRequest(fp_C, rwDEVICESYSTEMGETID, &local_10, 0, 0);
        local_10 &= 0xFF;
        if (local_10 && stk_14.unk_02 && local_10 != stk_14.unk_02)
            return 0;
        while (stk_14.unk_00--)
        {
            lcl_18 = 0;
            if (!RwStreamFindChunk(arg_0, rwID_TEXTURENATIVE, &l4, &var_8))
                return 0;
            if (var_8 < rwLIBRARYBASEVERSION || var_8 > rwLIBRARYCURRENTVERSION)
                return 0;
            if (!RWSRCGLOBAL(stdFunc[rwSTANDARDNATIVETEXTUREREAD])(arg_0, &lcl_18, l4))
                return 0;
            if (!lcl_18)
                return 0;
            if (!_rwPluginRegistryReadDataChunks(&textureTKList, arg_0, lcl_18))
                return 0;
            fp_1C = RwTexDictionaryFindNamedTexture(object, lcl_18->name);
            if (fp_1C)
            {
                RwTextureDestroy(lcl_18);
            }
            else
            {
                if (arg_4)
                    lcl_18->refCount++;
                RwTexDictionaryAddTexture(object, lcl_18);
            }
        }
        if (!_rwPluginRegistryReadDataChunks(&texDictTKList, arg_0, object))
            return 0;
        return object;
    }
    return 0;
}
