/*
 * \COD\SHARED\network\knet\sNetGameEP.cpp: the network game's own messages
 * (the join, the players' details, kicks, pings and the rest), each
 * written to a bit stream and sent (game/netmsg.h's type_1F8560), read back
 * and checked. The path is the image's own (the dead "broken packet"
 * prints pass it as __FILE__); its __LINE__ values pin the checks.
 */
#include <string.h>

#include "game/systemlink.h"
#include "types/cXboxLive.h"
#include "rw/ostypes.h"
#include "game/netmsg.h"
#include "types/type_DC400.h"
#include "game/functions.h"

// The network debug print (a pointer the retail build calls only in
// compiled-out code).
extern void (*off_42CD14)(const RwChar *arg_0, ...);

// A compiled-out assertion: no code, but the registers after it move on by
// the loads its condition would make (docs/toolchain.md). The conditions are
// not known; they are chosen for their loads.
#define SNET_ASSERT(e) { if (!(e)) { } }

// A message's check: on failure the (compiled-out) "broken packet" print
// and a return of 0.
#define SNET_CHECK(e) if (!(e)) { if (0) { off_42CD14("sNetGameEP:: broken packet %s:%d\n", __FILE__, __LINE__); } return 0; }

// Its data (PLAN M5): literals, constants and tables where the image has them.
// match: ??_C@_0CC@BDBOLACK@sNetGameEP?3?3?5broken?5packet?5?$CFs?3?$CFd@ @ 0x003E5194
// match: ??_C@_0CI@NFJAHPBD@?2COD?2SHARED?2network?2knet?2sNetGam@ @ 0x003E51B8
// match: ??_C@_0EM@CAFEKGIF@?6recieving?5encrypted?5channels?5wh@ @ 0x003E51E0
// match: ??_C@_0DN@NPNLPEAC@convertInternetAddressToXboxAddr@ @ 0x003E522C
// match: ??_C@_0DI@DHEGKGAM@convertXboxAddressToInternetAddr@ @ 0x003E526C

// match: ?sub_1D5DC0@type_1D5DC0@@QAEHPAUtype_4F8054@@ABUtype_1DDE20_mask@@PAH@Z @ 0x001D5DC0

RwInt32 type_1D5DC0::sub_1D5DC0(type_4F8054 *arg_0, const type_1DDE20_mask &arg_4, RwInt32 *arg_8)
{
#line 192 "\\COD\\SHARED\\network\\knet\\sNetGameEP.cpp"
    SNET_CHECK(sub_1D5F20(arg_0, arg_0->get_unk_B0()->sub_1CFF90(), arg_4));
    SNET_ASSERT(unk_00);
    type_1F8560_buf<12, 103> var_1C;
    var_1C.sub_1F8B90(1, 0, 15);
    var_1C.sub_1F8B90(unk_00, 0, 16);
    RwInt32 var_4 = var_1C.unk_08;
    var_1C.unk_08 = 0;
    *arg_8 = arg_0->sub_1CC5F0(arg_4, &var_1C, var_4);
    return 1;
}

// match: ?sub_1D5E80@type_1D5DC0@@QAEHPAUtype_1F8560@@H@Z @ 0x001D5E80
RwInt32 type_1D5DC0::sub_1D5E80(type_1F8560 *arg_0, RwInt32 arg_4)
{
    RwUInt32 a = arg_0->unk_08;
    SNET_ASSERT(unk_00);
    SNET_ASSERT(unk_00);
    RwInt32 kind = arg_0->sub_1F8B30(0, 15);

#line 229 "\\COD\\SHARED\\network\\knet\\sNetGameEP.cpp"
    SNET_CHECK(kind == 1);
    unk_00 = (RwUInt8)arg_0->sub_1F8B30(0, 16);
    SNET_ASSERT(unk_00);
    SNET_ASSERT(unk_00);
#line 235 "\\COD\\SHARED\\network\\knet\\sNetGameEP.cpp"
    SNET_CHECK(arg_0->get_unk_08() - a == arg_4);
    return 1;
}

