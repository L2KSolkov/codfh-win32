// cNetPlayerTrigger: its MakeNew, constructor, destructor, respawn and
// handlers. Its original file name is not in the image, so it is named for
// its start address.

#include <string.h>

#include "rw/ostypes.h"
#include "rw/baframe.h"
#include "rws/cattributehandler.h"
#include "rws/cclassfactory.h"
#include "rws/ceventhandler.h"
#include "game/functions.h"
#include "game/gameloop.h"
#include "game/weaponbank.h"
#include "game/worldmgr.h"
#include "game/netmsg.h"
#include "game/netplayer.h"
#include "types/cNetPlayerTrigger.h"
#include "types/type_10F710.h"
#include "types/type_3D32F8.h"
#include "types/type_4B85F8.h"
#include "types/type_4C19C0.h"

// Its data definitions (PLAN M5), in the image's address order.
#ifndef CODFH_SP // MP only: unreferenced constants single player does not emit (not in default.xbe; /O2 keeps them only while they are external)
// 0x003E2F64
extern const RwReal flt_3E2F64 = 0.01f;
// 0x003E2F68
extern const RwReal flt_3E2F68 = 0.01f;
// 0x003E2F6C
extern const RwReal flt_3E2F6C = 16.666666f;
#endif
// 0x004F8130
#ifndef CODFH_PLAIN
cNetPlayerTrigger *dword_4F8130;
#endif
// End of its data definitions.


RWS_IMPLEMENT_CLASSID(cNetPlayerTrigger);
RWS_REGISTERCLASS(cNetPlayerTrigger);
// Its data (PLAN M5): literals, constants and tables where the image has them.
// match: ??_C@_0BC@HBCEIDAG@cNetPlayerTrigger?$AA@ @ 0x003E2F50
// match: ?flt_3E2F64@@3MB @ 0x003E2F64
// match: ?flt_3E2F68@@3MB @ 0x003E2F68
// match: ?flt_3E2F6C@@3MB @ 0x003E2F6C
// match: ??_7cNetPlayerTrigger@@6BCEventHandler@RWS@@@ @ 0x003E2F70
// match: ??_7cNetPlayerTrigger@@6BCAttributeHandler@RWS@@@ @ 0x003E2F78
// match: __ehhandler$?MakeNew@cNetPlayerTrigger@@SAPAVCAttributeHandler@RWS@@ABVCAttributePacket@3@@Z>1>8 @ 0x0041F184
// match: __ehhandler$?MakeNew@cNetPlayerTrigger@@SAPAVCAttributeHandler@RWS@@ABVCAttributePacket@3@@Z>1 @ 0x0041F18C
// match: .CRT$XCU+0 @ 0x004271F4
// match: ?pcNetPlayerTriggerClassID@cNetPlayerTrigger@@2PBDB @ 0x0042CB3C

// match: _$E2 @ 0x0030C2D0
// match: _$E3 @ 0x0030EAE0

// (The class factory's registration and its exit thunk.)

// match: ?MakeNew@cNetPlayerTrigger@@SAPAVCAttributeHandler@RWS@@ABVCAttributePacket@3@@Z @ 0x001BE4D0
// match: __ehhandler$?MakeNew@cNetPlayerTrigger@@SAPAVCAttributeHandler@RWS@@ABVCAttributePacket@3@@Z-0xF @ 0x00302EA0
// match: __ehhandler$?MakeNew@cNetPlayerTrigger@@SAPAVCAttributeHandler@RWS@@ABVCAttributePacket@3@@Z @ 0x00302EAF
RWS_DEFINE_MAKENEW(cNetPlayerTrigger)

// match: ??0cNetPlayerTrigger@@QAE@ABVCAttributePacket@RWS@@@Z @ 0x001BE550
cNetPlayerTrigger::cNetPlayerTrigger(const RWS::CAttributePacket &attr) : PlayerTrigger(attr)
{
    // A compiled-out check (docs/toolchain.md).
    if (!unk_47C)
    {
    }
    dword_4F8130 = this;
    unk_47C = 0;
}

// match: ??_GcNetPlayerTrigger@@UAEPAXI@Z @ 0x001BE5A0

// match: ??1cNetPlayerTrigger@@UAE@XZ @ 0x001BE5C0

