// SplinePath: its MakeNew, constructor, destructor and handlers. Its original
// file name is not in the image, so it is named for its start address.

#include <xmmintrin.h>

#include "rw/ostypes.h"
#include "rw/badevice.h"
#include "rw/rpspline.h"
#include "rws/cattributehandler.h"
#include "rws/cclassfactory.h"
#include "rws/csystemcommands.h"
#include "rws/cresourcemanager.h"
#include "game/functions.h"
#include "types/SplinePath.h"
#include "types/type_72810.h"

RWS_IMPLEMENT_CLASSID(SplinePath);
RWS_REGISTERCLASS(SplinePath);
// Its data (PLAN M5): literals, constants and tables where the image has them.
// match: ??_C@_0L@DAHLGOFB@SplinePath?$AA@ @ 0x003D6624
// match: ??_7SplinePath@@6B@ @ 0x003D6630
// match: ??_C@_0M@GEDDLMCI@rwID_SPLINE?$AA@ @ 0x003D6640
// match: __ehhandler$?MakeNew@SplinePath@@SAPAVCAttributeHandler@RWS@@ABVCAttributePacket@3@@Z>1>8 @ 0x0041C214
// match: __ehhandler$?MakeNew@SplinePath@@SAPAVCAttributeHandler@RWS@@ABVCAttributePacket@3@@Z>1 @ 0x0041C21C
// match: __ehhandler$??0SplinePath@@QAE@ABVCAttributePacket@RWS@@@Z>1>8 @ 0x0041C238
// match: __ehhandler$??0SplinePath@@QAE@ABVCAttributePacket@RWS@@@Z>1 @ 0x0041C240
// match: __ehhandler$??1SplinePath@@UAE@XZ>1>8 @ 0x0041C25C
// match: __ehhandler$??1SplinePath@@UAE@XZ>1 @ 0x0041C264
// match: .CRT$XCU+0 @ 0x00426F6C
// match: ?pSplinePathClassID@SplinePath@@2PBDB @ 0x004291BC

// match: _$E2 @ 0x0030AB40
// match: _$E3 @ 0x0030E190

// (The class factory's registration and its exit thunk.)

// match: ?MakeNew@SplinePath@@SAPAVCAttributeHandler@RWS@@ABVCAttributePacket@3@@Z @ 0x000B9EA0
// match: __ehhandler$?MakeNew@SplinePath@@SAPAVCAttributeHandler@RWS@@ABVCAttributePacket@3@@Z-0xF @ 0x003003F0
// match: __ehhandler$?MakeNew@SplinePath@@SAPAVCAttributeHandler@RWS@@ABVCAttributePacket@3@@Z @ 0x003003FF
RWS_DEFINE_MAKENEW(SplinePath)

// match: ??0SplinePath@@QAE@ABVCAttributePacket@RWS@@@Z @ 0x000B9F20
// match: __ehhandler$??0SplinePath@@QAE@ABVCAttributePacket@RWS@@@Z-0x8 @ 0x00300410
// match: __ehhandler$??0SplinePath@@QAE@ABVCAttributePacket@RWS@@@Z @ 0x00300418
SplinePath::SplinePath(const RWS::CAttributePacket &attr)
{
    unk_2C.unk_00 = 0;
    unk_2C.unk_04 = 0;
    unk_1C = 0;
    unk_24 = 0.0f;
    unk_34 = sub_143D60(this);
    unk_28 = 0;
}

// match: ??_GSplinePath@@UAEPAXI@Z @ 0x000BA010

// match: ??1SplinePath@@UAE@XZ @ 0x000BA030
// match: __ehhandler$??1SplinePath@@UAE@XZ-0x8 @ 0x00300430
// match: __ehhandler$??1SplinePath@@UAE@XZ @ 0x00300438
// The empty destructor in SplinePath.h retains EH state 0 with this
// unit's /EHa setting (docs/toolchain.md).

