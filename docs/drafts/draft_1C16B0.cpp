// Parked 2026-09-28: sub_1C16B0, sub_1C1820, sub_1C1A40 (unit_1C0910).
// Code matches bar one thing: the image's frames hold one more 4-byte slot,
// never written, placed after the vector difference's temporaries (and its
// left operand's pointer), and the register rotation runs 1-2 steps ahead
// from the start. Tried: free operator-, a set() inside the 3-arg ctor, a
// named local in operator-, an inline operator= and copy ctor, a float
// direct-return length() wrapper, compiled-out checks (these fix the
// rotation in sub_1C1A40: `if (!unk_08) {}` before `*arg_10 = 1e10f` and
// after the length), a direct-return team getter (writes the slot).
// The header needs, on type_1F8560_v (game/netvec.h):
//   type_1F8560_v(RwReal x, RwReal y, RwReal z) { unk_00 = x; unk_04 = y; unk_08 = z; }
//   type_1F8560_v operator-(const type_1F8560_v &b) const
//   { return type_1F8560_v(unk_00 - b.unk_00, unk_04 - b.unk_04, unk_08 - b.unk_08); }
//   void operator+=(const type_1F8560_v &b) { unk_00 += b.unk_00; ... }
//   void operator/=(RwReal s) { unk_00 /= s; ... }

// match: ?sub_1C16B0@type_1C0F60@@QAEHIPAUtype_4FBC50_player@@H@Z @ 0x001C16B0
RwInt32 type_1C0F60::sub_1C16B0(RwUInt32 arg_0, type_4FBC50_player *arg_4, RwInt32 arg_8)
{
    RwInt32 var_28 = -1;
    RwReal var_20 = 0;
    type_1F8560_v var_C;
    type_1F8560_v var_18;
    RwUInt32 var_2C;
    RwReal var_24;
    RwUInt32 var_30;
    RwReal var_1C;

    for (var_2C = 0; var_2C < (RwUInt32)unk_08; var_2C++)
    {
        if (arg_8 != var_2C)
        {
            var_24 = 1e10f;
            for (var_30 = 0; var_30 < arg_0; var_30++)
            {
                unk_0C[var_2C]->sub_1C0F20(&var_18);
                var_C = arg_4[var_30].unk_00 - var_18;
                var_1C = var_C.sub_1BF590();
                if (var_1C < var_24)
                    var_24 = var_1C;
            }
            if (var_24 > var_20)
            {
                var_20 = var_24;
                var_28 = var_2C;
            }
        }
    }
    if (var_28 == -1)
    {
        var_28 = 0;
        if (0)
            sub_1C8A30("Failed to find valid spawn point\n");
    }
    return var_28;
}

// match: ?sub_1C1820@type_1C0F60@@QAEHIPAUtype_4FBC50_player@@H@Z @ 0x001C1820
RwInt32 type_1C0F60::sub_1C1820(RwUInt32 arg_0, type_4FBC50_player *arg_4, RwInt32 arg_8)
{
    RwInt32 var_34 = 0x7FFFFFFF;
    RwInt32 var_4 = 0x7FFFFFFF;
    type_1F8560_v var_1C;
    type_1F8560_v var_30;
    type_1F8560_v var_48;
    RwReal var_24 = 1e10f;
    RwReal var_8 = flt_3E3314;
    RwUInt32 var_4C;
    RwUInt32 var_3C;
    RwReal var_20;
    RwReal var_38;
    RwReal var_10;
    RwReal var_C;

    if (!arg_0)
        return 0;
    for (var_4C = 0; var_4C < arg_0; var_4C++)
        var_30 += arg_4[var_4C].unk_00;
    var_30 /= (RwReal)arg_0;
    for (var_3C = 0; var_3C < (RwUInt32)unk_08; var_3C++)
    {
        unk_0C[var_3C]->sub_1C0F20(&var_1C);
        var_48 = var_1C - var_30;
        var_20 = var_48.sub_1BF590();
        if (var_20 < var_24)
        {
            var_10 = sub_1C1A40(arg_0, arg_4, &var_1C, 8, &var_38);
            var_C = flt_3E3314 - var_10;
            if (var_C < flt_3CD84C)
            {
                var_24 = var_20;
                var_34 = var_3C;
            }
            else if (var_C < var_8)
            {
                var_8 = var_C;
                var_4 = var_3C;
            }
        }
    }
    if (var_34 != 0x7FFFFFFF)
        return var_34;
    if (var_4 != 0x7FFFFFFF)
        return var_4;
    if (0)
        sub_1C8A30("Unable to find a spawn point\n");
    return -1;
}

// match: ?sub_1C1A40@type_1C0F60@@QAEMIPAUtype_4FBC50_player@@PAUtype_1F8560_v@@HPAM@Z @ 0x001C1A40
RwReal type_1C0F60::sub_1C1A40(RwUInt32 arg_0, type_4FBC50_player *arg_4, type_1F8560_v *arg_8, RwInt32 arg_C,
                               RwReal *arg_10)
{
    type_1F8560_v var_10;
    RwReal var_14 = 1e10f;
    RwUInt32 var_18;
    RwReal var_4;

    *arg_10 = 1e10f;
    for (var_18 = 0; var_18 < arg_0; var_18++)
    {
        var_10 = arg_4[var_18].unk_00 - *arg_8;
        var_4 = var_10.sub_1BF590();
        if (arg_C == 8 || arg_C != arg_4[var_18].unk_0C)
        {
            if (var_4 < *arg_10)
                *arg_10 = var_4;
        }
        else if (var_4 < var_14)
            var_14 = var_4;
    }
    // Compared as a word: 1e10 is the untouched value.
    if (var_14 == 1e10f)
        var_14 = *arg_10;
    return var_14;
}

