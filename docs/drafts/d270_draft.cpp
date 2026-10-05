// Shown: the base's showing, then the question for the host or not.
// match: ?vf_008@type_21D0D0@@UAEXXZ @ 0x0021D270
// match: __ehhandler$?vf_008@type_21D0D0@@UAEXXZ-0x10 @ 0x00307F90
// match: __ehhandler$?vf_008@type_21D0D0@@UAEXXZ @ 0x00307FA0
void type_21D0D0::vf_008()
{
    type_21CB10::vf_008();
    if (sub_1C4BE0())
        unk_16C.sub_1F28C0(type_1CB670("QUIT_GAME_HOST", 0));
    else
        unk_16C.sub_1F28C0(type_1CB670("QUIT_GAME?", 0));
}

