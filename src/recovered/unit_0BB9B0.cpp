// Trigger, the base trigger behaviour: its MakeNew, constructor,
// destructor and handlers, and the helpers the derived triggers share. Its
// original file name is not in the image, so it is named for its start
// address.

#include "rw/ostypes.h"
#include "rw/bamatrix.h"
#include "rws/cattributehandler.h"
#include "rws/cclassfactory.h"
#include "rws/ceventhandler.h"
#include "rws/csystemcommands.h"
#include <math.h>
#include "game/data.h"
#include "game/functions.h"
#include "types/type_44350.h"
#include "types/type_129_base.h"
#include "types/type_3D2E7C.h"
#include "types/alfaobject.h"
#include "types/ccess.h"
#include "types/type_3D51C0.h"
#include "types/type_3DBC78.h"
#include "types/scriptvm.h"
#include <string.h>
#include <stdlib.h>
#include "game/frand.h"
#include "game/pathnodes.h"
#include "types/type_72810.h"
#include "types/CustomTrigger.h"

// Its data definitions (PLAN M5), in the image's address order.
// 0x003D6740
extern const RwReal flt_3D6740 = 16.666666f;
// End of its data definitions.


RWS_IMPLEMENT_CLASSID(Trigger);
RWS_REGISTERCLASS(Trigger);
// Its data (PLAN M5): literals, constants and tables where the image has them.
// match: ??_C@_07MBELDEGC@Trigger?$AA@ @ 0x003D6738
// match: ?flt_3D6740@@3MB @ 0x003D6740
// match: ??_7Trigger@@6BCEventHandler@RWS@@@ @ 0x003D6744
// match: ??_7Trigger@@6BCAttributeHandler@RWS@@@ @ 0x003D674C
// match: ??_C@_0EK@LKHGKEGE@?$CKTrigger?5?$CI?$CFd?$CJ?5being?5moved?5to?3?$CI?$CF6@ @ 0x003D6780
// match: ??_C@_0BN@LNBOAMJP@?7?7Rt?5now?3?$CI?$CF6?43f?0?$CF6?43f?0?$CF6?43f?$CJ?$AA@ @ 0x003D67CC
// match: ??_C@_0BN@EFFPNMMH@?7?7Up?5now?3?$CI?$CF6?43f?0?$CF6?43f?0?$CF6?43f?$CJ?$AA@ @ 0x003D67EC
// match: ??_C@_0BN@FAPOIKAJ@?7?7At?5now?3?$CI?$CF6?43f?0?$CF6?43f?0?$CF6?43f?$CJ?$AA@ @ 0x003D680C
// match: ??_C@_0BO@IFAGDPAD@?7?7Loc?5now?3?$CI?$CF6?43f?0?$CF6?43f?0?$CF6?43f?$CJ?$AA@ @ 0x003D682C
// match: ??_C@_0BO@FKEMPBCA@?7OrthoNormalizing?5trigger?$CI?$CFd?$CJ?$AA@ @ 0x003D684C
// match: ??_C@_0EK@GDAKAICG@?9Trigger?5?$CI?$CFd?$CJ?5being?5moved?5to?3?$CI?$CF6@ @ 0x003D6870
// match: __ehhandler$?MakeNew@Trigger@@SAPAVCAttributeHandler@RWS@@ABVCAttributePacket@3@@Z>1>8 @ 0x0041C2EC
// match: __ehhandler$?MakeNew@Trigger@@SAPAVCAttributeHandler@RWS@@ABVCAttributePacket@3@@Z>1 @ 0x0041C2F4
// match: __ehhandler$??0Trigger@@QAE@ABVCAttributePacket@RWS@@@Z>1>8 @ 0x0041C310
// match: __ehhandler$??0Trigger@@QAE@ABVCAttributePacket@RWS@@@Z>1 @ 0x0041C320
// match: __ehhandler$??1Trigger@@UAE@XZ>1>8 @ 0x0041C33C
// match: __ehhandler$??1Trigger@@UAE@XZ>1 @ 0x0041C34C
// match: .CRT$XCU+0 @ 0x00426F7C
// match: ?pTriggerClassID@Trigger@@2PBDB @ 0x004291CC

// match: _$E2 @ 0x0030AC00
// match: _$E3 @ 0x0030E1D0

// (The class factory's registration and its exit thunk.)

// match: ?MakeNew@Trigger@@SAPAVCAttributeHandler@RWS@@ABVCAttributePacket@3@@Z @ 0x000BB9B0
// match: __ehhandler$?MakeNew@Trigger@@SAPAVCAttributeHandler@RWS@@ABVCAttributePacket@3@@Z-0xF @ 0x003004B0
// match: __ehhandler$?MakeNew@Trigger@@SAPAVCAttributeHandler@RWS@@ABVCAttributePacket@3@@Z @ 0x003004BF
// sp-match: ?MakeNew@Trigger@@SAPAVCAttributeHandler@RWS@@ABVCAttributePacket@3@@Z @ 0x00091F80
RWS_DEFINE_MAKENEW(Trigger)

// match: ??0Trigger@@QAE@ABVCAttributePacket@RWS@@@Z @ 0x000BBA30
// match: __ehhandler$??0Trigger@@QAE@ABVCAttributePacket@RWS@@@Z-0x13 @ 0x003004D0
// match: __ehhandler$??0Trigger@@QAE@ABVCAttributePacket@RWS@@@Z @ 0x003004E3
// sp-match: ??0Trigger@@QAE@ABVCAttributePacket@RWS@@@Z @ 0x00090C70
Trigger::Trigger(const RWS::CAttributePacket &attr)
{
    sub_BBF80(0);
    unk_46 = 0;
    unk_48 = 100.0f;
    unk_4C = 100.0f;
    unk_50 = 100.0f;
    unk_B4 = 0;
    unk_30 = 0;
    unk_AC = 0;
    unk_45 = 0;
    unk_24 = 0;
    unk_A8 = 0;
    RwMatrixSetIdentity(&unk_60_m);
    unk_3C = sub_144C00(this);
    unk_3E = -1;
    unk_40 = -1;
    LinkMsg(dword_4B67B8, 0, 0x8000);
    LinkMsg(dword_4B67C0, 0, 0x8000);
    LinkMsg(dword_4B8750, 0, 0x8000);
    unk_28.unk_00 = 0;
    unk_28.unk_04 = 0;
    unk_34 = 0;
    unk_38 = 0;
    unk_43 = 0;
    unk_44 = -1;
    unk_54 = 0.0f;
    unk_B0 = 0;
}

// match: ??_GTrigger@@UAEPAXI@Z @ 0x000BBCF0
// sp-match: ??_GTrigger@@UAEPAXI@Z @ 0x00091250

