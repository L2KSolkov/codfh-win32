// The game loop: its set-up and what it runs each frame (the image's
// "GameLoop Init ..." messages). The original file name is not in the
// image, so it is named for its start address.

#ifdef CODFH_SP
#include "game/xboxlive.h"      // first, for the XDK's headers: dword_4F3130 (sub_D6EB0's relaunch)
#endif
#include <stdio.h>

#include "rw/ostypes.h"
#include "rw/bamemory.h"
#include "rws/ceventhandler.h"
#include "rws/cattributehandler.h"
#include "game/data.h"
#include "game/functions.h"
#include "game/gameloop.h"
#include "game/waitscreen.h"
#include "types/asynchload.h"
#include "types/soundbank.h"
#include "types/LevelInfo.h"
#include "types/StartingSections.h"
#include "types/SectionInfo.h"
#include "types/type_72810.h"
#include "types/ccess.h"
#include "types/type_4B8EF0.h"
#include "types/vec4.h"
#include "types/CAnimPackSelector.h"
#include "types/type_4B85F8.h"
#include "types/musicplayer.h"
#include "types/type_3D3548.h"
#include "types/CShellLevelBehaviorClass.h"
#include "types/type_10F710.h"
#include "types/type_DC400.h"
#include <string.h>
#include "rw/baraster.h"
#ifdef CODFH_SP
#include "game/savestate.h"     // type_4F45F8
#include "game/levels.h"        // sub_19BE30
#include "game/movie.h"         // sub_19BAC0
#include "game/profiles.h"      // sub_1A2650
#include "game/platform.h"      // Width, Height, ZDepth
#include "types/type_3DD948.h"  // sub_D7C20's vehicle mode
#include "rws/camerahelper.h"
#endif

#ifdef CODFH_SP
// Single player's debug print is an empty inline: its format text is gone, but
// its arguments are still evaluated.
static inline void sp_debug_print(const RwChar *, ...) {}
#endif

// Its data definitions (PLAN M5), in the image's address order.
// 0x003D7334
extern const RwChar iMsgSparkStartSystem_name[] = "iMsgSparkStartSystem";
// 0x003D734C
extern const RwChar iMsgSparkStartGame_name[] = "iMsgSparkStartGame";
// 0x003D7360
extern const RwReal flt_3D7360 = 16.666666f;
// 0x003D7364
extern const RwChar iMsgSparkRestartSystemBegin_name[] = "iMsgSparkRestartSystemBegin";
// 0x003D7380
extern const RwChar iMsgSparkRestartSystemEnd_name[] = "iMsgSparkRestartSystemEnd";
// 0x003D739C
extern const RwChar iMsgSparkRestartStartGame_name[] = "iMsgSparkRestartStartGame";
#ifndef CODFH_SP // single player has neither 0.01f: "Game Restart END" follows the message names (SP 0x2E3614)
// 0x003D73B8
extern const RwReal flt_3D73B8 = 0.01f;
// 0x003D73BC
extern const RwReal flt_3D73BC = 0.01f;
#endif
// 0x004B86F8
RwUInt32 dword_4B86F8;
// 0x004B86FC
RwInt32 dword_4B86FC;
// 0x004B8700
RwInt32 dword_4B8700;
// 0x004B8704
RwInt32 dword_4B8704;
// 0x004B8708
RwInt32 dword_4B8708;
// 0x004B870C
RwInt32 dword_4B870C;
// 0x004B8710
RwInt32 dword_4B8710;
// 0x004B8714
RwInt32 dword_4B8714;
// 0x004B8718
RwInt32 dword_4B8718;
// 0x004B871C
RwInt32 dword_4B871C;
// 0x004B8720
RwInt32 dword_4B8720;
// 0x004B8724
RwInt32 dword_4B8724;
// 0x004B8728
RwInt32 dword_4B8728;
// 0x004B872C
RwInt32 dword_4B872C;
// 0x004B8730
RwUInt32 dword_4B8730;
// 0x004B8734
RwInt32 dword_4B8734;
// 0x004B8740
bool byte_4B8740;
// 0x004B8760
RwInt32 dword_4B8760;
// 0x004B8764
bool byte_4B8764;
// 0x004B8770
RwInt32 dword_4B8770;
// 0x004B8774
void *pData;
// 0x004B8778
RwInt32 dword_4B8778;
// 0x004B877C
RwInt32 dword_4B877C;
// 0x004B8780
RwInt32 dword_4B8780;
// 0x004B8784
RwUInt8 byte_4B8784;
// 0x004B8788
RwInt32 dword_4B8788[4];
// 0x004B87C8
RwReal dword_4B87C8;
// 0x004B87CC
RwUInt32 dword_4B87CC;
// 0x004B87D0
RwUInt32 dword_4B87D0;
// 0x004B87D4
RwUInt32 dword_4B87D4;
// 0x004B87D8
RwUInt32 dword_4B87D8;
// 0x004B87DC
RwInt32 dword_4B87DC;
// 0x004B87E0
RwInt32 dword_4B87E0;
// 0x004B87E8
RwInt32 Width;
// 0x004B87EC
RwInt32 Height;
// 0x004B87F0
RwInt32 dword_4B87F0;
// 0x004B87F4
RwInt32 dword_4B87F4;
// 0x004B87F8
RwInt32 ZDepth;
// 0x004B8890
RwInt32 dword_4B8890;
// 0x004B918C
#ifndef CODFH_PLAIN
RwInt32 dword_4B918C;
#endif
// 0x004C1941
RwUInt8 byte_4C1941;
// 0x004F2B68
type_4F2B68 unk_4F2B68;
// End of its data definitions.


