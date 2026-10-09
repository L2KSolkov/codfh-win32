// The front end's link to the network game (its one trace names it
// cUIInterface: "cUIInterface::startServer %s"): the settings kept for the
// front end, the level list, the players' names and scores kept for the
// lobby, the screens it opens, the vote queries, the sound and player
// options, and the objective hint text. Free functions over this unit's
// globals; the original file name is not in the image, so it is named for
// its start address.

#include "game/liveservice.h"
#include <stdio.h>
#include <string.h>
#include "rw/ostypes.h"
#include "game/gameloop.h"
#include "game/netmsg.h"
#include "game/mpgame.h"
#include "game/data.h"
#include "game/functions.h"
#include "game/fileio.h"
#include "game/loc.h"
#include "game/voice.h"
#include "game/startup.h"
#include "types/type_DC400.h"
#include "types/type_1DDE20_mask.h"
#include "types/type_505188.h"
#include "types/type_10F710.h"
#include "types/PlayerTrigger.h"
#include "types/soundbank.h"
#include "types/CGlobalSounds.h"
#include "game/uiglue.h"
#include "game/ingamepages.h"
#include "game/parsedfile.h"

// Its data definitions (PLAN M5), in the image's address order.
#ifndef CODFH_SP // MP only: unreferenced constants single player does not emit (not in default.xbe; /O2 keeps them only while they are external)
// 0x003E3794
extern const RwReal flt_3E3794 = 0.01f;
// 0x003E3798
extern const RwReal flt_3E3798 = 0.01f;
// 0x003E379C
extern const RwReal flt_3E379C = 16.666666f;
#endif
// 0x0042CBA8
RwInt32 dword_42CBA8 = 4;
// 0x0042CBAC
RwInt32 dword_42CBAC = 4;
// 0x0042CBB0
RwInt32 dword_42CBB0 = 4;
// 0x0042CBB4
RwChar byte_42CBB4[8] = "mrsh";
// 0x0042CBBC
RwChar byte_42CBBC[12] = "winfo_N_W";
// 0x0042CBC8
RwChar byte_42CBC8[8] = "eurg";
// 0x004F8180
#ifndef CODFH_PLAIN
type_3E3860 *dword_4F8180;
#endif
// 0x004F8288
#ifndef CODFH_PLAIN
type_4F8288 dword_4F8288;
#endif
// 0x004FD6F0
RwInt32 dword_4FD6F0[16];
// 0x004FD730
RwInt32 dword_4FD730[16];
// 0x004FD770
RwInt32 dword_4FD770[16];
// 0x004FD7B0
RwInt32 dword_4FD7B0[16];
// 0x004FD7F0
RwChar byte_4FD7F0[16][0x18];
// 0x004FD970
RwUInt32 dword_4FD970;
// 0x004FD974
type_505188 *dword_4FD974;
// 0x004FD978
RwInt32 dword_4FD978;
// 0x004FD97C
RwUInt8 unk_4FD97C;
// 0x004FD98C
RwInt32 dword_4FD98C;
// 0x004FD990
RwChar byte_4FD990[0x100];
// 0x004FDA90
bool byte_4FDA90;
// 0x004FDA94
RwInt32 dword_4FDA94;
// 0x004FDA98
kujuUI::type_1E3DB0 *dword_4FDA98;
// 0x004FDA9C
RwInt32 dword_4FDA9C;
// 0x004FDAA0
RwInt32 dword_4FDAA0;
// 0x004FDAA4
RwInt32 dword_4FDAA4;
// 0x004FDAA8
RwUInt8 byte_4FDAA8;
// 0x004FDAB0
RwChar byte_4FDAB0[0x100];
// End of its data definitions.


// Globals with constructors defined here (their initializers and exit
// functions at the end of .text).
type_4FB9E0_08 unk_4FDBB0;


