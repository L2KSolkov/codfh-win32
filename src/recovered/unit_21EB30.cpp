/*
 * The scoreboards' base (game/ingamepages.h): its flags loaded and dropped,
 * the side shown swapped by the pad and the texts refreshed as the players
 * change, and its constructor (with the flags' default constructor closure,
 * sub_21EFC0), its texts (sub_21F1C0) and its showing (vf_008, 0x21FB60).
 */
#include <string.h>
#include "game/ingamepages.h"
#include "game/data.h"
#include "game/uiglue.h"
#include "game/gameloop.h"
#include "game/mpgame.h"
#include "types/type_DC400.h"
#include "types/type_505188.h"

// Its data definitions (PLAN M5), in the image's address order.
#ifndef CODFH_SP // MP only: unreferenced constants single player does not emit (not in default.xbe; /O2 keeps them only while they are external)
// 0x003EA524
extern const RwReal flt_3EA524 = 0.01f;
// 0x003EA528
extern const RwReal flt_3EA528 = 0.01f;
// 0x003EA52C
extern const RwReal flt_3EA52C = 16.666666f;
#endif
// 0x005051DC
RwInt32 dword_5051DC[3];
// End of its data definitions.


using namespace kujuUI;

// The team count, without a receiver temporary; no address, named for
// what it returns. Evidence: sub_21FB60's result and subsequent win-side
// accessors occupy 0x1E4/0x1E8/0x1FC. A member inline shifts all three by
// eight bytes through its attempted receiver expansion (docs/toolchain.md).
inline RwInt32 scoreboard_team_count()
{
    if (dword_4FB9E0.unk_10C)
        return 4;
    return 2;
}


// Built over the layout arg_8 in the pause menu arg_C: by teams when arg_0 is
// set, arg_4 kept in unk_154; its widgets registered by name (the teams'
// flags, names and round scores only by teams, the round scores cleared in
// game type 4) and its layout loaded.
// Its data (PLAN M5): literals, constants and tables where the image has them.
// match: ?flt_3EA524@@3MB @ 0x003EA524
// match: ?flt_3EA528@@3MB @ 0x003EA528
// match: ?flt_3EA52C@@3MB @ 0x003EA52C
// match: ??_C@_0BA@IKPNEJMA@RightRoundScore?$AA@ @ 0x003EA530
// match: ??_C@_0P@FOKGKEHN@LeftRoundScore?$AA@ @ 0x003EA540
// match: ??_C@_0O@DKPKNKAJ@RightTeamName?$AA@ @ 0x003EA550
// match: ??_C@_0N@DCEMKHAD@LeftTeamName?$AA@ @ 0x003EA560
// match: ??_C@_09GGHKKLNB@RightFlag?$AA@ @ 0x003EA570
// match: ??_C@_08EGEDKLA@LeftFlag?$AA@ @ 0x003EA57C
// match: ??_C@_0P@GGIBHPFP@BestPlayerText?$AA@ @ 0x003EA588
// match: ??_C@_0BA@DOIIGFGA@AboveCentreText?$AA@ @ 0x003EA598
// match: ??_C@_0L@KDLDIPFO@CentreText?$AA@ @ 0x003EA5A8
// match: ??_C@_0L@JPDKGGID@HeaderText?$AA@ @ 0x003EA5B4
// match: ??_C@_0BA@BKLCOCIH@RightRoundTotal?$AA@ @ 0x003EA5C0
// match: ??_C@_0P@MOOJAPDK@LeftRoundTotal?$AA@ @ 0x003EA5D0
// match: ??_C@_0L@CJABBFDH@rightnames?$AA@ @ 0x003EA5E0
// match: ??_C@_09NKBHNGGP@leftnames?$AA@ @ 0x003EA5EC
// match: ??_7type_21EB30@@6B@ @ 0x003EA5F8
// match: ??_C@_08PEIEJNJM@?5?5?5?5?5?5?$CFd?$AA@ @ 0x003EA648
// match: ??_C@_0BF@LOPALNNE@NEXT_SCOREBOARD_PAGE?$AA@ @ 0x003EA654
// match: ??_C@_0BF@GOEGOII@PREV_SCOREBOARD_PAGE?$AA@ @ 0x003EA66C
// match: ??_C@_0O@HFABCLKJ@score_axiswin?$AA@ @ 0x003EA684
// match: ??_C@_0BA@FMDMNHFI@score_allieswin?$AA@ @ 0x003EA694
// match: ??_C@_0O@GEADMPFB@score_?$CF1_wins?$AA@ @ 0x003EA6A4
// match: ??_C@_06FLEPPNOI@RANKED?$AA@ @ 0x003EA6B4
// match: ??_C@_05DBKDOICH@score?$AA@ @ 0x003EA6BC
// match: ??_C@_09JEDEOOOO@w_flagsDE?$AA@ @ 0x003EA6C4
// match: ??_C@_09MGFNCDHN@w_flagsRU?$AA@ @ 0x003EA6D0
// match: ??_C@_09JFEIJCHO@w_flagsUS?$AA@ @ 0x003EA6DC
// match: ??_C@_09NJDDMGHA@w_flagsGB?$AA@ @ 0x003EA6E8
// match: ??_7?$type_3E7CE8@Utype_21EB30@@@kujuUI@@6B@ @ 0x003EA6F4
// match: __ehhandler$??0type_21EB30@@QAE@_NHPBDPAUtype_21A5E0@@@Z>1>8 @ 0x00425414
// match: __ehhandler$??0type_21EB30@@QAE@_NHPBDPAUtype_21A5E0@@@Z>1 @ 0x004254BC
// match: __ehhandler$??_F?$type_E8780@Utype_1ECCE0@kujuUI@@@@QAEXXZ>1>8 @ 0x004254D8
// match: __ehhandler$??_F?$type_E8780@Utype_1ECCE0@kujuUI@@@@QAEXXZ>1 @ 0x004254E0
// match: __ehhandler$??1type_21EB30@@UAE@XZ>1>8 @ 0x004254FC
// match: __ehhandler$??1type_21EB30@@UAE@XZ>1 @ 0x00425594
// match: __ehhandler$?sub_21F1C0@type_21EB30@@QAEXXZ>1>8 @ 0x004255B0
// match: __ehhandler$?sub_21F1C0@type_21EB30@@QAEXXZ>1 @ 0x00425610
// match: __ehhandler$?vf_008@type_21EB30@@UAEXXZ>1>8 @ 0x0042562C
// match: __ehhandler$?vf_008@type_21EB30@@UAEXXZ>1 @ 0x004256A4
// match: __ehhandler$?sub_2203E0@type_21EB30@@QAEXXZ>1>8 @ 0x004256C0
// match: __ehhandler$?sub_2203E0@type_21EB30@@QAEXXZ>1 @ 0x004256D8
// match: ?off_42D2B8@?1??sub_2203E0@type_21EB30@@QAEXXZ@4PAPBDA @ 0x0042D2B8
// match: ?off_42D2C4@?1??sub_2203E0@type_21EB30@@QAEXXZ@4PAPBDA @ 0x0042D2C4