// match: ?sub_1D5F20@type_1D5DC0@@QAEHPAUtype_4F8054@@HABUtype_1DDE20_mask@@@Z @ 0x001D5F20
RwInt32 type_1D5DC0::sub_1D5F20(type_4F8054 *arg_0, RwInt32 arg_4, const type_1DDE20_mask &arg_8)
{
    arg_0 = arg_0;
#line 254 "\\COD\\SHARED\\network\\knet\\sNetGameEP.cpp"
    SNET_CHECK(arg_4 == arg_0->get_unk_B0()->host());
#line 258 "\\COD\\SHARED\\network\\knet\\sNetGameEP.cpp"
    SNET_CHECK(!arg_8.empty() && !arg_8.test(arg_4) && arg_8.single());
#line 262 "\\COD\\SHARED\\network\\knet\\sNetGameEP.cpp"
    SNET_CHECK(unk_00 < 16);
    return 1;
}

// match: ?sub_1D6020@type_1D6020@@QAEHPAUtype_4F8054@@ABUtype_1DDE20_mask@@PAH@Z @ 0x001D6020
RwInt32 type_1D6020::sub_1D6020(type_4F8054 *arg_0, const type_1DDE20_mask &arg_4, RwInt32 *arg_8)
{
#line 281 "\\COD\\SHARED\\network\\knet\\sNetGameEP.cpp"
    SNET_CHECK(sub_1D6160(arg_0, arg_0->get_unk_B0()->sub_1CFF90(), arg_4));
    SNET_ASSERT(unk_00);
    type_1F8560_buf<12, 103> var_1C;
    var_1C.sub_1F8B90(14, 0, 15);
    RwInt32 var_4 = var_1C.unk_08;
    var_1C.unk_08 = 0;
    *arg_8 = arg_0->sub_1CC5F0(arg_4, &var_1C, var_4);
    return 1;
}

// match: ?sub_1D60D0@type_1D6020@@QAEHPAUtype_1F8560@@H@Z @ 0x001D60D0
RwInt32 type_1D6020::sub_1D60D0(type_1F8560 *arg_0, RwInt32 arg_4)
{
    RwUInt32 a = arg_0->unk_08;
    SNET_ASSERT(unk_00);
    SNET_ASSERT(unk_00);
    RwInt32 kind = arg_0->sub_1F8B30(0, 15);

#line 317 "\\COD\\SHARED\\network\\knet\\sNetGameEP.cpp"
    SNET_CHECK(kind == 14);
    SNET_ASSERT(unk_00);
    SNET_ASSERT(unk_00);
#line 321 "\\COD\\SHARED\\network\\knet\\sNetGameEP.cpp"
    SNET_CHECK(arg_0->get_unk_08() - a == arg_4);
    return 1;
}

// match: ?sub_1D6160@type_1D6020@@QAEHPAUtype_4F8054@@HABUtype_1DDE20_mask@@@Z @ 0x001D6160
RwInt32 type_1D6020::sub_1D6160(type_4F8054 *arg_0, RwInt32 arg_4, const type_1DDE20_mask &arg_8)
{
    arg_0 = arg_0;
#line 340 "\\COD\\SHARED\\network\\knet\\sNetGameEP.cpp"
    SNET_CHECK(arg_4 == arg_0->get_unk_B0()->host());
#line 344 "\\COD\\SHARED\\network\\knet\\sNetGameEP.cpp"
    SNET_CHECK(!arg_8.empty() && !arg_8.test(arg_4) && arg_8.single());
    return 1;
}

// match: ?sub_1D6230@type_1D6230@@QAEHPAUtype_4F8054@@ABUtype_1DDE20_mask@@PAH@Z @ 0x001D6230
RwInt32 type_1D6230::sub_1D6230(type_4F8054 *arg_0, const type_1DDE20_mask &arg_4, RwInt32 *arg_8)
{
#line 363 "\\COD\\SHARED\\network\\knet\\sNetGameEP.cpp"
    SNET_CHECK(sub_1D6370(arg_0, arg_0->get_unk_B0()->sub_1CFF90(), arg_4));
    SNET_ASSERT(unk_00[0]);
    type_1F8560_buf<40, 351> var_34;
    var_34.sub_1F8B90(2, 0, 15);
    var_34.sub_1F89D0(this, 0xE0);
    RwInt32 var_38 = var_34.unk_08;
    var_34.unk_08 = 0;
    *arg_8 = arg_0->sub_1CC5F0(arg_4, &var_34, var_38);
    return 1;
}

// match: ?sub_1D62F0@type_1D6230@@QAEHPAUtype_1F8560@@H@Z @ 0x001D62F0
RwInt32 type_1D6230::sub_1D62F0(type_1F8560 *arg_0, RwInt32 arg_4)
{
    RwUInt32 a = arg_0->unk_08;
    RwInt32 kind = arg_0->sub_1F8B30(0, 15);

    a = arg_0->get_unk_08() - a;
    SNET_ASSERT(kind & 1);
#line 396 "\\COD\\SHARED\\network\\knet\\sNetGameEP.cpp"
    SNET_CHECK(kind == 2);
    arg_0->sub_1F8A40((RwChar *)this, arg_4 - a);
    return 1;
}

