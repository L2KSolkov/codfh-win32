// Resets the search settings (the "ResetSettings" action, also run when the
// page is shown): any level, game type 0x20, 8 players, a minimum of 0 and
// the subtype, team balance and friendly fire at 2 (any).
// match: ?sub_206850@type_2062B0@@QAEXXZ @ 0x00206850
// match: __ehhandler$?sub_206850@type_2062B0@@QAEXXZ-0x10 @ 0x00305AE0
// match: __ehhandler$?sub_206850@type_2062B0@@QAEXXZ @ 0x00305AF0
void type_2062B0::sub_206850()
{
    type_505188 lv_54;
    type_211860_key lv_10(&lv_54);

    unk_1E8.sub_201EC0(lv_10);
    unk_1C8.sub_201EC0((type_210430_value)0x20);
    unk_208.sub_201EC0((type_2138C0_value)8);
    unk_228.sub_1E7BB0(0);
    unk_2A4.sub_201EC0((type_214C30_value)2);
    unk_2C4.sub_201EC0((type_214C30_value)2);
    unk_2E4.sub_201EC0((type_214C30_value)2);
}

