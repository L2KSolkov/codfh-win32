// AnimatedBGTrigger, the RenderWare Studio behaviour of trigger kind 8: its
// MakeNew, constructor, destructor and handlers. Split from unit_09AD40.cpp at 0x09F130, where the image ends that object (its deferred
// functions come before the next out-of-line one; PLAN M7).

#include "rw/ostypes.h"
#include "game/functions.h"
#include "types/type_3D3548.h"
#include "types/type_3D32F8.h"
#include "types/type_3D51C0.h"
#include "types/type_3D5400.h"
#include "types/type_9BB60.h"
#include "types/type_3D5658.h"
#include "rws/cattributehandler.h"
#include "rws/cclassfactory.h"
#include "rws/ceventhandler.h"
#include "types/alfamessman.h"
#include "types/scriptvm.h"
#include "types/AddTaskTrigger.h"
#include "types/type_72810.h"
#include "types/AnimatedBGTrigger.h"
#include "types/vec4.h"
#include "rw/bavector.h"
#include "rw/rprandom.h"
#include "types/type_D48D0.h"
#include "types/alfaobject.h"
#include "types/type_3D2E7C.h"
#include "types/type_3DF8D8.h"
#include "types/type_44350.h"
#include "types/CustomTrigger.h"
#include "types/DogTrigger.h"
#include "types/type_10F710.h"
#include "game/vecutil.h"
#include "types/MeshSwapDestructableObjectTrigger.h"
#include "types/soundbank.h"
#include "rw/rphanim.h"
#include "game/clumpdata.h"
#include "types/animbank.h"
#include <string.h>
#include <math.h>

// Its data definitions (PLAN M5), in the image's address order.
// 0x003D5934
extern const RwReal flt_3D5934 = 0.01f;
// 0x003D5938
extern const RwReal flt_3D5938 = 0.01f;
// 0x003D593C
extern const RwReal flt_3D593C = 16.666666f;

// match: ?flt_3D5934@@3MB @ 0x003D5934
// match: ?flt_3D5938@@3MB @ 0x003D5938
// match: ?flt_3D593C@@3MB @ 0x003D593C


// match: __ehhandler$?MakeNew@AnimatedBGTrigger@@SAPAVCAttributeHandler@RWS@@ABVCAttributePacket@3@@Z>1>8 @ 0x0041B8E4
// match: __ehhandler$?MakeNew@AnimatedBGTrigger@@SAPAVCAttributeHandler@RWS@@ABVCAttributePacket@3@@Z>1 @ 0x0041B8EC
// match: __ehhandler$??0AnimatedBGTrigger@@QAE@ABVCAttributePacket@RWS@@@Z>1>8 @ 0x0041B908
// match: __ehhandler$??0AnimatedBGTrigger@@QAE@ABVCAttributePacket@RWS@@@Z>1 @ 0x0041B918
// match: __ehhandler$??1AnimatedBGTrigger@@UAE@XZ>1>8 @ 0x0041B934
// match: __ehhandler$??1AnimatedBGTrigger@@UAE@XZ>1 @ 0x0041B944
// match: ??_C@_0BC@OFLJMGFF@AnimatedBGTrigger?$AA@ @ 0x003D5920
// match: ??_7AnimatedBGTrigger@@6BCEventHandler@RWS@@@ @ 0x003D5940
// match: ??_7AnimatedBGTrigger@@6BCAttributeHandler@RWS@@@ @ 0x003D5948
// match: ?pAnimatedBGTriggerClassID@AnimatedBGTrigger@@2PBDB @ 0x00429128
// match: .CRT$XCU+0 @ 0x00426EE4

// match: _$E2 @ 0x0030A4E0
// match: _$E3 @ 0x0030DF70

// (The class factory's registration and its exit thunk.)
RWS_IMPLEMENT_CLASSID(AnimatedBGTrigger);
RWS_REGISTERCLASS(AnimatedBGTrigger);

// (The this-adjusting thunk for the second vtable's deleting destructor.)

// match: ?MakeNew@AnimatedBGTrigger@@SAPAVCAttributeHandler@RWS@@ABVCAttributePacket@3@@Z @ 0x0009F130
// match: __ehhandler$?MakeNew@AnimatedBGTrigger@@SAPAVCAttributeHandler@RWS@@ABVCAttributePacket@3@@Z-0xF @ 0x002FFBD0
// match: __ehhandler$?MakeNew@AnimatedBGTrigger@@SAPAVCAttributeHandler@RWS@@ABVCAttributePacket@3@@Z @ 0x002FFBDF
RWS_DEFINE_MAKENEW(AnimatedBGTrigger)