// match: ??1Trigger@@UAE@XZ @ 0x000BBD10
// match: __ehhandler$??1Trigger@@UAE@XZ-0x2F @ 0x003004F0
// match: __ehhandler$??1Trigger@@UAE@XZ @ 0x0030051F
// sp-match: ??1Trigger@@UAE@XZ @ 0x00090DF0
Trigger::~Trigger()
{
    type_144940 *lv_14;
    type_144940 *var_10;

    sub_BD310(&unk_A8);
    sub_BE810();
    if (unk_30)
    {
        if (unk_30->unk_00[0])
        {
            sub_BD350(&unk_30->unk_00[0]);
        }
        if (unk_30->unk_00[1])
        {
            sub_BD350(&unk_30->unk_00[1]);
        }
        if (unk_30->unk_00[2])
        {
            sub_BD350(&unk_30->unk_00[2]);
        }
        if (unk_30->unk_00[3])
        {
            sub_BD350(&unk_30->unk_00[3]);
        }
        if (unk_30->unk_00[4])
        {
            sub_BD350(&unk_30->unk_00[4]);
        }
        if (unk_30->unk_00[5])
        {
            sub_BD350(&unk_30->unk_00[5]);
        }
        if (unk_30->unk_00[6])
        {
            sub_BD350(&unk_30->unk_00[6]);
        }
        sub_BD380(&unk_30);
    }
    if (unk_AC)
    {
        sub_BD460(&unk_AC);
    }
    if (unk_B0)
    {
        ::operator delete(unk_B0);
        unk_B0 = 0;
    }
    if (unk_B4)
    {
        lv_14 = unk_B4;
        var_10 = 0;
        while (lv_14)
        {
            var_10 = (type_144940 *)lv_14->unk_00;
            lv_14->sub_144940(0);
            lv_14 = var_10;
        }
        unk_B4 = 0;
    }
    sub_8B250(static_cast<type_712B0 *>(this));
    sub_144C50(this);
    UnLinkMsg(RWS::iMsgRunningTick);
    UnLinkMsg(dword_4B8750);
    UnLinkMsg(dword_4B67B8);
    UnLinkMsg(dword_4B67C0);
}

// match: ?sub_BBF80@Trigger@@QAEXH@Z @ 0x000BBF80
// sp-match: ?sub_BBF80@Trigger@@QAEXH@Z @ 0x00090230
void Trigger::sub_BBF80(RwInt32 arg_0)
{
    unk_42 = (unk_42 & 0xF0) + arg_0;
}

// match: ?HandleAttributes@Trigger@@UAEXABVCAttributePacket@RWS@@@Z @ 0x000BBFB0
// sp-match: ?HandleAttributes@Trigger@@UAEXABVCAttributePacket@RWS@@@Z @ 0x00091710
// The system commands (sub_BD0B0), then command 35 (the buffer at unk_B0,
// unk_24_16) first, then the rest: its key (0, registered as a trigger
// handle) and named object (17), its shape and metrics (1 to 4), flags
// (5, 6, 11, 12, 16, 29 to 33), its facing limits in degrees (7, 8), its
// action icon (9), its blocks (18 to 24), its message filter list (15), its
// script's and task's names (13, 14), a running tick (28) and the buffer's
// fields (36 to 39).
void Trigger::HandleAttributes(const RWS::CAttributePacket &attr)
{
    RWS::CAttributeHandler::HandleAttributes(attr);
    sub_BD0B0(attr);
    RWS::CAttributeCommandIterator attrIt1(attr, RWS_CLASSID_OF(Trigger));
    while (!attrIt1.IsFinished())
    {
        switch (attrIt1->GetCommandId())
        {
        case 35:
        {
            RwInt32 var_14;

            attrIt1->GetCommandData(var_14);
            if (var_14)
            {
                unk_24_16 = 1;
                sub_BEA60();
            }
            else
            {
                unk_24_16 = 0;
            }
            break;
        }
        }
        ++attrIt1;
    }
    RWS::CAttributeCommandIterator attrIt(attr, RWS_CLASSID_OF(Trigger));
    while (!attrIt.IsFinished())
    {
        switch (attrIt->GetCommandId())
        {
        case 0:
            attrIt->GetCommandData(unk_28);
            if (unk_28.unk_00)
            {
                sub_198900((type_3DF8D8_04 *)&unk_28, 0x2E, (void (*)(RwInt32, RwInt32, RwInt32))sub_BDE40, 0, (RwInt32)this, 0);
            }
            break;
        case 17:
            attrIt->GetCommandData(unk_A0);
            if (unk_A0.unk_00 || unk_A0.unk_04)
            {
                sub_198900((type_3DF8D8_04 *)&unk_A0, 0x2E, 0, 0, 0, 0);
            }
            break;
        case 1:
            unk_46 = (RwUInt8)attrIt->GetAs_RwInt32();
            sub_145A40(this);
            break;
        case 2:
            unk_48 = attrIt->GetAs_RwReal();
            sub_145A40(this);
            break;
        case 3:
            unk_4C = attrIt->GetAs_RwReal();
            sub_145A40(this);
            break;
        case 4:
            unk_50 = attrIt->GetAs_RwReal();
            sub_145A40(this);
            break;
        case 28:
            if (attrIt->GetAs_RwInt32())
            {
                LinkMsg(RWS::iMsgRunningTick, 0, 0x8000);
            }
            else
            {
                UnLinkMsg(RWS::iMsgRunningTick);
            }
            break;
        case 29:
            if (attrIt->GetAs_RwInt32())
            {
                unk_24_2 = 1;
            }
            else
            {
                unk_24_2 = 0;
            }
            break;
        case 31:
            if (attrIt->GetAs_RwInt32())
            {
                unk_24_17 = 1;
            }
            else
            {
                unk_24_17 = 0;
            }
            break;
        case 30:
            if (attrIt->GetAs_RwInt32())
            {
                unk_24_4 = 1;
            }
            else
            {
                unk_24_4 = 0;
            }
            break;
        case 33:
            if (attrIt->GetAs_RwInt32())
            {
                unk_24_5 = 1;
            }
            else
            {
                unk_24_5 = 0;
            }
            break;
        case 13:
            sub_198900((type_3DF8D8_04 *)attrIt->GetAs_RwChar_ptr(), 0xA, (void (*)(RwInt32, RwInt32, RwInt32))sub_191EE0, (RwInt32)this,
                       0, 0);
            break;
        case 14:
        {
            const Trigger_key *var_18;
            type_3D2E7C *var_1C;

            var_18 = (const Trigger_key *)attrIt->GetAs_RwChar_ptr();
            var_1C = sub_BDF50();
            if (var_18->unk_00 && var_18->unk_04)
            {
                if (var_1C)
                {
                    var_1C->sub_70DB0();
                }
                sub_198900((type_3DF8D8_04 *)var_18, 0xC, (void (*)(RwInt32, RwInt32, RwInt32))sub_191EE0, (RwInt32)this, 0, 0);
            }
            break;
        }
        case 18:
        {
            RwInt32 var_20 = 0;

            if (unk_30)
            {
                if (unk_30->unk_00[0])
                {
                    sub_BD350(&unk_30->unk_00[0]);
                    var_20 = 1;
                }
            }
            else
            {
                sub_BD3B0(&unk_30);
            }
            sub_BD490(attrIt->GetAs_RwChar_ptr(), &unk_30->unk_00[0]);
            if (!var_20 && unk_30->unk_00[0])
            {
                sub_145A10(this);
            }
            sub_BD3D0(&unk_30);
            break;
        }
        case 19:
        {
            RwInt32 var_24 = 0;

            if (unk_30)
            {
                if (unk_30->unk_00[1])
                {
                    sub_BD350(&unk_30->unk_00[1]);
                    var_24 = 1;
                }
            }
            else
            {
                sub_BD3B0(&unk_30);
            }
            sub_BD490(attrIt->GetAs_RwChar_ptr(), &unk_30->unk_00[1]);
            if (!var_24 && unk_30->unk_00[1])
            {
                sub_145A10(this);
            }
            sub_BD3D0(&unk_30);
            break;
        }
        case 20:
        {
            RwInt32 var_28 = 0;

            if (unk_30)
            {
                if (unk_30->unk_00[2])
                {
                    sub_BD350(&unk_30->unk_00[2]);
                    var_28 = 1;
                }
            }
            else
            {
                sub_BD3B0(&unk_30);
            }
            sub_BD490(attrIt->GetAs_RwChar_ptr(), &unk_30->unk_00[2]);
            if (!var_28 && unk_30->unk_00[2])
            {
                sub_145A10(this);
            }
            sub_BD3D0(&unk_30);
            break;
        }
        case 21:
        {
            RwInt32 var_2C = 0;

            if (unk_30)
            {
                if (unk_30->unk_00[3])
                {
                    sub_BD350(&unk_30->unk_00[3]);
                    var_2C = 1;
                }
            }
            else
            {
                sub_BD3B0(&unk_30);
            }
            sub_BD490(attrIt->GetAs_RwChar_ptr(), &unk_30->unk_00[3]);
            if (!var_2C && unk_30->unk_00[3])
            {
                sub_145A10(this);
            }
            sub_BD3D0(&unk_30);
            break;
        }
        case 22:
        {
            RwInt32 var_30 = 0;

            if (unk_30)
            {
                if (unk_30->unk_00[4])
                {
                    sub_BD350(&unk_30->unk_00[4]);
                    var_30 = 1;
                }
            }
            else
            {
                sub_BD3B0(&unk_30);
            }
            sub_BD490(attrIt->GetAs_RwChar_ptr(), &unk_30->unk_00[4]);
            if (!var_30 && unk_30->unk_00[4])
            {
                sub_145A10(this);
            }
            sub_BD3D0(&unk_30);
            break;
        }
        case 23:
            if (unk_30)
            {
                if (unk_30->unk_00[5])
                {
                    sub_BD350(&unk_30->unk_00[5]);
                }
            }
            else
            {
                sub_BD3B0(&unk_30);
            }
            sub_BD490(attrIt->GetAs_RwChar_ptr(), &unk_30->unk_00[5]);
            sub_BD3D0(&unk_30);
            break;
        case 24:
        {
            RwInt32 var_34 = 0;

            if (unk_30)
            {
                if (unk_30->unk_00[6])
                {
                    sub_BD350(&unk_30->unk_00[6]);
                    var_34 = 1;
                }
            }
            else
            {
                sub_BD3B0(&unk_30);
            }
            sub_BD490(attrIt->GetAs_RwChar_ptr(), &unk_30->unk_00[6]);
            if (!var_34 && unk_30->unk_00[6])
            {
                sub_145A10(this);
            }
            sub_BD3D0(&unk_30);
            break;
        }
        case 15:
            if (unk_AC)
            {
                sub_BD460(&unk_AC);
            }
            sub_BDB60(attrIt->GetAs_RwChar_ptr());
            break;
        case 5:
            unk_24_7 = attrIt->GetAs_RwInt32();
            break;
        case 6:
            unk_24_12 = attrIt->GetAs_RwInt32();
            break;
        case 7:
            unk_34 = cos(attrIt->GetAs_RwReal() * 0.5f * 0.017453292f);
            break;
        case 8:
            unk_38 = cos(attrIt->GetAs_RwReal() * 0.5f * 0.017453292f);
            break;
        case 9:
        {
            RwUInt8 var_35;

            var_35 = (RwUInt8)attrIt->GetAs_RwInt32();
            sub_BBF80(var_35);
            unk_42 = unk_42 << 4;
            sub_BBF80(var_35);
            break;
        }
        case 10:
            unk_43 = (RwUInt8)attrIt->GetAs_RwInt32();
            break;
        case 34:
            unk_44 = (RwInt8)attrIt->GetAs_RwInt32();
            break;
        case 16:
            unk_24_13 = attrIt->GetAs_RwInt32();
            break;
        case 11:
        {
            RwInt32 var_3C;

            attrIt->GetCommandData(var_3C);
            if (var_3C)
            {
                unk_24_9 = 1;
            }
            else
            {
                unk_24_9 = 0;
            }
            break;
        }
        case 12:
        {
            RwInt32 var_40;

            attrIt->GetCommandData(var_40);
            if (var_40)
            {
                unk_24_10 = 1;
            }
            else
            {
                unk_24_10 = 0;
            }
            break;
        }
        case 36:
            if (unk_B0)
            {
                ((Trigger_B0 *)unk_B0)->unk_00 = attrIt->GetAs_RwInt32();
            }
            break;
        case 37:
            if (unk_B0)
            {
                ((Trigger_B0 *)unk_B0)->unk_04 = attrIt->GetAs_RwInt32();
            }
            break;
        case 38:
            if (unk_B0)
            {
                ((Trigger_B0 *)unk_B0)->unk_08 = attrIt->GetAs_RwInt32();
            }
            break;
        case 39:
            if (unk_B0)
            {
                attrIt->GetCommandData(((Trigger_B0 *)unk_B0)->unk_0C);
            }
            break;
        }
        ++attrIt;
    }
}

