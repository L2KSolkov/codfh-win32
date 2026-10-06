/*
 * The pause menu (game/ingamepages.h): its entries' pages, the one shown
 * and moving between them, its entries' actions and the vote's texts. The
 * loading (sub_21BD60) includes the map image, name and game-type text.
 */
#include <stdio.h>
#include "game/ingamepages.h"
#include "game/liveservice.h"
#include "game/data.h"
#include "game/frontend.h"
#include "game/gameloop.h"
#include "game/loc.h"
#include "game/uiglue.h"
#include "types/type_10F710.h"

// Its data definitions (PLAN M5), in the image's address order.
// 0x003E9FD8
extern const RwReal flt_3E9FD8 = 0.01f;
// 0x003E9FDC
extern const RwReal flt_3E9FDC = 0.01f;
// 0x003E9FE0
extern const RwReal flt_3E9FE0 = 16.666666f;
// 0x005051D8
type_21A5E0 *dword_5051D8;
// End of its data definitions.


// Inline with no address or database name. Evidence: sub_21BD60 loads
// the selected level after two one-load compiled-out checks, as the
// existing picked_level() accessor does (game/hostoptions.h).
inline type_505188 *level_at(RwUInt32 arg_0)
{
    LEVELS_CHECK(arg_0);
    LEVELS_CHECK(arg_0);
    return &dword_4FD974[arg_0];
}
// Its data (PLAN M5): literals, constants and tables where the image has them.
// match: ?flt_3E9FD8@@3MB @ 0x003E9FD8
// match: ?flt_3E9FDC@@3MB @ 0x003E9FDC
// match: ?flt_3E9FE0@@3MB @ 0x003E9FE0
// match: ??_C@_0N@NHJHFCEB@gametypeinfo?$AA@ @ 0x003E9FE4
// match: ??_C@_08NJPDEKHO@gametype?$AA@ @ 0x003E9FF4
// match: ??_C@_07KMNEBLH@mapname?$AA@ @ 0x003EA000
// match: ??_C@_08MCIBENOM@votetext?$AA@ @ 0x003EA008
// match: ??_C@_03HBNNNHNM@map?$AA@ @ 0x003EA014
// match: ??_7type_21A5E0@@6B@ @ 0x003EA018
// match: ??_C@_05GFCDIDHO@debug?$AA@ @ 0x003EA068
// match: ??_C@_04KNNLNNGO@quit?$AA@ @ 0x003EA070
// match: ??_C@_04GHHIKFLG@vote?$AA@ @ 0x003EA078
// match: ??_C@_04OODOLJMA@host?$AA@ @ 0x003EA080
// match: ??_C@_04KADBPNCB@team?$AA@ @ 0x003EA088
// match: ??_C@_07PKKCMMCH@weapons?$AA@ @ 0x003EA090
// match: ??_C@_04GLMHKBCH@live?$AA@ @ 0x003EA098
// match: ??_C@_06PLELHCEK@resume?$AA@ @ 0x003EA0A0
// match: ??_C@_0BJ@EAIBHIDO@LiveOptionsInGame?4layout?$AA@ @ 0x003EA0A8
// match: ??_C@_0BB@LLELCOCB@DebugMenu?4layout?$AA@ @ 0x003EA0C4
// match: ??_C@_0BO@LCJENJOK@PleaseInsertController?4layout?$AA@ @ 0x003EA0D8
// match: ??_C@_0O@OHJPBCDK@UseNow?4layout?$AA@ @ 0x003EA0F8
// match: ??_C@_0O@PJFCLAAP@Defect?4layout?$AA@ @ 0x003EA108
// match: ??_C@_0BC@JHGOBDEN@TeamSelect?4layout?$AA@ @ 0x003EA118
// match: ??_C@_0BA@BCIIEKAH@QuitGame?4layout?$AA@ @ 0x003EA12C
// match: ??_C@_0BG@HIPCOFOJ@OnlineSettings?4layout?$AA@ @ 0x003EA13C
// match: ??_C@_0BO@DAAPOAPG@OnlineSettingsAdvanced?4layout?$AA@ @ 0x003EA154
// match: ??_C@_0BB@MMBEHLPF@NextRound?4layout?$AA@ @ 0x003EA174
// match: ??_C@_0BC@MAEDADOB@KickPlayer?4layout?$AA@ @ 0x003EA188
// match: ??_C@_0BD@NPLJNKMH@HostOptions?4layout?$AA@ @ 0x003EA19C
// match: ??_C@_0BE@LCJFJLAO@GameSettings?4layout?$AA@ @ 0x003EA1B0
// match: ??_C@_0BD@IGBGICK@VoteConfirm?4layout?$AA@ @ 0x003EA1C4
// match: ??_C@_0BA@HEMFGDED@VoteGame?4layout?$AA@ @ 0x003EA1D8
// match: ??_C@_0P@KKEMPLNG@VoteMap?4layout?$AA@ @ 0x003EA1E8
// match: ??_C@_0BC@EMNCPJIE@VotePlayer?4layout?$AA@ @ 0x003EA1F8
// match: ??_C@_0BD@DAFLCEBP@VoteOptions?4layout?$AA@ @ 0x003EA20C
// match: ??_C@_0BH@EMAHFCDF@CurrentVoteGame?4layout?$AA@ @ 0x003EA220
// match: ??_C@_0BG@LALPEJHE@CurrentVoteMap?4layout?$AA@ @ 0x003EA238
// match: ??_C@_0BJ@GEGJBPAM@CurrentVotePlayer?4layout?$AA@ @ 0x003EA250
// match: ??_C@_08MIJEGIEN@Vote?5Now?$AA@ @ 0x003EA26C
// match: ??_C@_09HBHKKKMO@Call?5Vote?$AA@ @ 0x003EA278
// match: ??_C@_0N@BIENHFDJ@Confirm?5Vote?$AA@ @ 0x003EA284
// match: ??_C@_04MKFCAELI@_ctf?$AA@ @ 0x003EA294
// match: ??_C@_08MEJGLHCA@_destroy?$AA@ @ 0x003EA29C
// match: ??_C@_06IPPLNOL@_death?$AA@ @ 0x003EA2A8
// match: ??_C@_07MEHNIHAP@gui_map?$AA@ @ 0x003EA2B0
// match: ??_C@_0O@ONAIAMJG@info_type_ctf?$AA@ @ 0x003EA2B8
// match: ??_C@_0N@ECLKMDMM@info_type_sd?$AA@ @ 0x003EA2C8
// match: ??_C@_0O@NPBEBJAL@info_type_tdm?$AA@ @ 0x003EA2D8
// match: ??_C@_0N@IKBBMNHA@info_type_dm?$AA@ @ 0x003EA2E8
// match: ??_C@_0M@NLCLPDAJ@Kill?5Player?$AA@ @ 0x003EA2F8
// match: ??_C@_0BD@BDOGJPHP@kill_player_prompt?$AA@ @ 0x003EA304
// match: ??_7?$type_3E7CE8@Utype_21A5E0@@@kujuUI@@6B@ @ 0x003EA318
// match: ??_7?$type_3E7264@Utype_21A5E0@@@kujuUI@@6B@ @ 0x003EA328
// match: __ehhandler$??0type_21A5E0@@QAE@PBD@Z>1>8 @ 0x00424C14
// match: __ehhandler$??0type_21A5E0@@QAE@PBD@Z>1 @ 0x00424CCC
// match: __ehhandler$??1type_21A5E0@@UAE@XZ>1>8 @ 0x00424CE8
// match: __ehhandler$??1type_21A5E0@@UAE@XZ>1 @ 0x00424D90
// match: __ehhandler$?sub_21ADB0@type_21A5E0@@QAE_NXZ>1>8 @ 0x00424DAC
// match: __ehhandler$?sub_21ADB0@type_21A5E0@@QAE_NXZ>1 @ 0x00424E64
// match: __ehhandler$?sub_21B8F0@type_21A5E0@@QAEXXZ>1>8 @ 0x00424E80
// match: __ehhandler$?sub_21B8F0@type_21A5E0@@QAEXXZ>1 @ 0x00424E98
// match: __ehhandler$?vf_014@type_21A5E0@@UAEXM@Z>1>8 @ 0x00424EB4
// match: __ehhandler$?vf_014@type_21A5E0@@UAEXM@Z>1 @ 0x00424EBC
// match: __ehhandler$?vf_03C@type_21A5E0@@UAEXXZ>1>8 @ 0x00424ED8
// match: __ehhandler$?vf_03C@type_21A5E0@@UAEXXZ>1 @ 0x00424F00
// match: __ehhandler$?sub_21C4C0@type_21A5E0@@QAEXXZ>1>8 @ 0x00424F1C
// match: __ehhandler$?sub_21C4C0@type_21A5E0@@QAEXXZ>1 @ 0x00424F3C
// match: ?off_42D2AC@?1??vf_03C@type_21A5E0@@UAEXXZ@4PAPBDA @ 0x0042D2AC