// match: ??0type_21EB30@@QAE@_NHPBDPAUtype_21A5E0@@@Z @ 0x0021EB30
// match: __ehhandler$??0type_21EB30@@QAE@_NHPBDPAUtype_21A5E0@@@Z-0x11E @ 0x00308280
// match: __ehhandler$??0type_21EB30@@QAE@_NHPBDPAUtype_21A5E0@@@Z @ 0x0030839E
// match: ??_F?$type_E8780@Utype_1ECCE0@kujuUI@@@@QAEXXZ @ 0x0021EFC0
// match: __ehhandler$??_F?$type_E8780@Utype_1ECCE0@kujuUI@@@@QAEXXZ-0x8 @ 0x003083B0
// match: __ehhandler$??_F?$type_E8780@Utype_1ECCE0@kujuUI@@@@QAEXXZ @ 0x003083B8

type_21EB30::type_21EB30(bool arg_0, RwInt32 arg_4, const RwChar *arg_8, type_21A5E0 *arg_C)
    : type_21CB10(arg_8, arg_C, 0), unk_154(arg_4), unk_158(this, &type_21EB30::sub_220A80), unk_39C(arg_0),
      unk_39D(false), unk_3A0(1), unk_3A4(1)
{
    RwInt32 lv_10;

    for (lv_10 = 0; lv_10 < 2; lv_10++)
    {
        unk_174[lv_10] = 0;
        unk_17C[lv_10] = 0;
    }
    sub_204FC0("continue", &unk_158);
    sub_204FC0("leftnames", &unk_1D4);
    sub_204FC0("rightnames", &unk_1F0);
    sub_204FC0("LeftRoundTotal", &unk_25C);
    sub_204FC0("RightRoundTotal", &unk_284);
    sub_204FC0("HeaderText", &unk_2FC);
    sub_204FC0("CentreText", &unk_324);
    sub_204FC0("AboveCentreText", &unk_34C);
    sub_204FC0("BestPlayerText", &unk_374);
    if (get_unk_39C())
    {
        sub_204FC0("LeftFlag", &unk_164);
        sub_204FC0("RightFlag", &unk_16C);
        sub_204FC0("LeftTeamName", &unk_184);
        sub_204FC0("RightTeamName", &unk_1AC);
        sub_204FC0("LeftRoundScore", &unk_2AC);
        sub_204FC0("RightRoundScore", &unk_2D4);
        if (dword_4FB9E0.get_unk_08() == 4)
        {
            unk_2AC.sub_1F28C0(type_1CB670());
            unk_2D4.sub_1F28C0(type_1CB670());
        }
    }
    else
    {
        sub_204FC0("LeftFlag", &unk_164);
    }
    sub_20EA40();
}

