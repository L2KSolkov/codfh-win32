// match: ?sub_1E7A80@type_1E76A0@kujuUI@@QAEXXZ @ 0x001E7A80
void type_1E76A0::sub_1E7A80()
{
    if (has_unk_04())
    {
        if (unk_08 == unk_0C && !unk_24.empty())
            sub_1E3480()->sub_1E2A50(unk_24);
        else
        {
            type_1CB670 var_3C(unk_40);
            RwChar var_20[16];
            _itoa(unk_08, var_20, 10);
            var_3C.sub_1C84F0(sub_1CB720(var_20));
            var_3C.sub_1C84F0(unk_5C);
            sub_1E3480()->sub_1E2A50(var_3C);
        }
    }
}
