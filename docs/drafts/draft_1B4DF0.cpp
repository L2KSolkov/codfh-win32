// Draft: registers match with the two checks; the image's frame has two
// more unused slots (-0x18, -0x1C) allocated after the accessor temps.
// A session accessor with one unused local fixes the frame but adds a
// return temp's code; sub_1B4CF0 in its class gets inlined.
// match: ?sub_1B4DF0@type_4FB9E0@@QAEXXZ @ 0x001B4DF0
void type_4FB9E0::sub_1B4DF0()
{
    // The locals' names state their slots (docs/toolchain.md).
    type_1DDE20_mask bp_8;
    type_3E1074 bp_4;

    sub_1B4CF0(2);
    // Two compiled-out checks (docs/toolchain.md): the registers after
    // them are two loads on.
    if (!unk_04)
    {
    }
    if (!unk_04)
    {
    }
    unk_D8 = 0;
    unk_DC = 0;
    if (!unk_4F61F8.unk_104)
    {
        bp_8 = type_4F8054::get()->get_unk_B0()->sub_1A8050();
        unk_00->sub_1DDDB0(&bp_4, bp_8);
        unk_3C = 0;
        if (0)
            off_42CD14("(HOST) Broadcast level load start to clients\n");
    }
    sub_1B2810();
}

// Tells the network game the settings (its vf_064: level, type and three
// flags).
// match: ?sub_1B60E0@type_4FB9E0@@QAEXXZ @ 0x001B60E0
void type_4FB9E0::sub_1B60E0()
{
    type_4F8054::get_2()->vf_064((RwUInt8)unk_08.unk_28, (RwUInt8)unk_08.unk_00, (RwUInt8)unk_08.unk_04,
                                 (RwUInt8)unk_08.unk_0C, (RwUInt8)unk_08.unk_10);
}

// match: ?sub_1B6250@type_4FB9E0@@QAEXXZ @ 0x001B6250
void type_4FB9E0::sub_1B6250()
{
    type_1DDE20_mask bp_8;
    type_3E0EB8 bp_4;

    if (0)
        off_42CD14("(HOST) Game over, send message to clients\n");
    sub_1B4CF0(3);
    unk_4F7EB8.sub_1AB400(2);
    bp_8 = type_4F8054::get()->get_unk_B0()->sub_1A8050();
    unk_00->sub_1DDDB0(&bp_4, bp_8);
    unk_E0 = 0;
    unk_E4 = 0;
    sub_1C49A0();
    sub_124EE0(0.5f, 0);
}

// sub_1B60E0: the image copies an unwritten slot (-4) into the call's
// object temporary (-0xC) before storing dword_4F8054 there; get(),
// get_2() (direct return), a data member accessor and locals all differ.
// sub_1B6250: the same two unused slots as sub_1B4DF0.
