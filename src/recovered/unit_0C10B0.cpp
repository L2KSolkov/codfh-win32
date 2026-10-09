// CWeaponBehavior and the four explosive behaviours derived from it: their
// MakeNews, constructors, destructors and handlers. The original file name
// is not in the image, so it is named for its start address.

#include "rw/ostypes.h"
#include "rws/cattributehandler.h"
#include "rws/cclassfactory.h"
#include "rws/ceventhandler.h"
#include "game/functions.h"
#include "game/mathutil.h"
#include "types/CWeaponBehavior.h"
#include "types/type_10F710.h"
#include "types/type_4C19C0.h"
#include "types/type_72810.h"

// Its data definitions (PLAN M5), in the image's address order.
// 0x003D6A50
extern const RwReal flt_3D6A50 = 16.666666f;
// End of its data definitions.


RWS_IMPLEMENT_CLASSID(CWeaponBehavior);
RWS_REGISTERCLASS(CWeaponBehavior);
// Its data (PLAN M5): literals, constants and tables where the image has them.
// match: ??_C@_0BB@KAGOAJGP@CGrenadeBehavior?$AA@ @ 0x003D69F4
// match: ??_C@_0BC@IJKGNJBI@CAntiTankBehavior?$AA@ @ 0x003D6A08
// match: ??_C@_0O@DPFNAKIH@CTankBehavior?$AA@ @ 0x003D6A1C
// match: ??_C@_0BD@PLKCNIEB@CExplosiveBehavior?$AA@ @ 0x003D6A2C
// match: ??_C@_0BA@IPJJEJHA@CWeaponBehavior?$AA@ @ 0x003D6A40
// match: ?flt_3D6A50@@3MB @ 0x003D6A50
// match: ??_7CWeaponBehavior@@6BCEventHandler@RWS@@@ @ 0x003D6A54
// match: ??_7CWeaponBehavior@@6BCAttributeHandler@RWS@@@ @ 0x003D6A5C
// match: ??_7CExplosiveBehavior@@6BCEventHandler@RWS@@@ @ 0x003D6A64
// match: ??_7CExplosiveBehavior@@6BCAttributeHandler@RWS@@@ @ 0x003D6A6C
// match: ??_7CTankBehavior@@6BCEventHandler@RWS@@@ @ 0x003D6A74
// match: ??_7CTankBehavior@@6BCAttributeHandler@RWS@@@ @ 0x003D6A7C
// match: ??_7CAntiTankBehavior@@6BCEventHandler@RWS@@@ @ 0x003D6A84
// match: ??_7CAntiTankBehavior@@6BCAttributeHandler@RWS@@@ @ 0x003D6A8C
// match: ??_7CGrenadeBehavior@@6BCEventHandler@RWS@@@ @ 0x003D6A94
// match: ??_7CGrenadeBehavior@@6BCAttributeHandler@RWS@@@ @ 0x003D6A9C
// match: __ehhandler$?MakeNew@CExplosiveBehavior@@SAPAVCAttributeHandler@RWS@@ABVCAttributePacket@3@@Z>1>8 @ 0x0041C464
// match: __ehhandler$?MakeNew@CExplosiveBehavior@@SAPAVCAttributeHandler@RWS@@ABVCAttributePacket@3@@Z>1 @ 0x0041C46C
// match: __ehhandler$??0CWeaponBehavior@@QAE@ABVCAttributePacket@RWS@@@Z>1>8 @ 0x0041C488
// match: __ehhandler$??0CWeaponBehavior@@QAE@ABVCAttributePacket@RWS@@@Z>1 @ 0x0041C498
// match: __ehhandler$??1CWeaponBehavior@@UAE@XZ>1>8 @ 0x0041C4B4
// match: __ehhandler$??1CWeaponBehavior@@UAE@XZ>1 @ 0x0041C4C4
// match: __ehhandler$?MakeNew@CTankBehavior@@SAPAVCAttributeHandler@RWS@@ABVCAttributePacket@3@@Z>1>8 @ 0x0041C4E0
// match: __ehhandler$?MakeNew@CTankBehavior@@SAPAVCAttributeHandler@RWS@@ABVCAttributePacket@3@@Z>1 @ 0x0041C4E8
// match: __ehhandler$?MakeNew@CAntiTankBehavior@@SAPAVCAttributeHandler@RWS@@ABVCAttributePacket@3@@Z>1>8 @ 0x0041C504
// match: __ehhandler$?MakeNew@CAntiTankBehavior@@SAPAVCAttributeHandler@RWS@@ABVCAttributePacket@3@@Z>1 @ 0x0041C50C
// match: __ehhandler$?MakeNew@CGrenadeBehavior@@SAPAVCAttributeHandler@RWS@@ABVCAttributePacket@3@@Z>1>8 @ 0x0041C528
// match: __ehhandler$?MakeNew@CGrenadeBehavior@@SAPAVCAttributeHandler@RWS@@ABVCAttributePacket@3@@Z>1 @ 0x0041C530
// match: __ehhandler$?MakeNew@CWeaponBehavior@@SAPAVCAttributeHandler@RWS@@ABVCAttributePacket@3@@Z>1>8 @ 0x0041C54C
// match: __ehhandler$?MakeNew@CWeaponBehavior@@SAPAVCAttributeHandler@RWS@@ABVCAttributePacket@3@@Z>1 @ 0x0041C554
// match: .CRT$XCU+0 @ 0x00426F8C
// match: .CRT$XCU+4 @ 0x00426F90
// match: .CRT$XCU+8 @ 0x00426F94
// match: .CRT$XCU+12 @ 0x00426F98
// match: .CRT$XCU+16 @ 0x00426F9C
// match: ?pCWeaponBehaviorClassID@CWeaponBehavior@@2PBDB @ 0x004291DC
// match: ?pCExplosiveBehaviorClassID@CExplosiveBehavior@@2PBDB @ 0x004291E0
// match: ?pCTankBehaviorClassID@CTankBehavior@@2PBDB @ 0x004291E4
// match: ?pCAntiTankBehaviorClassID@CAntiTankBehavior@@2PBDB @ 0x004291E8
// match: ?pCGrenadeBehaviorClassID@CGrenadeBehavior@@2PBDB @ 0x004291EC

// match: _$E2 @ 0x0030ACC0
// match: _$E3 @ 0x0030E210
// sp-match: _$E2 @ 0x0021D050

// (The class factory's registration and its exit thunk.)
RWS_IMPLEMENT_CLASSID(CExplosiveBehavior);
RWS_REGISTERCLASS(CExplosiveBehavior);
// match: _$E5 @ 0x0030ACF0
// match: _$E6 @ 0x0030E220
// sp-match: _$E5 @ 0x0021D080
// (The class factory's registration and its exit thunk.)
RWS_IMPLEMENT_CLASSID(CTankBehavior);
RWS_REGISTERCLASS(CTankBehavior);
// match: _$E8 @ 0x0030AD20
// match: _$E9 @ 0x0030E230
// sp-match: _$E8 @ 0x0021D0B0
// (The class factory's registration and its exit thunk.)
RWS_IMPLEMENT_CLASSID(CAntiTankBehavior);
RWS_REGISTERCLASS(CAntiTankBehavior);
// match: _$E11 @ 0x0030AD50
// match: _$E12 @ 0x0030E240
// sp-match: _$E11 @ 0x0021D0E0
// (The class factory's registration and its exit thunk.)
RWS_IMPLEMENT_CLASSID(CGrenadeBehavior);
RWS_REGISTERCLASS(CGrenadeBehavior);
// match: _$E14 @ 0x0030AD80
// match: _$E15 @ 0x0030E250
// sp-match: _$E14 @ 0x0021D110
// (The class factory's registration and its exit thunk.)

// match: ?MakeNew@CWeaponBehavior@@SAPAVCAttributeHandler@RWS@@ABVCAttributePacket@3@@Z @ 0x000C10B0
// match: __ehhandler$?MakeNew@CWeaponBehavior@@SAPAVCAttributeHandler@RWS@@ABVCAttributePacket@3@@Z-0xF @ 0x00300670
// match: __ehhandler$?MakeNew@CWeaponBehavior@@SAPAVCAttributeHandler@RWS@@ABVCAttributePacket@3@@Z @ 0x0030067F
// sp-match: ?MakeNew@CWeaponBehavior@@SAPAVCAttributeHandler@RWS@@ABVCAttributePacket@3@@Z @ 0x00095F60
RWS_DEFINE_MAKENEW(CWeaponBehavior)