// match: ?HandleEvents@Trigger@@UAEXAAVCMsg@RWS@@@Z @ 0x000BCF10
// sp-match: ?HandleEvents@Trigger@@UAEXAAVCMsg@RWS@@@Z @ 0x00091260
// dword_4B67B8 (a restart) moves it back, takes its script's id and lets
// its script object go (clearing unk_24_3 and its CCESS slot, and its
// action icon from the high four bits); dword_4B67C0 and dword_4B8750 make
// it a new script object (dword_4B8750 once, setting unk_24_14).
void Trigger::HandleEvents(RWS::CMsg &pMsg)
{
    type_3D2E7C *var_4;
    type_72990 *local_8;

    if (pMsg.Id.p_msgrec == RWS::iMsgRunningTick.p_msgrec)
    {
        return;
    }
    if (pMsg.Id.p_msgrec == dword_4B67B8.p_msgrec)
    {
        sub_BE810();
        unk_3E = 0xFFFF;
        var_4 = sub_BDF50();
        if (var_4)
        {
            local_8 = var_4->unk_08;
            if (local_8)
            {
                unk_3E = (RwUInt16)local_8->unk_04;
            }
        }
        sub_BD310(&unk_A8);
        sub_8B250(static_cast<type_712B0 *>(this));
        set_unk_24_3(true);
        sub_BBF80(unk_42 >> 4);
    }
    else if (pMsg.Id.p_msgrec == dword_4B67C0.p_msgrec)
    {
        if (unk_3E != 0xFFFF || unk_40 != 0xFFFF)
        {
            sub_BD290(&unk_A8, unk_3E, unk_40);
        }
    }
    else if (pMsg.Id.p_msgrec == dword_4B8750.p_msgrec)
    {
        if (unk_3E != 0xFFFF || unk_40 != 0xFFFF)
        {
            sub_BD290(&unk_A8, unk_3E, unk_40);
        }
        unk_24 |= 0x4000;
        UnLinkMsg(dword_4B8750);
    }
}

