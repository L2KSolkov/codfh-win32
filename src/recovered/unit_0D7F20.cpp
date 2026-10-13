// Split from unit_0D6640.cpp at 0x0D7F20, where the image starts another object (the level path formatting first; its .data from 0x42926C):
// its .rdata begins at 0x3D7B9C with its own 16.666666, the unreferenced constant every game
// object starts its constants with (PLAN M7).

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

// Its data definitions (PLAN M5), in the image's address order.
// 0x003D7B9C
extern const RwReal flt_3D7B9C = 16.666666f;
// 0x0042926C
#ifndef CODFH_SP // single player defines it in unit_0D6640, before unk_4B8744 (SP 0x321508)
RwInt32 dword_42926C = 1;
#endif
// 0x00429270
RwReal flt_429270 = 73.0f;
// 0x00429274
RwReal flt_429274 = 56.0f;
// 0x00429278
RwReal flt_429278 = 1.0f;
// 0x0042927C
RwReal flt_42927C = 1.0f;
// 0x00429280
RwReal flt_429280 = 1.0f;

// match: ?flt_3D7B9C@@3MB @ 0x003D7B9C
// match: ?dword_42926C@@3HA @ 0x0042926C
// match: ?flt_429270@@3MA @ 0x00429270
// match: ?flt_429274@@3MA @ 0x00429274
// match: ?flt_429278@@3MA @ 0x00429278
// match: ?flt_42927C@@3MA @ 0x0042927C
// match: ?flt_429280@@3MA @ 0x00429280