// match: ??0CWeaponBehavior@@QAE@ABVCAttributePacket@RWS@@@Z @ 0x000C1130
// match: __ehhandler$??0CWeaponBehavior@@QAE@ABVCAttributePacket@RWS@@@Z-0x13 @ 0x00300610
// match: __ehhandler$??0CWeaponBehavior@@QAE@ABVCAttributePacket@RWS@@@Z @ 0x00300623
// sp-match: ??0CWeaponBehavior@@QAE@ABVCAttributePacket@RWS@@@Z @ 0x00093810
CWeaponBehavior::CWeaponBehavior(const RWS::CAttributePacket &attr)
{
    unk_24 = 0;
    LinkMsg(dword_4B8750, 0, 0x8000);
}

// match: ??_GCWeaponBehavior@@UAEPAXI@Z @ 0x000C1210
// sp-match: ??_GCWeaponBehavior@@UAEPAXI@Z @ 0x00093A80

// match: ??1CWeaponBehavior@@UAE@XZ @ 0x000C1230
// match: __ehhandler$??1CWeaponBehavior@@UAE@XZ-0x2F @ 0x00300630
// match: __ehhandler$??1CWeaponBehavior@@UAE@XZ @ 0x0030065F
// sp-match: ??1CWeaponBehavior@@UAE@XZ @ 0x00093890
CWeaponBehavior::~CWeaponBehavior()
{
    UnLinkMsg(dword_4B8750);
}

