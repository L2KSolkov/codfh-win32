// The HUD's update over the frame's time arg_0. With a player: its health
// fade (sub_DFE00) and stance (sub_E0340); in a network game the items of
// the game type (the bomb's time, the round's clock, the CTF icons by team,
// the flag carrier's blink, the scores), the letterbox modes (unk_90 1 and
// 2: the spectator's texts, the console's messages every 5000 frames), the
// items' layout and scales, the crosshair's spread and the buddy's bar.
// Then the name labels (timed, green, or red for enemies, fading with the
// distance), the items' timed fades (unk_2C) and fades to a target alpha
// (unk_30), the radar, the vehicle's turret and heading, the player's mode
// icon, the screen flash, the damage markers turning to face their hits,
// and the in-game screens (unk_1A4B0).
// match: ?sub_DD1C0@type_DC400@@QAEXM@Z @ 0x000DD1C0
// match: __ehhandler$?sub_DD1C0@type_DC400@@QAEXM@Z-0x8 @ 0x00300DE0
// match: __ehhandler$?sub_DD1C0@type_DC400@@QAEXM@Z @ 0x00300DE8
void type_DC400::sub_DD1C0(RwReal arg_0)
{
    type_10F710 *v_1C;
    RwInt32 v_24;
    RwInt32 v_28;
    RwInt32 v_114;
    type_3D3548 *v_118;
    RwInt32 v_148;
    type_3DBC78 *v_15C;
    RwCamera *v_21C;
    RwMatrix *v_220;
    RwInt32 v_224;

    v_1C = (type_10F710 *)sub_1745A0(0);
    if (v_1C)
    {
        sub_DFE00(v_1C->vf_17C());
        sub_E0340(v_1C->vf_0BC());
        if (type_4F8054::get() && unk_4F7EB8.sub_1AF670())
        {
            v_24 = unk_4F7EB8.sub_1AEC70();
            v_28 = dword_4F8288.sub_1C2A90(v_24);
            sub_E09E0(0x55, 0);
            sub_E09E0(4, 1);
            sub_E09E0(0xA, 1);
            sub_E09E0(0xE, 1);
            sub_E09E0(0x1D, 1);
            sub_E09E0(7, 1);
            if (unk_4F8184.sub_1A86E0(v_24))
            {
                sub_E09E0(0x94, 1);
                sub_E0080(((type_17DBD0_player *)v_1C)->unk_2290 / 4.0f);
            }
            else
            {
                sub_E09E0(0x94, 0);
            }
            if (dword_4FB9E0.sub_1B6E50())
            {
                sub_E09E0(0x42, 1);
                sub_E0110(dword_4FB9E0.sub_1B6E80());
            }
            else if (0.0f != dword_4FB9E0.unk_08.unk_14)
            {
                sub_E09E0(0x42, 1);
                sub_E0110(dword_4FB9E0.sub_1B6DA0());
            }
            else
            {
                sub_E09E0(0x42, 0);
            }
            if (v_28 == 2)
            {
                unk_E0[73].unk_110 = unk_98[unk_4F7EB8.sub_1AF2F0(2)];
                unk_E0[75].unk_110 = unk_A8[unk_4F7EB8.sub_1AF2F0(2)];
                unk_E0[78].unk_110 = unk_98[unk_4F7EB8.sub_1AF2F0(4)];
                unk_E0[80].unk_110 = unk_A8[unk_4F7EB8.sub_1AF2F0(4)];
            }
            else
            {
                unk_E0[73].unk_110 = unk_98[unk_4F7EB8.sub_1AF2F0(4)];
                unk_E0[75].unk_110 = unk_A8[unk_4F7EB8.sub_1AF2F0(4)];
                unk_E0[78].unk_110 = unk_98[unk_4F7EB8.sub_1AF2F0(2)];
                unk_E0[80].unk_110 = unk_A8[unk_4F7EB8.sub_1AF2F0(2)];
            }
            dword_4B9190->sub_E7050(0x50, (RwUInt32)Width * flt_4293F8, (RwUInt32)Height * flt_4293FC);
            sub_E09E0(0x51, 0);
            sub_E09E0(0x4B, 0);
            sub_E09E0(0x4C, 0);
            if (unk_4F823C.sub_1B2480(v_24))
            {
                unk_E0[80].unk_2B8 += arg_0 * 16.666666f;
                if (unk_E0[80].unk_2B8 >= 500.0f)
                {
                    unk_E0[80].unk_2B8 = 0;
                    unk_E0[80].unk_50 = !unk_E0[80].unk_50;
                }
            }
            else
            {
                sub_E09E0(0x50, 0);
            }
            switch (dword_4FB9E0.get_game_type())
            {
            case 2:
                sub_E09E0(0x4B, 0);
                sub_E09E0(0x4C, 0);
                sub_E09E0(0x50, 0);
                sub_E09E0(0x51, 0);
                sub_E09E0(0x54, 0);
                sub_E09E0(0x45, 0);
                sub_E09E0(0x47, 1);
                sub_E09E0(0x52, 0);
                if (v_28 == 2)
                {
                    sub_E0280(unk_4F7EBC.sub_1B33C0(2));
                    sub_E02E0(unk_4F7EBC.sub_1B33C0(4));
                }
                else
                {
                    sub_E0280(unk_4F7EBC.sub_1B33C0(4));
                    sub_E02E0(unk_4F7EBC.sub_1B33C0(2));
                }
                break;
            case 4:
                sub_E09E0(0x45, 0);
                sub_E09E0(0x47, 1);
                sub_E09E0(0x52, 0);
                sub_E09E0(0x54, 0);
                if (v_28 == 2)
                {
                    sub_E0280(unk_4F7EBC.sub_1B33C0(2));
                    sub_E02E0(unk_4F7EBC.sub_1B33C0(4));
                }
                else
                {
                    sub_E0280(unk_4F7EBC.sub_1B33C0(4));
                    sub_E02E0(unk_4F7EBC.sub_1B33C0(2));
                }
                break;
            case 8:
                sub_E09E0(0x4B, 0);
                sub_E09E0(0x4C, 0);
                sub_E09E0(0x50, 0);
                sub_E09E0(0x51, 0);
                sub_E09E0(0x54, 0);
                if (v_28 == 2)
                {
                    sub_E0280(unk_4F7EBC.sub_1B33C0(2));
                    sub_E02E0(unk_4F7EBC.sub_1B33C0(4));
                }
                else
                {
                    sub_E0280(unk_4F7EBC.sub_1B33C0(4));
                    sub_E02E0(unk_4F7EBC.sub_1B33C0(2));
                }
                sub_E09E0(0x52, 1);
                sub_E09E0(0x45, 0);
                sub_E09E0(0x47, 0);
                break;
            case 1:
                sub_E0220(unk_4F7EBC.sub_1B3360(v_24));
                sub_E09E0(0x45, 1);
                sub_E09E0(0x47, 0);
                sub_E09E0(0x52, 0);
                break;
            }
        }
        if (unk_90 == 1)
        {
            if (type_4F8054::get() && unk_4F7EB8.sub_1AF670())
            {
                sub_E09E0(0x55, 1);
                if (dword_4FB9E0.sub_1B6E50() || byte_4B8974 || (sub_1FF250() && sub_1FF250()->sub_200740()))
                {
                    sub_E09E0(0x58, 0);
                }
                else
                {
                    sub_E09E0(0x58, 1);
                }
                if (dword_4FB9E0.sub_1CA260())
                {
                    if (dword_4F62FC)
                    {
                        sub_E7380(0x58, unk_4B8A74.c_str());
                    }
                    else
                    {
                        sub_E7380(0x58, unk_4B8A90.c_str());
                    }
                }
                else
                {
                    sub_E7380(0x58, unk_4B8B04.c_str());
                }
                sub_E09E0(4, 0);
                sub_E09E0(0xA, 0);
                sub_E09E0(0xE, 0);
                sub_E09E0(0x1D, 0);
                sub_DEB80(3);
                sub_E09E0(0x45, 0);
                sub_E09E0(0x47, 0);
                sub_E09E0(0x52, 0);
                sub_E09E0(0x54, 0);
                sub_E09E0(7, 0);
                if (unk_94 != (dword_4F8060 ? dword_4F80E8 : -1))
                {
                    unk_94 = dword_4F8060 ? dword_4F80E8 : -1;
                }
                if (sub_1FF250() && !sub_1FF250()->sub_200740())
                {
                    if (unk_94 == -1)
                    {
                        sub_E7380(0x59, sub_1C5350().c_str());
                    }
                    else
                    {
                        RwChar v_110[0x80];

                        sub_1CB000(v_110, unk_4B8B20.c_str(),
                                   type_4F8054::get()->get_unk_B0()->unk_90[unk_94].unk_00);
                        sub_E7380(0x59, v_110);
                    }
                    sub_E09E0(0x59, 1);
                }
                else
                {
                    sub_E09E0(0x59, 0);
                }
            }
        }
        else if (unk_90 == 2)
        {
            sub_E09E0(0x55, 1);
            sub_E09E0(0x54, 1);
            sub_E09E0(0x42, 1);
            sub_E09E0(0x52, 1);
            sub_E0080(1.0f);
            flt_4B8B3C += arg_0 * 16.666666f;
            if (flt_4B8B3C > 5000.0f)
            {
                sub_EACA0("Console initialized -- Standard Message", 0, 0);
                sub_EACA0("Console initialized -- High Level Message", 1, 0);
                sub_EACA0("Console initialized -- Low Level Message", 2, 0);
                flt_4B8B3C = 0;
            }
        }
        sub_E09E0(0x14, 0);
        sub_E6610(&unk_E0[0]);
        if (v_1C->unk_1A0C)
        {
            sub_E6270(0xB, unk_1A154.x, unk_1A154.y);
            sub_E6270(0xC, unk_1A154.x, unk_1A154.y);
            sub_E6270(0xD, unk_1A154.x, unk_1A154.y);
        }
        else
        {
            sub_E6270(0xB, unk_1A14C.x, unk_1A14C.y);
            sub_E6270(0xC, unk_1A14C.x, unk_1A14C.y);
            sub_E6270(0xD, unk_1A14C.x, unk_1A14C.y);
        }
        if (unk_90 != 1 && v_1C->unk_1A48[v_1C->unk_1AE4])
        {
            sub_E08B0(v_1C->unk_1A48[v_1C->unk_1AE4]->sub_11D690());
        }
        sub_DFFC0(v_1C->unk_2104);
    }
    for (v_114 = 0; v_114 < 16; v_114++)
    {
        v_118 = unk_1A1A8[v_114].unk_28.sub_D4910();
        strcpy(unk_1A1A8[v_114].unk_00, pResourcePath);
        if (unk_1A1A8[v_114].unk_24 && v_118)
        {
            unk_1A1A8[v_114].unk_20 += deltaTime;
            if (unk_1A1A8[v_114].unk_20 > flt_4B915C)
            {
                unk_1A1A8[v_114].unk_24 = 0;
            }
            else
            {
                RwRGBAReal v_128;
                type_10F710 *v_134;

                v_128.red = 0;
                v_128.green = 0.75f;
                v_128.blue = 0;
                if (sub_1745A0(0) && ((type_10F710 *)sub_1745A0(0))->vf_24C(v_118))
                {
                    v_128.red = 0.75f;
                    v_128.green = 0;
                    v_128.blue = 0;
                }
                v_128.alpha = 1.0f;
                if (unk_1A1A8[v_114].unk_20 > flt_4B9160)
                {
                    RwReal v_130;

                    v_130 = unk_1A1A8[v_114].unk_20 - flt_4B9160;
                    v_128.alpha = 1.0f - v_130 / (flt_4B915C - flt_4B9160);
                }
                v_134 = (type_10F710 *)sub_1745A0(0);
                if (v_134)
                {
                    RwReal *v_138;
                    RwReal *v_13C;
                    RwReal v_140;

                    v_138 = v_134->vf_0C4();
                    v_13C = v_118->vf_0C4();
                    v_140 = (v_138[0] - v_13C[0]) * (v_138[0] - v_13C[0])
                        + (v_138[1] - v_13C[1]) * (v_138[1] - v_13C[1])
                        + (v_138[2] - v_13C[2]) * (v_138[2] - v_13C[2]);
                    if (v_140 > flt_4B9164)
                    {
                        RwReal v_144;

                        v_144 = 1.0f - (v_140 - flt_4B9164) / (flt_4B9168 - flt_4B9164);
                        if (v_144 < 0.0f)
                        {
                            v_144 = 0;
                        }
                        v_128.alpha *= v_144;
                    }
                }
                sub_E7480(unk_1A1A8[v_114].unk_2C, &v_128);
            }
        }
    }
    for (v_148 = 0; v_148 < 151; v_148++)
    {
        if (unk_E0[v_148].unk_20)
        {
            if (unk_E0[v_148].unk_44 && !unk_04)
            {
                if (unk_E0[v_148].unk_28)
                {
                    unk_E0[v_148].unk_2C = dword_4B8F1C;
                    sub_E3B90(v_148, flt_4B8F18);
                    unk_E0[v_148].unk_28 = 0;
                }
                else if (unk_E0[v_148].unk_2C > 0.0f)
                {
                    if (arg_0 >= unk_E0[v_148].unk_2C)
                    {
                        unk_E0[v_148].unk_2C = 0;
                    }
                    else
                    {
                        unk_E0[v_148].unk_2C -= 16.666666f * arg_0;
                    }
                }
                else if (unk_E0[v_148].unk_30 == -1)
                {
                    RwReal v_14C;
                    RwReal v_150;

                    v_14C = flt_4B8F14;
                    v_150 = arg_0 / 100.0f;
                    if (unk_E0[v_148].unk_24 != v_14C)
                    {
                        if (unk_E0[v_148].unk_24 - v_150 < v_14C)
                        {
                            sub_E3B90(v_148, v_14C);
                            unk_E0[v_148].unk_30 = 0;
                        }
                        else
                        {
                            sub_E3B90(v_148, unk_E0[v_148].unk_24 - v_150);
                        }
                    }
                }
                else if (unk_E0[v_148].unk_30 == 1)
                {
                    RwReal v_154;
                    RwReal v_158;

                    v_154 = flt_4B8F18;
                    v_158 = arg_0 / 100.0f;
                    if (unk_E0[v_148].unk_24 != v_154)
                    {
                        if (v_158 + unk_E0[v_148].unk_24 > v_154)
                        {
                            sub_E3B90(v_148, v_154);
                            unk_E0[v_148].unk_30 = 0;
                        }
                        else
                        {
                            sub_E3B90(v_148, v_158 + unk_E0[v_148].unk_24);
                        }
                    }
                }
            }
            sub_E3B90(v_148, flt_4B8F18);
            sub_E3B90(0x49, unk_5C);
            sub_E3B90(0x4E, unk_5C);
        }
    }
    if (unk_E0[29].unk_20)
    {
        sub_E4030(arg_0);
    }
    if (unk_E0[90].unk_20)
    {
        sub_DEF40(arg_0);
    }
    if (unk_08)
    {
        v_15C = (type_3DBC78 *)unk_1A034.sub_D4910();
        if (!v_15C)
        {
            sub_E0CC0();
        }
        else
        {
            RwInt32 v_160;
            RwInt32 v_164;
            RwInt32 v_168;

            v_160 = 0;
            v_164 = 0;
            v_168 = 0;
            switch (unk_1A030)
            {
            case 1:
                v_160 = 100;
                v_164 = 101;
                break;
            case 2:
                break;
            case 3:
                break;
            default:
                v_160 = v_164 = v_168 = -1;
                break;
            }
            if (v_160 >= 0 && v_164 >= 0 && unk_E0[v_160].unk_20 && unk_E0[v_164].unk_20)
            {
                RwReal v_170;
                RpClump *v_174;
                RwMatrix v_1C0;
                RwReal v_1C4;
                RwReal v_1C8;
                RwReal v_1D0;
                RwMatrix v_210;

                v_170 = dword_4B8EF0.unk_00;
                v_174 = v_15C->unk_25C.unk_08;
                sub_EC2D0(v_174, (RwInt32)&v_1C0, 0x41464952, 0, 1); // not an address: 'RIFA'
                v_1C4 = v_1C0.at.x;
                v_1C8 = v_1C0.right.x;
                v_1D0 = ((RwReal)atan2(v_1C8, v_1C4)) * 57.295776f;
                v_170 = sub_13F9E0(v_170);
                unk_1A038 = sub_13F9E0(v_1D0 - v_170);
                v_210 = v_15C->unk_7B0.unk_170;
                v_1D0 = ((RwReal)atan2(v_210.right.x, v_210.at.x)) * 57.295776f;
                v_170 = sub_13F9E0(v_170);
                unk_1A03C = sub_13F9E0(v_1D0 - v_170);
                sub_E5F60(v_164, unk_1A03C - unk_1A038);
            }
            if (v_15C)
            {
                // Two checks compiled out of this build: the registers of
                // the calls after them are two steps on (docs/toolchain.md).
                if (unk_00)
                {
                }
                if (unk_00)
                {
                }
                sub_E0A70(v_15C->vf_17C());
                sub_E0A90(v_15C->vf_250());
            }
        }
    }
    if (!unk_04 && v_1C)
    {
        sub_E06E0(-1);
        switch (v_1C->sub_10F790())
        {
        case 1:
            sub_E0410(8);
            break;
        case 2:
            sub_E0410(9);
            break;
        case 15:
            sub_E0410(1);
            break;
        case 19:
            sub_E0410(0);
            break;
        case 7:
            sub_E0410(4);
            break;
        case 11:
            sub_E0410(5);
            break;
        case 9:
            if (!unk_C0)
            {
                sub_E0410(5);
            }
            break;
        case 12:
            sub_E0410(6);
            break;
        case 5:
            sub_E0410(0xB);
            break;
        case 10:
            sub_E0410(0xA);
            break;
        case 14:
            sub_E0410(3);
            break;
        case 17:
            sub_E0410(0xC);
            break;
        default:
            sub_E0410(0);
            break;
        }
    }
    if (!unk_04 && unk_1A0A8)
    {
        unk_1A0C4 = (unk_1A0C0_f - unk_1A0AC) / unk_1A0C0_f * unk_1A0BC;
        unk_1A0AC += arg_0 * 16.666666f * 0.001f;
        if (unk_1A0AC > unk_1A0C0_f)
        {
            unk_1A0C4 = 0;
            unk_1A0AC = 0;
            unk_1A0A8 = 0;
        }
    }
    if (!unk_04)
    {
        v_21C = (RwCamera *)dword_4E5C74;
        v_220 = RwFrameGetMatrix(RwCameraGetFrame(v_21C));
        for (v_224 = 0; v_224 < 5; v_224++)
        {
            if (unk_1A0D4[v_224].unk_10)
            {
                unk_1A0D4[v_224].unk_0C -= arg_0 * 16.666666f;
                if (unk_1A0D4[v_224].unk_0C <= 0.0f)
                {
                    unk_1A0D4[v_224].unk_10 = 0;
                    unk_1A0D4[v_224].unk_00.z = 0;
                    unk_1A0D4[v_224].unk_00.y = 0;
                    unk_1A0D4[v_224].unk_00.x = 0;
                    unk_1A0D4[v_224].unk_0C = 0;
                    unk_1A0D4[v_224].unk_14.sub_D48D0(0);
                    sub_E09E0(v_224 + 0x8B, 0);
                    // The original jumps from here straight to the loop's
                    // step.
                    continue;
                }
                RwV3d v_230;
                RwReal v_234;

                v_230 = v_220->at;
                v_230.y = 0;
                unk_1A0D4[v_224].unk_00.y = 0;
                RwV3dNormalize(&v_230, &v_230);
                RwV3dNormalize(&unk_1A0D4[v_224].unk_00, &unk_1A0D4[v_224].unk_00);
                sub_E5F60(v_224 + 0x8B, -(v_234 = sub_141240(&v_220->at, &unk_1A0D4[v_224].unk_00) + 180.0f));
                sub_E3B90(v_224 + 0x8B, unk_1A0D4[v_224].unk_0C / dword_4B9154);
            }
        }
    }
    sub_E74D0(2, (RwV2d *)&unk_4B8F90);
    unk_1A4B0->sub_2003E0(arg_0 / flt_3CD8DC);
}
