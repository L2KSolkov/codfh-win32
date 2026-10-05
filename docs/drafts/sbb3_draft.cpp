// The vehicle exit state (state 14): it turns towards the point it leaves
// the vehicle for (unk_213C) and walks there by its trigger's speeds (scaled
// by the weapon's while it is aiming), then, when the transition is
// running (unk_215C), follows it along the blend from unk_2168 by its time;
// it leaves the state (sub_10C290) past 600 or when it is there.
// match: ?sub_10BB30@type_10F710@@QAEXM@Z @ 0x0010BB30
void type_10F710::sub_10BB30(RwReal arg_0)
{
    RwReal v_8;
    type_4C19C0 *v_C;
    RwInt32 v_14;
    RwMatrix *v_1C;
    RwV3d v_28;
    type_712B0_10F710 *v_2C;
    RwV3d v_38;
    RwReal v_3C;
    RwV3d v_48;
    RwReal v_4C;
    RwReal v_50;
    RwMatrix v_90;
    RwReal v_94;
    RwReal v_98;
    RwInt32 v_9C;
    RwReal v_A0;
    RwMatrix v_E0;
    RwReal v_E4;
    RwReal v_E8;
    RwV3d v_F4;

    v_8 = 1.0f;
    v_C = unk_1A48[unk_1AE4]->unk_448;
    v_14 = unk_2148 == 2.0f;
    v_1C = RwFrameGetMatrix(unk_338.get_unk_08());
    v_28 = v_1C->pos;
    if (unk_1B04)
        v_8 = v_C->unk_47C_r[unk_1A04];
    v_2C = (type_712B0_10F710 *)unk_344.unk_08;
    if (v_2C && v_2C->vf_008() != 1)
    {
        v_2C = 0;
    }
    if (!v_2C)
    {
        return;
    }
    if (unk_215C)
        unk_28 |= 0x10;
    else
        unk_28 |= 0x3C;
    unk_10C = v_2C->unk_184;
    unk_134 = v_2C->unk_19C;
    v_38.x = unk_213C.x - v_28.x;
    v_38.y = unk_213C.y - (v_28.y - unk_48 / 2.0f);
    v_38.z = unk_213C.z - v_28.z;
    v_3C = RwV3dDotProductMacro(&v_38, &v_38);
    v_38.y = 0.0f;
    RwV3dNormalize(&v_48, &v_38);
    v_4C = RwV3dDotProductMacro(&v_1C->at, &v_48);
    if (v_3C > 25000000.0f)
        v_50 = 0.96f;
    else
        v_50 = 1.0f - (1.0f - v_3C / 5000.0f * 5000.0f) * 0.04000002f;
    if (v_4C < v_50 && !v_14)
    {
        v_90 = *v_1C;
        RwMatrixRotate(&v_90, &stru_3D973C, 0.5f, rwCOMBINEPRECONCAT);
        v_94 = RwV3dDotProductMacro(&v_90.at, &v_48);
        if (v_94 < v_4C)
            unk_214C = -1.0f;
        else
            unk_214C = 1.0f;
        v_98 = 1.0f;
        if (v_4C > 0.9f)
            v_98 = 1.0f - v_4C;
        unk_214C *= v_98;
        sub_109AE0(v_2C->unk_1B4, arg_0);
    }
    else if (v_14 && v_4C < 0.95f)
        unk_2148 = 1.0f;
    else
    {
        unk_2148 = 2.0f;
        unk_215C = 2;
    }
    v_9C = 0;
    v_A0 = 1.0f;
    if (v_4C > 0.9f)
    {
        v_38.x = unk_213C.x - v_28.x;
        v_38.y = unk_213C.y - (v_28.y - unk_48);
        v_38.z = unk_213C.z - v_28.z;
        if (unk_215C)
            v_38.y = -75.0f;
        RwV3dNormalize(&v_48, &v_38);
        v_90 = *v_1C;
        RwMatrixRotate(&v_90, &stru_3D9730, unk_530, rwCOMBINEPRECONCAT);
        v_A0 = RwV3dDotProductMacro(&v_90.at, &v_48);
        if (v_A0 < 0.96f)
        {
            v_E0 = v_90;
            RwMatrixRotate(&v_E0, &stru_3D9730, 0.5f, rwCOMBINEPRECONCAT);
            v_94 = RwV3dDotProductMacro(&v_E0.at, &v_48);
            if (v_94 < v_A0)
                unk_2158 = -1.0f;
            else
                unk_2158 = 1.0f;
            v_E4 = 1.0f;
            if (v_A0 > 0.9f)
                v_E4 = v_A0;
            unk_2158 *= v_E4;
            v_9C = 0;
            if (unk_530 < 30.0f && unk_530 > -30.0f)
                sub_10A330(1.6f, arg_0);
        }
        else
            v_9C = 1;
    }
    if (unk_530 > 30.0f || unk_530 < -30.0f)
    {
        if (unk_530 > 30.0f)
            unk_2158 = -1.0f;
        else
            unk_2158 = 1.0f;
        sub_10A330(1.6f, arg_0);
    }
    if (!unk_215C)
    {
        if (v_3C > 10000.0f)
        {
            if (v_4C > 0.9f)
            {
                unk_2150 = 1.0f;
                sub_109110(v_8 * v_2C->unk_164[unk_1A04], v_8 * v_2C->unk_170[unk_1A04], arg_0);
            }
        }
        else if (v_9C)
            sub_10C290();
    }
    else
    {
        unk_215C = 2;
        unk_2160 += arg_0;
        v_E8 = unk_2160 / unk_2164;
        if (v_E8 > 1.0f)
        {
            v_E8 = 1.0f;
            unk_2154 = 600.0f;
        }
        sub_112FC0(&v_F4, &unk_2168, &unk_213C, v_E8);
        vf_0C0(&v_F4);
    }
    unk_2154 += arg_0;
    if (unk_2154 > 600.0f)
        sub_10C290();
    if (!((unk_28 >> 1) & 1) && !unk_215C)
        sub_1090F0(2);
    sub_10C370(arg_0);
}

