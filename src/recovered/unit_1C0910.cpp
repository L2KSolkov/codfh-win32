// cNetSpawnPoint, a RenderWare Studio behaviour (types/cNetSpawnPoint.h):
// MakeNew, its constructor, destructor, attributes and event handler; and
// the spawn points' lists (type_1C0F60, type_4FBC50; game/netmsg.h) with
// their picks. Its original file name is not in the image, so it is named
// for its start address.

#include "rw/ostypes.h"
#include "rw/rprandom.h"
#include "rws/cattributehandler.h"
#include "rws/cclassfactory.h"
#include "rws/ceventhandler.h"
#include "types/cNetSpawnPoint.h"
#include "game/netmsg.h"
#include "game/data.h"
#include "game/mpgame.h"
#include "game/fileio.h"

// Its data definitions (PLAN M5), in the image's address order.
// 0x003E3308
extern const RwReal flt_3E3308 = 0.01f;
// 0x003E330C
extern const RwReal flt_3E330C = 16.666666f;
// 0x003E3310
extern const RwReal flt_3E3310 = 0.01f;
// 0x003E3314
extern const RwReal flt_3E3314 = 120.0f;
// 0x003E3318
extern const RwReal flt_3E3318 = 3000.0f;
// 0x003E331C
extern const RwReal flt_3E331C = 3500.0f;
// 0x003E3320
extern const RwReal flt_3E3320 = 4000.0f;
// 0x003E3324
extern const RwReal flt_3E3324 = 4500.0f;
// 0x003E3328
extern const RwReal flt_3E3328 = 3000.0f;
// 0x003E332C
extern const RwReal flt_3E332C = 500.0f;
// End of its data definitions.


// Globals with constructors defined here (their initializers and exit
// functions at the end of .text).
type_4FBC50 unk_4FBC50;

// The picks' distances (constants of this unit's, read from memory): the
// room kept from every player (120), the distances by the count of players
// (rule 3: 3000, 3500, 4000, 4500), and rule 4's limit (3000) and aim (500).
extern const RwReal flt_3E3314;
extern const RwReal flt_3E3318;
extern const RwReal flt_3E331C;
extern const RwReal flt_3E3320;
extern const RwReal flt_3E3324;
extern const RwReal flt_3E3328;
extern const RwReal flt_3E332C;

RWS_IMPLEMENT_CLASSID(cNetSpawnPoint);
RWS_REGISTERCLASS(cNetSpawnPoint);
// Its data (PLAN M5): literals, constants and tables where the image has them.
// match: ??_C@_0P@LMBEKMGE@cNetSpawnPoint?$AA@ @ 0x003E32F8
// match: ?flt_3E3308@@3MB @ 0x003E3308
// match: ?flt_3E330C@@3MB @ 0x003E330C
// match: ?flt_3E3310@@3MB @ 0x003E3310
// match: ?flt_3E3314@@3MB @ 0x003E3314
// match: ?flt_3E3318@@3MB @ 0x003E3318
// match: ?flt_3E331C@@3MB @ 0x003E331C
// match: ?flt_3E3320@@3MB @ 0x003E3320
// match: ?flt_3E3324@@3MB @ 0x003E3324
// match: ?flt_3E3328@@3MB @ 0x003E3328
// match: ?flt_3E332C@@3MB @ 0x003E332C
// match: ??_7cNetSpawnPoint@@6BCEventHandler@RWS@@@ @ 0x003E3330
// match: ??_7cNetSpawnPoint@@6BCAttributeHandler@RWS@@@ @ 0x003E3338
// match: ??_C@_0CC@KAMLJMB@FAILED?5TO?5FIND?5VALID?5SPAWN?5POINT@ @ 0x003E3368
// match: ??_C@_0CN@KIELEJGD@Unable?5to?5find?5a?5spawn?5point?5at?5@ @ 0x003E338C
// match: ??_C@_0BD@BHKAINPF@Unknown?5game?5type?6?$AA@ @ 0x003E33BC
// match: __ehhandler$?MakeNew@cNetSpawnPoint@@SAPAVCAttributeHandler@RWS@@ABVCAttributePacket@3@@Z>1>8 @ 0x0041F238
// match: __ehhandler$?MakeNew@cNetSpawnPoint@@SAPAVCAttributeHandler@RWS@@ABVCAttributePacket@3@@Z>1 @ 0x0041F240
// match: __ehhandler$??1cNetSpawnPoint@@UAE@XZ>1>8 @ 0x0041F25C
// match: __ehhandler$??1cNetSpawnPoint@@UAE@XZ>1 @ 0x0041F26C
// match: __ehhandler$??0cNetSpawnPoint@@QAE@ABVCAttributePacket@RWS@@@Z>1>8 @ 0x0041F288
// match: __ehhandler$??0cNetSpawnPoint@@QAE@ABVCAttributePacket@RWS@@@Z>1 @ 0x0041F298
// match: .CRT$XCU+0 @ 0x004271FC
// match: .CRT$XCU+4 @ 0x00427200
// match: ?pcNetSpawnPointClassID@cNetSpawnPoint@@2PBDB @ 0x0042CB9C

