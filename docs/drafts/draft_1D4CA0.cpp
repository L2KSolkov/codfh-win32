// Parked 2026-09-28: cTimeKeeper::sub_1D4CA0 (unit_1D4AB0). Header pieces
// it needs (type_1DDE20_mask):
//     // include() after one compiled-out check: an inline with no address,
//     // named for what it does. Evidence: the time keeper's step
//     // (sub_1D4CA0) shifts by the peer in its parameter's slot with the
//     // registers one load on (docs/toolchain.md).
//     void include_checked(RwInt32 arg_0)
//     {
//         if (!unk_00)
//         {
//         }
//         unk_00 |= 1 << arg_0;
//     }
//     // The peers in both: an inline with no address, named for what it
//     // does. Evidence: the time keeper's step (sub_1D4CA0) builds the result
//     // in a local of its own, cleared first, and returns it through a
//     // temporary.
//     friend type_1DDE20_mask operator&(const type_1DDE20_mask &arg_0, const type_1DDE20_mask &arg_4)
//     {
//         type_1DDE20_mask r;
//         r.unk_00 = arg_0.unk_00 & arg_4.unk_00;
//         return r;
//     }
// 
// (the operator was also tried as a friend). With the two checks before the
// intersection and one before the merge the code lines up up to the
// intersection's copies: the image copies r into the return temporary with
// dx straight after the `and` (two copies in all); ours makes three.

// match: ?sub_1D4CA0@cTimeKeeper@@QAEXXZ @ 0x001D4CA0
void cTimeKeeper::sub_1D4CA0()
{
    RwUInt32 var_4;
    type_1CCA10 var_8 = sub_1CCA10();
    RwUInt32 var_C;

    if (var_8.get_unk_00() - unk_04.get_unk_00() >= 600)
    {
        type_1D7560 var_14;
        type_1DDE20_mask var_18;
        type_1DDE20_mask var_20 = unk_00->get_unk_B0()->sub_1A8050();
        RwInt32 var_1C;

        var_14.unk_00 = var_8;
        var_14.unk_04 = 0;
        for (var_4 = 0; var_4 < 4; var_4++)
        {
            var_C = unk_08 + var_4;
            var_18.include_checked((unk_08 + var_C) % 16);
        }
        unk_08 = var_C % 16;
        // A compiled-out check (docs/toolchain.md).
        if (!var_18.unk_00)
        {
        }
        var_18.unk_00 |= unk_69C.unk_00;
        unk_69C.unk_00 = 0;
        // Two compiled-out checks (docs/toolchain.md).
        if (!var_20.unk_00)
        {
        }
        if (!var_20.unk_00)
        {
        }
        var_20 = var_20 & var_18;
        if (!var_20.empty())
        {
            var_14.sub_1D7560(unk_00, var_20, &var_1C);
            for (var_4 = 0; var_4 < 16; var_4++)
            {
                if (var_20.test(var_4))
                {
                    var_C = unk_60C[var_4];
                    unk_0C[var_4][var_C].unk_00 = var_14.unk_00;
                    unk_0C[var_4][var_C].unk_04 = 0;
                    unk_0C[var_4][var_C].unk_08 = 0;
                    unk_60C[var_4] = (unk_60C[var_4] + 1) % 8;
                }
            }
        }
        unk_04 = var_8;
        for (var_4 = 0; var_4 < 16; var_4++)
        {
            RwInt32 var_28 = 0;
            RwInt32 var_24 = 0;
            RwInt32 var_2C = 0;

            for (var_C = 0; var_C < 8; var_C++)
            {
                if (unk_0C[var_4][var_C].unk_08.get_unk_00())
                {
                    var_28++;
                    var_24 += unk_0C[var_4][var_C].unk_08.get_unk_00() >> 1;
                    var_2C += unk_0C[var_4][var_C].unk_04.get_unk_00() - unk_0C[var_4][var_C].unk_00.get_unk_00();
                }
            }
            unk_61C[var_4] = 0;
            unk_65C[var_4] = 0;
            if (var_28)
            {
                unk_61C[var_4] = var_24 / var_28;
                unk_65C[var_4] = var_2C / var_28;
            }
        }
    }
}



// Parked 2026-09-28 too: cTimeKeeper::sub_1D5010. Names bp_4 (loop) fix the
// slots except the round trip's two temporaries: the image has the time's
// temporary at -0x1C and the conversion's at -0x20 (and loads the value
// before the record's address); ours allocates the conversion first. A
// functional cast and a named local did not help.
// extern void (*off_42CD14)(const RwChar *arg_0, ...);

// match: ?sub_1D5010@cTimeKeeper@@QAEHHHHPAUtype_1F8560@@H@Z @ 0x001D5010
RwInt32 cTimeKeeper::sub_1D5010(RwInt32 arg_0, RwInt32 arg_4, RwInt32 arg_8, type_1F8560 *arg_C, RwInt32 arg_10)
{
    type_1D7560 var_C;
    RwUInt32 bp_4;
    RwInt32 var_10;

    if (arg_0 != 7)
        return 0;
    if (!var_C.sub_1D7650(arg_C, arg_10))
    {
        if (0)
            off_42CD14("Warning: error in unpack of ping packet!\n");
        return 0;
    }
    if (!var_C.unk_04.unk_00)
    {
        var_C.unk_04 = sub_1CCA10();
        var_C.sub_1D7560(unk_00, type_1DDE20_mask(1 << arg_8), &var_10);
        return 1;
    }
    for (bp_4 = 0; bp_4 < 8; bp_4++)
    {
        if (var_C.unk_00 == unk_0C[arg_8][bp_4].unk_00)
        {
            unk_0C[arg_8][bp_4].unk_04 = var_C.unk_04;
            unk_0C[arg_8][bp_4].unk_00 = var_C.unk_00;
            unk_0C[arg_8][bp_4].unk_08 = sub_1CCA10() - var_C.unk_00;
            return 1;
        }
    }
    if (0)
        off_42CD14("KNET: cTimeKeeper() - Packet sent back to us, which we don't remember sending... could "
                   "just be big time lapse!\n");
    return 1;
}
