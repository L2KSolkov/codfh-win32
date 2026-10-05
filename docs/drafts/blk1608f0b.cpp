// match: ?vf_014@type_3DC7F8@@UAE_NM@Z @ 0x001608F0
// Its step by arg_0: the line to where it moves against the collision
// worlds, their atomics and the pool-6 projectiles; a hit entity takes the
// shot (vf_064, then its effects, vf_028), a hit pool-6 projectile has its
// time pushed back, a surface its effects (vf_02C); a hit bounces it when
// the cheat flags say so (twice at most). True when it is done.
bool type_3DC7F8::vf_014(RwReal arg_0)
{
    RwV3d var_10;
    type_3D3548 *var_14;
    type_161470 var_78;
    RpIntersection var_94;
    RwInt32 var_98;

    RwV3dScale(&var_10, &unk_10, arg_0);
    RwV3dAdd(&var_10, &unk_04, &var_10);
    var_14 = unk_30.sub_D4910();
    var_78.unk_00 = 1.0e37f;
    var_78.unk_0C = 0;
    var_78.unk_10 = 0;
    var_94.type = rpINTERSECTLINE;
    var_94.t.line.start = unk_04;
    var_94.t.line.end = var_10;
    var_78.sub_161470();
    var_78.unk_14 = unk_24;
    var_78.unk_18 = var_14;
    var_78.unk_1C = unk_34;
    var_78.unk_4C = 0xFFFF;
    var_78.unk_48 = sub_8F940();
    var_78.unk_00 = 1.0e37f;
    if (!(unk_28 & 2))
    {
        for (var_98 = 0; var_98 < 4; var_98++)
        {
            type_4E5D30 *var_9C = &dword_4E5D30[var_98];

            if (var_9C->get_unk_00() && var_9C->get_unk_28())
            {
                RpWorld *var_A8 = var_9C->unk_28;
                type_91F40 var_D4;

                sub_91F40(var_A8, &var_94.t.line, &var_D4, 1, 0x180000, 1); // not an address: line-test flags
                if (var_D4.unk_00 && var_D4.unk_04 < var_78.unk_00)
                {
                    var_78.unk_00 = var_D4.unk_04;
                    var_78.unk_2C = var_D4.unk_14;
                    var_78.unk_20 = var_D4.unk_08;
                    var_78.unk_0C = 0;
                    var_78.unk_38 = var_D4.unk_14;
                    var_78.unk_4C = material_data(((type_96E30 *)var_9C->get_unk_28())
                                                      ->unk_10[(RwUInt16)((RpTriangle *)var_D4.unk_00)->matIndex])->unk_04;
                }
            }
        }
    }
    for (var_98 = 0; var_98 < 4; var_98++)
    {
        type_4E5D30 *var_E4 = &dword_4E5D30[var_98];

        if (var_E4->get_unk_00() && var_E4->get_unk_28())
            RpWorldForAllAtomicIntersections(var_E4->get_unk_28(), &var_94, sub_1660C0, &var_78);
    }
    if (dword_4E5CD8 && get_4E5D00())
        RpWorldForAllAtomicIntersections(get_4E5D00(), &var_94, sub_1660C0, &var_78);
    RwReal var_FC = 2.0f;
    type_3DC7F8 *var_100 = 0;
    type_4E19F8 *var_104 = projectile_pool(6);
    type_3DC7F8 *var_108 = var_104->unk_24;
    while (var_108)
    {
        RwLine var_120;
        RwSphere var_130;
        RwReal var_134;

        var_120.start = unk_04;
        var_120.end = var_10;
        var_130.center = var_108->unk_04;
        var_130.radius = dword_429E70;
        if (RaySphereIntersect(&var_120, &var_130, &var_134) && var_134 < var_FC)
        {
            var_FC = var_134;
            var_100 = var_108;
        }
        var_108 = var_108->unk_40;
    }
    bool var_139 = dword_4B87C8 - unk_1C > unk_20;
    bool var_13A = false;
    if (var_78.unk_00 <= 1.0f || var_139 && vf_03C())
    {
        RwInt32 var_140 = 1;
        RwInt32 var_144 = 0;
        RwMatrix var_1B0;

        if (var_78.unk_0C)
        {
            type_3D3548 *var_148 = sub_FB960(var_78.unk_0C);

            if (var_148)
            {
                var_13A = true;
                RwInt32 var_14C = var_148->vf_1D4();
                if (var_14C != 0x38)
                {
                    type_439A48 *var_150 = unk_3C;
                    RwReal var_154 = var_78.unk_00;
                    RwV3d var_160;

                    RwV3dSub(&var_160, &var_94.t.line.end, &var_94.t.line.start);
                    RwV3dScale(&var_160, &var_160, var_154);
                    RwV3dAdd(&var_78.unk_20, &var_94.t.line.start, &var_160);
                    if (get_4FB9F8() || !((unk_24 & 7) == (var_148->unk_2C & 7)))
                    {
                        type_75600 var_1E0;

                        sub_140F00(&var_1B0, &var_78.unk_20, &var_78.unk_2C);
                        var_144 = 1;
                        var_1E0.unk_00_w = var_150->unk_00;
                        var_1E0.unk_02_w = 0;
                        var_1E0.unk_04 = (RwInt32)this;
                        var_1E0.unk_08 = unk_24;
                        var_1E0.unk_14 = (RwInt32)&var_78.unk_20;
                        var_1E0.unk_18 = (RwInt32)&var_78.unk_2C;
                        var_1E0.unk_20 = &var_78.unk_38;
                        var_1E0.unk_1C = (RwInt32)&var_1B0;
                        var_1E0.unk_0C = var_14;
                        var_1E0.unk_10 = unk_34;
                        var_1E0.unk_28 = var_150->unk_04;
                        var_1E0.unk_2C = var_150->unk_04;
                        var_1E0.unk_24 = var_78.unk_44;
                        var_148->vf_064(&var_1E0);
                    }
                }
                else
                {
                    var_140 = 0;
                }
                if (var_148->unk_2C_7 | var_148->unk_2C_24 | var_148->unk_2C_18 | var_148->unk_2C_25)
                {
                    sub_140F00(&var_1B0, &var_78.unk_20, &var_78.unk_2C);
                    var_144 = 1;
                }
            }
            if (var_144)
                vf_028(var_148, &var_1B0, var_14);
        }
        else if (var_100)
        {
            var_100->advance_time();
        }
        else if (!var_13A)
        {
            RwV3d var_1F0;
            RwMatrix var_230;

            if (var_139 && vf_03C())
            {
                RwV3dNormalize(&var_1F0, &unk_10);
                sub_140F00(&var_1B0, &var_10, &var_1F0);
            }
            else
            {
                sub_140F00(&var_230, &var_78.unk_20, &var_78.unk_2C);
            }
            switch (var_78.unk_4C & 0xFFFF)
            {
            default:
                vf_02C(var_78.unk_4C & 0xFFFF, &var_230, var_14, 1);
                break;
            case 0x38:
                var_140 = 0;
                break;
            }
        }
        if (var_140)
        {
            if ((var_14 && var_14->vf_00C() && ((type_4B8888 *)dword_4B8888)->unk_00_1)
                || ((type_4B8888 *)dword_4B8888)->unk_00_3)
            {
                RwV3d var_240;
                RwV3d var_24C;
                RwV3d var_258;
                RwReal var_25C;
                RwV3d var_268;
                RwV3d var_274;
                RwV3d var_280;
                RwReal var_284;

                unk_2C++;
                if (unk_2C > 2)
                    return true;
                var_240 = var_78.unk_38;
                var_24C = unk_10;
                RwV3dNormalize(&var_24C, &var_24C);
                var_258 = var_24C;
                var_25C = RwV3dDotProduct(&var_258, &var_240) * 2;
                RwV3dScale(&var_268, &var_240, var_25C);
                RwV3dSub(&var_274, &var_258, &var_268);
                RwV3dScale(&var_280, &var_24C, -2.0f);
                var_284 = PVSFindDiagonalSizeOfBBox((RwBBox *)&unk_10);
                unk_10 = var_274;
                RwV3dScale(&unk_10, &unk_10, var_284);
                var_10 = var_78.unk_20;
                RwV3dAdd(&var_10, &var_10, &var_280);
                unk_04 = var_10;
            }
            else
            {
                return true;
            }
        }
    }
    if (var_139)
        return true;
    if (dword_4B87C8 != unk_1C)
        unk_04 = var_10;
    vf_01C(arg_0);
    return false;
}

