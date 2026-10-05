// match: ?sub_1A4B40@type_4F6A7C@@QAEXHHHPAURwV3d@@H@Z @ 0x001A4B40
// match: __ehhandler$?sub_1A4B40@type_4F6A7C@@QAEXHHHPAURwV3d@@H@Z-0x58 @ 0x003028C0
// match: __ehhandler$?sub_1A4B40@type_4F6A7C@@QAEXHHHPAURwV3d@@H@Z @ 0x00302918
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
// The flag arg_0's state arg_4 (0 at home, 1 carried, 2 dropped) through
// the player arg_8 (-1: none), dropped at arg_C: with both bases set, the
// homes swapped for four teams (else put back); the carrier's flag state
// (vf_05C) and the flag put at its home or where it was dropped; unless
// arg_10, the change's text ("MW_CTF_..." with the player's name) on the
// HUD; then the state kept and the base's objective markers updated.
void type_4F6A7C::sub_1A4B40(RwInt32 arg_0, RwInt32 arg_4, RwInt32 arg_8, RwV3d *arg_C, RwInt32 arg_10)
{
    RwChar loc11C[0x100];
    type_3D3548 *m_18;
    type_3D3548 *ebp_14;
    RwInt32 lv_10;

    lv_10 = 0;
    if (unk_00[0].unk_04 && unk_00[1].unk_04)
    {
        if (dword_4FB9E0.get_unk_10C())
            sub_1A4A90();
        else
            sub_1A4B00();
    }
    switch (arg_4)
    {
    case 0:
        if (arg_8 != -1)
        {
            ebp_14 = unk_4F7EB8.sub_1AECA0(arg_8, 1);
            if (ebp_14)
                ebp_14->vf_05C();
        }
        sub_1A5C40(arg_0, &unk_00[arg_0].unk_0C);
        break;
    case 1:
        break;
    case 2:
        if (arg_8 != -1)
        {
            m_18 = unk_4F7EB8.sub_1AECA0(arg_8, 1);
            if (m_18)
                m_18->vf_05C();
        }
        if (!arg_C || ABS_REAL(arg_C->x) < 0.001f && ABS_REAL(arg_C->y) < 0.001f && ABS_REAL(arg_C->z) < 0.001f)
            sub_1A5C40(arg_0, &unk_00[arg_0].unk_0C);
        else
            sub_1A5C40(arg_0, arg_C);
        break;
    default:
        return;
    }
    if (!arg_10 && arg_4 != unk_00[arg_0].unk_00)
    {
        if (arg_8 == -1)
        {
            if (arg_0 == 0)
            {
                switch (arg_4)
                {
                case 0:
                    strcpy(loc11C, sub_E3970("MW_CTF_RETURNBLUE_AUTO", 1).c_str());
                }
            }
            else
            {
                switch (arg_4)
                {
                case 0:
                    strcpy(loc11C, sub_E3970("MW_CTF_RETURNRED_AUTO", 1).c_str());
                }
            }
        }
        else if (arg_0 == 0)
        {
            switch (arg_4)
            {
            case 0:
                if (dword_4F8288.sub_1C2A90(arg_8) == 2)
                    sub_1CB000(loc11C, sub_E3970("MW_CTF_RETURNBLUE", 1).c_str(),
                               type_4F8054::get()->get_unk_B0()->unk_90[arg_8].unk_00);
                else
                    sub_1CB000(loc11C, sub_E3970("MW_CTF_CAPBLUE", 1).c_str(),
                               type_4F8054::get()->get_unk_B0()->unk_90[arg_8].unk_00);
                break;
            case 1:
                sub_1CB000(loc11C, sub_E3970("MW_CTF_GOTBLUE", 1).c_str(),
                           type_4F8054::get()->get_unk_B0()->unk_90[arg_8].unk_00);
                break;
            case 2:
                sub_1CB000(loc11C, sub_E3970("MW_CTF_DROPBLUE", 1).c_str(),
                           type_4F8054::get()->get_unk_B0()->unk_90[arg_8].unk_00);
                break;
            }
        }
        else
        {
            switch (arg_4)
            {
            case 0:
                if (dword_4F8288.sub_1C2A90(arg_8) == 4)
                    sub_1CB000(loc11C, sub_E3970("MW_CTF_RETURNRED", 1).c_str(),
                               type_4F8054::get()->get_unk_B0()->unk_90[arg_8].unk_00);
                else
                    sub_1CB000(loc11C, sub_E3970("MW_CTF_CAPRED", 1).c_str(),
                               type_4F8054::get()->get_unk_B0()->unk_90[arg_8].unk_00);
                break;
            case 1:
                sub_1CB000(loc11C, sub_E3970("MW_CTF_GOTRED", 1).c_str(),
                           type_4F8054::get()->get_unk_B0()->unk_90[arg_8].unk_00);
                break;
            case 2:
                sub_1CB000(loc11C, sub_E3970("MW_CTF_DROPRED", 1).c_str(),
                           type_4F8054::get()->get_unk_B0()->unk_90[arg_8].unk_00);
                break;
            }
        }
        sub_EACA0(loc11C, 0, 0);
    }
    unk_00[arg_0].unk_00 = arg_4;
    if (!unk_00[arg_0].unk_04)
        return;
    sub_170790(&unk_00[arg_0].unk_04->unk_28, -2);
    switch (arg_4)
    {
    case 0:
        if (unk_38)
            sub_171070(flag_objective(this, arg_0), (type_712B0 *)unk_00[arg_0 ^ 1].unk_04);
        else
            sub_171070(flag_objective(this, arg_0), (type_712B0 *)unk_00[arg_0].unk_04);
        sub_171480(flag_objective(this, arg_0), 0);
        break;
    case 1:
        if (arg_8 != -1)
        {
            if (unk_4F7EB8.sub_1AECA0(arg_8, 0))
                sub_171110(flag_objective(this, arg_0), unk_4F7EB8.sub_1AECA0(arg_8, 0));
            else
                sub_171110(flag_objective(this, arg_0), unk_00[arg_0].unk_08);
            sub_171480(flag_objective(this, arg_0), 1);
        }
        break;
    case 2:
        if (unk_00[arg_0].unk_08)
        {
            sub_171110(flag_objective(this, arg_0), unk_00[arg_0].unk_08);
            unk_00[arg_0].unk_08->unk_28_4 = 1;
            unk_00[arg_0].unk_08->unk_28_5 = 1;
        }
        sub_171480(flag_objective(this, arg_0), 1);
        break;
    }
}