// Globals with constructors defined here (their initializers and exit
// functions at the end of .text).
#ifdef CODFH_SP // single player's .data opens with it, before the statically initialized unk_4B8744 (SP 0x321508)
RwInt32 dword_42926C = 1;
#endif
type_D9CF0 unk_4B8744;
// An event id no code uses.
RWS::CEventId iMsgSparkStartSystem;
RWS::CEventId dword_4B8750;
type_3DF8D8_04 unk_4B8798[6];
// Its data (PLAN M5): literals, constants and tables where the image has them.
#ifdef CODFH_DRAW_TRIGGERS
// port/src/debug/trigtools.cpp: the debug tools' main-thread work
void TrigWebTick();
#endif
// match: ?iMsgSparkStartSystem_name@@3QBDB @ 0x003D7334
// match: ?iMsgSparkStartGame_name@@3QBDB @ 0x003D734C
// match: ?flt_3D7360@@3MB @ 0x003D7360
// match: ?iMsgSparkRestartSystemBegin_name@@3QBDB @ 0x003D7364
// match: ?iMsgSparkRestartSystemEnd_name@@3QBDB @ 0x003D7380
// match: ?iMsgSparkRestartStartGame_name@@3QBDB @ 0x003D739C
// match: ?flt_3D73B8@@3MB @ 0x003D73B8
// match: ?flt_3D73BC@@3MB @ 0x003D73BC
// match: ??_C@_0BG@OMJIPGLB@GameLoop?5Init?5END?4?4?4?4?$AA@ @ 0x003D73C0
// match: ??_C@_0BP@EDCMIHGA@GameLoop?5Init?5RWStudio?5end?4?4?4?4?$AA@ @ 0x003D73D8
// match: ??_C@_0DN@IDBHEDOJ@GameLoopInit?5RWStudio?3?5Memory?5fr@ @ 0x003D73F8
// match: ??_C@_0CB@EPAHJPBC@GameLoop?5Init?5RWStudio?5begin?4?4?4?4@ @ 0x003D7438
// match: ??_C@_0DE@FDBPBMAK@GameLoopInit?3?5Memory?5freed?5on?5Rw@ @ 0x003D745C
// match: ??_C@_0BN@HOFKEKAE@GameLoop?5Init?5BEGIN?4?4?4?4at?5?$CFd?$AA@ @ 0x003D7490
// match: ??_C@_0CL@GFEGKKIE@?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK@ @ 0x003D74B0
// match: ??_C@_0BO@FAOMCKAD@GameLoop?5Init?5Modules?5end?4?4?4?4?$AA@ @ 0x003D74DC
// match: ??_C@_0BO@FKOCIDDI@GameLoopInitModules?5begin?4?4?4?4?$AA@ @ 0x003D74FC
// match: ??_C@_0BE@NCALDIKD@Game?5Restart?5END?4?4?4?$AA@ @ 0x003D751C
// match: ??_C@_0BB@OMDAEHCO@Game?5Restart?5END?$AA@ @ 0x003D7530
// match: ??_C@_0DH@KLIGGEBI@checked?5in?$CJ?5and?5tell?5him?5that?5re@ @ 0x003D7544
// match: ??_C@_0DF@GDCGGHIC@programmer?5immediately?5?$CIespecial@ @ 0x003D757C
// match: ??_C@_0DF@LEPOGILO@MEMORY?5LEAK?5detected?5during?5shut@ @ 0x003D75B4
// match: ??_C@_0DH@OAAKCECH@?$CK?$CK?$CKALERT?$CBALERT?$CBALERT?$CBALERT?$CBALERT@ @ 0x003D75EC
// match: ??_C@_0BJ@PHILNLHL@Restart?3?5Tick?3?3Restart?$CI?$CJ?$AA@ @ 0x003D7624
// match: ??_C@_0CG@FIPHFHKP@Restart?3?5CProfiler?3?3RestartProfi@ @ 0x003D7640
// match: ??_C@_0CF@LOEKLOPC@Restart?3?5SerializeManager?3?3Resta@ @ 0x003D7668
// match: ??_C@_0CB@PDANEDDA@Restart?3?5LevelManager?3?3Restart?$CI?$CJ@ @ 0x003D7690
// match: ??_C@_0CI@HMCKPFOH@Restart?3?5TextureManager?3?3Restart@ @ 0x003D76B4
// match: ??_C@_0CC@OBIEKBOB@Restart?3?5CAnimDatabase?3?3Restart?$CI@ @ 0x003D76DC
// match: ??_C@_0CJ@DMGADCNE@Restart?3?5GodAssetManager?3?3Restar@ @ 0x003D7700
// match: ??_C@_0BP@NBPDMEDJ@Restart?3?5Audio?3?3RestartClass?$CI?$CJ?$AA@ @ 0x003D772C
// match: ??_C@_0CA@HNCKICNO@Restart?3?5shellManager?4Restart?$CI?$CJ?$AA@ @ 0x003D774C
// match: ??_C@_0CC@MGLIIHKJ@Restart?3?5SplineManager?3?3Restart?$CI@ @ 0x003D776C
// match: ??_C@_0CE@MJBEEAJM@Restart?3?5PathNodeManager?3?3Restar@ @ 0x003D7790
// match: ??_C@_0CD@GNDNKPGO@Restart?3?5TriggerManager?3?3Restart@ @ 0x003D77B4
// match: ??_C@_0CE@NCODNJKG@Restart?3?5ParticleManager?3?3Restar@ @ 0x003D77D8
// match: ??_C@_0CB@CKBOIPOL@Restart?3?5CloneManager?3?3Restart?$CI?$CJ@ @ 0x003D77FC
// match: ??_C@_0CB@NBIHMGLE@Restart?3?5DecalManager?3?3Restart?$CI?$CJ@ @ 0x003D7820
// match: ??_C@_0DC@JFODHFEP@Restart?3?5TriggeredParticleManage@ @ 0x003D7844
// match: ??_C@_0CE@HIFNKCLH@Restart?3?5CNPCWeapon?3?3RestartClas@ @ 0x003D7878
// match: ??_C@_0DC@LNAAIGCE@Restart?3?5CPlayerWeapon?3?3RestartP@ @ 0x003D789C
// match: ??_C@_0CF@JGELMCBN@Restart?3?5SectionInfo?3?3RestartCla@ @ 0x003D78D0
// match: ??_C@_0CH@CAMFHHHM@Restart?3?5PlayerTrigger?3?3RestartC@ @ 0x003D78F8
// match: ??_C@_0CK@OMCFDCPO@Restart?3?5StartingSections?3?3Resta@ @ 0x003D7920
// match: ??_C@_0CD@HNPEGKKK@Restart?3?5LevelInfo?3?3RestartClass@ @ 0x003D794C
// match: ??_C@_0CH@HDAGOOLN@Restart?3?5StreamClumpManager?3?3Res@ @ 0x003D7970
// match: ??_C@_0CI@BKHIFHLN@Restart?3?5CProjectileMgr?3?3Restart@ @ 0x003D7998
// match: ??_C@_0DE@IPGEFPBE@Restart?3?5ProjectileGeneratorMana@ @ 0x003D79C0
// match: ??_C@_0CI@IBMANGDB@Restart?3?5CAnimObjectMgr?3?3Restart@ @ 0x003D79F4
// match: ??_C@_0BN@OEMJKNJP@Restart?3?5Alfa?5class?5restarts?$AA@ @ 0x003D7A1C
// match: ??_C@_0BL@BIFDFFCL@Restart?3?5AI?5class?5restarts?$AA@ @ 0x003D7A3C
// match: ??_C@_0BG@BANMMENE@Game?5Restart?5BEGIN?4?4?4?$AA@ @ 0x003D7A58
// match: ??_C@_0CH@KBFANHBB@?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK?$CK@ @ 0x003D7A70
// match: ??_C@_0DI@HPAKPDOM@checked?5in?$CJ?5and?5tell?5him?5that?5re@ @ 0x003D7A98
// match: ??_C@_0BK@JHOAJDJL@GameLoop?5Shutdown?5END?4?4?4?4?$AA@ @ 0x003D7AD0
// match: ??_C@_0CD@HCJKECMM@GameLoop?5Shutdown?5RWStudio?5end?4?4@ @ 0x003D7AEC
// match: ??_C@_0CF@KGLLGLHO@GameLoop?5Shutdown?5RWStudio?5begin@ @ 0x003D7B10
// match: ??_C@_0BM@GKIEJLHP@GameLoop?5Shutdown?5BEGIN?4?4?4?4?$AA@ @ 0x003D7B38
// match: ??_C@_0CC@JPJIBCNA@GameLoop?5Shutdown?5modules?5end?4?4?4@ @ 0x003D7B54
// match: ??_C@_0CC@BCNDGBBM@GameLoopShutdownModules?5begin?4?4?4@ @ 0x003D7B78
// match: __ehhandler$?sub_D7C20@@YAXXZ>1>8 @ 0x0041CC74
// match: __ehhandler$?sub_D7C20@@YAXXZ>1 @ 0x0041CC7C
// match: .CRT$XCU+0 @ 0x00426FF8
// match: .CRT$XCU+4 @ 0x00426FFC
// match: .CRT$XCU+8 @ 0x00427000
// match: .CRT$XCU+12 @ 0x00427004

