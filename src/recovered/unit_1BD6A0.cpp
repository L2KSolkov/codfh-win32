// Network messages' own methods (game/netmsg.h).

#include "game/netmsg.h"

// match: ?vf_000@type_3E1104@@UAEXPAUtype_1F8560@@@Z @ 0x001BD6A0
void type_3E1104::vf_000(type_1F8560 *arg_0)
{
    RwInt32 var_4 = sub_1F84A0(32);

    arg_0->sub_1F8860(unk_04, var_4);
}

// match: ?vf_004@type_3E1104@@UAEXPAUtype_1F8560@@@Z @ 0x001BD6D0
void type_3E1104::vf_004(type_1F8560 *arg_0)
{
    RwInt32 var_4 = sub_1F84A0(32);

    unk_04 = arg_0->sub_1F8810(var_4);
}

// match: ?vf_000@type_3E111C@@UAEXPAUtype_1F8560@@@Z @ 0x001BD700
void type_3E111C::vf_000(type_1F8560 *arg_0)
{
    RwInt32 var_4;

    var_4 = sub_1F84A0(32);
    arg_0->sub_1F8860(unk_04, var_4);
    var_4 = sub_1F84A0(110);
    arg_0->sub_1F8860(unk_08, var_4);
    // A compiled-out check: the registers after it are one load on
    // (docs/toolchain.md).
    if (!unk_0C)
    {
    }
    var_4 = sub_1F84A0(1000000);
    arg_0->sub_1F8860(unk_0C, var_4);
    arg_0->sub_1F85F0(unk_10.unk_00);
    arg_0->sub_1F85F0(unk_10.unk_04);
    arg_0->sub_1F85F0(unk_10.unk_08);
}

// match: ?vf_004@type_3E111C@@UAEXPAUtype_1F8560@@@Z @ 0x001BD7A0
void type_3E111C::vf_004(type_1F8560 *arg_0)
{
    RwInt32 var_4;

    var_4 = sub_1F84A0(32);
    unk_04 = arg_0->sub_1F8810(var_4);
    // A compiled-out check: the registers after it are one load on
    // (docs/toolchain.md).
    if (!unk_04)
    {
    }
    var_4 = sub_1F84A0(110);
    unk_08 = arg_0->sub_1F8810(var_4);
    var_4 = sub_1F84A0(1000000);
    unk_0C = arg_0->sub_1F8810(var_4);
    // A compiled-out check (one load; docs/toolchain.md).
    if (!unk_0C)
    {
    }
    unk_10.unk_00 = arg_0->sub_1F85A0();
    unk_10.unk_04 = arg_0->sub_1F85A0();
    unk_10.unk_08 = arg_0->sub_1F85A0();
}

// match: ?vf_000@type_3E1134@@UAEXPAUtype_1F8560@@@Z @ 0x001BD840
void type_3E1134::vf_000(type_1F8560 *arg_0)
{
    RwInt32 var_4;

    var_4 = sub_1F84A0(32);
    arg_0->sub_1F8860(unk_04, var_4);
    var_4 = sub_1F84A0(110);
    arg_0->sub_1F8860(unk_08, var_4);
    // A compiled-out check: the registers after it are one load on
    // (docs/toolchain.md).
    if (!unk_0C)
    {
    }
    var_4 = sub_1F84A0(1000000);
    arg_0->sub_1F8860(unk_0C, var_4);
}

// match: ?vf_004@type_3E1134@@UAEXPAUtype_1F8560@@@Z @ 0x001BD8C0
void type_3E1134::vf_004(type_1F8560 *arg_0)
{
    RwInt32 var_4;

    var_4 = sub_1F84A0(32);
    unk_04 = arg_0->sub_1F8810(var_4);
    // A compiled-out check: the registers after it are one load on
    // (docs/toolchain.md).
    if (!unk_04)
    {
    }
    var_4 = sub_1F84A0(110);
    unk_08 = arg_0->sub_1F8810(var_4);
    var_4 = sub_1F84A0(1000000);
    unk_0C = arg_0->sub_1F8810(var_4);
}
