// The voice chat (game/voice.h): the voice manager and the XHV engine's
// owner.

#include "game/liveservice.h"
#include <string.h>

#include "game/voice.h"
#include "game/gameloop.h"
#include "game/waitscreen.h"
#include "game/startup.h"

// Its data definitions (PLAN M5), in the image's address order.
// 0x003E3858
extern const RwReal flt_3E3858 = 0.01f;
// End of its data definitions.


// symbol: ?vf_000@type_3E386C@@UAEXHPAXI@Z = 0x00073D80
// symbol: ?vf_000@type_3E3868@@UAEXPAEI@Z = 0x00073D90

// Vtables (.rdata, PLAN M5): each in its own placement range (config/splits.txt).
// Its data (PLAN M5): literals, constants and tables where the image has them.
// match: ?flt_3E3858@@3MB @ 0x003E3858
// match: ??_7type_3E3860@@6Btype_3E3868@@@ @ 0x003E385C
// match: ??_7type_3E3860@@6Btype_3E386C@@@ @ 0x003E3860
// match: ??_7type_3E3868@@6B@ @ 0x003E3868
// match: ??_7type_3E386C@@6B@ @ 0x003E386C
// match: ??_7type_3E3870@@6B@ @ 0x003E3870
// match: __ehhandler$??0type_3E3860@@QAE@PAUtype_4F8054@@PAUtype_3E3860_10@@@Z>1>8 @ 0x0041F550
// match: __ehhandler$??0type_3E3860@@QAE@PAUtype_4F8054@@PAUtype_3E3860_10@@@Z>1 @ 0x0041F558
// match: __ehhandler$??1type_3E3860@@UAE@XZ>1>8 @ 0x0041F574
// match: __ehhandler$??1type_3E3860@@UAE@XZ>1 @ 0x0041F57C

// match: ??0type_3E3860@@QAE@PAUtype_4F8054@@PAUtype_3E3860_10@@@Z @ 0x001C60A0
// match: __ehhandler$??0type_3E3860@@QAE@PAUtype_4F8054@@PAUtype_3E3860_10@@@Z-0xB @ 0x003031E0
// match: __ehhandler$??0type_3E3860@@QAE@PAUtype_4F8054@@PAUtype_3E3860_10@@@Z @ 0x003031EB

type_3E3860::type_3E3860(type_4F8054 *arg_0, type_3E3860_10 *arg_4)
    : unk_08(0), unk_0C(arg_0), unk_10(arg_4), unk_14(arg_4)
{
    unk_315C = 0;
}

// The channel's destructor, out of line where the voice manager's
// constructor and destructor unwind, and its deleting destructor.
// match: ??1type_3E3870@@UAE@XZ @ 0x001C61C0
// match: ??_Gtype_3E3870@@UAEPAXI@Z @ 0x001C61E0

// match: ??_Gtype_3E3860@@UAEPAXI@Z @ 0x001C6210

// match: ??1type_3E3860@@UAE@XZ @ 0x001C6240
// match: __ehhandler$??1type_3E3860@@UAE@XZ-0xB @ 0x00303200
// match: __ehhandler$??1type_3E3860@@UAE@XZ @ 0x0030320B
type_3E3860::~type_3E3860()
{
}

// match: ?sub_1C62B0@type_3E3860@@QAEXXZ @ 0x001C62B0
void type_3E3860::sub_1C62B0()
{
    type_3E3860_10 *var_4 = unk_10;

    var_4->unk_08 = &unk_14;
    unk_14.unk_0C = this;
    unk_14.sub_1DE450();
    sub_1C64B0();
    unk_08 = 1;
}

// match: ?sub_1C6300@type_3E3860@@QAEXXZ @ 0x001C6300
void type_3E3860::sub_1C6300()
{
    type_3E3860_10 *var_4;

    unk_08 = 0;
    pDtor();
    unk_14.pDtor();
    unk_14.unk_0C = 0;
    var_4 = unk_10;
    var_4->unk_08 = 0;
}

