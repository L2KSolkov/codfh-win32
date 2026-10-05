// match: ?sub_1EAA50@type_3E7490@kujuUI@@QAEXH@Z @ 0x001EAA50
void type_3E7490::sub_1EAA50(RwInt32 arg_0)
{
    std::vector<type_3E74C0 *>::iterator var_4 = row_at(&unk_0C, arg_0);
    (*var_4)->sub_1EC110();
    unk_0C.erase(var_4);
    if (unk_FC > arg_0)
        --unk_FC;
    if (arg_0 < unk_F8)
        --unk_F8;
    unk_115 = true;
}

