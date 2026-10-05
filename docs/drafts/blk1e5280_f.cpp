// The font's last glyph (the one for missing characters): an inline with
// no address. Evidence: the constructor's frame is 32 bytes larger when
// it takes the address directly (the name's declined string constructor
// leaves its slots reserved until an inline call).
inline kujuUI::type_1E2250 *last_glyph(type_1E5A60 *arg_0)
{
    return &arg_0->unk_30[arg_0->unk_38 - 1];
}

// match: ??0type_1E5A60@@QAE@PBDPBUtype_1E5A80_header@@PBUtype_1E2250_entry@kujuUI@@HPBQAUtype_1E5830@@H@Z @ 0x001E5280
// match: __ehhandler$??0type_1E5A60@@QAE@PBDPBUtype_1E5A80_header@@PBUtype_1E2250_entry@kujuUI@@HPBQAUtype_1E5830@@H@Z-0x24 @ 0x00303AA0
// match: __ehhandler$??0type_1E5A60@@QAE@PBDPBUtype_1E5A80_header@@PBUtype_1E2250_entry@kujuUI@@HPBQAUtype_1E5830@@H@Z @ 0x00303AC4
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
type_1E5A60::type_1E5A60(const RwChar *arg_0, const type_1E5A80_header *arg_4, const type_1E2250_entry *arg_8,
                         RwInt32 arg_C, type_1E5830 *const *arg_10, RwInt32 arg_14)
    : unk_08(arg_4->unk_18), unk_0A(arg_4->unk_1A), unk_0C(arg_4->unk_1C), unk_0E(arg_4->unk_16), unk_10(arg_0)
{
    RwInt32 lv_10;
    const type_42CF80 *var_14;

    unk_2C = dword_503FD0;
    unk_38 = arg_C;
    unk_3A = arg_14;
    unk_30 = new type_1E2250[arg_C + 0x27];
    for (RwInt32 var_18 = 0; var_18 != arg_C; ++var_18)
    {
        type_1E2250 *l1C;
        RwInt32 loc20;
        const type_1E2250_entry *w24;
        RwRaster *var_28;
        RwUInt32 var_2C;
        RwUInt32 var_30;

        w24 = &arg_8[var_18];
        loc20 = w24->unk_02;
        var_28 = arg_10[loc20]->unk_1C->unk_00;
        var_30 = var_28->width;
        var_2C = var_28->height;
        {
            type_1E2250 var_48(w24, (RwReal)var_30, (RwReal)var_2C);
            l1C = &unk_30[var_18];
            *l1C = var_48;
        }
    }
    for (lv_10 = 0; lv_10 != arg_14; ++lv_10)
        unk_3C[lv_10] = arg_10[lv_10];
    for (; lv_10 != 4; ++lv_10)
        unk_3C[lv_10] = 0;
    dword_503FD0 = this;
    var_14 = unk_42CF80;
    while (var_14->unk_00 != -1)
    {
        type_1E2250 *lv_64 = sub_1E5940(var_14->unk_04);
        type_1E2250 lcl_60(*lv_64, (RwUInt16)var_14->unk_00);
        unk_30[unk_38] = lcl_60;
        ++unk_38;
        ++var_14;
    }
    unk_34 = last_glyph(this);
}

