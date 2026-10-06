// The multiplayer manager, cNetController (game/gameloop.h, type_4F7EB8):
// its state, its message handlers (the table at 0x42C848 lists them) and
// its scores.

#include <stdarg.h>
#include <stdio.h>
#include "game/liveservice.h"
#include "types/type_1CCA10.h"
#include <xtl.h>
#include "types/cNetLevelParams.h"

#include "game/gameloop.h"
#include "game/netmsg.h"
#include "game/netplayer.h"
#include "game/voice.h"
#include "game/data.h"
#include "game/mpgame.h"
#include "game/savestate.h"
#include "game/fade.h"
#include "types/soundbank.h"
#include "rw/bamatrix.h"
#include "game/loc.h"
#include "game/bombsites.h"
#include "game/flags.h"
#include "game/netsoldier.h"
#include "types/type_4AE70.h"
#include "types/type_4B85F8.h"
#include "game/worldmgr.h"
#include "types/SectionInfo.h"
#include "types/StartingSections.h"
#include "game/startup.h"
#include "types/type_DC400.h"
#include "types/cXboxLiveNetGame.h"
#include "game/uiglue.h"
#include "game/livemenu.h"
#include "game/frontend.h"
#include "game/kujuui.h"
#include "types/type_F5740.h"
#include "types/type_495F0.h"
#include "types/type_4C19C0.h"
#include "game/ingamemenu.h"
#include "game/hostoptions.h"
#include "types/cNetPlayerTrigger.h"
#include "rw/bavector.h"
#include "game/parsedfile.h"

// Its data definitions (PLAN M5), in the image's address order.
// 0x003E138C
extern const RwReal flt_3E138C = 16.666666f;
// 0x003E1390
extern const RwReal flt_3E1390 = 0.01f;
// 0x003E1394
extern const RwReal flt_3E1394 = 0.01f;
// 0x003E1398
extern const RwReal flt_3E1398 = 0.01f;
// 0x003E139C
extern const RwReal flt_3E139C = 0.01f;
// 0x003E13A0
extern const RwReal flt_3E13A0 = 16.666666f;
// 0x003E13A4
extern const RwReal flt_3E13A4 = 0.01f;
// 0x003E13A8
extern const RwReal flt_3E13A8 = 0.01f;
// 0x003E13AC
extern const RwReal flt_3E13AC = 16.666666f;
// 0x003E13B0
extern const RwReal flt_3E13B0 = 4000000.0f;
// 0x004F62F8
#ifndef CODFH_PLAIN
RwUInt16 word_4F62F8;
#endif
// 0x004F6300
#ifndef CODFH_PLAIN
RwInt32 dword_4F6300;
#endif
// 0x004F7E98
#ifndef CODFH_PLAIN
RwCamera *dword_4F7E98;
#endif
// 0x004F8054
#ifndef CODFH_PLAIN
type_4F8054 *dword_4F8054;
#endif
// 0x004F8058
#ifndef CODFH_PLAIN
type_4F8058 *dword_4F8058;
#endif
// 0x004F805C
#ifndef CODFH_PLAIN
type_4F805C *dword_4F805C;
#endif
// 0x004F8060
#ifndef CODFH_PLAIN
type_1BABA0 *dword_4F8060;
#endif
// 0x004F80E8
#ifndef CODFH_PLAIN
RwInt32 dword_4F80E8;
#endif
// 0x004F8138
#ifndef CODFH_PLAIN
cNetLevelParams *dword_4F8138;
#endif
// 0x004F8184
#ifndef CODFH_PLAIN
type_4F8184 unk_4F8184;
#endif
// 0x004F83D8
#ifndef CODFH_PLAIN
RwInt32 dword_4F83D8;
#endif
// 0x004F8478
RwUInt8 byte_4F8478;
// 0x004FBA18
#ifndef CODFH_PLAIN
RwInt32 dword_4FBA18;
#endif
// 0x004FBAA4
#ifndef CODFH_PLAIN
RwInt32 dword_4FBAA4;
#endif
// End of its data definitions.


// Globals with constructors defined here (their initializers and exit
// functions at the end of .text).
type_1DDE20_mask unk_4F7E90;
type_1CB670 unk_4F7E9C;
type_4F7EB8 unk_4F7EB8;
// Vtables (.rdata, PLAN M5): each in its own placement range (config/splits.txt).
// Its data (PLAN M5): literals, constants and tables where the image has them.
// match: ?flt_3E138C@@3MB @ 0x003E138C
// match: ?flt_3E1390@@3MB @ 0x003E1390
// match: ?flt_3E1394@@3MB @ 0x003E1394
// match: ?flt_3E1398@@3MB @ 0x003E1398
// match: ?flt_3E139C@@3MB @ 0x003E139C
// match: ?flt_3E13A0@@3MB @ 0x003E13A0
// match: ?flt_3E13A4@@3MB @ 0x003E13A4
// match: ?flt_3E13A8@@3MB @ 0x003E13A8
// match: ?flt_3E13AC@@3MB @ 0x003E13AC
// match: ?flt_3E13B0@@3MB @ 0x003E13B0
// match: ??_C@_0BI@HIBBPDCN@GAME?5EVENT?3?5No?5Time?3?5?$CFs?$AA@ @ 0x003E13B4
// match: ??_C@_0BJ@NPCGCHMP@GAME?5EVENT?3?5Time?$CI?$CFd?$CJ?3?5?$CFs?$AA@ @ 0x003E13CC
// match: ??_7type_4F7EB8@@6B@ @ 0x003E13E8
// match: ??_7type_4F8054_A8@@6B@ @ 0x003E13F4
// match: ??_C@_0CO@OHDBNMLM@?$CIHOST?$CJ?5Broadcast?5level?5load?5star@ @ 0x003E1400
// match: ??_C@_0BC@JFOLIEM@WAITING_JOIN_DONE?$AA@ @ 0x003E1430
// match: ??_C@_0BJ@FPCPAKEI@WAITING_PEER_CONNECTIONS?$AA@ @ 0x003E1444
// match: ??_C@_0BF@HHBPECCF@WAITING_PEER_DETAILS?$AA@ @ 0x003E1460
// match: ??_C@_0BE@NBJNEEOD@WAITING_DETAILS_ACK?$AA@ @ 0x003E1478
// match: ??_C@_0BD@PJGCHMNK@WAITING_JOIN_BEGIN?$AA@ @ 0x003E148C
// match: ??_C@_0DN@DNFHGIFP@name?5?3?5?$CFs?0?5ip?5?3?5?$CFd?4?$CFd?4?$CFd?4?$CFd?5?9?5po@ @ 0x003E14A0
// match: ??_C@_0FJ@KGJKNNBC@?5is?5not?5NULL?4?5?5If?5you?5get?5a?5lot?5@ @ 0x003E14E0
// match: ??_C@_0FJ@MDAGMCMG@cNetController?3?3updateVoiceSubSy@ @ 0x003E1540
// match: ??_C@_0BI@KMINLOAI@Removing?5Killcam?5Stuff?6?$AA@ @ 0x003E159C
// match: ??_C@_0CE@LMNBPLOD@Going?5into?5Static?5Spectate?5from?5@ @ 0x003E15B4
// match: ??_C@_0BN@LNOGPPLD@Remove?5LOCAL?5KILLCAM?5PLAYER?6?$AA@ @ 0x003E15D8
// match: ??_C@_0BI@BJMAKGDG@Bind?5from?5KILL?5CAM?3?5?$CFd?6?$AA@ @ 0x003E15F8
// match: ??_C@_0CF@FIODIOHP@Deleting?5Remote?5KILL?5CAM?5player?3@ @ 0x003E1610
// match: ??_C@_0BI@LPIMBDMO@Local?5player?5respawned?6?$AA@ @ 0x003E1638
// match: ??_C@_0DI@CJBLNAMA@?$CICLIENT?$CJ?5Requested?5spawn?5point?5f@ @ 0x003E1650
// match: ??_C@_0BH@CPHDIBH@Player?5Joined?3?5?$CD?$CFd?0?5?$CFs?$AA@ @ 0x003E1688
// match: ??_C@_0N@IGHIAKON@MW_GEN_LEAVE?$AA@ @ 0x003E16A0
// match: ??_C@_0BI@HJOEFNNH@Player?5Removed?3?5?$CD?$CFd?0?5?$CFs?$AA@ @ 0x003E16B0
// match: ??_C@_0CF@IHCBDFFM@Bullet?5hit?5local?5player?5?9?5Firer?3@ @ 0x003E16C8
// match: ??_C@_0BE@KIDPNBAE@MW_GEN_KILLS_YOUGUN?$AA@ @ 0x003E16F0
// match: ??_C@_0BJ@IDLNLIIL@MW_GEN_KILLS_YOUYOURSELF?$AA@ @ 0x003E1704
// match: ??_C@_0CO@DBPPAAP@Local?5player?5killed?5by?5bullet?5fr@ @ 0x003E1720
// match: ??_C@_0CG@FPNFFIAN@Bullet?5hit?5remote?5player?5?9?5Firer@ @ 0x003E1750
// match: ??_C@_0BK@IBBDFMED@Player?5Participating?3?5?$CD?$CFd?$AA@ @ 0x003E1778
// match: ??_C@_0BH@NFHODGNK@Player?5Spectating?3?5?$CD?$CFd?$AA@ @ 0x003E1794
// match: ??_C@_0CI@OJKOOMCJ@Grenade?5hit?5remote?5player?5?9?5Vict@ @ 0x003E17AC
// match: ??_C@_0CK@CBLIKALF@?$CISERVER?$CJ?5Player?5?$CFd?5given?5spawn?5p@ @ 0x003E17D4
// match: ??_C@_0DL@BILPEGAE@?$CISERVER?$CJ?5Player?5?$CFd?5requested?5spa@ @ 0x003E1800
// match: ??_C@_0CL@CNIPMDNL@?$CICLIENT?$CJ?5Valid?5respawn?5point?5rec@ @ 0x003E183C
// match: ??_C@_0P@DNFIOGPF@MW_GEN_SUICIDE?$AA@ @ 0x003E1868
// match: ??_C@_0BB@PLHOKACM@MW_GEN_KILLS_GUN?$AA@ @ 0x003E1878
// match: ??_C@_0CP@DCLFOGHM@Player?5?$CFd?5died?5from?5bullet?5fired@ @ 0x003E188C
// match: ??_C@_0BC@MNFLKHJA@MW_GEN_KILLS_GREN?$AA@ @ 0x003E18BC
// match: ??_C@_0BK@EILAHBND@MW_GEN_KILLS_THEMACCIDENT?$AA@ @ 0x003E18D0
// match: ??_C@_0DB@EBINKMDL@Player?5?$CFd?5killed?5by?5grenade?5thro@ @ 0x003E18EC
// match: ??_C@_0DG@HICJFHL@Player?5?$CFd?5unable?5to?5be?5respawned@ @ 0x003E1920
// match: ??_C@_0BF@OIOOCFHI@Player?5?$CFd?5respawned?6?$AA@ @ 0x003E1958
// match: ??_C@_0BO@JJNMKJHJ@?$CICLIENT?$CJ?5Round?5score?5updated?6?$AA@ @ 0x003E1970
// match: ??_C@_0BN@BLEOMGIF@?$CICLIENT?$CJ?5Game?5score?5updated?6?$AA@ @ 0x003E1990
// match: ??_C@_0BD@MEHIKGLL@Received?5net?5chat?6?$AA@ @ 0x003E19B0
// match: ??_C@_0BP@KHHCKKDC@Received?5receive?5Voice?5Status?6?$AA@ @ 0x003E19C4
// match: ??_C@_0BC@OPOPBMNG@Send?5swap?5pickup?6?$AA@ @ 0x003E19E4
// match: ??_C@_0BG@CJOFEPMD@Received?5swap?5pickup?6?$AA@ @ 0x003E19F8
// match: ??_C@_0BL@DEFCHCLF@Player?5?$CFd?5threw?5a?5grenade?6?$AA@ @ 0x003E1A10
// match: ??_C@_0BE@EBPDEBFB@RESPAWN_AS?$CF1_WITH?$CF2?$AA@ @ 0x003E1A2C
// match: ??_C@_0P@DAIHEFII@RESPAWN_WITH?$CF1?$AA@ @ 0x003E1A40
// match: ??_C@_04LBNBCLPC@Axis?$AA@ @ 0x003E1A50
// match: ??_C@_06KPDLJAFG@Allies?$AA@ @ 0x003E1A58
// match: __ehhandler$??0type_4F7EB8@@QAE@XZ>1>8 @ 0x0041EB5C
// match: __ehhandler$??0type_4F7EB8@@QAE@XZ>1 @ 0x0041EB74
// match: __ehhandler$??1type_4F7EB8@@QAE@XZ>1>8 @ 0x0041EB90
// match: __ehhandler$??1type_4F7EB8@@QAE@XZ>1 @ 0x0041EBA0
// match: __ehhandler$??1type_4F8348@@QAE@XZ>1>8 @ 0x0041EBBC
// match: __ehhandler$??1type_4F8348@@QAE@XZ>1 @ 0x0041EBC4
// match: __ehhandler$?sub_1A9580@type_4F7EB8@@QAEXXZ>1>8 @ 0x0041EBE0
// match: __ehhandler$?sub_1A9580@type_4F7EB8@@QAEXXZ>1 @ 0x0041EC00
// match: __ehhandler$?sub_1A9A70@type_4F7EB8@@QAEXHHPBD_N@Z>1>8 @ 0x0041EC1C
// match: __ehhandler$?sub_1A9A70@type_4F7EB8@@QAEXHHPBD_N@Z>1 @ 0x0041EC24
// match: __ehhandler$?sub_1A9CE0@type_4F7EB8@@QAE_NPBUtype_1CC1F0@@PBUtype_1CC3C0@@PAH_N@Z>1>8 @ 0x0041EC40
// match: __ehhandler$?sub_1A9CE0@type_4F7EB8@@QAE_NPBUtype_1CC1F0@@PBUtype_1CC3C0@@PAH_N@Z>1 @ 0x0041EC70
// match: __ehhandler$?vf_004@type_4F7EB8@@UAEXH@Z>1>8 @ 0x0041EC8C
// match: __ehhandler$?vf_004@type_4F7EB8@@UAEXH@Z>1 @ 0x0041EC94
// match: __ehhandler$?sub_1ACBA0@@YAXHPAUtype_3DA434@@@Z>1>8 @ 0x0041ECB0
// match: __ehhandler$?sub_1ACBA0@@YAXHPAUtype_3DA434@@@Z>1 @ 0x0041ECB8
// match: __ehhandler$?sub_1AD0F0@@YAXHHPAUtype_3DA44C@@@Z>1>8 @ 0x0041ECD4
// match: __ehhandler$?sub_1AD0F0@@YAXHHPAUtype_3DA44C@@@Z>1 @ 0x0041ECDC
// match: __ehhandler$?sub_1AD750@@YAXHHPAUtype_3DA44C@@@Z>1>8 @ 0x0041ECF8
// match: __ehhandler$?sub_1AD750@@YAXHHPAUtype_3DA44C@@@Z>1 @ 0x0041ED08
// match: __ehhandler$?sub_1ADD90@@YAXHHPAUtype_3DA44C@@@Z>1>8 @ 0x0041ED24
// match: __ehhandler$?sub_1ADD90@@YAXHHPAUtype_3DA44C@@@Z>1 @ 0x0041ED44
// match: __ehhandler$?sub_1AE8F0@@YAXHHPAUtype_3DA44C@@@Z>1>8 @ 0x0041ED60
// match: __ehhandler$?sub_1AE8F0@@YAXHHPAUtype_3DA44C@@@Z>1 @ 0x0041ED68
// match: __ehhandler$?sub_1AFBB0@type_4F7EB8@@QAEXXZ>1>8 @ 0x0041ED84
// match: __ehhandler$?sub_1AFBB0@type_4F7EB8@@QAEXXZ>1 @ 0x0041EDBC
// match: .CRT$XCU+0 @ 0x004271D4
// match: .CRT$XCU+4 @ 0x004271D8
// match: .CRT$XCU+8 @ 0x004271DC
// match: _$E2 @ 0x0030C1D0
// match: _$E4 @ 0x0030C1E0
// match: _$E5 @ 0x0030EA60
// match: _$E7 @ 0x0030C200
// match: _$E8 @ 0x0030EA70
// match: _$E12 @ 0x0030EA90
// match: _$E13 @ 0x0030EA80


// Localized Axis/Allies strings in sub_1AFBB0: their generated exits call
// the null-safe string destructor, folded into std::string's sub_43900.

