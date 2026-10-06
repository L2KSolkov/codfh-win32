// cXboxLiveNetGame, cNetGame's Xbox side (types/cXboxLiveNetGame.h): its
// constructor and destructor, its states' steps (the host's session made
// over Xbox Live or the system link, the join), the peers' data and user
// ids, the join's server settings and the link's watch. Named by its trace;
// its original file name is not in the image, so it is named for its start
// address.

#include <string.h>
#include <xtl.h>
#include "rw/ostypes.h"
#include "types/cXboxLiveNetGame.h"
#include "game/voice.h"
#include "game/gameloop.h"
#include "game/netmsg.h"

// The debug print (compiled out in its traces).
extern void (*off_42CD14)(const RwChar *arg_0, ...);

// Its data (PLAN M5): literals, constants and tables where the image has them.
// match: ??_7cXboxLiveNetGame@@6B@ @ 0x003E4FC0
// match: ??_C@_07JCBOOEDE@Failed?6?$AA@ @ 0x003E5048
// match: ??_C@_0BF@LACBLGNK@mState?5?$DN?5eStateNone?6?$AA@ @ 0x003E5050
// match: ??_C@_0DM@NBDAHAMG@cXboxLiveNetGame?3?3stateServerTak@ @ 0x003E5068
// match: ??_C@_08GKHOLFG@Success?6?$AA@ @ 0x003E50A4
// match: ??_C@_0BJ@NNOFCOKL@mState?5?$DN?5eStateServerUp?6?$AA@ @ 0x003E50B0
// match: ??_C@_0DM@HDCMEIFB@cXboxLiveNetGame?3?3stateServerTak@ @ 0x003E50CC
// match: ??_C@_0DC@OMJMJDBJ@ERROR?3?5Failed?5to?5create?5Xbox?5Sys@ @ 0x003E5108
// match: ??_C@_0CL@KIMMDKHP@ERROR?3?5Failed?5to?5create?5Xbox?5Liv@ @ 0x003E513C
// match: ??_C@_0CJ@MCCKIMHM@ERROR?3?5Could?5not?5create?5server?5?$CI@ @ 0x003E5168

// match: ??0cXboxLiveNetGame@@QAE@XZ @ 0x001D5190

cXboxLiveNetGame::cXboxLiveNetGame()
{
    unk_D0 = 0;
    unk_110 = 0;
    unk_188 = 0;
}

// match: ?vf_058@cXboxLiveNetGame@@UAEXH@Z @ 0x001D5200

// match: ??_GcXboxLiveNetGame@@UAEPAXI@Z @ 0x001D5220

// match: ??1cXboxLiveNetGame@@UAE@XZ @ 0x001D5250
cXboxLiveNetGame::~cXboxLiveNetGame()
{
}

// match: ?vf_004@cXboxLiveNetGame@@UAEXXZ @ 0x001D5270
void cXboxLiveNetGame::vf_004()
{
    type_4F8054::vf_004();
    unk_D0 = 0;
}

// match: ?vf_008@cXboxLiveNetGame@@UAEXXZ @ 0x001D5290
void cXboxLiveNetGame::vf_008()
{
    type_4F8054::vf_008();
    sub_1D8810()->sub_1D8900();
}

// match: ?vf_084@cXboxLiveNetGame@@UAEXHH@Z @ 0x001D52B0
void cXboxLiveNetGame::vf_084(RwInt32 arg_0, RwInt32 arg_4)
{
    sub_1D8810()->sub_1DBA40(arg_0, arg_4);
}

