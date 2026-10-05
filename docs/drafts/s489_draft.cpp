// The update by arg_0 frames, while there is a player. An emitter with
// children fires them, while its count lasts, when its interval runs out
// (a random count of emissions, each after a random delay; the next
// interval random too), and starts each emission due: its particle system
// at the child's matrix placed by the emission's, its sound (at the player
// when it follows the player, else at the emission) and, with a blast, a
// blast of the emitter's radius and damage there (the player shaken by
// it). A started emitter keeps its sound following the player while it
// plays and is let go once it has no children, system or sound left. An
// emitter without children starts after its delay: its particle system at
// its matrix, its sound and its blast.
// match: ?sub_F4890@@YAXM@Z @ 0x000F4890
// match: __ehhandler$?sub_F4890@@YAXM@Z-0x16 @ 0x003010D0
// match: __ehhandler$?sub_F4890@@YAXM@Z @ 0x003010E6
void sub_F4890(RwReal arg_0)
{
    type_F5740 *v_14;
    type_F5740 *v_18;
    type_3D3548 *v_1C;
    RwInt32 v_20;
    type_F58B0 *v_50;
    type_F5740 *v_54;
    RwMatrix v_A0;
    type_F5740 *v_A4;
    type_F5740 *v_A8;
    RwMatrix v_F0;
    RwMatrix v_230;

    v_14 = 0;
    v_18 = dword_4BFDD0;
    v_1C = sub_1745A0(0);
    if (!v_1C)
        return;
    while (v_18)
    {
        v_14 = v_18->unk_A8;
        if (v_18->unk_7C)
        {
            if (v_18->unk_84 < v_18->unk_80 || v_18->unk_80 == -1)
            {
                if (v_18->unk_90 > 0.0f && !v_18->unk_94)
                    v_18->unk_90 = v_18->unk_90 - arg_0;
                else
                {
                    v_18->unk_18 = 1;
                    v_20 = 0;
                    if (v_18->unk_94)
                        v_20 = v_18->unk_94;
                    else
                        v_20 = RpRandom() % (v_18->unk_9C - v_18->unk_98 + 1) + v_18->unk_98;
                    while (v_20-- > 0)
                    {
                        RwReal v_38;

                        v_38 = frand_range(v_18->unk_A0, v_18->unk_A4);
                        sub_F58B0(v_18, v_38);
                    }
                    v_18->unk_94 = 0;
                    v_18->unk_84++;
                    v_18->unk_90 = frand_range(v_18->unk_88, v_18->unk_8C);
                }
                sub_F57C0(arg_0);
                v_50 = 0;
                while ((v_50 = sub_F57F0()) != 0)
                {
                    v_54 = v_50->unk_00;
                    sub_F54E0(v_54, &v_A0);
                    v_A4 = v_54;
                    while (v_A4)
                    {
                        v_A8 = v_A4->unk_B0;
                        sub_F5370(v_A4, &v_F0, true);
                        RwMatrixTransform(&v_F0, &v_A0, rwCOMBINEPOSTCONCAT);
                        v_A4->unk_28.sub_F2880((type_F2FF0 *)sub_F2FF0(v_A4->unk_00, &v_F0, 0, 0, v_A4->unk_B8 != 0,
                                                                       false));
                        if (v_54->unk_20.unk_00 && v_54->unk_20.unk_04)
                        {
                            if (v_54->unk_1A && v_1C)
                                v_54->unk_60 = dword_4B1E98.sub_8A980(&v_54->unk_20, 0, 8, v_1C->sub_CD550(), 0, 0);
                            else
                                v_54->unk_60 = dword_4B1E98.sub_8A980(&v_54->unk_20, 0, 8, &v_F0.pos, 0, 0);
                            if (v_54->unk_60 == -1)
                                v_54->unk_60 = 0;
                            if (v_54->unk_60)
                            {
                                if (v_54->unk_1A && v_1C)
                                {
                                    do
                                    {
                                        ((type_44C4E8 *)v_54->unk_60)->unk_58 = *v_1C->sub_CD550();
                                        if (((type_44C4E8 *)v_54->unk_60)->unk_30)
                                        {
                                            sub_23F8B0(((type_44C4E8 *)v_54->unk_60)->unk_30, 0, 1,
                                                       v_1C->sub_CD550());
                                        }
                                    } while (0);
                                }
                                else
                                {
                                    do
                                    {
                                        ((type_44C4E8 *)v_54->unk_60)->unk_58 = v_F0.pos;
                                        if (((type_44C4E8 *)v_54->unk_60)->unk_30)
                                        {
                                            sub_23F8B0(((type_44C4E8 *)v_54->unk_60)->unk_30, 0, 1, &v_F0.pos);
                                        }
                                    } while (0);
                                }
                            }
                        }
                        if (v_54->unk_34)
                        {
                            type_F4890_50 v_124;

                            v_124.unk_00 = 0;
                            v_124.unk_04 = v_54->unk_3C;
                            v_124.unk_08 = v_54->unk_40;
                            v_124.unk_0C = v_54->unk_44;
                            v_124.unk_10 = v_54->unk_48;
                            v_124.unk_14 = v_54->unk_4C;
                            v_124.unk_18 = v_54->unk_50;
                            v_124.unk_1C = v_54->unk_64;
                            v_124.unk_24 = v_54->unk_6C;
                            v_124.unk_20 = v_54->unk_68;
                            v_124.unk_28 = v_54->unk_70;
                            v_124.unk_2C = v_54->unk_74;
                            v_124.unk_30 = v_54->unk_78;
                            type_F4890_blast v_1B0;

                            v_1B0.unk_4C_r = v_54->unk_38;
                            v_1B0.unk_04 = v_54->unk_3C;
                            v_1B0.unk_50 = v_124;
                            type_4AE70 v_1E4;

                            v_1E4.unk_00 = 0x804;
                            v_1E4.unk_08 = 0;
                            v_1E4.unk_0C = &v_F0;
                            v_1E4.unk_10 = v_54->unk_38;
                            v_1E4.unk_14 = v_54->unk_38;
                            v_1E4.unk_18 = v_54->unk_38;
                            v_1E4.unk_2C = v_54->unk_3C_f;
                            v_1E4.unk_30 = (RwInt32)&v_1B0;
                            sub_9A960(&v_1E4);
                            if (sub_1745A0(0))
                                ((type_10F710 *)sub_1745A0(0))->sub_114F90((type_114F90 *)&v_1B0, &v_F0.pos);
                        }
                        v_A4 = v_A8;
                    }
                }
            }
            if (v_18->unk_18)
            {
                if (v_18->unk_60)
                {
                    if ((((((type_44C4E8 *)v_18->unk_60)->unk_34 & 2) != 0) != 0))
                    {
                        if (v_18->unk_1A && v_1C)
                        {
                            do
                            {
                                ((type_44C4E8 *)v_18->unk_60)->unk_58 = *v_1C->sub_CD550();
                                if (((type_44C4E8 *)v_18->unk_60)->unk_30)
                                {
                                    sub_23F8B0(((type_44C4E8 *)v_18->unk_60)->unk_30, 0, 1, v_1C->sub_CD550());
                                }
                            } while (0);
                        }
                    }
                    else
                        v_18->unk_60 = 0;
                }
                if (!v_18->unk_7C && !v_18->unk_28.get_unk_08() && !v_18->unk_60)
                    sub_F5C70(v_18);
            }
        }
        else if (v_18->unk_18)
        {
            if (v_18->unk_60)
            {
                if ((((((type_44C4E8 *)v_18->unk_60)->unk_34 & 2) != 0) != 0))
                {
                    if (v_18->unk_1A && v_1C)
                    {
                        do
                        {
                            ((type_44C4E8 *)v_18->unk_60)->unk_58 = *v_1C->sub_CD550();
                            if (((type_44C4E8 *)v_18->unk_60)->unk_30)
                            {
                                sub_23F8B0(((type_44C4E8 *)v_18->unk_60)->unk_30, 0, 1, v_1C->sub_CD550());
                            }
                        } while (0);
                    }
                }
                else
                    v_18->unk_60 = 0;
            }
            if (!v_18->unk_28.get_unk_08() && !v_18->unk_60)
                sub_F5C70(v_18);
        }
        else if (v_18->unk_08 <= 0.0f && !v_18->unk_18)
        {
            v_18->unk_18 = 1;
            sub_F5370(v_18, &v_230, false);
            v_18->unk_28.sub_F2880((type_F2FF0 *)sub_F2FF0(v_18->unk_00, &v_230, 0, 0, v_18->unk_B8 != 0, false));
            if (v_18->unk_20.unk_00 && v_18->unk_20.unk_04)
            {
                if (v_18->unk_1A && v_1C)
                    v_18->unk_60 = dword_4B1E98.sub_8A980(&v_18->unk_20, 0, 8, v_1C->sub_CD550(), 0, 0);
                else
                    v_18->unk_60 = dword_4B1E98.sub_8A980(&v_18->unk_20, 0, 8, &v_230.pos, 0, 0);
                if (v_18->unk_60 == -1)
                    v_18->unk_60 = 0;
                if (v_18->unk_60)
                {
                    if (v_18->unk_1A && v_1C)
                    {
                        do
                        {
                            ((type_44C4E8 *)v_18->unk_60)->unk_58 = *v_1C->sub_CD550();
                            if (((type_44C4E8 *)v_18->unk_60)->unk_30)
                            {
                                sub_23F8B0(((type_44C4E8 *)v_18->unk_60)->unk_30, 0, 1, v_1C->sub_CD550());
                            }
                        } while (0);
                    }
                    else
                    {
                        do
                        {
                            ((type_44C4E8 *)v_18->unk_60)->unk_58 = v_230.pos;
                            if (((type_44C4E8 *)v_18->unk_60)->unk_30)
                            {
                                sub_23F8B0(((type_44C4E8 *)v_18->unk_60)->unk_30, 0, 1, &v_230.pos);
                            }
                        } while (0);
                    }
                }
            }
            if (v_18->unk_34)
            {
                type_F4890_50 v_264;

                v_264.unk_00 = 0;
                v_264.unk_04 = v_18->unk_3C;
                v_264.unk_08 = v_18->unk_40;
                v_264.unk_0C = v_18->unk_44;
                v_264.unk_10 = v_18->unk_48;
                v_264.unk_14 = v_18->unk_4C;
                v_264.unk_18 = v_18->unk_50;
                v_264.unk_1C = v_18->unk_64;
                v_264.unk_24 = v_18->unk_6C;
                v_264.unk_20 = v_18->unk_68;
                v_264.unk_28 = v_18->unk_70;
                v_264.unk_2C = v_18->unk_74;
                v_264.unk_30 = v_18->unk_78;
                type_F4890_blast v_2F0;

                v_2F0.unk_4C_r = v_18->unk_38;
                v_2F0.unk_04 = v_18->unk_3C;
                v_2F0.unk_50 = v_264;
                type_4AE70 v_324;

                v_324.unk_00 = 0x804;
                v_324.unk_08 = 0;
                v_324.unk_0C = &v_230;
                v_324.unk_10 = v_18->unk_38;
                v_324.unk_14 = v_18->unk_38;
                v_324.unk_18 = v_18->unk_38;
                v_324.unk_2C = v_18->unk_3C_f;
                v_324.unk_30 = (RwInt32)&v_2F0;
                sub_9A960(&v_324);
            }
        }
        else if (v_18->unk_08 > 0.0f)
            v_18->unk_08 = v_18->unk_08 - arg_0;
        v_18 = v_14;
    }
}

