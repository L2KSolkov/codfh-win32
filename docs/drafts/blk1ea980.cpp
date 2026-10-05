// match: ?sub_1EA980@type_3E7490@kujuUI@@QAEXPAUtype_3E74C0@2@H@Z @ 0x001EA980
void type_3E7490::sub_1EA980(type_3E74C0 *arg_0, RwInt32 arg_4)
{
    std::vector<type_3E74C0 *>::iterator var_4 = arg_4 == 0 ? unk_0C.begin() : row_at(&unk_0C, arg_4);
    unk_0C.insert(var_4, arg_0);
    arg_0->sub_1EBFA0(this);
    if (sub_1EA410() && arg_4 <= unk_FC)
        ++unk_FC;
    unk_115 = true;
}

