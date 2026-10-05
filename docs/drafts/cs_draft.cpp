// The collision step. From its last place (unk_440) towards the new one
// (unk_434), in two steps when the time is long or a wall is met (then the
// target is pulled 10 back from the wall), the eye height springs back
// (unk_524); each step moves the frame and collides it (sub_96EF0) with
// radii by its stance, keeping 0.01 off a wall. A pulse zone's charge dies
// on landing; the highest point of a fall is kept, a fall too long by its
// time kills it, and landing (from a jump or a fall) sets its jump's wait,
// its landing sound (by the surface) or its fall damage by the height (a
// damage message of 100 past the trigger's limit), and the surface under
// it. The frame then springs to the result (sub_112DA0 on each axis).
// match: ?vf_044@type_10F710@@UAEXM@Z @ 0x00113010
void type_10F710::vf_044(RwReal arg_0)
{
    RwFrame *v_4;
    type_4E5E40_08 *v_8;
    RwMatrix *v_C;
    type_4E5E40 *v_10;
    RwV3d v_1C;
    RwV3d v_28;
    RwV3d v_34;
    RwV3d v_40;
    RwInt32 v_44;
    RwV3d *v_48;
    RwReal v_4C;
    RwV3d v_58;
    RwInt32 v_5C;
    RwV3d v_68;
    RwInt32 v_6C;
    RwReal v_70;
    RwInt32 v_74;
    RwV3d v_80;
    RwInt32 v_84;
    RwInt32 v_88;
    RwReal v_8C;
    RwV3d v_98;
    type_712B0_10F710 *v_9C;
    RwReal v_A0;
    RwReal v_A4;
    RwReal v_B8;
    RwReal v_BC;
    RwReal v_C0;

    v_10 = &dword_4E5E40;
    v_8 = v_10->unk_08;
    v_4 = unk_338.unk_08;
    if (!v_4)
        return;
    if ((v_C = RwFrameGetMatrix(v_4)) == 0)
        return;
    v_48 = &v_C->pos;
    v_1C = *v_48;
    RwV3dSubMacro(&v_40, &unk_434, &unk_440);
    if (arg_0 > 2.0f)
    {
        v_44 = 2;
        RwV3dScaleMacro(&v_40, &v_40, 0.5f);
    }
    else
        v_44 = 1;
    if (sub_FCAE0(&unk_440, &unk_434, &v_34, &v_28, 0x10000, 1, 0))
    {
        RwV3dSubMacro(&v_58, &unk_440, &v_34);
        v_4C = PVSFindDiagonalSizeOfBBox((RwBBox *)&v_58);
        if (v_4C != 0.0f)
        {
            RwV3dScaleMacro(&v_58, &v_58, 10.0f / v_4C);
            RwV3dAddMacro(&unk_434, &v_34, &v_58);
            if (v_44 == 1)
            {
                v_44 = 2;
                RwV3dScaleMacro(&v_40, &v_40, 0.5f);
            }
        }
    }
    sub_112DA0(&unk_524, 0.0f, &unk_528, flt_429724, flt_429728, flt_42972C, arg_0);
    *v_48 = unk_440;
    for (v_5C = 0; v_5C < v_44; v_5C++)
    {
        v_80 = *v_48;
        RwV3dAddMacro(v_48, &v_40, v_48);
        RwFrameUpdateObjects(v_4);
        v_74 = 0;
        v_88 = 0;
        v_84 = 0;
        v_6C = 0;
        v_68.x = flt_429B1C * unk_4C;
        v_68.y = unk_48 - unk_524;
        v_68.z = v_68.x;
        sub_96EF0(this, v_4, &unk_3C_v, unk_420, &v_74, &v_68, &v_70, &v_88, &v_84, &v_6C, flt_429B10[unk_1A04],
                  flt_429B28[unk_1A04], 0);
        RwFrameUpdateObjects(v_4);
        if (sub_FCAE0(&v_80, v_48, &v_34, 0, 0x10000, 1, 0))
        {
            RwV3dSubMacro(&v_98, &v_80, &v_34);
            v_8C = PVSFindDiagonalSizeOfBBox((RwBBox *)&v_98);
            if (v_8C > 0.01f)
            {
                RwV3dScaleMacro(&v_98, &v_98, v_68.x / v_8C);
                RwV3dAddMacro(v_48, &v_34, &v_98);
                RwFrameUpdateObjects(v_4);
            }
        }
        if (v_6C && unk_520)
        {
            if (vf_17C() > 0.0f)
                dword_44E8B8 = unk_1C0.sub_8A980(&dword_4AF000, this, 0, sub_CD550(), 0, 0);
            vf_178(0);
        }
        if (dword_429B3C && !((unk_28 >> 1) & 1) && unk_19D0 != 0xD)
        {
            if (v_48->y > unk_510)
                unk_510 = v_48->y;
        }
        else
            unk_510 = -1000000.0f;
        if (unk_19D0 == 2 || unk_19D0 == 3 || unk_19D0 == 1 && unk_DC < 0.0f)
        {
            unk_518 += clamp_f(arg_0 * 0.5f, 0.5f, 4.0f);
            if (unk_518 >= flt_429B38)
                vf_178(0);
        }
        else
            unk_518 = 0.0f;
        if ((unk_19D0 == 2 || unk_19D0 == 3 || unk_19D0 == 1 && unk_DC < 0.0f) && v_6C)
        {
            unk_518 = 0.0f;
            unk_28 |= 2;
            sub_1090F0(3);
            v_9C = (type_712B0_10F710 *)unk_344.unk_08;
            if (v_9C && v_9C->vf_008() != 1)
            {
                v_9C = 0;
            }
            if (!v_9C)
                unk_408 = flt_429718;
            else
            {
                v_A4 = (-unk_DC - v_9C->unk_1D8) * 0.03846154f;
                if (v_A4 > 1.0f)
                    v_A4 = 1.0f;
                else if (v_A4 < 0.0f)
                    v_A4 = 0.0f;
                unk_408 = (flt_42971C - flt_429718) * v_A4 + flt_429718;
            }
            v_A0 = unk_510 - v_48->y;
            if (unk_514 && v_A0 > v_9C->unk_23C)
            {
                unk_52C = flt_429B34;
                if (v_A0 > v_9C->unk_240 || unk_520)
                {
                    if (vf_17C() > 0.0f)
                        dword_44E8B8 = unk_1C0.sub_8A980(&dword_4AF000, this, 0, sub_CD550(), 0, 0);
                    vf_178(0);
                    type_3DA434 v_B4;

                    v_B4.sub_1C5A80(100.0f);
                    v_B4.unk_08 = 0;
                    v_B4.unk_04 = 0;
                    sub_1ACBA0(unk_4F7EB8.sub_1AEC70(), &v_B4);
                }
                else
                {
                    v_C0 = (v_A0 - v_9C->unk_23C) / (v_9C->unk_240 - v_9C->unk_23C);
                    v_B8 = (v_BC = vf_17C()) - v_C0;
                    if (v_B8 < 0.0f)
                        v_B8 = 0.0f;
                    vf_23C(v_B8);
                    if (v_B8 > 0.0f)
                        unk_1C0.sub_8A980(&dword_4B1B10, this, 0, sub_CD550(), 0, 0);
                    else
                    {
                        dword_44E8B8 = unk_1C0.sub_8A980(&dword_4AF000, this, 0, sub_CD550(), 0, 0);
                        type_3DA434 v_D0;

                        v_D0.sub_1C5A80(100.0f);
                        v_D0.unk_08 = 0;
                        v_D0.unk_04 = 0;
                        sub_1ACBA0(unk_4F7EB8.sub_1AEC70(), &v_D0);
                    }
                }
            }
            else if (unk_514)
                unk_1C0.sub_8AA70(&dword_4AEFF8, v_8[unk_294].unk_00, this, 0, sub_CD550(), 0, 0);
            unk_514++;
            unk_428 = flt_429740;
            unk_DC = 0.0f;
            unk_420 = v_70;
        }
        else if (((unk_28 >> 1) & 1) && !v_6C && (unk_19D0 == 0 || unk_19D0 == 0xE && !unk_215C))
        {
            unk_28 &= ~2;
            sub_1090F0(2);
        }
        else if (((unk_28 >> 1) & 1) && v_6C)
            unk_420 = v_70;
    }
    RwFrameUpdateObjects(v_4);
    unk_434 = *v_48;
    sub_112DA0(&v_1C.x, unk_434.x, &unk_CC.x, flt_429724, flt_429728, flt_42972C, arg_0);
    sub_112DA0(&v_1C.y, unk_434.y, &unk_CC.y, flt_429724, flt_429728, flt_42972C, arg_0);
    sub_112DA0(&v_1C.z, unk_434.z, &unk_CC.z, flt_429724, flt_429728, flt_42972C, arg_0);
    *v_48 = v_1C;
    RwFrameUpdateObjects(v_4);
    unk_440 = unk_434;
}
