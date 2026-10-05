// match: ?sub_1F15C0@type_1F1420@kujuUI@@QAEXXZ @ 0x001F15C0
// match: __ehhandler$?sub_1F15C0@type_1F1420@kujuUI@@QAEXXZ-0x18 @ 0x003043F0
// match: __ehhandler$?sub_1F15C0@type_1F1420@kujuUI@@QAEXXZ @ 0x00304408
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void type_1F1420::sub_1F15C0()
{
    if (!unk_54.empty())
    {
        type_E8780<type_1E5A60> m_18(unk_70->sub_1E6610(unk_8C));
        RwUInt32 ebp_14;
        RwUInt32 lv_10 = unk_70->unk_18[unk_8C];
        if (unk_8C == 1)
        {
            RwUInt32 t20 = lv_10 >> 24 & 0xFF;
            RwUInt32 lcl_38 = lv_10 >> 16 & 0xFF;
            RwUInt32 r34 = lv_10 >> 8 & 0xFF;
            RwUInt32 lv_30 = lv_10 & 0xFF;
            RwUInt32 fp_2C = unk_70->get_colour(0);
            RwUInt32 stk_3C = fp_2C >> 24 & 0xFF;
            RwUInt32 q28 = fp_2C >> 16 & 0xFF;
            RwUInt32 frm_24 = fp_2C >> 8 & 0xFF;
            RwUInt32 l1C = fp_2C & 0xFF;
            RwReal loc40 = (RwReal)cos((RwReal)((RwReal)(unk_88 * 2) * 3.14159f / 50.0f)) * 0.5f + 0.5f;
            lcl_38 = (RwUInt32)((RwReal)lcl_38 * loc40 + (RwReal)q28 * (1.0f - loc40));
            r34 = (RwUInt32)((RwReal)r34 * loc40 + (RwReal)frm_24 * (1.0f - loc40));
            lv_30 = (RwUInt32)((RwReal)lv_30 * loc40 + (RwReal)l1C * (1.0f - loc40));
            t20 = (RwUInt32)((RwReal)t20 * loc40 + (RwReal)stk_3C * (1.0f - loc40));
            lv_10 = t20 << 24 | lcl_38 << 16 | r34 << 8 | lv_30;
        }
        if (unk_99)
        {
            m_18->sub_1E6690(unk_54.c_str(), lv_10, (RwUInt32)pvf_004()->width(), unk_90, unk_04,
                               (RwInt32 *)&ebp_14);
        }
        else
        {
            m_18->sub_1E6690(sub_1F2110().c_str(), lv_10, (RwUInt32)pvf_004()->width(), unk_90, unk_04,
                               (RwInt32 *)&ebp_14);
        }
        switch (unk_94)
        {
        case 0:
            unk_84 = 0;
            break;
        case 1:
            unk_84 = (RwInt32)((pvf_004()->height() - (RwReal)ebp_14) / 2.0f);
            break;
        }
    }
}