// match: ?sub_1D6370@type_1D6230@@QAEHPAUtype_4F8054@@HABUtype_1DDE20_mask@@@Z @ 0x001D6370
RwInt32 type_1D6230::sub_1D6370(type_4F8054 *arg_0, RwInt32 arg_4, const type_1DDE20_mask &arg_8)
{
    arg_0 = arg_0;
#line 417 "\\COD\\SHARED\\network\\knet\\sNetGameEP.cpp"
    SNET_CHECK(arg_4 != arg_0->get_unk_B0()->host());
#line 421 "\\COD\\SHARED\\network\\knet\\sNetGameEP.cpp"
    SNET_CHECK(!arg_8.empty() && !arg_8.test(arg_4) && arg_8.single());
#line 425 "\\COD\\SHARED\\network\\knet\\sNetGameEP.cpp"
    SNET_CHECK(strlen(unk_00) < 0x18);
    return 1;
}

// match: ?sub_1D6480@type_1D6480@@QAEHPAUtype_4F8054@@ABUtype_1DDE20_mask@@PAH@Z @ 0x001D6480
RwInt32 type_1D6480::sub_1D6480(type_4F8054 *arg_0, const type_1DDE20_mask &arg_4, RwInt32 *arg_8)
{
#line 444 "\\COD\\SHARED\\network\\knet\\sNetGameEP.cpp"
    SNET_CHECK(sub_1D65C0(arg_0, arg_0->get_unk_B0()->sub_1CFF90(), arg_4));
    SNET_ASSERT(unk_00);
    type_1F8560_buf<20, 191> var_20;
    var_20.sub_1F8B90(13, 0, 15);
    var_20.sub_1F8B90(unk_00, 0, 16);
    var_20.sub_1F8520(unk_04);
    RwInt32 var_24 = var_20.unk_08;
    var_20.unk_08 = 0;
    *arg_8 = arg_0->sub_1CC5F0(arg_4, &var_20, var_24);
    return 1;
}

// match: ?sub_1D6550@type_1D6480@@QAEHPAUtype_1F8560@@H@Z @ 0x001D6550
RwInt32 type_1D6480::sub_1D6550(type_1F8560 *arg_0, RwInt32 arg_4)
{
    SNET_ASSERT(unk_00);
    SNET_ASSERT(unk_00);
    RwInt32 var_4 = arg_0->sub_1F8B30(0, 15);

#line 476 "\\COD\\SHARED\\network\\knet\\sNetGameEP.cpp"
    SNET_CHECK(var_4 == 13);
    unk_00 = (RwUInt8)arg_0->sub_1F8B30(0, 16);
    unk_04 = arg_0->sub_1F8560();
    return 1;
}

// match: ?sub_1D65C0@type_1D6480@@QAEHPAUtype_4F8054@@HABUtype_1DDE20_mask@@@Z @ 0x001D65C0
RwInt32 type_1D6480::sub_1D65C0(type_4F8054 *arg_0, RwInt32 arg_4, const type_1DDE20_mask &arg_8)
{
    arg_0 = arg_0;
#line 498 "\\COD\\SHARED\\network\\knet\\sNetGameEP.cpp"
    SNET_CHECK(arg_4 != arg_0->get_unk_B0()->host());
#line 502 "\\COD\\SHARED\\network\\knet\\sNetGameEP.cpp"
    SNET_CHECK(!arg_8.empty() && !arg_8.test(arg_4) && arg_8.single());
#line 506 "\\COD\\SHARED\\network\\knet\\sNetGameEP.cpp"
    SNET_CHECK(arg_4 != unk_00);
    SNET_ASSERT(unk_00);
    SNET_ASSERT(unk_00);
#line 510 "\\COD\\SHARED\\network\\knet\\sNetGameEP.cpp"
    SNET_CHECK(!arg_8.test(unk_00));
    return 1;
}