using namespace kujuUI;

// match: ?sub_21A5E0@@YAPAUtype_21A5E0@@XZ @ 0x0021A5E0
type_21A5E0 *sub_21A5E0()
{
    return dword_5051D8;
}

// match: ??0type_21A5E0@@QAE@PBD@Z @ 0x0021A5F0
// match: __ehhandler$??0type_21A5E0@@QAE@PBD@Z-0x128 @ 0x00307A00
// match: __ehhandler$??0type_21A5E0@@QAE@PBD@Z @ 0x00307B28
type_21A5E0::type_21A5E0(const RwChar *arg_0)
    : type_21CB10(arg_0, 0, 0), unk_154(-1), unk_1B8(this, &type_21A5E0::sub_21C360),
      unk_1C4(this, &type_21A5E0::sub_21C380), unk_1D0(this, &type_21A5E0::sub_21C3A0),
      unk_1DC(this, &type_21A5E0::sub_21C3C0, &type_21A5E0::sub_21C410),
      unk_1EC(this, &type_21A5E0::sub_21C3E0, &type_21A5E0::sub_21C400),
      unk_1FC(this, &type_21A5E0::sub_21C430, &type_21A5E0::sub_21C6A0),
      unk_20C(this, &type_21A5E0::sub_21C6E0), unk_218(this, &type_21A5E0::sub_21C700),
      unk_224(this, &type_21A5E0::sub_21C720), unk_230(this, &type_21A5E0::sub_21C4C0, &type_21A5E0::sub_21C620),
      unk_240(this, &type_21A5E0::sub_21C670), unk_24C(this, &type_21A5E0::sub_1E41C0), unk_25C(0),
      unk_3E0(false), unk_3E1(false)
{
    sub_204FC0("map", &unk_260);
    sub_204FC0("votetext", &unk_268);
    sub_204FC0("mapname", &unk_290);
    sub_204FC0("gametype", &unk_2B8);
    sub_204FC0("gametypeinfo", &unk_2E0);
    sub_204FC0("XboxLiveOptions", &unk_308);
    // A compiled-out check on the one instance (it shifts the registers).
    if (dword_5051D8 != this)
    {
    }
    dword_5051D8 = this;
    unk_4FEB0C.sub_1CADA0(1, 0);
    sub_21ADB0();
    dword_504378 = &unk_330;
    type_1E7CF0 *var_10 = sub_1E7CF0();

    var_10->sub_1E80F0(false);
    var_10->sub_1E8110(true);
    sub_2172F0();
}

