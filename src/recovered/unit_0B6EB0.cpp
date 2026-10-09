// CShellLevelBehaviorClass: its MakeNew, constructor, destructor and
// handlers. Its original file name is not in the image, so it is named for
// its start address.

#include "rw/batypes.h"
#include "rw/ostypes.h"
#ifdef CODFH_SP
#define SP_HUD(mp, sp) (sp)
#else
#define SP_HUD(mp, sp) (mp)
#endif
#include "rws/cattributehandler.h"
#include "rws/cclassfactory.h"
#include "game/data.h"
#include "types/CShellLevelBehaviorClass.h"
#include "types/type_4B8EF0.h"
#include "types/type_72810.h"
#include "types/type_DC400.h"

// Its data definitions (PLAN M5), in the image's address order.
// 0x003D6490
extern const RwReal flt_3D6490 = 16.666666f;
// 0x004B8F14
#ifndef CODFH_PLAIN
RwReal flt_4B8F14;
#endif
// 0x004B8F18
#ifndef CODFH_PLAIN
RwReal flt_4B8F18;
#endif
// 0x004B8F1C
#ifndef CODFH_PLAIN
RwReal dword_4B8F1C;
#endif
// End of its data definitions.


RWS_IMPLEMENT_CLASSID(CShellLevelBehaviorClass);
RWS_REGISTERCLASS(CShellLevelBehaviorClass);
// Its data (PLAN M5): literals, constants and tables where the image has them.
// match: ??_C@_0BJ@GHLBOOMJ@CShellLevelBehaviorClass?$AA@ @ 0x003D6474
// match: ?flt_3D6490@@3MB @ 0x003D6490
// match: ??_7CShellLevelBehaviorClass@@6BCEventHandler@RWS@@@ @ 0x003D6494
// match: ??_7CShellLevelBehaviorClass@@6BCAttributeHandler@RWS@@@ @ 0x003D649C
// match: __ehhandler$?MakeNew@CShellLevelBehaviorClass@@SAPAVCAttributeHandler@RWS@@ABVCAttributePacket@3@@Z>1>8 @ 0x0041C08C
// match: __ehhandler$?MakeNew@CShellLevelBehaviorClass@@SAPAVCAttributeHandler@RWS@@ABVCAttributePacket@3@@Z>1 @ 0x0041C094
// match: __ehhandler$??1CShellLevelBehaviorClass@@UAE@XZ>1>8 @ 0x0041C0B0
// match: __ehhandler$??1CShellLevelBehaviorClass@@UAE@XZ>1 @ 0x0041C0B8
// match: .CRT$XCU+0 @ 0x00426F58
// match: ?pCShellLevelBehaviorClassClassID@CShellLevelBehaviorClass@@2PBDB @ 0x004291A8

// match: _$E2 @ 0x0030AA50
// match: _$E3 @ 0x0030E140

// (The class factory's registration and its exit thunk.)

// match: ?MakeNew@CShellLevelBehaviorClass@@SAPAVCAttributeHandler@RWS@@ABVCAttributePacket@3@@Z @ 0x000B6EB0
// match: __ehhandler$?MakeNew@CShellLevelBehaviorClass@@SAPAVCAttributeHandler@RWS@@ABVCAttributePacket@3@@Z-0xF @ 0x00300290
// match: __ehhandler$?MakeNew@CShellLevelBehaviorClass@@SAPAVCAttributeHandler@RWS@@ABVCAttributePacket@3@@Z @ 0x0030029F
// sp-match: ?MakeNew@CShellLevelBehaviorClass@@SAPAVCAttributeHandler@RWS@@ABVCAttributePacket@3@@Z @ 0x0008C630
RWS_DEFINE_MAKENEW(CShellLevelBehaviorClass)

// match: ??0CShellLevelBehaviorClass@@QAE@ABVCAttributePacket@RWS@@@Z @ 0x000B6F30
// sp-match: ??0CShellLevelBehaviorClass@@QAE@ABVCAttributePacket@RWS@@@Z @ 0x0008C320
CShellLevelBehaviorClass::CShellLevelBehaviorClass(const RWS::CAttributePacket &attr)
{
}

// match: ??_GCShellLevelBehaviorClass@@UAEPAXI@Z @ 0x000B6FC0
// sp-match: ??_GCShellLevelBehaviorClass@@UAEPAXI@Z @ 0x0008C3D0

