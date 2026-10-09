/*
 * ProjectileGeneratorTrigger (the class name it registers with the class
 * factory at 0x30A919, with its MakeNew, sub_AD1B0, and its size, 0x280): a
 * trigger derived from Trigger that fires projectiles, anchored at its
 * vtables off_3D6290 and off_3D6288 (+0x18), which its constructor
 * (sub_AD230) and destructor (sub_AD700) install. Only the widths of most of
 * its settings are known.
 */
#ifndef PROJECTILEGENERATORTRIGGER_H
#define PROJECTILEGENERATORTRIGGER_H

#include "rw/ostypes.h"
#include "types/type_3DF8D8.h"
#include "types/type_44350.h"
// Its projectiles' colours and life (type_429E54, 0x1C bytes), which its
// constructor copies from stru_429E54.
#include "types/projectile.h"

class ProjectileGeneratorTrigger : public Trigger
{
public:
    RWS_MAKENEWCLASS(ProjectileGeneratorTrigger);
    RWS_DECLARE_CLASSID(ProjectileGeneratorTrigger);

    ProjectileGeneratorTrigger(const RWS::CAttributePacket &attr);
    ~ProjectileGeneratorTrigger()
    {
    }

    virtual void HandleAttributes(const RWS::CAttributePacket &attr);

    // Its projectile (command 22): none (0), or a tank shell (1), a
    // panzerfaust rocket (2) or an artillery shell (3), whose mesh's name it
    // keeps in unk_1D0.
    void sub_AF020(RwInt32 arg_0);

    type_3DF8D8_04 unk_C0;
    RwInt32 unk_C8;
    type_3DF8D8_04 unk_CC;
    type_3DF8D8_04 unk_D4;
    RwInt32 unk_DC;
    RwInt32 unk_E0;
    RwInt32 unk_E4;
    type_3DF8D8_04 unk_E8;
    type_3DF8D8_04 unk_F0;
#ifdef CODFH_SP // a real in single player: SP 0xD84D2 loads it with fld
    RwReal unk_F8;              // the target's spread (type_1227C0::unk_60)
#else
    RwInt32 unk_F8;
#endif
    union                       // the generator's path speed (unk_D0)
    {
        RwInt32 unk_FC;         // (the attribute's raw bits)
        RwReal unk_FC_r;
    };
    RwInt32 unk_100;
    RwUInt32 unk_104;          // the chance, in percent, its projectiles
                                // are not flagged 2 (the kinds' vf_024)
    RwUInt32 unk_108;          // the bursts before a pause, a random
    RwUInt32 unk_10C;          // count between these (either order)
    RwInt32 unk_110;
    union                       // the pause after a burst (sub_120170)
    {
        RwInt32 unk_114;         // (the attribute's raw bits)
        RwReal unk_114_r;
    };
    RwReal unk_118;
    RwReal unk_11C;
    union                       // the pause between bursts, a random time
    {
        RwInt32 unk_120;         // (the attribute's raw bits)
        RwReal unk_120_r;
    };
    union                       // between these (either order)
    {
        RwInt32 unk_124;         // (the attribute's raw bits)
        RwReal unk_124_r;
    };
    union                       // the time between shots
    {
        RwInt32 unk_128;         // (the attribute's raw bits)
        RwReal unk_128_r;
    };
    RwReal unk_12C;
    RwReal unk_130;
    RwReal unk_134;
    RwReal unk_138;
    RwInt32 unk_13C;
    type_3DF8D8_04 unk_140;
    type_3DF8D8_04 unk_148;
    RwInt32 unk_150;
    RwInt32 unk_154;
    union                       // the projectiles' speed
    {
        RwInt32 unk_158;         // (the attribute's raw bits)
        RwReal unk_158_r;
    };
    RwReal unk_15C;
    RwReal unk_160;
    RwUInt32 unk_164;          // the firing stages' shot counts (random
    RwUInt32 unk_168;          // between each pair; sub_120310)
    RwReal unk_16C;
    RwUInt32 unk_170;
    RwUInt32 unk_174;
    RwReal unk_178;
    RwUInt32 unk_17C;
    RwUInt32 unk_180;
    RwReal unk_184;
    RwReal unk_188;
    RwReal unk_18C;
    RwInt32 unk_190;
    RwReal unk_194;
    RwReal unk_198;
    RwInt32 unk_19C;
    RwReal unk_1A0;
    RwReal unk_1A4;
    RwInt32 unk_1A8;
    RwInt32 unk_1AC;
    RwReal unk_1B0;
    RwReal unk_1B4;
    RwInt32 unk_1B8;
    RwInt32 unk_1BC;
    RwInt32 unk_1C0;
    RwReal unk_1C4;
    RwInt32 unk_1C8;
    RwInt32 unk_1CC;
    type_3DF8D8_04 unk_1D0;
    RwInt32 unk_1D8;
    RwInt32 unk_1DC;
    RwInt32 unk_1E0;
    RwInt32 unk_1E4;
    RwInt32 unk_1E8;
    RwInt32 unk_1EC;
    RwInt32 unk_1F0;
    RwInt32 unk_1F4;
    RwInt32 unk_1F8;
    RwInt32 unk_1FC;
    RwInt32 unk_200;
    RwReal unk_204;
    RwInt32 unk_208;
    RwInt32 unk_20C;
    RwInt32 unk_210;
    RwReal unk_214;
    RwInt32 unk_218;
    RwInt32 unk_21C;
    RwUInt32 unk_220;          // the sound's replay delay: a random time
                                // between its low and high words
    struct type_1227C0 *unk_224;    // its generator
    type_429E54 unk_228;       // commands 43 to 49 (stru_429E54 by default)
    RwInt32 unk_244;
    RwInt32 unk_248;
    RwInt32 unk_24C;
    RwReal unk_250;
    RwInt32 unk_254;
    RwInt32 unk_258;
    RwInt32 unk_25C;
    RwInt32 unk_260;
    RwInt32 unk_264;
    RwReal unk_268;
    RwInt32 unk_26C;
    RwInt32 unk_270;
    RwUInt8 unk_274[0xC];
    // HandleEvents, as the image's vtable has it (a trivial body, folded into
    // sub_A2BF0 with every other copy).
    virtual void HandleEvents(RWS::CMsg &pMsg)
    {
        Trigger::HandleEvents(pMsg);
    }
    // vf_008, as the image's vtable has it (a trivial body, folded into
    // sub_1A3190 with every other copy).
    virtual RwInt32 vf_008()
    {
        return 0x13;
    }
};
typedef RwChar ProjectileGeneratorTrigger_size_check[sizeof(ProjectileGeneratorTrigger) == 0x280 ? 1 : -1];

#endif
