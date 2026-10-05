// match: ?vf_008@type_21EB30@@UAEXXZ @ 0x0021FB60
void type_21EB30::vf_008()
{
    type_21CB10::vf_008();
    unk_39E = sub_1C48D0();
    RwInt32 var_14 = sub_1C42F0();
    RwInt32 var_10 = 2;

    if (var_14 != 0x29A)
        var_10 = sub_1C4880(var_14);
    if (unk_3A0 != var_10)
    {
        unk_3A0 = var_10;
        sub_2203E0();
    }
    sub_21F1C0();
    if (dword_4FB9E0.get_unk_08_00() == 1)
        unk_2FC.sub_1F28C0(type_1CB670(sub_1C4E60(dword_4FB9E0.get_unk_08_00()), 0));
    else
        unk_2FC.sub_1F28C0(type_1CB670("", 0));
    unk_34C.sub_1F28C0(type_1CB670("", 0));
    switch (unk_154)
    {
    case 0:
    {
        type_1CB670 var_34;

        var_34.sub_1C85D0(unk_3A4);
        unk_324.sub_1F28C0(sub_1CB7B0("RANKED", var_34.c_str(), 0));
        unk_374.sub_1F28C0(sub_1C5350());
        break;
    }
    case 1:
    case 2:
    {
        type_1A5EA0 var_50;

        var_50.sub_1C85D0(unk_3A4);
        unk_324.sub_1F28C0(sub_1CB7B0("RANKED", var_50.c_str(), 0));
        if (unk_4FDBB0.unk_00 == 1)
        {
            RwInt32 var_58 = -1;
            RwInt32 var_54 = -1;

            for (RwInt32 var_5C = 0; var_5C < 16; var_5C++)
            {
                if (sub_1C4630(var_5C))
                {
                    RwInt32 var_60 = sub_1C4800(var_5C);

                    if (var_58 < 0 || var_60 > var_54)
                    {
                        var_54 = var_60;
                        var_58 = var_5C;
                    }
                }
            }
            if (var_58 >= 0)
                unk_34C.sub_1F28C0(sub_1CB7B0("score_%1_wins", sub_1C4630(var_58), 0));
        }
        else if (unk_4FDBB0.unk_00 == 8)
        {
            if (dword_4FB9E0.get_team_count() == 2)
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
        else if (unk_4F7EB8.unk_04.sub_1B33C0(2) > unk_4F7EB8.unk_04.sub_1B33C0(4))
            unk_34C.sub_1F28C0(type_1CB670("score_allieswin", 0));
        else if (unk_4F7EB8.unk_04.sub_1B33C0(2) < unk_4F7EB8.unk_04.sub_1B33C0(4))
            unk_34C.sub_1F28C0(type_1CB670("score_axiswin", 0));
        break;
    }
    }
    sub_1E8B50(0);
}