// Its data (PLAN M5): literals, constants and tables where the image has them.
// match: ?flt_3E3794@@3MB @ 0x003E3794
// match: ?flt_3E3798@@3MB @ 0x003E3798
// match: ?flt_3E379C@@3MB @ 0x003E379C
// match: ??_C@_0BO@FJLPKKLE@cUIInterface?3?3startServer?5?$CFs?6?$AA@ @ 0x003E37A0
// match: ??_C@_07GLJOEIKH@Syslink?$AA@ @ 0x003E37C0
// match: ??_C@_07OMBLCLEA@WANPlay?$AA@ @ 0x003E37C8
// match: ??_C@_08DANENMBE@_SCORE?$CFs?$AA@ @ 0x003E37D0
// match: ??_C@_07GMGCCEGE@_DEFEND?$AA@ @ 0x003E37DC
// match: ??_C@_07OMNCAGNE@_ATTACK?$AA@ @ 0x003E37E4
// match: ??_C@_05NFIIAEJM@HINT_?$AA@ @ 0x003E37EC
// match: __ehhandler$?sub_1C3D90@@YAXXZ>1>8 @ 0x0041F49C
// match: __ehhandler$?sub_1C3D90@@YAXXZ>1 @ 0x0041F4B4
// match: __ehhandler$?sub_1C43C0@@YA?AUtype_1CB670@@HH@Z>1>8 @ 0x0041F4D0
// match: __ehhandler$?sub_1C43C0@@YA?AUtype_1CB670@@HH@Z>1 @ 0x0041F4E0
// match: __ehhandler$?sub_1C5350@@YA?AUtype_1CB670@@XZ>1>8 @ 0x0041F4FC
// match: __ehhandler$?sub_1C5350@@YA?AUtype_1CB670@@XZ>1 @ 0x0041F534
// match: .CRT$XCU+0 @ 0x0042720C
// match: ?dword_42CBA8@@3HA @ 0x0042CBA8
// match: ?dword_42CBAC@@3HA @ 0x0042CBAC
// match: ?dword_42CBB0@@3HA @ 0x0042CBB0
// match: ?byte_42CBB4@@3PADA @ 0x0042CBB4
// match: ?byte_42CBBC@@3PADA @ 0x0042CBBC
// match: ?byte_42CBC8@@3PADA @ 0x0042CBC8

// match: _$E2 @ 0x0030C3D0
// match: _$E3 @ 0x0030EB30
// match: ?sub_1C3D20@@YAXXZ @ 0x001C3D20

void sub_1C3D20()
{
    if (((kujuUI::type_1C8DF0_104_00 *)&dword_4FB9E0)->sub_1E3480())
    {
        unk_4FDBB0.sub_1B46F0();
        unk_4FDBB0 = dword_4FB9E0.get_unk_40();
    }
}

// match: ?sub_1C3D60@@YAXH@Z @ 0x001C3D60
void sub_1C3D60(RwInt32 arg_0)
{
    dword_4FB9E0.sub_1B5600(unk_4FDBB0, arg_0);
}

// match: ?sub_1C3D80@@YAXH@Z @ 0x001C3D80
void sub_1C3D80(RwInt32 arg_0)
{
    unk_4FDBB0.unk_28 = arg_0;
}

// The level list (eight entries, each named twice by sub_19B060) and the
// lobby's players cleared.
// match: ?sub_1C3D90@@YAXXZ @ 0x001C3D90
// match: __ehhandler$?sub_1C3D90@@YAXXZ-0x1B @ 0x00303110
// match: __ehhandler$?sub_1C3D90@@YAXXZ @ 0x0030312B
void sub_1C3D90()
{
    RwUInt32 var_10;
    RwUInt32 loc14;

    dword_4FD970 = 8;
    dword_4FD974 = new type_505188[dword_4FD970];
    for (var_10 = 0; var_10 < dword_4FD970; var_10++)
    {
        dword_4FD974[var_10].set_unk_00(var_10);
        dword_4FD974[var_10].set_unk_04(sub_19B060(var_10 + 1));
        dword_4FD974[var_10].set_unk_20(sub_19B060(var_10 + 1));
        dword_4FD974[var_10].set_unk_3C(0x1F);
    }
    kujuUI::sub_1E7CE0((kujuUI::type_1E7CF0 *)&unk_4FDBE4);
    for (loc14 = 0; loc14 < 16; loc14++)
    {
        dword_4FD770[loc14] = 1;
        byte_4FD7F0[loc14][0] = 0;
        dword_4FD7B0[loc14] = 0;
        dword_4FD730[loc14] = 0;
        dword_4FD6F0[loc14] = 0;
    }
}

// match: ??_Etype_505188@@QAEPAXI@Z @ 0x001C3FE0

// match: ?sub_1C4050@@YAXXZ @ 0x001C4050
void sub_1C4050()
{
    kujuUI::sub_1E7CE0(0);
    delete[] dword_4FD974;
    dword_4FD974 = 0;
    dword_4FD970 = 0;
}

// The pending message shown once the screen allows.
// match: ?sub_1C40B0@@YAXM@Z @ 0x001C40B0
void sub_1C40B0(RwReal arg_0)
{
    if (sub_1C4C00() && !sub_215A90() && byte_4FDAB0[0])
    {
        sub_1C4A90(byte_4FDAB0);
        byte_4FDAB0[0] = 0;
    }
}

