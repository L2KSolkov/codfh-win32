// SoundBankTrigger: its MakeNew, constructor, destructor and handlers. Its
// original file name is not in the image, so it is named for its start
// address.

#include "rw/ostypes.h"
#include "rws/cattributehandler.h"
#include "rws/cclassfactory.h"
#include "types/SoundBankTrigger.h"

RWS_IMPLEMENT_CLASSID(SoundBankTrigger);
RWS_REGISTERCLASS(SoundBankTrigger);
// Its data (PLAN M5): literals, constants and tables where the image has them.
// match: ??_C@_0BB@CDGNBCGN@SoundBankTrigger?$AA@ @ 0x003D65D8
// match: ??_7SoundBankTrigger@@6BCEventHandler@RWS@@@ @ 0x003D65EC
// match: ??_7SoundBankTrigger@@6BCAttributeHandler@RWS@@@ @ 0x003D65F4
// match: __ehhandler$?MakeNew@SoundBankTrigger@@SAPAVCAttributeHandler@RWS@@ABVCAttributePacket@3@@Z>1>8 @ 0x0041C1F0
// match: __ehhandler$?MakeNew@SoundBankTrigger@@SAPAVCAttributeHandler@RWS@@ABVCAttributePacket@3@@Z>1 @ 0x0041C1F8
// match: .CRT$XCU+0 @ 0x00426F68
// match: ?pSoundBankTriggerClassID@SoundBankTrigger@@2PBDB @ 0x004291B8

// match: _$E2 @ 0x0030AB10
// match: _$E3 @ 0x0030E180

// (The class factory's registration and its exit thunk.)

// match: ?MakeNew@SoundBankTrigger@@SAPAVCAttributeHandler@RWS@@ABVCAttributePacket@3@@Z @ 0x000B99C0
// match: __ehhandler$?MakeNew@SoundBankTrigger@@SAPAVCAttributeHandler@RWS@@ABVCAttributePacket@3@@Z-0xF @ 0x003003D0
// match: __ehhandler$?MakeNew@SoundBankTrigger@@SAPAVCAttributeHandler@RWS@@ABVCAttributePacket@3@@Z @ 0x003003DF
// sp-match: ?MakeNew@SoundBankTrigger@@SAPAVCAttributeHandler@RWS@@ABVCAttributePacket@3@@Z @ 0x0008E4D0
RWS_DEFINE_MAKENEW(SoundBankTrigger)

// match: ??0SoundBankTrigger@@QAE@ABVCAttributePacket@RWS@@@Z @ 0x000B9A40
// sp-match: ??0SoundBankTrigger@@QAE@ABVCAttributePacket@RWS@@@Z @ 0x0008E400
SoundBankTrigger::SoundBankTrigger(const RWS::CAttributePacket &attr) : Trigger(attr)
{
}

// match: ??_GSoundBankTrigger@@UAEPAXI@Z @ 0x000B9B00
// sp-match: ??_GSoundBankTrigger@@UAEPAXI@Z @ 0x0008E4C0

// match: ??1SoundBankTrigger@@UAE@XZ @ 0x000B9B20
// sp-match: ??1SoundBankTrigger@@UAE@XZ @ 0x0008E050
// (Defined in the class, in SoundBankTrigger.h.)

// Command 0: its banks, as CSoundBankSelector reads them (a word count).
// match: ?HandleAttributes@SoundBankTrigger@@UAEXABVCAttributePacket@RWS@@@Z @ 0x000B9B50
// sp-match: ?HandleAttributes@SoundBankTrigger@@UAEXABVCAttributePacket@RWS@@@Z @ 0x0008E070
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void SoundBankTrigger::HandleAttributes(const RWS::CAttributePacket &attr)
{
    RwInt16 var_14 = 0;
    RwInt32 var_1C;
    RwInt32 var_18;
    const RwUInt32 *ebp_10;
    RwInt32 l4;

    Trigger::HandleAttributes(attr);
    RWS::CAttributeCommandIterator locC(attr, RWS_CLASSID_OF(SoundBankTrigger));
    while (!locC.IsFinished())
    {
        switch (locC->GetCommandId())
        {
        case 0:
            for (l4 = 0; l4 < 6; l4++)
            {
                sub_83C60(&unk_C0[l4]);
            }
            for (l4 = 0; l4 < 0xA; l4++)
            {
                sub_83C60(&unk_120[l4]);
            }
            ebp_10 = (const RwUInt32 *)locC->GetAs_RwChar_ptr();
            var_14 = *(const RwInt16 *)ebp_10;
            ebp_10++;
            var_18 = 0;
            var_1C = 0;
            for (l4 = 0; l4 < var_14; l4++)
            {
                type_825E0 var_2C;

                var_2C.unk_00.unk_00 = *ebp_10;
                ebp_10++;
                var_2C.unk_00.unk_04 = *ebp_10;
                ebp_10++;
                ebp_10++;
                ebp_10++;
                ebp_10++;
                ebp_10++;
                var_2C.unk_08 = *ebp_10;
                ebp_10++;
                var_2C.unk_0C = *(const RwInt16 *)ebp_10;
                ebp_10++;
                if (var_2C.unk_08 == 0x63)
                {
                    if (var_18 < 0xA)
                    {
                        unk_120[var_18] = var_2C;
                        unk_120[var_18].unk_08 = 5;
                    }
                    var_18++;
                }
                else
                {
                    if (var_1C < 6)
                    {
                        unk_C0[var_1C] = var_2C;
                    }
                    var_1C++;
                }
            }
            break;
        }
        ++locC;
    }
}

// match: ?sub_B9D80@SoundBankTrigger@@QAEXXZ @ 0x000B9D80
// sp-match: ?sub_B9D80@SoundBankTrigger@@QAEXXZ @ 0x0008E1D0
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void SoundBankTrigger::sub_B9D80()
{
    RwInt32 var_8;
    RwInt32 l4;

    if (unk_120[0].unk_0C >= 0)
    {
        for (var_8 = 0; var_8 < 0xA; var_8++)
        {
            sub_83C60(&dword_4B1B60[var_8]);
        }
        for (l4 = 0; l4 < 0xA; l4++)
        {
            dword_4B1B60[l4] = unk_120[l4];
        }
        unk_C0[5] = unk_120[0];
        flt_4AEFF4 = flt_428E28;
        dword_428E2C = 0;
    }
    for (l4 = 0; l4 < 6; l4++)
    {
        sub_84300(&unk_C0[l4]);
    }
}

// match: ??_ESoundBankTrigger@@WBI@AEPAXI@Z @ 0x000B9E90
// sp-match: ??_ESoundBankTrigger@@WBI@AEPAXI@Z @ 0x0008E3F0

// Functions /OPT:ICF folded into another body (config/aliases.txt), defined here for the
// authentic link (PLAN M7) with that body; the placement link takes the folded one.

// ?HandleEvents@SoundBankTrigger@@UAEXAAVCMsg@RWS@@@Z (folded into 0xA2BF0)
void SoundBankTrigger::HandleEvents(class RWS::CMsg & pMsg)
{
    Trigger::HandleEvents(pMsg);
}

// ?vf_008@SoundBankTrigger@@UAEHXZ (folded into 0x36780)
RwInt32 SoundBankTrigger::vf_008()
{
    return 10;
}
