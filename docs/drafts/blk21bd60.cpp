// match: ?vf_03C@type_21A5E0@@UAEXXZ @ 0x0021BD60
void type_21A5E0::vf_03C()
{
    sub_20EA40();
    for (RwInt32 var_4C = 1; var_4C < 0x18; var_4C++)
    {
        unk_158[var_4C]->sub_20EA40();
        unk_158[var_4C]->vf_03C();
    }
    RwInt32 var_1C = dword_4FB9E0.get_unk_08();
    const RwChar *var_28 = "";
    RwInt32 var_20;

    switch (var_1C)
    {
    case 1:
        var_20 = 0;
        var_28 = "info_type_dm";
        break;
    case 2:
        var_20 = 0;
        var_28 = "info_type_tdm";
        break;
    case 8:
        var_20 = 1;
        var_28 = "info_type_sd";
        break;
    case 4:
        var_20 = 2;
        var_28 = "info_type_ctf";
        break;
    }
    unk_2B8.sub_1F28C0(type_1A5EA0(var_28, 0));
    sub_21C740();
    RwUInt32 var_18 = unk_4FDBB0.unk_28;
    LEVELS_CHECK(var_18);
    LEVELS_CHECK(var_18);
    type_505188 *var_48 = &dword_4FD974[var_18];
    const RwChar *var_14 = var_48->sub_1A5F60().c_str();
    RwInt32 var_10 = atol(var_14 + 3);

    if (var_18 < 8)
    {
        type_1A5EA0 var_6C("gui_map");

        var_6C.sub_21CA90(var_10).sub_1CA470(off_42D2AC[var_20]);
        unk_258 = sub_1ED040(var_6C.c_str());
        if (!unk_258.sub_E87C0())
        {
            type_1E3BA0_state *var_44[6];

            memset(var_44, 0, sizeof(var_44));
            type_1E7410 *var_2C = unk_258->sub_1ED630("map");
            var_44[0] = (type_1E3BA0_state *)var_2C;
            sub_1E3C10(var_44);
            type_1E3BA0 *var_24 = new type_1E3BA0(var_44, 0);
            unk_25C = var_24;
            if (unk_25C)
                unk_260.sub_1E7510(unk_25C);
            unk_290.sub_1F28C0(type_1A5EA0(var_48->sub_1A5F60().c_str(), 0));
        }
    }
}