// Command 0 picks the settings (numbered from 1); commands 1 to 219 fill
// them. The plain real copies go through the FPU (fld, fstp) where a float
// assignment is a dword move, which only a round trip through RwDouble
// reproduces; commands 83, 88, 93, 160, 170 and 180 also update the players'
// copies of the weapon once they have them (unk_24).
// match: ?HandleAttributes@CWeaponBehavior@@UAEXABVCAttributePacket@RWS@@@Z @ 0x000C12C0
// sp-match: ?HandleAttributes@CWeaponBehavior@@UAEXABVCAttributePacket@RWS@@@Z @ 0x00093A90
void CWeaponBehavior::HandleAttributes(const RWS::CAttributePacket &attr)
{
    type_4C19C0 *var_14;

    RWS::CAttributeHandler::HandleAttributes(attr);
    RWS::CAttributeCommandIterator bp_8(attr, RWS_CLASSID_OF(CWeaponBehavior));
    RWS::CAttributeCommandIterator ebp_10(attr, RWS_CLASSID_OF(CWeaponBehavior));
    while (!bp_8.IsFinished())
    {
        if (bp_8->GetCommandId() == 0)
        {
            unk_20 = bp_8->GetAs_RwInt32() - 1;
        }
        ++bp_8;
    }
    if (unk_20 == -1)
    {
        return;
    }
    var_14 = sub_119B70(unk_20);
    while (!ebp_10.IsFinished())
    {
        switch (ebp_10->GetCommandId())
        {
        case 1:
            var_14->unk_00 = *(const type_3DF8D8_04 *)ebp_10->GetAs_RwChar_ptr();
            break;
        case 3:
            var_14->unk_B4 = ebp_10->GetAs_RwInt32();
            break;
        case 2:
        {
            RwReal var_18 = *(const RwReal *)ebp_10->GetAs_RwChar_ptr();

#ifdef CODFH_SP
            // shape: two separate products, not folded into one constant (SP: fmul 0.5, fmul 0.017453292)
            var_18 = var_18 * 0.5f;
            var_18 = var_18 * 0.017453292f;
#else
            var_18 = var_18 * 0.5f * 0.017453292f;
#endif
            var_14->unk_324 = tan_ref(var_18);
            break;
        }
        case 5:
            var_14->unk_BC = ebp_10->GetAs_RwReal() * 60.0f;
            break;
        case 4:
            var_14->unk_B8 = ebp_10->GetAs_RwInt32();
            break;
        case 6:
            var_14->unk_C4 = ebp_10->GetAs_RwInt32();
            break;
        case 7:
            var_14->unk_4B8 = ebp_10->GetAs_RwInt32();
            break;
        case 8:
            var_14->unk_C0 = ebp_10->GetAs_RwInt32();
            break;
        case 9:
            var_14->unk_D4 = ebp_10->GetAs_RwInt32();
            break;
        case 10:
            var_14->unk_D8 = ebp_10->GetAs_RwInt32();
            break;
        case 11:
            var_14->unk_DC = ebp_10->GetAs_RwInt32();
            break;
        case 12:
            var_14->unk_E0 = ebp_10->GetAs_RwReal() * 100.0f;
            break;
        case 13:
            ebp_10->GetCommandData(var_14->unk_320);
            break;
        case 14:
            var_14->unk_98 = ebp_10->GetAs_RwInt32();
            break;
        case 15:
            var_14->unk_B0 = ebp_10->GetAs_RwInt32();
            break;
        case 66:
            var_14->unk_C8 = ebp_10->GetAs_RwInt32();
            break;
        case 67:
            var_14->unk_CC = ebp_10->GetAs_RwInt32();
            break;
        case 16:
            var_14->unk_20 = (bool)ebp_10->GetAs_RwInt32();
            break;
        case 17:
            var_14->unk_168 = *(const RwV3d *)ebp_10->GetAs_RwChar_ptr();
            break;
        case 18:
            var_14->unk_28C = (bool)ebp_10->GetAs_RwInt32();
            break;
        case 19:
            var_14->unk_174 = *(const RwV3d *)ebp_10->GetAs_RwChar_ptr();
            break;
        case 21:
            var_14->unk_18C = ebp_10->GetAs_RwInt32();
            break;
        case 22:
            var_14->unk_190 = ebp_10->GetAs_RwInt32();
            break;
        case 35:
            ebp_10->GetCommandData(var_14->unk_1C);
            break;
        case 36:
            var_14->unk_0C = *(const type_3DF8D8_04 *)ebp_10->GetAs_RwChar_ptr();
            break;
        case 37:
            var_14->unk_14 = *(const type_3DF8D8_04 *)ebp_10->GetAs_RwChar_ptr();
            break;
        case 38:
        {
            const type_3DF8D8_04 *var_1C = (const type_3DF8D8_04 *)ebp_10->GetAs_RwChar_ptr();

            if (var_1C->unk_00 || var_1C->unk_04)
            {
                sub_198900((type_3DF8D8_04 *)var_1C, 2, (void (*)(RwInt32, RwInt32, RwInt32))sub_195C10, 0,
                           (RwInt32)&var_14->unk_2C, 0);
            }
            break;
        }
        case 39:
        {
            const type_3DF8D8_04 *var_20 = (const type_3DF8D8_04 *)ebp_10->GetAs_RwChar_ptr();

            if (var_20->unk_00 || var_20->unk_04)
            {
                sub_198900((type_3DF8D8_04 *)var_20, 2, (void (*)(RwInt32, RwInt32, RwInt32))sub_195C10, 0,
                           (RwInt32)&var_14->unk_30, 0);
            }
            break;
        }
        case 40:
        {
            const type_3DF8D8_04 *var_24 = (const type_3DF8D8_04 *)ebp_10->GetAs_RwChar_ptr();

            if (var_24->unk_00 || var_24->unk_04)
            {
                sub_198900((type_3DF8D8_04 *)var_24, 2, (void (*)(RwInt32, RwInt32, RwInt32))sub_195C10, 0,
                           (RwInt32)&var_14->unk_34, 0);
            }
            break;
        }
        case 41:
        {
            const type_3DF8D8_04 *var_28 = (const type_3DF8D8_04 *)ebp_10->GetAs_RwChar_ptr();

            if (var_28->unk_00 || var_28->unk_04)
            {
                sub_198900((type_3DF8D8_04 *)var_28, 2, (void (*)(RwInt32, RwInt32, RwInt32))sub_195C10, 0,
                           (RwInt32)&var_14->unk_38, 0);
            }
            break;
        }
        case 42:
        {
            const type_3DF8D8_04 *var_2C = (const type_3DF8D8_04 *)ebp_10->GetAs_RwChar_ptr();

            if (var_2C->unk_00 || var_2C->unk_04)
            {
                sub_198900((type_3DF8D8_04 *)var_2C, 2, (void (*)(RwInt32, RwInt32, RwInt32))sub_195C10, 0,
                           (RwInt32)&var_14->unk_28, 0);
            }
            break;
        }
        case 43:
        {
            const type_3DF8D8_04 *var_30 = (const type_3DF8D8_04 *)ebp_10->GetAs_RwChar_ptr();

            if (var_30->unk_00 || var_30->unk_04)
            {
                sub_198900((type_3DF8D8_04 *)var_30, 2, (void (*)(RwInt32, RwInt32, RwInt32))sub_195C10, 0,
                           (RwInt32)&var_14->unk_3C, 0);
            }
            break;
        }
        case 44:
        {
            const type_3DF8D8_04 *var_34 = (const type_3DF8D8_04 *)ebp_10->GetAs_RwChar_ptr();

            if (var_34->unk_00 || var_34->unk_04)
            {
                sub_198900((type_3DF8D8_04 *)var_34, 2, (void (*)(RwInt32, RwInt32, RwInt32))sub_195C10, 0,
                           (RwInt32)&var_14->unk_40, 0);
            }
            break;
        }
        case 45:
        {
            const type_3DF8D8_04 *var_38 = (const type_3DF8D8_04 *)ebp_10->GetAs_RwChar_ptr();

            if (var_38->unk_00 || var_38->unk_04)
            {
                sub_198900((type_3DF8D8_04 *)var_38, 2, (void (*)(RwInt32, RwInt32, RwInt32))sub_195C10, 0,
                           (RwInt32)&var_14->unk_44, 0);
            }
            break;
        }
        case 46:
        {
            const type_3DF8D8_04 *var_3C = (const type_3DF8D8_04 *)ebp_10->GetAs_RwChar_ptr();

            if (var_3C->unk_00 || var_3C->unk_04)
            {
                sub_198900((type_3DF8D8_04 *)var_3C, 2, (void (*)(RwInt32, RwInt32, RwInt32))sub_195C10, 0,
                           (RwInt32)&var_14->unk_48, 0);
            }
            break;
        }
        case 47:
        {
            const type_3DF8D8_04 *var_40 = (const type_3DF8D8_04 *)ebp_10->GetAs_RwChar_ptr();

            if (var_40->unk_00 || var_40->unk_04)
            {
                sub_198900((type_3DF8D8_04 *)var_40, 2, (void (*)(RwInt32, RwInt32, RwInt32))sub_195C10, 0,
                           (RwInt32)&var_14->unk_4C, 0);
            }
            break;
        }
        case 48:
        {
            const type_3DF8D8_04 *var_44 = (const type_3DF8D8_04 *)ebp_10->GetAs_RwChar_ptr();

            if (var_44->unk_00 || var_44->unk_04)
            {
                sub_198900((type_3DF8D8_04 *)var_44, 2, (void (*)(RwInt32, RwInt32, RwInt32))sub_195C10, 0,
                           (RwInt32)&var_14->unk_50, 0);
            }
            break;
        }
        case 49:
        {
            const type_3DF8D8_04 *var_48 = (const type_3DF8D8_04 *)ebp_10->GetAs_RwChar_ptr();

            if (var_48->unk_00 || var_48->unk_04)
            {
                sub_198900((type_3DF8D8_04 *)var_48, 2, (void (*)(RwInt32, RwInt32, RwInt32))sub_195C10, 0,
                           (RwInt32)&var_14->unk_54, 0);
            }
            break;
        }
        case 50:
        {
            const type_3DF8D8_04 *var_4C = (const type_3DF8D8_04 *)ebp_10->GetAs_RwChar_ptr();

            if (var_4C->unk_00 || var_4C->unk_04)
            {
                sub_198900((type_3DF8D8_04 *)var_4C, 2, (void (*)(RwInt32, RwInt32, RwInt32))sub_195C10, 0,
                           (RwInt32)&var_14->unk_58, 0);
            }
            break;
        }
        case 51:
        {
            const type_3DF8D8_04 *var_50 = (const type_3DF8D8_04 *)ebp_10->GetAs_RwChar_ptr();

            if (var_50->unk_00 || var_50->unk_04)
            {
                sub_198900((type_3DF8D8_04 *)var_50, 2, (void (*)(RwInt32, RwInt32, RwInt32))sub_195C10, 0,
                           (RwInt32)&var_14->unk_60, 0);
            }
            break;
        }
        case 52:
        {
            const type_3DF8D8_04 *var_54 = (const type_3DF8D8_04 *)ebp_10->GetAs_RwChar_ptr();

            if (var_54->unk_00 || var_54->unk_04)
            {
                sub_198900((type_3DF8D8_04 *)var_54, 2, (void (*)(RwInt32, RwInt32, RwInt32))sub_195C10, 0,
                           (RwInt32)&var_14->unk_64, 0);
            }
            break;
        }
        case 53:
        {
            const type_3DF8D8_04 *var_58 = (const type_3DF8D8_04 *)ebp_10->GetAs_RwChar_ptr();

            if (var_58->unk_00 || var_58->unk_04)
            {
                sub_198900((type_3DF8D8_04 *)var_58, 2, (void (*)(RwInt32, RwInt32, RwInt32))sub_195C10, 0,
                           (RwInt32)&var_14->unk_68, 0);
            }
            break;
        }
        case 54:
        {
            const type_3DF8D8_04 *var_5C = (const type_3DF8D8_04 *)ebp_10->GetAs_RwChar_ptr();

            if (var_5C->unk_00 || var_5C->unk_04)
            {
                sub_198900((type_3DF8D8_04 *)var_5C, 2, (void (*)(RwInt32, RwInt32, RwInt32))sub_195C10, 0,
                           (RwInt32)&var_14->unk_6C, 0);
            }
            break;
        }
        case 55:
        {
            const type_3DF8D8_04 *var_60 = (const type_3DF8D8_04 *)ebp_10->GetAs_RwChar_ptr();

            if (var_60->unk_00 || var_60->unk_04)
            {
                sub_198900((type_3DF8D8_04 *)var_60, 2, (void (*)(RwInt32, RwInt32, RwInt32))sub_195C10, 0,
                           (RwInt32)&var_14->unk_70, 0);
            }
            break;
        }
        case 56:
        {
            const type_3DF8D8_04 *var_64 = (const type_3DF8D8_04 *)ebp_10->GetAs_RwChar_ptr();

            if (var_64->unk_00 || var_64->unk_04)
            {
                sub_198900((type_3DF8D8_04 *)var_64, 2, (void (*)(RwInt32, RwInt32, RwInt32))sub_195C10, 0,
                           (RwInt32)&var_14->unk_74, 0);
            }
            break;
        }
        case 57:
            if (*(const RwInt32 *)ebp_10->GetAs_RwChar_ptr())
            {
                sub_198900((type_3DF8D8_04 *)ebp_10->GetAs_RwChar_ptr(), 2,
                           (void (*)(RwInt32, RwInt32, RwInt32))sub_195C10, 0, (RwInt32)&var_14->unk_78, 0);
            }
            break;
        case 58:
        {
            const type_3DF8D8_04 *var_68 = (const type_3DF8D8_04 *)ebp_10->GetAs_RwChar_ptr();

            if (var_68->unk_00 || var_68->unk_04)
            {
                sub_198900((type_3DF8D8_04 *)var_68, 2, (void (*)(RwInt32, RwInt32, RwInt32))sub_195C10, 0,
                           (RwInt32)&var_14->unk_5C, 0);
            }
            break;
        }
        case 59:
        {
            const type_3DF8D8_04 *var_6C = (const type_3DF8D8_04 *)ebp_10->GetAs_RwChar_ptr();

            if (var_6C->unk_00 || var_6C->unk_04)
            {
                sub_198900((type_3DF8D8_04 *)var_6C, 2, (void (*)(RwInt32, RwInt32, RwInt32))sub_195C10, 0,
                           (RwInt32)&var_14->unk_7C, 0);
            }
            break;
        }
        case 60:
            var_14->unk_80 = *(const RwUInt8 *)ebp_10->GetAs_RwChar_ptr();
            break;
        case 61:
        {
            const type_3DF8D8_04 *var_70 = (const type_3DF8D8_04 *)ebp_10->GetAs_RwChar_ptr();

            if (var_70->unk_00 || var_70->unk_04)
            {
                sub_198900((type_3DF8D8_04 *)var_70, 2, (void (*)(RwInt32, RwInt32, RwInt32))sub_195C10, 0,
                           (RwInt32)&var_14->unk_84, 0);
            }
            break;
        }
        case 63:
        {
            const type_3DF8D8_04 *var_74 = (const type_3DF8D8_04 *)ebp_10->GetAs_RwChar_ptr();

            if (var_74->unk_00 || var_74->unk_04)
            {
                sub_198900((type_3DF8D8_04 *)var_74, 2, (void (*)(RwInt32, RwInt32, RwInt32))sub_195C10, 0,
                           (RwInt32)&var_14->unk_8C, 0);
            }
            break;
        }
        case 62:
        {
            const type_3DF8D8_04 *var_78 = (const type_3DF8D8_04 *)ebp_10->GetAs_RwChar_ptr();

            if (var_78->unk_00 || var_78->unk_04)
            {
                sub_198900((type_3DF8D8_04 *)var_78, 2, (void (*)(RwInt32, RwInt32, RwInt32))sub_195C10, 0,
                           (RwInt32)&var_14->unk_88, 0);
            }
            break;
        }
        case 64:
            var_14->unk_90 = *(const RwUInt8 *)ebp_10->GetAs_RwChar_ptr();
            break;
        case 65:
        {
            const type_3DF8D8_04 *var_7C = (const type_3DF8D8_04 *)ebp_10->GetAs_RwChar_ptr();

            if (var_7C->unk_00 || var_7C->unk_04)
            {
                sub_198900((type_3DF8D8_04 *)var_7C, 2, (void (*)(RwInt32, RwInt32, RwInt32))sub_195C10, 0,
                           (RwInt32)&var_14->unk_94, 0);
            }
            break;
        }
        case 68:
            var_14->unk_4E0 = ebp_10->GetAs_RwInt32();
            break;
        case 69:
            var_14->unk_4E4 = ebp_10->GetAs_RwInt32();
            break;
        case 70:
            var_14->unk_4E8 = (RwReal)(RwUInt32)ebp_10->GetAs_RwReal();
            break;
        case 71:
            var_14->unk_4EC = (RwReal)(RwUInt32)ebp_10->GetAs_RwReal();
            break;
        case 72:
            var_14->unk_4F0 = (RwReal)(RwUInt32)ebp_10->GetAs_RwReal();
            break;
        case 73:
            var_14->unk_4F4 = (RwReal)(RwUInt32)ebp_10->GetAs_RwReal();
            break;
        case 74:
            var_14->unk_4F8 = (RwReal)(RwUInt32)ebp_10->GetAs_RwReal();
            break;
        case 75:
            var_14->unk_4FC = ebp_10->GetAs_RwInt32();
            break;
        case 76:
            var_14->unk_500 = ebp_10->GetAs_RwInt32();
            break;
        case 77:
            var_14->unk_504 = (RwReal)(RwUInt32)ebp_10->GetAs_RwReal();
            break;
        case 78:
            var_14->unk_508 = (RwReal)(RwUInt32)ebp_10->GetAs_RwReal();
            break;
        case 79:
            var_14->unk_50C = (RwReal)(RwUInt32)ebp_10->GetAs_RwReal();
            break;
        case 80:
            var_14->unk_510 = (RwReal)(RwUInt32)ebp_10->GetAs_RwReal();
            break;
        case 81:
            var_14->unk_514 = (RwReal)(RwUInt32)ebp_10->GetAs_RwReal();
            break;
        case 82:
            var_14->unk_19C = *(const RwV3d *)ebp_10->GetAs_RwChar_ptr();
            break;
        case 83:
        {
            RwInt32 var_80;
            type_10F710 *var_84;

            var_14->unk_1C0 = *(const RwV3d *)ebp_10->GetAs_RwChar_ptr();
            if (unk_24)
            {
                for (var_80 = 0; var_80 < 4; var_80++)
                {
                    var_84 = (type_10F710 *)sub_1745A0(var_80);
                    if (var_84 && var_84->unk_1A48[unk_20])
                    {
                        var_84->unk_1A48[unk_20]->unk_238 = var_14->unk_1C0;
                    }
                }
            }
            break;
        }
        case 87:
            var_14->unk_1A8 = *(const RwV3d *)ebp_10->GetAs_RwChar_ptr();
            break;
        case 88:
        {
            RwInt32 var_88;
            type_10F710 *var_8C;

            var_14->unk_1CC = *(const RwV3d *)ebp_10->GetAs_RwChar_ptr();
            if (unk_24)
            {
                for (var_88 = 0; var_88 < 4; var_88++)
                {
                    var_8C = (type_10F710 *)sub_1745A0(var_88);
                    if (var_8C && var_8C->unk_1A48[unk_20])
                    {
                        var_8C->unk_1A48[unk_20]->unk_244 = var_14->unk_1CC;
                    }
                }
            }
            break;
        }
        case 92:
            var_14->unk_1B4 = *(const RwV3d *)ebp_10->GetAs_RwChar_ptr();
            break;
        case 93:
        {
            RwInt32 var_90;
            type_10F710 *var_94;

            var_14->unk_1D8 = *(const RwV3d *)ebp_10->GetAs_RwChar_ptr();
            if (unk_24)
            {
                for (var_90 = 0; var_90 < 4; var_90++)
                {
                    var_94 = (type_10F710 *)sub_1745A0(var_90);
                    if (var_94 && var_94->unk_1A48[unk_20])
                    {
                        var_94->unk_1A48[unk_20]->unk_250 = var_14->unk_1D8;
                    }
                }
            }
            break;
        }
        case 84:
            var_14->unk_1E4 = *(const RwV3d *)ebp_10->GetAs_RwChar_ptr();
            break;
        case 89:
            var_14->unk_1F0 = *(const RwV3d *)ebp_10->GetAs_RwChar_ptr();
            break;
        case 94:
            var_14->unk_1FC = *(const RwV3d *)ebp_10->GetAs_RwChar_ptr();
            break;
        case 86:
            ebp_10->GetCommandData(var_14->unk_22C);
            break;
        case 91:
            ebp_10->GetCommandData(var_14->unk_230);
            break;
        case 96:
            ebp_10->GetCommandData(var_14->unk_234);
            break;
        case 85:
            var_14->unk_208 = *(const RwV3d *)ebp_10->GetAs_RwChar_ptr();
            break;
        case 90:
            var_14->unk_214 = *(const RwV3d *)ebp_10->GetAs_RwChar_ptr();
            break;
        case 95:
            var_14->unk_220 = *(const RwV3d *)ebp_10->GetAs_RwChar_ptr();
            break;
        case 97:
            ebp_10->GetCommandData(var_14->unk_488);
            break;
        case 98:
            ebp_10->GetCommandData(var_14->unk_48C);
            break;
        case 153:
            ebp_10->GetCommandData(var_14->unk_3A0);
            break;
        case 156:
        {
            RwReal var_98 = ebp_10->GetAs_RwReal();

            var_14->unk_410 = var_98 * 60.0f;
            break;
        }
        case 154:
            ebp_10->GetCommandData(var_14->unk_3A4);
            if (var_14->unk_3A4 < 1.0f)
            {
                var_14->unk_3A4 = 1.0f;
            }
            break;
        case 155:
        {
            RwReal var_9C = ebp_10->GetAs_RwReal();

            var_14->unk_3B0 = var_9C * 60.0f;
            break;
        }
        case 157:
            ebp_10->GetCommandData(var_14->unk_3BC);
            break;
        case 158:
            ebp_10->GetCommandData(var_14->unk_47C);
            break;
        case 159:
            var_14->unk_3C8 = *(const RwV3d *)ebp_10->GetAs_RwChar_ptr();
            break;
        case 160:
        {
            RwInt32 var_A4;
            type_10F710 *var_A0;

            var_14->unk_3EC = *(const RwV3d *)ebp_10->GetAs_RwChar_ptr();
            if (unk_24)
            {
                for (var_A4 = 0; var_A4 < 4; var_A4++)
                {
                    var_A0 = (type_10F710 *)sub_1745A0(var_A4);
                    if (var_A0 && var_A0->unk_1A48[unk_20])
                    {
                        var_A0->unk_1A48[unk_20]->unk_25C = var_14->unk_3EC;
                    }
                }
            }
            break;
        }
        case 161:
            var_14->unk_238 = *(const RwV3d *)ebp_10->GetAs_RwChar_ptr();
            break;
        case 162:
            var_14->unk_25C = *(const RwV3d *)ebp_10->GetAs_RwChar_ptr();
            break;
        case 163:
            ebp_10->GetCommandData(var_14->unk_280);
            break;
        case 164:
            ebp_10->GetCommandData(var_14->unk_3A8);
            if (var_14->unk_3A8 < 1.0f)
            {
                var_14->unk_3A8 = 1.0f;
            }
            break;
        case 165:
        {
            RwReal var_A8 = ebp_10->GetAs_RwReal();

            var_14->unk_3B4 = var_A8 * 30.0f;
            break;
        }
        case 166:
        {
            RwReal var_AC = ebp_10->GetAs_RwReal();

            var_14->unk_414 = var_AC * 60.0f;
            break;
        }
        case 167:
            ebp_10->GetCommandData(var_14->unk_3C0);
            break;
        case 168:
            ebp_10->GetCommandData(var_14->unk_480);
            break;
        case 169:
            var_14->unk_3D4 = *(const RwV3d *)ebp_10->GetAs_RwChar_ptr();
            break;
        case 170:
        {
            RwInt32 var_B4;
            type_10F710 *var_B0;

            var_14->unk_3F8 = *(const RwV3d *)ebp_10->GetAs_RwChar_ptr();
            if (unk_24)
            {
                for (var_B4 = 0; var_B4 < 4; var_B4++)
                {
                    var_B0 = (type_10F710 *)sub_1745A0(var_B4);
                    if (var_B0 && var_B0->unk_1A48[unk_20])
                    {
                        var_B0->unk_1A48[unk_20]->unk_268 = var_14->unk_3F8;
                    }
                }
            }
            break;
        }
        case 171:
            var_14->unk_244 = *(const RwV3d *)ebp_10->GetAs_RwChar_ptr();
            break;
        case 172:
            var_14->unk_268 = *(const RwV3d *)ebp_10->GetAs_RwChar_ptr();
            break;
        case 173:
            ebp_10->GetCommandData(var_14->unk_284);
            break;
        case 174:
            ebp_10->GetCommandData(var_14->unk_3AC);
            if (var_14->unk_3AC < 1.0f)
            {
                var_14->unk_3AC = 1.0f;
            }
            break;
        case 175:
        {
            RwReal var_B8 = ebp_10->GetAs_RwReal();

            var_14->unk_3B8 = var_B8 * 30.0f;
            break;
        }
        case 176:
        {
            RwReal var_BC = ebp_10->GetAs_RwReal();

            var_14->unk_418 = var_BC * 60.0f;
            break;
        }
        case 177:
            ebp_10->GetCommandData(var_14->unk_3C4);
            break;
        case 178:
            ebp_10->GetCommandData(var_14->unk_484);
            break;
        case 179:
            var_14->unk_3E0 = *(const RwV3d *)ebp_10->GetAs_RwChar_ptr();
            break;
        case 180:
        {
            RwInt32 var_C0;
            type_10F710 *var_C4;

            var_14->unk_404 = *(const RwV3d *)ebp_10->GetAs_RwChar_ptr();
            if (unk_24)
            {
                for (var_C0 = 0; var_C0 < 4; var_C0++)
                {
                    var_C4 = (type_10F710 *)sub_1745A0(var_C0);
                    if (var_C4 && var_C4->unk_1A48[unk_20])
                    {
                        var_C4->unk_1A48[unk_20]->unk_274 = var_14->unk_404;
                    }
                }
            }
            break;
        }
        case 181:
            var_14->unk_250 = *(const RwV3d *)ebp_10->GetAs_RwChar_ptr();
            break;
        case 182:
            var_14->unk_274 = *(const RwV3d *)ebp_10->GetAs_RwChar_ptr();
            break;
        case 183:
            ebp_10->GetCommandData(var_14->unk_288);
            break;
        case 99:
            ebp_10->GetCommandData(var_14->unk_2A8);
            break;
        case 100:
            ebp_10->GetCommandData(var_14->unk_2B4);
            break;
        case 101:
            ebp_10->GetCommandData(var_14->unk_2C0);
            break;
        case 102:
            ebp_10->GetCommandData(var_14->unk_2D8);
            break;
        case 103:
            ebp_10->GetCommandData(var_14->unk_2CC);
            break;
        case 104:
            ebp_10->GetCommandData(var_14->unk_2E4);
            break;
        case 105:
            ebp_10->GetCommandData(var_14->unk_2FC);
            break;
        case 106:
            ebp_10->GetCommandData(var_14->unk_2F0);
            break;
        case 107:
            ebp_10->GetCommandData(var_14->unk_308[0]);
            break;
        case 108:
            ebp_10->GetCommandData(var_14->unk_314[0]);
            break;
        case 109:
            ebp_10->GetCommandData(var_14->unk_340);
            break;
        case 110:
            ebp_10->GetCommandData(var_14->unk_34C);
            break;
        case 111:
            ebp_10->GetCommandData(var_14->unk_358);
            break;
        case 112:
            ebp_10->GetCommandData(var_14->unk_370);
            break;
        case 113:
            ebp_10->GetCommandData(var_14->unk_364);
            break;
        case 114:
            ebp_10->GetCommandData(var_14->unk_37C);
            break;
        case 115:
            ebp_10->GetCommandData(var_14->unk_394);
            break;
        case 116:
            ebp_10->GetCommandData(var_14->unk_388);
            break;
        case 117:
            ebp_10->GetCommandData(var_14->unk_2AC);
            break;
        case 118:
            ebp_10->GetCommandData(var_14->unk_2B8);
            break;
        case 119:
            ebp_10->GetCommandData(var_14->unk_2C4);
            break;
        case 120:
            ebp_10->GetCommandData(var_14->unk_2DC);
            break;
        case 121:
            ebp_10->GetCommandData(var_14->unk_2D0);
            break;
        case 122:
            ebp_10->GetCommandData(var_14->unk_2E8);
            break;
        case 123:
            ebp_10->GetCommandData(var_14->unk_300);
            break;
        case 124:
            ebp_10->GetCommandData(var_14->unk_2F4);
            break;
        case 125:
            ebp_10->GetCommandData(var_14->unk_308[1]);
            break;
        case 126:
            ebp_10->GetCommandData(var_14->unk_314[1]);
            break;
        case 127:
            ebp_10->GetCommandData(var_14->unk_344);
            break;
        case 128:
            ebp_10->GetCommandData(var_14->unk_350);
            break;
        case 129:
            ebp_10->GetCommandData(var_14->unk_35C);
            break;
        case 130:
            ebp_10->GetCommandData(var_14->unk_374);
            break;
        case 131:
            ebp_10->GetCommandData(var_14->unk_368);
            break;
        case 132:
            ebp_10->GetCommandData(var_14->unk_380);
            break;
        case 133:
            ebp_10->GetCommandData(var_14->unk_398);
            break;
        case 134:
            ebp_10->GetCommandData(var_14->unk_38C);
            break;
        case 135:
            ebp_10->GetCommandData(var_14->unk_2B0);
            break;
        case 136:
            ebp_10->GetCommandData(var_14->unk_2BC);
            break;
        case 137:
            ebp_10->GetCommandData(var_14->unk_2C8);
            break;
        case 138:
            ebp_10->GetCommandData(var_14->unk_2E0);
            break;
        case 139:
            ebp_10->GetCommandData(var_14->unk_2D4);
            break;
        case 140:
            ebp_10->GetCommandData(var_14->unk_2EC);
            break;
        case 141:
            ebp_10->GetCommandData(var_14->unk_304);
            break;
        case 142:
            ebp_10->GetCommandData(var_14->unk_2F8);
            break;
        case 143:
            ebp_10->GetCommandData(var_14->unk_308[2]);
            break;
        case 144:
            ebp_10->GetCommandData(var_14->unk_314[2]);
            break;
        case 145:
            ebp_10->GetCommandData(var_14->unk_348);
            break;
        case 146:
            ebp_10->GetCommandData(var_14->unk_354);
            break;
        case 147:
            ebp_10->GetCommandData(var_14->unk_360);
            break;
        case 148:
            ebp_10->GetCommandData(var_14->unk_378);
            break;
        case 149:
            ebp_10->GetCommandData(var_14->unk_36C);
            break;
        case 150:
            ebp_10->GetCommandData(var_14->unk_384);
            break;
        case 151:
            ebp_10->GetCommandData(var_14->unk_39C);
            break;
        case 152:
            ebp_10->GetCommandData(var_14->unk_390);
            break;
        case 184:
            var_14->unk_E4 = ebp_10->GetAs_RwReal() / 2.0f;
            break;
        case 185:
            var_14->unk_E8 = ebp_10->GetAs_RwReal() / 2.0f;
            break;
        case 186:
            var_14->unk_EC = (RwReal)(RwDouble)ebp_10->GetAs_RwReal();
            break;
        case 187:
            var_14->unk_F0 = (RwReal)(RwDouble)ebp_10->GetAs_RwReal();
            break;
        case 188:
            var_14->unk_F4 = (RwReal)(RwDouble)ebp_10->GetAs_RwReal();
            break;
        case 189:
            var_14->unk_F8 = (RwReal)(RwDouble)ebp_10->GetAs_RwReal();
            break;
        case 190:
            var_14->unk_FC = (RwReal)(RwDouble)ebp_10->GetAs_RwReal();
            break;
        case 191:
            var_14->unk_100 = (RwReal)(RwDouble)ebp_10->GetAs_RwReal();
            break;
        case 192:
            var_14->unk_104 = (RwReal)(RwDouble)ebp_10->GetAs_RwReal();
            break;
        case 193:
            var_14->unk_108 = (RwReal)(RwDouble)ebp_10->GetAs_RwReal();
            break;
        case 194:
            var_14->unk_10C = (RwReal)(RwDouble)ebp_10->GetAs_RwReal();
            break;
        case 195:
            var_14->unk_110 = (RwReal)(RwDouble)ebp_10->GetAs_RwReal();
            break;
        case 196:
            var_14->unk_114 = (RwReal)(RwDouble)ebp_10->GetAs_RwReal();
            break;
        case 197:
            var_14->unk_118 = (RwReal)(RwDouble)ebp_10->GetAs_RwReal();
            break;
        case 198:
            var_14->unk_11C = (RwReal)(RwDouble)ebp_10->GetAs_RwReal();
            break;
        case 199:
            var_14->unk_120 = (RwReal)(RwDouble)ebp_10->GetAs_RwReal();
            break;
        case 200:
            var_14->unk_124 = (RwReal)(RwDouble)ebp_10->GetAs_RwReal();
            break;
        case 201:
            var_14->unk_128 = (RwReal)(RwDouble)ebp_10->GetAs_RwReal();
            break;
        case 202:
            var_14->unk_12C = (RwReal)(RwDouble)ebp_10->GetAs_RwReal();
            break;
        case 203:
            var_14->unk_130 = (RwReal)(RwDouble)ebp_10->GetAs_RwReal();
            break;
        case 204:
            var_14->unk_134 = (RwReal)(RwDouble)ebp_10->GetAs_RwReal();
            break;
        case 205:
            var_14->unk_138 = (RwReal)(RwDouble)ebp_10->GetAs_RwReal();
            break;
        case 206:
            var_14->unk_13C = (RwReal)(RwDouble)ebp_10->GetAs_RwReal();
            break;
        case 207:
            var_14->unk_140 = (RwReal)(RwDouble)ebp_10->GetAs_RwReal();
            break;
        case 208:
            var_14->unk_144 = (RwReal)(RwDouble)ebp_10->GetAs_RwReal();
            break;
        case 209:
            var_14->unk_148 = (bool)ebp_10->GetAs_RwInt32();
            break;
        case 210:
            var_14->unk_14C = (RwUInt8)ebp_10->GetAs_RwInt32();
            break;
        case 211:
            var_14->unk_14D = (RwUInt8)ebp_10->GetAs_RwInt32();
            // (falls through)
        case 212:
            var_14->unk_150 = (RwReal)(RwDouble)ebp_10->GetAs_RwReal();
            break;
        case 213:
            var_14->unk_154 = (RwReal)(RwDouble)ebp_10->GetAs_RwReal();
            break;
        case 214:
            var_14->unk_158 = (RwReal)(RwDouble)ebp_10->GetAs_RwReal();
            break;
        case 215:
            var_14->unk_15C = (RwReal)(RwDouble)ebp_10->GetAs_RwReal();
            break;
        case 218:
            var_14->unk_160 = (RwReal)(RwDouble)ebp_10->GetAs_RwReal();
            break;
        case 219:
            var_14->unk_164 = (RwReal)(RwDouble)ebp_10->GetAs_RwReal();
            break;
        case 23:
            var_14->unk_518 = ebp_10->GetAs_RwInt32();
            break;
        case 24:
            if (ebp_10->GetAs_RwChar_ptr())
            {
                type_3DF8D8_04 var_CC = *(const type_3DF8D8_04 *)ebp_10->GetAs_RwChar_ptr();

                if (var_CC.unk_00 || var_CC.unk_04)
                {
                    sub_198900((type_3DF8D8_04 *)&var_CC, 1, (void (*)(RwInt32, RwInt32, RwInt32))sub_18F8B0, 0, (RwInt32)&var_14->unk_51C, 0);
                }
            }
            break;
        case 25:
            var_14->unk_520 = ebp_10->GetAs_RwInt32();
            break;
        case 26:
            var_14->unk_524 = ebp_10->GetAs_RwReal() * 60.0f;
            break;
        case 27:
            var_14->unk_528 = ebp_10->GetAs_RwInt32();
            break;
        case 28:
            var_14->unk_52C = ebp_10->GetAs_RwInt32();
            break;
        case 29:
            var_14->unk_530 = ebp_10->GetAs_RwInt32();
            break;
        case 30:
            if (ebp_10->GetAs_RwChar_ptr())
            {
                type_3DF8D8_04 var_D4 = *(const type_3DF8D8_04 *)ebp_10->GetAs_RwChar_ptr();

                if (var_D4.unk_00 || var_D4.unk_04)
                {
                    sub_198900((type_3DF8D8_04 *)&var_D4, 1, (void (*)(RwInt32, RwInt32, RwInt32))sub_18F8B0, 0, (RwInt32)&var_14->unk_534, 0);
                }
            }
            break;
        case 31:
            var_14->unk_538 = ebp_10->GetAs_RwInt32();
            break;
        case 32:
            var_14->unk_53C = ebp_10->GetAs_RwReal() * 60.0f;
            break;
        case 33:
            var_14->unk_540 = ebp_10->GetAs_RwInt32();
            break;
        case 34:
            var_14->unk_544 = ebp_10->GetAs_RwInt32();
            break;
        case 216:
            if (ebp_10->GetAs_RwChar_ptr())
            {
                type_3DF8D8_04 var_DC = *(const type_3DF8D8_04 *)ebp_10->GetAs_RwChar_ptr();

                if (var_DC.unk_00 || var_DC.unk_04)
                {
                    sub_198900((type_3DF8D8_04 *)&var_DC, 1, (void (*)(RwInt32, RwInt32, RwInt32))sub_18F8B0, 0, (RwInt32)&var_14->unk_548, 0);
                }
            }
            break;
        case 217:
            if (ebp_10->GetAs_RwChar_ptr())
            {
                type_3DF8D8_04 var_E4 = *(const type_3DF8D8_04 *)ebp_10->GetAs_RwChar_ptr();

                if (var_E4.unk_00 || var_E4.unk_04)
                {
                    sub_198900((type_3DF8D8_04 *)&var_E4, 1, (void (*)(RwInt32, RwInt32, RwInt32))sub_18F8B0, 0, (RwInt32)&var_14->unk_54C, 0);
                }
            }
            break;
        }
        ++ebp_10;
    }
}

