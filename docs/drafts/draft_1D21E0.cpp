
// Peer arg_0's packet at the time arg_34: its check (when the game uses one),
// then its acks (arg_20, arg_24 of them; each done with dropped, the rest
// due again in 100 ms), the timed messages (arg_14, arg_18; due again in
// 250 ms), the plain ones (arg_8, arg_C; each done with once no peer is
// left) and, when arg_28 is set, the per-peer ones (arg_2C, arg_30) in the
// second buffer; the statistics kept and the lot handed to the game.
// match: ?sub_1D21E0@type_1D0100@@QAEXHHPAPAUtype_3E4E4C@@HHPAPAUtype_3E4E58@@IHPAPAUtype_3E4E84@@HHPAPAUtype_3E4E40@@HABUtype_1CCA10@@@Z @ 0x001D21E0
void type_1D0100::sub_1D21E0(RwInt32 arg_0, RwInt32 arg_4, type_3E4E4C **arg_8, RwInt32 arg_C, RwInt32 arg_10,
                             type_3E4E58 **arg_14, RwUInt32 arg_18, RwInt32 arg_1C, type_3E4E84 **arg_20,
                             RwInt32 arg_24, RwInt32 arg_28, type_3E4E40 **arg_2C, RwInt32 arg_30,
                             const type_1CCA10 &arg_34)
{
    type_1F8560 var_34((RwUInt8 *)unk_164, 0x2400);
    type_1F8560 var_48((RwUInt8 *)unk_168, 0x2400);
    type_1F8560 *var_18 = &var_48;
    RwUInt32 var_4C = (RwUInt32)-1;
    RwInt32 var_38 = -1;
    RwInt32 var_8 = unk_79C->vf_03C();
    RwUInt32 var_1C = 0;
    RwInt32 var_4 = 0;
    RwInt32 var_3C;
    RwInt32 var_28;
    RwUInt32 var_14;
    RwInt32 var_C;
    RwInt32 var_50;
    RwInt32 var_24;
    RwInt32 var_20;
    RwUInt32 var_10;

    if (!unk_4C4.unk_50[arg_0])
    {
        unk_4C4.unk_50[arg_0] = 1;
        unk_4C4.unk_90[arg_0] = arg_34;
    }
    var_3C = 0;
    var_34.sub_1F8520(0);
    var_34.sub_1F8860(0, 6);
    var_3C++;
    if (var_8)
    {
        var_4C = var_34.get_unk_08();
        type_1D2CC0_check var_60;

        var_34.sub_1F89D0((RwChar *)var_60.unk_00, 0x48);
        var_3C += 9;
    }
    var_28 = 0;
    for (var_14 = 0; var_14 < (RwUInt32)arg_24; var_14++)
    {
        RwUInt32 var_64;

        if (!var_14)
            var_28 = arg_20[0]->unk_04;
        var_64 = var_34.get_unk_08() + 0x66;
        if (var_64 > 0x2400)
        {
            arg_24 = var_14;
            break;
        }
        var_34.sub_1F8520(1);
        if (!var_14)
            var_34.sub_1F88A0(var_28);
        else
        {
            RwInt32 var_68 = arg_20[var_14]->unk_04 - var_28;

            var_34.sub_1F8AB0(var_68);
            var_28 = arg_20[var_14]->unk_04;
        }
        if (arg_34 >= arg_20[var_14]->unk_0C)
            unk_34.remove(arg_20[var_14]);
        else
            arg_20[var_14]->unk_08 = arg_34 + 100;
    }
    var_34.sub_1F8520(0);
    var_C = 0;
    var_50 = 1;
    var_24 = 0;
    var_20 = 0;
    for (var_14 = 0; var_14 < arg_18; var_14++)
    {
        RwUInt32 var_6C = var_34.get_unk_08() + arg_14[var_14]->unk_14 + 0xAF;
        RwInt32 var_70;

        if (var_6C > 0x2400)
            break;
        var_C++;
        var_34.sub_1F8520(1);
        if (var_50)
        {
            RwInt32 var_74;

            var_34.sub_1F88A0(arg_14[var_14]->unk_04);
            var_74 = arg_14[var_14]->unk_58[arg_0] - arg_14[var_14]->unk_04;
            var_34.sub_1F8AB0(var_74);
            var_50 = 0;
            var_24 = arg_14[var_14]->unk_04;
            var_20 = arg_14[var_14]->unk_58[arg_0];
        }
        else
        {
            RwInt32 var_78;

            var_78 = arg_14[var_14]->unk_04 - var_24;
            var_34.sub_1F8AB0(var_78);
            var_24 = arg_14[var_14]->unk_04;
            var_78 = arg_14[var_14]->unk_58[arg_0] - var_20;
            var_34.sub_1F8AB0(var_78);
            var_20 = arg_14[var_14]->unk_58[arg_0];
        }
        var_34.sub_1F88A0(arg_14[var_14]->unk_14 - 1);
        var_34.sub_1F89D0((RwChar *)arg_14[var_14]->unk_10, arg_14[var_14]->unk_14);
        unk_4C4.unk_110[arg_0] += arg_14[var_14]->unk_14;
        var_70 = arg_34.get_unk_00() - arg_14[var_14]->unk_18[arg_0].get_unk_00();
        if (var_70 < 0)
            var_70 = 0;
        arg_14[var_14]->unk_18[arg_0] = type_1CCA10(arg_34.get_unk_00() - var_70 + 0xFA);
    }
    var_34.sub_1F8520(0);
    for (var_14 = 0; var_14 < (RwUInt32)arg_C; var_14++)
    {
        RwUInt32 var_7C = var_34.get_unk_08() + arg_8[var_14]->unk_14 + 0x8A;

        if (var_7C > 0x2400)
        {
            arg_C = var_14;
            break;
        }
        var_34.sub_1F8520(1);
        if (!var_14)
            var_34.sub_1F88A0(arg_8[0]->unk_04);
        var_34.sub_1F88A0(arg_8[var_14]->unk_14 - 1);
        var_34.sub_1F89D0((RwChar *)arg_8[var_14]->unk_10, arg_8[var_14]->unk_14);
        unk_4C4.unk_D0[arg_0] += arg_8[var_14]->unk_14;
        arg_8[var_14]->unk_08.clear(arg_0);
        if (arg_8[var_14]->unk_08.empty())
        {
            arg_8[var_14]->vf_008();
            unk_04.remove(arg_8[var_14]);
        }
    }
    var_34.sub_1F8520(0);
    if (arg_28)
    {
        var_50 = 1;
        var_24 = 0;
        var_20 = 0;
        for (var_14 = 0; var_14 < (RwUInt32)arg_30; var_14++)
        {
            RwUInt32 var_80 = var_18->get_unk_08() + arg_2C[var_14]->unk_14 + 0xAF;

            if (var_80 > 0x2400)
            {
                arg_30 = var_14;
                break;
            }
            var_18->sub_1F8520(1);
            if (var_50)
            {
                RwInt32 var_84;

                var_18->sub_1F88A0(arg_2C[var_14]->unk_04);
                var_84 = arg_2C[var_14]->unk_18[arg_0] - arg_2C[var_14]->unk_04;
                var_18->sub_1F8AB0(var_84);
                var_50 = 0;
                var_24 = arg_2C[var_14]->unk_04;
                var_20 = arg_2C[var_14]->unk_18[arg_0];
            }
            else
            {
                RwInt32 var_88;

                var_88 = arg_2C[var_14]->unk_04 - var_24;
                var_18->sub_1F8AB0(var_88);
                var_24 = arg_2C[var_14]->unk_04;
                var_88 = arg_2C[var_14]->unk_18[arg_0] - var_20;
                var_18->sub_1F8AB0(var_88);
                var_20 = arg_2C[var_14]->unk_18[arg_0];
            }
            var_18->sub_1F88A0(arg_2C[var_14]->unk_14 - 1);
            var_18->sub_1F89D0((RwChar *)arg_2C[var_14]->unk_10, arg_2C[var_14]->unk_14);
            unk_4C4.unk_150[arg_0] += arg_2C[var_14]->unk_14;
            arg_2C[var_14]->unk_08.clear(arg_0);
            if (arg_2C[var_14]->unk_08.empty())
            {
                arg_2C[var_14]->vf_008();
                unk_4C.remove(arg_2C[var_14]);
            }
        }
        var_18->sub_1F8520(0);
        var_1C = (var_48.get_unk_08() + 7) >> 3;
    }
    var_10 = (var_34.get_unk_08() + 7) >> 3;
    if (var_8)
    {
        var_34.sub_1F8860(0, 7);
        type_1D2CC0_check var_94;

        var_94.sub_73D90((RwUInt8 *)unk_164 + var_3C, var_10 - var_3C);
        var_34.unk_08 = var_4C;
        var_34.sub_1F89D0((RwChar *)var_94.unk_00, 0x48);
    }
    if (unk_79C->vf_040(arg_0))
        unk_79C->vf_020((RwInt32)((RwUInt8 *)unk_164 + var_3C), var_10 - var_3C - var_4);
    unk_4C4.unk_00[0] += var_10 + var_1C;
    unk_4C4.unk_00[2] += var_10 + var_1C + 0x26;
    unk_4C4.unk_190[arg_0] += 0x130;
    unk_79C->vf_044(arg_0, (RwInt32)unk_164, var_10, var_1C ? (RwInt32)unk_168 : 0, var_1C);
}
