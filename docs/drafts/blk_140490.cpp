
// match: sub_140490 @ 0x00140490
// The weights of the point arg_0 against the triangle arg_4, arg_8, arg_C
// (the areas of the triangles it makes with each edge, projected on the
// triangle's normal) into *arg_10; negative weights are clamped to 0 and
// the rest renormalised. False unless they sum to 1 within 0.001 (the
// point lies outside).
bool sub_140490(type_140490 *arg_0, type_140490 *arg_4, type_140490 *arg_8, type_140490 *arg_C,
                type_140490 *arg_10)
{
    bool var_1;
    bool var_2;
    type_140490 var_20;
    type_140490 var_30;
    type_140490 var_40;
    type_140490 var_50;
    type_140490 var_60;
    type_140490 var_70;
    type_140490 var_80;
    type_140490 var_90;
    type_140490 var_A0;
    RwReal var_A4;
    type_140490 var_C0;
    RwReal var_C4;
    RwReal var_C8;

    var_1 = true;
    var_2 = false;
    RwV3dSubMacro(&var_20, arg_4, arg_0);
    RwV3dSubMacro(&var_30, arg_8, arg_0);
    RwV3dSubMacro(&var_40, arg_0, arg_C);
    RwV3dSubMacro(&var_50, arg_4, arg_C);
    RwV3dSubMacro(&var_60, arg_8, arg_C);
    RwV3dCrossProductMacro(&var_70, &var_20, &var_30);
    RwV3dCrossProductMacro(&var_80, &var_50, &var_60);
    RwV3dCrossProductMacro(&var_90, &var_60, &var_40);
    RwV3dCrossProductMacro(&var_A0, &var_40, &var_50);
    var_A4 = var_70.x + var_70.y + var_70.z;
    if (var_A4 != 0.0f)
    {
        RwV3dNormalize((RwV3d *)&var_C0, (RwV3d *)&var_70);
    }
    else
    {
        var_C0.x = 0.0f;
        var_C0.y = 0.0f;
        var_C0.z = 0.0f;
    }
    var_A4 = RwV3dDotProductMacro(&var_70, &var_C0);
    if (var_A4 != 0.0f)
        var_C4 = 1.0f / var_A4;
    else
        var_C4 = 0.0f;
    arg_10->x = RwV3dDotProductMacro(&var_80, &var_C0) * var_C4;
    if (arg_10->x < 0.0f)
    {
        arg_10->x = 0.0f;
        var_2 = true;
    }
    arg_10->y = RwV3dDotProductMacro(&var_90, &var_C0) * var_C4;
    if (arg_10->y < 0.0f)
    {
        arg_10->y = 0.0f;
        var_2 = true;
    }
    arg_10->z = RwV3dDotProductMacro(&var_A0, &var_C0) * var_C4;
    if (arg_10->z < 0.0f)
    {
        arg_10->z = 0.0f;
        var_2 = true;
    }
    if (var_2)
    {
        var_A4 = arg_10->x + arg_10->y + arg_10->z;
        if (var_A4 != 0.0f)
            var_C8 = 1.0f / var_A4;
        else
            var_C8 = 0.0f;
        arg_10->x = var_C8 * arg_10->x;
        arg_10->y = var_C8 * arg_10->y;
        arg_10->z = var_C8 * arg_10->z;
    }
    if (fabs(arg_10->x + arg_10->y + arg_10->z - 1.0f) > 0.001f)
        var_1 = false;
    return var_1;
}
