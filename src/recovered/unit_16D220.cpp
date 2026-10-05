// The profiler (game/profiler.h): the timing sections and the frame's
// counters.

#include "rw/ostypes.h"
#include "game/profiler.h"
#include "rw/bavector.h"
#include "game/debugmenu.h"
#include "rws/gftime.h"
#include <string.h>

// Its data definitions (PLAN M5), in the image's address order.
// 0x003DCD44
extern const RwReal flt_3DCD44 = 16.666666f;
// 0x004E23B0
type_16D6E0 dword_4E23B0;
// 0x004E23CC
type_16D6E0 dword_4E23CC;
// 0x004E23E8
type_4E23E8 dword_4E23E8[49];
// 0x004E3584
RwInt32 dword_4E3584;
// 0x004E3588
RwInt32 dword_4E3588;
// End of its data definitions.


// Its data (PLAN M5): literals, constants and tables where the image has them.
// match: ?flt_3DCD44@@3MB @ 0x003DCD44
// match: ??_C@_06OCNDMDBG@Clones?$AA@ @ 0x003DCD48
// match: ??_C@_0P@ELEHDBJP@WorldColl?5Line?$AA@ @ 0x003DCD50
// match: ??_C@_06JCDJGKII@Decals?$AA@ @ 0x003DCD60
// match: ??_C@_07LCEKACHM@Shrimps?$AA@ @ 0x003DCD68
// match: ??_C@_07GANOGIPG@Shadows?$AA@ @ 0x003DCD70
// match: ??_C@_08JPOODBIA@GameLoop?$AA@ @ 0x003DCD78
// match: ??_C@_05OJBIAJFH@Shell?$AA@ @ 0x003DCD84
// match: ??_C@_0BF@NGMIABFP@Atomic?5Renderer?5CB?5C?$AA@ @ 0x003DCD8C
// match: ??_C@_0BF@MPNDDABO@Atomic?5Renderer?5CB?5B?$AA@ @ 0x003DCDA4
// match: ??_C@_0BF@OEPOGDNN@Atomic?5Renderer?5CB?5A?$AA@ @ 0x003DCDBC
// match: ??_C@_0BA@PAMGHHMP@Atomic?5Renderer?$AA@ @ 0x003DCDD4
// match: ??_C@_0BJ@CHIGKHNG@Particles?1Decals?1Shadows?$AA@ @ 0x003DCDE4
// match: ??_C@_08EBFMCOPJ@RwStudio?$AA@ @ 0x003DCE00
// match: ??_C@_08BBBMCLMG@GameEnts?$AA@ @ 0x003DCE0C
// match: ??_C@_08FBPDBPOE@Sections?$AA@ @ 0x003DCE18
// match: ??_C@_06HDCPEBNJ@SkyBox?$AA@ @ 0x003DCE24
// match: ??_C@_0M@CODONACD@CameraClear?$AA@ @ 0x003DCE2C
// match: ??_C@_0P@MEGALKLI@Entity?5Trigger?$AA@ @ 0x003DCE38
// match: ??_C@_0BB@DPPFMGJD@Entity?5Collision?$AA@ @ 0x003DCE48
// match: ??_C@_0P@OIHLHONL@Entity?5Physics?$AA@ @ 0x003DCE5C
// match: ??_C@_08JHHJHPMD@Class?5AI?$AA@ @ 0x003DCE6C
// match: ??_C@_0P@COJFKCGN@Animation?5Post?$AA@ @ 0x003DCE78
// match: ??_C@_09ONEINPNJ@Animation?$AA@ @ 0x003DCE88
// match: ??_C@_0N@CHJPIFDC@Entity?5Class?$AA@ @ 0x003DCE94
// match: ??_C@_09NCLMNOLJ@Particles?$AA@ @ 0x003DCEA4
// match: ??_C@_02FAFNDFFG@AI?$AA@ @ 0x003DCEB0
// match: ??_C@_0M@OKIEBFGA@Projectiles?$AA@ @ 0x003DCEB4
// match: ??_C@_05KKCMAPLJ@Audio?$AA@ @ 0x003DCEC0
// match: ??_C@_0O@JHNPDMBC@Entity?5Update?$AA@ @ 0x003DCEC8
// match: ??_C@_06CEFAHBNL@Script?$AA@ @ 0x003DCED8
// match: ??_C@_08KPLHIKIL@PageFlip?$AA@ @ 0x003DCEE0
// match: ??_C@_06EPLDPNDB@Render?$AA@ @ 0x003DCEEC
// match: ??_C@_05ICOCHDKG@Logic?$AA@ @ 0x003DCEF4