// The front end's sound: its keys and volumes reset, the settings
// applied, its music bank asked for.
// match: ?sub_1C40F0@@YAXXZ @ 0x001C40F0
void sub_1C40F0()
{
    type_825E0 var_10;

    dword_4FD978 = 1;
    dword_4B1C88.unk_00 = 0x67DCEEDD;
    dword_4B1C88.unk_04 = 0xC93BC875;
    dword_4B1C00.unk_00 = 0x84CE123E;
    dword_4B1C00.unk_04 = 0x0337A60D;
    dword_4B1B48.unk_00 = 0x84CE123E;
    dword_4B1B48.unk_04 = 0x0337A60D;
    dword_4B1C98.unk_00 = 0x677A3165;
    dword_4B1C98.unk_04 = 0x8A1D61B9;
    dword_44E720[0] = 2;
    dword_44E720[1] = 2;
    dword_44E720[2] = 2;
    dword_44E720[3] = 2;
    dword_44E720[4] = 2;
    dword_44E720[5] = 2;
    dword_44E720[6] = 2;
    dword_44E720[7] = 2;
    sub_83B20();
    var_10.unk_08 = 0;
    var_10.unk_0C = 0x28;
    var_10.unk_00.unk_00 = 0x5F7D7350;
    var_10.unk_00.unk_04 = 0x1035E68B;
    // A compiled-out check: the registers after it are one load on
    // (docs/toolchain.md); its condition is a stand-in with one load.
    if (!dword_4F28F0->unk_00)
    {
    }
    sub_82C70(&var_10, 0);
    dword_44E834 = 1;
}

// match: ?sub_1C41F0@@YAXXZ @ 0x001C41F0
void sub_1C41F0()
{
    // A compiled-out check: the registers after it are one load on
    // (docs/toolchain.md); its condition is a stand-in with one load.
    if (!dword_4F28F0->unk_00)
    {
    }
    sub_19B000(unk_4FDBB0.unk_28 + 1);
    dword_4FB9E0.sub_1B54B0(unk_4FDBB0.unk_28);
    dword_4FD978 = 0;
    sub_83DE0(0);
    sub_83B40();
    dword_44E834 = 0;
}

// Named by its trace: hosts a game on the level chosen, for as many
// players as the team masks allow, over the internet (arg_0) or the
// system link.
// match: ?startServer@@YAX_N@Z @ 0x001C4240
void startServer(bool arg_0)
{
    RwInt32 var_4;

    if (0)
        sub_1C8A30("cUIInterface::startServer %s\n", arg_0 ? "WANPlay" : "Syslink");
    // A compiled-out check: the registers after it are one load on
    // (docs/toolchain.md); its condition is a stand-in with one load.
    if (!dword_4F28F0->unk_00)
    {
    }
    switch (unk_4F61F8.unk_108)
    {
    case 1:
        var_4 = 4;
        break;
    case 2:
        var_4 = 8;
        break;
    case 4:
        var_4 = 16;
        break;
    default:
        var_4 = 16;
    }
    unk_4F7EB8.sub_1A9A70(unk_4FDBB0.unk_28, var_4, byte_4FD990, arg_0);
}

// match: ?sub_1C42E0@@YAPADXZ @ 0x001C42E0
RwChar *sub_1C42E0()
{
    return dword_4F28F0->unk_183;
}

// match: ?sub_1C42F0@@YAHXZ @ 0x001C42F0
RwInt32 sub_1C42F0()
{
    sub_1C46D0();
    return dword_4FD98C;
}

// match: ?sub_1C4300@@YAXPBD@Z @ 0x001C4300
void sub_1C4300(const RwChar *arg_0)
{
    strncpy(byte_4FD990, arg_0, 0x100);
}

// match: ?sub_1C4320@@YAPADXZ @ 0x001C4320
RwChar *sub_1C4320()
{
    return byte_4FD990;
}

// match: ?sub_1C4330@@YAPAEXZ @ 0x001C4330
RwUInt8 *sub_1C4330()
{
    return &unk_4FD97C;
}

// match: ?sub_1C4340@@YAXH@Z @ 0x001C4340
void sub_1C4340(RwInt32 arg_0)
{
    unk_4F7EB8.sub_1AFB90(arg_0);
    unk_4F7EB8.sub_1AFBB0();
}

// match: ?sub_1C4360@@YAHXZ @ 0x001C4360
RwInt32 sub_1C4360()
{
    return unk_4F7EB8.get_unk_2C0();
}

// match: ?sub_1C4380@@YAXH@Z @ 0x001C4380
void sub_1C4380(RwInt32 arg_0)
{
    unk_4F7EB8.sub_1AFF20(arg_0);
    unk_4F7EB8.sub_1AFBB0();
}

// match: ?sub_1C43A0@@YAHXZ @ 0x001C43A0
RwInt32 sub_1C43A0()
{
    return unk_4F7EB8.get_unk_2BC();
}