// On dword_4B8750: the players have their weapons (unk_24), once.
// match: ?HandleEvents@CWeaponBehavior@@UAEXAAVCMsg@RWS@@@Z @ 0x000C47F0
// sp-match: ?HandleEvents@CWeaponBehavior@@UAEXAAVCMsg@RWS@@@Z @ 0x00096940
void CWeaponBehavior::HandleEvents(RWS::CMsg &pMsg)
{
    if (pMsg.Id.p_msgrec == dword_4B8750.p_msgrec)
    {
        unk_24 = 1;
        UnLinkMsg(dword_4B8750);
    }
}

// match: ?MakeNew@CExplosiveBehavior@@SAPAVCAttributeHandler@RWS@@ABVCAttributePacket@3@@Z @ 0x000C4830
// sp-match: ?MakeNew@CExplosiveBehavior@@SAPAVCAttributeHandler@RWS@@ABVCAttributePacket@3@@Z @ 0x00095FC0
// (its EH handler is CWeaponBehavior's,
// folded by /OPT:ICF.)
RWS_DEFINE_MAKENEW(CExplosiveBehavior)

// match: ??0CExplosiveBehavior@@QAE@ABVCAttributePacket@RWS@@@Z @ 0x000C48B0
// sp-match: ??0CExplosiveBehavior@@QAE@ABVCAttributePacket@RWS@@@Z @ 0x00093900
CExplosiveBehavior::CExplosiveBehavior(const RWS::CAttributePacket &attr) : CWeaponBehavior(attr)
{
}

