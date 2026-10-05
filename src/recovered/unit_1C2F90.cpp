// Network messages' own methods (game/netmsg.h).

#include "game/netmsg.h"

// match: ?vf_000@type_3E0FE4@@UAEXPAUtype_1F8560@@@Z @ 0x001C2F90
void type_3E0FE4::vf_000(type_1F8560 *arg_0)
{
    // A compiled-out check: the registers after it are one load on
    // (docs/toolchain.md).
    if (!unk_04)
    {
    }
    arg_0->sub_1F8B90(unk_04, 0, 3);
    arg_0->sub_1F8860(unk_08, 32);
    arg_0->sub_1F8860(unk_0C, 32);
    arg_0->sub_1F8860(unk_10, 32);
}

// match: ?vf_004@type_3E0FE4@@UAEXPAUtype_1F8560@@@Z @ 0x001C2FF0
void type_3E0FE4::vf_004(type_1F8560 *arg_0)
{
    unk_04 = arg_0->sub_1F8B30(0, 3);
    unk_08 = arg_0->sub_1F8810(32);
    unk_0C = arg_0->sub_1F8810(32);
    unk_10 = arg_0->sub_1F8810(32);
}

// match: ?vf_000@type_3E0FFC@@UAEXPAUtype_1F8560@@@Z @ 0x001C3040
void type_3E0FFC::vf_000(type_1F8560 *arg_0)
{
    arg_0->sub_1F8520(unk_04);
    arg_0->sub_1F8860(unk_08, 32);
}

// match: ?vf_004@type_3E0FFC@@UAEXPAUtype_1F8560@@@Z @ 0x001C3070
void type_3E0FFC::vf_004(type_1F8560 *arg_0)
{
    unk_04 = arg_0->sub_1F8560();
    unk_08 = arg_0->sub_1F8810(32);
}

// match: ?vf_000@type_3E1014@@UAEXPAUtype_1F8560@@@Z @ 0x001C30A0
void type_3E1014::vf_000(type_1F8560 *arg_0)
{
    arg_0->sub_1F8860(unk_04, 8);
    arg_0->sub_1F8860(unk_08, 8);
    arg_0->sub_1F8860(unk_0C, 32);
}

// match: ?vf_004@type_3E1014@@UAEXPAUtype_1F8560@@@Z @ 0x001C30E0
void type_3E1014::vf_004(type_1F8560 *arg_0)
{
    unk_04 = arg_0->sub_1F8810(8);
    unk_08 = arg_0->sub_1F8810(8);
    unk_0C = arg_0->sub_1F8810(32);
}