// The objective text for player arg_4's game type and the team arg_8: the
// key "winfo_N_W" with its letters put in.
// match: ?sub_1C43C0@@YA?AUtype_1CB670@@HH@Z @ 0x001C43C0
// match: __ehhandler$?sub_1C43C0@@YA?AUtype_1CB670@@HH@Z-0x21 @ 0x00303140
// match: __ehhandler$?sub_1C43C0@@YA?AUtype_1CB670@@HH@Z @ 0x00303161
type_1CB670 sub_1C43C0(RwInt32 arg_4, RwInt32 arg_8)
{
    RwInt32 var_10 = sub_1C4480(arg_4);

    if (var_10 < 4)
        byte_42CBBC[6] = byte_42CBC8[var_10];
    if (arg_8 < 4)
        byte_42CBBC[8] = byte_42CBB4[arg_8];
    type_1A5EA0 var_30(byte_42CBBC, 0);
    return type_1CB670(var_30);
}

// match: ?sub_1C4480@@YAHH@Z @ 0x001C4480
RwInt32 sub_1C4480(RwInt32 arg_0)
{
    return unk_4F7EB8.sub_1AF2F0(arg_0);
}

// match: ?sub_1C44A0@@YAXXZ @ 0x001C44A0
void sub_1C44A0()
{
    dword_4FB9E0.sub_1B5BC0();
}

// match: ?sub_1C44B0@@YAXH@Z @ 0x001C44B0
void sub_1C44B0(RwInt32 arg_0)
{
    sub_227560()->sub_2275F0(arg_0);
}

// match: ?sub_1C44D0@@YAXH@Z @ 0x001C44D0
void sub_1C44D0(RwInt32 arg_0)
{
    sub_227560()->sub_227660(arg_0);
}

// match: ?sub_1C44F0@@YAXXZ @ 0x001C44F0
void sub_1C44F0()
{
    if (unk_4F7EB8.get_unk_1A4())
        unk_4F7EB8.get_unk_1A4()->sub_1B8820();
}

// match: ?sub_1C4520@@YAXXZ @ 0x001C4520
void sub_1C4520()
{
    if (unk_4F7EB8.get_unk_1A4())
        unk_4F7EB8.get_unk_1A4_direct()->vf_23C(1.0f);
}

// match: ?sub_1C4560@@YAXH@Z @ 0x001C4560
void sub_1C4560(RwInt32 arg_0)
{
    unk_4F7EB8.get_unk_19C_direct()->vf_068(arg_0);
}

// match: ?sub_1C4590@@YAPBDH@Z @ 0x001C4590
const RwChar *sub_1C4590(RwInt32 arg_0)
{
    return sub_19B060(arg_0 + 1);
}

// match: ?sub_1C45B0@@YAXM@Z @ 0x001C45B0
void sub_1C45B0(RwReal arg_0)
{
    sub_1C45D0(sub_1C45E0() + arg_0);
}

// match: ?sub_1C45D0@@YAXM@Z @ 0x001C45D0
void sub_1C45D0(RwReal arg_0)
{
    // A compiled-out check: the registers after it are one load on
    // (docs/toolchain.md); its condition is a stand-in with one load.
    if (!dword_4F28F0->unk_00)
    {
    }
    dword_4FB9E0.unk_08.unk_14 = arg_0;
}

// match: ?sub_1C45E0@@YAMXZ @ 0x001C45E0
RwReal sub_1C45E0()
{
    return dword_4FB9E0.sub_1B6D80();
}

// match: ?sub_1C45F0@@YAHXZ @ 0x001C45F0
RwInt32 sub_1C45F0()
{
    return type_4F8054::get()->get_unk_B0()->get_unk_0C().sub_1D4A60();
}

// Player arg_0's name (refreshed while it plays), or 0.
// match: ?sub_1C4630@@YAPADI@Z @ 0x001C4630
RwChar *sub_1C4630(RwUInt32 arg_0)
{
    type_1DDE20_mask var_4 = sub_1C48D0();

    if (var_4.test(arg_0))
        sub_1C4720(arg_0);
    if (byte_4FD7F0[arg_0][0])
        return byte_4FD7F0[arg_0];
    return 0;
}

// match: ?sub_1C4690@@YAXXZ @ 0x001C4690
void sub_1C4690()
{
    RwUInt32 var_4;

    sub_1C46D0();
    for (var_4 = 0; var_4 < 16; var_4++)
        sub_1C4720(var_4);
}

// match: ?sub_1C46D0@@YAXXZ @ 0x001C46D0
void sub_1C46D0()
{
    if (type_4F8054::get()->get_unk_B0()->sub_1CFFC0())
        dword_4FD98C = type_4F8054::get()->get_unk_B0()->sub_1CFF90();
}

