// A network message's own methods (game/netmsg.h): the large message
// (type_3E0F9C, its 157 dwords).

#include "game/netmsg.h"

// match: ?vf_000@type_3E0F9C@@UAEXPAUtype_1F8560@@@Z @ 0x001B79E0
void type_3E0F9C::vf_000(type_1F8560 *arg_0)
{
    RwUInt32 var_4;

    arg_0->sub_1F8860(unk_04, 16);
    arg_0->sub_1F8B90(unk_06, 0, 628);
    arg_0->sub_1F8860(unk_08, 16);
    arg_0->sub_1F8B90(unk_0A, 0, 15);
    arg_0->sub_1F8520(unk_0C);
    for (var_4 = 0; var_4 < 0x9D; var_4++)
        arg_0->sub_1F8860(unk_10[var_4], 32);
}

// match: ?vf_004@type_3E0F9C@@UAEXPAUtype_1F8560@@@Z @ 0x001B7A80
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void type_3E0F9C::vf_004(type_1F8560 *arg_0)
{
    RwUInt32 var_8;
    RwUInt32 l4;

    unk_04 = arg_0->sub_1F8810(16);
    unk_06 = arg_0->sub_1F8B30(0, 628);
    unk_08 = arg_0->sub_1F8810(16);
    unk_0A = arg_0->sub_1F8B30(0, 15);
    unk_0C = arg_0->sub_1F8560();
    for (var_8 = 0; var_8 < 0x9D; var_8++)
    {
        l4 = arg_0->sub_1F8810(32);
        unk_10[var_8] = l4;
    }
}
