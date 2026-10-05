// The rows' index for the session arg_0 (by name) at the address arg_1C and
// port arg_20: the row already listing it, else the first whose name does
// not sort before it.
// match: ?sub_20DC80@type_20C470@@QAEHUtype_1A5EA0@@PBEG@Z @ 0x0020DC80
// match: __ehhandler$?sub_20DC80@type_20C470@@QAEHUtype_1A5EA0@@PBEG@Z-0x10 @ 0x00306780
// match: __ehhandler$?sub_20DC80@type_20C470@@QAEHUtype_1A5EA0@@PBEG@Z @ 0x00306790
RwInt32 type_20C470::sub_20DC80(type_1A5EA0 arg_0, const RwUInt8 *arg_1C, RwUInt16 arg_20)
{
    RwInt32 lv_1C = 0;
    bool lv_D = false;
    RwUInt32 lv_14 = unk_8758.size();

    for (RwUInt32 lv_18 = 0; lv_18 < lv_14; lv_18++)
    {
        type_1FB520 *lv_20 = sub_21DF90(lv_18);
        type_1FB520_session *lv_24 = lv_20->sub_21D030();

        if (lv_24 && lv_24->unk_04[0] == arg_1C[0] && lv_24->unk_04[1] == arg_1C[1] && lv_24->unk_04[2] == arg_1C[2]
            && lv_24->unk_04[3] == arg_1C[3] && lv_24->unk_08 == arg_20)
        {
            lv_D = true;
            break;
        }
        lv_1C++;
    }
    if (!lv_D)
    {
        lv_1C = 0;
        for (std::list<type_1FB520 *>::iterator lv_28 = unk_8758.begin(); lv_28 != unk_8758.end(); ++lv_28)
        {
            type_1FB520 *lv_2C = *lv_28;
            bool lv_31 = !(lv_2C->sub_1FB760().compare(arg_0) < 0);

            if (lv_31)
                break;
            lv_1C++;
        }
    }
    return lv_1C;
}

