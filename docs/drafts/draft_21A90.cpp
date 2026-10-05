// Draft: matches up to the function-scope local layout (var_4 lands at -0x10,
// needs -4). Block scopes put var_2C, var_30/var_3C and var_40 in the right slots.
// match: sub_21A90 @ 0x00021A90
RwInt32 AIData::sub_21A90(RwV3d *arg_0, RwV3d *arg_4)
{
    RwFrame *var_4;
    RwMatrix *var_8;
    RwInt32 var_C;
    RwReal var_10;
    RwV3d var_1C;
    RwReal var_20;

    var_4 = unk_568->get_unk_340();
    var_8 = RwFrameGetLTM(var_4);
    var_10 = RwV3dLength(arg_0);
    sub_1414C0(arg_4, arg_0, var_8);
    var_1C = *unk_568->sub_CD550();
    var_1C.y += unk_568->unk_48;
    var_20 = 0.0f;
    if ((var_C = !unk_568->sub_D2FC0(&var_1C, arg_4, 0, &var_20, 1, 0, 1, 1, 0x20000, 0, 0)) == 0 // not an address: a flag
            && var_20 * var_10 > flt_4275D4) {
        RwV3d var_2C;

        var_C = 1;
        RwV3dSub(&var_2C, arg_4, &var_1C);
        RwV3dScale(&var_2C, &var_2C, var_20);
        RwV3dAdd(arg_4, &var_2C, &var_1C);
    }
    if (var_C != 0) {
        RwReal var_30;
        RwV3d var_3C;

        var_3C = *arg_4;
        var_3C.y -= flt_4275D0 + unk_568->unk_48;
        var_30 = 0.0f;
        var_C = unk_568->sub_D2FC0(arg_4, &var_3C, 0, &var_30, 1, 0, 0, 1, 0x20000, 0, 0); // not an address: a flag
        if (var_C != 0) {
            RwReal var_40;

            var_40 = (flt_4275D0 + unk_568->unk_48) * var_30;
            arg_4->y -= var_40 - unk_568->unk_48;
        }
    }
    return var_C;
}
