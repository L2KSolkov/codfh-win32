// CAnimPackSelector, the RenderWare Studio behaviour that loads animation
// packs: MakeNew, its constructor, destructor and handlers. Split from
// unit_0A02D0.cpp at 0x0A0A50, where the image ends that object (its deferred
// functions come before the next out-of-line one; PLAN M7).

#include "rw/ostypes.h"
#include "rws/cattributehandler.h"
#include "rws/cclassfactory.h"
#include "types/CAnimBankInfo.h"
#include "types/CAnimPackSelector.h"
#include "types/animbank.h"
#include "types/musicplayer.h"
#include "types/soundbank.h"
#include "game/data.h"
#include "game/functions.h"
#include "types/type_3DF8D8.h"
#ifdef CODFH_WIN32
// (port/src/cli.cpp: a -leveldir test level's extra animation packs)
extern "C" RwInt32 port_anim_packs(const RwChar *const **pppNames);
#endif

// match: __ehhandler$?MakeNew@CAnimPackSelector@@SAPAVCAttributeHandler@RWS@@ABVCAttributePacket@3@@Z>1>8 @ 0x0041B9DC
// match: __ehhandler$?MakeNew@CAnimPackSelector@@SAPAVCAttributeHandler@RWS@@ABVCAttributePacket@3@@Z>1 @ 0x0041B9E4
// match: __ehhandler$??0CAnimPackSelector@@QAE@ABVCAttributePacket@RWS@@@Z>1>8 @ 0x0041BA00
// match: __ehhandler$??0CAnimPackSelector@@QAE@ABVCAttributePacket@RWS@@@Z>1 @ 0x0041BA10
// match: __ehhandler$??1CAnimPackSelector@@UAE@XZ>1>8 @ 0x0041BA2C
// match: __ehhandler$??1CAnimPackSelector@@UAE@XZ>1 @ 0x0041BA3C
// match: ??_C@_0BC@PNFNDLFG@CAnimPackSelector?$AA@ @ 0x003D59A4
// match: ?flt_3D59B8@@3MB @ 0x003D59B8
// match: ??_7CAnimPackSelector@@6BCEventHandler@RWS@@@ @ 0x003D59BC
// match: ??_7CAnimPackSelector@@6BCAttributeHandler@RWS@@@ @ 0x003D59C4
// match: ??_C@_0BI@PFNKGOIK@AnimPack?5Loading?5end?4?4?4?$AA@ @ 0x003D59CC
// match: ??_C@_0EE@MAKIAABF@Animation?5group?5god?5ID?3?5?$CFx?0?$CFx?5Na@ @ 0x003D59E8
// match: ??_C@_0DO@OIALOCDO@Loading?5animation?5group?5god?5ID?3?5@ @ 0x003D5A2C
// match: ??_C@_0BK@BAPPKCBN@AnimPack?5Loading?5begin?4?4?4?$AA@ @ 0x003D5A6C
// match: ?pCAnimPackSelectorClassID@CAnimPackSelector@@2PBDB @ 0x00429130
// match: .CRT$XCU+0 @ 0x00426EEC

// match: _$E2 @ 0x0030A540
// match: _$E3 @ 0x0030DF90

// Its data definitions (PLAN M5), in the image's address order.
// 0x003D59B8
extern const RwReal flt_3D59B8 = 16.666666f;
// 0x004B67CC
CAnimPackSelector *dword_4B67CC;
// End of its data definitions.
// (The class factory's registration and its exit thunk.)
RWS_IMPLEMENT_CLASSID(CAnimPackSelector);
RWS_REGISTERCLASS(CAnimPackSelector);


// match: ?MakeNew@CAnimPackSelector@@SAPAVCAttributeHandler@RWS@@ABVCAttributePacket@3@@Z @ 0x000A0A50
// match: __ehhandler$?MakeNew@CAnimPackSelector@@SAPAVCAttributeHandler@RWS@@ABVCAttributePacket@3@@Z-0xF @ 0x002FFCB0
// match: __ehhandler$?MakeNew@CAnimPackSelector@@SAPAVCAttributeHandler@RWS@@ABVCAttributePacket@3@@Z @ 0x002FFCBF
// sp-match: ?MakeNew@CAnimPackSelector@@SAPAVCAttributeHandler@RWS@@ABVCAttributePacket@3@@Z @ 0x0007E020
RWS_DEFINE_MAKENEW(CAnimPackSelector)