// The HUD's message line: arg_0 received from peer arg_4 (sub_1C4E80), and
// a refresh (sub_1C4C30).
void sub_1C4E80(type_1A5EA0 arg_0, RwInt32 arg_4);
void sub_1C4C30(bool arg_0);
extern RwUInt32 dword_4F6AB8[];
#ifdef CODFH_PLAIN
// (plain builds: a field of the multiplayer manager unk_4F7EB8; see unit_1A8B20)
extern RwInt32 &dword_4F83D8;
#else
extern RwInt32 dword_4F83D8;
#endif
// What the multiplayer manager's reset calls (sub_1AF6F0); only the width
// is known.
void sub_1C4690();
// Picks a spawn point from arg_0 for player arg_4 (sub_1AD380); only the
// widths are known.
RwInt32 sub_1AD380(RwInt32 arg_0, RwInt32 arg_4);
// What the join passes player arg_0 on to (sub_1C44B0); only the width is
// known.
void sub_1C44B0(RwInt32 arg_0);
// What the leave passes player arg_0 on to (sub_1C44D0); only the width is
// known.
void sub_1C44D0(RwInt32 arg_0);
// What the shutdown calls first (sub_1C4050); only the width is known.
void sub_1C4050();
// The network debug print (a pointer the retail build leaves unset calls
// through only in compiled-out code).
extern void (*off_42CD14)(const RwChar *arg_0, ...);
// What the set-up calls last (sub_1C3D90); only the width is known.
void sub_1C3D90();
// Set by the multiplayer manager's input step (sub_1AADF0) when the game
// data's unk_0C and the manager's unk_500 are both set.
extern RwUInt8 byte_4B8974;
// What the step calls after pad 0's button 0x26 (sub_1C4900) and when the
// front end's overlay is up and not playing (sub_1C4A10); only the widths
// are known.
void sub_1C4900();
void sub_1C4A10();
// The peers the voice goes to (sub_1AA380 stores its choice); the farthest
// a peer may be heard from, squared (4000000).
extern type_1DDE20_mask unk_4F7E90;
extern const RwReal flt_3E13B0;
// sub_1AF750's guard against calling itself; no other code reads it.
extern RwUInt8 byte_4F8478;
// The section streaming (types/asynchload.h and types/type_4D1DB8.h, which
// clash with <xtl.h>): whether section arg_4 is queued, the sections to
// keep, and the queue's lookup; the debug printf (game/debugtext.h).
RwInt32 sub_81FB0(RwInt32 arg_0, const RwChar *arg_4, RwInt32 arg_8);
RwInt32 sub_82020(RwInt32 arg_0, RwInt32 arg_4);
void sub_82070(RwInt32 arg_0, RwInt32 arg_4, RwInt32 arg_8, RwInt32 arg_C);
void sub_81EB0(RwInt32 arg_0, const RwChar *arg_4, RwInt32 arg_8);
void sub_16C220(const RwChar *arg_0, ...);

// The game event log (the image has its texts in this object, after its
// constants and before the vtables its constructor emits).
// match: ?sub_1A8A70@@YAXPAUtype_4F7EB8@@PBDZZ @ 0x001A8A70
void sub_1A8A70(type_4F7EB8 *arg_0, const RwChar *arg_4, ...)
{
    RwChar var_408[0x400];
    va_list var_4;

    va_start(var_4, arg_4);
    vsprintf(var_408, arg_4, var_4);
    va_end(var_4);
    if (arg_0->unk_19C)
        printf("GAME EVENT: Time(%d): %s", sub_1CCA10().get_unk_00(), var_408);
    else
        printf("GAME EVENT: No Time: %s", var_408);
}

// The manager: its scores, nothing running, the respawn and vote state
// reset.
// match: ??0type_4F7EB8@@QAE@XZ @ 0x001A8B20
// match: __ehhandler$??0type_4F7EB8@@QAE@XZ-0x24 @ 0x00302990
// match: __ehhandler$??0type_4F7EB8@@QAE@XZ @ 0x003029B4
type_4F7EB8::type_4F7EB8()
    : unk_19C(0), unk_1A0(0), unk_1A4(0), unk_1A8(0), unk_230(-1), unk_234(0), unk_278(0), unk_27C(0), unk_280(0),
      unk_284(0), unk_288(0), unk_290(0), unk_294(0), unk_2A4(5), unk_2A8(3), unk_2AC(2), unk_2B0(0), unk_2B4(-1),
      unk_2C4(0), unk_2C8(0), unk_4FC(0)
{
    dword_4FBA18 = 0;
}

// Clears dword_4F6AB8's sixteen entries.
// match: ?vf_008@type_4F7EB8@@UAEXXZ @ 0x001A8D60
void type_4F7EB8::vf_008()
{
    for (RwUInt32 i = 0; i < 16; i++)
    {
        dword_4F6AB8[i] = 0;
    }
}

// Defined in its class (game/gameloop.h), not inlined.
// match: ??1type_4F8348@@QAE@XZ @ 0x001A8E10
// match: __ehhandler$??1type_4F8348@@QAE@XZ-0xB @ 0x003029F0
// match: __ehhandler$??1type_4F8348@@QAE@XZ @ 0x003029FB
// symbol: __ehhandler$??1type_4F8348@@QAE@XZ = 0x003029FB

// Its frame's ten unused slots are the +0x490 part's destructor's
// expansion, reserved though it is not inlined (docs/toolchain.md).
// match: ??1type_4F7EB8@@QAE@XZ @ 0x001A8DA0
// match: __ehhandler$??1type_4F7EB8@@QAE@XZ-0x19 @ 0x003029C0
// match: __ehhandler$??1type_4F7EB8@@QAE@XZ @ 0x003029D9
type_4F7EB8::~type_4F7EB8()
{
}

// Cleans up after a game: the flag entities, the second and local players
// and the remote ones removed (with their cameras), the states back to
// their starts, the parts' records forgotten and the voice stopped.
// match: ?sub_1A8E80@type_4F7EB8@@QAEXXZ @ 0x001A8E80
void type_4F7EB8::sub_1A8E80()
{
    RwUInt32 i;

    dword_4F6A7C.sub_1A5D10();
    unk_234 = 0;
    unk_2A4 = 5;
    unk_2A8 = 3;
    unk_2AC = 2;
    unk_2B0 = 0;
    if (unk_1A8)
    {
        sub_D5A60(unk_1A8->unk_2110.sub_D4910(), 2);
        sub_D5A60(unk_1A8, 0);
        sub_D5D20(1);
        if (unk_230 != -1)
        {
            // A compiled-out check (docs/toolchain.md): the registers after
            // it are one load on.
            if (!unk_4FC)
            {
            }
            unk_4F6B00[unk_230].sub_1A63E0();
        }
        unk_1A8 = 0;
    }
    unk_230 = -1;
    dword_4FB9E0.sub_1B4CF0(0);
    unk_280 = 0;
    unk_278 = 0;
    unk_27C = 0;
    unk_4FBC50.sub_1C1C10();
    dword_4FBB20.sub_1BD950();
    dword_4F6A7C.sub_1A57E0();
    dword_4FB9E0.sub_1B6EF0(1);
    if (unk_1A4)
    {
        if (unk_19C->get_unk_B0()->sub_1CFFC0())
        {
            unk_4F6B00[get_1AEC70()].sub_1A6360();
        }
        else
        {
            // A compiled-out check (docs/toolchain.md): the registers after
            // it are one load on.
            if (!unk_4FC)
            {
            }
            unk_4F6B00[unk_504].sub_1A6360();
        }
        sub_D5A60(unk_1A4->unk_2110.sub_D4910(), 2);
        sub_D5A60(unk_1A4, 0);
        sub_D5D20(1);
        unk_1A4 = 0;
    }
    for (i = 0; i < 16; i++)
    {
        if (unk_1F0[i])
        {
            unk_4F6B00[i].sub_1A6460();
            // A compiled-out check (docs/toolchain.md): the registers after
            // it are one load on.
            if (!unk_4FC)
            {
            }
            sub_D5A60(unk_1F0[i], 0);
            sub_D5D20(1);
            unk_1F0[i] = 0;
        }
        unk_238[i] = 0;
    }
    unk_284 = 0;
    unk_288 = 0;
    unk_290 = 0;
    unk_294 = 0;
    if (unk_2C8 && unk_2C8->get_unk_08())
    {
        unk_2C8->sub_1C6300();
    }
}

// A level's load: the states back to their starts, the second, local and
// remote players removed, the kill cam's network players reset, and, when
// hosting, the level's load start broadcast.
// match: ?sub_1A9160@type_4F7EB8@@QAEXXZ @ 0x001A9160
void type_4F7EB8::sub_1A9160()
{
    // The locals' names state their slots (docs/toolchain.md).
    type_1DDE20_mask locC;
    type_3E1074 x8;
    RwUInt32 bp_4;

    // Two compiled-out checks (docs/toolchain.md): the registers after them
    // are two loads on.
    if (!unk_4FC)
    {
    }
    if (!unk_4FC)
    {
    }
    unk_2A4 = 5;
    unk_2A8 = 3;
    unk_2AC = 2;
    unk_2B0 = 0;
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
        }
        unk_1A8 = 0;
    }
    unk_230 = -1;
    for (bp_4 = 0; bp_4 < 16; bp_4++)
    {
        if (unk_1B0[bp_4])
        {
            unk_4F6B00[bp_4].pDtor();
        }
    }
    dword_4FB9E0.sub_1B4CF0(0);
    dword_4FB9E0.unk_D8 = 0;
    // A compiled-out check (docs/toolchain.md): the registers after it are
    // one load on.
    if (!unk_4FC)
    {
    }
    if (unk_1A4)
    {
        unk_4F6B00[get_1AEC70()].sub_1A6360();
        sub_D5A60(unk_1A4->unk_2110.sub_D4910(), 2);
        sub_D5A60(unk_1A4, 0);
        sub_D5D20(1);
        unk_1A4 = 0;
    }
    for (bp_4 = 0; bp_4 < 16; bp_4++)
    {
        if (unk_1F0[bp_4])
        {
            unk_4F6B00[bp_4].sub_1A6460();
            // A compiled-out check (docs/toolchain.md): the registers after it
            // are one load on.
            if (!unk_4FC)
            {
            }
            sub_D5A60(unk_1F0[bp_4], 0);
            sub_D5D20(1);
            unk_1F0[bp_4] = 0;
            unk_238[bp_4] = 0;
        }
    }
    dword_4FB9E0.sub_1B4CF0(2);
    dword_4FB9E0.unk_DC = 0;
    dword_4FB9E0.sub_1B6EF0(1);
    if (!unk_4F61F8.unk_104)
    {
        locC = type_4F8054::get()->get_unk_B0()->sub_1A8050();
        unk_1A0->sub_1DDDB0(&x8, locC);
        if (CODFH_DEBUG_LOGS)
        {
            off_42CD14("(HOST) Broadcast level load start to clients\n");
        }
    }
    unk_284 = 0;
    unk_288 = 0;
    unk_290 = 0;
    unk_294 = 0;
}

// Resets the game's parts: the bomb sites and flags (and the manager's parts
// of them), the ids, the full state part, the +0x490 part, the network
// players' unk_130, the respawn point and the round's scores; capture the
// flag sets its flags up again.
// match: ?sub_1A9440@type_4F7EB8@@QAEXXZ @ 0x001A9440
void type_4F7EB8::sub_1A9440()
{
    dword_4F6950.sub_1A4850();
    dword_4F6A7C.sub_1A5850();
    unk_2CC.sub_1A7CF0();
    unk_384.sub_1B1A30();
    sub_1C6050();
    unk_3D0.sub_1C25A0();
    unk_490.sub_1C3120();
    sub_1A94F0();
    unk_284 = 0;
    unk_288 = 0;
    unk_290 = 0;
    unk_294 = 0;
    dword_4F6A7C.sub_1A59D0();
    unk_D0.sub_1B3820();
}

// Clears unk_130 of the network players of the peers in the game.
// match: ?sub_1A94F0@type_4F7EB8@@QAEXXZ @ 0x001A94F0
void type_4F7EB8::sub_1A94F0()
{
    RwUInt32 i;
    type_1DDE20_mask mask;

    unk_500 = 0;
    mask = type_4F8054::get()->get_unk_B0()->sub_1A8050();
    for (i = 0; i < 16; i++)
    {
        if (mask.test(i))
        {
            // A compiled-out check (docs/toolchain.md): the registers after
            // it are one load on.
            if (!unk_4FC)
            {
            }
            unk_4F6B00[i].unk_130 = 0;
        }
    }
}

// Sets the network game up: the network players reset, the network game
// built and opened on port 0x3F9 with this as its third listener, the
// session, the message listener and the voice manager built and handed to
// it, the network system started, the game type 1, and the voice manager
// given the audio output's effects image and DirectSound.
// match: ?sub_1A9580@type_4F7EB8@@QAEXXZ @ 0x001A9580
// match: __ehhandler$?sub_1A9580@type_4F7EB8@@QAEXXZ-0x2C @ 0x00302A10
// match: __ehhandler$?sub_1A9580@type_4F7EB8@@QAEXXZ @ 0x00302A3C
// symbol: __ehhandler$?sub_1A9580@type_4F7EB8@@QAEXXZ = 0x00302A3C
void type_4F7EB8::sub_1A9580()
{
    RwUInt32 i;

    dword_4FB9E0.sub_1B4CF0(0);
    for (i = 0; i < 16; i++)
    {
        unk_1F0[i] = 0;
        unk_238[i] = 0;
        // A compiled-out check (docs/toolchain.md): the registers after it
        // are one load on.
        if (!unk_4FC)
        {
        }
        unk_4F6B00[i].sub_1A62D0(i);
    }
    unk_19C = new cXboxLiveNetGame;
    unk_19C->sub_1D5BB0(0x3F9);
    if (unk_19C)
    {
        get_unk_19C()->unk_A8 = this;
        unk_1A0 = new type_4F8058(unk_19C);
        unk_2C4 = new type_3E3860_10(unk_19C);
        unk_2C8 = new type_3E3860(unk_19C, unk_2C4);
        sub_1B18D0()->sub_1B0090(unk_19C);
    }
    sub_1D8810()->sub_1D8880();
    sub_1D8810()->set_unk_3DB0(get_unk_19C());
    unk_19C->vf_004();
    get_unk_19C()->unk_A0 = get_unk_1A0();
    get_unk_19C()->unk_A4 = get_unk_2C4();
    unk_1A0->sub_1DE1A0_16();
    dword_4FB9E0.unk_08.unk_00 = 1;
    unk_4F61F8.unk_108 = 4;
    dword_4FB9E0.sub_1B4AA0();
    dword_4FB9E0.sub_1B55B0(unk_1A0);
    type_44E8B0 *output = dword_44E8B0;
    if (output)
    {
        get_unk_2C8()->unk_3060.unk_04 = (DSEFFECTIMAGEDESC *)output->get_unk_88();
        get_unk_2C8()->unk_3060.unk_08 = (LPDIRECTSOUND8)output->get_unk_6C();
    }
    unk_29C = 1;
    unk_2BC = 1;
    unk_2A0 = 0;
    unk_2C0 = 0;
    sub_1C3D90();
}

// Retail checks retain their condition's register loads (docs/toolchain.md).
// Evidence: sub_1AED80 needs one before visibility and two before hiding;
// sub_1ABC00 needs one before recording the new state.
#define PLAYER_STATE_CHECK(condition) { if (!(condition)) { } }

// The network game's operator delete (inline in type_4F8054), which the unwinding of
// sub_1A9580's new cXboxLiveNetGame emits here (the image's funclet at 0x302A10 calls it).
// match: ??3type_4F8054@@SAXPAX@Z @ 0x001A9940

// Shuts the network game down: the voice manager stopped (its effect image
// and DirectSound cleared first) and deleted with unk_2C4, the log's
// unk_34F4 cleared, and the network game's vf_008.
// match: ?sub_1A9960@type_4F7EB8@@QAEXXZ @ 0x001A9960
void type_4F7EB8::sub_1A9960()
{
    sub_1C4050();
    get_unk_2C8()->unk_3060.unk_04 = 0;
    get_unk_2C8()->unk_3060.unk_08 = 0;
    if (unk_2C8->get_unk_08())
    {
        unk_2C8->sub_1C6300();
    }
    delete unk_2C8;
    unk_2C8 = 0;
    delete unk_2C4;
    unk_2C4 = 0;
    sub_1B18D0()->sub_1B0090(0);
    unk_19C->vf_008();
}

