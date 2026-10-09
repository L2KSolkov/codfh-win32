// The HUD (type_DC400). The original file name is not in the
// image, so it is named for its start address.

#ifdef CODFH_SP // the Live manager's message and render (sp_sub_A7930, SP 0xA7930); first, for d3d8.h
#include "game/xboxlive.h"
#endif
#include <math.h>
#include <stdio.h>
#include <string.h>

#include "rw/ostypes.h"
#include "game/data.h"
#include "game/gameloop.h"
#include "game/functions.h"
#include "rw/baengine.h"
#include "rw/bavector.h"
#include "game/startup.h"
#include "game/loc.h"
#include "types/type_DC400.h"
#include "types/type_4B8EF0.h"
#include "game/netmsg.h"
#include "types/type_3DBC78.h"
#include "game/flags.h"
#include "game/bombsites.h"
#include "game/netstate.h"
#include "game/netscore.h"
#include "game/ingamescreens.h"
#include "game/ingamepages.h"
#include "types/cNetPlayerTrigger.h"
#include "types/type_4D1DB8.h"
#include "game/clumpdata.h"
#include "rw/bastream.h"
#include "rw/babintex.h"
#include "game/parsedfile.h"
#ifdef CODFH_SP // the pause message box (sub_DD1C0, SP 0xACDB0)
#include "game/waitscreen.h"
#endif

// Its data definitions (PLAN M5), in the image's address order.
// 0x003D8058
extern const RwReal flt_3D8058 = 16.666666f;
// 0x003D805C
extern const RwV3d unk_3D805C = { 0.0f, 0.0f, 1.0f };
// 0x003D8068
#ifndef CODFH_SP // MP only: two scales and the objective keys (SP 0x2E3A60 follows unk_3D805C with sub_E0E90's literals)
extern const RwReal flt_3D8068 = 0.01f;
// 0x003D806C
extern const RwReal flt_3D806C = 0.01f;
// 0x003D8070
extern const RwChar unk_3D8070[7][0x20] =
{
    "HUD_OBJECTIVEINCOMPLETE",
    "HUD_OBJECTIVESECURE",
    "HUD_OBJECTIVEBOMBPLANTING",
    "HUD_OBJECTIVEBOMBPLANTED",
    "HUD_OBJECTIVEBOMBDEFUSING",
    "HUD_OBJECTIVECOMPLETED",
    "HUD_OBJECTIVEDESTROYED",
};
#endif
// 0x004293C0
RwReal flt_4293C0 = 50.0f;
// 0x004293C4
RwReal flt_4293C4 = 0.028f;
// 0x004293C8
RwInt32 dword_4293C8 = -1;
// 0x004293CC
RwInt32 dword_4293CC = -1;
// 0x004293D0
RwInt32 *dword_4293D0[2] = { &dword_4293C8, &dword_4293CC };
// 0x004293D8
RwReal flt_4293D8 = 0.09f;
// 0x004293DC
RwReal flt_4293DC = 185.0f;
// 0x004293E0
RwReal flt_4293E0 = 1.25f;
// 0x004293E4
RwReal flt_4293E4 = 25.0f;
// 0x004293E8
RwReal flt_4293E8 = 15000.0f;
// 0x004293EC
RwReal flt_4293EC = 25.0f;
// 0x004293F0
RwReal flt_4293F0 = 2.0f;
// 0x004293F4
RwReal flt_4293F4 = -1.0f;
// 0x004293F8
#ifndef CODFH_SP // MP only: the network game's HUD scales (SP 0x3216A0 holds dword_429400 after flt_4293F4)
RwReal flt_4293F8 = 0.38f;
// 0x004293FC
RwReal flt_4293FC = 0.095f;
#endif
// 0x00429400
RwInt32 dword_429400 = 36;
// 0x00429404
#ifndef CODFH_SP // MP only (SP 0x3216A4 holds unk_4B8B48 after dword_429400)
RwInt32 dword_429404 = 206;
#endif
// 0x004B8970
RwReal dword_4B8970;
// 0x004B8974
RwUInt8 byte_4B8974;
// 0x004B8975
bool byte_4B8975;
#ifdef CODFH_SP // single player's pause message box retries (SP 0x3B4804, between byte_4B8975 and dword_4B897C; SP 0xACDB0)
RwInt32 dword_sp_4B8978;
#endif
// 0x004B897C
RwInt32 dword_4B897C;
// 0x004B8980
RwInt32 dword_4B8980;
// 0x004B8984
RwReal flt_4B8984;
// 0x004B8B3C
RwReal flt_4B8B3C;
// 0x004B8F30
#ifndef CODFH_PLAIN
RwReal flt_4B8F30;
#endif
// 0x004B8F34
#ifndef CODFH_PLAIN
RwRGBA unk_4B8F34;
#endif
// 0x004B8F38
#ifndef CODFH_PLAIN
RwRGBA unk_4B8F38;
#endif
// End of its data definitions.


// Globals with constructors defined here (their initializers and exit
// functions at the end of .text).
#ifndef CODFH_SP // MP only: the network game's HUD texts (default.xbe has no HUD_* strings; only MP-only code reads them)
type_4B89B0 unk_4B89B0[7];
type_4B89B0 unk_4B8B20;
type_4B89B0 unk_4B8B04;
std::string unk_4B8AB0[3];
type_4B89B0 unk_4B8990;
type_4B89B0 unk_4B8A74;
type_4B89B0 unk_4B8A90;
#endif
// Two keys no code reads.
type_3DF8D8_04 unk_4B8B48(0xF2AA7ACD, 0x7D1EA238);
type_3DF8D8_04 unk_4B8B40(0x1CA63F25, 0x204B2F73);
// Its data (PLAN M5): literals, constants and tables where the image has them.
// match: ?flt_3D8058@@3MB @ 0x003D8058
// match: ?unk_3D805C@@3URwV3d@@B @ 0x003D805C
// match: ?flt_3D8068@@3MB @ 0x003D8068
// match: ?flt_3D806C@@3MB @ 0x003D806C
// match: ?unk_3D8070@@3QAY0CA@$$CBDA @ 0x003D8070
// match: ??_C@_0CJ@DFKEGOOG@Console?5initialized?5?9?9?5Low?5Level@ @ 0x003D8150
// match: ??_C@_0CK@KKPJIDPG@Console?5initialized?5?9?9?5High?5Leve@ @ 0x003D817C
// match: ??_C@_0CI@IONFDGMD@Console?5initialized?5?9?9?5Standard?5@ @ 0x003D81A8
// match: __real@459c4000 @ 0x003D81D0
// match: ??_C@_0BF@PFKKILBN@hud_t34_buddy_health?$AA@ @ 0x003D81D4
// match: ??_C@_0BF@CGBHGHCM@hud_m12_buddy_health?$AA@ @ 0x003D81EC
// match: ??_C@_0BI@NPFLCOFD@hud_person_buddy_health?$AA@ @ 0x003D8204
// match: ??_C@_04FGGPOPMG@?$CF?42d?$AA@ @ 0x003D821C
// match: ??_C@_01JLIPDDHJ@?3?$AA@ @ 0x003D8224
// match: ??_C@_0BD@HOLBBDGI@hud_hit_indicator5?$AA@ @ 0x003D8228
// match: ??_C@_0N@JMPNGMIL@hid_hit_root?$AA@ @ 0x003D823C
// match: ??_C@_0P@NPMHENMA@hud_pause_root?$AA@ @ 0x003D824C
// match: ??_C@_0BD@PNJGAIEJ@hud_buddy_status_9?$AA@ @ 0x003D825C
// match: ??_C@_0BD@OEINDJAI@hud_buddy_status_8?$AA@ @ 0x003D8270
// match: ??_C@_0BD@GDBFCFMH@hud_buddy_status_7?$AA@ @ 0x003D8284
// match: ??_C@_0BD@HKAOBEIG@hud_buddy_status_6?$AA@ @ 0x003D8298
// match: ??_C@_0BD@FBCDEHEF@hud_buddy_status_5?$AA@ @ 0x003D82AC
// match: ??_C@_0BD@EIDIHGAE@hud_buddy_status_4?$AA@ @ 0x003D82C0
// match: ??_C@_0BD@HHJOAMD@hud_buddy_status_3?$AA@ @ 0x003D82D4
// match: ??_C@_0BD@BOGCNBIC@hud_buddy_status_2?$AA@ @ 0x003D82E8
// match: ??_C@_0BD@DFEPICEB@hud_buddy_status_1?$AA@ @ 0x003D82FC
// match: ??_C@_0BB@NOFCAHEK@hud_buddy_status?$AA@ @ 0x003D8310
// match: ??_C@_0BF@OLBMPKEH@hud?5vehicle_armorbar?$AA@ @ 0x003D8324
// match: ??_C@_0BG@MMEKGJO@hud_vehicle_healthbar?$AA@ @ 0x003D833C
// match: ??_C@_0BG@GCEEHJF@hud_vehicle_lifeframe?$AA@ @ 0x003D8354
// match: ??_C@_0BB@FKMCBMPA@hud_vehicle_life?$AA@ @ 0x003D836C
// match: ??_C@_0N@IGONOBMK@hud_t34_body?$AA@ @ 0x003D8380
// match: ??_C@_0P@HNLFLDNE@hud_t34_turret?$AA@ @ 0x003D8390
// match: ??_C@_0P@FFOIIIDA@hud_tank_arrow?$AA@ @ 0x003D83A0
// match: ??_C@_0BA@MOMPEBEP@hud_t34_reticle?$AA@ @ 0x003D83B0
// match: ??_C@_0N@FPPGOHOE@hud_t34_root?$AA@ @ 0x003D83C0
// match: ??_C@_0BF@ECPDMJAD@hud_buddy_health_bar?$AA@ @ 0x003D83D0
// match: ??_C@_0BG@LMKNHBAH@hud_buddy_health?5root?$AA@ @ 0x003D83E8
// match: ??_C@_0BI@POOLMPMB@hud_enemy_hit_indicator?$AA@ @ 0x003D8400
// match: ??_C@_0BI@HNDMEIIM@hud_crosshair_overbuddy?$AA@ @ 0x003D8418
// match: ??_C@_0O@DLKGLCPK@hud_crosshair?$AA@ @ 0x003D8430
// match: ??_C@_0O@IIKJJAN@hud_inventory?$AA@ @ 0x003D8440
// match: ??_C@_0BC@IALAEJJK@hud_inventory_txt?$AA@ @ 0x003D8450
// match: ??_C@_0BE@MKHNNNKC@hud_inventory_radio?$AA@ @ 0x003D8464
// match: ??_C@_0BJ@HGEOANCB@hud_inventory_stickymine?$AA@ @ 0x003D8478
// match: ??_C@_0BJ@DOFGCOAJ@hud_inventory_tellermine?$AA@ @ 0x003D8494
// match: ??_C@_0BH@MDMFJMFH@hud_inventory_grenadeA?$AA@ @ 0x003D84B0
// match: ??_C@_0BH@KCCKNNMF@hud_inventory_grenadeR?$AA@ @ 0x003D84C8
// match: ??_C@_0BH@JFJPDLNB@hud_inventory_grenadeG?$AA@ @ 0x003D84E0
// match: ??_C@_0BD@JPEKAPG@hud_inventory_root?$AA@ @ 0x003D84F8
// match: ??_C@_0BC@LMFLDPLL@hud_ammo_txtgrens?$AA@ @ 0x003D850C
// match: ??_C@_0BC@KEHEGFIM@hud_ammo_txtclips?$AA@ @ 0x003D8520
// match: ??_C@_0BB@GEICFDKH@hud_ammo_txtammo?$AA@ @ 0x003D8534
// match: ??_C@_08FHKINLPF@hud_ammo?$AA@ @ 0x003D8548
// match: ??_C@_0BC@JCIFGEBB@hud_ammo_grenicon?$AA@ @ 0x003D8554
// match: ??_C@_0O@EGEHPIMJ@hud_ammo_root?$AA@ @ 0x003D8568
// match: ??_C@_0BC@CDNDOOBI@hud_posture_prone?$AA@ @ 0x003D8578
// match: ??_C@_0BD@GLMIIAGI@hud_posture_crouch?$AA@ @ 0x003D858C
// match: ??_C@_0BC@NDMDCPGE@hud_posture_stand?$AA@ @ 0x003D85A0
// match: ??_C@_0M@BDLCBAPE@hud_posture?$AA@ @ 0x003D85B4
// match: ??_C@_0BG@LPDBONF@Objective_german_flag?$AA@ @ 0x003D85C0
// match: ??_C@_0BG@PFKBKMNO@Objective_soviet_flag?$AA@ @ 0x003D85D8
// match: ??_C@_0BI@CEFJHBIB@Objective_american_flag?$AA@ @ 0x003D85F0
// match: ??_C@_0BH@EBENIBHN@Objective_british_flag?$AA@ @ 0x003D8608
// match: ??_C@_0BH@OFFLGKCK@hud_bomb_location_dest?$AA@ @ 0x003D8620
// match: ??_C@_0BC@EFIMDHBJ@hud_bomb_location?$AA@ @ 0x003D8638
// match: ??_C@_0BA@FLJLMJKA@hud_bomb_placed?$AA@ @ 0x003D864C
// match: ??_C@_0BF@MGDJJEOK@hud_german_objective?$AA@ @ 0x003D865C
// match: ??_C@_0BF@CGEFKHOK@hud_allied_objective?$AA@ @ 0x003D8674
// match: ??_C@_0BH@FMBBJEFA@hud_compass_star_pulse?$AA@ @ 0x003D868C
// match: ??_C@_0BB@HMFNFIMP@hud_compass_star?$AA@ @ 0x003D86A4
// match: ??_C@_0P@EPNANKLN@hud_compass_bg?$AA@ @ 0x003D86B8
// match: ??_C@_0BC@MGKAFOLF@hud_compass_glass?$AA@ @ 0x003D86C8
// match: ??_C@_0M@OPPLPMDP@hud_compass?$AA@ @ 0x003D86DC
// match: ??_C@_0BG@KIJKLDDI@hud_action_disarmmine?$AA@ @ 0x003D86E8
// match: ??_C@_0BF@JJGFLJFD@hud_action_text_dump?$AA@ @ 0x003D8700
// match: ??_C@_0BD@CBOKBLFD@hud_action_mountMG?$AA@ @ 0x003D8718
// match: ??_C@_0BA@BKAMEPND@hud_action_bomb?$AA@ @ 0x003D872C
// match: ??_C@_0BG@KDJIINFG@hud_action_rollbarrel?$AA@ @ 0x003D873C
// match: ??_C@_0BE@CDKLKFFN@hud_action_dismount?$AA@ @ 0x003D8754
// match: ??_C@_0BI@GOJJAIBG@hud_action_drivevehicle?$AA@ @ 0x003D8768
// match: ??_C@_0BI@JJFLHJL@hud_action_healfriendly?$AA@ @ 0x003D8780
// match: ??_C@_0BE@FPHMIBIB@hud_action_opendoor?$AA@ @ 0x003D8798
// match: ??_C@_0BD@OHOKECGD@hud_action_openbox?$AA@ @ 0x003D87AC
// match: ??_C@_0BC@JGJJFMH@hud_action_gogogo?$AA@ @ 0x003D87C0
// match: ??_C@_0P@NEGOHCJM@hud_action_get?$AA@ @ 0x003D87D4
// match: ??_C@_0BB@DABOOENI@hud_action_radio?$AA@ @ 0x003D87E4
// match: ??_C@_0M@NHHGHAIG@hud_actions?$AA@ @ 0x003D87F8
// match: ??_C@_08LMJKIGJP@codfontn?$AA@ @ 0x003D8804
// match: ??_C@_08IOKMOEBN@codfontl?$AA@ @ 0x003D8810
// match: ??_C@_07CGHBAICO@HUD_3RD?$AA@ @ 0x003D881C
// match: ??_C@_07ILPBDFFP@HUD_2ND?$AA@ @ 0x003D8824
// match: ??_C@_07MHHILIMD@HUD_1ST?$AA@ @ 0x003D882C
// match: ??_C@_0BI@GOEGKKHE@HUD_WAITINGFORHOST_HOST?$AA@ @ 0x003D8834
// match: ??_C@_0BK@JPOFDJFF@HUD_WAITINGFORHOST_CLIENT?$AA@ @ 0x003D884C
// match: ??_C@_0BI@KJEOBDNL@HUD_STOPSPECTATING_XBOX?$AA@ @ 0x003D8868
// match: ??_C@_0BB@EIBHECEB@HUD_SPECTATORCAM?$AA@ @ 0x003D8880
// match: ??_C@_0O@KICJPILD@HUD_FOLLOWING?$AA@ @ 0x003D8894
// match: ??_C@_0BJ@BHDFIDCC@hud_ctf_flag_icon_german?$AA@ @ 0x003D88A4
// match: ??_C@_0BJ@OIPJHLAJ@hud_ctf_flag_icon_soviet?$AA@ @ 0x003D88C0
// match: ??_C@_0BL@FDHEIHJM@hud_ctf_flag_icon_american?$AA@ @ 0x003D88DC
// match: ??_C@_0P@DAAEIGLD@hud_ctf_german?$AA@ @ 0x003D88F8
// match: ??_C@_0P@MPMIHOJI@hud_ctf_soviet?$AA@ @ 0x003D8908
// match: ??_C@_0BB@ELEEOPHJ@hud_ctf_american?$AA@ @ 0x003D8918
// match: ??_C@_0BG@EEHFDNND@You?5are?5following?5XXX?$AA@ @ 0x003D892C
// match: ??_C@_0BA@GLFPFMAL@Press?5?$BE?5to?5skip?$AA@ @ 0x003D8944
// match: ??_C@_02PLJDPFIO@00?$AA@ @ 0x003D8954
// match: ??_C@_0BB@NHKEPCBD@hud_bottom_shade?$AA@ @ 0x003D8958
// match: ??_C@_0O@DIGOKOH@hud_top_shade?$AA@ @ 0x003D896C
// match: ??_C@_0O@POPDCNJB@hud_following?$AA@ @ 0x003D897C
// match: ??_C@_0BE@BAIEJLIL@hud_stop_spectating?$AA@ @ 0x003D898C
// match: ??_C@_0O@LHLPBCEE@hud_spectator?$AA@ @ 0x003D89A0
// match: ??_C@_0BA@OADHILAD@hud_top_players?$AA@ @ 0x003D89B0
// match: ??_C@_0BD@EKGIJGPE@hud_objective_text?$AA@ @ 0x003D89C0
// match: ??_C@_0BF@IIIFFJIK@hud_enemy_team_score?$AA@ @ 0x003D89D4
// match: ??_C@_0BF@HBLLOHOO@hud_enemy_team_frame?$AA@ @ 0x003D89EC
// match: ??_C@_0BG@HAKLKEK@hud_ctf_flag_captured?$AA@ @ 0x003D8A04
// match: ??_C@_0BK@EHGBCGIL@hud_ctf_flag_icon_british?$AA@ @ 0x003D8A1C
// match: ??_C@_0BG@PCPNAIIK@hud_player_team_score?$AA@ @ 0x003D8A38
// match: ??_C@_0BA@MAEOLEFM@hud_ctf_british?$AA@ @ 0x003D8A50
// match: ??_C@_0BG@LMDLGOO@hud_player_team_frame?$AA@ @ 0x003D8A60
// match: ??_C@_0P@LHJEDDIN@hud_score_root?$AA@ @ 0x003D8A78
// match: ??_C@_0BH@LIFDCEMD@hud_player_score_value?$AA@ @ 0x003D8A88
// match: ??_C@_0P@FPNBDAHJ@hud_ctf_border?$AA@ @ 0x003D8AA0
// match: ??_C@_0BC@IDOPFDGI@hud_timer_seconds?$AA@ @ 0x003D8AB0
// match: ??_C@_0BC@IFNGFLDE@hud_timer_minutes?$AA@ @ 0x003D8AC4
// match: ??_C@_0BA@IOJBGJHK@hud_timer_colon?$AA@ @ 0x003D8AD8
// match: ??_C@_0BF@KPNNHLBP@hud_multiplayer_root?$AA@ @ 0x003D8AE8
// match: ??_C@_0P@PHJPNJB@hud_bomb_frame?$AA@ @ 0x003D8B00
// match: ??_C@_08PKPBHOD@hud_bomb?$AA@ @ 0x003D8B10
// match: ??_C@_0BD@KAAJJEEE@hud_healthpack_txt?$AA@ @ 0x003D8B1C
// match: ??_C@_0BG@HEDAPIDO@hud_inventory_medpack?$AA@ @ 0x003D8B30
// match: ??_C@_0P@BACHILAI@hud_healthpack?$AA@ @ 0x003D8B48
// match: ??_C@_0P@NJIHOBEF@hud_health_bar?$AA@ @ 0x003D8B58
// match: ??_C@_0BB@PMPLCAIN@hud_health_frame?$AA@ @ 0x003D8B68
// match: ??_C@_0L@CIJIONHO@hud_health?$AA@ @ 0x003D8B7C
// match: ??_C@_0BB@GGFGOCOF@hud_soldier_root?$AA@ @ 0x003D8B88
// match: ??_C@_0BC@EGPGANIC@hud_subtitle_text?$AA@ @ 0x003D8B9C
// match: ??_C@_0N@DILMIDHL@hud_subtitle?$AA@ @ 0x003D8BB0
// match: ??_C@_08HAFDOBNI@hud_root?$AA@ @ 0x003D8BC0
// match: __real@3eb33333 @ 0x003D8BCC
// match: __real@c3340000 @ 0x003D8BD0
// match: ??_C@_03MAAJKOHM@t10?$AA@ @ 0x003D8BD4
// match: ??_C@_0CE@KFIMNKPN@Attempting?5to?5load?5new?5HUD?5font?3@ @ 0x003D8BD8
// match: ??_C@_0CJ@MGLHOLF@Unloading?5current?5font?3?5?$CFs?5for?5n@ @ 0x003D8BFC
// match: __real@3d8f5c29 @ 0x003D8C28
// match: __real@3f955555 @ 0x003D8C2C
// match: __real@c2700000 @ 0x003D8C30
// match: __real@41940000 @ 0x003D8C34
// match: ??_C@_02FGAJKBDK@B?3?$AA@ @ 0x003D8C38
// match: ??_C@_02FEEPBPGD@A?3?$AA@ @ 0x003D8C3C
// match: ??_C@_04HDOCAJNK@?$CFs?$CFs?$AA@ @ 0x003D8C40
// match: ??_C@_0BB@GMHGFHKF@Capture?5The?5Flag?$AA@ @ 0x003D8C48
// match: ??_C@_0BA@KHHNIIJE@Team?5Deathmatch?$AA@ @ 0x003D8C5C
// match: ??_C@_0L@NKMACCB@Deathmatch?$AA@ @ 0x003D8C6C
// match: ??_C@_02JINPPBEP@No?$AA@ @ 0x003D8C78
// match: ??_C@_03CCLAEDDF@Yes?$AA@ @ 0x003D8C7C
// match: ??_C@_08CNMBOIMN@1?5minute?$AA@ @ 0x003D8C80
// match: ??_C@_08OHNNABNB@No?5limit?$AA@ @ 0x003D8C8C
// match: ??_C@_09PKIODIAL@?$CFs?5?$CFd?3?5?$CFs?$AA@ @ 0x003D8C98
// match: __ehhandler$??0type_DC400@@QAE@XZ>1>8 @ 0x0041CCBC
// match: __ehhandler$??0type_DC400@@QAE@XZ>1 @ 0x0041CCFC
// match: __ehhandler$??1type_DC400@@QAE@XZ>1>8 @ 0x0041CD18
// match: __ehhandler$??1type_DC400@@QAE@XZ>1 @ 0x0041CD38
// match: __ehhandler$?sub_DC5F0@type_DC400@@QAEHPAURwCamera@@@Z>1>8 @ 0x0041CD54
// match: __ehhandler$?sub_DC5F0@type_DC400@@QAEHPAURwCamera@@@Z>1 @ 0x0041CD5C
// match: __ehhandler$?sub_DD1C0@type_DC400@@QAEXM@Z>1>8 @ 0x0041CD78
// match: __ehhandler$?sub_DD1C0@type_DC400@@QAEXM@Z>1 @ 0x0041CD80
// match: __ehhandler$?sub_DFFC0@type_DC400@@QAEXUtype_D48D0@@@Z>1>8 @ 0x0041CD9C
// match: __ehhandler$?sub_DFFC0@type_DC400@@QAEXUtype_D48D0@@@Z>1 @ 0x0041CDA4
// match: __ehhandler$?sub_E0E90@type_DC400@@QAEXXZ>1>8 @ 0x0041CDC0
// match: __ehhandler$?sub_E0E90@type_DC400@@QAEXXZ>1 @ 0x0041CE18
// match: __ehhandler$?sub_E4030@type_DC400@@QAEXM@Z>1>8 @ 0x0041CE34
// match: __ehhandler$?sub_E4030@type_DC400@@QAEXM@Z>1 @ 0x0041CE3C
// match: __ehhandler$?sub_E7600@type_DC400@@QAEXPAUtype_DC400_E0@@@Z>1>8 @ 0x0041CE58
// match: __ehhandler$?sub_E7600@type_DC400@@QAEXPAUtype_DC400_E0@@@Z>1 @ 0x0041CE78
// match: __ehhandler$?sub_E7EF0@type_DC400@@QAEXXZ>1>8 @ 0x0041CE94
// match: __ehhandler$?sub_E7EF0@type_DC400@@QAEXXZ>1 @ 0x0041CE9C
// match: __ehhandler$?_Xlen@?$vector@HV?$allocator@H@std@@@std@@IBEXXZ>1>8 @ 0x0041CEB8
// match: __ehhandler$?_Xlen@?$vector@HV?$allocator@H@std@@@std@@IBEXXZ>1 @ 0x0041CEC0
// match: __ehhandler$?_Xlen@?$vector@IV?$allocator@I@std@@@std@@IBEXXZ>1>8 @ 0x0041CEDC
// match: __ehhandler$?_Xlen@?$vector@IV?$allocator@I@std@@@std@@IBEXXZ>1 @ 0x0041CEE4
// match: .CRT$XCU+0 @ 0x00427008
// match: .CRT$XCU+4 @ 0x0042700C
// match: .CRT$XCU+8 @ 0x00427010
// match: .CRT$XCU+12 @ 0x00427014
// match: .CRT$XCU+16 @ 0x00427018
// match: .CRT$XCU+20 @ 0x0042701C
// match: .CRT$XCU+24 @ 0x00427020
// match: .CRT$XCU+28 @ 0x00427024
// match: .CRT$XCU+32 @ 0x00427028
// match: ?flt_4293C0@@3MA @ 0x004293C0
// match: ?flt_4293C4@@3MA @ 0x004293C4
// match: ?dword_4293C8@@3HA @ 0x004293C8
// match: ?dword_4293CC@@3HA @ 0x004293CC
// match: ?dword_4293D0@@3PAPAHA @ 0x004293D0
// match: ?flt_4293D8@@3MA @ 0x004293D8
// match: ?flt_4293DC@@3MA @ 0x004293DC
// match: ?flt_4293E0@@3MA @ 0x004293E0
// match: ?flt_4293E4@@3MA @ 0x004293E4
// match: ?flt_4293E8@@3MA @ 0x004293E8
// match: ?flt_4293EC@@3MA @ 0x004293EC
// match: ?flt_4293F0@@3MA @ 0x004293F0
// match: ?flt_4293F4@@3MA @ 0x004293F4
// match: ?flt_4293F8@@3MA @ 0x004293F8
// match: ?flt_4293FC@@3MA @ 0x004293FC
// match: ?dword_429400@@3HA @ 0x00429400
// match: ?dword_429404@@3HA @ 0x00429404

// match: _$E2 @ 0x0030B2C0
// match: _$E3 @ 0x0030E410
// match: _$E5 @ 0x0030B2F0
// match: _$E6 @ 0x0030E430
// match: _$E8 @ 0x0030B310
// match: _$E9 @ 0x0030E440
// match: _$E11 @ 0x0030B330
// match: _$E12 @ 0x0030E450
// match: _$E14 @ 0x0030B360
// match: _$E15 @ 0x0030E470
// match: _$E17 @ 0x0030B380
// match: _$E18 @ 0x0030E480
// match: _$E20 @ 0x0030B3A0
// match: _$E21 @ 0x0030E490
// match: _$E23 @ 0x0030B3C0
// match: _$E25 @ 0x0030B3E0
// match: ??0type_DC400@@QAE@XZ @ 0x000DC400
// match: __ehhandler$??0type_DC400@@QAE@XZ-0x52 @ 0x00300D10
// match: __ehhandler$??0type_DC400@@QAE@XZ @ 0x00300D62
// sp-match: ??0type_DC400@@QAE@XZ @ 0x000A99B0

type_DC400::type_DC400()
{
    unk_0C = 0;
}

// match: ??0type_DC500@@QAE@XZ @ 0x000DC500
// match: ??0type_DC530@@QAE@XZ @ 0x000DC530
// sp-match: ??0type_DC530@@QAE@XZ @ 0x000A76C0
// sp-match: ??0type_DC500@@QAE@XZ @ 0x000A76B0
// The CRT's inline ceilf (math.h), kept out of line in single player for sub_E5480 (SP 0xA875B calls it):
// sp-match: _ceilf @ 0x000A7690

