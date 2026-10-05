// State 12's movement (vf_040): its turn velocity (unk_F0) takes its turn
// (unk_E4), its yaw rate kept within 80; past a thousandth it turns the
// frame arg_0 by it, and with an animation its two root matrices
// (unk_100, unk_140) turn with it about the second's position, the first
// placed again by the turned offset until it lies within 1e8 in height.
// arg_4 is unused.
// match: ?sub_113D90@type_10F710@@QAEXPAURwFrame@@M@Z @ 0x00113D90
void type_10F710::sub_113D90(RwFrame *arg_0, RwReal arg_4)
{
    RwMatrix *v_8;
    RwMatrix *v_C;
    RwV3d v_18;
    RwInt32 v_1C;
    RwMatrix v_60;
    RwMatrix v_A0;
    RwMatrix v_E0;
    RwV3d v_F0;
    RwV3d v_FC;
    RwMatrix *v_100;

    v_8 = 0;
    v_C = 0;
    v_18.x = 0.0f;
    v_18.y = 0.0f;
    v_18.z = 0.0f;
    v_1C = 0;
    RwV3dAddMacro(&unk_F0_v, &unk_F0_v, &unk_E4_v);
    if (unk_F4 > 80.0f)
        unk_F4 = 80.0f;
    else if (unk_F4 < -80.0f)
        unk_F4 = -80.0f;
    if (unk_284)
    {
        v_8 = &v_60;
        v_C = &v_A0;
        RwMatrixSetIdentityMacro(&v_60);
        RwMatrixSetIdentityMacro(&v_A0);
        v_60 = *(RwMatrix *)&unk_284->unk_100;
        v_A0 = *(RwMatrix *)&unk_284->unk_140;
        v_18.x = v_8->pos.x - v_C->pos.x;
        v_18.y = v_8->pos.y - v_C->pos.y;
        v_18.z = v_8->pos.z - v_C->pos.z;
        RwMatrixSetIdentityMacro(&v_E0);
        v_E0.pos = v_C->pos;
        RwMatrixUpdate(&v_E0);
    }
    if (ABS(unk_F4) > 0.001f)
    {
        RwFrameRotate(arg_0, &stru_3D973C, unk_F4, rwCOMBINEPRECONCAT);
        if (v_8)
        {
            RwMatrixRotate(v_8, &stru_3D973C, unk_F4, rwCOMBINEPRECONCAT);
            RwMatrixRotate(v_C, &stru_3D973C, unk_F4, rwCOMBINEPRECONCAT);
            RwMatrixRotate(&v_E0, &stru_3D973C, unk_F4, rwCOMBINEPRECONCAT);
            v_1C = 1;
        }
    }
    if (v_1C && v_8)
    {
        v_F0 = v_18;
        while (1)
        {
            sub_1414C0(&v_FC, &v_18, &v_E0);
            v_8->pos = v_FC;
            RwMatrixUpdate(v_8);
            if (v_8->pos.y < -1.0e8f || v_8->pos.y > 1.0e8f)
                v_18 = v_F0;
            else
                break;
        }
    }
    if (v_8)
    {
        v_100 = (RwMatrix *)&unk_284->unk_100;
        *v_100 = *v_8;
        v_100 = (RwMatrix *)&unk_284->unk_140;
        *v_100 = *v_C;
    }
    RwFrameUpdateObjects(arg_0);
}

