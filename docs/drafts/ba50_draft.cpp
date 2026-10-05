// The update: the vote's text when the vote's state changes, and "Xbox Live
// Options" marked with the service's two flags; then the base's update.
// match: ?vf_014@type_21A5E0@@UAEXM@Z @ 0x0021BA50
// match: __ehhandler$?vf_014@type_21A5E0@@UAEXM@Z-0xB @ 0x00307DD0
// match: __ehhandler$?vf_014@type_21A5E0@@UAEXM@Z @ 0x00307DDB
void type_21A5E0::vf_014(RwReal arg_0)
{
    bool lv_D;
    bool lv_15;
    RwInt32 lv_14;
    RwChar lv_11C[256];

    lv_D = sub_1C4CB0();
    lv_15 = sub_1C4E40() != 0;
    if (unk_3E0 != lv_D || unk_3E1 != lv_15)
    {
        unk_3E0 = lv_D;
        unk_3E1 = lv_15;
        sub_21B8F0();
    }
    lv_14 = sub_227560()->sub_227950();
    if ((lv_14 & 3) == 3)
        sprintf(lv_11C, "\xbc \xbd %s", type_1CB670("Xbox Live Options", 0).c_str());
    else if (lv_14 & 1)
        sprintf(lv_11C, "\xbc %s", type_1CB670("Xbox Live Options", 0).c_str());
    else if (lv_14 & 2)
        sprintf(lv_11C, "\xbd %s", type_1CB670("Xbox Live Options", 0).c_str());
    else
        sprintf(lv_11C, "%s", type_1CB670("Xbox Live Options", 0).c_str());
    unk_308.sub_1F28C0(sub_1CB720(lv_11C));
    type_21CB10::vf_014(arg_0);
}

