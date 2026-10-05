// match: ?sub_1F3510@cTopLayoutPage@kujuUI@@QAEXXZ @ 0x001F3510
void cTopLayoutPage::sub_1F3510()
{
    if (0)
        sub_1C8A30("Parsing file %s\n", unk_80.c_str());
    RwInt32 var_14 = 0;
    type_1C8DF0_104 *var_2448 = unk_9C->sub_1E3480()->sub_1C90B0(sub_1F2920()->get_unk_A60());
    type_1C8DF0_104 *var_44 = 0;

    if (!var_2448)
    {
        var_44 = unk_9C->sub_1E3480()->sub_1C90B0(sub_1F2920()->get_unk_A8C());
        if (var_44)
            var_14 = 1;
    }
    else
        var_14 = 2;
    bool var_35 = (bool)(var_44 || var_2448);
    type_1C8DF0_104 *var_34 = var_35 ? unk_9C->sub_1E3480()->sub_1C90B0(sub_1F2920()->get_unk_AB8()) : 0;

    if (var_35 && !var_34)
    {
        if (0)
            sub_1C8A30("Missing border dimensions!\n");
    }
    type_3E7D08 *var_30 = 0;
    RwUInt32 var_10 = 0;
    type_1C8DF0 *var_40 = unk_9C->sub_1E3480();
    type_1EFCF0<type_3E7D08 *> *var_20 = unk_A4;
    type_1F31C0_entry var_2444[256];

    sub_1EDBC0(var_40->sub_1C9090() - unk_B8.sub_1E10A0() - unk_AC.sub_1E10A0() + var_14);
    for (RwUInt32 var_244C = 0; var_244C != var_40->sub_1C9090(); ++var_244C)
    {
        type_1C8DF0 *var_2454 = var_40->sub_1E3BF0(var_244C);
        const cScopeValidator *var_2450 = var_2454->sub_1C8FE0();

        if (var_2450 != sub_1E3CD0() && var_2450 != sub_1E6590())
        {
            type_3E7D08 *var_2458 = 0;

            sub_1F2920()->create_(var_2454, &unk_AC, &unk_B8, unk_A0, this, &var_2458);
            if (var_2458)
            {
                if (var_20)
                {
                    const RwChar *var_2464 = var_2454->sub_1C8FC0();

                    if (var_2464)
                    {
                        type_3E7D08 **var_2468 = var_20->sub_1ED670(var_2464);

                        if (var_2468)
                            *var_2468 = var_2458;
                    }
                }
                sub_1E8A20(var_2458);
                if (!var_30 && var_2458->vf_010())
                    var_30 = var_2458;
                const RwChar *var_245C = var_2454->sub_1C8FC0();
                type_1F31C0_entry *var_2460 = &var_2444[var_10];

                var_2460->unk_00 = var_2458;
                var_2460->unk_04 = var_245C;
                var_2460->unk_08[0] = sub_1F3270(sub_1E35D0(), var_2454);
                var_2460->unk_08[1] = sub_1F3270(sub_1E35E0(), var_2454);
                var_2460->unk_08[2] = sub_1F3270(sub_1E35B0(), var_2454);
                var_2460->unk_08[3] = sub_1F3270(sub_1E35C0(), var_2454);
                var_2460->unk_08[4] = sub_1F3270(sub_1E35F0(), var_2454);
                var_2460->unk_08[5] = sub_1F3270(sub_1E3600(), var_2454);
                var_2460->unk_08[6] = sub_1F3270(sub_1E3610(), var_2454);
                var_10++;
            }
        }
    }
    type_1C8DF0_104 *var_1C = var_40->sub_1C90B0(sub_1E3740());
    type_1C8DF0_104 *var_18 = var_40->sub_1C90B0(sub_1E3750());
    type_1C8DF0_104 *var_2C = var_40->sub_1C90B0(sub_1E3760());
    type_1C8DF0_104 *var_3C = var_40->sub_1C90B0(sub_1E3770());

    if (var_1C)
    {
        type_1DFE80_target *var_246C;

        unk_A0->sub_1E0D50(var_1C->sub_1C9890(0)->sub_1E3480(), 0, &var_246C);
        sub_1F43D0(7, var_246C);
    }
    if (var_18)
    {
        type_1DFE80_target *var_2470;

        unk_A0->sub_1E0D50(var_18->sub_1C9890(0)->sub_1E3480(), 0, &var_2470);
        sub_1F43D0(4, var_2470);
    }
    if (var_2C)
    {
        type_1DFE80_target *var_2474;

        unk_A0->sub_1E0D50(var_2C->sub_1C9890(0)->sub_1E3480(), 0, &var_2474);
        sub_1F43D0(5, var_2474);
    }
    if (var_3C)
    {
        type_1DFE80_target *var_2478;

        unk_A0->sub_1E0D50(var_3C->sub_1C9890(0)->sub_1E3480(), 0, &var_2478);
        sub_1F43D0(6, var_2478);
    }
    for (RwUInt32 var_247C = 0; var_247C != var_10; ++var_247C)
    {
        type_1F31C0_entry *var_2480 = &var_2444[var_247C];

        sub_1F3230(var_2480->unk_00, var_2480->unk_08[6], var_2444, var_10, 14, this);
        sub_1F3230(var_2480->unk_00, var_2480->unk_08[0], var_2444, var_10, 0, this);
        sub_1F3230(var_2480->unk_00, var_2480->unk_08[1], var_2444, var_10, 1, this);
        sub_1F3230(var_2480->unk_00, var_2480->unk_08[2], var_2444, var_10, 2, this);
        sub_1F3230(var_2480->unk_00, var_2480->unk_08[3], var_2444, var_10, 3, this);
        sub_1F3230(var_2480->unk_00, var_2480->unk_08[4], var_2444, var_10, 7, this);
        sub_1F3230(var_2480->unk_00, var_2480->unk_08[5], var_2444, var_10, 4, this);
    }
    type_1C8DF0_104 *var_28 = var_40->sub_1C90B0(sub_1F2920()->get_unk_A08());
    type_3E7D08 *var_24 = 0;

    if (var_28)
    {
        var_24 = sub_1F31C0((const RwChar *)var_28->sub_1C9890(0)->sub_1E3480(), var_2444, var_10);
        if (var_24)
            sub_1E8A40(var_24);
    }
    if (!sub_1E8BB0() && var_30)
        sub_1E8A40(var_30);
    sub_1E8C30(var_40->sub_1C90B0(sub_1F2920()->get_unk_A34()) != 0);
    if (var_2448 && var_34)
    {
        type_1E6350 *var_2484 = unk_B8.sub_1ED670((const RwChar *)var_2448->sub_1C9890(1)->sub_1E3480());

        if (var_2484)
        {
            type_1A5EA0 var_24A4((const RwChar *)var_2448->sub_1C9890(0)->sub_1E3480(), 0);

            sub_1F4540(var_24A4, var_2484, var_34->sub_1C9890(0)->sub_1E3480(), var_34->sub_1C9890(1)->sub_1E3480(),
                       var_34->sub_1C9890(2)->sub_1E3480());
        }
        else if (0)
            sub_1C8A30("Missing font in page title: %s\n", unk_80.c_str());
    }
    else if (var_44 && var_34)
        sub_1F4540(type_1CB670(), 0, var_34->sub_1C9890(0)->sub_1E3480(), var_34->sub_1C9890(1)->sub_1E3480(),
                   var_34->sub_1C9890(2)->sub_1E3480());
    delete unk_9C;
    unk_9C = 0;
    unk_A0 = 0;
    unk_AC.sub_1E1080();
    unk_B8.sub_1E1080();
    unk_A8 = 5;
    vf_038();
}