// Starts a game as the host: the session described (the player's name, over
// the internet or not, no address, the port, the level, the game type and
// its settings, the player count and the voice setting) and created, then
// waited for while it starts (the leave passed on with the interface still
// drawn). Once it runs, this machine is not a client: the game data takes
// the front end's settings (the scores only without a time limit) with the
// level arg_0, the players arg_4, and the live service is told.
// match: ?sub_1A9A70@type_4F7EB8@@QAEXHHPBD_N@Z @ 0x001A9A70
// match: __ehhandler$?sub_1A9A70@type_4F7EB8@@QAEXHHPBD_N@Z-0x8 @ 0x00302A50
// match: __ehhandler$?sub_1A9A70@type_4F7EB8@@QAEXHHPBD_N@Z @ 0x00302A58
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void type_4F7EB8::sub_1A9A70(RwInt32 arg_0, RwInt32 arg_4, const RwChar *arg_8, bool arg_C)
{
    // The locals' names state their slots (docs/toolchain.md).
    type_1CC1F0 var_6C;
    RwInt32 var_50;
    RwInt32 var_4C;
    RwInt32 var_48;
    RwInt32 loc44;
    type_4FB9E0_08 var_40;

    var_50 = 0;
    var_4C = 0;
    var_48 = 0;
    loc44 = 0;
    unk_4F7E9C.sub_1CB790();
    var_6C.unk_05[0] = (RwUInt8)var_50;
    var_6C.unk_05[1] = (RwUInt8)var_4C;
    var_6C.unk_05[2] = (RwUInt8)var_48;
    var_6C.unk_05[3] = (RwUInt8)loc44;
    var_6C.unk_0A = unk_4F61F8.unk_100;
    var_6C.unk_10 = (RwUInt8)arg_0;
    var_6C.unk_13 = (RwUInt8)arg_4;
    var_6C.unk_00 = dword_4F28F0->unk_183;
    var_6C.unk_0C = arg_8;
    var_6C.unk_04 = arg_C;
    var_6C.unk_11 = (RwUInt8)unk_4FDBB0.unk_00;
    var_6C.unk_12 = (RwUInt8)unk_4FDBB0.unk_04;
    var_6C.unk_14 = (RwUInt8)unk_4FDBB0.unk_0C;
    var_6C.unk_15 = (RwUInt8)unk_4FDBB0.unk_10;
    sub_227560()->sub_227870();
    var_6C.unk_16 = (RwUInt8)dword_4FDAA4;
    unk_19C->vf_05C(&var_6C);
    while (unk_19C->get_unk_04() == 1)
    {
        sub_1AF750(sub_1CCA10(), 1, 0);
        if (dword_4F7E98)
            kujuUI::sub_1F77D0(dword_4F7E98, true);
    }
    if (unk_19C->get_unk_04() == 2)
    {
        unk_4F61F8.unk_104 = 0;
        var_40.sub_1B46F0();
        var_40.unk_00 = unk_4FDBB0.unk_00;
        var_40.unk_10 = unk_4FDBB0.unk_10;
        var_40.unk_04 = unk_4FDBB0.unk_04;
        var_40.unk_24 = unk_4FDBB0.unk_24;
        var_40.unk_1C = unk_4FDBB0.unk_1C;
        var_40.unk_2C = unk_4FDBB0.unk_2C;
        if (!var_40.unk_04)
        {
            var_40.unk_14 = unk_4FDBB0.unk_14;
            var_40.unk_18 = unk_4FDBB0.unk_18;
        }
        else
        {
            var_40.unk_14 = 0;
            var_40.unk_18 = 0;
        }
        var_40.unk_08 = unk_4FDBB0.unk_08;
        var_40.unk_0C = unk_4FDBB0.unk_0C;
        var_40.unk_20 = unk_4FDBB0.unk_20;
        var_40.unk_30 = 0;
        var_40.unk_28 = arg_0;
        dword_4FB9E0.pDtor();
        dword_4FB9E0.sub_1B55D0(var_40);
        dword_4FB9E0.sub_1B57A0();
        dword_4FB9E0.sub_1B54B0(arg_0);
        unk_4FC = 0;
        sub_227560()->sub_2283F0(1);
        unk_298 = 1;
    }
}

// Joins the game arg_0 at the host arg_4 (voice with arg_C): the session
// told (vf_060) and this machine a client, then the join waited for while
// its state is neither 7 (joined) nor 8 (refused), with the interface drawn
// and fed its events and the join's state shown ("WAITING_JOIN_BEGIN" and
// on). An error ends it with the session's reason in *arg_8 (10 when
// refused) and false; once joined the game type and the players' limit (4,
// 8 or 16) are the host's, and the manager starts.
// match: ?sub_1A9CE0@type_4F7EB8@@QAE_NPBUtype_1CC1F0@@PBUtype_1CC3C0@@PAH_N@Z @ 0x001A9CE0
// match: __ehhandler$?sub_1A9CE0@type_4F7EB8@@QAE_NPBUtype_1CC1F0@@PBUtype_1CC3C0@@PAH_N@Z-0x42 @ 0x00302A70
// match: __ehhandler$?sub_1A9CE0@type_4F7EB8@@QAE_NPBUtype_1CC1F0@@PBUtype_1CC3C0@@PAH_N@Z @ 0x00302AB2
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
bool type_4F7EB8::sub_1A9CE0(const type_1CC1F0 *arg_0, const type_1CC3C0 *arg_4, RwInt32 *arg_8, bool arg_C)
{
    // The locals' names state their slots (docs/toolchain.md).
    dword_4FB9E0.sub_1B57C0();
    if (CODFH_DEBUG_LOGS)
    {
        off_42CD14("name : %s, ip : %d.%d.%d.%d - port %d, number players %d/%d\n", arg_4->unk_10,
                   arg_4->unk_04[0], arg_4->unk_04[1], arg_4->unk_04[2], arg_4->unk_04[3], arg_4->unk_08,
                   arg_4->unk_29, arg_4->unk_2A);
    }
    sub_227560()->sub_227870();
    unk_19C->vf_060(arg_0, arg_4, arg_C);
    unk_4F61F8.unk_104 = 1;
    kujuUI::type_1E7560 v11C;
    kujuUI::type_1EE900 stk_128;
    kujuUI::type_1E3DB0 *local_10 = dword_5043B4;

    while (unk_19C->get_unk_B0()->get_unk_310() != 7 && unk_19C->get_unk_B0()->get_unk_310() != 8)
    {
        if (dword_4F7E98)
        {
            unk_4B9308.sub_EE6D0();
            kujuUI::type_3E7D08 *v12C = kujuUI::sub_1F7760();

            if (local_10)
            {
                if (local_10->sub_2015D0())
                {
                    kujuUI::type_1EE900 fp_138 = local_10->sub_1E3DD0();

                    fp_138.sub_1EE940(&stk_128, &v11C);
                    stk_128 = fp_138;
                }
                while (v11C.sub_1E75F0())
                {
                    v12C->processEvent(v11C.sub_1E7610());
                }
            }
            kujuUI::sub_1F77D0(dword_4F7E98, true);
        }
        sub_1AF750(sub_1CCA10(), 1, 0);
        if (unk_19C->get_unk_10())
        {
            if (arg_8)
                *arg_8 = unk_19C->get_unk_14();
            unk_19C->sub_1CC120();
            return false;
        }
        switch (unk_19C->get_unk_B0()->get_unk_310_direct())
        {
        case 0:
            static_cast<std::string &>(unk_4F7E9C) = type_1CB670("WAITING_JOIN_BEGIN", 0);
            break;
        case 2:
            static_cast<std::string &>(unk_4F7E9C) = type_1CB670("WAITING_DETAILS_ACK", 0);
            break;
        case 3:
            static_cast<std::string &>(unk_4F7E9C) = type_1CB670("WAITING_PEER_DETAILS", 0);
            break;
        case 4:
        case 5:
            static_cast<std::string &>(unk_4F7E9C) = type_1CB670("WAITING_PEER_CONNECTIONS", 0);
            break;
        case 6:
            static_cast<std::string &>(unk_4F7E9C) = type_1CB670("WAITING_JOIN_DONE", 0);
            break;
        default:
            unk_4F7E9C.sub_1CB790();
            break;
        }
    }
    if (unk_19C->get_unk_B0()->get_unk_310() == 8)
    {
        if (arg_8)
            *arg_8 = 10;
        return false;
    }
    dword_4FB9E0.set_game_type(arg_4->unk_2B);
    switch (arg_4->unk_2A)
    {
    case 4:
        dword_4F6300 = 1;
        break;
    case 8:
        dword_4F6300 = 2;
        break;
    case 16:
        dword_4F6300 = 4;
        break;
    default:
        dword_4F6300 = 4;
        break;
    }
    unk_29C = 1;
    unk_2BC = 1;
    unk_298 = 1;
    unk_4FC = 0;
    return true;
}

// Leaves the game (by the shell's Xbox Live choice) unless the shell's
// unk_3C is set.
// match: ?sub_1AA320@type_4F7EB8@@QAEXXZ @ 0x001AA320
void type_4F7EB8::sub_1AA320()
{
    if (!dword_4F45F8->unk_3C)
    {
        if (dword_4F45F8->unk_40)
        {
            sub_227560()->sub_2270E0(5);
        }
        else
        {
            sub_227560()->sub_2270E0(4);
        }
        sub_1AF750(sub_1CCA10(), 1, 0);
    }
}

inline type_1DDE20_mask voice_mask_copy(type_1DDE20_mask &arg_0);
inline void set_voice_peers(type_1DDE20_mask arg_0);
// Chooses whom the local player talks to: the peers in the game (only those
// with remote players, by the game type and unk_29C's team rule), their
// squared distances into the voice channel's table, and every two seconds
// the nearest four within reach handed to the voice manager.
// Named by its trace ("cNetController::updateVoiceSubSystem() Player %d is
// not in player set but remote player").
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
                if (!unk_1F0[locC])
                {
                }
                lv_120.unk_00 &= ~(1 << locC);
            }
        }
    }
    else if (dword_4FB9E0.get_unk_08() == 1)
    {
        for (locC = 0; locC < 16; locC++)
        {
            if (!unk_1F0[locC])
            {
            }
            if (lv_120.test(locC) && !unk_1F0[locC])
            {
                if (!unk_1F0[locC])
                {
                }
                lv_120.unk_00 &= ~(1 << locC);
            }
        }
    }
    else
    {
        for (locC = 0; locC < 16; locC++)
        {
            if (!lv_120.unk_00)
            {
            }
            if (lv_120.test(locC))
            {
                if (unk_29C == 2 && unk_3D0.sub_1C2A90(locC) == 4 || unk_29C == 4 && unk_3D0.sub_1C2A90(locC) == 2
                    || unk_29C == 1 || !unk_1F0[locC])
                {
                    if (!lv_120.unk_00)
                    {
                    }
                    lv_120.unk_00 &= ~(1 << locC);
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
        set_voice_peers(voice_mask_copy(lv_120));
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
                        if (CODFH_DEBUG_LOGS)
                        {
                            sub_1C8A30("cNetController::updateVoiceSubSystem() Player %d is not in player set but remote player\n", locC);
                        }
                        if (CODFH_DEBUG_LOGS)
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
                    if (lcl_14C.test_checked(locC) && !bp_4.test_checked(locC) && bp_118[locC] < loc128)
                    {
                        loc128 = bp_118[locC];
                        slot_12C = locC;
                        x8 = 1;
                    }
                }
                if (x8)
                {
                    lcl_14C.discard(slot_12C);
                    bp_4.unk_00 |= 1 << slot_12C;
                    lv_144--;
                }
            }
            unk_2C8->sub_1C6440(bp_4);
        }
    }
}

// match: ?sub_1AAB30@type_4F7EB8@@QAEXXZ @ 0x001AAB30
void type_4F7EB8::sub_1AAB30()
{
    unk_4FC = 1;
}

// The step by arg_0 frames: a pending pause taken, then, while the game
// runs, its end (when the network game has an unk_10 the rules take it and
// the screen fades) or its step (the kill cam's state, the respawn and
// round checks, the input by unk_2A4, the parts' steps and the network
// players'); then the rules' step, the in-game menu's button and the flags'
// clean-up.
// match: ?sub_1AAB50@type_4F7EB8@@QAEXM@Z @ 0x001AAB50
void type_4F7EB8::sub_1AAB50(RwReal arg_0)
{
    // The locals' names state their slots (docs/toolchain.md).
    RwInt32 x8;
    RwReal bp_4;

    if (unk_4FC)
    {
        unk_4FC = 0;
        dword_4FB9E0.sub_1B6EA0();
    }
    if (sub_1AED50())
    {
        sub_1AF750(sub_1CCA10(), 0, 1);
        sub_1B18D0()->sub_1B00B0();
        if (unk_19C->get_unk_10() && !dword_4FB9E0.get_unk_C8())
        {
            unk_4F7EB8.sub_1AB400(2);
            if (!sub_227560()->get_unk_111C())
            {
                dword_4FB9E0.sub_1B5110(unk_19C->get_unk_10());
                sub_124EE0(0.5f, 0);
            }
        }
        else if (sub_1AF670() && (((kujuUI::type_1C8DF0_104_00 *)&dword_4FB9E0)->sub_1E3480() == 1 || ((kujuUI::type_1C8DF0_104_00 *)&dword_4FB9E0)->sub_1E3480() == 3))
        {
            sub_1ABC00();
            sub_1AB440();
            if (!dword_4FB9E0.get_unk_C4() && !dword_4FB9E0.get_unk_C8() && ((kujuUI::type_1C8DF0_104_00 *)&dword_4FB9E0)->sub_1E3480() == 1)
            {
                sub_1ABE30();
            }
            switch (unk_2A4)
            {
            case 3:
                sub_1AAF40();
                break;
            case 1:
                sub_1AADF0();
                break;
            case 4:
                sub_1AB070();
                break;
            }
            switch (unk_2AC)
            {
            }
            sub_19A750();
            unk_2CC.sub_1A84C0(arg_0);
            unk_384.sub_1B23B0(arg_0);
            unk_384.sub_1B2670();
            unk_490.sub_1C31D0(arg_0);
            for (x8 = 0; x8 < 16; x8++)
            {
                // A compiled-out check (docs/toolchain.md): the registers after it
                // are one load on.
                if (!unk_4FC)
                {
                }
                unk_4F6B00[x8].sub_1A64A0(sub_1CCA10());
            }
            updateVoiceSubSystem();
        }
        dword_4FB9E0.sub_1B5A40();
        bp_4 = unk_4B9308.sub_EE9A0(0, 0x26);
        if (bp_4 != 0.0f)
        {
            sub_1C4900();
        }
        else if (sub_1FF250()->sub_200780() && !sub_1FF250()->get_unk_0C())
        {
            sub_1C4A10();
        }
        dword_4F6A7C.sub_1A4980();
    }
}

// The input step: pad 0's button 0x17 pauses (a half-second fade, the
// game's pause), buttons 0x15 and 0x16 view the previous and next team
// mates; then the view.
// match: ?sub_1AADF0@type_4F7EB8@@QAEXXZ @ 0x001AADF0
void type_4F7EB8::sub_1AADF0()
{
    // A compiled-out check (docs/toolchain.md): the registers after it
    // are one load on.
    if (!unk_4FC)
    {
    }
    if (dword_4FB9E0.get_unk_0C() && unk_500)
    {
        byte_4B8974 = 1;
    }
    if (!((dword_4B86F8 >> 4) & 1))
    {
        if (unk_4B9308.sub_EE950(0, 0x17) != 0.0f && ((kujuUI::type_1C8DF0_104_00 *)&dword_4FB9E0)->sub_1E3480() == 1)
        {
            if (!unk_4F61F8.unk_104)
            {
                dword_4FB9E0.sub_1B6EF0(0);
            }
            if (!dword_4FB9E0.sub_1B6E50())
            {
                if ((dword_4FB9E0.get_unk_08() == 8 || !dword_4FB9E0.get_unk_0C() || !unk_500)
                    && !((kujuUI::cScopeValidator *)&dword_4FB9E0)->sub_1CA260())
                {
                    sub_124EE0(0.5f, 1);
                    sub_1AB400(0);
                    unk_500 = 1;
                }
            }
        }
        if (unk_4B9308.sub_EE950(0, 0x15) != 0.0f)
        {
            sub_1AB140();
        }
        if (unk_4B9308.sub_EE950(0, 0x16) != 0.0f)
        {
            sub_1AB200();
        }
    }
    sub_1AAF40();
}

// The view: without a player viewed, the second player's view goes to
// unk_234's matrix (else to an identity one), its weapon back on; with one,
// that remote player's sections are streamed in.
// match: ?sub_1AAF40@type_4F7EB8@@QAEXXZ @ 0x001AAF40
void type_4F7EB8::sub_1AAF40()
{
    if (unk_230 == -1)
    {
        if (unk_234)
        {
            unk_1A8->sub_1BD1C0(&unk_234->unk_60);
            unk_1A8->set_unk_1B3C(false);
        }
        else
        {
            RwMatrix view;

            RwMatrixSetIdentityMacro(&view);
            unk_1A8->sub_1BD1C0(&view);
            unk_1A8->set_unk_1B3C(false);
        }
    }
    else if (unk_1F0[unk_230])
    {
        sub_1AF850(unk_230);
    }
}

// match: ?sub_1AB070@type_4F7EB8@@QAEXXZ @ 0x001AB070
void type_4F7EB8::sub_1AB070()
{
    RwInt32 me;

    // A compiled-out check (docs/toolchain.md): the registers after it are
    // one load on.
    if (!unk_4FC)
    {
    }
    if (!((dword_4B86F8 >> 4) & 1) && unk_4B9308.sub_EE950(0, 0x17) != 0.0f
        && ((kujuUI::type_1C8DF0_104_00 *)&dword_4FB9E0)->sub_1E3480() == 1)
    {
        sub_124EE0(0.5f, 1);
        sub_1AB400(0);
        sub_1AB420(0);
    }
    unk_524 = 1;
    // A compiled-out check (docs/toolchain.md): the registers after it are
    // one load on.
    if (!unk_4FC)
    {
    }
    if (unk_4F6B00[unk_2B8].sub_1E4CB0() || (me = sub_1AEC70(), unk_4F6B00[me].sub_1E4CB0()))
    {
        // A compiled-out check (docs/toolchain.md): the registers after it
        // are one load on.
        if (!unk_4FC)
        {
        }
        unk_524 = 0;
    }
}