// match: ??1type_DC400@@QAE@XZ @ 0x000DC560
// match: __ehhandler$??1type_DC400@@QAE@XZ-0x42 @ 0x00300D70
// match: __ehhandler$??1type_DC400@@QAE@XZ @ 0x00300DB2
// sp-match: ??1type_DC400@@QAE@XZ @ 0x000A76D0
type_DC400::~type_DC400()
{
}

// match: ?sub_DC5F0@type_DC400@@QAEHPAURwCamera@@@Z @ 0x000DC5F0
// match: __ehhandler$?sub_DC5F0@type_DC400@@QAEHPAURwCamera@@@Z-0xB @ 0x00300DC0
// match: __ehhandler$?sub_DC5F0@type_DC400@@QAEHPAURwCamera@@@Z @ 0x00300DCB
// sp-match: ?sub_DC5F0@type_DC400@@QAEHPAURwCamera@@@Z @ 0x000AC7D0
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
RwInt32 type_DC400::sub_DC5F0(RwCamera *arg_0)
{
    RwRGBAReal var_38;
    RwInt32 var_28;
    RwInt32 ebp_24;
    RwInt32 var_20;
    RwInt32 l1C;
    RwInt32 m_18;
    RwInt32 ebp_14;
    RwInt32 lv_10;

    unk_B8 = -1.0f;
    unk_BC = -1;
    unk_C0 = 0;
    unk_C4 = -1;
    unk_C8 = -1;
    unk_CC = -1;
    unk_D0 = -1;
    unk_D4 = 0;
    unk_08 = 0;
    unk_1A024 = 0;
    unk_1A020 = dword_4F28F0->get_unk_180();
    for (ebp_14 = 0; ebp_14 < type_DC400_items; ebp_14++)
    {
        unk_E0[ebp_14].unk_00[0] = 0;
        unk_E0[ebp_14].unk_20 = 0;
        unk_E0[ebp_14].unk_24 = flt_4B8F14;
        unk_E0[ebp_14].unk_28 = 0;
        unk_E0[ebp_14].unk_2C = 0;
        unk_E0[ebp_14].unk_30 = 0;
        unk_E0[ebp_14].unk_34.red = unk_E0[ebp_14].unk_34.blue = unk_E0[ebp_14].unk_34.green =
            unk_E0[ebp_14].unk_34.alpha = 1.0f;
        unk_E0[ebp_14].unk_44 = 0;
        unk_E0[ebp_14].unk_48 = 0;
        unk_E0[ebp_14].unk_50 = 1;
        unk_E0[ebp_14].unk_58 = 0;
        unk_E0[ebp_14].unk_60[0] = 0;
#ifdef CODFH_SP // shape: single player's ten label items are 65 to 74 (SP 0xAC7D0)
        if (ebp_14 >= 65 && ebp_14 <= 74)
#else
        if (ebp_14 >= 106 && ebp_14 < 122)
#endif
        {
            unk_E0[ebp_14].unk_24 = 1.0f;
        }
        for (m_18 = 0; m_18 < 4; m_18++)
        {
            unk_E0[ebp_14].unk_E0[m_18].x = unk_E0[ebp_14].unk_E0[m_18].y =
                unk_E0[ebp_14].unk_E0[m_18].z = 0.0f;
        }
        for (l1C = 0; l1C < 4; l1C++)
        {
            unk_E0[ebp_14].unk_118[l1C].emissiveColor = 0xFFFFFFFF;
        }
        unk_E0[ebp_14].unk_110 = 0;
        unk_E0[ebp_14].unk_114 = 0;
        unk_E0[ebp_14].unk_188.x = 0.0f;
        unk_E0[ebp_14].unk_188.y = 0.0f;
        unk_E0[ebp_14].unk_190.red = 0xFF;
        unk_E0[ebp_14].unk_190.green = 0xFF;
        unk_E0[ebp_14].unk_190.blue = 0xFF;
        unk_E0[ebp_14].unk_190.alpha = 0xFF;
        unk_E0[ebp_14].unk_54 = 0;
        unk_E0[ebp_14].unk_1E0 = 0.0f;
        unk_E0[ebp_14].unk_2A8 = 0;
        unk_E0[ebp_14].unk_5C = 0;
        unk_E0[ebp_14].unk_1E4 = unk_E0[ebp_14].unk_1E8.x = unk_E0[ebp_14].unk_1E8.y =
            unk_E0[ebp_14].unk_1E8.z = 0.0f;
        unk_E0[ebp_14].unk_1F4.x = unk_E0[ebp_14].unk_1F4.y = unk_E0[ebp_14].unk_1F4.z = 0.0f;
        unk_E0[ebp_14].unk_200 = 0;
        for (var_20 = 0; var_20 < type_DC400_children; var_20++)
        {
            unk_E0[ebp_14].unk_204[var_20] = 0;
        }
        unk_E0[ebp_14].unk_2A4 = 0;
        RwMatrixSetIdentity(&unk_E0[ebp_14].unk_1A0);
        unk_E0[ebp_14].unk_2AC = 0;
#ifndef CODFH_SP // MP only: single player's items have no unk_2B0..unk_2BC (SP 0xAC7D0 clears unk_2AC last)
        unk_E0[ebp_14].unk_2B0 = 0;
        unk_E0[ebp_14].unk_2B4 = 0;
        unk_E0[ebp_14].unk_2B8 = 0;
        unk_E0[ebp_14].unk_2BC = 1;
#endif
#ifndef CODFH_SP // MP only: single player's HUD has no +0x5C..+0xB7 block (include/types/type_DC400.h)
        unk_94 = -2;
#endif
    }
    unk_04 = ((type_4B86F8 *)&dword_4B86F8)->unk_00_4;
    unk_1A028 = 0;
    unk_1A02C = arg_0;
    unk_1A040 = 0;
    unk_1A044 = 0;
    unk_1A048 = 0;
    unk_1A04C[0] = 0;
#ifndef CODFH_SP // single player has one objective pointer (SP 0xAC7D0)
    unk_1A04C[1] = 0;
#endif
    memset(unk_1A054, 0, sizeof(unk_1A054));
    unk_1A0CC = 0;
    unk_1A0D0 = 0;
    unk_1A0A8 = 0;
    unk_1A0AC = 0;
    unk_1A0BC = 0.0f;
    unk_1A0B8 = 0.0f;
    unk_1A0B4 = 0.0f;
    unk_1A0B0 = 0.0f;
    unk_1A0C0 = 0;
    unk_1A0C4 = 0.0f;
    unk_1A0C8 = 0;
    for (ebp_24 = 0; ebp_24 < 5; ebp_24++)
    {
        unk_1A0D4[ebp_24].unk_00.z = 0.0f;
        unk_1A0D4[ebp_24].unk_00.y = 0.0f;
        unk_1A0D4[ebp_24].unk_00.x = 0.0f;
        unk_1A0D4[ebp_24].unk_0C = 0;
        unk_1A0D4[ebp_24].unk_10 = 0;
        unk_1A0D4[ebp_24].unk_14.sub_D48D0(0);
    }
    unk_1A14C.x = unk_1A14C.y = unk_1A154.x = unk_1A154.y = 1.0f;
    unk_10 = 1;
    unk_1A15C = 0;
    for (var_28 = 0; var_28 < type_DC400_labels; var_28++)
    {
        unk_1A1A8[var_28].unk_24 = 0;
#ifdef CODFH_SP // shape: single player's label items are 65 to 74 (SP 0xAC7D0)
        unk_1A1A8[var_28].unk_2C = var_28 + 65;
#else
        unk_1A1A8[var_28].unk_2C = var_28 + 106;
#endif
        unk_E0[unk_1A1A8[var_28].unk_2C].unk_190.alpha = 0;
        unk_E0[unk_1A1A8[var_28].unk_2C].unk_190.blue = 0;
        unk_E0[unk_1A1A8[var_28].unk_2C].unk_190.green = 0;
        unk_E0[unk_1A1A8[var_28].unk_2C].unk_190.red = 0;
        var_38.red = 0.0f;
        var_38.green = 0.0f;
        var_38.blue = 0.0f;
        var_38.alpha = 0.0f;
        sub_E7480(unk_1A1A8[var_28].unk_2C, &var_38);
    }
    unk_00 = 0;
    sub_DEB80(0);
    sub_DEEB0(0);
    sub_DEEF0(0);
    unk_1A4AC = 0;
    unk_1A4B4 = 0;
    unk_1A4B8 = 0;
    unk_1A4BC = 0;
    memset(unk_1A4C0, 0, sizeof(unk_1A4C0));
#ifndef CODFH_SP // MP only: single player's HUD has no +0x5C..+0xB7 block (include/types/type_DC400.h); no in-game screens
    unk_84 = -1.0f;
    unk_5C = 1.0f;
    unk_7C = 0;
    unk_80 = 0;
    for (lv_10 = 0; lv_10 < 5; lv_10++)
    {
        unk_60[lv_10].red = unk_60[lv_10].green = unk_60[lv_10].blue = 0xFF;
        unk_60[lv_10].alpha = 0xFF;
    }
    for (lv_10 = 0; lv_10 < 4; lv_10++)
    {
        unk_98[lv_10] = 0;
        unk_A8[lv_10] = 0;
    }
    unk_94 = -666;
    unk_90 = 0;
    unk_1A4B0 = new type_1FF250;
#endif
    return 1;
}

// The HUD's frame: the pending toggle (byte_4B8975) first, then the
// items' layout (sub_E6610). arg_0 is unused; a check compiled out of this
// build (an empty if on unk_00) shifts the registers that follow it.
// match: ?sub_DD180@type_DC400@@QAEXM@Z @ 0x000DD180
// sp-match: ?sub_DD180@type_DC400@@QAEXM@Z @ 0x000AA480
void type_DC400::sub_DD180(RwReal arg_0)
{
    if (byte_4B8975)
    {
        sub_DFDD0();
        byte_4B8975 = false;
    }
    if (unk_00)
    {
    }
    sub_E6610(&unk_E0[0]);
}

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
// sp-match: ?sub_DD1C0@type_DC400@@QAEXM@Z @ 0x000ACDB0
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
#ifndef CODFH_SP // MP only: the network game's items (SP 0xACDB0 has none)
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
#ifndef CODFH_SP // MP only: single player's HUD has no +0x5C..+0xB7 block (include/types/type_DC400.h) (the CTF icons)
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
#endif
            dword_4B9190->sub_E7050(0x50, (RwUInt32)Width * flt_4293F8, (RwUInt32)Height * flt_4293FC);
            sub_E09E0(0x51, 0);
            sub_E09E0(0x4B, 0);
            sub_E09E0(0x4C, 0);
            if (unk_4F7EB8.unk_384.sub_1B2480(v_24))
            {
                unk_E0[80].unk_2B8 += arg_0 * flt_3D8058;
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
                    sub_E0280(unk_4F7EB8.unk_04.sub_1B33C0(2));
                    sub_E02E0(unk_4F7EB8.unk_04.sub_1B33C0(4));
                }
                else
                {
                    sub_E0280(unk_4F7EB8.unk_04.sub_1B33C0(4));
                    sub_E02E0(unk_4F7EB8.unk_04.sub_1B33C0(2));
                }
                break;
            case 4:
                sub_E09E0(0x45, 0);
                sub_E09E0(0x47, 1);
                sub_E09E0(0x52, 0);
                sub_E09E0(0x54, 0);
                if (v_28 == 2)
                {
                    sub_E0280(unk_4F7EB8.unk_04.sub_1B33C0(2));
                    sub_E02E0(unk_4F7EB8.unk_04.sub_1B33C0(4));
                }
                else
                {
                    sub_E0280(unk_4F7EB8.unk_04.sub_1B33C0(4));
                    sub_E02E0(unk_4F7EB8.unk_04.sub_1B33C0(2));
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
                    sub_E0280(unk_4F7EB8.unk_04.sub_1B33C0(2));
                    sub_E02E0(unk_4F7EB8.unk_04.sub_1B33C0(4));
                }
                else
                {
                    sub_E0280(unk_4F7EB8.unk_04.sub_1B33C0(4));
                    sub_E02E0(unk_4F7EB8.unk_04.sub_1B33C0(2));
                }
                sub_E09E0(0x52, 1);
                sub_E09E0(0x45, 0);
                sub_E09E0(0x47, 0);
                break;
            case 1:
                sub_E0220(unk_4F7EB8.unk_04.sub_1B3360(v_24));
                sub_E09E0(0x45, 1);
                sub_E09E0(0x47, 0);
                sub_E09E0(0x52, 0);
                break;
            }
        }
#endif
#ifndef CODFH_SP // MP only: single player's HUD has no +0x5C..+0xB7 block (include/types/type_DC400.h) (unk_90: the scoreboard and console modes)
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
                if (((kujuUI::cScopeValidator *)&dword_4FB9E0)->sub_1CA260())
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
            flt_4B8B3C += arg_0 * flt_3D8058;
            if (flt_4B8B3C > 5000.0f)
            {
                sub_EACA0("Console initialized -- Standard Message", 0, 0);
                sub_EACA0("Console initialized -- High Level Message", 1, 0);
                sub_EACA0("Console initialized -- Low Level Message", 2, 0);
                flt_4B8B3C = 0;
            }
        }
#endif
#ifndef CODFH_SP // MP only: single player hides no inventory and lays out no items here (SP 0xACDB0)
        sub_E09E0(0x14, 0);
        sub_E6610(&unk_E0[0]);
#endif
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
#ifndef CODFH_SP
        if (unk_90 != 1 && v_1C->unk_1A48[v_1C->unk_1AE4])
#else
        if (v_1C->unk_1A48[v_1C->unk_1AE4])
#endif
        {
            sub_E08B0(v_1C->unk_1A48[v_1C->unk_1AE4]->sub_11D690());
        }
        sub_DFFC0(v_1C->unk_2104);
    }
    for (v_114 = 0; v_114 < type_DC400_labels; v_114++)
    {
        v_118 = unk_1A1A8[v_114].unk_28.sub_D4910();
        strcpy(unk_1A1A8[v_114].unk_00, "");
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

#ifdef CODFH_SP // single player colours a colour-coded name by its soldier's health (SP 0xACDB0), not green/red by side
                if (((type_3DAFC8 *)v_118)->unk_64C)
                {
                    RwReal v_sp_health;

                    v_sp_health = v_118->vf_17C();
                    if (v_sp_health < 0.0f)
                    {
                        v_sp_health = 0.0f;
                    }
                    if (v_sp_health > 0.5f)
                    {
                        v_sp_health = (v_sp_health - 0.5f) * 2.0f;
                        v_128.red = 1.0f - v_sp_health;
                        v_128.blue = v_sp_health * 0.25f;
                        v_128.green = 1.0f;
                    }
                    else
                    {
                        v_128.red = 1.0f;
                        v_128.green = v_sp_health * 2.0f;
                        v_128.blue = 0;
                    }
                }
                else
                {
                    v_128.red = 0;
                    v_128.blue = 0.25f;
                    v_128.green = 1.0f;
                }
#else
                v_128.red = 0;
                v_128.green = 0.75f;
                v_128.blue = 0;
                if (sub_1745A0(0) && ((type_10F710 *)sub_1745A0(0))->vf_24C(v_118))
                {
                    v_128.red = 0.75f;
                    v_128.green = 0;
                    v_128.blue = 0;
                }
#endif
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
    for (v_148 = 0; v_148 < type_DC400_items; v_148++)
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
                        unk_E0[v_148].unk_2C -= flt_3D8058 * arg_0;
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
#ifndef CODFH_SP // MP only: single player leaves the items' alphas to their fades (SP 0xACDB0)
            sub_E3B90(v_148, flt_4B8F18);
#endif
#ifndef CODFH_SP // MP only: single player's HUD has no +0x5C..+0xB7 block (include/types/type_DC400.h)
            sub_E3B90(0x49, unk_5C);
            sub_E3B90(0x4E, unk_5C);
#endif
        }
    }
#ifdef CODFH_SP // single player turns the compass only while unpaused (SP 0xACDB0); its crosshair is item 49
    if (unk_E0[29].unk_20 && !unk_04)
    {
        sub_E4030(arg_0);
    }
    if (unk_E0[49].unk_20)
    {
#else
    if (unk_E0[29].unk_20)
    {
        sub_E4030(arg_0);
    }
    if (unk_E0[90].unk_20)
    {
#endif
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
#ifdef CODFH_SP // shape: single player's t34 body and turret are items 59 and 60 (SP 0xACDB0)
                v_160 = 59;
                v_164 = 60;
#else
                v_160 = 100;
                v_164 = 101;
#endif
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
#ifdef CODFH_SP // shape: the heading normalised first (SP 0xACDB0)
                v_170 = sub_13F9E0(v_170);
                v_1D0 = ((RwReal)atan2(v_1C8, v_1C4)) * 57.295776f;
#else
                v_1D0 = ((RwReal)atan2(v_1C8, v_1C4)) * 57.295776f;
                v_170 = sub_13F9E0(v_170);
#endif
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
#ifdef CODFH_SP // shape: the time left over the length first (SP 0xACDB0)
        unk_1A0C4 = ((unk_1A0C0_f - unk_1A0AC) / unk_1A0C0_f) * unk_1A0BC;
#else
        unk_1A0C4 = (unk_1A0C0_f - unk_1A0AC) / unk_1A0C0_f * unk_1A0BC;
#endif
        unk_1A0AC += arg_0 * flt_3D8058 * 0.001f;
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
                unk_1A0D4[v_224].unk_0C -= arg_0 * flt_3D8058;
                if (unk_1A0D4[v_224].unk_0C <= 0.0f)
                {
                    unk_1A0D4[v_224].unk_10 = 0;
                    unk_1A0D4[v_224].unk_00.z = 0;
                    unk_1A0D4[v_224].unk_00.y = 0;
                    unk_1A0D4[v_224].unk_00.x = 0;
                    unk_1A0D4[v_224].unk_0C = 0;
                    unk_1A0D4[v_224].unk_14.sub_D48D0(0);
#ifdef CODFH_SP // shape: single player's hit indicators are items 0x5C to 0x60 (SP 0xACDB0)
                    sub_E09E0(v_224 + 0x5C, 0);
#else
                    sub_E09E0(v_224 + 0x8B, 0);
#endif
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
#ifdef CODFH_SP // shape: items 0x5C to 0x60 (SP 0xACDB0)
                sub_E5F60(v_224 + 0x5C, -(v_234 = sub_141240(&v_220->at, &unk_1A0D4[v_224].unk_00) + 180.0f));
                sub_E3B90(v_224 + 0x5C, unk_1A0D4[v_224].unk_0C / dword_4B9154);
#else
                sub_E5F60(v_224 + 0x8B, -(v_234 = sub_141240(&v_220->at, &unk_1A0D4[v_224].unk_00) + 180.0f));
                sub_E3B90(v_224 + 0x8B, unk_1A0D4[v_224].unk_0C / dword_4B9154);
#endif
            }
        }
    }
    sub_E74D0(2, (RwV2d *)&unk_4B8F90);
#ifndef CODFH_SP // MP only: no in-game screens
    unk_1A4B0->sub_2003E0(arg_0 / 60.0f);
#endif
#ifdef CODFH_SP // single player's pause (SP 0xACDB0): its fade-in timer, the pause message box, then the objectives' list fading in
    if (unk_04)
    {
        if (unk_1A4B4 >= dword_4B8F5C)
        {
            unk_1A4B8 = 1;
            unk_1A4B4 = 0;
        }
        else if (!unk_1A4B8)
        {
            unk_1A4B4 += arg_0 * flt_3D8058;
            if (unk_1A4B4 >= dword_4B8F5C)
            {
                if (dword_42926C)
                {
                    sub_186E70(0, 0, 0);
                }
                else if (sub_188350() != 4)
                {
                    sub_186E70(4, 0, 0);
                }
                unk_1A4B8 = 1;
                unk_1A4B4 = 0;
            }
        }
        if (!dword_42926C)
        {
            if (sub_188350() != 4)
            {
                if (++dword_sp_4B8978 >= 2)
                {
                    sub_186E70(4, 0, 0);
                }
            }
            else
            {
                dword_sp_4B8978 = 0;
            }
        }
        if (unk_1A4B8)
        {
            RwInt8 v_sp_1;
            type_4E56A0 *v_sp_8;
            bool v_sp_level;
            RwInt32 v_sp_n;

            v_sp_1 = byte_4E564D;
            v_sp_8 = sub_1708B0(v_sp_1);
            v_sp_level = sub_19B050() == 30;
            v_sp_n = 0;
            while (v_sp_8)
            {
                if ((v_sp_8->unk_04 & 2) && (!(v_sp_8->unk_04 & 4) || !v_sp_level))
                {
                    if (v_sp_n <= unk_1A4BC && v_sp_8->unk_14 < dword_4B8F5C)
                    {
                        v_sp_8->unk_14 += arg_0 * 133.33333f;
                    }
                    if (v_sp_8->unk_14 > dword_4B8F5C)
                    {
                        v_sp_8->unk_14 = dword_4B8F5C;
                    }
                    v_sp_n++;
                }
                v_sp_1 = sub_170890(v_sp_1);
                v_sp_8 = sub_1708B0(v_sp_1);
            }
        }
    }
#endif
}
// match: ?sub_DEB80@type_DC400@@QAEXH@Z @ 0x000DEB80
// sp-match: ?sub_DEB80@type_DC400@@QAEXH@Z @ 0x000A9A30
void type_DC400::sub_DEB80(RwInt32 arg_0)
{
    RwInt32 var_4;

    var_4 = 0;
    switch (arg_0)
    {
    case 0:
        var_4 = 1;
        break;
    case 2:
        var_4 = 0;
        break;
    case 1:
        var_4 = 0;
        break;
    case 3:
        var_4 = 0;
#ifdef CODFH_SP // shape: single player's items 0x37 and 0x36 (SP 0xA9A30)
        sub_E09E0(0x37, 0);
        sub_E09E0(0x36, 0);
#else
        sub_E09E0(0x60, 0);
        sub_E09E0(0x5F, 0);
#endif
        break;
    }
#ifdef CODFH_SP // shape: single player's crosshair arms are items 0x32 to 0x35 (SP 0xA9A30)
    sub_E09E0(0x32, var_4);
    sub_E09E0(0x33, var_4);
    sub_E09E0(0x34, var_4);
    sub_E09E0(0x35, var_4);
#else
    sub_E09E0(0x5B, var_4);
    sub_E09E0(0x5C, var_4);
    sub_E09E0(0x5D, var_4);
    sub_E09E0(0x5E, var_4);
#endif
    unk_1A4A8 = arg_0;
}

// match: ?sub_DEC40@type_DC400@@QAEXPAURwV3d@@0@Z @ 0x000DEC40
// sp-match: ?sub_DEC40@type_DC400@@QAEXPAURwV3d@@0@Z @ 0x000A7740
// Projects arg_0 through the main camera (dword_4E5C74) at the player's field
// of view, its view matrix scaled for the screen's aspect (and 4:3 widening),
// into *arg_4: x and y in pixels of its frame buffer scaled by the player's
// unk_538, z the depth; only between the near and far planes.
void type_DC400::sub_DEC40(RwV3d *arg_0, RwV3d *arg_4)
{
    RwCamera *var_8;
    type_10F710 *var_C;
    RwMatrix *var_10;
    RwReal var_14;
    RwReal var_18;
    RwRaster *var_1C;
    RwReal var_28;
    RwInt32 var_2C;
    RwInt32 var_30;
    RwInt32 var_34;
    RwInt32 var_38;
    RwReal var_3C;
    RwV3d var_48;
    RwMatrix var_A0;
    RwMatrix var_E0;
    RwReal var_E4;

    var_8 = (RwCamera *)dword_4E5C74;
    var_C = (type_10F710 *)sub_1745A0(dword_429EB0);
    if (!var_8 || !var_C || !arg_0 || !arg_4)
    {
        return;
    }
    RWS::CameraHelper::SetFieldOfView(var_C->unk_534, var_8);
    var_10 = &var_8->viewMatrix;
    // The clip planes go through the FPU (fld/fstp), which a float copy does
    // not give; a round trip through RwDouble does.
    var_14 = (RwReal)(RwDouble)var_8->nearPlane;
    var_18 = (RwReal)(RwDouble)var_8->farPlane;
    var_1C = var_8->frameBuffer;
    var_28 = var_C ? var_C->get_unk_538() : 1.0f;
    var_2C = var_1C->width;
    var_30 = var_1C->height;
    var_34 = (RwInt32)(var_2C * var_28);
    var_38 = (RwInt32)(var_30 * var_28);
    var_3C = 1.0f;
    if (dword_4CF9A8)
    {
        var_3C = 1.0f / 1.333f;
    }
    var_48.x = var_3C;
    var_48.y = (RwReal)(RwUInt32)Height / (RwReal)(RwUInt32)Width;
    var_48.z = 1.0f;
    RwMatrixSetIdentityMacro(&var_A0);
    RwMatrixScale(&var_A0, &var_48, rwCOMBINEPOSTCONCAT);
    RwMatrixMultiply(&var_E0, var_10, &var_A0);
    sub_141590(arg_4, arg_0, 1, &var_E0);
    if (arg_4->z > var_14 && arg_4->z < var_18)
    {
        var_E4 = 1.0f / arg_4->z;
#ifdef CODFH_SP // shape: the size times the depth first, then the coordinate (SP 0xA7740)
        arg_4->x = arg_4->x * (var_34 * var_E4);
        arg_4->y = arg_4->y * (var_38 * var_E4);
#else
        arg_4->x = var_34 * var_E4 * arg_4->x;
        arg_4->y = var_38 * var_E4 * arg_4->y;
#endif
    }
}

#ifdef CODFH_SP
// sp-match: ?sp_sub_A7930@@YAXPAUtype_DA580@@H@Z @ 0x000A7930
// Single player only (SP 0xA7930, no MP twin; the HUD's render calls it last): with arg_4
// set and the game paused, the Live manager (dword_4F3130) puts its message up at
// (30, 358) on the main camera; then it renders it. arg_0 (the HUD's font) is unused.
void sp_sub_A7930(type_DA580 *arg_0, RwInt32 arg_4)
{
    RwV2d var_10;
    RwV2d var_8;
    RwInt32 var_show;

    var_show = ((type_4B86F8 *)&dword_4B86F8)->unk_00_4;
    if (!arg_4)
    {
        var_show = 0;
    }
    if (var_show)
    {
        var_8.x = 30.0f;
        var_8.y = 358.0f;
        var_10.x = 0.0f;
        var_10.y = 358.0f;
        dword_4F3130.sp_sub_12BE30((RwCamera *)dword_4E5C74, &var_8, 0, 0, &var_10, 0, 0, 0);
    }
    dword_4F3130.sp_sub_12A970();
}
#endif

// match: ?sub_DEEB0@type_DC400@@QAEXH@Z @ 0x000DEEB0
// sp-match: ?sub_DEEB0@type_DC400@@QAEXH@Z @ 0x000A9AA0
void type_DC400::sub_DEEB0(RwInt32 arg_0)
{
    if (unk_1A020 && unk_1A4A8 != 3)
    {
#ifdef CODFH_SP // shape: single player's crosshair-over-buddy is item 0x36 (SP 0xA9AA0)
        sub_E09E0(0x36, arg_0);
#else
        sub_E09E0(0x5F, arg_0);
#endif
    }
}

// match: ?sub_DEEF0@type_DC400@@QAEXH@Z @ 0x000DEEF0
// sp-match: ?sub_DEEF0@type_DC400@@QAEXH@Z @ 0x000AA4B0
void type_DC400::sub_DEEF0(RwInt32 arg_0)
{
    if (unk_1A4A8 != 3)
    {
#ifdef CODFH_SP // shape: single player's enemy hit indicator is item 0x37 (SP 0xAA4B0)
        sub_E09E0(0x37, arg_0);
        sub_E3B90(0x37, 1.0f);
#else
        sub_E09E0(0x60, arg_0);
        sub_E3B90(0x60, 1.0f);
#endif
        unk_1A4AC = 0;
    }
}

// match: ?sub_DEF40@type_DC400@@QAEXM@Z @ 0x000DEF40
// sp-match: ?sub_DEF40@type_DC400@@QAEXM@Z @ 0x000AA4F0
void type_DC400::sub_DEF40(RwReal arg_0)
{
    RwReal var_4;

#ifdef CODFH_SP // shape: single player's items 0x36 and 0x37 (SP 0xAA4F0)
    if (sub_E0A10(0x36))
    {
        sub_E09E0(0x36, 0);
    }
    if (sub_E0A10(0x37))
    {
        var_4 = 1.0f - unk_1A4AC / unk_1A0C8;
        if (var_4 < 0.0f)
        {
            var_4 = 0.0f;
        }
        sub_E3B90(0x37, var_4);
        if (unk_1A4AC > unk_1A0C8)
        {
            sub_E09E0(0x37, 0);
        }
        unk_1A4AC += arg_0;
    }
#else
    if (sub_E0A10(0x5F))
    {
        sub_E09E0(0x5F, 0);
    }
    if (sub_E0A10(0x60))
    {
        var_4 = 1.0f - unk_1A4AC / unk_1A0C8;
        if (var_4 < 0.0f)
        {
            var_4 = 0.0f;
        }
        sub_E3B90(0x60, var_4);
        if (unk_1A4AC > unk_1A0C8)
        {
            sub_E09E0(0x60, 0);
        }
        unk_1A4AC += arg_0;
    }
#endif
}

// Stops the object sub_1FF250 returns. An inline with no address and so no
// database name, named for what it does. Evidence: the HUD's render keeps
// the stop's result in a slot among its inlines' (sub_DF000).
inline void stop_1FF250()
{
    type_1FBDA0_menu *r = sub_1FF250()->sub_200900();
}