// match: ?sub_BD0B0@Trigger@@QAEXABVCAttributePacket@RWS@@@Z @ 0x000BD0B0
// sp-match: ?sub_BD0B0@Trigger@@QAEXABVCAttributePacket@RWS@@@Z @ 0x00090250
// The system commands: its matrix (orthonormalised, marking unk_24_0).
void Trigger::sub_BD0B0(const RWS::CAttributePacket &attr)
{
    RwMatrix var_60;

    RWS::CAttributeCommandIterator attrIt(attr, RWS::CSystemCommands::pCSystemCommandsClassID);
    while (!attrIt.IsFinished())
    {
        switch (attrIt->GetCommandId())
        {
        case RWS::CSystemCommands::CMD_LoadMatrix:
        {
            const RwMatrixTag *pMatrix = (const RwMatrixTag *)attrIt->GetAs_RwChar_ptr();

            unk_60_m = *pMatrix;
            var_60 = unk_60_m;
            RwMatrixOrthoNormalize((RwMatrix *)&unk_60_m, &var_60);
            RwMatrixOptimize((RwMatrix *)&unk_60_m, 0);
            unk_24 |= 1;
            sub_145A40(this);
            break;
        }
        }
        ++attrIt;
    }
}

// match: ?sub_BD1A0@Trigger@@QAEXPAUtype_144940@@@Z @ 0x000BD1A0
// sp-match: ?sub_BD1A0@Trigger@@QAEXPAUtype_144940@@@Z @ 0x00090310
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void Trigger::sub_BD1A0(type_144940 *arg_0)
{
    type_144940 *local_8;
    type_144940 *var_4;

    var_4 = unk_B4;
    arg_0->unk_00 = (RwInt32)var_4;
    arg_0->unk_04 = 0;
    if (unk_B4)
    {
        local_8 = unk_B4;
        local_8->unk_04 = (RwInt32)arg_0;
    }
    unk_B4 = arg_0;
}

// match: ?sub_BD200@Trigger@@QAEXPAUtype_144940@@@Z @ 0x000BD200
// sp-match: ?sub_BD200@Trigger@@QAEXPAUtype_144940@@@Z @ 0x00090340
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void Trigger::sub_BD200(type_144940 *arg_0)
{
    type_144940 *var_4;
    type_144940 *v8;
    type_144940 *stk_C;
    type_144940 *var_10;

    var_4 = (type_144940 *)arg_0->unk_04;
    if (var_4)
    {
        v8 = (type_144940 *)arg_0->unk_00;
        var_4->unk_00 = (RwInt32)v8;
    }
    var_4 = (type_144940 *)arg_0->unk_00;
    if (var_4)
    {
        stk_C = (type_144940 *)arg_0->unk_04;
        var_4->unk_04 = (RwInt32)stk_C;
    }
    if (arg_0 == unk_B4)
    {
        var_10 = (type_144940 *)arg_0->unk_00;
        unk_B4 = var_10;
    }
    arg_0->unk_00 = 0;
    arg_0->unk_04 = 0;
}

// match: ?sub_BD290@Trigger@@QAEXPAHGG@Z @ 0x000BD290
// sp-match: ?sub_BD290@Trigger@@QAEXPAHGG@Z @ 0x00090FA0
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void Trigger::sub_BD290(RwInt32 *arg_0, RwUInt16 arg_4, RwUInt16 arg_8)
{
    type_3D2E7C *var_4;
    RwUInt32 local_8;

    sub_BD310(arg_0);
    local_8 = sub_71870();
    *arg_0 = local_8;
    var_4 = (type_3D2E7C *)sub_67620(*arg_0);
    var_4->sub_70DF0((type_3D3548 *)this, 1);
    if (arg_4 != 0xFFFF)
    {
        var_4->sub_70E10(arg_4, 1);
    }
    if (arg_8 != 0xFFFF)
    {
        var_4->sub_70F40(arg_8, 1);
    }
}

// match: ?sub_BD310@Trigger@@QAEXPAH@Z @ 0x000BD310
// sp-match: ?sub_BD310@Trigger@@QAEXPAH@Z @ 0x00090380
void Trigger::sub_BD310(RwInt32 *arg_0)
{
    type_67620 *var_4;

    var_4 = sub_67620(*arg_0);
    if (var_4)
    {
        sub_71970((type_3D2C88 *)var_4);
    }
    *arg_0 = 0;
}

// match: ?sub_BD350@Trigger@@QAEXPAPAE@Z @ 0x000BD350
// sp-match: ?sub_BD350@Trigger@@QAEXPAPAE@Z @ 0x000903B0
void Trigger::sub_BD350(RwUInt8 **arg_0)
{
    sub_145790(*arg_0);
    *arg_0 = 0;
}

// match: ?sub_BD380@Trigger@@QAEXPAPAUTrigger_30@@@Z @ 0x000BD380
// sp-match: ?sub_BD380@Trigger@@QAEXPAPAUTrigger_30@@@Z @ 0x000903D0
void Trigger::sub_BD380(Trigger_30 **arg_0)
{
    sub_1457B0(*arg_0);
    *arg_0 = 0;
}

// match: ?sub_BD3B0@Trigger@@QAEXPAPAUTrigger_30@@@Z @ 0x000BD3B0
// sp-match: ?sub_BD3B0@Trigger@@QAEXPAPAUTrigger_30@@@Z @ 0x000903F0
void Trigger::sub_BD3B0(Trigger_30 **arg_0)
{
    *arg_0 = sub_1457D0();
}

// match: ?sub_BD3D0@Trigger@@QAEXPAPAUTrigger_30@@@Z @ 0x000BD3D0
// sp-match: ?sub_BD3D0@Trigger@@QAEXPAPAUTrigger_30@@@Z @ 0x00090400
// Frees the block list *arg_0 once all seven of its blocks are gone.
void Trigger::sub_BD3D0(Trigger_30 **arg_0)
{
    RwInt32 var_4;

    if (arg_0 && *arg_0)
    {
        var_4 = 1;
        if ((*arg_0)->unk_00[2] || (*arg_0)->unk_00[3] || (*arg_0)->unk_00[4] || (*arg_0)->unk_00[6]
            || (*arg_0)->unk_00[5] || (*arg_0)->unk_00[0] || (*arg_0)->unk_00[1])
        {
            var_4 = 0;
        }
        if (var_4)
        {
            sub_BD380(arg_0);
        }
    }
}

// match: ?sub_BD460@Trigger@@QAEXPAPAUtype_71250@@@Z @ 0x000BD460
// sp-match: ?sub_BD460@Trigger@@QAEXPAPAUtype_71250@@@Z @ 0x00090450
void Trigger::sub_BD460(type_71250 **arg_0)
{
    sub_6CA20(*arg_0);
    *arg_0 = 0;
    unk_45 = 0;
}

