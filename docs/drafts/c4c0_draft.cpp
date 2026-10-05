// "kill": asks whether to kill the player, "yes" running unk_240 and "no"
// (and backing out) unk_24C.
// match: ?sub_21C4C0@type_21A5E0@@QAEXXZ @ 0x0021C4C0
// match: __ehhandler$?sub_21C4C0@type_21A5E0@@QAEXXZ-0x20 @ 0x00307E40
// match: __ehhandler$?sub_21C4C0@type_21A5E0@@QAEXXZ @ 0x00307E60
void type_21A5E0::sub_21C4C0()
{
    sub_2171F0(type_1CB670("Kill Player", 0), type_1CB670("kill_player_prompt", 0), type_1CB670("Yes", 0), &unk_240,
               type_1CB670("No", 0), &unk_24C, &unk_24C);
}