// The host's session: its settings given to the network system and the
// session made (over Xbox Live when unk_3C is set) with the host's socket;
// then its creation followed until it runs or fails.
// match: ?stateServerTakeUp@cXboxLiveNetGame@@QAEXABUtype_1CCA10@@@Z @ 0x001D52E0
void cXboxLiveNetGame::stateServerTakeUp(const type_1CCA10 &arg_0)
{
    if (unk_0C == 0)
    {
        unk_10 = 0;
        unk_14 = 0;
        sub_1D8810()->sub_1DB8C0(unk_40);
        sub_1D8810()->sub_1DB800(unk_42);
        sub_1D8810()->sub_1DB7C0(unk_41);
        sub_1D8810()->sub_1DB750(unk_43 - unk_48, unk_48);
        sub_1D8810()->sub_1DB840(unk_44);
        sub_1D8810()->sub_1DB880(unk_45);
        if (unk_3C)
        {
            if (sub_1D8810()->sub_1D8C00())
            {
                if (sub_1D8810()->sub_1D9610(1))
                    unk_0C = 1;
                else
                {
                    if (CODFH_DEBUG_LOGS)
                        off_42CD14("ERROR: Could not create server (socket)\n");
                    setError(1, 10);
                    unk_04 = 0;
                    return;
                }
            }
            else
            {
                if (CODFH_DEBUG_LOGS)
                    off_42CD14("ERROR: Failed to create Xbox Live Session\n");
                setError(4, 10);
                unk_04 = 0;
                return;
            }
        }
        else
        {
            sub_1D8810()->sub_1DB920(unk_1C);
            if (sub_1D8810()->sub_1D8E10())
            {
                if (sub_1D8810()->sub_1D9610(0))
                    unk_0C = 1;
                else
                {
                    if (CODFH_DEBUG_LOGS)
                        off_42CD14("ERROR: Could not create server (socket)\n");
                    setError(1, 10);
                    unk_04 = 0;
                    return;
                }
            }
            else
            {
                if (CODFH_DEBUG_LOGS)
                    off_42CD14("ERROR: Failed to create Xbox System Link Session\n");
                setError(4, 10);
                unk_04 = 0;
                return;
            }
        }
    }
    else if (unk_0C == 1)
    {
        switch (sub_1D8810()->get_unk_291C())
        {
        case 2:
            if (CODFH_DEBUG_LOGS)
                sub_1C8A30("cXboxLiveNetGame::stateServerTakeUp SESSION_STATUS_RUNNING\n");
            if (CODFH_DEBUG_LOGS)
                sub_1C8A30("mState = eStateServerUp\n");
            unk_04 = 2;
            unk_0C = 0;
            if (CODFH_DEBUG_LOGS)
                off_42CD14("Success\n");
            break;
        case 0:
            if (CODFH_DEBUG_LOGS)
                sub_1C8A30("cXboxLiveNetGame::stateServerTakeUp SERVER_CONNECTION_NONE\n");
            if (CODFH_DEBUG_LOGS)
                sub_1C8A30("mState = eStateNone\n");
            unk_04 = 0;
            unk_0C = 0;
            if (CODFH_DEBUG_LOGS)
                off_42CD14("Failed\n");
        }
    }
}

// The join: the server's address and keys given to the network system,
// then its state followed until it joins or fails (with the reason).
// match: ?sub_1D55A0@cXboxLiveNetGame@@QAEXABUtype_1CCA10@@@Z @ 0x001D55A0
void cXboxLiveNetGame::sub_1D55A0(const type_1CCA10 &arg_0)
{
    RwInt32 bp_4;
    RwInt32 var_8;

    if (unk_0C == 0)
    {
        unk_10 = 0;
        unk_14 = 0;
        if (!sub_1D8810()->sub_1D9700(&unk_D4, &unk_F8, &unk_100, arg_0, unk_110))
        {
            setError(2, 10);
            unk_04 = 0;
            return;
        }
        unk_0C = 1;
    }
    if (unk_0C == 1)
    {
        bp_4 = sub_1D8810()->get_unk_4038();
        if (bp_4 == 1)
            return;
        if (bp_4 == 3)
        {
            var_8 = 1;
            // A compiled-out check (docs/toolchain.md).
            if (!unk_04)
            {
            }
            if (sub_1D8810()->get_unk_403C() == 2)
                var_8 = 2;
            else if (sub_1D8810()->get_unk_403C() == 3)
                var_8 = 4;
            unk_04 = 0;
            setError(3, var_8);
        }
        else
        {
            // A compiled-out check (docs/toolchain.md).
            if (!unk_04)
            {
            }
            unk_04 = 5;
        }
    }
}

// match: ?vf_048@cXboxLiveNetGame@@UAEHHH@Z @ 0x001D56D0
RwInt32 cXboxLiveNetGame::vf_048(RwInt32 arg_0, RwInt32 arg_4)
{
    // Two compiled-out checks (docs/toolchain.md).
    if (!unk_04)
    {
    }
    if (!unk_04)
    {
    }
    return sub_1D8810()->sub_1D9C30(arg_0, (type_1D9C30_peer *)arg_4, sub_1CCA10());
}

