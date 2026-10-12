// The music players: streaming a file through the audio library, their
// requests and states and volumes. The file's original name is not recovered
// (M1), so it is named for its start address.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "rw/ostypes.h"
#include "game/functions.h"
#include "types/soundbank.h"
#include "types/musicplayer.h"
#include "rw/bastream.h"
#include "types/type_3DF8D8.h"
#ifdef CODFH_WIN32
// (the port: the game's printf prints, which the Xbox showed on its debug output, to the log)
extern "C" void port_debug_print(const RwChar *fmt, ...);
#define printf port_debug_print
#endif
#ifdef CODFH_SP
#include "game/data.h"
#include "game/savestate.h"
#endif

// Its data definitions (PLAN M5), in the image's address order.
// 0x003D4798
extern const RwReal flt_3D4798 = 16.666666f;
// 0x00428E74
#ifdef CODFH_SP // file-static in single player: sub_87250 (SP 0x6CC90) matches only with them static
static RwInt32 dword_428E74 = 4;
#else
RwInt32 dword_428E74 = 4;
#endif
// 0x00428E78
#ifdef CODFH_SP // file-static in single player (as dword_428E74)
static RwInt32 dword_428E78 = 2;
#else
RwInt32 dword_428E78 = 2;
#endif
// 0x004B1F68
RwChar byte_4B1F68[256];
// 0x004B2068
RwInt32 dword_4B2068;
// 0x004B206C
RwInt32 dword_4B206C;
// 0x004B2070
RwInt32 dword_4B2070;
// 0x004B9194
#ifndef CODFH_PLAIN
RwUInt32 dword_4B9194;
#endif
// End of its data definitions.