// match: _$E2 @ 0x0030C330
// match: _$E4 @ 0x0030C340
// match: _$E5 @ 0x0030EB00

// (The class factory's registration and its exit thunk.)

// match: ?MakeNew@cNetSpawnPoint@@SAPAVCAttributeHandler@RWS@@ABVCAttributePacket@3@@Z @ 0x001C0910
// match: __ehhandler$?MakeNew@cNetSpawnPoint@@SAPAVCAttributeHandler@RWS@@ABVCAttributePacket@3@@Z-0xF @ 0x00302F40
// match: __ehhandler$?MakeNew@cNetSpawnPoint@@SAPAVCAttributeHandler@RWS@@ABVCAttributePacket@3@@Z @ 0x00302F4F
RWS_DEFINE_MAKENEW(cNetSpawnPoint)

// Its handler serves the destructor too (folded by /OPT:ICF).
// match: ??0cNetSpawnPoint@@QAE@ABVCAttributePacket@RWS@@@Z @ 0x001C0990
// match: __ehhandler$??0cNetSpawnPoint@@QAE@ABVCAttributePacket@RWS@@@Z-0x16 @ 0x00302F60
// match: __ehhandler$??0cNetSpawnPoint@@QAE@ABVCAttributePacket@RWS@@@Z @ 0x00302F76
cNetSpawnPoint::cNetSpawnPoint(const RWS::CAttributePacket &attr) : Trigger(attr)
{
    unk_C4 = 1;
    unk_C8 = 1;
    unk_CC = 1;
    unk_D0 = 0;
    unk_D4 = -1;
    unk_E0 = 0;
    unk_E4 = 0;
    unk_E8 = 0;
    unk_EC = 0;
    RWS::CEventHandler::RegisterMsg(unk_D8, "kujuUpdateTriggerObjectVisibility", "sNetTriggerVisibility *");
    LinkMsg(unk_D8, "sNetTriggerVisibility *", 0x8000);
    LinkMsg(dword_4B8750, 0, 0x8000);
}

// match: ?vf_008@cNetSpawnPoint@@UAEHXZ @ 0x001C0AD0

// match: ??_GcNetSpawnPoint@@UAEPAXI@Z @ 0x001C0AE0

// match: ??1cNetSpawnPoint@@UAE@XZ @ 0x001C0B00
cNetSpawnPoint::~cNetSpawnPoint()
{
    UnLinkMsg(unk_D8);
    RWS::CEventHandler::UnRegisterMsg(unk_D8);
    UnLinkMsg(dword_4B8750);
    UnLinkMsg(RWS::iMsgRunningTick);
}