// Keeps player arg_0's name and team while it has a name.
// match: ?sub_1C4720@@YAXI@Z @ 0x001C4720
void sub_1C4720(RwUInt32 arg_0)
{
    RwChar *var_4 = type_4F8054::get()->get_unk_B0()->unk_90[arg_0].unk_00;

    if (var_4 && strlen(var_4) > 0)
    {
        strcpy(byte_4FD7F0[arg_0], var_4);
        dword_4FD770[arg_0] = sub_1C4880(arg_0);
    }
}

// Player arg_0's scores (live while it plays, else as kept).
// match: ?sub_1C47A0@@YAHI@Z @ 0x001C47A0
RwInt32 sub_1C47A0(RwUInt32 arg_0)
{
    type_1DDE20_mask var_4 = sub_1C48D0();

    if (var_4.test(arg_0))
        return unk_4F7EB8.unk_04.sub_1B3380(arg_0);
    return dword_4FD730[arg_0];
}

// match: ?sub_1C47E0@@YAHH@Z @ 0x001C47E0
RwInt32 sub_1C47E0(RwInt32 arg_0)
{
    return unk_4F7EB8.unk_04.sub_1B33C0(arg_0);
}

// match: ?sub_1C4800@@YAHI@Z @ 0x001C4800
RwInt32 sub_1C4800(RwUInt32 arg_0)
{
    type_1DDE20_mask var_4 = sub_1C48D0();

    if (var_4.test(arg_0))
        return unk_4F7EB8.unk_04.sub_1B3360(arg_0);
    return dword_4FD7B0[arg_0];
}

// match: ?sub_1C4840@@YAHI@Z @ 0x001C4840
RwInt32 sub_1C4840(RwUInt32 arg_0)
{
    type_1DDE20_mask var_4 = sub_1C48D0();

    if (var_4.test(arg_0))
        return unk_4F7EB8.unk_04.sub_1B33A0(arg_0);
    return dword_4FD6F0[arg_0];
}

// match: ?sub_1C4880@@YAHH@Z @ 0x001C4880
RwInt32 sub_1C4880(RwInt32 arg_0)
{
    return dword_4F8288.sub_1C2A90(arg_0);
}

// match: ?sub_1C48A0@@YA?AUtype_1DDE20_mask@@XZ @ 0x001C48A0
type_1DDE20_mask sub_1C48A0()
{
    return type_4F8054::get()->get_unk_B0()->sub_1A8050();
}

// match: ?sub_1C48D0@@YA?AUtype_1DDE20_mask@@XZ @ 0x001C48D0
type_1DDE20_mask sub_1C48D0()
{
    return type_4F8054::get()->get_unk_B0()->get_unk_0C();
}

// The front end's screens: each asked for (dword_4FDA94 notes which) and
// shown, the game unpaused.
// match: ?sub_1C4900@@YAXXZ @ 0x001C4900
void sub_1C4900()
{
    if (!sub_D7C00() && !sub_1FF250()->sub_200780())
    {
        dword_4FDA94 = 1;
        sub_1FF250()->sub_2008B0(0);
        sub_1FF250()->sub_2007A0(1);
        sub_D7C10(0);
    }
}

// match: ?sub_1C4960@@YAXXZ @ 0x001C4960
void sub_1C4960()
{
    dword_4FDA94 = 2;
    sub_1FF250()->sub_2008B0(1);
    sub_1FF250()->sub_2007A0(1);
    sub_D7C10(0);
}

// match: ?sub_1C49A0@@YAXXZ @ 0x001C49A0
void sub_1C49A0()
{
    dword_4FDA94 = 3;
    sub_1FF250()->sub_2008B0(2);
    sub_1FF250()->sub_2007A0(1);
    sub_D7C10(0);
}

// match: ?sub_1C49E0@@YAXXZ @ 0x001C49E0
void sub_1C49E0()
{
    sub_1FF250()->sub_2008B0(3);
    sub_1FF250()->sub_2007A0(1);
    sub_D7C10(0);
}

// match: ?sub_1C4A10@@YAXXZ @ 0x001C4A10
void sub_1C4A10()
{
    sub_1FF250()->sub_2007A0(0);
}

// match: ?sub_1C4A30@@YAXXZ @ 0x001C4A30
void sub_1C4A30()
{
    sub_1FF250()->sub_2008B0(6);
    sub_1FF250()->sub_2007A0(1);
    sub_D7C10(0);
}

// match: ?sub_1C4A60@@YAXXZ @ 0x001C4A60
void sub_1C4A60()
{
    sub_1FF250()->sub_2008B0(7);
    sub_1FF250()->sub_2007A0(1);
    sub_D7C10(0);
}

