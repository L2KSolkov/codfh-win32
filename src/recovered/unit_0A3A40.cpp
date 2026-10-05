// MeshSwapDestructableObjectTrigger: its MakeNew, constructor, destructor
// and handlers. Its original file name is not in the image, so it is named
// for its start address.

#include "rw/ostypes.h"
#include "rws/cattributehandler.h"
#include "rws/cclassfactory.h"
#include "game/functions.h"
#include "types/MeshSwapDestructableObjectTrigger.h"
#include "types/type_3D5400.h"
#include "types/type_72810.h"

RWS_IMPLEMENT_CLASSID(MeshSwapDestructableObjectTrigger);
RWS_REGISTERCLASS(MeshSwapDestructableObjectTrigger);
// Its data (PLAN M5): literals, constants and tables where the image has them.
// match: ??_C@_0CC@BGMMKMNL@MeshSwapDestructableObjectTrigge@ @ 0x003D5D50
// match: ??_7MeshSwapDestructableObjectTrigger@@6BCEventHandler@RWS@@@ @ 0x003D5D74
// match: ??_7MeshSwapDestructableObjectTrigger@@6BCAttributeHandler@RWS@@@ @ 0x003D5D7C
// match: __ehhandler$?MakeNew@MeshSwapDestructableObjectTrigger@@SAPAVCAttributeHandler@RWS@@ABVCAttributePacket@3@@Z>1>8 @ 0x0041BBE4
// match: __ehhandler$?MakeNew@MeshSwapDestructableObjectTrigger@@SAPAVCAttributeHandler@RWS@@ABVCAttributePacket@3@@Z>1 @ 0x0041BBEC
// match: .CRT$XCU+0 @ 0x00426F10
// match: ?pMeshSwapDestructableObjectTriggerClassID@MeshSwapDestructableObjectTrigger@@2PBDB @ 0x00429154

// match: _$E2 @ 0x0030A6F0
// match: _$E3 @ 0x0030E020

// (The class factory's registration and its exit thunk.)

// match: ?MakeNew@MeshSwapDestructableObjectTrigger@@SAPAVCAttributeHandler@RWS@@ABVCAttributePacket@3@@Z @ 0x000A3A40
// match: __ehhandler$?MakeNew@MeshSwapDestructableObjectTrigger@@SAPAVCAttributeHandler@RWS@@ABVCAttributePacket@3@@Z-0xF @ 0x002FFE90
// match: __ehhandler$?MakeNew@MeshSwapDestructableObjectTrigger@@SAPAVCAttributeHandler@RWS@@ABVCAttributePacket@3@@Z @ 0x002FFE9F
RWS_DEFINE_MAKENEW(MeshSwapDestructableObjectTrigger)

// match: ??0MeshSwapDestructableObjectTrigger@@QAE@ABVCAttributePacket@RWS@@@Z @ 0x000A3AC0
MeshSwapDestructableObjectTrigger::MeshSwapDestructableObjectTrigger(const RWS::CAttributePacket &attr)
    : DestructableObjectTrigger(attr)
{
    unk_100.unk_00 = 0;
    unk_100.unk_04 = 0;
    unk_108.unk_00 = 0;
    unk_108.unk_04 = 0;
    unk_110 = 0;
    unk_114 = 0;
}

// match: ?vf_008@MeshSwapDestructableObjectTrigger@@UAEHXZ @ 0x000A3B80

// match: ??_GMeshSwapDestructableObjectTrigger@@UAEPAXI@Z @ 0x000A3B90

// match: ??1MeshSwapDestructableObjectTrigger@@UAE@XZ @ 0x000A3BB0
// (Defined in the class, in MeshSwapDestructableObjectTrigger.h.)

// Commands 2 and 3 first (the kind of names unk_110 picks), then 0 and 1,
// its meshes' names.
// match: ?HandleAttributes@MeshSwapDestructableObjectTrigger@@UAEXABVCAttributePacket@RWS@@@Z @ 0x000A3BE0
void MeshSwapDestructableObjectTrigger::HandleAttributes(const RWS::CAttributePacket &attr)
{
    DestructableObjectTrigger::HandleAttributes(attr);
    {
        RWS::CAttributeCommandIterator attrIt(attr, RWS_CLASSID_OF(MeshSwapDestructableObjectTrigger));
        while (!attrIt.IsFinished())
        {
            switch (attrIt->GetCommandId())
            {
            case 2:
                unk_110 = attrIt->GetAs_RwInt32();
                break;
            case 3:
                unk_114 = attrIt->GetAs_RwInt32();
                break;
            }
            ++attrIt;
        }
    }
    RWS::CAttributeCommandIterator attrIt(attr, RWS_CLASSID_OF(MeshSwapDestructableObjectTrigger));
    while (!attrIt.IsFinished())
    {
        switch (attrIt->GetCommandId())
        {
        case 0:
            unk_100 = *(const type_3DF8D8_04 *)attrIt->GetAs_RwChar_ptr();
            if (unk_100.unk_00 || unk_100.unk_04)
            {
                if (!unk_110)
                {
                    sub_198900((type_3DF8D8_04 *)&unk_100, 3, 0, 0, 0, 0);
                }
                else
                {
                    sub_198900((type_3DF8D8_04 *)&unk_100, 0x30, 0, 0, 0, 0);
                }
            }
            break;
        case 1:
            unk_108 = *(const type_3DF8D8_04 *)attrIt->GetAs_RwChar_ptr();
            if (unk_108.unk_00 || unk_108.unk_04)
            {
                if (!unk_110)
                {
                    sub_198900((type_3DF8D8_04 *)&unk_108, 3, 0, 0, 0, 0);
                }
                else
                {
                    sub_198900((type_3DF8D8_04 *)&unk_108, 0x30, 0, 0, 0, 0);
                }
            }
            break;
        }
        ++attrIt;
    }
}

// match: ?HandleEvents@MeshSwapDestructableObjectTrigger@@UAEXAAVCMsg@RWS@@@Z @ 0x000A3DF0
void MeshSwapDestructableObjectTrigger::HandleEvents(RWS::CMsg &pMsg)
{
    DestructableObjectTrigger::HandleEvents(pMsg);
}

// match: ?vf_020@MeshSwapDestructableObjectTrigger@@UAEPAUtype_3D3548@@XZ @ 0x000A3E10
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
type_3D3548 *MeshSwapDestructableObjectTrigger::vf_020()
{
    type_3DF8D8 *var_C;
    type_3D3548 *bp_8;
    type_3DF8D8 *bp_4;

    bp_8 = 0;
    bp_4 = sub_198800(&unk_100);
    if (!bp_4)
    {
    }
    else
    {
        var_C = sub_198800(&unk_108);
        bp_8 = sub_9B700((type_712B0 *)this);
    }
    return bp_8;
}

// match: ??_EMeshSwapDestructableObjectTrigger@@WBI@AEPAXI@Z @ 0x000A3E70
