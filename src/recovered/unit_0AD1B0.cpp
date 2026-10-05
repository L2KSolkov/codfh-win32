// ProjectileGeneratorTrigger: its MakeNew, constructor, destructor and
// handlers. Its original file name is not in the image, so it is named for
// its start address.

#include <math.h>
#include <string.h>

#include "rw/ostypes.h"
#include "rws/cattributehandler.h"
#include "rws/cclassfactory.h"
#include "game/data.h"
#include "types/ProjectileGeneratorTrigger.h"
#include "types/type_72810.h"
#include "game/pooledconsts.h"
#include "game/frames.h"

// Its data definitions (PLAN M5), in the image's address order.
// 0x003D6284
extern const RwReal flt_3D6284 = 16.666666f;
// End of its data definitions.


RWS_IMPLEMENT_CLASSID(ProjectileGeneratorTrigger);
RWS_REGISTERCLASS(ProjectileGeneratorTrigger);
// Its data (PLAN M5): literals, constants and tables where the image has them.
// match: ??_C@_0BL@EOAELLGC@ProjectileGeneratorTrigger?$AA@ @ 0x003D6268
// match: ?flt_3D6284@@3MB @ 0x003D6284
// match: ??_7ProjectileGeneratorTrigger@@6BCEventHandler@RWS@@@ @ 0x003D6288
// match: ??_7ProjectileGeneratorTrigger@@6BCAttributeHandler@RWS@@@ @ 0x003D6290
// match: ??_C@_0CN@KFFDLLPN@GameWeapons?$CLWeapons?$CLArtillery?$CLPr@ @ 0x003D62C0
// match: ??_C@_0CN@GGLJGNGH@COD_EnemyWeaponProjectiles?$CLPanze@ @ 0x003D62F0
// match: ??_C@_0CI@FLOHMPNN@GameWeapons?$CLWeapons?$CLTank?$CLProject@ @ 0x003D6320
// match: __ehhandler$?MakeNew@ProjectileGeneratorTrigger@@SAPAVCAttributeHandler@RWS@@ABVCAttributePacket@3@@Z>1>8 @ 0x0041BF24
// match: __ehhandler$?MakeNew@ProjectileGeneratorTrigger@@SAPAVCAttributeHandler@RWS@@ABVCAttributePacket@3@@Z>1 @ 0x0041BF2C
// match: .CRT$XCU+0 @ 0x00426F3C
// match: ?pProjectileGeneratorTriggerClassID@ProjectileGeneratorTrigger@@2PBDB @ 0x00429180

// match: _$E2 @ 0x0030A900
// match: _$E3 @ 0x0030E0D0

// (The class factory's registration and its exit thunk.)

// match: ?MakeNew@ProjectileGeneratorTrigger@@SAPAVCAttributeHandler@RWS@@ABVCAttributePacket@3@@Z @ 0x000AD1B0
// match: __ehhandler$?MakeNew@ProjectileGeneratorTrigger@@SAPAVCAttributeHandler@RWS@@ABVCAttributePacket@3@@Z-0xF @ 0x00300150
// match: __ehhandler$?MakeNew@ProjectileGeneratorTrigger@@SAPAVCAttributeHandler@RWS@@ABVCAttributePacket@3@@Z @ 0x0030015F
RWS_DEFINE_MAKENEW(ProjectileGeneratorTrigger)