// match: _$E2 @ 0x0030B200
// match: _$E3 @ 0x0030E3E0
// match: _$E5 @ 0x0030B230
// match: _$E6 @ 0x0030E3F0
// match: _$E8 @ 0x0030B250
// match: _$E9 @ 0x0030E400
// match: _$E11 @ 0x0030B270
// match: ?sub_D6640@@YAHXZ @ 0x000D6640
// sp-match: _$E5 @ 0x0021D540
// sp-match: _$E8 @ 0x0021D560
// sp-match: _$E6 @ 0x0021E810
// sp-match: _$E9 @ 0x0021E820
// sp-match: ?sub_D6640@@YAHXZ @ 0x000A2B80

// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
RwInt32 sub_D6640()
{
    RwInt32 var_8;
    RwInt32 l4;

#if !defined(CODFH_SP) || defined(CODFH_SP_LOGS)
    sub_19A750(" ");
    sub_19A750(" ");
    sub_19A750("******************************************");
#endif
#if defined(CODFH_SP) && !defined(CODFH_SP_LOGS)
    sp_debug_print("", RWS::Time::GetTime());
#else
    sub_19A750("GameLoop Init BEGIN....at %d", RWS::Time::GetTime());
#endif
#if !defined(CODFH_SP) || defined(CODFH_SP_LOGS)
    sub_19A750("******************************************");
#endif
#ifndef CODFH_SP // single player has no call here (SP 0xA2B85 goes on to the purge)
    sub_1A2D80();
#endif
    l4 = RwFreeListPurgeAllFreeLists();
#if !defined(CODFH_SP) || defined(CODFH_SP_LOGS)
    sub_19A750("GameLoopInit: Memory freed on RwFreeList purge - %d", l4);
#endif
    dword_4B8718 = 0;
    sub_19A750();
    var_8 = 1;
    if (sub_31DB0())
    {
#if !defined(CODFH_SP) || defined(CODFH_SP_LOGS)
        sub_19A750("GameLoop Init RWStudio begin....");
#endif
        RWS::MainLoop::Open(Width, Height, ZDepth);
        RWS::CEventHandler::RegisterMsg(iMsgSparkStartSystem, iMsgSparkStartSystem_name, 0);
        RWS::CEventHandler::RegisterMsg(dword_4B8750, iMsgSparkStartGame_name, 0);
        RWS::CEventHandler::RegisterMsg(dword_4B67B8, iMsgSparkRestartSystemBegin_name, 0);
        RWS::CEventHandler::RegisterMsg(dword_4B67C0, iMsgSparkRestartSystemEnd_name, 0);
        RWS::CEventHandler::RegisterMsg(dword_4B67B0, iMsgSparkRestartStartGame_name, 0);
        l4 = RwFreeListPurgeAllFreeLists();
#if !defined(CODFH_SP) || defined(CODFH_SP_LOGS)
        sub_19A750("GameLoopInit RWStudio: Memory freed on RwFreeList purge - %d", l4);
        sub_19A750("GameLoop Init RWStudio end....");
#endif
        var_8 = sub_D6820(0);
        var_8 = sub_19CF10();
        if (var_8 && sub_D8B90())
        {
            dword_4B86F8 = 0;
            dword_4B86F8 |= 1;
        }
        sub_124E90();
    }
    else
    {
        var_8 = 0;
    }
#if !defined(CODFH_SP) || defined(CODFH_SP_LOGS)
    sub_19A750("******************************************");
    sub_19A750("GameLoop Init END....");
    sub_19A750("******************************************");
    sub_19A750(" ");
    sub_19A750(" ");
#endif
    dword_4B88B0 = 0;
    return var_8;
}

// match: ?sub_D6820@@YAHH@Z @ 0x000D6820
// sp-match: ?sub_D6820@@YAHH@Z @ 0x000A2380
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
RwInt32 sub_D6820(RwInt32 arg_0)
{
    RwInt32 var_8;
    RwInt32 l4;

#if !defined(CODFH_SP) || defined(CODFH_SP_LOGS)
    sub_19A750("GameLoopInitModules begin....");
#endif
    RwFreeListPurgeAllFreeLists();
    l4 = 1;
    var_8 = 0;
    sub_D95A0();
    sub_16D3A0();
    sub_174950();
    sub_F25F0();
    dword_4B2550.unk_00 = 0;
    dword_4B2550.unk_04 = 0;
    dword_4B2550.unk_08 = 0;
    sub_1446B0();
    sub_811C0();
    sub_171DC0();
    sub_770C0();
    sub_198390();
    sub_83280();
    sub_F1190();
    sub_17E290();
    if (var_8 |= 4)
    {
        dword_4B8EF0.sub_E9790(var_8, dword_4E5CBC);
    }
    unk_4E5CC8.sub_144310();
    sub_F7F60();
    sub_143CE0();
    sub_144990();
    RpPrtStdEmitterCreatePTank();
    sub_122FB0();
    sub_F2920();
    sub_F47F0();
    sub_15C790();
    sub_116310();
    LevelInfo::sub_C5C10();
    StartingSections::sub_B05C0();
    sub_AA3F0();
    SectionInfo::sub_AFD70();
    sub_15F1B0();
    sub_122230();
    sub_786A0();
    sub_672F0();
    sub_67B10();
    sub_72810();
    sub_71360();
    sub_6B3B0();
    sub_42990();
    sub_73360();
    sub_32E50();
    sub_19A750();
    sub_34FA0();
    sub_40720();
    sub_3C1D0();
    sub_3CBF0();
    sub_31AD0();
    sub_3EC40();
    sub_16D10();
    sub_FB4F0();
    sub_8AB60();
    sub_141BB0();
    sub_17D240();
    dword_4B86FC = 0;
    sub_16FF90();
    sub_17C430();
    sub_125A50();
    sub_16F160();
    sub_16FC80();
    sub_E8800();
    unk_4F2B68.pDtor();
    sub_186720();
    sub_19AAB0();
    dword_4B8700 = 0;
    dword_4B8704 = 0;
    dword_4B8708 = 0;
    dword_4B870C = 0;
    dword_4B8710 = 0;
    dword_4B8714 = 0;
    dword_4B8778 = 0;
    dword_4B8720 = 0;
    dword_4B8724 = 0;
    dword_4B8728 = 0;
    dword_4B8734 = 0;
    RwFreeListPurgeAllFreeLists();
    unk_4E73A8.sub_183130();
#if !defined(CODFH_SP) || defined(CODFH_SP_LOGS)
    sub_19A750("GameLoop Init Modules end....");
#endif
    return l4;
}

