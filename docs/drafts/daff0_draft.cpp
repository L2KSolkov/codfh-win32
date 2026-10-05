// The update: the base's; a join that failed since (the service's unk_A4)
// shows "Join Failed" and why; then "Friends List" marked with the
// service's two flags.
// match: ?vf_014@type_20AA10@@UAEXM@Z @ 0x0020AFF0
// match: __ehhandler$?vf_014@type_20AA10@@UAEXM@Z-0x21 @ 0x00306270
// match: __ehhandler$?vf_014@type_20AA10@@UAEXM@Z @ 0x00306291
void type_20AA10::vf_014(RwReal arg_0)
{
    RwInt32 lv_10;
    RwChar lv_114[256];

    type_2049D0::vf_014(arg_0);
    if (sub_227560()->get_unk_A4())
    {
        sub_1E7CF0()->sub_1E7D30(&unk_188);
        unk_370.sub_1F28C0(type_1CB670("Join Failed", 0));
        unk_348.sub_1F28C0(type_1CB670("GAME_SESSION_UNAVAILABLE", 0));
        sub_227560()->set_unk_A4(0);
    }
    lv_10 = sub_227560()->sub_227950();
    if ((lv_10 & 3) == 3)
        sprintf(lv_114, "\xbc \xbd %s", sub_20B3A0().c_str());
    else if (lv_10 & 1)
        sprintf(lv_114, "\xbc %s", sub_20B3A0().c_str());
    else if (lv_10 & 2)
        sprintf(lv_114, "\xbd %s", sub_20B3A0().c_str());
    else
        sprintf(lv_114, "%s", sub_20B3A0().c_str());
    unk_3C0.sub_1F28C0(sub_1CB720(lv_114));
}

