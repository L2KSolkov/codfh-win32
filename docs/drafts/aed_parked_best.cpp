// SUPERSEDED for sub_1AED80: matched in src/recovered/unit_1A8B20.cpp.
// A checked network-player accessor fixes the post-conversion registers.
// This historical snapshot must not replace the current unit.

// The multiplayer manager, cNetController (game/gameloop.h, type_4F7EB8):
// its state, its message handlers (the table at 0x42C848 lists them) and
// its scores.

#include "game/liveservice.h"
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

// The HUD's message line: arg_0 received from peer arg_4 (sub_1C4E80), and
// a refresh (sub_1C4C30).
void sub_1C4E80(type_1A5EA0 arg_0, RwInt32 arg_4);
void sub_1C4C30(RwInt32 arg_0);
extern RwUInt32 dword_4F6AB8[];
extern RwInt32 dword_4F83D8;
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
extern const RwChar pResourcePath[];
void sub_16C220(const RwChar *arg_0, ...);
// The name of the weapon arg_0 (of kind arg_4) for the respawn message; only
// the widths are known.
std::string sub_1C43C0(RwInt32 arg_0, RwInt32 arg_4);

// match: ?sub_1A9940@@YAXPAX@Z @ 0x001A9940
void sub_1A9940(void *arg_0)
{
    sub_1CBC30()->sub_1F8C30(arg_0);
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

// match: ?sub_1AAB30@type_4F7EB8@@QAEXXZ @ 0x001AAB30
void type_4F7EB8::sub_1AAB30()
{
    unk_4FC = 1;
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

// match: ?sub_1ACA70@type_4F7EB8@@QAEIXZ @ 0x001ACA70
RwUInt32 type_4F7EB8::sub_1ACA70()
{
    return get_unk_19C()->get_unk_B0()->get_unk_0C().sub_1D4A60();
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

// match: ?sub_1ADB40@type_4F7EB8@@QAEXH@Z @ 0x001ADB40
void type_4F7EB8::sub_1ADB40(RwInt32 arg_0)
{
    unk_2B8 = arg_0;
    if (arg_0 == unk_4F7EB8.sub_1AEC70())
        dword_4F83D8 = 1;
    else
        dword_4F83D8 = 0;
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
    unk_4F7EBC = *(type_3E1E3C *)arg_8;
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
    unk_4F7F88 = *(type_3E1FC4 *)arg_8;
    sub_1C4C30(1);
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

// match: ?sub_1AEC70@type_4F7EB8@@QAEHXZ @ 0x001AEC70
RwInt32 type_4F7EB8::sub_1AEC70()
{
    return unk_19C->get_unk_B0()->sub_1CFF90();
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
        (dword_4FB9E0.sub_1E3480() == 1 || dword_4FB9E0.sub_1E3480() == 2))
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

    unk_4F8348.sub_1C3520(m.unk_04, m.unk_08, m.unk_0C, m.unk_10);
}

// The message's copy constructor, compiler-made and out of line.
// match: ??0type_3E0FE4@@QAE@ABU0@@Z @ 0x001AF4F0

// match: ?sub_1AF570@@YAXHHPAUtype_3DA44C@@@Z @ 0x001AF570
void sub_1AF570(RwInt32 arg_0, RwInt32 arg_4, type_3DA44C *arg_8)
{
    type_3E0FFC m = *(type_3E0FFC *)arg_8;

    unk_4F8348.sub_1C3900(m.unk_04, m.unk_08);
}

// match: ?sub_1AF5D0@@YAXHHPAUtype_3DA44C@@@Z @ 0x001AF5D0
void sub_1AF5D0(RwInt32 arg_0, RwInt32 arg_4, type_3DA44C *arg_8)
{
    type_3E1014 m = *(type_3E1014 *)arg_8;

    unk_4F8348.sub_1C3B40(m.unk_04, m.unk_08, m.unk_0C);
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
                if (!sub_81FB0(0, pResourcePath, fp_34))
                {
                    sub_16C220("Adding load of section %d to AsynchQueue...\n", fp_34);
                    sub_81EB0(0, pResourcePath, fp_34);
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

// Tells the player (on the console, while a game or its peers are there)
// what they respawn with, and as which side outside the game type 1.
// Not yet matched (sub_1AFBB0): the image calls std::string's default
// constructor out of line (sub_E87E0) for text, and its exit thunks
// (sub_30EA80, sub_30EA90) call the destructor out of line (sub_43900);
// this compiler inlines both. With a declared constructor standing in, the
// rest is identical.
void type_4F7EB8::sub_1AFBB0()
{
    std::string text;
    static std::string unk_4F8498 = sub_E3970("Allies", 0);
    static std::string unk_4F847C = sub_E3970("Axis", 0);

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
    if (dword_4FB9E0.sub_1E3480() != 1 || dword_4FB9E0.get_unk_C8() || dword_4FB9E0.get_unk_C4()
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

    if (dword_4FB9E0.sub_1E3480() != 1 || dword_4FB9E0.get_unk_C8() || dword_4FB9E0.get_unk_C4())
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

    if (dword_4FB9E0.sub_1E3480() != 1 || dword_4FB9E0.get_unk_C8() || dword_4FB9E0.get_unk_C4())
    {
        return;
    }
    unk_4F823C.sub_1B1DE0(m);
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

// match: ?sub_1AE5C0@@YAXHHPAUtype_3DA44C@@@Z @ 0x001AE5C0
void sub_1AE5C0(RwInt32 arg_0, RwInt32 arg_4, type_3DA44C *arg_8)
{
    type_3E1104 m = *(type_3E1104 *)arg_8;

    if (dword_4FB9E0.sub_1E3480() != 1 || dword_4FB9E0.get_unk_C8() || dword_4FB9E0.get_unk_C4())
    {
        return;
    }
    if (dword_4FB9E0.sub_1E3480() != 1)
    {
        return;
    }
    dword_4FBB20.sub_1BDD20(m.unk_04);
}

// match: ?sub_1AE650@@YAXHHPAUtype_3DA44C@@@Z @ 0x001AE650
void sub_1AE650(RwInt32 arg_0, RwInt32 arg_4, type_3DA44C *arg_8)
{
    type_3E111C m = *(type_3E111C *)arg_8;

    if (dword_4FB9E0.sub_1E3480() != 1 || dword_4FB9E0.get_unk_C8() || dword_4FB9E0.get_unk_C4())
    {
        return;
    }
    if (dword_4FB9E0.sub_1E3480() != 1)
    {
        return;
    }
    dword_4FBB20.sub_1BDD70(m.unk_04, m.unk_08, m.unk_0C, &m.unk_10);
}

// match: ??0type_3E111C@@QAE@ABU0@@Z @ 0x001AE6C0

// match: ?sub_1AE810@@YAXHHPAUtype_3DA44C@@@Z @ 0x001AE810
void sub_1AE810(RwInt32 arg_0, RwInt32 arg_4, type_3DA44C *arg_8)
{
    type_3E1134 m = *(type_3E1134 *)arg_8;

    if (dword_4FB9E0.sub_1E3480() != 1 || dword_4FB9E0.get_unk_C8() || dword_4FB9E0.get_unk_C4())
    {
        return;
    }
    if (0)
    {
        sub_1C8A30("Received swap pickup\n");
    }
    dword_4FBB20.sub_1BDE70(m.unk_04, m.unk_08, m.unk_0C);
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
    if (0)
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

// match: ?sub_1AE250@@YAXHHPAUtype_3DA44C@@@Z @ 0x001AE250
void sub_1AE250(RwInt32 arg_0, RwInt32 arg_4, type_3DA44C *arg_8)
{
    type_3E117C *m = (type_3E117C *)arg_8;

    dword_4F8288.sub_1C28F0(arg_4, m->unk_04, 0);
    if (dword_4FB9E0.sub_1E3480() != 1 || dword_4FB9E0.get_unk_C8() || dword_4FB9E0.get_unk_C4())
    {
        return;
    }
    if (dword_4FB9E0.sub_1E3480() == 1)
    {
        sub_1A8A70(&unk_4F7EB8, "Player %d respawned\n", arg_4);
        unk_4F7EB8.sub_1AED80(arg_4, m->unk_04, m->unk_08);
    }
    else
    {
        sub_1A8A70(&unk_4F7EB8, "Player %d unable to be respawned because not in game\n", arg_4);
    }
}

// A respawn point from the server: kept (unk_294, unk_298) and flagged
// (unk_290) in a game type 1 when neither dword_4FBAA4 nor dword_4FBAA8 is
// set.
// match: ?sub_1AD6B0@@YAXHHPAUtype_3DA44C@@@Z @ 0x001AD6B0
void sub_1AD6B0(RwInt32 arg_0, RwInt32 arg_4, type_3DA44C *arg_8)
{
    type_3E10EC *m = (type_3E10EC *)arg_8;

    sub_1A8A70(&unk_4F7EB8, "(CLIENT) Valid respawn point received #%d\n", m->unk_04);
    if (dword_4FB9E0.sub_1E3480() != 1 || dword_4FB9E0.get_unk_C8() || dword_4FB9E0.get_unk_C4())
    {
        return;
    }
    unk_4F7EB8.unk_294 = m->unk_04;
    unk_4F7EB8.unk_298 = m->unk_08;
    unk_4F7EB8.unk_290 = 1;
}

// A chat line from peer arg_4, for the HUD's message line.
// match: ?sub_1AE460@@YAXHHPAUtype_3DA44C@@@Z @ 0x001AE460
void sub_1AE460(RwInt32 arg_0, RwInt32 arg_4, type_3DA44C *arg_8)
{
    sub_1A8A70(&unk_4F7EB8, "Received net chat\n");
    type_1A5EA0 *text = &((type_3E102C *)arg_8)->unk_04;
    sub_1C4E80(*text, arg_4);
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
    if (dword_4FB9E0.sub_1E3480() != 1 || dword_4FB9E0.get_unk_C8() || dword_4FB9E0.get_unk_C4()
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
    if (dword_4FB9E0.sub_1E3480() != 1 || dword_4FB9E0.get_unk_C8() || dword_4FB9E0.get_unk_C4()
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

    if (dword_4FB9E0.sub_1E3480() != 1 || dword_4FB9E0.get_unk_C8() || dword_4FB9E0.get_unk_C4())
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
        unk_4F7EBC.sub_1B3270(arg_0);
    }
}

// A grenade hit on the remote player arg_4, on the bullet hit's terms: an
// explosion's hit at the message's point, to that player and to the second
// player when it is unk_230.
// match: ?sub_1AD0F0@@YAXHHPAUtype_3DA44C@@@Z @ 0x001AD0F0
// symbol: __ehhandler$?sub_1AD0F0@@YAXHHPAUtype_3DA44C@@@Z = 0x00302B08
void sub_1AD0F0(RwInt32 arg_0, RwInt32 arg_4, type_3DA44C *arg_8)
{
    sub_1A8A70(&unk_4F7EB8, "Grenade hit remote player - Victim: %d\n", arg_4);
    type_3E1194 *m = (type_3E1194 *)arg_8;
    if (dword_4FB9E0.sub_1E3480() != 1 || dword_4FB9E0.get_unk_C8() || dword_4FB9E0.get_unk_C4()
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

    if (dword_4FB9E0.sub_1E3480() != 1 || dword_4FB9E0.get_unk_C8() || dword_4FB9E0.get_unk_C4())
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

// Clears dword_4F6AB8's sixteen entries.
// match: ?vf_008@type_4F7EB8@@UAEXXZ @ 0x001A8D60
void type_4F7EB8::vf_008()
{
    for (RwUInt32 i = 0; i < 16; i++)
    {
        dword_4F6AB8[i] = 0;
    }
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

// match: ?sub_1AB070@type_4F7EB8@@QAEXXZ @ 0x001AB070
void type_4F7EB8::sub_1AB070()
{
    RwInt32 me;

    // A compiled-out check (docs/toolchain.md): the registers after it are
    // one load on.
    if (!unk_4FC)
    {
    }
    if (!((dword_4B86F8 >> 4) & 1) && dword_4B9308.sub_EE950(0, 0x17) != 0.0f
        && dword_4FB9E0.sub_1E3480() == 1)
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

// Takes the requested state (unk_2B0) as unk_2AC; leaving state 1 for 0
// ends the kill cam: its players go, and the peers in the game get remote
// players (made by unk_27C) where they have none.
// Not yet matched (sub_1ABC00): the frame and the code match (the network
// part is the remote player's second base: the conversion and the virtual
// call through it are the image's), but from the push after the null-checked
// conversion the registers are two loads behind the image's; the explicit
// casts, a hand ternary and checks before the call all keep this compile's
// order. The respawn's sub_1AED80 converts the same way.
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
                        if (0)
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
                            if (0)
                            {
                                sub_1C8A30("Bind from KILL CAM: %d\n", i);
                            }
                            if (!unk_1F0[i])
                            {
                                unk_1F0[i] = unk_27C->vf_020();
                                unk_4F6B00[i].sub_1A6420(unk_1F0[i]);
                                unk_1F0[i]->pvf_010(unk_1A0);
                            }
                        }
                    }
                }
            }
            break;
        }
    }
    unk_2AC = unk_2B0;
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
    if (!unk_4F61F8.unk_104 && !dword_4FB9E0.sub_1CA260())
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
// symbol: __ehhandler$?sub_1AC790@type_4F7EB8@@QAEXH@Z = 0x00302ACB
void type_4F7EB8::vf_004(RwInt32 arg_0)
{
    RwChar text[0x100];

    unk_384.sub_1B24E0(arg_0);
    unk_4F7EBC.sub_1B2D00(arg_0, arg_0, 0);
    sub_1AC990(arg_0);
    sprintf(text, "Player Removed: #%d, %s", arg_0, unk_19C->get_unk_B0()->unk_90[arg_0].unk_00);
    sub_1B18D0()->sub_1B1780(text, 1);
    sub_1CB000(text, sub_E3970("MW_GEN_LEAVE", 1).c_str(), type_4F8054::get()->get_unk_B0()->unk_90[arg_0].unk_00);
    sub_EACA0(text, 0, 0);
    dword_4F8288.sub_1C2940(arg_0);
    sub_1C44D0(arg_0);
}

// The local player killed by peer arg_0's bullet (arg_4): the kill sent to
// the other peers, shown ("MW_GEN_KILLS_YOUYOURSELF" or
// "MW_GEN_KILLS_YOUGUN" with the killer's name) and counted; when not
// hosting the scores take it and the local player drops its pickups.
// Not yet matched (sub_1ACBA0): the frame is 8 bytes larger, and inside
// the peers' mask (type_4F8054_B0::others) the registers are one load
// behind the image's; any statement added to that inline stops it being
// expanded here.
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
    type_1DDE20_mask ebp_12A = type_4F8054::get()->get_unk_B0()->others();
    type_4F8058::get()->sub_1DDDB0(&lcl_128, ebp_12A);
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
    sub_EACA0(l114, 0, 0);
    dword_4F8288.sub_1C28F0(unk_4F7EB8.sub_1AEC70(), 1, 1);
    if (!unk_4F61F8.unk_104)
    {
        unk_4F7EBC.sub_1B2D00(unk_4F7EB8.sub_1AEC70(), arg_0, 0);
        unk_4F7EB8.sub_1ADB80(lcl_128.unk_10, 0);
    }
}

// Peer arg_4 died from the bullet of player unk_0D: shown
// ("MW_GEN_KILLS_GUN" with both names, or "MW_GEN_SUICIDE"), its remote
// player told, counted and its pickups dropped when not hosting, and its
// remote player kept for the kill cam.
// Not yet matched (sub_1AD750): the named slots match, but this compile
// leaves four unused slots between the two branches' string temporaries
// where the image leaves two (so its frame is 8 bytes smaller); sub_1ACBA0
// shows the same.
void sub_1AD750(RwInt32 arg_0, RwInt32 arg_4, type_3DA44C *arg_8)
{
    // The locals' names state their slots (docs/toolchain.md).
    RwChar lv_114[0x100];
    type_3E114C *var118 = (type_3E114C *)arg_8;

    sub_1A8A70(&unk_4F7EB8, "Player %d died from bullet fired by player %d\n", arg_4, var118->unk_0D);
    dword_4F8288.sub_1C28F0(arg_4, 1, 1);
    if (dword_4FB9E0.sub_1E3480() != 1 || dword_4FB9E0.get_unk_C8() || dword_4FB9E0.get_unk_C4())
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
    sub_EACA0(lv_114, 0, 0);
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
    if (!unk_4F61F8.unk_104)
    {
        unk_4F7EBC.sub_1B2D00(arg_4, var118->unk_0D, 0);
        if (lv_10 && unk_4F7EB8.unk_2A4 != 4)
        {
            unk_4F7EB8.sub_1ADB80(var118->unk_10, arg_4);
        }
    }
    if (unk_4F7EB8.unk_2A4 != 4)
    {
        if (unk_4F6B00[arg_4].is_visible())
        {
            unk_4F6B00[arg_4].sub_1A63E0();
            unk_4F7EB8.sub_1AB2C0();
        }
        if (unk_4F7EB8.unk_1F0[arg_4])
        {
            unk_4F6B00[arg_4].sub_1A6460();
            unk_4F7EB8.unk_1B0[arg_4] = unk_4F7EB8.unk_1F0[arg_4];
            unk_4F7EB8.unk_1F0[arg_4] = 0;
        }
        unk_4F7EB8.sub_73D90(var118->unk_0D, arg_4);
    }
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

// Defined in its class (game/gameloop.h), not inlined.
// match: ??1type_4F8348@@QAE@XZ @ 0x001A8E10
// symbol: __ehhandler$??1type_4F8348@@QAE@XZ = 0x003029FB

// Its frame's ten unused slots are the +0x490 part's destructor's
// expansion, reserved though it is not inlined (docs/toolchain.md).
// match: ??1type_4F7EB8@@QAE@XZ @ 0x001A8DA0
type_4F7EB8::~type_4F7EB8()
{
}

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
        if (0)
        {
            off_42CD14("(HOST) Broadcast level load start to clients\n");
        }
    }
    unk_284 = 0;
    unk_288 = 0;
    unk_290 = 0;
    unk_294 = 0;
}

// Sets the network game up: the network players reset, the network game
// built and opened on port 0x3F9 with this as its third listener, the
// session, the message listener and the voice manager built and handed to
// it, the network system started, the game type 1, and the voice manager
// given the audio output's effects image and DirectSound.
// match: ?sub_1A9580@type_4F7EB8@@QAEXXZ @ 0x001A9580
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
        if (dword_4B9308.sub_EE950(0, 0x17) != 0.0f && dword_4FB9E0.sub_1E3480() == 1)
        {
            if (!unk_4F61F8.unk_104)
            {
                dword_4FB9E0.sub_1B6EF0(0);
            }
            if (!dword_4FB9E0.sub_1B6E50())
            {
                if ((dword_4FB9E0.get_unk_08() == 8 || !dword_4FB9E0.get_unk_0C() || !unk_500)
                    && !dword_4FB9E0.sub_1CA260())
                {
                    sub_124EE0(0.5f, 1);
                    sub_1AB400(0);
                    unk_500 = 1;
                }
            }
        }
        if (dword_4B9308.sub_EE950(0, 0x15) != 0.0f)
        {
            sub_1AB140();
        }
        if (dword_4B9308.sub_EE950(0, 0x16) != 0.0f)
        {
            sub_1AB200();
        }
    }
    sub_1AAF40();
}

// Respawns peer arg_0 (team arg_4, spawn point arg_8 or -1): its old remote
// player kept in unk_238 (or unk_238's one removed when no other peer has
// it and it is not flagged), unk_27C set up from the spawn table and named
// after the peer, and a new remote player made and shown, its network part
// given the session.
// Not yet matched (sub_1AED80): the image nudges the position through two
// late slots holding each float's address (compiler temporaries, after the
// conversion's); pointer or reference locals take early slots, and
// RwMatrixGetPos and the plain member give none.
inline RwReal &ref(RwReal &arg_0)
{
    return arg_0;
}
// match: ?sub_1AED80@type_4F7EB8@@QAEXHII@Z @ 0x001AED80
void type_4F7EB8::sub_1AED80(RwInt32 arg_0, RwUInt32 arg_4, RwUInt32 arg_8)
{
    if (unk_1F0[arg_0])
    {
        if (!unk_2A4)
        {
        }
        if (unk_4F6B00[arg_0].is_visible())
        {
            if (!unk_2A4)
            {
            }
            if (!unk_2A4)
            {
            }
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
    unk_4F6B00[arg_0].sub_1A6420(unk_1F0[arg_0]);
    unk_1F0[arg_0]->pvf_010(unk_1A0);
    ref(unk_27C->unk_60.pos.x) += 1.0f;
    ref(unk_27C->unk_60.pos.y) -= 1000.0f;
    RwMatrixUpdate(&unk_27C->unk_60);
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
        else if (sub_1AF670() && (dword_4FB9E0.sub_1E3480() == 1 || dword_4FB9E0.sub_1E3480() == 3))
        {
            sub_1ABC00();
            sub_1AB440();
            if (!dword_4FB9E0.get_unk_C4() && !dword_4FB9E0.get_unk_C8() && dword_4FB9E0.sub_1E3480() == 1)
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
        bp_4 = dword_4B9308.sub_EE9A0(0, 0x26);
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

// Chooses whom the local player talks to: the peers in the game (only those
// with remote players, by the game type and unk_29C's team rule), their
// squared distances into the voice channel's table, and every two seconds
// the nearest four within reach handed to the voice manager.
// Named by its trace ("cNetController::updateVoiceSubSystem() Player %d is
// not in player set but remote player").
// Not yet matched (sub_1AA380): the named locals' slots match (their names
// state them), but the image has five more compiler temporaries, some of
// them (0x150 to 0x164) taken before the first accessor's.
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
                lv_120.unk_00 &= ~(1 << locC);
            }
        }
    }
    else if (dword_4FB9E0.get_unk_08() == 1)
    {
        for (locC = 0; locC < 16; locC++)
        {
            if (lv_120.test(locC) && !unk_1F0[locC])
            {
                lv_120.unk_00 &= ~(1 << locC);
            }
        }
    }
    else
    {
        for (locC = 0; locC < 16; locC++)
        {
            if (lv_120.test(locC))
            {
                if (unk_29C == 2 && unk_3D0.sub_1C2A90(locC) == 4 || unk_29C == 4 && unk_3D0.sub_1C2A90(locC) == 2
                    || unk_29C == 1 || !unk_1F0[locC])
                {
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
        unk_4F7E90 = type_1DDE20_mask(lv_120);
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
                        if (0)
                        {
                            sub_1C8A30("cNetController::updateVoiceSubSystem() Player %d is not in player set but remote player\n", locC);
                        }
                        if (0)
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
                    if (lcl_14C.test(locC) && !bp_4.test(locC) && bp_118[locC] < loc128)
                    {
                        loc128 = bp_118[locC];
                        slot_12C = locC;
                        x8 = 1;
                    }
                }
                if (x8)
                {
                    lcl_14C.unk_00 &= ~(1 << slot_12C);
                    bp_4.unk_00 |= 1 << slot_12C;
                    lv_144--;
                }
            }
            unk_2C8->sub_1C6440(bp_4);
        }
    }
}

// Changes the view to the requested one (unk_2A8): 3, spectating others (the
// local player removed); 0, playing (the second player and the kill cam
// player removed); 1, following (from anything but 3: the local player
// removed); 2, static spectating (from anything but 1 and 3, else the view
// reset). Each tells the peers whether this machine spectates, fades and
// shows the letterbox.
// Not yet matched (sub_1AB440): the image passes the game data's unk_34
// to sub_1B6DE0 through the FPU (fld; push; fstp [esp]) with no rounding
// store; a plain member gives mov, and the double casts, a volatile field
// and an inline getter each add a slot.
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
                // Two unused slots (docs/toolchain.md).
                unused_slot();
                unused_slot();
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
                if (0)
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
                // Two unused slots (docs/toolchain.md).
                unused_slot();
                unused_slot();
                get_unk_1A0()->sub_1DDDB0(&m, mask);
            }
            sub_1AED30();
            break;
        case 1:
            if (unk_2A4 != 3)
            {
                dword_4FB9E0.sub_1B6DE0(dword_4FB9E0.unk_08.unk_2C);
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
                    // Two unused slots (docs/toolchain.md).
                    unused_slot();
                    unused_slot();
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
                    // Two unused slots (docs/toolchain.md).
                    unused_slot();
                    unused_slot();
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
        unk_2A4 = unk_2A8;
    }
}
