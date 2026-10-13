// CSoundBankSelector: its MakeNew, constructor, destructor and handlers. Its
// original file name is not in the image, so it is named for its start
// address.

#include "rw/ostypes.h"
#include "rws/cattributehandler.h"
#include "rws/cclassfactory.h"
#include "rws/ceventhandler.h"
#include "game/functions.h"
#include "types/CSoundBankSelector.h"
#include "types/type_4B8EF0.h"
#ifdef CODFH_SP
#include "game/data.h" // dword_4B8720, for sub_B9800
#include "types/soundbank.h" // dword_4B1B60, for sub_B9800
#endif
#ifdef CODFH_WIN32
#include "types/soundbank.h" // dword_4B1A20, SOUND_BANK_SLOTS
// (port/src/cli.cpp: a -leveldir test level's extra sound banks)
extern "C" RwInt32 port_sound_banks(RwUInt32 *pKeys, RwInt32 *pBanks, RwInt32 nMax);
#endif

// Its data definitions (PLAN M5), in the image's address order.
// 0x003D6554
extern const RwReal flt_3D6554 = 16.666666f;
// End of its data definitions.


RWS_IMPLEMENT_CLASSID(CSoundBankSelector);
RWS_REGISTERCLASS(CSoundBankSelector);
// Its data (PLAN M5): literals, constants and tables where the image has them.
// match: ??_C@_0BD@HJFAHKGO@CSoundBankSelector?$AA@ @ 0x003D6540
// match: ?flt_3D6554@@3MB @ 0x003D6554
// match: ??_7CSoundBankSelector@@6BCEventHandler@RWS@@@ @ 0x003D6558
// match: ??_7CSoundBankSelector@@6BCAttributeHandler@RWS@@@ @ 0x003D6560
// match: ??_C@_0BK@GPNEDLGC@SoundBank?5Loading?5end?4?4?4?6?$AA@ @ 0x003D6568
// match: ??_C@_0DG@JJHEPHN@Sound?5bank?5god?5ID?3?5?$CFx?0?$CFx?5is?5alre@ @ 0x003D6584
// match: ??_C@_0BM@GBFOPHAA@SoundBank?5Loading?5begin?4?4?4?6?$AA@ @ 0x003D65BC
// match: __ehhandler$?MakeNew@CSoundBankSelector@@SAPAVCAttributeHandler@RWS@@ABVCAttributePacket@3@@Z>1>8 @ 0x0041C174
// match: __ehhandler$?MakeNew@CSoundBankSelector@@SAPAVCAttributeHandler@RWS@@ABVCAttributePacket@3@@Z>1 @ 0x0041C17C
// match: __ehhandler$??0CSoundBankSelector@@QAE@ABVCAttributePacket@RWS@@@Z>1>8 @ 0x0041C198
// match: __ehhandler$??0CSoundBankSelector@@QAE@ABVCAttributePacket@RWS@@@Z>1 @ 0x0041C1A8
// match: __ehhandler$??1CSoundBankSelector@@UAE@XZ>1>8 @ 0x0041C1C4
// match: __ehhandler$??1CSoundBankSelector@@UAE@XZ>1 @ 0x0041C1D4
// match: .CRT$XCU+0 @ 0x00426F64
// match: ?pCSoundBankSelectorClassID@CSoundBankSelector@@2PBDB @ 0x004291B4

// match: _$E2 @ 0x0030AAE0
// match: _$E3 @ 0x0030E170

// (The class factory's registration and its exit thunk.)

// match: ?MakeNew@CSoundBankSelector@@SAPAVCAttributeHandler@RWS@@ABVCAttributePacket@3@@Z @ 0x000B9110
// match: __ehhandler$?MakeNew@CSoundBankSelector@@SAPAVCAttributeHandler@RWS@@ABVCAttributePacket@3@@Z-0xF @ 0x00300350
// match: __ehhandler$?MakeNew@CSoundBankSelector@@SAPAVCAttributeHandler@RWS@@ABVCAttributePacket@3@@Z @ 0x0030035F
// sp-match: ?MakeNew@CSoundBankSelector@@SAPAVCAttributeHandler@RWS@@ABVCAttributePacket@3@@Z @ 0x0008DFE0
RWS_DEFINE_MAKENEW(CSoundBankSelector)

// match: ??0CSoundBankSelector@@QAE@ABVCAttributePacket@RWS@@@Z @ 0x000B9190
// match: __ehhandler$??0CSoundBankSelector@@QAE@ABVCAttributePacket@RWS@@@Z-0x13 @ 0x00300370
// match: __ehhandler$??0CSoundBankSelector@@QAE@ABVCAttributePacket@RWS@@@Z @ 0x00300383
// sp-match: ??0CSoundBankSelector@@QAE@ABVCAttributePacket@RWS@@@Z @ 0x0008DC00
CSoundBankSelector::CSoundBankSelector(const RWS::CAttributePacket &attr)
{
    RwInt32 r10;
    RwInt32 var_14;

    for (r10 = 0; r10 < 6; r10++)
    {
        sub_83C60(&unk_20[r10]);
    }
    for (var_14 = 0; var_14 < 0xA; var_14++)
    {
        sub_83C60(&unk_120[var_14]);
    }
    LinkMsg(iMsgSparkStartSystem, 0, 0x8000);
    LinkMsg(RWS::iMsgStartSystem, 0, 0x8000);
    LinkMsg(dword_4B67B8, 0, 0x8000);
    LinkMsg(dword_4B67C0, 0, 0x8000);
}

