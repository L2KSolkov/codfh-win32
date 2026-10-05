// match: sub_3E3B0 @ 0x0003E3B0
void type_3DF30::sub_3E3B0(RwUInt32 arg_0)
{
    type_3CE6D0 *var_4 = sub_3D3E0(arg_0);

    if (var_4 && unk_2C0[var_4->vf_030()])
        return;
    type_3CE6D0 *var_C = sub_3D3E0(unk_2A8);
    type_3CE6D0 *var_8 = 0;

    while (var_C && var_C != var_4)
    {
        var_8 = var_C;
        var_C = sub_3D3E0(var_C->get_unk_14().unk_00);
    }
    if (var_8)
        var_8->set_unk_14(var_C->get_unk_14());
    else
        unk_2A8_h = sub_3D3E0(unk_2A8)->get_unk_14();
    for (type_3D3548 *var_10 = unk_00; var_10; var_10 = var_10->vf_118())
    {
        if (var_10->vf_120())
        {
            if (sub_3D3E0(var_10->vf_120()->get_unk_574_h().unk_00) == var_4)
            {
                var_4->vf_014(var_10);
                var_C = sub_3D3E0(unk_2A8);
                while (var_C)
                {
                    if (var_C->vf_018(var_10))
                        break;
                    var_C = sub_3D3E0(var_C->get_unk_14().unk_00);
                }
            }
        }
    }
    sub_3D0B0(var_4->get_unk_18());
}

