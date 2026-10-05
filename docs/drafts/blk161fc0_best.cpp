// match: ?vf_014@type_3DC8B8@@UAE_NM@Z @ 0x00161FC0
// Its step by arg_0. Unless it sticks to something (unk_12C), its model moves
// by its velocity and gravity; the line (or, for a table-6 grenade at rest, a
// sphere) there is tested against the worlds and their atomics. A hit sticks
// a table-5 grenade (to the entity's nearest bone or frame), bounces the
// others off the surface (with its sound), alerts the entities near where it
// will land and spins it. Stuck, it follows what it sticks to. When its fuse
// is over it tells the entities it alerted, blows up (vf_024's sound, its
// effects, a shake, sub_1614E0) and is done (true).
bool type_3DC8B8::vf_014(RwReal arg_0)
{
    type_439A48 *var_8 = unk_3C;
    RwReal var_C = arg_0;
    RwInt32 var_10 = 0;
    RwInt32 var_24 = ABS_(unk_10.x) < 1.0e-5f && ABS_(unk_10.y) < 1.0e-5f && ABS_(unk_10.z) < 1.0e-5f;
    type_3D3548 *var_28 = unk_30.sub_D4910();
    RpClump *var_2C = unk_94.unk_08;
    RwFrame *var_30 = RpClumpGetFrame(var_2C);
    RwFrame *var_34 = RwFrameGetParent(var_30);
    RwMatrix var_80 = *RwFrameGetMatrix(var_30);
    RwV3d var_8C;

    if (unk_15C)
    {
        if (var_34)
            vf_04C();
        return true;
    }
    if (!unk_12C)
    {
        RwV3dScale(&var_8C, &unk_10, arg_0);
        if (unk_8C)
        {
            unk_8C = 0;
        }
        else
        {
            RwReal var_90 = 0.5f * arg_0 * arg_0;
            RwReal var_94 = vf_020() * var_90;

            var_8C.y = var_8C.y + var_94;
        }
        RwV3dAdd(&var_8C, &var_80.pos, &var_8C);
        if (!unk_78)
        {
            unk_8C = 1;
            unk_10.x = unk_10.y = unk_10.z = 0.0f;
        }
        RwV3d var_A0;

        RwV3dSub(&var_A0, &var_80.pos, &var_8C);
        if (var_A0.x != 0.0f || var_A0.y != 0.0f || var_A0.z != 0.0f || unk_70 == 6)
        {
            type_161470 var_100;

            var_100.unk_00 = 1.0e37f;
            var_100.unk_0C = 0;
            var_100.unk_10 = 0;
            RwInt32 var_104 = 6;
            RwInt32 var_10C = unk_70 == var_104 && !unk_78;
            RpIntersection var_128;
            RwInt32 var_12C;

            if (!var_10C)
            {
                var_128.type = rpINTERSECTLINE;
                var_128.t.line.start = var_80.pos;
                var_128.t.line.end = var_8C;
                var_100.sub_161470();
                var_100.unk_14 = unk_24;
                var_100.unk_18 = var_28;
                var_100.unk_1C = unk_34;
                for (var_12C = 0; var_12C < 4; var_12C++)
                {
                    type_4E5D30 *var_130 = &dword_4E5D30[var_12C];

                    if (var_130->get_unk_00() && var_130->get_unk_28())
                    {
                        RpWorld *var_13C = var_130->unk_28;
                        type_91F40 var_168;

                        sub_91F40(var_13C, &var_128.t.line, &var_168, 1, 0x180000, 1); // not an address: line-test flags
                        if (var_168.unk_00 && var_168.unk_04 < var_100.unk_00)
                        {
                            var_100.unk_00 = var_168.unk_04;
                            var_100.unk_2C = var_168.unk_14;
                            var_100.unk_20 = var_168.unk_08;
                            var_100.unk_0C = 0;
                            var_100.unk_4C = material_data(((type_96E30 *)var_130->get_unk_28())
                                                               ->unk_10[(RwUInt16)((RpTriangle *)var_168.unk_00)->matIndex])->unk_04;
                        }
                    }
                }
            }
            else
            {
                var_128.type = rpINTERSECTSPHERE;
                var_128.t.sphere.center = var_80.pos;
                var_128.t.sphere.radius = dword_429E8C > dword_429E88 ? dword_429E8C : dword_429E88;
                var_100.sub_161470();
                var_100.unk_14 = unk_24;
                var_100.unk_18 = var_28;
                var_100.unk_1C = unk_34;
                var_100.unk_08 = (RwInt32)var_30;
                var_100.unk_50 = dword_429E88;
                var_100.unk_54 = dword_429E8C;
                var_100.unk_58 = 1;
            }
            for (var_12C = 0; var_12C < 4; var_12C++)
            {
                type_4E5D30 *var_17C = &dword_4E5D30[var_12C];

                if (var_17C->get_unk_00() && var_17C->get_unk_28())
                    RpWorldForAllAtomicIntersections(var_17C->get_unk_28(), &var_128, sub_1660C0, &var_100);
            }
            if (dword_4E5CD8 && get_4E5D00())
                RpWorldForAllAtomicIntersections(get_4E5D00(), &var_128, sub_1660C0, &var_100);
            if (var_100.unk_00 <= 1.0f)
            {
                if (unk_3C->unk_00 == 5)
                {
                    unk_10.x = unk_10.y = unk_10.z = 0.0f;
                    unk_12C = 1;
                    sub_140CE0(&var_80, &var_100.unk_20, &var_100.unk_2C);
                    unk_04 = var_80.pos;
                    RwFrameTransform(var_30, &var_80, rwCOMBINEREPLACE);
                    dword_4B1E98.sub_8A980(&dword_4B1B58, 0, 0, &unk_04, 1, 0);
                }
                unk_A0++;
                var_C = var_100.unk_00 * arg_0;
                if (var_100.unk_0C)
                {
                    type_3D3548 *var_194 = sub_FB960(var_100.unk_0C);

                    if (var_194)
                    {
                        if (var_194->vf_00C() || var_194->vf_008())
                            var_10 = 1;
                        if (unk_12C)
                        {
                            RwInt32 var_198 = var_194->vf_174();

                            if (var_194->unk_28_0 || var_194->unk_28_9 || var_198 < 1)
                            {
                                unk_1C = 0;
                            }
                            else
                            {
                                unk_1A0.sub_D48D0(var_194);
                                switch (var_194->unk_2C & 0x3FFFFF0)
                                {
                                case 0x200000:
                                case 0x20:
                                    {
                                        unk_13C = 2;
                                        RpHAnimHierarchy *var_1A0 = var_194->unk_284->unk_18;
                                        RwMatrix *var_1A4 = RpHAnimHierarchyGetMatrixArray(var_1A0);
                                        RwInt32 var_1A8 = var_1A0->numNodes;
                                        RwReal var_1AC = 1.0e7f;
                                        RwMatrix *var_1B0 = RwFrameGetMatrix(var_30);
                                        RwV3d var_1BC = var_1B0->pos;
                                        RwInt32 var_1C0;

                                        unk_140 = -1;
                                        for (var_1C0 = 0; var_1C0 < var_1A8; var_1C0++)
                                        {
                                            RwReal var_1C4 = (var_1BC.x - var_1A4[var_1C0].pos.x) * (var_1BC.x - var_1A4[var_1C0].pos.x)
                                                + (var_1BC.y - var_1A4[var_1C0].pos.y) * (var_1BC.y - var_1A4[var_1C0].pos.y)
                                                + (var_1BC.z - var_1A4[var_1C0].pos.z) * (var_1BC.z - var_1A4[var_1C0].pos.z);

                                            if (var_1C4 < var_1AC)
                                            {
                                                var_1AC = var_1C4;
                                                unk_140 = var_1C0;
                                            }
                                        }
                                        if (unk_140 != -1)
                                        {
                                            RwMatrix var_210 = var_1A4[unk_140];
                                            RwMatrix var_250;
                                            RwV3d var_25C;

                                            RwMatrixInvert(&var_250, &var_210);
                                            RwMatrixTransform(var_1B0, &var_250, rwCOMBINEPOSTCONCAT);
                                            unk_144 = var_1B0->pos;
                                            RwV3dScale(&var_25C, &var_1A4[unk_140].right, 5.0f);
                                            RwV3dAdd(&unk_144, &unk_144, &var_25C);
                                        }
                                        else
                                        {
                                            unk_13C = 1;
                                        }
                                    }
                                    break;
                                case 0x40000:
                                case 0x2000000:
                                    {
                                        unk_13C = 3;
                                        RpHAnimHierarchy *var_260 = var_194->unk_284->unk_18;
                                        RwMatrix *var_264 = RpHAnimHierarchyGetMatrixArray(var_260);
                                        RwInt32 var_268 = var_260->numNodes;
                                        RwReal var_26C = 1.0e7f;
                                        RwMatrix var_2B0 = *RwFrameGetMatrix(var_30);
                                        RwV3d var_2BC = var_2B0.pos;
                                        RwInt32 var_2C0;

                                        unk_140 = -1;
                                        for (var_2C0 = 0; var_2C0 < var_268; var_2C0++)
                                        {
                                            RwReal var_2C4 = (var_2BC.x - var_264[var_2C0].pos.x) * (var_2BC.x - var_264[var_2C0].pos.x)
                                                + (var_2BC.y - var_264[var_2C0].pos.y) * (var_2BC.y - var_264[var_2C0].pos.y)
                                                + (var_2BC.z - var_264[var_2C0].pos.z) * (var_2BC.z - var_264[var_2C0].pos.z);

                                            if (var_2C4 < var_26C)
                                            {
                                                var_26C = var_2C4;
                                                unk_140 = var_2C0;
                                            }
                                        }
                                        if (unk_140 != -1)
                                        {
                                            RwMatrix var_310 = var_264[unk_140];
                                            RwMatrix var_350;

                                            RwMatrixInvert(&var_350, &var_310);
                                            RwMatrixTransform(&var_2B0, &var_350, rwCOMBINEPOSTCONCAT);
                                            unk_144 = var_2B0.pos;
                                        }
                                        else
                                        {
                                            unk_13C = 1;
                                        }
                                    }
                                    break;
                                default:
                                    {
                                        unk_13C = 1;
                                        RwFrame *var_358 = var_194->get_unk_340();
                                        RwMatrix *var_35C = RwFrameGetMatrix(var_358);
                                        RwMatrix var_3A0;

                                        unk_160 = *var_35C;
                                        RwMatrixInvert(&var_3A0, var_35C);
                                        RwMatrixTransform(&var_80, &var_3A0, rwCOMBINEPOSTCONCAT);
                                        RwFrameTransform(var_30, &var_80, rwCOMBINEREPLACE);
                                        RwFrameAddChild(var_358, var_30);
                                        unk_1A0.sub_D48D0(var_194);
                                    }
                                }
                                dword_4B1E98.sub_8A980(&dword_4B1B58, 0, 0, (RwV3d *)var_194->vf_0C4(), 1, 0);
                                RwReal var_3A4 = var_8->unk_50;

                                if (var_194->vf_098())
                                    sub_6B5F0("GrenadeIsFreakingOnMe", var_194->vf_098(), 0, 0, &var_3A4, 1, 1, 0);
                            }
                        }
                        if (unk_70 == 6 && var_24 && var_10C && unk_A0 > 8)
                        {
                            RwInt32 var_3A8 = 0;

                            switch (var_194->unk_2C & 0x3FFFFF0)
                            {
                            case 0x1000000:
                            case 0x80:
                            case 0x40000:
                            case 0x2000000:
                                var_3A8 = 1;
                                break;
                            default:
                                var_3A8 = 0;
                            }
                            if (var_3A8)
                                unk_1C -= var_8->unk_50;
                        }
                        type_439A48 *var_3B0 = unk_3C;
                        type_75600 var_3E0;
                        RwMatrix var_420;

                        var_3E0.unk_00_w = var_3B0->unk_00;
                        var_3E0.unk_02_w = 0;
                        var_3E0.unk_04 = (RwInt32)this;
                        var_3E0.unk_14 = (RwInt32)&var_100.unk_20;
                        var_3E0.unk_18 = (RwInt32)&var_100.unk_2C;
                        var_3E0.unk_20 = &var_100.unk_38;
                        var_3E0.unk_1C = (RwInt32)&var_420;
                        var_3E0.unk_08 = unk_24;
                        var_3E0.unk_0C = var_28;
                        var_3E0.unk_10 = unk_34;
                        var_3E0.unk_28 = 0;
                        var_3E0.unk_2C = 0;
                        var_3E0.unk_24 = var_100.unk_44;
                        var_194->vf_064(&var_3E0);
                    }
                }
                if (!unk_12C)
                {
                    RwReal var_424 = PVSFindDiagonalSizeOfBBox((RwBBox *)&var_A0);
                    RwReal var_428 = var_100.unk_00 * var_424;

                    if (dword_429E80 > var_428)
                    {
                        if (var_428 < 0.0f)
                            var_8C = var_100.unk_20;
                        else
                            var_8C = var_128.t.line.start;
                    }
                    else
                    {
                        RwV3d var_434;

                        var_8C = var_100.unk_20;
                        RwV3dNormalize(&var_434, &var_A0);
                        RwV3dIncrementScaledMacro(&var_8C, &var_434, dword_429E80);
                    }
                    RwReal var_438 = RwV3dDotProduct(&unk_10, &var_100.unk_2C);

                    RwV3dIncrementScaledMacro(&unk_10, &var_100.unk_2C, -2.0f * var_438);
                    RwV3d var_444;

                    if (var_100.unk_2C.x == 0.0f && var_100.unk_2C.y == 0.0f && var_100.unk_2C.z == 0.0f)
                    {
                        var_444 = unk_10;
                        RwV3dNormalize(&var_444, &var_444);
                    }
                    else
                    {
                        var_444 = var_100.unk_2C;
                    }
                    RwReal var_448 = RwV3dDotProduct(&unk_10, &var_444);
                    RwV3d var_454;
                    RwV3d var_460;

                    RwV3dScale(&var_454, &var_444, var_448);
                    RwV3dSub(&var_460, &unk_10, &var_454);
                    RwV3dScale(&var_460, &var_460, var_8->unk_48);
                    RwInt32 var_468 = RwV3dDotProduct(&var_454, &var_454) < dword_429E84;

                    if (var_10)
                    {
                        RwV3dScale(&var_454, &var_454, var_8->unk_44 * var_8->unk_44);
                        if (!var_468)
                        {
                            vf_024(&var_100.unk_20, &dword_4B1B50, -2, var_28, 0);
                        }
                        else if (!unk_A4)
                        {
                            vf_024(&var_100.unk_20, &dword_4B1B50, -2, var_28, 0);
                            unk_A4 = 1;
                        }
                    }
                    else
                    {
                        RwV3dScale(&var_454, &var_454, var_8->unk_44);
                        if (!var_468)
                        {
                            vf_024(&var_100.unk_20, &dword_4B1C38, -2, var_28, 0);
                        }
                        else if (!unk_A4)
                        {
                            vf_024(&var_100.unk_20, &dword_4B1C38, -2, var_28, 0);
                            unk_A4 = 1;
                        }
                    }
                    if (var_468)
                        var_454.x = var_454.y = var_454.z = 0.0f;
                    RwV3dAdd(&unk_10, &var_454, &var_460);
                    if (unk_70 == 6 && ABS_(unk_10.x) < 0.1f && ABS_(unk_10.y) < 0.1f && ABS_(unk_10.z) < 0.1f)
                    {
                        unk_78 = 0;
                        unk_8C = 1;
                    }
                    if (!var_10)
                    {
                        unk_158++;
                        if (unk_158 >= 4 && PVSFindDiagonalSizeOfBBox((RwBBox *)&unk_10) < 50.0f)
                        {
                            sub_164210(&unk_04, &unk_10, &unk_130);
                            type_161FC0_alert var_480;

                            var_480.unk_00 = 0;
                            var_480.unk_04 = var_8->unk_50;
                            var_480.unk_08 = unk_154;
                            RwReal var_484 = (unk_3C->unk_4C + 300.0f) * (unk_3C->unk_4C + 300.0f);

                            if (dword_4B87C8 - unk_1C + 3.0f < var_8->unk_50)
                            {
                                RwInt32 var_488;

                                for (var_488 = 0; var_488 < 32; var_488++)
                                {
                                    type_3D3548 *var_48C = unk_438CA8[var_488].sub_D4910();

                                    if (var_48C && !unk_A8[var_488].sub_D4910())
                                    {
                                        RwReal var_490 = sub_140C90(var_48C->sub_CD550(), &unk_130);

                                        if (var_490 < var_484)
                                        {
                                            RwV3d var_49C;

                                            RwV3dSub(&var_49C, var_48C->sub_CD550(), &unk_130);
                                            var_480.unk_00 = PVSFindDiagonalSizeOfBBox((RwBBox *)&var_49C);
                                            sub_6B5F0("GrenadeAlert", var_48C->vf_098(), 0, 0, &var_480, 3, 1, 0);
                                            if (var_48C->vf_008())
                                                var_48C->vf_008()->unk_610 = (type_3DAFC8_610 *)this;
                                            unk_A8[var_488] = unk_438CA8[var_488];
                                            if (!var_48C->vf_00C())
                                            {
                                                if (unk_154 <= 0)
                                                    var_48C->unk_1C0.sub_8A980(&dword_4B1C38, var_48C, 2, var_48C->sub_CD550(), 0, 0);
                                                unk_154++;
                                                var_480.unk_08 = unk_154;
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                    RwV3dCrossProduct(&unk_7C, &var_80.at, &var_444);
                    RwReal var_4A0 = 0;

                    if (RwV3dDotProduct(&unk_7C, &unk_7C) > 1.0e-4f)
                    {
                        RwV3dNormalize(&unk_7C, &unk_7C);
                        var_4A0 = acos(0.99999f > ((var_4A0 = RwV3dDotProduct(&var_444, &var_80.at)) > -0.99999f
                                                       ? var_4A0 : -0.99999f)
                                           ? (var_4A0 > -0.99999f ? var_4A0 : -0.99999f) : 0.99999f) * 57.295776f;
                        if (dword_429E78 * arg_0 >= var_4A0)
                            var_4A0 = var_4A0 / arg_0;
                        else
                            var_4A0 = dword_429E78;
                        unk_7C.x = RwV3dDotProduct(&unk_7C, &var_80.right);
                        unk_7C.y = RwV3dDotProduct(&unk_7C, &var_80.up);
                        unk_7C.z = RwV3dDotProduct(&unk_7C, &var_80.at);
                    }
                    unk_88 = var_4A0;
                }
            }
        }
    }
    else
    {
        type_3D3548 *var_4B4 = unk_1A0.sub_D4910();

        if (var_4B4)
        {
            var_34 = RwFrameGetParent(var_30);
            if (!var_4B4)
                return false;
            RwInt32 var_4B8 = var_4B4->vf_174();
            RwMatrix *var_4BC;

            if (var_4B4->unk_28_0 || var_4B4->unk_28_9 || var_4B8 < 1 || unk_13C == 1 && !var_34)
            {
                if (unk_13C == 1 && var_34)
                {
                    RwFrameRemoveChild(var_30);
                    var_4BC = &unk_160;
                }
                unk_1C = 0;
            }
            switch (unk_13C)
            {
            case 1:
                if (var_34)
                {
                    var_4BC = RwFrameGetMatrix(var_34);
                    unk_160 = *var_4BC;
                    var_80 = *RwFrameGetMatrix(var_30);
                    RwMatrixTransform(&var_80, var_4BC, rwCOMBINEPOSTCONCAT);
                    unk_04 = var_80.pos;
                }
                break;
            case 2:
            case 3:
                {
                    type_3D3548 *var_4C4 = unk_1A0.sub_D4910();

                    if (var_4C4)
                    {
                        RpHAnimHierarchy *var_4C8 = var_4C4->unk_284->unk_18;
                        RwMatrix *var_4CC = RpHAnimHierarchyGetMatrixArray(var_4C8);
                        RwMatrix var_510;

                        RwMatrixSetIdentity(&var_510);
                        var_510.pos = unk_144;
                        RwMatrixTransform(&var_510, &var_4CC[unk_140], rwCOMBINEPOSTCONCAT);
                        RwMatrix *var_514 = RwFrameGetMatrix(var_30);

                        *var_514 = var_510;
                        RwFrameUpdateObjects(var_30);
                    }
                }
                break;
            }
        }
    }
    if (dword_4B87C8 - unk_1C > var_8->unk_50)
    {
        RwFrame *var_518 = RwFrameGetParent(var_30);

        if (var_518)
        {
            vf_04C();
            var_80 = *RwFrameGetMatrix(var_30);
        }
        type_161FC0_explode var_528;
        RwInt32 var_52C;

        var_528.unk_00.x = unk_04.x;
        var_528.unk_00.y = unk_04.y;
        var_528.unk_00.z = unk_04.z;
        var_528.unk_0C = 0;
        for (var_52C = 0; var_52C < 32; var_52C++)
        {
            if (unk_A8[var_52C].sub_D4910())
            {
                RwV3d var_538;

                RwV3dSub(&var_538, unk_A8[var_52C].sub_D4910()->sub_CD550(), &unk_04);
                var_528.unk_0C = PVSFindDiagonalSizeOfBBox((RwBBox *)&var_538);
                type_3D3548 *var_53C = unk_A8[var_52C].sub_D4910();

                sub_6B5F0("GrenadeExplode", var_53C->vf_098(), 0, 0, &var_528, 4, 1, 0);
            }
        }
        unk_128 = 1;
        type_439A48 *var_540 = unk_3C;

        vf_024(&var_80.pos, &dword_4B1B20, -2, var_28, 0);
        vf_038(&var_80);
        unk_4E5E50.sub_176180(8, &var_80.pos, 1.0f, 0);
        sub_1614E0(&var_80, var_28, var_540);
        if (!var_518)
            unk_04 = var_8C;
        return true;
    }
    if (!unk_12C)
    {
        unk_04 = var_8C;
        var_80.pos = var_8C;
        RwReal var_544 = arg_0 * unk_88;

        if (!unk_8C && var_544 != 0.0f && unk_70 != 6)
            RwMatrixRotate(&var_80, &unk_7C, var_544, rwCOMBINEPRECONCAT);
        RwFrameTransform(var_30, &var_80, rwCOMBINEREPLACE);
        if (var_C != arg_0 && dword_429E7C > dword_4E1B60)
        {
            // A check compiled out of this build (it moves the registers one step).
            if (unk_78)
            {
            }
            dword_4E1B60++;
            vf_014(arg_0 - var_C);
            dword_4E1B60 = 0;
        }
        else if (!unk_8C)
        {
            vf_01C(var_C);
        }
    }
    return false;
}