// match: ?sub_D7F20@@YAXPADPBD@Z @ 0x000D7F20
// match: ??_C@_0N@MCMCBNAF@LEVELS?2?$CFs?2?$CFs?$AA@ @ 0x003D7BA0
// match: ??_C@_0BJ@FOHBJFBA@Unabled?5to?5open?5file?3?5?$CFs?$AA@ @ 0x003D7BB0
// match: ??_C@_0BC@IMGKNJOL@SECTIONS?2S_?$CFd?4RWS?$AA@ @ 0x003D7BCC
// match: ??_C@_0CF@CFPLNNJ@?$CK?$CK?$CKUnable?5to?5load?5GODDATA?4DFF?5fi@ @ 0x003D7BE0
// match: ??_C@_0BN@FKGIKKNI@Loading?5GODDATA?4DFF?5file?4?4?4?6?$AA@ @ 0x003D7C08
// match: ??_C@_0M@NPFEOOPH@GODDATA?4DFF?$AA@ @ 0x003D7C28
// match: ??_C@_0BN@MFDJFIEN@?$CK?$CK?$CKUnable?5to?5load?5LEVEL?4RWS?6?$AA@ @ 0x003D7C34
// match: ??_C@_0BL@HGJFOAGH@Loading?5LEVEL?4RWS?5file?4?4?4?6?$AA@ @ 0x003D7C54
// match: ??_C@_09BGIGDMIJ@LEVEL?4RWS?$AA@ @ 0x003D7C70
// match: ??_C@_0BN@NINBGLAO@?$CK?$CK?$CKUnable?5to?5load?5LEVEL?4DFF?6?$AA@ @ 0x003D7C7C
// match: ??_C@_0BL@CKGLFAHK@Loading?5LEVEL?4DFF?5file?4?4?4?6?$AA@ @ 0x003D7C9C
// match: ??_C@_09EJKFBLJJ@LEVEL?4DFF?$AA@ @ 0x003D7CB8
// match: ??_C@_0BO@IFIJAKGD@?$CK?$CK?$CKUnable?5to?5load?5GLOBAL?4DFF?6?$AA@ @ 0x003D7CC4
// match: ??_C@_0BM@POINMIFI@Loading?5GLOBAL?4DFF?5file?4?4?4?6?$AA@ @ 0x003D7CE4
// match: ??_C@_0L@KHELFPDD@GLOBAL?4DFF?$AA@ @ 0x003D7D00
// match: ??_C@_0BF@OEACHANB@Surfaces?$CLSurface_IDs?$AA@ @ 0x003D7D0C
// match: ??_C@_0BP@OBGGHKAF@COD_MapData?$CLTransData?$CLFilename?$AA@ @ 0x003D7D24
// match: ??_C@_0BO@NNMCLFJE@COD_MapData?$CLPerfData?$CLFilename?$AA@ @ 0x003D7D44
// match: ??_C@_0CH@KDICDKGC@Scripts?$CLClassList?$CLPlayerClass?$CLFi@ @ 0x003D7D64
// match: ??_C@_0CL@NOEFLDDJ@Scripts?$CLTaskList?$CLScriptedSequenc@ @ 0x003D7D8C
// match: ??_C@_0M@CHDMHENH@Credits?4bik?$AA@ @ 0x003D7DB8
// match: ??_C@_0CF@POJDIPAA@Do?5not?5remove?5Memory?5Card?5in?5Slo@ @ 0x003D7DC4
// match: ??_C@_0CK@LLJLCCI@Saving?5progress?5to?5Memory?5Card?5i@ @ 0x003D7DEC
// match: __real@43e00000 @ 0x003D7E18
// match: __real@44000000 @ 0x003D7E1C
// sp-match: ?sub_D7F20@@YAXPADPBD@Z @ 0x000A3420
void sub_D7F20(RwChar *arg_0, const RwChar *arg_4)
{
    sprintf(arg_0, "%s", arg_4);
}
#ifdef CODFH_WIN32
// (the port's -leveldir: the level's files from another folder, port/src/cli.cpp)
extern "C" const RwChar *port_level_dir;
#endif
// match: ?sub_D7F40@@YAXPADPBD@Z @ 0x000D7F40
// sp-match: ?sub_D7F40@@YAXPADPBD@Z @ 0x000A3440
void sub_D7F40(RwChar *arg_0, const RwChar *arg_4)
{
#ifdef CODFH_WIN32
    // (its clump banks still the -map level's own, from the pack: a level folder built from
    // that level, tools/testmap/make_flat.py, keeps its god data and so its banks; a bank read
    // off the disk instead failed in type_3DF9C4::sub_190B20)
    if (port_level_dir && _strnicmp(arg_4, "Clumps\\", 7) != 0)
    {
        sprintf(arg_0, "LEVELS\\%s\\%s", port_level_dir, arg_4);
        return;
    }
#endif
    sprintf(arg_0, "LEVELS\\%s\\%s", sub_19B060(sub_19B050()), arg_4);
}
// match: ?sub_D7F70@@YAXH@Z @ 0x000D7F70
// sp-match: ?sub_D7F70@@YAXH@Z @ 0x000A3F90
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void sub_D7F70(RwInt32 arg_0)
{
    RwChar var_1A8[0x80];
    type_142F70 var_128;
    RwInt32 m_10C;
    RwChar var108[0x80];
    RwChar var_88[0x80];
    RwStream *l4;

    m_10C = -1;
    sprintf(var108, "SECTIONS\\S_%d.RWS", arg_0);
    sub_D7F40(var_88, var108);
    sub_D7F20(var_1A8, var_88);
    l4 = RwStreamOpen(rwSTREAMFILENAME, rwSTREAMREAD, var_1A8);
    if (l4)
    {
        var_128.unk_00 = 0x13;
        var_128.unk_04 = arg_0;
        var_128.unk_08 = 0;
        m_10C = sub_142F70(l4, (type_141C10 *)&var_128);
        RwStreamClose(l4, var_1A8);
    }
#if !defined(CODFH_SP) || defined(CODFH_SP_LOGS)
    else
    {
        sub_19A750("Unabled to open file: %s", var108);
    }
#endif
    if (m_10C == -1)
    {
        return;
    }
    dword_4E5D30[m_10C].unk_00 = 1;
    dword_4E5D30[m_10C].unk_04 = 0;
}
// match: ?sub_D80C0@@YAHPBDP6AHPAURwStream@@PAUtype_142F70@@@ZHPAH@Z @ 0x000D80C0
// sp-match: ?sub_D80C0@@YAHPBDP6AHPAURwStream@@PAUtype_142F70@@@ZHPAH@Z @ 0x000A3A70
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
RwInt32 sub_D80C0(const RwChar *arg_0, RwInt32 (*arg_4)(RwStream *, type_142F70 *), RwInt32 arg_8,
                  RwInt32 *arg_C)
{
    RwMemory var_18;
    RwStream *lv_10;
    RwStream *var_C;
    RwUInt32 bp_8;
    void *bp_4;

    sub_19BB40(arg_0, 1);
    sub_82350();
    lv_10 = RwStreamOpen(rwSTREAMFILENAME, rwSTREAMREAD, (void *)arg_0);
    sub_82360();
    if (!lv_10)
    {
        sub_19BB40(arg_0, 0);
        return 0;
    }
    bp_4 = lv_10->Type.file.fpFile;
    bp_8 = sub_16D200(bp_4);
    sub_82330();
    pData = RWSMalloc(bp_8, 0x34250); // not an address: an allocation tag
    sub_19B1F0(pData != 0);
    sub_82340();
    RwStreamRead(lv_10, pData, bp_8);
    RwStreamClose(lv_10, 0);
    sub_82330();
    var_18.start = (RwUInt8 *)pData;
    var_18.length = bp_8;
    var_C = RwStreamOpen(rwSTREAMMEMORY, rwSTREAMREAD, &var_18);
    if (var_C)
    {
        type_142F70 var_34;

        var_34.unk_00 = 0x13;
        var_34.unk_04 = arg_8;
        var_34.unk_08 = 0;
        *arg_C = arg_4(var_C, &var_34);
        RwStreamClose(var_C, pData);
    }
    operator delete(pData);
    sub_82340();
    sub_19BB40(arg_0, 0);
    return 1;
}
// match: ?sub_D8230@@YAXH@Z @ 0x000D8230
// sp-match: ?sub_D8230@@YAXH@Z @ 0x000A3BA0
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void sub_D8230(RwInt32 arg_0)
{
    RwChar var_190[0x80];
    RwInt32 l10C;
    RwChar var_108[0x80];
    RwChar stk_88[0x80];

    l10C = -1;
    sprintf(var_108, "SECTIONS\\S_%d.RWS", arg_0);
    sub_D7F40(stk_88, var_108);
    sub_D7F20(var_190, stk_88);
    if (!sub_D80C0(var_190, (RwInt32 (*)(RwStream *, type_142F70 *))sub_142F70, arg_0, &l10C))
    {
        return;
    }
    if (l10C != -1)
    {
        get_4E5D30(l10C)->unk_00 = 1;
        get_4E5D30(l10C)->unk_04 = 0;
    }
}
// match: ?sub_D8310@@YAHXZ @ 0x000D8310
// sp-match: ?sub_D8310@@YAHXZ @ 0x000A3470
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
RwInt32 sub_D8310()
{
    RwChar var_208[0x100];
    RwChar var_108[0x100];
    RwStream *l4;

    sub_D7F40(var_108, "GODDATA.DFF");
    sub_D7F20(var_208, var_108);
    l4 = RwStreamOpen(rwSTREAMFILENAME, rwSTREAMREAD, var_208);
    if (l4)
    {
#if !defined(CODFH_SP) || defined(CODFH_SP_LOGS)
        sub_19A750("Loading GODDATA.DFF file...\n");
#endif
        RWS::CStreamHandler::ProcessStream(l4);
        RwStreamClose(l4, var_208);
    }
#if !defined(CODFH_SP) || defined(CODFH_SP_LOGS)
    else
    {
        sub_19A750("***Unable to load GODDATA.DFF file!\n");
    }
#endif
    dword_4B8EF0.sub_E9FB0(3);
    return 1;
}
// match: ?sub_D83C0@@YAHXZ @ 0x000D83C0
// sp-match: ?sub_D83C0@@YAHXZ @ 0x000A3C50
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
RwInt32 sub_D83C0()
{
    RwChar var_138[0x80];
    RwChunkHeaderInfo var_9C;
    RwChar var_88[0x80];
    RwStream *l4;

    sub_D8A40();
    var_9C.type = 0;
    var_9C.length = 0;
    var_9C.version = 0;
    var_9C.buildNum = 0;
    var_9C.isComplex = 0;
    RWS::MainLoop::Init(var_9C, 0);
    RWS::MainLoop::StopSystem(var_9C, 0);
    RWS::MainLoop::Logic::Frozen();
    sub_D7F40(var_88, "GLOBAL.DFF");
    sub_D7F20(var_138, var_88);
    l4 = RwStreamOpen(rwSTREAMFILENAME, rwSTREAMREAD, var_138);
    if (l4)
    {
#if !defined(CODFH_SP) || defined(CODFH_SP_LOGS)
        sub_19A750("Loading GLOBAL.DFF file...\n");
#endif
        RWS::CStreamHandler::ProcessStream(l4);
        RwStreamClose(l4, var_138);
    }
#if !defined(CODFH_SP) || defined(CODFH_SP_LOGS)
    else
    {
        sub_19A750("***Unable to load GLOBAL.DFF\n");
    }
#endif
    dword_4B8EF0.sub_E9FB0(1);
    sub_D7F40(var_88, "LEVEL.DFF");
    sub_D7F20(var_138, var_88);
    l4 = RwStreamOpen(rwSTREAMFILENAME, rwSTREAMREAD, var_138);
    if (l4)
    {
#if !defined(CODFH_SP) || defined(CODFH_SP_LOGS)
        sub_19A750("Loading LEVEL.DFF file...\n");
#endif
        RWS::CStreamHandler::ProcessStream(l4);
        RwStreamClose(l4, var_138);
    }
#if !defined(CODFH_SP) || defined(CODFH_SP_LOGS)
    else
    {
        sub_19A750("***Unable to load LEVEL.DFF\n");
    }
#endif
    dword_4B8EF0.sub_E9FB0(2);
    RWS::MainLoop::StartSystem(var_9C, 0);
    RWS::MainLoop::Logic::Running();
    type_142F70 stk_B8;
    sub_D7F40(var_88, "LEVEL.RWS");
    sub_D7F20(var_138, var_88);
    l4 = RwStreamOpen(rwSTREAMFILENAME, rwSTREAMREAD, var_138);
    if (l4)
    {
#if !defined(CODFH_SP) || defined(CODFH_SP_LOGS)
        sub_19A750("Loading LEVEL.RWS file...\n");
#endif
        stk_B8.unk_00 = 0x13;
        stk_B8.unk_04 = 0;
        stk_B8.unk_08 = 0;
        sub_142F70(l4, (type_141C10 *)&stk_B8);
        RwStreamClose(l4, var_138);
    }
#if !defined(CODFH_SP) || defined(CODFH_SP_LOGS)
    else
    {
        sub_19A750("***Unable to load LEVEL.RWS\n");
    }
#endif
    dword_4B8EF0.sub_E9FB0(6);
    sub_D8310();
    return 1;
}
// match: ?sub_D8660@@YAXXZ @ 0x000D8660
// sp-match: ?sub_D8660@@YAXXZ @ 0x000A4070
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void sub_D8660()
{
    type_4E5D30 *var_30;
    type_4E5D30 *var_2C;
    type_4E5D30 *var_28;
    type_4E5D30 *ebp_24;
    RwInt32 var_20;
    RwInt32 l1C;
    RwInt32 m_18;
    RwInt32 *ebp_14;
    RwInt32 *lv_10;
    RwUInt16 var_C;
    RwInt32 bp_8;
    RwInt32 bp_4;

    dword_4B870C = 1;
#ifdef CODFH_ALL_SECTIONS
    // (the port's every-section switch: nothing unloaded, what is missing loaded)
    if (port_all_sections_on())
    {
        port_all_sections_load();
        return;
    }
#endif
    bp_8 = 0;
    var_20 = 0;
    l1C = 0;
    var_C = 0;
    bp_4 = 0;
    m_18 = 0;
    ebp_14 = dword_4B6840;
    lv_10 = dword_4B6830;
    if (SectionInfo::sub_B0140())
    {
        for (bp_8 = 0; bp_8 < 4; bp_8++)
        {
            l1C = 0;
            if (dword_4B6850)
            {
                bp_4 = ebp_14[bp_8];
            }
            else
            {
                bp_4 = bp_8 + 1;
            }
            m_18 = lv_10[bp_8];
            if (m_18 <= 0)
            {
                continue;
            }
            m_18--;
            ebp_24 = &dword_4E5D30[m_18];
            var_C = ebp_24->unk_08;
            if (m_18 < 0 || m_18 >= 4)
            {
                continue;
            }
            if (ebp_24->get_unk_00())
            {
                l1C = 1;
                if (bp_4)
                {
                    if (var_C != bp_4)
                    {
                        l1C = 0;
                    }
                }
                else
                {
                    l1C = 0;
                }
                if (!l1C)
                {
                    sub_174060(ebp_24, 0);
                }
            }
            if (!l1C && bp_4)
            {
                for (var_20 = 0; var_20 < SECTION_SLOTS; var_20++)
                {
                    if (var_20 != ebp_24->get_unk_0A())
                    {
                        var_28 = &dword_4E5D30[var_20];
                        if (var_28->get_unk_00() && var_28->get_unk_08() == (RwUInt16)bp_4)
                        {
                            sub_174060(var_28, 0);
                        }
                    }
                }
                ebp_24->unk_04 = 1;
                ebp_24->unk_08 = (RwUInt16)bp_4;
                sub_D7F70(bp_4);
            }
            if (!byte_4B8E9C)
            {
                dword_4B8EF0.sub_E9FB0(7);
                sub_D9450();
            }
        }
    }
    else if (dword_4B6850)
    {
        for (bp_8 = 0; bp_8 < SECTION_SLOTS; bp_8++)
        {
            l1C = 1;
            var_2C = &dword_4E5D30[bp_8];
            if (var_2C->get_unk_00())
            {
                l1C = 0;
                var_C = var_2C->unk_08;
                for (var_20 = 0; var_20 < 4; var_20++)
                {
                    if (var_C == (RwUInt16)ebp_14[var_20])
                    {
                        l1C = 1;
                    }
                }
            }
            if (!l1C)
            {
                sub_174060(var_2C, 0);
            }
        }
        for (bp_8 = 0; bp_8 < 4; bp_8++)
        {
            bp_4 = ebp_14[bp_8];
            if (bp_4 && !sub_174640((RwUInt16)bp_4))
            {
                sub_D7F70(bp_4);
            }
            if (!byte_4B8E9C)
            {
                dword_4B8EF0.sub_E9FB0(7);
                sub_D9450();
            }
        }
    }
    else
    {
        for (bp_8 = 0; bp_8 < SECTION_SLOTS; bp_8++)
        {
            l1C = 1;
            var_30 = &dword_4E5D30[bp_8];
            if (var_30->get_unk_00())
            {
                l1C = 0;
                var_C = var_30->unk_08;
                if (var_C > 0 && var_C <= 4)
                {
                    l1C = 1;
                }
            }
            if (!l1C)
            {
                sub_174060(var_30, 0);
            }
        }
        for (bp_8 = 0; bp_8 < 4; bp_8++)
        {
            bp_4 = bp_8 + 1;
            if (!sub_174640((RwUInt16)bp_4))
            {
                sub_D7F70(bp_4);
            }
            if (!byte_4B8E9C)
            {
                dword_4B8EF0.sub_E9FB0(7);
                sub_D9450();
            }
        }
    }
}
// match: ?sub_D8A40@@YAHXZ @ 0x000D8A40
// sp-match: ?sub_D8A40@@YAHXZ @ 0x000A3500
RwInt32 sub_D8A40()
{
    dword_4B86FC++;
    dword_4B86FC++;
    sub_1989D0("Scripts+TaskList+ScriptedSequence+Filename", 0xC, 0, 0, 0);
    sub_1989D0("COD_EnemyWeaponProjectiles+PanzerFaustBullet", 3, 0, 0, 0);
    sub_1989D0("Scripts+ClassList+PlayerClass+Filename", 0xA, 0, 0, 0);
    dword_4B86FC++;
    dword_4B86FC++;
    sub_1989D0("COD_MapData+PerfData+Filename", 0x10, 0, 0, 0);
    dword_4B86FC++;
    sub_1989D0("COD_MapData+TransData+Filename", 0x29, 0, 0, 0);
    dword_4B86FC++;
    sub_1989D0("Surfaces+Surface_IDs", 0x33, 0, 0, 0);
    dword_4B86FC++;
    sub_F2680();
    sub_186980();
    dword_4B86FC++;
    dword_4B86FC++;
    dword_4B86FC++;
    dword_4B86FC++;
    dword_4B86FC++;
    dword_4B86FC++;
    return 1;
}
// match: ?sub_D8B90@@YAHXZ @ 0x000D8B90
// sp-match: ?sub_D8B90@@YAHXZ @ 0x000A3E00
RwInt32 sub_D8B90()
{
    RwInt32 var_4;

    var_4 = 1;
    dword_4B8EF0.sub_E9CA0();
    sub_D83C0();
    return var_4;
}
// match: ?sub_D8BC0@@YAXXZ @ 0x000D8BC0
// sp-match: ?sub_D8BC0@@YAXXZ @ 0x000A3E20
void sub_D8BC0()
{
    if (!((dword_4B86F8 >> 6) & 1))
    {
        dword_4B86F8 |= 0x40;
        sub_1252E0(sub_D8C00, 1);
        sub_124EE0(1.0f, 1);
    }
}
// match: ?sub_D8C00@@YAXXZ @ 0x000D8C00
// sp-match: ?sub_D8C00@@YAXXZ @ 0x000A35D0
void sub_D8C00()
{
    sub_19B000(-1);
    dword_4B86F8 |= 4;
}
// match: ?sub_D8C20@@YAXXZ @ 0x000D8C20
// sp-match: ?sub_D8C20@@YAXXZ @ 0x000A42A0
void sub_D8C20()
{
    if (!((dword_4B86F8 >> 6) & 1))
    {
        dword_4B86F8 |= 0x40;
        sub_1252E0(sub_D8C60, 1);
        sub_124EE0(1.0f, 1);
    }
}
// match: ?sub_D8C60@@YAXXZ @ 0x000D8C60
// sp-match: ?sub_D8C60@@YAXXZ @ 0x000A3E60
void sub_D8C60()
{
    unk_4B9308.sub_EEF90(0, 1);
    sub_E89E0();
    if (dword_4B918C)
    {
        sub_E8AC0("Credits.bik", dword_4E5C74, 1, 0);
    }
#ifdef CODFH_SP
    // Single player records the level and, after level 38, unlocks 0x4000
    // and the difficulty's extras (SP 0xA3E93).
    dword_4B8770 = sub_19B050();
    {
        RwInt32 *flags = &dword_4F28F0->unk_30;

        if (dword_4B8770 == 38)
        {
            *flags |= 0x4000;
            switch (dword_42B714)
            {
            case 2:
                *flags |= 0x40;
            case 1:
                *flags |= 0x30;
            case 0:
                *flags |= 0xF;
            }
        }
    }
#endif
    sub_D8F60();
    sub_D8F80();
    sub_19B000(-1);
    dword_4B86F8 |= 4;
}
// match: ?sub_D8CC0@@YAXH@Z @ 0x000D8CC0
// sp-match: ?sub_D8CC0@@YAXH@Z @ 0x000A42E0
void sub_D8CC0(RwInt32 arg_0)
{
    if (!((dword_4B86F8 >> 7) & 1))
    {
        dword_4B8770 = sub_19B050();
#ifdef CODFH_SP
        // Single player unlocks 0x1000 when entering level 12 and 0x2000 for
        // level 18 (SP 0xA42EE).
        {
            type_4F28F0 *data = dword_4F28F0;

            if (dword_4B8770 == 12)
                data->unk_30 |= 0x1000;
            else if (dword_4B8770 == 18)
                data->unk_30 |= 0x2000;
        }
#endif
        sub_19B000(arg_0);
        dword_4B86F8 |= 0x80;
        sub_124EE0(2.0f, 1);
        sub_1252E0(sub_D8DC0, 1);
    }
}
// match: ?sub_D8D20@@YAXXZ @ 0x000D8D20
// sp-match: ?sub_D8D20@@YAXXZ @ 0x000A4350
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void sub_D8D20()
{
#ifdef CODFH_SP
    // Single player's level sequence (SP 0xA4350): twenty levels, ending
    // with 39.
    RwInt32 frm_24[20] = {1, 2, 4, 5, 7, 8, 11, 12, 14, 15, 17, 18, 24, 25, 26, 30, 36, 37, 38, 39};
#else
    RwInt32 frm_24[9] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
#endif
    RwInt32 var_2C;
    RwInt32 var_28;

    if (!((dword_4B86F8 >> 7) & 1))
    {
        var_2C = sub_19B050();
        var_28 = 0;
#ifdef CODFH_SP
        while (frm_24[var_28] != 39)
#else
        while (frm_24[var_28] != 9)
#endif
        {
            if (frm_24[var_28] == var_2C)
            {
                sub_D8CC0(frm_24[var_28 + 1]);
            }
            var_28++;
        }
    }
}
// match: ?sub_D8DC0@@YAXXZ @ 0x000D8DC0
// sp-match: ?sub_D8DC0@@YAXXZ @ 0x000A3F00
void sub_D8DC0()
{
    unk_4B9308.sub_EEF90(0, 1);
    sub_E89E0();
    if (dword_4B918C)
    {
        sub_E8AC0("Credits.bik", dword_4E5C74, 1, 0);
    }
#ifdef CODFH_PLAIN
    // (plain builds: the image clears the block dword_4B8780 to unk_4B8798 in one; a plain
    // link does not keep those variables together)
    memset(&dword_4B8780, 0, sizeof(dword_4B8780));
    memset(&byte_4B8784, 0, sizeof(byte_4B8784));
    memset(dword_4B8788, 0, sizeof(dword_4B8788));
    memset(unk_4B8798, 0, sizeof(unk_4B8798));
#else
    memset(&dword_4B8780, 0, 0x48);
#endif
    sub_D93F0();
    sub_D8F60();
    sub_D8F80();
    dword_4B86F8 |= 0x20;
}
// match: ?sub_D8E30@@YAXXZ @ 0x000D8E30
// sp-match: ?sub_D8E30@@YAXXZ @ 0x000A35F0
void sub_D8E30()
{
    dword_4B877C = 1;
    sub_D6EB0();
    dword_4B877C = 0;
    sub_D6640();
    dword_4B86F8 &= ~0x20;
    dword_4B86F8 &= ~0x80;
}
// match: ?sub_D8E80@@YAXXZ @ 0x000D8E80
// sp-match: ?sub_D8E80@@YAXXZ @ 0x000A3620
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void sub_D8E80()
{
    RwV2d var_110;
    RwChar var_108[0x100];
    RwReal l4;

    l4 = 24.0f;
    var_110.x = 120.0f;
    var_110.y = 156.0f;
    var_108[0] = 0;
    sprintf(var_108, "Saving progress to Memory Card in Slot 1\n");
    dword_4B8EF0.sub_E9BE0(var_108, &var_110, 0, -1.0f, -1.0f, -1.0f);
    var_110.y -= l4;
    var_110.x += 16.0f;
    sprintf(var_108, "Do not remove Memory Card in Slot 1\n");
    dword_4B8EF0.sub_E9BE0(var_108, &var_110, 0, -1.0f, -1.0f, -1.0f);
}
// match: ?sub_D8F60@@YAXXZ @ 0x000D8F60
// sp-match: ?sub_D8F60@@YAXXZ @ 0x000A36F0
void sub_D8F60()
{
    sub_85D60();
    sub_186880(0);
    dword_4B8890 = 0;
}
// match: ?sub_D8F80@@YAXXZ @ 0x000D8F80
// sp-match: ?sub_D8F80@@YAXXZ @ 0x000A3710
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void sub_D8F80()
{
    type_D90B0 var_138;
    type_10F710 *local_D4;
    type_DA0A0 vD0;

    local_D4 = (type_10F710 *)sub_1745A0(0);
    local_D4->sub_111040(&var_138);
    if (!var_138.sub_D9180(true))
    {
        var_138.sub_D90B0();
    }
    local_D4->sub_108FF0(0);
    dword_4F28F0->unk_5C = var_138;
    dword_4F28F0->unk_58 = 1;
    if (sub_19B050() > dword_4F28F0->get_unk_54())
    {
        set_4F28F0_unk_54(sub_19B050());
    }
    type_186020 slot_140 = sub_1866E0((RwCamera *)dword_4E5CBC, &unk_4B8744,
                                      dword_4F28F0->get_unk_44(), 0, 0);
    sub_D9EC0(&vD0);
    dword_4F28F0->unk_B8 = vD0;
    {
        // Never used; the image's frame keeps their slots below the
        // function's own locals.
        RwInt32 var_144;
        RwInt32 var_148;
        RwInt32 var_14C;
        RwInt32 var_150;
    }
}
// (Single player has sub_D9120 and sub_D90B0 inline: include/types/type_DA0A0.h.)
#ifndef CODFH_SP
// match: ?sub_D90B0@type_D90B0@@QAEXXZ @ 0x000D90B0
// sp-match: ?sub_D90B0@type_D90B0@@QAEXXZ @ 0x000A33C0
void type_D90B0::sub_D90B0()
{
    RwInt32 var_4;              // never used; the image's frame keeps its slot

    sub_D9120();
    unk_18.clear();
    unk_54 = 1.0f;
    unk_50 = 100;
    unk_58 = 0;
}
#endif
#ifndef CODFH_SP
// match: ?sub_D9120@type_D90B0@@QAEXXZ @ 0x000D9120
void type_D90B0::sub_D9120()
{
    RwUInt32 var_4;

    unk_00 = 0;
    unk_04 = 0;
    for (var_4 = 0; var_4 < 2; var_4++)
    {
        unk_10[var_4] = 0;
        unk_08[var_4] = -1;
    }
}
#endif
// match: ?sub_D9180@type_D90B0@@QAE_N_N@Z @ 0x000D9180
// sp-match: ?sub_D9180@type_D90B0@@QAE_N_N@Z @ 0x00083E70
bool type_D90B0::sub_D9180(bool arg_0)
{
    RwInt32 var_4;              // never used; the image's frame keeps their
    RwInt32 var_8;              // slots

    if (!sub_D9240(arg_0) || !unk_18.is_valid())
    {
        return false;
    }
    if (unk_50 < 0)
    {
        return false;
    }
    if (unk_54 < 0.0f || unk_54 > 1.0f)
    {
        return false;
    }
    return true;
}
// match: ?sub_D9240@type_D90B0@@QAE_N_N@Z @ 0x000D9240
// sp-match: ?sub_D9240@type_D90B0@@QAE_N_N@Z @ 0x00083E00
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
bool type_D90B0::sub_D9240(bool arg_0)
{
    RwUInt32 var_8;
    RwInt32 l4;

    if ((unk_00 < 0 || unk_00 >= 0x27) && unk_00 != -1 && unk_00 != -1)
    {
        return false;
    }
    if (unk_04 < 0 || unk_04 >= 2)
    {
        return false;
    }
    l4 = 0;
    for (var_8 = 0; var_8 < 2; var_8++)
    {
        if (unk_08[var_8] == -1 || unk_08[var_8] == -1)
        {
            l4++;
        }
        else if (unk_08[var_8] < 0 || unk_08[var_8] >= 0x27 || (arg_0 && unk_08[var_8] == 0x20))
        {
            return false;
        }
    }
    if (arg_0 && l4 == 2)
    {
        return false;
    }
    return true;
}
// match: ?sub_D9320@@YAXXZ @ 0x000D9320
// sp-match: ?sub_D9320@@YAXXZ @ 0x000A3800
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void sub_D9320()
{
    bool var_9;
    RwInt32 *frm_8;
    RwInt32 l4;

#ifdef CODFH_PLAIN
    // (plain builds: the image clears the block dword_4B8780 to unk_4B8798 in one; a plain
    // link does not keep those variables together)
    memset(&dword_4B8780, 0, sizeof(dword_4B8780));
    memset(&byte_4B8784, 0, sizeof(byte_4B8784));
    memset(dword_4B8788, 0, sizeof(dword_4B8788));
    memset(unk_4B8798, 0, sizeof(unk_4B8798));
#else
    memset(&dword_4B8780, 0, 0x48);
#endif
    if (dword_4B67CC)
    {
        for (l4 = 0; l4 < 6; l4++)
        {
            dword_4B67CC->sub_A11A0(l4, &unk_4B8798[l4]);
        }
    }
    frm_8 = dword_4B6840;
    if (frm_8)
    {
        var_9 = (bool)dword_4B6850;
        for (l4 = 0; l4 < 4; l4++)
        {
            if (var_9)
            {
                dword_4B8788[l4] = frm_8[l4];
            }
            else
            {
                dword_4B8788[l4] = l4 + 1;
            }
        }
    }
    byte_4B8784 = (RwUInt8)dword_429EA8;
}
// match: ?sub_D93F0@@YAXXZ @ 0x000D93F0
// sp-match: ?sub_D93F0@@YAXXZ @ 0x000A38C0
void sub_D93F0()
{
    RwInt32 var_4;

    sub_1727E0(dword_4B8788);
    if (dword_4B67CC)
    {
        for (var_4 = 0; var_4 < 6; var_4++)
        {
            dword_4B67CC->sub_A1130(var_4, &unk_4B8798[var_4]);
        }
    }
    dword_429EA8 = byte_4B8784;
}
// match: ?sub_D9450@@YAXXZ @ 0x000D9450
// sp-match: ?sub_D9450@@YAXXZ @ 0x000A3F60
void sub_D9450()
{
    if (!dword_4B8710)
    {
        return;
    }
    if (!((dword_4B86F8 >> 3) & 1))
    {
        return;
    }
    dword_4B8734++;
    sub_D9490(0, dword_4B8734);
}
// match: ?sub_D9490@@YAXHH@Z @ 0x000D9490
// sp-match: ?sub_D9490@@YAXHH@Z @ 0x000A3920
// The loading screen's drawing: "Loading" and arg_4 dots at the screen's
// share of (73, 56) of 512 by 448, twice on the camera (flipped between),
// then shown. The function jumps to its end straight away: its set-up is
// dropped and only the dots' loop and the drawing remain in the image.
// Local names state their slots.
void sub_D9490(RwInt32 arg_0, RwInt32 arg_4)
{
    RwInt32 stk_7c;
    RwReal fp_78;
    RwV2d frm_74;
    RwChar m_6c[0x10];
    RwReal v5c;
    RwChar stk_58[0x40];
    RwReal ebp_14;
    RwReal lv_10;
    RwReal local_c;
    RwReal bp_8;
    RwCamera *bp_4;

#ifdef CODFH_SP
    // Single player draws it (SP 0xA3920): on the second camera, with the
    // localised "_Loading" text and at most 32 dots.
    bp_4 = (RwCamera *)dword_4E5CBC;
    if (!bp_4)
        return;
    if (arg_0 == 0)
        sprintf(stk_58, dword_4F6178[5]);
    else
        sprintf(stk_58, dword_4F6178[5]);
    if (arg_4 > 32)
        arg_4 = 32;
    sprintf(m_6c, ".");
    for (stk_7c = 0; stk_7c < arg_4; stk_7c++)
        strcat(stk_58, m_6c);
    ebp_14 = flt_429270 / 512.0f;
    v5c = flt_429274 / 448.0f;
    fp_78 = (RwReal)bp_4->frameBuffer->width;
    lv_10 = (RwReal)bp_4->frameBuffer->height;
    local_c = fp_78 * ebp_14;
    bp_8 = lv_10 * v5c;
    frm_74.x = local_c;
    frm_74.y = bp_8;
    dword_4B8EF0.sub_E9BE0(stk_58, &frm_74, 0, flt_429278, flt_42927C, flt_429280);
    sub_126750(bp_4);
    dword_4B8EF0.sub_E9BE0(stk_58, &frm_74, 0, flt_429278, flt_42927C, flt_429280);
    sub_126750(bp_4);
    sub_125ED0(bp_4, 0);
    return;
#endif
    goto end;
    bp_4 = (RwCamera *)dword_4E5C74;
    strcpy(stk_58, "Loading");
    strcpy(m_6c, ".");
    for (stk_7c = 0; stk_7c < arg_4; stk_7c++)
        strcat(stk_58, m_6c);
    ebp_14 = flt_429270 / 512.0f;
    v5c = flt_429274 / 448.0f;
    fp_78 = (RwReal)bp_4->frameBuffer->width;
    lv_10 = (RwReal)bp_4->frameBuffer->height;
    local_c = fp_78 * ebp_14;
    bp_8 = lv_10 * v5c;
    frm_74.x = local_c;
    frm_74.y = bp_8;
    dword_4B8EF0.sub_E9BE0(stk_58, &frm_74, 0, flt_429278, flt_42927C, flt_429280);
    sub_126750(bp_4);
    dword_4B8EF0.sub_E9BE0(stk_58, &frm_74, 0, flt_429278, flt_42927C, flt_429280);
    sub_126750(bp_4);
    sub_125ED0(bp_4, 0);
end:
    ;
}
