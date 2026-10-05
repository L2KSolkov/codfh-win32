// match: ?vf_008@type_3E6FA4@kujuUI@@UAEXPAUtype_1C8DF0@2@HHPAUtype_1ED670@2@PAUtype_3E7D08@2@PAPAU52@@Z @ 0x001E2C40
// match: __ehhandler$?vf_008@type_3E6FA4@kujuUI@@UAEXPAUtype_1C8DF0@2@HHPAUtype_1ED670@2@PAUtype_3E7D08@2@PAPAU52@@Z-0x65 @ 0x00303900
// match: __ehhandler$?vf_008@type_3E6FA4@kujuUI@@UAEXPAUtype_1C8DF0@2@HHPAUtype_1ED670@2@PAUtype_3E7D08@2@PAPAU52@@Z @ 0x00303965
void type_3E6FA4::vf_008(type_1C8DF0 *arg_0, RwInt32 arg_4, RwInt32 arg_8, type_1ED670 *arg_C, type_3E7D08 *arg_10,
                         type_3E7D08 **arg_14)
{
    type_1E0330_rect var_24(0, 0, 0, 0);
    const RwChar *var_10;
    RwInt32 var_14;

    if (sub_1F7D80(arg_0, arg_4, &var_10) == 1 && sub_1F7B10(arg_0, var_10, &var_24) == 1 &&
        sub_1F7E70(arg_0, arg_8, &var_14) == 1)
    {
        type_1E34A0 *var_80 = 0;
        type_1C8DF0_104 *var_3C = arg_0->sub_1C90B0(sub_1E35A0());
        RwInt32 var_30 = 0;

        if (arg_0->sub_1C90B0(&unk_5033F8))
            var_30 = 1;
        else if (arg_0->sub_1C90B0(&unk_503450))
            var_30 = 3;
        else if (arg_0->sub_1C90B0(&unk_503348))
            var_30 = 2;
        const RwChar *var_2C = 0;
        const RwChar *var_44 = 0;
        type_1C8DF0_104 *var_40 = arg_0->sub_1C90B0(&unk_50347C);
        type_1C8DF0_104 *var_34 = arg_0->sub_1C90B0(&unk_50331C);

        if (var_40)
            var_2C = (const RwChar *)var_40->sub_1C9890(0)->sub_1E3480();
        if (var_34)
            var_44 = (const RwChar *)var_34->sub_1C9890(0)->sub_1E3480();
        if (var_3C)
        {
            RwInt32 var_84 = var_3C->sub_1C9890(0)->sub_1E3480();

            arg_C->sub_1E0D50(var_84, 1, &var_80);
        }
        sub_1F7A60(arg_0, "a source");
        if (!var_3C)
        {
            if (0)
                sub_1C8A30("Widget factory - source missing! Widget \"%s\" type \"%s\"\n",
                           arg_0->sub_1C8FC0() ? arg_0->sub_1C8FC0() : "(none)", arg_0->sub_1C8FE0()->sub_1CA280());
        }
        sub_1F7A60(var_3C != 0, pResourcePath);
        type_1C8DF0_104 *var_28 = arg_0->sub_1C90B0(sub_1E3550());
        type_1CB670 var_78;
        RwUInt32 var_48 = 0;
        type_1E0330_rect var_58;
        RwUInt32 var_7C;

        if (var_28)
        {
            type_1C8DF0_104 *var_8C = arg_0->sub_1C90B0(&unk_5034D4);
            type_1C8DF0_104 *var_88 = arg_0->sub_1C90B0(&unk_5033CC);
            RwInt32 var_90 = sub_1F7F40(arg_0, &unk_5033CC, arg_8, &var_48);

            if (var_90 != 1)
            {
                if (0)
                    sub_1C8A30("Combobox - font not found: %s\n", unk_5033CC.unk_00);
            }
            if (var_8C && var_48)
            {
                var_78 = type_1CB670((const RwChar *)var_28->sub_1C9890(0)->sub_1E3480(), 0);
                var_58 = type_1E0330_rect((RwReal)var_8C->sub_1C9890(0)->sub_1E3480(),
                                         (RwReal)var_8C->sub_1C9890(1)->sub_1E3480(),
                                         (RwReal)var_8C->sub_1C9890(2)->sub_1E3480(),
                                         (RwReal)var_8C->sub_1C9890(3)->sub_1E3480());
                var_7C = arg_0->sub_1C90B0(&unk_5034A8) ? 0 : arg_0->sub_1C90B0(&unk_5033A0) ? 2 : 1;
            }
            else
            {
                if (0)
                    sub_1C8A30("Combobox - missing %s\n", unk_5034D4.unk_00);
            }
        }
        RwInt32 var_38 = arg_0->sub_1C90B0(sub_1E3570()) ? 0 : arg_0->sub_1C90B0(sub_1E3590()) ? 2 : 1;

        *arg_14 = new type_3E6F74(var_10, &var_24, sub_1F7FE0(arg_0), var_80, type_1CB670(var_2C, 0),
                                  type_1CB670(var_44, 0), var_14, var_78.empty() ? 0 : &var_78, &var_58, &var_7C, var_48,
                                  var_38, var_30, arg_10);
        sub_1F7CC0(arg_0, arg_C, static_cast<type_3E76B4 *>(*arg_14));
        sub_1F7DB0(arg_0, arg_C, static_cast<type_3E76B4 *>(*arg_14));
    }
}

