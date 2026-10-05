// A site's state from a peer (the handler sub_1AEB90). The host takes a
// newer one (its update count, unk_1C, above the site's): the state, the
// count, the player and the bomb's position, the bomb taken away when it
// is defused, and, unless it is its own, the site's state set without
// telling the manager (sub_1A4200) and its own defusing or planting there
// stopped. A client takes a changed state, like sub_1A7D80, and sends it on
// as its own copy.
// match: ?sub_1A80B0@type_4F8184@@QAEXPAUtype_3E0FCC@@@Z @ 0x001A80B0
void type_4F8184::sub_1A80B0(type_3E0FCC *arg_0)
{
    if (unk_4F61F8.unk_104)
    {
        // A compiled-out check (docs/toolchain.md): the registers after it
        // are one load on.
        if (!unk_00[0].unk_00)
        {
        }
        if (arg_0->unk_1C > unk_00[arg_0->unk_04].unk_04)
        {
            unk_00[arg_0->unk_04].unk_00 = arg_0->unk_08;
            unk_00[arg_0->unk_04].unk_04 = arg_0->unk_1C;
            unk_00[arg_0->unk_04].unk_0C = arg_0->unk_18;
            unk_00[arg_0->unk_04].unk_18 = arg_0->unk_0C;
            if (arg_0->unk_08 == 5)
                dword_4F6950.sub_1A3E30(arg_0->unk_04);
            if (arg_0->unk_18 != unk_4F7EB8.sub_1AEC70())
            {
                dword_4F6950.sub_1A4200(arg_0->unk_04, arg_0->unk_08, arg_0->unk_18, &arg_0->unk_0C);
                if (unk_4F7EB8.get_unk_1A4())
                {
                    if (arg_0->unk_08 == 2)
                    {
                        if (unk_4F7EB8.get_unk_1A4()->defusing_at(arg_0->unk_04))
                            unk_4F7EB8.get_unk_1A4()->sub_1B8690();
                    }
                    if (arg_0->unk_08 == 4)
                    {
                        if (unk_4F7EB8.get_unk_1A4()->planting_at(arg_0->unk_04))
                            unk_4F7EB8.get_unk_1A4()->sub_1B87D0();
                    }
                }
            }
        }
    }
    else if (arg_0->unk_08 != unk_00[arg_0->unk_04].unk_00)
    {
        type_4F8184_site var_24 = unk_00[arg_0->unk_04];

        unk_00[arg_0->unk_04].unk_00 = arg_0->unk_08;
        unk_00[arg_0->unk_04].unk_0C = arg_0->unk_18;
        unk_00[arg_0->unk_04].unk_08 = unk_B4;
        unk_00[arg_0->unk_04].unk_18 = arg_0->unk_0C;
        if (arg_0->unk_08 == 3 && var_24.unk_00 != 4 && var_24.unk_00 != 5 && var_24.unk_00 != 6)
            unk_00[arg_0->unk_04].unk_14 = arg_0->unk_18;
        type_3E0FCC var_44(*arg_0);

        var_44.unk_1C = ++unk_00[arg_0->unk_04].unk_04;
        unk_4F7EBC.sub_1B3190(arg_0->unk_04, &var_24, &unk_00[arg_0->unk_04]);
        type_4F8058::get()->sub_1DDE20(&var_44, type_4F8054::get()->get_unk_B0()->sub_1A8050());
        dword_4F6950.sub_1A4200(arg_0->unk_04, arg_0->unk_08, arg_0->unk_18, &arg_0->unk_0C);
    }
}

// The message's compiler-made copy constructor, out of line (sub_1A80B0
// sends its copy through it).
// match: ??0type_3E0FCC@@QAE@ABU0@@Z @ 0x001A8400