// match: ?sub_1D6700@type_1D6700@@QAEHPAUtype_4F8054@@ABUtype_1DDE20_mask@@PAH@Z @ 0x001D6700
RwInt32 type_1D6700::sub_1D6700(type_4F8054 *arg_0, const type_1DDE20_mask &arg_4, RwInt32 *arg_8)
{
    XNADDR var_598;
    RwUInt32 l4;
    RwUInt32 a;

#line 533 "\\COD\\SHARED\\network\\knet\\sNetGameEP.cpp"
    SNET_CHECK(sub_1D6B20(arg_0, arg_0->get_unk_B0()->sub_1CFF90(), arg_4));
    SNET_ASSERT(unk_00);
    SNET_ASSERT(unk_00);
    type_1F8560_buf<1372, 11007> var_570;
    var_570.sub_1F8B90(3, 0, 15);
    var_570.sub_1F8B90(unk_00, 0, 16);
    var_570.sub_1F8520(0);
    for (l4 = 0; l4 < unk_00; l4++)
    {
        a = strlen(unk_04[l4].unk_00);
        var_570.sub_1F8B90(unk_244[l4], 0, 16);
        var_570.sub_1F8B90(a, 0, 24);
        var_570.sub_1F89D0(unk_04[l4].unk_00, a * 8);
        var_570.sub_1F8860(unk_04[l4].unk_20, 16);
        sub_1D8810()->sub_1DA0C0(unk_04[l4].unk_18, &var_598);
        var_570.sub_1F89D0(&var_598, 0x120);
        var_570.sub_1F8860(unk_04[l4].unk_1C, 32);
    }
    a = var_570.unk_08;
    var_570.unk_08 = 0;
    *arg_8 = arg_0->sub_1CC5F0(arg_4, &var_570, a);
    return 1;
}

// match: ?sub_1D6920@type_1D6700@@QAEHPAUtype_1F8560@@H@Z @ 0x001D6920
RwInt32 type_1D6700::sub_1D6920(type_1F8560 *arg_0, RwInt32 arg_4)
{
    RwUInt32 i;
    RwUInt32 start = arg_0->unk_08;
    RwInt32 kind = arg_0->sub_1F8B30(0, 15);

#line 608 "\\COD\\SHARED\\network\\knet\\sNetGameEP.cpp"
    SNET_CHECK(kind == 3);
    unk_00 = arg_0->sub_1F8B30(0, 16);
#line 614 "\\COD\\SHARED\\network\\knet\\sNetGameEP.cpp"
    SNET_CHECK((RwUInt32)unk_00 < 16);
    RwUInt32 enc = arg_0->sub_1F8560();
    for (i = 0; i < unk_00; i++)
    {
        RwUInt32 idx;
        RwUInt32 len;
        XNADDR var_38;
        idx = arg_0->sub_1F8B30(0, 16);
        len = arg_0->sub_1F8B30(0, 24);
#line 624 "\\COD\\SHARED\\network\\knet\\sNetGameEP.cpp"
        SNET_CHECK(len <= 0x18 && idx < 0x10);
        unk_244[i] = (RwUInt8)idx;
        unk_04[i].unk_00[len] = 0;
        arg_0->sub_1F8A40(unk_04[i].unk_00, len * 8);
        unk_04[i].unk_20 = (RwUInt16)arg_0->sub_1F8810(16);
        arg_0->sub_1F8A40((RwChar *)&var_38, 0x120);
        sub_1D8810()->sub_1DA110(&var_38, unk_04[i].unk_18);
        unk_04[i].unk_1C = arg_0->sub_1F8810(32);
        SNET_ASSERT(unk_00);
        if (enc)
            sub_19A750("\nrecieving encrypted channels when this build does not support encryption!\n");
    }
#line 662 "\\COD\\SHARED\\network\\knet\\sNetGameEP.cpp"
    SNET_CHECK(arg_0->get_unk_08() - start == arg_4);
    return 1;
}

// match: ?sub_1D6B20@type_1D6700@@QAEHPAUtype_4F8054@@HABUtype_1DDE20_mask@@@Z @ 0x001D6B20
RwInt32 type_1D6700::sub_1D6B20(type_4F8054 *arg_0, RwInt32 arg_4, const type_1DDE20_mask &arg_8)
{
    RwUInt32 var_4;

    arg_0 = arg_0;
#line 682 "\\COD\\SHARED\\network\\knet\\sNetGameEP.cpp"
    SNET_CHECK(arg_4 == arg_0->get_unk_B0()->host());
#line 686 "\\COD\\SHARED\\network\\knet\\sNetGameEP.cpp"
    SNET_CHECK(!arg_8.empty() && !arg_8.test(arg_4));
    if ((RwUInt32)unk_00 > 16)
        return 1;
    for (var_4 = 0; var_4 < unk_00; var_4++)
    {
#line 694 "\\COD\\SHARED\\network\\knet\\sNetGameEP.cpp"
        SNET_CHECK(unk_244[var_4] <= 16);
#line 696 "\\COD\\SHARED\\network\\knet\\sNetGameEP.cpp"
        SNET_CHECK(strlen(unk_04[var_4].unk_00) <= 0x18);
    }
    return 1;
}