// match: ?sub_D6A50@@YAXXZ @ 0x000D6A50
// sp-match: ?sub_D6A50@@YAXXZ @ 0x000A2540
void sub_D6A50()
{
#if !defined(CODFH_SP) || defined(CODFH_SP_LOGS)
    sub_19A750(" ");
    sub_19A750(" ");
    sub_19A750("**************************************");
    sub_19A750("Game Restart BEGIN...");
    sub_19A750("**************************************");
#endif
#ifndef CODFH_SP // single player has no call here (SP 0xA2540 starts with the count)
    sub_1A2D50();
#endif
    dword_4B8720++;
    dword_4B8734 = 2;
    sub_125E00();
    sub_D9450();
    sub_81300();
    unk_4B9308.sub_EEF90(0, 1);
    sub_1701B0();
    sub_17C4C0();
    sub_F1190();
    sub_17E2E0();
    sub_19A750();
    sub_17D280();
    sub_D5480();
    RWS::SendMsg(dword_4B67B8);
    sub_D9450();
    sub_8ACE0();
    sub_FB530();
    sub_16D50();
    sub_31B10();
    sub_3EC80();
    sub_3CC80();
#if !defined(CODFH_SP) || defined(CODFH_SP_LOGS)
    sub_19A750("Restart: AI class restarts");
#endif
    sub_3C220();
    sub_407C0();
    sub_35020();
    sub_19A750();
    sub_32EB0();
#if !defined(CODFH_SP) || defined(CODFH_SP_LOGS)
    sub_19A750("Restart: Alfa class restarts");
#endif
    sub_733A0();
    sub_429E0();
    sub_6B490();
    sub_714F0();
    sub_19A750();
    sub_19A750();
    sub_67340();
#if !defined(CODFH_SP) || defined(CODFH_SP_LOGS)
    sub_19A750("Restart: CAnimObjectMgr::RestartClass()");
#endif
    sub_78790();
#if !defined(CODFH_SP) || defined(CODFH_SP_LOGS)
    sub_19A750("Restart: ProjectileGeneratorManager::RestartClass()");
#endif
    sub_1222A0();
#if !defined(CODFH_SP) || defined(CODFH_SP_LOGS)
    sub_19A750("Restart: CProjectileMgr::RestartClass()");
#endif
    sub_15F240();
#if !defined(CODFH_SP) || defined(CODFH_SP_LOGS)
    sub_19A750("Restart: StreamClumpManager::Restart()");
#endif
    sub_16F1C0();
    sub_16FD10();
#if !defined(CODFH_SP) || defined(CODFH_SP_LOGS)
    sub_19A750("Restart: LevelInfo::RestartClass()");
#endif
    sub_19A750();
#if !defined(CODFH_SP) || defined(CODFH_SP_LOGS)
    sub_19A750("Restart: StartingSections::RestartClass()");
#endif
    sub_19A750();
#if !defined(CODFH_SP) || defined(CODFH_SP_LOGS)
    sub_19A750("Restart: PlayerTrigger::RestartClass()");
#endif
    sub_19A750();
#if !defined(CODFH_SP) || defined(CODFH_SP_LOGS)
    sub_19A750("Restart: SectionInfo::RestartClass()");
#endif
    sub_19A750();
#if !defined(CODFH_SP) || defined(CODFH_SP_LOGS)
    sub_19A750("Restart: CPlayerWeapon::RestartPlayerWeaponDefs()");
#endif
    sub_19A750();
#if !defined(CODFH_SP) || defined(CODFH_SP_LOGS)
    sub_19A750("Restart: CNPCWeapon::RestartClass()");
#endif
    sub_19A750();
#if !defined(CODFH_SP) || defined(CODFH_SP_LOGS)
    sub_19A750("Restart: TriggeredParticleManager::RestartClass()");
#endif
    sub_F4850();
#if !defined(CODFH_SP) || defined(CODFH_SP_LOGS)
    sub_19A750("Restart: DecalManager::Restart()");
#endif
    sub_EFF70();
#if !defined(CODFH_SP) || defined(CODFH_SP_LOGS)
    sub_19A750("Restart: CloneManager::Restart()");
#endif
    sub_19A750();
#if !defined(CODFH_SP) || defined(CODFH_SP_LOGS)
    sub_19A750("Restart: ParticleManager::Restart()");
#endif
    sub_F29F0();
#if !defined(CODFH_SP) || defined(CODFH_SP_LOGS)
    sub_19A750("Restart: TriggerManager::Restart()");
#endif
    sub_19A750();
#if !defined(CODFH_SP) || defined(CODFH_SP_LOGS)
    sub_19A750("Restart: PathNodeManager::Restart()");
#endif
    sub_F8010();
#if !defined(CODFH_SP) || defined(CODFH_SP_LOGS)
    sub_19A750("Restart: SplineManager::Restart()");
#endif
    sub_19A750();
#if !defined(CODFH_SP) || defined(CODFH_SP_LOGS)
    sub_19A750("Restart: shellManager.Restart()");
#endif
    dword_4B8EF0.sub_E99A0();
    sub_186950();
#if !defined(CODFH_SP) || defined(CODFH_SP_LOGS)
    sub_19A750("Restart: Audio::RestartClass()");
#endif
    sub_83510();
    sub_D9450();
#if !defined(CODFH_SP) || defined(CODFH_SP_LOGS)
    sub_19A750("Restart: GodAssetManager::RestartClass()");
#endif
    sub_198570();
#if !defined(CODFH_SP) || defined(CODFH_SP_LOGS)
    sub_19A750("Restart: CAnimDatabase::Restart()");
#endif
    sub_19A750();
#if !defined(CODFH_SP) || defined(CODFH_SP_LOGS)
    sub_19A750("Restart: TextureManager::RestartClass()");
#endif
    sub_19A750();
#if !defined(CODFH_SP) || defined(CODFH_SP_LOGS)
    sub_19A750("Restart: LevelManager::Restart()");
#endif
    sub_172210();
#if !defined(CODFH_SP) || defined(CODFH_SP_LOGS)
    sub_19A750("Restart: SerializeManager::Restart()");
#endif
    unk_4F2B68.pDtor();
#if !defined(CODFH_SP) || defined(CODFH_SP_LOGS)
    sub_19A750("Restart: CProfiler::RestartProfiler()");
#endif
    sub_16D630();
#if !defined(CODFH_SP) || defined(CODFH_SP_LOGS)
    sub_19A750("Restart: Tick::Restart()");
#endif
    sub_D9610();
    RwFreeListPurgeAllFreeLists();
    sub_D8660();
    sub_D9450();
    RWS::SendMsg(dword_4B67C0);
    sub_D9450();
    RwFreeListPurgeAllFreeLists();
    if (sub_12F080(2))
    {
        sub_12F060(2);
#if !defined(CODFH_SP) || defined(CODFH_SP_LOGS)
        sub_19A750("***ALERT!ALERT!ALERT!ALERT!ALERT!ALERT!ALERT!ALERT!***");
        sub_19A750("MEMORY LEAK detected during shutdown! Show this to a");
        sub_19A750("programmer immediately (especially the last one that");
        sub_19A750("checked in) and tell him that restart/reset is broken.");
        sub_19A750("***ALERT!ALERT!ALERT!ALERT!ALERT!ALERT!ALERT!ALERT!***");
#endif
    }
    sub_83C90();
    sub_19A750("Game Restart END"); // single player keeps this print (SP 0xA2715)
    dword_4B8714 = 1;
#if !defined(CODFH_SP) || defined(CODFH_SP_LOGS)
    sub_19A750("**************************************");
    sub_19A750("Game Restart END...");
    sub_19A750("**************************************");
    sub_19A750(" ");
    sub_19A750(" ");
#endif
#ifndef CODFH_SP // single player has no call here (SP 0xA271F goes on to sub_124EE0)
    sub_1A2D60();
#endif
    sub_124EE0(2.5f, 0);
}

