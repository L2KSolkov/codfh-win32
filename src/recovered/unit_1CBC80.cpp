// The network game, cNetGame (types/type_DC400.h, type_4F8054): its
// parts, its reset and take-down, its step, and creating and joining a
// server.

#include <xtl.h>
#include <string.h>

#include "types/type_DC400.h"
#include "game/fileio.h"
#include "game/netmsg.h"

// Its data definitions (PLAN M5), in the image's address order.
// 0x004FEC60
LARGE_INTEGER PerformanceCount;
// 0x004FEC68
RwDouble dbl_4FEC68;
// End of its data definitions.


// The inline slots' bodies are shared with other classes' (/OPT:ICF).
// symbol: ?vf_074@type_4F8054@@UAEHXZ = 0x00115460
// symbol: ?vf_078@type_4F8054@@UAEHH@Z = 0x00032260
// symbol: ?vf_07C@type_4F8054@@UAEXXZ = 0x001E41C0
// symbol: ?vf_080@type_4F8054@@UAEXHH@Z = 0x00073D90
// symbol: ?vf_084@type_4F8054@@UAEXHH@Z = 0x00073D90

// Vtables (.rdata, PLAN M5): each in its own placement range (config/splits.txt).
// Its data (PLAN M5): literals, constants and tables where the image has them.
// match: ??_7type_4F8054@@6B@ @ 0x003E3DA8
// match: ??_C@_0CA@HDDIIDOG@?5mState?5?$DN?5eStateServerTakeDown?6?$AA@ @ 0x003E3E30
// match: ??_C@_0BI@CHEEPMGK@cNetGame?3?3deinitialise?6?$AA@ @ 0x003E3E50
// match: ??_C@_0BO@FEOOBDNF@?5mState?5?$DN?5eStateServerTakeUp?6?$AA@ @ 0x003E3E68
// match: ??_C@_0L@EFPAJMOC@?5map?5?$DN?5?$CFd?6?$AA@ @ 0x003E3E88
// match: ??_C@_0CC@DGABLDOM@cNetGame?3?3createServer?5name?$DN?$CC?$CFs?$CC@ @ 0x003E3E94
// match: ??_C@_0BG@BPMLLGEJ@cNetGame?3?3joinServer?6?$AA@ @ 0x003E3EB8
// match: ??_C@_0BN@EDPIONEH@cNetGame?3?3setError?$CI?$CFd?5?3?5?$CFs?$CJ?6?$AA@ @ 0x003E3ED0
// match: ??_C@_0DI@OONCKADM@packetEngineHasRunOutOfRam?5?9?5has@ @ 0x003E3EF0
// match: ??_C@_0CN@PCAEJDGG@Error?5condition?5missing?5from?5err@ @ 0x003E3F28
// match: ??_C@_0BC@LJFJPPFB@eErrorRunOutOfRam?$AA@ @ 0x003E3F58
// match: ??_C@_0BP@FBDBCIPE@eErrorFailureDuringGetGameList?$AA@ @ 0x003E3F6C
// match: ??_C@_0BL@LMPALJKE@eErrorCouldNotRegisterGame?$AA@ @ 0x003E3F8C
// match: ??_C@_0BM@PEBJHALO@eErrorUnexpectedTermination?$AA@ @ 0x003E3FA8
// match: ??_C@_0BM@KDCLMMHP@eErrorCouldNotConnectToGame?$AA@ @ 0x003E3FC4
// match: ??_C@_0BO@MJEOONEP@eErrorCouldNotConnectToSocket?$AA@ @ 0x003E3FE0
// match: ??_C@_0BL@EAOHPNOE@eErrorCouldNotCreateSocket?$AA@ @ 0x003E4000
// match: ??_C@_0BP@GJEKGNEB@eErrorNone?9?5there?5is?5no?5error?$CB?$AA@ @ 0x003E401C
// match: __ehhandler$??0type_4F8054@@QAE@XZ>1>8 @ 0x0041F908
// match: __ehhandler$??0type_4F8054@@QAE@XZ>1 @ 0x0041F920

// match: ??0type_4F8054@@QAE@XZ @ 0x001CBC80
// match: __ehhandler$??0type_4F8054@@QAE@XZ-0x21 @ 0x00303500
// match: __ehhandler$??0type_4F8054@@QAE@XZ @ 0x00303521