// match: ?sub_1D6C60@type_1D6C60@@QAEHPAUtype_4F8054@@ABUtype_1DDE20_mask@@PAH@Z @ 0x001D6C60
RwInt32 type_1D6C60::sub_1D6C60(type_4F8054 *arg_0, const type_1DDE20_mask &arg_4, RwInt32 *arg_8)
{
#line 716 "\\COD\\SHARED\\network\\knet\\sNetGameEP.cpp"
    SNET_CHECK(sub_1D6DA0(arg_0, arg_0->get_unk_B0()->sub_1CFF90(), arg_4));
    SNET_ASSERT(unk_00[0]);
    type_1F8560_buf<36, 319> a;
    a.sub_1F8B90(4, 0, 15);
    a.sub_1F89D0(this, 0xC0);
    RwInt32 b = a.unk_08;
    a.unk_08 = 0;
    *arg_8 = arg_0->sub_1CC5F0(arg_4, &a, b);
    return 1;
}

// match: ?sub_1D6D20@type_1D6C60@@QAEHPAUtype_1F8560@@H@Z @ 0x001D6D20
RwInt32 type_1D6C60::sub_1D6D20(type_1F8560 *arg_0, RwInt32 arg_4)
{
    RwUInt32 a = arg_0->unk_08;
    RwInt32 kind = arg_0->sub_1F8B30(0, 15);

    a = arg_0->get_unk_08() - a;
    SNET_ASSERT(kind & 1);
#line 749 "\\COD\\SHARED\\network\\knet\\sNetGameEP.cpp"
    SNET_CHECK(kind == 4);
    arg_0->sub_1F8A40(unk_00, arg_4 - a);
    return 1;
}

// match: ?sub_1D6DA0@type_1D6C60@@QAEHPAUtype_4F8054@@HABUtype_1DDE20_mask@@@Z @ 0x001D6DA0
RwInt32 type_1D6C60::sub_1D6DA0(type_4F8054 *arg_0, RwInt32 arg_4, const type_1DDE20_mask &arg_8)
{
    arg_0 = arg_0;
#line 770 "\\COD\\SHARED\\network\\knet\\sNetGameEP.cpp"
    SNET_CHECK(arg_4 == arg_0->get_unk_B0()->host());
#line 774 "\\COD\\SHARED\\network\\knet\\sNetGameEP.cpp"
    SNET_CHECK(!arg_8.empty() && !arg_8.test(arg_4) && arg_8.single());
#line 778 "\\COD\\SHARED\\network\\knet\\sNetGameEP.cpp"
    SNET_CHECK(strlen(unk_00) <= 0x18);
    return 1;
}

// match: ?sub_1D6EB0@type_1D6EB0@@QAEHPAUtype_4F8054@@ABUtype_1DDE20_mask@@PAH@Z @ 0x001D6EB0
RwInt32 type_1D6EB0::sub_1D6EB0(type_4F8054 *arg_0, const type_1DDE20_mask &arg_4, RwInt32 *arg_8)
{
    XNADDR var_9C;

#line 801 "\\COD\\SHARED\\network\\knet\\sNetGameEP.cpp"
    SNET_CHECK(sub_1D7120(arg_0, arg_0->get_unk_B0()->sub_1CFF90(), arg_4));
    SNET_ASSERT(unk_00);
    type_1F8560_buf<100, 799> a;
    a.sub_1F8B90(5, 0, 15);
    a.sub_1F8520(0);
    a.sub_1F8B90(unk_00, 0, 16);
    sub_1D8810()->sub_1DA0C0(unk_25, &var_9C);
    a.sub_1F89D0(&var_9C, 0x120);
    a.sub_1F8860(unk_2A, 16);
    a.sub_1F89D0(unk_01, 0xC0);
    a.sub_1F8860(unk_2C, 32);
    RwInt32 n = a.unk_08;
    a.unk_08 = 0;
    *arg_8 = arg_0->sub_1CC5F0(arg_4, &a, n);
    return 1;
}

