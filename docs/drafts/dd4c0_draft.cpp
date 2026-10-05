// The update: the searching page and text over three frames before the
// search starts (sub_20CB70); while it runs, the text and the sessions
// refreshed until the network game stops searching (then the "no
// sessions" page when none were found); after a failed join, its text.
// match: ?vf_014@type_20C470@@UAEXM@Z @ 0x0020D4C0
// match: __ehhandler$?vf_014@type_20C470@@UAEXM@Z-0x36 @ 0x00306710
// match: __ehhandler$?vf_014@type_20C470@@UAEXM@Z @ 0x00306746
void type_20C470::vf_014(RwReal arg_0)
{
    type_2049D0::vf_014(arg_0);
    if (unk_876C == 0)
    {
        if (!sub_1E7CF0()->sub_1E7D00(&unk_84B4))
            sub_1E7CF0()->sub_1E7D30(&unk_84B4);
        unk_8708.sub_1F28C0(sub_20EB30(type_1CB670("Searching...", 0), arg_0));
        unk_876C++;
    }
    else if (unk_876C == 1)
    {
        unk_876C++;
    }
    else if (unk_876C == 2)
    {
        sub_20CB70();
        unk_876C++;
    }
    type_1E7CF0 *lv_10 = sub_1E7CF0();

    if (unk_8764)
    {
        if (!lv_10->sub_1E7D00(&unk_84B4))
            lv_10->sub_1E7D30(&unk_84B4);
        unk_8708.sub_1F28C0(sub_20EB30(type_1CB670("Searching...", 0), arg_0));
        sub_20D8D0();
        unk_8764 = !unk_4F7EB8.get_unk_19C_direct()->vf_074();
        if (!unk_8764)
        {
            lv_10->sub_1E7D90(&unk_84B4);
            if (unk_8758.empty() && sub_204EA0())
                lv_10->sub_1E7D30(&unk_81A4);
        }
        unk_4F7EB8.sub_1AF750((RwInt32)arg_0, 1, 0);
    }
    else if (unk_8768)
    {
        unk_86E0.sub_1F28C0(sub_20EB30(type_1CB670("Joining", 0), arg_0));
        unk_86B8.sub_1F28C0(unk_4F7E9C);
    }
}

