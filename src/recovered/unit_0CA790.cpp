// CMountedWeaponSelector: its MakeNew, constructor, destructor and handlers.
// Its original file name is not in the image, so it is named for its start
// address.

#include "rw/ostypes.h"
#include "rws/cattributehandler.h"
#include "rws/cclassfactory.h"
#include "types/CMountedWeaponSelector.h"
#include "types/type_44350.h"
#include "types/type_4E1B70.h"
#include "types/type_72810.h"

RWS_IMPLEMENT_CLASSID(CMountedWeaponSelector);
RWS_REGISTERCLASS(CMountedWeaponSelector);
// Its data (PLAN M5): literals, constants and tables where the image has them.
// match: ??_C@_0BH@BPPHMIKC@CMountedWeaponSelector?$AA@ @ 0x003D6CF8
// match: ??_7CMountedWeaponSelector@@6BCEventHandler@RWS@@@ @ 0x003D6D10
// match: ??_7CMountedWeaponSelector@@6BCAttributeHandler@RWS@@@ @ 0x003D6D18
// match: __ehhandler$?MakeNew@CMountedWeaponSelector@@SAPAVCAttributeHandler@RWS@@ABVCAttributePacket@3@@Z>1>8 @ 0x0041C970
// match: __ehhandler$?MakeNew@CMountedWeaponSelector@@SAPAVCAttributeHandler@RWS@@ABVCAttributePacket@3@@Z>1 @ 0x0041C978
// match: __ehhandler$??1CMountedWeaponSelector@@UAE@XZ>1>8 @ 0x0041C994
// match: __ehhandler$??1CMountedWeaponSelector@@UAE@XZ>1 @ 0x0041C99C
// match: .CRT$XCU+0 @ 0x00426FC8
// match: ?pCMountedWeaponSelectorClassID@CMountedWeaponSelector@@2PBDB @ 0x00429218

// match: _$E2 @ 0x0030AF90
// match: _$E3 @ 0x0030E300

// (The class factory's registration and its exit thunk.)

// match: ?MakeNew@CMountedWeaponSelector@@SAPAVCAttributeHandler@RWS@@ABVCAttributePacket@3@@Z @ 0x000CA790
// match: __ehhandler$?MakeNew@CMountedWeaponSelector@@SAPAVCAttributeHandler@RWS@@ABVCAttributePacket@3@@Z-0xF @ 0x00300A00
// match: __ehhandler$?MakeNew@CMountedWeaponSelector@@SAPAVCAttributeHandler@RWS@@ABVCAttributePacket@3@@Z @ 0x00300A0F
// sp-match: ?MakeNew@CMountedWeaponSelector@@SAPAVCAttributeHandler@RWS@@ABVCAttributePacket@3@@Z @ 0x00099D40
RWS_DEFINE_MAKENEW(CMountedWeaponSelector)

// match: ??0CMountedWeaponSelector@@QAE@ABVCAttributePacket@RWS@@@Z @ 0x000CA810
// sp-match: ??0CMountedWeaponSelector@@QAE@ABVCAttributePacket@RWS@@@Z @ 0x00099B90
CMountedWeaponSelector::CMountedWeaponSelector(const RWS::CAttributePacket &attr)
{
}

// match: ??_GCMountedWeaponSelector@@UAEPAXI@Z @ 0x000CA8A0
// sp-match: ??_GCMountedWeaponSelector@@UAEPAXI@Z @ 0x00099CB0

// match: ??1CMountedWeaponSelector@@UAE@XZ @ 0x000CA8C0
// match: __ehhandler$??1CMountedWeaponSelector@@UAE@XZ-0x8 @ 0x00300A20
// match: __ehhandler$??1CMountedWeaponSelector@@UAE@XZ @ 0x00300A28
// sp-match: ??1CMountedWeaponSelector@@UAE@XZ @ 0x00099BD0
// (Defined in the class, in CMountedWeaponSelector.h.)

// Command 0: the mounted weapons' names.
// match: ?HandleAttributes@CMountedWeaponSelector@@UAEXABVCAttributePacket@RWS@@@Z @ 0x000CA940
// sp-match: ?HandleAttributes@CMountedWeaponSelector@@UAEXABVCAttributePacket@RWS@@@Z @ 0x00099CC0
void CMountedWeaponSelector::HandleAttributes(const RWS::CAttributePacket &attr)
{
    RWS::CAttributeHandler::HandleAttributes(attr);
    RWS::CAttributeCommandIterator attrIt(attr, RWS_CLASSID_OF(CMountedWeaponSelector));
    while (!attrIt.IsFinished())
    {
        switch (attrIt->GetCommandId())
        {
        case 0:
            sub_CA9C0((const RwUInt32 *)attrIt->GetAs_RwChar_ptr());
            break;
        }
        ++attrIt;
    }
}

// match: ?sub_CA9C0@CMountedWeaponSelector@@QAEXPBI@Z @ 0x000CA9C0
// sp-match: ?sub_CA9C0@CMountedWeaponSelector@@QAEXPBI@Z @ 0x00099C30
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void CMountedWeaponSelector::sub_CA9C0(const RwUInt32 *arg_0)
{
    type_4E1B70 *local_C;
    RwInt32 var_8;
    RwInt32 l4;

    l4 = *arg_0;
    arg_0++;
    for (var_8 = 0; var_8 < 7; var_8++)
    {
        local_C = sub_166990(var_8);
        local_C->unk_F8 = 0;
    }
    for (var_8 = 0; var_8 < l4; var_8++)
    {
        Trigger_key var_14;

        var_14.unk_00 = 0;
        var_14.unk_04 = 0;
        var_14.unk_00 = *arg_0;
        arg_0++;
        var_14.unk_04 = *arg_0;
        arg_0++;
        sub_198900((type_3DF8D8_04 *)&var_14, 0x2F, 0, 0, 0, 0);
    }
}

// match: ??_ECMountedWeaponSelector@@WBI@AEPAXI@Z @ 0x000CAA80
// sp-match: ??_ECMountedWeaponSelector@@WBI@AEPAXI@Z @ 0x00099CA0

// Members /OPT:ICF folded into shared trivial bodies (config/aliases.txt): defined here for
// the authentic link (PLAN M7); the placement link takes the shared bodies.

// ?HandleEvents@CMountedWeaponSelector@@UAEXAAVCMsg@RWS@@@Z (folded into the empty body at 0x15FB30)
void CMountedWeaponSelector::HandleEvents(RWS::CMsg &pMsg)
{
}
