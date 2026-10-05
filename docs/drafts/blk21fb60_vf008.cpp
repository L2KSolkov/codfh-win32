void type_21EB30::vf_008()
{
    RwInt32 lv_10;
    RwInt32 lv_14;

    type_21CB10::vf_008();
    unk_39E = sub_1C48D0();
    lv_14 = sub_1C42F0();
    lv_10 = 2;
    if (lv_14 != 666)
        lv_10 = sub_1C4880(lv_14);
    if (unk_3A0 != lv_10)
    {
        unk_3A0 = lv_10;
        sub_2203E0();
    }
    sub_21F1C0();
    if (dword_4FB9E0.get_unk_08() == 1)
        unk_2FC.sub_1F28C0(type_1CB670(sub_1C4E60(dword_4FB9E0.get_unk_08()), 0));
    else
        unk_2FC.sub_1F28C0(type_1CB670("", 0));
    unk_34C.sub_1F28C0(type_1CB670("", 0));
    switch (unk_154)
    {
    case 0:
        {
            type_1CB670 lv_34;

            lv_34.sub_1C85D0(unk_3A4);
            unk_324.sub_1F28C0(sub_1CB7B0("RANKED", lv_34.c_str(), 0));
            unk_374.sub_1F28C0(sub_1C5350());
        }
        break;
    case 1:
    case 2:
        {
            type_1A5EA0 lv_50;

            lv_50.sub_1C85D0(unk_3A4);
            unk_324.sub_1F28C0(sub_1CB7B0("RANKED", lv_50.c_str(), 0));
            if (unk_4FDBB0.unk_00 == 1)
            {
                RwInt32 lv_58 = -1;
                RwInt32 lv_54 = -1;

                for (RwInt32 lv_5C = 0; lv_5C < 16; lv_5C++)
                {
                    if (sub_1C4630(lv_5C))
                    {
                        RwInt32 lv_60 = sub_1C4800(lv_5C);

                        if (lv_58 < 0 || lv_60 > lv_54)
                        {
                            lv_54 = lv_60;
                            lv_58 = lv_5C;
                        }
                    }
                }
                if (lv_58 >= 0)
                    unk_34C.sub_1F28C0(sub_1CB7B0("score_%1_wins", sub_1C4630(lv_58), 0));
            }
            else if (unk_4FDBB0.unk_00 == 8)
            {
                if (dword_4FB9E0.get_unk_10C_side() == 2)
                {
                    if (dword_4FB9E0.get_unk_E8())
                        unk_34C.sub_1F28C0(type_1CB670("score_allieswin", 0));
                    else
                        unk_34C.sub_1F28C0(type_1CB670("score_axiswin", 0));
                }
                else if (!dword_4FB9E0.get_unk_E8())
                    unk_34C.sub_1F28C0(type_1CB670("score_allieswin", 0));
                else
                    unk_34C.sub_1F28C0(type_1CB670("score_axiswin", 0));
            }
            else if (unk_4F7EBC.sub_1B33C0(2) > unk_4F7EBC.sub_1B33C0(4))
                unk_34C.sub_1F28C0(type_1CB670("score_allieswin", 0));
            else if (unk_4F7EBC.sub_1B33C0(2) < unk_4F7EBC.sub_1B33C0(4))
                unk_34C.sub_1F28C0(type_1CB670("score_axiswin", 0));
        }
        break;
    }
    sub_1E8B50(0);
}