// Views the previous player on the local player's team (sub_1AB2C0 first;
// the search after it is dead code).
// match: ?sub_1AB140@type_4F7EB8@@QAEXXZ @ 0x001AB140
void type_4F7EB8::sub_1AB140()
{
    RwInt32 i;

    sub_1AB2C0();
    return;
    while (i > 0)
    {
        i--;
        // A compiled-out check (docs/toolchain.md): the registers after it
        // are one load on.
        if (!unk_4FC)
        {
        }
        if (unk_4F6B00[i].is_shown())
        {
            if (unk_3D0.sub_1C2A90(i) == unk_3D0.sub_1C2A90(sub_1AEC70()))
            {
                // A compiled-out check (docs/toolchain.md): the registers
                // after it are one load on.
                if (!unk_4FC)
                {
                }
                unk_4F6B00[i].sub_1A63A0(unk_1A8);
                unk_230 = i;
                sub_1AF810(i);
                return;
            }
        }
    }
    sub_1AB2C0();
}

// Views the next player on the local player's team (likewise dead after
// sub_1AB2C0).
// match: ?sub_1AB200@type_4F7EB8@@QAEXXZ @ 0x001AB200
void type_4F7EB8::sub_1AB200()
{
    RwInt32 i;

    sub_1AB2C0();
    return;
    while (i < 16)
    {
        // A compiled-out check (docs/toolchain.md): the registers after it
        // are one load on.
        if (!unk_4FC)
        {
        }
        if (unk_4F6B00[i].is_shown())
        {
            if (unk_3D0.sub_1C2A90(i) == unk_3D0.sub_1C2A90(sub_1AEC70()))
            {
                // A compiled-out check (docs/toolchain.md): the registers
                // after it are one load on.
                if (!unk_4FC)
                {
                }
                unk_4F6B00[i].sub_1A63A0(unk_1A8);
                unk_230 = i;
                sub_1AF810(i);
                return;
            }
        }
        i++;
    }
    sub_1AB2C0();
}

// Stops viewing another player: the second player's view goes to unk_234's
// matrix (else to an identity one), its weapon back on.
// match: ?sub_1AB2C0@type_4F7EB8@@QAEXXZ @ 0x001AB2C0
void type_4F7EB8::sub_1AB2C0()
{
    // A compiled-out check (docs/toolchain.md): the registers after it are
    // one load on.
    if (!unk_4FC)
    {
    }
    if (unk_1A8)
    {
        if (unk_230 != -1)
        {
            // A compiled-out check (docs/toolchain.md): the registers after
            // it are one load on.
            if (!unk_4FC)
            {
            }
            unk_4F6B00[unk_230].sub_1A63E0();
        }
        unk_230 = -1;
        if (unk_234)
        {
            unk_1A8->sub_1BD1C0(&unk_234->unk_60);
            unk_1A8->set_unk_1B3C(false);
        }
        else
        {
            RwMatrix view;

            RwMatrixSetIdentityMacro(&view);
            unk_1A8->sub_1BD1C0(&view);
            unk_1A8->set_unk_1B3C(false);
        }
        sub_1AF7E0();
    }
}

// match: ?sub_1AB400@type_4F7EB8@@QAEXH@Z @ 0x001AB400
void type_4F7EB8::sub_1AB400(RwInt32 arg_0)
{
    unk_2A8 = arg_0;
}

// match: ?sub_1AB420@type_4F7EB8@@QAEXH@Z @ 0x001AB420
void type_4F7EB8::sub_1AB420(RwInt32 arg_0)
{
    unk_2B0 = arg_0;
}

// Changes the view to the requested one (unk_2A8): 3, spectating others (the
// local player removed); 0, playing (the second player and the kill cam
// player removed); 1, following (from anything but 3: the local player
// removed); 2, static spectating (from anything but 1 and 3, else the view
// reset). Each tells the peers whether this machine spectates, fades and
// shows the letterbox.
// The following view's countdown (the game data's unk_08.unk_2C, 0x4FBA14)
// goes to sub_1B6DE0 through the FPU (fld; push ecx; fstp [esp]) with no
// temporary: nowhere else in the image, and no C++ form gives it (a member
// is copied with mov; casts, a volatile field or an inline getter add a
// slot), so the original made that call in __asm.
// match: ?sub_1AB440@type_4F7EB8@@QAEXXZ @ 0x001AB440
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
                if (CODFH_DEBUG_LOGS)
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
                // begin original __asm (the original passes the countdown on the
                // FPU: dword_4FB9E0.sub_1B6DE0(dword_4FB9E0.unk_08.unk_2C))
                __asm
                {
                    fld dword ptr [dword_4FB9E0 + 0x34]
                    push ecx
                    fstp dword ptr [esp]
                    mov ecx, offset dword_4FB9E0
                    call type_4FB9E0::sub_1B6DE0
                }
                // end original __asm
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
        // A compiled-out check (docs/toolchain.md): the registers after it
        // are one load on.
        if (!unk_4FC)
        {
        }
        unk_2A4 = unk_2A8;
    }
}

// Takes the requested state (unk_2B0) as unk_2AC; leaving state 1 for 0
// ends the kill cam: its players go, and the peers in the game get remote
// players (made by unk_27C) where they have none.
// match: ?sub_1ABC00@type_4F7EB8@@QAEXXZ @ 0x001ABC00
void type_4F7EB8::sub_1ABC00()
{
    type_1DDE20_mask mask;
    RwUInt32 i;

    if (unk_2AC != unk_2B0)
    {
        switch (unk_2B0)
        {
        case 0:
            if (unk_2AC == 1)
            {
                mask = type_4F8054::get()->get_unk_B0()->sub_1A8050();
                for (i = 0; i < 16; i++)
                {
                    if (unk_1B0[i])
                    {
                        if (CODFH_DEBUG_LOGS)
                        {
                            sub_1C8A30("Deleting Remote KILL CAM player: %d\n", i);
                        }
                        unk_4F6B00[i].pDtor();
                        // A compiled-out check (docs/toolchain.md): the
                        // registers after it are one load on.
                        if (!unk_4FC)
                        {
                        }
                        sub_D5A60(unk_1B0[i], 0);
                    }
                }
                sub_D5D20(1);
                for (i = 0; i < 16; i++)
                {
                    if (unk_1B0[i])
                    {
                        unk_1B0[i] = 0;
                        if (mask.test(i))
                        {
                            if (CODFH_DEBUG_LOGS)
                            {
                                sub_1C8A30("Bind from KILL CAM: %d\n", i);
                            }
                            if (!unk_1F0[i])
                            {
                                unk_1F0[i] = unk_27C->vf_020();
                                network_player(i).sub_1A6420(unk_1F0[i]);
                                unk_1F0[i]->pvf_010(unk_1A0);
                            }
                        }
                    }
                }
            }
            break;
        }
    }
    PLAYER_STATE_CHECK(unk_2B0 >= 0);
    unk_2AC = unk_2B0;
}

// The local player's respawn, once asked for (unk_284). The first step picks
// the team and kit chosen (the second player's team taken when team 1 is
// asked for) and the spawn point: the host's own (sub_1AD380 over the
// point set), a client's asked of the host (type_3E10D4). The next steps
// (after 10 seconds the session gives up and the screen fades) wait for the
// point and the fade, then place the player's trigger at the point (made
// upright), give it the team's kit, respawn it, fade in and tell the peers
// (type_3E117C) and the teams.
// match: ?sub_1ABE30@type_4F7EB8@@QAEXXZ @ 0x001ABE30
void type_4F7EB8::sub_1ABE30()
{
    type_1DDE20_mask var_8;
    type_3E10D4 var_10;
    RwUInt32 *var_14 = 0;
    RwInt32 var_18;

    if (unk_284)
    {
        if (!unk_288)
        {
            unk_29C = unk_2BC;
            unk_2A0 = unk_2C0;
            if (!sub_1AEC70())
            {
                if (unk_29C == 1)
                {
                    sub_1AFB70();
                    unk_29C = unk_2BC;
                    unk_298 = unk_29C;
                }
                // A compiled-out check (docs/toolchain.md): one load on.
                if (!unk_2BC)
                {
                }
                unk_3D0.sub_1C2600(0, unk_29C);
                var_18 = sub_1AC4E0(unk_29C);
                unk_294 = sub_1AD380(var_18, 0);
                unk_290 = 1;
            }
            else
            {
                // Another (docs/toolchain.md): one load on.
                if (!unk_2BC)
                {
                }
                var_10.unk_04 = unk_29C;
                // Two more (docs/toolchain.md): two loads on.
                if (!unk_2BC)
                {
                }
                if (!unk_2BC)
                {
                }
                var_8.put(0);
                dword_4F8058->sub_1DDE20(&var_10, var_8);
                sub_1A8A70(&unk_4F7EB8, "(CLIENT) Requested spawn point from set %d from server\n", var_18);
            }
            unk_288 = 1;
            unk_28C = sub_1CCA10();
        }
        else
        {
            RwInt32 var_30 = sub_1CCA10() - unk_28C;
            RwReal var_34 = var_30 * 0.001f;

            if (var_34 > 10.0f)
            {
                unk_19C->get_unk_B0()->sub_1CD370();
                unk_19C->setError(7, 6);
                sub_124EE0(0.5f, 0);
            }
            if (unk_290 && fade_done())
            {
                if (unk_29C == 1)
                {
                    // Another (docs/toolchain.md): one load on.
                    if (!unk_2BC)
                    {
                    }
                    unk_2BC = unk_298;
                    unk_29C = unk_2BC;
                }
                // Another (docs/toolchain.md): one load on.
                if (!unk_2BC)
                {
                }
                var_14 = unk_4FBC50.sub_1C20D0(unk_294);
                sub_1C58C0();
                dword_4B6850 = 1;
                // Two more (docs/toolchain.md): two loads on.
                if (!unk_2BC)
                {
                }
                if (!unk_2BC)
                {
                }
                dword_4B6840[0] = var_14[0];
                dword_4B6840[1] = var_14[1];
                dword_4B6840[2] = var_14[2];
                dword_4B6840[3] = var_14[3];
                sub_D8660();
                RwMatrix var_80 = *unk_4FBC50.sub_1C20F0(unk_294);

                {
                    RwV3d *var_84 = &var_80.up;
                    RwV3d *var_88 = &var_80.at;
                    RwV3d *var_8C = &var_80.right;

                    var_84->x = 0;
                    var_84->y = 1.0f;
                    var_84->z = 0;
                    RwV3dCrossProduct(var_88, var_8C, var_84);
                    RwV3dCrossProduct(var_8C, var_84, var_88);
                }
                RwMatrixUpdate(&var_80);
                unk_278->sub_1BEAC0(&var_80);
                if (unk_280)
                {
                    unk_278->unk_470[0] = sub_1C5860(unk_280->sub_1B79A0(unk_29C, unk_2A0));
                    unk_278->unk_470[1] = -1;
                    unk_278->unk_478 = sub_1C5860(unk_280->sub_1B79A0(unk_29C, 4));
                    unk_278->unk_47C = sub_1AF2C0(unk_2A0);
                    unk_278->unk_CC = *(type_3DF8D8_04 *)unk_280->sub_1B7940(unk_29C);
                }
                unk_278->sub_1BE5E0();
                unk_284 = 0;
                sub_124EE0(0.5f, 0);
                dword_4FDA9C = 0;
                type_3E117C var_98;

                var_98.unk_04 = unk_29C;
                var_98.unk_08 = unk_278->unk_108[0];
                // Two more (docs/toolchain.md): two loads on.
                if (!unk_2BC)
                {
                }
                if (!unk_2BC)
                {
                }
                get_unk_1A0()->sub_1DDE20(&var_98, get_unk_19C()->get_unk_B0()->sub_1A8050());
                sub_1A8A70(&unk_4F7EB8, "Local player respawned\n");
                unk_3D0.sub_1C28F0(sub_1AEC70(), unk_29C, 0);
                clear_hud_unk_90();
                unk_290 = 0;
                unk_288 = 0;
            }
        }
    }
}

// How many spawn points team arg_0 has by the game type (the other of
// teams 2 and 4 with four teams).
// match: ?sub_1AC4E0@type_4F7EB8@@QAEHH@Z @ 0x001AC4E0
RwInt32 type_4F7EB8::sub_1AC4E0(RwInt32 arg_0)
{
    RwInt32 r = 0;

    if (dword_4FB9E0.get_unk_10C())
    {
        if (arg_0 == 2)
        {
            arg_0 = 4;
        }
        else
        {
            arg_0 = 2;
        }
    }
    switch (dword_4FB9E0.get_game_type())
    {
    case 1:
        r = 0;
        break;
    case 2:
        r = unk_4FBC50.sub_1C2050(arg_0, -1);
        break;
    case 4:
        r = unk_4FBC50.sub_1C2050(arg_0, -1);
        break;
    case 8:
        r = unk_4FBC50.sub_1C2050(arg_0, -1);
        break;
    case 16:
        r = 0;
        break;
    }
    return r;
}

// Player arg_0 joins: logged, and told whether this game spectates
// (unk_2A4 1 or 3) and, from a client outside the rules' unk_10C, the
// rules.
// match: ?vf_000@type_4F7EB8@@UAEXH@Z @ 0x001AC5D0
void type_4F7EB8::vf_000(RwInt32 arg_0)
{
    // The locals' names state their slots (docs/toolchain.md).
    RwChar fp_108[0x100];

    if (arg_0 != -1 && (RwUInt32)arg_0 < 16)
    {
        dword_4F6AB8[arg_0] = 0;
    }
    dword_4FB9E0.sub_1B4EA0(arg_0);
    sprintf(fp_108, "Player Joined: #%d, %s", arg_0, unk_19C->get_unk_B0()->unk_90[arg_0].unk_00);
    sub_1B18D0()->sub_1B1780(fp_108, 1);
    type_1DDE20_mask bp_4;
    // Two compiled-out checks (docs/toolchain.md): the registers after them
    // are two loads on.
    if (!bp_4.unk_00)
    {
    }
    if (!bp_4.unk_00)
    {
    }
    bp_4.insert(arg_0);
    type_3E0F84 ebp_110;
    ebp_110.unk_04 = unk_2A4 == 1 || unk_2A4 == 3 ? 1 : 0;
    get_unk_1A0()->sub_1DDDB0(&ebp_110, bp_4);
    if (!unk_4F61F8.unk_104 && !((kujuUI::cScopeValidator *)&dword_4FB9E0)->sub_1CA260())
    {
        type_3E10BC fp_118;
        fp_118.unk_04 = 0;
        get_unk_1A0()->sub_1DDDB0(&fp_118, bp_4);
    }
    sub_1C44B0(arg_0);
}

// Player arg_0 leaves: its flag and scores dropped, its remote player
// removed, logged and shown ("MW_GEN_LEAVE" with its name).
// match: ?vf_004@type_4F7EB8@@UAEXH@Z @ 0x001AC790
// match: __ehhandler$?vf_004@type_4F7EB8@@UAEXH@Z-0xB @ 0x00302AC0
// match: __ehhandler$?vf_004@type_4F7EB8@@UAEXH@Z @ 0x00302ACB
// symbol: __ehhandler$?sub_1AC790@type_4F7EB8@@QAEXH@Z = 0x00302ACB
void type_4F7EB8::vf_004(RwInt32 arg_0)
{
    RwChar text[0x100];

    unk_384.sub_1B24E0(arg_0);
    unk_4F7EB8.unk_04.sub_1B2D00(arg_0, arg_0, 0);
    sub_1AC990(arg_0);
    sprintf(text, "Player Removed: #%d, %s", arg_0, unk_19C->get_unk_B0()->unk_90[arg_0].unk_00);
    sub_1B18D0()->sub_1B1780(text, 1);
    sub_1CB000(text, sub_E3970("MW_GEN_LEAVE", 1).c_str(), type_4F8054::get()->get_unk_B0()->unk_90[arg_0].unk_00);
    sub_EACA0(text, 0, 0);
    dword_4F8288.sub_1C2940(arg_0);
    sub_1C44D0(arg_0);
}

// match: ?sub_1AC950@type_4F7EB8@@QAEXH@Z @ 0x001AC950
void type_4F7EB8::sub_1AC950(RwInt32 arg_0)
{
    unk_4F6B00[arg_0].sub_1A62F0();
    // A compiled-out check (docs/toolchain.md): the registers after it are
    // one load on.
    if (!unk_4FC)
    {
    }
    dword_4F6AB8[arg_0] = 0;
    unk_238[arg_0] = 0;
}

