// VehicleTrigger: its MakeNew, constructor, destructor and handlers. Its
// original file name is not in the image, so it is named for its start
// address.

#include <math.h>
#include <string.h>

#include "rw/ostypes.h"
#include "rws/cattributehandler.h"
#include "rws/cclassfactory.h"
#include "rws/ceventhandler.h"
#include "game/functions.h"
#include "types/CustomTrigger.h"
#include "types/type_72810.h"
#include "types/VehicleTrigger.h"
#include "types/type_3DF8D8.h"

// Its data definitions (PLAN M5), in the image's address order.
// 0x003D699C
extern const RwReal flt_3D699C = 16.666666f;
// End of its data definitions.


RWS_IMPLEMENT_CLASSID(VehicleTrigger);
RWS_REGISTERCLASS(VehicleTrigger);
// Its data (PLAN M5): literals, constants and tables where the image has them.
// match: ??_C@_0P@CCLFLGOO@VehicleTrigger?$AA@ @ 0x003D698C
// match: ?flt_3D699C@@3MB @ 0x003D699C
// match: __real@3f860a92 @ 0x003D69A0
// match: ??_7VehicleTrigger@@6BCEventHandler@RWS@@@ @ 0x003D69A4
// match: ??_7VehicleTrigger@@6BCAttributeHandler@RWS@@@ @ 0x003D69AC
// match: ??_C@_0M@MOCHHBHJ@CreateChild?$AA@ @ 0x003D69E8
// match: __ehhandler$?MakeNew@VehicleTrigger@@SAPAVCAttributeHandler@RWS@@ABVCAttributePacket@3@@Z>1>8 @ 0x0041C3F8
// match: __ehhandler$?MakeNew@VehicleTrigger@@SAPAVCAttributeHandler@RWS@@ABVCAttributePacket@3@@Z>1 @ 0x0041C400
// match: __ehhandler$??0VehicleTrigger@@QAE@ABVCAttributePacket@RWS@@@Z>1>8 @ 0x0041C41C
// match: __ehhandler$??0VehicleTrigger@@QAE@ABVCAttributePacket@RWS@@@Z>1 @ 0x0041C424
// match: __ehhandler$??1VehicleTrigger@@UAE@XZ>1>8 @ 0x0041C440
// match: __ehhandler$??1VehicleTrigger@@UAE@XZ>1 @ 0x0041C448
// match: .CRT$XCU+0 @ 0x00426F88
// match: ?pVehicleTriggerClassID@VehicleTrigger@@2PBDB @ 0x004291D8

// match: _$E2 @ 0x0030AC90
// match: _$E3 @ 0x0030E200

// (The class factory's registration and its exit thunk.)

// match: ?MakeNew@VehicleTrigger@@SAPAVCAttributeHandler@RWS@@ABVCAttributePacket@3@@Z @ 0x000BF960
// match: __ehhandler$?MakeNew@VehicleTrigger@@SAPAVCAttributeHandler@RWS@@ABVCAttributePacket@3@@Z-0xF @ 0x003005B0
// match: __ehhandler$?MakeNew@VehicleTrigger@@SAPAVCAttributeHandler@RWS@@ABVCAttributePacket@3@@Z @ 0x003005BF
// sp-match: ?MakeNew@VehicleTrigger@@SAPAVCAttributeHandler@RWS@@ABVCAttributePacket@3@@Z @ 0x000937A0
RWS_DEFINE_MAKENEW(VehicleTrigger)