// match: ??0ProjectileGeneratorTrigger@@QAE@ABVCAttributePacket@RWS@@@Z @ 0x000AD230
ProjectileGeneratorTrigger::ProjectileGeneratorTrigger(const RWS::CAttributePacket &attr) : Trigger(attr)
{
    unk_DC = 0;
    unk_104 = 100;
    unk_E0 = 0;
    unk_E4 = 1;
    unk_100 = 0;
    unk_108 = 0;
    unk_10C = 0;
    unk_114 = 0;
    unk_120 = 0;
    unk_124 = 0;
    unk_128 = 0;
    unk_12C = 0;
    unk_130 = 0;
    unk_134 = 0;
    unk_138 = 0;
    unk_118 = 0.15f;
    unk_11C = seconds_to_frames(5.0f);
    unk_13C = 0;
    unk_140.unk_00 = 0;
    unk_140.unk_04 = 0;
    unk_148.unk_00 = 0;
    unk_148.unk_04 = 0;
    unk_150 = 0;
    unk_110 = 1;
    unk_154 = 0;
    unk_158 = 0;
    unk_160 = 0;
    unk_164 = 0;
    unk_168 = 0;
    unk_16C = 0;
    unk_170 = 0;
    unk_174 = 0;
    unk_178 = 0;
    unk_17C = 0;
    unk_180 = 0;
    unk_184 = 0;
    unk_188 = 0;
    unk_18C = 0;
    unk_194 = 0;
    unk_198 = 0;
    unk_19C = 0;
    unk_1CC = 0;
    unk_1D0.unk_00 = 0;
    unk_1D0.unk_04 = 0;
    unk_1D8 = 0;
    unk_1DC = 0;
    unk_1E0 = 0;
    unk_1E4 = 0;
    unk_1E8 = 0;
    unk_1EC = 0;
    unk_1F0 = 1;
    unk_1F4 = 1;
    unk_1F8 = 1;
    unk_218 = 0;
    unk_1FC = 0;
    unk_200 = 1;
    unk_204 = 1.0f;
    unk_208 = 0;
    unk_20C = 0;
    unk_210 = 0;
    unk_214 = 15.0f;
    unk_15C = 0;
    unk_224 = 0;
    unk_21C = 0;
    unk_220 = 0;
    unk_228 = stru_429E54;
    memset(&unk_244, 0, 0x30);
}

// match: ??_GProjectileGeneratorTrigger@@UAEPAXI@Z @ 0x000AD6E0

// match: ??1ProjectileGeneratorTrigger@@UAE@XZ @ 0x000AD700
// (Defined in the class, in ProjectileGeneratorTrigger.h.)