type_4F8054::type_4F8054()
{
    unk_04 = 0;
    unk_0C = 0;
    unk_AC = new type_1D0100;
    unk_B0 = new type_4F8054_B0;
    unk_B4 = new cTimeKeeper;
    unk_A0 = 0;
    unk_A4 = 0;
    unk_A8 = 0;
    unk_B8 = 0;
    unk_C0 = type_1CCA10();
    unk_C4 = type_1CCA10();
    unk_C8 = 1;
    unk_CC = 1;
}

// match: ?vf_06C@type_4F8054@@UAEHXZ @ 0x001CBE70

// The players' compiler-generated constructor, out of line.
// match: ??0type_4F8054_B0@@QAE@XZ @ 0x001CBEC0

// match: ??_Gtype_4F8054@@UAEPAXI@Z @ 0x001CBE90

// match: ??1type_4F8054@@UAE@XZ @ 0x001CBFD0
type_4F8054::~type_4F8054()
{
    delete unk_AC;
    delete unk_B0;
    delete unk_B4;
}

// match: ?vf_004@type_4F8054@@UAEXXZ @ 0x001CC080
void type_4F8054::vf_004()
{
    unk_BC = 0;
    memset(&unk_18, 0, 0x34);
    unk_80[0] = 0;
    unk_04 = 0;
    unk_0C = 0;
    unk_10 = 0;
    unk_B0->sub_1CCC00(this);
    unk_AC->sub_1D04B0(this);
    unk_B4->sub_1D4B80(this);
    unk_10 = 0;
    unk_14 = 0;
}

// match: ?sub_1CC120@type_4F8054@@QAEXXZ @ 0x001CC120
void type_4F8054::sub_1CC120()
{
    vf_008();
    vf_004();
}

// match: ?vf_008@type_4F8054@@UAEXXZ @ 0x001CC150
void type_4F8054::vf_008()
{
    if (unk_04 == 1 || unk_04 == 2)
    {
        if (CODFH_DEBUG_LOGS)
            sub_1C8A30("cNetGame::deinitialise\n");
        if (CODFH_DEBUG_LOGS)
            sub_1C8A30(" mState = eStateServerTakeDown\n");
        unk_04 = 3;
        vf_00C(sub_1CCA10());
    }
    vf_07C();
    unk_AC->sub_1D07A0();
    unk_B0->sub_1CCD20();
    unk_B4->pDtor();
}

// match: ?vf_05C@type_4F8054@@UAEXPBUtype_1CC1F0@@@Z @ 0x001CC1F0
void type_4F8054::vf_05C(const type_1CC1F0 *arg_0)
{
    if (CODFH_DEBUG_LOGS)
        sub_1C8A30("cNetGame::createServer name=\"%s\"\n", arg_0->unk_0C);
    if (CODFH_DEBUG_LOGS)
        sub_1C8A30(" map = %d\n", arg_0->unk_10);
    if (CODFH_DEBUG_LOGS)
        sub_1C8A30(" mState = eStateServerTakeUp\n");
    unk_18 = 0x34;
    memcpy(unk_34, arg_0->unk_05, 4);
    unk_38 = arg_0->unk_0A;
    if (!unk_04)
    {
    }
    strcpy(unk_1C, arg_0->unk_0C);
    if (!unk_04)
    {
    }
    strcpy(unk_80, arg_0->unk_00);
    unk_3C = arg_0->unk_04;
    unk_40 = arg_0->unk_10;
    unk_41 = arg_0->unk_11;
    unk_42 = arg_0->unk_12;
    if (!unk_04)
    {
    }
    unk_43 = arg_0->unk_13;
    unk_44 = arg_0->unk_14;
    unk_45 = arg_0->unk_15;
    unk_48 = arg_0->unk_16;
    if (!unk_04)
    {
    }
    unk_04 = 1;
    unk_0C = 0;
    unk_B8 = 1;
}

