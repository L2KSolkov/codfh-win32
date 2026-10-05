// match: ?sub_1EA260@type_3E7490@kujuUI@@QAEXXZ @ 0x001EA260
void type_3E7490::sub_1EA260()
{
    RwUInt32 var_10 = sub_1EB090();
    type_1E0330_rect var_20(0, unk_104.unk_04, 0, unk_104.unk_04 + unk_F0);
    std::vector<type_3E74C0 *>::iterator var_8 = unk_0C.begin() + unk_F8;
    std::vector<type_3E74C0 *>::iterator var_C = unk_0C.end();
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

// match: ?sub_1EA980@type_3E7490@kujuUI@@QAEXPAUtype_3E74C0@2@H@Z @ 0x001EA980
void type_3E7490::sub_1EA980(type_3E74C0 *arg_0, RwInt32 arg_4)
{
    std::vector<type_3E74C0 *>::iterator var_4 = arg_4 == 0 ? unk_0C.begin() : unk_0C.begin() + arg_4;
    unk_0C.insert(var_4, arg_0);
    arg_0->sub_1EBFA0(this);
    if (sub_1EA410() && arg_4 <= unk_FC)
        ++unk_FC;
    unk_115 = true;
}

// match: ?sub_1EAA50@type_3E7490@kujuUI@@QAEXH@Z @ 0x001EAA50
void type_3E7490::sub_1EAA50(RwInt32 arg_0)
{
    std::vector<type_3E74C0 *>::iterator var_4 = unk_0C.begin() + arg_0;
    (*var_4)->sub_1EC110();
    unk_0C.erase(var_4);
    if (unk_FC > arg_0)
        --unk_FC;
    if (arg_0 < unk_F8)
        --unk_F8;
    unk_115 = true;
}