// match: ?sub_BD490@Trigger@@QAEXPBDPAPAE@Z @ 0x000BD490
// sp-match: ?sub_BD490@Trigger@@QAEXPBDPAPAE@Z @ 0x00090480
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void Trigger::sub_BD490(const RwChar *arg_0, RwUInt8 **arg_4)
{
    RwInt32 var_4;
    RwInt32 v8;
    RwInt32 stk_C;
    RwInt32 var_10;

    stk_C = *(const RwInt32 *)arg_0;
    arg_0 += 4;
    if (!stk_C)
    {
        return;
    }
    *arg_4 = (RwUInt8 *)sub_145770();
    memset(*arg_4, -1, 0x20);
    v8 = 0;
    var_4 = 0;
    for (var_10 = 0; var_10 < stk_C; var_10++)
    {
        v8 = *(const RwInt32 *)arg_0;
        arg_0 += 4;
        var_4 = *(const RwInt32 *)arg_0;
        arg_0 += 4;
        ((Trigger_block *)*arg_4)->unk_14[var_10] = sub_6A860(v8, var_4);
        ((Trigger_block *)*arg_4)->unk_00[var_10] = *(const RwInt32 *)arg_0;
        arg_0 += 4;
    }
}

// match: ?sub_BD560@Trigger@@QAEXPAUtype_3D3548@@@Z @ 0x000BD560
// sp-match: ?sub_BD560@Trigger@@QAEXPAUtype_3D3548@@@Z @ 0x00091360
// Runs the block for an entity of the kind arg_0 (its unk_2C kind bits):
// block 0 for kind 0x10, 2 for 0x20 and 0x20000 (and for 0x80 and 0x40000
// unless its player passenger is of kind 0x10), 4 for 0x100, 0x2000 and
// 0x200000.
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void Trigger::sub_BD560(type_3D3548 *arg_0)
{
    RwUInt8 *var_4;
    type_3DBC78 *v8;
    type_3D3548 *varC;

    var_4 = 0;
    if (unk_30)
    {
        switch (arg_0->unk_2C & 0x3FFFFF0) // not an address: kind bits
        {
        case 0x10:
            var_4 = unk_30->unk_00[0];
            break;
        case 0x80:
        case 0x40000: // not an address: kind bits
            v8 = arg_0->vf_010();
            varC = v8->unk_118C.sub_D4910();
            if (!varC || (varC->unk_2C & 0x3FFFFF0) != 0x10) // not an address: kind bits
            {
                var_4 = unk_30->unk_00[2];
            }
            break;
        case 0x20:
        case 0x20000: // not an address: kind bits
            var_4 = unk_30->unk_00[2];
            break;
        case 0x100:
        case 0x2000: // not an address: kind bits
        case 0x200000: // not an address: kind bits
            var_4 = unk_30->unk_00[4];
            break;
        }
    }
    if (var_4)
    {
        sub_BD900(var_4, arg_0);
    }
}

// match: ?sub_BD780@Trigger@@QAEXPAUtype_3D3548@@@Z @ 0x000BD780
// sp-match: ?sub_BD780@Trigger@@QAEXPAUtype_3D3548@@@Z @ 0x00091500
// sub_BD560's counterpart: block 1 for kind 0x10, 3 for the others.
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void Trigger::sub_BD780(type_3D3548 *arg_0)
{
    RwUInt8 *var_4;
    type_3DBC78 *v8;
    type_3D3548 *varC;

    var_4 = 0;
    if (unk_30)
    {
        switch (arg_0->unk_2C & 0x3FFFFF0) // not an address: kind bits
        {
        case 0x10:
            var_4 = unk_30->unk_00[1];
            break;
        case 0x80:
        case 0x40000: // not an address: kind bits
            v8 = arg_0->vf_010();
            varC = v8->unk_118C.sub_D4910();
            if (!varC || (varC->unk_2C & 0x3FFFFF0) != 0x10) // not an address: kind bits
            {
                var_4 = unk_30->unk_00[3];
            }
            break;
        case 0x20:
        case 0x20000: // not an address: kind bits
            var_4 = unk_30->unk_00[3];
            break;
        }
    }
    if (var_4)
    {
        sub_BD900(var_4, arg_0);
    }
}

// match: ?sub_BD860@Trigger@@QAEXXZ @ 0x000BD860
// sp-match: ?sub_BD860@Trigger@@QAEXXZ @ 0x00091580
void Trigger::sub_BD860()
{
    if (unk_30 && unk_30->unk_00[5])
    {
        sub_BD900(unk_30->unk_00[5], 0);
    }
}

// match: ?sub_BD8A0@Trigger@@QAEXPAUtype_3D3548@@@Z @ 0x000BD8A0
// sp-match: ?sub_BD8A0@Trigger@@QAEXPAUtype_3D3548@@@Z @ 0x000915A0
// Runs block 6 for an entity of kind 0x10.
void Trigger::sub_BD8A0(type_3D3548 *arg_0)
{
    RwUInt8 *var_4;

    var_4 = 0;
    if (unk_30)
    {
        switch (arg_0->unk_2C & 0x3FFFFF0) // not an address: kind bits
        {
        case 0x10:
            var_4 = unk_30->unk_00[6];
            break;
        }
    }
    if (var_4)
    {
        sub_BD900(var_4, 0);
    }
}

// match: ?sub_BD900@Trigger@@QAEXPAEPAUtype_3D3548@@@Z @ 0x000BD900
// sp-match: ?sub_BD900@Trigger@@QAEXPAEPAUtype_3D3548@@@Z @ 0x00091000
// Sends the messages of the block arg_0 (up to five, each with its value)
// from the entity arg_4 to its script object, or, with unk_24_13, to the
// named object unk_A0's (an entity's, or a trigger's); nothing when that
// object has none.
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void Trigger::sub_BD900(RwUInt8 *arg_0, type_3D3548 *arg_4)
{
    RwInt32 l4;
    type_3D2E7C *var_8;
    type_3D2E7C *fp_C;
    type_3DF8D8_BD900 *local_10;
    type_3D3548 *stk_14;
    Trigger *lcl_18;
    RwInt32 fp_1C;
    RwInt32 ebp_20;

    fp_C = arg_4 ? arg_4->vf_098() : 0;
    var_8 = 0;
    l4 = 1;
    if (unk_24_13)
    {
        if (unk_A0.unk_00 || unk_A0.unk_04)
        {
            local_10 = (type_3DF8D8_BD900 *)sub_198800(&unk_A0);
            if (local_10)
            {
                if (local_10->unk_10 & 2)
                {
                    stk_14 = local_10->unk_24.sub_D4910();
                    if (stk_14)
                    {
                        if (stk_14->vf_098())
                        {
                            var_8 = stk_14->vf_098();
                        }
                        else
                        {
                            l4 = 0;
                        }
                    }
                    else
                    {
                        l4 = 0;
                    }
                }
                else if (local_10->unk_10)
                {
                    lcl_18 = local_10->unk_2C;
                    if (lcl_18)
                    {
                        if (lcl_18->sub_BDF50())
                        {
                            var_8 = lcl_18->sub_BDF50();
                        }
                        else
                        {
                            l4 = 0;
                        }
                    }
                    else
                    {
                        l4 = 0;
                    }
                }
                else
                {
                    l4 = 0;
                }
            }
        }
        else if (fp_C)
        {
            var_8 = fp_C;
        }
        else
        {
            l4 = 0;
        }
    }
    if (!l4)
    {
        return;
    }
    for (fp_1C = 0; fp_1C < 5 && ((Trigger_block *)arg_0)->unk_14[fp_1C] != 0xFFFF; fp_1C++)
    {
#ifdef CODFH_SP
        // shape: the value in a loop-scoped local (SP 0x91000 keeps it in the dead argument's slot)
        RwInt32 val = ((Trigger_block *)arg_0)->unk_00[fp_1C];
        sub_6B680(((Trigger_block *)arg_0)->unk_14[fp_1C], (type_67620 *)var_8, (type_42E00_10 *)((RwInt32)this), (type_3D2E7C *)((RwInt32)fp_C), &val, 1, 1, 0);
#else
        ebp_20 = ((Trigger_block *)arg_0)->unk_00[fp_1C];
        sub_6B680(((Trigger_block *)arg_0)->unk_14[fp_1C], (type_67620 *)var_8, (type_42E00_10 *)((RwInt32)this), (type_3D2E7C *)((RwInt32)fp_C), &ebp_20, 1, 1, 0);
#endif
    }
}