// match: ?vf_070@type_4F8054@@UAEXPBUtype_1CC1F0@@PBUtype_4F8054_4C@@HH@Z @ 0x001CC320
void type_4F8054::vf_070(const type_1CC1F0 *arg_0, const type_4F8054_4C *arg_4, RwInt32 arg_8, RwInt32 arg_C)
{
    unk_3C = arg_0->unk_04;
    unk_38 = arg_0->unk_0A;
    if (arg_4)
        unk_4C = *arg_4;
    else
    {
        unk_4C.unk_18 = -1;
        unk_4C.unk_14 = -1;
        unk_4C.unk_10 = -1;
        unk_4C.unk_00[0] = -1;
        unk_4C.unk_00[1] = -1;
        unk_4C.unk_00[2] = -1;
        unk_4C.unk_00[3] = -1;
        unk_4C.unk_1C = 0;
        unk_4C.unk_2C = 1;
    }
}

// match: ?vf_060@type_4F8054@@UAEXPBUtype_1CC1F0@@PBUtype_1CC3C0@@H@Z @ 0x001CC3C0
void type_4F8054::vf_060(const type_1CC1F0 *arg_0, const type_1CC3C0 *arg_4, RwInt32 arg_8)
{
    if (CODFH_DEBUG_LOGS)
        sub_1C8A30("cNetGame::joinServer\n");
    if (CODFH_DEBUG_LOGS)
        sub_1C8A30(" mState = eStateServerTakeUp\n");
    memcpy(unk_34, arg_4->unk_04, 4);
    unk_38 = arg_4->unk_08;
    unk_3C = arg_0->unk_04;
    unk_42 = arg_4->unk_2C;
    unk_41 = arg_4->unk_2B;
    unk_40 = arg_4->unk_28;
    unk_43 = arg_4->unk_2A;
    unk_44 = arg_4->unk_2D;
    unk_45 = arg_4->unk_2E;
    strcpy(unk_1C, arg_4->unk_10);
    unk_18 = 0x34;
    memcpy(unk_98, arg_0->unk_05, 4);
    unk_9C = arg_0->unk_0A;
    if (!unk_04)
    {
    }
    strcpy(unk_80, arg_0->unk_00);
    if (!unk_04)
    {
    }
    unk_04 = 4;
    unk_0C = 0;
    unk_B8 = 0;
}

// match: ?vf_064@type_4F8054@@UAEXEEEEE@Z @ 0x001CC4F0
void type_4F8054::vf_064(RwUInt8 arg_0, RwUInt8 arg_4, RwUInt8 arg_8, RwUInt8 arg_C, RwUInt8 arg_10)
{
    unk_42 = arg_8;
    unk_41 = arg_4;
    unk_40 = arg_0;
    unk_44 = arg_C;
    unk_45 = arg_10;
    vf_080(0, 1);
}

// match: ?vf_00C@type_4F8054@@UAEXABUtype_1CCA10@@@Z @ 0x001CC540
void type_4F8054::vf_00C(const type_1CCA10 &arg_0)
{
    if (get_unk_10())
        return;
    unk_7C = arg_0;
    if (unk_04 == 2)
    {
        // A compiled-out check: the registers after it are one load on
        // (docs/toolchain.md).
        if (!unk_04)
        {
        }
        unk_B0->sub_1CFD50(arg_0);
    }
    else if (unk_04 == 5)
    {
        // A compiled-out check: the registers after it are one load on
        // (docs/toolchain.md).
        if (!unk_04)
        {
        }
        unk_B0->sub_1CFD50(arg_0);
    }
    unk_B4->sub_1D4CA0();
    unk_AC->sub_1D3610(arg_0);
    unk_08 = unk_04;
}

// match: ?vf_068@type_4F8054@@UAEXH@Z @ 0x001CC5D0
void type_4F8054::vf_068(RwInt32 arg_0)
{
    unk_B0->sub_1CD6E0(arg_0);
}

// match: ?sub_1CC5F0@type_4F8054@@QAEHABUtype_1DDE20_mask@@PAUtype_1F8560@@H@Z @ 0x001CC5F0
RwInt32 type_4F8054::sub_1CC5F0(const type_1DDE20_mask &arg_0, type_1F8560 *arg_4, RwInt32 arg_8)
{
    type_1CCA10 var_4 = sub_1CCA10();

    if (!((type_1DDE20_mask &)arg_0).empty())
        return unk_AC->sub_1D0F60(arg_0, arg_4, arg_8, var_4, 2);
    return 0;
}