// match: ?HandleAttributes@cNetSpawnPoint@@UAEXABVCAttributePacket@RWS@@@Z @ 0x001C0BB0
void cNetSpawnPoint::HandleAttributes(const RWS::CAttributePacket &attr)
{
    Trigger::HandleAttributes(attr);
    RWS::CAttributeCommandIterator attrIt(attr, RWS_CLASSID_OF(cNetSpawnPoint));
    while (!attrIt.IsFinished())
    {
        switch (attrIt->GetCommandId())
        {
        case 0:
            sub_1C0D80(attrIt);
            sub_15FB30(&unk_4FD6D4);
            break;
        case 1:
            sub_1C0DB0(attrIt);
            sub_15FB30(&unk_4FD6D4);
            break;
        case 2:
            sub_1C0DE0(attrIt);
            sub_15FB30(&unk_4FD6D4);
            break;
        case 3:
            sub_1C0E10(attrIt);
            sub_15FB30(&unk_4FD6D4);
            break;
        case 4:
            sub_1C0E60(attrIt);
            sub_15FB30(&unk_4FD6D4);
            break;
        case 5:
            unk_E0 = attrIt->GetAs_RwUInt32();
            break;
        case 6:
            unk_E4 = attrIt->GetAs_RwUInt32();
            break;
        case 7:
            unk_E8 = attrIt->GetAs_RwUInt32();
            break;
        case 8:
            unk_EC = attrIt->GetAs_RwUInt32();
            break;
        default:
            if (CODFH_DEBUG_LOGS)
                sub_1C8A30("Unknown renderware studio attribute\n");
        }
        ++attrIt;
    }
}

// match: ?sub_1C0D80@cNetSpawnPoint@@QAEXAAVCAttributeCommandIterator@RWS@@@Z @ 0x001C0D80
void cNetSpawnPoint::sub_1C0D80(RWS::CAttributeCommandIterator &arg_0)
{
    arg_0->GetCommandData(unk_C4);
}

// match: ?sub_1C0DB0@cNetSpawnPoint@@QAEXAAVCAttributeCommandIterator@RWS@@@Z @ 0x001C0DB0
void cNetSpawnPoint::sub_1C0DB0(RWS::CAttributeCommandIterator &arg_0)
{
    arg_0->GetCommandData(unk_C8);
}

// match: ?sub_1C0DE0@cNetSpawnPoint@@QAEXAAVCAttributeCommandIterator@RWS@@@Z @ 0x001C0DE0
void cNetSpawnPoint::sub_1C0DE0(RWS::CAttributeCommandIterator &arg_0)
{
    arg_0->GetCommandData(unk_CC);
}

// match: ?sub_1C0E10@cNetSpawnPoint@@QAEXAAVCAttributeCommandIterator@RWS@@@Z @ 0x001C0E10
void cNetSpawnPoint::sub_1C0E10(RWS::CAttributeCommandIterator &arg_0)
{
    RwInt32 var_4 = arg_0->GetAs_RwInt32();

    if (var_4 == -1)
        unk_D0 = 1;
    else
        unk_D0 = 0;
}

// match: ?sub_1C0E60@cNetSpawnPoint@@QAEXAAVCAttributeCommandIterator@RWS@@@Z @ 0x001C0E60
void cNetSpawnPoint::sub_1C0E60(RWS::CAttributeCommandIterator &arg_0)
{
    unk_D4 = arg_0->GetAs_RwInt32();
}

// At the game's start it joins the spawn points' lists and stops
// listening; its visibility message passes its data on.
// match: ?HandleEvents@cNetSpawnPoint@@UAEXAAVCMsg@RWS@@@Z @ 0x001C0E90
void cNetSpawnPoint::HandleEvents(RWS::CMsg &pMsg)
{
    // The locals' names state their slots (docs/toolchain.md).
    void *bp_4;

    if (pMsg.Id.p_msgrec == RWS::iMsgRunningTick.p_msgrec)
        return;
    if (pMsg.Id.p_msgrec == dword_4B8750.p_msgrec)
    {
        unk_4FBC50.sub_1C1CE0(this);
        UnLinkMsg(dword_4B8750);
    }
    else if (pMsg.Id.p_msgrec == unk_D8)
    {
        if (pMsg.pData)
        {
            bp_4 = pMsg.pData;
            sub_15FB30(bp_4);
        }
    }
}

// match: ?sub_1C0F20@cNetSpawnPoint@@QAEXPAUtype_1F8560_v@@@Z @ 0x001C0F20
void cNetSpawnPoint::sub_1C0F20(type_1F8560_v *arg_0)
{
    RwMatrixTag *var_4 = &unk_60_m;

    arg_0->unk_00 = var_4->pos.x;
    arg_0->unk_04 = var_4->pos.y;
    arg_0->unk_08 = var_4->pos.z;
}

