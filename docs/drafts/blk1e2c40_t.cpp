inline RwInt32 f_(RwInt32 arg_0)
{
    return arg_0 + 1;
}
// match: ?vf_008@type_3E6FA4@kujuUI@@UAEXPAUtype_1C8DF0@2@HHPAUtype_1ED670@2@PAUtype_3E7D08@2@PAPAU52@@Z @ 0x001E2C40
// match: __ehhandler$?vf_008@type_3E6FA4@kujuUI@@UAEXPAUtype_1C8DF0@2@HHPAUtype_1ED670@2@PAUtype_3E7D08@2@PAPAU52@@Z-0x65 @ 0x00303900
// match: __ehhandler$?vf_008@type_3E6FA4@kujuUI@@UAEXPAUtype_1C8DF0@2@HHPAUtype_1ED670@2@PAUtype_3E7D08@2@PAPAU52@@Z @ 0x00303965
void type_3E6FA4::vf_008(type_1C8DF0 *arg_0, RwInt32 arg_4, RwInt32 arg_8, type_1ED670 *arg_C, type_3E7D08 *arg_10,
                         type_3E7D08 **arg_14)
{
    type_1E0330_rect lv_24(0, 0, 0, 0);
    const RwChar *lv_10;
    RwInt32 lv_14;

    if (sub_1F7D80(arg_0, arg_4, &lv_10) == 1 && sub_1F7B10(arg_0, lv_10, &lv_24) == 1 &&
        sub_1F7E70(arg_0, arg_8, &lv_14) == 1)
    {
        type_1E34A0 *lv_80 = 0;
        type_1C8DF0_104 *lv_3C = arg_0->sub_1C90B0(sub_1E35A0());
        RwInt32 lv_30 = 0;

        if (arg_0->sub_1C90B0(&unk_5033F8))
            lv_30 = 1;
        else if (arg_0->sub_1C90B0(&unk_503450))
            lv_30 = 3;
        else if (arg_0->sub_1C90B0(&unk_503348))
            lv_30 = 2;
        const RwChar *lv_2C = 0;
        const RwChar *lv_44 = 0;
        type_1C8DF0_104 *lv_40 = arg_0->sub_1C90B0(&unk_50347C);
        type_1C8DF0_104 *lv_34 = arg_0->sub_1C90B0(&unk_50331C);

        if (lv_40)
            lv_2C = (const RwChar *)lv_40->sub_1C9890(0)->sub_1E3480();
        if (lv_34)
            lv_44 = (const RwChar *)lv_34->sub_1C9890(0)->sub_1E3480();
        if (lv_3C)
        {
            RwInt32 lv_84 = lv_3C->sub_1C9890(0)->sub_1E3480();

            arg_C->sub_1E0D50(lv_84, 1, &lv_80);
        }
        sub_1F7A60(arg_0, "a source");
        if (!lv_3C)
        {
            if (0)
                sub_1C8A30("Widget factory - source missing! Widget \"%s\" type \"%s\"\n",
                           arg_0->sub_1C8FC0() ? arg_0->sub_1C8FC0() : "(none)", arg_0->sub_1C8FE0()->sub_1CA280());
        }
        sub_1F7A60(lv_3C != 0, pResourcePath);
        type_1C8DF0_104 *lv_28 = arg_0->sub_1C90B0(sub_1E3550());
        type_1CB670 lv_78;
        RwUInt32 lv_48 = 0;
        type_1E0330_rect lv_58;
        RwUInt32 lv_7C;

        if (lv_28)
        {
            type_1C8DF0_104 *lv_8C = arg_0->sub_1C90B0(&unk_5034D4);
            type_1C8DF0_104 *lv_88 = arg_0->sub_1C90B0(&unk_5033CC);
            RwInt32 lv_90 = sub_1F7F40(arg_0, &unk_5033CC, arg_8, &lv_48);

            if (lv_90 != 1)
            {
                if (0)
                    sub_1C8A30("Combobox - font not found: %s\n", unk_5033CC.unk_00);
            }
            if (lv_8C && lv_48)
            {
                lv_78 = type_1CB670((const RwChar *)lv_28->sub_1C9890(0)->sub_1E3480(), 0);
                lv_58 = type_1E0330_rect((RwReal)lv_8C->sub_1C9890(0)->sub_1E3480(),
                                         (RwReal)lv_8C->sub_1C9890(1)->sub_1E3480(),
                                         (RwReal)lv_8C->sub_1C9890(2)->sub_1E3480(),
                                         (RwReal)lv_8C->sub_1C9890(3)->sub_1E3480());
                lv_7C = arg_0->sub_1C90B0(&unk_5034A8) ? 0 : f_(arg_0->sub_1C90B0(&unk_5033A0) != 0);
            }
            else
            {
                if (0)
                    sub_1C8A30("Combobox - missing %s\n", unk_5034D4.unk_00);
            }
        }
        RwInt32 lv_38 = arg_0->sub_1C90B0(sub_1E3570()) ? 0 : f_(arg_0->sub_1C90B0(sub_1E3590()) != 0);

        *arg_14 = new type_3E6F74(lv_10, &lv_24, sub_1F7FE0(arg_0), lv_80, type_1CB670(lv_2C, 0),
                                  type_1CB670(lv_44, 0), lv_14, lv_78.empty() ? 0 : &lv_78, &lv_58, &lv_7C, lv_48,
                                  lv_38, lv_30, arg_10);
        sub_1F7CC0(arg_0, arg_C, static_cast<type_3E76B4 *>(*arg_14));
        sub_1F7DB0(arg_0, arg_C, static_cast<type_3E76B4 *>(*arg_14));
    }
}

