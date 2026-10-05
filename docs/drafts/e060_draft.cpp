// Shows the column the results are sorted by ("Sorting by %1" with its
// name).
// match: ?sub_20E060@type_20C470@@QAEXXZ @ 0x0020E060
// match: __ehhandler$?sub_20E060@type_20C470@@QAEXXZ-0x3C @ 0x003067A0
// match: __ehhandler$?sub_20E060@type_20C470@@QAEXXZ @ 0x003067DC
// The locals' names state their slots (docs/toolchain.md).
void type_20C470::sub_20E060()
{
    RwInt32 lv_10 = sub_1FBB50();
    type_1A5EA0 lv_A4[4] = {type_1A5EA0("Name", 0), type_1A5EA0("Map", 0), type_1A5EA0("Number of players", 0),
                             type_1A5EA0("Game type", 0)};

    type_1CB670 lv_30 = sub_1CB7B0("Sorting by %1", lv_A4[lv_10].c_str(), 0);

    unk_8730.sub_1F28C0(lv_30);
}