// match: ??0type_1C0F60@@QAE@XZ @ 0x001C0F60
type_1C0F60::type_1C0F60()
{
    unk_00 = 1;
    unk_04 = -1;
    unk_08 = 0;
    unk_264 = -1;
}

// match: ?sub_1C0FA0@type_1C0F60@@QAEXXZ @ 0x001C0FA0
void type_1C0F60::sub_1C0FA0()
{
    unk_00 = 1;
    unk_04 = -1;
    unk_08 = 0;
    unk_264 = -1;
}

// match: ?sub_1C0FE0@type_1C0F60@@QAEXPAVcNetSpawnPoint@@@Z @ 0x001C0FE0
void type_1C0F60::sub_1C0FE0(cNetSpawnPoint *arg_0)
{
    unk_0C[unk_08] = arg_0;
    unk_08++;
}

// match: ?sub_1C1010@type_1C0F60@@QAEHIPAUtype_4FBC50_player@@HHH@Z @ 0x001C1010
RwInt32 type_1C0F60::sub_1C1010(RwUInt32 arg_0, type_4FBC50_player *arg_4, RwInt32 arg_8, RwInt32 arg_C,
                                RwInt32 arg_10)
{
    RwInt32 var_4;

    // Compiled-out checks.
    if (!unk_08)
    {
    }
    if (!unk_08)
    {
    }
    // (the image's jump table: case 6's block first, then 0 to 5)
    switch (arg_C)
    {
    case 6:
        var_4 = sub_1C1660();
        break;
    case 0:
        var_4 = sub_1C16B0(arg_0, arg_4, arg_8);
        break;
    case 1:
        var_4 = sub_1C1820(arg_0, arg_4, arg_8);
        break;
    case 2:
        var_4 = sub_1C1140(arg_0, arg_4, arg_8);
        break;
    case 3:
        var_4 = sub_1C13C0(arg_0, arg_4, arg_10, arg_8);
        break;
    case 4:
        var_4 = sub_1C1560(arg_0, arg_4, arg_10, arg_8);
        break;
    case 5:
        var_4 = sub_1C1630(arg_0, arg_4, arg_10, arg_8);
        break;
    default:
        var_4 = sub_1C16B0(arg_0, arg_4, arg_8);
    }
    return unk_0C[var_4]->get_unk_C0();
}

// match: ?sub_1C1140@type_1C0F60@@QAEHIPAUtype_4FBC50_player@@H@Z @ 0x001C1140
RwInt32 type_1C0F60::sub_1C1140(RwUInt32 arg_0, type_4FBC50_player *arg_4, RwInt32 arg_8)
{
    RwInt32 var_4 = -1;

    switch (arg_0)
    {
    case 0:
        var_4 = sub_1C13A0();
        break;
    case 1:
        var_4 = sub_1C1210(arg_0, arg_4, arg_8, flt_3E3318);
        break;
    case 2:
        var_4 = sub_1C1210(arg_0, arg_4, arg_8, flt_3E331C);
        break;
    case 3:
        var_4 = sub_1C1210(arg_0, arg_4, arg_8, flt_3E3320);
        break;
    default:
        var_4 = sub_1C1210(arg_0, arg_4, arg_8, flt_3E3324);
    }
    return var_4;
}

// match: ?sub_1C1210@type_1C0F60@@QAEHIPAUtype_4FBC50_player@@HM@Z @ 0x001C1210
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
RwInt32 type_1C0F60::sub_1C1210(RwUInt32 arg_0, type_4FBC50_player *arg_4, RwInt32 arg_8, RwReal arg_C)
{
    RwInt32 frm_8 = -1;
    RwInt32 l4 = -1;
    type_1F8560_v bp_18;
    RwReal var_1C = 1e12f;
    RwReal bp_28 = -1e12f;
    RwReal l24;
    RwUInt32 l20;
    RwReal qC;

    if (!arg_0)
        return sub_1C13A0();
    for (l20 = 0; l20 < (RwUInt32)unk_08; l20++)
    {
        if (l20 != arg_8)
        {
            unk_0C[l20]->sub_1C0F20(&bp_18);
            sub_1C1A40(arg_0, arg_4, &bp_18, 8, &qC);
            l24 = qC - arg_C;
            if (l24 < 0.0f && l24 > bp_28)
            {
                bp_28 = l24;
                l4 = l20;
            }
            else if (l24 >= 0.0f && l24 < var_1C)
            {
                var_1C = l24;
                frm_8 = l20;
            }
        }
    }
    if (frm_8 != -1)
        return frm_8;
    if (l4 != -1)
        return l4;
    return sub_1C16B0(arg_0, arg_4, arg_8);
}

