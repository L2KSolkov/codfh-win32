#pragma warning(push)
#pragma warning(disable : 4716)
// match: sub_13FFA0 @ 0x0013FFA0
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
RwV3d *sub_13FFA0(RwV3d *arg_0, RwV3d *arg_4, RwReal arg_8)
{
    RwV3d var_C;
    RwReal local_10;
    RwReal stk_14;
    RwV3d local_20;
    RwReal l24;

    local_10 = cos(arg_8);
    l24 = sin(arg_8);
    RwV3dScaleMacro(&var_C, arg_0, local_10);
    stk_14 = (1.0f - local_10) * RwV3dDotProductMacro(arg_4, arg_0);
    RwV3dScaleMacro(&local_20, arg_4, stk_14);
    RwV3dAddMacro(&var_C, &var_C, &local_20);
    RwV3dCrossProductMacro(&local_20, arg_4, arg_0);
    RwV3dScaleMacro(&local_20, &local_20, l24);
    RwV3dAddMacro(&var_C, &var_C, &local_20);
    *arg_0 = var_C;
    // No return statement: eax still holds arg_0 from the copy (C4716).
}
#pragma warning(pop)