// match: ?sub_16D220@type_4E23E8@@QAEXPBDE@Z @ 0x0016D220

void type_4E23E8::sub_16D220(const RwChar *arg_0, RwUInt8 arg_4)
{
    unk_58 = arg_4;
    sub_16D6E0(&unk_00);
    sub_16D6E0(&unk_1C);
    strncpy(unk_38, arg_0, 0x1F);
    unk_38[0x1F] = 0;
}

// match: ?sub_16D270@type_4E23E8@@QAEXXZ @ 0x0016D270
void type_4E23E8::sub_16D270()
{
    sub_16D6E0(&unk_00);
    sub_16D6E0(&unk_1C);
}

// match: ?sub_16D2A0@type_4E23E8@@QAEXXZ @ 0x0016D2A0
// Ends its frame: the extremes, the copy for the last frame, and this
// frame's counters cleared (not the extremes).
void type_4E23E8::sub_16D2A0()
{
    if (unk_00.unk_0C < unk_00.unk_14)
        unk_00.unk_14 = unk_00.unk_0C;
    if (unk_00.unk_0C > unk_00.unk_18)
        unk_00.unk_18 = unk_00.unk_0C;
    unk_1C = unk_00;
    unk_00.unk_00 = 0;
    unk_00.unk_04 = 0;
    unk_00.unk_08 = 0;
    unk_00.unk_0C = 0;
    unk_00.unk_10 = 0;
}

// match: ?sub_16D330@type_4E23E8@@QAEXXZ @ 0x0016D330
void type_4E23E8::sub_16D330()
{
    unk_00.unk_00 = RWS::Time::GetTime();
    unk_00.unk_10++;
}

// match: ?sub_16D360@type_4E23E8@@QAEXXZ @ 0x0016D360
void type_4E23E8::sub_16D360()
{
    unk_00.unk_04 = RWS::Time::GetTime();
    unk_00.unk_08 = unk_00.unk_04 - unk_00.unk_00 + unk_00.unk_08;
    unk_00.unk_0C = unk_00.unk_0C + unk_00.unk_08;
}

// match: ?sub_16D3A0@@YAXXZ @ 0x0016D3A0
// Names the sections (the flag: shown).
void sub_16D3A0()
{
    dword_4E23E8[0].sub_16D220("Logic", 1);
    dword_4E23E8[1].sub_16D220("Render", 1);
    dword_4E23E8[2].sub_16D220("PageFlip", 1);
    dword_4E23E8[3].sub_16D220("Script", 0);
    dword_4E23E8[4].sub_16D220("Entity Update", 1);
    dword_4E23E8[5].sub_16D220("Audio", 1);
    dword_4E23E8[6].sub_16D220("Projectiles", 1);
    dword_4E23E8[7].sub_16D220("AI", 1);
    dword_4E23E8[8].sub_16D220("Particles", 1);
    dword_4E23E8[21].sub_16D220("Entity Class", 1);
    dword_4E23E8[22].sub_16D220("Animation", 1);
    dword_4E23E8[23].sub_16D220("Animation Post", 1);
    dword_4E23E8[24].sub_16D220("Class AI", 0);
    dword_4E23E8[25].sub_16D220("Entity Physics", 0);
    dword_4E23E8[26].sub_16D220("Entity Collision", 1);
    dword_4E23E8[27].sub_16D220("Entity Trigger", 0);
    dword_4E23E8[9].sub_16D220("CameraClear", 0);
    dword_4E23E8[10].sub_16D220("SkyBox", 0);
    dword_4E23E8[11].sub_16D220("Sections", 1);
    dword_4E23E8[12].sub_16D220("GameEnts", 1);
    dword_4E23E8[13].sub_16D220("Projectiles", 0);
    dword_4E23E8[14].sub_16D220("RwStudio", 1);
    dword_4E23E8[15].sub_16D220("Particles/Decals/Shadows", 1);
    dword_4E23E8[16].sub_16D220("Player", 0);
    dword_4E23E8[17].sub_16D220("Atomic Renderer", 1);
    dword_4E23E8[18].sub_16D220("Atomic Renderer CB A", 0);
    dword_4E23E8[19].sub_16D220("Atomic Renderer CB B", 0);
    dword_4E23E8[20].sub_16D220("Atomic Renderer CB C", 0);
    dword_4E23E8[28].sub_16D220("Shell", 0);
    dword_4E23E8[29].sub_16D220("GameLoop", 0);
    dword_4E23E8[30].sub_16D220("Shadows", 0);
    dword_4E23E8[31].sub_16D220("Shrimps", 0);
    dword_4E23E8[32].sub_16D220("Decals", 0);
    dword_4E23E8[33].sub_16D220("WorldColl Line", 0);
    dword_4E23E8[34].sub_16D220("Clones", 0);
    sub_16D6E0(&dword_4E23CC);
    sub_16D6E0(&dword_4E23B0);
    dword_4E3584 = 0;
    dword_4E3588 = 0;
}

