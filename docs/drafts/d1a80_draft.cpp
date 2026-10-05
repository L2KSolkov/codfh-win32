// The question: the vote (the level, the game type or a player's kick) and
// who called it, then the votes for and against.
// match: ?vf_058@type_221780@@UAE?AUtype_1CB670@@XZ @ 0x00221A80
// match: __ehhandler$?vf_058@type_221780@@UAE?AUtype_1CB670@@XZ-0x9A @ 0x003088A0
// match: __ehhandler$?vf_058@type_221780@@UAE?AUtype_1CB670@@XZ @ 0x0030893A
type_1CB670 type_221780::vf_058()
{
    type_1CB670 lv_48;
    type_1CB670 lv_2C("%uyes%uno", 0);
    type_1CB670 lv_64;
    RwChar lv_164[256];
    RwUInt32 lv_168;
    RwUInt32 lv_16C;

    unk_334 = sub_1C4D60();
    unk_338 = sub_1C4D80();
    sub_1C4DA0(&lv_16C, &lv_168);
    lv_64 = sub_1C4DD0();
    switch (unk_334)
    {
    case 0:
        sub_1CB0F0(lv_164, type_1CB670("vote%1map%2", 0).c_str(), lv_64.c_str(),
                   type_1CB670(sub_1C4590(unk_338), 0).c_str());
        break;
    case 1:
        sub_1CB0F0(lv_164, type_1CB670("vote%1gamemode%2", 0).c_str(), lv_64.c_str(),
                   type_1CB670(sub_1C4E60(unk_338), 0).c_str());
        break;
    case 2:
        sub_1CB0F0(lv_164, type_1CB670("vote%1kick%2", 0).c_str(), lv_64.c_str(), sub_1C4630(unk_338));
        break;
    }
    lv_48 = sub_1CB720(lv_164);
    lv_48.sub_1C84F0(sub_1CB720("\n\n"));
    sprintf(lv_164, lv_2C.c_str(), lv_16C, lv_168);
    lv_48.sub_1C84F0(sub_1CB720(lv_164));
    return lv_48;
}