// match: ??0CAnimPackSelector@@QAE@ABVCAttributePacket@RWS@@@Z @ 0x000A0AD0
// match: __ehhandler$??0CAnimPackSelector@@QAE@ABVCAttributePacket@RWS@@@Z-0x13 @ 0x002FFCD0
// match: __ehhandler$??0CAnimPackSelector@@QAE@ABVCAttributePacket@RWS@@@Z @ 0x002FFCE3
// sp-match: ??0CAnimPackSelector@@QAE@ABVCAttributePacket@RWS@@@Z @ 0x0007DEF0
CAnimPackSelector::CAnimPackSelector(const RWS::CAttributePacket &attr)
{
    dword_4B67CC = this;
    sub_A0D40();
    LinkMsg(iMsgSparkStartSystem, 0, 0x8000);
    LinkMsg(dword_4B67C0, 0, 0x8000);
}

// match: ??_GCAnimPackSelector@@UAEPAXI@Z @ 0x000A0C70
// sp-match: ??_GCAnimPackSelector@@UAEPAXI@Z @ 0x0007E010

// match: ??1CAnimPackSelector@@UAE@XZ @ 0x000A0C90
// match: __ehhandler$??1CAnimPackSelector@@UAE@XZ-0x2F @ 0x002FFCF0
// match: __ehhandler$??1CAnimPackSelector@@UAE@XZ @ 0x002FFD1F
// sp-match: ??1CAnimPackSelector@@UAE@XZ @ 0x0007DB90
CAnimPackSelector::~CAnimPackSelector()
{
    UnLinkMsg(iMsgSparkStartSystem);
    UnLinkMsg(dword_4B67C0);
    dword_4B67CC = 0;
}

// match: ?sub_A0D40@CAnimPackSelector@@QAEXXZ @ 0x000A0D40
// sp-match: ?sub_A0D40@CAnimPackSelector@@QAEXXZ @ 0x0007DC20
void CAnimPackSelector::sub_A0D40()
{
    RwInt32 var_4;

    for (var_4 = 0; var_4 < 6; var_4++)
    {
        unk_28[var_4].unk_00.unk_00 = 0;
        unk_28[var_4].unk_00.unk_04 = 0;
        unk_28[var_4].unk_08[0] = 0;
        unk_118[var_4].unk_00.unk_00 = 0;
        unk_118[var_4].unk_00.unk_04 = 0;
        unk_118[var_4].unk_08[0] = 0;
    }
}

// Command 0: the six packs of the first set (their names looked up); command
// 1: the key.
// match: ?HandleAttributes@CAnimPackSelector@@UAEXABVCAttributePacket@RWS@@@Z @ 0x000A0DD0
// sp-match: ?HandleAttributes@CAnimPackSelector@@UAEXABVCAttributePacket@RWS@@@Z @ 0x0007DC60
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void CAnimPackSelector::HandleAttributes(const RWS::CAttributePacket &attr)
{
    RwInt32 var_14;
    const type_3DF8D8_04 *ebp_10;
    const type_3DF8D8_04 *l4;

    RWS::CAttributeHandler::HandleAttributes(attr);
    RWS::CAttributeCommandIterator locC(attr, RWS_CLASSID_OF(CAnimPackSelector));
    while (!locC.IsFinished())
    {
        switch (locC->GetCommandId())
        {
        case 0:
            sub_A0D40();
            l4 = (const type_3DF8D8_04 *)locC->GetAs_RwChar_ptr();
            for (var_14 = 0; var_14 < 6; var_14++)
            {
                unk_28[var_14].unk_00 = l4[var_14];
                if (l4[var_14].unk_00 || l4[var_14].unk_04)
                {
                    sub_198900((type_3DF8D8_04 *)&l4[var_14], 2, (void (*)(RwInt32, RwInt32, RwInt32))sub_195B70, 0,
                               (RwInt32)unk_28[var_14].unk_08, 0);
                }
            }
            break;
        case 1:
            ebp_10 = (const type_3DF8D8_04 *)locC->GetAs_RwChar_ptr();
            unk_20.unk_00 = ebp_10->unk_00;
            unk_20.unk_04 = ebp_10->unk_04;
            break;
        }
        ++locC;
    }
}

// match: ??_ECAnimPackSelector@@WBI@AEPAXI@Z @ 0x000A11D0
// sp-match: ??_ECAnimPackSelector@@WBI@AEPAXI@Z @ 0x0007DEE0