// match: ?HandleAttributes@ProjectileGeneratorTrigger@@UAEXABVCAttributePacket@RWS@@@Z @ 0x000AD730
void ProjectileGeneratorTrigger::HandleAttributes(const RWS::CAttributePacket &attr)
{
    Trigger::HandleAttributes(attr);
    RWS::CAttributeCommandIterator attrIt(attr, RWS_CLASSID_OF(ProjectileGeneratorTrigger));
    while (!attrIt.IsFinished())
    {
        switch (attrIt->GetCommandId())
        {
        case 0:
            unk_DC = attrIt->GetAs_RwInt32();
            if (unk_DC == 0)
            {
                unk_DC = 2;
            }
            else if (unk_DC == 1)
            {
                unk_DC = 1;
            }
            break;
        case 1:
            unk_E0 = attrIt->GetAs_RwInt32();
            break;
        case 10:
            unk_E4 = attrIt->GetAs_RwInt32();
            break;
        case 2:
        {
            type_3DF8D8_04 var_10 = *(const type_3DF8D8_04 *)attrIt->GetAs_RwChar_ptr();

            if (var_10.unk_00 || var_10.unk_04)
            {
                unk_C0 = var_10;
            }
            break;
        }
        case 3:
            unk_C8 = attrIt->GetAs_RwInt32();
            break;
        case 4:
        {
            type_3DF8D8_04 var_18 = *(const type_3DF8D8_04 *)attrIt->GetAs_RwChar_ptr();

            if (var_18.unk_00 || var_18.unk_04)
            {
                unk_CC = var_18;
            }
            break;
        }
        case 5:
            unk_110 = attrIt->GetAs_RwInt32();
            break;
        case 6:
        {
            type_3DF8D8_04 var_20 = *(const type_3DF8D8_04 *)attrIt->GetAs_RwChar_ptr();

            if (var_20.unk_00 || var_20.unk_04)
            {
                unk_D4 = var_20;
            }
            break;
        }
        case 11:
        {
            type_3DF8D8_04 var_28 = *(const type_3DF8D8_04 *)attrIt->GetAs_RwChar_ptr();

            if (var_28.unk_00 || var_28.unk_04)
            {
                unk_F0 = var_28;
            }
            break;
        }
        case 12:
            unk_F8 = attrIt->GetAs_RwInt32();
            break;
        case 14:
            unk_FC = attrIt->GetAs_RwInt32();
            break;
        case 13:
        {
            type_3DF8D8_04 var_30 = *(const type_3DF8D8_04 *)attrIt->GetAs_RwChar_ptr();

            if (var_30.unk_00 || var_30.unk_04)
            {
                unk_E8 = var_30;
            }
            break;
        }
        case 15:
            unk_100 = attrIt->GetAs_RwInt32();
            break;
        case 47:
            unk_108 = attrIt->GetAs_RwInt32();
            break;
        case 48:
            unk_10C = attrIt->GetAs_RwInt32();
            break;
        case 16:
            unk_114 = attrIt->GetAs_RwInt32();
            break;
        case 49:
            unk_120 = attrIt->GetAs_RwInt32();
            break;
        case 50:
            unk_124 = attrIt->GetAs_RwInt32();
            break;
        case 17:
            unk_128 = attrIt->GetAs_RwInt32();
            break;
        case 54:
        {
            RwReal var_34 = attrIt->GetAs_RwReal();

            var_34 *= 0.5f;
            unk_12C = var_34;
            break;
        }
        case 55:
        {
            RwReal var_38 = attrIt->GetAs_RwReal();

            var_38 *= 0.5f;
            unk_130 = var_38;
            break;
        }
        case 56:
        {
            RwReal var_3C = attrIt->GetAs_RwReal();

            unk_134 = (RwReal)cos(var_3C *= 0.0087266462f);
            break;
        }
        case 57:
        {
            RwReal var_40 = attrIt->GetAs_RwReal();

            unk_138 = (RwReal)cos(var_40 *= 0.0087266462f);
            break;
        }
        case 21:
            unk_13C = attrIt->GetAs_RwInt32();
            break;
        case 19:
            if (attrIt->GetAs_RwChar_ptr())
            {
                unk_140 = *(const type_3DF8D8_04 *)attrIt->GetAs_RwChar_ptr();
            }
            break;
        case 20:
            if (attrIt->GetAs_RwChar_ptr())
            {
                unk_148 = *(const type_3DF8D8_04 *)attrIt->GetAs_RwChar_ptr();
            }
            break;
        case 18:
            unk_150 = attrIt->GetAs_RwInt32();
            break;
        case 23:
            unk_154 = attrIt->GetAs_RwInt32();
            break;
        case 24:
            unk_158 = attrIt->GetAs_RwInt32();
            break;
        case 72:
            unk_160 = attrIt->GetAs_RwReal() * 100.0f;
            break;
        case 73:
            unk_164 = attrIt->GetAs_RwInt32();
            break;
        case 74:
            unk_168 = attrIt->GetAs_RwInt32();
            break;
        case 75:
            unk_16C = attrIt->GetAs_RwReal() * 100.0f;
            break;
        case 76:
            unk_170 = attrIt->GetAs_RwInt32();
            break;
        case 77:
            unk_174 = attrIt->GetAs_RwInt32();
            break;
        case 78:
            unk_178 = attrIt->GetAs_RwReal() * 100.0f;
            break;
        case 79:
            unk_17C = attrIt->GetAs_RwInt32();
            break;
        case 80:
            unk_180 = attrIt->GetAs_RwInt32();
            break;
        case 51:
            unk_184 = attrIt->GetAs_RwReal() * 100.0f;
            break;
        case 52:
            unk_188 = attrIt->GetAs_RwReal() * 100.0f;
            break;
        case 59:
            unk_194 = attrIt->GetAs_RwReal() * 100.0f;
            break;
        case 60:
            unk_198 = attrIt->GetAs_RwReal() * 60.0f;
            break;
        case 61:
            unk_1B0 = attrIt->GetAs_RwReal() * 100.0f;
            break;
        case 62:
            unk_1A0 = attrIt->GetAs_RwReal() * 100.0f;
            break;
        case 63:
            unk_1A8 = attrIt->GetAs_RwInt32();
            break;
        case 64:
            unk_1A4 = attrIt->GetAs_RwReal() * 100.0f;
            break;
        case 65:
            unk_1AC = attrIt->GetAs_RwInt32();
            break;
        case 66:
            unk_1B4 = attrIt->GetAs_RwReal() * 100.0f;
            break;
        case 67:
            unk_1B8 = attrIt->GetAs_RwInt32();
            break;
        case 68:
            unk_1BC = attrIt->GetAs_RwInt32();
            break;
        case 69:
            unk_1C0 = attrIt->GetAs_RwInt32();
            break;
        case 70:
            unk_1C4 = attrIt->GetAs_RwReal() * 100.0f;
            break;
        case 71:
            unk_1C8 = attrIt->GetAs_RwInt32();
            break;
        case 25:
            unk_104 = attrIt->GetAs_RwInt32();
            break;
        case 53:
        {
            RwReal var_44 = attrIt->GetAs_RwReal();

            var_44 *= 0.5f;
            unk_18C = var_44;
            break;
        }
        case 22:
        {
            RwInt32 var_48 = attrIt->GetAs_RwInt32();

            sub_AF020(var_48);
            break;
        }
        case 98:
            unk_218 = attrIt->GetAs_RwInt32();
            break;
        case 58:
            unk_190 = attrIt->GetAs_RwInt32();
            break;
        case 81:
            unk_1FC = attrIt->GetAs_RwInt32();
            break;
        case 84:
            unk_200 = attrIt->GetAs_RwInt32();
            break;
        case 85:
            unk_204 = -attrIt->GetAs_RwReal();
            break;
        case 86:
            unk_210 = attrIt->GetAs_RwInt32();
            break;
        case 87:
            unk_208 = attrIt->GetAs_RwInt32();
            break;
        case 88:
            unk_20C = attrIt->GetAs_RwInt32();
            break;
        case 89:
            unk_214 = attrIt->GetAs_RwReal();
            break;
        case 90:
            unk_15C = attrIt->GetAs_RwReal() * 100.0f;
            break;
        case 28:
            if (attrIt->GetAs_RwChar_ptr())
            {
                Trigger_key var_50 = *(const Trigger_key *)attrIt->GetAs_RwChar_ptr();

                if (var_50.unk_00 || var_50.unk_04)
                {
                    sub_198900((type_3DF8D8_04 *)&var_50, 1, (void (*)(RwInt32, RwInt32, RwInt32))sub_18F8B0, 0, (RwInt32)&unk_1D8, 0);
                }
            }
            break;
        case 31:
            if (attrIt->GetAs_RwChar_ptr())
            {
                Trigger_key var_58 = *(const Trigger_key *)attrIt->GetAs_RwChar_ptr();

                if (var_58.unk_00 || var_58.unk_04)
                {
                    sub_198900((type_3DF8D8_04 *)&var_58, 1, (void (*)(RwInt32, RwInt32, RwInt32))sub_18F8B0, 0, (RwInt32)&unk_1DC, 0);
                }
            }
            break;
        case 34:
            if (attrIt->GetAs_RwChar_ptr())
            {
                Trigger_key var_60 = *(const Trigger_key *)attrIt->GetAs_RwChar_ptr();

                if (var_60.unk_00 || var_60.unk_04)
                {
                    sub_198900((type_3DF8D8_04 *)&var_60, 1, (void (*)(RwInt32, RwInt32, RwInt32))sub_18F8B0, 0, (RwInt32)&unk_1E0, 0);
                }
            }
            break;
        case 26:
            unk_1E4 = attrIt->GetAs_RwInt32();
            break;
        case 29:
            unk_1E8 = attrIt->GetAs_RwInt32();
            break;
        case 32:
            unk_1EC = attrIt->GetAs_RwInt32();
            break;
        case 27:
            unk_1F0 = attrIt->GetAs_RwInt32();
            break;
        case 30:
            unk_1F4 = attrIt->GetAs_RwInt32();
            break;
        case 33:
            unk_1F8 = attrIt->GetAs_RwInt32();
            break;
        case 35:
            unk_244 = attrIt->GetAs_RwInt32();
            break;
        case 36:
            if (attrIt->GetAs_RwChar_ptr())
            {
                Trigger_key var_68 = *(const Trigger_key *)attrIt->GetAs_RwChar_ptr();

                if (var_68.unk_00 || var_68.unk_04)
                {
                    sub_198900((type_3DF8D8_04 *)&var_68, 1, (void (*)(RwInt32, RwInt32, RwInt32))sub_18F8B0, 0, (RwInt32)&unk_248, 0);
                }
            }
            break;
        case 37:
            unk_24C = attrIt->GetAs_RwInt32();
            break;
        case 38:
            unk_250 = attrIt->GetAs_RwReal() * 60.0f;
            break;
        case 39:
            unk_254 = attrIt->GetAs_RwInt32();
            break;
        case 40:
            unk_258 = attrIt->GetAs_RwInt32();
            break;
        case 41:
            unk_25C = attrIt->GetAs_RwInt32();
            break;
        case 42:
            if (attrIt->GetAs_RwChar_ptr())
            {
                Trigger_key var_70 = *(const Trigger_key *)attrIt->GetAs_RwChar_ptr();

                if (var_70.unk_00 || var_70.unk_04)
                {
                    sub_198900((type_3DF8D8_04 *)&var_70, 1, (void (*)(RwInt32, RwInt32, RwInt32))sub_18F8B0, 0, (RwInt32)&unk_260, 0);
                }
            }
            break;
        case 43:
            unk_264 = attrIt->GetAs_RwInt32();
            break;
        case 44:
            unk_268 = attrIt->GetAs_RwReal() * 60.0f;
            break;
        case 45:
            unk_26C = attrIt->GetAs_RwInt32();
            break;
        case 46:
            unk_270 = attrIt->GetAs_RwInt32();
            break;
        case 91:
            unk_228.unk_00 = attrIt->GetAs_RwInt32();
            break;
        case 92:
            unk_228.unk_04 = attrIt->GetAs_RwInt32();
            break;
        case 93:
            unk_228.unk_08 = attrIt->GetAs_RwInt32();
            break;
        case 94:
            unk_228.unk_0C = attrIt->GetAs_RwInt32();
            break;
        case 95:
            unk_228.unk_10 = attrIt->GetAs_RwInt32();
            break;
        case 96:
            unk_228.unk_14 = attrIt->GetAs_RwInt32();
            break;
        case 97:
            unk_228.unk_18 = attrIt->GetAs_RwInt32();
            break;
        case 82:
            unk_118 = attrIt->GetAs_RwReal();
            break;
        case 83:
            unk_11C = attrIt->GetAs_RwReal() * 60.0f;
            break;
        case 7:
            unk_21C = attrIt->GetAs_RwInt32();
            break;
        case 8:
        {
            RwInt32 var_74 = (RwInt32)(attrIt->GetAs_RwReal() * 60.0f);

            unk_220 = (unk_220 & 0xFFFF0000) + var_74;
            break;
        }
        case 9:
        {
            RwInt32 var_78 = (RwInt32)(attrIt->GetAs_RwReal() * 60.0f);

            unk_220 = (var_78 << 16) + unk_220;
            break;
        }
        }
        ++attrIt;
    }
}

// match: ?sub_AF020@ProjectileGeneratorTrigger@@QAEXH@Z @ 0x000AF020
void ProjectileGeneratorTrigger::sub_AF020(RwInt32 arg_0)
{
    switch (arg_0)
    {
    case 0:
        unk_1CC = 0;
        break;
    case 1:
        unk_1CC = 1;
        sub_198A20("GameWeapons+Weapons+Tank+ProjectileMesh", &unk_1D0);
        sub_198900((type_3DF8D8_04 *)&unk_1D0, 3, 0, 0, 0, 0);
        break;
    case 2:
        unk_1CC = 1;
        sub_198A20("COD_EnemyWeaponProjectiles+PanzerFaustBullet", &unk_1D0);
        sub_198900((type_3DF8D8_04 *)&unk_1D0, 3, 0, 0, 0, 0);
        break;
    case 3:
        unk_1CC = 3;
        sub_198A20("GameWeapons+Weapons+Artillery+ProjectileMesh", &unk_1D0);
        sub_198900((type_3DF8D8_04 *)&unk_1D0, 3, 0, 0, 0, 0);
        break;
    }
}

// match: ??_EProjectileGeneratorTrigger@@WBI@AEPAXI@Z @ 0x000AF140
