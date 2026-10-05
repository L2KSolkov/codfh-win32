// match: sub_1401B0 @ 0x001401B0
// The vector *arg_4 through the 4x4 matrix arg_8 (rows times the vector's
// components), into *arg_0. Only the matrix's first row is copied into its
// local (0x10 bytes): the other rows are whatever the stack held.
void sub_1401B0(type_140490 *arg_0, type_140490 *arg_4, type_8BFA0 *arg_8)
{
    type_8BFA0 var_40;
    type_140490 var_50;

    memcpy(&var_40, arg_8, 0x10);
    var_50.unk_00 = var_40.unk_00[0].unk_00 * arg_4->unk_00 + var_40.unk_00[1].unk_00 * arg_4->unk_04
                    + var_40.unk_00[2].unk_00 * arg_4->unk_08 + var_40.unk_00[3].unk_00 * arg_4->unk_0C;
    var_50.unk_04 = var_40.unk_00[0].unk_04 * arg_4->unk_00 + var_40.unk_00[1].unk_04 * arg_4->unk_04
                    + var_40.unk_00[2].unk_04 * arg_4->unk_08 + var_40.unk_00[3].unk_04 * arg_4->unk_0C;
    var_50.unk_08 = var_40.unk_00[0].unk_08 * arg_4->unk_00 + var_40.unk_00[1].unk_08 * arg_4->unk_04
                    + var_40.unk_00[2].unk_08 * arg_4->unk_08 + var_40.unk_00[3].unk_08 * arg_4->unk_0C;
    var_50.unk_0C = var_40.unk_00[0].unk_0C * arg_4->unk_00 + var_40.unk_00[1].unk_0C * arg_4->unk_04
                    + var_40.unk_00[2].unk_0C * arg_4->unk_08 + var_40.unk_00[3].unk_0C * arg_4->unk_0C;
    *arg_0 = var_50;
}