// When the system starts (or on its second message): plays the pack music,
// then loads each of the six animation packs (the restart set's where one
// is given) not yet loaded, keeping the music and the loading screen
// going between them.
// match: ?HandleEvents@CAnimPackSelector@@UAEXAAVCMsg@RWS@@@Z @ 0x000A0F10
// sp-match: ?HandleEvents@CAnimPackSelector@@UAEXAAVCMsg@RWS@@@Z @ 0x0007DD40
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void CAnimPackSelector::HandleEvents(RWS::CMsg &pMsg)
{
    RwInt32 var_10;
    CAnimPackSelector_pack *var_C;
    type_5E730 *bp_8;
    RwInt32 bp_4;

    if (pMsg.Id.p_msgrec == iMsgSparkStartSystem.p_msgrec || pMsg.Id.p_msgrec == dword_4B67C0.p_msgrec)
    {
#ifndef CODFH_SP
        // single player compiles the debug prints out (SP 0x7DD40)
        sub_19A750("AnimPack Loading begin...");
#endif
        if (unk_20.unk_00 && unk_20.unk_04 && !dword_4B8720)
        {
            bp_8 = (type_5E730 *)sub_198800(&unk_20);
            if (bp_8 && bp_8->unk_20 < 3)
            {
                dword_44E8D8[bp_8->unk_20].unk_244 = 1;
                dword_4B1E98.sub_8A980(&unk_20, 0, 0, 0, 1, 0);
            }
        }
        for (bp_4 = 0; bp_4 < 6; bp_4++)
        {
            for (var_10 = 0; var_10 < 3; var_10++)
            {
                dword_44E8D8[var_10].sub_873B0();
            }
            sub_86350();
            sub_83B50();
            if (unk_118[bp_4].unk_00.unk_00 || unk_118[bp_4].unk_00.unk_04)
            {
                var_C = &unk_118[bp_4];
            }
            else
            {
                var_C = &unk_28[bp_4];
            }
            if (var_C->unk_00.unk_00 || var_C->unk_00.unk_04)
            {
                if (!sub_774F0(*(type_449C94_08 *)&var_C->unk_00, bp_4))
                {
#ifndef CODFH_SP
                    sub_19A750("Loading animation group god ID: %x,%x to slot %d from file %s",
                               var_C->unk_00.unk_00, var_C->unk_00.unk_04, bp_4, var_C->unk_08);
#endif
                    sub_77540(var_C->unk_08, *(type_449C94_08 *)&var_C->unk_00, bp_4, 1, 0);
                }
                else
                {
#ifndef CODFH_SP
                    sub_19A750("Animation group god ID: %x,%x Name: %s is already loaded to slot %d",
                               var_C->unk_00.unk_00, var_C->unk_00.unk_04, var_C->unk_08, bp_4);
#endif
                }
            }
            dword_4B8EF0.sub_E9FB0(4);
            sub_D9450();
        }
#ifdef CODFH_WIN32
        {
            // (the port: a test level's extra animation packs into the banks after the six,
            // CAnimBankInfo's; each under an id of its own, so a restart finds it loaded)
            const RwChar *const *ppszExtra;
            RwInt32 nExtra = port_anim_packs(&ppszExtra), i;

            for (i = 0; i < nExtra; i++)
            {
                type_449C94_08 id;

                id.unk_00 = (RwInt32)0xC0DEA9A0 + i; // not an address: an id of the port's
                id.unk_04 = 0x0000C0DE;     // not an address: an id of the port's
                if (!sub_774F0(id, 6 + i))
                    sub_77540(ppszExtra[i], id, 6 + i, 1, 0);
                sub_D9450();
            }
        }
#endif
        if (pMsg.Id.p_msgrec == iMsgSparkStartSystem.p_msgrec)
        {
            UnLinkMsg(iMsgSparkStartSystem);
        }
#ifndef CODFH_SP
        sub_19A750("AnimPack Loading end...");
#endif
    }
}

// match: ?sub_A1130@CAnimPackSelector@@QAEXHPAUtype_3DF8D8_04@@@Z @ 0x000A1130
// sp-match: ?sub_A1130@CAnimPackSelector@@QAEXHPAUtype_3DF8D8_04@@@Z @ 0x0007DE70
void CAnimPackSelector::sub_A1130(RwInt32 arg_0, type_3DF8D8_04 *arg_4)
{
    unk_118[arg_0].unk_00 = *arg_4;
    if (arg_4->unk_00 || arg_4->unk_04)
    {
        sub_198900((type_3DF8D8_04 *)arg_4, 2, (void (*)(RwInt32, RwInt32, RwInt32))sub_195B70, 0, (RwInt32)unk_118[arg_0].unk_08, 0);
    }
}

// match: ?sub_A11A0@CAnimPackSelector@@QAEXHPAUtype_3DF8D8_04@@@Z @ 0x000A11A0
// sp-match: ?sub_A11A0@CAnimPackSelector@@QAEXHPAUtype_3DF8D8_04@@@Z @ 0x0007DEC0
void CAnimPackSelector::sub_A11A0(RwInt32 arg_0, type_3DF8D8_04 *arg_4)
{
    *arg_4 = unk_118[arg_0].unk_00;
}