// match: ??_Gtype_21EB30@@UAEPAXI@Z @ 0x0021EF90
// match: ??1type_21EB30@@UAE@XZ @ 0x0021F020
// match: __ehhandler$??1type_21EB30@@UAE@XZ-0x10E @ 0x003083D0
// match: __ehhandler$??1type_21EB30@@UAE@XZ @ 0x003084DE
type_21EB30::~type_21EB30()
{
    sub_220680();
}

// The texts: the players ranked by score, then deaths (the local player's
// rank into unk_3A4), into the two columns (by teams, each side's own,
// eight rows at most, the page turned by unk_39D when a side has more;
// else the first eight and the rest), and by teams the sides' names and
// round scores.
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
// match: ?sub_21F1C0@type_21EB30@@QAEXXZ @ 0x0021F1C0
// match: __ehhandler$?sub_21F1C0@type_21EB30@@QAEXXZ-0x7E @ 0x003084F0
// match: __ehhandler$?sub_21F1C0@type_21EB30@@QAEXXZ @ 0x0030856E
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void type_21EB30::sub_21F1C0()
{
    RwInt32 lv_10;

    {
        type_1A5EA0 slot_16C;
        RwInt32 slot_178;
        RwInt32 bp_174;
        type_21D7C0 *m_170;
        RwInt32 bp_150;
        RwInt32 fp_14C;
        RwInt32 loc148;
        RwInt32 p144;
        RwInt32 lcl_140;
        type_21F1C0_entry lv_13C[16];
        RwInt32 fp_78;
        RwInt32 frm_74;
        RwInt32 s70;
        RwInt32 m_6C;
        RwInt32 q68;
        RwInt32 lcl_64;
        RwInt32 fp_40;
        RwInt32 ebp_3C;
        RwInt32 local_38;
        RwInt32 local_34;

        lv_10 = sub_1C42F0();
        unk_3A4 = 1;
        ebp_3C = 0;
        lcl_140 = 2;
        fp_14C = 4;
        if (unk_3A0 == 4)
        {
            lcl_140 = 4;
            fp_14C = 2;
        }
        unk_1D4.sub_21D950();
        unk_1F0.sub_21D950();
        lcl_64 = 0;
        fp_78 = 0;
        for (local_34 = 0; local_34 < 16; local_34++)
        {
            if (sub_1C4630(local_34) && sub_1C4880(local_34) != 1)
            {
                p144 = sub_1C4800(local_34);
                s70 = sub_1C47A0(local_34);
                for (bp_174 = 0; bp_174 < ebp_3C; bp_174++)
                {
                    if (p144 > lv_13C[bp_174].unk_04
                        || (p144 == lv_13C[bp_174].unk_04 && s70 > lv_13C[bp_174].unk_08))
                        break;
                }
                if (bp_174 < ebp_3C)
                {
                    for (slot_178 = ebp_3C - 1; slot_178 >= bp_174; slot_178--)
                        lv_13C[slot_178 + 1] = lv_13C[slot_178];
                }
                if (get_unk_39C())
                {
                    if (sub_1C4880(local_34) == lcl_140)
                        lcl_64++;
                    else
                        fp_78++;
                }
                lv_13C[bp_174].unk_00 = local_34;
                lv_13C[bp_174].unk_04 = sub_1C4800(local_34);
                lv_13C[bp_174].unk_08 = sub_1C47A0(local_34);
                ebp_3C++;
            }
        }
        type_1CB670 frm_30("PREV_SCOREBOARD_PAGE", 0);
        type_1CB670 l60("NEXT_SCOREBOARD_PAGE", 0);
        type_1A5EA0 *loc44;

        if (!unk_39D)
            loc44 = &l60;
        else
            loc44 = &frm_30;
        unk_25C.sub_1F28C0(type_1CB670("", 0));
        unk_284.sub_1F28C0(type_1CB670("", 0));
        m_6C = 0;
        fp_40 = 0;
        local_38 = 0;
        if (lcl_64 > 8)
        {
            unk_25C.sub_1F28C0(*loc44);
            m_6C = lcl_64 - 8;
            fp_40 = 1;
        }
        else if (fp_78 > 8)
        {
            unk_284.sub_1F28C0(*loc44);
            m_6C = fp_78 - 8;
            local_38 = 1;
        }
        frm_74 = 1;
        q68 = 1;
        for (local_34 = 0; local_34 < ebp_3C; local_34++)
        {
            loc148 = lv_13C[local_34].unk_00;
            if (loc148 >= 0 && sub_1C4630(loc148))
            {
                if (loc148 == lv_10)
                    unk_3A4 = frm_74;
                if (local_34 + 1 < ebp_3C)
                {
                    if (lv_13C[local_34].unk_04 == lv_13C[local_34 + 1].unk_04
                        && lv_13C[local_34].unk_08 == lv_13C[local_34 + 1].unk_08)
                    {
                        q68++;
                    }
                    else
                    {
                        frm_74 += q68;
                        q68 = 1;
                    }
                }
                if (get_unk_39C())
                {
                    if (sub_1C4880(loc148) == lcl_140)
                    {
                        if (fp_40 && lcl_64 > m_6C && unk_39D)
                        {
                            lcl_64--;
                            continue;
                        }
                        if (unk_1D4.sub_1ECAF0() >= 8)
                            continue;
                        m_170 = &unk_1D4;
                    }
                    else
                    {
                        if (local_38 && fp_78 > m_6C && unk_39D)
                        {
                            fp_78--;
                            continue;
                        }
                        if (unk_1F0.sub_1ECAF0() >= 8)
                            continue;
                        m_170 = &unk_1F0;
                    }
                }
                else if (local_34 < 8)
                    m_170 = &unk_1D4;
                else
                    m_170 = &unk_1F0;
                if (m_170)
                {
                    slot_16C = sub_1C4630(loc148);
                    p144 = sub_1C4800(loc148);
                    s70 = sub_1C47A0(loc148);
                    bp_150 = sub_1C4840(loc148);
                    m_170->sub_21D9F0(loc148, slot_16C, p144, s70, bp_150);
                }
            }
        }
        if (get_unk_39C())
        {
            RwChar lv_20C[32];
            RwInt32 x198;
            type_1CB670 m_1D0("Allies", 0);
            type_1CB670 x1B4("Axis", 0);

            x198 = sub_1C47E0(lcl_140);
            sprintf(lv_20C, "      %d", x198);
            type_1CB670 lcl_1EC = sub_1CB720(lv_20C);
            x198 = sub_1C47E0(fp_14C);
            sprintf(lv_20C, "      %d", x198);
            type_1CB670 loc194 = sub_1CB720(lv_20C);
            unk_2AC.sub_1F28C0(type_1CB670("", 0));
            unk_2D4.sub_1F28C0(type_1CB670("", 0));
            switch (lcl_140)
            {
            case 2:
                m_1D0.sub_1C84F0(lcl_1EC);
                x1B4.sub_1C84F0(loc194);
                unk_184.sub_1F28C0(m_1D0);
                unk_1AC.sub_1F28C0(x1B4);
                break;
            default:
                x1B4.sub_1C84F0(lcl_1EC);
                m_1D0.sub_1C84F0(loc194);
                unk_184.sub_1F28C0(x1B4);
                unk_1AC.sub_1F28C0(m_1D0);
            }
            // Compiled-out diagnostics of the four texts: no code, but four
            // inline expansions the function's inline budget counts (its
            // frame, docs/toolchain.md).
            debug_text(m_1D0);
            debug_text(x1B4);
            debug_text(lcl_1EC);
            debug_text(loc194);
        }
    }
}