// Its data (PLAN M5): literals, constants and tables where the image has them.
// match: ?flt_3D4798@@3MB @ 0x003D4798
// match: ??_C@_0EO@COMCACFE@AudioStream?5?$CFd?3?5Wow?0?5crazy?5timin@ @ 0x003D47A0
// match: ??_C@_0EL@IAMGCFKI@AudioStream?5?$CFd?3?5Can?8t?5duck?$CB?5I?8m?5@ @ 0x003D47F0
// match: ??_C@_0BJ@PGHIKBDN@AudioStream?5?$CFd?3?5Ducking?$CB?$AA@ @ 0x003D483C
// match: ??_C@_0GA@JJKDNMIE@AudioStream?5?$CFd?3?5I?5refuse?5to?5duck@ @ 0x003D4858
// match: ??_C@_0DL@ENKPKCKD@AudioStream?5?$CFd?3?5Unable?5to?5duck?5?$CI@ @ 0x003D48B8
// match: ??_C@_0BL@DPKCPCMN@AudioStream?5?$CFd?3?5Unducking?$CB?$AA@ @ 0x003D48F4
// match: ??_C@_0EL@DDFHGMDA@AudioStream?5?$DP?$DP?3?5?$CD?$CD?$CB?$CB?$CD?$CD?5Inverted?5@ @ 0x003D4910
// match: ??_C@_0EC@NECALPIM@AudioStream?5?$CFd?3?5Inverted?5Unducki@ @ 0x003D4960
// match: ??_C@_0CE@EFIPPMFG@AudioStream?5?$DP?$DP?3?5Unducking?5Finish@ @ 0x003D49A4
// match: ??_C@_0CE@EDDGJGLN@AudioStream?5?$CFd?3?5Unducking?5Finish@ @ 0x003D49C8
// match: ??_C@_0EM@DHNLLAAE@?$FL?9?9?9?9?$CB?$CB?$CB?$CB?5Audio?5stream?5?$CFd?5?$CI?$CD?$CFd?$CJB@ @ 0x003D49F0
// match: ??_C@_0EG@GLJFMPKA@?$FL?9?9?9?9?$CB?$CB?$CB?$CB?5Audio?5stream?5?$CFd?5?$CI?$CD?$CFd?$CJI@ @ 0x003D4A40
// match: ??_C@_02DKCKIIND@?$CFs?$AA@ @ 0x003D4A88
// match: ??_C@_04FCOCJDHE@?$CF?44d?$AA@ @ 0x003D4A8C
// match: ??_C@_0DH@MLFGEFOE@?$FL?9?9?9?9?$CB?$CB?$CB?$CB?5Audio?5stream?5?$CFd?5?$CI?$CD?$CFd?$CJS@ @ 0x003D4A94
// match: ??_C@_0DL@OHJBKLIO@?$FL?9?9?9?9?$CB?$CB?$CB?$CB?5Audio?5stream?5?$CFd?5?$CI?$CD?$CFd?$CJW@ @ 0x003D4ACC
// match: ??_C@_0CO@KBOAHOKF@?$FL?9?9?9?9?$CB?$CB?$CB?$CB?5Audio?5stream?5?$CFd?5?$CI?$CD?$CFd?$CJD@ @ 0x003D4B08
// match: ??_C@_0DG@OMCEAPMD@?$FL?9?9?9?9?$CB?$CB?$CB?$CB?5Audio?5stream?5?$CFd?5?$CI?$CD?$CFd?$CJW@ @ 0x003D4B38
// match: ??_C@_0EB@PDIOPOAF@?$FL?9?9?9?9?$CB?$CB?$CB?$CB?5Audio?5stream?5?$CFd?5?$CI?$CD?$CFd?$CJC@ @ 0x003D4B70
// match: ??_C@_0DE@EAKBEMPD@?$FL?9?9?9?9?$CB?$CB?$CB?$CB?5Audio?5stream?5?$CFd?5?$CI?$CD?$CFd?$CJI@ @ 0x003D4BB4
// match: ??_C@_0BF@CCBMBHCN@StreamPrimedAndReady?$AA@ @ 0x003D4BE8
// match: ??_C@_0DG@BLOFIDOH@?$FL?9?9?9?9?$CB?$CB?$CB?$CB?5Audio?5stream?5?$CFd?5?$CI?$CD?$CFd?$CJC@ @ 0x003D4C00
// match: ??_C@_0DD@OGNPNADM@?$FL?9?9?9?9?$CB?$CB?$CB?$CB?5Audio?5stream?5?$CFd?5?$CI?$CD?$CFd?$CJC@ @ 0x003D4C38
// match: ??_C@_0EG@CGPIKEFD@?$FL?9?9?9?9?$CB?$CB?$CB?$CB?5Audio?5stream?5?$CFd?5?$CI?$CD?$CFd?$CJC@ @ 0x003D4C70
// match: ??_C@_0EO@MHKPFMLP@?$FL?9?9?9?9?$CB?$CB?$CB?$CB?5Audio?5stream?5?$CFd?5?$CI?$CD?$CFd?$CJM@ @ 0x003D4CB8
// match: ??_C@_0FJ@IMHGACNI@?$FL?9?9?9?9?$CB?$CB?$CB?$CB?5Audio?5stream?5?$CFd?5?$CI?$CD?$CFd?$CJS@ @ 0x003D4D08
// match: ??_C@_0DA@DAMLOCBP@?$DM?$DN?$DN?$DNUNKNOWN?5Audio?5stream?5is?5star@ @ 0x003D4D64
// match: ??_C@_0CM@DJMJGJOK@?$DM?$DN?$DN?$DN?$CB?$CB?$CB?$CB?5Audio?5stream?5C?5?$CI?$CD?$CFd?$CJ?5is@ @ 0x003D4D94
// match: ??_C@_0CM@COOBANCK@?$DM?$DN?$DN?$DN?$CB?$CB?$CB?$CB?5Audio?5stream?5B?5?$CI?$CD?$CFd?$CJ?5is@ @ 0x003D4DC0
// match: ??_C@_0CL@GFKNDJGL@?$DM?$DN?$DN?$DN?$CB?$CB?$CB?$CB?5Audio?5stream?5A?5?$CI?$CD?$CFd?$CJis?5@ @ 0x003D4DEC
// match: ??_C@_0DB@FCHPAJHI@?$FL?9?9?9?9?$CB?$CB?$CB?$CB?5Audio?5stream?5?$CFd?5?$CI?$CD?$CFd?$CJA@ @ 0x003D4E18
// match: ??_C@_0FC@JIGGMJOD@?$FL?9?9?9?9?$CB?$CB?$CB?$CB?5Audio?5stream?5?$CFd?5?$CI?$CD?$CFd?$CJP@ @ 0x003D4E50
// match: ??_C@_0O@OMGPKAPP@Bounty?$CBARRRR?$CB?$AA@ @ 0x003D4EA4
// match: ??_C@_06JKPDBEPA@?5r?3?5?$CFs?$AA@ @ 0x003D4EB4
// match: ??_C@_0N@HOGAOPPG@initializing?$AA@ @ 0x003D4EBC
// match: ??_C@_06GIHDKELO@?5m?3?5?$CFs?$AA@ @ 0x003D4ECC
// match: ??_C@_05LCLMIABE@s?3?5?$CFs?$AA@ @ 0x003D4ED4
// match: ??_C@_07NMEOOBNC@?$CIerror?$CJ?$AA@ @ 0x003D4EDC
// match: ??_C@_07EIFOIALH@nomedia?$AA@ @ 0x003D4EE4
// match: ??_C@_08FJBHPJOK@stopping?$AA@ @ 0x003D4EEC
// match: ??_C@_07OBEGHFKF@starved?$AA@ @ 0x003D4EF8
// match: ??_C@_07GDCKGKBF@playing?$AA@ @ 0x003D4F00
// match: ??_C@_06EKGGOLPA@paused?$AA@ @ 0x003D4F08
// match: ??_C@_07NAAKFDPJ@pausing?$AA@ @ 0x003D4F10
// match: ??_C@_07IEOHBIGJ@stopped?$AA@ @ 0x003D4F18
// match: ??_C@_07CPJOLGKM@opening?$AA@ @ 0x003D4F20
// match: ??_C@_08MKACHNJL@nastatus?$AA@ @ 0x003D4F28
// match: ?dword_428E74@@3HA @ 0x00428E74
// match: ?dword_428E78@@3HA @ 0x00428E78

// match: ??0type_44E8D8@@QAE@XZ @ 0x000863C0
// sp-match: ??0type_44E8D8@@QAE@XZ @ 0x0006BDE0

type_44E8D8::type_44E8D8()
{
    unk_00 = 0;
}