// match: ??_GCSoundBankSelector@@UAEPAXI@Z @ 0x000B9390
// sp-match: ??_GCSoundBankSelector@@UAEPAXI@Z @ 0x0008DD70

// match: ??1CSoundBankSelector@@UAE@XZ @ 0x000B93B0
// match: __ehhandler$??1CSoundBankSelector@@UAE@XZ-0x2F @ 0x00300390
// match: __ehhandler$??1CSoundBankSelector@@UAE@XZ @ 0x003003BF
// sp-match: ??1CSoundBankSelector@@UAE@XZ @ 0x0008D8D0
CSoundBankSelector::~CSoundBankSelector()
{
    UnLinkMsg(iMsgSparkStartSystem);
    UnLinkMsg(RWS::iMsgStartSystem);
    UnLinkMsg(dword_4B67B8);
    UnLinkMsg(dword_4B67C0);
}

// Command 0: its banks.
// match: ?HandleAttributes@CSoundBankSelector@@UAEXABVCAttributePacket@RWS@@@Z @ 0x000B9470
// sp-match: ?HandleAttributes@CSoundBankSelector@@UAEXABVCAttributePacket@RWS@@@Z @ 0x0008DD80
void CSoundBankSelector::HandleAttributes(const RWS::CAttributePacket &attr)
{
    RWS::CAttributeHandler::HandleAttributes(attr);
    RWS::CAttributeCommandIterator attrIt(attr, RWS_CLASSID_OF(CSoundBankSelector));
    while (!attrIt.IsFinished())
    {
        switch (attrIt->GetCommandId())
        {
        case 0:
            sub_B95B0((const RwUInt32 *)attrIt->GetAs_RwChar_ptr());
            break;
        }
        ++attrIt;
    }
}

// match: ?HandleEvents@CSoundBankSelector@@UAEXAAVCMsg@RWS@@@Z @ 0x000B94F0
// sp-match: ?HandleEvents@CSoundBankSelector@@UAEXAAVCMsg@RWS@@@Z @ 0x0008DE00
void CSoundBankSelector::HandleEvents(RWS::CMsg &pMsg)
{
    RwInt32 var_4;

    if (pMsg.Id.p_msgrec == RWS::iMsgStartSystem.p_msgrec)
    {
    }
    else if (pMsg.Id.p_msgrec == iMsgSparkStartSystem.p_msgrec)
    {
        sub_B9800();
        UnLinkMsg(iMsgSparkStartSystem);
    }
    else if (pMsg.Id.p_msgrec == dword_4B67B8.p_msgrec)
    {
    }
    else if (pMsg.Id.p_msgrec == dword_4B67C0.p_msgrec)
    {
        for (var_4 = 0; var_4 < 0xA; var_4++)
        {
            dword_4B1B60[var_4] = unk_120[var_4];
        }
        sub_B9800();
    }
}

// match: ?sub_B95B0@CSoundBankSelector@@QAEXPBI@Z @ 0x000B95B0
// sp-match: ?sub_B95B0@CSoundBankSelector@@QAEXPBI@Z @ 0x0008D970
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void CSoundBankSelector::sub_B95B0(const RwUInt32 *arg_0)
{
    RwInt32 var_10;
    RwInt32 var_C;
    RwInt32 bp_8;
    RwInt32 bp_4;

    bp_8 = *arg_0;
    arg_0++;
    for (var_C = 0; var_C < 6; var_C++)
    {
        sub_83C60(&unk_20[var_C]);
    }
    for (var_C = 0; var_C < 0xA; var_C++)
    {
        sub_83C60(&unk_120[var_C]);
        sub_83C60(&dword_4B1B60[var_C]);
    }
    bp_4 = 0;
    var_10 = 0;
    for (var_C = 0; var_C < bp_8; var_C++)
    {
        type_825E0 var_20;

        var_20.unk_00.unk_00 = *arg_0;
        arg_0++;
        var_20.unk_00.unk_04 = *arg_0;
        arg_0++;
        arg_0++;
        arg_0++;
        arg_0++;
        arg_0++;
        var_20.unk_08 = *arg_0;
        arg_0++;
        var_20.unk_0C = *(const RwInt16 *)arg_0;
        arg_0++;
        if (var_20.unk_08 == 0x63)
        {
            if (bp_4 < 0xA)
            {
                unk_120[bp_4] = var_20;
                unk_120[bp_4].unk_08 = 5;
                dword_4B1B60[bp_4] = var_20;
                dword_4B1B60[bp_4].unk_08 = 5;
            }
            bp_4++;
        }
        else
        {
            if (var_10 < 6)
            {
                unk_20[var_10] = var_20;
            }
            var_10++;
        }
    }
    if (bp_8)
    {
        for (var_C = 0; var_C < 3; var_C++)
        {
            dword_4B1C20[var_C].unk_00 = *arg_0;
            arg_0++;
            dword_4B1C20[var_C].unk_04 = *arg_0;
            arg_0++;
        }
    }
}

