// Player arg_4 killed by a grenade (type_3E1164), on the same terms as the
// others: its team's state set, the kill written to the console
// ("MW_GEN_KILLS_THEMACCIDENT", "MW_GEN_KILLS_GREN" with both names, or
// "MW_GEN_SUICIDE"), its remote player given the blast (at the message's
// point, of its radius and damage), counted and its pickups dropped when not
// hosting, and, unless the manager's state is 4, its remote player kept for
// the kill cam.
// match: ?sub_1ADD90@@YAXHHPAUtype_3DA44C@@@Z @ 0x001ADD90
// match: __ehhandler$?sub_1ADD90@@YAXHHPAUtype_3DA44C@@@Z-0x29 @ 0x00302B40
// match: __ehhandler$?sub_1ADD90@@YAXHHPAUtype_3DA44C@@@Z-0x21 @ 0x00302B48
// match: __ehhandler$?sub_1ADD90@@YAXHHPAUtype_3DA44C@@@Z-0x16 @ 0x00302B53
// match: __ehhandler$?sub_1ADD90@@YAXHHPAUtype_3DA44C@@@Z-0xB @ 0x00302B5E
// match: __ehhandler$?sub_1ADD90@@YAXHHPAUtype_3DA44C@@@Z @ 0x00302B69
void sub_1ADD90(RwInt32 arg_0, RwInt32 arg_4, type_3DA44C *arg_8)
{
    type_3E1164 *var_18 = (type_3E1164 *)arg_8;

    sub_1A8A70(&unk_4F7EB8, "Player %d killed by grenade thrown by player %d\n", arg_4, var_18->unk_18);
    dword_4F8288.sub_1C28F0(arg_4, 1, 1);
    if (dword_4FB9E0.sub_1E3480() != 1 || dword_4FB9E0.get_unk_C8() || dword_4FB9E0.get_unk_C4())
    {
        return;
    }
    RwChar var_158[0x100];

    if (arg_4 != var_18->unk_18)
    {
        const RwChar *var_2C = type_4F8054::get()->get_unk_B0()->unk_90[var_18->unk_18].unk_00;

        if (var_18->unk_18 == arg_4)
        {
            sub_1CB000(var_158, sub_E3970("MW_GEN_KILLS_THEMACCIDENT", 1).c_str(), var_2C);
        }
        else
        {
            const RwChar *var_164 = type_4F8054::get()->get_unk_B0()->unk_90[arg_4].unk_00;

            sub_1CB0F0(var_158, sub_E3970("MW_GEN_KILLS_GREN", 1).c_str(), var_2C, var_164);
        }
    }
    else
    {
        sub_1CB000(var_158, sub_E3970("MW_GEN_SUICIDE", 1).c_str(),
                   type_4F8054::get()->get_unk_B0()->unk_90[arg_4].unk_00);
    }
    sub_EACA0(var_158, 0, 0);
    // Two compiled-out checks (docs/toolchain.md): the registers after them
    // are two loads on.
    if (!var_18->unk_1C)
    {
    }
    if (!var_18->unk_1C)
    {
    }
    type_4F7EB8_1F0 *var_1C0 = unk_4F7EB8.unk_1F0[arg_4];

    if (var_1C0 && unk_4F7EB8.unk_2A4 != 4)
    {
        type_4AE70 var_1F4;
        RwMatrix var_240;

        var_1F4.unk_2C = var_18->unk_04;
        var_240.pos.x = var_18->unk_08.unk_00;
        var_240.pos.y = var_18->unk_08.unk_04;
        var_240.pos.z = var_18->unk_08.unk_08;
        var_1F4.unk_0C = &var_240;
        var_1F4.unk_10 = var_18->unk_14;
        var_1F4.unk_14 = var_18->unk_14;
        var_1F4.unk_18 = var_18->unk_14;
        var_1C0->pvf_020(&var_1F4);
    }
    if (!unk_4F61F8.unk_104)
    {
        unk_4F7EBC.sub_1B2D00(arg_4, var_18->unk_18, 1);
        if (var_1C0 && unk_4F7EB8.unk_2A4 != 4)
        {
            unk_4F7EB8.sub_1ADB80(var_18->unk_1C, arg_4);
        }
    }
    if (unk_4F7EB8.unk_2A4 != 4)
    {
        unk_4F7EB8.sub_73D90(var_18->unk_18, arg_4);
        // A compiled-out check (docs/toolchain.md): the registers after it
        // are one load on.
        if (!var_18->unk_1C)
        {
        }
        if (unk_4F6B00[arg_4].is_visible())
        {
            unk_4F6B00[arg_4].sub_1A63E0();
            unk_4F7EB8.sub_1AB2C0();
        }
        // Another (docs/toolchain.md): one load on.
        if (!var_18->unk_1C)
        {
        }
        if (unk_4F7EB8.unk_1F0[arg_4])
        {
            unk_4F6B00[arg_4].sub_1A6460();
            // Another (docs/toolchain.md): one load on.
            if (!var_18->unk_1C)
            {
            }
            unk_4F7EB8.unk_238[arg_4] = unk_4F7EB8.unk_1F0[arg_4];
            unk_4F7EB8.unk_1F0[arg_4] = 0;
        }
    }
}