// match: ?sub_863E0@type_44E8D8@@QAEXPAUtype_44E8AC@@PAUtype_44E8B0@@@Z @ 0x000863E0
// sp-match: ?sub_863E0@type_44E8D8@@QAEXPAUtype_44E8AC@@PAUtype_44E8B0@@@Z @ 0x0006CEC0
void type_44E8D8::sub_863E0(type_44E8AC *arg_0, type_44E8B0 *arg_4)
{
    unk_254 = arg_0;
    unk_258 = arg_4;
    unk_24C = 0;
    unk_250 = 0;
    if (!unk_258)
    {
        return;
    }
    unk_104 = RwaStreamCreate_0(unk_258, 0, 4, (void *)sub_88640, unk_25C);
    sub_86470();
    unk_00 = 1;
}

// match: ?sub_86470@type_44E8D8@@QAEXXZ @ 0x00086470
// sp-match: ?sub_86470@type_44E8D8@@QAEXXZ @ 0x0006BDF0
void type_44E8D8::sub_86470()
{
    unk_248 = 0;
    unk_244 = 0;
    unk_188 = 0;
    unk_18C = 0;
    unk_1B0[0] = 0;
    unk_190[0] = 0;
    unk_1B0[1] = 0;
    unk_190[1] = 0;
    unk_1B0[2] = 0;
    unk_190[2] = 0;
    unk_1B0[3] = 0;
    unk_190[3] = 0;
    unk_1B0[4] = 0;
    unk_190[4] = 0;
    unk_1B0[5] = 0;
    unk_190[5] = 0;
    unk_1B0[6] = 0;
    unk_190[6] = 0;
    unk_1B0[7] = 0;
    unk_190[7] = 0;
    unk_1D0[0] = 1.0f;
    unk_1D0[1] = 1.0f;
    unk_1D0[2] = 1.0f;
    unk_1D0[3] = 1.0f;
    unk_1D0[4] = 1.0f;
    unk_1D0[5] = 1.0f;
    unk_1D0[6] = 1.0f;
    unk_1D0[7] = 1.0f;
    unk_184 = 0;
    unk_230 = 0;
    memset(unk_01, 0, sizeof(unk_01));
    unk_160 = 1;
    unk_168 = 0;
    unk_16C = 0;
    unk_164 = 0;
    unk_170 = 0;
    unk_174 = 4;
    unk_178 = 2;
    unk_17C = 0;
    unk_180 = 1;
    dword_4B2068 = 0;
}

// match: ??1type_44E8D8@@QAE@XZ @ 0x000866A0
// sp-match: ??1type_44E8D8@@QAE@XZ @ 0x0006DCD0
type_44E8D8::~type_44E8D8()
{
    if (unk_00)
    {
        sub_866C0();
    }
}

// match: ?sub_866C0@type_44E8D8@@QAEXXZ @ 0x000866C0
// sp-match: ?sub_866C0@type_44E8D8@@QAEXXZ @ 0x0006DC90
void type_44E8D8::sub_866C0()
{
    if (unk_104)
    {
        sub_867A0();
        sub_86470();
        DSPHandle_Stop(unk_104, 0, 0);
        unk_104 = 0;
    }
    unk_00 = 0;
}

// match: ?sub_86710@type_44E8D8@@QAEXXZ @ 0x00086710
// sp-match: ?sub_86710@type_44E8D8@@QAEXXZ @ 0x0006BF10
void type_44E8D8::sub_86710()
{
    if (unk_244)
    {
        unk_180 = 0xD;
        unk_244 = 0;
    }
    else
    {
        unk_180 = 0x13;
    }
}

// match: ?sub_86750@type_44E8D8@@QAEXXZ @ 0x00086750
// sp-match: ?sub_86750@type_44E8D8@@QAEXXZ @ 0x0006CF20
void type_44E8D8::sub_86750()
{
    unk_184 = 0;
    if (unk_104)
    {
        if (sub_86830())
        {
            return;
        }
        unk_180 = 0x10;
    }
}

// match: ?sub_867A0@type_44E8D8@@QAEXXZ @ 0x000867A0
// sp-match: ?sub_867A0@type_44E8D8@@QAEXXZ @ 0x0006DC30
void type_44E8D8::sub_867A0()
{
    RwInt32 var_4;

    unk_184 = 0;
    if (unk_104)
    {
        if (sub_86830())
        {
            return;
        }
        unk_180 = 0x10;
    }
    while (!sub_86830())
    {
        var_4 = 0;
        sub_873B0();
        if (var_4 % 10 == 0)
        {
            sub_86350();
            RtFSManagerSyncAllFiles();
        }
        var_4++;
    }
}

// match: ?sub_86830@type_44E8D8@@QAE_NXZ @ 0x00086830
// sp-match: ?sub_86830@type_44E8D8@@QAE_NXZ @ 0x0006BF40
bool type_44E8D8::sub_86830()
{
    if (unk_104)
    {
        if (unk_180 == 1)
        {
            return true;
        }
        return false;
    }
    return true;
}

// match: ?sub_86860@type_44E8D8@@QAEXH@Z @ 0x00086860
// sp-match: ?sub_86860@type_44E8D8@@QAEXH@Z @ 0x0006BF60
void type_44E8D8::sub_86860(RwInt32 arg_0)
{
    sub_23FFD0(unk_104, arg_0);
}