// match: ??0AnimatedBGTrigger@@QAE@ABVCAttributePacket@RWS@@@Z @ 0x0009F1B0
// match: __ehhandler$??0AnimatedBGTrigger@@QAE@ABVCAttributePacket@RWS@@@Z-0x16 @ 0x002FFBF0
// match: __ehhandler$??0AnimatedBGTrigger@@QAE@ABVCAttributePacket@RWS@@@Z @ 0x002FFC06
AnimatedBGTrigger::AnimatedBGTrigger(const RWS::CAttributePacket &attr) : Trigger(attr)
{
    RwInt32 var_10;
    RwInt32 lv_14;

    unk_C0.unk_00 = 0;
    unk_C0.unk_04 = 0;
    unk_C8.unk_00 = 0;
    unk_C8.unk_04 = 0;
    unk_D0.unk_00 = 0;
    unk_D0.unk_04 = 0;
    unk_D8.unk_00 = 0;
    unk_D8.unk_04 = 0;
    unk_F0.unk_00 = 0;
    unk_F0.unk_04 = 0;
    unk_F8 = 0;
    unk_FC = 0;
    unk_100 = 0;
    unk_114 = 0;
    unk_118 = 0;
    unk_120 = 0;
    unk_11C = 0;
    unk_128 = 1;
    unk_12C = 1;
    unk_130 = 1;
    unk_134 = 1;
    unk_138 = 0;
    unk_180.sub_D48D0(0);
    memset(unk_104, 0, 6);
    for (var_10 = 0; var_10 < 2; var_10++)
    {
        unk_104[var_10 + 4] = 1;
    }
    for (lv_14 = 0; lv_14 < 5; lv_14++)
    {
        unk_10A[lv_14] = -1;
    }
    unk_178 = 0;
}

// match: ?vf_008@AnimatedBGTrigger@@UAEHXZ @ 0x0009F4C0

// match: ?vf_01C@AnimatedBGTrigger@@UAEPAUtype_3DF8D8_04@@XZ @ 0x0009F4D0

// match: ?vf_030@AnimatedBGTrigger@@UAEIXZ @ 0x0009F4F0

// match: ?vf_034@AnimatedBGTrigger@@UAEIXZ @ 0x0009F510

// match: ?vf_038@AnimatedBGTrigger@@UAEIXZ @ 0x0009F530

// match: ??_GAnimatedBGTrigger@@UAEPAXI@Z @ 0x0009F550

// match: ??1AnimatedBGTrigger@@UAE@XZ @ 0x0009F570
// match: __ehhandler$??1AnimatedBGTrigger@@UAE@XZ-0x16 @ 0x002FFC10
// match: __ehhandler$??1AnimatedBGTrigger@@UAE@XZ @ 0x002FFC26
AnimatedBGTrigger::~AnimatedBGTrigger()
{
    if (unk_178 != 0)
    {
        sub_BD350(&unk_178);
    }
}

