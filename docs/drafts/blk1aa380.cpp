// match: ?updateVoiceSubSystem@type_4F7EB8@@QAEXXZ @ 0x001AA380
void type_4F7EB8::updateVoiceSubSystem()
{
    // The locals' names state their slots (docs/toolchain.md).
    type_1DDE20_mask lcl_14C;
    type_1DDE20_mask lv_120;
    type_1DDE20_mask bp_4;
    RwInt32 lv_144 = 4;
    RwInt32 x8 = 1;
    type_1CCA10 m_D4 = 0;
    type_1CCA10 ebp_140 = 0;
    RwInt32 v130 = sub_1AEC70();
    RwUInt32 locC;
    RwUInt32 r148;
    RwV3d lD0[16];
    RwReal bp_118[16];
    RwV3d s13C;
    RwReal stk_11C;
    type_4F7EB8_1F0 *o124;
    RwReal loc128;
    RwInt32 slot_12C;

    lv_120 = unk_19C->get_unk_B0()->sub_1A8050();
    if (unk_2A4)
    {
        for (locC = 0; locC < 16; locC++)
        {
            if (lv_120.test(locC) && unk_1F0[locC])
            {
                lv_120.clear(locC);
            }
        }
    }
    else if (dword_4FB9E0.get_unk_08() == 1)
    {
        for (locC = 0; locC < 16; locC++)
        {
            if (lv_120.test(locC) && !unk_1F0[locC])
            {
                lv_120.clear(locC);
            }
        }
    }
    else
    {
        for (locC = 0; locC < 16; locC++)
        {
            if (lv_120.test(locC))
            {
                if (unk_29C == 2 && unk_3D0.sub_1C2A90(locC) == 4 || unk_29C == 4 && unk_3D0.sub_1C2A90(locC) == 2
                    || unk_29C == 1 || !unk_1F0[locC])
                {
                    lv_120.clear(locC);
                }
            }
        }
    }
    if (sub_1D8810()->get_unk_2918() == 4)
    {
        if (!unk_2C8->get_unk_08())
        {
            unk_2C8->sub_1C62B0();
        }
        unk_4F7E90 = type_1DDE20_mask(lv_120);
        lcl_14C = unk_19C->get_unk_B0()->get_unk_0C();
        for (locC = 0; locC < 16; locC++)
        {
            if (locC == v130)
            {
                if (unk_1A4)
                {
                    lD0[locC] = *(RwV3d *)unk_1A4->vf_0C4();
                }
                else
                {
                    lD0[locC].x = 0;
                    lD0[locC].y = 0;
                    lD0[locC].z = 0;
                }
            }
            else
            {
                o124 = unk_1F0[locC];
                if (o124 && lcl_14C.test(locC))
                {
                    lD0[locC] = *(RwV3d *)o124->vf_0C4();
                }
                else
                {
                    if (o124)
                    {
                        if (0)
                        {
                            sub_1C8A30("cNetController::updateVoiceSubSystem() Player %d is not in player set but remote player\n", locC);
                        }
                        if (0)
                        {
                            sub_1C8A30(" is not NULL.  If you get a lot of these messages then something may be wrong somewhere\n");
                        }
                    }
                    lD0[locC].x = 0;
                    lD0[locC].y = 0;
                    lD0[locC].z = 0;
                }
            }
        }
        for (locC = 0; locC < 16; locC++)
        {
            for (r148 = 0; r148 < 16; r148++)
            {
                if (locC != r148 && lcl_14C.test(locC) && lcl_14C.test(r148))
                {
                    RwV3dSubMacro(&s13C, &lD0[r148], &lD0[locC]);
                    stk_11C = RwV3dDotProductMacro(&s13C, &s13C);
                    get_unk_2C8()->unk_14.unk_2234[locC][r148] = stk_11C;
                    if (locC == v130)
                    {
                        bp_118[r148] = stk_11C;
                    }
                }
            }
        }
        m_D4 = unk_19C->get_unk_7C();
        ebp_140 = m_D4 - unk_528;
        if (ebp_140 > type_1CCA10(2000))
        {
            unk_528 = m_D4;
            lcl_14C = lv_120;
            while (lv_144 && x8)
            {
                x8 = 0;
                loc128 = flt_3E13B0;
                for (locC = 0; locC < 16; locC++)
                {
                    if (lcl_14C.test(locC) && !bp_4.test(locC) && bp_118[locC] < loc128)
                    {
                        loc128 = bp_118[locC];
                        slot_12C = locC;
                        x8 = 1;
                    }
                }
                if (x8)
                {
                    lcl_14C.unk_00 &= ~(1 << slot_12C);
                    bp_4.unk_00 |= 1 << slot_12C;
                    lv_144--;
                }
            }
            unk_2C8->sub_1C6440(bp_4);
        }
    }
}