// match: ?sub_1C6350@type_3E3860@@QAEXXZ @ 0x001C6350
void type_3E3860::sub_1C6350()
{
    type_1CCA10 var_4;

    if (unk_315C)
        unk_3060.sub_1C6EC0();
    if (unk_08 && (unk_0C->get_unk_04() == 5 || unk_0C->get_unk_04() == 2) &&
        (unk_0C->get_unk_B0()->get_unk_310() == 7 || unk_0C->get_unk_B8()))
    {
        var_4 = unk_0C->get_unk_7C();
        sub_1C6420(var_4);
        unk_14.sub_1DF970(var_4);
    }
}

// match: ?sub_1C6420@type_3E3860@@QAEXABUtype_1CCA10@@@Z @ 0x001C6420
void type_3E3860::sub_1C6420(const type_1CCA10 &arg_0)
{
    sub_1C6530();
    sub_1C6700();
}

// match: ?sub_1C6440@type_3E3860@@QAEXABUtype_1DDE20_mask@@@Z @ 0x001C6440
void type_3E3860::sub_1C6440(const type_1DDE20_mask &arg_0)
{
    unk_267C = arg_0;
}

// match: ?vf_000@type_3E3860@@UAEXHPAXI@Z @ 0x001C6460
void type_3E3860::vf_000(RwInt32 arg_0, void *arg_4, RwUInt32 arg_8)
{
    // A compiled-out check: the registers after it are one load on
    // (docs/toolchain.md).
    if (!unk_08)
    {
    }
    // A compiled-out check: the registers after it are one load on
    // (docs/toolchain.md).
    if (!unk_08)
    {
    }
    if (!unk_267C.test(arg_0))
        return;
    if (unk_315C)
        unk_3060.sub_1C7330(arg_0, (RwUInt8 *)arg_4, arg_8);
}

// match: ?sub_1C64B0@type_3E3860@@QAEXXZ @ 0x001C64B0
void type_3E3860::sub_1C64B0()
{
    memset(unk_2688, 0, sizeof(unk_2688));
    unk_304C = 0;
    unk_3050 = 0;
    unk_2680 = type_1CCA10();
    unk_2684 = type_1CCA10();
    unk_267C.unk_00 = 0;
}

// match: ?sub_1C6530@type_3E3860@@QAEXXZ @ 0x001C6530
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void type_3E3860::sub_1C6530()
{
    type_1DDE20_mask var_C;
    type_1DDE20_mask var_10;
    type_1DDE20_mask bp_8;
    RwUInt32 bp_4;

    var_C = unk_0C->get_unk_B0()->sub_1A8050();
    // A compiled-out check: the registers after it are one load on
    // (docs/toolchain.md).
    if (!unk_08)
    {
    }
    var_10 = unk_3060.get_unk_14();
    // A compiled-out check: the registers after it are one load on
    // (docs/toolchain.md).
    if (!unk_08)
    {
    }
    bp_8 = sub_1D8810()->get_unk_292C();
    for (bp_4 = 0; bp_4 < 16; bp_4++)
    {
        if (!unk_08)
        {
        }
        if (var_C.test(bp_4))
        {
            if (!unk_08)
            {
            }
            if (!unk_267E.test(bp_4))
                unk_267E.add(bp_4);
            if (!unk_08)
            {
            }
            if (!var_10.test(bp_4) && bp_8.test(bp_4))
                unk_3060.sub_1C70D0(bp_4);
        }
        else
        {
            if (!unk_08)
            {
            }
            if (unk_267E.test(bp_4))
            {
                unk_267E.clear(bp_4);
                if (!unk_08)
                {
                }
                if (var_10.test(bp_4))
                    unk_3060.sub_1C7230(bp_4);
            }
            unk_14.sub_1DE770(bp_4);
            if (!unk_08)
            {
            }
            if (unk_267C.test(bp_4))
                unk_267C.clear(bp_4);
        }
    }
}