// Removes peer arg_0's remote player (hiding its network player when in
// view) and resets the network player; the scores drop it when not hosting.
// match: ?sub_1AC990@type_4F7EB8@@QAEXH@Z @ 0x001AC990
void type_4F7EB8::sub_1AC990(RwInt32 arg_0)
{
    if (unk_1F0[arg_0])
    {
        // A compiled-out check (docs/toolchain.md): the registers after it
        // are one load on.
        if (!unk_4FC)
        {
        }
        if (unk_4F6B00[arg_0].is_visible())
        {
            unk_4F6B00[arg_0].sub_1A63E0();
            unk_4F7EB8.sub_1AB2C0();
        }
        unk_4F6B00[arg_0].sub_1A6460();
        // Two compiled-out checks (docs/toolchain.md): the registers after
        // them are two loads on.
        if (!unk_4FC)
        {
        }
        if (!unk_4FC)
        {
        }
        sub_D5A60(unk_1F0[arg_0], 0);
        sub_D5D20(1);
        unk_1F0[arg_0] = 0;
        unk_238[arg_0] = 0;
    }
    unk_4F6B00[arg_0].pDtor();
    // A compiled-out check (docs/toolchain.md): the registers after it are
    // one load on.
    if (!unk_4FC)
    {
    }
    if (!unk_4F61F8.unk_104)
    {
        unk_4F7EB8.unk_04.sub_1B3270(arg_0);
    }
}

// match: ?sub_1ACA70@type_4F7EB8@@QAEIXZ @ 0x001ACA70
RwUInt32 type_4F7EB8::sub_1ACA70()
{
    return get_unk_19C()->get_unk_B0()->get_unk_0C().sub_1D4A60();
}

// A bullet hit on the local player from peer arg_4 (in a game type 1 when
// neither dword_4FBAA4 nor dword_4FBAA8 is set and unk_2A4 is not 4): its
// amount given to the player's network part, and on a hit sub_1ACBA0 and
// sub_1ADB40.
// match: ?sub_1ACAB0@@YAXHHPAUtype_3DA44C@@@Z @ 0x001ACAB0
void sub_1ACAB0(RwInt32 arg_0, RwInt32 arg_4, type_3DA44C *arg_8)
{
    // The locals' names state their slots (docs/toolchain.md).
    type_75600 r34;
    type_3DA434 *bp_4;

    sub_1A8A70(&unk_4F7EB8, "Bullet hit local player - Firer: %d\n", arg_4);
    bp_4 = (type_3DA434 *)arg_8;
    if (((kujuUI::type_1C8DF0_104_00 *)&dword_4FB9E0)->sub_1E3480() != 1 || dword_4FB9E0.get_unk_C8() || dword_4FB9E0.get_unk_C4()
        || unk_4F7EB8.unk_2A4 == 4)
    {
        return;
    }
    if (unk_4F7EB8.unk_1A4)
    {
        r34.unk_24 = bp_4->unk_08;
        r34.unk_28 = bp_4->get_unk_0C();
        r34.unk_2C = bp_4->get_unk_0C();
        r34.unk_0C = unk_4F7EB8.sub_1AECA0(arg_4, 0);
        if (unk_4F7EB8.unk_1A4->pvf_03C(&r34))
        {
            sub_1ACBA0(arg_4, bp_4);
            unk_4F7EB8.sub_1ADB40(arg_4);
        }
    }
}

// The local player killed by peer arg_0's bullet (arg_4): the kill sent to
// the other peers, shown ("MW_GEN_KILLS_YOUYOURSELF" or
// "MW_GEN_KILLS_YOUGUN" with the killer's name) and counted; when not
// hosting the scores take it and the local player drops its pickups.
// match: ?sub_1ACBA0@@YAXHPAUtype_3DA434@@@Z @ 0x001ACBA0
// match: __ehhandler$?sub_1ACBA0@@YAXHPAUtype_3DA434@@@Z-0xB @ 0x00302AE0
// match: __ehhandler$?sub_1ACBA0@@YAXHPAUtype_3DA434@@@Z @ 0x00302AEB
void sub_1ACBA0(RwInt32 arg_0, type_3DA434 *arg_4)
{
    // The locals' names state their slots (docs/toolchain.md).
    RwChar l114[0x100];

    if (unk_4F7EB8.unk_2A4 == 4)
    {
        return;
    }
    type_3E114C lcl_128;
    lcl_128.unk_04 = arg_4->get_unk_0C();
    lcl_128.unk_0C = arg_4->unk_08;
    lcl_128.unk_08 = arg_4->unk_04;
    lcl_128.unk_0D = (RwUInt8)arg_0;
    lcl_128.unk_10 = unk_4F7EB8.sub_1AD730();
    // Two compiled-out checks (docs/toolchain.md): the registers after them
    // are two loads on.
    if (!arg_4->unk_04)
    {
    }
    if (!arg_4->unk_04)
    {
    }
    type_4F8058::get()->sub_1DDDB0(&lcl_128, type_4F8054::get()->get_unk_B0_checked()->others_checked());
    sub_1A8A70(&unk_4F7EB8, "Local player killed by bullet from player %d\n", arg_0);
    if (arg_0 == unk_4F7EB8.sub_1AEC70())
    {
        strcpy(l114, sub_E3970("MW_GEN_KILLS_YOUYOURSELF", 1).c_str());
    }
    else
    {
        sub_1CB000(l114, sub_E3970("MW_GEN_KILLS_YOUGUN", 1).c_str(),
                   type_4F8054::get()->get_unk_B0()->unk_90[arg_0].unk_00);
    }
    show_message(l114);
    dword_4F8288.sub_1C28F0(unk_4F7EB8.sub_1AEC70(), 1, 1);
    if (!hosting())
    {
        unk_4F7EB8.unk_04.sub_1B2D00(unk_4F7EB8.sub_1AEC70(), arg_0, 0);
        unk_4F7EB8.sub_1ADB80(lcl_128.unk_10, 0);
    }
}

// A bullet hit on a remote player (the one in the message) from peer arg_4,
// on the bullet hit's terms: to that player, and to the second player when
// the one hit is unk_230.
// match: ?sub_1ACEB0@@YAXHHPAUtype_3DA44C@@@Z @ 0x001ACEB0
void sub_1ACEB0(RwInt32 arg_0, RwInt32 arg_4, type_3DA44C *arg_8)
{
    // The locals' names state their slots (docs/toolchain.md).
    type_75600 r34;
    type_3E0F6C *bp_4;

    sub_1A8A70(&unk_4F7EB8, "Bullet hit remote player - Firer: %d\n", arg_4);
    bp_4 = (type_3E0F6C *)arg_8;
    if (((kujuUI::type_1C8DF0_104_00 *)&dword_4FB9E0)->sub_1E3480() != 1 || dword_4FB9E0.get_unk_C8() || dword_4FB9E0.get_unk_C4()
        || unk_4F7EB8.unk_2A4 == 4)
    {
        return;
    }
    // Two compiled-out checks (docs/toolchain.md): the registers after them
    // are two loads on.
    if (!bp_4->unk_04)
    {
    }
    if (!bp_4->unk_04)
    {
    }
    if (unk_4F7EB8.unk_1F0[bp_4->unk_09])
    {
        r34.unk_24 = bp_4->unk_08;
        r34.unk_28 = bp_4->get_unk_0C();
        r34.unk_2C = bp_4->get_unk_0C();
        r34.unk_0C = unk_4F7EB8.sub_1AECA0(arg_4, 0);
        unk_4F7EB8.unk_1F0[bp_4->unk_09]->pvf_014(&r34);
        if (unk_4F7EB8.unk_230 == bp_4->unk_09 && unk_4F7EB8.unk_1A8)
        {
            unk_4F7EB8.unk_1A8->pvf_014(&r34);
        }
    }
}

// Peer arg_4 starts spectating (the message's unk_04 set: its remote player
// goes) or participating again.
// match: ?sub_1ACFD0@@YAXHHPAUtype_3DA44C@@@Z @ 0x001ACFD0
void sub_1ACFD0(RwInt32 arg_0, RwInt32 arg_4, type_3DA44C *arg_8)
{
    RwChar text[0x100];
    type_3E0F84 *m = (type_3E0F84 *)arg_8;

    if (((kujuUI::type_1C8DF0_104_00 *)&dword_4FB9E0)->sub_1E3480() != 1 || dword_4FB9E0.get_unk_C8() || dword_4FB9E0.get_unk_C4())
    {
        return;
    }
    if (m->unk_04)
    {
        if (unk_4F7EB8.unk_1F0[arg_4])
        {
            unk_4F7EB8.sub_1AC990(arg_4);
            sprintf(text, "Player Spectating: #%d", arg_4);
            sub_1B18D0()->sub_1B1780(text, 1);
        }
        if (unk_4F7EB8.unk_230 == arg_4)
        {
            unk_4F7EB8.sub_1AB2C0();
        }
    }
    else if (!unk_4F7EB8.unk_1F0[arg_4])
    {
        unk_4F7EB8.sub_1AC950(arg_4);
        sprintf(text, "Player Participating: #%d", arg_4);
        sub_1B18D0()->sub_1B1780(text, 1);
    }
}

// A grenade hit on the remote player arg_4, on the bullet hit's terms: an
// explosion's hit at the message's point, to that player and to the second
// player when it is unk_230.
// match: ?sub_1AD0F0@@YAXHHPAUtype_3DA44C@@@Z @ 0x001AD0F0
// match: __ehhandler$?sub_1AD0F0@@YAXHHPAUtype_3DA44C@@@Z-0x8 @ 0x00302B00
// match: __ehhandler$?sub_1AD0F0@@YAXHHPAUtype_3DA44C@@@Z @ 0x00302B08
// symbol: __ehhandler$?sub_1AD0F0@@YAXHHPAUtype_3DA44C@@@Z = 0x00302B08
void sub_1AD0F0(RwInt32 arg_0, RwInt32 arg_4, type_3DA44C *arg_8)
{
    sub_1A8A70(&unk_4F7EB8, "Grenade hit remote player - Victim: %d\n", arg_4);
    type_3E1194 *m = (type_3E1194 *)arg_8;
    if (((kujuUI::type_1C8DF0_104_00 *)&dword_4FB9E0)->sub_1E3480() != 1 || dword_4FB9E0.get_unk_C8() || dword_4FB9E0.get_unk_C4()
        || unk_4F7EB8.unk_2A4 == 4)
    {
        return;
    }
    // Two compiled-out checks (docs/toolchain.md): the registers after them
    // are two loads on.
    if (!unk_4F7EB8.unk_1F0[arg_4])
    {
    }
    if (!unk_4F7EB8.unk_1F0[arg_4])
    {
    }
    if (unk_4F7EB8.unk_1F0[arg_4])
    {
        type_4AE70 hit;
        RwMatrix where;

        hit.unk_2C = m->unk_04;
        where.pos.x = m->unk_08.unk_00;
        where.pos.y = m->unk_08.unk_04;
        where.pos.z = m->unk_08.unk_08;
        hit.unk_0C = &where;
        hit.unk_10 = m->unk_14;
        hit.unk_14 = m->unk_14;
        hit.unk_18 = m->unk_14;
        unk_4F7EB8.unk_1F0[arg_4]->pvf_01C(&hit);
        if (unk_4F7EB8.unk_230 == arg_4 && unk_4F7EB8.unk_1A8)
        {
            unk_4F7EB8.unk_1A8->pvf_01C(&hit);
        }
    }
}

// A spawn point request from peer arg_4 (with its team, or 1 for the one
// the full state part keeps): the point picked is sent back to it.
// match: ?sub_1AD260@@YAXHHPAUtype_3DA44C@@@Z @ 0x001AD260
void sub_1AD260(RwInt32 arg_0, RwInt32 arg_4, type_3DA44C *arg_8)
{
    // The locals' names state their slots (docs/toolchain.md).
    type_1DDE20_mask bp_18;
    type_3E10EC r10;
    RwInt32 lv_20 = 1;
    type_3E10D4 *bp_4 = (type_3E10D4 *)arg_8;

    if (((kujuUI::type_1C8DF0_104_00 *)&dword_4FB9E0)->sub_1E3480() != 1 || dword_4FB9E0.get_unk_C8() || dword_4FB9E0.get_unk_C4())
    {
        return;
    }
    sub_1A8A70(&unk_4F7EB8, "(SERVER) Player %d requested spawn point using team id %d\n", arg_4, bp_4->unk_04);
    lv_20 = bp_4->unk_04;
    if (lv_20 == 1)
    {
        lv_20 = dword_4F8288.sub_1C2440();
    }
    dword_4F8288.sub_1C2600(arg_4, lv_20);
    RwInt32 lv_1C = unk_4F7EB8.sub_1AC4E0(lv_20);
    RwInt32 frm_14 = sub_1AD380(lv_1C, arg_4);
    bp_18.insert(arg_4);
    r10.unk_04 = frm_14;
    r10.unk_08 = lv_20;
    dword_4F8058->sub_1DDE20(&r10, bp_18);
    sub_1A8A70(&unk_4F7EB8, "(SERVER) Player %d given spawn point #%d\n", arg_4, frm_14);
}

// Picks a spawn point from arg_0 for player arg_4 away from the other
// players (the remote ones and the local one) by the game type's rule.
// match: ?sub_1AD380@@YAHHH@Z @ 0x001AD380
RwInt32 sub_1AD380(RwInt32 arg_0, RwInt32 arg_4)
{
    // The locals' names state their slots (docs/toolchain.md).
    RwReal *bp_4;
    RwUInt32 x8;
    type_4FBC50_player u108[16];
    RwInt32 m_10C;
    type_4F7EB8_1F0 *loc110;
    RwUInt32 slot_118;
    RwInt32 q114;

    x8 = 0;
    for (slot_118 = 0; slot_118 < 16; slot_118++)
    {
        if (slot_118 != arg_4)
        {
            loc110 = unk_4F7EB8.unk_1F0[slot_118];
            if (loc110)
            {
                bp_4 = loc110->vf_0C4();
                u108[x8].unk_00.unk_00 = bp_4[0];
                u108[x8].unk_00.unk_04 = bp_4[1];
                u108[x8].unk_00.unk_08 = bp_4[2];
                u108[x8].unk_0C = dword_4F8288.sub_1C2A90(slot_118);
                x8++;
            }
        }
    }
    if (unk_4F7EB8.sub_1AEC70() != arg_4 && unk_4F7EB8.unk_1A4)
    {
        bp_4 = unk_4F7EB8.unk_1A4->vf_0C4();
        u108[x8].unk_00.unk_00 = bp_4[0];
        u108[x8].unk_00.unk_04 = bp_4[1];
        u108[x8].unk_00.unk_08 = bp_4[2];
        u108[x8].unk_0C = dword_4F8288.sub_1C2A90(unk_4F7EB8.sub_1AEC70());
        x8++;
    }
    q114 = dword_4F8288.sub_1C2A90(arg_4);
    switch (dword_4FB9E0.get_game_type())
    {
    case 1:
        m_10C = unk_4FBC50.sub_1C1C80(arg_0, x8, u108, 2, q114);
        break;
    case 2:
        m_10C = unk_4FBC50.sub_1C1C80(arg_0, x8, u108, 3, q114);
        break;
    case 4:
        m_10C = unk_4FBC50.sub_1C1C80(arg_0, x8, u108, 4, q114);
        break;
    case 8:
        m_10C = unk_4FBC50.sub_1C1C80(arg_0, x8, u108, 5, q114);
        break;
    case 16:
        m_10C = -1;
        break;
    }
    return m_10C;
}

// A respawn point from the server: kept (unk_294, unk_298) and flagged
// (unk_290) in a game type 1 when neither dword_4FBAA4 nor dword_4FBAA8 is
// set.
// match: ?sub_1AD6B0@@YAXHHPAUtype_3DA44C@@@Z @ 0x001AD6B0
void sub_1AD6B0(RwInt32 arg_0, RwInt32 arg_4, type_3DA44C *arg_8)
{
    type_3E10EC *m = (type_3E10EC *)arg_8;

    sub_1A8A70(&unk_4F7EB8, "(CLIENT) Valid respawn point received #%d\n", m->unk_04);
    if (((kujuUI::type_1C8DF0_104_00 *)&dword_4FB9E0)->sub_1E3480() != 1 || dword_4FB9E0.get_unk_C8() || dword_4FB9E0.get_unk_C4())
    {
        return;
    }
    unk_4F7EB8.unk_294 = m->unk_04;
    unk_4F7EB8.unk_298 = m->unk_08;
    unk_4F7EB8.unk_290 = 1;
}

// match: ?sub_1AD730@type_4F7EB8@@QAEHXZ @ 0x001AD730
RwInt32 type_4F7EB8::sub_1AD730()
{
    // A compiled-out check (docs/toolchain.md): the registers after it are
    // one load on.
    if (!unk_4FC)
    {
    }
    return unk_1A4->sub_1B91B0();
}