// The message arg_0 on its screen, or kept (sub_1C40B0) until it may show.
// match: ?sub_1C4A90@@YAXPBD@Z @ 0x001C4A90
void sub_1C4A90(const RwChar *arg_0)
{
    if (sub_1C4C00() && !sub_215A90())
    {
        type_1FF250 *var_4 = sub_1FF250();

        if (var_4)
        {
            var_4->sub_2008B0(9);
            ((type_216C10 *)var_4->sub_200900())->sub_216C10(arg_0);
            var_4->sub_2007A0(1);
        }
        sub_D7C10(0);
    }
    else
        strncpy(byte_4FDAB0, arg_0, 0x100);
}

// match: ?sub_1C4B10@@YAXXZ @ 0x001C4B10
void sub_1C4B10()
{
    if (sub_227560()->get_unk_A4() && sub_1FF250()->get_unk_0C() != 8)
    {
        sub_227560()->set_unk_A4(0);
        sub_1FF250()->sub_2007A0(0);
        sub_21A5E0()->sub_21C360();
    }
    dword_4FB9E0.sub_1B5250(1);
}

// match: ?sub_1C4B90@@YAXXZ @ 0x001C4B90
void sub_1C4B90()
{
    dword_4FB9E0.unk_E4 = 1;
}

// match: ?sub_1C4BA0@@YAXH@Z @ 0x001C4BA0
void sub_1C4BA0(RwInt32 arg_0)
{
    dword_4FB9E0.sub_1B5B50(arg_0);
}

// match: ?sub_1C4BC0@@YAHXZ @ 0x001C4BC0
RwInt32 sub_1C4BC0()
{
    // A compiled-out check: the registers after it are one load on
    // (docs/toolchain.md); its condition is a stand-in with one load.
    if (!dword_4F28F0->unk_00)
    {
    }
    return dword_4FB9E0.unk_40.get_unk_28();
}

// match: ?sub_1C4BE0@@YA_NXZ @ 0x001C4BE0
bool sub_1C4BE0()
{
    return unk_4F61F8.unk_104 == 0;
}

// match: ?sub_1C4C00@@YA_NXZ @ 0x001C4C00
bool sub_1C4C00()
{
    return (bool)dword_4FB9E0.get_unk_D8();
}

// match: ?sub_1C4C20@@YA_NXZ @ 0x001C4C20
bool sub_1C4C20()
{
    return byte_4FDA90;
}

// match: ?sub_1C4C30@@YAX_N@Z @ 0x001C4C30
void sub_1C4C30(bool arg_0)
{
    if (byte_4FDA90 != arg_0)
    {
        byte_4FDA90 = arg_0;
        if (byte_4FDA90)
            sub_1C5230();
    }
}

// match: ?sub_1C4C60@@YAXXZ @ 0x001C4C60
void sub_1C4C60()
{
    sub_1FF250()->sub_200920();
}

// The vote from the front end: called (when none runs) and given; its
// state and the last one's result.
// match: ?sub_1C4C80@@YAXHH@Z @ 0x001C4C80
void sub_1C4C80(RwInt32 arg_0, RwInt32 arg_4)
{
    if (sub_1C4CB0())
        unk_4F7EB8.unk_490.sub_1C32B0(arg_0, arg_4);
}

// match: ?sub_1C4CB0@@YA_NXZ @ 0x001C4CB0
bool sub_1C4CB0()
{
    return (bool)(sub_1C4D00() == -1);
}

// match: ?sub_1C4CC0@@YA_NXZ @ 0x001C4CC0
bool sub_1C4CC0()
{
    return (bool)(!sub_1C4CB0() && !unk_4F7EB8.unk_490.get_unk_38());
}

// match: ?sub_1C4D00@@YAHXZ @ 0x001C4D00
RwInt32 sub_1C4D00()
{
    return unk_4F7EB8.unk_490.get_unk_00();
}

// match: ?sub_1C4D20@@YAHXZ @ 0x001C4D20
RwInt32 sub_1C4D20()
{
    return unk_4F7EB8.unk_490.get_unk_04();
}

// match: ?sub_1C4D40@@YAXH@Z @ 0x001C4D40
void sub_1C4D40(RwInt32 arg_0)
{
    if (sub_1C4CC0())
        unk_4F7EB8.unk_490.sub_1C37E0(arg_0);
}

// match: ?sub_1C4D60@@YAHXZ @ 0x001C4D60
RwInt32 sub_1C4D60()
{
    return unk_4F7EB8.unk_490.get_unk_3C();
}

// match: ?sub_1C4D80@@YAHXZ @ 0x001C4D80
RwInt32 sub_1C4D80()
{
    return unk_4F7EB8.unk_490.get_unk_40();
}

