// match: ?sub_15B5D0@type_4D51C0@@QAEXXZ @ 0x0015B5D0
// Does nothing: its body is under `if (0)` (a plain jump over it); it which builds dword_4D5170 (an
// identity matrix, the square of four corners 50 apart, sub_15B730) and
// runs its sub_15BC10.
void type_4D51C0::sub_15B5D0()
{
    RwV3d var_30[4];
    RwReal var_34;

    if (0)
    {
        RwMatrixSetIdentityMacro(&dword_4D5170.unk_00);
        dword_4D5170.unk_00.pos.x = 0.0f;
        dword_4D5170.unk_00.pos.y = 0.0f;
        dword_4D5170.unk_00.pos.z = 0.0f;
        var_34 = 50.0f;
        var_30[0].x = -var_34;
        var_30[0].y = var_34;
        var_30[0].z = 0.0f;
        var_30[1].x = var_34;
        var_30[1].y = var_34;
        var_30[1].z = 0.0f;
        var_30[2].x = var_34;
        var_30[2].y = -var_34;
        var_30[2].z = 0.0f;
        var_30[3].x = -var_34;
        var_30[3].y = -var_34;
        var_30[3].z = 0.0f;
        dword_4D5170.unk_40 = sub_15B730(var_30);
        dword_4D5170.unk_44 = 0;
        dword_4D5170.sub_15BC10();
    }
}

