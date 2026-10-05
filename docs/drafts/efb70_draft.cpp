
// Draws a mesh particle system (type_F2FF0::sub_F43B0 with flag 0x10): its
// mesh lit as a clone, then once per particle at its matrices.
// match: ?sub_EFB70@@YAXPAUtype_F2FF0@@@Z @ 0x000EFB70
void sub_EFB70(type_F2FF0 *arg_0)
{
    if (arg_0->unk_60.unk_20)
    {
        sub_123AF0(arg_0->unk_60.unk_20, 1, 0, 0, 0, 0);
        sub_123FE0((type_1243F0 *)arg_0->unk_60.unk_00, arg_0->unk_60.unk_1C, 0);
        sub_124D70();
    }
}