// A first pass takes commands 3 and 4 (the kind its keys are registered
// by), then the rest: keys (0, 2, 5 to 8, 31), block words (17 to 19),
// settings, the ranges 35 and 36 (halved unless -1), its block (40) and its
// registration as a multiplayer flag (41, 42).
// match: ?HandleAttributes@AnimatedBGTrigger@@UAEXABVCAttributePacket@RWS@@@Z @ 0x0009F5F0
void AnimatedBGTrigger::HandleAttributes(const RWS::CAttributePacket &attr)
{
    Trigger::HandleAttributes(attr);
    {
        RWS::CAttributeCommandIterator attrIt(attr, RWS_CLASSID_OF(AnimatedBGTrigger));
        while (!attrIt.IsFinished())
        {
            switch (attrIt->GetCommandId())
            {
            case 3:
                unk_114 = attrIt->GetAs_RwInt32();
                break;
            case 4:
                unk_118 = attrIt->GetAs_RwInt32();
                break;
            }
            ++attrIt;
        }
    }
    RWS::CAttributeCommandIterator attrIt(attr, RWS_CLASSID_OF(AnimatedBGTrigger));
    while (!attrIt.IsFinished())
    {
        switch (attrIt->GetCommandId())
        {
        case 0:
            unk_C0 = *(const type_3DF8D8_04 *)attrIt->GetAs_RwChar_ptr();
            if (unk_C0.unk_00 != 0 || unk_C0.unk_04 != 0)
            {
                if (unk_114 == 0)
                {
                    sub_198900((type_3DF8D8_04 *)&unk_C0, 3, 0, 0, 0, 0);
                }
                else
                {
                    sub_198900((type_3DF8D8_04 *)&unk_C0, 0x30, 0, 0, 0, 0);
                }
            }
            break;
        case 2:
            unk_C8 = *(const type_3DF8D8_04 *)attrIt->GetAs_RwChar_ptr();
            if (unk_C8.unk_00 != 0 || unk_C8.unk_04 != 0)
            {
                if (unk_114 == 0)
                {
                    sub_198900((type_3DF8D8_04 *)&unk_C8, 3, 0, 0, 0, 0);
                }
                else
                {
                    sub_198900((type_3DF8D8_04 *)&unk_C8, 0x30, 0, 0, 0, 0);
                }
            }
            break;
        case 1:
            unk_138 = attrIt->GetAs_RwInt32();
            break;
        case 5:
            unk_E0 = *(const type_3DF8D8_04 *)attrIt->GetAs_RwChar_ptr();
            if (unk_E0.unk_00 != 0)
            {
                sub_198900((type_3DF8D8_04 *)&unk_E0, 0x2E, 0, 0, 0, 0);
            }
            break;
        case 6:
            unk_E8 = *(const type_3DF8D8_04 *)attrIt->GetAs_RwChar_ptr();
            if (unk_E8.unk_00 != 0)
            {
                sub_198900((type_3DF8D8_04 *)&unk_E8, 0x2E, 0, 0, 0, 0);
            }
            break;
        case 7:
        {
            const type_3DF8D8_04 *var_14;

            var_14 = (const type_3DF8D8_04 *)attrIt->GetAs_RwChar_ptr();
            unk_D0 = *var_14;
            sub_198900((type_3DF8D8_04 *)&unk_D0, 0xA, 0, 0, 0, 0);
            break;
        }
        case 8:
        {
            const type_3DF8D8_04 *var_18;

            var_18 = (const type_3DF8D8_04 *)attrIt->GetAs_RwChar_ptr();
            if (var_18->unk_00 != 0 || var_18->unk_04 != 0)
            {
                unk_D8 = *var_18;
                sub_198900((type_3DF8D8_04 *)&unk_D8, 0xC, 0, 0, 0, 0);
            }
            break;
        }
        case 16:
        {
            Trigger_key var_20 = *(const Trigger_key *)attrIt->GetAs_RwChar_ptr();

            if (var_20.unk_00 != 0 || var_20.unk_04 != 0)
            {
                sub_198900((type_3DF8D8_04 *)&var_20, 1, (void (*)(RwInt32, RwInt32, RwInt32))sub_18F8E0, 0, (RwInt32)&unk_104[2], 0);
            }
            break;
        }
        case 17:
        {
            RwUInt8 *var_24 = 0;

            sub_BD490(attrIt->GetAs_RwChar_ptr(), &var_24);
            if (var_24 != 0)
            {
                unk_10A[0] = *(RwInt16 *)(var_24 + 0x14);
                sub_145790(var_24);
            }
            break;
        }
        case 18:
        {
            RwUInt8 *var_28 = 0;

            sub_BD490(attrIt->GetAs_RwChar_ptr(), &var_28);
            if (var_28 != 0)
            {
                unk_10A[1] = *(RwInt16 *)(var_28 + 0x14);
                sub_145790(var_28);
            }
            break;
        }
        case 19:
        {
            RwUInt8 *var_2C = 0;

            sub_BD490(attrIt->GetAs_RwChar_ptr(), &var_2C);
            if (var_2C != 0)
            {
                unk_10A[2] = *(RwInt16 *)(var_2C + 0x14);
                sub_145790(var_2C);
            }
            break;
        }
        case 20:
        {
            Trigger_key var_34 = *(const Trigger_key *)attrIt->GetAs_RwChar_ptr();

            if (var_34.unk_00 != 0 || var_34.unk_04 != 0)
            {
                *(Trigger_key *)&unk_F0 = var_34;
            }
            break;
        }
        case 21:
            unk_F8 = attrIt->GetAs_RwInt32();
            break;
        case 22:
            unk_FC = attrIt->GetAs_RwInt32();
            break;
        case 23:
            unk_100 = attrIt->GetAs_RwInt32();
            break;
        case 24:
            unk_124 = attrIt->GetAs_RwInt32();
            break;
        case 12:
            unk_128 = attrIt->GetAs_RwInt32();
            break;
        case 13:
            unk_12C = attrIt->GetAs_RwInt32();
            break;
        case 14:
            unk_130 = attrIt->GetAs_RwInt32();
            break;
        case 15:
            unk_134 = attrIt->GetAs_RwInt32();
            break;
        case 10:
            unk_120 = attrIt->GetAs_RwInt32();
            break;
        case 11:
            unk_11C = attrIt->GetAs_RwInt32();
            break;
        case 25:
            attrIt->GetCommandData(unk_13C);
            break;
        case 26:
            attrIt->GetCommandData(unk_140);
            break;
        case 27:
            unk_144 = attrIt->GetAs_RwInt32();
            break;
        case 28:
            // No break: the image falls through into command 29.
            attrIt->GetCommandData(unk_17C);
        case 29:
            attrIt->GetCommandData(unk_148);
            break;
        case 31:
        {
            const type_3DF8D8_04 *var_38;

            var_38 = (const type_3DF8D8_04 *)attrIt->GetAs_RwChar_ptr();
            unk_150 = *var_38;
            sub_198900((type_3DF8D8_04 *)&unk_150, 0xA, 0, 0, 0, 0);
            break;
        }
        case 32:
            attrIt->GetCommandData(unk_158);
            break;
        case 33:
            attrIt->GetCommandData(unk_15C);
            break;
        case 34:
            attrIt->GetCommandData(unk_160);
            break;
        case 30:
            unk_14C = attrIt->GetAs_RwUInt32();
            break;
        case 35:
            unk_164 = attrIt->GetAs_RwReal();
            if (unk_164 != -1.0f)
            {
                unk_164 = unk_164 * 0.5f;
            }
            break;
        case 36:
            unk_168 = attrIt->GetAs_RwReal();
            if (unk_168 != -1.0f)
            {
                unk_168 = unk_168 * 0.5f;
            }
            break;
        case 37:
            unk_16C = attrIt->GetAs_RwInt32();
            break;
        case 38:
            attrIt->GetCommandData(unk_170);
            break;
        case 39:
            attrIt->GetCommandData(unk_174);
            break;
        case 40:
        {
            RwInt32 var_3C = 0;

            if (unk_178 != 0)
            {
                sub_BD350(&unk_178);
                var_3C = 1;
            }
            sub_BD490(attrIt->GetAs_RwChar_ptr(), &unk_178);
            break;
        }
        case 41:
        {
            RwInt32 var_40;

            attrIt->GetCommandData(var_40);
            if (var_40 != 0)
            {
                dword_4F6A7C.sub_1A58C0(0, this);
            }
            break;
        }
        case 42:
        {
            RwInt32 var_44;

            attrIt->GetCommandData(var_44);
            if (var_44 != 0)
            {
                dword_4F6A7C.sub_1A58C0(1, this);
            }
            break;
        }
        }
        ++attrIt;
    }
}

