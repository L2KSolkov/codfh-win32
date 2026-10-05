// Loaded: the host options' fields, the level picked (the first when none
// is), 16 players, and the server's name (else the signed-in user's name,
// or the player's own).
// match: ?vf_03C@type_2053C0@@UAEXXZ @ 0x00205880
// match: __ehhandler$?vf_03C@type_2053C0@@UAEXXZ-0x20 @ 0x003058E0
// match: __ehhandler$?vf_03C@type_2053C0@@UAEXXZ @ 0x00305900
void type_2053C0::vf_03C()
{
    sub_205C10();
    if (unk_4FDBB0.unk_28 == -1)
        sub_1C3D80(0);
    type_211860_key lv_10(&dword_4FD974[unk_4FDBB0.unk_28]);

    unk_D8.sub_201EC0(lv_10);
    unk_174.sub_201EC0((type_2138C0_value)4);
    type_1CB670 lv_30 = sub_1CB720(sub_1C4320());

    if (lv_30.empty())
    {
        if (sub_227560()->sub_228100())
            lv_30 = sub_1CB720(sub_1C42E0());
        else
            lv_30 = sub_1CB720(dword_4F28F0->unk_183);
    }
    unk_90.sub_1F28C0(lv_30);
}

