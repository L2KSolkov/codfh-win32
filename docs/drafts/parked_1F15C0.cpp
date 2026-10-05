// match: ?sub_1F15C0@type_1F1420@kujuUI@@QAEXXZ @ 0x001F15C0
void type_1F1420::sub_1F15C0()
{
    if (!unk_54.empty())
    {
        type_E8780<type_1E5A60> var_18(unk_70->sub_1E6610(unk_8C));
        RwUInt32 var_10 = unk_70->unk_18[unk_8C];
        RwUInt32 var_14;
        if (unk_8C == 1)
        {
            RwUInt32 var_20 = var_10 >> 24 & 0xFF;
            RwUInt32 var_38 = var_10 >> 16 & 0xFF;
            RwUInt32 var_34 = var_10 >> 8 & 0xFF;
            RwUInt32 var_30 = var_10 & 0xFF;
            RwUInt32 var_2C = unk_70->unk_18[0];
            RwUInt32 var_3C = var_2C >> 24 & 0xFF;
            RwUInt32 var_28 = var_2C >> 16 & 0xFF;
            RwUInt32 var_24 = var_2C >> 8 & 0xFF;
            RwUInt32 var_1C = var_2C & 0xFF;
            RwReal var_64;
            RwReal var_40 = (RwReal)cos(var_64 = (RwReal)(unk_88 * 2) * 3.14159f / 50.0f) * 0.5f + 0.5f;
            var_38 = (RwUInt32)((RwReal)var_38 * var_40 + (RwReal)var_28 * (1.0f - var_40));
            var_34 = (RwUInt32)((RwReal)var_34 * var_40 + (RwReal)var_24 * (1.0f - var_40));
            var_30 = (RwUInt32)((RwReal)var_30 * var_40 + (RwReal)var_1C * (1.0f - var_40));
            var_20 = (RwUInt32)((RwReal)var_20 * var_40 + (RwReal)var_3C * (1.0f - var_40));
            var_10 = var_20 << 24 | var_38 << 16 | var_34 << 8 | var_30;
        }
        if (unk_99)
        {
            const type_1E0330_rect *var_68 = pvf_004();
            var_18->sub_1E6690(unk_54.c_str(), var_10, (RwUInt32)(var_68->unk_08 - var_68->unk_00), unk_90, unk_04,
                               (RwInt32 *)&var_14);
        }
        else
        {
            const type_1E0330_rect *var_70;
            var_18->sub_1E6690(sub_1F2110().c_str(), var_10, (RwUInt32)((var_70 = pvf_004())->unk_08 - var_70->unk_00),
                               unk_90, unk_04, (RwInt32 *)&var_14);
        }
        switch (unk_94)
        {
        case 0:
            unk_84 = 0;
            break;
        case 1:
            const type_1E0330_rect *var_88 = pvf_004();
            unk_84 = (RwInt32)((var_88->unk_0C - var_88->unk_04 - (RwReal)var_14) / 2.0f);
            break;
        }
    }
}

