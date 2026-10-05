// PARKED sub_1C5350 (2026-10-01). Trial: put this after sub_1C5340 in
// unit_1C3D20.cpp with type_DC400.h's declaration changed to
// `struct type_1CB670 sub_1C5350();` (PSCORE_INC overlay). Code identical; the
// frame is 0x120 against the image's 0x140.
// - Without the two no-code inline calls at the end, VC7.1 declines the fifth
//   type_1A5EA0(const RwChar *) conversion ("_SCORE%s"); one call is not
//   enough; two or more (anywhere after it) expand all five. Removing code
//   after it declines more: the decision is not a front-to-back budget.
// - Each extra call shrinks the frame (fewer attempted _Tidy leftovers); 0x138
//   is the largest frame with the fifth declined, 0x130 with all expanded.
// - Four unused_slot() calls before `if (bp_D)` give 0x140, but their named
//   locals sort above the bp_D block's temporary (0xE8 in the image, 0xF8).
//   After a return (dead code) they count for nothing.
// - inline_depth pragmas, getter forms, empty checks and the temporary's type
//   (type_1CB670 vs type_1A5EA0) change nothing here.

// Follow-up: explicit empty derived destructors, c_str/append wrappers and
// visible localization constructors did not close the gap. A diagnostic
// forced char constructor expanded unwanted std::string bodies; suppressing
// those expansions in an SDK-header overlay still left an 0x138 frame.
// Neither compiler flags nor SDK headers were changed in production.
// Current-header reproductions: build/tooltmp/hint_context_*.py.

inline void nop_()
{
}

type_1CB670 sub_1C5350()
{
    bool bp_D = false;
    type_1A5EA0 stk_30("HINT_");

    stk_30.sub_1C84F0(sub_1A3CB0(dword_4FB9E0.get_unk_08()));
    if (dword_4FB9E0.get_unk_08() == 8)
    {
        bool ebp_35 = false;
        RwInt32 local_34 = sub_1C4880(unk_4F7EB8.sub_1AEC70());

        if (local_34 == 1)
            local_34 = sub_1C43A0();
        if (local_34 == dword_4FB9E0.get_team_count())
            ebp_35 = true;
        if (ebp_35)
            stk_30.sub_1C84F0("_ATTACK");
        else
            stk_30.sub_1C84F0("_DEFEND");
    }
    else if ((RwUInt32)unk_4FDBB0.unk_18 > 0)
    {
        stk_30.sub_1C84F0("_SCORE%s");
        bp_D = true;
    }
    if (bp_D)
    {
        RwChar v44[0xC];

        sprintf(v44, "%d", unk_4FDBB0.unk_18);
        return sub_1CB7B0(type_1A5EA0(stk_30.c_str(), 1).c_str(), v44, 0);
    }
    nop_();
    nop_();
    return type_1CB670(stk_30.c_str(), 1);
}