// match: ??_Gtype_21A5E0@@UAEPAXI@Z @ 0x0021A950
// match: ??1type_21A5E0@@UAE@XZ @ 0x0021A980
// match: __ehhandler$??1type_21A5E0@@UAE@XZ-0x120 @ 0x00307B40
// match: __ehhandler$??1type_21A5E0@@UAE@XZ @ 0x00307C60
type_21A5E0::~type_21A5E0()
{
    // A compiled-out check on the one instance (it shifts the registers).
    if (dword_5051D8 != this)
    {
    }
    dword_5051D8 = 0;
    dword_504378 = 0;
    sub_21C740();
    for (RwInt32 var_10 = 1; var_10 < 0x18; var_10++)
    {
        if (sub_1E7CF0()->sub_1E7D00(unk_158[var_10]))
            sub_1E7CF0()->sub_1E7D90(unk_158[var_10]);
        delete unk_158[var_10];
    }
    unk_4FEB0C.sub_1CACC0(1);
    sub_217450();
}

// match: ?sub_21ABF0@type_21A5E0@@QAEHXZ @ 0x0021ABF0
RwInt32 type_21A5E0::sub_21ABF0()
{
    return unk_154;
}

// match: ?sub_21AC10@type_21A5E0@@QAE_NH@Z @ 0x0021AC10
bool type_21A5E0::sub_21AC10(RwInt32 arg_0)
{
    if (unk_154 != arg_0)
    {
        if (unk_154 >= 0 && unk_154 < 0x18)
        {
            unk_158[unk_154]->lostFocus();
            sub_1E7CF0()->sub_1E7D90(unk_158[unk_154]);
            if (unk_154 > 0)
                unk_158[unk_154]->vf_00C();
        }
        unk_154 = arg_0;
        if (unk_154 >= 0 && unk_154 < 0x18)
        {
            sub_1E7CF0()->sub_1E7D30(unk_158[unk_154]);
            if (!unk_158[unk_154]->sub_1F7720())
                unk_158[unk_154]->givenFocus();
            if (unk_154 > 0)
                unk_158[unk_154]->vf_008();
        }
        return true;
    }
    return false;
}

