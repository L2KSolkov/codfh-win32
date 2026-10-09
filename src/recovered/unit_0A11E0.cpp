// AnimPackTrigger, a trigger behaviour holding six animation packs: its
// MakeNew, constructor, destructor and handlers. Its original file name is
// not in the image, so it is named for its start address.

#include "rw/ostypes.h"
#include "rws/cattributehandler.h"
#include "rws/cclassfactory.h"
#include "types/AnimPackTrigger.h"
#include "types/musicplayer.h"
#include "types/soundbank.h"
#include "types/animbank.h"
#include "game/data.h"
#include "game/functions.h"
#include "types/type_3DF8D8.h"

RWS_IMPLEMENT_CLASSID(AnimPackTrigger);
RWS_REGISTERCLASS(AnimPackTrigger);
// Its data (PLAN M5): literals, constants and tables where the image has them.
// match: ??_C@_0BA@EFBKODBE@AnimPackTrigger?$AA@ @ 0x003D5A88
// match: ??_7AnimPackTrigger@@6BCEventHandler@RWS@@@ @ 0x003D5A98
// match: ??_7AnimPackTrigger@@6BCAttributeHandler@RWS@@@ @ 0x003D5AA0
// match: __ehhandler$?MakeNew@AnimPackTrigger@@SAPAVCAttributeHandler@RWS@@ABVCAttributePacket@3@@Z>1>8 @ 0x0041BA58
// match: __ehhandler$?MakeNew@AnimPackTrigger@@SAPAVCAttributeHandler@RWS@@ABVCAttributePacket@3@@Z>1 @ 0x0041BA60
// match: __ehhandler$??0AnimPackTrigger@@QAE@ABVCAttributePacket@RWS@@@Z>1>8 @ 0x0041BA7C
// match: __ehhandler$??0AnimPackTrigger@@QAE@ABVCAttributePacket@RWS@@@Z>1 @ 0x0041BA84
// match: .CRT$XCU+0 @ 0x00426EF0
// match: ?pAnimPackTriggerClassID@AnimPackTrigger@@2PBDB @ 0x00429134

// match: _$E2 @ 0x0030A570
// match: _$E3 @ 0x0030DFA0

// (The class factory's registration and its exit thunk.)

// match: ?MakeNew@AnimPackTrigger@@SAPAVCAttributeHandler@RWS@@ABVCAttributePacket@3@@Z @ 0x000A11E0
// match: __ehhandler$?MakeNew@AnimPackTrigger@@SAPAVCAttributeHandler@RWS@@ABVCAttributePacket@3@@Z-0xF @ 0x002FFD30
// match: __ehhandler$?MakeNew@AnimPackTrigger@@SAPAVCAttributeHandler@RWS@@ABVCAttributePacket@3@@Z @ 0x002FFD3F
// sp-match: ?MakeNew@AnimPackTrigger@@SAPAVCAttributeHandler@RWS@@ABVCAttributePacket@3@@Z @ 0x0007E310
RWS_DEFINE_MAKENEW(AnimPackTrigger)

// match: ??0AnimPackTrigger@@QAE@ABVCAttributePacket@RWS@@@Z @ 0x000A1260
// match: __ehhandler$??0AnimPackTrigger@@QAE@ABVCAttributePacket@RWS@@@Z-0x8 @ 0x002FFD50
// match: __ehhandler$??0AnimPackTrigger@@QAE@ABVCAttributePacket@RWS@@@Z @ 0x002FFD58
// sp-match: ??0AnimPackTrigger@@QAE@ABVCAttributePacket@RWS@@@Z @ 0x0007E290
AnimPackTrigger::AnimPackTrigger(const RWS::CAttributePacket &attr) : Trigger(attr)
{
    sub_A1360();
}

// match: ?vf_008@AnimPackTrigger@@UAEHXZ @ 0x000A1330
// sp-match: ?vf_008@AnimPackTrigger@@UAEHXZ @ 0x0007E0D0

// match: ??_GAnimPackTrigger@@UAEPAXI@Z @ 0x000A1340
// sp-match: ??_GAnimPackTrigger@@UAEPAXI@Z @ 0x0007E300