// match: ?sub_1C1350@type_1C0F60@@QAEHIPAUtype_4FBC50_player@@H@Z @ 0x001C1350
RwInt32 type_1C0F60::sub_1C1350(RwUInt32 arg_0, type_4FBC50_player *arg_4, RwInt32 arg_8)
{
    RwUInt32 var_4;

    // A compiled-out check.
    if (!unk_08)
    {
    }
    for (var_4 = 0; var_4 < arg_0; var_4++)
    {
        if (arg_4[var_4].unk_0C == arg_8)
            return 1;
    }
    return 0;
}

// match: ?sub_1C13A0@type_1C0F60@@QAEHXZ @ 0x001C13A0
RwInt32 type_1C0F60::sub_1C13A0()
{
    // From 0 to the last point, as written (the divisor is computed).
    return RpRandom() % (unk_08 - 1 + 1);
}

// match: ?sub_1C13C0@type_1C0F60@@QAEHIPAUtype_4FBC50_player@@HH@Z @ 0x001C13C0
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
RwInt32 type_1C0F60::sub_1C13C0(RwUInt32 arg_0, type_4FBC50_player *arg_4, RwInt32 arg_8, RwInt32 arg_C)
{
    RwInt32 frm_8 = -1;
    RwInt32 l4 = -1;
    type_1F8560_v bp_18;
    RwReal var20 = 1e12f;
    RwReal var_30 = -1e12f;
    RwReal qC = flt_3E3314;
    RwReal var_2C;
    RwUInt32 loc28;
    RwReal slot_24;
    RwReal t1C;

    if (!arg_0)
        return sub_1C13A0();
    if (!sub_1C1350(arg_0, arg_4, arg_8))
        return sub_1C1140(arg_0, arg_4, arg_C);
    for (loc28 = 0; loc28 < (RwUInt32)unk_08; loc28++)
    {
        if (loc28 != arg_C)
        {
            unk_0C[loc28]->sub_1C0F20(&bp_18);
            t1C = sub_1C1A40(arg_0, arg_4, &bp_18, arg_8, &slot_24);
            if (slot_24 > qC)
            {
                if (slot_24 < flt_3E3328)
                    qC = slot_24;
                var_2C = t1C - flt_3E332C;
                if (var_2C < 0.0f && var_2C > var_30)
                {
                    var_30 = var_2C;
                    l4 = loc28;
                }
                else if (var_2C >= 0.0f && var_2C < var20)
                {
                    var20 = var_2C;
                    frm_8 = loc28;
                }
            }
        }
    }
    if (frm_8 != -1)
        return frm_8;
    if (l4 != -1)
        return l4;
    return sub_1C16B0(arg_0, arg_4, arg_C);
}

// match: ?sub_1C1560@type_1C0F60@@QAEHIPAUtype_4FBC50_player@@HH@Z @ 0x001C1560
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
RwInt32 type_1C0F60::sub_1C1560(RwUInt32 arg_0, type_4FBC50_player *arg_4, RwInt32 arg_8, RwInt32 arg_C)
{
    RwInt32 var_1C;
    RwUInt32 var_18;
    RwInt32 var_14;
    type_1F8560_v ebp_10;
    RwReal l4;

    var_14 = sub_1C13A0();
    var_1C = var_14;
    if (!arg_0)
        return var_14;
    for (var_18 = 0; var_18 < (RwUInt32)unk_08; var_18++)
    {
        unk_0C[var_14]->sub_1C0F20(&ebp_10);
        sub_1C1A40(arg_0, arg_4, &ebp_10, 8, &l4);
        if (l4 > flt_3E3314 && var_14 != arg_C)
            return var_14;
        var_14++;
        if (var_14 >= unk_08)
            var_14 = 0;
    }
    return var_1C;
}

