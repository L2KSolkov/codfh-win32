// Its texts: the session's name, game type, level and players ("n/most");
// with no session, the player's name and "Host new".
// match: ?vf_004@type_1FB520@@UAEXXZ @ 0x001FB7B0
// match: __ehhandler$?vf_004@type_1FB520@@UAEXXZ-0x5A @ 0x00304B90
// match: __ehhandler$?vf_004@type_1FB520@@UAEXXZ @ 0x00304BEA
void type_1FB520::vf_004()
{
    if (unk_40)
    {
        const RwChar *lv_34 = sub_1A3CB0(unk_40->unk_2B);
        const RwChar *lv_38 = sub_1C4590(unk_40->unk_28);

        sub_1EC2C0(sub_1CB720(unk_40->unk_10), 0);
        sub_1EC2C0(type_1CB670(lv_34, 0), 1);
        sub_1EC2C0(type_1CB670(lv_38, 0), 2);
        type_1CB670 lv_2C;
        RwUInt8 lv_2D = unk_40->unk_29;

        if (lv_2D > unk_40->unk_2A)
            lv_2D = unk_40->unk_2A;
        lv_2C.sub_1FBB70(lv_2D).sub_1FBB90(*sub_1CBB30()).sub_1FBB70(unk_40->unk_2A);
        sub_1EC2C0(lv_2C, 3);
    }
    else
    {
        sub_1EC2C0(sub_1CB720(sub_1C42E0()), 0);
        sub_1EC2C0(type_1CB670(), 2);
        sub_1EC2C0(type_1CB670("Host new", 0), 1);
        sub_1EC2C0(type_1CB670(), 3);
    }
}

