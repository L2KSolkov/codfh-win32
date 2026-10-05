// Parked 2026-09-28: type_4F8288::sub_1C2600 (unit_1C2440). Code matches
// with the two checks; the frame is 8 bytes too big: ours has two dead
// slots between the first branch's temporaries (-0x178) and the second's
// (image -0x17C). The image's dead groups after the branches are 0, 4, 4;
// ours 2, 4, 4. Tried: `4 == arg_4`, a nested else block, the direct
// game-type getter, no checks. Needs includes game/loc.h, types/type_DC400.h.

// match: ?sub_1C2600@type_4F8288@@QAEXHH@Z @ 0x001C2600
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
    unk_00[arg_0].unk_00 = arg_4;
    unk_00[arg_0].unk_08 = 1;
}