// Ducks the stream (arg_0 how far; -1 for its own depth).
// match: ?sub_86890@type_44E8D8@@QAEXM@Z @ 0x00086890
// sp-match: ?sub_86890@type_44E8D8@@QAEXM@Z @ 0x0006BF80
void type_44E8D8::sub_86890(RwReal arg_0)
{
    RwChar var_108[0x100];
    RwInt32 var_10C;

    if (!unk_248)
    {
        return;
    }
    if (unk_108 != 6)
    {
        if (dword_44E860 && dword_44E864)
        {
            sprintf(var_108, "AudioStream %d: Unable to duck (this stream isn't playing!", unk_248->unk_20);
        }
        return;
    }
    if (unk_248->unk_10 && arg_0 == -1.0f)
    {
        if (dword_44E860 && dword_44E864)
        {
            sprintf(var_108, "AudioStream %d: I refuse to duck. I am a master, so I don't duck for anyone!! Including myself!",
                    unk_248->unk_20);
        }
        return;
    }
    if (!unk_188 && !unk_18C)
    {
        if (dword_44E860 && dword_44E864)
        {
            sprintf(var_108, "AudioStream %d: Ducking!", unk_248->unk_20);
        }
        for (var_10C = 0; var_10C < 8; var_10C++)
        {
            unk_1F0[var_10C] = unk_190[var_10C];
            if (arg_0 == -1.0f)
            {
                unk_190[var_10C] = (100 - unk_248->unk_14) / 100.0f * unk_190[var_10C];
            }
            else
            {
                unk_190[var_10C] = (1.0f - arg_0) * unk_190[var_10C];
            }
            unk_210[var_10C] = unk_1D0[var_10C];
            if (arg_0 == -1.0f)
            {
                unk_1D0[var_10C] = 1.0f / dword_44D4D8;
            }
            else
            {
                unk_1D0[var_10C] = 1.0f;
            }
        }
        unk_188 = 1;
        unk_18C = 0;
        return;
    }
    if (unk_188)
    {
        if (dword_44E860 && dword_44E864)
        {
            sprintf(var_108, "AudioStream %d: Can't duck! I'm already ducking! I can't duck any farther!",
                    unk_248->unk_20);
        }
        return;
    }
    if (unk_18C)
    {
        if (dword_44E860 && dword_44E864)
        {
            sprintf(var_108, "AudioStream %d: Wow, crazy timing! I was unducking, but now I'll duck again!)",
                    unk_248->unk_20);
        }
        for (var_10C = 0; var_10C < 8; var_10C++)
        {
            unk_190[var_10C] = unk_248->unk_14 * unk_190[var_10C];
        }
        unk_188 = 1;
        unk_18C = 0;
    }
}

// Unducks the stream (arg_0 the rate; -1 for dword_44D4CC).
// match: ?sub_86C40@type_44E8D8@@QAEXM@Z @ 0x00086C40
// sp-match: ?sub_86C40@type_44E8D8@@QAEXM@Z @ 0x0006C6F0
void type_44E8D8::sub_86C40(RwReal arg_0)
{
    RwChar var_108[0x100];
    RwInt32 var_10C;

    if (unk_188)
    {
        if (dword_44E860 && dword_44E864)
        {
            sprintf(var_108, "AudioStream %d: Unducking!", unk_248->unk_20);
        }
        for (var_10C = 0; var_10C < 8; var_10C++)
        {
            unk_190[var_10C] = unk_1F0[var_10C];
            if (arg_0 == -1.0f)
            {
                unk_1D0[var_10C] = 1.0f / dword_44D4CC;
            }
            else
            {
                unk_1D0[var_10C] = 1.0f / arg_0;
            }
        }
        unk_188 = 0;
        unk_18C = 1;
    }
}

// match: ?sub_86D70@type_44E8D8@@QAEXH@Z @ 0x00086D70
// sp-match: ?sub_86D70@type_44E8D8@@QAEXH@Z @ 0x0006C990
void type_44E8D8::sub_86D70(RwInt32 arg_0)
{
    RwChar var_108[0x100];

    if (unk_1B0[arg_0] != unk_190[arg_0])
    {
        if (unk_1B0[arg_0] < unk_190[arg_0])
        {
            unk_1B0[arg_0] = unk_1B0[arg_0] + unk_1D0[arg_0];
            if (unk_1B0[arg_0] >= unk_190[arg_0])
            {
                unk_1B0[arg_0] = unk_190[arg_0];
                if (unk_18C)
                {
                    unk_18C = 0;
                    unk_1D0[arg_0] = unk_210[arg_0];
                    if (unk_248)
                    {
                        if (dword_44E860 && dword_44E864)
                        {
                            sprintf(var_108, "AudioStream %d: Unducking Finished!", unk_248->unk_20);
                        }
                    }
                    else if (dword_44E860 && dword_44E864)
                    {
                        sprintf(var_108, "AudioStream ??: Unducking Finished!");
                    }
                }
            }
        }
        else
        {
            unk_1B0[arg_0] = unk_1B0[arg_0] - unk_1D0[arg_0];
            if (unk_1B0[arg_0] <= unk_190[arg_0])
            {
                unk_1B0[arg_0] = unk_190[arg_0];
                if (unk_18C)
                {
                    unk_18C = 0;
                    unk_1D0[arg_0] = unk_210[arg_0];
                    if (unk_248)
                    {
                        if (dword_44E860 && dword_44E864)
                        {
                            sprintf(var_108, "AudioStream %d: Inverted Unducking Finished! That's really wierd!",
                                    unk_248->unk_20);
                        }
                    }
                    else if (dword_44E860 && dword_44E864)
                    {
                        sprintf(var_108, "AudioStream ??: ##!!## Inverted Unducking Finished! That's really strange!");
                    }
                }
            }
        }
        if (unk_1B0[arg_0] > 1.0f)
        {
            unk_1B0[arg_0] = 1.0f;
        }
        if (unk_1B0[arg_0] < 0.0f)
        {
            unk_1B0[arg_0] = 0;
        }
    }
}

