// match: ?sub_11CF50@type_10F710_1A48@@QAEXPAUtype_10F710@@@Z @ 0x0011CF50
void type_10F710_1A48::sub_11CF50(type_10F710 *arg_0)
{
    type_75600 frm_124;
    type_4E5D30 *local_f4;
    RwReal local_f0;
    RwV3d var_ec;
    RpIntersection frm_24;
    RwInt32 bp_8;
    RwInt32 bp_4;

    if (arg_0->unk_217C)
    {
        return;
    }
    var_ec.x = unk_448->unk_E0;
    var_ec.y = 50.0f;
    var_ec.z = unk_448->unk_E0;
    bp_4 = 0;
    type_93DF0 var_e0;
    frm_24.type = rpINTERSECTSPHERE;
    frm_24.t.sphere.center = *RwMatrixGetPos(RwFrameGetLTM(arg_0->get_unk_340()));
    frm_24.t.sphere.center.y -= 50.0f;
    frm_24.t.sphere.radius = var_ec.x;
    local_f0 = frm_24.t.sphere.radius * frm_24.t.sphere.radius;
    var_e0.unk_6C = 0;
    var_e0.unk_24 = local_f0;
    var_e0.unk_20 = 0;
    var_e0.unk_18 = 0;
    var_e0.unk_04 = arg_0;
    var_e0.unk_14 = arg_0->get_unk_340();
    var_e0.unk_0C = 0;
    var_e0.unk_08 = 0;
    var_e0.unk_60 = 0;
    var_e0.unk_64 = 0;
    var_e0.unk_7C = 0;
    var_e0.unk_28 = 0.0f;
    var_e0.unk_48 = arg_0->unk_50_r;
    var_e0.unk_50 = &bp_4;
    var_e0.unk_58 = 0;
    var_e0.unk_54 = 0;
    var_e0.unk_70 = sub_8F940();
    bp_8 = 0;
    for (bp_8 = 0; bp_8 < 4; bp_8++)
    {
        local_f4 = &dword_4E5D30[bp_8];
        if (local_f4->get_unk_00() && local_f4->get_unk_28())
        {
            RpWorldForAllAtomicIntersections(local_f4->get_unk_28(), &frm_24, sub_104D00, &var_e0);
        }
    }
    if (var_e0.unk_28 != 0.0f && var_e0.unk_08)
    {
        if (get_4FB9F8() || (var_e0.unk_08->unk_2C & 7) != (unk_42C->unk_2C & 7))
        {
            memset(&frm_124, 0, sizeof(type_75600));
            frm_124.unk_00_w = 0;
            frm_124.unk_02_w = 1;
            if ((unk_42C->unk_2C & 7) == 2)
            {
                frm_124.unk_08 = 0x202;
            }
            else
            {
                frm_124.unk_08 = 0x201;
            }
            frm_124.unk_14 = 0;
            frm_124.unk_18 = 0;
            if ((var_e0.unk_08->vf_008() || var_e0.unk_08->vf_024())
                && and_sides(arg_0->unk_2C & 7, var_e0.unk_08->unk_2C & 7))
            {
                frm_124.unk_28 = 0.0f;
                frm_124.unk_2C = 0.0f;
            }
            else
            {
                frm_124.unk_28 = unk_448->unk_DC_f;
                frm_124.unk_2C = unk_448->unk_DC_f;
            }
            frm_124.unk_0C = arg_0;
            frm_124.unk_10 = arg_0->unk_2C;
            frm_124.unk_24 = var_e0.unk_08->vf_07C(2, &frm_24, 0, 0);
            var_e0.unk_08->vf_064(&frm_124);
            var_e0.unk_08->unk_1C0.sub_8A980(&dword_4AF030, (type_3D3548 *)this, 0, var_e0.unk_08->sub_CD550(), 0,
                                             0);
        }
    }
}
