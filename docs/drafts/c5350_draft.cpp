
// The objective hint text: the localised text for "HINT_" and the game
// type's name, then, in the bomb game (8), "_ATTACK" when the local player's
// team (sub_1C43A0 when it is 1) is the attacking one (4 with four teams,
// else 2), "_DEFEND" otherwise; in the others with a score limit set,
// "_SCORE%s" with the limit in place of its "%1".
// match: ?sub_1C5350@@YA?AUtype_1CB670@@XZ @ 0x001C5350
type_1CB670 sub_1C5350()
{
    bool v_D;

    v_D = false;
    type_1A5EA0 v_30("HINT_");

    v_30.sub_1C84F0(sub_1A3CB0(dword_4FB9E0.get_unk_08()));
    if (dword_4FB9E0.get_unk_08() == 8)
    {
        bool v_35;
        RwInt32 v_34;

        v_35 = false;
        v_34 = sub_1C4880(unk_4F7EB8.sub_1AEC70());
        if (v_34 == 1)
        {
            v_34 = sub_1C43A0();
        }
        if (v_34 == dword_4FB9E0.get_team_count())
        {
            v_35 = true;
        }
        if (v_35)
        {
            v_30.sub_1C84F0("_ATTACK");
        }
        else
        {
            v_30.sub_1C84F0("_DEFEND");
        }
    }
    else if ((RwUInt32)unk_4FDBB0.unk_18 > 0)
    {
        v_30.sub_1C84F0("_SCORE%s");
        v_D = true;
    }
    if (v_D)
    {
        RwChar v_44[0xC];

        sprintf(v_44, "%d", unk_4FDBB0.unk_18);
        return sub_1CB7B0(type_1CB670(v_30.c_str(), 1).c_str(), v_44, 0);
    }
    return type_1CB670(v_30.c_str(), 1);
}
// PARKED 2026-09-29. With path 1 through type_1CB670 every call matches (all
// five "x ? x : """ string ctors expanded, both key ctors 1CB6B0 out of line),
// but: frame 0x11C vs 0x140 (image has 0x40 unused bytes under -0xE8 = 2 x
// 0x20, a declined inline's reserve per key-ctor site?), path 1's ctor `this`
// goes eax -> [-0x144] -> [-0xE8] in the image (a call result), and v_D sits
// above the cookie (-0xD). Making the key ctor inline expands it (E3970 called);
// extra inline pressure declines the simple ctors first. Return type is
// type_1CB670 (hidden ret goes straight to sub_1CB7B0); the HUD declares it
// std::string for now.
