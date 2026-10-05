// match: ?sub_1EA260@type_3E7490@kujuUI@@QAEXXZ @ 0x001EA260
void type_3E7490::sub_1EA260()
{
    RwUInt32 var_10 = sub_1EB090();
    type_1E0330_rect var_20(0, unk_104.unk_04, 0, unk_104.unk_04 + unk_F0);
    std::vector<type_3E74C0 *>::iterator var_8 = row_at(&unk_0C, unk_F8);
    std::vector<type_3E74C0 *>::iterator var_C = std::vector<type_3E74C0 *>::iterator(unk_0C.end());
    RwInt32 var_4 = 0;

    while (var_8 != var_C && var_4 != unk_F4)
    {
        type_3E74C0 *var_24 = *var_8;
        var_20.unk_00 = unk_104.unk_00;
        var_20.unk_08 = unk_104.unk_00;
        for (RwUInt32 var_28 = 0; var_28 < var_10; ++var_28)
        {
            RwUInt32 var_2C = unk_100->unk_0C[var_28].unk_00;
            var_20.unk_08 += (RwReal)var_2C;
            var_24->sub_1EC370(&var_20, var_28);
            var_20.unk_00 += (RwReal)var_2C;
        }
        var_20.unk_04 += unk_F0;
        var_20.unk_0C += unk_F0;
        ++var_8;
        ++var_4;
    }
    unk_115 = false;
}
