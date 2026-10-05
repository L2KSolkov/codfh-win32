// Starts a game as the host: the session described (the player's name, over
// the internet or not, no address, the port, the level, the game type and
// its settings, the player count and the voice setting) and created, then
// waited for while it starts (the leave passed on with the interface still
// drawn). Once it runs, this machine is not a client: the game data takes
// the front end's settings (the scores only without a time limit) with the
// level arg_0, the players arg_4, and the live service is told.
// match: ?sub_1A9A70@type_4F7EB8@@QAEXHHPBD_N@Z @ 0x001A9A70
void type_4F7EB8::sub_1A9A70(RwInt32 arg_0, RwInt32 arg_4, const RwChar *arg_8, bool arg_C)
{
    type_4FB9E0_08 var_40;
    RwInt32 var_44;
    RwInt32 var_48;
    RwInt32 var_4C;
    RwInt32 var_50;
    type_1CC1F0 var_6C;

    var_50 = 0;
    var_4C = 0;
    var_48 = 0;
    var_44 = 0;
    unk_4F7E9C.sub_1CB790();
    var_6C.unk_05[0] = (RwUInt8)var_50;
    var_6C.unk_05[1] = (RwUInt8)var_4C;
    var_6C.unk_05[2] = (RwUInt8)var_48;
    var_6C.unk_05[3] = (RwUInt8)var_44;
    var_6C.unk_0A = unk_4F61F8.unk_100;
    var_6C.unk_10 = (RwUInt8)arg_0;
    var_6C.unk_13 = (RwUInt8)arg_4;
    var_6C.unk_00 = dword_4F28F0->unk_183;
    var_6C.unk_0C = arg_8;
    var_6C.unk_04 = arg_C;
    var_6C.unk_11 = (RwUInt8)unk_4FDBB0.unk_00;
    var_6C.unk_12 = (RwUInt8)unk_4FDBB0.unk_04;
    var_6C.unk_14 = (RwUInt8)unk_4FDBB0.unk_0C;
    var_6C.unk_15 = (RwUInt8)unk_4FDBB0.unk_10;
    sub_227560()->sub_227870();
    var_6C.unk_16 = (RwUInt8)dword_4FDAA4;
    unk_19C->vf_05C(&var_6C);
    while (unk_19C->get_unk_04() == 1)
    {
        sub_1AF750(sub_1CCA10(), 1, 0);
        if (dword_4F7E98)
            kujuUI::sub_1F77D0(dword_4F7E98, true);
    }
    if (unk_19C->get_unk_04() == 2)
    {
        unk_4F61F8.unk_104 = 0;
        var_40.sub_1B46F0();
        var_40.unk_00 = unk_4FDBB0.unk_00;
        var_40.unk_10 = unk_4FDBB0.unk_10;
        var_40.unk_04 = unk_4FDBB0.unk_04;
        var_40.unk_24 = unk_4FDBB0.unk_24;
        var_40.unk_1C = unk_4FDBB0.unk_1C;
        var_40.unk_2C = unk_4FDBB0.unk_2C;
        if (!var_40.unk_04)
        {
            var_40.unk_14 = unk_4FDBB0.unk_14;
            var_40.unk_18 = unk_4FDBB0.unk_18;
        }
        else
        {
            var_40.unk_14 = 0;
            var_40.unk_18 = 0;
        }
        var_40.unk_08 = unk_4FDBB0.unk_08;
        var_40.unk_0C = unk_4FDBB0.unk_0C;
        var_40.unk_20 = unk_4FDBB0.unk_20;
        var_40.unk_30 = 0;
        var_40.unk_28 = arg_0;
        dword_4FB9E0.pDtor();
        dword_4FB9E0.sub_1B55D0(var_40);
        dword_4FB9E0.sub_1B57A0();
        dword_4FB9E0.sub_1B54B0(arg_0);
        unk_4FC = 0;
        sub_227560()->sub_2283F0(1);
        unk_298 = 1;
    }
}

