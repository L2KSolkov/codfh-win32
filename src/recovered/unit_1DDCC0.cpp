// Split from unit_1DDBE0.cpp at 0x1DDCC0, where the image ends that object (its deferred
// functions come before the next out-of-line one; PLAN M7).

#include <new>
#include "game/netmsg.h"
#include "game/netplayer.h"
#include "game/voice.h"
#include "types/type_DC400.h"
#include "game/mpgame.h"

// Its data definitions (PLAN M5), in the image's address order.
// 0x003E66BC
extern const RwReal flt_3E66BC = 16.666666f;
// 0x003E66C0
extern const RwReal flt_3E66C0 = 0.01f;
// 0x003E66C4
extern const RwReal flt_3E66C4 = 0.01f;

// match: ?flt_3E66BC@@3MB @ 0x003E66BC
// match: ?flt_3E66C0@@3MB @ 0x003E66C0
// match: ?flt_3E66C4@@3MB @ 0x003E66C4


// The session's element: a networked object.
typedef type_3E1388 *type_3E1388_p;

// match: __ehhandler$??1type_4F8058@@UAE@XZ>1>8 @ 0x0041FC5C
// match: __ehhandler$??1type_4F8058@@UAE@XZ>1 @ 0x0041FC64
// match: ??_Gtype_4F8058@@UAEPAXI@Z @ 0x001DDD10
// match: ??_7type_4F8058@@6B@ @ 0x003E66C8
// match: ??_7type_4F8054_A0@@6B@ @ 0x003E66D0
// match: ??_7type_3E66D4@@6B@ @ 0x003E66D4
// The message listener's base's empty method (type_4F8054_A4's, in
// game/netlisten.h; the voice channel's base, type_3E66D4, has one identical
// to it, folded by /OPT:ICF).

