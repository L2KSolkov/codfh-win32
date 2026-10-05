
// match: ?vf_0D8@type_3DBC78@@UAEXPAURwV3d@@@Z @ 0x00151CF0
// Turns it to face along arg_0 (unless that is about zero).
void type_3DBC78::vf_0D8(RwV3d *arg_0)
{
    RwFrame *var_C;
    RwReal var_10;
    RwV3d var_20;
    RwMatrix var_60;

    var_C = get_unk_340();
    if ((RwReal)fabs((RwDouble)(var_10 = (arg_0->z * arg_0->z) + ((arg_0->y * arg_0->y) + (arg_0->x * arg_0->x))))
        > 0.0001f)
    {
        RwV3dNormalize(&var_20, arg_0);
        sub_140CE0(&var_60, &unk_450.unk_170.pos, &var_20);
        RwMatrixTransform(&unk_450.unk_170, &var_60, rwCOMBINEREPLACE);
        RwFrameUpdateObjects(var_C);
    }
}
