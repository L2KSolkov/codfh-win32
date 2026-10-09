/*
 * sp_target.h: single player's sub_3DE00 (whether the entity arg_0 may take
 * the entity arg_4 as its target), a static inline there. Every caller keeps it
 * out of line, as a static copy with its arguments in registers (edi = arg_0,
 * esi = arg_4); the copies fold into one, SP 0x28F30, called from SP 0x290D0
 * (type_3CE4F0::sub_34C60), 0x2A994 and 0x2AB36 (unit_036730) and 0x2EE73
 * (type_3D410::sub_3DCD0). Multiplayer's is an ordinary function (MP 0x3DE00,
 * game/functions.h). Include after types/AIData.h and types/type_3D3548.h.
 */
#ifndef SP_TARGET_H
#define SP_TARGET_H

#ifdef CODFH_SP

#include "rw/ostypes.h"
#include "game/data.h"
#include "types/AIData.h"
#include "types/type_3D3548.h"

static inline RwInt32 sub_3DE00(type_3D3548 *arg_0, type_3D3548 *arg_4)
{
    if (byte_4C1940 != 0 && arg_4 != 0 && ((arg_4->unk_2C >> 4) & 1) != 0)
        return 0;
    if (arg_0 != 0 && arg_4 != 0 && xor_unk_2C(arg_0, arg_4) && ((arg_4->unk_28 >> 9) & 1) == 0
            && (arg_4->unk_28 & 1) == 0
            && ((arg_4->unk_2C & 0x3FFFFF0) & (arg_0->unk_34 & 0x3FFFFF0)) != 0 // not an address: kind bits
            && arg_4->vf_120() != 0 && ((arg_4->vf_120()->unk_49C >> 6) & 1) != 0
            && (((arg_4->unk_2C >> 4) & 1) == 0 || arg_4->vf_200() == 0 || arg_4->vf_1E4() != 0))
        return 1;
    return 0;
}

#endif

#endif
