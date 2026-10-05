// Fires once its recoil time (unk_220) reaches the settings' rate (unk_BC);
// false before. Whether its particles follow it (unk_465): always within 5
// of the rate unless the settings say so (unk_28C), else by chance as
// shots run together. With nothing loaded when rounds count it only plays
// the empty sound. Otherwise: the rumble (sub_119050); weapons 30 and 36
// fire the vehicle's gun from a vehicle's seat 2, and aim from the hand's
// weapon; its sound starts; past the first shots (unk_2A8 by stance) the
// recoil line (unk_24) is kicked by a random spread (the aimed settings
// when the player is aiming, unk_1B04), swung back when it runs past its
// bound, and the kick stored into the stance's sway (unk_238 or unk_25C)
// with the recoil's size (unk_18) growing; the aim is the camera's matrix
// blended towards the muzzle by the distance to the nearest world hit,
// turned by the recoil and a random spread; the bullet flies along it
// (0x202 for a player of kind 2, else 0x201; from the vehicle while its
// pair's second, with its gun's settings from seat 2), with its fire
// animation, its spread (unk_450, unk_454), the pair's muzzle particles, the
// weapon 4 twist, and the rounds display.
// match: ?vf_018@type_10F710_1A48@@UAE_NXZ @ 0x001176F0
bool type_10F710_1A48::vf_018()
{
    RpHAnimHierarchy *v_8;
    type_3DBC78 *v_C;
    RwInt32 v_10;
    RwMatrix v_60;
    RwLine v_7C;
    RwReal v_98;
    RwReal v_B0;
    RwReal v_110;
    RwReal v_114;
    RwMatrix *v_118;
    RwReal v_11C;
    RwLine v_134;
    RwInt32 v_138;
    type_4E5D30 *v_13C;
    type_91F40 v_174;
    RwV3d v_180;
    RwReal v_184;
    RwMatrix v_1D0;
    RwMatrix v_210;
    RtSlerp *v_214;
    RwMatrix v_260;
    RwReal v_278;
    RwReal v_290;
    RwV3d v_2C8;
    RwV3d v_2D4;
    RwInt32 v_2D8;
    RwInt32 v_2F4;
    RwInt32 v_2F8;
    RwInt32 v_2FC;
    RwInt32 v_300;
    RwMatrix v_360;
    type_F2FF0 *v_364;
    type_F2FF0 *v_368;

    if (unk_220 < unk_448->unk_BC)
        return false;
    if (unk_448->unk_BC + 5.0f >= unk_220)
    {
        if (unk_448->unk_28C)
            unk_465 = 1;
        else
        {
            unk_468++;
            unk_465 = (rand() & unk_468) != 0;
        }
    }
    else
    {
        unk_465 = 1;
        unk_468 = 0;
    }
    memset(&unk_29C, 0, sizeof(type_10F710_1A48_29C));
    unk_44 = 1;
    unk_220 = 0.0f;
    if (unk_414 || !unk_448->unk_CC || dword_4C19AC)
    {
        sub_119050();
        unk_48 = unk_448->unk_D4;
        v_8 = unk_42C->unk_284->unk_18;
        if (unk_458 == 30 || unk_458 == 36)
        {
            if (unk_42C->unk_4D0 == 2)
            {
                v_C = (type_3DBC78 *)unk_42C->vf_200();
                dword_4C19A8 = 1;
                v_10 = v_C->vf_2A8(1, 0, 1);
                dword_4C19A8 = 0;
                return v_10;
            }
            sub_EC310(unk_42C->unk_1A48[unk_42C->unk_1AE4]->unk_420.get_unk_08(), v_8, &v_60, 0x46495245, 0,
                      1); // not an address: 'FIRE'
        }
        else
        {
            sub_EC310(unk_420.get_unk_08(), v_8, &v_60, 0x46495245, 0, 1); // not an address: 'FIRE'
        }
        if (!unk_46 && unk_448->unk_1C && !unk_464)
        {
            unk_21C = unk_42C->unk_1C0.sub_8A980(&unk_448->unk_0C, unk_42C, 1, unk_42C->sub_CD550(), 0, 0);
            unk_46 = 1;
        }
        if ((RwUInt32)unk_40 >= unk_448->unk_2A8_u[unk_42C->unk_1A04])
        {
            v_7C.start.z = 0.0f;
            v_7C.end.z = 0.0f;
            if (unk_3C)
            {
                unk_24_l.end.x = unk_1C;
                unk_24_l.end.y = unk_20;
                v_7C.start.x = unk_24_l.end.x;
                v_7C.start.y = unk_24_l.end.y;
                RwV3dSubMacro(&v_7C.end, &unk_24_l.end, &unk_24_l.start);
                RwV3dAddMacro(&v_7C.end, &unk_24_l.end, &v_7C.end);
            }
            else
            {
                v_7C.start.x = unk_1C;
                v_7C.start.y = unk_20;
                v_7C.end.x = v_7C.start.x;
                v_7C.end.y = v_7C.start.y + 2.0f;
                unk_3C = 1;
            }
            if (unk_42C->unk_1B04)
            {
                v_98 = frand_range(-unk_448->unk_370_r[unk_42C->unk_1A04], unk_448->unk_370_r[unk_42C->unk_1A04]);
                v_B0 = frand_range(0.0f, unk_448->unk_364_r[unk_42C->unk_1A04]);
            }
            else
            {
                v_98 = frand_range(-unk_448->unk_2D8_r[unk_42C->unk_1A04], unk_448->unk_2D8_r[unk_42C->unk_1A04]);
                v_B0 = frand_range(0.0f, unk_448->unk_2CC_r[unk_42C->unk_1A04]);
            }
            unk_64 = v_98;
            sub_1403D0(&v_7C, v_B0);
            sub_1402B0(&v_7C, v_98);
            if (unk_42C->unk_1B04)
            {
                if (fabs_ref(v_7C.end.x) > unk_448->unk_34C_r[unk_42C->unk_1A04]
                    || fabs_ref(v_7C.end.y) > unk_448->unk_34C_r[unk_42C->unk_1A04])
                {
                    RwV3d v_F0;

                    v_F0 = v_7C.end;
                    v_7C.end = v_7C.start;
                    v_7C.start = v_F0;
                }
            }
            else
            {
                if (fabs_ref(v_7C.end.x) > unk_448->unk_2B4_r[unk_42C->unk_1A04]
                    || fabs_ref(v_7C.end.y) > unk_448->unk_2B4_r[unk_42C->unk_1A04])
                {
                    RwV3d v_10C;

                    v_10C = v_7C.end;
                    v_7C.end = v_7C.start;
                    v_7C.start = v_10C;
                }
            }
            v_110 = v_7C.end.x;
            v_114 = v_7C.end.y;
            unk_24_l = v_7C;
            if (unk_42C->unk_1B04)
            {
                unk_25C_a[unk_42C->unk_1A04].x -= v_114 - unk_20;
                unk_25C_a[unk_42C->unk_1A04].y += v_110 - unk_1C;
            }
            else
            {
                unk_238_a[unk_42C->unk_1A04].x -= v_114 - unk_20;
                unk_238_a[unk_42C->unk_1A04].y += v_110 - unk_1C;
            }
            unk_1C = v_110;
            unk_20 = v_114;
            sub_170ED0(unk_1C);
            sub_170ED0(unk_20);
            if (unk_42C->unk_1B04)
            {
                if (unk_18 < unk_448->unk_34C_r[unk_42C->unk_1A04])
                {
                    if (unk_18 != 0.0f)
                        unk_18 = unk_448->unk_358_r[unk_42C->unk_1A04]
                            * (unk_18 / unk_448->unk_34C_r[unk_42C->unk_1A04]) + unk_18;
                    else
                        unk_18 = 1.0f;
                }
            }
            else
            {
                if (unk_18 < unk_448->unk_2B4_r[unk_42C->unk_1A04])
                {
                    if (unk_18 != 0.0f && unk_448->unk_2B4_r[unk_42C->unk_1A04] != 0.0f)
                        unk_18 = unk_448->unk_2C0_r[unk_42C->unk_1A04]
                            * (unk_18 / unk_448->unk_2B4_r[unk_42C->unk_1A04]) + unk_18;
                    else
                        unk_18 = 1.0f;
                }
            }
            unk_40++;
        }
        else
            unk_40++;
        v_118 = RwFrameGetMatrix(RwCameraGetFrame((RwCamera *)dword_4E5C74));
        v_11C = (RwDouble)unk_448->unk_488_f * flt_3D7118 + flt_3CD8E0;
        v_134.start = v_118->pos;
        v_134.end.x = v_118->at.x * unk_448->unk_488_f * flt_3D7118 + v_134.start.x;
        v_134.end.y = v_118->at.y * unk_448->unk_488_f * flt_3D7118 + v_134.start.y;
        v_134.end.z = v_118->at.z * unk_448->unk_488_f * flt_3D7118 + v_134.start.z;
        for (v_138 = 0; v_138 < 4; v_138++)
        {
            v_13C = &dword_4E5D30[v_138];
            if (v_13C->get_unk_00() && v_13C->get_unk_28()
                && sub_91F40(v_13C->get_unk_28(), &v_134, &v_174, 1, 0x590000, 1)) // not an address: line-test flags
            {
                RwV3dSubMacro(&v_180, &v_174.unk_08, &v_118->pos);
                if (PVSFindDiagonalSizeOfBBox((RwBBox *)&v_180) < v_11C)
                    v_11C = PVSFindDiagonalSizeOfBBox((RwBBox *)&v_180);
            }
        }
        v_184 = 1.0f;
        if (v_11C >= unk_448->unk_48C_f && v_11C <= unk_448->unk_488_f)
        {
            v_1D0 = *v_118;
            v_210 = v_60;
            v_214 = RtSlerpCreate(0);
            RtSlerpInitialize(v_214, &v_1D0, &v_210);
            v_184 = 1.0f - (v_11C - unk_448->unk_48C_f) / (unk_448->unk_488_f - unk_448->unk_48C_f);
            RtSlerpGetMatrix(v_214, &v_260, v_184);
            RtSlerpDestroy(v_214);
        }
        else
            v_260 = *v_118;
        RwMatrixRotate(&v_260, &stru_3DA4F0, v_184 * unk_20 * -1.0f, rwCOMBINEPRECONCAT);
        RwMatrixRotate(&v_260, &stru_3DA4FC, v_184 * unk_1C, rwCOMBINEPRECONCAT);
        if (unk_42C->unk_1B04)
        {
            v_278 = frand_range(-unk_448->unk_388_r[unk_42C->unk_1A04], unk_448->unk_388_r[unk_42C->unk_1A04]);
            v_290 = frand_range(-unk_448->unk_388_r[unk_42C->unk_1A04], unk_448->unk_388_r[unk_42C->unk_1A04]);
        }
        else
        {
            v_278 = frand_range(-unk_448->unk_2F0_r[unk_42C->unk_1A04], unk_448->unk_2F0_r[unk_42C->unk_1A04]);
            v_290 = frand_range(-unk_448->unk_2F0_r[unk_42C->unk_1A04], unk_448->unk_2F0_r[unk_42C->unk_1A04]);
        }
        RwMatrixRotate(&v_260, &stru_3DA4F0, v_278, rwCOMBINEPRECONCAT);
        RwMatrixRotate(&v_260, &stru_3DA4FC, v_290, rwCOMBINEPRECONCAT);
        v_2C8 = v_260.pos;
        RwV3dIncrementScaledMacro(&v_2C8, &v_260.at, 2000.0f);
        RwV3dSubMacro(&v_2D4, &v_2C8, &v_260.pos);
        RwV3dNormalize(&v_2D4, &v_2D4);
        RwV3dScaleMacro(&v_2D4, &v_2D4, unk_448->unk_B8_f);
        if (unk_448->unk_CC && !unk_464 && !dword_4C19AC)
            unk_414--;
        if ((unk_42C->unk_2C & 7) == 2)
            v_2D8 = 0x202;
        else
            v_2D8 = 0x201;
        if (!unk_42C->unk_217C)
        {
            if (!unk_464)
            {
                unk_29C.unk_00 = 1;
                unk_29C.unk_04_r = (RwUInt32)unk_448->unk_C4 * 1.0f;
                sub_15F2C0(v_2D8, (RwInt32)unk_42C, &v_260, &v_2D4, unk_42C->vf_138(), (type_439A48 *)&unk_29C, 0);
            }
            else
            {
                void *v_2E4;

                v_2E4 = 0;
                switch (unk_42C->unk_4D0)
                {
                case 0:
                    v_2E4 = 0;
                    break;
                case 2:
                    v_2E4 = &unk_448->unk_4FC;
                    break;
                default:
                    v_2E4 = 0;
                }
                unk_29C.unk_00 = 0;
                unk_29C.unk_04_r = (RwUInt32)unk_448->unk_C4 * 1.0f;
                sub_15F2C0(v_2D8, (RwInt32)unk_42C->vf_200(), &v_260, &v_2D4, unk_42C->vf_138(),
                           (type_439A48 *)&unk_29C, (RwInt32)v_2E4);
                unk_42C->unk_1C0.sub_8A980(&dword_4AEFEC, unk_42C, 1, unk_42C->sub_CD550(), 0, 0);
            }
        }
        v_2F4 = 0;
        v_2F8 = 0;
        v_2FC = 0;
        v_300 = unk_42C->unk_1A48[unk_42C->unk_1AE4]->get_unk_458();
        if (!(v_300 == 17 || v_300 == 13 || v_300 == 18 || v_300 == 0 ? 1 : 0) || unk_448->unk_90 || !unk_42C->unk_1B04 || unk_42C->unk_1B0C)
        {
            v_2FC = unk_448->unk_2C;
            if (unk_230)
                v_2FC = unk_448->unk_74;
            if (unk_42C->unk_1B04 && unk_448->unk_90)
                v_2FC = unk_448->unk_94;
            if (!unk_464 && sub_77B70(v_2FC, &v_2F4, &v_2F8))
            {
                unk_42C->unk_284->sub_794C0(0.06666667f);
                unk_42C->unk_284->sub_796A0((RtAnimAnimation *)v_2F4, v_2FC, 0, (struct type_783F0 *)v_2F8, 0.0f,
                                            1.0f, 1.0f);
                unk_10 = 0;
                unk_45 = 1;
            }
        }
        unk_450 = crand() * 2 * unk_448->unk_18C_f - unk_448->unk_18C_f;
        unk_454 = crand() * 2 * unk_448->unk_190_f + 1.0f - unk_448->unk_190_f;
        if (unk_464)
        {
            v_360 = v_260;
            dword_4C19A8 = 1;
            v_364 = (type_F2FF0 *)sub_F2FF0(unk_448->unk_548, &v_360, 0, 0, false, false);
            v_368 = (type_F2FF0 *)sub_F2FF0(unk_448->unk_54C, &v_360, 0, 0, false, false);
            dword_4C19A8 = 0;
            if (!unk_42C->unk_4D0)
            {
                if (v_364)
                {
                    v_364->unk_150_h = unk_42C->get_unk_384_h();
                    v_364->unk_158 = unk_458;
                    v_364->unk_154 = sub_119D50;
                    v_364->unk_40 |= 0x40;
                }
                if (v_368)
                {
                    v_368->unk_150_h = unk_42C->get_unk_384_h();
                    v_368->unk_158 = unk_458;
                    v_368->unk_154 = sub_119D50;
                    v_368->unk_40 |= 0x40;
                }
            }
        }
        unk_50 = unk_50 + unk_54;
        if (unk_50 > 360.0f)
            unk_50 -= 360.0f;
        sub_115390(unk_414, unk_418);
        if (dword_4B9190)
            dword_4B9190->sub_E07A0(unk_414, unk_448->unk_C8);
        return true;
    }
    unk_48 = 1;
    unk_42C->unk_1C0.sub_8A980(&dword_4B1F4C, unk_42C, 0, (RwV3d *)unk_42C->vf_0C4(), 1, 0);
    return false;
}