// match: ?sub_D6EB0@@YAXXZ @ 0x000D6EB0
// sp-match: ?sub_D6EB0@@YAXXZ @ 0x000A2C60
void sub_D6EB0()
{
#if !defined(CODFH_SP) || defined(CODFH_SP_LOGS)
    sub_19A750(" ");
    sub_19A750(" ");
    sub_19A750("******************************************");
    sub_19A750("GameLoop Shutdown BEGIN....");
    sub_19A750("******************************************");
#endif
#ifndef CODFH_SP // single player has no call here (SP 0xA2C7A starts with sub_19D060)
    sub_1A2D40();
#endif
    sub_19D060();
    unk_4B9308.sub_EEF90(0, 1);
    sub_D7040(0);
#if !defined(CODFH_SP) || defined(CODFH_SP_LOGS)
    sub_19A750("GameLoop Shutdown RWStudio begin....");
#endif
    RWS::CEventHandler::UnRegisterMsg(iMsgSparkStartSystem);
    RWS::CEventHandler::UnRegisterMsg(dword_4B8750);
    RWS::CEventHandler::UnRegisterMsg(dword_4B67B8);
    RWS::CEventHandler::UnRegisterMsg(dword_4B67C0);
    RWS::CEventHandler::UnRegisterMsg(dword_4B67B0);
    RWS::MainLoop::Close();
#if !defined(CODFH_SP) || defined(CODFH_SP_LOGS)
    sub_19A750("GameLoop Shutdown RWStudio end....");
#endif
    sub_19A750();
    sub_172A80();
    RwFreeListPurgeAllFreeLists();
    dword_4B86F8 &= ~1;
#ifdef CODFH_SP
    // Single player then starts the multiplayer image unless the launch data
    // asked it to keep its defaults, handing it the profile, the level, the
    // pad, the Live state and logon (SP 0xA2CE3-0xA2DD8).
    if (!dword_4F45F8->unk_20)
    {
        LAUNCH_DATA var_C00;
        type_4F45F8 *var_8 = (type_4F45F8 *)&var_C00;
        RwInt32 var_C04 = dword_4F28F0->unk_44;
        RwCamera *l4;

        memset(var_8, 0, 0x6A0);
        var_8->unk_10 = 1;
        var_8->unk_14 = var_C04;
        var_8->unk_18 = dword_4B877C;
        if (dword_4B877C)
        {
            *(RwInt32 *)var_8->unk_1C = sub_19B050();
        }
        var_8->unk_24 = get_dword_4B9E50();
        *(RwInt32 *)&var_8->unk_04[8] = dword_4F3130.unk_764;
        if (dword_4F3130.sub_19C500() && !dword_4F3130.unk_24
            && XOnlineSaveLogonState((PXONLINE_LOGON_STATE)var_8->unk_48A) == 0)
        {
            var_8->unk_40 = 1;
        }
        else
        {
            var_8->unk_40 = 0;
        }
        sub_1A2650(var_8);
        var_8->unk_394 = dword_4F5A30;
        sub_19BE30((type_19BE30 *)var_8);
        l4 = RWS::CameraHelper::CreateMainRasterCamera(Width, Height, ZDepth);
        sub_19BAC0(l4);
        sub_EA560(l4);
        RWS::CameraHelper::Destroy(l4);
        D3DDevice_PersistDisplay();
        XLaunchNewImage("d:\\default.xbe", (PLAUNCH_DATA)&var_C00);
    }
#endif
#if !defined(CODFH_SP) || defined(CODFH_SP_LOGS)
    sub_19A750("******************************************");
    sub_19A750("GameLoop Shutdown END....");
    sub_19A750("******************************************");
    sub_19A750(" ");
    sub_19A750(" ");
#endif
    if (sub_12F080(1))
    {
        sub_12F060(1);
#if !defined(CODFH_SP) || defined(CODFH_SP_LOGS)
        sub_19A750("***ALERT!ALERT!ALERT!ALERT!ALERT!ALERT!ALERT!ALERT!***");
        sub_19A750("MEMORY LEAK detected during shutdown! Show this to a");
        sub_19A750("programmer immediately (especially the last one that");
        sub_19A750("checked in) and tell him that restart/reset! is broken.");
        sub_19A750("***ALERT!ALERT!ALERT!ALERT!ALERT!ALERT!ALERT!ALERT!***");
#endif
    }
}