// Peer arg_4 died from the bullet of player unk_0D: shown
// ("MW_GEN_KILLS_GUN" with both names, or "MW_GEN_SUICIDE"), its remote
// player told, counted and its pickups dropped when not hosting, and its
// remote player kept for the kill cam.
// match: ?sub_1AD750@@YAXHHPAUtype_3DA44C@@@Z @ 0x001AD750
// match: __ehhandler$?sub_1AD750@@YAXHHPAUtype_3DA44C@@@Z-0x16 @ 0x00302B20
// match: __ehhandler$?sub_1AD750@@YAXHHPAUtype_3DA44C@@@Z @ 0x00302B36
void sub_1AD750(RwInt32 arg_0, RwInt32 arg_4, type_3DA44C *arg_8)
{
    // The locals' names state their slots (docs/toolchain.md).
    RwChar lv_114[0x100];
    type_3E114C *var118 = (type_3E114C *)arg_8;

    sub_1A8A70(&unk_4F7EB8, "Player %d died from bullet fired by player %d\n", arg_4, var118->unk_0D);
    dword_4F8288.sub_1C28F0(arg_4, 1, 1);
    if (((kujuUI::type_1C8DF0_104_00 *)&dword_4FB9E0)->sub_1E3480() != 1 || dword_4FB9E0.get_unk_C8() || dword_4FB9E0.get_unk_C4())
    {
        return;
    }
    if (arg_4 != var118->unk_0D)
    {
        sub_1CB0F0(lv_114, sub_E3970("MW_GEN_KILLS_GUN", 1).c_str(),
                   type_4F8054::get()->get_unk_B0()->unk_90[var118->unk_0D].unk_00,
                   type_4F8054::get()->get_unk_B0()->unk_90[arg_4].unk_00);
    }
    else
    {
        sub_1CB000(lv_114, sub_E3970("MW_GEN_SUICIDE", 1).c_str(),
                   type_4F8054::get()->get_unk_B0()->unk_90[arg_4].unk_00);
    }
    show_message(lv_114);
    // A compiled-out check: the registers after it are two loads on.
    if (!var118->unk_0D)
    {
    }
    type_4F7EB8_1F0 *lv_10 = unk_4F7EB8.unk_1F0[arg_4];
    if (lv_10)
    {
        type_75600 loc148;

        loc148.unk_24 = var118->unk_0C;
        loc148.unk_28 = var118->unk_04;
        loc148.unk_2C = var118->unk_04;
        loc148.unk_0C = unk_4F7EB8.sub_1AECA0(var118->unk_0D, 0);
        lv_10->pvf_018(&loc148);
    }
    if (!hosting())
    {
        unk_4F7EB8.unk_04.sub_1B2D00(arg_4, var118->unk_0D, 0);
        if (lv_10 && unk_4F7EB8.unk_2A4 != 4)
        {
            unk_4F7EB8.sub_1ADB80(var118->unk_10, arg_4);
        }
    }
    // Compiled-out checks (docs/toolchain.md): the hosting test shrinks
    // the frame (inline budget), the remote-player ones each move the
    // registers one load on.
    if (!hosting())
    {
    }
    if (unk_4F7EB8.unk_2A4 != 4)
    {
        if (!unk_4F7EB8.unk_1F0[arg_4])
        {
        }
        if (unk_4F6B00[arg_4].is_visible())
        {
            if (!unk_4F7EB8.unk_1F0[arg_4])
            {
            }
            unk_4F6B00[arg_4].sub_1A63E0();
            unk_4F7EB8.sub_1AB2C0();
        }
        if (unk_4F7EB8.unk_1F0[arg_4])
        {
            if (!unk_4F7EB8.unk_1F0[arg_4])
            {
            }
            unk_4F6B00[arg_4].sub_1A6460();
            unk_4F7EB8.unk_238[arg_4] = unk_4F7EB8.unk_1F0[arg_4];
            unk_4F7EB8.unk_1F0[arg_4] = 0;
        }
        unk_4F7EB8.sub_73D90(var118->unk_0D, arg_4);
    }
}

// match: ?sub_1ADB40@type_4F7EB8@@QAEXH@Z @ 0x001ADB40
void type_4F7EB8::sub_1ADB40(RwInt32 arg_0)
{
    unk_2B8 = arg_0;
    if (arg_0 == unk_4F7EB8.sub_1AEC70())
        dword_4F83D8 = 1;
    else
        dword_4F83D8 = 0;
}

// Drops two pickups where player arg_4 (the local one for 0) died: one of
// the kind arg_0 (9 of it for kinds 16 and 17, else 100) twenty units to its
// right, and 50 of kind 75 twenty units to its left; each sent to the peers
// and taken.
// match: ?sub_1ADB80@type_4F7EB8@@QAEXHH@Z @ 0x001ADB80
void type_4F7EB8::sub_1ADB80(RwInt32 arg_0, RwInt32 arg_4)
{
    // The locals' names state their slots (docs/toolchain.md).
    type_3E111C w24;
    type_1DDE20_mask slot_30;
    RwV3d *t2C;
    RwMatrix *bp_4;
    RwInt32 l28;
    type_4F7EB8_1F0 *x8;

    // Two compiled-out checks (docs/toolchain.md): the registers after them
    // are two loads on.
    if (!unk_4FC)
    {
    }
    if (!unk_4FC)
    {
    }
    if (!arg_4)
    {
        t2C = unk_4F7EB8.unk_1A4->vf_0CC();
        bp_4 = unk_4F7EB8.unk_1A4->sub_1C05B0();
    }
    else
    {
        x8 = unk_4F7EB8.unk_1F0[arg_4];
        t2C = x8->vf_0CC();
        bp_4 = x8->sub_1C05B0();
    }
    slot_30 = get_unk_19C()->get_unk_B0()->sub_1A8050();
    l28 = dword_4FBB20.sub_1BDAD0();
    if (l28 != -1)
    {
        w24.unk_04 = l28;
        w24.unk_08 = arg_0;
        if (arg_0 == 16 || arg_0 == 17)
        {
            w24.unk_0C = 9;
        }
        else
        {
            w24.unk_0C = 100;
        }
        w24.unk_10.unk_00 = t2C->x + bp_4->right.x * 20.0f;
        w24.unk_10.unk_04 = t2C->y + bp_4->right.y * 20.0f;
        w24.unk_10.unk_08 = t2C->z + bp_4->right.z * 20.0f;
        dword_4F8058->sub_1DDE20(&w24, slot_30);
        dword_4FBB20.sub_1BDD70(w24.unk_04, w24.unk_08, w24.unk_0C, &w24.unk_10);
    }
    l28 = dword_4FBB20.sub_1BDAD0();
    if (l28 != -1)
    {
        w24.unk_04 = l28;
        w24.unk_08 = 75;
        w24.unk_0C = 50;
        w24.unk_10.unk_00 = t2C->x - bp_4->right.x * 20.0f;
        w24.unk_10.unk_04 = t2C->y - bp_4->right.y * 20.0f;
        w24.unk_10.unk_08 = t2C->z - bp_4->right.z * 20.0f;
        dword_4F8058->sub_1DDE20(&w24, slot_30);
        dword_4FBB20.sub_1BDD70(w24.unk_04, w24.unk_08, w24.unk_0C, &w24.unk_10);
    }
}

// Player arg_4 killed by a grenade (type_3E1164), on the same terms as the
// others: its team's state set, the kill written to the console
// ("MW_GEN_KILLS_THEMACCIDENT", "MW_GEN_KILLS_GREN" with both names, or
// "MW_GEN_SUICIDE"), its remote player given the blast (at the message's
// point, of its radius and damage), counted and its pickups dropped when not
// hosting, and, unless the manager's state is 4, its remote player kept for
// the kill cam.
// match: ?sub_1ADD90@@YAXHHPAUtype_3DA44C@@@Z @ 0x001ADD90
// match: __ehhandler$?sub_1ADD90@@YAXHHPAUtype_3DA44C@@@Z-0x29 @ 0x00302B40
// match: __ehhandler$?sub_1ADD90@@YAXHHPAUtype_3DA44C@@@Z @ 0x00302B69
void sub_1ADD90(RwInt32 arg_0, RwInt32 arg_4, type_3DA44C *arg_8)
{
    type_3E1164 *var_18 = (type_3E1164 *)arg_8;

    sub_1A8A70(&unk_4F7EB8, "Player %d killed by grenade thrown by player %d\n", arg_4, var_18->unk_18);
    dword_4F8288.sub_1C28F0(arg_4, 1, 1);
    if (((kujuUI::type_1C8DF0_104_00 *)&dword_4FB9E0)->sub_1E3480() != 1 || dword_4FB9E0.get_unk_C8() || dword_4FB9E0.get_unk_C4())
    {
        return;
    }
    RwChar var_158[0x100];

    if (arg_4 != var_18->unk_18)
    {
        const RwChar *var_2C = type_4F8054::get()->get_unk_B0()->unk_90[var_18->unk_18].unk_00;

        if (var_18->unk_18 == arg_4)
        {
            sub_1CB000(var_158, sub_E3970("MW_GEN_KILLS_THEMACCIDENT", 1).c_str(), var_2C);
        }
        else
        {
            const RwChar *var_164 = type_4F8054::get()->get_unk_B0()->unk_90[arg_4].unk_00;

            sub_1CB0F0(var_158, sub_E3970("MW_GEN_KILLS_GREN", 1).c_str(), var_2C, var_164);
        }
    }
    else
    {
        sub_1CB000(var_158, sub_E3970("MW_GEN_SUICIDE", 1).c_str(),
                   type_4F8054::get()->get_unk_B0()->unk_90[arg_4].unk_00);
    }
    sub_EACA0(var_158, 0, 0);
    // Two compiled-out checks (docs/toolchain.md): the registers after them
    // are two loads on.
    if (!var_18->unk_1C)
    {
    }
    if (!var_18->unk_1C)
    {
    }
    type_4F7EB8_1F0 *var_1C0 = unk_4F7EB8.unk_1F0[arg_4];

    if (var_1C0 && unk_4F7EB8.unk_2A4 != 4)
    {
        type_4AE70 var_1F4;
        RwMatrix var_240;

        var_1F4.unk_2C = var_18->unk_04;
        var_240.pos.x = var_18->unk_08.unk_00;
        var_240.pos.y = var_18->unk_08.unk_04;
        var_240.pos.z = var_18->unk_08.unk_08;
        var_1F4.unk_0C = &var_240;
        var_1F4.unk_10 = var_18->unk_14;
        var_1F4.unk_14 = var_18->unk_14;
        var_1F4.unk_18 = var_18->unk_14;
        var_1C0->pvf_020(&var_1F4);
    }
    if (!unk_4F61F8.unk_104)
    {
        unk_4F7EB8.unk_04.sub_1B2D00(arg_4, var_18->unk_18, 1);
        if (var_1C0 && unk_4F7EB8.unk_2A4 != 4)
        {
            unk_4F7EB8.sub_1ADB80(var_18->unk_1C, arg_4);
        }
    }
    if (unk_4F7EB8.unk_2A4 != 4)
    {
        unk_4F7EB8.sub_73D90(var_18->unk_18, arg_4);
        // A compiled-out check (docs/toolchain.md): the registers after it
        // are one load on.
        if (!var_18->unk_1C)
        {
        }
        if (unk_4F6B00[arg_4].is_visible())
        {
            unk_4F6B00[arg_4].sub_1A63E0();
            unk_4F7EB8.sub_1AB2C0();
        }
        // Another (docs/toolchain.md): one load on.
        if (!var_18->unk_1C)
        {
        }
        if (unk_4F7EB8.unk_1F0[arg_4])
        {
            unk_4F6B00[arg_4].sub_1A6460();
            // Another (docs/toolchain.md): one load on.
            if (!var_18->unk_1C)
            {
            }
            unk_4F7EB8.unk_238[arg_4] = unk_4F7EB8.unk_1F0[arg_4];
            unk_4F7EB8.unk_1F0[arg_4] = 0;
        }
    }
}

// match: ?sub_1AE250@@YAXHHPAUtype_3DA44C@@@Z @ 0x001AE250
void sub_1AE250(RwInt32 arg_0, RwInt32 arg_4, type_3DA44C *arg_8)
{
    type_3E117C *m = (type_3E117C *)arg_8;

    dword_4F8288.sub_1C28F0(arg_4, m->unk_04, 0);
    if (((kujuUI::type_1C8DF0_104_00 *)&dword_4FB9E0)->sub_1E3480() != 1 || dword_4FB9E0.get_unk_C8() || dword_4FB9E0.get_unk_C4())
    {
        return;
    }
    if (((kujuUI::type_1C8DF0_104_00 *)&dword_4FB9E0)->sub_1E3480() == 1)
    {
        sub_1A8A70(&unk_4F7EB8, "Player %d respawned\n", arg_4);
        unk_4F7EB8.sub_1AED80(arg_4, m->unk_04, m->unk_08);
    }
    else
    {
        sub_1A8A70(&unk_4F7EB8, "Player %d unable to be respawned because not in game\n", arg_4);
    }
}

// The round and game scores' handlers.
// match: ?sub_1AE300@@YAXHHPAUtype_3DA44C@@@Z @ 0x001AE300
void sub_1AE300(RwInt32 arg_0, RwInt32 arg_4, type_3DA44C *arg_8)
{
    // Four unused slots (docs/toolchain.md).
    unused_slot();
    unused_slot();
    unused_slot();
    unused_slot();
    sub_1A8A70(&unk_4F7EB8, "(CLIENT) Round score updated\n");
    // A compiled-out check (docs/toolchain.md): the registers after it are
    // one load on.
    if (!((type_3E1E3C *)arg_8)->unk_04[0])
    {
    }
    unk_4F7EB8.unk_04 = *(type_3E1E3C *)arg_8;
    sub_1C4C30(1);
}

// match: ??4type_3E1E3C@@QAEAAU0@ABU0@@Z @ 0x001AE340
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
type_3E1E3C &type_3E1E3C::operator=(const type_3E1E3C &arg_0)
{
    RwUInt32 bp_4;
    RwUInt32 x8;
    RwUInt32 locc;
    RwUInt32 ebp_10;

    for (bp_4 = 0; bp_4 < 0x10; bp_4++)
        unk_04[bp_4] = arg_0.unk_04[bp_4];
    for (x8 = 0; x8 < 0x10; x8++)
        unk_44[x8] = arg_0.unk_44[x8];
    for (locc = 0; locc < 0x10; locc++)
        unk_84[locc] = arg_0.unk_84[locc];
    for (ebp_10 = 0; ebp_10 < 2; ebp_10++)
        unk_C4[ebp_10] = arg_0.unk_C4[ebp_10];
    return *this;
}

// match: ?sub_1AE420@@YAXHHPAUtype_3DA44C@@@Z @ 0x001AE420
void sub_1AE420(RwInt32 arg_0, RwInt32 arg_4, type_3DA44C *arg_8)
{
    // Four unused slots (docs/toolchain.md).
    unused_slot();
    unused_slot();
    unused_slot();
    unused_slot();
    sub_1A8A70(&unk_4F7EB8, "(CLIENT) Game score updated\n");
    // A compiled-out check (docs/toolchain.md): the registers after it are
    // one load on.
    if (!((type_3E1FC4 *)arg_8)->unk_04[0])
    {
    }
    unk_4F7EB8.unk_D0 = *(type_3E1FC4 *)arg_8;
    sub_1C4C30(1);
}

// A chat line from peer arg_4, for the HUD's message line.
// match: ?sub_1AE460@@YAXHHPAUtype_3DA44C@@@Z @ 0x001AE460
void sub_1AE460(RwInt32 arg_0, RwInt32 arg_4, type_3DA44C *arg_8)
{
    sub_1A8A70(&unk_4F7EB8, "Received net chat\n");
    type_1A5EA0 *text = &((type_3E102C *)arg_8)->unk_04;
    sub_1C4E80(*text, arg_4);
}

// The voice status handler.
// match: ?sub_1AE4D0@@YAXHHPAUtype_3DA44C@@@Z @ 0x001AE4D0
void sub_1AE4D0(RwInt32 arg_0, RwInt32 arg_4, type_3DA44C *arg_8)
{
    type_3E0F54 *msg;
    type_3E3860 *voice;

    sub_1A8A70(&unk_4F7EB8, "Received receive Voice Status\n");
    msg = (type_3E0F54 *)arg_8;
    voice = dword_4F8180;
    voice->unk_3060.sub_1C7840(arg_4, msg, 0);
}

// match: ??0type_3E1134@@QAE@ABU0@@Z @ 0x001AE880

// Tells the peers of the pickup arg_0 (by its handle), and the pickups.
// match: ?sub_1AE520@type_4F7EB8@@QAEXPAUtype_1AE520@@@Z @ 0x001AE520
void type_4F7EB8::sub_1AE520(type_1AE520 *arg_0)
{
    // The locals' names state their slots (docs/toolchain.md).
    type_1DDE20_mask rC;
    type_3E1104 bp_8;

    // Two compiled-out checks (docs/toolchain.md): the registers after them
    // are two loads on.
    if (!unk_4FC)
    {
    }
    if (!unk_4FC)
    {
    }
    bp_8.unk_04 = arg_0->get_unk_3D0();
    rC = get_unk_19C()->get_unk_B0()->sub_1A8050();
    dword_4F8058->sub_1DDE20(&bp_8, rC);
    dword_4FBB20.sub_1BDD20(arg_0->get_unk_3D0());
}

// match: ?sub_1AE5C0@@YAXHHPAUtype_3DA44C@@@Z @ 0x001AE5C0
void sub_1AE5C0(RwInt32 arg_0, RwInt32 arg_4, type_3DA44C *arg_8)
{
    type_3E1104 m = *(type_3E1104 *)arg_8;

    if (((kujuUI::type_1C8DF0_104_00 *)&dword_4FB9E0)->sub_1E3480() != 1 || dword_4FB9E0.get_unk_C8() || dword_4FB9E0.get_unk_C4())
    {
        return;
    }
    if (((kujuUI::type_1C8DF0_104_00 *)&dword_4FB9E0)->sub_1E3480() != 1)
    {
        return;
    }
    dword_4FBB20.sub_1BDD20(m.unk_04);
}