// match: ?sub_BDAC0@Trigger@@QAEXHHPAUtype_3D2E7C@@@Z @ 0x000BDAC0
// sp-match: ?sub_BDAC0@Trigger@@QAEXHHPAUtype_3D2E7C@@@Z @ 0x00090500
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void Trigger::sub_BDAC0(RwInt32 arg_0, RwInt32 arg_4, type_3D2E7C *arg_8)
{
    type_3D2E7C *var_4;
    RwInt32 v8;
    RwInt32 varC;

    var_4 = arg_4 ? ((type_3D3548 *)arg_4)->vf_098() : 0;
    for (v8 = 0; v8 < 5 && ((Trigger_block *)arg_0)->unk_14[v8] != 0xFFFF; v8++)
    {
#ifdef CODFH_SP
        // shape: the value in a loop-scoped local (SP 0x90500 keeps it in the dead argument's slot)
        RwInt32 val = ((Trigger_block *)arg_0)->unk_00[v8];
        sub_6B680(((Trigger_block *)arg_0)->unk_14[v8], (type_67620 *)arg_8, (type_42E00_10 *)((RwInt32)this), (type_3D2E7C *)((RwInt32)var_4), &val, 1, 1, 0);
#else
        varC = ((Trigger_block *)arg_0)->unk_00[v8];
        sub_6B680(((Trigger_block *)arg_0)->unk_14[v8], (type_67620 *)arg_8, (type_42E00_10 *)((RwInt32)this), (type_3D2E7C *)((RwInt32)var_4), &varC, 1, 1, 0);
#endif
    }
}

// match: ?sub_BDB60@Trigger@@QAEXPBD@Z @ 0x000BDB60
// sp-match: ?sub_BDB60@Trigger@@QAEXPBD@Z @ 0x00091650
// Builds its message filter list (unk_AC) from a count and that many pairs
// of named variables: each pair's channel (sub_BDC90) and rank (sub_BDD10)
// fill their entry when registered, and the list is sorted once all are in.
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void Trigger::sub_BDB60(const RwChar *arg_0)
{
    Trigger_key var_8;
    RwInt32 local_C;
    RwInt32 var_10;

    local_C = *(const RwInt32 *)arg_0;
    arg_0 += 4;
    if (!local_C)
    {
        return;
    }
    unk_AC = sub_6C9D0(local_C);
    unk_AC->unk_00 = (RwUInt8)local_C;
    var_8.unk_00 = 0;
    var_8.unk_04 = 0;
    for (var_10 = 0; var_10 < local_C; var_10++)
    {
        var_8.unk_00 = *(const RwInt32 *)arg_0;
        arg_0 += 4;
        var_8.unk_04 = *(const RwInt32 *)arg_0;
        arg_0 += 4;
        sub_198900((type_3DF8D8_04 *)&var_8, 1, (void (*)(RwInt32, RwInt32, RwInt32))sub_BDC90, (RwInt32)this,
                   var_10, 0);
        var_8.unk_00 = *(const RwInt32 *)arg_0;
        arg_0 += 4;
        var_8.unk_04 = *(const RwInt32 *)arg_0;
        arg_0 += 4;
        sub_198900((type_3DF8D8_04 *)&var_8, 1, (void (*)(RwInt32, RwInt32, RwInt32))sub_BDD10, (RwInt32)this,
                   var_10, 0);
        unk_AC->unk_02[var_10].unk_02 = 0xFFFF;
        unk_AC->unk_02[var_10].unk_00 = 0xFF;
    }
}

// match: ?sub_BDC90@@YAHHHH@Z @ 0x000BDC90
// sp-match: ?sub_BDC90@@YAHHHH@Z @ 0x000915D0
// The channel variable arg_0 of the trigger arg_4's filter entry arg_8
// (sub_198900's callback); sorts the list once every value is in.
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
RwInt32 sub_BDC90(RwInt32 arg_0, RwInt32 arg_4, RwInt32 arg_8)
{
    RwInt32 var_4;
    type_FA620 *v8;
    RwInt32 stk_C;
    type_71250 *var_10;
    Trigger *lv_14;

    v8 = (type_FA620 *)arg_0;
    lv_14 = (Trigger *)arg_4;
    stk_C = arg_8;
    var_10 = lv_14->unk_AC;
    var_4 = v8->unk_10;
    var_10->unk_02[stk_C].unk_00 = (RwUInt8)var_4;
    if (lv_14->inc_unk_45() == var_10->unk_00 * 2)
    {
        sub_BDD90(var_10);
    }
    return 0;
}

// match: ?sub_BDD10@@YAHHHH@Z @ 0x000BDD10
// sp-match: ?sub_BDD10@@YAHHHH@Z @ 0x00091610
// Likewise for the rank.
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
RwInt32 sub_BDD10(RwInt32 arg_0, RwInt32 arg_4, RwInt32 arg_8)
{
    RwInt32 var_4;
    type_FA620 *v8;
    RwInt32 stk_C;
    type_71250 *var_10;
    Trigger *lv_14;

    v8 = (type_FA620 *)arg_0;
    lv_14 = (Trigger *)arg_4;
    stk_C = arg_8;
    var_10 = lv_14->unk_AC;
    var_4 = v8->unk_10;
    var_10->unk_02[stk_C].unk_02 = (RwUInt16)var_4;
    if (lv_14->inc_unk_45() == var_10->unk_00 * 2)
    {
        sub_BDD90(var_10);
    }
    return 0;
}

// match: ?sub_BDD90@@YAXPAUtype_71250@@@Z @ 0x000BDD90
// sp-match: ?sub_BDD90@@YAXPAUtype_71250@@@Z @ 0x00091120
void sub_BDD90(type_71250 *arg_0)
{
    qsort(arg_0->unk_02, arg_0->unk_00, 4, sub_BDDC0);
}

// match: ?sub_BDDC0@@YAHPBX0@Z @ 0x000BDDC0
// sp-match: ?sub_BDDC0@@YAHPBX0@Z @ 0x00090580
// By channel, then by rank.
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
RwInt32 __cdecl sub_BDDC0(const void *arg_0, const void *arg_4)
{
    const type_71250_02 *local_8;
    const type_71250_02 *var_4;

    local_8 = (const type_71250_02 *)arg_0;
    var_4 = (const type_71250_02 *)arg_4;
    if (local_8->unk_00 < var_4->unk_00)
    {
        return -1;
    }
    if (local_8->unk_00 > var_4->unk_00)
    {
        return 1;
    }
    if (local_8->unk_02 < var_4->unk_02)
    {
        return -1;
    }
#ifdef CODFH_SP
    // shape: the last test as the returned value (SP 0x90580)
    return local_8->unk_02 > var_4->unk_02;
#else
    if (local_8->unk_02 > var_4->unk_02)
    {
        return 1;
    }
    return 0;
#endif
}