// match: ?sub_1C4DA0@@YAXPAI0@Z @ 0x001C4DA0
void sub_1C4DA0(RwUInt32 *arg_0, RwUInt32 *arg_4)
{
    type_4F8348 *var_4 = &unk_4F7EB8.unk_490;

    *arg_0 = var_4->unk_44;
    *arg_4 = var_4->unk_48;
}

// match: ?sub_1C4DD0@@YA?AUtype_1CB670@@XZ @ 0x001C4DD0
type_1CB670 sub_1C4DD0()
{
    return unk_4F7EB8.unk_490.sub_1C4E00();
}

// match: ?sub_1C4E00@type_4F8348@@QAE?AUtype_1CB670@@XZ @ 0x001C4E00
type_1CB670 type_4F8348::sub_1C4E00()
{
    return type_1CB670(static_cast<const std::string &>(unk_4C));
}

// match: ?sub_1C4E40@@YAHXZ @ 0x001C4E40
RwInt32 sub_1C4E40()
{
    return unk_4F7EB8.unk_490.sub_1C3CC0();
}

// match: ?sub_1C4E50@@YAXXZ @ 0x001C4E50
void sub_1C4E50()
{
    unk_4F7EB8.unk_490.sub_1C3D00();
}

// match: ?sub_1C4E60@@YAPBDH@Z @ 0x001C4E60
const RwChar *sub_1C4E60(RwInt32 arg_0)
{
    return sub_1A3C10(arg_0);
}

// match: ?sub_1C4E80@@YAXUtype_1A5EA0@@@Z @ 0x001C4E80
void sub_1C4E80(type_1A5EA0 arg_0)
{
}

// match: ?sub_1C4EA0@@YAPAUtype_1E3DB0@kujuUI@@XZ @ 0x001C4EA0
kujuUI::type_1E3DB0 *sub_1C4EA0()
{
    if (!dword_4FDA98)
        kujuUI::sub_1E3F50(0, &dword_4FDA98);
    return dword_4FDA98;
}

// match: ?sub_1C4ED0@@YAXXZ @ 0x001C4ED0
void sub_1C4ED0()
{
    if (dword_4FDA98)
    {
        delete dword_4FDA98;
        dword_4FDA98 = 0;
    }
}

// The options: the speakers (0 mono, 1 stereo, 2 surround), the rumble,
// the difficulty and the sensitivity, the aiming aid and the voice
// through the speakers.
// match: ?sub_1C4F30@@YAHXZ @ 0x001C4F30
RwInt32 sub_1C4F30()
{
    switch (dword_4F28F0->get_unk_14_direct())
    {
    case 2:
        return 0;
    default:
        return 1;
    case 4:
        return 2;
    }
}

// match: ?sub_1C4F70@@YAXH@Z @ 0x001C4F70
void sub_1C4F70(RwInt32 arg_0)
{
    switch (arg_0)
    {
    case 0:
        dword_44D4C4 = 2;
        break;
    case 1:
        dword_44D4C4 = 1;
        break;
    case 2:
        dword_44D4C4 = 4;
        break;
    default:
        dword_44D4C4 = 1;
    }
    set_4F28F0_unk_14(dword_44D4C4);
    sub_22C6E0(dword_44E8B0, dword_44D4C4);
}

// match: ?sub_1C4FF0@@YAHXZ @ 0x001C4FF0
RwInt32 sub_1C4FF0()
{
    if (dword_4F28F0->get_unk_22())
        return 1;
    return 0;
}

// match: ?sub_1C5020@@YAXH@Z @ 0x001C5020
void sub_1C5020(RwInt32 arg_0)
{
    if (arg_0 == 1)
        dword_4F28F0->unk_22 = 1;
    else
        dword_4F28F0->unk_22 = 0;
}

// match: ?sub_1C5040@@YAHXZ @ 0x001C5040
RwInt32 sub_1C5040()
{
    switch (dword_4F28F0->get_unk_18_direct())
    {
    case 0:
        return 1;
    case 2:
        return 2;
    default:
        return 0;
    }
}

// match: ?sub_1C5080@@YAXH@Z @ 0x001C5080
void sub_1C5080(RwInt32 arg_0)
{
    type_10F710 *var_4;
    PlayerTrigger *l8;

    switch (arg_0)
    {
    case 1:
        dword_4F28F0->unk_18 = 0;
        break;
    case 2:
        dword_4F28F0->unk_18 = 2;
        break;
    default:
        dword_4F28F0->unk_18 = 1;
    }
    var_4 = (type_10F710 *)sub_1745A0(0);
    if (var_4)
    {
        l8 = (PlayerTrigger *)var_4->get_unk_34C();
        l8->sub_ACA70();
    }
}