// match: ??0VehicleTrigger@@QAE@ABVCAttributePacket@RWS@@@Z @ 0x000BF9E0
// match: __ehhandler$??0VehicleTrigger@@QAE@ABVCAttributePacket@RWS@@@Z-0x8 @ 0x003005D0
// match: __ehhandler$??0VehicleTrigger@@QAE@ABVCAttributePacket@RWS@@@Z @ 0x003005D8
// sp-match: ??0VehicleTrigger@@QAE@ABVCAttributePacket@RWS@@@Z @ 0x00092A70
VehicleTrigger::VehicleTrigger(const RWS::CAttributePacket &attr) : Trigger(attr)
{
    unk_1FC = 0;
    unk_C0.unk_00 = 0;
    unk_C0.unk_04 = 0;
    unk_C8.unk_00 = 0;
    unk_C8.unk_04 = 0;
    unk_D0.unk_00 = 0;
    unk_D0.unk_04 = 0;
    unk_D8.unk_00 = 0;
    unk_D8.unk_04 = 0;
    unk_13C = 0;
    unk_E8 = -1;
    unk_EC = 0;
    unk_F0 = 10000;
    unk_F4 = 7500;
    unk_F8 = 60.0f;
    unk_FC = 0;
    unk_1F4 = 0;
    unk_1F8 = 0;
    unk_100 = 0;
    memset(&unk_104, 0, 0xC);
    memset(unk_118, 0, 0xC);
    // pi/3 (60 degrees), a literal: the float overload's argument is not
    // copied, and the constant lands in .rdata at 0x3D69A0.
    unk_124 = (RwReal)cos(1.0471976f);
    unk_128 = (RwReal)cos(1.0471976f);
    unk_12C = 7000.0f;
    unk_130 = 7000.0f;
    unk_154 = 1.0f;
    unk_140 = 200;
    unk_144 = 500;
    unk_148 = 0;
    unk_134 = 2500.0f;
    unk_138 = 500.0f;
    unk_110 = 0;
    unk_19C = 0;
    unk_1A0 = 360.0f;
    unk_1A4 = 0;
    unk_1A8 = 0;
    LinkMsg(dword_4B8750, 0, 0x8000);
    LinkMsg(dword_4B67B8, 0, 0x8000);
    LinkMsg(dword_4B67C0, 0, 0x8000);
}

// match: ?vf_008@VehicleTrigger@@UAEHXZ @ 0x000BFD70
// sp-match: ?vf_008@VehicleTrigger@@UAEHXZ @ 0x00122410

// match: ??_GVehicleTrigger@@UAEPAXI@Z @ 0x000BFD80
// sp-match: ??_GVehicleTrigger@@UAEPAXI@Z @ 0x00092E30

// match: ??1VehicleTrigger@@UAE@XZ @ 0x000BFDA0
// match: __ehhandler$??1VehicleTrigger@@UAE@XZ-0x8 @ 0x003005F0
// match: __ehhandler$??1VehicleTrigger@@UAE@XZ @ 0x003005F8
// sp-match: ??1VehicleTrigger@@UAE@XZ @ 0x00092C70
VehicleTrigger::~VehicleTrigger()
{
    if (unk_1FC)
    {
        sub_BD350(&unk_1FC);
    }
    UnLinkMsg(dword_4B8750);
    UnLinkMsg(dword_4B67B8);
    UnLinkMsg(dword_4B67C0);
}

