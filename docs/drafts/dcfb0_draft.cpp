// The join (the selected row's session): "Joining" shown while the manager
// joins; on success the in-game menu is hidden, else the level picked is put
// back and, over Xbox Live, the failure is shown ("Join Failed" with the
// reason), or over the system link the failure page is taken down.
// match: ?sub_20CFB0@type_20C470@@QAEXXZ @ 0x0020CFB0
// match: __ehhandler$?sub_20CFB0@type_20C470@@QAEXXZ-0x4F @ 0x003066B0
// match: __ehhandler$?sub_20CFB0@type_20C470@@QAEXXZ @ 0x003066FF
void type_20C470::sub_20CFB0()
{
    bool lv_D;
    RwInt32 lv_14;
    type_1FB520 *lv_18;
    RwInt32 lv_1C;
    type_1FB520_session *lv_20;

    lv_D = false;
    lv_14 = 0;
    sub_1E7CF0()->sub_1E7D30(&unk_832C);
    if (sub_1ECB40())
    {
        lv_18 = (type_1FB520 *)sub_20E520();
        if (lv_18)
        {
            unk_8768 = true;
            unk_86E0.sub_1F28C0(type_1CB670("Joining", 0));
            unk_86B8.sub_1F28C0(type_1CB670());
            type_2053C0::sub_205BF0(2);
            lv_20 = lv_18->sub_21D030();
            lv_1C = unk_4FDBB0.unk_28;
            sub_1C3D80(lv_20->unk_28);
            lv_D = unk_4F7EB8.sub_1A9CE0((const type_1CC1F0 *)&unk_198, (const type_1CC3C0 *)lv_20, &lv_14, 0);
            unk_8768 = false;
        }
    }
    if (lv_14 == 0)
    {
        sub_1FC310()->sub_1FBE20();
        return;
    }
    sub_1C3D80(lv_1C);
    if (sub_204EA0())
    {
        switch (lv_14)
        {
        case 1:
            unk_86B8.sub_1F28C0(type_1CB670("Game session is full", 0));
            break;
        case 3:
            unk_86B8.sub_1F28C0(type_1CB670("PEER_CONNECTION_FAILED", 0));
            break;
        case 2:
            unk_86B8.sub_1F28C0(type_1CB670("Blocked from game session", 0));
            break;
        case 4:
            unk_86B8.sub_1F28C0(type_1CB670("SERVER_CONNECTION_FAILED", 0));
            break;
        default:
            unk_86B8.sub_1F28C0(type_1CB670("UNEXPECTED_CONNECTION_FAILURE", 0));
            break;
        }
        unk_86E0.sub_1F28C0(type_1CB670("Join Failed", 0));
    }
    else
    {
        if (sub_1E7CF0()->sub_1E7D00(&unk_832C))
            sub_1E7CF0()->sub_1E7D90(&unk_832C);
    }
}

