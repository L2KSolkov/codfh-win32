// The vote's text: "Confirm Vote", "Call Vote" or "Vote Now".
// match: ?sub_21B8F0@type_21A5E0@@QAEXXZ @ 0x0021B8F0
// match: __ehhandler$?sub_21B8F0@type_21A5E0@@QAEXXZ-0x18 @ 0x00307DA0
// match: __ehhandler$?sub_21B8F0@type_21A5E0@@QAEXXZ @ 0x00307DB8
void type_21A5E0::sub_21B8F0()
{
    if (unk_3E1)
        unk_268.sub_1F28C0(type_1CB670("Confirm Vote", 0));
    else if (unk_3E0)
        unk_268.sub_1F28C0(type_1CB670("Call Vote", 0));
    else
        unk_268.sub_1F28C0(type_1CB670("Vote Now", 0));
}

