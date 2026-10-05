// Parked sub_1AB440, for src/recovered/unit_1A8B20.cpp.
// 2026-10-01: current headers already supply the old eight unused slots.
// Removing the eight unused_slot calls restores the original 0xB8 frame
// and every slot. First authoritative mismatch +0x29 is a branch size;
// the first instruction-shape mismatch is at 0x1AB7F8: MOV/PUSH instead
// of FLD/PUSH/FSTP [esp], followed by register rotation differences.
// Additional call-context trials: double-returning getter, float/double
// conversion operators, functional casts, double multiply/divide by one,
// and float/double/volatile-float forwarding inlines. FPU forms retain an
// extra rounding store/slot; none match. VC7.1 remains fixed.
// Reproduction scripts: build/tooltmp/view_state_context.py,
// view_state_conversion.py, view_state_call_context.py.

void type_4F7EB8::sub_1AB440()
{
    if (unk_2A4 != unk_2A8 && !unk_284)
    {
        // A compiled-out check (docs/toolchain.md): the registers after it
        // are one load on.
        if (!unk_4FC)
        {
        }
        switch (unk_2A8)
        {
        case 3:
            dword_4FB9E0.sub_1B6DE0(0);
            if (unk_1A4)
            {
                unk_4F6B00[get_1AEC70()].sub_1A6360();
                sub_D5A60(unk_1A4->unk_2110.sub_D4910(), 2);
                sub_D5A60(unk_1A4, 0);
                sub_D5D20(1);
                unk_1A4 = 0;
            }
            if (get_unk_19C())
            {
                type_1DDE20_mask mask = get_unk_19C()->get_unk_B0()->sub_1A8050();
                type_3E0F84 m;
                m.unk_04 = 1;
                get_unk_1A0()->sub_1DDDB0(&m, mask);
            }
            unk_278->sub_1BE9B0();
            unk_230 = -1;
            sub_1AB200();
            sub_1AF7E0();
            unk_2A8 = 3;
            sub_124EE0(0.5f, 0);
            set_hud_unk_90();
            break;
        case 0:
            if (unk_1A8)
            {
                sub_D5A60(unk_1A8->unk_2110.sub_D4910(), 2);
                sub_D5A60(unk_1A8, 0);
                sub_D5D20(1);
                if (unk_230 != -1)
                {
                    // A compiled-out check (docs/toolchain.md): the registers after it
                    // are one load on.
                    if (!unk_4FC)
                    {
                    }
                    unk_4F6B00[unk_230].sub_1A63E0();
                    unk_230 = -1;
                }
                unk_1A8 = 0;
            }
            if (unk_2A4 == 4 && unk_1AC)
            {
                if (0)
                {
                    sub_1C8A30("Remove LOCAL KILLCAM PLAYER\n");
                }
                unk_4F6B00[get_1AEC70()].pDtor();
                sub_D5A60(unk_1AC->unk_2110.sub_D4910(), 2);
                sub_D5A60(unk_1AC, 0);
                sub_D5D20(1);
            }
            if (get_unk_19C())
            {
                type_1DDE20_mask mask = get_unk_19C()->get_unk_B0()->sub_1A8050();
                type_3E0F84 m;
                m.unk_04 = 0;
                get_unk_1A0()->sub_1DDDB0(&m, mask);
            }
            sub_1AED30();
            break;
        case 1:
            if (unk_2A4 != 3)
            {
                dword_4FB9E0.sub_1B6DE0(dword_4FB9E0.unk_08.unk_2C);
                if (unk_1A4)
                {
                    unk_4F6B00[get_1AEC70()].sub_1A6360();
                    sub_D5A60(unk_1A4->unk_2110.sub_D4910(), 2);
                    sub_D5A60(unk_1A4, 0);
                    sub_D5D20(1);
                    unk_1A4 = 0;
                }
                if (get_unk_19C())
                {
                    type_1DDE20_mask mask = get_unk_19C()->get_unk_B0()->sub_1A8050();
                    type_3E0F84 m;
                    m.unk_04 = 1;
                    get_unk_1A0()->sub_1DDDB0(&m, mask);
                }
                unk_278->sub_1BE9B0();
                unk_230 = -1;
                sub_1AB200();
                sub_124EE0(0.5f, 0);
                set_hud_unk_90();
            }
            break;
        case 2:
            if (unk_2A4 != 1 && unk_2A4 != 3)
            {
                sub_19A750("Going into Static Spectate from %d\n", unk_2A4);
                if (unk_2A4 == 4 && unk_1AC)
                {
                    sub_19A750("Removing Killcam Stuff\n");
                    unk_4F6B00[get_1AEC70()].pDtor();
                    sub_D5A60(unk_1AC->unk_2110.sub_D4910(), 2);
                    sub_D5A60(unk_1AC, 0);
                    sub_D5D20(1);
                }
                if (unk_1A4)
                {
                    unk_4F6B00[get_1AEC70()].sub_1A6360();
                    sub_D5A60(unk_1A4->unk_2110.sub_D4910(), 2);
                    sub_D5A60(unk_1A4, 0);
                    sub_D5D20(1);
                    unk_1A4 = 0;
                }
                if (get_unk_19C())
                {
                    type_1DDE20_mask mask = get_unk_19C()->get_unk_B0()->sub_1A8050();
                    type_3E0F84 m;
                    m.unk_04 = 1;
                    get_unk_1A0()->sub_1DDDB0(&m, mask);
                }
                unk_278->sub_1BE9B0();
                unk_230 = -1;
                sub_1AF7E0();
            }
            else
            {
                unk_4F7EB8.sub_1AB2C0();
            }
            unk_2A8 = 1;
            sub_124EE0(0.5f, 0);
            set_hud_unk_90();
        }
        unk_2A4 = unk_2A8;
    }
}
