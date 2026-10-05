// match: ?sub_21ADB0@type_21A5E0@@QAE_NXZ @ 0x0021ADB0
bool type_21A5E0::sub_21ADB0()
{
    unk_158[0] = this;
    unk_158[5] = new type_215F30("CurrentVotePlayer.layout", this);
    unk_158[6] = new type_215D40("CurrentVoteMap.layout", this);
    unk_158[7] = new type_215B40("CurrentVoteGame.layout", this);
    unk_158[8] = new type_2225E0("VoteOptions.layout", this);
    unk_158[9] = new type_222960("VotePlayer.layout", this);
    unk_158[0xA] = new type_222350("VoteMap.layout", this);
    unk_158[0xB] = new type_2220E0("VoteGame.layout", this);
    unk_158[0xC] = new type_221780("VoteConfirm.layout", this);
    unk_158[0xD] = new type_216D20("GameSettings.layout", this);
    unk_158[4] = new type_2179E0("HostOptions.layout", this);
    unk_158[0x11] = new type_2181E0("KickPlayer.layout", this);
    unk_158[0xF] = new type_219D10("NextRound.layout", this);
    unk_158[0x10] = new type_217CD0("OnlineSettings.layout", "OnlineSettingsAdvanced.layout", this);
    unk_158[0xE] = new type_21D0D0("QuitGame.layout", this);
    unk_158[2] = new type_220C40("TeamSelect.layout", this);
    unk_158[3] = new type_216760("Defect.layout", this);
    unk_158[0x12] = new type_221590("UseNow.layout", this);
    unk_158[0x13] = new type_21CB10("PleaseInsertController.layout", this, 0);
    unk_158[1] = new type_223280(0, this);
    unk_158[0x14] = new type_216440("DebugMenu.layout", this);
    unk_158[0x15] = new type_219010("LiveOptionsInGame.layout", this);
    unk_158[0x16] = new type_218F40(this);
    unk_158[0x17] = new type_219C20(this);
    sub_204FC0("resume", &unk_1B8);
    sub_204FC0("live", &unk_1C4);
    sub_204FC0("weapons", &unk_1D0);
    sub_204FC0("team", &unk_1DC);
    sub_204FC0("host", &unk_1EC);
    sub_204FC0("vote", &unk_1FC);
    sub_204FC0("settings", &unk_20C);
    sub_204FC0("quit", &unk_218);
    sub_204FC0("kill", &unk_230);
    sub_204FC0("debug", &unk_224);
    for (RwInt32 var_10 = 0; var_10 < 0x18; var_10++)
    {
        unk_154 = var_10;
        unk_158[var_10]->sub_20EA40();
        unk_158[var_10]->type_21CB10::vf_00C();
    }
    unk_154 = 0;
    return true;
}
