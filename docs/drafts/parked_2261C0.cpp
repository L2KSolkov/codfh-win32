// match: ?sub_226DD0@type_5051E8@@QAEXABUtype_1CCA10@@@Z @ 0x00226DD0
void type_5051E8::sub_226DD0(const type_1CCA10 &arg_0)
{
    RwInt32 var_4;

    switch (XOnlineTaskContinue(unk_160))
    {
    }
    // A compiled-out check (docs/toolchain.md).
    if (!unk_160)
    {
    }
    var_4 = 0;

    if (has_dword_4B9E50())
        var_4 = dword_4B9E50;
    if (unk_164 && !unk_16C && sub_1C4C00())
    {
        unk_164 = 0;
        if (XOnlineMutelistGet(var_4, 0xFA, 0, &unk_16C, unk_174, &unk_170))
            unk_16C = 0;
    }
    else if (!sub_1C4C00() && !unk_164)
        unk_164 = 1;
    if (unk_16C)
    {
        switch (XOnlineTaskContinue(unk_16C))
        {
        case XONLINETASK_S_SUCCESS:
            XOnlineTaskClose(unk_16C);
            unk_16C = 0;
            break;
        }
    }
    if (!unk_16C)
    {
        unk_168++;
        if (unk_168 >= 0x10)
            unk_168 = 0;
        // A compiled-out check of a dword (docs/toolchain.md): the mask's
        // copy is one load on. Which member it read is not in the code.
        if (!unk_16C)
        {
        }
        type_1DDE20_mask ebp_14 = sub_1D8810()->get_unk_292C();
        XUID lv_10;

        ebp_14.discard(unk_4F7EB8.get_unk_19C()->get_unk_B0()->sub_1CFF90());
        // Another (the test is one load on).
        if (!unk_168)
        {
        }
        if (ebp_14.test(unk_168))
        {
            if (sub_1D8810()->sub_1DBD60(unk_168, &lv_10, 1) && lv_10.qwUserID)
            {
                RwUInt32 var_18;

                for (var_18 = 0; var_18 < unk_170; var_18++)
                {
                    if (unk_174[var_18].xuid.qwUserID == lv_10.qwUserID)
                    {
                        get_dword_4F8180()->unk_3060.sub_1C7C70(unk_168, true);
                        break;
                    }
                }
                if (var_18 == unk_170)
                    get_dword_4F8180()->unk_3060.sub_1C7C70(unk_168, false);
            }
        }
    }
}