// match: ?sub_870B0@type_44E8D8@@QAE_NXZ @ 0x000870B0
// sp-match: ?sub_870B0@type_44E8D8@@QAE_NXZ @ 0x0006CBB0
bool type_44E8D8::sub_870B0()
{
    if (unk_248->unk_24 == 0x4F || unk_248->unk_24 == 0x50 || unk_248->unk_24 == 0x55 || unk_248->unk_24 == 0x82)
    {
        if (dword_44E868)
        {
            printf("[----!!!! Audio stream %d (#%d)Is a STOP stream... stopping channel.\n", unk_248->unk_20,
                   unk_248->unk_24);
        }
        unk_180 = 0x10;
        return false;
    }
    if (unk_248->unk_24 == 0x61 || unk_248->unk_24 == 0x18 || unk_248->unk_24 == 0x1C || unk_248->unk_24 == 0x1F
        || unk_248->unk_24 == 0x3A || unk_248->unk_24 == 0xA6 || unk_248->unk_24 == 0xA8 || unk_248->unk_24 == 0xBD)
    {
        unk_180 = 0x10;
        if (dword_44E868)
        {
            printf("[----!!!! Audio stream %d (#%d)Blacklisted.Ignoring and going to inactive.\n", unk_248->unk_20,
                   unk_248->unk_24);
        }
        return false;
    }
    if (dword_44E5F0[unk_248->unk_20])
    {
        unk_180 = 0x10;
        return false;
    }
    if (!unk_01[0])
    {
        unk_180 = 1;
        return false;
    }
    return true;
}

// match: ?sub_87250@type_44E8D8@@QAEXXZ @ 0x00087250
// sp-match: ?sub_87250@type_44E8D8@@QAEXXZ @ 0x0006CC90
void type_44E8D8::sub_87250()
{
    type_87250 var_8;
    type_87250_e var_18;

    unk_250 = 0;
    unk_188 = 0;
    unk_18C = 0;
    unk_15C = unk_01;
    unk_174 = dword_428E74;
    unk_178 = dword_428E78;
    unk_17C = unk_248->unk_1C;
    var_8.unk_04 = 1;
    var_8.unk_00 = &var_18;
    var_18.unk_04 = 1;
    var_18.unk_0C = 2;
    var_18.unk_08 = 0;
    sprintf(unk_154, "%.4d", unk_248->unk_24);
    var_18.unk_00 = unk_154;
    sprintf(byte_4B1F68, "%s", unk_01);
#ifdef CODFH_SP // single player (SP 0x6CD2C) leaves track 0071 idle on level 1 when dword_4B8780 is set
    if (sub_19B050() == 1 && dword_4B8780 && strcmp(unk_154, "0071") == 0)
    {
        unk_180 = 1;
        return;
    }
#endif
    sub_240010(unk_104, &unk_15C);
    sub_23FE30(unk_104, &var_8);
    if (dword_44E8A0 == 2)
    {
        sub_2401B0(unk_104, flt_428E30);
    }
    else if (dword_44E898 == 2)
    {
        sub_2401B0(unk_104, flt_44E808);
    }
}