// match: ?sub_D7040@@YAXH@Z @ 0x000D7040
// sp-match: ?sub_D7040@@YAXH@Z @ 0x000A2740
void sub_D7040(RwInt32 arg_0)
{
#if !defined(CODFH_SP) || defined(CODFH_SP_LOGS)
    sub_19A750("GameLoopShutdownModules begin....");
#endif
    // Three shutdowns that expand to nothing (see unused_slot).
    unused_slot();
    unused_slot();
    unused_slot();
#ifndef CODFH_SP // single player has none of these (SP 0xA2740)
    unk_4F7EB8.sub_1AF750(sub_1CCA10(), 1, 0);
#endif
    dword_4B8700 = 0;
    dword_4B8704 = 0;
    dword_4B8708 = 0;
    dword_4B870C = 0;
    dword_4B8710 = 0;
    dword_4B8734 = 0;
    sub_81310();
    sub_125E40();
    dword_4B86FC = 0;
    sub_1702F0();
    sub_17C4E0();
    sub_17D2B0();
    sub_D5570();
    sub_F1190();
    sub_17E310();
    sub_19A750();
    sub_E8830();
#ifndef CODFH_SP
    unk_4F7EB8.sub_1AF750(sub_1CCA10(), 1, 0);
#endif
    RWS::CEventHandler::DeleteEventHandlers(RWS::iMsgDeleteEventHandler);
    RWS::CAttributeHandler::PurgeAll();
    RWS::CResourceManager::PurgeAll();
    sub_141BD0();
    sub_8ACF0();
    sub_FB570();
    sub_16D50();
    sub_31B50();
    sub_3ECA0();
    sub_3CCE0();
#ifndef CODFH_SP
    unk_4F7EB8.sub_1AF750(sub_1CCA10(), 1, 0);
#endif
    sub_3C270();
    sub_40840();
    sub_35080();
    sub_19A750();
    sub_32F00();
    sub_733B0();
    sub_429F0();
    sub_6B4A0();
    sub_71560();
    sub_72890();
    sub_67E00();
    sub_673A0();
#ifndef CODFH_SP
    unk_4F7EB8.sub_1AF750(sub_1CCA10(), 1, 0);
#endif
    sub_787F0();
    sub_1222D0();
    sub_15F280();
    sub_19A750();
    sub_AA3F0();
    sub_19A750();
    sub_19A750();
    sub_19A750();
    sub_15C7D0();
    sub_F4860();
    sub_F0000();
    sub_1230F0();
    sub_F2A30();
    sub_144A70();
    sub_143D40();
    sub_F8120();
#ifndef CODFH_SP
    unk_4F7EB8.sub_1AF750(sub_1CCA10(), 1, 0);
#endif
    dword_4B8EF0.sub_E99E0();
    sub_1868E0();
    sub_835E0();
    sub_16F1D0();
#ifndef CODFH_SP
    unk_4F7EB8.sub_1AF750(sub_1CCA10(), 1, 0);
#endif
    sub_16FD60();
#ifndef CODFH_SP
    unk_4F7EB8.sub_1AF750(sub_1CCA10(), 1, 0);
#endif
    sub_198580();
#ifndef CODFH_SP
    unk_4F7EB8.sub_1AF750(sub_1CCA10(), 1, 0);
#endif
    sub_773A0();
#ifndef CODFH_SP
    unk_4F7EB8.sub_1AF750(sub_1CCA10(), 1, 0);
#endif
#ifdef CODFH_SP
    // single player expands sub_D73C0 here (SP 0xA288D)
    if (dword_4E5E40.unk_08)
    {
        delete dword_4E5E40.unk_08;
    }
    dword_4E5E40.unk_08 = 0;
    dword_4E5E40.unk_00[0] = 0;
    dword_4E5E40.unk_00[1] = 0;
#else
    sub_D73C0();
#endif
    sub_F2630();
    sub_172230();
    unk_4E5CC8.sub_144330();
    sub_1446C0();
    sub_16D6A0();
    sub_19A750();
#ifdef CODFH_SP
    // single player expands type_8F300::sub_D7350 here (SP 0xA28D4)
    if (dword_4B2550.unk_08)
    {
        delete dword_4B2550.unk_08;
    }
    if (dword_4B2550.unk_04)
    {
        delete dword_4B2550.unk_04;
    }
    dword_4B2550.unk_08 = 0;
    dword_4B2550.unk_00 = 0;
    dword_4B2550.unk_04 = 0;
#else
    dword_4B2550.sub_D7350();
#endif
#ifndef CODFH_SP
    unk_4F7EB8.sub_1AF750(sub_1CCA10(), 1, 0);
#endif
    sub_E8830();
    unk_4F2B68.pDtor();
    RwFreeListPurgeAllFreeLists();
    unk_4E73A8.sub_1833D0();
#ifndef CODFH_SP
    unk_4F7EB8.sub_1AF750(sub_1CCA10(), 1, 0);
#endif
#if !defined(CODFH_SP) || defined(CODFH_SP_LOGS)
    sub_19A750("GameLoop Shutdown modules end....");
#endif
}

// match: ?sub_D7350@type_8F300@@QAEXXZ @ 0x000D7350
void type_8F300::sub_D7350()
{
    if (unk_08)
    {
        delete unk_08;
    }
    if (unk_04)
    {
        delete unk_04;
    }
    unk_08 = 0;
    unk_00 = 0;
    unk_04 = 0;
}

#ifndef CODFH_SP
// The out-of-line body is MP-only; SP expands it at its sole call (0xA288D).
// match: ?sub_D73C0@@YAXXZ @ 0x000D73C0
void sub_D73C0()
{
    if (dword_4E5E40.unk_08)
    {
        delete dword_4E5E40.unk_08;
    }
    dword_4E5E40.unk_08 = 0;
    dword_4E5E40.unk_00[0] = 0;
    dword_4E5E40.unk_00[1] = 0;
}
#endif

// match: ?sub_D7410@@YAXXZ @ 0x000D7410
// sp-match: ?sub_D7410@@YAXXZ @ 0x000A32B0
void sub_D7410()
{
    while ((dword_4B86F8 & 1) && !(dword_4B86F8 & 4))
    {
        if (((dword_4B86F8 >> 3) & 1) && is_4F26D0_clear() && is_4B86FC_clear() && always_true())
        {
            sub_D6A50();
            dword_4B86F8 &= ~8;
        }
        if (((dword_4B86F8 >> 1) & 1) && is_4F26D0_clear() && is_4B86FC_clear() && always_true())
        {
            sub_D6EB0();
            sub_D6640();
            dword_4B86F8 &= ~2;
        }
        if (byte_4C1941)
        {
            sub_D8D20();
            byte_4C1941 = 0;
        }
        if (((dword_4B86F8 >> 5) & 1) && is_4F26D0_clear() && is_4B86FC_clear() && always_true())
        {
#ifdef CODFH_SP
            sub_D9490(1, 0); // single player shows the loading screen first (SP 0xA3352)
#endif
            sub_D8E30();
        }
        if (sub_19D020())
        {
            sub_D7880();
            sub_19D040();
        }
        if (dword_44D4B4 || !dword_4AF24C || dword_4AF24C == 3)
        {
            sub_813E0(0);
        }
    }
    sub_D9490(1, 0);
}