// match: ?sub_1C1630@type_1C0F60@@QAEHIPAUtype_4FBC50_player@@HH@Z @ 0x001C1630
RwInt32 type_1C0F60::sub_1C1630(RwUInt32 arg_0, type_4FBC50_player *arg_4, RwInt32 arg_8, RwInt32 arg_C)
{
    return sub_1C1560(arg_0, arg_4, arg_8, arg_C);
}

// match: ?sub_1C1660@type_1C0F60@@QAEHXZ @ 0x001C1660
RwInt32 type_1C0F60::sub_1C1660()
{
    unk_264++;
    if (unk_264 >= unk_08)
        unk_264 = 0;
    return unk_264;
}

// match: ?sub_1C16B0@type_1C0F60@@QAEHIPAUtype_4FBC50_player@@H@Z @ 0x001C16B0
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
// The point (not arg_8) farthest from the nearest of the arg_0 players
// arg_4; the first one when there is none.
RwInt32 type_1C0F60::sub_1C16B0(RwUInt32 arg_0, type_4FBC50_player *arg_4, RwInt32 arg_8)
{
    RwUInt32 lv_30;
    RwUInt32 fp_2C;
    RwInt32 q28 = -1;
    RwReal frm_24;
    RwReal loc20 = 0;
    RwReal p1C;
    type_1F8560_v var_C;
    type_1F8560_v lv_18;

    // Compiled-out checks.
    if (!unk_08)
    {
    }
    if (!unk_08)
    {
    }
    for (fp_2C = 0; fp_2C < (RwUInt32)unk_08; fp_2C++)
    {
        if (arg_8 != fp_2C)
        {
            frm_24 = 1e10f;
            for (lv_30 = 0; lv_30 < arg_0; lv_30++)
            {
                unk_0C[fp_2C]->sub_1C0F20(&lv_18);
                var_C = arg_4[lv_30].unk_00 - lv_18;
                p1C = var_C.len();
                if (p1C < frm_24)
                {
                    if (!unk_08)
                    {
                    }
                    frm_24 = p1C;
                }
            }
            if (frm_24 > loc20)
            {
                loc20 = frm_24;
                q28 = fp_2C;
            }
        }
    }
    if (q28 == -1)
    {
        q28 = 0;
        if (CODFH_DEBUG_LOGS)
        {
            sub_1C8A30("FAILED TO FIND VALID SPAWN POINT\n");
        }
    }
    return q28;
}

// match: ?sub_1C1820@type_1C0F60@@QAEHIPAUtype_4FBC50_player@@H@Z @ 0x001C1820
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
// The point nearest the players' centre that is far enough from them all
// (sub_1C1A40), else the farthest; -1 when there is none.
RwInt32 type_1C0F60::sub_1C1820(RwUInt32 arg_0, type_4FBC50_player *arg_4, RwInt32 arg_8)
{
    RwInt32 l34 = 0x7FFFFFFF;
    RwInt32 bp_4 = 0x7FFFFFFF;
    type_1F8560_v x1C;
    type_1F8560_v o30;
    type_1F8560_v m_48;
    RwReal ebp_24 = 1e10f;
    RwReal x8 = flt_3E3314;
    RwUInt32 v4C;
    RwUInt32 p3C;
    RwReal w20;
    RwReal fp_38;
    RwReal r10;
    RwReal locC;

    if (!arg_0)
        return 0;
    // Compiled-out checks (docs/toolchain.md).
    if (!unk_08)
    {
    }
    if (!unk_08)
    {
    }
    for (v4C = 0; v4C < arg_0; v4C++)
        o30 += arg_4[v4C].unk_00;
    o30 /= (RwReal)arg_0;
    for (p3C = 0; p3C < (RwUInt32)unk_08; p3C++)
    {
        unk_0C[p3C]->sub_1C0F20(&x1C);
        m_48 = x1C - o30;
        w20 = m_48.len();
        if (w20 < ebp_24)
        {
            // A compiled-out check (docs/toolchain.md).
            if (!unk_08)
            {
            }
            r10 = sub_1C1A40(arg_0, arg_4, &x1C, 8, &fp_38);
            locC = flt_3E3314 - r10;
            if (locC < 0.0f)
            {
                ebp_24 = w20;
                l34 = p3C;
            }
            else if (locC < x8)
            {
                x8 = locC;
                bp_4 = p3C;
            }
        }
    }
    if (l34 != 0x7FFFFFFF)
        return l34;
    if (bp_4 != 0x7FFFFFFF)
        return bp_4;
    if (CODFH_DEBUG_LOGS)
        sub_1C8A30("Unable to find a spawn point at min distance");
    return -1;
}