// match: ?sub_21ADB0@type_21A5E0@@QAE_NXZ @ 0x0021ADB0
// match: __ehhandler$?sub_21ADB0@type_21A5E0@@QAE_NXZ-0x118 @ 0x00307C70
// match: __ehhandler$?sub_21ADB0@type_21A5E0@@QAE_NXZ @ 0x00307D88
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

// match: ?vf_018@type_21A5E0@@UAEXPAUtype_1E4130@kujuUI@@@Z @ 0x0021B8D0
void type_21A5E0::vf_018(type_1E4130 *arg_0)
{
    type_21CB10::vf_018(arg_0);
}

// The vote's text: "Confirm Vote", "Call Vote" or "Vote Now".
// match: ?sub_21B8F0@type_21A5E0@@QAEXXZ @ 0x0021B8F0
// match: __ehhandler$?sub_21B8F0@type_21A5E0@@QAEXXZ-0x18 @ 0x00307DA0
// match: __ehhandler$?sub_21B8F0@type_21A5E0@@QAEXXZ @ 0x00307DB8
void type_21A5E0::sub_21B8F0()
{
    if (unk_3E1)
        unk_268.sub_1F28C0(type_1CB670("Confirm Vote", 0));
    else if (unk_3E0)
        unk_268.sub_1F28C0(type_1CB670("Call Vote", 0));
    else
        unk_268.sub_1F28C0(type_1CB670("Vote Now", 0));
}

