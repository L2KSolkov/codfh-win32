// SUPERSEDED: sub_1A7480 now matches in src/recovered/unit_1A6140.cpp.
// This is the historical draft; see the const-reference angle constructor
// and inline normalization in include/game/netplayer.h.

// PARKED sub_1A7480 (2026-10-01): instructions identical to the image (put it before sub_1A7A60 in
// unit_1A6140.cpp). Left: in the case block the image has the two returned vectors (0x50, 0x5C)
// above the two scalars (0x60, 0x64); this build always allocates those temporaries after every
// named local, whatever the names, scopes or file position. Also the image leaves nine unused
// dwords before `this` (0xC8-0xE8): leftover slots, untried. The pointer cast for var_C is
// what gives the image's copy of *var_C; set()'s mixed signature and delta() are in game/netplayer.h.

void type_4F6B00::sub_1A7480(const type_1CCA10 &arg_0)
{
    type_4F6B00_F4 *var_C;
    RwReal r10;
    RwReal var_14;

    type_1CCA10 bp_18((RwInt32)(unk_5C * 1000.0f * 1.5f));
    type_1CCA10 bp_8 = unk_58 + bp_18;
    type_1CCA10 *bp_4 = &bp_8;
    type_1CCA10 t1C((RwInt32)(unk_5C * 1000.0f));
    type_1CCA10 fp_20 = *bp_4 + t1C;
    if (arg_0 > fp_20)
    {
        if (unk_D4 == 0 || unk_D4 == 1)
        {
            type_1F8560_v var_2C;

            unk_E4 = var_2C;
            unk_D4 = 2;
        }
    }
    else if (arg_0 > *bp_4)
    {
        unk_D4 = 2;
    }
    else if (unk_D4 == 1 || unk_D4 == 2)
    {
        RwReal var_30;

        unk_D4 = 0;
        unk_6C.sub_1FAF00(unk_D8, unk_E4, unk_F8.unk_00 * 0.001f, unk_24, unk_30, bp_4->unk_00 * 0.001f);
        var_30 = sub_1A6E10(unk_3C);
        var_14 = sub_1A6E10(unk_F4.delta(var_30));
        var_C = (type_4F6B00_F4 *)&var_14;
        r10 = unk_F4.get_unk_00() + var_C->get_unk_00();
        if (((RwReal)fabs(((RwReal)(r10 - unk_F4.get_unk_00())))) > 180.0f)
        {
            if (r10 > 0.0f)
            {
                RwReal var_34 = r10 - 360.0f;
                RwReal var_38 = unk_F4.get_unk_00();

                unk_FC.set(var_38, unk_F8.unk_00 * 0.001f, var_34, bp_4->unk_00 * 0.001f);
            }
            else
            {
                RwReal local_3C = r10 + 360.0f;
                RwReal bp_40 = unk_F4.get_unk_00();

                unk_FC.set(bp_40, unk_F8.unk_00 * 0.001f, local_3C, bp_4->unk_00 * 0.001f);
            }
        }
        else
        {
            RwReal bp_44 = unk_F4.get_unk_00();

            unk_FC.set(bp_44, unk_F8.unk_00 * 0.001f, r10, bp_4->unk_00 * 0.001f);
        }
        unk_10C.set(unk_F0_r, unk_F8.unk_00 * 0.001f, unk_40, bp_4->unk_00 * 0.001f);
    }
    switch (unk_D4)
    {
    case 0:
    case 1:
        {
            RwReal var_60;
            RwReal var_64;

            unk_D8 = unk_6C.sub_1FB250(arg_0.unk_00 * 0.001f);
            unk_E4 = unk_6C.sub_1FB2E0(arg_0.unk_00 * 0.001f);
            var_64 = unk_FC.sub_1A7B70(arg_0.unk_00 * 0.001f);
            var_60 = sub_1A6E10(var_64);
            unk_F4.unk_00 = var_60;
            unk_F0_r = unk_10C.sub_1A7B70(arg_0.unk_00 * 0.001f);
        }
        break;
    }
    unk_F8 = arg_0;
}