// match: ?sub_1D7010@type_1D6EB0@@QAEHPAUtype_1F8560@@H@Z @ 0x001D7010
RwInt32 type_1D6EB0::sub_1D7010(type_1F8560 *arg_0, RwInt32 arg_4)
{
    XNADDR var_34;
    RwUInt32 l4 = arg_0->unk_08;
    RwInt32 p = arg_0->sub_1F8B30(0, 15);

    l4 = arg_0->get_unk_08() - l4;
    SNET_ASSERT(unk_00);
    SNET_ASSERT(unk_00);
#line 863 "\\COD\\SHARED\\network\\knet\\sNetGameEP.cpp"
    SNET_CHECK(p == 5);
    RwUInt32 a = arg_0->sub_1F8560();
    unk_00 = (RwUInt8)arg_0->sub_1F8B30(0, 16);
    arg_0->sub_1F8A40((RwChar *)&var_34, 0x120);
    sub_1D8810()->sub_1DA110(&var_34, unk_25);
    unk_2A = (RwUInt16)arg_0->sub_1F8810(16);
    arg_0->sub_1F8A40(unk_01, 0xC0);
    unk_2C = arg_0->sub_1F8810(32);
    if (a)
        sub_19A750("\nrecieving encrypted channels when this build does not support encryption!\n");
    return 1;
}

// match: ?sub_1D7120@type_1D6EB0@@QAEHPAUtype_4F8054@@HABUtype_1DDE20_mask@@@Z @ 0x001D7120
RwInt32 type_1D6EB0::sub_1D7120(type_4F8054 *arg_0, RwInt32 arg_4, const type_1DDE20_mask &arg_8)
{
    arg_0 = arg_0;
#line 910 "\\COD\\SHARED\\network\\knet\\sNetGameEP.cpp"
    SNET_CHECK(arg_4 == arg_0->get_unk_B0()->host());
#line 914 "\\COD\\SHARED\\network\\knet\\sNetGameEP.cpp"
    SNET_CHECK(!arg_8.empty() && !arg_8.test(arg_4));
#line 918 "\\COD\\SHARED\\network\\knet\\sNetGameEP.cpp"
    SNET_CHECK(unk_00 <= 16 && strlen(unk_01) <= 0x18);
    return 1;
}

// match: ?sub_1D7200@type_1D7200@@QAEHPAUtype_4F8054@@ABUtype_1DDE20_mask@@PAH@Z @ 0x001D7200
RwInt32 type_1D7200::sub_1D7200(type_4F8054 *arg_0, const type_1DDE20_mask &arg_4, RwInt32 *arg_8)
{
    XNADDR var_84;

#line 941 "\\COD\\SHARED\\network\\knet\\sNetGameEP.cpp"
    SNET_CHECK(sub_1D7420(arg_0, arg_0->get_unk_B0()->sub_1CFF90(), arg_4));
    SNET_ASSERT(unk_00);
    type_1F8560_buf<76, 615> a;
    a.sub_1F8B90(6, 0, 15);
    a.sub_1F8B90(unk_00, 0, 16);
    a.sub_1F89D0(unk_01, 0xC0);
    if (!sub_1D8810()->sub_1DA0C0(unk_19, &var_84))
    {
        if (CODFH_DEBUG_LOGS)
        {
            off_42CD14("convertInternetAddressToXboxAddress() failed in packAndSend\n");
        }
        return 0;
    }
    a.sub_1F89D0(&var_84, 0x120);
    RwInt32 n = a.unk_08;
    a.unk_08 = 0;
    *arg_8 = arg_0->sub_1CC5F0(arg_4, &a, n);
    return 1;
}

// match: ?sub_1D7340@type_1D7200@@QAEHPAUtype_1F8560@@H@Z @ 0x001D7340
RwInt32 type_1D7200::sub_1D7340(type_1F8560 *arg_0, RwInt32 arg_4)
{
    XNADDR var_30;
    RwUInt32 a = arg_0->unk_08;
    RwInt32 kind = arg_0->sub_1F8B30(0, 15);

    a = arg_0->get_unk_08() - a;
    SNET_ASSERT(unk_00);
    SNET_ASSERT(unk_00);
#line 996 "\\COD\\SHARED\\network\\knet\\sNetGameEP.cpp"
    SNET_CHECK(kind == 6);
    unk_00 = (RwUInt8)arg_0->sub_1F8B30(0, 16);
    arg_0->sub_1F8A40(unk_01, 0xC0);
    arg_0->sub_1F8A40((RwChar *)&var_30, 0x120);
    if (!sub_1D8810()->sub_1DA110(&var_30, unk_19))
    {
        if (CODFH_DEBUG_LOGS)
        {
            off_42CD14("convertXboxAddressToInternetAddress() failed in unpack\n");
        }
        return 0;
    }
    return 1;
}

