
// Peer arg_8's unordered message number arg_0 (arg_4 the one before it) of
// arg_10 bits in the stream arg_C: handed on (sub_1CC780) unless already
// seen; one arriving before its predecessor is noted (once) so the numbers
// it covers are skipped later (its trace: "receive unordered").
// match: ?sub_1D3C80@type_1D0100@@QAEXIIHPAUtype_1F8560@@H@Z @ 0x001D3C80
void type_1D0100::sub_1D3C80(RwUInt32 arg_0, RwUInt32 arg_4, RwInt32 arg_8, type_1F8560 *arg_C, RwInt32 arg_10)
{
    type_1D3C80 *var_4;
    RwInt32 var_8 = 0;
    RwInt32 var_C;

    if (unk_124[arg_8] == -1)
        unk_124[arg_8] = arg_4;
    if (arg_0 <= (RwUInt32)unk_124[arg_8])
        var_8 = 1;
    else if (arg_4 != (RwUInt32)unk_124[arg_8])
    {
        RwInt32 var_18 = unk_E4[arg_8]->count();

        var_4 = unk_E4[arg_8]->first();
        while (var_18--)
        {
            if (var_4->unk_04 == arg_0)
            {
                var_8 = 1;
                break;
            }
            var_4 = unk_E4[arg_8]->next();
        }
        if (!var_8)
        {
            type_1D3C80 var_14;

            var_14.unk_04 = arg_0;
            var_14.unk_00 = arg_4;
            RwInt32 var_1C = unk_E4[arg_8]->add(var_14);

            if (!var_1C)
            {
                if (0)
                    off_42CD14("Just ran out of ram in receive unordered - guaranteed packed que!");
                unk_794 = 1;
                return;
            }
        }
    }
    else
    {
        unk_124[arg_8] = arg_0;
        while (1)
        {
            RwInt32 var_20;

            var_C = unk_E4[arg_8]->count();
            if (!var_C)
                break;
            var_4 = unk_E4[arg_8]->first();
            var_20 = 0;
            while (var_C--)
            {
                if (var_4->unk_00 == arg_0)
                {
                    arg_0 = var_4->unk_04;
                    unk_E4[arg_8]->sub_1D4100();
                    unk_124[arg_8] = arg_0;
                    var_20 = 1;
                    break;
                }
                var_4 = unk_E4[arg_8]->next();
            }
            if (!var_20)
                break;
        }
    }
    if (!var_8)
        unk_79C->sub_1CC780(arg_0, arg_8, (RwInt32)arg_C, arg_10);
}
