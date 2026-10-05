// Fires once its recoil time (unk_220) reaches the settings' rate (unk_BC);
// false before. With nothing loaded when rounds count (unk_CC) and no
// infinite ammunition (dword_4C19AC) it only plays the empty sound and
// sets unk_48. Otherwise, as the mounted kind's fire, from the bone 0x2B73
// moved by the settings' offset (unk_168) towards 1000 along the blended
// view: a round taken, the projectile's record (unk_30C, table 4) filled,
// fired as kind 0x1002 for a player of kind 2, else 0x1001; the settings'
// particle system (unk_4DC) spawned upright at the muzzle and handed to the
// projectile (with the flame callback sub_119BA0, pushed along the aim at
// 10), the player's camera shaken, its animation played, and the rounds
// display updated.
// match: ?vf_018@type_3DA510@@UAE_NXZ @ 0x0011C540
bool type_3DA510::vf_018()
{
    RpHAnimHierarchy *v_8;
    RwMatrix *v_C;
    RwInt32 v_10;
    RwMatrix *v_14;
    RwMatrix v_60;
    RwV3d v_6C;
    RwMatrix *v_70;
    RwReal v_74;
    RwLine v_8C;
    RwInt32 v_90;
    type_4E5D30 *v_94;
    type_91F40 v_CC;
    RwV3d v_D8;
    RwReal v_DC;
    RwMatrix v_120;
    RwMatrix v_160;
    RwMatrix v_1A0;
    RtSlerp *v_1A4;
    RwMatrix v_1F0;
    RwV3d v_1FC;
    RwV3d v_208;
    type_495F0 *v_20C;
    RwInt32 v_21C;
    type_3DC858 *v_220;
    type_F2FF0 *v_224;
    RwV3d v_230;
    type_3DD948 *v_234;
    RwInt32 v_238;
    RwInt32 v_23C;

    if (unk_220 < unk_448->unk_BC)
        return false;
    memset(&unk_30C, 0, sizeof(type_439A48));
    unk_220 = 0.0f;
    if (unk_414 || !unk_448->unk_CC || dword_4C19AC)
    {
        v_8 = unk_42C->unk_284->unk_18;
        v_C = RpHAnimHierarchyGetMatrixArray(v_8);
        unk_48 = unk_448->unk_D4;
        v_10 = RpHAnimIDGetIndex(v_8, 0x2B73);
        v_14 = &v_C[v_10];
        v_60 = *v_14;
        sub_141320(&v_6C, &unk_448->unk_168, v_14);
        RwMatrixTranslate(&v_60, &v_6C, rwCOMBINEPOSTCONCAT);
        v_70 = RwFrameGetMatrix(RwCameraGetFrame((RwCamera *)dword_4E5C74));
        v_74 = (RwDouble)unk_448->unk_488_f * flt_3D7118 + flt_3CD8E0;
        v_8C.start = v_70->pos;
        v_8C.end.x = v_70->at.x * unk_448->unk_488_f * flt_3D7118 + v_8C.start.x;
        v_8C.end.y = v_70->at.y * unk_448->unk_488_f * flt_3D7118 + v_8C.start.y;
        v_8C.end.z = v_70->at.z * unk_448->unk_488_f * flt_3D7118 + v_8C.start.z;
        for (v_90 = 0; v_90 < 4; v_90++)
        {
            v_94 = &dword_4E5D30[v_90];
            if (v_94->get_unk_00() && v_94->get_unk_28()
                && sub_91F40(v_94->get_unk_28(), &v_8C, &v_CC, 1, 0x590000, 1)) // not an address: line-test flags
            {
                RwV3dSubMacro(&v_D8, &v_CC.unk_08, &v_70->pos);
                if (PVSFindDiagonalSizeOfBBox((RwBBox *)&v_D8) < v_74)
                    v_74 = PVSFindDiagonalSizeOfBBox((RwBBox *)&v_D8);
            }
        }
        v_DC = 1.0f;
        if (v_74 >= unk_448->unk_48C_f && v_74 <= unk_448->unk_488_f)
        {
            v_120 = *v_70;
            sub_141690(&v_160, 0);
            v_1A0 = v_160;
            v_1A4 = RtSlerpCreate(0);
            RtSlerpInitialize(v_1A4, &v_120, &v_1A0);
            v_DC = 1.0f - (v_74 - unk_448->unk_48C_f) / (unk_448->unk_488_f - unk_448->unk_48C_f);
            RtSlerpGetMatrix(v_1A4, &v_1F0, v_DC);
            RtSlerpDestroy(v_1A4);
        }
        else
            v_1F0 = *v_70;
        v_14 = &v_1F0;
        v_1FC = v_14->pos;
        RwV3dIncrementScaledMacro(&v_1FC, &v_14->at, 1000.0f);
        RwV3dSubMacro(&v_208, &v_1FC, &v_60.pos);
        RwV3dNormalize(&v_208, &v_208);
        RwV3dScaleMacro(&v_208, &v_208, unk_448->unk_B8_f);
        if (unk_448->unk_CC && !dword_4C19AC)
            unk_414--;
        v_20C = (type_495F0 *)sub_198800(&unk_448->unk_00);
        ((type_439A48 *)&unk_30C)->unk_00 = 4;
        ((type_439A48 *)&unk_30C)->unk_04 = (RwUInt32)unk_448->unk_C4 * 1.0f;
        ((type_439A48 *)&unk_30C)->unk_38 = v_20C->sub_18F800(&v_20C->unk_38);
        ((type_439A48 *)&unk_30C)->unk_3C = 1;
        ((type_439A48 *)&unk_30C)->unk_40 = unk_448->unk_C0_f;
        ((type_439A48 *)&unk_30C)->unk_44 = unk_448->unk_194_f;
        ((type_439A48 *)&unk_30C)->unk_48 = unk_448->unk_198_f;
        ((type_439A48 *)&unk_30C)->unk_4C = unk_448->unk_D0;
        ((type_439A48 *)&unk_30C)->unk_50 = unk_448->unk_4B4;
        ((type_439A48 *)&unk_30C)->unk_54 = unk_448->unk_4B8_f;
        ((type_439A48 *)&unk_30C)->unk_58 = unk_448->unk_4BC;
        ((type_439A48 *)&unk_30C)->unk_5C = unk_448->unk_4C0;
        ((type_439A48 *)&unk_30C)->unk_60 = unk_448->unk_4C4_f;
        ((type_439A48 *)&unk_30C)->unk_64 = unk_448->unk_4C8_f;
        ((type_439A48 *)&unk_30C)->unk_68 = unk_448->unk_4CC;
        ((type_439A48 *)&unk_30C)->unk_70 = unk_448->unk_98_f;
        ((type_439A48 *)&unk_30C)->unk_6C = unk_448->unk_9C;
        ((type_439A48 *)&unk_30C)->unk_78 = unk_448->unk_A0_f;
        ((type_439A48 *)&unk_30C)->unk_74 = unk_448->unk_A4_f;
        ((type_439A48 *)&unk_30C)->unk_7C = unk_448->unk_A8;
        ((type_439A48 *)&unk_30C)->unk_80 = unk_448->unk_AC_f;
        if ((unk_42C->unk_2C & 7) == 2)
            v_21C = 0x1002;
        else
            v_21C = 0x1001;
        v_220 = (type_3DC858 *)sub_15F2C0(v_21C, (RwInt32)unk_42C, &v_60, &v_208, unk_42C->vf_138(),
                                          (type_439A48 *)&unk_30C, 0);
        v_60.at.x = 0.0f;
        v_60.at.y = 0.0f;
        v_60.at.z = 1.0f;
        v_60.up.x = 0.0f;
        v_60.up.y = 1.0f;
        v_60.up.z = 0.0f;
        v_60.right.x = 1.0f;
        v_60.right.y = 0.0f;
        v_60.right.z = 0.0f;
        v_224 = (type_F2FF0 *)sub_F2FF0(unk_448->unk_4DC, &v_60, 0, 0, false, true);
        v_220->unk_70.sub_F2880(v_224);
        if (v_224)
        {
            v_224->unk_154 = sub_119BA0;
            RwV3dScaleMacro(&v_230, &v_208, 10.0f);
            sub_19E9B0((type_19E9B0 *)&v_224->unk_60, &v_230);
        }
        v_234 = (type_3DD948 *)unk_42C->unk_2110.sub_D4910();
        v_234->sub_175E50(6.0f, 8.0f, 5.0f);
        if (sub_77B70(unk_448->unk_2C, &v_23C, &v_238))
        {
            unk_42C->unk_284->sub_794C0(0.06666667f);
            unk_42C->unk_284->sub_796A0((RtAnimAnimation *)v_23C, unk_448->unk_2C, 0, (struct type_783F0 *)v_238,
                                        0.0f, 1.0f, 1.0f);
            unk_10 = 0;
            unk_45 = 1;
        }
        unk_42C->sub_108B60();
        return true;
    }
    unk_48 = 1;
    unk_42C->unk_1C0.sub_8A980(&dword_4B1F4C, unk_42C, 0, (RwV3d *)unk_42C->vf_0C4(), 1, 0);
    return false;
}