// The update: the vote's text when the vote's state changes, and "Xbox Live
// Options" marked with the service's two flags; then the base's update.
// match: ?vf_014@type_21A5E0@@UAEXM@Z @ 0x0021BA50
// match: __ehhandler$?vf_014@type_21A5E0@@UAEXM@Z-0xB @ 0x00307DD0
// match: __ehhandler$?vf_014@type_21A5E0@@UAEXM@Z @ 0x00307DDB
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void type_21A5E0::vf_014(RwReal arg_0)
{
    bool lv_D;
    bool lv_15;
    RwInt32 local_14;

    lv_D = sub_1C4CB0();
    lv_15 = sub_1C4E40();
    if (unk_3E0 != lv_D || unk_3E1 != lv_15)
    {
        unk_3E0 = lv_D;
        unk_3E1 = lv_15;
        sub_21B8F0();
    }
    local_14 = sub_227560()->sub_227950();
    {
        RwChar lv_11C[256];

        if ((local_14 & 3) == 3)
            sprintf(lv_11C, "\xbc \xbd %s", type_1CB670("Xbox Live Options", 0).c_str());
        else if (local_14 & 1)
            sprintf(lv_11C, "\xbc %s", type_1CB670("Xbox Live Options", 0).c_str());
        else if (local_14 & 2)
            sprintf(lv_11C, "\xbd %s", type_1CB670("Xbox Live Options", 0).c_str());
        else
            sprintf(lv_11C, "%s", type_1CB670("Xbox Live Options", 0).c_str());
        unk_308.sub_1F28C0(sub_1CB720(lv_11C));
    }
    type_21CB10::vf_014(arg_0);
}

// match: ?vf_03C@type_21A5E0@@UAEXXZ @ 0x0021BD60
// match: __ehhandler$?vf_03C@type_21A5E0@@UAEXXZ-0x37 @ 0x00307DF0
// match: __ehhandler$?vf_03C@type_21A5E0@@UAEXXZ @ 0x00307E27
// Loads the pause menu's game-type text, map image and map name.
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void type_21A5E0::vf_03C()
{
    // The game-type suffixes (0x42D2AC): a static of this function, its texts come out with
    // it, before its own, as the image has them.
    static const RwChar *off_42D2AC[3] = { "_death", "_destroy", "_ctf" };
    RwInt32 x4C;
    type_505188 *w48;
    type_1E3BA0_state *loc44[6];
    type_1E7410 *fp_2C;
    const RwChar *q28;
    type_1E3BA0 *frm_24;
    RwInt32 var_20;
    RwInt32 l1C;
    RwUInt32 m_18;
    const RwChar *ebp_14;
    RwInt32 lv_10;

    sub_20EA40();
    for (x4C = 1; x4C < 0x18; x4C++)
    {
        unk_158[x4C]->sub_20EA40();
        unk_158[x4C]->vf_03C();
    }
    l1C = dword_4FB9E0.get_unk_08();
    q28 = "";

    switch (l1C)
    {
    case 1:
        var_20 = 0;
        q28 = "info_type_dm";
        break;
    case 2:
        var_20 = 0;
        q28 = "info_type_tdm";
        break;
    case 8:
        var_20 = 1;
        q28 = "info_type_sd";
        break;
    case 4:
        var_20 = 2;
        q28 = "info_type_ctf";
        break;
#ifdef CODFH_WIN32
    case 16:
        // (Supremacy: the retail build lists it but has no page text or map image for it; the
        // team map image, and the mode's name)
        var_20 = 0;
        q28 = "Supremacy";
        break;
#endif
    }
    unk_2B8.sub_1F28C0(type_1CB670(q28, 0));
    sub_21C740();
    m_18 = unk_4FDBB0.unk_28;
    w48 = level_at(m_18);
    ebp_14 = w48->sub_1A5F60().c_str();
    lv_10 = atoi(ebp_14 + 3);

    if (m_18 < 8)
    {
        type_1A5EA0 var_6C("gui_map");

        var_6C.sub_21CA90(lv_10).sub_1CA470(off_42D2AC[var_20]);
        unk_258 = sub_1ED040(var_6C.c_str());
        if (!unk_258.sub_E87C0())
        {
            memset(loc44, 0, sizeof(loc44));
            fp_2C = unk_258->sub_1ED630("map");
            loc44[0] = (type_1E3BA0_state *)fp_2C;
            sub_1E3C10(loc44);
            // The original retains an unwritten inline slot at -0xCC
            // before the second name read's this slot (-0xD0). Its exact
            // discarded source expression is unknown; use the existing
            // no-code helper to preserve that allocation (docs/toolchain.md).
            unused_slot();
            frm_24 = new type_1E3BA0(loc44, 0);
            unk_25C = frm_24;
            if (unk_25C)
                unk_260.sub_1E7510(unk_25C);
            unk_290.sub_1F28C0(type_1CB670(w48->sub_1A5F60().c_str(), 0));
        }
    }
}


