// A player's line: its number, 'F' when it is in the game's peers ('E'
// otherwise), '*' for this machine, its latency in seconds, its kills and
// deaths. An inline with no address, named for what it does. Evidence:
// the debug display (sub_1B00F0) prints it twice with the same code, the
// latency and the peer's bit kept in slots of their own first.
inline void print_peer(RwChar *arg_0, RwUInt32 arg_4, RwInt32 arg_8, RwInt32 arg_C, RwInt32 arg_10)
{
    sprintf(arg_0, "%02d) %c%c p:%02.3f k:%d d:%d", arg_4, 'E' + (arg_C != 0), arg_4 == arg_8 ? '*' : ' ',
            (RwReal)arg_10 / 1000.0f, unk_4F7EB8.unk_04.sub_1B3380(arg_4), unk_4F7EB8.unk_04.sub_1B33A0(arg_4));
}

// The debug display, returning at once in this build: the log's lines
// in the chosen channel; with a network game, each player's traffic (its
// running averages in unk_2F18) with its latency, kills and deaths, the
// totals (averaged in unk_3498) and the view position; and with unk_34F1
// set, the voice chat's state.
// match: ?sub_1B00F0@type_4F84B8@@QAEXXZ @ 0x001B00F0
// match: __ehhandler$?sub_1B00F0@type_4F84B8@@QAEXXZ-0x8 @ 0x00302C00
// match: __ehhandler$?sub_1B00F0@type_4F84B8@@QAEXXZ @ 0x00302C08
void type_4F84B8::sub_1B00F0()
{
    RwUInt32 lv_10;
    RwUInt32 lv_14;
    std::vector<RwUInt32> lv_24;
    type_1D02A0 *lv_28;
    RwUInt32 lv_50[10];
    cTimeKeeper *lv_54;
    RwUInt32 lv_58;
    type_4F8054_B0 *lv_5C;
    RwChar lv_164[256];
    RwReal lv_168;
    RwUInt32 lv_16C;
    RwUInt32 lv_194[10];
    RwInt32 lv_198;
    RwUInt16 lv_19C;
    RwUInt32 lv_1A0;
    RwUInt32 lv_1A4;
    type_1D02A0 *lv_1A8;
    RwReal lv_1AC;
    RwUInt32 lv_1B0;
    RwReal *lv_1B4;
    type_1DF990 lv_2C4;
    RwChar lv_2E4[32];
    RwChar lv_304[32];
    type_1DDE20_mask lv_308;
    type_1C6900 lv_3EC;

    return;
    for (lv_14 = 0; lv_14 < dword_3E1A60[unk_00] && lv_14 < unk_14[unk_04]; lv_14++)
    {
        lv_1A4 = (lv_14 + unk_20[unk_04]) % 50;
        switch (unk_00)
        {
        case 0:
        case 1:
            sub_16BB00(unk_2C[unk_04][lv_1A4], 300, lv_14 * 15 + 10);
            break;
        case 2:
            sub_16BB00(unk_2C[unk_04][lv_1A4], 10, lv_14 * 15 + 10);
            break;
        }
    }
    if (!unk_34F4)
    {
        sub_16BBA0();
        return;
    }
    memset(lv_50, 0, sizeof(lv_50));
    lv_5C = unk_34F4->unk_B0;
    if (!unk_34F4->get_unk_B8() && lv_5C->get_unk_310() != 7)
    {
        sub_16BBA0();
        return;
    }
    if (!unk_34F4->get_unk_04() || unk_34F4->get_unk_04() == 3)
        return;
    lv_54 = unk_34F4->unk_B4;
    lv_19C = lv_5C->unk_0C.unk_00;
    lv_198 = lv_5C->sub_1CFF90();
    unk_4F7EB8.unk_04.sub_1B3480(lv_24);
    for (lv_58 = 0; lv_58 < lv_24.size(); lv_58++)
    {
        lv_14 = lv_24[lv_58];
        lv_1A8 = &unk_34F4->get_unk_AC()->unk_4C4;
        if (lv_198 != lv_14 && lv_1A8->unk_50[lv_14])
        {
            lv_194[0] = lv_1A8->unk_D0[lv_14];
            lv_194[1] = lv_1A8->unk_1D0[lv_14];
            lv_194[2] = lv_1A8->unk_110[lv_14];
            lv_194[3] = lv_1A8->unk_210[lv_14];
            lv_194[4] = lv_1A8->unk_150[lv_14];
            lv_194[5] = lv_1A8->unk_250[lv_14];
            lv_194[6] = lv_1A8->unk_190[lv_14];
            lv_194[7] = lv_1A8->unk_290[lv_14];
            lv_194[8] = lv_194[0] + lv_194[2] + lv_194[4] + lv_194[6];
            lv_194[9] = lv_194[1] + lv_194[3] + lv_194[5] + lv_194[7];
            for (lv_1A0 = 0; lv_1A0 < 10; lv_1A0++)
                lv_50[lv_1A0] += lv_194[lv_1A0];
            lv_1B0 = sub_1CCA10().since(lv_1A8->unk_90[lv_14]).get_unk_00();
            lv_1AC = (RwReal)(lv_1B0 - unk_2F18[lv_14].unk_50) / 1000.0f;
            if (unk_2F18[lv_14].unk_54)
            {
                for (lv_1A0 = 0; lv_1A0 < 10; lv_1A0++)
                    unk_2F18[lv_14].unk_28[lv_1A0] = unk_2F18[lv_14].unk_28[lv_1A0] * 0.99f
                        + (RwReal)(lv_194[lv_1A0] - unk_2F18[lv_14].unk_00[lv_1A0]) / lv_1AC * 0.01f;
            }
            else
            {
                for (lv_1A0 = 0; lv_1A0 < 10; lv_1A0++)
                    unk_2F18[lv_14].unk_28[lv_1A0] = (RwReal)lv_194[lv_1A0] * 1000.0f / (RwReal)lv_1B0;
                unk_2F18[lv_14].unk_54 = 1;
            }
            memcpy(unk_2F18[lv_14].unk_00, lv_194, sizeof(lv_194));
            unk_2F18[lv_14].unk_50 = lv_1B0;
            print_peer(lv_164, lv_14, lv_198, lv_19C & (1 << lv_14), lv_54->get_unk_61C(lv_14).get_unk_00());
            if (lv_58 == 15)
            {
                sprintf(&lv_164[strlen(lv_164)], "  Allies:%d  Germans:%d", unk_4F7EB8.unk_04.sub_1B33C0(2),
                        unk_4F7EB8.unk_04.sub_1B33C0(4));
            }
        }
        else
        {
            unk_2F18[lv_14].unk_54 = 0;
            print_peer(lv_164, lv_14, lv_198, lv_19C & (1 << lv_14), lv_54->get_unk_61C(lv_14).get_unk_00());
            if (lv_58 == 15)
            {
                sprintf(&lv_164[strlen(lv_164)], "  Allies:%d  Germans:%d", unk_4F7EB8.unk_04.sub_1B33C0(2),
                        unk_4F7EB8.unk_04.sub_1B33C0(4));
            }
            for (lv_1A0 = 0; lv_1A0 < 10; lv_1A0++)
                lv_50[lv_1A0] += unk_2F18[lv_14].unk_00[lv_1A0];
        }
        if (unk_34F0 && !unk_34F1 && unk_00 != 2)
            sub_16BB00(lv_164, 0, lv_58 * 15 + 150);
    }
    lv_28 = &unk_34F4->get_unk_AC()->unk_4C4;
    lv_16C = sub_1CCA10().since(lv_28->unk_90[lv_14]).get_unk_00();
    lv_168 = (RwReal)(lv_16C - unk_3498.unk_50) / 1000.0f;
    for (lv_1A0 = 0; lv_1A0 < 10; lv_1A0++)
        unk_3498.unk_28[lv_1A0] = unk_3498.unk_28[lv_1A0] * 0.99f
            + (RwReal)(lv_50[lv_1A0] - unk_3498.unk_00[lv_1A0]) / lv_168 * 0.01f;
    memcpy(unk_3498.unk_00, lv_50, sizeof(lv_50));
    unk_3498.unk_50 = lv_16C;
    sprintf(lv_164, "Total          n:%d/%d g:%d/%d t:%d/%d h:%d/%d o:%d/%d", (RwInt32)(unk_3498.unk_28[0] / 8.0f),
            (RwInt32)(unk_3498.unk_28[1] / 8.0f), (RwInt32)(unk_3498.unk_28[2] / 8.0f),
            (RwInt32)(unk_3498.unk_28[3] / 8.0f), (RwInt32)(unk_3498.unk_28[4] / 8.0f),
            (RwInt32)(unk_3498.unk_28[5] / 8.0f), (RwInt32)(unk_3498.unk_28[6] / 8.0f),
            (RwInt32)(unk_3498.unk_28[7] / 8.0f), (RwInt32)(unk_3498.unk_28[8] / 8.0f),
            (RwInt32)(unk_3498.unk_28[9] / 8.0f));
    if (unk_34F0 && !unk_34F1 && unk_00 != 2)
        sub_16BB00(lv_164, 0, 405);
    if (unk_4F7EB8.sub_1AECA0(unk_4F7EB8.sub_1AEC70(), 0))
    {
        lv_1B4 = unk_4F7EB8.sub_1AECA0(unk_4F7EB8.sub_1AEC70(), 0)->vf_0C4();
        sprintf(lv_164, "ViewPos: %.0f, %.0f, %.0f", lv_1B4[0], lv_1B4[1], lv_1B4[2]);
        if (unk_34F0 && !unk_34F1 && unk_00 != 2)
            sub_16BB00(lv_164, 10, 10);
    }
    if (unk_34F1)
    {
        lv_308 = type_4F8054::get()->get_unk_B0()->others();
        get_dword_4F8180()->sub_1C6900(&lv_3EC, sub_1CCA10());
        get_dword_4F8180()->unk_14.sub_1DF990(&lv_2C4, sub_1CCA10());
        lv_10 = 50;
        sprintf(lv_164, "PENDING ENCODE      : %5d", lv_3EC.unk_00);
        sub_16BB00(lv_164, 50, lv_10);
        lv_10 += 15;
        sprintf(lv_164, "PENDING DISPATCH    : %5d", lv_3EC.unk_04);
        sub_16BB00(lv_164, 50, lv_10);
        lv_10 += 15;
        sprintf(lv_164, "PENDING PLAYBACK    : %5d", lv_3EC.unk_48);
        sub_16BB00(lv_164, 50, lv_10);
        lv_10 += 15;
        sprintf(lv_164, "DECODE DEST OFFSET  : %5d", lv_3EC.unk_D4);
        sub_16BB00(lv_164, 50, lv_10);
        lv_10 += 15;
        sprintf(lv_164, "PLAYBACK OFFSET     : %5d", lv_3EC.unk_D8);
        sub_16BB00(lv_164, 50, lv_10);
        lv_10 += 15;
        sprintf(lv_164, "PLAYBACK BYTES REMNG: %5d", lv_3EC.unk_DC);
        sub_16BB00(lv_164, 50, lv_10);
        lv_10 += 15;
        sprintf(lv_164, "MISSING PACKETS: %5d", lv_2C4.unk_108);
        sub_16BB00(lv_164, 50, lv_10);
        lv_10 += 15;
        if (lv_3EC.unk_4C.unk_00 > 5000)
            sprintf(lv_164, "SINCE LAST DECODE   : >5000");
        else
            sprintf(lv_164, "SINCE LAST DECODE   : %5d", lv_3EC.unk_4C.unk_00);
        sub_16BB00(lv_164, 50, lv_10);
        lv_10 += 15;
        if (lv_3EC.unk_50.unk_00 > 5000)
            sprintf(lv_164, "SINCE LAST DISPATCH : >5000");
        else
            sprintf(lv_164, "SINCE LAST DISPATCH : %5d", lv_3EC.unk_50.unk_00);
        sub_16BB00(lv_164, 50, lv_10);
        lv_10 += 15;
        if (lv_2C4.unk_D8.unk_00 > 5000)
            sprintf(lv_164, "SINCE LAST NETWORK DISPATCH : >5000");
        else
            sprintf(lv_164, "SINCE LAST NETWORK DISPATCH : %5d", lv_2C4.unk_D8.unk_00);
        sub_16BB00(lv_164, 50, lv_10);
        lv_10 += 15;
        switch (lv_2C4.unk_40)
        {
        case 0:
            sprintf(lv_164, "PACKETS PENDING DISPATCH    : 0");
            break;
        case 1:
            sprintf(lv_164, "PACKETS PENDING DISPATCH    : 1 (%2d)", lv_2C4.unk_44[0]);
            break;
        case 2:
            sprintf(lv_164, "PACKETS PENDING DISPATCH    : 2 (%2d %2d)", lv_2C4.unk_44[0], lv_2C4.unk_44[1]);
            break;
        case 3:
            sprintf(lv_164, "PACKETS PENDING DISPATCH    : 3 (%2d %2d %2d)", lv_2C4.unk_44[0], lv_2C4.unk_44[1],
                    lv_2C4.unk_44[2]);
            break;
        case 4:
            sprintf(lv_164, "PACKETS PENDING DISPATCH    : 4 (%2d %2d %2d %2d)", lv_2C4.unk_44[0], lv_2C4.unk_44[1],
                    lv_2C4.unk_44[2], lv_2C4.unk_44[3]);
            break;
        case 5:
            sprintf(lv_164, "PACKETS PENDING DISPATCH    : 5 (%2d %2d %2d %2d %2d)", lv_2C4.unk_44[0],
                    lv_2C4.unk_44[1], lv_2C4.unk_44[2], lv_2C4.unk_44[3], lv_2C4.unk_44[4]);
            break;
        }
        sub_16BB00(lv_164, 50, lv_10);
        lv_10 += 15;
        sprintf(lv_164, "DISPATCHED:");
        lv_1A0 = lv_2C4.unk_105 + 1;
        lv_1A0 = lv_1A0 < 10 ? lv_1A0 : 0;
        for (lv_14 = 0; lv_14 < 10; lv_14++)
        {
            if (lv_2C4.unk_F0[lv_1A0] != 16 && lv_2C4.unk_FA[lv_1A0] != 16)
            {
                sprintf(lv_2E4, "(%d,%d)", lv_2C4.unk_F0[lv_1A0], lv_2C4.unk_FA[lv_1A0]);
                strcat(lv_164, lv_2E4);
            }
            lv_1A0++;
            lv_1A0 = lv_1A0 < 10 ? lv_1A0 : 0;
        }
        sub_16BB00(lv_164, 50, lv_10);
        lv_10 += 15;
        sprintf(lv_164, "RECEIVED:");
        lv_1A0 = lv_2C4.unk_104 + 1;
        lv_1A0 = lv_1A0 < 10 ? lv_1A0 : 0;
        for (lv_14 = 0; lv_14 < 10; lv_14++)
        {
            if (lv_2C4.unk_DC[lv_1A0] != 16 && lv_2C4.unk_E6[lv_1A0] != 16)
            {
                sprintf(lv_2E4, "(%d,%d)", lv_2C4.unk_DC[lv_1A0], lv_2C4.unk_E6[lv_1A0]);
                strcat(lv_164, lv_2E4);
            }
            lv_1A0++;
            lv_1A0 = lv_1A0 < 10 ? lv_1A0 : 0;
        }
        sub_16BB00(lv_164, 50, lv_10);
        lv_10 += 15;
        lv_10 += 15;
        sprintf(lv_164, "NUM  DECODE  L-TIME  PENDING  A-TIME");
        sub_16BB00(lv_164, 50, lv_10);
        lv_10 += 15;
        for (lv_14 = 0; lv_14 < 16; lv_14++)
        {
            if (lv_308.unk_00 & (1 << lv_14))
            {
                if (lv_3EC.unk_54[lv_14].get_unk_00() > 5000)
                    sprintf(lv_2E4, ">5000");
                else
                    sprintf(lv_2E4, "%d", lv_3EC.unk_54[lv_14].get_unk_00());
                if (lv_2C4.unk_58[lv_14])
                    sprintf(lv_304, "%d", lv_2C4.unk_98[lv_14].get_unk_00());
                else
                    sprintf(lv_304, "----");
                sprintf(lv_164, "%3d  %6d  %6s  %7d  %6s  %6s  %7s", lv_14, lv_3EC.unk_08[lv_14], lv_2E4,
                        lv_2C4.unk_00[lv_14], lv_304, (lv_3EC.unk_94[lv_14] & 1) ? "ACTIVE" : "",
                        (lv_3EC.unk_94[lv_14] & 2) ? "AUDIBLE" : "");
                sub_16BB00(lv_164, 50, lv_10);
                lv_10 += 15;
            }
        }
    }
    sub_16BBA0();
}
