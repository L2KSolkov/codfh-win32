// match: sub_3E2C0 @ 0x0003E2C0
void type_3DF30::sub_3E2C0(type_365A0 arg_0)
{
    type_3CE6D0 *bp_4 = sub_3D3E0(arg_0.unk_00);

    bp_4->vf_004(this);
    type_3CE6D0 *rC = sub_3D3E0(unk_2A8);
    type_3CE6D0 *x8 = 0;

    while (rC && rC->vf_02C() < bp_4->vf_02C())
    {
        x8 = rC;
        rC = sub_3D3E0(rC->get_unk_14().unk_00);
    }
    if (x8)
    {
        bp_4->set_unk_14(x8->get_unk_14());
        x8->set_unk_14(bp_4->get_unk_18());
    }
    else
    {
        bp_4->set_unk_14(unk_2A8_h);
        unk_2A8_h = bp_4->get_unk_18();
    }
}