// match: ?sub_1AE650@@YAXHHPAUtype_3DA44C@@@Z @ 0x001AE650
void sub_1AE650(RwInt32 arg_0, RwInt32 arg_4, type_3DA44C *arg_8)
{
    type_3E111C m = *(type_3E111C *)arg_8;

    if (((kujuUI::type_1C8DF0_104_00 *)&dword_4FB9E0)->sub_1E3480() != 1 || dword_4FB9E0.get_unk_C8() || dword_4FB9E0.get_unk_C4())
    {
        return;
    }
    if (((kujuUI::type_1C8DF0_104_00 *)&dword_4FB9E0)->sub_1E3480() != 1)
    {
        return;
    }
    dword_4FBB20.sub_1BDD70(m.unk_04, m.unk_08, m.unk_0C, &m.unk_10);
}

// Tells the peers of the swap of the pickup arg_0, and the pickups.
// match: ?sub_1AE750@type_4F7EB8@@QAEXPAUtype_1AE520@@II@Z @ 0x001AE750
void type_4F7EB8::sub_1AE750(type_1AE520 *arg_0, RwUInt32 arg_4, RwUInt32 arg_8)
{
    // The locals' names state their slots (docs/toolchain.md).
    type_1DDE20_mask rC;
    type_3E1134 bp_8;

    // Two compiled-out checks (docs/toolchain.md): the registers after them
    // are two loads on.
    if (!unk_4FC)
    {
    }
    if (!unk_4FC)
    {
    }
    if (CODFH_DEBUG_LOGS)
    {
        sub_1C8A30("Send swap pickup\n");
    }
    bp_8.unk_04 = arg_0->get_unk_3D0();
    bp_8.unk_08 = arg_4;
    bp_8.unk_0C = arg_8;
    rC = get_unk_19C()->get_unk_B0()->sub_1A8050();
    dword_4F8058->sub_1DDE20(&bp_8, rC);
    dword_4FBB20.sub_1BDE70(arg_0->get_unk_3D0(), arg_4, arg_8);
}

// match: ??0type_3E111C@@QAE@ABU0@@Z @ 0x001AE6C0

// match: ?sub_1AE810@@YAXHHPAUtype_3DA44C@@@Z @ 0x001AE810
void sub_1AE810(RwInt32 arg_0, RwInt32 arg_4, type_3DA44C *arg_8)
{
    type_3E1134 m = *(type_3E1134 *)arg_8;

    if (((kujuUI::type_1C8DF0_104_00 *)&dword_4FB9E0)->sub_1E3480() != 1 || dword_4FB9E0.get_unk_C8() || dword_4FB9E0.get_unk_C4())
    {
        return;
    }
    if (CODFH_DEBUG_LOGS)
    {
        sub_1C8A30("Received swap pickup\n");
    }
    dword_4FBB20.sub_1BDE70(m.unk_04, m.unk_08, m.unk_0C);
}

// A grenade thrown by peer arg_4 (type_3E11AC), on the same terms and not
// while the manager's state is 4: thrown (sub_15F2C0, flags 0x401) from the
// thrower's entity at the message's position with its velocity, with the
// weapon's projectile settings (table 2: its damage, spawned object and the
// values for the throw's hand, unk_1C) in a static record.
// match: ?sub_1AE8F0@@YAXHHPAUtype_3DA44C@@@Z @ 0x001AE8F0
// match: __ehhandler$?sub_1AE8F0@@YAXHHPAUtype_3DA44C@@@Z-0xE @ 0x00302B80
// match: __ehhandler$?sub_1AE8F0@@YAXHHPAUtype_3DA44C@@@Z @ 0x00302B8E
void sub_1AE8F0(RwInt32 arg_0, RwInt32 arg_4, type_3DA44C *arg_8)
{
    sub_1A8A70(&unk_4F7EB8, "Player %d threw a grenade\n", arg_4);
    if (((kujuUI::type_1C8DF0_104_00 *)&dword_4FB9E0)->sub_1E3480() != 1 || dword_4FB9E0.get_unk_C8() || dword_4FB9E0.get_unk_C4()
        || unk_4F7EB8.unk_2A4 == 4)
    {
        return;
    }
    type_3E11AC *m = (type_3E11AC *)arg_8;
    RwInt32 v_20 = 0x401;
    RwMatrix v_60;
    RwV3d v_6C;

    v_60.up.x = 0;
    v_60.up.y = 1.0f;
    v_60.up.z = 0;
    v_60.at.x = 0;
    v_60.at.y = 0;
    v_60.at.z = 1.0f;
    v_60.right.x = 1.0f;
    v_60.right.y = 0;
    v_60.right.z = 0;
    // Two compiled-out checks (docs/toolchain.md): the registers after them
    // are two loads on.
    if (!m->unk_1C)
    {
    }
    if (!m->unk_1C)
    {
    }
    v_60.pos.x = m->unk_04.unk_00;
    v_60.pos.y = m->unk_04.unk_04;
    v_60.pos.z = m->unk_04.unk_08;
    v_6C.x = m->unk_10.unk_00;
    v_6C.y = m->unk_10.unk_04;
    v_6C.z = m->unk_10.unk_08;
    static type_F4890_blast unk_4F83F0;

    memset(&unk_4F83F0, 0, sizeof(unk_4F83F0));
    type_4C19C0 *v_70 = sub_119B70(m->unk_20);

    unk_4F83F0.unk_00 = 2;
    unk_4F83F0.unk_04_r = (RwReal)(RwUInt32)v_70->unk_C4;
    unk_4F83F0.unk_38 = projectile_object(sub_198800(&v_70->unk_00));
    unk_4F83F0.unk_3C = 1;
    unk_4F83F0.unk_40 = v_70->unk_C0;
    unk_4F83F0.unk_44_r = v_70->unk_498_a[m->unk_1C];
    unk_4F83F0.unk_48 = v_70->unk_4AC_a[m->unk_1C];
    unk_4F83F0.unk_4C_r = v_70->unk_D0;
    unk_4F83F0.unk_50.unk_00_r = v_70->unk_4B4;
    unk_4F83F0.unk_50.unk_04 = v_70->unk_4B8;
    unk_4F83F0.unk_50.unk_08 = v_70->unk_4BC;
    unk_4F83F0.unk_50.unk_10 = v_70->unk_4C4;
    unk_4F83F0.unk_50.unk_0C = v_70->unk_4C0;
    unk_4F83F0.unk_50.unk_14 = v_70->unk_4C8;
    unk_4F83F0.unk_50.unk_18_r = v_70->unk_4CC;
    sub_15F2C0(v_20, (RwInt32)unk_4F7EB8.sub_1AECA0(arg_4, 0), &v_60, &v_6C, 0, (type_439A48 *)&unk_4F83F0,
               0);
}

// A bomb site's state from peer arg_4, taken in a game type 1 when neither
// dword_4FBAA4 nor dword_4FBAA8 is set.
// match: ?sub_1AEB90@@YAXHHPAUtype_3DA44C@@@Z @ 0x001AEB90
void sub_1AEB90(RwInt32 arg_0, RwInt32 arg_4, type_3DA44C *arg_8)
{
    type_3E0FCC *m = (type_3E0FCC *)arg_8;

    if (((kujuUI::type_1C8DF0_104_00 *)&dword_4FB9E0)->sub_1E3480() != 1 || dword_4FB9E0.get_unk_C8() || dword_4FB9E0.get_unk_C4())
    {
        return;
    }
    unk_4F8184.sub_1A80B0(m);
}

// A flag's state from peer arg_4, on the same terms.
// match: ?sub_1AEBE0@@YAXHHPAUtype_3DA44C@@@Z @ 0x001AEBE0
void sub_1AEBE0(RwInt32 arg_0, RwInt32 arg_4, type_3DA44C *arg_8)
{
    type_3E0FB4 *m = (type_3E0FB4 *)arg_8;

    if (((kujuUI::type_1C8DF0_104_00 *)&dword_4FB9E0)->sub_1E3480() != 1 || dword_4FB9E0.get_unk_C8() || dword_4FB9E0.get_unk_C4())
    {
        return;
    }
    unk_4F7EB8.unk_384.sub_1B1DE0(m);
}

// match: ?sub_1AEC30@@YAXHHPAUtype_3DA44C@@@Z @ 0x001AEC30
void sub_1AEC30(RwInt32 arg_0, RwInt32 arg_4, type_3DA44C *arg_8)
{
    type_3E0F9C *m = (type_3E0F9C *)arg_8;

    // Compiled-out checks (docs/toolchain.md): the first needs a fourth
    // register (the saved esi), and the registers after them are two loads
    // on.
    if (m->unk_10[m->unk_04] == m->unk_10[m->unk_06])
    {
    }
    if (!m->unk_0C)
    {
    }
    if (!m->unk_0C)
    {
    }
    if (unk_4F6B00[m->unk_0A].sub_32260(m))
    {
        unk_4F7EB8.sub_1AEC70();
    }
}

// match: ?sub_1AEC70@type_4F7EB8@@QAEHXZ @ 0x001AEC70
RwInt32 type_4F7EB8::sub_1AEC70()
{
    return unk_19C->get_unk_B0()->sub_1CFF90();
}

// match: ?sub_1AECA0@type_4F7EB8@@QAEPAUtype_3D3548@@IH@Z @ 0x001AECA0
type_3D3548 *type_4F7EB8::sub_1AECA0(RwUInt32 arg_0, RwInt32 arg_4)
{
    if (arg_0 >= 16)
    {
        return 0;
    }
    if (arg_0 == sub_1AEC70())
    {
        // A compiled-out check (docs/toolchain.md): the registers after it
        // are one load on.
        if (!unk_4FC)
        {
        }
        return unk_1A4;
    }
    if (!unk_1F0[arg_0] && arg_4)
    {
        if (unk_238[arg_0] && !(unk_238[arg_0]->unk_28 & 1))
        {
            return unk_238[arg_0];
        }
        return 0;
    }
    return unk_1F0[arg_0];
}

// match: ?sub_1AED30@type_4F7EB8@@QAEXXZ @ 0x001AED30
void type_4F7EB8::sub_1AED30()
{
    // A compiled-out check (docs/toolchain.md): the registers after it are
    // one load on.
    if (!unk_4FC)
    {
    }
    unk_284 = 1;
}

// match: ?sub_1AED50@type_4F7EB8@@QAEHXZ @ 0x001AED50
RwInt32 type_4F7EB8::sub_1AED50()
{
    cXboxLive *net;

    net = sub_1D8810();
    return net->unk_3DAC & 8;
}

// Respawns peer arg_0 (team arg_4, spawn point arg_8 or -1): its old remote
// player kept in unk_238 (or unk_238's one removed when no other peer has
// it and it is not flagged), unk_27C set up from the spawn table and named
// after the peer, and a new remote player made and shown, its network part
// given the session.
// match: ?sub_1AED80@type_4F7EB8@@QAEXHII@Z @ 0x001AED80
void type_4F7EB8::sub_1AED80(RwInt32 arg_0, RwUInt32 arg_4, RwUInt32 arg_8)
{
    if (unk_1F0[arg_0])
    {
        PLAYER_STATE_CHECK(unk_2A4);
        if (unk_4F6B00[arg_0].is_visible())
        {
            PLAYER_STATE_CHECK(unk_2A4);
            PLAYER_STATE_CHECK(unk_2A4);
            unk_4F6B00[arg_0].sub_1A63E0();
            unk_4F7EB8.sub_1AB2C0();
        }
        unk_4F6B00[arg_0].sub_1A6460();
        unk_238[arg_0] = unk_1F0[arg_0];
        sub_D5A60(unk_1F0[arg_0], 0);
        unk_1F0[arg_0] = 0;
    }
    else if (unk_238[arg_0])
    {
        bool found = false;
        for (RwInt32 i = 0; i < 16; i++)
        {
            if (unk_1F0[i] == unk_238[arg_0])
            {
                found = true;
            }
        }
        if (!found && !(unk_238[arg_0]->unk_28 & 1))
        {
            sub_D5A60(unk_238[arg_0], 0);
        }
    }
    if (unk_4F7EB8.unk_280)
    {
        unk_27C->unk_D8 = *unk_280->sub_1B7910(arg_4);
        unk_27C->unk_120 = *unk_280->sub_1B7970(arg_4, arg_8);
        unk_27C->unk_12C = 0;
        unk_27C->unk_128 = 0;
        if (arg_8 == -1)
        {
            unk_27C->unk_130 = unk_280->sub_1B79A0(arg_4, 0);
        }
        else
        {
            unk_27C->unk_130 = sub_1C5800(arg_8);
        }
        unk_27C->unk_134 = -1;
    }
    strcpy(unk_27C->unk_174, type_4F8054::get()->get_unk_B0()->unk_90[arg_0].unk_00);
    sub_D5D20(1);
    unk_1F0[arg_0] = unk_27C->vf_020();
    network_player(arg_0).sub_1A6420(unk_1F0[arg_0]);
    unk_1F0[arg_0]->pvf_010(unk_1A0);
    position_component(unk_27C->unk_60.pos.x) += 1.0f;
    position_component(unk_27C->unk_60.pos.y) -= 1000.0f;
    RwMatrixUpdate(&unk_27C->unk_60);
}

// Takes arg_0 as the local player: its network player lets the old one go
// and, when not hosting or once joined (state 7), drives the new one.
// match: ?sub_1AF0F0@type_4F7EB8@@QAEXPAUtype_17DBD0_player@@@Z @ 0x001AF0F0
void type_4F7EB8::sub_1AF0F0(type_17DBD0_player *arg_0)
{
    if (unk_1A4)
    {
        unk_4F6B00[get_1AEC70()].sub_1A6360();
    }
    unk_1A4 = arg_0;
    if (unk_4F61F8.unk_104 && unk_19C->get_unk_B0()->get_unk_310() == 7 || !unk_4F61F8.unk_104)
    {
        unk_4F6B00[get_1AEC70()].sub_1A6310(arg_0);
    }
}

// The player index of the entity arg_0: the local player's, a remote
// player's or unk_238's; -1 for none.
// match: ?sub_1AF1B0@type_4F7EB8@@QAEHPAUtype_3D3548@@@Z @ 0x001AF1B0
RwInt32 type_4F7EB8::sub_1AF1B0(type_3D3548 *arg_0)
{
    if (arg_0 == unk_1A4)
    {
        return sub_1AEC70();
    }
    for (RwUInt32 i = 0; i < 16; i++)
    {
        if (unk_1F0[i] && arg_0 == unk_1F0[i])
        {
            return i;
        }
        if (unk_238[i] && arg_0 == unk_238[i])
        {
            return i;
        }
    }
    return -1;
}

// match: ?sub_1AF250@type_4F7EB8@@QAEXXZ @ 0x001AF250
void type_4F7EB8::sub_1AF250()
{
    type_4F84B8 *log;

    log = sub_1B18D0();
    log->unk_34F0 = !log->unk_34F0;
}

// match: ?sub_1AF280@type_4F7EB8@@QAEHXZ @ 0x001AF280
RwInt32 type_4F7EB8::sub_1AF280()
{
    if (dword_4FB9E0.get_unk_08() == 1)
        return 1;
    return unk_29C == 4;
}

// match: ?sub_1AF2C0@@YAEH@Z @ 0x001AF2C0
RwUInt8 sub_1AF2C0(RwInt32 arg_0)
{
    RwUInt8 r;

    r = 0;
    switch (arg_0)
    {
    case 0:
        r = 2;
        break;
    case 1:
        r = 3;
        break;
    }
    return r;
}

// match: ?sub_1AF2F0@type_4F7EB8@@QAEHH@Z @ 0x001AF2F0
RwInt32 type_4F7EB8::sub_1AF2F0(RwInt32 arg_0)
{
    if (unk_280)
        return unk_280->sub_1B78E0(arg_0);
    return -1;
}

// The rules messages' handlers.
// match: ?sub_1AF320@@YAXHHPAUtype_3DA44C@@@Z @ 0x001AF320
void sub_1AF320(RwInt32 arg_0, RwInt32 arg_4, type_3DA44C *arg_8)
{
    type_3E1074 m = *(type_3E1074 *)arg_8;

    dword_4FB9E0.sub_1B5470(m);
}

// match: ?sub_1AF370@@YAXHHPAUtype_3DA44C@@@Z @ 0x001AF370
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void sub_1AF370(RwInt32 arg_0, RwInt32 arg_4, type_3DA44C *arg_8)
{
    type_3E1074 bp_4;
    type_1DDE20_mask x8;

    // Two compiled-out checks (docs/toolchain.md): the registers after them
    // are two loads on.
    if (!*(RwInt32 *)arg_8)
    {
    }
    if (!*(RwInt32 *)arg_8)
    {
    }
    if (!dword_4FB9E0.get_unk_C4() && !dword_4FB9E0.get_unk_C8() &&
        (((kujuUI::type_1C8DF0_104_00 *)&dword_4FB9E0)->sub_1E3480() == 1 || ((kujuUI::type_1C8DF0_104_00 *)&dword_4FB9E0)->sub_1E3480() == 2))
    {
        x8.unk_00 = 1 << arg_4;
        type_4F8058::get()->sub_1DDDB0(&bp_4, x8);
    }
}