// Commands 4 and 5 first, then the rest.
// match: ?HandleAttributes@VehicleTrigger@@UAEXABVCAttributePacket@RWS@@@Z @ 0x000BFE40
// sp-match: ?HandleAttributes@VehicleTrigger@@UAEXABVCAttributePacket@RWS@@@Z @ 0x00092E40
void VehicleTrigger::HandleAttributes(const RWS::CAttributePacket &attr)
{
    Trigger::HandleAttributes(attr);
    RWS::CAttributeCommandIterator var_14(attr, RWS_CLASSID_OF(VehicleTrigger));
    while (!var_14.IsFinished())
    {
        switch (var_14->GetCommandId())
        {
        case 4:
            unk_1F4 = var_14->GetAs_RwInt32();
            break;
        case 5:
            unk_1F8 = var_14->GetAs_RwInt32();
            break;
        }
        ++var_14;
    }
    RWS::CAttributeCommandIterator sysIt(attr, RWS_CLASSID_OF(VehicleTrigger));
    RwInt32 n;

    while (!sysIt.IsFinished())
    {
        switch (sysIt->GetCommandId())
        {
        case 50:
            n = *(const RwInt32 *)sysIt->GetAs_RwChar_ptr();
            if (n)
            {
                unk_24 |= 0x40000; // not an address: a flag bit
            }
            break;
        case 51:
            n = *(const RwInt32 *)sysIt->GetAs_RwChar_ptr();
            if (!n)
            {
                unk_24 |= 0x80000; // not an address: a flag bit
            }
            break;
        case 0:
            unk_E0 = *(const type_3DF8D8_04 *)sysIt->GetAs_RwChar_ptr();
            if (unk_E0.unk_00)
            {
                sub_198900((type_3DF8D8_04 *)&unk_E0, 0x2e, 0, 0, 0, 0);
            }
            break;
        case 2:
            unk_C0 = *(const type_3DF8D8_04 *)sysIt->GetAs_RwChar_ptr();
            if (unk_C0.unk_00 || unk_C0.unk_04)
            {
                RwUInt8 *var_18 = (RwUInt8 *)sub_198900((type_3DF8D8_04 *)&unk_C0, 0x27, 0, 0, 0, 0);

                if (unk_1F4)
                {
                    *(RwInt16 *)(var_18 + 0xC) = 1;
                }
            }
            break;
        case 3:
            unk_13C = sysIt->GetAs_RwInt32();
            break;
        case 6:
            unk_E8 = sysIt->GetAs_RwInt32();
            break;
        case 7:
            unk_EC = sysIt->GetAs_RwInt32();
            break;
        case 8:
            unk_F0 = sysIt->GetAs_RwInt32();
            break;
        case 9:
            unk_F4 = sysIt->GetAs_RwInt32();
            break;
        case 12:
            unk_100 = sysIt->GetAs_RwInt32();
            break;
        case 10:
            unk_F8 = sysIt->GetAs_RwReal();
            break;
        case 11:
            unk_FC = sysIt->GetAs_RwInt32();
            break;
        case 13:
            unk_C8 = *(const type_3DF8D8_04 *)sysIt->GetAs_RwChar_ptr();
            sub_198900((type_3DF8D8_04 *)&unk_C8, 0xa, 0, 0, 0, 0);
            break;
        case 14:
            unk_D0 = *(const type_3DF8D8_04 *)sysIt->GetAs_RwChar_ptr();
            if (unk_D0.unk_00)
            {
                sub_198900((type_3DF8D8_04 *)&unk_D0, 0xc, 0, 0, 0, 0);
            }
            break;
        case 15:
            unk_D8 = *(const type_3DF8D8_04 *)sysIt->GetAs_RwChar_ptr();
            if (unk_D8.unk_00)
            {
                sub_198900((type_3DF8D8_04 *)&unk_D8, 0xc, 0, 0, 0, 0);
            }
            break;
        case 16:
            if (unk_1FC)
            {
                sub_BD350(&unk_1FC);
            }
            sub_BD490(sysIt->GetAs_RwChar_ptr(), &unk_1FC);
            break;
        case 18:
        {
            RwReal var_1C = sysIt->GetAs_RwReal();

            unk_158 = var_1C;
            unk_124 = (RwReal)cos(var_1C *= 0.0087266462f);
            break;
        }
        case 19:
        {
            RwReal var_20 = sysIt->GetAs_RwReal();

            unk_128 = (RwReal)cos(var_20 *= 0.0087266462f);
            break;
        }
        case 20:
            unk_12C = sysIt->GetAs_RwReal() * 100.0f;
            break;
        case 21:
            unk_130 = sysIt->GetAs_RwReal() * 100.0f;
            break;
        case 22:
            unk_154 = sysIt->GetAs_RwReal();
            break;
        case 23:
            unk_134 = sysIt->GetAs_RwReal() * 100.0f;
            break;
        case 24:
            unk_138 = sysIt->GetAs_RwReal() * 100.0f;
            break;
        case 25:
            unk_140 = sysIt->GetAs_RwInt32();
            break;
        case 26:
            unk_144 = sysIt->GetAs_RwInt32();
            break;
        case 27:
            unk_15C = sysIt->GetAs_RwInt32();
            break;
        case 28:
            unk_16C = sysIt->GetAs_RwInt32();
            unk_170 = 0;
            unk_174 = 0;
            unk_178 = 0;
            break;
        case 29:
            unk_17C = sysIt->GetAs_RwInt32();
            break;
        case 30:
            unk_160 = sysIt->GetAs_RwInt32();
            break;
        case 31:
            unk_180 = sysIt->GetAs_RwInt32();
            break;
        case 32:
            unk_164 = sysIt->GetAs_RwInt32();
            break;
        case 33:
            unk_184 = sysIt->GetAs_RwInt32();
            break;
        case 34:
            unk_168 = sysIt->GetAs_RwInt32();
            break;
        case 35:
            unk_188 = sysIt->GetAs_RwInt32();
            break;
        case 36:
            unk_148 = sysIt->GetAs_RwInt32();
            break;
        case 37:
        {
            RwReal var_24 = sysIt->GetAs_RwReal();

            var_24 *= 0.5f;
            unk_14C = var_24;
            break;
        }
        case 38:
        {
            RwReal var_28 = sysIt->GetAs_RwReal();

            var_28 *= 0.5f;
            unk_150 = var_28;
            break;
        }
        case 39:
            unk_18C = sysIt->GetAs_RwInt32();
            break;
        case 40:
            unk_190 = sysIt->GetAs_RwInt32();
            break;
        case 41:
            unk_194 = sysIt->GetAs_RwInt32();
            break;
        case 42:
            unk_198 = sysIt->GetAs_RwInt32();
            break;
        case 43:
            unk_104 = *(const RwV3d *)sysIt->GetAs_RwChar_ptr();
            break;
        case 44:
            unk_110 = *(const RwInt32 *)sysIt->GetAs_RwChar_ptr();
            break;
        case 46:
            unk_19C = *(const RwInt32 *)sysIt->GetAs_RwChar_ptr();
            break;
        case 45:
            unk_114 = *(const RwInt32 *)sysIt->GetAs_RwChar_ptr();
            break;
        case 47:
            unk_1A0 = *(const RwReal *)sysIt->GetAs_RwChar_ptr();
            break;
        case 48:
            unk_1A4 = *(const RwInt32 *)sysIt->GetAs_RwChar_ptr();
            break;
        case 49:
            unk_1A8 = *(const RwInt32 *)sysIt->GetAs_RwChar_ptr();
            break;
        case 52:
            unk_1AC = *(const RwInt32 *)sysIt->GetAs_RwChar_ptr();
            break;
        case 53:
            unk_1B0 = *(const RwInt32 *)sysIt->GetAs_RwChar_ptr();
            break;
        case 54:
            unk_1B4 = sysIt->GetAs_RwInt32();
            break;
        case 55:
            unk_1E8 = *(const RwInt32 *)sysIt->GetAs_RwChar_ptr();
        case 56:
            unk_1B8 = *(const RwInt32 *)sysIt->GetAs_RwChar_ptr();
            break;
        case 58:
        {
            const type_3DF8D8_04 *var_2C = (const type_3DF8D8_04 *)sysIt->GetAs_RwChar_ptr();

            unk_1C0 = *var_2C;
            sub_198900((type_3DF8D8_04 *)&unk_1C0, 0xa, 0, 0, 0, 0);
            break;
        }
        case 59:
            unk_1C8 = *(const RwInt32 *)sysIt->GetAs_RwChar_ptr();
            break;
        case 60:
            unk_1CC = *(const RwInt32 *)sysIt->GetAs_RwChar_ptr();
            break;
        case 61:
            unk_1D0 = *(const RwInt32 *)sysIt->GetAs_RwChar_ptr();
            break;
        case 57:
            unk_1BC = sysIt->GetAs_RwInt32();
            break;
        case 62:
            unk_1D4 = sysIt->GetAs_RwReal();
            if (unk_1D4 != -1.0f)
            {
                unk_1D4 *= 0.5f;
            }
            break;
        case 63:
            unk_1D8 = sysIt->GetAs_RwReal();
            if (unk_1D8 != -1.0f)
            {
                unk_1D8 *= 0.5f;
            }
            break;
        case 64:
            unk_1DC = sysIt->GetAs_RwInt32();
            break;
        case 65:
            unk_1E0 = *(const RwInt32 *)sysIt->GetAs_RwChar_ptr();
            break;
        case 66:
            unk_1E4 = *(const RwInt32 *)sysIt->GetAs_RwChar_ptr();
            break;
        case 17:
        {
            type_3DF8D8_04 var_34 = *(const type_3DF8D8_04 *)sysIt->GetAs_RwChar_ptr();

            if (var_34.unk_00 || var_34.unk_04)
            {
                unk_1EC = var_34;
            }
            break;
        }
        }
        ++sysIt;
    }
}