// match: ?sub_1C1A40@type_1C0F60@@QAEMIPAUtype_4FBC50_player@@PAUtype_1F8560_v@@HPAM@Z @ 0x001C1A40
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
// The players' nearest distance to arg_8 (in *arg_10) and the nearest of
// team arg_C's (8: any team).
RwReal type_1C0F60::sub_1C1A40(RwUInt32 arg_0, type_4FBC50_player *arg_4, type_1F8560_v *arg_8, RwInt32 arg_C,
                               RwReal *arg_10)
{
    RwUInt32 m_18;
    RwReal ebp_14;
    type_1F8560_v lv_10;
    RwReal bp_4;

    ebp_14 = 1e10f;
    // A compiled-out check (docs/toolchain.md).
    if (!unk_08)
    {
    }
    *arg_10 = 1e10f;
    for (m_18 = 0; m_18 < arg_0; m_18++)
    {
        lv_10 = arg_4[m_18].unk_00 - *arg_8;
        bp_4 = lv_10.len();
        // A compiled-out check (docs/toolchain.md).
        if (!unk_08)
        {
        }
        if (arg_C == 8 || arg_C != arg_4[m_18].unk_0C)
        {
            if (bp_4 < *arg_10)
                *arg_10 = bp_4;
        }
        else if (bp_4 < ebp_14)
            ebp_14 = bp_4;
    }
    // Compared as a word: 1e10 is the untouched value.
    if (ebp_14 == 1e10f)
        ebp_14 = *arg_10;
    return ebp_14;
}

// match: ?sub_1C1B60@type_1C0F60@@QAEPAIH@Z @ 0x001C1B60
RwUInt32 *type_1C0F60::sub_1C1B60(RwInt32 arg_0)
{
    // A compiled-out check.
    if (!unk_08)
    {
    }
    return &unk_0C[arg_0]->unk_E0;
}

// match: ?sub_1C1B80@type_1C0F60@@QAEPAURwMatrixTag@@H@Z @ 0x001C1B80
RwMatrixTag *type_1C0F60::sub_1C1B80(RwInt32 arg_0)
{
    // A compiled-out check.
    if (!unk_08)
    {
    }
    return &unk_0C[arg_0]->unk_60_m;
}

// match: ??0type_4FBC50@@QAE@XZ @ 0x001C1BA0
type_4FBC50::type_4FBC50()
{
    unk_268 = 0;
    unk_1A7C = -1;
}

// match: ?sub_1C1C10@type_4FBC50@@QAEXXZ @ 0x001C1C10
void type_4FBC50::sub_1C1C10()
{
    RwUInt32 var_4;

    unk_00.sub_1C0FA0();
    for (var_4 = 0; var_4 < unk_268; var_4++)
        unk_26C[var_4].sub_1C0FA0();
    unk_268 = 0;
    unk_1A7C = -1;
}

// match: ?sub_1C1C80@type_4FBC50@@QAEHHIPAUtype_4FBC50_player@@HH@Z @ 0x001C1C80
RwInt32 type_4FBC50::sub_1C1C80(RwInt32 arg_0, RwUInt32 arg_4, type_4FBC50_player *arg_8, RwInt32 arg_C,
                                RwInt32 arg_10)
{
    RwInt32 var_4 = unk_26C[arg_0].sub_1C1010(arg_4, arg_8, unk_1A7C, arg_C, arg_10);

    unk_1A7C = var_4;
    return var_4;
}