// match: ?sub_BDE40@@YAHHHH@Z @ 0x000BDE40
// sp-match: ?sub_BDE40@@YAHHHH@Z @ 0x000905C0
// A trigger-handle variable arg_0 made to hold the trigger arg_8
// (sub_198900's callback).
RwInt32 sub_BDE40(RwInt32 arg_0, RwInt32 arg_4, RwInt32 arg_8)
{
    type_BDE40 *var_4;

    var_4 = (type_BDE40 *)arg_0;
    var_4->unk_24.sub_144940((Trigger *)arg_8);
    var_4->unk_10 = 1;
    return 1;
}

// match: ?sub_BDE70@Trigger@@QAEXG@Z @ 0x000BDE70
// sp-match: ?sub_BDE70@Trigger@@QAEXG@Z @ 0x00091140
// Sets its script (unk_3E) and, once its script object is live (unk_24_14),
// starts it, making the object first when there is none.
void Trigger::sub_BDE70(RwUInt16 arg_0)
{
    unk_3E = arg_0;
    if (unk_24_14)
    {
        if (!sub_BDF50())
        {
            sub_BD290(&unk_A8, 0xFFFF, 0xFFFF);
        }
        sub_BDF50()->sub_70E10(arg_0, 1);
    }
}

// match: ?sub_BDEE0@Trigger@@QAEXG@Z @ 0x000BDEE0
// sp-match: ?sub_BDEE0@Trigger@@QAEXG@Z @ 0x00091190
// Likewise for its task function (unk_40).
void Trigger::sub_BDEE0(RwUInt16 arg_0)
{
    unk_40 = arg_0;
    if (unk_24_14)
    {
        if (!sub_BDF50())
        {
            sub_BD290(&unk_A8, 0xFFFF, 0xFFFF);
        }
        sub_BDF50()->sub_70F40(arg_0, 1);
    }
}

// match: ?sub_BDF50@Trigger@@QAEPAUtype_3D2E7C@@XZ @ 0x000BDF50
// sp-match: ?sub_BDF50@Trigger@@QAEPAUtype_3D2E7C@@XZ @ 0x000905E0
type_3D2E7C *Trigger::sub_BDF50()
{
    return (type_3D2E7C *)sub_67620(unk_A8);
}

// match: ?sub_BDF70@Trigger@@QAEXPAURwV3d@@@Z @ 0x000BDF70
// sp-match: ?sub_BDF70@Trigger@@QAEXPAURwV3d@@@Z @ 0x000905F0
// A random point inside its shape (a sphere's cube, a cylinder's box or a
// box), through its matrix, into *arg_0.
void Trigger::sub_BDF70(RwV3d *arg_0)
{
    RwV3d var_C;

    if (!arg_0)
    {
        return;
    }
    switch (get_unk_46())
    {
    case 0:
        var_C.x = var_C.y = var_C.z = get_unk_48();
        break;
    case 1:
        var_C.x = var_C.z = get_unk_48();
        var_C.y = get_unk_4C() / 2.0f;
        break;
    case 2:
        var_C.x = get_unk_48() / 2.0f;
        var_C.y = get_unk_4C() / 2.0f;
        var_C.z = get_unk_50() / 2.0f;
        break;
    default:
        var_C.x = var_C.y = var_C.z = 0.0f;
        break;
    }
    var_C.x = frand_range(-var_C.x, var_C.x);
    var_C.y = frand_range(-var_C.y, var_C.y);
    var_C.z = frand_range(-var_C.z, var_C.z);
    sub_1414C0(arg_0, &var_C, (RwMatrix *)&unk_60_m);
}

// match: ?vf_028@Trigger@@UAEHPAURwMatrixTag@@@Z @ 0x000BE110
// sp-match: ?vf_028@Trigger@@UAEHPAURwMatrixTag@@@Z @ 0x00090760
// Whether the matrix arg_0 faces the trigger's way (always, unless
// unk_24_7): its at axis, laid into the trigger's right-at plane, must be
// within unk_34 of the trigger's at axis, and laid into its up-at plane
// within unk_38 of it either way.
RwInt32 Trigger::vf_028(RwMatrixTag *arg_0)
{
    RwV3d *l4;
    RwV3d *var_8;
    RwV3d fp_14;
    RwReal var_18;
    RwV3d *slot_1C;
    RwV3d v28;
    RwV3d v34;
    RwMatrixTag *l38;

    if (!unk_24_7)
    {
        return 1;
    }
    l38 = &unk_60_m;
    slot_1C = &l38->at;
    var_8 = &l38->right;
    v28.x = arg_0->at.x;
    v28.y = arg_0->at.y;
    v28.z = arg_0->at.z;
    RwV3dScaleMacro(&v34, var_8, RwV3dDotProductMacro(&v28, var_8));
    RwV3dScaleMacro(&fp_14, slot_1C, RwV3dDotProductMacro(&v28, slot_1C));
    RwV3dAddMacro(&v34, &v34, &fp_14);
#ifdef CODFH_SP // shape: z first
    if (v34.z * v34.z + v34.y * v34.y + v34.x * v34.x == 0.0f)
#else
    if (RwV3dDotProductMacro(&v34, &v34) == 0.0f)
#endif
    {
    }
    else
    {
        RwV3dNormalize(&v34, &v34);
    }
    var_18 = RwV3dDotProductMacro(&v34, slot_1C);
    if (var_18 < unk_34)
    {
        return 0;
    }
    l4 = &l38->up;
#ifdef CODFH_SP // shape: the up axis read through l38
    RwV3dScaleMacro(&v34, &l38->up, RwV3dDotProductMacro(&v28, &l38->up));
#else
    RwV3dScaleMacro(&v34, l4, RwV3dDotProductMacro(&v28, l4));
#endif
    RwV3dAddMacro(&v34, &v34, &fp_14);
    RwV3dNormalize(&v34, &v34);
    var_18 = RwV3dDotProductMacro(&v34, slot_1C);
    var_18 = absref(var_18);
    if (var_18 < unk_38)
    {
        return 0;
    }
    return 1;
}

