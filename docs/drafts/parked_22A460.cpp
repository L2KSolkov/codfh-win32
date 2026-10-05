// match: ?sub_22A460@type_229A90@@QAEXPAUD3DTexture@@MMMM@Z @ 0x0022A460
void type_229A90::sub_22A460(IDirect3DTexture8 *arg_0, RwReal arg_4, RwReal arg_8, RwReal arg_C, RwReal arg_10)
{
    type_1EEAD0 bp_D4;
    RwRaster *var_FC = sub_1EF040();
    RwReal local_F0 = arg_0 && arg_0->Size ? arg_C : 1.0f;
    RwReal var_F4 = arg_0 && arg_0->Size ? arg_10 : 1.0f;
    type_1E0330_rect var_20;
    type_1E0330_rect qE8;
    RwRaster *var_F8;

    var_20.unk_00 = arg_4;
    var_20.unk_04 = arg_8;
    var_20.unk_08 = arg_4 + arg_C;
    var_20.unk_0C = arg_8 + arg_10;
    qE8.unk_00 = 0;
    qE8.unk_04 = 0;
    qE8.unk_08 = local_F0;
    qE8.unk_0C = var_F4;
    RwRenderStateGet(rwRENDERSTATETEXTURERASTER, &var_F8);
    IDirect3DTexture8 **var_EC = (IDirect3DTexture8 **)RASTEREXTFROMRASTER(var_FC);
    IDirect3DTexture8 *m_D8 = *var_EC;

    *var_EC = arg_0;
    RwRenderStateSet(rwRENDERSTATETEXTURERASTER, var_FC);
    RwUInt32 lv_10 = arg_0 ? 0xFFFFFFFF : 0x80808080;

    bp_D4.sub_1EEC20(&var_20, 1.0f, 1.0f, &qE8, lv_10);
    bp_D4.sub_1EEB60();
    *var_EC = m_D8;
    RwRenderStateSet(rwRENDERSTATETEXTURERASTER, var_F8);
}