// match: ??_GCExplosiveBehavior@@UAEPAXI@Z @ 0x000C48E0
// sp-match: ??_GCExplosiveBehavior@@UAEPAXI@Z @ 0x00095A30

// match: ??1CExplosiveBehavior@@UAE@XZ @ 0x000C4900
// sp-match: ??1CExplosiveBehavior@@UAE@XZ @ 0x00093920
CExplosiveBehavior::~CExplosiveBehavior()
{
}

// match: ?HandleAttributes@CExplosiveBehavior@@UAEXABVCAttributePacket@RWS@@@Z @ 0x000C4930
// sp-match: ?HandleAttributes@CExplosiveBehavior@@UAEXABVCAttributePacket@RWS@@@Z @ 0x00095A40
void CExplosiveBehavior::HandleAttributes(const RWS::CAttributePacket &attr)
{
    type_4C19C0 *local_C;

    CWeaponBehavior::HandleAttributes(attr);
    RWS::CAttributeCommandIterator attrIt(attr, RWS_CLASSID_OF(CExplosiveBehavior));
    local_C = sub_119B70(unk_20);
    while (!attrIt.IsFinished())
    {
        switch (attrIt->GetCommandId())
        {
        case 2:
            local_C->unk_D0 = attrIt->GetAs_RwReal() * 100.0f;
            break;
        case 0:
            local_C->unk_4B4 = attrIt->GetAs_RwReal() * 60.0f;
            break;
        case 1:
            local_C->unk_4CC = attrIt->GetAs_RwReal() * 100.0f;
            break;
        case 3:
            local_C->unk_4BC = attrIt->GetAs_RwReal() * 100.0f;
            break;
        case 4:
            local_C->unk_4C4 = attrIt->GetAs_RwInt32();
            break;
        case 5:
            local_C->unk_4C0 = attrIt->GetAs_RwReal() * 100.0f;
            break;
        case 6:
            local_C->unk_4C8 = attrIt->GetAs_RwInt32();
            break;
        case 7:
            local_C->unk_9C = attrIt->GetAs_RwReal() * 100.0f;
            break;
        case 8:
            local_C->unk_98 = attrIt->GetAs_RwInt32();
            break;
        case 9:
            local_C->unk_A4 = attrIt->GetAs_RwInt32();
            break;
        case 10:
            local_C->unk_A0 = attrIt->GetAs_RwInt32();
            break;
        case 11:
            local_C->unk_A8 = attrIt->GetAs_RwReal() * 100.0f;
            break;
        case 12:
            local_C->unk_AC = attrIt->GetAs_RwInt32();
            break;
        }
        ++attrIt;
    }
}