// match: ?sub_D7570@@YAHXZ @ 0x000D7570
// sp-match: ?sub_D7570@@YAHXZ @ 0x000A2930
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
RwInt32 sub_D7570()
{
    type_198660 var_10;
    RwInt32 var_8;
    RwInt32 l4;

    if (is_4F26D0_clear() && is_4B86FC_clear())
    {
        if (dword_4B8700)
        {
            dword_4B8700 = 0;
            sub_713E0();
            sub_D5320(0);
            RWS::SendMsg(iMsgSparkStartSystem);
            dword_4B8EF0.sub_E9C20();
            dword_4B8EF0.sub_E9FB0(10);
#ifndef CODFH_SP // single player has no call here (SP 0xA298B goes on to the store)
            sub_1FF250()->sub_200630();
#endif
            dword_4B8704 = 1;
            return 0;
        }
        if (dword_4B8704)
        {
            dword_4B8704 = 0;
            sub_144B80();
            sub_198610();
            sub_E8910();
            sub_D8660();
            RWS::SendMsg(dword_4B8750);
            dword_4B8EF0.pDtor();
            RwFreeListPurgeAllFreeLists();
            sub_12F090();
            dword_4B871C = 0;
            sub_83C90();
            sub_124EE0(2.5f, 0);
            if (!dword_4B8720)
            {
                sub_D9320();
            }
            dword_4B8710 = 1;
            dword_4B8730 = RWS::Time::GetTime();
            return 0;
        }
        if (dword_4B8708)
        {
            RWS::SendMsg(iMsgSparkStartSystem);
            RWS::SendMsg(dword_4B8750);
            dword_4B8708 = 0;
            return 0;
        }
        if (dword_4B870C)
        {
            l4 = 0;
            for (var_8 = 0; var_8 < 4; var_8++)
            {
                if (dword_4E5D30[var_8].get_unk_00())
                {
                    l4 = 1;
                    break;
                }
            }
            if (l4)
            {
#ifdef CODFH_SP
                // single player clears the flag first and has no sub_1A2D70 call (SP 0xA2A75)
                dword_4B870C = 0;
                unk_4E5CD8.unk_00 = 1;
#else
                unk_4E5CD8.unk_00 = 1;
                dword_4B870C = 0;
                sub_1A2D70();
#endif
            }
            return 0;
        }
        if (dword_4B8714)
        {
            RWS::SendMsg(dword_4B67B0);
            dword_4B8714 = 0;
        }
        else
        {
#ifdef CODFH_SP
            // single player also waits on bits 4 and 5 (SP 0xA2AB3: & 0x3A)
            return !((RwUInt8)dword_4B86F8 & 0x3A);
#else
            if (((dword_4B86F8 >> 3) & 1) || ((dword_4B86F8 >> 1) & 1))
            {
                return 0;
            }
            return 1;
#endif

        }
    }
    else if (sub_198650() > 30.0f)
    {
        dword_4B8760++;
        if (dword_4B8760 > 60)
        {
            var_10.unk_00 = 0;
            var_10.unk_04 = 0;
            sub_198660(&var_10);
            dword_4B8760 = 0;
        }
    }
    return 0;
}

// match: ?sub_D7880@@YAXXZ @ 0x000D7880
// sp-match: ?sub_D7880@@YAXXZ @ 0x000A2FD0
void sub_D7880()
{
    RwInt32 var_4;
#ifdef CODFH_DRAW_TRIGGERS
    // (the debug tools, port/src/debug/trigtools.cpp: a section load, a give, a teleport asked for)
    TrigWebTick();
#endif

    sub_D9620();
    unk_4E73A8.sub_183840();
    sub_16D730();
    sub_16D7F0(0x1D);
    sub_16D7F0(0);
    dword_4CFA00 = 0;
    unk_4B9308.sub_EE6D0();
    unk_4B9308.sub_EE770();
    sub_19A750();
    sub_187B30();
    if (dword_4B8710)
    {
        sub_D7C20();
    }
    if (sub_D7570() && deltaTime > 0.0f)
    {
#ifndef CODFH_SP // single player has no call here (SP 0xA304F goes on to the profiler)
        sub_1A2A80(deltaTime);
#endif
        sub_16D7F0(0x1C);
        dword_4B8EF0.sub_E9AD0(deltaTime);
        sub_16D850(0x1C);
        sub_16D7F0(5);
        sub_19A750(deltaTime);
        sub_16D850(5);
        RWS::MainLoop::Poll();
        sub_16D7F0(3);
        sub_73650(deltaTime);
        sub_42C50(deltaTime);
        sub_16D850(3);
        sub_16E9C0();
        sub_16D7F0(4);
        sub_19A750(deltaTime);
        sub_8ADD0(deltaTime);
        sub_D62D0((void *)dword_4E5C74);
        sub_D5E20();
        sub_16D850(4);
        sub_16D7F0(5);
        sub_16D7F0(0x23);
        sub_85090(deltaTime, 1);
        sub_16D850(5);
        sub_16D850(0x23);
        sub_16D7F0(6);
        sub_15F350(deltaTime);
        sub_16D850(6);
        sub_17D370(deltaTime);
        sub_F11D0(deltaTime);
        sub_17E330(deltaTime);
        sub_173750();
        sub_16D7F0(7);
        sub_F6090();
        sub_31BB0(deltaTime);
        sub_3ED10(deltaTime);
        sub_16D850(7);
        sub_170310(deltaTime);
        sub_16D7F0(8);
        sub_F4890(deltaTime);
        sub_F3410();
        sub_1222F0(deltaTime);
        sub_16D850(8);
        sub_F00C0();
        sub_19A750();
        sub_124F70(deltaTime);
        sub_16D7F0(5);
        sub_857B0(deltaTime);
        sub_16D850(5);
        unk_4E5CC8.sub_144420();
        sub_16D850(0);
        unk_4F2B68.pDtor();
        sub_125F20(0);
        unk_4F2B68.pDtor();
    }
    else if ((dword_4B86F8 >> 4) & 1)
    {
        sub_16D850(0);
        dword_4B8EF0.sub_E9AD0(deltaTime);
        for (var_4 = 0; var_4 < 3; var_4++)
        {
            dword_44E8D8[var_4].sub_873B0();
        }
        sub_86350();
        unk_4F2B68.pDtor();
        sub_125F20(0);
        unk_4F2B68.pDtor();
    }
    else
    {
        sub_16D850(0);
    }
    sub_19A750();
    sub_16D850(0x1D);
    sub_16D740();
    sub_19A750();
}

// match: ?sub_D7C00@@YA_NXZ @ 0x000D7C00
bool sub_D7C00()
{
    return byte_4B8740;
}

