/*
 * type_F3130: a particle system's definition (0x10C bytes), named for the
 * function that starts a system from one (sub_F3130). ParticleEditor edits
 * one (types/ParticleEditor.h); the surfaces' particle events list them
 * (sub_F2750).
 */
#ifndef TYPE_F3130_H
#define TYPE_F3130_H

#include "rw/ostypes.h"
#include "rw/bamatrix.h"
#include "rw/batextur.h"

// A particle system's definition, named for the function that starts a
// system from one (sub_F3130); only the widths are known where no default
// (ParticleEditor::sub_F23F0) or reader tells more.
struct type_F3130
{
    RwInt32 unk_00;             // 6 by default
    RwTexture *unk_04;          // the texture named unk_84, without its extension
    RwInt32 unk_08;             // 300 by default
    RwReal unk_0C;
    RwReal unk_10;
    RwReal unk_14;
    RwReal unk_18;
    RwReal unk_1C;
    RwReal unk_20;              // its duration (0: endless)
    RwReal unk_24;              // its start age when endless
    RwReal unk_28;
    RwReal unk_2C;
    RwReal unk_30;
    RwReal unk_34;              // (0, -20, 0) by default
    RwReal unk_38;
    RwReal unk_3C;
    RwReal unk_40;
    RwReal unk_44;
    RwReal unk_48;
    RwReal unk_4C;
    RwReal unk_50;
    RwReal unk_54;
    RwUInt32 unk_58;            // colours (ARGB: red, blue by default)
    RwUInt32 unk_5C;
    RwReal unk_60;
    RwReal unk_64;
    RwReal unk_68;
    RwReal unk_6C;
    RwReal unk_70;
    RwReal unk_74;
    RwReal unk_78;
    RwReal unk_7C;
    RwInt32 unk_80;
    RwChar unk_84[0x20];        // the texture's name
    RwInt32 unk_A4;             // 1 by default
    RwInt32 unk_A8;             // sub_F3130 refuses kind 3 and up with it set
    RwChar unk_AC[0x20];
    RwReal unk_CC;              // 1.0 by default
    RwChar unk_D0[0x20];
    RwInt32 unk_F0;             // set: its particles start trails (unk_D0)
    union
    {
        RwInt32 unk_F4;
        RwReal unk_F4_f;        // the trails' rate (0: one a particle; sub_EF040)
    };
    RwReal unk_F8;              // a spin (kind 4 and up; a sprite system is
    RwReal unk_FC;              // drawn offset by them, sub_F34C0)
    RwReal unk_100;
    RwReal unk_104;
    RwUInt32 unk_108;           // a colour (ARGB: green by default)

    type_F3130()
    {
        unk_04 = 0;
        unk_84[0] = 0;
    }
};
// The trails' starting velocity, a fraction of the definition's fall
// (unk_34..unk_3C; the mesh systems' update, sub_EF040; .data).
// unk_4296B4 (one .data object: a lone zero global would be in .bss).
struct type_4296B4
{
    RwReal unk_00;
    RwInt32 unk_04;
    RwInt32 unk_08;
};
extern type_4296B4 unk_4296B4;

typedef RwChar type_F3130_size_check[sizeof(type_F3130) == 0x10C ? 1 : -1];

// The particle systems (still binary): the ones started from the
// definition arg_0 are destroyed (sub_F3370); one is started from arg_0 at
// the matrix arg_4 (sub_F3130; the rest only known by width); all are
// cleared, with the decals too when arg_0 is set (sub_F2A00).
void sub_F3370(type_F3130 *arg_0);
// arg_8 1: counted (refused past 40); arg_14: may take the second pool.
struct type_F2FF0 *sub_F3130(type_F3130 *arg_0, RwMatrix *arg_4, RwInt32 arg_8, RwInt32 arg_C,
                             bool arg_10, bool arg_14);
void sub_F2A00(RwInt32 arg_0);
#endif