// match: ?HandleEvents@CExplosiveBehavior@@UAEXAAVCMsg@RWS@@@Z @ 0x000C4BF0
// sp-match: ?HandleEvents@CExplosiveBehavior@@UAEXAAVCMsg@RWS@@@Z @ 0x00093940
void CExplosiveBehavior::HandleEvents(RWS::CMsg &pMsg)
{
    CWeaponBehavior::HandleEvents(pMsg);
}

// match: ?MakeNew@CTankBehavior@@SAPAVCAttributeHandler@RWS@@ABVCAttributePacket@3@@Z @ 0x000C4C10
// sp-match: ?MakeNew@CTankBehavior@@SAPAVCAttributeHandler@RWS@@ABVCAttributePacket@3@@Z @ 0x00096020
// (its EH handler is CWeaponBehavior's,
// folded by /OPT:ICF.)
RWS_DEFINE_MAKENEW(CTankBehavior)

// match: ??0CTankBehavior@@QAE@ABVCAttributePacket@RWS@@@Z @ 0x000C4C90
// sp-match: ??0CTankBehavior@@QAE@ABVCAttributePacket@RWS@@@Z @ 0x00093950
CTankBehavior::CTankBehavior(const RWS::CAttributePacket &attr) : CExplosiveBehavior(attr)
{
}