// match: ?processEvent@type_21A5E0@@UAE?AW4eEventWasHandled@kujuUI@@ABVcStateChange@3@@Z @ 0x0021C1E0
eEventWasHandled type_21A5E0::processEvent(const cStateChange &arg_0)
{
    return cTopLayoutPage::processEvent(arg_0);
}

// match: ?sub_21C200@type_21A5E0@@QAEXHH@Z @ 0x0021C200
void type_21A5E0::sub_21C200(RwInt32 arg_0, RwInt32 arg_4)
{
    if (arg_0 >= 0 && arg_0 < 0x18)
    {
        type_21CB10 *var_4 = unk_158[arg_0];

        var_4->unk_134 = arg_4;
    }
    sub_21AC10(arg_0);
}

// match: ?sub_21C250@type_21A5E0@@QAEX_N@Z @ 0x0021C250
void type_21A5E0::sub_21C250(bool arg_0)
{
    sub_1C4D40(arg_0);
    sub_21C200(0, 0);
}

// match: ?sub_21C280@type_21A5E0@@QAEXH@Z @ 0x0021C280
void type_21A5E0::sub_21C280(RwInt32 arg_0)
{
    sub_21C200(0, 0);
}

// match: ?sub_21C2A0@type_21A5E0@@QAEX_N@Z @ 0x0021C2A0
void type_21A5E0::sub_21C2A0(bool arg_0)
{
    if (arg_0)
        sub_1C44A0();
    else
        sub_21C200(0, 0);
}

// match: ?sub_21C2D0@type_21A5E0@@QAEX_N@Z @ 0x0021C2D0
void type_21A5E0::sub_21C2D0(bool arg_0)
{
    if (arg_0)
    {
        RwInt32 var_4 = static_cast<type_220C40 *>(unk_158[2])->unk_170;

        sub_1C4380(var_4);
        sub_21C360();
        sub_1C44F0();
    }
    else
    {
        RwInt32 var_8 = static_cast<type_220C40 *>(unk_158[2])->unk_170;

        if (var_8 == 4)
            static_cast<type_220C40 *>(unk_158[2])->sub_221100(2);
        else
            static_cast<type_220C40 *>(unk_158[2])->sub_221100(4);
        sub_21C3C0();
    }
}

// match: ?sub_21C360@type_21A5E0@@QAEXXZ @ 0x0021C360
void type_21A5E0::sub_21C360()
{
    sub_D7C10(false);
}

// match: ?sub_21C380@type_21A5E0@@QAEXXZ @ 0x0021C380
void type_21A5E0::sub_21C380()
{
    sub_21C200(0x15, 0);
}

// match: ?sub_21C3A0@type_21A5E0@@QAEXXZ @ 0x0021C3A0
void type_21A5E0::sub_21C3A0()
{
    sub_21C200(1, 0);
}

// match: ?sub_21C3C0@type_21A5E0@@QAEXXZ @ 0x0021C3C0
void type_21A5E0::sub_21C3C0()
{
    sub_21C200(2, 0);
}