// match: ??0type_4F8058@@QAE@PAUtype_4F8054@@@Z @ 0x001DDCC0
type_4F8058::type_4F8058(type_4F8054 *arg_0) : unk_04(arg_0), unk_08(sub_1CBC30())
{
}
// match: ??1type_4F8058@@UAE@XZ @ 0x001DDD40
// match: __ehhandler$??1type_4F8058@@UAE@XZ-0x8 @ 0x00303730
// match: __ehhandler$??1type_4F8058@@UAE@XZ @ 0x00303738
type_4F8058::~type_4F8058()
{
}
extern type_1F8560 unk_502EF0;
// match: ?sub_1DDDB0@type_4F8058@@QAEXPAUtype_3DA44C@@ABUtype_1DDE20_mask@@@Z @ 0x001DDDB0
void type_4F8058::sub_1DDDB0(type_3DA44C *arg_0, const type_1DDE20_mask &arg_4)
{
    unk_502EF0.unk_08 = 0;
    unk_502EF0.sub_1F8B90(arg_0->vf_008(), 0, 0x23);
    arg_0->vf_000(&unk_502EF0);
    unk_04->sub_1CC640(arg_4, &unk_502EF0, unk_502EF0.get_unk_08());
}
// match: ?sub_1DDE20@type_4F8058@@QAEXPAUtype_3DA44C@@ABUtype_1DDE20_mask@@@Z @ 0x001DDE20
void type_4F8058::sub_1DDE20(type_3DA44C *arg_0, const type_1DDE20_mask &arg_4)
{
    unk_502EF0.unk_08 = 0;
    unk_502EF0.sub_1F8B90(arg_0->vf_008(), 0, 0x23);
    arg_0->vf_000(&unk_502EF0);
    unk_04->sub_1CC690(arg_4, &unk_502EF0, unk_502EF0.get_unk_08());
}
// match: ?sub_1DDE90@type_4F8058@@QAEXPAUtype_3DA44C@@ABUtype_1DDE20_mask@@@Z @ 0x001DDE90
void type_4F8058::sub_1DDE90(type_3DA44C *arg_0, const type_1DDE20_mask &arg_4)
{
    unk_502EF0.unk_08 = 0;
    unk_502EF0.sub_1F8B90(arg_0->vf_008(), 0, 0x23);
    arg_0->vf_000(&unk_502EF0);
    unk_04->sub_1CC6E0(arg_4, &unk_502EF0, unk_502EF0.get_unk_08());
}
// match: ?sub_1DDF00@type_4F8058@@QAEXHHPAUtype_1F8560@@@Z @ 0x001DDF00
void type_4F8058::sub_1DDF00(RwInt32 arg_0, RwInt32 arg_4, type_1F8560 *arg_8)
{
    RwInt32 var_C = arg_8->sub_1F8B30(0, 0x23);
    RwUInt32 var_8;
    struct type_3DA44C *var_4;

    for (var_8 = 0; var_8 < dword_42CAB4; var_8++)
    {
        if (unk_42C848[var_8].unk_04 == var_C)
        {
            switch (unk_42C848[var_8].unk_00)
            {
            case 0:
                // Two compiled-out checks: the registers after them are two
                // loads on (docs/toolchain.md).
                if (!unk_42C848[var_8].unk_08)
                {
                }
                if (!unk_42C848[var_8].unk_0C)
                {
                }
                var_4 = unk_42C848[var_8].unk_08(arg_8);
                unk_42C848[var_8].unk_0C(arg_0, arg_4, var_4);
                break;
            case 1:
                // A compiled-out check (docs/toolchain.md).
                if (!unk_42C848[var_8].unk_10)
                {
                }
                unk_42C848[var_8].unk_10(arg_0, arg_4, arg_8);
                break;
            }
            break;
        }
    }
}
// match: ?sub_1DDFD0@type_4F8058@@QAEXABUtype_1CCA10@@@Z @ 0x001DDFD0
void type_4F8058::sub_1DDFD0(const type_1CCA10 &arg_0)
{
    sub_1DDFF0(arg_0);
}
// match: ?sub_1DDFF0@type_4F8058@@QAEXABUtype_1CCA10@@@Z @ 0x001DDFF0
void type_4F8058::sub_1DDFF0(const type_1CCA10 &arg_0)
{
    for (unk_08.first(); unk_08.sub_1FA590(); unk_08.sub_1D0E70())
    {
        type_3E1388 *var_8 = *unk_08.current();
        type_1CCA10 var_4 = var_8->unk_18 + var_8->get_unk_04();

        if (var_8->unk_08 && arg_0 > var_4)
        {
            type_1DDE20_mask var_C;

            switch (var_8->unk_10)
            {
            case 0:
                var_C = unk_04->get_unk_B0()->sub_1A8050();
                break;
            case 1:
                var_C.put(0);
                break;
            case 2:
                var_C.unk_00 = var_8->unk_0C.unk_00;
                break;
            }
            if (!var_C.empty())
            {
                switch (var_8->unk_14)
                {
                case 1:
                    sub_1DDDB0(var_8->vf_000(), var_C);
                    break;
                case 0:
                    sub_1DDE90(var_8->vf_000(), var_C);
                    break;
                }
                // A compiled-out check (docs/toolchain.md).
                if (!var_8->unk_08)
                {
                }
                var_8->unk_08 = 0;
                var_8->unk_18 = arg_0;
            }
        }
    }
}
// match: ?sub_1DE1A0@type_4F8058@@QAEXPAUtype_4F6B00@@@Z @ 0x001DE1A0
void type_4F8058::sub_1DE1A0(type_4F6B00 *arg_0)
{
    void *p = unk_08.sub_1FA310(sizeof(type_3E1388 *));

    if (p)
        new (p) type_3E1388_p(static_cast<type_3E1388 *>(arg_0));
}
// match: ?vf_000@type_4F8058@@UAEXHHHHHH@Z @ 0x001DE1F0
void type_4F8058::vf_000(RwInt32 arg_0, RwInt32 arg_4, RwInt32 arg_8, RwInt32 arg_C, RwInt32 arg_10,
                         RwInt32 arg_14)
{
    if (unk_4F61F8.unk_104)
    {
        if (!type_4F8054::get())
            return;
        if (!type_4F8054::get()->get_unk_B0())
            return;
        if (type_4F8054::get()->get_unk_B0()->get_unk_310() != 7)
            return;
    }
    sub_1DDF00(arg_0, arg_4, (type_1F8560 *)arg_8);
}
// match: ??0type_3E3870@@QAE@PAUtype_3E3860_10@@@Z @ 0x001DE280
type_3E3870::type_3E3870(type_3E3860_10 *arg_0)
    : unk_04(arg_0), unk_0C(0), unk_1A50(0), unk_21A0(0), unk_21A4(0), unk_2230(0), unk_2634(0), unk_2660(0),
      unk_2661(0), unk_2664(0)
{
}
// match: ?sub_1DE450@type_3E3870@@QAEXXZ @ 0x001DE450
void type_3E3870::sub_1DE450()
{
    RwUInt32 var_8;
    RwUInt32 var_4;
    unk_08 = type_1CCA10::zero();
    unk_21A4 = 0;
    unk_21A8.unk_00 = 0;
    unk_21EC = type_1CCA10::zero();
    unk_2230 = 0;
    unk_2634 = 0;
    unk_2660 = 0;
    unk_2661 = 0;
    unk_2664 = 0;
    memset(unk_1A54, 0, sizeof(unk_1A54));
    memset(unk_21AC, 0, sizeof(unk_21AC));
    memset(unk_2642, 16, sizeof(unk_2642));
    memset(unk_2638, 16, sizeof(unk_2638));
    memset(unk_2656, 16, sizeof(unk_2656));
    memset(unk_264C, 16, sizeof(unk_264C));
    unk_1A50 = &unk_10[0];
    unk_10[0].unk_110 = 0;
    unk_10[0].unk_114 = &unk_10[1];
    for (var_8 = 1; var_8 < 23; var_8++)
    {
        unk_10[var_8].unk_110 = &unk_10[var_8 - 1];
        unk_10[var_8].unk_114 = &unk_10[var_8 + 1];
    }
    unk_10[23].unk_110 = &unk_10[22];
    unk_10[23].unk_114 = 0;
    for (var_8 = 0; var_8 < 16; var_8++)
        unk_1A94[var_8] = (RwUInt32)-1;
    unk_21A0 = &unk_1AD4[0];
    unk_1AD4[0].unk_154 = 0;
    unk_1AD4[0].unk_158 = &unk_1AD4[1];
    for (var_8 = 1; var_8 < 4; var_8++)
    {
        unk_1AD4[var_8].unk_154 = &unk_1AD4[var_8 - 1];
        unk_1AD4[var_8].unk_158 = &unk_1AD4[var_8 + 1];
    }
    unk_1AD4[4].unk_154 = &unk_1AD4[3];
    unk_1AD4[4].unk_158 = 0;
    for (var_8 = 0; var_8 < 16; var_8++)
        unk_21F0[var_8] = 0;
    for (var_8 = 0; var_8 < 16; var_8++)
    {
        for (var_4 = 0; var_4 < 16; var_4++)
            unk_2234[var_8][var_4] = -1.0f;
    }
}
// match: ?sub_1DE770@type_3E3870@@QAEXH@Z @ 0x001DE770
void type_3E3870::sub_1DE770(RwInt32 arg_0)
{
    RwUInt32 var_C;
    type_3E3870_out *var_8;
    type_3E3870_out *var_4;

    check();
    while (unk_1A54[arg_0])
        sub_1DED60(arg_0, 1);
    unk_1A94[arg_0] = (RwUInt32)-1;
    unk_21F0[arg_0] = 0;
    var_8 = unk_21A4;
    while (var_8)
    {
        var_4 = var_8->unk_158;
        check();
        check();
        if (var_8->unk_104.test(arg_0))
        {
            var_8->unk_104.clear(arg_0);
            if (var_8->unk_104.empty())
                sub_1DF0E0(var_8);
        }
        var_8 = var_4;
    }
    if (unk_21A8.test(arg_0))
    {
        check();
        unk_21A8.clear(arg_0);
        unk_21AC[arg_0] = type_1CCA10::zero();
        unk_2634--;
    }
    for (var_C = 0; var_C < 16; var_C++)
    {
        unk_2234[var_C][arg_0] = -1.0f;
        unk_2234[arg_0][var_C] = -1.0f;
    }
}
// match: ?vf_000@type_3E3870@@UAEXHHHHH@Z @ 0x001DE900
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void type_3E3870::vf_000(RwInt32 arg_0, RwInt32 arg_4, RwInt32 arg_8, RwInt32 arg_C, RwInt32 arg_10)
{
    RwInt32 var_6C;
    RwUInt8 v65;
    type_3E3870_in *var_64;
    RwUInt32 stk_60;
    type_4F8054_B0 *y5C;
    RwUInt32 stk_58;
    RwUInt32 lcl_54;
    type_1DDE20_mask v50;
    RwUInt32 var4C;
    RwUInt32 q48;
    type_1DDE20_mask v44;
    RwUInt32 stk_40[16];

    y5C = unk_04->get_unk_04()->unk_B0;
    var_6C = y5C->sub_1CFF90();
    stk_60 = ((type_1F8560 *)arg_C)->unk_08;
    v65 = (RwUInt8)((type_1F8560 *)arg_C)->sub_1F8810(8);
    v50.bits((RwUInt16)((type_1F8560 *)arg_C)->sub_1F8810(16));
    v44.bits((RwUInt16)((type_1F8560 *)arg_C)->sub_1F8810(16));
    stk_58 = ((type_1F8560 *)arg_C)->sub_1F8950();
    for (q48 = 0; q48 < 16; q48++)
    {
        if (v50.test(q48))
            stk_40[q48] = stk_58 - ((type_1F8560 *)arg_C)->sub_1F8950();
        else
            stk_40[q48] = (RwUInt32)-1;
    }
    unk_2638[unk_2660] = v65;
    unk_2642[unk_2660] = (RwUInt8)arg_8;
    unk_2660++;
    unk_2660 = unk_2660 < 10 ? unk_2660 : 0;
    lcl_54 = ((type_1F8560 *)arg_C)->unk_08;
    var4C = arg_10 - (lcl_54 - stk_60);
    if (v50.test(var_6C))
    {
        if ((unk_1A94[v65] == (RwUInt32)-1 || unk_1A94[v65] <= stk_40[var_6C]) && !sub_1DED00(stk_58, v65))
        {
            var_64 = sub_1DEB60();
            check();
            ((type_1F8560 *)arg_C)->sub_1F8A40((RwChar *)var_64->unk_000, var4C);
            var_64->unk_108 = var4C >> 3;
            var_64->unk_100 = stk_40[var_6C];
            var_64->unk_104 = stk_58;
            var_64->unk_10C = unk_04->get_unk_04()->get_unk_7C();
            sub_1DEC50(var_64, v65);
        }
        v50.drop(var_6C);
    }
}
// match: ?sub_1DEB60@type_3E3870@@QAEPAUtype_3E3870_in@@XZ @ 0x001DEB60
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
type_3E3870_in *type_3E3870::sub_1DEB60()
{
    RwUInt32 var_C = 16;
    type_3E3870_in *bp_8;
    RwUInt32 bp_4;

    if (!unk_1A50)
    {
        for (bp_4 = 0; bp_4 < 16; bp_4++)
        {
            if (unk_1A54[bp_4] && (var_C == 16 || unk_1A54[bp_4]->unk_10C < unk_1A54[var_C]->unk_10C))
                var_C = bp_4;
        }
        check();
        sub_1DED60(var_C, 0);
    }
    check();
    bp_8 = unk_1A50;
    unk_1A50 = bp_8->unk_114;
    if (unk_1A50)
        unk_1A50->unk_110 = 0;
    bp_8->unk_110 = 0;
    bp_8->unk_114 = 0;
    return bp_8;
}
// match: ?sub_1DEC50@type_3E3870@@QAEXPAUtype_3E3870_in@@H@Z @ 0x001DEC50
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void type_3E3870::sub_1DEC50(type_3E3870_in *arg_0, RwInt32 arg_4)
{
    type_3E3870_in *var_8;
    type_3E3870_in *l4;

    check();
    var_8 = unk_1A54[arg_4];
    l4 = 0;
    while (var_8 && var_8->unk_104 < arg_0->unk_104)
    {
        l4 = var_8;
        var_8 = var_8->unk_114;
    }
    check();
    arg_0->unk_110 = l4;
    if (l4)
        l4->unk_114 = arg_0;
    arg_0->unk_114 = var_8;
    if (var_8)
        var_8->unk_110 = arg_0;
    if (!arg_0->unk_110)
        unk_1A54[arg_4] = arg_0;
}
// match: ?sub_1DED00@type_3E3870@@QAEHIH@Z @ 0x001DED00
RwInt32 type_3E3870::sub_1DED00(RwUInt32 arg_0, RwInt32 arg_4)
{
    type_3E3870_in *var_4 = unk_1A54[arg_4];

    while (var_4 && arg_0 >= var_4->unk_104)
    {
        if (arg_0 == var_4->unk_104)
            return 1;
        var_4 = var_4->unk_114;
    }
    return 0;
}
// match: ?sub_1DED60@type_3E3870@@QAEXHH@Z @ 0x001DED60
void type_3E3870::sub_1DED60(RwInt32 arg_0, RwInt32 arg_4)
{
    type_3E3870_in *var_4;

    do
    {
        check();
        check();
        var_4 = unk_1A54[arg_0];
        unk_1A94[arg_0] = var_4->unk_104;
        unk_1A54[arg_0] = var_4->unk_114;
        if (!arg_4)
            unk_0C->vf_000(arg_0, var_4, var_4->unk_108);
        if (unk_1A50)
            unk_1A50->unk_110 = var_4;
        var_4->unk_110 = 0;
        var_4->unk_114 = unk_1A50;
        unk_1A50 = var_4;
    } while (unk_1A54[arg_0] && unk_1A54[arg_0]->unk_100 == unk_1A94[arg_0]);
}
// match: ?sub_1DEE60@type_3E3870@@QAEXUtype_1DDE20_mask@@PAEI@Z @ 0x001DEE60
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void type_3E3870::sub_1DEE60(type_1DDE20_mask arg_0, RwUInt8 *arg_4, RwUInt32 arg_8)
{
    RwInt32 var_10;
    type_4F8054_B0 *local_C;
    type_3E3870_out *var_8;
    RwUInt32 l4;

    check();
    local_C = unk_04->get_unk_04()->unk_B0;
    var_10 = local_C->sub_1CFF90();
    var_8 = sub_1DEFD0();
    check();
    memcpy(var_8->unk_000, arg_4, arg_8);
    var_8->unk_100 = (RwUInt8)var_10;
    check();
    var_8->unk_102.unk_00 = 1 << var_10;
    var_8->unk_104.unk_00 = 0;
    var_8->unk_104.join(arg_0);
    var_8->unk_148 = unk_2230;
    var_8->unk_14C = arg_8;
    var_8->unk_150 = unk_04->get_unk_04()->get_unk_7C();
    for (l4 = 0; l4 < 16; l4++)
    {
        check();
        if (arg_0.test(l4))
        {
            var_8->unk_108[l4] = unk_21F0[l4];
            unk_21F0[l4] = unk_2230;
        }
        else
            var_8->unk_108[l4] = (RwUInt32)-1;
    }
    unk_2230++;
    sub_1DF080(var_8);
}
// match: ?sub_1DEFD0@type_3E3870@@QAEPAUtype_3E3870_out@@XZ @ 0x001DEFD0
type_3E3870_out *type_3E3870::sub_1DEFD0()
{
    type_3E3870_out *var_4;

    if (!unk_21A0)
    {
        check();
        var_4 = unk_21A4;
        while (var_4->unk_158)
            var_4 = var_4->unk_158;
        sub_1DF0E0(var_4);
    }
    check();
    var_4 = unk_21A0;
    unk_21A0 = var_4->unk_158;
    if (var_4->unk_158)
        var_4->unk_158->unk_154 = 0;
    var_4->unk_154 = 0;
    var_4->unk_158 = 0;
    return var_4;
}
// match: ?sub_1DF080@type_3E3870@@QAEXPAUtype_3E3870_out@@@Z @ 0x001DF080
void type_3E3870::sub_1DF080(type_3E3870_out *arg_0)
{
    check();
    if (unk_21A4)
        unk_21A4->unk_154 = arg_0;
    check();
    check();
    arg_0->unk_154 = 0;
    arg_0->unk_158 = unk_21A4;
    unk_21A4 = arg_0;
}
// match: ?sub_1DF0E0@type_3E3870@@QAEXPAUtype_3E3870_out@@@Z @ 0x001DF0E0
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void type_3E3870::sub_1DF0E0(type_3E3870_out *arg_0)
{
    type_3E3870_out *l4 = 0;
    type_3E3870_out *var_8;

    check();
    var_8 = unk_21A4;
    while (var_8 && var_8 != arg_0)
    {
        l4 = var_8;
        var_8 = var_8->unk_158;
    }
    if (var_8)
    {
        if (!l4)
        {
            unk_21A4 = arg_0->unk_158;
            if (unk_21A4)
                unk_21A4->unk_154 = 0;
        }
        else
        {
            l4->unk_158 = arg_0->unk_158;
            if (l4->unk_158)
                l4->unk_158->unk_154 = l4;
        }
        var_8->unk_154 = 0;
        var_8->unk_158 = unk_21A0;
        if (unk_21A0)
            unk_21A0->unk_154 = var_8;
        unk_21A0 = var_8;
    }
}
// match: ?sub_1DF1E0@type_3E3870@@QAEXPAUtype_1DDE20_mask@@0H@Z @ 0x001DF1E0
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void type_3E3870::sub_1DF1E0(type_1DDE20_mask *arg_0, type_1DDE20_mask *arg_4, RwInt32 arg_8)
{
    RwUInt8 var_9;
    RwUInt8 var_A;
    type_4F8054_B0 *bp_8;
    RwUInt8 var_1;

    bp_8 = unk_04->get_unk_04()->unk_B0;
    var_A = (RwUInt8)bp_8->sub_1CFF90();
    for (var_1 = 0; var_1 < 16; var_1++)
    {
        if (var_1 != arg_8 && (check(), arg_0->test(var_1)))
        {
            var_9 = sub_1DF5E0(var_A, var_1);
            if (var_9 == var_1)
            {
                arg_0->drop(var_1);
                check();
                arg_4->include(var_1);
            }
        }
    }
}
// match: ?sub_1DF2A0@type_3E3870@@QAEXPAUtype_3E3870_out@@H@Z @ 0x001DF2A0
void type_3E3870::sub_1DF2A0(type_3E3870_out *arg_0, RwInt32 arg_4)
{
    RwUInt32 w170[0x56];
    type_1F8560 var_18((RwUInt8 *)w170, 0xAC0);
    type_1DDE20_mask var_8;
    type_1DDE20_mask var_C;
    RwUInt32 var_4;

    check();
    var_18.sub_1F8860(arg_0->unk_100, 8);
    check();
    var_8.merge(arg_0->unk_104);
    check();
    var_C.merge(arg_0->unk_102);
    sub_1DF1E0(&var_8, &var_C, arg_4);
    var_18.sub_1F8860(var_8.unk_00, 16);
    var_18.sub_1F8860(var_C.unk_00, 16);
    var_18.sub_1F88A0(arg_0->unk_148);
    for (var_4 = 0; var_4 < 16; var_4++)
    {
        if (var_8.test(var_4))
        {
            check();
            var_18.sub_1F88A0(arg_0->unk_148 - arg_0->unk_108[var_4]);
        }
    }
    var_18.sub_1F89D0(arg_0, arg_0->unk_14C * 8);
    unk_04->sub_1DDC50(&var_18, var_18.get_unk_08(), type_1DDE20_mask((RwUInt16)(1 << arg_4)));
    unk_264C[unk_2661] = arg_0->unk_100;
    unk_2656[unk_2661] = (RwUInt8)arg_4;
    unk_2661++;
    unk_2661 = unk_2661 < 10 ? unk_2661 : 0;
}
extern RwInt32 dword_503304;
// match: ?sub_1DF4A0@type_3E3870@@QAEXABUtype_1CCA10@@@Z @ 0x001DF4A0
void type_3E3870::sub_1DF4A0(const type_1CCA10 &arg_0)
{
    RwUInt32 var_8;
    type_1CCA10 var_4;

    for (var_8 = 0; var_8 < 16; var_8++)
    {
        if (unk_1A54[var_8])
        {
            var_4 = arg_0 - unk_1A54[var_8]->unk_10C.ref_unk_00();
            if (unk_1A54[var_8]->unk_100 == (RwUInt32)-1 || unk_1A54[var_8]->unk_100 == unk_1A94[var_8] ||
                var_4 > dword_503304)
            {
                if (var_4 > dword_503304)
                    unk_2664++;
                sub_1DED60(var_8, 0);
            }
        }
    }
}
extern RwUInt8 *unk_42CE38[18];
// match: ?sub_1DF5A0@type_3E3870@@QAEEEEE@Z @ 0x001DF5A0
RwUInt8 type_3E3870::sub_1DF5A0(RwUInt8 arg_0, RwUInt8 arg_4, RwUInt8 arg_8)
{
    check();
    check();
    RwUInt8 var_1 = unk_42CE38[arg_0][arg_4 * arg_0 + arg_8];

    return var_1;
}
// match: ?sub_1DF5E0@type_3E3870@@QAEEEE@Z @ 0x001DF5E0
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
RwUInt8 type_3E3870::sub_1DF5E0(RwUInt8 arg_0, RwUInt8 arg_4)
{
    RwUInt8 var_1;
    RwUInt8 var_18[16];
    RwUInt8 var_2;

    {
        RwUInt8 var_19;
        type_4F8054_B0 *y20;
        type_1DDE20_mask var_24;
        RwUInt8 var_25;
        RwUInt8 v38[16];

        check();
        check();
        y20 = unk_04->get_unk_04()->unk_B0;
        var_24 = y20->get_unk_0C();
        var_19 = (RwUInt8)var_24.sub_1D4A60();
        check();
        memset(v38, 16, sizeof(v38));
        var_25 = 0;
        for (var_2 = 0; var_2 < 16; var_2++)
        {
            check();
            check();
            if (var_24.test(var_2))
            {
                var_18[var_2] = var_25;
                check();
                v38[var_25] = var_2;
                var_25++;
            }
            else
                var_18[var_2] = 16;
        }
        check();
        check();
        var_1 = sub_1DF5A0(var_19, var_18[arg_0], var_18[arg_4]);
        check();
        check();
        return v38[var_1];
    }
}
// match: ?sub_1DF6D0@type_3E3870@@QAEXABUtype_1CCA10@@PAUtype_3E3870_out@@E@Z @ 0x001DF6D0
void type_3E3870::sub_1DF6D0(const type_1CCA10 &arg_0, type_3E3870_out *arg_4, RwUInt8 arg_8)
{
    check();
    sub_1DF2A0(arg_4, arg_8);
    arg_4->unk_104.drop(arg_8);
    if (arg_4->unk_104.empty())
        sub_1DF0E0(arg_4);
}
// match: ?sub_1DF740@type_3E3870@@QAEXABUtype_1CCA10@@PAUtype_1DDE20_mask@@PAH@Z @ 0x001DF740
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void type_3E3870::sub_1DF740(const type_1CCA10 &arg_0, type_1DDE20_mask *arg_4, RwInt32 *arg_8)
{
    RwUInt8 var_9;
    type_3E3870_out *frm_8;
    type_3E3870_out *l4;

    if (unk_21A4)
    {
        l4 = unk_21A4;
        while (l4)
        {
            frm_8 = l4->unk_158;
            var_9 = (RwUInt8)l4->unk_104.sub_1D4900();
            sub_1DF6D0(arg_0, l4, var_9);
            check();
            arg_4->include(var_9);
            (*arg_8)--;
            l4 = frm_8;
        }
    }
}
// match: ?sub_1DF7D0@type_3E3870@@QAEXABUtype_1CCA10@@@Z @ 0x001DF7D0
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void type_3E3870::sub_1DF7D0(const type_1CCA10 &arg_0)
{
    type_1CCA10 var_4;
    RwInt32 var_14 = 4;
    type_1DDE20_mask var_10;
    type_3E3870_out *var_8;
    type_3E3870_out *var_C;

    if (unk_21A4)
    {
        var_C = unk_21A4;
        while (var_C)
        {
            var_8 = var_C->unk_158;
            var_4 = arg_0 - var_C->unk_150;
            if (var_4 > 1000)
                sub_1DF0E0(var_C);
            var_C = var_8;
        }
    }
    var_4 = arg_0 - unk_21EC;
    if (var_4 > 100)
    {
        sub_1DF740(arg_0, &var_10, &var_14);
        if (unk_21EC == type_1CCA10(0))
            unk_21EC = arg_0;
        else if (var_14 == 4)
            unk_21EC = arg_0 - 100;
        else
            unk_21EC = unk_21EC + 100;
    }
}
// match: ?sub_1DF940@type_3E3870@@QAEXABUtype_1CCA10@@@Z @ 0x001DF940
void type_3E3870::sub_1DF940(const type_1CCA10 &arg_0)
{
    sub_1DF4A0(arg_0);
    sub_1DF7D0(arg_0);
}
// match: ?sub_1DF970@type_3E3870@@QAEXABUtype_1CCA10@@@Z @ 0x001DF970
void type_3E3870::sub_1DF970(const type_1CCA10 &arg_0)
{
    sub_1DF940(arg_0);
}
// match: ?sub_1DF990@type_3E3870@@QAEXPAUtype_1DF990@@ABUtype_1CCA10@@@Z @ 0x001DF990
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void type_3E3870::sub_1DF990(type_1DF990 *arg_0, const type_1CCA10 &arg_4)
{
    type_3E3870_in *var_10;
    type_3E3870_out *var_C;
    RwUInt32 bp_8;
    RwUInt32 bp_4;

    check();
    memset(arg_0, 0, sizeof(*arg_0));
    for (bp_4 = 0; bp_4 < 16; bp_4++)
    {
        check();
        if (unk_21A8.test(bp_4))
        {
            arg_0->unk_58[bp_4] = 1;
            arg_0->unk_98[bp_4] = arg_4.since(unk_21AC[bp_4]);
        }
        else
        {
            arg_0->unk_58[bp_4] = 0;
            arg_0->unk_98[bp_4] = type_1CCA10::zero();
        }
        bp_8 = 0;
        var_10 = unk_1A54[bp_4];
        while (var_10)
        {
            bp_8++;
            var_10 = var_10->unk_114;
        }
        arg_0->unk_00[bp_4] = bp_8;
    }
    bp_8 = 0;
    var_C = unk_21A4;
    while (var_C)
    {
        arg_0->unk_44[bp_8] = var_C->unk_100;
        bp_8++;
        var_C = var_C->unk_158;
    }
    arg_0->unk_40 = bp_8;
    arg_0->unk_D8 = arg_4.since(unk_21EC);
    memcpy(arg_0->unk_F0, unk_264C, sizeof(arg_0->unk_F0));
    memcpy(arg_0->unk_FA, unk_2656, sizeof(arg_0->unk_FA));
    memcpy(arg_0->unk_DC, unk_2638, sizeof(arg_0->unk_DC));
    memcpy(arg_0->unk_E6, unk_2642, sizeof(arg_0->unk_E6));
    arg_0->unk_105 = unk_2661;
    arg_0->unk_104 = unk_2660;
    arg_0->unk_108 = unk_2664;
}