// The HUD's render into arg_0 (its own camera by default), while it is
// shown: the soldiers' name labels placed over their heads in the view
// (when the player's camera is usable), then with the render states saved
// and set for the HUD: the in-game screen stopped at pages 6 and 7, the
// items and the rest unless a screen is up, the screen flash (unk_1A0A8)
// and the menus (sub_1FFE80); the states put back. A check compiled out
// of this build (an empty if on unk_00) shifts the registers of their
// restoring.
// match: ?sub_DF000@type_DC400@@QAEXPAURwCamera@@@Z @ 0x000DF000
// sp-match: ?sub_DF000@type_DC400@@QAEXPAURwCamera@@@Z @ 0x000AA590
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void type_DC400::sub_DF000(RwCamera *arg_0)
{
    RwReal local_A8;
    RwReal local_A4;
    RwReal var_A0;
    RwInt32 var9C;
    RwInt32 y98;
    RwMatrix *var_94;
    RwV3d stk_90;
    RwInt32 m_84;
    RwInt32 m_80;
    RwInt32 l7C;
    RwInt32 t78;
    RwReal stk_74;
    RwInt32 var_70;
    RwInt32 l6C;
    RwReal local_68;
    RwMatrix *local_64;
    RwReal local_60;
    RwInt32 l5C;
    RwRaster *m_58;
    RwV3d m_54;
    RwMatrix *frm_48;
    type_3DAFC8 *w44;
    RwInt32 s40;
    void *w3C;
    void *var_38;
    void *l34;
    type_62A60 *var30;
    void *ebp_2C;
    RwInt32 lcl_28;
    RwCamera *frm_24;
    void *var_20;
    void *l1C;
    type_10F710 *m_18;
    void *ebp_14;
    void *lv_10;
    void *var_C;
    void *bp_8;
    void *bp_4;

    dword_4B8980 = 0;
    if (!unk_10)
    {
        return;
    }
    if (!arg_0)
    {
        arg_0 = unk_1A02C;
    }
#ifndef CODFH_SP // MP only: single player renders whatever dword_42926C (SP 0xAA590 has no check)
    if (!dword_42926C)
    {
#ifndef CODFH_SP // MP only: no in-game screens
        RwCameraBeginUpdate(arg_0);
        unk_1A4B0->sub_1FFE80();
        RwCameraEndUpdate(arg_0);
#endif
        return;
    }
#endif
    RwCameraBeginUpdate(arg_0);
    lcl_28 = 1;
    m_18 = (type_10F710 *)sub_1745A0(dword_429EB0);
    var30 = 0;
    if (m_18)
    {
        var30 = (type_62A60 *)m_18->unk_2110.sub_D4910();
    }
    frm_24 = (RwCamera *)dword_4E5C74;
    if (!frm_24 || ((type_4B86F8 *)&dword_4B86F8)->unk_00_4 || !var30 || var30->get_unk_414())
    {
        lcl_28 = 0;
    }
    if (lcl_28)
    {
        RWS::CameraHelper::SetFieldOfView(((type_10F710 *)sub_1745A0(dword_429EB0))->unk_534, frm_24);
        for (s40 = 0; s40 < type_DC400_labels; s40++)
        {
            w44 = (type_3DAFC8 *)unk_1A1A8[s40].unk_28.sub_D4910();
            strcpy(unk_1A1A8[s40].unk_00, "");
            sub_E09E0(unk_1A1A8[s40].unk_2C, 0);
            if (unk_1A1A8[s40].unk_24 && w44 && frm_24)
            {
                local_64 = &frm_24->viewMatrix;
                // Read as doubles and narrowed: the image loads them through
                // the FPU (a plain float copy is a mov).
                stk_74 = (RwReal)(RwDouble)frm_24->nearPlane;
                local_60 = (RwReal)(RwDouble)frm_24->farPlane;
                m_58 = (RwRaster *)frm_24->frameBuffer;
                local_68 = m_18 ? m_18->get_unk_538() : 1.0f;
                l7C = m_58->width;
                t78 = m_58->height;
                m_80 = (RwInt32)(l7C * local_68);
                m_84 = (RwInt32)(t78 * local_68);
                var_70 = (RwInt32)((m_80 - l7C) * 0.5f);
                l6C = var_70 + l7C;
                var9C = (RwInt32)((m_84 - t78) * 0.5f);
                y98 = var9C + t78;
                l5C = RpHAnimIDGetIndex(w44->unk_284->get_unk_18(), 425);
                frm_48 = RpHAnimHierarchyGetMatrixArray(w44->unk_284->get_unk_18());
                var_94 = &frm_48[l5C];
                stk_90 = var_94->pos;
                stk_90.y += dword_4B9158;
                sub_141590(&m_54, &stk_90, 1, local_64);
                if (m_54.z > stk_74 && m_54.z < local_60)
                {
                    var_A0 = 1.0f / m_54.z;
#ifdef CODFH_SP // shape: the size times the depth first, then the coordinate (SP 0xAA590)
                    m_54.x = m_54.x * (m_80 * var_A0);
                    m_54.y = m_54.y * (m_84 * var_A0);
#else
                    m_54.x = m_80 * var_A0 * m_54.x;
                    m_54.y = m_84 * var_A0 * m_54.y;
#endif
                    m_54.y = m_84 - m_54.y;
                    local_A8 = m_54.x;
                    local_A4 = unk_1A028->sub_DA7B0(w44->unk_62C, 0.0f) * l7C;
                    if (var_70 > local_A8)
                    {
                        local_A8 += local_A4;
                    }
                    else if (local_A8 + local_A4 > l6C)
                    {
                        local_A8 -= local_A4;
                    }
#ifdef CODFH_SP // shape: the place on the left of each test (SP 0xAA590)
                    if (local_A8 > var_70 && local_A8 < l6C && m_54.y > var9C && y98 > m_54.y)
#else
                    if (var_70 < local_A8 && l6C > local_A8 && var9C < m_54.y && y98 > m_54.y)
#endif
                    {
                        m_54.x = m_54.x - var_70;
                        m_54.y = m_54.y - var9C;
                        strcpy(unk_1A1A8[s40].unk_00, w44->unk_62C);
                        sub_E6200(unk_1A1A8[s40].unk_2C, m_54.x, m_54.y);
                        sub_E09E0(unk_1A1A8[s40].unk_2C, 1);
                    }
                }
            }
            sub_E7380(unk_1A1A8[s40].unk_2C, unk_1A1A8[s40].unk_00);
        }
    }
    RwRenderStateGet(rwRENDERSTATEZWRITEENABLE, &w3C);
    RwRenderStateGet(rwRENDERSTATEZTESTENABLE, &var_20);
    RwRenderStateGet(rwRENDERSTATESHADEMODE, &lv_10);
    RwRenderStateGet(rwRENDERSTATETEXTUREFILTER, &ebp_14);
    RwRenderStateGet(rwRENDERSTATEVERTEXALPHAENABLE, &var_C);
    RwRenderStateGet(rwRENDERSTATECULLMODE, &ebp_2C);
    RwRenderStateGet(rwRENDERSTATESRCBLEND, &var_38);
    RwRenderStateGet(rwRENDERSTATEDESTBLEND, &l34);
    RwRenderStateGet(rwRENDERSTATEFOGENABLE, &l1C);
    RwRenderStateGet(rwRENDERSTATETEXTURERASTER, &bp_8);
    RwRenderStateGet(rwRENDERSTATETEXTUREADDRESS, &bp_4);
    RwRenderStateSet(rwRENDERSTATESRCBLEND, (void *)rwBLENDSRCALPHA);
    RwRenderStateSet(rwRENDERSTATEDESTBLEND, (void *)rwBLENDINVSRCALPHA);
    RwRenderStateSet(rwRENDERSTATEVERTEXALPHAENABLE, (void *)TRUE);
    RwRenderStateSet(rwRENDERSTATEZWRITEENABLE, (void *)TRUE);
    RwRenderStateSet(rwRENDERSTATEZTESTENABLE, (void *)TRUE);
    RwRenderStateSet(rwRENDERSTATESHADEMODE, (void *)rwSHADEMODEGOURAUD);
    RwRenderStateSet(rwRENDERSTATETEXTUREFILTER, (void *)rwFILTERLINEAR);
    RwRenderStateSet(rwRENDERSTATECULLMODE, (void *)rwCULLMODECULLNONE);
    RwRenderStateSet(rwRENDERSTATEFOGENABLE, (void *)FALSE);
    RwRenderStateSet(rwRENDERSTATETEXTURERASTER, (void *)NULL);
    RwRenderStateSet(rwRENDERSTATETEXTUREADDRESS, (void *)rwTEXTUREADDRESSCLAMP);
    RwRenderStateSet(rwRENDERSTATEALPHATESTFUNCTION, (void *)rwALPHATESTFUNCTIONGREATER);
    RwRenderStateSet(rwRENDERSTATEALPHATESTFUNCTIONREF, (void *)0);
#ifdef CODFH_SP // single player (SP 0xAA590): the items unless paused, the flash, the pause screen and its items (item 0x59), then the subtitles
    if (!unk_04)
    {
        sub_E5480(&unk_E0[0]);
    }
    if (unk_1A0A8)
    {
        sub_E5C60();
    }
    if (unk_04)
    {
        sp_sub_A81E0();
        if (sub_188350() != 1)
        {
            sp_sub_A7FB0();
        }
        sub_E5480(&unk_E0[0x59]);
    }
    sp_sub_A7930(dword_4B9190->unk_1A028, 1);
#else
    sub_E79C0();
    if (sub_1FF250() && sub_1FF250()->sub_200740()
        && (sub_1FF250()->get_unk_0C() == 6 || sub_1FF250()->get_unk_0C() == 7))
    {
        stop_1FF250();
    }
    if (!sub_1FF250() || !sub_1FF250()->sub_200740())
    {
        sub_E5480(&unk_E0[0]);
        sub_E7600(&unk_E0[0]);
        sub_E7D00();
        sub_E7EF0();
        sub_E82F0(arg_0);
    }
    if (unk_1A0A8)
    {
        sub_E5C60();
    }
#endif
#ifndef CODFH_SP // MP only: no in-game screens
    unk_1A4B0->sub_1FFE80();
#endif
    if (unk_00)
    {
    }
    RwRenderStateSet(rwRENDERSTATEZWRITEENABLE, w3C);
    RwRenderStateSet(rwRENDERSTATEZTESTENABLE, var_20);
    RwRenderStateSet(rwRENDERSTATEVERTEXALPHAENABLE, var_C);
    RwRenderStateSet(rwRENDERSTATESRCBLEND, var_38);
    RwRenderStateSet(rwRENDERSTATEDESTBLEND, l34);
    RwRenderStateSet(rwRENDERSTATEFOGENABLE, l1C);
    RwRenderStateSet(rwRENDERSTATETEXTURERASTER, bp_8);
    RwRenderStateSet(rwRENDERSTATETEXTUREADDRESS, bp_4);
    RwRenderStateSet(rwRENDERSTATESHADEMODE, lv_10);
    RwRenderStateSet(rwRENDERSTATETEXTUREFILTER, ebp_14);
    RwRenderStateSet(rwRENDERSTATECULLMODE, ebp_2C);
    RwCameraEndUpdate(arg_0);
    dword_4B897C = dword_4B8980;
}

// match: ?sub_DF880@type_DC400@@QAEXXZ @ 0x000DF880
// sp-match: ?sub_DF880@type_DC400@@QAEXXZ @ 0x000ACB80
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void type_DC400::sub_DF880()
{
    RwInt32 var_8;
    RwInt32 l4;

    sub_E0CC0();
    for (l4 = 0; l4 < 5; l4++)
    {
        unk_1A0D4[l4].unk_00.z = 0.0f;
        unk_1A0D4[l4].unk_00.y = 0.0f;
        unk_1A0D4[l4].unk_00.x = 0.0f;
        unk_1A0D4[l4].unk_0C = 0;
        unk_1A0D4[l4].unk_10 = 0;
        unk_1A0D4[l4].unk_14.sub_D48D0(0);
#ifdef CODFH_SP // shape: single player's hit indicators are items 0x5C to 0x60 (SP 0xACB80)
        sub_E09E0(l4 + 0x5C, 0);
#else
        sub_E09E0(l4 + 0x8B, 0);
#endif
    }
    for (var_8 = 0; var_8 < type_DC400_labels; var_8++)
    {
        unk_1A1A8[var_8].unk_24 = 0;
#ifdef CODFH_SP // shape: single player's buddy status labels are items 0x41 to 0x4A (SP 0xACB80)
        unk_1A1A8[var_8].unk_2C = var_8 + 0x41;
#else
        unk_1A1A8[var_8].unk_2C = var_8 + 106;
#endif
    }
    unk_1A0A8 = 0;
    unk_04 = 0;
    unk_00 = 0;
    unk_1A15C = 0;
    unk_1A4B4 = 0;
    unk_1A4B8 = 0;
    unk_1A4BC = 0;
    sub_E8470();
}

// match: ?sub_DF9F0@type_DC400@@QAEHXZ @ 0x000DF9F0
// sp-match: ?sub_DF9F0@type_DC400@@QAEHXZ @ 0x000A9AD0
RwInt32 type_DC400::sub_DF9F0()
{
    if (unk_1A028)
    {
        delete unk_1A028;
    }
    sub_E83D0(unk_1A024);
    unk_1A024 = 0;
    unk_1A15C = 0;
    unk_00 = 0;
    unk_1A4B4 = 0;
    unk_1A4B8 = 0;
    unk_1A4BC = 0;
#ifndef CODFH_SP // MP only: no in-game screens
    delete unk_1A4B0;
#endif
    return 1;
}

// match: ?sub_DFB00@type_DC400@@QAE_NPBD0@Z @ 0x000DFB00
// sp-match: ?sub_DFB00@type_DC400@@QAE_NPBD0@Z @ 0x000ACC90
bool type_DC400::sub_DFB00(const RwChar *arg_0, const RwChar *arg_4)
{
    unk_1A024 = sub_E8320(arg_0);
    sub_E52B0(0);
    sub_E0E90();
    unk_0C = 1;
    return true;
}

// match: ?sub_DFB40@type_DC400@@QAEXPAUtype_3D3548@@PAURwV3d@@@Z @ 0x000DFB40
// sp-match: ?sub_DFB40@type_DC400@@QAEXPAUtype_3D3548@@PAURwV3d@@@Z @ 0x000AAB90
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void type_DC400::sub_DFB40(type_3D3548 *arg_0, RwV3d *arg_4)
{
    RwV3d *var_24;
    RwV3d *var_20;
    RwReal l1C;
    type_3D3548 *m_18;
    RwInt32 ebp_14;
    RwInt32 lv_10;
    bool w9;
    RwMatrix *bp_8;
    RwCamera *bp_4;

    unk_1A0A8 = 1;
    unk_1A0AC = 0;
    w9 = false;
    bp_4 = (RwCamera *)dword_4E5C74;
    bp_8 = RwFrameGetMatrix(RwCameraGetFrame(bp_4));
    if (arg_0 || arg_4)
    {
        unk_4B9308.sub_EED30(0, 0, 0xB9, 1);
        if (arg_0)
        {
            for (lv_10 = 0; lv_10 < 5; lv_10++)
            {
                if (arg_0 == unk_1A0D4[lv_10].unk_14.sub_D4910())
                {
                    w9 = true;
                    break;
                }
            }
        }
        if (!w9)
        {
            for (ebp_14 = 0; ebp_14 < 5; ebp_14++)
            {
                if (!unk_1A0D4[ebp_14].unk_10)
                {
                    m_18 = sub_1745A0(0);
                    if (m_18)
                    {
                        var_24 = m_18->sub_CD550();
                        var_20 = arg_0 ? arg_0->sub_CD550() : arg_4;
                        RwV3dSub(&unk_1A0D4[ebp_14].unk_00, var_20, var_24);
                        RwV3dNormalize(&unk_1A0D4[ebp_14].unk_00, &unk_1A0D4[ebp_14].unk_00);
                        unk_1A0D4[ebp_14].unk_0C = dword_4B9154;
                        unk_1A0D4[ebp_14].unk_10 = 1;
                        unk_1A0D4[ebp_14].unk_14.sub_D48D0(arg_0);
                        l1C = sub_141240(&bp_8->at, &unk_1A0D4[ebp_14].unk_00) + 180.0f;
#ifdef CODFH_SP // shape: single player's hit indicators are items 0x5C to 0x60 (SP 0xAAB90)
                        sub_E5F60(ebp_14 + 0x5C, -l1C);
                        sub_E3B90(ebp_14 + 0x5C, 1.0f);
                        sub_E09E0(ebp_14 + 0x5C, 1);
#else
                        sub_E5F60(ebp_14 + 0x8B, -l1C);
                        sub_E3B90(ebp_14 + 0x8B, 1.0f);
                        sub_E09E0(ebp_14 + 0x8B, 1);
#endif
                    }
                    break;
                }
            }
        }
    }
    sub_128C20(unk_1A0CC, (RwReal)unk_1A0D0, (RwReal)unk_1A0D0);
}

// match: ?sub_DFDD0@type_DC400@@QAEXXZ @ 0x000DFDD0
// sp-match: ?sub_DFDD0@type_DC400@@QAEXXZ @ 0x000A9B30
void type_DC400::sub_DFDD0()
{
    dword_4CF9A8 ^= 1;
    sub_E70D0(&unk_E0[0]);
}

// match: ?sub_DFE00@type_DC400@@QAEXM@Z @ 0x000DFE00
// sp-match: ?sub_DFE00@type_DC400@@QAEXM@Z @ 0x000AAD20
void type_DC400::sub_DFE00(RwReal arg_0)
{
    if (unk_B8 == arg_0)
    {
        return;
    }
    if (unk_E0[4].unk_20)
    {
        if (arg_0 < 0.0f)
        {
            arg_0 = 0.0f;
        }
        if (arg_0 > 1.0f)
        {
            arg_0 = 1.0f;
        }
        unk_B8 = arg_0;
        sub_E6270(6, 1.0f, unk_B8);
    }
    sub_E3B50(4);
    sub_E3B50(0xE);
    sub_E3B50(7);
}