// Refreshes the scoreboard's round/end-of-game status texts.
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
// match: ?vf_008@type_21EB30@@UAEXXZ @ 0x0021FB60
// match: __ehhandler$?vf_008@type_21EB30@@UAEXXZ-0x9C @ 0x00308580
// match: __ehhandler$?vf_008@type_21EB30@@UAEXXZ @ 0x0030861C
void type_21EB30::vf_008()
{
    RwInt32 lv_10;
    RwInt32 lv_14;

    type_21CB10::vf_008();
    unk_39E = sub_1C48D0();
    lv_14 = sub_1C42F0();
    lv_10 = 2;
    if (lv_14 != 666)
        lv_10 = sub_1C4880(lv_14);
    if (unk_3A0 != lv_10)
    {
        unk_3A0 = lv_10;
        sub_2203E0();
    }
    sub_21F1C0();
    if (dword_4FB9E0.get_unk_08() == 1)
        unk_2FC.sub_1F28C0(type_1CB670(sub_1C4E60(dword_4FB9E0.get_unk_08()), 0));
    else
        unk_2FC.sub_1F28C0(type_1CB670("", 0));
    unk_34C.sub_1F28C0(type_1CB670("", 0));
    switch (unk_154)
    {
    case 0:
        {
            type_1CB670 lv_34;

            lv_34.sub_1C85D0(unk_3A4);
            unk_324.sub_1F28C0(sub_1CB7B0("RANKED", lv_34.c_str(), 0));
            unk_374.sub_1F28C0(sub_1C5350());
        }
        break;
    case 1:
    case 2:
        {
            type_1A5EA0 lv_50;

            lv_50.sub_1C85D0(unk_3A4);
            unk_324.sub_1F28C0(sub_1CB7B0("RANKED", lv_50.c_str(), 0));
            if (unk_4FDBB0.unk_00 == 1)
            {
                RwInt32 lv_58 = -1;
                RwInt32 lv_54 = -1;

                for (RwInt32 lv_5C = 0; lv_5C < 16; lv_5C++)
                {
                    if (sub_1C4630(lv_5C))
                    {
                        RwInt32 lv_60 = sub_1C4800(lv_5C);

                        if (lv_58 < 0 || lv_60 > lv_54)
                        {
                            lv_54 = lv_60;
                            lv_58 = lv_5C;
                        }
                    }
                }
                if (lv_58 >= 0)
                    unk_34C.sub_1F28C0(sub_1CB7B0("score_%1_wins", sub_1C4630(lv_58), 0));
            }
            else if (unk_4FDBB0.unk_00 == 8)
            {
                if (scoreboard_team_count() == 2)
                {
                    if (dword_4FB9E0.get_unk_E8())
                        unk_34C.sub_1F28C0(type_1CB670("score_allieswin", 0));
                    else
                        unk_34C.sub_1F28C0(type_1CB670("score_axiswin", 0));
                }
                else if (!dword_4FB9E0.get_unk_E8())
                    unk_34C.sub_1F28C0(type_1CB670("score_allieswin", 0));
                else
                    unk_34C.sub_1F28C0(type_1CB670("score_axiswin", 0));
                // Compiled-out text diagnostics: seven no-code inline
                // expansions preserve this block's destructor budget.
                // Two unused inline locals then restore the image's
                // final this/temporary slots (docs/toolchain.md).
                debug_text(lv_50);
                debug_text(lv_50);
                debug_text(lv_50);
                debug_text(lv_50);
                debug_text(lv_50);
                debug_text(lv_50);
                debug_text(lv_50);
                unused_slot();
                unused_slot();
            }
            else if (unk_4F7EB8.unk_04.sub_1B33C0(2) > unk_4F7EB8.unk_04.sub_1B33C0(4))
                unk_34C.sub_1F28C0(type_1CB670("score_allieswin", 0));
            else if (unk_4F7EB8.unk_04.sub_1B33C0(2) < unk_4F7EB8.unk_04.sub_1B33C0(4))
                unk_34C.sub_1F28C0(type_1CB670("score_axiswin", 0));
        }
        break;
    }
    sub_1E8B50(0);
}