// match: ?vf_02C@Trigger@@UAEHPAURwMatrixTag@@@Z @ 0x000BE410
// sp-match: ?vf_02C@Trigger@@UAEHPAURwMatrixTag@@@Z @ 0x00090950
// Whether the matrix arg_0 faces the trigger (always, unless unk_24_12):
// likewise, against the direction to the trigger and the level axes about
// it.
RwInt32 Trigger::vf_02C(RwMatrixTag *arg_0)
{
    RwV3d var_C;
    RwV3d var_18;
    RwV3d slot_24;
    RwReal v28;
    RwV3d v34;
    RwV3d bp_40;
    RwV3d stk_4C;

    if (!unk_24_12)
    {
        return 1;
    }
    RwV3dSubMacro(&var_C, &unk_60_m.pos, &arg_0->pos);
    RwV3dNormalize(&var_C, &var_C);
    stk_4C.x = 0.0f;
    stk_4C.y = 1.0f;
    stk_4C.z = 0.0f;
    RwV3dCrossProductMacro(&slot_24, &stk_4C, &var_C);
    v34.x = arg_0->at.x;
    v34.y = arg_0->at.y;
    v34.z = arg_0->at.z;
    RwV3dScaleMacro(&bp_40, &slot_24, RwV3dDotProductMacro(&v34, &slot_24));
    RwV3dScaleMacro(&var_18, &var_C, RwV3dDotProductMacro(&v34, &var_C));
    RwV3dAddMacro(&bp_40, &bp_40, &var_18);
#ifdef CODFH_SP // shape: z first
    if (bp_40.z * bp_40.z + bp_40.y * bp_40.y + bp_40.x * bp_40.x == 0.0f)
#else
    if (RwV3dDotProductMacro(&bp_40, &bp_40) == 0.0f)
#endif
    {
    }
    else
    {
        RwV3dNormalize(&bp_40, &bp_40);
    }
    v28 = RwV3dDotProductMacro(&bp_40, &var_C);
    if (v28 < unk_34)
    {
        return 0;
    }
    RwV3dScaleMacro(&bp_40, &stk_4C, RwV3dDotProductMacro(&v34, &stk_4C));
    RwV3dAddMacro(&bp_40, &bp_40, &var_18);
    RwV3dNormalize(&bp_40, &bp_40);
    v28 = RwV3dDotProductMacro(&bp_40, &var_C);
    v28 = absref(v28);
    if (v28 < unk_38)
    {
        return 0;
    }
    return 1;
}

// match: ?sub_BE710@Trigger@@QAEXMMM@Z @ 0x000BE710
// sp-match: ?sub_BE710@Trigger@@QAEXMMM@Z @ 0x000911E0
// Moves it to (arg_0, arg_4, arg_8), keeping where it was in a record
// (sub_145830) for sub_BE810.
void Trigger::sub_BE710(RwReal arg_0, RwReal arg_4, RwReal arg_8)
{
    type_145830 *var_4;

    sub_BE810();
    var_4 = sub_145830();
#ifndef CODFH_SP
    // single player compiles the debug prints out (SP 0x911E0)
    sub_19A750("*Trigger (%d) being moved to:(%6.3f,%6.3f,%6.3f) from:(%6.3f,%6.3f,%6.3f)", unk_3C,
               (RwDouble)arg_0, (RwDouble)arg_4, (RwDouble)arg_8, (RwDouble)unk_90, (RwDouble)unk_94,
               (RwDouble)unk_98);
#endif
    var_4->unk_04.x = unk_90;
    var_4->unk_04.y = unk_94;
    var_4->unk_04.z = unk_98;
    var_4->unk_00 = unk_3C;
    unk_90 = arg_0;
    unk_94 = arg_4;
    unk_98 = arg_8;
    unk_24_15 = 1;
    sub_145A40(this);
}

// match: ?sub_BE810@Trigger@@QAEXXZ @ 0x000BE810
// sp-match: ?sub_BE810@Trigger@@QAEXXZ @ 0x00090BA0
// Moves it back to where its record says, if it was moved.
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void Trigger::sub_BE810()
{
    type_145830 *var_4;
    RwInt32 local_8;

    if (unk_24_15)
    {
        for (local_8 = 0; local_8 < dword_4D1D98.get_unk_0C(); local_8++)
        {
            var_4 = (type_145830 *)dword_4D1D98.sub_16C6A0(local_8);
            if (var_4 && var_4->unk_00 == unk_3C)
            {
#ifndef CODFH_SP
                // single player compiles the debug prints out (SP 0x90BA0)
                sub_19A750("-Trigger (%d) being moved to:(%6.3f,%6.3f,%6.3f) from:(%6.3f,%6.3f,%6.3f)", unk_3C,
                           (RwDouble)var_4->unk_04.x, (RwDouble)var_4->unk_04.y, (RwDouble)var_4->unk_04.z,
                           (RwDouble)unk_90, (RwDouble)unk_94, (RwDouble)unk_98);
#endif
                unk_90 = var_4->unk_04.x;
                unk_94 = var_4->unk_04.y;
                unk_98 = var_4->unk_04.z;
                RwMatrixOrthoNormalize((RwMatrix *)&unk_60_m, (RwMatrix *)&unk_60_m);
                RwMatrixOptimize((RwMatrix *)&unk_60_m, 0);
#ifndef CODFH_SP
                sub_19A750("\tOrthoNormalizing trigger(%d)", unk_3C);
                sub_19A750("\t\tLoc now:(%6.3f,%6.3f,%6.3f)", (RwDouble)unk_90, (RwDouble)unk_94, (RwDouble)unk_98);
                sub_19A750("\t\tAt now:(%6.3f,%6.3f,%6.3f)", (RwDouble)unk_60_m.at.x, (RwDouble)unk_60_m.at.y,
                           (RwDouble)unk_60_m.at.z);
                sub_19A750("\t\tUp now:(%6.3f,%6.3f,%6.3f)", (RwDouble)unk_60_m.up.x, (RwDouble)unk_60_m.up.y,
                           (RwDouble)unk_60_m.up.z);
                sub_19A750("\t\tRt now:(%6.3f,%6.3f,%6.3f)", (RwDouble)unk_60_m.right.x,
                           (RwDouble)unk_60_m.right.y, (RwDouble)unk_60_m.right.z);
#endif
                sub_145A40(this);
                sub_145870(var_4);
                break;
            }
        }
        unk_24_15 = 0;
    }
}

// match: ?sub_BEA60@Trigger@@QAEPAEXZ @ 0x000BEA60
// sp-match: ?sub_BEA60@Trigger@@QAEPAEXZ @ 0x00090C40
RwUInt8 *Trigger::sub_BEA60()
{
    if (!unk_B0)
    {
        unk_B0 = (RwUInt8 *)RWSMalloc(0x18, 0x34252); // not an address: allocation tag
    }
    return unk_B0;
}

// match: ??_ETrigger@@WBI@AEPAXI@Z @ 0x000BEAA0
// sp-match: ??_ETrigger@@WBI@AEPAXI@Z @ 0x00090DE0

// Members /OPT:ICF folded into shared trivial bodies (config/aliases.txt): defined here for
// the authentic link (PLAN M7); the placement link takes the shared bodies.

// ?vf_008@Trigger@@UAEHXZ (folded into `return 0` at 0x1E4CB0)
RwInt32 Trigger::vf_008()
{
    return 0;
}

// ?vf_014@Trigger@@UAEHXZ (folded into `return 0` at 0x1E4CB0)
RwInt32 Trigger::vf_014()
{
    return 0;
}

// ?vf_020@Trigger@@UAEPAUtype_3D3548@@XZ (folded into `return 0` at 0x1E4CB0)
type_3D3548 *Trigger::vf_020()
{
    return 0;
}

// Functions /OPT:ICF folded into another body (config/aliases.txt), defined here for the
// authentic link (PLAN M7) with that body; the placement link takes the folded one.

// ?vf_010@Trigger@@UAEXHH@Z (folded into 0x73D90)
void Trigger::vf_010(RwInt32 arg_0, RwInt32 arg_4)
{
}

// Functions /OPT:ICF folded into another body (config/aliases.txt), defined here for the
// authentic link (PLAN M7) with that body; the placement link takes the folded one.

// ?sub_15FB30@Trigger@@QAEXPAUtype_3D3548@@@Z (folded into 0x15FB30)
void Trigger::sub_15FB30(struct type_3D3548 * arg_0)
{
}
