// match: ?sub_1C16B0@type_1C0F60@@QAEHIPAUtype_4FBC50_player@@H@Z @ 0x001C16B0
// The point (not arg_8) farthest from the nearest of the arg_0 players
// arg_4; the first one when there is none.
RwInt32 type_1C0F60::sub_1C16B0(RwUInt32 arg_0, type_4FBC50_player *arg_4, RwInt32 arg_8)
{
    RwUInt32 lv_30;
    RwUInt32 fp_2C;
    RwInt32 q28 = -1;
    RwReal frm_24;
    RwReal var_20 = 0;
    RwReal l1C;
    type_1F8560_v var_C;
    type_1F8560_v m_18;

    for (fp_2C = 0; fp_2C < (RwUInt32)unk_08; fp_2C++)
    {
        if (arg_8 != fp_2C)
        {
            frm_24 = 1e10f;
            for (lv_30 = 0; lv_30 < arg_0; lv_30++)
            {
                unk_0C[fp_2C]->sub_1C0F20(&m_18);
                var_C = arg_4[lv_30].unk_00 - m_18;
                l1C = var_C.sub_1BF590();
                if (l1C < frm_24)
                    frm_24 = l1C;
            }
            if (frm_24 > var_20)
            {
                var_20 = frm_24;
                q28 = fp_2C;
            }
        }
    }
    if (q28 == -1)
    {
        q28 = 0;
        if (0)
        {
            sub_1C8A30("Failed to find valid spawn point!\n");
        }
    }
    return q28;
}