// match: ?sub_2270E0@type_5051E8@@QAEXH@Z @ 0x002270E0
void type_5051E8::sub_2270E0(RwInt32 arg_0)
{
    UIX_FRIENDS_PARAMS fp_98;
    UIX_LOGON_PARAMS lv_80;
    bool bp_21;
    HRESULT t20;
    UIX_PLAYERS_PARAMS l1C;

    bp_21 = false;

    switch (arg_0)
    {
    case 1:
    case 4:
    case 5:
    {
        memset(&lv_80, 0, sizeof(lv_80));
        lv_80.LogonServiceIDs[0] = 6;
        lv_80.LogonServiceIDs[1] = 8;
        lv_80.LogonUserCount = 1;
        if (dword_4F45F8->unk_3C == 1)
        {
            lv_80.LogonType = UIX_LOGON_TYPE_RETRIEVED_GAME_INVITE;
            lv_80.pGameInvite = (XONLINE_ACCEPTED_GAMEINVITE *)dword_4F45F8->unk_398;
        }
        else if (dword_4F45F8->unk_40)
        {
            dword_4F45F8->unk_40 = 0;
            lv_80.LogonType = UIX_LOGON_TYPE_RETRIEVED_STATE;
            lv_80.pLogonState = (XONLINE_LOGON_STATE *)dword_4F45F8->unk_48A;
            RwInt32 t9C = dword_4B9E50;

            if (t9C)
            {
                XONLINE_USER *varA4;
                XONLINE_USER *locA0;

                locA0 = (XONLINE_USER *)(dword_4F45F8->unk_48A + 4);
                varA4 = &locA0[t9C];

                if (locA0->szGamertag[0] && !varA4->szGamertag[0])
                {
                    XONLINE_USER *varA8 = &locA0[t9C];

                    *varA8 = *locA0;
                    memset(locA0, 0, sizeof(XONLINE_USER));
                }
            }
        }
        else
        {
            dword_4F45F8->unk_3C = 0;
            bp_21 = true;
        }
        if (bp_21)
            lv_80.LogonType = (UIX_LOGON_TYPE)(arg_0 == 4);
        if (lv_80.LogonType == UIX_LOGON_TYPE_SILENT)
            sub_228090(0);
        lv_80.StructSize = sizeof(lv_80);
        t20 = unk_84->StartFeature(UIX_LOGON_FEATURE, &lv_80);
        if (t20 == S_OK)
            sub_1D8810()->sub_1DB970();
        unk_90 = arg_0;
        break;
    }
    case 2:
    case 6:
    {
        unk_15D = sub_2279D0(false);
        memset(&fp_98, 0, sizeof(fp_98));
        fp_98.StructSize = sizeof(fp_98);
        if (has_dword_4B9E50())
            fp_98.UserPort = get_dword_4B9E50();
        t20 = unk_84->StartFeature(UIX_FRIENDS_FEATURE, &fp_98);
        if (t20 == S_OK)
            unk_90 = arg_0;
        else
        {
            fp_98.UserPort = sub_227900(0);
            t20 = unk_84->StartFeature(UIX_FRIENDS_FEATURE, &fp_98);
        }
        if (t20 == S_OK)
            unk_90 = arg_0;
        break;
    }
    case 3:
    case 7:
    {
        unk_15D = sub_2279D0(false);
        memset(&l1C, 0, sizeof(l1C));
        l1C.StructSize = sizeof(l1C);
        l1C.DisplayType = UIX_PLAYERS_DISPLAY_CURRENT_PLAYERS | UIX_PLAYERS_DISPLAY_DEPARTED_PLAYERS;
        l1C.FilterFlags = 0;
        l1C.pPlayerControllingScreen = 0;
        l1C.SortCurrentPlayersList = FALSE;
        if (has_dword_4B9E50())
            l1C.UserPort = get_dword_4B9E50();
        t20 = unk_84->StartFeature(UIX_PLAYERS_FEATURE, &l1C);
        if (t20 == S_OK)
            unk_90 = arg_0;
        else
        {
            l1C.UserPort = sub_227900(0);
            l1C.UserPort = l1C.UserPort;
            t20 = unk_84->StartFeature(UIX_PLAYERS_FEATURE, &l1C);
        }
        if (t20 == S_OK)
            unk_90 = arg_0;
        break;
    }
    }
}

// match: ?sub_227660@type_5051E8@@QAEXH@Z @ 0x00227660
void type_5051E8::sub_227660(RwInt32 arg_0)
{
    if (unk_148.size())
    {
        // A compiled-out check of a dword (docs/toolchain.md): the test's
        // registers are one load on. Which member it read is not in the
        // code.
        if (!unk_90)
        {
        }
        if (unk_1116.test(arg_0))
        {
            ILivePlayersList *var_4;
            XUID var_10;

            unk_84->GetFeatureInterface(UIX_PLAYERS_FEATURE, 0, (VOID **)&var_4);
            if (sub_1D8810()->sub_1DBD60(arg_0, &var_10, 0))
            {
                for (std::vector<type_22AF50 *>::iterator var_14 = unk_148.begin(); var_14 != unk_148.end(); ++var_14)
                {
                    type_22AF50 *var_18 = *var_14;

                    if (var_18->GetXUID()->qwUserID == var_10.qwUserID)
                    {
                        var_4->UnregisterPlayer(var_18);
                        delete var_18;
                        unk_148.erase(var_14);
                        break;
                    }
                }
            }
            unk_1116.drop(arg_0);
        }
    }
    unk_1114.drop(arg_0);
}


// match: ?sub_227CA0@type_5051E8@@QAEXXZ @ 0x00227CA0
void type_5051E8::sub_227CA0()
{
    if (!(unk_94 & 2) || unk_4F7EB8.get_unk_19C_direct()->vf_06C())
        unk_94 &= ~0x10;
    else
    {
        RwUInt32 slot_C;
        type_1DDE20_mask bp_8 = unk_4F7EB8.get_unk_19C()->get_unk_B0()->get_unk_0C();
        RwUInt32 bp_4;

        slot_C = bp_8.sub_1D4A60();
        bp_4 = unk_4F7EB8.get_unk_19C()->unk_43;

        if (bp_4 - slot_C >= 4)
            unk_94 |= 0x10;
        else
            unk_94 &= ~0x10;
    }
}