// match: ??_GCTankBehavior@@UAEPAXI@Z @ 0x000C4CC0
// sp-match: ??_GCTankBehavior@@UAEPAXI@Z @ 0x00095C40

// match: ??1CTankBehavior@@UAE@XZ @ 0x000C4CE0
// sp-match: ??1CTankBehavior@@UAE@XZ @ 0x00093970
CTankBehavior::~CTankBehavior()
{
}

// match: ?HandleAttributes@CTankBehavior@@UAEXABVCAttributePacket@RWS@@@Z @ 0x000C4D10
// sp-match: ?HandleAttributes@CTankBehavior@@UAEXABVCAttributePacket@RWS@@@Z @ 0x00095C50
void CTankBehavior::HandleAttributes(const RWS::CAttributePacket &attr)
{
    CExplosiveBehavior::HandleAttributes(attr);
}

// (Folded by /OPT:ICF into CGrenadeBehavior's, sub_C5310.)
void CTankBehavior::HandleEvents(RWS::CMsg &pMsg)
{
    CExplosiveBehavior::HandleEvents(pMsg);
}

// match: ?MakeNew@CAntiTankBehavior@@SAPAVCAttributeHandler@RWS@@ABVCAttributePacket@3@@Z @ 0x000C4D30
// sp-match: ?MakeNew@CAntiTankBehavior@@SAPAVCAttributeHandler@RWS@@ABVCAttributePacket@3@@Z @ 0x00096080
// (its EH handler is CWeaponBehavior's,
// folded by /OPT:ICF.)
RWS_DEFINE_MAKENEW(CAntiTankBehavior)

// match: ??0CAntiTankBehavior@@QAE@ABVCAttributePacket@RWS@@@Z @ 0x000C4DB0
// sp-match: ??0CAntiTankBehavior@@QAE@ABVCAttributePacket@RWS@@@Z @ 0x000939A0
CAntiTankBehavior::CAntiTankBehavior(const RWS::CAttributePacket &attr) : CExplosiveBehavior(attr)
{
}