// match: ?sub_873B0@type_44E8D8@@QAEXXZ @ 0x000873B0
// sp-match: ?sub_873B0@type_44E8D8@@QAEXXZ @ 0x0006CF50
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void type_44E8D8::sub_873B0()
{
    RwUInt32 var_94;
    RwUInt32 var90;
    type_873B0_a lv_8C;
    type_873B0_b var_78;
    bool slot_65;
    RwInt32 var_64;
    const RwChar *stk_60;
    RwInt32 y5C;
    type_873B0_c lv_10;

    dword_4B206C++;
    if (dword_4B206C == 4)
    {
        dword_4B206C = 1;
    }
    if (!unk_104)
    {
        return;
    }
    if (unk_184 && unk_1B0[0] <= 0.0f && unk_1B0[1] <= 0.0f && unk_1B0[2] <= 0.0f && unk_1B0[3] <= 0.0f
        && unk_1B0[4] <= 0.0f && unk_1B0[5] <= 0.0f && unk_1B0[6] <= 0.0f && unk_1B0[7] <= 0.0f)
    {
        sub_86750();
        return;
    }
    for (var_64 = 0; var_64 < 8; var_64++)
    {
        sub_86D70(var_64);
    }
    unk_108 = sub_240120(unk_104);
    unk_10C = sub_240140(unk_104);
    unk_110 = sub_240130(unk_104);
    RwChar stk_58[0x40] = { 0 };

    switch (unk_108)
    {
    case 0:
        stk_60 = "nastatus";
        break;
    case 2:
        stk_60 = "opening";
        break;
    case 3:
        stk_60 = "stopped";
        break;
    case 4:
        stk_60 = "pausing";
        break;
    case 5:
        stk_60 = "paused";
        break;
    case 6:
        stk_60 = "playing";
        break;
    case 7:
        stk_60 = "starved";
        break;
    case 8:
        stk_60 = "stopping";
        break;
    case 9:
        stk_60 = "nomedia";
        break;
    default:
        stk_60 = "(error)";
        break;
    }
    sprintf(stk_58, "s: %s", stk_60);
    switch (unk_110)
    {
    case 0:
        stk_60 = "nastatus";
        break;
    case 2:
        stk_60 = "opening";
        break;
    case 3:
        stk_60 = "stopped";
        break;
    case 4:
        stk_60 = "pausing";
        break;
    case 5:
        stk_60 = "paused";
        break;
    case 6:
        stk_60 = "playing";
        break;
    case 7:
        stk_60 = "starved";
        break;
    case 8:
        stk_60 = "stopping";
        break;
    default:
        stk_60 = "(error)";
        break;
    }
    sprintf(stk_58 + strlen(stk_58), " m: %s", stk_60);
    switch (unk_10C)
    {
    case 0:
        stk_60 = "nastatus";
        break;
    case 2:
        stk_60 = "initializing";
        break;
    case 3:
        stk_60 = "stopped";
        break;
    case 4:
        stk_60 = "pausing";
        break;
    case 5:
        stk_60 = "paused";
        break;
    case 6:
        stk_60 = "playing";
        break;
    case 7:
        stk_60 = "starved";
        break;
    case 8:
        stk_60 = "stopping";
        break;
    default:
        stk_60 = "(error)";
        break;
    }
    sprintf(stk_58 + strlen(stk_58), " r: %s", stk_60);
    switch (unk_180)
    {
    case 19:
        if (!dword_4B2068)
        {
            y5C = dword_4AF038[0].unk_00.unk_00.unk_00 != -1 && dword_4AF038[0].unk_00.unk_00.unk_04 != -1;
            if (y5C)
            {
                break;
            }
            dword_4B2068 = 1;
            dword_44D4B4 = 1;
            sprintf(byte_4B1F68, "%s", unk_01);
            sub_81EB0(1, "Bounty!ARRRR!", 0);
            unk_180 = 0x14;
        }
        break;
    case 20:
        if (!dword_44D4B4)
        {
            unk_180 = 2;
        }
        break;
    case 2:
        if (unk_108 == 2 || unk_108 == 8)
        {
            break;
        }
        if (unk_108 == 3)
        {
            unk_180 = 0xC;
            break;
        }
        if (unk_108 != 9)
        {
            sub_2400E0(unk_104, 1);
        }
        unk_180 = 3;
        break;
    case 3:
        if (unk_108 == 9)
        {
            unk_180 = 4;
        }
        if (unk_108 == 3)
        {
            sub_240010(unk_104, 0);
            unk_180 = 4;
        }
        break;
    case 4:
        if (unk_108 == 9)
        {
            if (!sub_870B0())
            {
                unk_180 = 0x10;
                break;
            }
            if (sub_886D0())
            {
                break;
            }
            unk_180 = 5;
            sub_87250();
        }
        break;
    case 5:
        unk_250++;
        unk_24C = unk_250 > 0xB4;
        if (unk_108 == 3)
        {
            sub_2400E0(unk_104, 2);
            if (unk_248)
            {
                sub_86860(unk_248->unk_1C);
            }
            if (dword_44E8C0)
            {
                sub_86890(-1.0f);
            }
            unk_180 = 6;
        }
        if (unk_108 == 9 && dword_44E868)
        {
            printf("[----!!!! Audio stream %d (#%d)Probably couldn't allocate enough memory! NOOOO??\n",
                   unk_248->unk_20, unk_248->unk_24);
        }
        break;
    case 6:
        if (unk_108 == 6)
        {
            unk_24C = 0;
            slot_65 = true;
            if (slot_65)
            {
                lv_8C.unk_0C = 1;
                lv_8C.unk_04 = 3;
                lv_8C.unk_00 = 0;
                sub_240240(unk_104, &lv_8C);
                unk_234 = lv_8C.unk_10;
                for (var90 = 0; var90 < unk_234; var90++)
                {
                    var_78.unk_08 = var90;
                    var_78.unk_00 = 0;
                    var_78.unk_04 = 3;
                    sub_240370(unk_104, &var_78);
                    unk_238[var90] = var_78.unk_0C;
                }
                unk_180 = 7;
                if (dword_44E868)
                {
                    printf("[----!!!! Audio stream %d (#%d)Actually Playing\n", unk_248->unk_20, unk_248->unk_24);
                }
            }
        }
        break;
    case 7:
        if (dword_44BAD0)
        {
            break;
        }
        if (dword_44E8D4)
        {
            break;
        }
        if (unk_108 == 7)
        {
            if (dword_44E868)
            {
                if (unk_248)
                {
                    if (unk_248->unk_20 == 0)
                    {
                        printf("<===!!!! Audio stream A (#%d)is starved!!\n", unk_248->unk_24);
                    }
                    if (unk_248->unk_20 == 1)
                    {
                        printf("<===!!!! Audio stream B (#%d) is starved!!\n", unk_248->unk_24);
                    }
                    if (unk_248->unk_20 == 2)
                    {
                        printf("<===!!!! Audio stream C (#%d) is starved!!\n", unk_248->unk_24);
                    }
                }
                else
                {
                    printf("<===UNKNOWN Audio stream is starved!! WHAAAAT?\n");
                }
            }
            break;
        }
        if (unk_108 == 6)
        {
            for (var_94 = 0; var_94 < unk_234; var_94++)
            {
                if (unk_238[var_94] == 2)
                {
                    lv_10.unk_00 = var_94;
                    lv_10.unk_0C = unk_1B0[var_94];
                    lv_10.unk_04 = 0;
                    lv_10.unk_08 = 0;
                    sub_240150(unk_104, &lv_10);
                    lv_10.unk_04 = 1;
                    lv_10.unk_08 = 1;
                    sub_240150(unk_104, &lv_10);
                    lv_10.unk_0C = 0;
                    lv_10.unk_04 = 1;
                    lv_10.unk_08 = 0;
                    sub_240150(unk_104, &lv_10);
                    lv_10.unk_04 = 0;
                    lv_10.unk_08 = 1;
                    sub_240150(unk_104, &lv_10);
                }
                else if (unk_238[var_94] == 1)
                {
                    lv_10.unk_00 = var_94;
                    lv_10.unk_0C = unk_1B0[var_94];
                    lv_10.unk_04 = 0;
                    lv_10.unk_08 = 0;
                    sub_240150(unk_104, &lv_10);
                    lv_10.unk_08 = 1;
                    sub_240150(unk_104, &lv_10);
                }
            }
        }
        if (unk_108 == 3)
        {
            if (dword_44E868)
            {
                printf("[----!!!! Audio stream %d (#%d)Stopped on it's own. Disconnecting and going to INACTIVE\n",
                       unk_248->unk_20, unk_248->unk_24);
            }
            sub_240010(unk_104, 0);
            unk_180 = 0x10;
        }
        if (unk_108 == 9)
        {
            if (dword_44E868)
            {
                printf("[----!!!! Audio stream %d (#%d)Magically went to no media! going to INACTIVE\n",
                       unk_248->unk_20, unk_248->unk_24);
            }
            unk_180 = 0x10;
        }
        break;
    case 8:
        if (dword_44E868)
        {
            printf("[----!!!! Audio stream %d (#%d)Commanded to recover from starvation!\n", unk_248->unk_20,
                   unk_248->unk_24);
        }
        sub_2400E0(unk_104, 3);
        unk_180 = 5;
        break;
    case 9:
        if (unk_108 != 8 && unk_108 != 3 && unk_108 != 9)
        {
            if (dword_44E868)
            {
                printf("[----!!!! Audio stream %d (#%d)Commanded to pause\n", unk_248->unk_20, unk_248->unk_24);
            }
            sub_2400E0(unk_104, 3);
            unk_180 = 0xA;
        }
        else if (unk_108 == 3 && unk_180 != 0xF)
        {
            if (dword_44E868)
            {
                printf("[----!!!! Audio stream %d (#%d)Commanded to pause\n", unk_248->unk_20, unk_248->unk_24);
            }
            sub_2400E0(unk_104, 3);
            unk_180 = 0xA;
        }
        else
        {
            unk_180 = 0x10;
        }
        break;
    case 10:
        if (unk_108 == 5)
        {
            unk_180 = 0xB;
        }
        if (unk_108 == 8 && unk_108 == 3 && unk_108 == 9)
        {
            unk_180 = 0x10;
        }
        break;
    case 12:
        if (unk_108 != 9)
        {
            if (dword_44E868)
            {
                printf("[----!!!! Audio stream %d (#%d)Commanded to UN-Pause\n", unk_248->unk_20, unk_248->unk_24);
            }
            sub_2400E0(unk_104, 2);
            unk_180 = 6;
        }
        break;
    case 13:
        if (unk_108 == 2 || unk_108 == 8 || unk_108 == 3)
        {
            break;
        }
        if (!sub_870B0())
        {
            unk_180 = 0x10;
            break;
        }
        if (sub_886D0())
        {
            break;
        }
        unk_180 = 0xE;
        sub_87250();
        break;
    case 14:
        unk_250++;
        unk_24C = unk_250 > 0xB4;
        if (unk_108 == 3)
        {
            if (!(dword_4B9194 & 1))
            {
                sub_6B5F0("StreamPrimedAndReady", 0, 0, 0, 0, 0, 1, 0);
            }
            unk_180 = 0xF;
            unk_24C = 0;
            if (dword_44E868)
            {
                printf("[----!!!! Audio stream %d (#%d)Is PRIMED AND READY\n", unk_248->unk_20, unk_248->unk_24);
            }
        }
        break;
    case 16:
        if (unk_108 != 3 && unk_108 != 8 && unk_108 != 9)
        {
            if (dword_44E868)
            {
                printf("[----!!!! Audio stream %d (#%d)COMMANDED TO STOP AND DISCONNECT\n", unk_248->unk_20,
                       unk_248->unk_24);
            }
            sub_2400E0(unk_104, 1);
        }
        unk_180 = 0x11;
        if (dword_44E868)
        {
            printf("[----!!!! Audio stream %d (#%d)WAITING UNTIL STOPPED\n", unk_248->unk_20, unk_248->unk_24);
        }
        break;
    case 17:
        if (unk_108 == 3 && unk_110 == 3 && unk_10C == 3)
        {
            if (dword_44E868)
            {
                printf("[----!!!! Audio stream %d (#%d)DISCONNECTING\n", unk_248->unk_20, unk_248->unk_24);
            }
            sub_240010(unk_104, 0);
            if (dword_44E868)
            {
                printf("[----!!!! Audio stream %d (#%d)WAITING UNTIL DISCONNECTED\n", unk_248->unk_20,
                       unk_248->unk_24);
            }
            unk_180 = 0x12;
        }
        if (unk_108 == 9)
        {
            unk_180 = 0x12;
        }
        break;
    case 18:
        if (unk_108 == 9)
        {
            if (dword_44E868)
            {
                printf("[----!!!! Audio stream %d (#%d)SHUT DOWN SUCCESSFULLY\n", unk_248->unk_20, unk_248->unk_24);
            }
            unk_180 = 1;
        }
        break;
    }
}

