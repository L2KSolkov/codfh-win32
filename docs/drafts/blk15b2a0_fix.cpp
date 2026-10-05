// match: ?sub_15B2A0@type_15B110@@QAEXPAUtype_3DF8D8@@PAX@Z @ 0x0015B2A0
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
// The guns from the vehicle's model object arg_0 (a copy of each gun's
// projectile model, its particles, speed, magazine and flash time) and its
// trigger arg_4 (their damage and rate of fire; without one, a shot every
// six frames).
void type_15B110::sub_15B2A0(type_3DF8D8 *arg_0, void *arg_4)
{
    RwInt32 var_C;
    RpClump *bp_8;
    RpClump *bp_4;

    bp_4 = 0;
    bp_8 = 0;
    for (var_C = 0; var_C < 4; var_C++)
    {
        bp_8 = arg_0->sub_18F830(get_gun_model((type_14D2C0_10 *)arg_0->unk_10, var_C));
        if (!bp_8)
        {
            unk_00[var_C].unk_00.sub_129620(0);
        }
        else
        {
            bp_4 = RpClumpClone(bp_8);
            if (!bp_4)
                return;
            unk_00[var_C].unk_00.sub_129620(bp_4);
        }
        unk_00[var_C].unk_10 = ((type_14D2C0_10 *)arg_0->unk_10)->get_unk_4C(var_C, 0);
        unk_00[var_C].unk_14 = ((type_14D2C0_10 *)arg_0->unk_10)->get_unk_4C(var_C, 1);
        unk_00[var_C].unk_0C = ((type_14D2C0_10 *)arg_0->unk_10)->get_unk_3C(var_C);
        unk_00[var_C].unk_18 = 0;
        unk_00[var_C].unk_1C = ((type_14D2C0_10 *)arg_0->unk_10)->get_unk_6C(var_C) * 60.0f;
        unk_00[var_C].unk_20 = 0;
        unk_00[var_C].unk_34 = ((type_14D2C0_10 *)arg_0->unk_10)->get_unk_7C(var_C);
        if (arg_4)
        {
            unk_00[var_C].unk_24 = ((type_712B0_3DBC78 *)arg_4)->unk_15C[var_C];
            unk_00[var_C].unk_28 = ((type_712B0_3DBC78 *)arg_4)->unk_16C[var_C];
            unk_00[var_C].unk_30 = 1.0f / ((type_712B0_3DBC78 *)arg_4)->unk_17C[var_C] * 60.0f;
            unk_00[var_C].unk_2C = 0.0f;
        }
        else
        {
            unk_00[var_C].unk_24 = 0;
            unk_00[var_C].unk_28 = 0;
            unk_00[var_C].unk_30 = 6.0f;
            unk_00[var_C].unk_2C = 0.0f;
        }
    }
}
