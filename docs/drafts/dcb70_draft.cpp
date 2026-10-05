// Starts the search: the session description from the settings copy
// (the server's name and the map), the search's filter (the game type, the
// level, the players (4, 8 or 16), the rules (4 for any) and the name), and
// the network game's search over Xbox Live, else the system link's.
// match: ?sub_20CB70@type_20C470@@QAEXXZ @ 0x0020CB70
void type_20C470::sub_20CB70()
{
    RwInt32 lv_48[4] = {0, 0, 0, 0};
    RwUInt8 *lv_38;
    type_4F8054_4C lv_34;

    sub_20CA70();
    unk_19D = lv_48[0];
    unk_19E = lv_48[1];
    unk_19F = lv_48[2];
    unk_1A0 = lv_48[3];
    unk_1A2 = word_4F62F8;
    unk_198 = sub_1C42E0();
    unk_19C = vf_044();
    lv_34.unk_00[0] = unk_4FDBB0.unk_00;
    lv_34.unk_00[1] = unk_4FDBB0.unk_28;
    lv_34.unk_00[2] = dword_4F6300;
    lv_34.unk_00[3] = dword_4FDAA0;
    lv_34.unk_10 = dword_42CBA8;
    lv_34.unk_14 = dword_42CBAC;
    lv_34.unk_18 = dword_42CBB0;
    lv_34.unk_2C = 0;
    lv_38 = sub_1C4330();
    strncpy((RwChar *)&lv_34.unk_1C, (const RwChar *)lv_38, 16);
    lv_34.unk_1D[0xE] = 0;
    if (lv_34.unk_00[3] == 0)
        lv_34.unk_00[3] = -1;
    if (lv_34.unk_00[0] == 0x20)
        lv_34.unk_00[0] = -1;
    if (lv_34.unk_10 == 4)
        lv_34.unk_10 = -1;
    else
        lv_34.unk_10 = lv_34.unk_10 == 2;
    if (lv_34.unk_14 == 4)
        lv_34.unk_14 = -1;
    else
        lv_34.unk_14 = lv_34.unk_14 == 2;
    if (lv_34.unk_18 == 4)
        lv_34.unk_18 = -1;
    else
        lv_34.unk_18 = lv_34.unk_18 == 2;
    switch (lv_34.unk_00[2])
    {
    case 1:
        lv_34.unk_00[2] = 4;
        break;
    case 2:
        lv_34.unk_00[2] = 8;
        break;
    case 4:
        lv_34.unk_00[2] = 16;
        break;
    default:
        lv_34.unk_00[2] = -1;
        break;
    }
    if (sub_204EA0())
    {
        unk_4F7EB8.get_unk_19C_direct()->vf_070((const type_1CC1F0 *)&unk_198, &lv_34, (RwInt32)unk_1A4, 0x8000);
        unk_8764 = 1;
    }
    else
    {
        sub_20CF20();
    }
    sub_1E41C0();
}

