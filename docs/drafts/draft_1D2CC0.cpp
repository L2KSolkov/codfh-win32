
// Peer arg_0's packet: its check (when the game uses one), then the acks, the
// guaranteed messages (in order or not, each acked), the unreliable ones and
// the extra stream's; the statistics kept. 0 when the packet is dropped.
// match: ?sub_1D2CC0@type_1D0100@@QAEHHPAEI0H@Z @ 0x001D2CC0
RwInt32 type_1D0100::sub_1D2CC0(RwInt32 arg_0, RwUInt8 *arg_4, RwUInt32 arg_8, RwUInt8 *arg_C, RwInt32 arg_10)
{
    type_1F8560 var_40(arg_4, 0x2400);
    RwUInt32 var_60 = 0;
    RwInt32 var_1C = unk_79C->vf_03C();
    type_1CCA10 var_48 = unk_79C->get_unk_7C();
    RwInt32 var_18 = 0;
    RwInt32 var_30;
    RwInt32 var_5C;
    type_1D2CC0_check var_2C;
    RwInt32 var_70;
    RwInt32 var_14;
    RwInt32 var_64;
    RwInt32 var_58;
    RwInt32 var_44;
    RwInt32 var_34;
    RwInt32 var_6C;
    RwInt32 var_54;
    RwInt32 var_10;
    RwInt32 var_68;
    RwInt32 var_50;
    RwInt32 var_4C;

    unk_480[arg_0] = var_48;
    unk_4C4.unk_00[1] += arg_8;
    unk_4C4.unk_00[3] += arg_8 + 0x26;
    var_30 = var_40.sub_1F8560();
    if (var_30)
    {
        unk_4C4.unk_18[3]++;
        return 0;
    }
    var_5C = var_40.sub_1F8810(6);
    if (var_5C)
    {
        unk_4C4.unk_18[3]++;
        return 0;
    }
    var_60++;
    if (var_1C)
    {
        var_40.sub_1F8A40((RwChar *)var_2C.unk_00, 0x48);
        var_60 += 9;
    }
    if (unk_79C->vf_028(arg_0) == 1)
    {
        var_70 = 1;
        if (var_1C)
        {
            type_1D2CC0_check var_7C;

            var_7C.sub_73D90(arg_4 + var_60, arg_8 - var_60);
            if (arg_8 <= var_60 || !var_7C.sub_1F5A00(&var_2C))
                var_70 = 0;
        }
        if (!var_70)
            unk_79C->vf_02C(arg_0, 2);
    }
    if (unk_79C->vf_040(arg_0))
        unk_79C->vf_024(arg_0, (RwInt32)(arg_4 + var_60), arg_8 - var_60);
    if (var_1C)
    {
        type_1D2CC0_check var_88;

        var_88.sub_73D90(arg_4 + var_60, arg_8 - var_60);
        if (arg_8 <= var_60 || !var_88.sub_1F5A00(&var_2C))
        {
            unk_4C4.unk_18[3]++;
            if (unk_79C->vf_028(arg_0) == 2)
                unk_4C4.unk_18[4]++;
            return 0;
        }
    }
    var_14 = 0;
    var_64 = 0;
    while (var_40.sub_1F8560())
    {
        if (!var_14)
            var_64 = var_40.sub_1F8950();
        else
            var_64 += var_40.sub_1F8AF0();
        var_14++;
        sub_1D1AE0(var_64, arg_0);
    }
    var_58 = 0;
    var_44 = 0;
    var_34 = 0;
    var_6C = 1;
    while (var_40.sub_1F8560())
    {
        RwInt32 var_94;
        RwUInt32 var_90;
        RwInt32 var_98;
        type_3E4E84 *var_8C;

        if (var_6C)
        {
            var_6C = 0;
            var_44 = var_40.sub_1F8950();
            var_34 = var_40.sub_1F8AF0() + var_44;
        }
        else
        {
            var_44 += var_40.sub_1F8AF0();
            var_34 += var_40.sub_1F8AF0();
        }
        var_94 = var_40.sub_1F8950() + 1;
        var_90 = var_94 + var_40.get_unk_08();
        var_98 = var_44;
        if (!(var_44 & 3))
            sub_1D3C80(var_44, var_34, arg_0, &var_40, var_94);
        else
            sub_1D3770(var_44, var_34, arg_0, &var_40, var_94);
        unk_4C4.unk_210[arg_0] += var_94;
        var_8C = sub_1D1A30(var_98, arg_0);
        if (!var_8C)
        {
            type_3E4E84 var_AC;

            var_AC.unk_0C = var_48 + 0xA6;
            var_AC.unk_08 = var_48;
            var_AC.unk_12 = (RwUInt8)arg_0;
            var_AC.unk_13 = (RwUInt8)arg_0;
            var_AC.unk_10.unk_00 = 1 << arg_0;
            var_AC.unk_04 = var_98;
            if (!unk_34.sub_1D3F80(var_AC))
            {
                if (0)
                    off_42CD14("Just ran out of ram in ACK que!");
                unk_794 = 1;
            }
        }
        else
        {
            var_8C->unk_0C = var_48 + 0xA6;
            var_8C->unk_08 = var_48;
        }
        var_40.unk_08 = var_90;
        var_58++;
    }
    var_54 = 0;
    var_10 = 0;
    while (var_40.sub_1F8560())
    {
        RwInt32 var_B4;
        RwUInt32 var_B0;

        if (!var_54)
            var_10 = var_40.sub_1F8950();
        var_B4 = var_40.sub_1F8950() + 1;
        var_B0 = var_B4 + var_40.get_unk_08();
        unk_79C->sub_1CC7D0(var_10, arg_0, (RwInt32)&var_40, var_B4);
        unk_4C4.unk_1D0[arg_0] += var_B4;
        var_40.unk_08 = var_B0;
        var_54++;
    }
    var_68 = 0;
    var_50 = 0;
    var_4C = 0;
    if (arg_10)
    {
        type_1F8560 var_C4(arg_C, 0x2400);
        type_1F8560 *var_B8 = &var_C4;

        var_6C = 1;
        while (var_B8->sub_1F8560())
        {
            RwInt32 var_CC;
            RwUInt32 var_C8;

            if (var_6C)
            {
                var_6C = 0;
                var_50 = var_B8->sub_1F8950();
                var_4C = var_B8->sub_1F8AF0() + var_50;
            }
            else
            {
                var_50 += var_B8->sub_1F8AF0();
                var_4C += var_B8->sub_1F8AF0();
            }
            var_CC = var_B8->sub_1F8950() + 1;
            var_C8 = var_CC + var_B8->get_unk_08();
            unk_79C->sub_1CC8A0(var_50, var_4C, arg_0, (RwInt32)&var_C4, var_CC);
            unk_4C4.unk_250[arg_0] += var_CC;
            var_B8->unk_08 = var_C8;
            var_68++;
        }
    }
    unk_4C4.unk_18[2]++;
    unk_4C4.unk_290[arg_0] += 0x130;
    return 1;
}
