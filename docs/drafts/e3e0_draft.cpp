inline void add_text(type_1A5EA0 &arg_0, const type_1A5EA0 &arg_4)
{
    arg_0.sub_1C84F0(arg_4);
}

// The countdown's text: "Continue in" and the seconds left, rounded.
// match: ?sub_21E3E0@type_21DFE0@@QAEXXZ @ 0x0021E3E0
// match: __ehhandler$?sub_21E3E0@type_21DFE0@@QAEXXZ-0x10 @ 0x003081F0
// match: __ehhandler$?sub_21E3E0@type_21DFE0@@QAEXXZ @ 0x00308200
void type_21DFE0::sub_21E3E0()
{
    RwInt32 lv_10;
    type_1CB670 lv_30("Continue in", 0);

    add_text(lv_30, sub_1CB720(" "));
    lv_10 = (RwInt32)(unk_1FC + 0.99f);
    if (lv_10 < 0)
        lv_10 = 0;
    lv_30.sub_214A70(lv_10);
    unk_1D0.sub_1F28C0(lv_30);
}

