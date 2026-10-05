// Fires once its recoil time (unk_220) reaches the settings' rate (unk_BC);
// false before. From a vehicle's seat the vehicle fires (its vf_2A8).
// Otherwise from the model's "FIRE" node towards 2000 along the view: the
// camera's matrix, or within the settings' near and far ranges (unk_48C,
// unk_488) of the nearest world hit along the camera's at row a blend
// towards the aim matrix (sub_141690) by that distance; its spread (unk_450,
// unk_454) random within the settings'; the projectile's record (unk_30C,
// table 3) filled from the settings; a round taken when they count
// (unk_CC); fired as kind 0x1002 for a player of kind 2, else 0x1001; the
// vehicle it stands on pushed back by its mass, the camera shaken, the
// muzzle light lit, and its animation played (or its particle events'
// effects spawned from a vehicle's seat).
// match: ?vf_018@type_3DA558@@UAE_NXZ @ 0x0011B9C0
bool type_3DA558::vf_018()
{
    RpHAnimHierarchy *v_8;
    RwMatrix *v_C;
    RpClump *v_10;
    RwMatrix v_50;
    RwMatrix *v_54;
    RwReal v_58;
    RwLine v_70;
    RwInt32 v_74;
    type_4E5D30 *v_78;
    type_91F40 v_B0;
    RwV3d v_BC;
    RwReal v_C0;
    RwMatrix v_100;
    RwMatrix v_140;
    RwMatrix v_180;
    RtSlerp *v_184;
    RwMatrix v_1D0;
    RwMatrix *v_1D4;
    RwV3d v_1E0;
    type_3DBC78 *v_1E4;
    RwV3d v_200;
    type_495F0 *v_204;
    RwInt32 v_214;
    type_3DBC78 *v_218;
    RwV3d v_224;
    RwV3d v_230;
    type_3DBC78 *v_234;
    type_140490 v_250;
    RwV3d v_25C;
    RwInt32 v_260;
    RwInt32 v_264;
    type_783F0_04 *v_268;
    RwInt32 *v_26C;

    if (unk_220 < unk_448->unk_BC)
        return false;
    memset(&unk_30C, 0, sizeof(type_439A48));
    unk_220 = 0.0f;
    v_8 = unk_42C->unk_284->unk_18;
    v_C = RpHAnimHierarchyGetMatrixArray(v_8);
    unk_48 = unk_448->unk_D4;
    if (!unk_42C->unk_4D0)
    {
        v_10 = unk_420.unk_08;
        sub_EC310(v_10, v_8, &v_50, 0x46495245, 0, 1); // not an address: 'FIRE'
        v_54 = RwFrameGetMatrix(RwCameraGetFrame((RwCamera *)dword_4E5C74));
        v_58 = (RwDouble)unk_448->unk_488_f * flt_3D7118 + flt_3CD8E0;
        v_70.start = v_54->pos;
        v_70.end.x = v_54->at.x * unk_448->unk_488_f * flt_3D7118 + v_70.start.x;
        v_70.end.y = v_54->at.y * unk_448->unk_488_f * flt_3D7118 + v_70.start.y;
        v_70.end.z = v_54->at.z * unk_448->unk_488_f * flt_3D7118 + v_70.start.z;
        for (v_74 = 0; v_74 < 4; v_74++)
        {
            v_78 = &dword_4E5D30[v_74];
            if (v_78->get_unk_00() && v_78->get_unk_28()
                && sub_91F40(v_78->get_unk_28(), &v_70, &v_B0, 1, 0x590000, 1)) // not an address: line-test flags
            {
                RwV3dSubMacro(&v_BC, &v_B0.unk_08, &v_54->pos);
                if (PVSFindDiagonalSizeOfBBox((RwBBox *)&v_BC) < v_58)
                    v_58 = PVSFindDiagonalSizeOfBBox((RwBBox *)&v_BC);
            }
        }
        v_C0 = 1.0f;
        if (v_58 >= unk_448->unk_48C_f && v_58 <= unk_448->unk_488_f)
        {
            v_100 = *v_54;
            sub_141690(&v_140, 0);
            v_180 = v_140;
            v_184 = RtSlerpCreate(0);
            RtSlerpInitialize(v_184, &v_100, &v_180);
            v_C0 = 1.0f - (v_58 - unk_448->unk_48C_f) / (unk_448->unk_488_f - unk_448->unk_48C_f);
            RtSlerpGetMatrix(v_184, &v_1D0, v_C0);
            RtSlerpDestroy(v_184);
        }
        else
            v_1D0 = *v_54;
        v_1D4 = &v_1D0;
        v_1E0 = v_1D4->pos;
        RwV3dIncrementScaledMacro(&v_1E0, &v_1D4->at, 2000.0f);
    }
    else
    {
        v_1E4 = (type_3DBC78 *)unk_42C->vf_200();
        return v_1E4->vf_2A8(0, 0, 1);
    }
    unk_450 = crand() * 2 * unk_448->unk_18C_f - unk_448->unk_18C_f;
    unk_454 = crand() * 2 * unk_448->unk_190_f + 1.0f - unk_448->unk_190_f;
    RwV3dSubMacro(&v_200, &v_1E0, &v_50.pos);
    RwV3dNormalize(&v_200, &v_200);
    RwV3dScaleMacro(&v_200, &v_200, unk_448->unk_B8_f);
    if (unk_448->unk_CC)
        unk_418--;
    v_204 = (type_495F0 *)sub_198800(&unk_448->unk_00);
    ((type_439A48 *)&unk_30C)->unk_00 = 3;
    ((type_439A48 *)&unk_30C)->unk_04 = (RwUInt32)unk_448->unk_C4 * 1.0f;
    ((type_439A48 *)&unk_30C)->unk_38 = v_204->sub_18F800(&v_204->unk_38);
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
        v_214 = 0x1002;
    else
        v_214 = 0x1001;
    sub_15F2C0(v_214, (RwInt32)unk_42C, &v_50, &v_200, unk_42C->vf_138(), (type_439A48 *)&unk_30C, 0);
    v_218 = (type_3DBC78 *)unk_42C->vf_200();
    if (v_218)
    {
        v_224.x = 0.0f;
        v_224.y = 200.0f;
        v_224.z = 100.0f;
        v_230.x = 0.0f;
        v_230.y = 0.0f;
        v_230.z = -5.0f * v_218->unk_450.unk_24C;
        sub_141320(&v_224, &v_224, &v_50);
        sub_141320(&v_230, &v_230, &v_50);
        v_218->vf_264(0xF0, &v_230, &v_224);
    }
    unk_4E5E50.sub_176180(4, 0, 1.0f, 0);
    if (!unk_42C->unk_4D0)
    {
        v_234 = (type_3DBC78 *)unk_42C->vf_200();
        v_250.x = 1.0f;
        v_250.y = 1.0f;
        v_250.z = 1.0f;
        v_250.w = 1.0f;
        v_25C.x = 1.0f;
        v_25C.y = 0.0f;
        v_25C.z = 0.0f;
        v_234->unk_90.sub_8F140(1, 0.1f, &v_25C, (type_8BEC0 *)&v_250, 0, 0);
    }
    if (sub_77B70(unk_448->unk_2C, &v_264, &v_260))
    {
        if (!unk_42C->unk_4D0)
        {
            unk_42C->unk_284->sub_794C0(0.06666667f);
            unk_42C->unk_284->sub_796A0((RtAnimAnimation *)v_264, unk_448->unk_2C, 0, (struct type_783F0 *)v_260,
                                        0.0f, 1.0f, 1.0f);
            unk_10 = 0;
        }
        else
        {
            v_268 = ((type_783F0 *)v_260)->sub_78550(0.0f, -1);
            while (v_268)
            {
                if (v_268->unk_00 == 0x514)
                {
                    v_26C = &v_268->unk_08;
                    sub_F2FF0(v_26C[3], &v_50, 0, 1, 0, 1);
                }
                v_268 = ((type_783F0 *)v_260)->sub_785C0(v_268, -1);
            }
        }
    }
    return true;
}