// match: ?sub_21C3E0@type_21A5E0@@QAEXXZ @ 0x0021C3E0
void type_21A5E0::sub_21C3E0()
{
    sub_21C200(4, 0);
}

// match: ?sub_21C400@type_21A5E0@@QAE_NXZ @ 0x0021C400
bool type_21A5E0::sub_21C400()
{
    return sub_1C4BE0();
}

// match: ?sub_21C410@type_21A5E0@@QAE_NXZ @ 0x0021C410
bool type_21A5E0::sub_21C410()
{
    return dword_4FB9E0.get_unk_08() != 1;
}

// match: ?sub_21C430@type_21A5E0@@QAEXXZ @ 0x0021C430
void type_21A5E0::sub_21C430()
{
    if (unk_3E1)
        sub_21C200(0xC, 0);
    else if (unk_3E0)
        sub_21C200(8, 0);
    else
    {
        switch (sub_1C4D00())
        {
        case 2:
            sub_21C200(5, 0);
            break;
        case 0:
            sub_21C200(6, 0);
            break;
        case 1:
            sub_21C200(7, 0);
            break;
        }
    }
}

// "kill": asks whether to kill the player, "yes" running unk_240 and "no"
// (and backing out) unk_24C.
// match: ?sub_21C4C0@type_21A5E0@@QAEXXZ @ 0x0021C4C0
// match: __ehhandler$?sub_21C4C0@type_21A5E0@@QAEXXZ-0x20 @ 0x00307E40
// match: __ehhandler$?sub_21C4C0@type_21A5E0@@QAEXXZ @ 0x00307E60
void type_21A5E0::sub_21C4C0()
{
    sub_2171F0(type_1CB670("Kill Player", 0), type_1CB670("kill_player_prompt", 0), type_1CB670("Yes", 0), &unk_240,
               type_1CB670("No", 0), &unk_24C, &unk_24C);
}

// match: ?sub_21C620@type_21A5E0@@QAE_NXZ @ 0x0021C620
bool type_21A5E0::sub_21C620()
{
    type_4F805C *var_4 = dword_4F805C;

    return var_4 && var_4->unk_19DC > 0.0f;
}

// match: ?sub_21C670@type_21A5E0@@QAEXXZ @ 0x0021C670
void type_21A5E0::sub_21C670()
{
    sub_1C44F0();
    sub_21C200(0, 0);
    sub_21C360();
}

// match: ?sub_21C6A0@type_21A5E0@@QAE_NXZ @ 0x0021C6A0
bool type_21A5E0::sub_21C6A0()
{
    return unk_3E0 || sub_1C4CC0();
}

// match: ?sub_21C6E0@type_21A5E0@@QAEXXZ @ 0x0021C6E0
void type_21A5E0::sub_21C6E0()
{
    sub_21C200(0xD, 0);
}

// match: ?sub_21C700@type_21A5E0@@QAEXXZ @ 0x0021C700
void type_21A5E0::sub_21C700()
{
    sub_21C200(0xE, 0);
}

// match: ?sub_21C720@type_21A5E0@@QAEXXZ @ 0x0021C720
void type_21A5E0::sub_21C720()
{
    sub_21C200(0x14, 0);
}

// match: ?sub_21C740@type_21A5E0@@QAEXXZ @ 0x0021C740
void type_21A5E0::sub_21C740()
{
    unk_258 = 0;
    delete unk_25C;
}

// match: ?vf_008@type_21A5E0@@UAEXXZ @ 0x0021C7B0
void type_21A5E0::vf_008()
{
    if (unk_154 > 0 && unk_154 < 0x18)
        unk_158[unk_154]->vf_008();
    sub_21B8F0();
    type_21CB10::vf_008();
    if (unk_154 >= 0 && unk_154 < 0x18)
        sub_1E7CF0()->sub_1E7D30(unk_158[unk_154]);
}