// Command 0: its name (a kind 0x2E, which takes it through sub_BA420);
// 1: its end mode; 2: a flag.
// match: ?HandleAttributes@SplinePath@@UAEXABVCAttributePacket@RWS@@@Z @ 0x000BA080
void SplinePath::HandleAttributes(const RWS::CAttributePacket &attr)
{
    vf_008(attr);
    RWS::CAttributeCommandIterator attrIt(attr, RWS_CLASSID_OF(SplinePath));
    while (!attrIt.IsFinished())
    {
        switch (attrIt->GetCommandId())
        {
        case 0:
            unk_2C = *(const type_3DF8D8_04 *)attrIt->GetAs_RwChar_ptr();
            if (unk_2C.unk_00)
            {
                sub_198900((type_3DF8D8_04 *)&unk_2C, 0x2E, (void (*)(RwInt32, RwInt32, RwInt32))sub_BA420, 0,
                           (RwInt32)this, 0);
            }
            break;
        case 1:
            unk_1C_0 = attrIt->GetAs_RwUInt32();
            break;
        case 2:
            unk_1C_2 = attrIt->GetAs_RwUInt32();
            break;
        }
        ++attrIt;
    }
}

// match: ?vf_008@SplinePath@@UAEXABVCAttributePacket@RWS@@@Z @ 0x000BA1B0
void SplinePath::vf_008(const RWS::CAttributePacket &attr)
{
    RWS::CAttributeCommandIterator attrIt(attr, RWS::CSystemCommands::pCSystemCommandsClassID);
    while (!attrIt.IsFinished())
    {
        switch (attrIt->GetCommandId())
        {
        case RWS::CSystemCommands::CMD_AttachResource:
        {
            const RwChar *var_C = attrIt->GetAs_RwChar_ptr();

            vf_00C(var_C);
            break;
        }
        }
        ++attrIt;
    }
}

// match: ?vf_00C@SplinePath@@UAEXPBX@Z @ 0x000BA230
// Takes the attached resource arg_0 (a resource id) as its spline when it is
// an "rwID_SPLINE" (none for a resource of -1), and measures its length
// (unk_24) in steps of a hundredth of a segment.
void SplinePath::vf_00C(const void *arg_0)
{
    const RwChar *var_8;
    const RwChar *var_C;
    const void *var_10;
    RwReal var_14;
    RwInt32 var_18;
    RwReal var_1C;
    RwV3d var_28;
    RwV3d var_34;
    RwV3d var_40;
    RwReal var_44;

    var_10 = RWS::CResourceManager::FindById((const RWS::RWSGUID *)arg_0, &var_C, 0, &var_8);
    if (var_10)
    {
        if (*(const RwInt32 *)var_10 == -1)
        {
            unk_28 = 0;
        }
        else if (!rwstrcmp("rwID_SPLINE", var_C))
        {
            unk_28 = (RpSpline *)var_10;
            unk_24 = 0.0f;
            var_14 = 0.0f;
            var_18 = RpSplineGetNumControlPoints(unk_28);
            if (var_18 <= 1)
            {
                return;
            }
            var_1C = 1.0f / (var_18 - 1.0f);
            RpSplineFindPosition(unk_28, 0xA, var_14, &var_28, 0);
            while (var_14 < 1.0f)
            {
                var_14 += var_1C * 0.01f;
                if (var_14 > 1.0f)
                {
                    break;
                }
                RpSplineFindPosition(unk_28, 0xA, var_14, &var_34, 0);
                RwV3dSubMacro(&var_40, &var_28, &var_34);
                var_44 = RwV3dDotProductMacro(&var_40, &var_40);
                do
                {
                    __m128 a = _mm_set_ss(var_44);
                    __m128 b = _mm_sqrt_ss(a);
                    _mm_store_ss(&var_44, b);
                } while (0);
                unk_24 += var_44;
                var_28 = var_34;
            }
        }
    }
}

// match: ?sub_BA420@@YAHHHH@Z @ 0x000BA420
RwInt32 sub_BA420(RwInt32 arg_0, RwInt32 arg_4, RwInt32 arg_8)
{
    type_3DFEEC *var_4 = (type_3DFEEC *)arg_0;

    var_4->unk_24 = (SplinePath *)arg_8;
    var_4->unk_10 = 0x80;
    return 1;
}