// match: ?sub_B9800@CSoundBankSelector@@QAEXXZ @ 0x000B9800
// sp-match: ?sub_B9800@CSoundBankSelector@@QAEXXZ @ 0x0008DB00
void CSoundBankSelector::sub_B9800()
{
    RwInt32 var_4;

#if !defined(CODFH_SP) || defined(CODFH_SP_LOGS) // single player compiles the debug prints out (SP 0x8DB00)
    sub_19A750("SoundBank Loading begin...\n");
#endif
    var_4 = 0;
    for (var_4 = 0; var_4 < 6; var_4++)
    {
        sub_83DE0(var_4);
    }
    for (var_4 = 0; var_4 < 5; var_4++)
    {
        if (unk_20[var_4].unk_00.unk_00 != -1 && unk_20[var_4].unk_00.unk_04 != -1 &&
            unk_20[var_4].unk_0C != -1 && unk_20[var_4].unk_08 != -1)
        {
            if (dword_4B1A20[unk_20[var_4].unk_08].unk_18.unk_00.unk_00 == unk_20[var_4].unk_00.unk_00 &&
                dword_4B1A20[unk_20[var_4].unk_08].unk_18.unk_00.unk_04 == unk_20[var_4].unk_00.unk_04)
            {
#if !defined(CODFH_SP) || defined(CODFH_SP_LOGS)
                sub_19A750("Sound bank god ID: %x,%x is already loaded to slot %d",
                           unk_20[var_4].unk_00.unk_00, unk_20[var_4].unk_00.unk_00, unk_20[var_4].unk_08);
#endif
                continue;
            }
            if (dword_4B1A20[unk_20[var_4].unk_08].unk_10)
            {
                sub_83DE0(unk_20[var_4].unk_08);
            }
            sub_82C70(&unk_20[var_4], 0);
        }
        dword_4B8EF0.sub_E9FB0(5);
        sub_D9450();
    }
#ifdef CODFH_WIN32
    {
        // (the port: a test level's extra banks, port_sound_banks, each into a slot of its own
        // after the six, unless it is there already)
        RwUInt32 auKey[2 * (SOUND_BANK_SLOTS - 6)];
        RwInt32 anBank[SOUND_BANK_SLOTS - 6];
        RwInt32 i, n = port_sound_banks(auKey, anBank, SOUND_BANK_SLOTS - 6);

        for (i = 0; i < n; i++)
        {
            type_825E0 bank;

            bank.unk_00.unk_00 = auKey[i * 2];
            bank.unk_00.unk_04 = auKey[i * 2 + 1];
            bank.unk_08 = 6 + i;
            bank.unk_0C = (RwInt16)anBank[i];
            if (dword_4B1A20[6 + i].unk_18.unk_00.unk_00 == bank.unk_00.unk_00
                && dword_4B1A20[6 + i].unk_18.unk_00.unk_04 == bank.unk_00.unk_04)
                continue;
            if (dword_4B1A20[6 + i].unk_10)
                sub_83DE0(6 + i);
            sub_82C70(&bank, 0);
            sub_D9450();
        }
    }
#endif
#ifdef CODFH_SP // single player then loads one bank of the second set, picked by the restart count (SP 0x8DB9D)
    {
        RwInt32 i;
        RwInt32 n;

        for (n = 0, i = dword_4B8720 % 10; n < 10; n++)
        {
            if (dword_4B1B60[i].unk_00.unk_00 != -1 && dword_4B1B60[i].unk_00.unk_04 != -1)
            {
                sub_82C70(&dword_4B1B60[i], 0);
#ifdef CODFH_SP_LOGS
                sub_19A750("SoundBank Loading end...\n"); // (multiplayer's print, at its end)
#endif
                return;
            }
            i++;
            if (i >= 10)
                i = 0;
        }
    }
#ifdef CODFH_SP_LOGS
    sub_19A750("SoundBank Loading end...\n");
#endif
#else
    sub_19A750("SoundBank Loading end...\n");
#endif
}

// match: ??_ECSoundBankSelector@@WBI@AEPAXI@Z @ 0x000B99B0
// sp-match: ??_ECSoundBankSelector@@WBI@AEPAXI@Z @ 0x0008DBF0
