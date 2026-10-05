// SUPERSEDED: matched in src/recovered/unit_1A6140.cpp with a 128-byte buffer.
// The older 132-byte buffer below caused the eight-byte alignment difference.

// match: ?vf_004@type_3E102C@@UAEXPAUtype_1F8560@@@Z @ 0x001A8990
void type_3E102C::vf_004(type_1F8560 *arg_0)
{
    RwChar var_94[0x84];

    // Its length is block-scoped: it sits below the /GS array
    // (docs/toolchain.md).
    {
        RwUInt32 var_98 = arg_0->sub_1F8810(8);

        var_94[var_98] = 0;
        arg_0->sub_1F8A40(var_94, var_98 << 3);
    }
    unk_04 = var_94;
}