// match: ?sub_1C5100@@YAHXZ @ 0x001C5100
RwInt32 sub_1C5100()
{
    return dword_4F28F0->get_unk_1C();
}

// match: ?sub_1C5120@@YAXH@Z @ 0x001C5120
void sub_1C5120(RwInt32 arg_0)
{
    type_10F710 *var_4 = (type_10F710 *)sub_1745A0(0);

    dword_4F28F0->unk_1C = arg_0;
    if (var_4)
    {
        var_4->unk_3DC = arg_0;
        var_4->sub_FEFE0();
    }
}

// match: ?sub_1C5160@@YAHXZ @ 0x001C5160
RwInt32 sub_1C5160()
{
    return !dword_4F28F0->get_unk_20();
}

// match: ?sub_1C5180@@YAXH@Z @ 0x001C5180
void sub_1C5180(RwInt32 arg_0)
{
    dword_4F28F0->unk_20 = (RwInt32)(arg_0 == 0);
}

// match: ?sub_1C51A0@@YAHXZ @ 0x001C51A0
RwInt32 sub_1C51A0()
{
    RwInt32 var_4 = unk_4F7EB8.get_unk_2C8()->unk_3060.unk_F0;

    return var_4 == 0;
}

// match: ?sub_1C51D0@@YAXH@Z @ 0x001C51D0
void sub_1C51D0(RwInt32 arg_0)
{
    RwInt32 var_4 = arg_0 == 0;

    unk_4F7EB8.get_unk_2C8()->unk_3060.sub_1C7420(var_4);
}

// match: ?sub_1C5210@@YAXXZ @ 0x001C5210
void sub_1C5210()
{
    unk_4F7EB8.sub_1AFB70();
}

// match: ?sub_1C5220@@YAXXZ @ 0x001C5220
void sub_1C5220()
{
    byte_4FDAA8 = 0;
}

// The lobby's copy of the game: its type, and each player's name, team
// and scores.
// match: ?sub_1C5230@@YAXXZ @ 0x001C5230
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void sub_1C5230()
{
    RwUInt32 var_8;

    unk_4FDBB0.unk_00 = dword_4FB9E0.get_unk_08();
    type_1DDE20_mask l4 = sub_1C48D0();
    for (var_8 = 0; var_8 < 16; var_8++)
    {
        if (l4.test(var_8))
        {
            sub_1C4720(var_8);
            dword_4FD7B0[var_8] = sub_1C4800(var_8);
            dword_4FD730[var_8] = sub_1C47A0(var_8);
            dword_4FD6F0[var_8] = sub_1C4840(var_8);
        }
    }
}

// match: ?sub_1C52E0@@YAXXZ @ 0x001C52E0
void sub_1C52E0()
{
    RwUInt32 var_4;

    for (var_4 = 0; var_4 < 16; var_4++)
    {
        byte_4FD7F0[var_4][0] = 0;
        dword_4FD7B0[var_4] = 0;
        dword_4FD730[var_4] = 0;
        dword_4FD6F0[var_4] = 0;
    }
}

// match: ?sub_1C5340@@YAXXZ @ 0x001C5340
void sub_1C5340()
{
    sub_1C52E0();
}

// match: ?sub_1C5350@@YA?AUtype_1CB670@@XZ @ 0x001C5350
// match: __ehhandler$?sub_1C5350@@YA?AUtype_1CB670@@XZ-0x58 @ 0x00303170
// match: __ehhandler$?sub_1C5350@@YA?AUtype_1CB670@@XZ @ 0x003031C8
// Builds the localized objective hint from the game type, assault side,
// or target score. The score substitution buffer has 12 bytes.
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
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
        return sub_1CB7B0(type_1CB670(stk_30.c_str(), 1).c_str(), v44, 0);
    }
    // Two discarded text diagnostics preserve expansion of all five
    // C-string conversions. Their original text is not known.
    debug_text(stk_30);
    debug_text(stk_30);
    {
        // Evidence: 0x20 bytes of unwritten inline locals follow the
        // formatted-return scope. Keep this scope separate so that
        // branch's temporary stays at -0xE8 and the frame stays 0x140.
        // The original discarded expressions are not known.
        unused_slot();
        unused_slot();
        unused_slot();
        unused_slot();
        unused_slot();
        unused_slot();
        unused_slot();
        unused_slot();
        return type_1CB670(stk_30.c_str(), 1);
    }
}

// Functions /OPT:ICF folded into another body (config/aliases.txt), defined here for the
// authentic link (PLAN M7) with that body; the placement link takes the folded one.

// ?sub_215A90@@YA_NXZ (folded into 0x215A90)
bool sub_215A90()
{
    return (bool)dword_5051CC->unk_154;
}