// match: ??1CShellLevelBehaviorClass@@UAE@XZ @ 0x000B6FE0
// match: __ehhandler$??1CShellLevelBehaviorClass@@UAE@XZ-0x8 @ 0x003002B0
// match: __ehhandler$??1CShellLevelBehaviorClass@@UAE@XZ @ 0x003002B8
// sp-match: ??1CShellLevelBehaviorClass@@UAE@XZ @ 0x0008C360
// (Defined in the class, in CShellLevelBehaviorClass.h.)

// match: ?HandleAttributes@CShellLevelBehaviorClass@@UAEXABVCAttributePacket@RWS@@@Z @ 0x000B7060
// sp-match: ?HandleAttributes@CShellLevelBehaviorClass@@UAEXABVCAttributePacket@RWS@@@Z @ 0x0008C3E0
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void CShellLevelBehaviorClass::HandleAttributes(const RWS::CAttributePacket &attr)
{
    Trigger_key bp_8;

    RWS::CAttributeHandler::HandleAttributes(attr);
    RWS::CAttributeCommandIterator r10(attr, RWS_CLASSID_OF(CShellLevelBehaviorClass));
    RwInt32 var_14;
    RwRGBA var_18;
    RwUInt32 var_1C;

    bp_8.unk_00 = 0;
    bp_8.unk_04 = 0;
    while (!r10.IsFinished())
    {
        switch (r10->GetCommandId())
        {
        case 0:
            dword_4B8EF0.unk_00 = *(const RwReal *)r10->GetAs_RwChar_ptr();
            break;
        case 3:
            dword_4B8EF0.unk_24 = *(const RwInt32 *)r10->GetAs_RwChar_ptr();
            break;
        case 4:
            dword_4B8EF0.unk_28 = *(const RwInt32 *)r10->GetAs_RwChar_ptr();
            break;
        case 2:
            dword_4B8EF0.unk_2C = *(const RwReal *)r10->GetAs_RwChar_ptr();
            dword_4B8EF0.unk_2C *= 1000.0f;
            break;
        case 5:
            var_1C = *(const RwUInt32 *)r10->GetAs_RwChar_ptr();
            var_18.alpha = (RwUInt8)((var_1C & 0xFF000000) >> 24);
            var_18.red = (RwUInt8)((var_1C & 0xFF0000) >> 16);
            var_18.green = (RwUInt8)((var_1C & 0xFF00) >> 8);
            var_18.blue = (RwUInt8)(var_1C & 0xFF);
            if (dword_4B9190)
            {
                dword_4B9190->sub_E7200(SP_HUD(0x5B, 0x32), var_18.red, var_18.green, var_18.blue, var_18.alpha);
                dword_4B9190->sub_E7200(SP_HUD(0x5C, 0x33), var_18.red, var_18.green, var_18.blue, var_18.alpha);
                dword_4B9190->sub_E7200(SP_HUD(0x5D, 0x34), var_18.red, var_18.green, var_18.blue, var_18.alpha);
                dword_4B9190->sub_E7200(SP_HUD(0x5E, 0x35), var_18.red, var_18.green, var_18.blue, var_18.alpha);
            }
            dword_4B8EF0.unk_38 = var_18;
            break;
        case 6:
            bp_8 = *(const Trigger_key *)r10->GetAs_RwChar_ptr();
            if (bp_8.unk_00 || bp_8.unk_04)
            {
                sub_198900((type_3DF8D8_04 *)&bp_8, 0x3B, 0, 0, 0, 0);
                sub_E8DB0(&bp_8);
            }
            break;
        case 7:
            bp_8 = *(const Trigger_key *)r10->GetAs_RwChar_ptr();
            if (bp_8.unk_00 || bp_8.unk_04)
            {
                sub_198900((type_3DF8D8_04 *)&bp_8, 0x3B, 0, 0, 0, 0);
                sub_E8E30(&bp_8);
            }
            break;
        case 8:
            var_14 = *(const RwInt32 *)r10->GetAs_RwChar_ptr();
            dword_4B918C = var_14;
            break;
        }
        ++r10;
    }
}

// match: ??_ECShellLevelBehaviorClass@@WBI@AEPAXI@Z @ 0x000B7320
// sp-match: ??_ECShellLevelBehaviorClass@@WBI@AEPAXI@Z @ 0x0008C3C0

// Members /OPT:ICF folded into shared trivial bodies (config/aliases.txt): defined here for
// the authentic link (PLAN M7); the placement link takes the shared bodies.

// ?HandleEvents@CShellLevelBehaviorClass@@UAEXAAVCMsg@RWS@@@Z (folded into the empty body at 0x15FB30)
void CShellLevelBehaviorClass::HandleEvents(RWS::CMsg &pMsg)
{
}
