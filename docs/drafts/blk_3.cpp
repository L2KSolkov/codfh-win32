// match: sub_1402B0 @ 0x001402B0
// Turns the line *arg_0 about the vertical through its start by arg_4
// degrees.
void sub_1402B0(RwLine *arg_0, RwReal arg_4)
{
    RwV3d var_C;
    RwV3d var_18;
    RwMatrix var_60;

    var_C.x = 0.0f;
    var_C.y = 0.0f;
    var_C.z = 1.0f;
    var_18.x = arg_0->end.x - arg_0->start.x;
    var_18.y = arg_0->end.y - arg_0->start.y;
    var_18.z = arg_0->end.z - arg_0->start.z;
    RwMatrixSetIdentityMacro(&var_60);
    RwMatrixRotate(&var_60, &var_C, arg_4, rwCOMBINEPRECONCAT);
    sub_1414C0(&var_18, &var_18, &var_60);
    arg_0->end.x = var_18.x + arg_0->start.x;
    arg_0->end.y = var_18.y + arg_0->start.y;
    arg_0->end.z = var_18.z + arg_0->start.z;
}