// On dword_4B8750 (once) and dword_4B67C0 it creates its child.
// match: ?HandleEvents@VehicleTrigger@@UAEXAAVCMsg@RWS@@@Z @ 0x000C0EC0
// sp-match: ?HandleEvents@VehicleTrigger@@UAEXAAVCMsg@RWS@@@Z @ 0x00093750
void VehicleTrigger::HandleEvents(RWS::CMsg &pMsg)
{
    Trigger::HandleEvents(pMsg);
    if (pMsg.Id.p_msgrec == dword_4B8750.p_msgrec)
    {
        sub_C0F30();
        UnLinkMsg(dword_4B8750);
    }
    else if (pMsg.Id.p_msgrec == dword_4B67B8.p_msgrec)
    {
    }
    else if (pMsg.Id.p_msgrec == dword_4B67C0.p_msgrec)
    {
        sub_C0F30();
    }
}

// match: ?sub_C0F30@VehicleTrigger@@QAEXXZ @ 0x000C0F30
// sp-match: ?sub_C0F30@VehicleTrigger@@QAEXXZ @ 0x00092D10
void VehicleTrigger::sub_C0F30()
{
    RwInt32 var_4;

    if (unk_EC == 2 && sub_BDF50())
    {
        var_4 = 0;
        sub_6B5F0("CreateChild", (type_67620 *)(sub_BDF50()), 0, 0, &var_4, 1, 1, 0);
    }
}

