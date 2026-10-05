// match: ?sub_1C5350@@YA?AUtype_1CB670@@XZ @ 0x001C5350
// The objective hint's text: the key "HINT_" with the game type's short
// name, then for assault "_ATTACK" or "_DEFEND" by the local player's team
// (and whether four teams play), or "_SCORE%s" with the score to reach
// (when there is one) put in; localised.
type_1CB670 sub_1C5350()
{
    bool bp_D = false;
    type_1A5EA0 stk_30("HINT_");

    stk_30.sub_1C84F0(sub_1A3CB0(dword_4FB9E0.get_unk_08()));
    if (dword_4FB9E0.get_unk_08() == 8)
    {
        bool ebp_35 = false;
        RwInt32 local_34 = sub_1C4880(unk_4F7EB8.sub_1AEC70());

        if (local_34 == 1)
            local_34 = sub_1C43A0();
        if (local_34 == dword_4FB9E0.get_team_count())
            ebp_35 = true;
        if (ebp_35)
            stk_30.sub_1C84F0("_ATTACK");
        else
            stk_30.sub_1C84F0("_DEFEND");
    }
    else if ((RwUInt32)get_4FDBB0_unk_18() > 0)
    {
        stk_30.sub_1C84F0("_SCORE%s");
        bp_D = true;
    }
    if (bp_D)
    {
        RwChar v44[0xC];

        sprintf(v44, "%d", get_4FDBB0_unk_18());
        return sub_1CB7B0(type_1A5EA0(stk_30.c_str(), 1).c_str(), v44, 0);
    }
    return type_1CB670(stk_30.c_str(), 1);
}