// match: ?sub_1BE5E0@cNetPlayerTrigger@@QAEXXZ @ 0x001BE5E0
void cNetPlayerTrigger::sub_1BE5E0()
{
    RpClump *m_18;
    type_4C19C0 *ebp_14;
    RwUInt32 lv_10;
    type_4C19C0 *slot_C;
    RwUInt32 bp_8;
    type_10F710 *bp_4;

    bp_4 = (type_10F710 *)unk_46C.sub_D4910();
    if (bp_4)
    {
        if (bp_4->unk_2110.sub_D4910())
            sub_D5A60(bp_4->unk_2110.sub_D4910(), 2);
        sub_D5A60(bp_4, 0);
        sub_D5D20(1);
    }
    sub_1BEB00();
    bp_4 = (type_10F710 *)unk_46C.sub_D4910();
    if (bp_4)
    {
        sub_821C0();
        sub_16FD10();
        for (bp_8 = 0; bp_8 < 2; bp_8++)
        {
            slot_C = sub_119B70(unk_108[bp_8]);
            if (slot_C)
                sub_16F2C0(bp_8, slot_C->unk_24);
        }
        memset(unk_384, 0, 0x9C);
        if (unk_470[0] >= 0)
            unk_384[unk_470[0]] = 10000;
        if (unk_470[1] >= 0)
            unk_384[unk_470[1]] = 10000;
        if (unk_478 >= 0)
            unk_384[unk_478] = unk_47C;
        unk_46C.sub_D48D0(bp_4);
        sub_1745C0(bp_4, bp_4->unk_3D4);
        sub_ACF10(bp_4);
        sub_174580(bp_4, unk_C0);
        sub_ACE00();
        bp_4->sub_FF210();
        sub_ACEA0();
        for (lv_10 = 0; lv_10 < 2; lv_10++)
        {
            if (unk_470[lv_10] != unk_108[lv_10])
            {
                if (bp_4->unk_1A48[bp_4->unk_1B30[lv_10]])
                    bp_4->unk_1A48[bp_4->unk_1B30[lv_10]]->sub_117370();
                bp_4->unk_1A48[unk_108[lv_10]]->vf_00C();
                sub_16FAE0(lv_10);
                bp_4->unk_1B30[lv_10] = unk_470[lv_10];
                ebp_14 = sub_119B70(bp_4->unk_1B30[lv_10]);
                if (ebp_14)
                {
                    sub_16F2C0(lv_10, ebp_14->unk_24);
                    m_18 = bp_4->unk_1A3C.get_unk_08();
                    bp_4->unk_1A48[bp_4->unk_1B30[lv_10]]->vf_008(bp_4, m_18, bp_4->unk_1B30[lv_10]);
                }
                unk_114[unk_108[lv_10]] = 0;
                unk_108[lv_10] = unk_470[lv_10];
                unk_114[unk_108[lv_10]] = 1;
                unk_13C = unk_108[0];
            }
        }
        bp_4->unk_2134 = 2;
        bp_4->unk_1AE4 = bp_4->unk_1B30[0];
        bp_4->unk_1AE8 = 0;
        bp_4->unk_1A48[bp_4->unk_1B30[0]]->sub_1170B0(1, 1);
    }
}

// match: ?sub_1BE9B0@cNetPlayerTrigger@@QAEXXZ @ 0x001BE9B0
void cNetPlayerTrigger::sub_1BE9B0()
{
    RwMatrix *ebp_14;
    type_4C19C0 *lv_10;
    RwUInt32 slot_C;
    RwFrame *bp_8;
    type_1BABA0 *bp_4;

    bp_4 = sub_1BAA90(static_cast<type_712B0 *>(static_cast<Trigger *>(this)));
    dword_4F8060 = bp_4;
    if (bp_4)
    {
        sub_821C0();
        sub_16FD10();
        for (slot_C = 0; slot_C < 2; slot_C++)
        {
            lv_10 = sub_119B70(unk_108[slot_C]);
            if (lv_10)
                sub_16F2C0(slot_C, lv_10->unk_24);
        }
        sub_1745C0(bp_4, bp_4->unk_3D4);
        sub_ACF10(bp_4);
        sub_174580(bp_4, unk_C0);
        sub_ACE00();
        bp_4->sub_FF210();
        bp_8 = bp_4->get_unk_340();
        if (bp_8)
        {
            if (ebp_14 = RwFrameGetMatrix(bp_8))
            {
                *ebp_14 = unk_60_m;
                RwFrameUpdateObjects(bp_8);
            }
        }
    }
}

// match: ?sub_1BEAC0@cNetPlayerTrigger@@QAEXPBURwMatrixTag@@@Z @ 0x001BEAC0
void cNetPlayerTrigger::sub_1BEAC0(const RwMatrixTag *arg_0)
{
    unk_60_m = *arg_0;
    unk_94 += unk_144;
}

// match: ?sub_1BEB00@cNetPlayerTrigger@@QAEXXZ @ 0x001BEB00
void cNetPlayerTrigger::sub_1BEB00()
{
    type_17DBD0_player *var_4 = sub_1B7B20(static_cast<type_712B0 *>(static_cast<Trigger *>(this)));

    if (var_4)
        unk_46C.sub_D48D0(var_4);
    unk_4F7EB8.sub_1AF0F0(var_4);
}

// match: ?HandleEvents@cNetPlayerTrigger@@UAEXAAVCMsg@RWS@@@Z @ 0x001BEB50
void cNetPlayerTrigger::HandleEvents(RWS::CMsg &pMsg)
{
    if (pMsg.Id.p_msgrec == dword_4B67B0.p_msgrec)
    {
        sub_ACE00();
    }
    else if (pMsg.Id.p_msgrec == dword_4B67C0.p_msgrec)
    {
    }
    else
    {
        PlayerTrigger::HandleEvents(pMsg);
    }
}

// match: ??_EcNetPlayerTrigger@@WBI@AEPAXI@Z @ 0x001BEBA0