// match: ?sub_D7C10@@YAX_N@Z @ 0x000D7C10
void sub_D7C10(bool arg_0)
{
    byte_4B8740 = arg_0;
}

// match: ?sub_D7C20@@YAXXZ @ 0x000D7C20
// match: __ehhandler$?sub_D7C20@@YAXXZ-0xE @ 0x00300CD0
// match: __ehhandler$?sub_D7C20@@YAXXZ @ 0x00300CDE
// sp-match: ?sub_D7C20@@YAXXZ @ 0x000A2E10
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void sub_D7C20()
{
    bool var_19;
    type_3D3548 *l18;
    RwReal v14;
    RwReal lv_10;

    if ((dword_4B86F8 >> 4) & 1)
    {
        flt_4B8984 += (deltaTime * flt_3D7360) / 1000.0f;
    }
    else
    {
        flt_4B8984 = 0.0f;
    }
#ifdef CODFH_SP
    // Single player's pause: not while the Live front end is up (unless at
    // step 7) or once asked to quit (dword_4B8738), nor while the player's
    // vehicle is in mode 1; the pause button (or a dropped pad: dword_42926C)
    // toggles it, the front end's step 7 forces it, and leaving it closes the
    // in-game menu (SP 0xA2E43-0xA2FC8).
    if (dword_4F3130.sp_sub_12AAD0() && dword_4F3130.unk_38 != 7)
    {
        return;
    }
    if (dword_4B8738)
    {
        return;
    }
    type_10F710 *sp_l18 = (type_10F710 *)sub_1745A0(0);
    if (sp_l18)
    {
        type_3DD948 *sp_v = (type_3DD948 *)sp_l18->unk_2110.sub_D4910();

        if (sp_v && sp_v->unk_414 == 1)
        {
            return;
        }
    }
    RwReal sp_v14 = unk_4B9308.sub_EE9A0(0, 0xB);
    RwInt32 sp_bit = (dword_4B86F8 >> 4) & 1;
    RwInt32 sp_held = dword_4EBCD8;
    if (!sp_bit && !dword_42926C)
    {
        sp_v14 = 1.0f;
    }
    if (!((dword_4B86F8 >> 4) & 1) && dword_4F3130.unk_38 == 7)
    {
        dword_4B8738 = 1;
    }
    else if (sp_v14 == 0.0f && (!sp_held || !sp_bit))
    {
        return;
    }
    dword_4EBCD8 = 0;
    ((type_4B86F8 *)&dword_4B86F8)->unk_00_4 = !((type_4B86F8 *)&dword_4B86F8)->unk_00_4;
    if ((dword_4B86F8 >> 4) & 1)
    {
        sub_D7EA0();
    }
    else
    {
        sub_D7EE0();
    }
    if (dword_4B9190)
    {
        if ((dword_4B86F8 >> 4) & 1)
        {
            dword_4B9190->sub_E0DD0();
        }
        else
        {
            dword_4B9190->sub_E0E00();
        }
    }
    if (!((dword_4B86F8 >> 4) & 1))
    {
        dword_4B86F8 |= 0x10;
        sub_187040();
        dword_4B86F8 &= ~0x10;
        if (sp_l18 && sp_l18->unk_1A48[sp_l18->unk_1AE4] && dword_4B9190
            && sp_l18->unk_1A48[sp_l18->unk_1AE4]->unk_458 != 0x20 && !sp_l18->unk_1B28 && !sp_l18->unk_1B04)
        {
            dword_4B9190->sub_DEB80(0);
        }
    }
    sub_1745A0(0);
#else
    if ((dword_4B86F8 >> 4) & 1)
    {
        static RwReal s_4B8768 = unk_4B9308.sub_EE9A0(0, 3);

        lv_10 = unk_4B9308.sub_EE9A0(0, 3);
        if (s_4B8768 == 0.0f && lv_10 != 0.0f)
        {
            unk_4F7EB8.sub_1AF250();
        }
        s_4B8768 = lv_10;
    }
    l18 = sub_1745A0(0);
    var_19 = false;
    v14 = 0.0f;
    if (byte_4B8764 || !sub_1FF250()->sub_200780())
    {
        v14 = unk_4B9308.sub_EE9A0(0, 0xB);
    }
    if (v14 != 0.0f)
    {
        var_19 = true;
        byte_4B8764 = !byte_4B8764;
        sub_D7C10(byte_4B8764);
    }
    else if (sub_D7C00() != byte_4B8764)
    {
        var_19 = true;
        byte_4B8764 = sub_D7C00();
    }
    if (var_19)
    {
        dword_4EBCD8 = 0;
        ((type_4B86F8 *)&dword_4B86F8)->unk_00_4 = byte_4B8764;
        sub_1FF250()->sub_2006A0((dword_4B86F8 >> 4) & 1);
        unk_4B9308.sub_EEF50(1);
        if ((dword_4B86F8 >> 4) & 1)
        {
            sub_D7EA0();
        }
        else
        {
            sub_D7EE0();
        }
        if (dword_4B9190)
        {
            if ((dword_4B86F8 >> 4) & 1)
            {
                dword_4B9190->sub_E0DD0();
            }
            else
            {
                dword_4B9190->sub_E0E00();
            }
        }
        if ((dword_4B86F8 >> 4) & 1)
        {
        }
        else if (dword_4B9190)
        {
            dword_4B9190->sub_DEB80(0);
        }
        sub_1745A0(0);
        sub_D7C10(byte_4B8764);
    }
#endif
}

// match: ?sub_D7EA0@@YAXXZ @ 0x000D7EA0
// sp-match: ?sub_D7EA0@@YAXXZ @ 0x000A2B10
void sub_D7EA0()
{
    dword_4B8728 = RWS::Time::GetTime();
    sub_85D60();
    dword_4B872C = dword_4B87DC;
    if (dword_4B87DC != 3)
    {
        dword_4B87DC = 6;
    }
}

// match: ?sub_D7EE0@@YAXXZ @ 0x000D7EE0
// sp-match: ?sub_D7EE0@@YAXXZ @ 0x000A2B40
void sub_D7EE0()
{
    dword_4B8724 += RWS::Time::GetTime() - dword_4B8728;
    sub_860E0();
    if (dword_4B87DC != 3)
    {
        dword_4B87DC = dword_4B872C;
    }
}





































// Functions /OPT:ICF folded into another body (config/aliases.txt), defined here for the
// authentic link (PLAN M7) with that body; the placement link takes the folded one.

// ?pDtor@type_4F2B68@@QAEXXZ (folded into 0x1E41C0)
// Single player keeps the call to it (SP 0xA24CF in sub_D6820): its empty body here
// would let /O2 drop that call, so SP only declares it.
#ifndef CODFH_SP
void type_4F2B68::pDtor()
{
}
#endif
