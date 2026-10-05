// match: ?sub_1C16B0@type_1C0F60@@QAEHIPAUtype_4FBC50_player@@H@Z @ 0x001C16B0
// The point (not arg_8) farthest from the nearest of the arg_0 players
// arg_4; the first one when there is none.
RwInt32 type_1C0F60::sub_1C16B0(RwUInt32 arg_0, type_4FBC50_player *arg_4, RwInt32 arg_8)
{
    RwInt32 lv_28 = -1;
    RwReal lv_20 = 0;
    type_1F8560_v lv_C;
    type_1F8560_v lv_18;
    RwUInt32 lv_2C;

    for (lv_2C = 0; lv_2C < (RwUInt32)unk_08; lv_2C++)
    {
        if (arg_8 != lv_2C)
        {
            RwReal lv_24 = 1e10f;
            RwUInt32 lv_30;

            for (lv_30 = 0; lv_30 < arg_0; lv_30++)
            {
                unk_0C[lv_2C]->sub_1C0F20(&lv_18);
                lv_C = arg_4[lv_30].unk_00 - lv_18;
                RwReal lv_1C = lv_C.sub_1BF590();

                if (lv_1C < lv_24)
                    lv_24 = lv_1C;
            }
            if (lv_24 > lv_20)
            {
                lv_20 = lv_24;
                lv_28 = lv_2C;
            }
        }
    }
    if (lv_28 == -1)
    {
        lv_28 = 0;
        if (0)
        {
            sub_1C8A30("Failed to find valid spawn point!\n");
        }
    }
    return lv_28;
}