// match: ?sub_A1360@AnimPackTrigger@@QAEXXZ @ 0x000A1360
// sp-match: ?sub_A1360@AnimPackTrigger@@QAEXXZ @ 0x0007E090
void AnimPackTrigger::sub_A1360()
{
    RwInt32 var_4;

    for (var_4 = 0; var_4 < 6; var_4++)
    {
        unk_C8[var_4].unk_00.unk_00 = 0;
        unk_C8[var_4].unk_00.unk_04 = 0;
        unk_C8[var_4].unk_08[0] = 0;
    }
}

// match: ??1AnimPackTrigger@@UAE@XZ @ 0x000A13C0
// sp-match: ??1AnimPackTrigger@@UAE@XZ @ 0x0007E0B0
// (Defined in the class, in AnimPackTrigger.h.)

// Command 0: its six packs (their names looked up); command 1: its key.
// match: ?HandleAttributes@AnimPackTrigger@@UAEXABVCAttributePacket@RWS@@@Z @ 0x000A13F0
// sp-match: ?HandleAttributes@AnimPackTrigger@@UAEXABVCAttributePacket@RWS@@@Z @ 0x0007E0E0
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void AnimPackTrigger::HandleAttributes(const RWS::CAttributePacket &attr)
{
    RwInt32 var_14;
    const type_3DF8D8_04 *ebp_10;
    const type_3DF8D8_04 *l4;

    Trigger::HandleAttributes(attr);
    RWS::CAttributeCommandIterator locC(attr, RWS_CLASSID_OF(AnimPackTrigger));
    while (!locC.IsFinished())
    {
        switch (locC->GetCommandId())
        {
        case 0:
            sub_A1360();
            l4 = (const type_3DF8D8_04 *)locC->GetAs_RwChar_ptr();
            for (var_14 = 0; var_14 < 6; var_14++)
            {
                unk_C8[var_14].unk_00 = l4[var_14];
                if (l4[var_14].unk_00 || l4[var_14].unk_04)
                {
                    sub_198900((type_3DF8D8_04 *)&l4[var_14], 2, (void (*)(RwInt32, RwInt32, RwInt32))sub_195B70, 0,
                               (RwInt32)unk_C8[var_14].unk_08, 0);
                }
            }
            break;
        case 1:
            ebp_10 = (const type_3DF8D8_04 *)locC->GetAs_RwChar_ptr();
            unk_C0.unk_00 = ebp_10->unk_00;
            unk_C0.unk_04 = ebp_10->unk_04;
            break;
        }
        ++locC;
    }
}

// match: ?vf_030@AnimPackTrigger@@UAEXXZ @ 0x000A1540
// sp-match: ?vf_030@AnimPackTrigger@@UAEXXZ @ 0x0007E1D0
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void AnimPackTrigger::vf_030()
{
    type_5E730 *var_C;
    RwInt32 bp_8;
    RwInt32 bp_4;

    bp_8 = 0;
    for (bp_4 = 0; bp_4 < 6; bp_4++)
    {
        if (!unk_C8[bp_4].unk_00.unk_00 && !unk_C8[bp_4].unk_00.unk_04)
        {
            continue;
        }
        bp_8 |= sub_777F0(unk_C8[bp_4].unk_08, *(type_449C94_08 *)&unk_C8[bp_4].unk_00, bp_4, (RwV3d *)&unk_90);
    }
    if (unk_C0.unk_00 && unk_C0.unk_04)
    {
        var_C = (type_5E730 *)sub_198800(&unk_C0);
        if (var_C)
        {
            if ((unk_C0.unk_00 == 0x756CB864 && unk_C0.unk_04 == 0x185BB351) == 0)
            {
                dword_44E8D8[var_C->unk_20].unk_244 = 1;
                dword_4B1E98.sub_8A980(&unk_C0, 0, 0, 0, 0, 0);
            }
        }
    }
}

// match: ??_EAnimPackTrigger@@WBI@AEPAXI@Z @ 0x000A1680
// sp-match: ??_EAnimPackTrigger@@WBI@AEPAXI@Z @ 0x0007E280
