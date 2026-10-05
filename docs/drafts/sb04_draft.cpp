// Fires its projectile (at its animation's event 1900): from the model's
// "FIRE" node, pushed along the camera's at row, at the settings' speed
// for how it was loaded (unk_47C) turned up by the camera's right row
// (unk_4D8); its record (unk_390, the 0x84-byte settings sub_15F2C0 takes)
// filled from the settings, of table 5 with arg_0, 6 with arg_4 (and the
// longer time), else 2; a grenade kind (0x402) for a player of kind 2,
// else 0x401; raised by 10 while crouched; then the network is told.
// match: ?sub_11B040@type_3DA5A0@@QAEXHH@Z @ 0x0011B040
void type_3DA5A0::sub_11B040(RwInt32 arg_0, RwInt32 arg_4)
{
    RwInt32 v_8;
    RwReal v_C;
    RwMatrix *v_10;
    RpHAnimHierarchy *v_14;
    RwMatrix *v_18;
    RpClump *v_1C;
    RwMatrix v_60;
    RwMatrix *v_64;
    RwReal v_68;
    RwV3d v_74;
    RwMatrix v_C0;
    RwV3d v_CC;
    type_495F0 *v_D0;
    RwInt32 v_DC;

    if (unk_47C)
    {
        v_8 = 0;
        v_C = 13.0f;
    }
    else
    {
        v_8 = 1;
        v_C = 15.0f;
    }
    v_10 = RwFrameGetMatrix(RwCameraGetFrame((RwCamera *)dword_4E5C74));
    memset(&unk_390, 0, sizeof(type_439A48));
    v_14 = unk_42C->unk_284->unk_18;
    v_18 = RpHAnimHierarchyGetMatrixArray(v_14);
    v_1C = unk_420.unk_08;
    sub_EC310(v_1C, v_14, &v_60, 0x46495245, 0, 1); // not an address: 'FIRE'
    v_64 = v_18;
    v_68 = dword_429B64;
    if (unk_458 == 0x21)
        v_68 = 15.0f;
    RwV3dScaleMacro(&v_74, &v_10->at, dword_429B64);
    RwV3dAddMacro(&v_60.pos, &v_74, &v_60.pos);
    RwMatrixInitializeMacro(&v_C0, rwMATRIXTYPENORMAL);
    sub_14D1B0(&v_C0, v_10->right.x, v_10->right.y, v_10->right.z, unk_448->unk_4D8);
    sub_141320(&v_CC, &v_10->at, &v_C0);
    RwV3dScaleMacro(&v_CC, &v_CC, (&unk_448->unk_490)[v_8]);
    v_D0 = (type_495F0 *)sub_198800(&unk_448->unk_00);
    if (arg_0)
        ((type_439A48 *)&unk_390)->unk_00 = 5;
    else if (arg_4)
        ((type_439A48 *)&unk_390)->unk_00 = 6;
    else
        ((type_439A48 *)&unk_390)->unk_00 = 2;
    ((type_439A48 *)&unk_390)->unk_04 = (RwUInt32)unk_448->unk_C4 * 1.0f;
    ((type_439A48 *)&unk_390)->unk_38 = v_D0->sub_18F800(&v_D0->unk_38);
    ((type_439A48 *)&unk_390)->unk_3C = 1;
    ((type_439A48 *)&unk_390)->unk_40 = unk_448->unk_C0_f;
    ((type_439A48 *)&unk_390)->unk_44 = (&unk_448->unk_498)[v_8];
    ((type_439A48 *)&unk_390)->unk_48 = (&unk_448->unk_4AC_f)[v_8];
    ((type_439A48 *)&unk_390)->unk_4C = unk_448->unk_D0;
    if (arg_4)
        ((type_439A48 *)&unk_390)->unk_50 = 18000.0f;
    else
        ((type_439A48 *)&unk_390)->unk_50 = unk_448->unk_4B4;
    ((type_439A48 *)&unk_390)->unk_54 = unk_448->unk_4B8_f * 1.0f;
    ((type_439A48 *)&unk_390)->unk_58 = unk_448->unk_4BC;
    ((type_439A48 *)&unk_390)->unk_60 = unk_448->unk_4C4_f;
    ((type_439A48 *)&unk_390)->unk_5C = unk_448->unk_4C0;
    ((type_439A48 *)&unk_390)->unk_64 = unk_448->unk_4C8_f;
    ((type_439A48 *)&unk_390)->unk_68 = unk_448->unk_4CC;
    ((type_439A48 *)&unk_390)->unk_70 = unk_448->unk_98_f;
    ((type_439A48 *)&unk_390)->unk_6C = unk_448->unk_9C;
    ((type_439A48 *)&unk_390)->unk_78 = unk_448->unk_A0_f;
    ((type_439A48 *)&unk_390)->unk_74 = unk_448->unk_A4_f;
    ((type_439A48 *)&unk_390)->unk_7C = unk_448->unk_A8;
    ((type_439A48 *)&unk_390)->unk_80 = unk_448->unk_AC_f;
    if ((unk_42C->unk_2C & 7) == 2)
        v_DC = 0x402;
    else
        v_DC = 0x401;
    v_60.up.x = 0.0f;
    v_60.up.y = 1.0f;
    v_60.up.z = 0.0f;
    v_60.at.x = 0.0f;
    v_60.at.y = 0.0f;
    v_60.at.z = 1.0f;
    v_60.right.x = 1.0f;
    v_60.right.y = 0.0f;
    v_60.right.z = 0.0f;
    if (unk_42C->unk_1A04 == 2)
        v_60.pos.y += 10.0f;
    sub_15F2C0(v_DC, (RwInt32)unk_42C, &v_60, &v_CC, unk_42C->vf_138(), (type_439A48 *)&unk_390, 0);
    sub_1C5CA0((type_1F8560_v &)v_60.pos, (type_1F8560_v &)v_CC, v_8, unk_458);
}