// match: ?vf_00C@type_21A5E0@@UAEXXZ @ 0x0021C850
void type_21A5E0::vf_00C()
{
    if (unk_154 >= 0 && unk_154 < 0x18)
        sub_1E7CF0()->sub_1E7D90(unk_158[unk_154]);
    if (unk_154 > 0 && unk_154 < 0x18)
        unk_158[unk_154]->vf_00C();
    type_21CB10::vf_00C();
}

// match: ?vf_040@type_21A5E0@@UAEXXZ @ 0x0021C8E0
void type_21A5E0::vf_040()
{
    sub_21C360();
}

// The map's image library's pointer's assignments (game/kujufont.h's
// template; the originals every other pointee's are folded into).
// match: ??4?$type_E8780@Utype_1ECCE0@kujuUI@@@@QAEAAU0@PAUtype_1ECCE0@kujuUI@@@Z @ 0x0021C900
// match: ??4?$type_E8780@Utype_1ECCE0@kujuUI@@@@QAEAAU0@ABU0@@Z @ 0x0021C950


// The assignment of another pointer: only the loading (sub_21BD60)
// uses it here.
template type_E8780<type_1ECCE0> &type_E8780<type_1ECCE0>::operator=(const type_E8780<type_1ECCE0> &);

// The actions' members (game/kujuui.h's templates, their definitions
// repeated here).
// match: ??0?$type_3E7CE8@Utype_21A5E0@@@kujuUI@@QAE@PAUtype_21A5E0@@P82@AEXXZ@Z @ 0x0021C9A0
template <class T> type_3E7CE8<T>::type_3E7CE8(T *arg_0, void (T::*arg_4)())
{
    unk_04 = arg_0;
    unk_08 = arg_4;
}

// match: ??0?$type_3E7264@Utype_21A5E0@@@kujuUI@@QAE@PAUtype_21A5E0@@P82@AEXXZP82@AE_NXZ@Z @ 0x0021CA00
template <class T> type_3E7264<T>::type_3E7264(T *arg_0, void (T::*arg_4)(), bool (T::*arg_C)())
{
    unk_04 = arg_0;
    unk_08 = arg_4;
    unk_10 = arg_C;
}

// match: ?pvf_00C@?$type_3E7264@Utype_21A5E0@@@kujuUI@@UAE_NXZ @ 0x0021CA70
template <class T> bool type_3E7264<T>::pvf_00C()
{
    return (unk_04->*unk_10)();
}

template <class T> void type_3E7CE8<T>::pvf_008()
{
    (unk_04->*unk_08)();
}

// match: ?sub_21CA90@type_1A5EA0@@QAEAAU1@H@Z @ 0x0021CA90
type_1A5EA0 &type_1A5EA0::sub_21CA90(RwInt32 arg_0)
{
    return sub_1C85D0(arg_0);
}

// match: ??_G?$type_3E7CE8@Utype_21A5E0@@@kujuUI@@UAEPAXI@Z @ 0x0021CAB0
// match: ??1?$type_3E7CE8@Utype_21A5E0@@@kujuUI@@UAE@XZ @ 0x0021C9E0
template <class T> type_3E7CE8<T>::~type_3E7CE8()
{
}

template <class T> void type_3E7264<T>::pvf_008()
{
    (unk_04->*unk_08)();
}

// match: ??_G?$type_3E7264@Utype_21A5E0@@@kujuUI@@UAEPAXI@Z @ 0x0021CAE0
// match: ??1?$type_3E7264@Utype_21A5E0@@@kujuUI@@UAE@XZ @ 0x0021CA50
template <class T> type_3E7264<T>::~type_3E7264()
{
}

// Members /OPT:ICF folded into shared trivial bodies (config/aliases.txt): defined here for
// the authentic link (PLAN M7); the placement link takes the shared bodies.

// ?sub_1E41C0@type_21A5E0@@QAEXXZ (folded into the empty body at 0x1E41C0)
void type_21A5E0::sub_1E41C0()
{
}