// Its step: the link watched, the network system stepped, then the state's
// step.
// match: ?vf_00C@cXboxLiveNetGame@@UAEXABUtype_1CCA10@@@Z @ 0x001D5700
void cXboxLiveNetGame::vf_00C(const type_1CCA10 &arg_0)
{
    vf_054(0);
    sub_1D8810()->sub_1DBA80(arg_0);
    if (!unk_04)
        return;
    type_4F8054::vf_00C(arg_0);
    switch (unk_04)
    {
    case 1:
        stateServerTakeUp(arg_0);
        break;
    case 3:
        sub_15FB30(arg_0);
        break;
    case 2:
        sub_15FB30(arg_0);
        break;
    case 4:
        sub_1D55A0(arg_0);
        break;
    case 6:
        sub_15FB30(arg_0);
        break;
    case 5:
        sub_15FB30(arg_0);
    }
}

// Peer arg_0's user id told to the network system as it leaves.
// match: ?vf_068@cXboxLiveNetGame@@UAEXH@Z @ 0x001D57E0
void cXboxLiveNetGame::vf_068(RwInt32 arg_0)
{
    XUID var_C;

    if (sub_1D8810()->sub_1DBD60(arg_0, &var_C, 1))
        sub_1D8810()->sub_1DA680(var_C);
    type_4F8054::vf_068(arg_0);
}

// match: ?vf_04C@cXboxLiveNetGame@@UAEXABUtype_1DDE20_mask@@@Z @ 0x001D5840
void cXboxLiveNetGame::vf_04C(const type_1DDE20_mask &arg_0)
{
    RwUInt32 var_4;

    // A compiled-out check (docs/toolchain.md).
    if (!unk_04)
    {
    }
    for (var_4 = 0; var_4 < 16; var_4++)
    {
        // A compiled-out check (docs/toolchain.md).
        if (!unk_04)
        {
        }
        if (arg_0.test(var_4))
            sub_1D8810()->sub_1D9DD0(var_4);
    }
}

// match: ?vf_044@cXboxLiveNetGame@@UAEXHHHHH@Z @ 0x001D5890
void cXboxLiveNetGame::vf_044(RwInt32 arg_0, RwInt32 arg_4, RwInt32 arg_8, RwInt32 arg_C, RwInt32 arg_10)
{
    sub_1D8810()->sub_1D8B40(arg_0, arg_4, arg_8, arg_C, arg_10);
}

// match: ?vf_010@cXboxLiveNetGame@@UAEPBDXZ @ 0x001D58C0
const RwChar *cXboxLiveNetGame::vf_010()
{
    return sub_1D8810()->sub_1DA070();
}

// match: ?vf_01C@cXboxLiveNetGame@@UAEHHHHHH@Z @ 0x001D58E0
RwInt32 cXboxLiveNetGame::vf_01C(RwInt32 arg_0, RwInt32 arg_4, RwInt32 arg_8, RwInt32 arg_C, RwInt32 arg_10)
{
    return 1;
}

// match: ?vf_024@cXboxLiveNetGame@@UAEHHHH@Z @ 0x001D5900
RwInt32 cXboxLiveNetGame::vf_024(RwInt32 arg_0, RwInt32 arg_4, RwInt32 arg_8)
{
    return 1;
}

// match: ?vf_038@cXboxLiveNetGame@@UAEXHPAEH@Z @ 0x001D5920
void cXboxLiveNetGame::vf_038(RwInt32 arg_0, RwUInt8 *arg_4, RwInt32 arg_8)
{
    memset(arg_4, 0, arg_8);
}

// The session's settings given again while it runs, with the two lists
// (sub_1DA170) redone as asked.
// match: ?vf_080@cXboxLiveNetGame@@UAEXHH@Z @ 0x001D5940
void cXboxLiveNetGame::vf_080(RwInt32 arg_0, RwInt32 arg_4)
{
    if (get_unk_B8())
    {
        sub_1D8810()->sub_1DB800(unk_42);
        sub_1D8810()->sub_1DB7C0(unk_41);
        sub_1D8810()->sub_1DB8C0(unk_40);
        sub_1D8810()->sub_1DB840(unk_44);
        sub_1D8810()->sub_1DB880(unk_45);
        if (arg_4)
            sub_1D8810()->sub_1DA170();
        if (arg_0)
            sub_1D8810()->sub_1DA170();
    }
}

