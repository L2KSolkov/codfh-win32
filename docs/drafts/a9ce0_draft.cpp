// Joins the game arg_0 at the host arg_4 (voice with arg_C): the session
// told (vf_060) and this machine a client, then the join waited for while
// its state is neither 7 (joined) nor 8 (refused), with the interface drawn
// and fed its events and the join's state shown ("WAITING_JOIN_BEGIN" and
// on). An error ends it with the session's reason in *arg_8 (10 when
// refused) and false; once joined the game type and the players' limit (4,
// 8 or 16) are the host's, and the manager starts.
// match: ?sub_1A9CE0@type_4F7EB8@@QAE_NPBUtype_1CC1F0@@PBUtype_1CC3C0@@PAH_N@Z @ 0x001A9CE0
bool type_4F7EB8::sub_1A9CE0(const type_1CC1F0 *arg_0, const type_1CC3C0 *arg_4, RwInt32 *arg_8, bool arg_C)
{
    dword_4FB9E0.sub_1B57C0();
    if (0)
    {
        off_42CD14("name : %s, ip : %d.%d.%d.%d - port %d, number players %d/%d\n", arg_4->unk_10,
                   arg_4->unk_04[0], arg_4->unk_04[1], arg_4->unk_04[2], arg_4->unk_04[3], arg_4->unk_08,
                   arg_4->unk_29, arg_4->unk_2A);
    }
    sub_227560()->sub_227870();
    unk_19C->vf_060(arg_0, arg_4, arg_C);
    unk_4F61F8.unk_104 = 1;
    kujuUI::type_1E7560 var_11C;
    kujuUI::type_1EE900 var_128;
    kujuUI::type_1E3DB0 *var_10 = dword_5043B4;

    while (unk_19C->get_unk_B0()->get_unk_310() != 7 && unk_19C->get_unk_B0()->get_unk_310() != 8)
    {
        if (dword_4F7E98)
        {
            unk_4B9308.sub_EE6D0();
            kujuUI::type_3E7D08 *var_12C = kujuUI::sub_1F7760();

            if (var_10)
            {
                if (var_10->sub_2015D0())
                {
                    kujuUI::type_1EE900 var_138 = var_10->sub_1E3DD0();

                    var_138.sub_1EE940(&var_128, &var_11C);
                    var_128 = var_138;
                }
                while (var_11C.sub_1E75F0())
                {
                    var_12C->processEvent(var_11C.sub_1E7610());
                }
            }
            kujuUI::sub_1F77D0(dword_4F7E98, true);
        }
        sub_1AF750(sub_1CCA10(), 1, 0);
        if (unk_19C->get_unk_10())
        {
            if (arg_8)
                *arg_8 = unk_19C->get_unk_14();
            unk_19C->sub_1CC120();
            return false;
        }
        switch (unk_19C->get_unk_B0()->get_unk_310_direct())
        {
        case 0:
            static_cast<std::string &>(unk_4F7E9C) = type_1A5EA0("WAITING_JOIN_BEGIN", 0);
            break;
        case 2:
            static_cast<std::string &>(unk_4F7E9C) = type_1A5EA0("WAITING_DETAILS_ACK", 0);
            break;
        case 3:
            static_cast<std::string &>(unk_4F7E9C) = type_1A5EA0("WAITING_PEER_DETAILS", 0);
            break;
        case 4:
        case 5:
            static_cast<std::string &>(unk_4F7E9C) = type_1A5EA0("WAITING_PEER_CONNECTIONS", 0);
            break;
        case 6:
            static_cast<std::string &>(unk_4F7E9C) = type_1A5EA0("WAITING_JOIN_DONE", 0);
            break;
        default:
            unk_4F7E9C.sub_1CB790();
            break;
        }
    }
    if (unk_19C->get_unk_B0()->get_unk_310() == 8)
    {
        if (arg_8)
            *arg_8 = 10;
        return false;
    }
    dword_4FB9E0.set_game_type(arg_4->unk_2B);
    switch (arg_4->unk_2A)
    {
    case 4:
        dword_4F6300 = 1;
        break;
    case 8:
        dword_4F6300 = 2;
        break;
    case 16:
        dword_4F6300 = 4;
        break;
    default:
        dword_4F6300 = 4;
        break;
    }
    unk_29C = 1;
    unk_2BC = 1;
    unk_298 = 1;
    unk_4FC = 0;
    return true;
}

