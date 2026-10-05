// match: ?sub_15F590@type_4E19F8@@QAEPAUtype_3DC7F8@@HPAUtype_3D3548@@PAURwMatrixTag@@PAURwV3d@@HPAUtype_439A48@@PAUtype_429E54@@@Z @ 0x0015F590
type_3DC7F8 *type_4E19F8::sub_15F590(RwInt32 arg_0, type_3D3548 *arg_4, RwMatrix *arg_8, RwV3d *arg_C,
                                     RwInt32 arg_10, type_439A48 *arg_14, type_429E54 *arg_18)
{
    type_3DC7F8 *var_10;
    RwReal var_14;
    type_3DC8B8 *var_18;
    RwReal var_1C;
    type_4E19F8 *var_20;
    type_3DC8B8 *var_24;
    type_3DC8B8 *var_28;

    var_10 = 0;
    switch (unk_00)
    {
    case 3:
        var_10 = new (unk_04.sub_16C5A0(0)) type_3DC798;
        break;
    case 4:
        var_10 = new (unk_04.sub_16C5A0(0)) type_3DC858;
        break;
    case 2:
    case 5:
        var_10 = new (unk_04.sub_16C5A0(0)) type_3DC8B8;
        break;
    case 6:
        var_10 = new (unk_04.sub_16C5A0(0)) type_3DC8B8;
        if (!unk_04.get_unk_18())
        {
            var_20 = projectile_pool(6);
            var_18 = (type_3DC8B8 *)var_20->unk_24;
            var_24 = 0;
            var_14 = 1.0e9f;
            while (var_18)
            {
                var_28 = (type_3DC8B8 *)var_18->unk_40;
                var_1C = var_18->vf_054();
                if (var_1C < var_14)
                {
                    var_14 = var_1C;
                    var_24 = var_18;
                }
                var_18 = var_28;
            }
            var_24->vf_060();
        }
        break;
    case 0:
        var_10 = new (unk_04.sub_16C5A0(0)) type_3DC7F8;
        break;
    case 1:
        var_10 = new (unk_04.sub_16C5A0(0)) type_3DC7F8;
        break;
    case 7:
        var_10 = new (unk_04.sub_16C5A0(0)) type_3DC738;
        break;
    case 8:
        var_10 = new (unk_04.sub_16C5A0(0)) type_3DC6D8;
        break;
    }
    if (var_10)
    {
        var_10->vf_000(arg_0, arg_4, arg_14, arg_18);
        var_10->vf_008(arg_8);
        var_10->vf_00C(arg_C);
        var_10->vf_010(arg_10);
        sub_15F4D0(var_10);
    }
    return var_10;
}