// The join's search: over Xbox Live (arg_0's unk_04) or the system link.
// match: ?vf_070@cXboxLiveNetGame@@UAEXPBUtype_1CC1F0@@PBUtype_4F8054_4C@@HH@Z @ 0x001D59F0
void cXboxLiveNetGame::vf_070(const type_1CC1F0 *arg_0, const type_4F8054_4C *arg_4, RwInt32 arg_8, RwInt32 arg_C)
{
    // A compiled-out check (docs/toolchain.md).
    if (!unk_04)
    {
    }
    unk_D0 = 1;
    type_4F8054::vf_070(arg_0, arg_4, arg_8, arg_C);
    if (arg_0->unk_04)
        sub_1D8810()->sub_1D8EE0(&unk_4C, arg_8, arg_C);
    else
        sub_1D8810()->sub_1D9100(&unk_4C, arg_8, arg_C);
}

// match: ?vf_07C@cXboxLiveNetGame@@UAEXXZ @ 0x001D5A70
void cXboxLiveNetGame::vf_07C()
{
    if (unk_D0)
    {
        unk_D0 = 0;
        sub_1D8810()->sub_1D9090();
    }
}

// match: ?vf_074@cXboxLiveNetGame@@UAEHXZ @ 0x001D5AA0
RwInt32 cXboxLiveNetGame::vf_074()
{
    return sub_1D8810()->sub_1D91E0();
}

// match: ?vf_078@cXboxLiveNetGame@@UAEHH@Z @ 0x001D5AC0
RwInt32 cXboxLiveNetGame::vf_078(RwInt32 arg_0)
{
    return (RwInt32)sub_1D8810()->sub_1D9270((RwUInt32 *)arg_0);
}

// The join's server kept with its address and keys.
// match: ?vf_060@cXboxLiveNetGame@@UAEXPBUtype_1CC1F0@@PBUtype_1CC3C0@@H@Z @ 0x001D5AE0
void cXboxLiveNetGame::vf_060(const type_1CC1F0 *arg_0, const type_1CC3C0 *arg_4, RwInt32 arg_8)
{
    // Two compiled-out checks (docs/toolchain.md).
    if (!unk_04)
    {
    }
    if (!unk_04)
    {
    }
    type_4F8054::vf_060(arg_0, arg_4, 0);
    unk_114 = *(const cXboxLiveNetGame_114 *)arg_4;
    unk_D4 = unk_114.unk_38;
    // A compiled-out check (docs/toolchain.md).
    if (!unk_04)
    {
    }
    unk_F8 = unk_114.unk_5C;
    unk_100 = unk_114.unk_64;
    unk_110 = arg_8;
}

// match: ?vf_05C@cXboxLiveNetGame@@UAEXPBUtype_1CC1F0@@@Z @ 0x001D5B80
void cXboxLiveNetGame::vf_05C(const type_1CC1F0 *arg_0)
{
    type_4F8054::vf_05C(arg_0);
    memset(&unk_114, 0, 0x74);
}

// match: ?sub_1D5BB0@type_4F8054@@QAEXH@Z @ 0x001D5BB0
void type_4F8054::sub_1D5BB0(RwInt32 arg_0)
{
    sub_1D8810()->sub_1DB900(arg_0);
}

// match: ?vf_050@cXboxLiveNetGame@@UAEHXZ @ 0x001D5BD0
RwInt32 cXboxLiveNetGame::vf_050()
{
    if (unk_188)
        return unk_CC;
    return 1;
}

// The link's watch, each second: unk_CC clears once it has been down for
// three seconds (ten while arg_0 is set); unk_C0 notes when it went down.
// match: ?vf_054@cXboxLiveNetGame@@UAEXH@Z @ 0x001D5C00
void cXboxLiveNetGame::vf_054(RwInt32 arg_0)
{
    type_1CCA10 bp_C;
    type_1CCA10 bp_4;
    RwInt32 var_8;

    bp_4 = sub_1CCA10();
    bp_C = bp_4 - unk_C4;
    if (bp_C > 1000)
    {
        unk_C4 = bp_4;
        if ((var_8 = XNetGetEthernetLinkStatus() ? 1 : 0))
            unk_CC = 1;
        else if (unk_C8)
            unk_C0 = bp_4;
        else
        {
            bp_C = bp_4 - unk_C0;
            if (arg_0)
            {
                if (bp_C > 10000)
                    unk_CC = 0;
            }
            else if (bp_C > 3000)
                unk_CC = 0;
        }
        unk_C8 = var_8;
    }
}

// Functions /OPT:ICF folded into another body (config/aliases.txt), defined here for the
// authentic link (PLAN M7) with that body; the placement link takes the folded one.

// ?sub_15FB30@cXboxLiveNetGame@@QAEXABUtype_1CCA10@@@Z (folded into 0x15FB30)
void cXboxLiveNetGame::sub_15FB30(struct type_1CCA10 const & arg_0)
{
}
