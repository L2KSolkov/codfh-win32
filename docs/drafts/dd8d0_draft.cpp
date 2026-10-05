// The sessions' rows refilled from the network game's results, keeping
// the session selected (found again by its address, port and name) and the
// scroll above it.
// match: ?sub_20D8D0@type_20C470@@QAEXXZ @ 0x0020D8D0
// match: __ehhandler$?sub_20D8D0@type_20C470@@QAEXXZ-0x1E @ 0x00306750
// match: __ehhandler$?sub_20D8D0@type_20C470@@QAEXXZ @ 0x0030676E
void type_20C470::sub_20D8D0()
{
    RwUInt32 lv_10;
    type_1A5EA0 lv_30;
    RwUInt8 lv_34[4];
    type_1FB520 *lv_38;
    type_1FB520_session *lv_3C;
    RwInt32 lv_40;
    RwInt32 lv_44;
    RwUInt32 lv_48;
    RwUInt16 lv_4C;
    RwInt32 lv_50;
    type_1FB520_session *lv_54;
    type_1FB520_session *lv_58;

    lv_4C = 0;
    lv_40 = 0;
    if (sub_1ECB40())
    {
        lv_38 = (type_1FB520 *)sub_20E520();
        if (lv_38)
        {
            lv_58 = lv_38->sub_21D030();
            if (lv_58)
            {
                memcpy(lv_34, lv_58->unk_04, 4);
                lv_4C = lv_58->unk_08;
                lv_30 = lv_38->sub_1FB760();
                lv_40 = sub_1E3480()->sub_1EB1F0() - sub_1E3480()->sub_1EB280();
                lv_40 = lv_40 < 0 ? 0 : lv_40;
            }
        }
    }
    // The results and their count (the Xbox Live override takes the count's
    // address and returns the array; the slot is declared over integers).
    lv_54 = (type_1FB520_session *)unk_4F7EB8.get_unk_19C_direct()->vf_078((RwInt32)&lv_48);
    if (lv_48 > 0)
    {
        sub_1E3480()->sub_1EB160();
        sub_20CA70();
        sub_1E41C0();
        for (lv_10 = 0; lv_10 < lv_48; lv_10++)
        {
            type_1FB520_session *lv_5C = lv_54;

            lv_3C = &lv_5C[lv_10];
            if (lv_3C && lv_3C->unk_34)
            {
                type_1FB520 *lv_60 = new type_1FB520(lv_3C);

                unk_8758.push_back(lv_60);
                sub_20E540(lv_60);
            }
        }
    }
    lv_44 = -1;
    if (!lv_30.empty())
        lv_44 = sub_20DC80(lv_30, lv_34, lv_4C);
    lv_50 = lv_44 - lv_40;
    lv_50 = lv_50 < 0 ? 0 : lv_50;
    if (lv_44 != -1)
    {
        sub_1E3480()->sub_1EB210(lv_50);
        sub_1E3480()->sub_1EB0B0(lv_44);
    }
}

