// WorldLight: its MakeNew, constructor, destructor and handlers. Its
// original file name is not in the image, so it is named for its start
// address.

#include "rw/ostypes.h"
#include "rw/baframe.h"
#include "rw/rplight.h"
#include "rws/cattributehandler.h"
#include "rws/cclassfactory.h"
#include "types/type_129_base.h"
#include "types/WorldLight.h"

RWS_IMPLEMENT_CLASSID(WorldLight);
RWS_REGISTERCLASS(WorldLight);
// Its data (PLAN M5): literals, constants and tables where the image has them.
// match: ??_C@_0L@IECHNJOD@WorldLight?$AA@ @ 0x003D6AA4
// match: ??_7WorldLight@@6BCEventHandler@RWS@@@ @ 0x003D6AB0
// match: ??_7WorldLight@@6BCAttributeHandler@RWS@@@ @ 0x003D6AB8
// match: __real@437f0000 @ 0x003D6AE8
// match: __ehhandler$?MakeNew@WorldLight@@SAPAVCAttributeHandler@RWS@@ABVCAttributePacket@3@@Z>1>8 @ 0x0041C570
// match: __ehhandler$?MakeNew@WorldLight@@SAPAVCAttributeHandler@RWS@@ABVCAttributePacket@3@@Z>1 @ 0x0041C578
// match: __ehhandler$??0WorldLight@@QAE@ABVCAttributePacket@RWS@@@Z>1>8 @ 0x0041C594
// match: __ehhandler$??0WorldLight@@QAE@ABVCAttributePacket@RWS@@@Z>1 @ 0x0041C5A4
// match: __ehhandler$??1type_129BD0@@QAE@XZ>1>8 @ 0x0041C5C0
// match: __ehhandler$??1type_129BD0@@QAE@XZ>1 @ 0x0041C5C8
// match: __ehhandler$??1WorldLight@@UAE@XZ>1>8 @ 0x0041C5E4
// match: __ehhandler$??1WorldLight@@UAE@XZ>1 @ 0x0041C5FC
// match: .CRT$XCU+0 @ 0x00426FA0
// match: ?pWorldLightClassID@WorldLight@@2PBDB @ 0x004291F0

// match: _$E2 @ 0x0030ADB0
// match: _$E3 @ 0x0030E260

// (The class factory's registration and its exit thunk.)

// match: ?MakeNew@WorldLight@@SAPAVCAttributeHandler@RWS@@ABVCAttributePacket@3@@Z @ 0x000C5380
// match: __ehhandler$?MakeNew@WorldLight@@SAPAVCAttributeHandler@RWS@@ABVCAttributePacket@3@@Z-0xF @ 0x00300690
// match: __ehhandler$?MakeNew@WorldLight@@SAPAVCAttributeHandler@RWS@@ABVCAttributePacket@3@@Z @ 0x0030069F
// sp-match: ?MakeNew@WorldLight@@SAPAVCAttributeHandler@RWS@@ABVCAttributePacket@3@@Z @ 0x000965D0
RWS_DEFINE_MAKENEW(WorldLight)

// A white light of no type yet: its type comes with command 0.
// match: ??0WorldLight@@QAE@ABVCAttributePacket@RWS@@@Z @ 0x000C5400
// match: __ehhandler$??0WorldLight@@QAE@ABVCAttributePacket@RWS@@@Z-0x16 @ 0x003006B0
// match: __ehhandler$??0WorldLight@@QAE@ABVCAttributePacket@RWS@@@Z @ 0x003006C6
// sp-match: ??0WorldLight@@QAE@ABVCAttributePacket@RWS@@@Z @ 0x00096260
WorldLight::WorldLight(const RWS::CAttributePacket &attr)
    : Trigger(attr), unk_C0(0), unk_C8(1000.0f), unk_CC(3), unk_D0(0xFFFFFFFF)
{
    unk_C4 = 0.78539819f;
    unk_D4.sub_129BD0(0);
}

// match: ??1type_129BD0@@QAE@XZ @ 0x000C54E0
// match: __ehhandler$??1type_129BD0@@QAE@XZ-0x8 @ 0x003006D0
// match: __ehhandler$??1type_129BD0@@QAE@XZ @ 0x003006D8
// (Defined in the struct, in type_129_base.h; out of line for the
// constructor's unwinding.)

// match: ?vf_008@WorldLight@@UAEHXZ @ 0x000C5540
// sp-match: ?vf_008@WorldLight@@UAEHXZ @ 0x00028FF0
RwInt32 WorldLight::vf_008()
{
    return 3;
}

// match: ??_GWorldLight@@UAEPAXI@Z @ 0x000C5550
// sp-match: ??_GWorldLight@@UAEPAXI@Z @ 0x000965C0

// match: ??1WorldLight@@UAE@XZ @ 0x000C5570
// match: __ehhandler$??1WorldLight@@UAE@XZ-0x1E @ 0x003006F0
// match: __ehhandler$??1WorldLight@@UAE@XZ @ 0x0030070E
// sp-match: ??1WorldLight@@UAE@XZ @ 0x00096310
WorldLight::~WorldLight()
{
    if (unk_D4.get_unk_08())
    {
        unk_D4.sub_129C40();
    }
}

