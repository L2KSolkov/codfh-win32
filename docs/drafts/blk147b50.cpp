
// match: ?sub_147B50@type_3DBC78_450@@QAEXPAUtype_712B0_3DBC78@@PAUtype_3D3548@@M@Z @ 0x00147B50
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
// Steps the body by arg_8 (at most 3): the trigger arg_0 resets its
// position while dword_4D50F8 counts down, and a player on a mounted
// weapon (posture 5) aboard arg_4 marks it (unk_2A0). Then come the
// steering torque, the grip, gravity and drag, the contacts (sub_149F80 for
// gimp level 2, else sub_14A250), their impulses, and the velocity capped
// at the top speed. Its moves (unk_148, unk_13C) come last.
void type_3DBC78_450::sub_147B50(type_712B0_3DBC78 *arg_0, type_3D3548 *arg_4, RwReal arg_8)
{
    RwReal zE0;
    RwReal locDC;
    RwV3d var_D8;
    RwV3d lcl_CC;
    RwReal vC0;
    type_149920 var_BC;
    RwV3d frm_A4;
    RwReal l98;
    RwReal var94;
    RwReal x90;
    RwReal ebp_8C;
    RwReal loc88;
    RwReal u84;
    RwReal frm_80;
    RwReal bp_7C;
    RwReal var_78;
    RwReal var_74;
    RwReal var70;
    RwReal stk_6C;
    RwReal q68;
    RwV3d var_64;
    RwV3d stk_58;
    RwV3d x4C;
    RwMatrix *var_40;
    RwV3d l3C;
    RwV3d lv_30;
    RwV3d frm_24;
    type_3D3548 *m_18;
    RwInt32 ebp_14;
    RwReal lv_10;
    RwInt32 var_C;
    RwReal bp_8;
    RwReal bp_4;

    if (!unk_104)
    {
        zero_v3d(&unk_148);
        zero_v3d(&unk_13C);
        zero_v3d(&unk_124);
        zero_v3d(&unk_130);
        return;
    }
    sub_147A20(unk_310);
    if (arg_8 > 3.0f)
        arg_8 = 3.0f;
    unk_350 = arg_8;
    lv_30 = unk_170.pos;
    unk_2A0 = 0;
    m_18 = sub_1745A0(0);
    if (m_18 && ((type_10F710 *)m_18)->unk_19D0 == 5 && m_18->vf_200() == arg_4)
        unk_2A0 = 1;
    ebp_14 = unk_230 || unk_234;
    if (dword_4D50F8)
    {
        unk_170.pos = arg_0->unk_90;
        unk_170.pos.y += 100.0f;
        zero_v3d(&unk_124);
        zero_v3d(&unk_130);
        set_xyz(&unk_170.right, 1.0f, 0.0f, 0.0f);
        set_xyz(&unk_170.up, 0.0f, 1.0f, 0.0f);
        set_xyz(&unk_170.at, 0.0f, 0.0f, 1.0f);
        dword_4D50F8--;
    }
    unk_27C = 0;
    set_xyz(&var_64, 0.0f, 0.0f, unk_280.z);
    set_xyz(&stk_58, 0.0f, 0.0f, unk_28C.z);
    if (sub_14C520(&var_64) || sub_14C520(&stk_58))
    {
        unk_27C = 1;
        unk_124.y = 0.0f;
    }
    if (unk_27C && !unk_2A0)
        return;
    l3C = unk_124;
    sub_14C340();
    if (arg_0)
    {
        unk_24C = (RwReal)arg_0->unk_F0;
        unk_254 = (RwReal)arg_0->unk_F4;
    }
    lv_10 = 1.0f / unk_350;
    zero_v3d(&unk_10C);
    zero_v3d(&unk_118);
    var_40 = &unk_170;
    unk_1F0 = *var_40;
    RwMatrixInvert(&unk_1B0, var_40);
    bp_4 = unk_244;
    if (fabs(unk_23C) > 0.01f && !ebp_14)
        bp_4 = unk_23C;
    if (unk_298 || unk_27C)
    {
        var70 = RwV3dDotProduct(&unk_170.up, &dword_429D90);
        if ((RwReal)fabs((RwDouble)var70) < flt_429D88)
        {
            var_74 = ((RwReal)fabs((RwDouble)var70) - flt_429D84) / (flt_429D88 - flt_429D84);
            if (var_74 < 0.0f)
                var_74 = 0.0f;
            if (var_74 > 1.0f)
                var_74 = 1.0f;
            bp_4 = bp_4 * var_74;
        }
        if (bp_4 > 0.01f || bp_4 < -0.01f)
        {
            var_78 = unk_238 * unk_350;
            if (var_78 > 0.5f)
                var_78 = 0.5f;
            bp_7C = 1.0f - var_78;
            if (bp_4 < 0.0f)
                var_78 = -var_78;
            frm_80 = bp_4 * bp_7C + var_78;
            set_xyz(&x4C, 0.0f, 0.0f, 0.0f);
            set_xyz(&frm_24, 0.0f, 0.0f, frm_80 * unk_254 * flt_429D2C);
            sub_141320(&x4C, &x4C, var_40);
            sub_141320(&frm_24, &frm_24, var_40);
            sub_149780(&x4C, &frm_24);
        }
        stk_6C = unk_248;
        if (unk_29C)
        {
            u84 = PVSFindDiagonalSizeOfBBox((RwBBox *)&unk_124);
            if (u84 > 15.0f)
                u84 = 15.0f;
            loc88 = RwV3dDotProduct(&unk_124, &unk_170.at);
            stk_6C = u84 * 0.5f * unk_248;
            if (loc88 < 0.0f)
                stk_6C = stk_6C * -1.0f;
        }
        if (unk_2A0)
            q68 = dword_429D04;
        else
            q68 = 0.7f;
        set_xyz(&x4C, -150.0f, -113.0f, 0.0f);
        set_xyz(&frm_24, 0.0f, 0.0f, q68 * unk_254 * stk_6C);
        sub_141320(&x4C, &x4C, var_40);
        sub_141320(&frm_24, &frm_24, var_40);
        sub_149780(&x4C, &frm_24);
        set_xyz(&x4C, 150.0f, -113.0f, 0.0f);
        set_xyz(&frm_24, 0.0f, 0.0f, -unk_254 * q68 * stk_6C);
        sub_141320(&x4C, &x4C, var_40);
        sub_141320(&frm_24, &frm_24, var_40);
        sub_149780(&x4C, &frm_24);
    }
    if ((RwReal)fabs((RwDouble)bp_4) > 0.05f)
        unk_230 = 0;
    if (unk_298 && (RwReal)fabs((RwDouble)bp_4) < 0.01f && fabs(unk_248) < 0.1f)
    {
        x90 = PVSFindDiagonalSizeOfBBox((RwBBox *)&unk_124);
        var94 = 0.6f;
        var94 = (RwReal)fabs((RwDouble)(ebp_8C = RwV3dDotProduct(&unk_170.at, &dword_429D90))) * flt_429D78 * var94;
        if (x90 < var94)
            unk_234 = 1;
    }
    else
    {
        unk_234 = 0;
        if (unk_2A0)
            unk_230 = 0;
    }
    if (!unk_27C)
        unk_10C.y += flt_429D28;
    set_xyz(&x4C, 0.0f, 0.0f, 0.0f);
    if (unk_298)
    {
        unk_10C.x += -unk_124.x * flt_429D18;
        unk_10C.y += -unk_124.y * flt_429D18;
        unk_10C.z += -unk_124.z * flt_429D18;
        unk_118.x += -unk_130.x * flt_429D1C;
        unk_118.y += -unk_130.y * flt_429D1C;
        unk_118.z += -unk_130.z * flt_429D1C;
    }
    bp_8 = PVSFindDiagonalSizeOfBBox((RwBBox *)&unk_10C);
    if (bp_8 > 2.0f)
    {
        RwV3dNormalize(&unk_10C, &unk_10C);
        RwV3dScale(&unk_10C, &unk_10C, 2.0f);
    }
    sub_149AA0();
    if (unk_108 == 2)
        var_C = sub_149F80(0);
    else
        var_C = sub_14A250(arg_4, unk_350, 0);
    if (var_C)
    {
        zero_v3d(&var_BC.unk_00);
        zero_v3d(&var_BC.unk_0C);
        RwV3dSub(&lcl_CC, &lv_30, &unk_170.pos);
        sub_141320(&var_D8, &lcl_CC, &unk_1B0);
        sub_149F00(&x4C, 0.0f, 0.0f, 0.0f);
        vC0 = RwV3dDotProduct(&unk_170.right, &dword_429D90);
        if ((RwReal)fabs((RwDouble)vC0) < 0.34f)
        {
            unk_274 = dword_429D3C;
            locDC = ((RwReal)ebp_14 + unk_274) * unk_350 * unk_350;
            if (var_D8.x > locDC)
                var_D8.x = locDC;
            if (-locDC > var_D8.x)
                var_D8.x = -locDC;
            sub_149F00(&frm_A4, var_D8.x * flt_429D34 * unk_24C, 0.0f, 0.0f);
            sub_149920(&var_BC, &x4C, &frm_A4);
        }
        unk_278 = dword_429D40;
        zE0 = ((RwReal)ebp_14 + unk_278) * unk_350 * unk_350;
        if (var_D8.z > zE0)
            var_D8.z = zE0;
        if (-zE0 > var_D8.z)
            var_D8.z = -zE0;
        sub_149F00(&frm_A4, 0.0f, 0.0f, var_D8.z * flt_429D34 * unk_24C);
        sub_149920(&var_BC, &x4C, &frm_A4);
        sub_149D60(&var_BC);
        var_D8.x = (unk_170.pos.x - lv_30.x) * lv_10;
        var_D8.y = (unk_170.pos.y - lv_30.y) * lv_10;
        var_D8.z = (unk_170.pos.z - lv_30.z) * lv_10;
        RwV3dSub(&lcl_CC, &var_D8, &unk_124);
        l98 = PVSFindDiagonalSizeOfBBox((RwBBox *)&lcl_CC);
        if (2.5f * unk_350 < l98)
        {
            RwV3dNormalize(&lcl_CC, &lcl_CC);
            RwV3dScale(&lcl_CC, &lcl_CC, 2.5f * unk_350);
        }
        unk_124.x += lcl_CC.x;
        unk_124.y += lcl_CC.y;
        unk_124.z += lcl_CC.z;
        if (dword_429D74)
        {
            l98 = PVSFindDiagonalSizeOfBBox((RwBBox *)&unk_124);
            if (l98 > unk_268)
            {
                RwV3dNormalize(&unk_124, &unk_124);
                RwV3dScale(&unk_124, &unk_124, unk_268);
            }
        }
        unk_298 = 1;
    }
    else
    {
        unk_298 = 0;
    }
    RwV3dSub(&unk_148, &unk_170.pos, &lv_30);
    RwV3dScale(&unk_148, &unk_148, lv_10);
    RwV3dSub(&unk_13C, &l3C, &unk_124);
}
