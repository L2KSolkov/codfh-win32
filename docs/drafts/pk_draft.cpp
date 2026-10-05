// Takes the pick-up arg_0 it touched. First by its settings index: a
// weapon (2 to 17, 92 to 104 by threes) sets flag 12, and is its own when
// it carries it (full: flag 18 instead), else its name is flashed (HUD 6);
// a weapon's rounds (18 to 65, 93 to 106 in pairs) can be taken when it
// carries that weapon (full: flag 18); a health pack (75, 76) unless its
// health is full or it is in state 10; the health packs for later (77)
// up to 6, 4 or 2 by the difficulty; the inventory kinds (78 to 89, 108,
// 109) always; the bears (90, 91) set flag 11 (HUD 5). With flag 11 or 18
// set (or rounds it can take) the pick-up's message is kept (or a "full"
// help message shown), the inventory takes it and, when it gave anything,
// the message and its sound play and its trigger respawns; with flag 12 or
// 18 set (or its own weapon) the weapon is taken into the hand it frees or
// swapped with the one in hand (the old one dropped with its rounds), or
// its rounds added, and the trigger respawns. Flag 11 is cleared after.
// match: ?sub_106A60@type_10F710@@QAEXPAUtype_3D94B8@@@Z @ 0x00106A60
void type_10F710::sub_106A60(type_3D94B8 *arg_0)
{
    type_712B0_10F710 *v_C;
    RwInt32 v_10;
    RwInt32 v_14;
    type_3DF8D8 *v_18;
    RwInt32 v_1C;
    RwInt32 v_20;
    RwInt32 v_24;
    RwInt32 v_28;
    RwInt32 v_2C;
    RwChar v_88[64];
    RwInt32 v_144;

    v_C = (type_712B0_10F710 *)unk_344.unk_08;
    if (v_C && v_C->vf_008() != 1)
    {
        v_C = 0;
    }
    v_10 = -1;
    v_14 = 0;
    v_18 = 0;
    v_1C = 0;
    v_20 = 1;
    v_24 = 0;
    v_28 = 0;
    v_2C = arg_0->unk_3B0.sub_FB710();
    switch (v_2C)
    {
    case 75:
    case 76:
        if (unk_19DC < flt_3CD8E0 && unk_19DC > flt_3CD84C && unk_19D0 != 10)
            v_14 = 1;
        else
            sub_10F7E0(18, 1);
        break;
    case 77:
    {
        RwInt32 v_34;

        v_34 = 0;
        switch (dword_42B714)
        {
        case 0:
            v_34 = 6;
            break;
        case 1:
            v_34 = 4;
            break;
        default:
            v_34 = 2;
        }
        if (unk_21B4.sub_1E3BF0(1) < v_34)
            v_14 = 1;
        else
        {
            sub_10F7E0(18, 1);
            v_24 = 1;
        }
        break;
    }
    case 90:
    case 91:
        sub_10F7E0(11, 1);
        if (sub_10F790() == 11 && dword_4B9190)
            dword_4B9190->sub_E0410(5);
        break;
    case 18:
    case 19:
    case 20:
    case 21:
    case 22:
    case 23:
    case 24:
    case 25:
    case 26:
    case 27:
    case 28:
    case 29:
    case 30:
    case 31:
    case 32:
    case 33:
    case 34:
    case 35:
    case 36:
    case 37:
    case 38:
    case 39:
    case 40:
    case 41:
    case 42:
    case 43:
    case 44:
    case 45:
    case 46:
    case 47:
    case 48:
    case 49:
    case 50:
    case 51:
    case 52:
    case 53:
    case 54:
    case 55:
    case 56:
    case 57:
    case 58:
    case 59:
    case 60:
    case 61:
    case 62:
    case 63:
    case 64:
    case 65:
    case 93:
    case 94:
    case 96:
    case 97:
    case 99:
    case 100:
    case 102:
    case 103:
    case 105:
    case 106:
    {
        RwInt32 v_3C;

        for (v_3C = 0; v_3C < 39; v_3C++)
        {
            if (sub_106830(v_2C, v_3C))
                break;
        }
        if (v_3C < 39)
        {
            if ((RwUInt32)unk_1A48[v_3C]->unk_418 < unk_1A48[v_3C]->get_unk_448()->unk_CC)
                v_14 = 1;
            else
            {
                sub_10F7E0(18, 1);
                v_28 = 1;
            }
        }
        break;
    }
    case 78:
    case 79:
    case 80:
    case 81:
    case 82:
    case 83:
    case 84:
    case 85:
    case 86:
    case 87:
    case 88:
    case 89:
    case 108:
    case 109:
        v_14 = 1;
        break;
    case 2:
    case 3:
    case 4:
    case 5:
    case 6:
    case 7:
    case 8:
    case 9:
    case 10:
    case 11:
    case 12:
    case 13:
    case 14:
    case 15:
    case 16:
    case 17:
    case 92:
    case 95:
    case 98:
    case 101:
    case 104:
    {
        RwInt32 v_44;

        sub_10F7E0(12, 1);
        v_44 = sub_1068A0(v_2C);
        if ((v_44 == unk_1B30[0] || v_44 == unk_1B30[1]) && !unk_1B2C)
        {
            if ((RwUInt32)unk_1A48[v_44]->unk_418 < unk_1A48[v_44]->get_unk_448()->unk_CC)
                v_1C = 1;
            else
            {
                sub_10F7E0(12, 0);
                sub_10F7E0(18, 1);
                v_28 = 1;
            }
        }
        else if (v_44 != -1 && sub_10F790() == 12)
        {
            if (dword_4B9190)
                dword_4B9190->sub_E0410(6);
            sub_EAB80(unk_1D1C[v_44], 6);
        }
    }
    }
    if (sub_10F710() == 11 || sub_10F710() == 18 || v_14)
    {
        v_88[0] = 0;
        if (!v_28)
        {
            v_18 = 0;
            switch (v_2C)
            {
            case 75:
            case 76:
                if (unk_19DC >= flt_3CD8E0 && unk_19DC > flt_3CD84C && unk_19D0 != 10)
                {
                    type_3DF8D8_04 v_94;
                    type_3DF8D8_04 *v_98;

                    sub_198A20("COD_HelpMessages+Generic+Error_HealthFull", &v_94);
                    v_98 = sub_17C630();
                    if (!v_98 || (v_98 && v_98->unk_00 != v_94.unk_00))
                    {
                        sub_17C6C0(0);
                        sub_17C500(&v_94, 1, 1);
                        dword_4B1E98.sub_8A980(&dword_4B1A18, 0, 0, (RwV3d *)vf_0C4(), 1, 0);
                    }
                    v_20 = 0;
                }
                break;
            case 77:
                if (!v_24)
                {
                    v_18 = sub_198800(&unk_4B8FA4);
                    sub_EACA0(v_18->sub_197550(0, 0), 0, 0);
                }
                else
                {
                    type_3DF8D8_04 v_A0;
                    type_3DF8D8_04 *v_A4;

                    sub_198A20("COD_HelpMessages+Generic+Error_InvItemFull", &v_A0);
                    v_A4 = sub_17C630();
                    if (!v_A4 || (v_A4 && v_A4->unk_00 != v_A0.unk_00))
                    {
                        sub_17C6C0(0);
                        sub_17C500(&v_A0, 1, 1);
                        dword_4B1E98.sub_8A980(&dword_4B1A18, 0, 0, (RwV3d *)vf_0C4(), 1, 0);
                    }
                    v_20 = 0;
                }
                dword_4B9190->sub_E07D0();
                break;
            case 90:
            case 91:
            {
                RwInt32 v_A8;

                v_18 = sub_198800(&unk_4B9084);
                strcpy(v_88, v_18->sub_197550(0, 0));
                sub_6B5F0("PickedUpTeddyBear", vf_098(), 0, 0, &v_A8, 1, true, false);
                break;
            }
            case 18:
            case 19:
            case 20:
                v_18 = sub_198800(&unk_4B8FAC);
                strcpy(v_88, v_18->sub_197550(0, 0));
                break;
            case 21:
            case 22:
            case 23:
                v_18 = sub_198800(&unk_4B8FB4);
                strcpy(v_88, v_18->sub_197550(0, 0));
                break;
            case 24:
            case 25:
            case 26:
                v_18 = sub_198800(&unk_4B8FBC);
                strcpy(v_88, v_18->sub_197550(0, 0));
                break;
            case 27:
            case 28:
            case 29:
                v_18 = sub_198800(&unk_4B8FC4);
                strcpy(v_88, v_18->sub_197550(0, 0));
                break;
            case 30:
            case 31:
            case 32:
                v_18 = sub_198800(&unk_4B8FCC);
                strcpy(v_88, v_18->sub_197550(0, 0));
                break;
            case 33:
            case 34:
            case 35:
                v_18 = sub_198800(&unk_4B8FD4);
                strcpy(v_88, v_18->sub_197550(0, 0));
                break;
            case 36:
            case 37:
            case 38:
                v_18 = sub_198800(&unk_4B8FDC);
                strcpy(v_88, v_18->sub_197550(0, 0));
                break;
            case 39:
            case 40:
            case 41:
                v_18 = sub_198800(&unk_4B8FE4);
                strcpy(v_88, v_18->sub_197550(0, 0));
                break;
            case 42:
            case 43:
            case 44:
                v_18 = sub_198800(&unk_4B8FEC);
                strcpy(v_88, v_18->sub_197550(0, 0));
                break;
            case 45:
            case 46:
            case 47:
                v_18 = sub_198800(&unk_4B8FF4);
                strcpy(v_88, v_18->sub_197550(0, 0));
                break;
            case 93:
            case 94:
                v_18 = sub_198800(&unk_4B8FFC);
                strcpy(v_88, v_18->sub_197550(0, 0));
                break;
            case 96:
            case 97:
                v_18 = sub_198800(&unk_4B9004);
                strcpy(v_88, v_18->sub_197550(0, 0));
                break;
            case 51:
            case 52:
            case 53:
            case 99:
            case 100:
                v_18 = sub_198800(&unk_4B900C);
                strcpy(v_88, v_18->sub_197550(0, 0));
                break;
            case 102:
            case 103:
                v_18 = sub_198800(&unk_4B9014);
                strcpy(v_88, v_18->sub_197550(0, 0));
                break;
            case 105:
            case 106:
                v_18 = sub_198800(&unk_4B9044);
                strcpy(v_88, v_18->sub_197550(0, 0));
                break;
            case 63:
            case 64:
            case 65:
                v_18 = sub_198800(&unk_4B903C);
                strcpy(v_88, v_18->sub_197550(0, 0));
                break;
            case 48:
            case 49:
            case 50:
                v_18 = sub_198800(&unk_4B9034);
                strcpy(v_88, v_18->sub_197550(0, 0));
                break;
            case 54:
            case 55:
            case 56:
                v_18 = sub_198800(&unk_4B904C);
                strcpy(v_88, v_18->sub_197550(0, 0));
                break;
            case 57:
            case 58:
            case 59:
                v_18 = sub_198800(&unk_4B9024);
                strcpy(v_88, v_18->sub_197550(0, 0));
                break;
            case 60:
            case 61:
            case 62:
                v_18 = sub_198800(&unk_4B902C);
                strcpy(v_88, v_18->sub_197550(0, 0));
                break;
            case 78:
            case 79:
                v_18 = sub_198800(&unk_4B9054);
                strcpy(v_88, v_18->sub_197550(0, 0));
                break;
            case 80:
            case 81:
                v_18 = sub_198800(&unk_4B905C);
                strcpy(v_88, v_18->sub_197550(0, 0));
                break;
            case 82:
            case 83:
                v_18 = sub_198800(&unk_4B9064);
                strcpy(v_88, v_18->sub_197550(0, 0));
                break;
            case 84:
            case 85:
                v_18 = sub_198800(&unk_4B906C);
                strcpy(v_88, v_18->sub_197550(0, 0));
                break;
            case 86:
            case 87:
                v_18 = sub_198800(&unk_4B9074);
                strcpy(v_88, v_18->sub_197550(0, 0));
                break;
            case 88:
            case 89:
                v_18 = sub_198800(&unk_4B907C);
                strcpy(v_88, v_18->sub_197550(0, 0));
                break;
            case 108:
            {
                RwInt32 v_AC;

                v_18 = sub_198800(&unk_4B908C);
                strcpy(v_88, v_18->sub_197550(0, 0));
                sub_6B5F0("PickedUpKaiserBear", 0, 0, (RwInt32)vf_098(), &v_AC, 1, true, false);
                break;
            }
            case 109:
            {
                RwInt32 v_B0;

                v_18 = sub_198800(&unk_4B9094);
                strcpy(v_88, v_18->sub_197550(0, 0));
                sub_6B5F0("PickedUpStickyBear", 0, 0, (RwInt32)vf_098(), &v_B0, 1, true, false);
                break;
            }
            }
        }
        else
        {
            type_3DF8D8_04 v_B8;
            type_3DF8D8_04 *v_BC;

            v_B8.unk_00 = 0x5F20A5E7; // not an address: a key
            v_B8.unk_04 = 0xCC486714; // not an address: a key
            v_BC = sub_17C630();
            if (!v_BC || (v_BC && v_BC->unk_00 != v_B8.unk_00))
            {
                sub_17C6C0(0);
                sub_17C500(&v_B8, 1, 1);
                dword_4B1E98.sub_8A980(&dword_4B1A18, 0, 0, (RwV3d *)vf_0C4(), 1, 0);
            }
            v_20 = 0;
        }
        if (v_20)
        {
            RwInt32 v_C0;

            v_C0 = unk_21B4.sub_1159C0(arg_0);
            sub_115390(unk_1A48[unk_1AE4]->unk_414, unk_1A48[unk_1AE4]->unk_418);
            if (v_C0 != -1)
            {
                type_4C09B0 *v_C4;
                PickupTrigger *v_CC;

                if (v_88[0])
                    sub_EACA0(v_88, 0, 0);
                v_C4 = sub_FB6C0(arg_0->unk_3B0.sub_FB710());
                if (v_C4->unk_1C.unk_00)
                    unk_1C0.sub_8A980(&v_C4->unk_1C, this, 1, sub_CD550(), 0, 0);
                v_CC = (PickupTrigger *)arg_0->unk_344.get_unk_08();
                if (v_CC)
                    v_CC->sub_A9910();
                sub_D5A60(arg_0, 0);
                sub_10F7E0(11, 0);
                unk_2240 = 0;
            }
            else
            {
                type_3DF8D8_04 v_D4;
                type_3DF8D8_04 *v_D8;

                v_D4.unk_00 = 0x2B312134; // not an address: a key
                v_D4.unk_04 = 0xB4335C07; // not an address: a key
                v_D8 = sub_17C630();
                if (!v_D8 || (v_D8 && v_D8->unk_00 != v_D4.unk_00))
                {
                    sub_17C6C0(0);
                    sub_17C500(&v_D4, 1, 1);
                    dword_4B1E98.sub_8A980(&dword_4B1A18, 0, 0, (RwV3d *)vf_0C4(), 1, 0);
                }
            }
        }
    }
    else
    {
        if (sub_10F710() == 12 || sub_10F710() == 18 || v_1C)
        {
            if (!v_28)
            {
                type_4C09B0 *v_E0;
                PickupTrigger *v_180;

                switch (arg_0->unk_3B0.sub_FB710())
                {
                case 2:
                    if (v_1C)
                        v_18 = sub_198800(&unk_4B8FB4);
                    else
                        v_18 = sub_198800(&unk_4B909C);
                    sub_EACA0(v_18->sub_197550(0, 0), 0, 0);
                    v_10 = 8;
                    break;
                case 4:
                    if (v_1C)
                        v_18 = sub_198800(&unk_4B8FAC);
                    else
                        v_18 = sub_198800(&unk_4B90A4);
                    sub_EACA0(v_18->sub_197550(0, 0), 0, 0);
                    v_10 = 11;
                    break;
                case 5:
                    if (v_1C)
                        v_18 = sub_198800(&unk_4B8FBC);
                    else
                        v_18 = sub_198800(&unk_4B90AC);
                    sub_EACA0(v_18->sub_197550(0, 0), 0, 0);
                    v_10 = 10;
                    break;
                case 3:
                    if (v_1C)
                        v_18 = sub_198800(&unk_4B8FC4);
                    else
                        v_18 = sub_198800(&unk_4B90B4);
                    sub_EACA0(v_18->sub_197550(0, 0), 0, 0);
                    v_10 = 7;
                    break;
                case 6:
                    if (v_1C)
                        v_18 = sub_198800(&unk_4B8FCC);
                    else
                        v_18 = sub_198800(&unk_4B90BC);
                    sub_EACA0(v_18->sub_197550(0, 0), 0, 0);
                    v_10 = 9;
                    break;
                case 7:
                    if (v_1C)
                        v_18 = sub_198800(&unk_4B8FD4);
                    else
                        v_18 = sub_198800(&unk_4B90C4);
                    sub_EACA0(v_18->sub_197550(0, 0), 0, 0);
                    v_10 = 2;
                    break;
                case 8:
                    if (v_1C)
                        v_18 = sub_198800(&unk_4B8FDC);
                    else
                        v_18 = sub_198800(&unk_4B90CC);
                    sub_EACA0(v_18->sub_197550(0, 0), 0, 0);
                    v_10 = 4;
                    break;
                case 9:
                    if (v_1C)
                        v_18 = sub_198800(&unk_4B8FE4);
                    else
                        v_18 = sub_198800(&unk_4B90D4);
                    sub_EACA0(v_18->sub_197550(0, 0), 0, 0);
                    v_10 = 6;
                    break;
                case 10:
                    if (v_1C)
                        v_18 = sub_198800(&unk_4B8FEC);
                    else
                        v_18 = sub_198800(&unk_4B90DC);
                    sub_EACA0(v_18->sub_197550(0, 0), 0, 0);
                    v_10 = 3;
                    break;
                case 11:
                    if (v_1C)
                        v_18 = sub_198800(&unk_4B8FF4);
                    else
                        v_18 = sub_198800(&unk_4B90E4);
                    sub_EACA0(v_18->sub_197550(0, 0), 0, 0);
                    v_10 = 5;
                    break;
                case 12:
                    if (v_1C)
                        v_18 = sub_198800(&unk_4B9034);
                    else
                        v_18 = sub_198800(&unk_4B90EC);
                    sub_EACA0(v_18->sub_197550(0, 0), 0, 0);
                    v_10 = 14;
                    break;
                case 14:
                    if (v_1C)
                        v_18 = sub_198800(&unk_4B904C);
                    else
                        v_18 = sub_198800(&unk_4B90FC);
                    sub_EACA0(v_18->sub_197550(0, 0), 0, 0);
                    v_10 = 15;
                    break;
                case 15:
                    if (v_1C)
                        v_18 = sub_198800(&unk_4B9024);
                    else
                        v_18 = sub_198800(&unk_4B9104);
                    sub_EACA0(v_18->sub_197550(0, 0), 0, 0);
                    v_10 = 18;
                    break;
                case 16:
                    if (v_1C)
                        v_18 = sub_198800(&unk_4B902C);
                    else
                        v_18 = sub_198800(&unk_4B910C);
                    sub_EACA0(v_18->sub_197550(0, 0), 0, 0);
                    v_10 = 0;
                    break;
                case 17:
                    if (v_1C)
                        v_18 = sub_198800(&unk_4B903C);
                    else
                        v_18 = sub_198800(&unk_4B9114);
                    sub_EACA0(v_18->sub_197550(0, 0), 0, 0);
                    v_10 = 1;
                    break;
                case 92:
                    if (v_1C)
                        v_18 = sub_198800(&unk_4B8FFC);
                    else
                        v_18 = sub_198800(&unk_4B911C);
                    sub_EACA0(v_18->sub_197550(0, 0), 0, 0);
                    v_10 = 12;
                    break;
                case 95:
                    if (v_1C)
                        v_18 = sub_198800(&unk_4B9004);
                    else
                        v_18 = sub_198800(&unk_4B9124);
                    sub_EACA0(v_18->sub_197550(0, 0), 0, 0);
                    v_10 = 13;
                    break;
                case 13:
                case 98:
                    if (v_1C)
                        v_18 = sub_198800(&unk_4B900C);
                    else
                        v_18 = sub_198800(&unk_4B90F4);
                    sub_EACA0(v_18->sub_197550(0, 0), 0, 0);
                    v_10 = 16;
                    break;
                case 104:
                    if (v_1C)
                        v_18 = sub_198800(&unk_4B9044);
                    else
                        v_18 = sub_198800(&unk_4B912C);
                    sub_EACA0(v_18->sub_197550(0, 0), 0, 0);
                    v_10 = 37;
                    break;
                case 101:
                    if (v_1C)
                        v_18 = sub_198800(&unk_4B9014);
                    else
                        v_18 = sub_198800(&unk_4B9134);
                    sub_EACA0(v_18->sub_197550(0, 0), 0, 0);
                    v_10 = 17;
                    break;
                default:
                    v_10 = -1;
                }
                v_E0 = sub_FB6C0(arg_0->unk_3B0.sub_FB710());
                if (v_E0->unk_1C.unk_00)
                    unk_1C0.sub_8A980(&v_E0->unk_1C, this, 1, sub_CD550(), 0, 0);
                if (v_10 != -1)
                {
                    if (v_10 != unk_1AE4)
                    {
                        bool v_E1;
                        RwInt32 v_E8;

                        v_E1 = false;
                        v_E8 = unk_1AE8 == 0;
                        if (v_10 == unk_1B30[v_E8])
                            v_E1 = true;
                        if (!v_E1)
                        {
                            if (unk_1B30[v_E8] == -1)
                            {
                                unk_1B30[v_E8] = v_10;
                                unk_1A48[v_10]->vf_008(this, unk_1A3C.get_unk_08(), v_10);
                                sub_100200(unk_1B30[unk_1AE8 == 0]);
                            }
                            else if (unk_1B30[unk_1AE8] == -1)
                            {
                                unk_1B30[unk_1AE8] = v_10;
                                unk_1A48[v_10]->vf_008(this, unk_1A3C.get_unk_08(), v_10);
                            }
                            else
                            {
                                RwInt32 v_F4;
                                type_4C19C0 *v_150;
                                RwInt32 v_154;
                                RwInt32 v_158;

                                v_F4 = sub_1064C0(unk_1B30[unk_1AE8]);
                                if (v_F4 != -1)
                                {
                                    RwMatrix *v_FC;
                                    RwMatrix v_140;

                                    v_FC = RwFrameGetMatrix(arg_0->unk_338.get_unk_08());
                                    v_140 = *RwFrameGetMatrix(unk_338.get_unk_08());
                                    v_140.pos.x = v_FC->pos.x;
                                    v_140.pos.z = v_FC->pos.z;
                                    v_144 = unk_1A48[unk_1B30[unk_1AE8]]->unk_414;
                                    unk_1A48[unk_1B30[unk_1AE8]]->unk_414 = 0;
                                    sub_FABC0(v_F4, v_144, &v_140, 1.0f, 1, 0);
                                }
                                if (unk_1A48[unk_1AE4]->unk_21C)
                                {
                                    unk_1C0.sub_8A910(unk_1A48[unk_1AE4]->unk_21C);
                                    unk_1A48[unk_1AE4]->unk_21C = 0;
                                }
                                if (unk_1A48[unk_1AE4]->unk_46)
                                {
                                    unk_1C0.sub_8A910(unk_1A48[unk_1AE4]->unk_21C);
                                    unk_1A48[unk_1AE4]->unk_21C = 0;
                                    unk_1C0.sub_8A980(&unk_1A48[unk_1AE4]->get_unk_448()->unk_14, this, 1, sub_CD550(),
                                                      0, 0);
                                    unk_1A48[unk_1AE4]->unk_46 = 0;
                                }
                                unk_1A48[unk_1AE4]->sub_117370();
                                unk_1B30[unk_1AE8] = v_10;
                                unk_1AE4 = v_10;
                                unk_1A48[unk_1AE4]->vf_008(this, unk_1A3C.get_unk_08(), unk_1AE4);
                                v_150 = unk_1A48[unk_1AE4]->unk_448;
                                if (sub_77B70(v_150->unk_38, &v_158, &v_154))
                                {
                                    unk_284->sub_794C0(0.0f);
                                    unk_284->sub_796A0((RtAnimAnimation *)v_158, v_150->unk_38, 0,
                                                       (struct type_783F0 *)v_154, 0.0f, 1.0f, 1.0f);
                                    unk_1A48[unk_1AE4]->unk_224 = 3;
                                }
                            }
                            v_144 = arg_0->unk_3B0.unk_04;
                            unk_1A48[unk_1B30[unk_1AE8]]->unk_414 = v_144;
                            if ((RwUInt32)unk_1A48[unk_1B30[unk_1AE8]]->unk_414 >
                                unk_1A48[unk_1B30[unk_1AE8]]->get_unk_448()->unk_C8)
                            {
                                v_144 = unk_1A48[unk_1B30[unk_1AE8]]->unk_414 -
                                        unk_1A48[unk_1B30[unk_1AE8]]->get_unk_448()->unk_C8;
                                unk_1A48[unk_1B30[unk_1AE8]]->unk_414 =
                                    unk_1A48[unk_1B30[unk_1AE8]]->get_unk_448()->unk_C8;
                            }
                            else
                                v_144 = 0;
                            unk_1A48[v_10]->unk_418 = unk_1A48[v_10]->unk_418 + v_144;
                            sub_108B60();
                            unk_2134 = sub_10E930();
                        }
                        else
                        {
                            unk_1A48[unk_1B30[v_E8]]->unk_418 =
                                unk_1A48[unk_1B30[v_E8]]->unk_418 + arg_0->unk_3B0.unk_04;
                            if ((RwUInt32)unk_1A48[unk_1B30[v_E8]]->unk_418 >
                                unk_1A48[unk_1B30[v_E8]]->get_unk_448()->unk_CC)
                                unk_1A48[unk_1B30[v_E8]]->unk_418 = unk_1A48[unk_1B30[v_E8]]->get_unk_448()->unk_CC;
                        }
                    }
                    else
                    {
                        unk_1A48[unk_1AE4]->unk_418 = unk_1A48[unk_1AE4]->unk_418 + arg_0->unk_3B0.unk_04;
                        if ((RwUInt32)unk_1A48[unk_1AE4]->unk_418 > unk_1A48[unk_1AE4]->get_unk_448()->unk_CC)
                            unk_1A48[unk_1AE4]->unk_418 = unk_1A48[unk_1AE4]->get_unk_448()->unk_CC;
                        if (!unk_1A48[unk_1AE4]->unk_414 && !unk_1A48[unk_1AE4]->unk_12)
                            unk_1A48[unk_1AE4]->vf_020();
                        sub_115390(unk_1A48[unk_1AE4]->unk_414, unk_1A48[unk_1AE4]->unk_418);
                        dword_4B9190->sub_E07A0(unk_1A48[unk_1AE4]->unk_414,
                                                unk_1A48[unk_1AE4]->get_unk_448()->unk_C8);
                    }
                }
                v_180 = (PickupTrigger *)arg_0->unk_344.get_unk_08();
                if (v_180)
                    v_180->sub_A9910();
                sub_D5A60(arg_0, 0);
                sub_10F7E0(12, 0);
                unk_2240 = 0;
            }
            else
            {
                type_3DF8D8_04 v_188;
                type_3DF8D8_04 *v_18C;

                v_188.unk_00 = 0x5F20A5E7; // not an address: a key
                v_188.unk_04 = 0xCC486714; // not an address: a key
                v_18C = sub_17C630();
                if (!v_18C || (v_18C && v_18C->unk_00 != v_188.unk_00))
                {
                    sub_17C6C0(0);
                    sub_17C500(&v_188, 1, 1);
                    dword_4B1E98.sub_8A980(&dword_4B1A18, 0, 0, (RwV3d *)vf_0C4(), 1, 0);
                }
                v_20 = 0;
            }
        }
        sub_10F7E0(11, 0);
    }
}

