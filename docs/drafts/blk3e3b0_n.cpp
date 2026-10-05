// match: sub_3E3B0 @ 0x0003E3B0
void type_3DF30::sub_3E3B0(RwUInt32 arg_0)
{
    type_3CE6D0 *bp_4 = sub_3D3E0(arg_0);

    if (bp_4 && unk_2C0[bp_4->vf_030()])
        return;
    type_3CE6D0 *rC = sub_3D3E0(unk_2A8);
    type_3CE6D0 *x8 = 0;

    while (rC && rC != bp_4)
    {
        x8 = rC;
        rC = sub_3D3E0(rC->get_unk_14().unk_00);
    }
    if (x8)
        x8->set_unk_14(rC->get_unk_14());
    else
        unk_2A8_h = sub_3D3E0(unk_2A8)->get_unk_14();
    for (type_3D3548 *var_10 = unk_00; var_10; var_10 = var_10->vf_118())
    {
        if (var_10->vf_120())
        {
            if (sub_3D3E0(var_10->vf_120()->get_unk_574_h().unk_00) == bp_4)
            {
                bp_4->vf_014(var_10);
                rC = sub_3D3E0(unk_2A8);
                while (rC)
                {
                    if (rC->vf_018(var_10))
                        break;
                    rC = sub_3D3E0(rC->get_unk_14().unk_00);
                }
            }
        }
    }
    sub_3D0B0(bp_4->get_unk_18());
}