#ifdef CODFH_SP
// Single player's disc-error handler (unit_19CD50, SP 0x12C410): its one-argument checks
// after the stream reads call it where multiplayer calls the empty sub_19A750.
void sp_sub_12C410(void *arg_0);
#endif

// Reads the pending bank file (arg_0 set: from the loading thread, with the
// stream lock; clear: a word of it, as a probe).
// match: ?sub_885B0@@YAXH@Z @ 0x000885B0
// sp-match: ?sub_885B0@@YAXH@Z @ 0x0006CDE0
void sub_885B0(RwInt32 arg_0)
{
    RwStream *var_4;
    RwStream *v8;
    RwInt32 varC;

    if (arg_0)
    {
        sub_82350();
    }
    var_4 = RwStreamOpen(rwSTREAMFILENAME, rwSTREAMREAD, byte_4B1F68);
    if (var_4)
    {
        if (!arg_0)
        {
            v8 = RwStreamReadInt32(var_4, &varC, sizeof(RwInt32));
#ifdef CODFH_SP // the disc-error check (SP 0x6CE19 calls 0x12C410)
            sp_sub_12C410((void *)v8);
#else
            sub_19A750(v8);
#endif
        }
        RwStreamClose(var_4, 0);
    }
    if (arg_0)
    {
        sub_82360();
        dword_4B2068 = 0;
        dword_44D4B4 = 0;
    }
}