// match: ?sub_DFEB0@type_DC400@@QAEX_NPAUtype_3D3548@@@Z @ 0x000DFEB0
// sp-match: ?sub_DFEB0@type_DC400@@QAEX_NPAUtype_3D3548@@@Z @ 0x000ACCD0
void type_DC400::sub_DFEB0(bool arg_0, type_3D3548 *arg_4)
{
#ifdef CODFH_SP // shape: single player's buddy health is item 0x61 (SP 0xACCD0)
    if (unk_E0[0x61].unk_20)
    {
        if (arg_0)
        {
            sub_E0A30(0x61, 1);
        }
        else
        {
            sub_E0A30(0x61, -1);
        }
#else
    if (unk_E0[0x90].unk_20)
    {
        if (arg_0)
        {
            sub_E0A30(0x90, 1);
        }
        else
        {
            sub_E0A30(0x90, -1);
        }
#endif
        unk_00 = arg_0;
        if (arg_4)
        {
            if (arg_4->vf_014() || arg_4->vf_010())
            {
                sub_DFF40(0);
            }
            else
            {
                sub_DFF40(1);
            }
        }
    }
}

// match: ?sub_DFF40@type_DC400@@QAEXH@Z @ 0x000DFF40
// sp-match: ?sub_DFF40@type_DC400@@QAEXH@Z @ 0x000AADB0
void type_DC400::sub_DFF40(RwInt32 arg_0)
{
    RwInt32 var_4;

    var_4 = arg_0;
    unk_1A1A4 = var_4;
    switch (var_4)
    {
#ifdef CODFH_SP // shape: single player's buddy icon is item 0x62 (SP 0xAADB0)
    case 1:
        sub_E39B0(0x62, "hud_person_buddy_health", 1);
        break;
    case 2:
        sub_E39B0(0x62, "hud_m12_buddy_health", 1);
        break;
    default:
        sub_E39B0(0x62, "hud_t34_buddy_health", 1);
        break;
#else
    case 1:
        sub_E39B0(0x91, "hud_person_buddy_health", 1);
        break;
    case 2:
        sub_E39B0(0x91, "hud_m12_buddy_health", 1);
        break;
    default:
        sub_E39B0(0x91, "hud_t34_buddy_health", 1);
        break;
#endif
    }
}

// match: ?sub_DFFC0@type_DC400@@QAEXUtype_D48D0@@@Z @ 0x000DFFC0
// match: __ehhandler$?sub_DFFC0@type_DC400@@QAEXUtype_D48D0@@@Z-0x8 @ 0x00300E00
// match: __ehhandler$?sub_DFFC0@type_DC400@@QAEXUtype_D48D0@@@Z @ 0x00300E08
// sp-match: ?sub_DFFC0@type_DC400@@QAEXUtype_D48D0@@@Z @ 0x000ACD40
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void type_DC400::sub_DFFC0(type_D48D0 arg_0)
{
    RwReal var_14;
    type_3D3548 *lv_10;

    lv_10 = arg_0.sub_D4910();
#ifdef CODFH_SP // shape: single player's buddy items 0x61 and 0x64 (SP 0xACD40)
    if (lv_10 && unk_E0[0x61].unk_20)
#else
    if (lv_10 && unk_E0[0x90].unk_20)
#endif
    {
        if (lv_10->unk_28_9)
        {
            sub_DFEB0(false, 0);
        }
        else
        {
            var_14 = lv_10->vf_17C();
            if (var_14 < 0.0f)
            {
                var_14 = 0.0f;
            }
#ifdef CODFH_SP // shape: item 0x64 (SP 0xACD40)
            sub_E6270(0x64, var_14, 1.0f);
#else
            sub_E6270(0x93, var_14, 1.0f);
#endif
        }
    }
}

#ifndef CODFH_SP // MP only: no single-player twin, it sets unk_84 (absent there)
// match: ?sub_E0080@type_DC400@@QAEXM@Z @ 0x000E0080
void type_DC400::sub_E0080(RwReal arg_0)
{
    if (unk_84 == arg_0)
    {
        return;
    }
    if (unk_E0[0x94].unk_20)
    {
        if (arg_0 < 0.0f)
        {
            arg_0 = 0.0f;
        }
        if (arg_0 > 1.0f)
        {
            arg_0 = 1.0f;
        }
        unk_84 = arg_0;
        sub_E6270(0x96, 1.0f, unk_84);
    }
}
#endif

// match: ?sub_E0110@type_DC400@@QAEXM@Z @ 0x000E0110
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void type_DC400::sub_E0110(RwReal arg_0)
{
    RwChar var_1C[0x10];
    RwUInt32 var_8;
    RwInt32 l4;

    if (unk_E0[0x43].unk_20 && unk_E0[0x42].unk_20 && unk_E0[0x44].unk_20)
    {
        l4 = (RwInt32)floorf(arg_0 / 60.0f);
        var_8 = (RwUInt32)arg_0 % 60;
        sprintf(var_1C, "%d", l4);
        sub_E7380(0x43, var_1C);
        sprintf(var_1C, ":");
        sub_E7380(0x42, var_1C);
        sprintf(var_1C, "%.2d", var_8);
        sub_E7380(0x44, var_1C);
    }
    sub_E3B50(0x43);
    sub_E3B50(0x42);
    sub_E3B50(0x44);
}

// match: ?sub_E0220@type_DC400@@QAEXH@Z @ 0x000E0220
void type_DC400::sub_E0220(RwInt32 arg_0)
{
    RwChar var_14[0x10];

    if (unk_E0[0x46].unk_20)
    {
        sprintf(var_14, "%d", arg_0);
        sub_E7380(0x46, var_14);
    }
    sub_E3B50(0x46);
}

// match: ?sub_E0280@type_DC400@@QAEXH@Z @ 0x000E0280
void type_DC400::sub_E0280(RwInt32 arg_0)
{
    RwChar var_14[0x10];

    if (unk_E0[0x4A].unk_20)
    {
        sprintf(var_14, "%d", arg_0);
        sub_E7380(0x4A, var_14);
    }
    sub_E3B50(0x4A);
}

// match: ?sub_E02E0@type_DC400@@QAEXH@Z @ 0x000E02E0
void type_DC400::sub_E02E0(RwInt32 arg_0)
{
    RwChar var_14[0x10];

    if (unk_E0[0x4F].unk_20)
    {
        sprintf(var_14, "%d", arg_0);
        sub_E7380(0x4F, var_14);
    }
    sub_E3B50(0x4F);
}

// match: ?sub_E0340@type_DC400@@QAEXH@Z @ 0x000E0340
// sp-match: ?sub_E0340@type_DC400@@QAEXH@Z @ 0x000A9B50
void type_DC400::sub_E0340(RwInt32 arg_0)
{
    if (unk_BC != arg_0)
    {
        unk_BC = arg_0;
        switch (arg_0)
        {
        case 0:
            sub_E09E0(0xB, 1);
            sub_E09E0(0xC, 0);
            sub_E09E0(0xD, 0);
            break;
        case 1:
            sub_E09E0(0xB, 0);
            sub_E09E0(0xC, 1);
            sub_E09E0(0xD, 0);
            break;
        case 2:
            sub_E09E0(0xB, 0);
            sub_E09E0(0xC, 0);
            sub_E09E0(0xD, 1);
            break;
        }
        sub_E3B50(0xA);
    }
}

// match: ?sub_E0410@type_DC400@@QAEXH@Z @ 0x000E0410
// sp-match: ?sub_E0410@type_DC400@@QAEXH@Z @ 0x000A9BD0
void type_DC400::sub_E0410(RwInt32 arg_0)
{
    type_10F710 *var_4;

    var_4 = (type_10F710 *)sub_1745A0(0);
    if (var_4 && var_4->unk_1B2C)
    {
#ifdef CODFH_SP // shape: single player numbers its HUD items differently (SP 0xA9BD0)
        sub_E09E0(0x4D, 0);
        sub_E09E0(0x4E, 0);
        sub_E09E0(0x4F, 0);
        sub_E09E0(0x50, 0);
        sub_E09E0(0x4C, 0);
        sub_E09E0(0x51, 0);
        sub_E09E0(0x53, 0);
        sub_E09E0(0x54, 0);
        sub_E09E0(0x55, 0);
        sub_E09E0(0x56, 0);
        sub_E09E0(0x57, 0);
        sub_E09E0(0x58, 0);
#else
        sub_E09E0(0x7C, 0);
        sub_E09E0(0x7D, 0);
        sub_E09E0(0x7E, 0);
        sub_E09E0(0x7F, 0);
        sub_E09E0(0x7B, 0);
        sub_E09E0(0x80, 0);
        sub_E09E0(0x82, 0);
        sub_E09E0(0x83, 0);
        sub_E09E0(0x84, 0);
        sub_E09E0(0x85, 0);
        sub_E09E0(0x86, 0);
        sub_E09E0(0x87, 0);
#endif
    }
    else
    {
        unk_C0 = arg_0;
#ifdef CODFH_SP // shape: single player numbers its HUD items differently (SP 0xA9BD0)
        sub_E09E0(0x4D, 0);
        sub_E09E0(0x4E, 0);
        sub_E09E0(0x4F, 0);
        sub_E09E0(0x50, 0);
        sub_E09E0(0x4C, 0);
        sub_E09E0(0x51, 0);
        sub_E09E0(0x53, 0);
        sub_E09E0(0x54, 0);
        sub_E09E0(0x55, 0);
        sub_E09E0(0x56, 0);
        sub_E09E0(0x57, 0);
        sub_E09E0(0x58, 0);
#else
        sub_E09E0(0x7C, 0);
        sub_E09E0(0x7D, 0);
        sub_E09E0(0x7E, 0);
        sub_E09E0(0x7F, 0);
        sub_E09E0(0x7B, 0);
        sub_E09E0(0x80, 0);
        sub_E09E0(0x82, 0);
        sub_E09E0(0x83, 0);
        sub_E09E0(0x84, 0);
        sub_E09E0(0x85, 0);
        sub_E09E0(0x86, 0);
        sub_E09E0(0x87, 0);
#endif
        switch (unk_C0)
        {
        case 8:
#ifdef CODFH_SP // shape: single player numbers its HUD items differently (SP 0xA9BD0)
            sub_E09E0(0x53, 1);
#else
            sub_E09E0(0x82, 1);
#endif
            break;
        case 9:
#ifdef CODFH_SP // shape: single player numbers its HUD items differently (SP 0xA9BD0)
            sub_E09E0(0x54, 1);
#else
            sub_E09E0(0x83, 1);
#endif
            break;
        case 1:
#ifdef CODFH_SP // shape: single player numbers its HUD items differently (SP 0xA9BD0)
            sub_E09E0(0x4E, 1);
#else
            sub_E09E0(0x7D, 1);
#endif
            break;
        case 4:
#ifdef CODFH_SP // shape: single player numbers its HUD items differently (SP 0xA9BD0)
            sub_E09E0(0x50, 1);
#else
            sub_E09E0(0x7F, 1);
#endif
            break;
        case 5:
#ifdef CODFH_SP // shape: single player numbers its HUD items differently (SP 0xA9BD0)
            sub_E09E0(0x4D, 1);
#else
            sub_E09E0(0x7C, 1);
#endif
            break;
        case 2:
#ifdef CODFH_SP // shape: single player numbers its HUD items differently (SP 0xA9BD0)
            sub_E09E0(0x4D, 1);
#else
            sub_E09E0(0x7C, 1);
#endif
            break;
        case 7:
#ifdef CODFH_SP // shape: single player numbers its HUD items differently (SP 0xA9BD0)
            sub_E09E0(0x4C, 1);
#else
            sub_E09E0(0x7B, 1);
#endif
            break;
        case 10:
#ifdef CODFH_SP // shape: single player numbers its HUD items differently (SP 0xA9BD0)
            sub_E09E0(0x56, 1);
#else
            sub_E09E0(0x85, 1);
#endif
            break;
        case 11:
#ifdef CODFH_SP // shape: single player numbers its HUD items differently (SP 0xA9BD0)
            sub_E09E0(0x57, 1);
#else
            sub_E09E0(0x86, 1);
#endif
            break;
        case 3:
#ifdef CODFH_SP // shape: single player numbers its HUD items differently (SP 0xA9BD0)
            sub_E09E0(0x51, 1);
#else
            sub_E09E0(0x80, 1);
#endif
            break;
        case 6:
#ifdef CODFH_SP // shape: single player numbers its HUD items differently (SP 0xA9BD0)
            sub_E09E0(0x4D, 1);
            sub_E09E0(0x52, 1);
#else
            sub_E09E0(0x7C, 1);
            sub_E09E0(0x81, 1);
#endif
            break;
        case 12:
#ifdef CODFH_SP // shape: single player numbers its HUD items differently (SP 0xA9BD0)
            sub_E09E0(0x58, 1);
#else
            sub_E09E0(0x87, 1);
#endif
            break;
        }
        if (arg_0)
        {
#ifdef CODFH_SP // shape: single player numbers its HUD items differently (SP 0xA9BD0)
            sub_E3B50(0x4B);
#else
            sub_E3B50(0x7A);
#endif
        }
    }
}

// match: ?sub_E06E0@type_DC400@@QAEXH@Z @ 0x000E06E0
// sp-match: ?sub_E06E0@type_DC400@@QAEXH@Z @ 0x000A9D80
void type_DC400::sub_E06E0(RwInt32 arg_0)
{
    if (arg_0 != unk_CC)
    {
        unk_CC = arg_0;
    }
    else
    {
        return;
    }
    switch (unk_CC)
    {
    case 2:
    case 3:
    case 4:
    case 5:
    case 6:
    case 8:
    case 9:
    case 10:
    case 11:
    case 12:
    case 13:
    case 14:
    case 15:
        unk_C0 = 6;
        break;
    case -1:
        unk_C0 = 0;
        break;
    default:
        unk_C0 = 5;
        break;
    }
    sub_E0410(unk_C0);
}

#ifdef CODFH_SP
// sp-match: ?sp_sub_A9E00@type_DC400@@QAEXH@Z @ 0x000A9E00
// Single player only (SP 0xA9E00, called from SP 0xCB733): sets unk_D0 and from it the
// mode unk_C0 (0xB while it is not -1, else 0) through sub_E0410.
void type_DC400::sp_sub_A9E00(RwInt32 arg_0)
{
    if (arg_0 != unk_D0)
    {
        unk_D0 = arg_0;
    }
    switch (unk_D0)
    {
    case -1:
        unk_C0 = 0;
        break;
    case 0:
        unk_C0 = 0xB;
        break;
    default:
        unk_C0 = 0xB;
        break;
    }
    sub_E0410(unk_C0);
}
#endif

// match: ?sub_E07A0@type_DC400@@QAEXHH@Z @ 0x000E07A0
// sp-match: ?sub_E07A0@type_DC400@@QAEXHH@Z @ 0x000A9E40
void type_DC400::sub_E07A0(RwInt32 arg_0, RwInt32 arg_4)
{
    sub_E3B50(0xE);
    sub_E3B50(4);
    sub_E3B50(7);
}

// match: ?sub_E07D0@type_DC400@@QAEXXZ @ 0x000E07D0
// sp-match: ?sub_E07D0@type_DC400@@QAEXXZ @ 0x000A9E60
void type_DC400::sub_E07D0()
{
    sub_E3B50(0xE);
    sub_E3B50(4);
    sub_E3B50(7);
}

// match: ?sub_E0800@type_DC400@@QAEXH@Z @ 0x000E0800
// sp-match: ?sub_E0800@type_DC400@@QAEXH@Z @ 0x000A79A0
void type_DC400::sub_E0800(RwInt32 arg_0)
{
    unk_C8 = arg_0;
    switch (arg_0)
    {
    case 3:
    case 4:
    case 6:
    case 23:
        unk_C4 = 2;
        break;
    case 7:
    case 8:
    case 9:
    case 10:
        unk_C4 = 1;
        break;
    case 12:
    case 14:
    case 15:
    case 16:
    case 18:
        unk_C4 = 4;
        break;
    case 11:
        unk_C4 = 0;
        break;
    }
}

// match: ?sub_E08B0@type_DC400@@QAEXM@Z @ 0x000E08B0
// sp-match: ?sub_E08B0@type_DC400@@QAEXM@Z @ 0x000AADF0
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void type_DC400::sub_E08B0(RwReal arg_0)
{
    RwReal var_20;
    RwReal l1C;
    RwReal m_18;
    type_4C19C0 *ebp_14;
    type_10F710 *lv_10;
    RwReal var_C;
    RwReal bp_8;
    RwReal bp_4;

    lv_10 = (type_10F710 *)sub_1745A0(0);
    if (!lv_10)
    {
        return;
    }
    if (lv_10->unk_1A48[lv_10->unk_1AE4])
    {
        ebp_14 = lv_10->unk_1A48[lv_10->unk_1AE4]->unk_448;
        if (!ebp_14)
        {
            return;
        }
        bp_8 = ebp_14->unk_308[lv_10->unk_1A04];
        l1C = ebp_14->unk_314[lv_10->unk_1A04];
        m_18 = l1C - bp_8;
        var_C = lv_10->unk_1A48[lv_10->unk_1AE4]->sub_11D690();
        bp_4 = m_18 * var_C + bp_8;
        var_20 = 1.0f;
#ifdef CODFH_SP // shape: single player's crosshair arms are items 0x32 to 0x35 (SP 0xAADF0)
        sub_E6200(0x32, 0.0f, -bp_4);
        sub_E6200(0x35, bp_4 * var_20, 0.0f);
        sub_E6200(0x33, 0.0f, bp_4);
        sub_E6200(0x34, -bp_4 * var_20, 0.0f);
#else
        sub_E6200(0x5B, 0.0f, -bp_4);
        sub_E6200(0x5E, bp_4 * var_20, 0.0f);
        sub_E6200(0x5C, 0.0f, bp_4);
        sub_E6200(0x5D, -bp_4 * var_20, 0.0f);
#endif
    }
}

// Stubbed out: it returns at once. The code after the return is gone; its
// frame keeps a local above `this` and a switch temporary below it, so the
// dead part switched on arg_0 (the rest of it is unknown).
// match: ?sub_E09D0@type_DC400@@QAEXH@Z @ 0x000E09D0
// sp-match: ?sub_E09D0@type_DC400@@QAEXH@Z @ 0x000A9E80
void type_DC400::sub_E09D0(RwInt32 arg_0)
{
#ifdef CODFH_SP // SP 0xA9E80: single player shows the inventory item of arg_0 (MP returns at once)
    RwInt32 lv_item;

    sub_E09E0(0x15, 0);
    sub_E09E0(0x16, 0);
    sub_E09E0(0x17, 0);
    sub_E09E0(0x19, 0);
    sub_E09E0(0x1A, 0);
    sub_E09E0(0x18, 0);
    sub_E09E0(0x1B, 0);
    switch (arg_0)
    {
    case 0:
        return;
    case 6:
        lv_item = 0x17;
        break;
    case 9:
        lv_item = 0x15;
        break;
    case 8:
        lv_item = 0x18;
        break;
    case 7:
        lv_item = 0x19;
        break;
    case 5:
        lv_item = 0x1A;
        break;
    default:
        lv_item = 0x16;
        break;
    }
    sub_E09E0(lv_item, 1);
    sub_E09E0(0x1B, 1);
    sub_E09E0(0x1C, 1);
    sub_E09E0(0x14, 1);
    sub_E3B50(0x14);
#else
    RwInt32 var_4;

    return;
    switch (arg_0)
    {
    default:
        break;
    }
#endif
}

// match: ?sub_E09E0@type_DC400@@QAEXHH@Z @ 0x000E09E0
// sp-match: ?sub_E09E0@type_DC400@@QAEXHH@Z @ 0x000A7A20
void type_DC400::sub_E09E0(RwInt32 arg_0, RwInt32 arg_4)
{
    unk_E0[arg_0].unk_50 = arg_4;
}

// match: ?sub_E0A10@type_DC400@@QAEHH@Z @ 0x000E0A10
// sp-match: ?sub_E0A10@type_DC400@@QAEHH@Z @ 0x000A7A40
RwInt32 type_DC400::sub_E0A10(RwInt32 arg_0)
{
    return unk_E0[arg_0].unk_50;
}

// match: ?sub_E0A30@type_DC400@@QAEXHH@Z @ 0x000E0A30
// sp-match: ?sub_E0A30@type_DC400@@QAEXHH@Z @ 0x000A7A60
void type_DC400::sub_E0A30(RwInt32 arg_0, RwInt32 arg_4)
{
    unk_E0[arg_0].unk_50 = 1;
    unk_E0[arg_0].unk_30 = arg_4;
}

// match: ?sub_E0A70@type_DC400@@QAEXM@Z @ 0x000E0A70
// sp-match: ?sub_E0A70@type_DC400@@QAEXM@Z @ 0x000AAEB0
void type_DC400::sub_E0A70(RwReal arg_0)
{
#ifdef CODFH_SP // shape: single player's vehicle health bar is item 0x3F (SP 0xAAEB0)
    sub_E6270(0x3F, arg_0, 1.0f);
#else
    sub_E6270(0x68, arg_0, 1.0f);
#endif
}

// match: ?sub_E0A90@type_DC400@@QAEXM@Z @ 0x000E0A90
// sp-match: ?sub_E0A90@type_DC400@@QAEXM@Z @ 0x000AAED0
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void type_DC400::sub_E0A90(RwReal arg_0)
{
    RwRGBA var_C;
    RwRGBA bp_8;
    RwRGBA bp_4;

#ifdef CODFH_SP // shape: single player's vehicle armour bar is item 0x40 (SP 0xAAED0)
    sub_E6270(0x40, arg_0, 1.0f);
#else
    sub_E6270(0x69, arg_0, 1.0f);
#endif
    var_C = unk_4B8F34;
    bp_4 = unk_4B8F38;
    bp_8.red = (RwUInt8)(var_C.red + (bp_4.red - var_C.red) * arg_0);
    bp_8.green = (RwUInt8)(var_C.green + (bp_4.green - var_C.green) * arg_0);
    bp_8.blue = (RwUInt8)(var_C.blue + (bp_4.blue - var_C.blue) * arg_0);
    bp_8.alpha = 0xFF;
#ifdef CODFH_SP // shape: item 0x40 (SP 0xAAED0)
    sub_E7270(0x40, &bp_8, &bp_8, &var_C, &var_C);
#else
    sub_E7270(0x69, &bp_8, &bp_8, &var_C, &var_C);
#endif
}

// match: ?sub_E0B60@type_DC400@@QAEXHPAUtype_3D3548@@H@Z @ 0x000E0B60
// sp-match: ?sub_E0B60@type_DC400@@QAEXHPAUtype_3D3548@@H@Z @ 0x000AAFA0
void type_DC400::sub_E0B60(RwInt32 arg_0, type_3D3548 *arg_4, RwInt32 arg_8)
{
    if (!arg_4)
    {
        return;
    }
    unk_1A030 = arg_0;
    unk_1A034.sub_D48D0(arg_4);
    if (arg_8 == 1)
    {
#ifdef CODFH_SP // shape: single player's t34 reticle is item 0x39 (SP 0xAAFA0)
        sub_E09E0(0x39, 0);
#else
        sub_E09E0(0x62, 0);
#endif
        sub_E09E0(3, 1);
        sub_E09E0(4, 1);
        sub_E09E0(7, 0);
        sub_E09E0(0xA, 0);
        sub_E09E0(0x14, 0);
        sub_E7050(0xE, unk_14[0].unk_08.x, unk_14[0].unk_08.y);
        sub_E7050(0xF, unk_14[1].unk_08.x, unk_14[1].unk_08.y);
        sub_E7050(0x10, unk_14[2].unk_08.x, unk_14[2].unk_08.y);
        sub_E7050(4, unk_14[3].unk_08.x, unk_14[3].unk_08.y);
    }
    else
    {
#ifdef CODFH_SP // shape: item 0x39 (SP 0xAAFA0)
        sub_E09E0(0x39, 0);
#else
        sub_E09E0(0x62, 0);
#endif
        sub_E09E0(3, 0);
    }
    sub_DEB80(0);
    switch (unk_1A030)
    {
#ifdef CODFH_SP // shape: single player's t34 root is item 0x38 (SP 0xAAFA0)
    case 1:
        sub_E09E0(0x38, 1);
        break;
    case 2:
        sub_E09E0(0x38, 1);
        break;
    case 3:
        sub_E09E0(0x38, 1);
        break;
#else
    case 1:
        sub_E09E0(0x61, 1);
        break;
    case 2:
        sub_E09E0(0x61, 1);
        break;
    case 3:
        sub_E09E0(0x61, 1);
        break;
#endif
    }
    unk_08 = 1;
}

// match: ?sub_E0CC0@type_DC400@@QAEXXZ @ 0x000E0CC0
// sp-match: ?sub_E0CC0@type_DC400@@QAEXXZ @ 0x000AB090
void type_DC400::sub_E0CC0()
{
    switch (unk_1A030)
    {
    case 1:
    case 2:
    case 3:
#ifdef CODFH_SP // shape: single player's t34 root is item 0x38 (SP 0xAB090)
        sub_E09E0(0x38, 0);
#else
        sub_E09E0(0x61, 0);
#endif
        break;
    }
    sub_E09E0(3, 1);
    sub_E09E0(4, 1);
    sub_E09E0(7, 1);
    sub_E09E0(0xA, 1);
    sub_E09E0(0x14, 1);
    sub_E7050(0xE, unk_14[0].unk_00.x, unk_14[0].unk_00.y);
    sub_E7050(0xF, unk_14[1].unk_00.x, unk_14[1].unk_00.y);
    sub_E7050(0x10, unk_14[2].unk_00.x, unk_14[2].unk_00.y);
    sub_E7050(4, unk_14[3].unk_00.x, unk_14[3].unk_00.y);
    unk_08 = 0;
    unk_1A030 = 0;
    unk_1A034.sub_D48D0(0);
    sub_E0800(unk_C8);
}

// match: ?sub_E0DD0@type_DC400@@QAEXXZ @ 0x000E0DD0
// sp-match: ?sub_E0DD0@type_DC400@@QAEXXZ @ 0x000A7A90
void type_DC400::sub_E0DD0()
{
    unk_04 = 1;
#ifdef CODFH_SP // shape: single player's pause root is item 0x59 (SP 0xA7A90)
    sub_E09E0(0x59, 1);
#else
    sub_E09E0(0x88, 1);
#endif
    flt_4B8984 = 0;
}

// match: ?sub_E0E00@type_DC400@@QAEXXZ @ 0x000E0E00
// sp-match: ?sub_E0E00@type_DC400@@QAEXXZ @ 0x000A7AB0
void type_DC400::sub_E0E00()
{
    RwInt8 var_1;
    type_4E56A0 *var_8;

    unk_04 = 0;
    unk_1A4B8 = 0;
    var_8 = 0;
    var_1 = byte_4E564D;
    var_8 = sub_1708B0(var_1);
    while (var_8)
    {
        var_8->unk_14 = 0;
        var_1 = sub_170890(var_1);
        var_8 = sub_1708B0(var_1);
    }
    unk_1A4BC = 0;
#ifdef CODFH_SP // shape: single player's pause root is item 0x59 (SP 0xA7AB0)
    sub_E09E0(0x59, 0);
#else
    sub_E09E0(0x88, 0);
#endif
}

// match: ?sub_E0E90@type_DC400@@QAEXXZ @ 0x000E0E90
// match: __ehhandler$?sub_E0E90@type_DC400@@QAEXXZ-0x70 @ 0x00300E20
// match: __ehhandler$?sub_E0E90@type_DC400@@QAEXXZ @ 0x00300E90
// sp-match: ?sub_E0E90@type_DC400@@QAEXXZ @ 0x000AB150
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void type_DC400::sub_E0E90()
{
#ifdef CODFH_SP // single player builds its own HUD (SP 0xAB150): 101 items, no multiplayer, CTF or objective items,
                // no texts or fonts, a hud_logo item, the pause root at 0x59 and the hit indicators from 0x5C
    RwInt32 lv_10;

    sub_E6570(0, 1);
    sub_E6570(1, 2);
    sub_E6570(0, 3);
    sub_E6570(3, 4);
    sub_E6570(4, 5);
    sub_E6570(4, 6);
    sub_E6570(3, 7);
    sub_E6570(7, 8);
    sub_E6570(7, 9);
    sub_E6570(3, 0xA);
    sub_E6570(0xA, 0xB);
    sub_E6570(0xA, 0xC);
    sub_E6570(0xA, 0xD);
    sub_E6570(3, 0xE);
    sub_E6570(0xE, 0xF);
    sub_E6570(0xE, 0x10);
    sub_E6570(0xE, 0x13);
    sub_E6570(0xE, 0x12);
    sub_E6570(3, 0x14);
    sub_E6570(0x14, 0x15);
    sub_E6570(0x14, 0x16);
    sub_E6570(0x14, 0x17);
    sub_E6570(0x14, 0x19);
    sub_E6570(0x14, 0x1A);
    sub_E6570(0x14, 0x18);
    sub_E6570(0x14, 0x1B);
    sub_E6570(0x14, 0x1C);
    sub_E6570(0, 0x31);
    sub_E6570(0x31, 0x32);
    sub_E6570(0x31, 0x33);
    sub_E6570(0x31, 0x34);
    sub_E6570(0x31, 0x35);
    sub_E6570(0x31, 0x36);
    sub_E6570(0x31, 0x37);
    sub_E6570(0, 0x61);
    sub_E6570(0x61, 0x63);
    sub_E6570(0x61, 0x62);
    sub_E6570(0x61, 0x64);
    sub_E6570(0, 0x1D);
    sub_E6570(0x1D, 0x1E);
    sub_E6570(0x1D, 0x1F);
    sub_E6570(0x1D, 0x20);
    sub_E6570(0x1D, 0x21);
    for (lv_10 = 0; lv_10 < 15; lv_10++)
    {
        sub_E6570(0x1D, lv_10 + 0x22);
    }
    sub_E6570(0, 0x4B);
    sub_E6570(0x4B, 0x4C);
    sub_E6570(0x4B, 0x4D);
    sub_E6570(0x4B, 0x4E);
    sub_E6570(0x4B, 0x4F);
    sub_E6570(0x4B, 0x50);
    sub_E6570(0x4B, 0x51);
    sub_E6570(0x4B, 0x53);
    sub_E6570(0x4B, 0x54);
    sub_E6570(0x4B, 0x55);
    sub_E6570(0x4B, 0x56);
    sub_E6570(0x4B, 0x57);
    sub_E6570(0x4B, 0x52);
    sub_E6570(0x4B, 0x58);
    sub_E6570(0, 0x38);
    sub_E6570(0x38, 0x39);
    sub_E6570(0x38, 0x3A);
    sub_E6570(0x3A, 0x3B);
    sub_E6570(0x3A, 0x3C);
    sub_E6570(0x38, 0x3D);
    sub_E6570(0x3D, 0x3E);
    sub_E6570(0x3D, 0x3F);
    sub_E6570(0x3D, 0x40);
    sub_E6570(0, 0x41);
    sub_E6570(0, 0x42);
    sub_E6570(0, 0x43);
    sub_E6570(0, 0x44);
    sub_E6570(0, 0x45);
    sub_E6570(0, 0x46);
    sub_E6570(0, 0x47);
    sub_E6570(0, 0x48);
    sub_E6570(0, 0x49);
    sub_E6570(0, 0x4A);
    sub_E6570(0, 0x59);
    sub_E6570(0x59, 0x5A);
    sub_E6570(0, 0x5B);
    for (lv_10 = 0; lv_10 < 5; lv_10++)
    {
        sub_E6570(0x5B, lv_10 + 0x5C);
    }
    sub_E83F0();
    sub_E6F90(0, "hud_root", false, true, false, false, false, false);
    sub_E6F90(1, "hud_subtitle", false, true, false, false, false, false);
    sub_E6F90(2, "hud_subtitle_text", false, false, true, false, true, false);
    sub_E6F90(3, "hud_soldier_root", false, true, false, false, false, false);
    sub_E6F90(4, "hud_health", false, true, false, true, true, false);
    sub_E6F90(5, "hud_health_frame", true, false, false, false, true, true);
    sub_E6F90(6, "hud_health_bar", false, false, false, false, true, true);
    sub_E6F90(7, "hud_healthpack", false, true, false, true, true, false);
    sub_E6F90(8, "hud_inventory_medpack", true, false, false, false, true, true);
    sub_E6F90(9, "hud_healthpack_txt", false, false, true, true, true, false);
    sub_E6F90(0x4B, "hud_actions", false, true, false, false, true, false);
    sub_E6F90(0x4C, "hud_action_radio", true, false, false, false, false, true);
    sub_E6F90(0x4D, "hud_action_get", true, false, false, false, false, true);
    sub_E6F90(0x4E, "hud_action_gogogo", true, false, false, false, false, true);
    sub_E6F90(0x4F, "hud_action_openbox", true, false, false, false, false, true);
    sub_E6F90(0x50, "hud_action_opendoor", true, false, false, false, false, true);
    sub_E6F90(0x51, "hud_action_healfriendly", true, false, false, false, false, true);
    sub_E6F90(0x53, "hud_action_drivevehicle", true, false, false, false, false, true);
    sub_E6F90(0x54, "hud_action_dismount", true, false, false, false, false, true);
    sub_E6F90(0x55, "hud_action_rollbarrel", true, false, false, false, false, true);
    sub_E6F90(0x56, "hud_action_plantbomb", true, false, false, false, false, true);
    sub_E6F90(0x57, "hud_action_mountMG", true, false, false, false, false, true);
    sub_E6F90(0x52, "hud_action_text_dump", false, false, true, false, true, false);
    sub_E6F90(0x58, "hud_action_disarmmine", true, false, false, false, false, true);
    sub_E6F90(0x1D, "hud_compass", false, true, false, false, true, false);
    sub_E6F90(0x1E, "hud_compass_glass", true, false, false, false, false, true);
    sub_E6F90(0x1F, "hud_compass_bg", true, false, false, false, false, true);
    sub_E6F90(0x20, "hud_compass_star", true, false, false, false, false, false);
    sub_E6F90(0x21, "hud_compass_star_pulse", true, false, false, false, false, false);
    for (lv_10 = 0; lv_10 < 15; lv_10++)
    {
        sub_E6F90(lv_10 + 0x22, "hud_compass_star", true, false, false, false, false, false);
        sub_E09E0(lv_10 + 0x22, 0);
    }
    sub_E6F90(0xA, "hud_posture", false, true, false, false, true, false);
    sub_E6F90(0xB, "hud_posture_stand", true, false, false, false, true, false);
    sub_E6F90(0xC, "hud_posture_crouch", true, false, false, false, true, false);
    sub_E6F90(0xD, "hud_posture_prone", true, false, false, false, true, false);
    sub_E6F90(0xE, "hud_ammo_root", false, true, false, true, true, false);
    sub_E6F90(0x12, "hud_ammo_grenicon", true, false, false, false, true, false);
    sub_E6F90(0x13, "hud_ammo", true, false, false, false, false, true);
    sub_E6F90(0xF, "hud_ammo_txtammo", false, false, true, false, true, false);
    sub_E6F90(0x10, "hud_ammo_txtclips", false, false, true, false, true, false);
    sub_E6F90(0x11, "hud_ammo_txtgrens", false, false, true, false, true, false);
    sub_E6F90(0x14, "hud_inventory_root", false, true, false, true, true, false);
    sub_E6F90(0x15, "hud_inventory_grenadeG", true, false, false, false, true, true);
    sub_E6F90(0x16, "hud_inventory_grenadeR", true, false, false, false, true, true);
    sub_E6F90(0x18, "hud_inventory_grenadeA", true, false, false, false, true, true);
    sub_E6F90(0x19, "hud_inventory_tellermine", true, false, false, false, true, true);
    sub_E6F90(0x1A, "hud_inventory_stickymine", true, false, false, false, true, true);
    sub_E6F90(0x17, "hud_inventory_radio", true, false, false, false, true, true);
    sub_E6F90(0x1B, "hud_inventory_txt", false, false, true, false, true, false);
    sub_E6F90(0x1C, "hud_inventory", true, false, false, false, true, true);
    sub_E6F90(0x31, "hud_crosshair", false, true, false, false, true, false);
    sub_E6F90(0x32, "hud_crosshair", true, false, false, false, false, true);
    sub_E6F90(0x33, "hud_crosshair", true, false, false, false, false, true);
    sub_E6F90(0x34, "hud_crosshair", true, false, false, false, false, true);
    sub_E6F90(0x35, "hud_crosshair", true, false, false, false, false, true);
    sub_E6F90(0x36, "hud_crosshair_overbuddy", true, false, false, false, false, true);
    sub_E6F90(0x37, "hud_enemy_hit_indicator", true, false, false, false, false, true);
    sub_E6F90(0x61, "hud_buddy_health root", false, true, false, true, true, false);
    sub_E6F90(0x62, "hud_t34_buddy_health", true, false, false, false, true, false);
    sub_E6F90(0x64, "hud_buddy_health_bar", false, false, false, false, true, true);
    sub_E6F90(0x63, "hud_health_frame", true, false, false, false, true, false);
    sub_E6F90(0x38, "hud_t34_root", false, true, false, false, true, false);
    sub_E6F90(0x39, "hud_t34_reticle", true, false, false, false, true, true);
    sub_E6F90(0x3A, "hud_tank_arrow", true, false, false, false, true, false);
    sub_E6F90(0x3B, "hud_t34_turret", true, false, false, false, true, false);
    sub_E6F90(0x3C, "hud_t34_body", true, false, false, false, true, true);
    sub_E6F90(0x3D, "hud_vehicle_life", false, true, false, false, true, false);
    sub_E6F90(0x3E, "hud_vehicle_lifeframe", true, true, false, false, true, false);
    sub_E6F90(0x3F, "hud_vehicle_healthbar", false, false, false, false, true, true);
    sub_E6F90(0x40, "hud vehicle_armorbar", false, false, false, false, true, true);
    sub_E6F90(0x41, "hud_buddy_status", false, false, true, false, true, false);
    sub_E6F90(0x42, "hud_buddy_status_1", false, false, true, false, true, false);
    sub_E6F90(0x43, "hud_buddy_status_2", false, false, true, false, true, false);
    sub_E6F90(0x44, "hud_buddy_status_3", false, false, true, false, true, false);
    sub_E6F90(0x45, "hud_buddy_status_4", false, false, true, false, true, false);
    sub_E6F90(0x46, "hud_buddy_status_5", false, false, true, false, true, false);
    sub_E6F90(0x47, "hud_buddy_status_6", false, false, true, false, true, false);
    sub_E6F90(0x48, "hud_buddy_status_7", false, false, true, false, true, false);
    sub_E6F90(0x49, "hud_buddy_status_8", false, false, true, false, true, false);
    sub_E6F90(0x4A, "hud_buddy_status_9", false, false, true, false, true, false);
    sub_E6F90(0x59, "hud_pause_root", false, true, false, false, false, false);
    sub_E6F90(0x5A, "hud_logo", true, false, false, false, true, false);
    sub_E6F90(0x5B, "hid_hit_root", false, true, false, false, false, true);
    for (lv_10 = 0; lv_10 < 5; lv_10++)
    {
        sub_E6F90(lv_10 + 0x5C, "hud_hit_indicator5", true, false, false, false, true, false);
        sub_E09E0(lv_10 + 0x5C, 0);
    }
    for (lv_10 = 0; lv_10 < type_DC400_items; lv_10++)
    {
        if (!unk_E0[lv_10].unk_00[0])
        {
            continue;
        }
        if (!sub_E39B0(lv_10, unk_E0[lv_10].unk_00, 0))
        {
            continue;
        }
        sub_E7140(lv_10, 0.0f);
        RwMatrixSetIdentity(&unk_E0[lv_10].unk_1A0);
        unk_E0[lv_10].unk_E0[0].x = 0.0f - unk_E0[lv_10].unk_188.x * 0.5f;
        unk_E0[lv_10].unk_E0[0].y = unk_E0[lv_10].unk_188.y * 0.5f + 0.0f;
        unk_E0[lv_10].unk_E0[1].x = 0.0f - unk_E0[lv_10].unk_188.x * 0.5f;
        unk_E0[lv_10].unk_E0[1].y = 0.0f - unk_E0[lv_10].unk_188.y * 0.5f;
        unk_E0[lv_10].unk_E0[2].x = unk_E0[lv_10].unk_188.x * 0.5f + 0.0f;
        unk_E0[lv_10].unk_E0[2].y = unk_E0[lv_10].unk_188.y * 0.5f + 0.0f;
        unk_E0[lv_10].unk_E0[3].x = unk_E0[lv_10].unk_188.x * 0.5f + 0.0f;
        unk_E0[lv_10].unk_E0[3].y = 0.0f - unk_E0[lv_10].unk_188.y * 0.5f;
        if (unk_E0[lv_10].unk_200)
        {
            sub_E7140(lv_10, unk_E0[lv_10].unk_200->unk_1E4 + 0.01f);
        }
        RwIm2DVertexSetU(&unk_E0[lv_10].unk_118[0], 0.0f, 1.0f);
        RwIm2DVertexSetV(&unk_E0[lv_10].unk_118[0], 1.0f, 1.0f);
        RwIm2DVertexSetU(&unk_E0[lv_10].unk_118[1], 0.0f, 1.0f);
        RwIm2DVertexSetV(&unk_E0[lv_10].unk_118[1], 0.0f, 1.0f);
        RwIm2DVertexSetU(&unk_E0[lv_10].unk_118[2], 1.0f, 1.0f);
        RwIm2DVertexSetV(&unk_E0[lv_10].unk_118[2], 1.0f, 1.0f);
        RwIm2DVertexSetU(&unk_E0[lv_10].unk_118[3], 1.0f, 1.0f);
        RwIm2DVertexSetV(&unk_E0[lv_10].unk_118[3], 0.0f, 1.0f);
        sub_E5F60(lv_10, unk_E0[lv_10].unk_1E0);
        unk_E0[lv_10].unk_20 = 1;
    }
    sub_E7140(4, 0.0f);
    sub_E7140(5, 0.02f);
    sub_E7140(6, 0.01f);
    sub_E7140(8, 0.0f);
    sub_E7140(9, 0.0f);
    sub_E7140(0x1D, 0.0f);
    sub_E7140(0x20, 0.1f);
    sub_E7140(0x21, 0.1f);
    for (lv_10 = 0; lv_10 < 15; lv_10++)
    {
        sub_E7140(lv_10 + 0x22, 0.1f);
    }
    sub_E7140(0x1E, 0.2f);
    sub_E7140(0x1F, 0.3f);
    sub_E7140(0x13, 0.3f);
    sub_E7140(0x1C, 0.2f);
    sub_E7140(0x15, 0.0f);
    sub_E7140(0x16, 0.0f);
    sub_E7140(0x17, 0.0f);
    sub_E7140(0x18, 0.0f);
    sub_E7140(0x19, 0.0f);
    sub_E7140(0x1A, 0.0f);
    sub_E7140(0x1B, 0.0f);
    sub_E7140(0x3A, 0.3f);
    sub_E7140(0x3B, 0.1f);
    sub_E7140(0x3C, 0.2f);
    sub_E7140(0x3E, 0.1f);
    sub_E7140(0x40, 0.0f);
    sub_E7140(0x3F, 0.0f);
    sub_E5F60(0x35, 90.0f);
    sub_E5F60(0x33, 180.0f);
    sub_E5F60(0x34, 270.0f);
    sub_E09E0(0x4D, 0);
    sub_E09E0(0x4E, 0);
    sub_E09E0(0x4F, 0);
    sub_E09E0(0x50, 0);
    sub_E09E0(0x4C, 0);
    sub_E09E0(0x51, 0);
    sub_E09E0(0x53, 0);
    sub_E09E0(0x54, 0);
    sub_E09E0(0x55, 0);
    sub_E09E0(0x56, 0);
    sub_E09E0(0x57, 0);
    sub_E09E0(0x58, 0);
    sub_E09E0(0x15, 0);
    sub_E09E0(0x16, 0);
    sub_E09E0(0x18, 0);
    sub_E09E0(0x19, 0);
    sub_E09E0(0x1A, 0);
    sub_E09E0(0x17, 0);
    sub_E09E0(0x1B, 0);
    sub_E09E0(0x1C, 0);
    sub_E09E0(0x14, 0);
    sub_E09E0(0x38, 0);
    sub_E09E0(0x59, 0);
    sub_E09E0(0x36, 0);
    sub_E09E0(0x37, 0);
    sub_E8470();
    sub_E3B90(0x52, 1.0f);
    sub_E3B90(9, 1.0f);
    sub_E70D0(&unk_E0[0]);
    sub_E6610(&unk_E0[0]);
#else
    RwInt32 var_14;
    RwInt32 lv_10;

    sub_E6570(0, 1);
    sub_E6570(1, 2);
    sub_E6570(0, 3);
    sub_E6570(3, 4);
    sub_E6570(4, 5);
    sub_E6570(4, 6);
    sub_E6570(3, 7);
    sub_E6570(7, 8);
    sub_E6570(7, 9);
    sub_E6570(3, 0x41);
    sub_E6570(0x41, 0x42);
    sub_E6570(0x42, 0x43);
    sub_E6570(0x42, 0x44);
    sub_E6570(0x41, 0x45);
    sub_E6570(0x45, 0x46);
    sub_E6570(0x41, 0x47);
    sub_E6570(0x47, 0x48);
    sub_E6570(0x48, 0x49);
    sub_E6570(0x48, 0x4a);
    sub_E6570(0x48, 0x4b);
    sub_E6570(0x48, 0x4c);
    sub_E6570(0x47, 0x4d);
    sub_E6570(0x4d, 0x4e);
    sub_E6570(0x4d, 0x4f);
    sub_E6570(0x41, 0x50);
    sub_E6570(0x4d, 0x51);
    sub_E6570(0x41, 0x94);
    sub_E6570(0x94, 0x95);
    sub_E6570(0x94, 0x96);
    sub_E6570(0x41, 0x52);
    sub_E6570(0x41, 0x53);
    sub_E6570(0x41, 0x54);
    sub_E6570(0x41, 0x55);
    sub_E6570(0x55, 0x56);
    sub_E6570(0x55, 0x57);
    sub_E6570(0x55, 0x58);
    sub_E6570(0x55, 0x59);
    sub_E6570(3, 0xa);
    sub_E6570(0xa, 0xb);
    sub_E6570(0xa, 0xc);
    sub_E6570(0xa, 0xd);
    sub_E6570(3, 0xe);
    sub_E6570(0xe, 0xf);
    sub_E6570(0xe, 0x10);
    sub_E6570(0xe, 0x13);
    sub_E6570(0xe, 0x12);
    sub_E6570(3, 0x14);
    sub_E6570(0x14, 0x15);
    sub_E6570(0x14, 0x16);
    sub_E6570(0x14, 0x17);
    sub_E6570(0x14, 0x19);
    sub_E6570(0x14, 0x1a);
    sub_E6570(0x14, 0x18);
    sub_E6570(0x14, 0x1b);
    sub_E6570(0x14, 0x1c);
    sub_E6570(0, 0x5a);
    sub_E6570(0x5a, 0x5b);
    sub_E6570(0x5a, 0x5c);
    sub_E6570(0x5a, 0x5d);
    sub_E6570(0x5a, 0x5e);
    sub_E6570(0x5a, 0x5f);
    sub_E6570(0x5a, 0x60);
    sub_E6570(0, 0x90);
    sub_E6570(0x90, 0x92);
    sub_E6570(0x90, 0x91);
    sub_E6570(0x90, 0x93);
    sub_E6570(0, 0x1d);
    sub_E6570(0x1d, 0x1e);
    sub_E6570(0x1d, 0x1f);
    sub_E6570(0x1d, 0x20);
    sub_E6570(0x1d, 0x21);
    for (lv_10 = 0; lv_10 < 15; lv_10++)
    {
        sub_E6570(0x1D, lv_10 + 0x22);
    }
    sub_E6570(0x1d, 0x31);
    sub_E6570(0x1d, 0x32);
    sub_E6570(0x1d, 0x33);
    sub_E6570(0x1d, 0x34);
    sub_E6570(0x1d, 0x35);
    sub_E6570(0x1d, 0x36);
    sub_E6570(0x1d, 0x37);
    sub_E6570(0x1d, 0x38);
    sub_E6570(0x1d, 0x39);
    sub_E6570(0x1d, 0x3a);
    sub_E6570(0x1d, 0x3b);
    sub_E6570(0x1d, 0x3c);
    sub_E6570(0x1d, 0x3d);
    sub_E6570(0x1d, 0x3e);
    sub_E6570(0x1d, 0x3f);
    sub_E6570(0x1d, 0x40);
    sub_E6570(0, 0x7a);
    sub_E6570(0x7a, 0x7b);
    sub_E6570(0x7a, 0x7c);
    sub_E6570(0x7a, 0x7d);
    sub_E6570(0x7a, 0x7e);
    sub_E6570(0x7a, 0x7f);
    sub_E6570(0x7a, 0x80);
    sub_E6570(0x7a, 0x82);
    sub_E6570(0x7a, 0x83);
    sub_E6570(0x7a, 0x84);
    sub_E6570(0x7a, 0x85);
    sub_E6570(0x7a, 0x86);
    sub_E6570(0x7a, 0x81);
    sub_E6570(0x7a, 0x87);
    sub_E6570(0, 0x61);
    sub_E6570(0x61, 0x62);
    sub_E6570(0x61, 0x63);
    sub_E6570(0x63, 0x64);
    sub_E6570(0x63, 0x65);
    sub_E6570(0x61, 0x66);
    sub_E6570(0x66, 0x67);
    sub_E6570(0x66, 0x68);
    sub_E6570(0x66, 0x69);
    sub_E6570(0, 0x6a);
    sub_E6570(0, 0x6b);
    sub_E6570(0, 0x6c);
    sub_E6570(0, 0x6d);
    sub_E6570(0, 0x6e);
    sub_E6570(0, 0x6f);
    sub_E6570(0, 0x70);
    sub_E6570(0, 0x71);
    sub_E6570(0, 0x72);
    sub_E6570(0, 0x73);
    sub_E6570(0, 0x88);
    sub_E6570(0, 0x8a);
    for (lv_10 = 0; lv_10 < 5; lv_10++)
    {
        sub_E6570(0x8A, lv_10 + 0x8B);
    }
    sub_E83F0();
    sub_E6F90(0, "hud_root", false, true, false, false, false, false);
    sub_E6F90(1, "hud_subtitle", false, true, false, false, false, false);
    sub_E6F90(2, "hud_subtitle_text", false, false, true, false, true, false);
    sub_E6F90(3, "hud_soldier_root", false, true, false, false, false, false);
    sub_E6F90(4, "hud_health", false, true, false, true, true, false);
    sub_E6F90(5, "hud_health_frame", true, false, false, false, true, true);
    sub_E6F90(6, "hud_health_bar", false, false, false, false, true, true);
    sub_E6F90(7, "hud_healthpack", false, true, false, true, true, false);
    sub_E6F90(8, "hud_inventory_medpack", true, false, false, false, true, true);
    sub_E6F90(9, "hud_healthpack_txt", false, false, true, true, true, false);
    sub_E6F90(0x94, "hud_bomb", false, true, false, true, true, false);
    sub_E6F90(0x95, "hud_bomb_frame", true, false, false, false, true, true);
    sub_E6F90(0x96, "hud_health_bar", false, false, false, false, true, true);
    sub_E6F90(0x41, "hud_multiplayer_root", false, true, false, true, true, false);
    sub_E6F90(0x42, "hud_timer_colon", false, false, true, false, true, false);
    sub_E6F90(0x43, "hud_timer_minutes", false, false, true, false, true, false);
    sub_E6F90(0x44, "hud_timer_seconds", false, false, true, false, true, false);
    sub_E6F90(0x45, "hud_ctf_border", true, true, false, false, true, true);
    sub_E6F90(0x46, "hud_player_score_value", false, false, true, false, true, false);
    sub_E6F90(0x47, "hud_score_root", false, true, false, false, true, true);
    sub_E6F90(0x48, "hud_player_team_frame", false, true, false, false, true, true);
    sub_E6F90(0x49, "hud_ctf_british", true, true, false, false, true, true);
    sub_E6F90(0x4a, "hud_player_team_score", false, false, true, false, true, true);
    sub_E6F90(0x4b, "hud_ctf_flag_icon_british", true, false, false, false, true, true);
    sub_E6F90(0x4c, "hud_ctf_flag_captured", true, false, false, false, true, true);
    sub_E6F90(0x4d, "hud_enemy_team_frame", false, true, false, false, true, true);
    sub_E6F90(0x4e, "hud_ctf_british", true, true, false, false, true, true);
    sub_E6F90(0x4f, "hud_enemy_team_score", false, false, true, false, true, true);
    sub_E6F90(0x50, "hud_ctf_flag_icon_british", true, false, false, false, true, true);
    sub_E6F90(0x51, "hud_ctf_flag_captured", true, false, false, false, true, true);
    sub_E6F90(0x52, "hud_objective_text", false, false, false, false, true, true);
    sub_E6F90(0x53, "hud_objective_text", false, false, false, false, true, true);
    sub_E6F90(0x54, "hud_top_players", false, false, false, false, true, true);
    sub_E6F90(0x55, "hud_spectator", false, true, false, false, true, true);
    sub_E6F90(0x58, "hud_stop_spectating", false, false, true, false, true, true);
    sub_E6F90(0x59, "hud_following", false, false, true, false, true, true);
    sub_E6F90(0x56, "hud_top_shade", false, false, false, false, true, true);
    sub_E6F90(0x57, "hud_bottom_shade", false, false, false, false, true, true);
    sub_E7570(0x58, 0);
    sub_E7570(0x59, 0);
    sub_E09E0(0x52, 0);
    sub_E09E0(0x53, 0);
    sub_E09E0(0x55, 0);
    sub_E09E0(0x54, 0);
    sub_E7540(0x46, 1);
    sub_E7540(0x4a, 1);
    sub_E7540(0x4f, 1);
    sub_E7540(0x42, 1);
    sub_E7540(0x43, 1);
    sub_E7540(0x44, 1);
    sub_E7540(0x58, 1);
    sub_E7540(0x59, 1);
    sub_E75A0(0x42, 1);
    sub_E75A0(0x43, 2);
    sub_E75A0(0x44, 0);
    sub_E75A0(0x46, 1);
    sub_E75A0(0x4a, 1);
    sub_E75A0(0x4f, 1);
    sub_E75A0(0x58, 1);
    sub_E75A0(0x59, 1);
    sub_E7380(0x46, "00");
    sub_E7380(0x4a, "00");
    sub_E7380(0x4f, "00");
    sub_E7380(0x43, "00");
    sub_E7380(0x44, "00");
    sub_E7380(0x42, ":");
    sub_E7380(0x58, "Press  to skip");
    sub_E7380(0x59, "You are following XXX");
#ifndef CODFH_SP // MP only: single player's HUD has no +0x5C..+0xB7 block (include/types/type_DC400.h) (single player has no hud_ctf_ textures)
    sub_E0080(1.0f);
    unk_98[0] = RwTexDictionaryFindNamedTexture(unk_1A024, "hud_ctf_british");
    unk_98[1] = RwTexDictionaryFindNamedTexture(unk_1A024, "hud_ctf_american");
    unk_98[2] = RwTexDictionaryFindNamedTexture(unk_1A024, "hud_ctf_soviet");
    unk_98[3] = RwTexDictionaryFindNamedTexture(unk_1A024, "hud_ctf_german");
    unk_A8[0] = RwTexDictionaryFindNamedTexture(unk_1A024, "hud_ctf_flag_icon_british");
    unk_A8[1] = RwTexDictionaryFindNamedTexture(unk_1A024, "hud_ctf_flag_icon_american");
    unk_A8[2] = RwTexDictionaryFindNamedTexture(unk_1A024, "hud_ctf_flag_icon_soviet");
    unk_A8[3] = RwTexDictionaryFindNamedTexture(unk_1A024, "hud_ctf_flag_icon_german");
#endif
    for (var_14 = 0; var_14 < 7; var_14++)
    {
        unk_4B89B0[var_14] = sub_E3970(unk_3D8070[var_14], 1);
    }
    unk_4B8B20 = sub_E3970("HUD_FOLLOWING", 1);
    unk_4B8990 = sub_E3970("HUD_SPECTATORCAM", 1);
    unk_4B8B04 = sub_E3970("HUD_STOPSPECTATING_XBOX", 1);
    unk_4B8A74 = sub_E3970("HUD_WAITINGFORHOST_CLIENT", 1);
    unk_4B8A90 = sub_E3970("HUD_WAITINGFORHOST_HOST", 1);
    unk_4B8AB0[0] = sub_E3970("HUD_1ST", 1);
    unk_4B8AB0[1] = sub_E3970("HUD_2ND", 1);
    unk_4B8AB0[2] = sub_E3970("HUD_3RD", 1);
    sub_E7380(0x58, unk_4B8B04.c_str());
#ifndef CODFH_SP // MP only: single player's HUD has no +0x5C..+0xB7 block (include/types/type_DC400.h) (single player has no codfont fonts)
    unk_88 = sub_1E5A80("codfontl");
    unk_8C = sub_1E5A80("codfontn");
#endif
    sub_E6F90(0x7a, "hud_actions", false, true, false, false, true, false);
    sub_E6F90(0x7b, "hud_action_radio", true, false, false, false, false, true);
    sub_E6F90(0x7c, "hud_action_get", true, false, false, false, false, true);
    sub_E6F90(0x7d, "hud_action_gogogo", true, false, false, false, false, true);
    sub_E6F90(0x7e, "hud_action_openbox", true, false, false, false, false, true);
    sub_E6F90(0x7f, "hud_action_opendoor", true, false, false, false, false, true);
    sub_E6F90(0x80, "hud_action_healfriendly", true, false, false, false, false, true);
    sub_E6F90(0x82, "hud_action_drivevehicle", true, false, false, false, false, true);
    sub_E6F90(0x83, "hud_action_dismount", true, false, false, false, false, true);
    sub_E6F90(0x84, "hud_action_rollbarrel", true, false, false, false, false, true);
    sub_E6F90(0x85, "hud_action_bomb", true, false, false, false, false, true);
    sub_E6F90(0x86, "hud_action_mountMG", true, false, false, false, false, true);
    sub_E6F90(0x81, "hud_action_text_dump", false, false, true, false, true, false);
    sub_E6F90(0x87, "hud_action_disarmmine", true, false, false, false, false, true);
    sub_E6F90(0x1d, "hud_compass", false, true, false, false, true, false);
    sub_E6F90(0x1e, "hud_compass_glass", true, false, false, false, false, true);
    sub_E6F90(0x1f, "hud_compass_bg", true, false, false, false, false, true);
    sub_E6F90(0x20, "hud_compass_star", true, false, false, false, false, false);
    sub_E6F90(0x21, "hud_compass_star_pulse", true, false, false, false, false, false);
    for (lv_10 = 0; lv_10 < 15; lv_10++)
    {
        sub_E6F90(lv_10 + 0x22, "hud_compass_star", true, false, false, false, false, false);
        sub_E09E0(lv_10 + 0x22, 0);
    }
    sub_E6F90(0x31, "hud_allied_objective", true, false, false, false, false, false);
    sub_E6F90(0x32, "hud_allied_objective", true, false, false, false, false, false);
    sub_E6F90(0x33, "hud_german_objective", true, false, false, false, false, false);
    sub_E6F90(0x34, "hud_german_objective", true, false, false, false, false, false);
    sub_E6F90(0x35, "hud_bomb_placed", true, false, false, false, false, false);
    sub_E6F90(0x36, "hud_bomb_placed", true, false, false, false, false, false);
    sub_E6F90(0x37, "hud_bomb_location", true, false, false, false, false, false);
    sub_E6F90(0x38, "hud_bomb_location", true, false, false, false, false, false);
    sub_E6F90(0x39, "hud_bomb_location_dest", true, false, false, false, false, false);
    sub_E6F90(0x3a, "hud_bomb_location_dest", true, false, false, false, false, false);
    sub_E6F90(0x3b, "Objective_british_flag", true, false, false, false, false, false);
    sub_E6F90(0x3c, "Objective_american_flag", true, false, false, false, false, false);
    sub_E6F90(0x3d, "Objective_soviet_flag", true, false, false, false, false, false);
    sub_E6F90(0x3e, "Objective_german_flag", true, false, false, false, false, false);
    sub_E6F90(0x3f, "hud_compass_star_pulse", true, false, false, false, false, false);
    sub_E6F90(0x40, "hud_compass_star_pulse", true, false, false, false, false, false);
    sub_E6F90(0xa, "hud_posture", false, true, false, false, true, false);
    sub_E6F90(0xb, "hud_posture_stand", true, false, false, false, true, false);
    sub_E6F90(0xc, "hud_posture_crouch", true, false, false, false, true, false);
    sub_E6F90(0xd, "hud_posture_prone", true, false, false, false, true, false);
    sub_E6F90(0xe, "hud_ammo_root", false, true, false, true, true, false);
    sub_E6F90(0x12, "hud_ammo_grenicon", true, false, false, false, true, false);
    sub_E6F90(0x13, "hud_ammo", true, false, false, false, false, true);
    sub_E6F90(0xf, "hud_ammo_txtammo", false, false, true, false, true, false);
    sub_E6F90(0x10, "hud_ammo_txtclips", false, false, true, false, true, false);
    sub_E6F90(0x11, "hud_ammo_txtgrens", false, false, true, false, true, false);
    sub_E6F90(0x14, "hud_inventory_root", false, true, false, true, true, false);
    sub_E6F90(0x15, "hud_inventory_grenadeG", true, false, false, false, true, true);
    sub_E6F90(0x16, "hud_inventory_grenadeR", true, false, false, false, true, true);
    sub_E6F90(0x18, "hud_inventory_grenadeA", true, false, false, false, true, true);
    sub_E6F90(0x19, "hud_inventory_tellermine", true, false, false, false, true, true);
    sub_E6F90(0x1a, "hud_inventory_stickymine", true, false, false, false, true, true);
    sub_E6F90(0x17, "hud_inventory_radio", true, false, false, false, true, true);
    sub_E6F90(0x1b, "hud_inventory_txt", false, false, true, false, true, false);
    sub_E6F90(0x1c, "hud_inventory", true, false, false, false, true, true);
    sub_E6F90(0x5a, "hud_crosshair", false, true, false, false, true, false);
    sub_E6F90(0x5b, "hud_crosshair", true, false, false, false, false, true);
    sub_E6F90(0x5c, "hud_crosshair", true, false, false, false, false, true);
    sub_E6F90(0x5d, "hud_crosshair", true, false, false, false, false, true);
    sub_E6F90(0x5e, "hud_crosshair", true, false, false, false, false, true);
    sub_E6F90(0x5f, "hud_crosshair_overbuddy", true, false, false, false, false, true);
    sub_E6F90(0x60, "hud_enemy_hit_indicator", true, false, false, false, false, true);
    sub_E6F90(0x90, "hud_buddy_health root", false, true, false, true, true, false);
    sub_E6F90(0x91, "hud_t34_buddy_health", true, false, false, false, true, false);
    sub_E6F90(0x93, "hud_buddy_health_bar", false, false, false, false, true, true);
    sub_E6F90(0x92, "hud_health_frame", true, false, false, false, true, false);
    sub_E6F90(0x61, "hud_t34_root", false, true, false, false, true, false);
    sub_E6F90(0x62, "hud_t34_reticle", true, false, false, false, true, true);
    sub_E6F90(0x63, "hud_tank_arrow", true, false, false, false, true, false);
    sub_E6F90(0x64, "hud_t34_turret", true, false, false, false, true, false);
    sub_E6F90(0x65, "hud_t34_body", true, false, false, false, true, true);
    sub_E6F90(0x66, "hud_vehicle_life", false, true, false, false, true, false);
    sub_E6F90(0x67, "hud_vehicle_lifeframe", true, true, false, false, true, false);
    sub_E6F90(0x68, "hud_vehicle_healthbar", false, false, false, false, true, true);
    sub_E6F90(0x69, "hud vehicle_armorbar", false, false, false, false, true, true);
    sub_E6F90(0x6a, "hud_buddy_status", false, false, true, false, true, false);
    sub_E6F90(0x6b, "hud_buddy_status_1", false, false, true, false, true, false);
    sub_E6F90(0x6c, "hud_buddy_status_2", false, false, true, false, true, false);
    sub_E6F90(0x6d, "hud_buddy_status_3", false, false, true, false, true, false);
    sub_E6F90(0x6e, "hud_buddy_status_4", false, false, true, false, true, false);
    sub_E6F90(0x6f, "hud_buddy_status_5", false, false, true, false, true, false);
    sub_E6F90(0x70, "hud_buddy_status_6", false, false, true, false, true, false);
    sub_E6F90(0x71, "hud_buddy_status_7", false, false, true, false, true, false);
    sub_E6F90(0x72, "hud_buddy_status_8", false, false, true, false, true, false);
    sub_E6F90(0x73, "hud_buddy_status_9", false, false, true, false, true, false);
    sub_E6F90(0x88, "hud_pause_root", false, true, false, false, false, false);
    sub_E6F90(0x8a, "hid_hit_root", false, true, false, false, false, true);
    for (lv_10 = 0; lv_10 < 5; lv_10++)
    {
        sub_E6F90(lv_10 + 0x8B, "hud_hit_indicator5", true, false, false, false, true, false);
        sub_E09E0(lv_10 + 0x8B, 0);
    }
    for (lv_10 = 0; lv_10 < type_DC400_items; lv_10++)
    {
        if (!unk_E0[lv_10].unk_00[0])
        {
            continue;
        }
        if (!sub_E39B0(lv_10, unk_E0[lv_10].unk_00, 0))
        {
            continue;
        }
        sub_E7140(lv_10, 0.0f);
        RwMatrixSetIdentity(&unk_E0[lv_10].unk_1A0);
        unk_E0[lv_10].unk_E0[0].x = 0.0f - unk_E0[lv_10].unk_188.x * 0.5f;
        unk_E0[lv_10].unk_E0[0].y = unk_E0[lv_10].unk_188.y * 0.5f + 0.0f;
        unk_E0[lv_10].unk_E0[1].x = 0.0f - unk_E0[lv_10].unk_188.x * 0.5f;
        unk_E0[lv_10].unk_E0[1].y = 0.0f - unk_E0[lv_10].unk_188.y * 0.5f;
        unk_E0[lv_10].unk_E0[2].x = unk_E0[lv_10].unk_188.x * 0.5f + 0.0f;
        unk_E0[lv_10].unk_E0[2].y = unk_E0[lv_10].unk_188.y * 0.5f + 0.0f;
        unk_E0[lv_10].unk_E0[3].x = unk_E0[lv_10].unk_188.x * 0.5f + 0.0f;
        unk_E0[lv_10].unk_E0[3].y = 0.0f - unk_E0[lv_10].unk_188.y * 0.5f;
        if (unk_E0[lv_10].unk_200)
        {
            sub_E7140(lv_10, unk_E0[lv_10].unk_200->unk_1E4 + 0.01f);
        }
        RwIm2DVertexSetU(&unk_E0[lv_10].unk_118[0], 0.0f, 1.0f);
        RwIm2DVertexSetV(&unk_E0[lv_10].unk_118[0], 1.0f, 1.0f);
        RwIm2DVertexSetU(&unk_E0[lv_10].unk_118[1], 0.0f, 1.0f);
        RwIm2DVertexSetV(&unk_E0[lv_10].unk_118[1], 0.0f, 1.0f);
        RwIm2DVertexSetU(&unk_E0[lv_10].unk_118[2], 1.0f, 1.0f);
        RwIm2DVertexSetV(&unk_E0[lv_10].unk_118[2], 1.0f, 1.0f);
        RwIm2DVertexSetU(&unk_E0[lv_10].unk_118[3], 1.0f, 1.0f);
        RwIm2DVertexSetV(&unk_E0[lv_10].unk_118[3], 0.0f, 1.0f);
        sub_E5F60(lv_10, unk_E0[lv_10].unk_1E0);
        unk_E0[lv_10].unk_20 = 1;
    }
    sub_E7140(4, 0.0f);
    sub_E7140(5, 0.02f);
    sub_E7140(6, 0.01f);
    sub_E7140(8, 0.0f);
    sub_E7140(9, 0.0f);
    sub_E7140(0x94, 0.0f);
    sub_E7140(0x95, 0.01f);
    sub_E7140(0x96, 0.02f);
    sub_E7140(0x41, 0.0f);
    sub_E7140(0x42, 0.0f);
    sub_E7140(0x43, 0.0f);
    sub_E7140(0x44, 0.0f);
    sub_E7140(0x45, 0.0f);
    sub_E7140(0x46, 0.0f);
    sub_E7140(0x47, 0.0f);
    sub_E7140(0x48, 0.0f);
    sub_E7140(0x49, 0.01f);
    sub_E7140(0x4a, 0.0f);
    sub_E7140(0x4b, 0.01f);
    sub_E7140(0x4c, 0.0f);
    sub_E7140(0x4d, 0.0f);
    sub_E7140(0x4e, 0.01f);
    sub_E7140(0x4f, 0.0f);
    sub_E7140(0x50, 0.01f);
    sub_E7140(0x51, 0.0f);
    sub_E7140(0x54, 0.0f);
    sub_E7140(0x55, 0.0f);
    sub_E7140(0x56, 1.0f);
    sub_E7140(0x57, 1.0f);
    sub_E7140(0x58, 0.0f);
    sub_E7140(0x59, 0.0f);
    sub_E7140(0x1d, 0.0f);
    sub_E7140(0x20, 0.1f);
    sub_E7140(0x21, 0.1f);
    for (lv_10 = 0; lv_10 < 15; lv_10++)
    {
        sub_E7140(lv_10 + 0x22, 0.1f);
    }
    sub_E7140(0x1e, 0.2f);
    sub_E7140(0x1f, 0.3f);
    sub_E7140(0x31, 0.1f);
    sub_E7140(0x32, 0.1f);
    sub_E7140(0x33, 0.1f);
    sub_E7140(0x34, 0.1f);
    sub_E7140(0x35, 0.1f);
    sub_E7140(0x36, 0.1f);
    sub_E7140(0x37, 0.1f);
    sub_E7140(0x38, 0.1f);
    sub_E7140(0x39, 0.1f);
    sub_E7140(0x3a, 0.1f);
    sub_E7140(0x3b, 0.1f);
    sub_E7140(0x3c, 0.1f);
    sub_E7140(0x3d, 0.1f);
    sub_E7140(0x3e, 0.1f);
    sub_E7140(0x3f, 0.05f);
    sub_E7140(0x40, 0.05f);
    sub_E7140(0x13, 0.3f);
    sub_E7140(0x1c, 0.2f);
    sub_E7140(0x15, 0.0f);
    sub_E7140(0x16, 0.0f);
    sub_E7140(0x17, 0.0f);
    sub_E7140(0x18, 0.0f);
    sub_E7140(0x19, 0.0f);
    sub_E7140(0x1a, 0.0f);
    sub_E7140(0x1b, 0.0f);
    sub_E7140(0x63, 0.3f);
    sub_E7140(0x64, 0.1f);
    sub_E7140(0x65, 0.2f);
    sub_E7140(0x67, 0.1f);
    sub_E7140(0x69, 0.0f);
    sub_E7140(0x68, 0.0f);
    sub_E5F60(0x5e, 90.0f);
    sub_E5F60(0x5c, 180.0f);
    sub_E5F60(0x5d, 270.0f);
    sub_E09E0(0x7c, 0);
    sub_E09E0(0x7d, 0);
    sub_E09E0(0x7e, 0);
    sub_E09E0(0x7f, 0);
    sub_E09E0(0x7b, 0);
    sub_E09E0(0x80, 0);
    sub_E09E0(0x82, 0);
    sub_E09E0(0x83, 0);
    sub_E09E0(0x84, 0);
    sub_E09E0(0x85, 0);
    sub_E09E0(0x86, 0);
    sub_E09E0(0x87, 0);
    sub_E09E0(0x15, 0);
    sub_E09E0(0x16, 0);
    sub_E09E0(0x18, 0);
    sub_E09E0(0x19, 0);
    sub_E09E0(0x1a, 0);
    sub_E09E0(0x17, 0);
    sub_E09E0(0x1b, 0);
    sub_E09E0(0x1c, 0);
    sub_E09E0(0x14, 0);
    sub_E09E0(0x61, 0);
    sub_E09E0(0x88, 0);
    sub_E09E0(0x5f, 0);
    sub_E09E0(0x60, 0);
    sub_E09E0(8, 0);
    sub_E09E0(9, 0);
    sub_E09E0(0x59, 0);
    sub_E8470();
    sub_E3B90(0x81, 1.0f);
    sub_E3B90(9, 1.0f);
    sub_E70D0(&unk_E0[0]);
    sub_E6610(&unk_E0[0]);
#endif
}

#ifndef CODFH_SP // MP only: no twin in config/sp/shared.txt; its only callers are the HUD's multiplayer parts (already MP only)
// match: ?sub_E3970@@YA?AUtype_1A5EA0@@PBDH@Z @ 0x000E3970
type_1A5EA0 sub_E3970(const RwChar *arg_0, RwInt32 arg_4)
{
    return unk_4FEB0C.sub_1CAF30(arg_0, arg_4);
}
#endif

// match: ?sub_E39B0@type_DC400@@QAEHHPBDH@Z @ 0x000E39B0
// sp-match: ?sub_E39B0@type_DC400@@QAEHHPBDH@Z @ 0x000A9F60
RwInt32 type_DC400::sub_E39B0(RwInt32 arg_0, const RwChar *arg_4, RwInt32 arg_8)
{
    if (unk_E0[arg_0].unk_54)
    {
        if (unk_1A024 && arg_4)
        {
            unk_E0[arg_0].unk_110 = RwTexDictionaryFindNamedTexture(unk_1A024, arg_4);
        }
        else
        {
            unk_E0[arg_0].unk_110 = 0;
        }
        if (!unk_E0[arg_0].unk_110)
        {
            return 0;
        }
        unk_E0[arg_0].unk_114 = unk_E0[arg_0].unk_110->raster;
        if (!unk_E0[arg_0].unk_114)
        {
            return 0;
        }
        if ((unk_E0[arg_0].unk_188.x == 0.0f && unk_E0[arg_0].unk_188.y == 0.0f) || arg_8)
        {
            unk_E0[arg_0].unk_188.x = (RwReal)unk_E0[arg_0].unk_114->width;
            unk_E0[arg_0].unk_188.y = (RwReal)unk_E0[arg_0].unk_114->height;
            if (arg_8)
            {
#ifdef CODFH_SP // shape: single player's buddy icon is item 0x62 (SP 0xA9F60)
                sub_E70D0(&unk_E0[0x62]);
#else
                sub_E70D0(&unk_E0[0x91]);
#endif
            }
        }
    }
    return 1;
}

// match: ?sub_E3B50@type_DC400@@QAEXH@Z @ 0x000E3B50
// sp-match: ?sub_E3B50@type_DC400@@QAEXH@Z @ 0x000A7B20
void type_DC400::sub_E3B50(RwInt32 arg_0)
{
    unk_E0[arg_0].unk_28 = 1;
    unk_E0[arg_0].unk_30 = -1;
}

// match: ?sub_E3B90@type_DC400@@QAEXHM@Z @ 0x000E3B90
// sp-match: ?sub_E3B90@type_DC400@@QAEXHM@Z @ 0x000AA030
void type_DC400::sub_E3B90(RwInt32 arg_0, RwReal arg_4)
{
    RwInt32 var_4;

    var_4 = (RwInt32)(255.0f * arg_4);
    unk_E0[arg_0].unk_24 = arg_4;
    sub_E3CB0(&unk_E0[arg_0], var_4);
    if (arg_0 == 0xE)
    {
        unk_E0[0xF].unk_24 = arg_4;
        unk_E0[0x11].unk_24 = arg_4;
        unk_E0[0x10].unk_24 = arg_4;
    }
    if (arg_0 == 0x14)
    {
        unk_E0[0x15].unk_24 = arg_4;
        unk_E0[0x16].unk_24 = arg_4;
        unk_E0[0x17].unk_24 = arg_4;
        unk_E0[0x18].unk_24 = arg_4;
        unk_E0[0x19].unk_24 = arg_4;
        unk_E0[0x1A].unk_24 = arg_4;
        unk_E0[0x1B].unk_24 = arg_4;
        unk_E0[0x1C].unk_24 = arg_4;
    }
#ifdef CODFH_SP // shape: single player's buddy items 0x61, 0x64 and 0x63 (SP 0xAA030)
    if (arg_0 == 0x61)
    {
        unk_E0[0x64].unk_24 = arg_4;
        unk_E0[0x63].unk_24 = arg_4;
    }
#else
    if (arg_0 == 0x90)
    {
        unk_E0[0x93].unk_24 = arg_4;
        unk_E0[0x92].unk_24 = arg_4;
    }
#endif
    if (arg_0 == 7)
    {
        unk_E0[9].unk_24 = arg_4;
    }
}

// match: ?sub_E3CB0@type_DC400@@QAEXPAUtype_DC400_E0@@H@Z @ 0x000E3CB0
// sp-match: ?sub_E3CB0@type_DC400@@QAEXPAUtype_DC400_E0@@H@Z @ 0x000A7B50
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void type_DC400::sub_E3CB0(type_DC400_E0 *arg_0, RwInt32 arg_4)
{
    RwInt32 var_14;
    RwInt32 lv_10;
    RwUInt32 var_C;
    RwUInt32 bp_8;
    RwUInt32 bp_4;

    for (lv_10 = 0; lv_10 < 4; lv_10++)
    {
        var_C = RwIm2DVertexGetRed(&arg_0->unk_118[lv_10]);
        bp_8 = RwIm2DVertexGetGreen(&arg_0->unk_118[lv_10]);
        bp_4 = RwIm2DVertexGetBlue(&arg_0->unk_118[lv_10]);
        RwIm2DVertexSetIntRGBA(&arg_0->unk_118[lv_10], var_C, bp_8, bp_4, arg_4);
    }
    for (var_14 = 0; var_14 < type_DC400_children; var_14++)
    {
        if (arg_0->unk_204[var_14] && arg_0->unk_204[var_14]->unk_20)
        {
            sub_E3CB0(arg_0->unk_204[var_14], arg_4);
        }
    }
}

// match: ?sub_E3DB0@type_DC400@@QAEXPAUtype_DC400_E0@@H@Z @ 0x000E3DB0
// sp-match: ?sub_E3DB0@type_DC400@@QAEXPAUtype_DC400_E0@@H@Z @ 0x000A7C50
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void type_DC400::sub_E3DB0(type_DC400_E0 *arg_0, RwInt32 arg_4)
{
    RwInt32 var_10;
    RwUInt32 var_C;
    RwUInt32 bp_8;
    RwUInt32 bp_4;

    if (!arg_0)
    {
        return;
    }
    for (var_10 = 0; var_10 < 4; var_10++)
    {
        var_C = RwIm2DVertexGetRed(&arg_0->unk_118[var_10]);
        bp_8 = RwIm2DVertexGetGreen(&arg_0->unk_118[var_10]);
        bp_4 = RwIm2DVertexGetBlue(&arg_0->unk_118[var_10]);
        RwIm2DVertexSetIntRGBA(&arg_0->unk_118[var_10], var_C, bp_8, bp_4, arg_4);
    }
}

// match: ?sub_E3E60@type_DC400@@QAEXMPAURwV3d@@0PAMM@Z @ 0x000E3E60
// sp-match: ?sub_E3E60@type_DC400@@QAEXMPAURwV3d@@0PAMM@Z @ 0x000A7D20
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void type_DC400::sub_E3E60(RwReal arg_0, RwV3d *arg_4, RwV3d *arg_8, RwReal *arg_C, RwReal arg_10)
{
    RwMatrix *var_20;
    RwReal l1C;
    RwV3d m_18;
    RwReal var_C;
    RwReal bp_8;
    RwCamera *bp_4;

    bp_4 = (RwCamera *)dword_4E5C74;
    var_20 = RwFrameGetMatrix(RwCameraGetFrame(bp_4));
    arg_4->z = 1.0f;
    arg_4->x = 0.0f;
    arg_4->y = 0.0f;
    m_18 = var_20->at;
    m_18.y = 0.0f;
    arg_8->y = 0.0f;
    RwV3dNormalize(&m_18, &m_18);
    RwV3dNormalize(arg_8, arg_8);
    var_C = sub_141240(&m_18, arg_8) + 180.0f;
    bp_8 = 0.0f;
    l1C = *arg_C - var_C;
    if (l1C > 180.0f)
    {
        l1C -= 360.0f;
    }
    if (l1C < -180.0f)
    {
        l1C += 360.0f;
    }
    sub_112DA0(&l1C, 0.0f, &bp_8, 0.2f, 0.9f, 5.0f, arg_0);
    *arg_C = var_C + l1C;
    arg_4->x = sinf(*arg_C * 0.017453292f);
    arg_4->z = cosf(*arg_C * 0.017453292f);
    RwV3dScale(arg_4, arg_4, arg_10 * unk_E0[0x1F].unk_188.y * 0.35f);
}

// match: ?sub_E4030@type_DC400@@QAEXM@Z @ 0x000E4030
// match: __ehhandler$?sub_E4030@type_DC400@@QAEXM@Z-0x8 @ 0x00300EA0
// match: __ehhandler$?sub_E4030@type_DC400@@QAEXM@Z @ 0x00300EA8
// sp-match: ?sub_E4030@type_DC400@@QAEXM@Z @ 0x000ABF70
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void type_DC400::sub_E4030(RwReal arg_0)
{
    RwV3d stk_130;
    RwInt32 l124;
    RwInt32 l120;
    RwReal q11C;
    RwReal lv_118;
    RwReal lcl_114;
    RwReal o110;
    RwReal lv_10C;
    RwInt32 frm_108;
    RwInt32 loc104;
    RwReal x100;
    RwV3d stk_FC;
    RwV3d lcl_F0;
    RwInt32 varE4;
    RwReal xE0;
#ifndef CODFH_SP
    RwV3d varDC;
#endif
    RwInt32 vD0;
    RwReal stk_CC;
    RwReal stk_C8;
    RwReal lcl_C4;
    RwV3d varC0;
    RwReal lB4;
    RwReal xB0;
    RwReal locAC;
    RwReal slot_A8;
    RwV3d bp_A4;
    RwReal s98;
    RwReal var94;
    RwReal x90;
    type_4E56A0_34 *ebp_8C;
    type_3D3548 *loc88;
    RwReal u84;
    RwInt32 frm_80;
    RwReal bp_7C;
    type_4E56A0 *var_78;
    RwInt32 var_74;
    RwReal var70;
    RwReal stk_6C;
    RwV3d q68;
    RwMatrix *x4C;
    RwReal w48;
    RwInt32 loc44;
    type_3D3548 *fp_40;
    RwReal l3C;
    RwV3d local_38;
    RwV3d *stk_2C;
#ifndef CODFH_SP
    RwV3d var28;
#endif
    RwCamera *l1C;
    RwV3d m_18;

    stk_6C = dword_4B8EF0.unk_00;
    stk_2C = 0;
    fp_40 = sub_1745A0(0);
    if (!fp_40)
    {
        return;
    }
    q68 = *fp_40->sub_CD550();
    q68.y -= fp_40->unk_48;
    l1C = (RwCamera *)dword_4E5C74;
    x4C = RwFrameGetMatrix(RwCameraGetFrame(l1C));
    var70 = atan2(x4C->at.z, x4C->at.x) * 57.295776f;
    stk_6C = sub_13F9E0(stk_6C);
    unk_D4 = sub_13F9E0(var70 - stk_6C);
    unk_1A040 = sub_13F9E0(unk_D4);
    l3C = unk_1A044 - unk_1A040;
    if (l3C > 180.0f)
    {
        l3C -= 360.0f;
    }
    if (l3C < -180.0f)
    {
        l3C += 360.0f;
    }
    sub_112DA0(&l3C, 0.0f, &unk_1A048, 0.01f, 0.92f, 11.0f, arg_0);
    unk_1A044 = l3C + unk_1A040;
    sub_E5F60(0x1F, -unk_1A044);
    sub_E5F60(0x1F, -unk_1A044);
#ifndef CODFH_SP // single player has no marker items 0x31..0x40 and resets none (SP 0xAC0CA)
    sub_E09E0(0x31, 0);
    sub_E09E0(0x32, 0);
    sub_E09E0(0x33, 0);
    sub_E09E0(0x34, 0);
    sub_E09E0(0x35, 0);
    sub_E09E0(0x36, 0);
    sub_E09E0(0x37, 0);
    sub_E09E0(0x38, 0);
    sub_E09E0(0x39, 0);
    sub_E09E0(0x3A, 0);
    sub_E09E0(0x3B, 0);
    sub_E09E0(0x3C, 0);
    sub_E09E0(0x3D, 0);
    sub_E09E0(0x3E, 0);
    sub_E09E0(0x20, 0);
    sub_E09E0(0x21, 0);
    sub_E09E0(0x3F, 0);
    sub_E09E0(0x40, 0);
#endif
#ifdef CODFH_SP // single player points at one objective, sp_sub_10DBA0's (SP 0xAC0CA)
    var_74 = 0;
    var_78 = sub_1708B0(sp_sub_10DBA0());
    {
#else
    std::vector<RwInt32> y5C;

    sub_1708E0(&y5C);
    loc44 = y5C.size();
    for (var_74 = 0; var_74 < loc44; var_74++)
    {
        var_78 = (type_4E56A0 *)y5C[var_74];
#endif
        if (var_78 && var_78->unk_40 != -1)
        {
            loc88 = 0;
            ebp_8C = 0;
            switch (var_78->unk_40)
            {
            case 1:
                loc88 = var_78->unk_38.sub_D4910();
                if (loc88)
                {
                    stk_2C = var_78->unk_38.sub_D4910()->sub_CD550();
                }
                else
                {
                    sub_E09E0(0x20, 0);
                    sub_E09E0(0x21, 0);
#ifdef CODFH_SP // single player stops here (SP 0xAC114)
                    return;
#else
                    continue;
#endif
                }
                break;
            case 0:
                ebp_8C = var_78->unk_2C.unk_08_obj;
                if (ebp_8C)
                {
                    stk_2C = get_unk_90(var_78->unk_2C.unk_08_obj);
                }
                else
                {
                    sub_E09E0(0x20, 0);
                    sub_E09E0(0x21, 0);
#ifdef CODFH_SP // single player stops here (SP 0xAC114)
                    return;
#else
                    continue;
#endif
                }
                break;
            }
            if (var_78->unk_3C)
            {
                var94 = var_78->unk_3C->sub_BA450(&q68, flt_4293EC, flt_4293F0);
                slot_A8 = (x90 = var_78->unk_3C->sub_BA450(stk_2C, 100.0f, 1.0f)) - var94;
                if (slot_A8 != 0.0f)
                {
#ifdef CODFH_SP // shape: block-scoped, sharing var28's slot (SP frame 0x98)
                    RwV3d varDC;

#endif
                    if (var_78->unk_4C == -1.0f)
                    {
                        var_78->unk_4C = 1.0f;
                        if (var_78->unk_48 == -1.0f)
                        {
                            if (unk_08)
                            {
                                var_78->unk_48 = 1000000.0f;
                            }
                            else
                            {
                                var_78->unk_48 = 250000.0f;
                            }
                        }
                        frm_108 = 0;
                        x100 = 3.4028235e38f;
                        loc104 = 0;
                        var_78->unk_3C->sub_BA990(0.0f, &stk_FC, 0);
                        while (!loc104)
                        {
                            var_78->unk_3C->sub_BA990(var_78->unk_4C, &lcl_F0, 0);
                            x100 = sub_140C90(&stk_FC, &lcl_F0);
                            if (x100 < var_78->unk_48 || frm_108 > 100)
                            {
                                loc104 = 1;
                            }
                            else
                            {
                                var_78->unk_4C /= 2.0f;
                                frm_108++;
                            }
                        }
                        var_78->unk_50 = var_78->unk_4C / 4.0f;
                    }
                    locAC = slot_A8 / fabs(slot_A8);
                    var_78->unk_3C->sub_BA990(var94, &varDC, 0);
                    s98 = locAC * var_78->unk_4C + var94;
                    if (s98 > 1.0f)
                    {
                        s98 = 1.0f;
                    }
                    else if (s98 < 0.0f)
                    {
                        s98 = 0.0f;
                    }
                    var_78->unk_3C->sub_BA990(s98, &varC0, 0);
                    stk_C8 = sub_140C90(&varC0, &varDC);
                    vD0 = 0;
                    varE4 = 0;
                    lB4 = 0.0f;
                    stk_CC = 0.0f;
                    lcl_C4 = 0.0f;
                    xE0 = var_78->unk_4C;
                    stk_CC = fabs(var_78->unk_48 - stk_C8);
                    if (stk_CC < flt_4293E8)
                    {
                        vD0 = 1;
                    }
                    else if (stk_C8 > var_78->unk_48)
                    {
                        lB4 = -var_78->unk_50;
                    }
                    else
                    {
                        lB4 = var_78->unk_50;
                    }
                    while (!vD0)
                    {
                        xE0 = var_78->unk_4C;
                        var_78->unk_4C = lB4 + var_78->unk_4C;
                        if (var_78->unk_4C > 1.0f)
                        {
                            var_78->unk_4C = 1.0f;
                        }
                        else if (var_78->unk_4C < 0.0f)
                        {
                            var_78->unk_4C = 0.0f;
                        }
                        s98 = locAC * var_78->unk_4C + var94;
                        if (s98 > 1.0f)
                        {
                            s98 = 1.0f;
                        }
                        else if (s98 < 0.0f)
                        {
                            s98 = 0.0f;
                        }
                        var_78->unk_3C->sub_BA990(s98, &varC0, 0);
                        xB0 = stk_C8;
                        stk_C8 = sub_140C90(&varC0, &varDC);
                        lcl_C4 = stk_CC;
                        stk_CC = fabs(var_78->unk_48 - stk_C8);
                        if (stk_CC < flt_4293E8)
                        {
                            if (lcl_C4 < stk_CC)
                            {
                                var_78->unk_4C = xE0;
                                stk_CC = lcl_C4;
                            }
                            vD0 = 1;
                        }
                        else if ((lB4 > 0.0f && (stk_C8 > var_78->unk_48 || var_78->unk_4C == 1.0f))
                                 || (lB4 < 0.0f && (stk_C8 < var_78->unk_48 || var_78->unk_4C == 0.0f)))
                        {
                            lcl_114 = xB0;
                            o110 = stk_C8;
                            if (o110 - lcl_114 == 0.0f)
                            {
                                lv_10C = 1.0f;
                            }
                            else
                            {
                                lv_10C = o110 - lcl_114;
                            }
                            lv_118 = (var_78->unk_48 - lcl_114) / lv_10C;
                            q11C = (var_78->unk_4C - xE0) * lv_118 + xE0;
                            var_78->unk_4C = q11C;
                            vD0 = 1;
                        }
                        varE4++;
                        if (varE4 > flt_4293E4)
                        {
                            vD0 = 1;
                        }
                    }
                    s98 = locAC * var_78->unk_4C + var94;
                    if (s98 > 1.0f)
                    {
                        s98 = 1.0f;
                    }
                    else if (s98 < 0.0f)
                    {
                        s98 = 0.0f;
                    }
                }
                else
                {
                    s98 = x90;
                }
                if (fabs(x90 - var94) < fabs(s98 - var94))
                {
                    s98 = x90;
                }
                var_78->unk_3C->sub_BA990(s98, &m_18, 0);
                RwV3dSub(&local_38, &m_18, &q68);
                RwV3dSub(&bp_A4, stk_2C, &q68);
                w48 = (w48 = (w48 = RwV3dLength((RwV3d *)&bp_A4)) / 100.0f) / flt_4B8F30;
                if (w48 > 1.0f || var_78->unk_04 & 0x100)
                {
                    w48 = 1.0f;
                }
            }
            else
            {
                m_18 = *stk_2C;
                RwV3dSub(&local_38, &m_18, &q68);
                w48 = (w48 = (w48 = RwV3dLength((RwV3d *)&local_38)) / 100.0f) / flt_4B8F30;
                if (w48 > 1.0f || var_78->unk_04 & 0x100)
                {
                    w48 = 1.0f;
                }
            }
#ifdef CODFH_SP // shape: declared here, sharing varDC's slot (SP 0xAC63A)
            RwV3d var28;

#endif
            sub_E3E60(arg_0, &var28, &local_38, &unk_1A04C[var_74], w48);
#ifdef CODFH_SP // single player shows the objective's arrow (0x20) and pulse (0x21) (SP 0xAC647)
            sub_E09E0(0x20, 1);
            sub_E6200(0x20, var28.x, var28.z);
            sub_E6610(&unk_E0[0x20]);
            if (sub_1712C0(var_78, &u84, &bp_7C))
            {
                sub_E09E0(0x21, 1);
                sub_E6200(0x21, var28.x, var28.z);
                sub_E6270(0x21, u84, u84);
                sub_E3B90(0x21, bp_7C);
                sub_E6610(&unk_E0[0x21]);
            }
            else
            {
                sub_E09E0(0x21, 0);
            }
#else
            sub_E09E0(0x20, 0);
            sub_E09E0(0x21, 0);
            if (var_74 == 0)
            {
                frm_80 = 0x3F;
            }
            else
            {
                frm_80 = 0x40;
            }
            if (sub_1712C0(var_78, &u84, &bp_7C))
            {
                sub_E09E0(frm_80, 1);
                sub_E6200(frm_80, var28.x, var28.z);
                sub_E6270(frm_80, u84, u84);
                sub_E3B90(frm_80, bp_7C);
                sub_E6610(&unk_E0[frm_80]);
            }
            else
            {
                sub_E09E0(frm_80, 0);
            }
            switch (dword_4FB9E0.get_game_type())
            {
            case 8:
                if (!(var_78->unk_04 & 4))
                {
                    if (var_74 == 0)
                    {
                        if (var_78->unk_04 & 0x80)
                        {
                            if (var_78->unk_04 & 2)
                            {
                                sub_E09E0(0x39, 1);
                                sub_E6200(0x39, var28.x, var28.z);
                            }
                            else
                            {
                                sub_E09E0(0x37, 1);
                                sub_E6200(0x37, var28.x, var28.z);
                            }
                        }
                        else if (var_78->unk_04 & 2)
                        {
                            sub_E09E0(0x35, 1);
                            sub_E6200(0x35, var28.x, var28.z);
                        }
                        else if (dword_4FB9E0.get_team_count() == 4)
                        {
                            sub_E09E0(0x31, 1);
                            sub_E6200(0x31, var28.x, var28.z);
                        }
                        else
                        {
                            sub_E09E0(0x33, 1);
                            sub_E6200(0x33, var28.x, var28.z);
                        }
                    }
                    else
                    {
                        if (var_78->unk_04 & 0x80)
                        {
                            if (var_78->unk_04 & 2)
                            {
                                sub_E09E0(0x3A, 1);
                                sub_E6200(0x3A, var28.x, var28.z);
                            }
                            else
                            {
                                sub_E09E0(0x38, 1);
                                sub_E6200(0x38, var28.x, var28.z);
                            }
                        }
                        else if (var_78->unk_04 & 2)
                        {
                            sub_E09E0(0x36, 1);
                            sub_E6200(0x36, var28.x, var28.z);
                        }
                        else if (dword_4FB9E0.get_team_count() == 4)
                        {
                            sub_E09E0(0x32, 1);
                            sub_E6200(0x32, var28.x, var28.z);
                        }
                        else
                        {
                            sub_E09E0(0x34, 1);
                            sub_E6200(0x34, var28.x, var28.z);
                        }
                    }
                }
                break;
            case 4:
                if (!(var_78->unk_04 & 4))
                {
                    if (var_74 == 1)
                    {
                        if (var_78->unk_04 & 2)
                        {
                            sub_E09E0(0x3E, 1);
                            sub_E6200(0x3E, var28.x, var28.z);
                        }
                        else
                        {
                            sub_E09E0(0x3E, 1);
                            sub_E6200(0x3E, var28.x, var28.z);
                        }
                    }
                    else
                    {
                        switch (unk_4F7EB8.sub_1AF2F0(2))
                        {
                        case 0:
                            l120 = 0x3B;
                            break;
                        case 1:
                            l120 = 0x3C;
                            break;
                        default:
                            l120 = 0x3D;
                            break;
                        }
                        if (var_78->unk_04 & 2)
                        {
                            sub_E09E0(l120, 1);
                            sub_E6200(l120, var28.x, var28.z);
                        }
                        else
                        {
                            sub_E09E0(l120, 1);
                            sub_E6200(l120, var28.x, var28.z);
                        }
                    }
                }
                break;
            }
#endif
        }
#ifdef CODFH_SP // no objective: arrow and pulse hidden (SP 0xAC6C9)
        else
        {
            sub_E09E0(0x20, 0);
            sub_E09E0(0x21, 0);
        }
#endif
    }
    for (l124 = 0; l124 < 15; l124++)
    {
        stk_2C = sub_171340(l124);
        if (stk_2C)
        {
            m_18 = *stk_2C;
            RwV3dSub(&local_38, &m_18, &q68);
            w48 = RwV3dLength((RwV3d *)&local_38);
            w48 = w48 / (100.0f * flt_4B8F30);
            if (w48 > 1.0f)
            {
                w48 = 1.0f;
            }
            sub_E3E60(arg_0, &stk_130, &local_38, &unk_1A054[l124], w48);
            sub_E09E0(l124 + 0x22, 1);
            sub_E6200(l124 + 0x22, stk_130.x, stk_130.z);
        }
        else
        {
            sub_E09E0(l124 + 0x22, 0);
        }
    }
}

// match: ?sub_E52B0@type_DC400@@QAEXPBD@Z @ 0x000E52B0
// sp-match: ?sub_E52B0@type_DC400@@QAEXPBD@Z @ 0x000A7E90
void type_DC400::sub_E52B0(const RwChar *arg_0)
{
    RwChar var_48[0x40];

    memset(var_48, 0, sizeof(var_48));
    if (arg_0)
    {
        strncpy(var_48, arg_0, 0x3F);
    }
    else
    {
        strncpy(var_48, unk_1A4C0, 0x3F);
    }
    if (unk_1A028)
    {
        sub_16C220("Unloading current font: %s for new font.", unk_1A4C0);
        delete unk_1A028;
        unk_1A028 = 0;
    }
    if (1)
    {
        dword_4E23A8 = 1;
        sub_16C220("Attempting to load new HUD font: %s", var_48);
        unk_1A028 = type_DA580::sub_DA680(var_48);
        if (!unk_1A028)
        {
            strcpy(var_48, "t10");
            unk_1A028 = type_DA580::sub_DA680(var_48);
        }
        memset(unk_1A4C0, 0, sizeof(unk_1A4C0));
        strncpy(unk_1A4C0, var_48, 0x3F);
        dword_4E23A8 = 0;
        sub_186970(unk_1A028);
    }
    else
    {
        memset(dword_4B9190->unk_1A4C0, 0, sizeof(dword_4B9190->unk_1A4C0));
        strncpy(dword_4B9190->unk_1A4C0, var_48, 0x3F);
    }
}

#ifdef CODFH_SP
// sp-match: ?sp_sub_A7FB0@type_DC400@@QAEXXZ @ 0x000A7FB0
// Single player only (SP 0xA7FB0): the pause screen's objectives list, from
// dword_4B8F54 down by the font's line height. Each shown objective (flag 2; not
// flag 4 on level 30) reads "- " and its text in its colour (dword_4B8F48 for flag 4,
// dword_4B8F4C for 8, dword_4B8F50 for 0x10, else dword_4B8F44), faded in by its
// unk_14 of dword_4B8F5C; the next one starts once this one is past half
// (unk_1A4BC counts them).
void type_DC400::sp_sub_A7FB0()
{
    RwChar var_80[0x80];
    Rt2dBBox var_bbox;
    RwV2d var_pos;
    RwReal var_scale;
    RwV2d var_at;
    RwInt8 var_id;
    RwRGBA var_c;
    bool var_level;
    type_4E56A0 *var_o;
    RwInt32 var_n;

    var_pos.x = dword_4B8F54.x;
    var_pos.y = dword_4B8F54.y;
    var_n = 0;
    var_at = var_pos;
    var_at.y -= unk_1A028->sub_DA790();
    var_scale = 1.0f;
    if (dword_4CF9A8)
    {
        var_scale = 0.8333333f;
    }
    var_id = byte_4E564D;
    var_o = sub_1708B0(var_id);
    var_level = sub_19B050() == 30;
    Rt2dCTMPush();
    Rt2dCTMSetIdentity();
    Rt2dCTMScale(dword_4B8970 * var_scale, 1.0f);
    while (var_o)
    {
        if ((var_o->unk_04 & 2) && (!(var_o->unk_04 & 4) || !var_level))
        {
            if (var_o->unk_04 & 4)
            {
                var_c = dword_4B8F48;
            }
            else if (var_o->unk_04 & 8)
            {
                var_c = dword_4B8F4C;
            }
            else if (var_o->unk_04 & 0x10)
            {
                var_c = dword_4B8F50;
            }
            else
            {
                var_c = dword_4B8F44;
            }
            if (var_n <= unk_1A4BC)
            {
                var_c.alpha = (RwUInt8)(var_o->unk_14 / dword_4B8F5C * 255.0f);
            }
            else
            {
                var_c.alpha = 0;
            }
            if (var_n == unk_1A4BC && var_c.alpha > 0x80)
            {
                unk_1A4BC++;
            }
            sprintf(var_80, "- ");
            var_o->unk_00->sub_197550(var_80 + 2, var_o->unk_08);
            var_bbox.x = var_pos.x / dword_4B8970;
            var_bbox.y = var_at.y - 0.5f + unk_1A028->sub_DA790();
            var_bbox.w = 1.0f - (var_bbox.x + var_bbox.x);
            var_bbox.h = 0.5f;
            unk_1A028->sub_DAC60(var_80, &var_bbox, 0.0f, 0, &var_c, 0.0f);
            var_at.y -= unk_1A028->sub_DA8C0(var_80, &var_bbox, 0.0f);
            var_n++;
        }
        var_id = sub_170890(var_id);
        var_o = sub_1708B0(var_id);
    }
    Rt2dCTMPop();
}

// sp-match: ?sp_sub_A81E0@type_DC400@@QAEXXZ @ 0x000A81E0
// Single player only (SP 0xA81E0): the pause screen's black over the whole screen, as
// sub_E5C60's flash, at unk_1A4B4 of dword_4B8F5C of the opacity dword_4B8F60 while it
// fades in (unk_1A4B8 clear), then at dword_4B8F60.
void type_DC400::sp_sub_A81E0()
{
    RwInt32 var_94;
    void *var_90;
    void *l8C;
    void *var_88;
    void *lcl_84;
    void *var_80;
    void *var_7C;
    void *m_78;
    void *v74;
    RwIm2DVertex l70[4];
    RwInt32 var_alpha;

    if (unk_1A4B8)
    {
        var_alpha = (RwInt32)(dword_4B8F60 * 255.0f);
    }
    else
    {
        var_alpha = (RwInt32)(unk_1A4B4 / dword_4B8F5C * dword_4B8F60 * 255.0f);
    }
    RwRenderStateGet(rwRENDERSTATESRCBLEND, &m_78);
    RwRenderStateGet(rwRENDERSTATEDESTBLEND, &l8C);
    RwRenderStateGet(rwRENDERSTATEVERTEXALPHAENABLE, &lcl_84);
    RwRenderStateGet(rwRENDERSTATEZWRITEENABLE, &var_80);
    RwRenderStateGet(rwRENDERSTATEZTESTENABLE, &var_90);
    RwRenderStateGet(rwRENDERSTATEFOGENABLE, &v74);
    RwRenderStateGet(rwRENDERSTATETEXTURERASTER, &var_7C);
    RwRenderStateGet(rwRENDERSTATESHADEMODE, &var_88);
    RwRenderStateSet(rwRENDERSTATESRCBLEND, (void *)rwBLENDSRCALPHA);
    RwRenderStateSet(rwRENDERSTATEDESTBLEND, (void *)rwBLENDINVSRCALPHA);
    RwRenderStateSet(rwRENDERSTATEVERTEXALPHAENABLE, (void *)TRUE);
    RwRenderStateSet(rwRENDERSTATEZWRITEENABLE, (void *)FALSE);
    RwRenderStateSet(rwRENDERSTATEZTESTENABLE, (void *)FALSE);
    RwRenderStateSet(rwRENDERSTATEFOGENABLE, (void *)FALSE);
    RwRenderStateSet(rwRENDERSTATETEXTURERASTER, (void *)NULL);
    RwRenderStateSet(rwRENDERSTATESHADEMODE, (void *)rwSHADEMODEGOURAUD);
    RwIm2DVertexSetScreenX(&l70[0], 0.0f);
    RwIm2DVertexSetScreenY(&l70[0], 0.0f);
    RwIm2DVertexSetScreenX(&l70[1], 0.0f);
    RwIm2DVertexSetScreenY(&l70[1], (RwReal)(RwUInt32)Height);
    RwIm2DVertexSetScreenX(&l70[2], (RwReal)(RwUInt32)Width);
    RwIm2DVertexSetScreenY(&l70[2], (RwReal)(RwUInt32)Height);
    RwIm2DVertexSetScreenX(&l70[3], (RwReal)(RwUInt32)Width);
    RwIm2DVertexSetScreenY(&l70[3], 0.0f);
    for (var_94 = 0; var_94 < 4; var_94++)
    {
        RwIm2DVertexSetScreenZ(&l70[var_94], RwIm2DGetNearScreenZ());
        RwIm2DVertexSetRecipCameraZ(&l70[var_94], 1.0f / RwCameraGetNearClipPlane(unk_1A02C));
        RwIm2DVertexSetIntRGBA(&l70[var_94], 0, 0, 0, var_alpha);
    }
    RwIm2DRenderPrimitive(rwPRIMTYPETRIFAN, l70, 4);
    RwRenderStateSet(rwRENDERSTATESRCBLEND, m_78);
    RwRenderStateSet(rwRENDERSTATEDESTBLEND, l8C);
    RwRenderStateSet(rwRENDERSTATEVERTEXALPHAENABLE, lcl_84);
    RwRenderStateSet(rwRENDERSTATEZWRITEENABLE, var_80);
    RwRenderStateSet(rwRENDERSTATEZTESTENABLE, var_90);
    RwRenderStateSet(rwRENDERSTATEFOGENABLE, v74);
    RwRenderStateSet(rwRENDERSTATETEXTURERASTER, var_7C);
    RwRenderStateSet(rwRENDERSTATESHADEMODE, var_88);
}
#endif

// match: ?sub_E5480@type_DC400@@QAEXPAUtype_DC400_E0@@@Z @ 0x000E5480
// sp-match: ?sub_E5480@type_DC400@@QAEXPAUtype_DC400_E0@@@Z @ 0x000A8450
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void type_DC400::sub_E5480(type_DC400_E0 *arg_0)
{
    RwInt32 var_850;
    RwInt32 l84C;
    RwInt32 s848;
    RwUInt32 var844;
    RwReal s840;
    RwUInt32 local_83C;
    RwChar w838[0x400];
    RwReal u434;
    Rt2dBBox u430;
    RwChar local_420[0x400];
    RwReal loc1C;
    RwRGBA bp_18;
    RwReal var_14;
    RwReal lv_10;
    RwV2d var_C;
    RwInt32 bp_4;

    if (!arg_0 || !arg_0->unk_20 || !arg_0->unk_50)
    {
        return;
    }
    for (bp_4 = 0; bp_4 < type_DC400_children; bp_4++)
    {
        if (arg_0->unk_204[bp_4] && arg_0->unk_204[bp_4]->unk_20)
        {
            sub_E5480(arg_0->unk_204[bp_4]);
        }
    }
#ifndef CODFH_SP // MP only: single player's items have no unk_2B0 (SP 0xA8450 has no check)
    if (arg_0->unk_2B0)
    {
        return;
    }
#endif
    if (arg_0->unk_58 && unk_1A028)
    {
        var_14 = 1.0f;
        lv_10 = 1.0f;
        if (dword_4CF9A8)
        {
            var_14 = 1.3333f;
            lv_10 = 1.0f / var_14;
        }
        Rt2dCTMPush();
        Rt2dCTMSetIdentity();
        Rt2dCTMScale(lv_10 * dword_4B8970, 1.0f);
        var_C.x = arg_0->unk_1F4.x / (RwReal)(RwUInt32)Width;
        var_C.y = arg_0->unk_1F4.y / (RwReal)(RwUInt32)Height;
#ifdef CODFH_SP // shape: the scale over the aspect first (SP 0xA8450)
        var_C.x = (1.1666666f / dword_4B8970) * var_C.x;
#else
        var_C.x = 1.1666666f / dword_4B8970 * var_C.x;
#endif
        if (dword_4CF9A8)
        {
            var_C.x = (var_14 + flt_4293C4) * var_C.x;
        }
        bp_18.red = (RwUInt8)(255.0f * arg_0->unk_34.red);
        bp_18.green = (RwUInt8)(255.0f * arg_0->unk_34.green);
        bp_18.blue = (RwUInt8)(255.0f * arg_0->unk_34.blue);
        bp_18.alpha = (RwUInt8)(arg_0->unk_24 * 255.0f * arg_0->unk_34.alpha);
        if (arg_0 == &unk_E0[2])
        {
            if (unk_1A15C && dword_4F28F0->get_unk_21())
            {
                switch (sub_19B0A0())
                {
                case 2:
                    if (sub_19BCB0(unk_1A15C, local_420))
                    {
                        unk_1A15C = local_420;
                    }
                    break;
                case 1:
                    if (sub_19BC70((RwChar *)unk_1A15C, local_420))
                    {
                        unk_1A15C = local_420;
                    }
                    if (sub_19BC70(unk_1A164, w838))
                    {
                        strcpy(unk_1A164, w838);
                    }
                    break;
                }
                u430.h = unk_E0[2].unk_188.y;
                u430.w = unk_E0[2].unk_188.x;
                u430.x = dword_4B8F88.x;
                u430.y = dword_4B8F88.y;
                if (((type_10F710 *)sub_1745A0(0))->unk_19D0 == 5)
                {
                    u430.y += flt_4293D8;
                }
                u430.x /= dword_4B8970;
                if (dword_4B897C)
                {
                    u430.x += 0.07f;
                }
                u430.y += 0.05f;
                loc1C = 0.0f;
                u434 = unk_1A028->sub_DA8C0(unk_1A15C, &u430, 0.0f);
                if (u430.h < u434)
                {
                    s840 = 1.0f / unk_1A028->sub_DA790();
                    local_83C = (RwUInt32)ceilf(u434 * s840);
                    var844 = (RwUInt32)(u430.h * s840);
                    loc1C = unk_1A160 / dword_4B8FA0 * unk_1A028->sub_DA790() - u430.h;
                    if (loc1C < 0.0f)
                    {
                        loc1C = 0.0f;
                    }
                    if (unk_1A028->sub_DA790() * (RwReal)(local_83C - var844) < loc1C)
                    {
                        loc1C = unk_1A028->sub_DA790() * (RwReal)(local_83C - var844);
                    }
                }
                unk_1A028->sub_DAC60(unk_1A15C, &u430, loc1C, 0, &dword_4B8F98, 0.0f);
                unk_1A028->sub_DAC60(unk_1A164, &u430, loc1C, 0, &dword_4B8F9C, 0.0f);
#ifdef CODFH_SP // shape: the frame time scaled first (SP 0xA8450 multiplies by 16.67 and by 1/1000)
                unk_1A160 = (deltaTime * flt_3D8058) / 1000.0f + unk_1A160;
#else
                unk_1A160 = deltaTime * flt_3D8058 / 1000.0f + unk_1A160;
#endif
                unk_1A15C = 0;
            }
        }
        else
        {
            s848 = arg_0 - unk_E0;
            switch (s848)
            {
            case 9:
            case 15:
            case 16:
            case 17:
                var_C.y = 25.0f / (RwReal)(RwUInt32)Height + var_C.y;
                break;
            case 27:
                var_C.y = var_C.y - 25.0f / (RwReal)(RwUInt32)Height;
                break;
            }
            RwRenderStateSet(rwRENDERSTATEALPHATESTFUNCTIONREF, (void *)0x82);
            unk_1A028->sub_DAB00(arg_0->unk_60, &var_C, &bp_18, 0.0f, 0);
            RwRenderStateSet(rwRENDERSTATEALPHATESTFUNCTIONREF, (void *)0);
        }
        Rt2dCTMPop();
    }
    else
    {
        if (arg_0->unk_54)
        {
            arg_0->unk_114 = arg_0->unk_110->raster;
            RwRenderStateSet(rwRENDERSTATETEXTURERASTER, arg_0->unk_114);
        }
        else
        {
            RwRenderStateSet(rwRENDERSTATETEXTURERASTER, (void *)NULL);
        }
        l84C = arg_0 - unk_E0;
        if (l84C == 29)
        {
            dword_4B8980 = 1;
        }
        if (arg_0->unk_2AC & 1)
        {
            return;
        }
        if (l84C == 30)
        {
            for (var_850 = 0; var_850 < 4; var_850++)
            {
                RwIm2DVertexSetScreenZ(&arg_0->unk_118[var_850], 1.0f);
            }
        }
        switch (l84C)
        {
        case 21:
        case 22:
        case 23:
        case 24:
        case 25:
        case 26:
            RwRenderStateSet(rwRENDERSTATEALPHATESTFUNCTIONREF, (void *)0xDC);
            break;
        }
        RwIm2DRenderPrimitive(rwPRIMTYPETRISTRIP, arg_0->unk_118, 4);
        RwRenderStateSet(rwRENDERSTATEALPHATESTFUNCTIONREF, (void *)0);
    }
}

// match: ?sub_E5C60@type_DC400@@QAEXXZ @ 0x000E5C60
// sp-match: ?sub_E5C60@type_DC400@@QAEXXZ @ 0x000A89F0
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void type_DC400::sub_E5C60()
{
    RwInt32 var_94;
    void *var_90;
    void *l8C;
    void *var_88;
    void *lcl_84;
    void *var_80;
    void *var_7C;
    void *m_78;
    void *v74;
    RwIm2DVertex l70[4];

    RwRenderStateGet(rwRENDERSTATESRCBLEND, &m_78);
    RwRenderStateGet(rwRENDERSTATEDESTBLEND, &l8C);
    RwRenderStateGet(rwRENDERSTATEVERTEXALPHAENABLE, &lcl_84);
    RwRenderStateGet(rwRENDERSTATEZWRITEENABLE, &var_80);
    RwRenderStateGet(rwRENDERSTATEZTESTENABLE, &var_90);
    RwRenderStateGet(rwRENDERSTATEFOGENABLE, &v74);
    RwRenderStateGet(rwRENDERSTATETEXTURERASTER, &var_7C);
    RwRenderStateGet(rwRENDERSTATESHADEMODE, &var_88);
    RwRenderStateSet(rwRENDERSTATESRCBLEND, (void *)rwBLENDSRCALPHA);
    RwRenderStateSet(rwRENDERSTATEDESTBLEND, (void *)rwBLENDINVSRCALPHA);
    RwRenderStateSet(rwRENDERSTATEVERTEXALPHAENABLE, (void *)TRUE);
    RwRenderStateSet(rwRENDERSTATEZWRITEENABLE, (void *)FALSE);
    RwRenderStateSet(rwRENDERSTATEZTESTENABLE, (void *)FALSE);
    RwRenderStateSet(rwRENDERSTATEFOGENABLE, (void *)FALSE);
    RwRenderStateSet(rwRENDERSTATETEXTURERASTER, (void *)NULL);
    RwRenderStateSet(rwRENDERSTATESHADEMODE, (void *)rwSHADEMODEGOURAUD);
    RwIm2DVertexSetScreenX(&l70[0], 0.0f);
    RwIm2DVertexSetScreenY(&l70[0], 0.0f);
    RwIm2DVertexSetScreenX(&l70[1], 0.0f);
    RwIm2DVertexSetScreenY(&l70[1], (RwReal)(RwUInt32)Height);
    RwIm2DVertexSetScreenX(&l70[2], (RwReal)(RwUInt32)Width);
    RwIm2DVertexSetScreenY(&l70[2], (RwReal)(RwUInt32)Height);
    RwIm2DVertexSetScreenX(&l70[3], (RwReal)(RwUInt32)Width);
    RwIm2DVertexSetScreenY(&l70[3], 0.0f);
    for (var_94 = 0; var_94 < 4; var_94++)
    {
        RwIm2DVertexSetScreenZ(&l70[var_94], RwIm2DGetNearScreenZ());
        RwIm2DVertexSetRecipCameraZ(&l70[var_94], 1.0f / RwCameraGetNearClipPlane((RwCamera *)dword_4E5C74));
        RwIm2DVertexSetIntRGBA(&l70[var_94], (RwInt32)(unk_1A0B0 * 255.0f), (RwInt32)(unk_1A0B4 * 255.0f),
                               (RwInt32)(unk_1A0B8 * 255.0f), (RwInt32)(unk_1A0C4 * 128.0f));
    }
    RwIm2DRenderPrimitive(rwPRIMTYPETRIFAN, l70, 4);
    RwRenderStateSet(rwRENDERSTATESRCBLEND, m_78);
    RwRenderStateSet(rwRENDERSTATEDESTBLEND, l8C);
    RwRenderStateSet(rwRENDERSTATEVERTEXALPHAENABLE, lcl_84);
    RwRenderStateSet(rwRENDERSTATEZWRITEENABLE, var_80);
    RwRenderStateSet(rwRENDERSTATEZTESTENABLE, var_90);
    RwRenderStateSet(rwRENDERSTATEFOGENABLE, v74);
    RwRenderStateSet(rwRENDERSTATETEXTURERASTER, var_7C);
}

// match: ?sub_E5F60@type_DC400@@QAEXHM@Z @ 0x000E5F60
// sp-match: ?sub_E5F60@type_DC400@@QAEXHM@Z @ 0x000AA100
void type_DC400::sub_E5F60(RwInt32 arg_0, RwReal arg_4)
{
    RwV3d var_C;

    var_C.x = -1.0f * unk_E0[arg_0].unk_1E8.x * unk_E0[arg_0].unk_188.x * 0.5f;
    var_C.y = -1.0f * unk_E0[arg_0].unk_1E8.y * unk_E0[arg_0].unk_188.y * 0.5f;
    var_C.z = 0.0f;
    RwMatrixSetIdentity(&unk_E0[arg_0].unk_1A0);
    unk_E0[arg_0].unk_1E0 = arg_4;
    if (unk_E0[arg_0].unk_1E0 >= 360.0f)
    {
        unk_E0[arg_0].unk_1E0 -= 360.0f;
    }
    RwMatrixRotate(&unk_E0[arg_0].unk_1A0, &unk_3D805C, unk_E0[arg_0].unk_1E0, rwCOMBINEPOSTCONCAT);
    RwMatrixTranslate(&unk_E0[arg_0].unk_1A0, &var_C, rwCOMBINEPRECONCAT);
    sub_E70D0(&unk_E0[arg_0]);
}

// match: ?sub_E6200@type_DC400@@QAEXHMM@Z @ 0x000E6200
// sp-match: ?sub_E6200@type_DC400@@QAEXHMM@Z @ 0x000AA220
void type_DC400::sub_E6200(RwInt32 arg_0, RwReal arg_4, RwReal arg_8)
{
    RwV3d var_C;

    var_C.x = arg_4;
    var_C.y = arg_8;
    var_C.z = 0.0f;
    unk_E0[arg_0].unk_1F4 = var_C;
    sub_E70D0(&unk_E0[arg_0]);
}

// match: ?sub_E6270@type_DC400@@QAEXHMM@Z @ 0x000E6270
// sp-match: ?sub_E6270@type_DC400@@QAEXHMM@Z @ 0x000AA280
void type_DC400::sub_E6270(RwInt32 arg_0, RwReal arg_4, RwReal arg_8)
{
    RwV3d var_C;
    RwV3d var_18;

    var_C.x = arg_4;
    var_C.y = arg_8;
    var_C.z = 1.0f;
    var_18.x = -1.0f * unk_E0[arg_0].unk_1E8.x * unk_E0[arg_0].unk_188.x * 0.5f;
    var_18.y = -1.0f * unk_E0[arg_0].unk_1E8.y * unk_E0[arg_0].unk_188.y * 0.5f;
    var_18.z = 0.0f;
    RwMatrixSetIdentity(&unk_E0[arg_0].unk_1A0);
    RwMatrixTranslate(&unk_E0[arg_0].unk_1A0, &var_18, rwCOMBINEPRECONCAT);
    RwMatrixRotate(&unk_E0[arg_0].unk_1A0, &unk_3D805C, -unk_E0[arg_0].unk_1E0, rwCOMBINEPRECONCAT);
    RwMatrixScale(&unk_E0[arg_0].unk_1A0, &var_C, rwCOMBINEPRECONCAT);
    var_18.x = unk_E0[arg_0].unk_1E8.x * unk_E0[arg_0].unk_188.x * 0.5f;
    var_18.y = unk_E0[arg_0].unk_1E8.y * unk_E0[arg_0].unk_188.y * 0.5f;
    var_18.z = 0.0f;
    RwMatrixTranslate(&unk_E0[arg_0].unk_1A0, &var_18, rwCOMBINEPRECONCAT);
    sub_E70D0(&unk_E0[arg_0]);
}

// match: ?sub_E6570@type_DC400@@QAEXHH@Z @ 0x000E6570
// sp-match: ?sub_E6570@type_DC400@@QAEXHH@Z @ 0x000A8C20
void type_DC400::sub_E6570(RwInt32 arg_0, RwInt32 arg_4)
{
    unk_E0[arg_0].unk_204[unk_E0[arg_0].unk_2A4] = &unk_E0[arg_4];
    unk_E0[arg_0].unk_2A4++;
    unk_E0[arg_4].unk_200 = &unk_E0[arg_0];
}

// match: ?sub_E6610@type_DC400@@QAEXPAUtype_DC400_E0@@@Z @ 0x000E6610
// sp-match: ?sub_E6610@type_DC400@@QAEXPAUtype_DC400_E0@@@Z @ 0x000A8C80
// Lays out the item arg_0 (its children first) when it is marked (unk_2A8):
// its quad from its size (unk_188, in 512-wide units, less a 20-pixel bar),
// through each of its ancestors' matrices and offsets (some items and
// parents nudged by hand), squeezed for 4:3 and moved out by flt_4293C0 in
// widescreen, into its vertices.
void type_DC400::sub_E6610(type_DC400_E0 *arg_0)
{
    type_DC400_E0 *var_8;
    RwInt32 var_C;
    RwReal var_10;
    RwReal var_1C;
    RwReal var_44;
    RwV3d var_50;
    RwInt32 var_54;
    RwReal var_64;
    RwReal var_8C;
    RwInt32 var_90;
    type_10F710 *var_98;
    RwInt32 var_9C;
    RwV3d var_A8;
    RwMatrix var_F0;
    RwReal var_F4;
    RwInt32 var_F8;
    RwInt32 var_104;

    if (!arg_0 || !arg_0->unk_20)
    {
        return;
    }
    var_8 = arg_0;
    for (var_C = 0; var_C < type_DC400_children; var_C++)
    {
        if (arg_0->unk_204[var_C] && arg_0->unk_204[var_C]->unk_20)
        {
            sub_E6610(arg_0->unk_204[var_C]);
        }
    }
    if (arg_0->unk_2A8)
    {
        var_10 = 1.0f;
        if (dword_4CF9A8)
        {
            var_10 = 1.0f / 1.333f;
        }
#ifdef CODFH_SP // shape: the width over 512 first (SP 0xA8C80 keeps 1/512 and 0.5 apart)
        var_1C = ((RwReal)(RwUInt32)Width / 512.0f) * arg_0->unk_188.x * 0.5f;
#else
        var_1C = (RwReal)(RwUInt32)Width / 512.0f * arg_0->unk_188.x * 0.5f;
#endif
        var_44 = ((RwReal)(RwUInt32)Height - 20.0f) * arg_0->unk_188.y / (RwReal)(RwUInt32)Height
                 * ((RwReal)(RwUInt32)Width / (RwReal)(RwUInt32)Height) * 0.5f;
        arg_0->unk_E0[0].x = -var_1C;
        arg_0->unk_E0[0].y = var_44;
        arg_0->unk_E0[1].x = -var_1C;
        arg_0->unk_E0[1].y = -var_44;
        arg_0->unk_E0[2].x = var_1C;
        arg_0->unk_E0[2].y = var_44;
        arg_0->unk_E0[3].x = var_1C;
        arg_0->unk_E0[3].y = -var_44;
        do
        {
            sub_141590(arg_0->unk_E0, arg_0->unk_E0, 4, &var_8->unk_1A0);
            var_50 = var_8->unk_1F4;
            var_54 = arg_0 - unk_E0;
            switch (var_54)
            {
#ifdef CODFH_SP // shape: single player's vehicle bars and buddy health bar are items 63, 64 and 100 (SP 0xA8C80)
            case 63:
            case 64:
            case 100:
#else
            case 104:
            case 105:
            case 147:
#endif
                if (var_50.x > 0.0f)
                {
                    var_64 = (RwReal)(RwUInt32)Width * arg_0->unk_188.x / 512.0f - arg_0->unk_188.x;
                    var_50.x += (1.0f - arg_0->unk_1A0.right.x) * var_64 * 0.5f;
                }
                break;
            case 6:
                if (var_50.y > 0.0f)
                {
                    var_8C = ((RwReal)(RwUInt32)Height - 20.0f) / (RwReal)(RwUInt32)Height
                             * ((RwReal)(RwUInt32)Width / (RwReal)(RwUInt32)Height) * arg_0->unk_188.y
                             - arg_0->unk_188.y;
                    var_50.y += (1.0f - arg_0->unk_1A0.up.y) * var_8C * 0.5f;
                }
                break;
            }
#ifdef CODFH_SP // shape: the scale and the division stay two steps (SP 0xA8C80 multiplies by 512 and by 1/448)
            var_50.y *= 512.0f;
            var_50.y /= 448.0f;
#else
            var_50.y = var_50.y * 512.0f / 448.0f;
#endif
            if (var_8->unk_200)
            {
                var_90 = var_8->unk_200 - unk_E0;
                switch (var_90)
                {
                case 7:
                case 10:
                case 14:
                case 29:
#ifdef CODFH_SP // shape: single player's item 56 (MP 97; SP 0xA8C80)
                case 56:
#else
                case 97:
#endif
                    var_50.y -= 25.0f;
                    break;
                case 4:
                    var_50.y -= 18.5f;
                    break;
#ifdef CODFH_SP // shape: single player's buddy health is item 97 (SP 0xA8C80)
                case 97:
#else
                case 144:
#endif
                    var_50.y += 25.0f;
                    break;
                case 20:
                    var_50.y += 25.0f;
                    break;
#ifdef CODFH_SP // shape: single player's crosshair is item 49 (SP 0xA8C80)
                case 49:
#else
                case 90:
#endif
                    var_98 = (type_10F710 *)sub_1745A0(dword_429EB0);
                    if (var_98 && var_98->unk_4D0)
                    {
                        var_50.y += 25.0f;
                    }
                    break;
                }
            }
            for (var_9C = 0; var_9C < 4; var_9C++)
            {
                RwV3dAddMacro(&arg_0->unk_E0[var_9C], &arg_0->unk_E0[var_9C], &var_50);
            }
            var_8 = var_8->unk_200;
        } while (var_8);
        var_A8.x = var_10;
        var_A8.y = 1.0f;
        var_A8.z = 1.0f;
        RwMatrixSetIdentityMacro(&var_F0);
        RwMatrixScale(&var_F0, &var_A8, rwCOMBINEPOSTCONCAT);
        var_F4 = 0.0f;
        for (var_F8 = 0; var_F8 < 4; var_F8++)
        {
            arg_0->unk_E0[var_F8].x -= (RwReal)(RwUInt32)Width * 0.5f;
            var_F4 += arg_0->unk_E0[var_F8].x;
        }
        var_F4 *= 0.25f;
        sub_1413E0(arg_0->unk_E0, arg_0->unk_E0, 4, &var_F0);
        for (var_104 = 0; var_104 < 4; var_104++)
        {
            if (dword_4CF9A8)
            {
                if (var_F4 < -60.0f)
                {
                    arg_0->unk_E0[var_104].x -= flt_4293C0;
                }
                if (var_F4 > 60.0f)
                {
                    arg_0->unk_E0[var_104].x += flt_4293C0;
                }
            }
            arg_0->unk_E0[var_104].x += (RwReal)(RwUInt32)Width * 0.5f;
        }
        // The vertices take the corners through the FPU (fld/fstp), which a
        // float copy does not give; a round trip through RwDouble does.
        arg_0->unk_118[0].x = (RwReal)(RwDouble)arg_0->unk_E0[0].x;
        arg_0->unk_118[0].y = (RwReal)(RwDouble)arg_0->unk_E0[0].y;
        arg_0->unk_118[1].x = (RwReal)(RwDouble)arg_0->unk_E0[1].x;
        arg_0->unk_118[1].y = (RwReal)(RwDouble)arg_0->unk_E0[1].y;
        arg_0->unk_118[2].x = (RwReal)(RwDouble)arg_0->unk_E0[2].x;
        arg_0->unk_118[2].y = (RwReal)(RwDouble)arg_0->unk_E0[2].y;
        arg_0->unk_118[3].x = (RwReal)(RwDouble)arg_0->unk_E0[3].x;
        arg_0->unk_118[3].y = (RwReal)(RwDouble)arg_0->unk_E0[3].y;
        arg_0->unk_2A8 = 0;
    }
}

// match: ?sub_E6F90@type_DC400@@QAEXHPBD_N11111@Z @ 0x000E6F90
// sp-match: ?sub_E6F90@type_DC400@@QAEXHPBD_N11111@Z @ 0x000A9480
void type_DC400::sub_E6F90(RwInt32 arg_0, const RwChar *arg_4, bool arg_8, bool arg_C, bool arg_10, bool arg_14,
                           bool arg_18, bool arg_1C)
{
    strcpy(unk_E0[arg_0].unk_00, arg_4);
    unk_E0[arg_0].unk_54 = arg_8;
    unk_E0[arg_0].unk_5C = arg_C;
    unk_E0[arg_0].unk_58 = arg_10;
    unk_E0[arg_0].unk_44 = arg_14;
    unk_E0[arg_0].unk_48 = arg_18;
    unk_E0[arg_0].unk_4C = arg_1C;
}

// match: ?sub_E7050@type_DC400@@QAEXHMM@Z @ 0x000E7050
// sp-match: ?sub_E7050@type_DC400@@QAEXHMM@Z @ 0x000AA3E0
void type_DC400::sub_E7050(RwInt32 arg_0, RwReal arg_4, RwReal arg_8)
{
    RwReal var_4;

    var_4 = 1.0f;
    if (dword_4CF9A8)
    {
        var_4 = 1.3333f;
    }
    unk_E0[arg_0].unk_1F4.x = arg_4 * var_4;
    unk_E0[arg_0].unk_1F4.y = arg_8;
    sub_E70D0(&unk_E0[arg_0]);
}

// match: ?sub_E70D0@type_DC400@@QAEXPAUtype_DC400_E0@@@Z @ 0x000E70D0
// sp-match: ?sub_E70D0@type_DC400@@QAEXPAUtype_DC400_E0@@@Z @ 0x000A94F0
void type_DC400::sub_E70D0(type_DC400_E0 *arg_0)
{
    RwInt32 var_4;

    for (var_4 = 0; var_4 < type_DC400_children; var_4++)
    {
        if (arg_0->unk_204[var_4] && arg_0->unk_204[var_4]->unk_20)
        {
            sub_E70D0(arg_0->unk_204[var_4]);
        }
    }
    arg_0->unk_2A8 = 1;
}

// match: ?sub_E7140@type_DC400@@QAEXHM@Z @ 0x000E7140
// sp-match: ?sub_E7140@type_DC400@@QAEXHM@Z @ 0x000A9540
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void type_DC400::sub_E7140(RwInt32 arg_0, RwReal arg_4)
{
    RwInt32 var_14;
    RwReal lv_10;
    RwReal var_C;
    RwReal bp_8;
    RwReal bp_4;

    bp_8 = 1.0f / RwCameraGetNearClipPlane(unk_1A02C);
    unk_E0[arg_0].unk_1E4 = arg_4;
    lv_10 = RwIm2DGetFarScreenZ();
    bp_4 = RwIm2DGetNearScreenZ();
    var_C = (lv_10 - bp_4) * arg_4 + bp_4;
    for (var_14 = 0; var_14 < 4; var_14++)
    {
        RwIm2DVertexSetScreenZ(&unk_E0[arg_0].unk_118[var_14], var_C);
        RwIm2DVertexSetRecipCameraZ(&unk_E0[arg_0].unk_118[var_14], bp_8);
    }
}

// match: ?sub_E7200@type_DC400@@QAEXHHHHH@Z @ 0x000E7200
// sp-match: ?sub_E7200@type_DC400@@QAEXHHHHH@Z @ 0x000A95C0
void type_DC400::sub_E7200(RwInt32 arg_0, RwInt32 arg_4, RwInt32 arg_8, RwInt32 arg_C, RwInt32 arg_10)
{
    RwInt32 var_4;

    for (var_4 = 0; var_4 < 4; var_4++)
    {
        RwIm2DVertexSetIntRGBA(&unk_E0[arg_0].unk_118[var_4], arg_4, arg_8, arg_C, arg_10);
    }
}

// match: ?sub_E7270@type_DC400@@QAEXHPAURwRGBA@@000@Z @ 0x000E7270
// sp-match: ?sub_E7270@type_DC400@@QAEXHPAURwRGBA@@000@Z @ 0x000A9610
void type_DC400::sub_E7270(RwInt32 arg_0, RwRGBA *arg_4, RwRGBA *arg_8, RwRGBA *arg_C, RwRGBA *arg_10)
{
    RwIm2DVertexSetIntRGBA(&unk_E0[arg_0].unk_118[0], arg_4->red, arg_4->green, arg_4->blue, arg_4->alpha);
    RwIm2DVertexSetIntRGBA(&unk_E0[arg_0].unk_118[1], arg_8->red, arg_8->green, arg_8->blue, arg_8->alpha);
    RwIm2DVertexSetIntRGBA(&unk_E0[arg_0].unk_118[2], arg_C->red, arg_C->green, arg_C->blue, arg_C->alpha);
    RwIm2DVertexSetIntRGBA(&unk_E0[arg_0].unk_118[3], arg_10->red, arg_10->green, arg_10->blue,
                           arg_10->alpha);
}

// match: ?sub_E7380@type_DC400@@QAEXHPBD@Z @ 0x000E7380
// sp-match: ?sub_E7380@type_DC400@@QAEXHPBD@Z @ 0x000A96B0
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void type_DC400::sub_E7380(RwInt32 arg_0, const RwChar *arg_4)
{
    const RwChar *var_8;
    RwInt32 l4;

    if (arg_4 && arg_0 < type_DC400_items)
    {
        if (arg_0 == 2)
        {
            if (arg_4)
            {
                l4 = strlen(arg_4);
                var_8 = strstr(arg_4, ":");
                memset(unk_1A164, 0, sizeof(unk_1A164));
                if (var_8)
                {
                    l4 -= strlen(var_8);
                    strncpy(unk_1A164, arg_4, l4 <= 0x3F ? l4 : 0x3F);
                }
            }
            unk_1A15C = arg_4;
        }
        else
        {
            if (strlen(arg_4) < 0x80)
            {
                strcpy(unk_E0[arg_0].unk_60, arg_4);
            }
        }
    }
}

// match: ?sub_E7480@type_DC400@@QAEXHPAURwRGBAReal@@@Z @ 0x000E7480
// sp-match: ?sub_E7480@type_DC400@@QAEXHPAURwRGBAReal@@@Z @ 0x000A9790
void type_DC400::sub_E7480(RwInt32 arg_0, RwRGBAReal *arg_4)
{
    if (arg_4 && arg_0 < type_DC400_items)
    {
        unk_E0[arg_0].unk_34 = *arg_4;
    }
}

// match: ?sub_E74D0@type_DC400@@QAEXHPAURwV2d@@@Z @ 0x000E74D0
// sp-match: ?sub_E74D0@type_DC400@@QAEXHPAURwV2d@@@Z @ 0x000A97D0
void type_DC400::sub_E74D0(RwInt32 arg_0, RwV2d *arg_4)
{
    if (!arg_4)
    {
        return;
    }
    unk_E0[arg_0].unk_188.x = arg_4->x;
    unk_E0[arg_0].unk_188.y = arg_4->y;
    sub_E70D0(&unk_E0[arg_0]);
}

#ifndef CODFH_SP // MP only: no single-player twins, they set unk_2B0, unk_2BC and unk_2B4 (absent there)
// match: ?sub_E7540@type_DC400@@QAEXHH@Z @ 0x000E7540
void type_DC400::sub_E7540(RwInt32 arg_0, RwInt32 arg_4)
{
    unk_E0[arg_0].unk_2B0 = arg_4;
}

// match: ?sub_E7570@type_DC400@@QAEXHH@Z @ 0x000E7570
void type_DC400::sub_E7570(RwInt32 arg_0, RwInt32 arg_4)
{
    unk_E0[arg_0].unk_2BC = arg_4;
}

// match: ?sub_E75A0@type_DC400@@QAEXHH@Z @ 0x000E75A0
void type_DC400::sub_E75A0(RwInt32 arg_0, RwInt32 arg_4)
{
    unk_E0[arg_0].unk_2B4 = arg_4;
}
#endif

// match: ?sub_E75D0@type_DC400@@QAEXHURwRGBA@@@Z @ 0x000E75D0
void type_DC400::sub_E75D0(RwInt32 arg_0, RwRGBA arg_4)
{
    unk_E0[arg_0].unk_190 = arg_4;
}

#ifndef CODFH_SP // MP only: no single-player twin (SP 0xAA590 draws no item texts), it reads unk_2B0 (absent there)
// match: ?sub_E7600@type_DC400@@QAEXPAUtype_DC400_E0@@@Z @ 0x000E7600
// match: __ehhandler$?sub_E7600@type_DC400@@QAEXPAUtype_DC400_E0@@@Z-0x23 @ 0x00300EC0
// match: __ehhandler$?sub_E7600@type_DC400@@QAEXPAUtype_DC400_E0@@@Z @ 0x00300EE3
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void type_DC400::sub_E7600(type_DC400_E0 *arg_0)
{
    RwUInt32 var_14;
    RwInt32 lv_10;

    if (!arg_0 || !arg_0->unk_20 || !arg_0->unk_50)
    {
        return;
    }
    for (lv_10 = 0; lv_10 < type_DC400_children; lv_10++)
    {
        if (arg_0->unk_204[lv_10] && arg_0->unk_204[lv_10]->unk_20)
        {
            sub_E7600(arg_0->unk_204[lv_10]);
        }
    }
    if (arg_0->unk_2B0)
    {
#ifndef CODFH_SP // MP only: the text through the kujuUI fonts (unk_88, unk_8C)
        if (arg_0->unk_58 && arg_0->unk_60 && arg_0->unk_60[0])
        {
            type_E8780<type_1E5A60> var_18;

            var_18 = arg_0->unk_2BC ? unk_88 : unk_8C;
            if (!var_18.sub_E87C0())
            {
                RwInt32 l1C;
                RwInt32 lcl_70;
                type_1F5A50 *lv_74;
                void *var_78;

                var_14 = var_18->sub_1F2490(arg_0->unk_60, -1);
                type_1F5A50 var6C[4];

                var_18->sub_1E6690(arg_0->unk_60, -1, var_14, 0, var6C, &l1C);
                for (lcl_70 = 0; lcl_70 != 4; lcl_70++)
                {
                    lv_74 = &var6C[lcl_70];
                    if (!lv_74->test_unk_04())
                    {
                        RwRenderStateSet(rwRENDERSTATETEXTURERASTER, get_texture_raster(var_18->sub_1E5A60(lcl_70)));
                        switch (arg_0->unk_2B4)
                        {
                        case 0:
                            lv_74->sub_1F5CD0(arg_0->unk_1F4.x, arg_0->unk_1F4.y);
                            break;
                        case 1:
                            lv_74->sub_1F5CD0(arg_0->unk_1F4.x - (RwReal)(var_14 >> 1), arg_0->unk_1F4.y);
                            break;
                        case 2:
                            lv_74->sub_1F5CD0(arg_0->unk_1F4.x - (RwReal)var_14, arg_0->unk_1F4.y);
                            break;
                        }
                        RwRenderStateGet(rwRENDERSTATEZTESTENABLE, &var_78);
                        RwRenderStateSet(rwRENDERSTATEZTESTENABLE, (void *)FALSE);
                        lv_74->sub_1F5C00();
                        RwRenderStateSet(rwRENDERSTATEZTESTENABLE, &var_78);
                        RwRenderStateSet(rwRENDERSTATETEXTURERASTER, (void *)NULL);
                    }
                }
            }
        }
        else
#endif
        {
            if (arg_0->unk_54)
            {
                arg_0->unk_114 = arg_0->unk_110->raster;
                RwRenderStateSet(rwRENDERSTATETEXTURERASTER, arg_0->unk_114);
            }
            else
            {
                RwRenderStateSet(rwRENDERSTATETEXTURERASTER, (void *)NULL);
            }
            RwIm2DRenderPrimitive(rwPRIMTYPETRISTRIP, arg_0->unk_118, 4);
        }
    }
}
#endif

#ifndef CODFH_SP // MP only: no single-player twin, it reads unk_90/unk_60 (absent there)
// match: ?sub_E79C0@type_DC400@@QAEXXZ @ 0x000E79C0
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void type_DC400::sub_E79C0()
{
    RwReal var_10;
    RwReal var_C;
    RwReal bp_8;
    RwReal bp_4;

    if (unk_90 == 1 || unk_90 == 2)
    {
        var_10 = 0.0f;
        var_C = 0.0f;
        bp_8 = (RwReal)(RwUInt32)Width;
        bp_4 = unk_E0[0x56].unk_1F4.y;
        sub_E7AB0(var_10, var_C, bp_8, bp_4, unk_E0[0x56].unk_190);
        var_10 = 0.0f;
        var_C = (RwReal)(RwUInt32)Height - unk_E0[0x57].unk_1F4.y;
        bp_8 = (RwReal)(RwUInt32)Width;
        bp_4 = (RwReal)(RwUInt32)Height;
        sub_E7AB0(var_10, var_C, bp_8, bp_4, unk_E0[0x57].unk_190);
    }
}
#endif

// match: ?sub_E7AB0@type_DC400@@QAEXMMMMURwRGBA@@@Z @ 0x000E7AB0
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void type_DC400::sub_E7AB0(RwReal arg_0, RwReal arg_4, RwReal arg_8, RwReal arg_C, RwRGBA arg_10)
{
    RwInt32 var_94;
    void *var_90;
    void *l8C;
    void *var_88;
    void *lcl_84;
    void *var_80;
    void *var_7C;
    void *m_78;
    void *v74;
    RwIm2DVertex l70[4];

    RwRenderStateGet(rwRENDERSTATESRCBLEND, &m_78);
    RwRenderStateGet(rwRENDERSTATEDESTBLEND, &l8C);
    RwRenderStateGet(rwRENDERSTATEVERTEXALPHAENABLE, &lcl_84);
    RwRenderStateGet(rwRENDERSTATEZWRITEENABLE, &var_80);
    RwRenderStateGet(rwRENDERSTATEZTESTENABLE, &var_90);
    RwRenderStateGet(rwRENDERSTATEFOGENABLE, &v74);
    RwRenderStateGet(rwRENDERSTATETEXTURERASTER, &var_7C);
    RwRenderStateGet(rwRENDERSTATESHADEMODE, &var_88);
    RwRenderStateSet(rwRENDERSTATESRCBLEND, (void *)rwBLENDSRCALPHA);
    RwRenderStateSet(rwRENDERSTATEDESTBLEND, (void *)rwBLENDINVSRCALPHA);
    RwRenderStateSet(rwRENDERSTATEVERTEXALPHAENABLE, (void *)TRUE);
    RwRenderStateSet(rwRENDERSTATEZWRITEENABLE, (void *)FALSE);
    RwRenderStateSet(rwRENDERSTATEZTESTENABLE, (void *)FALSE);
    RwRenderStateSet(rwRENDERSTATEFOGENABLE, (void *)FALSE);
    RwRenderStateSet(rwRENDERSTATETEXTURERASTER, (void *)NULL);
    RwRenderStateSet(rwRENDERSTATESHADEMODE, (void *)rwSHADEMODEGOURAUD);
    RwIm2DVertexSetScreenX(&l70[0], arg_0);
    RwIm2DVertexSetScreenY(&l70[0], arg_4);
    RwIm2DVertexSetScreenX(&l70[1], arg_0);
    RwIm2DVertexSetScreenY(&l70[1], arg_C);
    RwIm2DVertexSetScreenX(&l70[2], arg_8);
    RwIm2DVertexSetScreenY(&l70[2], arg_C);
    RwIm2DVertexSetScreenX(&l70[3], arg_8);
    RwIm2DVertexSetScreenY(&l70[3], arg_4);
    for (var_94 = 0; var_94 < 4; var_94++)
    {
        RwIm2DVertexSetScreenZ(&l70[var_94], RwIm2DGetNearScreenZ());
        RwIm2DVertexSetRecipCameraZ(&l70[var_94], 1.0f / RwCameraGetNearClipPlane(unk_1A02C));
        RwIm2DVertexSetIntRGBA(&l70[var_94], arg_10.red, arg_10.green, arg_10.blue, arg_10.alpha);
    }
    RwIm2DRenderPrimitive(rwPRIMTYPETRIFAN, l70, 4);
    RwRenderStateSet(rwRENDERSTATESRCBLEND, m_78);
    RwRenderStateSet(rwRENDERSTATEDESTBLEND, l8C);
    RwRenderStateSet(rwRENDERSTATEVERTEXALPHAENABLE, lcl_84);
    RwRenderStateSet(rwRENDERSTATEZWRITEENABLE, var_80);
    RwRenderStateSet(rwRENDERSTATEZTESTENABLE, var_90);
    RwRenderStateSet(rwRENDERSTATEFOGENABLE, v74);
    RwRenderStateSet(rwRENDERSTATETEXTURERASTER, var_7C);
    RwRenderStateSet(rwRENDERSTATESHADEMODE, var_88);
}

#ifndef CODFH_SP // MP only: no single-player twin, it reads unk_90/unk_60 (absent there)
// match: ?sub_E7D00@type_DC400@@QAEXXZ @ 0x000E7D00
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void type_DC400::sub_E7D00()
{
    std::string *var_1C;
    std::string *var_18;
    RwV3d var_14;
    RwRGBA var8;
    type_DC400_E0 *l4;

    l4 = &unk_E0[0x52];
    if (l4->unk_50)
    {
        var_14 = l4->unk_1F4;
        var8.red = var8.green = var8.blue = var8.alpha = 0xFF;
        sub_E8220("A:", var_14, var8);
        var_14.y -= unk_1A028->sub_DA790() * (RwReal)(RwUInt32)Height;
        sub_E8220("B:", var_14, var8);
        var_14 = unk_E0[0x53].unk_1F4;
        var_18 = &unk_4B89B0[dword_4F6950.sub_1A3D50(0)];
        sub_E8220(var_18->c_str(), var_14, unk_60[dword_4F6950.sub_1A3D50(0)]);
        var_14.y -= unk_1A028->sub_DA790() * (RwReal)(RwUInt32)Height;
        var_1C = &unk_4B89B0[dword_4F6950.sub_1A3D50(1)];
        sub_E8220(var_1C->c_str(), var_14, unk_60[dword_4F6950.sub_1A3D50(1)]);
    }
}
#endif

// Not in the image: a stand-in for a function the original object held here, which
// the link dropped (/OPT:REF) but whose literals stayed first: "%s%s", the game
// modes' names, "No"/"Yes" and "1 minute"/"No limit" sit between sub_E7D00's and
// sub_E7EF0's literals (0x3D8C40-0x3D8C98), before their users in later objects
// (unit_0E8800, unit_1A3BE0, unit_214A90, unit_200B90). A function's literals come
// out last-referenced first. Unreferenced.
void dropped_3D8C40(RwChar *arg_0, RwInt32 arg_4, RwInt32 arg_8, RwInt32 arg_C)
{
    const RwChar *lv_4;
    const RwChar *lv_8;
    const RwChar *lv_C;

    lv_4 = arg_C ? "No limit" : "1 minute";
    lv_8 = arg_8 ? "Yes" : "No";
    lv_C = arg_4 == 2 ? "Deathmatch" : arg_4 == 1 ? "Team Deathmatch" : "Capture The Flag";
    sprintf(arg_0, "%s%s", lv_C, lv_8);
    sprintf(arg_0, "%s%s", arg_0, lv_4);
}

#ifndef CODFH_SP // MP only: no twin in config/sp/shared.txt; its only callers are the HUD's multiplayer parts (already MP only)
// match: ?sub_E7EF0@type_DC400@@QAEXXZ @ 0x000E7EF0
// match: __ehhandler$?sub_E7EF0@type_DC400@@QAEXXZ-0x8 @ 0x00300EF0
// match: __ehhandler$?sub_E7EF0@type_DC400@@QAEXXZ @ 0x00300EF8
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void type_DC400::sub_E7EF0()
{
    RwUInt32 var_18;
    RwUInt32 var_14;
    type_DC400_E0 *lv_10;

    lv_10 = &unk_E0[0x54];
    if (lv_10->unk_50)
    {
        RwRGBA ebp_2C;
        RwChar vB4[0x80];
        RwV3d vC0;
        const RwChar *lC4;

        vC0 = lv_10->unk_1F4;
        ebp_2C.red = ebp_2C.green = ebp_2C.blue = ebp_2C.alpha = 0xFF;
        var_14 = 0;
        std::vector<RwUInt32> var_28;

        unk_4F7EB8.unk_04.sub_1B3480(var_28);
        for (var_18 = 0; var_18 < var_28.size(); var_18++)
        {
            if (var_14 < unk_4F7EB8.sub_1ACA70())
            {
                if (unk_4F7EB8.sub_1AECA0(var_28[var_18], 0))
                {
                    lC4 = type_4F8054::get()->get_unk_B0()->unk_90[var_28[var_18]].unk_00;
                    sprintf(vB4, "%s %d: %s", unk_4B8AB0[var_14].c_str(), unk_4F7EB8.unk_D0.sub_1B3380(var_28[var_18]),
                            lC4);
                    sub_E8220(vB4, vC0, ebp_2C);
                    vC0.y -= unk_1A028->sub_DA790() * (RwReal)(RwUInt32)Height;
                    var_14++;
                }
            }
        }
    }
}
#endif

// match: ?sub_E8220@type_DC400@@QAEXPBDURwV3d@@URwRGBA@@@Z @ 0x000E8220
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void type_DC400::sub_E8220(const RwChar *arg_0, RwV3d arg_4, RwRGBA arg_10)
{
    RwReal var_10;
    RwReal var_C;
    RwV2d bp_8;

    var_10 = 1.0f;
    var_C = 1.0f;
    if (dword_4CF9A8)
    {
        var_10 = 1.3333f;
        var_C = 1.0f / var_10;
    }
    Rt2dCTMPush();
    Rt2dCTMSetIdentity();
    Rt2dCTMScale(var_C, 1.0f);
    bp_8.x = arg_4.x / (RwReal)(RwUInt32)Height;
    bp_8.y = arg_4.y / (RwReal)(RwUInt32)Height;
    if (dword_4CF9A8)
    {
        bp_8.x = (var_10 + flt_4293C4) * bp_8.x;
    }
    unk_1A028->sub_DAB00(arg_0, &bp_8, &arg_10, 0.0f, 0);
    Rt2dCTMPop();
}

// match: ?sub_E82F0@type_DC400@@QAEXPAURwCamera@@@Z @ 0x000E82F0
void type_DC400::sub_E82F0(RwCamera *arg_0)
{
    RwRGBA var_4;

    var_4.alpha = var_4.red = var_4.green = var_4.blue = 0xFF;
}

// Reads the texture dictionary arg_0 (a level path, sub_D7F20); 0 when it
// will not open or holds none.
// match: ?sub_E8320@@YAPAURwTexDictionary@@PBD@Z @ 0x000E8320
// sp-match: ?sub_E8320@@YAPAURwTexDictionary@@PBD@Z @ 0x000A9810
RwTexDictionary *sub_E8320(const RwChar *arg_0)
{
    RwChar var_210[0x200];
    RwTexDictionary *var8;
    RwStream *l4;

    l4 = 0;
    var8 = 0;
    sub_D7F20(var_210, arg_0);
#ifndef CODFH_SP // MP only: single player compiles out the debug print (SP 0xA9810)
    sub_19A750("Loading HUD Texture Dictionary file from: %s...", var_210);
#endif
    l4 = RwStreamOpen(rwSTREAMFILENAME, rwSTREAMREAD, var_210);
    if (l4)
    {
        if (RwStreamFindChunk(l4, rwID_TEXDICTIONARY, 0, 0))
        {
            var8 = RwTexDictionaryStreamRead(l4, 0);
        }
        RwStreamClose(l4, 0);
    }
    return var8;
}

// match: ?sub_E83D0@@YAXPAURwTexDictionary@@@Z @ 0x000E83D0
// sp-match: ?sub_E83D0@@YAXPAURwTexDictionary@@@Z @ 0x000A9890
void sub_E83D0(RwTexDictionary *arg_0)
{
    if (arg_0)
    {
        RwTexDictionaryDestroy(arg_0);
    }
}

// match: ?sub_E83F0@type_DC400@@QAEXXZ @ 0x000E83F0
// sp-match: ?sub_E83F0@type_DC400@@QAEXXZ @ 0x000A98B0
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void type_DC400::sub_E83F0()
{
    type_DC400_E0 *var_C;
    RwInt32 *bp_8;
    RwInt32 bp_4;

    for (bp_4 = 0; bp_4 < 1; bp_4++)
    {
        bp_8 = dword_4293D0[bp_4];
        while (*bp_8 != -1)
        {
            var_C = &unk_E0[*bp_8];
            var_C->unk_2AC |= 1 << bp_4;
            bp_8++;
        }
    }
}

// match: ?sub_E8470@type_DC400@@QAEXXZ @ 0x000E8470
// sp-match: ?sub_E8470@type_DC400@@QAEXXZ @ 0x000AA430
void type_DC400::sub_E8470()
{
#ifdef CODFH_SP // shape: single player's buddy items are 0x61, 0x63 and 0x64 (SP 0xAA430)
    sub_E09E0(0x61, 0);
    sub_E7140(0x61, 0.0f);
    sub_E7140(0x63, 0.01f);
    sub_E7140(0x64, 0.01f);
    sub_E3B90(0x61, flt_4B8F14);
#else
    sub_E09E0(0x90, 0);
    sub_E7140(0x90, 0.0f);
    sub_E7140(0x92, 0.01f);
    sub_E7140(0x93, 0.01f);
    sub_E3B90(0x90, flt_4B8F14);
#endif
    unk_1A1A4 = 1;
}

// match: ?sub_E84E0@type_DC400@@QAEPAUtype_DC530@@PAUtype_3DAFC8@@@Z @ 0x000E84E0
// sp-match: ?sub_E84E0@type_DC400@@QAEPAUtype_DC530@@PAUtype_3DAFC8@@@Z @ 0x000A98F0
type_DC530 *type_DC400::sub_E84E0(type_3DAFC8 *arg_0)
{
    RwInt32 var_4;

    for (var_4 = 0; var_4 < type_DC400_labels; var_4++)
    {
        if (unk_1A1A8[var_4].unk_28.sub_D4910() == arg_0 && unk_1A1A8[var_4].unk_24)
        {
            unk_1A1A8[var_4].unk_20 = 0;
            return &unk_1A1A8[var_4];
        }
    }
    for (var_4 = 0; var_4 < type_DC400_labels; var_4++)
    {
        if (!unk_1A1A8[var_4].unk_24)
        {
            unk_1A1A8[var_4].unk_24 = 1;
            unk_1A1A8[var_4].unk_28.sub_D48D0(arg_0);
            unk_1A1A8[var_4].unk_20 = 0;
            strcpy(unk_1A1A8[var_4].unk_00, arg_0->unk_62C);
            return &unk_1A1A8[var_4];
        }
    }
    return 0;
}

// The Dinkumware std::vector<RwInt32> functions the scoreboard (sub_E7EF0)
// instantiates (the XDK's headers, compiled here at /Od): _Buy, and _Xlen,
// which throws std::length_error.
// match: ?_Buy@?$vector@HV?$allocator@H@std@@@std@@IAE_NI@Z @ 0x000E8610
// match: ?_Xlen@?$vector@HV?$allocator@H@std@@@std@@IBEXXZ @ 0x000E86B0
// match: __ehhandler$?_Xlen@?$vector@HV?$allocator@H@std@@@std@@IBEXXZ-0x8 @ 0x00300F10
// match: __ehhandler$?_Xlen@?$vector@HV?$allocator@H@std@@@std@@IBEXXZ @ 0x00300F18

// kujuUI's pointer's constructors and null test (type_DC400.h), which the
// HUD instantiates first.
// match: ??0?$type_E8780@Utype_1E5A60@@@@QAE@PAUtype_1E5A60@@@Z @ 0x000E8780
// match: ??0?$type_E8780@Utype_1E5A60@@@@QAE@ABU0@@Z @ 0x000E8740
// match: ?sub_E87C0@?$type_E8780@Utype_1E5A60@@@@QBE_NXZ @ 0x000E87C0


// Functions /OPT:ICF folded into another body (config/aliases.txt), defined here for the
// authentic link (PLAN M7) with that body; the placement link takes the folded one.

// ??0type_4B89B0@@QAE@XZ (folded into 0xE87E0)
type_4B89B0::type_4B89B0()
{
}