// match: ?vf_020@AnimatedBGTrigger@@UAEPAUtype_3D3548@@XZ @ 0x000A0220
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
type_3D3548 *AnimatedBGTrigger::vf_020()
{
    type_3DF8D8 *var_C;
    type_3D3548 *bp_8;
    type_3DF8D8 *bp_4;

    bp_8 = 0;
    bp_4 = sub_198800(&unk_C0);
    if (!bp_4)
    {
    }
    else
    {
        var_C = sub_198800(&unk_C8);
        // The entity reads its trigger as a type_712B0.
        bp_8 = sub_73710(static_cast<type_712B0 *>(static_cast<Trigger *>(this)));
    }
    return bp_8;
}

// match: ?vf_018@AnimatedBGTrigger@@UAEHXZ @ 0x000A0280
RwInt32 AnimatedBGTrigger::vf_018()
{
    switch (unk_11C)
    {
    case 1:
        return 2;
    case 2:
        return 1;
    }
    return 4;
}

// match: ??_EAnimatedBGTrigger@@WBI@AEPAXI@Z @ 0x000A02C0
// (The this-adjusting thunk for the second vtable's deleting destructor.)

// Members /OPT:ICF folded into shared trivial bodies (config/aliases.txt): defined here for
// the authentic link (PLAN M7); the placement link takes the shared bodies.

// ?vf_234@type_3D5658@@UAEPAU1@XZ (folded into `return this` at 0x6FCD0)
type_3D5658 *type_3D5658::vf_234()
{
    return this;
}