// match: ?vf_020@VehicleTrigger@@UAEPAUtype_3D3548@@XZ @ 0x000C0F80
// sp-match: ?vf_020@VehicleTrigger@@UAEPAUtype_3D3548@@XZ @ 0x00092D60
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
type_3D3548 *VehicleTrigger::vf_020()
{
    type_3DF8D8 *n;
    type_3D3548 *bp_8;
    type_3DF8D8 *bp_4;

    bp_8 = 0;
    bp_4 = 0;
    n = sub_198800(&unk_C0);
    if (n)
    {
        bp_4 = ((type_3DFE7C *)n)->sub_1954D0();
    }
    if (!bp_4)
    {
    }
    else
    {
        switch (unk_E8)
        {
        case 0:
            bp_8 = (type_3D3548 *)sub_14C820((type_712B0 *)((type_3D3548 *)this));
            break;
        case 1:
            bp_8 = (type_3D3548 *)sub_155470((type_712B0 *)((type_3D3548 *)this));
            break;
        }
    }
    return bp_8;
}

// match: ?sub_C1010@VehicleTrigger@@QAEXPAUtype_3D2E7C@@@Z @ 0x000C1010
// sp-match: ?sub_C1010@VehicleTrigger@@QAEXPAUtype_3D2E7C@@@Z @ 0x00092DB0
void VehicleTrigger::sub_C1010(type_3D2E7C *arg_0)
{
    RwInt32 r10;
    RwInt32 var_8;

    if (!unk_1FC)
    {
        return;
    }
    for (r10 = 0; r10 < 5 && ((RwUInt16 *)(unk_1FC + 0x14))[r10] != 0xFFFF; r10++)
    {
        var_8 = ((RwInt32 *)unk_1FC)[r10];
        sub_6B680(((RwUInt16 *)(unk_1FC + 0x14))[r10], (type_67620 *)arg_0, (type_42E00_10 *)((RwInt32)this), 0, &var_8, 1, 1, 0);
    }
}

// match: ??_EVehicleTrigger@@WBI@AEPAXI@Z @ 0x000C10A0
// sp-match: ??_EVehicleTrigger@@WBI@AEPAXI@Z @ 0x00092E20

// Functions /OPT:ICF folded into another body (config/aliases.txt), defined here for the
// authentic link (PLAN M7) with that body; the placement link takes the folded one.

// ?vf_01C@VehicleTrigger@@UAEPAUtype_3DF8D8_04@@XZ (folded into 0x9F4D0)
// sp-match: ?vf_01C@VehicleTrigger@@UAEPAUtype_3DF8D8_04@@XZ @ 0x00092870
struct type_3DF8D8_04 *VehicleTrigger::vf_01C()
{
    return &unk_E0;
}
