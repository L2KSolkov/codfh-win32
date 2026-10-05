// Tells the network game the settings (vf_064): the time limit's index, the
// game type, unk_04, unk_0C and unk_10. A check compiled out of this build
// (an empty if) moves the registers one step on.
// match: ?sub_1B60E0@type_4FB9E0@@QAEXXZ @ 0x001B60E0
void type_4FB9E0::sub_1B60E0()
{
    if (!unk_00)
    {
    }
    unk_4F7EB8.get_unk_19C_direct()->vf_064(unk_08.unk_28, unk_08.unk_00, unk_08.unk_04, unk_08.unk_0C,
                                            unk_08.unk_10);
}

