// Updates the mesh particle system arg_0 by arg_4 frames; 0 once its
// duration and its particles' life have run out. While it emits (flag 1)
// its rate (unk_18, a second) gives the new particles due. Each new one
// starts at the system's matrix scaled by unk_CC and offset by up to half of
// unk_0C..unk_14 (turned with it), with a velocity of unk_40..unk_48 give or
// take half of unk_4C..unk_54 (times unk_2C x 10) and, with unk_A4, a random
// spin axis and rate. The live ones age, fall by unk_34..unk_3C and move and
// spin, and die at the age unk_24; with unk_F0 they start the system unk_D0
// at their places (one a particle, following it, when the trails' rate unk_F4
// is 0).
// match: ?sub_EF040@@YAHPAUtype_F2FF0@@M@Z @ 0x000EF040
RwInt32 sub_EF040(type_F2FF0 *arg_0, RwReal arg_4)
{
    RwInt32 v_4;
    RwInt32 v_8;
    RwInt32 v_C;
    RwReal v_10;
    RwReal v_14;
    RwInt32 v_18;
    type_F2FF0_60_04 *v_1C;
    RwMatrix *v_20;

    v_4 = 1;
    arg_0->unk_60.unk_08 += arg_4;
    v_8 = 0;
    v_C = 0;
    if (arg_0->unk_60.unk_14 & 1)
    {
        v_8 = (RwInt32)(v_10 = arg_0->unk_44->unk_18 * (arg_0->unk_60.unk_08 - arg_0->unk_60.unk_0C) * 66.666664f);
        if (v_8 > 0)
        {
            arg_0->unk_60.unk_0C = arg_0->unk_60.unk_08;
        }
    }
    v_C = (RwInt32)(v_14 = arg_0->unk_44->unk_F4_f * (arg_0->unk_60.unk_08 - arg_0->unk_60.unk_10) * 66.666664f);
    if (v_C > 0)
    {
        arg_0->unk_60.unk_10 = arg_0->unk_60.unk_08;
    }
    for (v_18 = 0; v_18 < arg_0->unk_60.unk_1C; v_18++)
    {
        v_1C = &arg_0->unk_60.unk_04[v_18];
        v_20 = &arg_0->unk_00;
        if (v_1C->unk_00 < 0.0f && v_8 > 0)
        {
            v_1C->unk_10.z = 0;
            v_1C->unk_10.y = 0;
            v_1C->unk_10.x = 0;
            v_1C->unk_00 = 0;
            v_1C->unk_20 = 0;
            arg_0->unk_60.unk_00[v_18] = *v_20;
            v_1C->unk_04.x = arg_0->unk_44->unk_40 + frand_range(-0.5f, 0.5f) * arg_0->unk_44->unk_4C;
            v_1C->unk_04.y = arg_0->unk_44->unk_44 + frand_range(-0.5f, 0.5f) * arg_0->unk_44->unk_50;
            v_1C->unk_04.z = arg_0->unk_44->unk_48 + frand_range(-0.5f, 0.5f) * arg_0->unk_44->unk_54;
            RwV3dScale(&v_1C->unk_04, &v_1C->unk_04, arg_0->unk_44->unk_2C * 10.0f);
            sub_141320(&v_1C->unk_04, &v_1C->unk_04, &arg_0->unk_60.unk_00[v_18]);
            if (arg_0->unk_44->unk_A4)
            {
                v_1C->unk_10.x = frand_range(-1.0f, 1.0f);
                v_1C->unk_10.y = frand_range(-1.0f, 1.0f);
                v_1C->unk_10.z = frand_range(-1.0f, 1.0f);
                RwV3dNormalize(&v_1C->unk_10, &v_1C->unk_10);
                v_1C->unk_1C = frand_range(0.0f, arg_0->unk_44->unk_A4 * 3.14159f);
            }
            RwV3d v_A8;

            v_A8.x = frand_range(-0.5f, 0.5f) * arg_0->unk_44->unk_0C;
            v_A8.y = frand_range(-0.5f, 0.5f) * arg_0->unk_44->unk_10;
            v_A8.z = frand_range(-0.5f, 0.5f) * arg_0->unk_44->unk_14;
            sub_141320(&v_A8, &v_A8, &arg_0->unk_60.unk_00[v_18]);
            RwV3dAdd(&arg_0->unk_60.unk_00[v_18].pos, &arg_0->unk_60.unk_00[v_18].pos, &v_A8);
            RwV3dScale(&arg_0->unk_60.unk_00[v_18].right, &arg_0->unk_60.unk_00[v_18].right, arg_0->unk_44->unk_CC);
            RwV3dScale(&arg_0->unk_60.unk_00[v_18].up, &arg_0->unk_60.unk_00[v_18].up, arg_0->unk_44->unk_CC);
            RwV3dScale(&arg_0->unk_60.unk_00[v_18].at, &arg_0->unk_60.unk_00[v_18].at, arg_0->unk_44->unk_CC);
            arg_0->unk_60.unk_18++;
            v_8--;
        }
        else if (v_1C->unk_00 >= 0.0f)
        {
            RwV3d *v_C8;

            v_1C->unk_00 += arg_4;
            v_1C->unk_04.x += arg_4 * arg_0->unk_44->unk_34 * 20.0f;
            v_1C->unk_04.y += arg_4 * arg_0->unk_44->unk_38 * 20.0f;
            v_1C->unk_04.z += arg_4 * arg_0->unk_44->unk_3C * 20.0f;
            v_C8 = &arg_0->unk_60.unk_00[v_18].pos;
            v_C8->x += arg_4 * v_1C->unk_04.x;
            v_C8->y += arg_4 * v_1C->unk_04.y;
            v_C8->z += arg_4 * v_1C->unk_04.z;
            if (arg_0->unk_44->unk_A4)
            {
                sub_140440(&arg_0->unk_60.unk_00[v_18], &v_1C->unk_10, arg_4 * v_1C->unk_1C);
            }
            if (v_1C->unk_00 >= arg_0->unk_44->unk_24)
            {
                v_1C->unk_00 = -1.0f;
                arg_0->unk_60.unk_18--;
                arg_0->unk_60.unk_00[v_18].pos.z = 10000000.0f;
            }
            if (arg_0->unk_44->unk_F0)
            {
                if (v_C || arg_0->unk_44->unk_F4_f == 0.0f)
                {
                    if (v_1C->unk_00 >= 0.0f)
                    {
                        RwMatrix v_110;

                        arg_0->unk_60.unk_14 |= 4;
                        RwMatrixSetIdentity(&v_110);
                        v_110.pos = arg_0->unk_60.unk_00[v_18].pos;
                        if (arg_0->unk_44->unk_F4_f != 0.0f)
                        {
                            sub_F3070(arg_0->unk_44->unk_D0, &v_110, 0, 1, false, false);
                        }
                        else if (!v_1C->unk_20)
                        {
                            type_F2FF0 *v_114;

                            v_114 = sub_F3070(arg_0->unk_44->unk_D0, &v_110, 0, 1, false, false);
                            if (v_114)
                            {
                                RwV3d v_120;

                                sub_19E9B0((type_19E9B0 *)&v_114->unk_60, &v_1C->unk_04);
                                v_120.x = flt_4296B4 * arg_0->unk_44->unk_34;
                                v_120.y = flt_4296B4 * arg_0->unk_44->unk_38;
                                v_120.z = flt_4296B4 * arg_0->unk_44->unk_3C;
                                sub_19E9E0((type_19E9B0 *)&v_114->unk_60, &v_120);
                                v_1C->unk_20 = 1;
                            }
                        }
                    }
                }
            }
        }
    }
    if (arg_0->unk_44->unk_20 > 0.0f)
    {
        RwReal v_124;
        RwReal v_128;

        v_124 = arg_0->unk_44->unk_20;
        v_128 = arg_0->unk_44->unk_24;
        if (arg_0->unk_60.unk_08 > v_124)
        {
            arg_0->unk_60.unk_14 &= ~1;
        }
        if (v_124 + v_128 < arg_0->unk_60.unk_08)
        {
            v_4 = 0;
        }
    }
    return v_4;
}

