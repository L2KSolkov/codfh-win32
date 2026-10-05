inline RwUInt16 site_section_(RwUInt32 i)
{
    RwUInt16 r = dword_4E5D30[i].unk_08;
    return r;
}
inline type_4F6B00_F4 facing_of_(RwReal arg_0)
{
    return sub_1A6E10(arg_0);
}
// match: ?sub_1A65B0@type_4F6B00@@QAEXABUtype_1CCA10@@@Z @ 0x001A65B0
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
// Its step at the time arg_0 while driven: its interface steps; a jump in
// the height of the shared position marks it moved; a pending flag clears
// once 50 ms have passed since it was sent; unless moved and at rest with
// the state unchanged (angle, the two values, the facing and the seven
// flags), the state is copied in and taken (sub_1A7A60), else only once the
// resend time (dword_4F7E8C) is over; the sites' sections are kept (at most
// 31); then its position, velocity and facing are copied from the
// interface.
void type_4F6B00::sub_1A65B0(const type_1CCA10 &arg_0)
{
    RwUInt32 lv_10;
    RwReal var_C;
    RwInt32 bp_8;
    RwInt32 bp_4;

    bp_4 = 0;
    bp_8 = 0;
    // Compiled-out checks: the registers after them are two loads on
    // (docs/toolchain.md).
    if (!unk_11C)
    {
    }
    if (!unk_11C)
    {
    }
    unk_11C->pvf_000((RwInt32)&arg_0);
    var_C = dword_4F6AF8 - unk_11C->pvf_004()->unk_04;
    dword_4F6AF8 = unk_11C->pvf_004()->unk_04;
    if ((RwReal)fabs((RwDouble)var_C) > 0.02f)
        bp_8 = 1;
    if (unk_134)
    {
        RwInt32 ebp_14 = 50;
        type_1CCA10 y18 = arg_0 - ebp_14;

        if (unk_18 >= y18)
        {
            unk_4C &= ~1;
            unk_134 = 0;
        }
    }
    bp_4 = !(!bp_8 && unk_11C->pvf_008()->sub_1A6D70() && !(fabs(unk_11C->pvf_00C() - unk_3C) > 0.1f)
             && unk_11C->pvf_014() == unk_44 && unk_11C->pvf_018() == unk_48 && unk_11C->pvf_010() == unk_40
             && get_bit_4C(0) == unk_11C->pvf_01C() && get_bit_4C(1) == unk_11C->pvf_020()
             && get_bit_4C(2) == unk_11C->pvf_024() && get_bit_4C(3) == unk_11C->pvf_028()
             && get_bit_4C(4) == unk_11C->pvf_02C() && get_bit_4C(5) == unk_11C->pvf_030()
             && get_bit_4C(6) == unk_11C->pvf_034());
    if (bp_4)
    {
        unk_24 = *unk_11C->pvf_004();
        unk_30 = *unk_11C->pvf_008();
        unk_3C = unk_11C->pvf_00C();
        unk_40 = unk_11C->pvf_010();
        unk_44 = unk_11C->pvf_014();
        unk_48 = unk_11C->pvf_018();
        if ((unk_4C & 1) && !unk_11C->pvf_01C())
            unk_134 = 1;
        if (unk_11C->pvf_01C())
            set_bit_4C(0, 1);
        set_bit_4C(1, unk_11C->pvf_020());
        set_bit_4C(2, unk_11C->pvf_024());
        set_bit_4C(3, unk_11C->pvf_028());
        set_bit_4C(4, unk_11C->pvf_02C());
        set_bit_4C(5, unk_11C->pvf_030());
        set_bit_4C(6, unk_11C->pvf_034());
        sub_1A7A60(arg_0);
    }
    else
    {
        type_1CCA10 l1C = unk_64 + dword_4F7E8C;

        if (arg_0 > l1C)
            sub_1A7A60(arg_0);
    }
    for (lv_10 = 0; lv_10 < 4; lv_10++)
    {
        unk_50[lv_10] = dword_4E5D30[lv_10].get_unk_08();
        if (unk_50[lv_10] > 0x1F)
            unk_50[lv_10] = 0x1F;
    }
    unk_D8 = *unk_11C->pvf_004();
    unk_E4 = *unk_11C->pvf_008();
    unk_F4 = facing_of_(unk_11C->pvf_00C());
    *(RwReal *)&unk_F0 = unk_11C->pvf_010();
}