// Sends the microphone data buffered since the last send: 50 bytes at a time,
// or what there is once 100 milliseconds have passed.
// match: ?sub_1C6700@type_3E3860@@QAEXXZ @ 0x001C6700
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void type_3E3860::sub_1C6700()
{
    type_1CCA10 var_4;
    type_1CCA10 lv_C;
    RwUInt32 loc8;

    if (unk_2680 == lv_C)
        unk_2684 = unk_0C->get_unk_7C();
    if (unk_304C >= unk_3050)
        loc8 = unk_304C - unk_3050;
    else
        loc8 = sizeof(unk_2688) - unk_3050;
    if (!loc8 || unk_2680 == type_1CCA10())
        unk_2680 = unk_0C->get_unk_7C();
    var_4 = unk_0C->get_unk_7C().since(unk_2680);
    if (loc8 >= 50 || (loc8 > 0 && var_4 > 100))
    {
        if (loc8 > 50)
            loc8 = 50;
        if (!unk_267C.empty())
        {
            unk_14.sub_1DEE60(get_unk_267C(), &unk_2688[unk_3050], loc8);
            unk_2684 = unk_0C->get_unk_7C();
        }
        unk_2680 = unk_2680 + 100;
        unk_3050 += loc8;
        // A compiled-out check (docs/toolchain.md): one load on.
        if (!unk_08)
        {
        }
        if (unk_3050 >= sizeof(unk_2688))
            unk_3050 = 0;
    }
}

// match: ?sub_1C6900@type_3E3860@@QAEXPAUtype_1C6900@@ABUtype_1CCA10@@@Z @ 0x001C6900
void type_3E3860::sub_1C6900(type_1C6900 *arg_0, const type_1CCA10 &arg_4)
{
    // A compiled-out check: the registers after it are one load on
    // (docs/toolchain.md).
    if (!unk_08)
    {
    }
    memset(arg_0, 0, 0xE0);
}

// match: ?sub_1C6920@type_3E3860@@QAEXH@Z @ 0x001C6920
void type_3E3860::sub_1C6920(RwInt32 arg_0)
{
    RwUInt32 var_4;

    // A compiled-out check: the registers after it are one load on
    // (docs/toolchain.md).
    if (!unk_08)
    {
    }
    unk_3060.set_unk_24(this);
    var_4 = 0;
    if (has_dword_4B9E50())
        var_4 = get_dword_4B9E50();
    unk_3060.sub_1C6C00(var_4, arg_0);
    unk_315C = 1;
}

// match: ?sub_1C69A0@type_3E3860@@QAEXXZ @ 0x001C69A0
void type_3E3860::sub_1C69A0()
{
    // A compiled-out check: the registers after it are one load on
    // (docs/toolchain.md).
    if (!unk_08)
    {
    }
    unk_3060.sub_1C6E70();
    unk_315C = 0;
}

// match: ?vf_000@type_3E3860@@UAEXPAEI@Z @ 0x001C69D0
void type_3E3860::vf_000(RwUInt8 *arg_4, RwUInt32 arg_8)
{
    RwUInt32 var_4;
    RwUInt32 l8;

    if (unk_08)
    {
        l8 = sizeof(unk_2688) - unk_304C;
        var_4 = arg_8 > l8 ? l8 : arg_8;
        memcpy(&unk_2688[unk_304C], arg_4, var_4);
        unk_304C += var_4;
        if (unk_304C == sizeof(unk_2688))
        {
            unk_304C = 0;
            arg_8 -= var_4;
            arg_4 += var_4;
            if (arg_8)
            {
                memcpy(unk_2688, arg_4, arg_8);
                unk_304C += arg_8;
            }
        }
    }
}



// The playback volume's scale (0x7FFFFF).
extern const RwReal flt_3E389C;













// The interface's own microphone callback (not overridden).







// Empty and out of line (folded by /OPT:ICF into the shared pDtor, 0x1E41C0).
void type_3E3860::pDtor()
{
}
