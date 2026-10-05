// match: sub_3E2C0 @ 0x0003E2C0
void type_3DF30::sub_3E2C0(type_365A0 arg_0)
{
    type_3CE6D0 *var_4 = sub_3D3E0(arg_0.unk_00);

    var_4->vf_004(this);
    type_3CE6D0 *var_C = sub_3D3E0(unk_2A8);
    type_3CE6D0 *var_8 = 0;

    while (var_C && var_C->vf_02C() < var_4->vf_02C())
    {
        var_8 = var_C;
        var_C = sub_3D3E0(var_C->get_unk_14().unk_00);
    }
    if (var_8)
    {
        var_4->set_unk_14(var_8->get_unk_14());
        var_8->set_unk_14(var_4->get_unk_18());
    }
    else
    {
        var_4->set_unk_14(unk_2A8_h);
        unk_2A8_h = var_4->get_unk_18();
    }
}