// match: ?sub_1CC640@type_4F8054@@QAEHABUtype_1DDE20_mask@@PAUtype_1F8560@@H@Z @ 0x001CC640
RwInt32 type_4F8054::sub_1CC640(const type_1DDE20_mask &arg_0, type_1F8560 *arg_4, RwInt32 arg_8)
{
    type_1CCA10 var_4 = sub_1CCA10();

    if (!((type_1DDE20_mask &)arg_0).empty())
        return unk_AC->sub_1D0F60(arg_0, arg_4, arg_8, var_4, 1);
    return 0;
}

// match: ?sub_1CC690@type_4F8054@@QAEHABUtype_1DDE20_mask@@PAUtype_1F8560@@H@Z @ 0x001CC690
RwInt32 type_4F8054::sub_1CC690(const type_1DDE20_mask &arg_0, type_1F8560 *arg_4, RwInt32 arg_8)
{
    type_1CCA10 var_4 = sub_1CCA10();

    if (!((type_1DDE20_mask &)arg_0).empty())
        return unk_AC->sub_1D0F60(arg_0, arg_4, arg_8, var_4, 4);
    return 0;
}

// match: ?sub_1CC6E0@type_4F8054@@QAEHABUtype_1DDE20_mask@@PAUtype_1F8560@@H@Z @ 0x001CC6E0
RwInt32 type_4F8054::sub_1CC6E0(const type_1DDE20_mask &arg_0, type_1F8560 *arg_4, RwInt32 arg_8)
{
    type_1CCA10 var_4 = sub_1CCA10();

    if (!((type_1DDE20_mask &)arg_0).empty())
        return unk_AC->sub_1D0F60(arg_0, arg_4, arg_8, var_4, 0);
    return 0;
}

// match: ?sub_1CC730@type_4F8054@@QAEHABUtype_1DDE20_mask@@PAUtype_1F8560@@H@Z @ 0x001CC730
RwInt32 type_4F8054::sub_1CC730(const type_1DDE20_mask &arg_0, type_1F8560 *arg_4, RwInt32 arg_8)
{
    type_1CCA10 var_4 = sub_1CCA10();

    if (!((type_1DDE20_mask &)arg_0).empty())
        return unk_AC->sub_1D0F60(arg_0, arg_4, arg_8, var_4, 3);
    return 0;
}

// match: ?sub_1CC780@type_4F8054@@QAEXHHHH@Z @ 0x001CC780
void type_4F8054::sub_1CC780(RwInt32 arg_0, RwInt32 arg_4, RwInt32 arg_8, RwInt32 arg_C)
{
    // A compiled-out check: the registers after it are one load on
    // (docs/toolchain.md).
    if (!unk_04)
    {
    }
    if (unk_A0)
        unk_A0->vf_000(arg_0, arg_4, arg_8, arg_C, 1, 1);
}

// match: ?sub_1CC7D0@type_4F8054@@QAEXHHHH@Z @ 0x001CC7D0
void type_4F8054::sub_1CC7D0(RwInt32 arg_0, RwInt32 arg_4, RwInt32 arg_8, RwInt32 arg_C)
{
    // A compiled-out check: the registers after it are one load on
    // (docs/toolchain.md).
    if (!unk_04)
    {
    }
    if (unk_A0)
        unk_A0->vf_000(arg_0, arg_4, arg_8, arg_C, 0, 0);
}

// match: ?sub_1CC820@type_4F8054@@QAEXHHPAUtype_1F8560@@H@Z @ 0x001CC820
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void type_4F8054::sub_1CC820(RwInt32 arg_0, RwInt32 arg_4, type_1F8560 *arg_8, RwInt32 arg_C)
{
    RwUInt32 var_8;
    RwInt32 l4;

    var_8 = arg_8->unk_08;
    l4 = arg_8->sub_1F8B30(0, 0xF);
    arg_8->unk_08 = var_8;
    if (unk_B4->sub_1D5010(l4, arg_0, arg_4, arg_8, arg_C) == 1)
        return;
    unk_B0->sub_1CE650(l4, arg_0, arg_4, arg_8, arg_C);
}

