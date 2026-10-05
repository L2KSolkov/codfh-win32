// The step after the others'. With its trigger: its animation advances, its
// frame is kept orthonormal every 64 frames, its eye height follows the
// stance (blended while it changes), its model and the weapon's hold the
// head bone's place 100 units away; alive and moving freely, the pickup it
// stands on is taken, the help text cleared, its mounted weapon, the action
// object and the performance maps it is in offer their actions (the level's
// end trigger ends the level); then a mounted weapon it no longer holds lets
// it go, and its AI's late step, its vf_1D0 and the ladder's step run.
// match: ?vf_04C@type_10F710@@UAEXM@Z @ 0x00105B00
void type_10F710::vf_04C(RwReal arg_0)
{
    type_712B0_10F710 *v_8;
    RwReal v_14;
    RpHAnimHierarchy *v_18;
    RwMatrix *v_1C;
    RwMatrix v_60;
    RwV3d v_6C;
    type_3DC9B0 *v_78;

    v_8 = (type_712B0_10F710 *)unk_344.unk_08;
    if (v_8 && v_8->vf_008() != 1)
    {
        v_8 = 0;
    }
    if (!v_8)
        return;
    sub_CDF40(arg_0);
    if ((dword_4B87D8 & 0x3F) == 0x3F)
    {
        RwMatrix *v_10 = RwFrameGetMatrix(get_unk_340());

        RwMatrixOrthoNormalize(v_10, v_10);
    }
    unk_3E0 += arg_0;
    unk_48 = v_8->unk_144_a[unk_1A04];
    if (unk_1A0C)
        unk_48 = sub_112F80(v_8->unk_144_a[unk_1A08], v_8->unk_144_a[unk_1A04], unk_1A10);
    v_14 = 100.0f;
    v_18 = unk_284->unk_18;
    v_1C = RpHAnimHierarchyGetMatrixArray(v_18);
    RwMatrixInvert(&v_60, RwFrameGetLTM(RpClumpGetFrame(unk_1A3C.get_unk_08())));
    sub_1414C0(&v_6C, &v_1C->pos, &v_60);
    v_6C.z += 50.0f;
    sub_16DFA0(unk_1A3C.get_unk_08(), &v_6C, v_14);
    sub_16DFA0(unk_1A48[unk_1AE4]->get_unk_428(), &v_6C, v_14);
    if (unk_19F8 <= 0 && unk_19DC > 0.0f && !((dword_4B86F8 >> 6) & 1) && unk_2148 == 0.0f)
    {
        type_144E80 *v_84;
        RwInt32 v_88;
        RwInt32 v_8C;
        RwInt32 v_90;

        if (!sub_106620((struct type_3D94B8 *)unk_2108.sub_D4910()))
            unk_2108.sub_D48D0(0);
        sub_EAB80(pResourcePath, 6);
        if (unk_2108.sub_D4910())
        {
            sub_106A60(unk_2108.sub_D4910());
            unk_2108.sub_D48D0(0);
        }
        else
        {
            sub_10F7E0(0xB, 0);
            sub_10F7E0(0xC, 0);
        }
        v_78 = (type_3DC9B0 *)unk_210C.sub_D4910();
        if (v_78 && v_78->sub_169190(this))
        {
            if (!unk_1B28)
            {
                sub_10F7E0(5, 1);
                sub_10F7E0(4, 0);
            }
            else
            {
                sub_10F7E0(5, 0);
                sub_10F7E0(4, 1);
            }
        }
        else
        {
            sub_10F7E0(5, 0);
            sub_10F7E0(4, 0);
        }
        if (unk_2114.sub_D4910())
        {
            sub_10F7E0(9, 1);
            if (sub_10F710() == 9)
            {
                if (((type_3D3548 *)unk_2114.sub_D4910())->vf_098())
                    sub_6B5F0("ActionItem", ((type_3D3548 *)unk_2114.sub_D4910())->vf_098(), 0, 0, 0, 0, 1, 0);
                sub_10F7E0(9, 0);
            }
        }
        else
            sub_10F7E0(9, 0);
        unk_2114.sub_D48D0(0);
        v_84 = (type_144E80 *)unk_24C;
        v_88 = unk_248;
        v_8C = 1;
        v_90 = sub_144E80(&v_84, &v_8C, -1);
        while (v_90 != -1)
        {
            if (v_8C & v_88)
            {
                RwInt32 v_94 = 1;
                Trigger *v_98 = (Trigger *)get_performance_map(v_90);

                if (v_98->vf_008() == 0x24)
                {
                    EndLevelTrigger *v_9C = (EndLevelTrigger *)v_98;

                    if (v_9C->unk_C4)
                    {
                        sub_10F7E0(0, 1);
                        v_94 = 0;
                        if (!sub_10F710())
                        {
                            RwInt32 v_A0;

                            if (dword_4B9190)
                                dword_4B9190->sub_E0410(4);
                            v_A0 = v_9C->sub_CC330();
                            if (v_A0)
                                sub_D8CC0(v_A0);
                            else
                                sub_D8C20();
                        }
                    }
                }
                else
                    sub_10F7E0(0, 0);
                if (v_94 && (v_98->unk_42 & 0xF))
                {
                    sub_10F7E0(9, 1);
                    if (sub_10F790() == 9)
                    {
                        if (dword_4B9190)
                            dword_4B9190->sub_E0410(v_98->unk_42 & 0xF);
                    }
                    else
                        sub_10F7E0(9, 0);
                    break;
                }
                if (sub_10F790() != 9)
                    sub_10F7E0(9, 0);
            }
            v_90 = sub_144E80(&v_84, &v_8C, (RwInt16)v_90);
        }
        if (sub_10F710() == 5 && !v_78->unk_47C)
        {
            v_78->sub_168820(this);
            sub_1090F0(7);
            if (dword_4B9190)
                dword_4B9190->sub_DEB80(2);
        }
        if (sub_10F710() == 4)
        {
            v_78 = (type_3DC9B0 *)unk_210C.sub_D4910();
            if (v_78 && unk_1B28 && v_78->sub_169350(1))
            {
                v_78->sub_168A90(this);
                sub_1090F0(0);
                if (dword_4B9190)
                    dword_4B9190->sub_DEB80(0);
            }
        }
    }
    v_78 = (type_3DC9B0 *)unk_210C.sub_D4910();
    if (v_78 && (unk_19D0 == 7 || unk_1B28) && v_78->vf_1F8(0) != this)
    {
        v_78->sub_168A90(this);
        sub_1090F0(0);
        if (dword_4B9190)
            dword_4B9190->sub_DEB80(0);
    }
    if (v_78)
        v_78->unk_47C = 0;
    if (!unk_1B28)
        unk_210C.sub_D48D0(0);
    sub_16D7F0(0x18);
    unk_550.sub_17A20(arg_0);
    sub_16D850(0x18);
    vf_1D0();
    unk_1A30 = 1.0f;
    if (unk_19D0 == 0xD)
        sub_114E70(arg_0);
}
