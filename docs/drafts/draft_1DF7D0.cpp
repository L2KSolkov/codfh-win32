// match: ?sub_1DF7D0@type_3E3870@@QAEXABUtype_1CCA10@@@Z @ 0x001DF7D0
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void type_3E3870::sub_1DF7D0(const type_1CCA10 &arg_0)
{
    type_1CCA10 var_10;
    RwInt32 var_8 = 4;
    type_1DDE20_mask var_14;
    type_3E3870_out *var_C;
    type_3E3870_out *var_4;

    if (unk_21A4)
    {
        var_4 = unk_21A4;
        while (var_4)
        {
            var_C = var_4->unk_158;
            var_10 = arg_0 - var_4->unk_150;
            if (var_10 > 1000)
                sub_1DF0E0(var_4);
            var_4 = var_C;
        }
    }
    var_10 = arg_0 - unk_21EC;
    if (var_10 > 100)
    {
        sub_1DF740(arg_0, &var_14, &var_8);
        if (unk_21EC == type_1CCA10(0))
            unk_21EC = arg_0;
        else if (var_8 == 4)
            unk_21EC = arg_0 - 100;
        else
            unk_21EC = unk_21EC + 100;
    }
}