// match: ?sub_BA450@SplinePath@@QAEMPAURwV3d@@MM@Z @ 0x000BA450
RwReal SplinePath::sub_BA450(RwV3d *arg_0, RwReal arg_4, RwReal arg_8)
{
    RwInt32 var_8;
    RwReal var_C;
    RwReal var_10;
    RwReal var_14;
    RwInt32 var_18;
    RwReal var_1C;
    RwInt32 var_20;
    RwReal var_24;
    RwV3d var_30;
    RwV3d var_3C;
    RwReal var_40;
    RwReal var_44;
    RwReal var_48;
    RwReal var_4C;
    RwV3d var_58;
    RwV3d var_64;
    RwV3d var_70;
    RwReal var_74;
    RwReal var_D4;
    RwReal var_D8;
    RwReal var_DC;
    RwReal var_E0;
    RwV3d var_EC;
    RwV3d var_F8;
    RwV3d var_104;
    RwReal var_108;
    RwReal var_164;

    var_8 = 0;
    var_C = 0.0f;
    var_10 = 0.0f;
    var_14 = 0.0f;
    var_18 = RpSplineGetNumControlPoints(unk_28);
    if (var_18 <= 1)
    {
        return 0.0f;
    }
    var_1C = 1.0f / (var_18 - 1.0f);
    for (var_20 = 0; var_20 < var_18; var_20++)
    {
        var_24 = var_20 * var_1C;
        RpSplineFindPosition(unk_28, 0xA, var_24, &var_30, 0);
        RwV3dSubMacro(&var_3C, arg_0, &var_30);
        var_3C.y *= arg_8;
        var_40 = RwV3dDotProductMacro(&var_3C, &var_3C);
        if (!var_8 || var_40 < var_C)
        {
            var_8 = 1;
            var_C = var_40;
            var_14 = var_24;
            var_10 = (RwReal)var_20;
        }
    }
    if (var_10 > 0.0f)
    {
        var_44 = (var_10 - 1.0f) * var_1C;
        var_48 = var_10 * var_1C;
        var_4C = var_44;
        RpSplineFindPosition(unk_28, 0xA, var_44, &var_58, 0);
        RpSplineFindPosition(unk_28, 0xA, var_48, &var_64, 0);
        RwV3dSubMacro(&var_70, &var_58, &var_64);
        var_74 = RwV3dDotProductMacro(&var_70, &var_70);
        do
        {
            __m128 a = _mm_set_ss(var_74);
            __m128 b = _mm_sqrt_ss(a);
            _mm_store_ss(&var_74, b);
        } while (0);
        var_74 = arg_4 / var_74 * var_1C;
        while (var_4C < var_48)
        {
            RpSplineFindPosition(unk_28, 0xA, var_4C, &var_30, 0);
            RwV3dSubMacro(&var_3C, arg_0, &var_30);
            var_3C.y *= arg_8;
            var_D4 = RwV3dDotProductMacro(&var_3C, &var_3C);
            if (var_D4 < var_C)
            {
                var_C = var_D4;
                var_14 = var_4C;
            }
            var_4C += var_74;
        }
    }
    if (var_10 + 1.0f < var_18)
    {
        var_D8 = var_10 * var_1C;
        var_DC = (var_10 + 1.0f) * var_1C;
        var_E0 = var_D8;
        RpSplineFindPosition(unk_28, 0xA, var_D8, &var_EC, 0);
        RpSplineFindPosition(unk_28, 0xA, var_DC, &var_F8, 0);
        RwV3dSubMacro(&var_104, &var_EC, &var_F8);
        var_108 = RwV3dDotProductMacro(&var_104, &var_104);
        do
        {
            __m128 a = _mm_set_ss(var_108);
            __m128 b = _mm_sqrt_ss(a);
            _mm_store_ss(&var_108, b);
        } while (0);
        var_108 = arg_4 / var_108 * var_1C;
        while (var_E0 <= var_DC)
        {
            RpSplineFindPosition(unk_28, 0xA, var_E0, &var_30, 0);
            RwV3dSubMacro(&var_3C, arg_0, &var_30);
            var_3C.y *= arg_8;
            var_164 = RwV3dDotProductMacro(&var_3C, &var_3C);
            if (var_164 < var_C)
            {
                var_C = var_164;
                var_14 = var_E0 + var_108;
            }
            var_E0 += var_108;
        }
    }
    if (var_14 > 1.0f)
    {
        var_14 = 1.0f;
    }
    return var_14;
}

// match: ?sub_BA990@SplinePath@@QAEXMPAURwV3d@@PAURwMatrixTag@@@Z @ 0x000BA990
void SplinePath::sub_BA990(RwReal arg_0, RwV3d *arg_4, RwMatrix *arg_8)
{
    if (!arg_4)
    {
        return;
    }
    RpSplineFindPosition(unk_28, 0xA, arg_0, arg_4, 0);
    if (arg_8)
    {
        sub_1414C0(arg_4, arg_4, arg_8);
    }
}
