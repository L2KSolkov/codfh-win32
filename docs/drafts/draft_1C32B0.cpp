// Parked 2026-09-28: type_4F8348::sub_1C32B0 and sub_1C3520 (unit_1C3120).
// Fixed so far: the peers mask passed as others()'s temporary (not a named
// local); the client's mask filled with type_1DDE20_mask::mark(0) (two
// checks then the r local; add mark() back to the mask header). With a
// get_unk_B0_checked() (r = unk_B0; if (!unk_B0) {}) on type_4F8054 the
// copy lines up; left: in others()'s clear the shift register is one load
// early in the image (image eax/edx, ours edx/eax). Variants of others()
// with an extra check (at the start, on the peer read, through
// get_unk_0C) were not inlined at all.

// match: ?sub_1C32B0@type_4F8348@@QAEXHH@Z @ 0x001C32B0
void type_4F8348::sub_1C32B0(RwInt32 arg_0, RwInt32 arg_4)
{
    if (unk_4F61F8.unk_104)
    {
        if (0)
            off_42CD14("VOTE localVoteCall (client)\n");
        type_3E0FE4 var_24;
        var_24.unk_04 = arg_0;
        var_24.unk_08 = arg_4;
        var_24.unk_10 = unk_4F7EB8.sub_1AEC70();
        type_1DDE20_mask m_10;
        m_10.mark(0);
        type_4F8058::get()->sub_1DDE20(&var_24, m_10);
        unk_38 = 1;
    }
    else if (unk_00 == -1)
    {
        if (0)
            off_42CD14("VOTE localVoteCall (server) - sending out vote call\n");
        unk_00 = arg_0;
        unk_04 = arg_4;
        unk_10 = 1;
        unk_14 = 0;
        unk_38 = 1;
        unk_18 = unk_4F7EB8.sub_1ACA70();
        unk_1C = sub_1CB720(dword_4F28F0->unk_183);
        unk_0C = 60.0f;
        type_3E0FE4 var_38;
        var_38.unk_04 = arg_0;
        var_38.unk_08 = arg_4;
        var_38.unk_0C = unk_08;
        var_38.unk_10 = 0;
        type_4F8058::get()->sub_1DDE20(&var_38, type_4F8054::get()->get_unk_B0_checked()->others());
    }
}

// match: ?sub_1C3520@type_4F8348@@QAEXHIII@Z @ 0x001C3520
void type_4F8348::sub_1C3520(RwInt32 arg_0, RwUInt32 arg_4, RwUInt32 arg_8, RwUInt32 arg_C)
{
    if (unk_4F61F8.unk_104)
    {
        if (0)
            off_42CD14("VOTE remoteVoteCall (client)  idx %d %d\n", arg_8, unk_08);
        if (arg_8 >= unk_08)
        {
            unk_00 = arg_0;
            unk_04 = arg_4;
            unk_08 = arg_8;
            unk_38 = arg_C == unk_4F7EB8.sub_1AEC70();
            sub_1C3740();
        }
    }
    else if (unk_00 == -1)
    {
        if (0)
            off_42CD14("VOTE remoteVoteCall (server) - sending out vote call\n");
        unk_00 = arg_0;
        unk_04 = arg_4;
        unk_10 = 1;
        unk_14 = 0;
        unk_38 = 0;
        unk_18 = unk_4F7EB8.sub_1ACA70();
        unk_1C = sub_1CB720(type_4F8054::get()->get_unk_B0()->unk_90[arg_C].unk_00);
        unk_0C = 60.0f;
        type_3E0FE4 var_20;
        var_20.unk_04 = arg_0;
        var_20.unk_08 = arg_4;
        var_20.unk_0C = unk_08;
        var_20.unk_10 = arg_C;
        type_4F8058::get()->sub_1DDE20(&var_20, type_4F8054::get()->get_unk_B0_checked()->others());
        sub_1C3740();
    }
}