// match: ?sub_1C1CE0@type_4FBC50@@QAEXPAVcNetSpawnPoint@@@Z @ 0x001C1CE0
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void type_4FBC50::sub_1C1CE0(cNetSpawnPoint *arg_0)
{
    RwInt32 l4 = 0;
    RwInt32 var_10;
    RwInt32 local_C;
    RwInt32 var_8;

    if ((arg_0->unk_C4 & dword_4FB9E0.get_unk_08()) && (arg_0->unk_C8 & unk_4F61F8.unk_108))
    {
        switch (dword_4FB9E0.get_unk_08_00())
        {
        case 1:
            unk_26C[0].sub_1C0FE0(arg_0);
            unk_268 = 1;
            l4 = 1;
            break;
        case 2:
        case 4:
            if (arg_0->unk_CC & get_mask(2))
            {
                unk_26C[0].sub_1C0FE0(arg_0);
                unk_26C[0].unk_00 = 2;
                l4 = 1;
            }
            if (arg_0->unk_CC & get_mask(4))
            {
                unk_26C[1].sub_1C0FE0(arg_0);
                unk_26C[1].unk_00 = 4;
                l4 = 1;
            }
            unk_268 = 2;
            break;
        case 8:
        case 16:
            if (arg_0->get_unk_D0())
                var_8 = arg_0->unk_D4;
            else
                var_8 = -1;
            if (arg_0->unk_CC & get_mask(2))
            {
                var_10 = sub_1C2050(2, var_8);
                if (var_10 != -1)
                {
                    unk_26C[var_10].sub_1C0FE0(arg_0);
                    l4 = 1;
                }
                else
                {
                    unk_26C[unk_268].sub_1C0FE0(arg_0);
                    unk_26C[unk_268].set_unk_00(2);
                    unk_26C[unk_268].set_unk_04(var_8);
                    unk_268++;
                    l4 = 1;
                }
            }
            if (arg_0->unk_CC & get_mask(4))
            {
                var_10 = sub_1C2050(4, var_8);
                if (var_10 != -1)
                {
                    unk_26C[var_10].sub_1C0FE0(arg_0);
                    l4 = 1;
                }
                else
                {
                    unk_26C[unk_268].sub_1C0FE0(arg_0);
                    unk_26C[unk_268].set_unk_00(4);
                    unk_26C[unk_268].set_unk_04(var_8);
                    unk_268++;
                    l4 = 1;
                }
            }
            break;
        default:
            if (CODFH_DEBUG_LOGS)
                sub_1C8A30("Unknown game type\n");
        }
        if (l4)
        {
            local_C = unk_00.unk_08;
            arg_0->unk_C0 = local_C;
            unk_00.sub_1C0FE0(arg_0);
        }
    }
}

// match: ?sub_1C2050@type_4FBC50@@QAEHHH@Z @ 0x001C2050
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
RwInt32 type_4FBC50::sub_1C2050(RwInt32 arg_0, RwInt32 arg_4)
{
    RwUInt32 var_8;
    type_1C0F60 *l4;

    for (var_8 = 0; var_8 < unk_268; var_8++)
    {
        l4 = &unk_26C[var_8];
        if (l4->get_unk_00() == arg_0 && (arg_4 == -1 || l4->get_unk_04() == arg_4))
            return var_8;
    }
    return -1;
}

// match: ?sub_1C20D0@type_4FBC50@@QAEPAIH@Z @ 0x001C20D0
RwUInt32 *type_4FBC50::sub_1C20D0(RwInt32 arg_0)
{
    return unk_00.sub_1C1B60(arg_0);
}

// match: ?sub_1C20F0@type_4FBC50@@QAEPAURwMatrixTag@@H@Z @ 0x001C20F0
RwMatrixTag *type_4FBC50::sub_1C20F0(RwInt32 arg_0)
{
    return unk_00.sub_1C1B80(arg_0);
}

// The CEventHandler part's deleting destructor thunk (sub ecx, 0x18).
// match: ??_EcNetSpawnPoint@@WBI@AEPAXI@Z @ 0x001C2110

// Members /OPT:ICF folded into shared trivial bodies (config/aliases.txt): defined here for
// the authentic link (PLAN M7); the placement link takes the shared bodies.

// ?sub_15FB30@cNetSpawnPoint@@QAEXPAX@Z (folded into the empty body at 0x15FB30)
void cNetSpawnPoint::sub_15FB30(void *arg_0)
{
}