// match: ?vf_00C@type_21EB30@@UAEXXZ @ 0x002202E0
void type_21EB30::vf_00C()
{
    unk_39D = false;
    type_21CB10::vf_00C();
}

// match: ?vf_014@type_21EB30@@UAEXM@Z @ 0x00220300
void type_21EB30::vf_014(RwReal arg_0)
{
    type_21CB10::vf_014(arg_0);
    type_1DDE20_mask var_4 = sub_1C48D0();

    if (sub_1C4C20())
    {
        sub_1C4C30(false);
        sub_21F1C0();
    }
    else if (var_4 != unk_39E)
    {
        if (dword_4FB9E0.get_unk_C8() == 0)
        {
            unk_39E.unk_00 = var_4.unk_00;
            sub_21F1C0();
        }
    }
    if (vf_048())
    {
        RwReal var_8 = unk_4B9308.sub_EE9A0(0, 0x19);

        if (var_8 != 0.0f)
        {
            unk_39D = !unk_39D;
            sub_21F1C0();
        }
    }
}

// match: ?sub_2203E0@type_21EB30@@QAEXXZ @ 0x002203E0
// match: __ehhandler$?sub_2203E0@type_21EB30@@QAEXXZ-0x1B @ 0x00308630
// match: __ehhandler$?sub_2203E0@type_21EB30@@QAEXXZ @ 0x0030864B
void type_21EB30::sub_2203E0()
{
    // The flags' bitmap libraries by team and the score bitmap's name (0x42D2C4 and
    // 0x42D2B8): statics of this function, its literals come out with it (score, then
    // the flags last to first) and their data the score's first, as the image has them.
    static const RwChar *off_42D2C4[4] = { "w_flagsGB", "w_flagsUS", "w_flagsRU", "w_flagsDE" };
    static const RwChar *off_42D2B8[3] = { "score", 0, 0 };
    RwInt32 var_44;
    RwInt32 var_40;
    RwInt32 as_3C;
    RwInt32 ebp_38;
    type_1E3BA0_state *var_34[6];
    type_1E7410 *ebp_1C;
    RwInt32 l18;
    type_1E3BA0 *ebp_14;
    RwInt32 lv_10;

    sub_220680();
    l18 = 2;
    as_3C = 4;
    ebp_38 = sub_1C42F0();
    if (ebp_38 != 0x29A && sub_1C4880(ebp_38) == 4)
    {
        l18 = 4;
        as_3C = 2;
    }
    lv_10 = sub_1C4480(l18);
    if (lv_10 != -1)
        unk_174[0] = sub_1ED040(off_42D2C4[lv_10]);
    lv_10 = sub_1C4480(as_3C);
    if (lv_10 != -1)
        unk_174[1] = sub_1ED040(off_42D2C4[lv_10]);
    if (!unk_174[0].sub_E87C0() && !unk_174[1].sub_E87C0())
    {
        for (var_40 = 0; var_40 < 2; var_40++)
        {
            memset(var_34, 0, sizeof(var_34));
            for (var_44 = 0; var_44 < 1; var_44++)
            {
                ebp_1C = unk_174[var_40]->sub_1ED630(off_42D2B8[var_44]);
                var_34[dword_5051DC[var_44]] = (type_1E3BA0_state *)ebp_1C;
            }
            sub_1E3C10(var_34);
            ebp_14 = new type_1E3BA0(var_34, 0);
            unk_17C[var_40] = ebp_14;
        }
        if (unk_17C[0])
            unk_164.sub_1E7510(unk_17C[0]);
        if (unk_17C[1] && get_unk_39C())
            unk_16C.sub_1E7510(unk_17C[1]);
    }
}