// match: ?sub_88640@@YAHPAX0PAUtype_88640@@@Z @ 0x00088640
// sp-match: ?sub_88640@@YAHPAX0PAUtype_88640@@@Z @ 0x0006CE90
RwInt32 sub_88640(void *arg_0, void *arg_4, type_88640 *arg_8)
{
    type_88640 *var_4;

    var_4 = arg_8;
    var_4->unk_00 = (void *)sub_88670;
    var_4->unk_04 = (void *)(void (*)(void *))sub_19A750;
    var_4->unk_08 = arg_4;
    return 0;
}

// match: ?sub_88670@@YAHPAUtype_88670_0@@PAXPAUtype_88670_8@@@Z @ 0x00088670
// sp-match: ?sub_88670@@YAHPAUtype_88670_0@@PAXPAUtype_88670_8@@@Z @ 0x0006CE50
RwInt32 sub_88670(type_88670_0 *arg_0, void *arg_4, type_88670_8 *arg_8)
{
    type_88670_8 *var_4;
    type_88670_8 *local_8;

    if (!RwaUUIDCompare(arg_0->unk_00, unk_3ED29C))
    {
        var_4 = arg_8;
        var_4->unk_44 = 0x20000; // not an address: the buffer's size
        var_4->unk_48 = arg_4;
    }
    if (!RwaUUIDCompare(arg_0->unk_00, unk_3EDF6C))
    {
        local_8 = arg_8;
    }
    return 0;
}

// Whether any player is busy; it answers 0 before it looks.
// match: ?sub_886D0@type_44E8D8@@QAEHXZ @ 0x000886D0
// sp-match: ?sub_886D0@type_44E8D8@@QAEHXZ @ 0x0006CEB0
RwInt32 type_44E8D8::sub_886D0()
{
    RwInt32 var_4;
    RwInt32 local_8;

    return 0;
    for (local_8 = 0; local_8 < 3; local_8++)
    {
        switch (dword_44E8D8[local_8].unk_108)
        {
        case 2:
        case 4:
        case 7:
        case 8:
            var_4 = 1;
        }
        switch (dword_44E8D8[local_8].unk_110)
        {
        case 2:
        case 4:
        case 7:
        case 8:
            var_4 = 1;
        }
        switch (dword_44E8D8[local_8].unk_10C)
        {
        case 2:
        case 4:
        case 7:
        case 8:
            var_4 = 1;
        }
        switch (dword_44E8D8[local_8].unk_180)
        {
        case 6:
        case 12:
        case 14:
        case 15:
            var_4 = 1;
        }
    }
    return var_4;
}












// Members /OPT:ICF folded into shared trivial bodies (config/aliases.txt): defined here for
// the authentic link (PLAN M7); the placement link takes the shared bodies.

// ?pDtor@type_44E8D8@@QAEXXZ (folded into the empty body at 0x1E41C0)
void type_44E8D8::pDtor()
{
}