// match: ?sub_1D7420@type_1D7200@@QAEHPAUtype_4F8054@@HABUtype_1DDE20_mask@@@Z @ 0x001D7420
RwInt32 type_1D7200::sub_1D7420(type_4F8054 *arg_0, RwInt32 arg_4, const type_1DDE20_mask &arg_8)
{
    arg_0 = arg_0;
#line 1028 "\\COD\\SHARED\\network\\knet\\sNetGameEP.cpp"
    SNET_CHECK((RwUInt32)arg_4 <= 16);
#line 1032 "\\COD\\SHARED\\network\\knet\\sNetGameEP.cpp"
    SNET_CHECK(!arg_8.empty() && !arg_8.test(arg_4));
#line 1038 "\\COD\\SHARED\\network\\knet\\sNetGameEP.cpp"
    SNET_CHECK(arg_8.single() || arg_4 == arg_0->get_unk_B0()->host());
#line 1043 "\\COD\\SHARED\\network\\knet\\sNetGameEP.cpp"
    SNET_CHECK(unk_00 <= 16 && strlen(unk_01) <= 0x18);
    return 1;
}

// match: ?sub_1D7560@type_1D7560@@QAEHPAUtype_4F8054@@ABUtype_1DDE20_mask@@PAH@Z @ 0x001D7560
RwInt32 type_1D7560::sub_1D7560(type_4F8054 *arg_0, const type_1DDE20_mask &arg_4, RwInt32 *arg_8)
{
#line 1207 "\\COD\\SHARED\\network\\knet\\sNetGameEP.cpp"
    SNET_CHECK(sub_18F420(arg_0, arg_4));
    SNET_ASSERT(unk_00.unk_00);
    SNET_ASSERT(unk_00.unk_00);
    type_1F8560_buf<20, 191> var_20;
    RwInt32 a = unk_00.ms();
    RwInt32 x = unk_04.ms();
    var_20.sub_1F8B90(7, 0, 15);
    var_20.sub_1F8AB0(a);
    if (x == 0)
    {
        var_20.sub_1F8520(0);
    }
    else
    {
        var_20.sub_1F8520(1);
        var_20.sub_1F8AB0(a - unk_04.ms());
    }
    RwInt32 var_2C = var_20.unk_08;
    var_20.unk_08 = 0;
    *arg_8 = arg_0->sub_1CC5F0(arg_4, &var_20, var_2C);
    return 1;
}

// match: ?sub_1D7650@type_1D7560@@QAEHPAUtype_1F8560@@H@Z @ 0x001D7650
RwInt32 type_1D7560::sub_1D7650(type_1F8560 *arg_0, RwInt32 arg_4)
{
    RwUInt32 var_8 = arg_0->unk_08;
    RwUInt32 var_10 = arg_0->unk_08;
    RwInt32 var_C = arg_0->sub_1F8B30(0, 15);

    var_10 = arg_0->get_unk_08() - var_10;
    SNET_ASSERT(unk_00.unk_00);
#line 1250 "\\COD\\SHARED\\network\\knet\\sNetGameEP.cpp"
    SNET_CHECK(var_C == 7);
    unk_00 = arg_0->sub_1F8AF0();
    if (arg_0->sub_1F8560())
        unk_04 = unk_00.get_unk_00() + arg_0->sub_1F8AF0();
    else
        unk_04 = 0;
    RwInt32 var_4 = arg_0->get_unk_08() - var_8;
    if (var_4 == arg_4)
        return 1;
#line 1264 "\\COD\\SHARED\\network\\knet\\sNetGameEP.cpp"
    if (CODFH_DEBUG_LOGS)
    {
        off_42CD14("sNetGameEP:: broken packet %s:%d\n", __FILE__, __LINE__);
    }
    return 0;
}