// Command 0 makes a new light of its type (0 to 5: none, directional,
// ambient, point, spot, soft spot); 1 to 4 set its settings, which are then
// given to it.
// match: ?HandleAttributes@WorldLight@@UAEXABVCAttributePacket@RWS@@@Z @ 0x000C5630
// sp-match: ?HandleAttributes@WorldLight@@UAEXABVCAttributePacket@RWS@@@Z @ 0x000963A0
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void WorldLight::HandleAttributes(const RWS::CAttributePacket &attr)
{
    RwFrame *bp_18;
    RpLight *var_14;
    RwInt32 lv_10;

    Trigger::HandleAttributes(attr);
    if (unk_D4.get_unk_08())
    {
        RWS::LightHelper::HandleSystemCommands(*unk_D4.get_unk_08(), attr);
    }
    RwInt32 var_C = 0;
    RWS::CAttributeCommandIterator bp_8(attr, RWS_CLASSID_OF(WorldLight));
    while (!bp_8.IsFinished())
    {
        switch (bp_8->GetCommandId())
        {
        case 0:
            lv_10 = bp_8->GetAs_RwInt32();
            switch (lv_10)
            {
            case 0:
                lv_10 = rpNALIGHTTYPE;
                break;
            case 1:
                lv_10 = rpLIGHTDIRECTIONAL;
                break;
            case 2:
                lv_10 = rpLIGHTAMBIENT;
                break;
            case 3:
                lv_10 = rpLIGHTPOINT;
                break;
            case 4:
                lv_10 = rpLIGHTSPOT;
                break;
            case 5:
                lv_10 = rpLIGHTSPOTSOFT;
                break;
            }
            if (unk_C0 != lv_10)
            {
                unk_C0 = lv_10;
                var_14 = unk_D4.get_unk_08();
                if (var_14)
                {
                    unk_D4.sub_129C40();
                }
                if (lv_10)
                {
                    var_14 = RpLightCreate(unk_C0);
                    if (var_14)
                    {
                        unk_D4.sub_129BD0(var_14);
                        bp_18 = RwFrameCreate();
                        if (bp_18)
                        {
                            RwFrameSetIdentity(bp_18);
                            RpLightSetFrame(var_14, bp_18);
                            sub_C58F0();
                            sub_173800(var_14);
                        }
                    }
                }
            }
            break;
        case 1:
            unk_C4 = bp_8->GetAs_RwReal() * 0.017453292f;
            var_C = 1;
            break;
        case 2:
            unk_C8 = bp_8->GetAs_RwReal();
            var_C = 1;
            break;
        case 3:
        {
            RwInt32 var_24[3] = {rpLIGHTLIGHTATOMICS | rpLIGHTLIGHTWORLD, rpLIGHTLIGHTATOMICS, rpLIGHTLIGHTWORLD};

            unk_CC = var_24[bp_8->GetAs_RwInt32()];
            var_C = 1;
            break;
        }
        case 4:
            bp_8->GetCommandData(unk_D0);
            var_C = 1;
            break;
        }
        ++bp_8;
    }
    if (var_C)
    {
        sub_C58F0();
    }
}

// match: ?sub_C58F0@WorldLight@@QAEXXZ @ 0x000C58F0
// sp-match: ?sub_C58F0@WorldLight@@QAEXXZ @ 0x00096140
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void WorldLight::sub_C58F0()
{
    RwUInt8 var_1F;
    RwUInt8 loc1E;
    RwUInt8 var_1D;
    RwRGBAReal lv_1C;
    RwInt32 lC;
    RwUInt8 var_5;
    RpLight *bp_4;

    bp_4 = unk_D4.get_unk_08();
    if (bp_4)
    {
        var_5 = (RwUInt8)((unk_D0 & 0xFF000000) >> 24);
        var_1D = (RwUInt8)((unk_D0 & 0xFF0000) >> 16);
        var_1F = (RwUInt8)((unk_D0 & 0xFF00) >> 8);
        loc1E = (RwUInt8)(unk_D0 & 0xFF);
        lv_1C.red = var_1D / 255.0f;
        lv_1C.green = var_1F / 255.0f;
        lv_1C.blue = loc1E / 255.0f;
        lv_1C.alpha = var_5 / 255.0f;
        RpLightSetColor(bp_4, &lv_1C);
        lC = RpLightGetType(bp_4);
        if (lC == rpLIGHTAMBIENT)
        {
            unk_4E5C60 = lv_1C;
        }
        RpLightSetRadius(bp_4, unk_C8);
        RpLightSetRadius(bp_4, unk_C8);
        RpLightSetConeAngle(bp_4, unk_C4);
        RpLightSetFlags(bp_4, unk_CC);
    }
    sub_1739C0();
}

// match: ??_EWorldLight@@WBI@AEPAXI@Z @ 0x000C5A50
// sp-match: ??_EWorldLight@@WBI@AEPAXI@Z @ 0x00096300

// Functions /OPT:ICF folded into another body (config/aliases.txt), defined here for the
// authentic link (PLAN M7) with that body; the placement link takes the folded one.

// ?HandleEvents@WorldLight@@UAEXAAVCMsg@RWS@@@Z (folded into 0xA2BF0)
void WorldLight::HandleEvents(class RWS::CMsg & pMsg)
{
    Trigger::HandleEvents(pMsg);
}
