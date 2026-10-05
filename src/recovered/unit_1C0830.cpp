// Network messages' own methods (game/netmsg.h).

#include "game/netmsg.h"

// match: ?vf_000@type_3E10D4@@UAEXPAUtype_1F8560@@@Z @ 0x001C0830
void type_3E10D4::vf_000(type_1F8560 *arg_0)
{
    arg_0->sub_1F8860(unk_04, 3);
}

// match: ?vf_004@type_3E10D4@@UAEXPAUtype_1F8560@@@Z @ 0x001C0850
void type_3E10D4::vf_004(type_1F8560 *arg_0)
{
    unk_04 = arg_0->sub_1F8810(3);
}

// match: ?vf_000@type_3E10EC@@UAEXPAUtype_1F8560@@@Z @ 0x001C0870
void type_3E10EC::vf_000(type_1F8560 *arg_0)
{
    RwInt32 var_4 = sub_1F84A0(150);

    arg_0->sub_1F8860(unk_04, var_4);
    arg_0->sub_1F8860(unk_08, 3);
}

// match: ?vf_004@type_3E10EC@@UAEXPAUtype_1F8560@@@Z @ 0x001C08C0
void type_3E10EC::vf_004(type_1F8560 *arg_0)
{
    RwInt32 var_4 = sub_1F84A0(150);

    unk_04 = arg_0->sub_1F8810(var_4);
    unk_08 = arg_0->sub_1F8810(3);
}
