
// Peer arg_8's message number arg_0 (arg_4 its first) of arg_10 bits in the
// stream arg_C: handed on in order (odd numbers through sub_1CC780, even
// through sub_1CC820), then the kept ones that follow it; one arriving early
// is kept (once) until its turn.
// match: ?sub_1D3770@type_1D0100@@QAEXIIHPAUtype_1F8560@@H@Z @ 0x001D3770
void type_1D0100::sub_1D3770(RwUInt32 arg_0, RwUInt32 arg_4, RwInt32 arg_8, type_1F8560 *arg_C, RwInt32 arg_10)
{
    type_1D7CA0 *var_4;
    RwInt32 var_8;
    RwUInt8 var_418[0x400];
    type_1D7CA0 var_428;
    RwInt32 var_42C;
    RwInt32 var_430;
    type_1D7CA0 *var_434;
    RwInt32 var_438;

    if (unk_A4[arg_8] == -1)
        unk_A4[arg_8] = arg_4;
    if (arg_0 <= (RwUInt32)unk_A4[arg_8])
        return;
    if (arg_4 != (RwUInt32)unk_A4[arg_8])
    {
        var_42C = unk_64[arg_8]->count();
        var_4 = unk_64[arg_8]->first();
        while (var_42C--)
        {
            if (var_4->unk_04 == (RwInt32)arg_0)
                return;
            var_4 = unk_64[arg_8]->sub_1D0E70();
        }
        arg_C->sub_1F8A40((RwChar *)var_418, arg_10);
        var_428.unk_04 = arg_0;
        var_428.unk_00 = arg_4;
        var_428.unk_08 = 0;
        if (!var_428.sub_1D7C30(var_418, arg_10))
        {
            if (0)
                off_42CD14("Just ran out of ram in receive in order - guaranteed packed que!");
            unk_794 = 1;
            return;
        }
        void *p = unk_64[arg_8]->sub_1FA310(sizeof(type_1D7CA0));
        if (p)
        {
            new (p) type_1D7CA0(var_428);
            var_8 = 1;
        }
        else
            var_8 = 0;
        if (!var_8)
        {
            var_428.sub_1D7CA0();
            if (0)
                off_42CD14("Just ran out of ram in receive in order - guaranteed packed que!");
            unk_794 = 1;
            return;
        }
        return;
    }
    if (arg_0 & 1)
        unk_79C->sub_1CC780(arg_0, arg_8, (RwInt32)arg_C, arg_10);
    else
        unk_79C->sub_1CC820(arg_0, arg_8, arg_C, arg_10);
    unk_A4[arg_8] = arg_0;
    while (1)
    {
        var_438 = unk_64[arg_8]->count();
        if (!var_438)
            return;
        var_434 = unk_64[arg_8]->first();
        var_430 = 0;
        while (var_438--)
        {
            if (var_434->unk_00 == (RwInt32)arg_0)
            {
                type_1F8560 var_444(var_434->unk_08, var_434->unk_0C + 0x40);

                arg_0 = var_434->unk_04;
                unk_64[arg_8]->sub_1D4100();
                unk_A4[arg_8] = arg_0;
                if (arg_0 & 1)
                    unk_79C->sub_1CC780(arg_0, arg_8, (RwInt32)&var_444, var_434->unk_0C);
                else
                    unk_79C->sub_1CC820(arg_0, arg_8, &var_444, var_434->unk_0C);
                var_434->sub_1D7CA0();
                var_430 = 1;
                break;
            }
            var_434 = unk_64[arg_8]->sub_1D0E70();
        }
        if (!var_430)
            return;
    }
}
