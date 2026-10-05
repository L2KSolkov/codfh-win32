// match: sub_26000 @ 0x00026000
RwInt32 AIData::sub_26000(type_F8350 *arg_0, RwMatrix *arg_4, RwV3d *arg_8, RwInt32 arg_C,
                          RwReal arg_10, RwInt32 arg_14, RwInt32 *arg_18)
{
    RwReal var_4;
    RwReal var_8;
    RwV3d var_14;
    RwReal var_18;
    RwReal var_1C;
    RwReal var_20;
    RwV3d var_2C;
    RwReal var_30;
    type_3D3548 *var_34;
    RwV3d var_40;
    type_3D3548 *var_44;
    RwV3d var_50;
    RwV3d var_5C;
    RwV3d var_68;
    RwV3d var_74;
    RwV3d var_80;
    RwReal var_84;

    if (arg_18 != 0)
        *arg_18 = 0;
    if (sub_23A10(arg_0) == 0 && arg_0->unk_04 != 0x0E)
        return 0;
    var_34 = unk_1374.sub_D4910();
    if (var_34 != 0 && sub_238E0(var_34) == 0 && sub_23930() == 0) {
        if (sub_26A80(arg_0, var_34, 0, 0) == 0)
            return 0;
    } else {
        var_44 = sub_1745A0(0);
        if (var_44 != 0 && ((var_44->unk_2C & 7) & (unk_568->unk_2C & 7)) != 0
                && (sub_238E0(0) == 0 || unk_F60 != arg_0)) {
            RwV3dSub(&var_50, var_44->sub_CD550(), &arg_0->unk_10);
            var_50.y -= var_44->unk_48;
            if (var_50.y <= flt_4275E4 && -flt_4275E8 <= var_50.y) {
                var_50.y = 0.0f;
                if (RwV3dDotProduct(&var_50, &var_50) < flt_4275E8) {
                    if (arg_18 != 0)
                        *arg_18 = 1;
                    return 0;
                }
            }
        }
    }
    var_30 = arg_10 / 10.0f;
    if (var_30 < 250.0f)
        var_30 = 250.0f;
    var_1C = var_30 + arg_8->y;
    var_18 = arg_8->y - var_30;
    if (arg_0->unk_10.y < var_18 || arg_0->unk_10.y > var_1C)
        return 0;
    RwV3dSub(&var_40, arg_8, &arg_0->unk_10);
    var_4 = RwV3dDotProduct(&var_40, &var_40);
    if (arg_10 * arg_10 < var_4)
        return 0;
    RwV3dSub(&var_2C, &arg_0->unk_10, &arg_4->pos);
    var_2C.y = 0.0f;
    RwV3dNormalize(&var_2C, &var_2C);
    var_84 = 2.0f / (arg_0->unk_1C.real * arg_0->unk_1C.real
            + RwV3dDotProduct(&arg_0->unk_1C.imag, &arg_0->unk_1C.imag));
    RwV3dScale(&var_80, &arg_0->unk_1C.imag, var_84);
    var_68.x = var_80.x * arg_0->unk_1C.real;
    var_68.y = var_80.y * arg_0->unk_1C.real;
    var_5C.x = var_80.x * arg_0->unk_1C.imag.x;
    var_5C.y = var_80.y * arg_0->unk_1C.imag.y;
    var_74.x = var_80.z * arg_0->unk_1C.imag.y;
    var_14.x = (var_74.y = var_80.x * arg_0->unk_1C.imag.z) + var_68.y;
    var_14.y = var_74.x - var_68.x;
    var_14.z = 1.0f - (var_5C.x + var_5C.y);
    var_8 = RwV3dDotProduct(&arg_4->at, &var_2C);
    if (arg_14 == 0 || arg_14 == 1 || arg_14 == 2) {
        if (var_8 >= flt_3CDE1C && arg_14 != 2)
            return sub_25EB0(arg_0, arg_4, &var_14, &var_2C);
        if ((arg_14 == 1 || arg_14 == 2) && var_8 <= flt_3CDE1C)
            return sub_25EB0(arg_0, arg_4, &var_14, &var_2C);
    } else if (arg_14 == 3) {
        if (var_8 >= flt_3CDE18) {
            var_20 = RwV3dDotProduct(&arg_4->at, &var_14);
            if (var_20 > 0.0f)
                return 1;
            if (arg_0->get_unk_04() == 0x0E && var_20 < flt_3CDE20 && -flt_3CDE20 < var_20)
                return 1;
        } else if (var_8 < flt_3CDE18 && -flt_3CDE18 < var_8) {
            RwReal var_8C = RwV3dDotProduct(&arg_4->right, &var_2C);

            if (var_8C >= flt_3CDE24) {
                var_20 = RwV3dDotProduct(&arg_4->right, &var_14);
                if (var_20 > 0.0f)
                    return 1;
            } else if (-flt_3CDE24 >= var_8C) {
                var_20 = RwV3dDotProduct(&arg_4->right, &var_14);
                if (var_20 < 0.0f)
                    return 1;
            }
        } else if (-flt_3CDE18 >= var_8) {
            var_20 = RwV3dDotProduct(&arg_4->at, &var_14);
            if (var_20 < 0.0f)
                return 1;
            if (arg_0->get_unk_04() == 0x0E && var_20 < flt_3CDE20 && -flt_3CDE20 < var_20)
                return 1;
        }
    } else if (arg_14 == 4) {
        if (flt_3CDE28 * flt_3CDE28 > var_4)
            return 0;
        return 1;
    }
    return 0;
}