// match: ??_GCAntiTankBehavior@@UAEPAXI@Z @ 0x000C4DE0
// sp-match: ??_GCAntiTankBehavior@@UAEPAXI@Z @ 0x00095C60

// match: ??1CAntiTankBehavior@@UAE@XZ @ 0x000C4E00
// sp-match: ??1CAntiTankBehavior@@UAE@XZ @ 0x000939C0
CAntiTankBehavior::~CAntiTankBehavior()
{
}

// Command 0 names a value (a kind 1) whose number goes to unk_4DC.
// match: ?HandleAttributes@CAntiTankBehavior@@UAEXABVCAttributePacket@RWS@@@Z @ 0x000C4E30
// sp-match: ?HandleAttributes@CAntiTankBehavior@@UAEXABVCAttributePacket@RWS@@@Z @ 0x00095C70
void CAntiTankBehavior::HandleAttributes(const RWS::CAttributePacket &attr)
{
    type_4C19C0 *local_C;

    CExplosiveBehavior::HandleAttributes(attr);
    RWS::CAttributeCommandIterator attrIt(attr, RWS_CLASSID_OF(CAntiTankBehavior));
    local_C = sub_119B70(unk_20);
    while (!attrIt.IsFinished())
    {
        switch (attrIt->GetCommandId())
        {
        case 0:
            if (attrIt->GetAs_RwChar_ptr())
            {
                type_3DF8D8_04 var_14 = *(const type_3DF8D8_04 *)attrIt->GetAs_RwChar_ptr();

                if (var_14.unk_00 || var_14.unk_04)
                {
                    sub_198900((type_3DF8D8_04 *)&var_14, 1, (void (*)(RwInt32, RwInt32, RwInt32))sub_18F8B0, 0, (RwInt32)&local_C->unk_4DC, 0);
                }
            }
            break;
        }
        ++attrIt;
    }
}

// (Folded by /OPT:ICF into CGrenadeBehavior's, sub_C5310.)
void CAntiTankBehavior::HandleEvents(RWS::CMsg &pMsg)
{
    CExplosiveBehavior::HandleEvents(pMsg);
}

// match: ?MakeNew@CGrenadeBehavior@@SAPAVCAttributeHandler@RWS@@ABVCAttributePacket@3@@Z @ 0x000C4F10
// sp-match: ?MakeNew@CGrenadeBehavior@@SAPAVCAttributeHandler@RWS@@ABVCAttributePacket@3@@Z @ 0x000960E0
// (its EH handler is CWeaponBehavior's,
// folded by /OPT:ICF.)
RWS_DEFINE_MAKENEW(CGrenadeBehavior)

// match: ??0CGrenadeBehavior@@QAE@ABVCAttributePacket@RWS@@@Z @ 0x000C4F90
// sp-match: ??0CGrenadeBehavior@@QAE@ABVCAttributePacket@RWS@@@Z @ 0x000939E0
CGrenadeBehavior::CGrenadeBehavior(const RWS::CAttributePacket &attr) : CExplosiveBehavior(attr)
{
    unk_20 = 1;
}

// match: ??_GCGrenadeBehavior@@UAEPAXI@Z @ 0x000C4FD0
// sp-match: ??_GCGrenadeBehavior@@UAEPAXI@Z @ 0x00095D30

// match: ??1CGrenadeBehavior@@UAE@XZ @ 0x000C4FF0
// sp-match: ??1CGrenadeBehavior@@UAE@XZ @ 0x00093A10
CGrenadeBehavior::~CGrenadeBehavior()
{
}

// match: ?HandleAttributes@CGrenadeBehavior@@UAEXABVCAttributePacket@RWS@@@Z @ 0x000C5020
// sp-match: ?HandleAttributes@CGrenadeBehavior@@UAEXABVCAttributePacket@RWS@@@Z @ 0x00095D40
void CGrenadeBehavior::HandleAttributes(const RWS::CAttributePacket &attr)
{
    type_4C19C0 *local_C;

    CExplosiveBehavior::HandleAttributes(attr);
    RWS::CAttributeCommandIterator attrIt(attr, RWS_CLASSID_OF(CGrenadeBehavior));
    local_C = sub_119B70(unk_20);
    while (!attrIt.IsFinished())
    {
        switch (attrIt->GetCommandId())
        {
        case 0:
            local_C->unk_490 = attrIt->GetAs_RwReal() * 10.0f;
            break;
        case 4:
            local_C->unk_4AC = attrIt->GetAs_RwInt32();
            break;
        case 5:
            local_C->unk_4B0 = attrIt->GetAs_RwInt32();
            break;
        case 1:
            local_C->unk_494 = attrIt->GetAs_RwReal() * 10.0f;
            break;
        case 2:
            local_C->unk_498 = attrIt->GetAs_RwReal() / 100.0f;
            break;
        case 3:
            local_C->unk_49C = attrIt->GetAs_RwReal() / 100.0f;
            break;
        case 6:
            local_C->unk_4D8 = -attrIt->GetAs_RwReal();
            break;
        case 7:
        {
            const type_3DF8D8_04 *var_10 = (const type_3DF8D8_04 *)attrIt->GetAs_RwChar_ptr();

            if (var_10->unk_00 || var_10->unk_04)
            {
                sub_198900((type_3DF8D8_04 *)var_10, 2, (void (*)(RwInt32, RwInt32, RwInt32))sub_195C10, 0, (RwInt32)&local_C->unk_4A0, 0);
            }
            break;
        }
        case 8:
        {
            const type_3DF8D8_04 *var_14 = (const type_3DF8D8_04 *)attrIt->GetAs_RwChar_ptr();

            if (var_14->unk_00 || var_14->unk_04)
            {
                sub_198900((type_3DF8D8_04 *)var_14, 2, (void (*)(RwInt32, RwInt32, RwInt32))sub_195C10, 0, (RwInt32)&local_C->unk_4A4, 0);
            }
            break;
        }
        case 9:
        {
            const type_3DF8D8_04 *var_18 = (const type_3DF8D8_04 *)attrIt->GetAs_RwChar_ptr();

            if (var_18->unk_00 || var_18->unk_04)
            {
                sub_198900((type_3DF8D8_04 *)var_18, 2, (void (*)(RwInt32, RwInt32, RwInt32))sub_195C10, 0, (RwInt32)&local_C->unk_4A8, 0);
            }
            break;
        }
        case 10:
            attrIt->GetCommandData(local_C->unk_4D0);
            break;
        case 11:
            attrIt->GetCommandData(local_C->unk_4D4);
            break;
        }
        ++attrIt;
    }
}

// CTankBehavior's and CAntiTankBehavior's, identical, are folded into this
// one by /OPT:ICF.
// match: ?HandleEvents@CGrenadeBehavior@@UAEXAAVCMsg@RWS@@@Z @ 0x000C5310
// sp-match: ?HandleEvents@CGrenadeBehavior@@UAEXAAVCMsg@RWS@@@Z @ 0x00093990
void CGrenadeBehavior::HandleEvents(RWS::CMsg &pMsg)
{
    CExplosiveBehavior::HandleEvents(pMsg);
}

// match: ??_ECTankBehavior@@WBI@AEPAXI@Z @ 0x000C5330
// sp-match: ??_ECTankBehavior@@WBI@AEPAXI@Z @ 0x00093A30

// match: ??_ECAntiTankBehavior@@WBI@AEPAXI@Z @ 0x000C5340
// sp-match: ??_ECAntiTankBehavior@@WBI@AEPAXI@Z @ 0x00093A40

// match: ??_ECGrenadeBehavior@@WBI@AEPAXI@Z @ 0x000C5350
// sp-match: ??_ECGrenadeBehavior@@WBI@AEPAXI@Z @ 0x00093A60

// match: ??_ECWeaponBehavior@@WBI@AEPAXI@Z @ 0x000C5360
// sp-match: ??_ECWeaponBehavior@@WBI@AEPAXI@Z @ 0x00093A50

// match: ??_ECExplosiveBehavior@@WBI@AEPAXI@Z @ 0x000C5370
// sp-match: ??_ECExplosiveBehavior@@WBI@AEPAXI@Z @ 0x00093A70
