// "quit": asks whether to quit the game, "yes" and "no" running unk_198 and
// unk_1A4 (unk_1A4 also on backing out).
// match: ?sub_21E880@type_21DFE0@@QAEXXZ @ 0x0021E880
// match: __ehhandler$?sub_21E880@type_21DFE0@@QAEXXZ-0x20 @ 0x00308250
// match: __ehhandler$?sub_21E880@type_21DFE0@@QAEXXZ @ 0x00308270
void type_21DFE0::sub_21E880()
{
    type_1CB670 lv_2C("QUIT_GAME", 0);
    type_1CB670 lv_80("QUIT_GAME?", 0);
    type_1CB670 lv_64("Yes", 0);
    type_1CB670 lv_48("No", 0);

    sub_2171F0(lv_2C, lv_80, lv_64, &unk_198, lv_48, &unk_1A4, &unk_1A4);
}