// match: ?sub_1D7760@type_1D7760@@QAEHPAUtype_1F8560@@H@Z @ 0x001D7760
RwInt32 type_1D7760::sub_1D7760(type_1F8560 *arg_0, RwInt32 arg_4)
{
    RwUInt32 a = arg_0->unk_08;
    RwInt32 kind = arg_0->sub_1F8B30(0, 15);

    a = arg_0->get_unk_08() - a;
    SNET_ASSERT(unk_00);
    SNET_ASSERT(unk_00);
#line 1328 "\\COD\\SHARED\\network\\knet\\sNetGameEP.cpp"
    SNET_CHECK(kind == 10);
    unk_00 = (RwUInt8)arg_0->sub_1F8B30(0, 16);
    arg_0->sub_1F8A40(unk_01, 0xC0);
    return 1;
}

// match: ?sub_1D77F0@type_1D77F0@@QAEHPAUtype_1F8560@@H@Z @ 0x001D77F0
RwInt32 type_1D77F0::sub_1D77F0(type_1F8560 *arg_0, RwInt32 arg_4)
{
    RwUInt32 a = arg_0->unk_08;
    RwInt32 kind = arg_0->sub_1F8B30(0, 15);

    a = arg_0->get_unk_08() - a;
    SNET_ASSERT(kind & 1);
#line 1395 "\\COD\\SHARED\\network\\knet\\sNetGameEP.cpp"
    SNET_CHECK(kind == 11);
    arg_0->sub_1F8A40(unk_00, 0xC0);
    return 1;
}

// match: ?sub_1D7870@type_1D7870@@QAEHPAUtype_4F8054@@ABUtype_1DDE20_mask@@PAH@Z @ 0x001D7870
RwInt32 type_1D7870::sub_1D7870(type_4F8054 *arg_0, const type_1DDE20_mask &arg_4, RwInt32 *arg_8)
{
#line 1429 "\\COD\\SHARED\\network\\knet\\sNetGameEP.cpp"
    SNET_CHECK(sub_1D79B0(arg_0, arg_0->get_unk_B0()->sub_1CFF90(), arg_4));
    SNET_ASSERT(unk_00);
    type_1F8560_buf<12, 103> var_1C;
    var_1C.sub_1F8B90(12, 0, 15);
    RwInt32 var_4 = var_1C.unk_08;
    var_1C.unk_08 = 0;
    *arg_8 = arg_0->sub_1CC5F0(arg_4, &var_1C, var_4);
    return 1;
}

// match: ?sub_1D7920@type_1D7870@@QAEHPAUtype_1F8560@@H@Z @ 0x001D7920
RwInt32 type_1D7870::sub_1D7920(type_1F8560 *arg_0, RwInt32 arg_4)
{
    RwUInt32 a = arg_0->unk_08;
    SNET_ASSERT(unk_00);
    SNET_ASSERT(unk_00);
    RwInt32 kind = arg_0->sub_1F8B30(0, 15);

#line 1466 "\\COD\\SHARED\\network\\knet\\sNetGameEP.cpp"
    SNET_CHECK(kind == 12);
    SNET_ASSERT(unk_00);
    SNET_ASSERT(unk_00);
#line 1472 "\\COD\\SHARED\\network\\knet\\sNetGameEP.cpp"
    SNET_CHECK(arg_0->get_unk_08() - a == arg_4);
    return 1;
}

// match: ?sub_1D79B0@type_1D7870@@QAEHPAUtype_4F8054@@HABUtype_1DDE20_mask@@@Z @ 0x001D79B0
RwInt32 type_1D7870::sub_1D79B0(type_4F8054 *arg_0, RwInt32 arg_4, const type_1DDE20_mask &arg_8)
{
    arg_0 = arg_0;
#line 1491 "\\COD\\SHARED\\network\\knet\\sNetGameEP.cpp"
    SNET_CHECK(arg_4 == arg_0->get_unk_B0()->host());
    SNET_ASSERT(unk_00);
    SNET_ASSERT(unk_00);
#line 1495 "\\COD\\SHARED\\network\\knet\\sNetGameEP.cpp"
    SNET_CHECK(((type_1DDE20_mask &)arg_8).sub_1D4A60() == 1 && !arg_8.test(arg_4));
    return 1;
}

// Functions /OPT:ICF folded into another body (config/aliases.txt), defined here for the
// authentic link (PLAN M7) with that body; the placement link takes the folded one.

// ?sub_18F420@type_1D7560@@QAEHPAUtype_4F8054@@ABUtype_1DDE20_mask@@@Z (folded into 0x18F420)
RwInt32 type_1D7560::sub_18F420(struct type_4F8054 *arg_0, struct type_1DDE20_mask const & arg_4)
{
    return 1;
}
