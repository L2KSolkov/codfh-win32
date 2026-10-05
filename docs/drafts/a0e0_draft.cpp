// "AppearStatus" shows "Appear Offline" or "Appear Online" as the service
// appears.
// match: ?sub_20A0E0@type_209E00@@QAEXXZ @ 0x0020A0E0
// match: __ehhandler$?sub_20A0E0@type_209E00@@QAEXXZ-0x10 @ 0x003060A0
// match: __ehhandler$?sub_20A0E0@type_209E00@@QAEXXZ @ 0x003060B0
void type_209E00::sub_20A0E0()
{
    if (sub_227560()->get_unk_A0())
        unk_378.sub_1F28C0(type_1CB670("Appear Offline", 0));
    else
        unk_378.sub_1F28C0(type_1CB670("Appear Online", 0));
}

