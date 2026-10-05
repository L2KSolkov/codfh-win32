// match: ?sub_1C2600@type_4F8288@@QAEXHH@Z @ 0x001C2600
// match: __ehhandler$?sub_1C2600@type_4F8288@@QAEXHH@Z-0x21 @ 0x00302FC0
// match: __ehhandler$?sub_1C2600@type_4F8288@@QAEXHH@Z @ 0x00302FE1
// Player arg_0 takes the team arg_4: unless it has it, the console says so
// ("MW_GEN_JOINDM" in deathmatch, else "MW_GEN_JOINRED" or "MW_GEN_JOINBLUE",
// with its name).
void type_4F8288::sub_1C2600(RwInt32 arg_0, RwInt32 arg_4)
{
    RwChar var_114[0x100];

    // Two compiled-out checks (docs/toolchain.md).
    if (!unk_00[0].unk_00)
    {
    }
    if (!unk_00[0].unk_00)
    {
    }
    if (arg_4 != unk_00[arg_0].unk_00)
    {
        if (dword_4FB9E0.get_unk_08() == 1)
            sub_1CB000(var_114, sub_E3970("MW_GEN_JOINDM", 1).c_str(),
                       type_4F8054::get()->get_unk_B0()->unk_90[arg_0].unk_00);
        else if (arg_4 == 4)
            sub_1CB000(var_114, sub_E3970("MW_GEN_JOINRED", 1).c_str(),
                       type_4F8054::get()->get_unk_B0()->unk_90[arg_0].unk_00);
        else
            sub_1CB000(var_114, sub_E3970("MW_GEN_JOINBLUE", 1).c_str(),
                       type_4F8054::get()->get_unk_B0()->unk_90[arg_0].unk_00);
        sub_EACA0(var_114, 0, 0);
    }
    set_team(this, arg_0, arg_4);
}