// match: ?sub_220680@type_21EB30@@QAEXXZ @ 0x00220680
void type_21EB30::sub_220680()
{
    for (RwInt32 var_4 = 0; var_4 < 2; var_4++)
    {
        unk_174[var_4] = 0;
        delete unk_17C[var_4];
    }
}

// The action's members (game/kujuui.h's template, its definitions repeated
// here; the constructor alone builds it, so it is instantiated whole).
// match: ??0?$type_3E7CE8@Utype_21EB30@@@kujuUI@@QAE@PAUtype_21EB30@@P82@AEXXZ@Z @ 0x00220710
template <class T> type_3E7CE8<T>::type_3E7CE8(T *arg_0, void (T::*arg_4)())
{
    unk_04 = arg_0;
    unk_08 = arg_4;
}

// match: ??_G?$type_3E7CE8@Utype_21EB30@@@kujuUI@@UAEPAXI@Z @ 0x00220770
// match: ??1?$type_3E7CE8@Utype_21EB30@@@kujuUI@@UAE@XZ @ 0x00220750
template <class T> type_3E7CE8<T>::~type_3E7CE8()
{
}

template <class T> void type_3E7CE8<T>::pvf_008()
{
    (unk_04->*unk_08)();
}

template struct type_3E7CE8<type_21EB30>;

// Functions /OPT:ICF folded into another body (config/aliases.txt), defined here for the
// authentic link (PLAN M7) with that body; the placement link takes the folded one.

// ?sub_220A80@type_21EB30@@QAEXXZ (folded into 0x220A80)
void type_21EB30::sub_220A80()
{
    sub_1C4B10();
}