// match: ?sub_1AF400@@YAXHHPAUtype_3DA44C@@@Z @ 0x001AF400
void sub_1AF400(RwInt32 arg_0, RwInt32 arg_4, type_3DA44C *arg_8)
{
    dword_4FB9E0.sub_1B5510(arg_4);
}

// match: ?sub_1AF420@@YAXHHPAUtype_3DA44C@@@Z @ 0x001AF420
void sub_1AF420(RwInt32 arg_0, RwInt32 arg_4, type_3DA44C *arg_8)
{
    type_3E1044 m = *(type_3E1044 *)arg_8;

    dword_4FB9E0.sub_1B6A30(m);
}

// match: ?sub_1AF470@@YAXHHPAUtype_3DA44C@@@Z @ 0x001AF470
void sub_1AF470(RwInt32 arg_0, RwInt32 arg_4, type_3DA44C *arg_8)
{
    type_3E0EB8 m = *(type_3E0EB8 *)arg_8;

    dword_4FB9E0.sub_1B6B30(m);
}

// match: ?sub_1AF4C0@@YAXHHPAUtype_3DA44C@@@Z @ 0x001AF4C0
void sub_1AF4C0(RwInt32 arg_0, RwInt32 arg_4, type_3DA44C *arg_8)
{
    type_3E0FE4 m = *(type_3E0FE4 *)arg_8;

    unk_4F7EB8.unk_490.sub_1C3520(m.unk_04, m.unk_08, m.unk_0C, m.unk_10);
}

// The message's copy constructor, compiler-made and out of line.
// match: ??0type_3E0FE4@@QAE@ABU0@@Z @ 0x001AF4F0

// match: ?sub_1AF570@@YAXHHPAUtype_3DA44C@@@Z @ 0x001AF570
void sub_1AF570(RwInt32 arg_0, RwInt32 arg_4, type_3DA44C *arg_8)
{
    type_3E0FFC m = *(type_3E0FFC *)arg_8;

    unk_4F7EB8.unk_490.sub_1C3900(m.unk_04, m.unk_08);
}

// match: ?sub_1AF5D0@@YAXHHPAUtype_3DA44C@@@Z @ 0x001AF5D0
void sub_1AF5D0(RwInt32 arg_0, RwInt32 arg_4, type_3DA44C *arg_8)
{
    type_3E1014 m = *(type_3E1014 *)arg_8;

    unk_4F7EB8.unk_490.sub_1C3B40(m.unk_04, m.unk_08, m.unk_0C);
}

// match: ??0type_3E1014@@QAE@ABU0@@Z @ 0x001AF600

// match: ?sub_1AF670@type_4F7EB8@@QAEHXZ @ 0x001AF670
RwInt32 type_4F7EB8::sub_1AF670()
{
    if (unk_4F61F8.unk_104 && unk_19C->get_unk_B0()->get_unk_310() == 7 && unk_19C->get_unk_04() == 5
        || !unk_4F61F8.unk_104 && unk_19C->get_unk_04() == 2)
    {
        return 1;
    }
    return 0;
}

// match: ?sub_1AF6F0@type_4F7EB8@@QAEXXZ @ 0x001AF6F0
void type_4F7EB8::sub_1AF6F0()
{
    sub_227560()->sub_2283F0(0);
    if (unk_19C->get_unk_B0()->sub_1CFFC0())
    {
        unk_504 = sub_1AEC70();
    }
    sub_1C4690();
    unk_19C->sub_1CCB10();
}

// match: ?sub_1AF750@type_4F7EB8@@QAEXABUtype_1CCA10@@HH@Z @ 0x001AF750
void type_4F7EB8::sub_1AF750(const type_1CCA10 &arg_0, RwInt32 arg_4, RwInt32 arg_8)
{
    if (byte_4F8478)
    {
        return;
    }
    byte_4F8478 = 1;
    type_4F8058 *session = dword_4F8058;
    unk_2C8->sub_1C6350();
    sub_227560()->sub_2266D0(arg_0);
    if (arg_4)
    {
        sub_19A750(0x28);
    }
    unk_19C->vf_00C(arg_0);
    if (arg_8)
    {
        session->sub_1DDFD0(arg_0);
    }
    byte_4F8478 = 0;
}

// match: ?sub_1AF7E0@type_4F7EB8@@QAEXXZ @ 0x001AF7E0
void type_4F7EB8::sub_1AF7E0()
{
    if (unk_234)
    {
        sub_1AFAF0(&unk_234->unk_C0);
    }
}

// match: ?sub_1AF810@type_4F7EB8@@QAEXH@Z @ 0x001AF810
void type_4F7EB8::sub_1AF810(RwInt32 arg_0)
{
    // A compiled-out check (docs/toolchain.md): the registers after it are
    // one load on.
    if (!unk_4FC)
    {
    }
    if (unk_1F0[arg_0])
    {
        sub_1AFAF0(&unk_1F0[arg_0]->unk_21AC);
    }
}

// Streams the peer arg_0's sections in: each collision-world slot holding
// none of them takes the next of theirs not yet in a slot (unloading its
// own unless that is still queued), and is queued to load. The last block's
// local names state their slots (docs/toolchain.md).
// match: ?sub_1AF850@type_4F7EB8@@QAEXH@Z @ 0x001AF850
void type_4F7EB8::sub_1AF850(RwInt32 arg_0)
{
    RwUInt32 next_index;
    RwUInt16 sections[4];

    // Two compiled-out checks (docs/toolchain.md): the registers after them
    // are two loads on.
    if (!unk_4FC)
    {
    }
    if (!unk_4FC)
    {
    }
    sub_82070(unk_1F0[arg_0]->unk_21AC.unk_00[0], unk_1F0[arg_0]->unk_21AC.unk_00[1],
              unk_1F0[arg_0]->unk_21AC.unk_00[2], unk_1F0[arg_0]->unk_21AC.unk_00[3]);
    for (RwUInt32 i = 0; i < 4; i++)
    {
        bool loaded = false;
        for (RwUInt32 j = 0; j < 4; j++)
        {
            if (dword_4E5D30[j].get_unk_08() == unk_1F0[arg_0]->unk_21AC.unk_00[i])
            {
                loaded = true;
            }
        }
        if (loaded)
        {
            sections[i] = 0xFFFF;
        }
        else
        {
            sections[i] = (RwUInt16)unk_1F0[arg_0]->unk_21AC.unk_00[i];
        }
    }
    next_index = 0;
    for (RwUInt32 i2 = 0; i2 < 4; i2++)
    {
        bool wanted = false;
        for (RwUInt32 j2 = 0; j2 < 4; j2++)
        {
            if (dword_4E5D30[i2].get_unk_08() == unk_1F0[arg_0]->unk_21AC.unk_00[j2])
            {
                wanted = true;
            }
        }
        if (!wanted)
        {
            RwUInt16 fp_34 = 0xFFFF;
            while (next_index < 4)
            {
                if (sections[next_index] != 0xFFFF)
                {
                    fp_34 = sections[next_index];
                    next_index++;
                    break;
                }
                next_index++;
            }
            // A compiled-out check (docs/toolchain.md): the registers after
            // it are one load on.
            if (!unk_4FC)
            {
            }
            type_4E5D30 *stk_2C = &dword_4E5D30[i2];
            RwUInt16 w3C = stk_2C->unk_08;
            RwUInt16 lv_30 = stk_2C->unk_0A;
            bool frm_35 = sub_82020(0, w3C);
            if (w3C != 0xFFFF && !frm_35)
            {
                // A compiled-out check (docs/toolchain.md): the registers
                // after it are one load on.
                if (!unk_4FC)
                {
                }
                sub_174030(lv_30, 0);
            }
            if (!frm_35)
            {
                stk_2C->unk_08 = fp_34;
                if (SectionInfo::sub_B0140())
                {
                    stk_2C->unk_04 = 1;
                }
                if (!sub_81FB0(0, "", fp_34))
                {
                    sub_16C220("Adding load of section %d to AsynchQueue...\n", fp_34);
                    sub_81EB0(0, "", fp_34);
                }
            }
        }
    }
}

// match: ?sub_1AFAF0@type_4F7EB8@@QAEXPBUtype_1AFAF0@@@Z @ 0x001AFAF0
void type_4F7EB8::sub_1AFAF0(const type_1AFAF0 *arg_0)
{
    if (!arg_0)
    {
        return;
    }
    if (!arg_0->unk_00[0] && !arg_0->unk_00[1] && !arg_0->unk_00[2] && !arg_0->unk_00[3])
    {
        return;
    }
    sub_1C58C0();
    dword_4B6850 = 1;
    // A compiled-out check (docs/toolchain.md): the registers after it are
    // one load on.
    if (!unk_4FC)
    {
    }
    dword_4B6840[0] = arg_0->unk_00[0];
    dword_4B6840[1] = arg_0->unk_00[1];
    dword_4B6840[2] = arg_0->unk_00[2];
    dword_4B6840[3] = arg_0->unk_00[3];
    sub_D8660();
}

// match: ?sub_1AFB70@type_4F7EB8@@QAEXXZ @ 0x001AFB70
void type_4F7EB8::sub_1AFB70()
{
    unk_2BC = dword_4F8288.sub_1C2440();
}

// match: ?sub_1AFB90@type_4F7EB8@@QAEXH@Z @ 0x001AFB90
void type_4F7EB8::sub_1AFB90(RwInt32 arg_0)
{
    unk_2C0 = arg_0;
}

// A checked copy of the peers mask, returned by value. Evidence:
// sub_1AA380 builds this return directly in the setter's argument slot.
// Its compiled-out mask check supplies the load between the copy's lea
// and its destination read (docs/toolchain.md). A reference-returning
// accessor cannot reproduce that order. The mutable input selects the
// unchecked mask copy; the helper supplies this call's own check.
inline type_1DDE20_mask voice_mask_copy(type_1DDE20_mask &arg_0)
{
    if (!arg_0.unk_00)
    {
    }
    return arg_0;
}

// Sets the voice peers (unk_4F7E90) to the mask arg_0, taken by value: an
// inline with no address, named for what it does. Evidence: the voice
// update (sub_1AA380) copies the mask in place through a `this` temporary
// and then stores the copy in unk_4F7E90.
inline void set_voice_peers(type_1DDE20_mask arg_0)
{
    unk_4F7E90 = arg_0;
}

// Tells the player (on the console, while a game or its peers are there)
// what they respawn with, and as which side outside the game type 1.
// match: ?sub_1AFBB0@type_4F7EB8@@QAEXXZ @ 0x001AFBB0
// match: __ehhandler$?sub_1AFBB0@type_4F7EB8@@QAEXXZ-0x47 @ 0x00302BA0
// match: __ehhandler$?sub_1AFBB0@type_4F7EB8@@QAEXXZ @ 0x00302BE7
void type_4F7EB8::sub_1AFBB0()
{
    type_1CB670 text;
    static type_1A5EA0 unk_4F8498 = sub_E3970("Allies", 0);
    static type_1A5EA0 unk_4F847C = sub_E3970("Axis", 0);

    if (dword_4FB9E0.get_unk_08() == 1)
    {
        text = sub_1CB7B0("RESPAWN_WITH%1", sub_1C43C0(unk_2BC, unk_2C0).c_str(), 0);
    }
    else
    {
        text = sub_1CB8B0("RESPAWN_AS%1_WITH%2", unk_2BC == 2 ? unk_4F8498.c_str() : unk_4F847C.c_str(),
                          sub_1C43C0(unk_2BC, unk_2C0).c_str(), 0);
    }
    if (unk_1A4 || unk_1A8)
    {
        sub_EACA0(text.c_str(), 0, 0);
    }
}

// match: ?sub_1AFF20@type_4F7EB8@@QAEXH@Z @ 0x001AFF20
void type_4F7EB8::sub_1AFF20(RwInt32 arg_0)
{
    unk_2BC = arg_0;
}

// Members /OPT:ICF folded into shared trivial bodies (config/aliases.txt): defined here for
// the authentic link (PLAN M7); the placement link takes the shared bodies.

// ?sub_15FB30@type_4F7EB8@@QAEXPAUtype_4F7EB8_1F0@@@Z (folded into the empty body at 0x15FB30)
void type_4F7EB8::sub_15FB30(type_4F7EB8_1F0 *arg_0)
{
}

// Functions /OPT:ICF folded into another body (config/aliases.txt), defined here for the
// authentic link (PLAN M7) with that body; the placement link takes the folded one.

// ?sub_73D90@type_4F7EB8@@QAEXHH@Z (folded into 0x73D90)
void type_4F7EB8::sub_73D90(RwInt32 arg_0, RwInt32 arg_4)
{
}

// ?vf_004@type_3E1044@@UAEXPAUtype_1F8560@@@Z (folded into 0x15FB30)
void type_3E1044::vf_004(struct type_1F8560 *arg_0)
{
}


// Functions /OPT:ICF folded into another body (config/aliases.txt), defined here for the
// authentic link (PLAN M7) with that body; the placement link takes the folded one.

// ?sub_1C4E80@@YAXUtype_1A5EA0@@H@Z (folded into 0x1C4E80)
void sub_1C4E80(struct type_1A5EA0 arg_0, RwInt32 arg_4)
{
}

// Functions /OPT:ICF folded into another body (config/aliases.txt), defined here for the
// authentic link (PLAN M7) with that body; the placement link takes the folded one.

// ?sub_19A750@@YAXXZ (folded into 0x19A750)
void sub_19A750()
{
}

#ifdef CODFH_PLAIN
// Plain builds (tools/plainbuild.py): these names are fields of the multiplayer manager in
// the image (0x4F7EB8 + offset); only the placement link gives them one storage, so any
// other link binds them here. Each offset is checked against the image address.
#include <stddef.h>
// (bound at start-up: the library initialization area runs before every game constructor)
#pragma warning(disable: 4073)
#pragma init_seg(lib)
class cNetSoldierTrigger;
typedef RwChar plain_check_dword_4F8054[offsetof(type_4F7EB8, unk_19C) == 0x19C ? 1 : -1];
type_4F8054 *&dword_4F8054 = unk_4F7EB8.unk_19C;
typedef RwChar plain_check_dword_4F8058[offsetof(type_4F7EB8, unk_1A0) == 0x1A0 ? 1 : -1];
type_4F8058 *&dword_4F8058 = unk_4F7EB8.unk_1A0;
typedef RwChar plain_check_dword_4F805C[offsetof(type_4F7EB8, unk_1A4) == 0x1A4 ? 1 : -1];
type_4F805C *&dword_4F805C = (type_4F805C *&)unk_4F7EB8.unk_1A4;
typedef RwChar plain_check_dword_4F8060[offsetof(type_4F7EB8, unk_1A8) == 0x1A8 ? 1 : -1];
type_1BABA0 *&dword_4F8060 = unk_4F7EB8.unk_1A8;
typedef RwChar plain_check_dword_4F80E8[offsetof(type_4F7EB8, unk_230) == 0x230 ? 1 : -1];
RwInt32 &dword_4F80E8 = unk_4F7EB8.unk_230;
typedef RwChar plain_check_dword_4F8130[offsetof(type_4F7EB8, unk_278) == 0x278 ? 1 : -1];
cNetPlayerTrigger *&dword_4F8130 = unk_4F7EB8.unk_278;
typedef RwChar plain_check_dword_4F8134[offsetof(type_4F7EB8, unk_27C) == 0x27C ? 1 : -1];
cNetSoldierTrigger *&dword_4F8134 = (cNetSoldierTrigger *&)unk_4F7EB8.unk_27C;
typedef RwChar plain_check_dword_4F8138[offsetof(type_4F7EB8, unk_280) == 0x280 ? 1 : -1];
cNetLevelParams *&dword_4F8138 = unk_4F7EB8.unk_280;
typedef RwChar plain_check_dword_4F8154[offsetof(type_4F7EB8, unk_29C) == 0x29C ? 1 : -1];
RwInt32 &dword_4F8154 = unk_4F7EB8.unk_29C;
typedef RwChar plain_check_dword_4F8180[offsetof(type_4F7EB8, unk_2C8) == 0x2C8 ? 1 : -1];
type_3E3860 *&dword_4F8180 = unk_4F7EB8.unk_2C8;
typedef RwChar plain_check_unk_4F8184[offsetof(type_4F7EB8, unk_2CC) == 0x2CC ? 1 : -1];
type_4F8184 &unk_4F8184 = unk_4F7EB8.unk_2CC;
typedef RwChar plain_check_dword_4F8288[offsetof(type_4F7EB8, unk_3D0) == 0x3D0 ? 1 : -1];
type_4F8288 &dword_4F8288 = unk_4F7EB8.unk_3D0;
#ifndef CODFH_WIN32
// (not on Win32: unk_490 holds a std::string, 0x1C bytes in the Xbox build's library and 0x18 in
// the port's, so the fields after it are 4 bytes lower; the reference binds by name either way)
typedef RwChar plain_check_dword_4F83D8[offsetof(type_4F7EB8, unk_520) == 0x520 ? 1 : -1];
#endif
RwInt32 &dword_4F83D8 = unk_4F7EB8.unk_520;
#endif