// match: ?sub_16D630@@YAXXZ @ 0x0016D630
// Clears every counter.
void sub_16D630()
{
    RwInt32 var_4;

    sub_16D6E0(&dword_4E23CC);
    sub_16D6E0(&dword_4E23B0);
    for (var_4 = 0; var_4 < 49; var_4++)
        dword_4E23E8[var_4].sub_16D270();
    dword_4E3584 = 0;
    dword_4E3588 = 0;
}

// match: ?sub_16D6A0@@YAXXZ @ 0x0016D6A0
void sub_16D6A0()
{
    RwInt32 var_4;

    for (var_4 = 0; var_4 < 49; var_4++)
        dword_4E23E8[var_4].pDtor();
}

// match: ?sub_16D6E0@@YAXPAUtype_16D6E0@@@Z @ 0x0016D6E0
void sub_16D6E0(type_16D6E0 *arg_0)
{
    arg_0->unk_00 = 0;
    arg_0->unk_04 = 0;
    arg_0->unk_08 = 0;
    arg_0->unk_0C = 0;
    arg_0->unk_10 = 0;
    arg_0->unk_14 = -1;
    arg_0->unk_18 = 0;
}

// match: ?sub_16D730@@YAXXZ @ 0x0016D730
// Starts the frame.
void sub_16D730()
{
    dword_4E23CC.unk_00 = RWS::Time::GetTime();
}

// match: ?sub_16D740@@YAXXZ @ 0x0016D740
// Ends the frame, then every section's (sub_16D780).
void sub_16D740()
{
    dword_4E23CC.unk_04 = RWS::Time::GetTime();
    dword_4E23CC.unk_08 = dword_4E23CC.unk_04 - dword_4E23CC.unk_00;
    dword_4E23CC.unk_0C = dword_4E23CC.unk_0C + dword_4E23CC.unk_08;
    sub_16D780();
}

// match: ?sub_16D780@@YAXXZ @ 0x0016D780
void sub_16D780()
{
    RwInt32 var_4;

    dword_4E23B0 = dword_4E23CC;
    dword_4E23CC.unk_00 = 0;
    dword_4E23CC.unk_04 = 0;
    dword_4E23CC.unk_08 = 0;
    dword_4E23CC.unk_10 = 0;
    for (var_4 = 0; var_4 < 49; var_4++)
        dword_4E23E8[var_4].sub_16D2A0();
}

// match: ?sub_16D7F0@@YAXH@Z @ 0x0016D7F0
void sub_16D7F0(RwInt32 arg_0)
{
    if (arg_0 >= 0 && arg_0 < 49)
    {
        dword_42A598[arg_0].unk_20 -= RWS::Time::GetTime();
        dword_42A598[arg_0].unk_44++;
        dword_4E23E8[arg_0].sub_16D330();
    }
}

// match: ?sub_16D850@@YAXH@Z @ 0x0016D850
void sub_16D850(RwInt32 arg_0)
{
    if (arg_0 >= 0 && arg_0 < 49)
    {
        if (dword_42A598[arg_0].unk_44 > 0)
        {
            dword_42A598[arg_0].unk_20 += RWS::Time::GetTime();
            dword_42A598[arg_0].unk_44--;
        }
        dword_4E23E8[arg_0].sub_16D360();
    }
}

// Members /OPT:ICF folded into shared trivial bodies (config/aliases.txt): defined here for
// the authentic link (PLAN M7); the placement link takes the shared bodies.

// ?pDtor@type_4E23E8@@QAEXXZ (folded into the empty body at 0x1E41C0)
void type_4E23E8::pDtor()
{
}
