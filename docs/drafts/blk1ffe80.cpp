// match: ?sub_1FFE80@type_1FF250@@QAEXXZ @ 0x001FFE80
// match: __ehhandler$?sub_1FFE80@type_1FF250@@QAEXXZ-0x79 @ 0x00305060
// match: __ehhandler$?sub_1FFE80@type_1FF250@@QAEXXZ @ 0x003050D9
void type_1FF250::sub_1FFE80()
{
    kujuUI::type_1E4130 local_CC;
    kujuUI::type_3E7D08 *ebp_14;

    ebp_14 = 0;

    if (dword_42926C && sub_188350() != 4 && !sub_227560()->get_unk_1120())
    {
        if (sub_1EF160())
        {
            if (sub_1E7CF0())
                ebp_14 = sub_1E7CF0()->sub_1E7FE0();
            if (!ebp_14)
            {
                sub_21A5E0()->get_shown(ebp_14);
            }
        }
        else if (sub_200780())
        {
            if (sub_1E7CF0())
                ebp_14 = sub_1E7CF0()->sub_1E7FE0();
            if (!ebp_14)
                ebp_14 = sub_1FF250()->sub_200900();
        }
    }
    RwInt32 lv_10 = 0;
    if (ebp_14)
    {
        sub_1E7CF0()->vf_018(&local_CC);
        lv_10 = ebp_14->vf_024();
    }
    if (unk_40 != lv_10)
    {
        unk_40 = lv_10;
        type_1CB670 lv_EC;

        if (unk_40 & 2)
        {
            add_text(lv_EC, type_1CB670("LEGEND_SELECT", 0));
            add_text(lv_EC, sub_1CB720("  "));
        }
        if (unk_40 & 4)
        {
            add_text(lv_EC, type_1CB670("CANCEL_BUTTON", 0));
            add_text(lv_EC, sub_1CB720("  "));
        }
        else if (unk_40 & 8)
        {
            add_text(lv_EC, type_1CB670("LEGEND_BACK", 0));
            add_text(lv_EC, sub_1CB720("  "));
        }
        if ((unk_40 & 0x30) == 0x30)
            add_text(lv_EC, type_1CB670("LEGEND_MOVE_CHANGE", 0));
        else if (unk_40 & 0x10)
            add_text(lv_EC, type_1CB670("LEGEND_MOVE", 0));
        else if (unk_40 & 0x20)
            add_text(lv_EC, type_1CB670("LEGEND_CHANGE", 0));
        dword_5043C0->sub_218F20(lv_EC);
    }
    if (unk_40)
        dword_5043C0->vf_018(&local_CC);
    sub_227560()->sub_227070();
}
