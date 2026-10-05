// The nearest entity of the two entity lists with under 0.4 of its health
// (vf_17C) within arg_0 of its eye point (its position raised by half its
// height) that is inside both its frame's and its turned view's cones,
// which narrow with the distance; 0 for none.
// match: ?sub_108CC0@type_10F710@@QAEPAUtype_3DAFC8@@M@Z @ 0x00108CC0
type_3DAFC8 *type_10F710::sub_108CC0(RwReal arg_0)
{
    RwReal v_8;
    RwReal v_C;
    RwReal v_10;
    type_3DAFC8 *v_14;
    RwV3d *v_18;
    RwMatrix *v_20;
    RwV3d *v_24;
    RwMatrix v_70;
    RwV3d *v_74;
    RwInt32 v_78;
    type_3D3548 *v_7C;
    RwV3d *v_80;
    RwV3d v_8C;
    RwReal v_90;
    RwReal v_94;
    RwV3d v_A0;
    RwV3d v_AC;
    RwReal v_B0;
    RwReal v_B4;
    RwV3d v_C0;
    RwReal v_C4;
    RwReal v_C8;

    v_8 = 1.0e10f;
    v_C = arg_0 * arg_0;
    v_10 = unk_48 * 0.5f;
    v_14 = 0;
    v_18 = (RwV3d *)vf_0C4();
    v_20 = RwFrameGetMatrix(unk_338.get_unk_08());
    v_24 = &v_20->at;
    v_70 = *v_20;
    RwMatrixRotate(&v_70, &stru_3D9730, unk_530, rwCOMBINEPRECONCAT);
    v_74 = &v_70.at;
    for (v_78 = 0; v_78 < 2; v_78++)
    {
        v_7C = 0;
        if (v_78 == 0)
            v_7C = dword_4B86A0;
        else
            v_7C = dword_4B8690;
        while (v_7C)
        {
            v_80 = (RwV3d *)v_7C->vf_0C4();
            v_8C.x = v_80->x - v_18->x;
            v_8C.y = v_80->y - (v_18->y - v_10);
            v_8C.z = v_80->z - v_18->z;
            v_90 = RwV3dDotProductMacro(&v_8C, &v_8C);
            v_94 = v_7C->vf_17C();
            if (v_90 < v_C && v_94 < 0.4f)
            {
                v_A0 = v_8C;
                v_A0.y = 0.0f;
                RwV3dNormalize(&v_AC, &v_A0);
                v_B0 = RwV3dDotProductMacro(&v_AC, v_24);
                v_B4 = 1.0f - (1.0f - v_90 / v_C) * 0.050000012f;
                v_C0 = v_8C;
                RwV3dNormalize(&v_AC, &v_C0);
                v_C4 = RwV3dDotProductMacro(&v_AC, v_74);
                v_C8 = 1.0f - (1.0f - v_90 / v_C) * 0.19999999f;
                if (v_B0 > v_B4 && v_C4 > v_C8 && v_90 < v_8)
                {
                    v_8 = v_90;
                    v_14 = (type_3DAFC8 *)v_7C;
                }
            }
            v_7C = v_7C->unk_10;
        }
    }
    return v_14;
}