// match: ?sub_1CC8A0@type_4F8054@@QAEXHHHHH@Z @ 0x001CC8A0
void type_4F8054::sub_1CC8A0(RwInt32 arg_0, RwInt32 arg_4, RwInt32 arg_8, RwInt32 arg_C, RwInt32 arg_10)
{
    // A compiled-out check: the registers after it are one load on
    // (docs/toolchain.md).
    if (!unk_04)
    {
    }
    if (unk_A4)
        unk_A4->vf_000(arg_0, arg_4, arg_8, arg_C, arg_10);
}

// The debug print through a pointer (its target is empty in this build).
extern void (*off_42CD14)(const RwChar *arg_0, ...);

// match: ?setError@type_4F8054@@QAEXHH@Z @ 0x001CC8F0
void type_4F8054::setError(RwInt32 arg_0, RwInt32 arg_4)
{
    if (CODFH_DEBUG_LOGS)
        off_42CD14("cNetGame::setError(%d : %s)\n", arg_0, errorToString(arg_0));
    // A compiled-out check: the registers after it are one load on
    // (docs/toolchain.md).
    if (!unk_04)
    {
    }
    unk_10 = arg_0;
    unk_14 = arg_4;
}

// match: ?packetEngineHasRunOutOfRam@type_4F8054@@QAEXXZ @ 0x001CC940
void type_4F8054::packetEngineHasRunOutOfRam()
{
    if (CODFH_DEBUG_LOGS)
        off_42CD14("packetEngineHasRunOutOfRam - has been called... Panic!\n");
    unk_B0->sub_1CD370();
    setError(6, 10);
}

// match: ?errorToString@type_4F8054@@QAEPBDH@Z @ 0x001CC980
const RwChar *type_4F8054::errorToString(RwInt32 arg_0)
{
    switch (arg_0)
    {
    case 0:
        return "eErrorNone- there is no error!";
    case 1:
        return "eErrorCouldNotCreateSocket";
    case 2:
        return "eErrorCouldNotConnectToSocket";
    case 3:
        return "eErrorCouldNotConnectToGame";
    case 7:
        return "eErrorUnexpectedTermination";
    case 4:
        return "eErrorCouldNotRegisterGame";
    case 5:
        return "eErrorFailureDuringGetGameList";
    case 6:
        return "eErrorRunOutOfRam";
    default:
        return "Error condition missing from errorToString()";
    }
}

// The counter's seconds per tick (worked out on the first call) and its
// start.
extern RwDouble dbl_4FEC68;
extern LARGE_INTEGER PerformanceCount;

// match: ?sub_1CCA10@@YA?AUtype_1CCA10@@XZ @ 0x001CCA10
type_1CCA10 sub_1CCA10()
{
    type_1CCA10 var_C;
    LARGE_INTEGER var_18;
    LARGE_INTEGER bp_8;

    if (dbl_4FEC68 == 0.0)
    {
        QueryPerformanceFrequency(&var_18);
        if (!var_18.QuadPart)
            var_18.QuadPart = 1;
        dbl_4FEC68 = 1.0 / (RwDouble)(ULONGLONG)var_18.QuadPart;
        QueryPerformanceCounter(&PerformanceCount);
    }
    QueryPerformanceCounter(&bp_8);
    var_C = type_1CCA10((RwInt32)((RwReal)((RwDouble)(ULONGLONG)(bp_8.QuadPart - PerformanceCount.QuadPart) * dbl_4FEC68) * 1000.0f));
    return var_C;
}

// match: ?sub_1CCB10@type_4F8054@@QAEXXZ @ 0x001CCB10
void type_4F8054::sub_1CCB10()
{
    get_unk_B0()->sub_1CD370();
    sub_1CC120();
}

// match: ?sub_1CCB40@type_4F8054@@QAEHXZ @ 0x001CCB40
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
RwInt32 type_4F8054::sub_1CCB40()
{
    RwChar var_2C[0x20];
    const RwUInt32 *var_8;
    const RwChar *l4;

    if (!unk_BC)
    {
        l4 = vf_010();
        memset(var_2C, 0, sizeof(var_2C));
        strcpy(var_2C, l4);
        var_8 = (const RwUInt32 *)var_2C;
        unk_BC = (var_8[0] ^ var_8[1] ^ var_8[2] ^ var_8[3]) + sub_1CCA10().get_unk_00();
        if (!unk_BC)
            unk_BC = 666;
    }
    return unk_BC;
}
