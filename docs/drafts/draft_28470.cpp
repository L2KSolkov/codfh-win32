// match: sub_28470 @ 0x00028470
RwInt32 AIData::sub_28470(RwV3d *arg_0)
{
    RwInt32 var_4 = 32;
    type_154C0_1048 var_70;
    type_4C00E8 *var_C = &unk_4C00E8;
    type_F8350 *var_8;
    RwReal var_74;
    RwReal var_78;
    type_F8350 *var_7C;
    type_154C0_F80 var_180[32];
    RwInt32 var_184;
    RwReal var_188;

    var_70.unk_04 = *unk_568->sub_CD550();
    var_70.unk_10 = 1000.0f;
    var_70.unk_00 = unk_568;
    var_70.unk_18 = 0;
    var_70.unk_1C = 1;
    var_70.unk_20 = var_180;
    var_70.unk_24 = 32;
    sub_F8970(&var_70, 0, 0);
    var_78 = 490000.0f;
    var_74 = 1000000.0f;
    var_8 = 0;
    for (var_184 = 0; var_184 < var_70.unk_4C; var_184++) {
        if (var_180[var_184].unk_04 < var_74) {
            var_7C = var_C->unk_2C[var_180[var_184].unk_00];
            if (var_7C != 0) {
                var_188 = sub_140C90(&var_7C->unk_10, arg_0);
                if (var_188 > var_78 && sub_140C90(&var_7C->unk_10, unk_568->sub_CD550()) < var_188) {
                    var_74 = var_180[var_184].unk_04;
                    var_8 = var_7C;
                }
            }
        }
    }
    if (var_8 != 0) {
        unk_5B0 = var_8->unk_10;
        return 1;
    }
    return 0;
}

