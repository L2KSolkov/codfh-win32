// match: sub_140130 @ 0x00140130
// The point *arg_4 through the 4x4 matrix arg_8, divided by its w, into
// *arg_0.
void sub_140130(RwV3d *arg_0, RwV3d *arg_4, type_8BFA0 *arg_8)
{
    type_140490 var_10;

    var_10.unk_00 = arg_4->x;
    var_10.unk_04 = arg_4->y;
    var_10.unk_08 = arg_4->z;
    var_10.unk_0C = 1.0f;
    sub_1401B0(&var_10, &var_10, arg_8);
    arg_0->x = var_10.unk_00 / var_10.unk_0C;
    arg_0->y = var_10.unk_04 / var_10.unk_0C;
    arg_0->z = var_10.unk_08 / var_10.unk_0C;
}

