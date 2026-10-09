// More network messages' own methods (game/netmsg.h) and the id maps
// between the game's and the network's numbering.

#include "game/netmsg.h"
#include "game/uiglue.h"
#include "game/gameloop.h"
#include "types/type_DC400.h"
#include "types/asynchload.h"

// Its data definitions (PLAN M5), in the image's address order.
#ifndef CODFH_SP // MP only: unreferenced constants single player does not emit (not in default.xbe; /O2 keeps them only while they are external)
// 0x003E37F4
extern const RwReal flt_3E37F4 = 0.01f;
// 0x003E37F8
extern const RwReal flt_3E37F8 = 0.01f;
// 0x003E37FC
extern const RwReal flt_3E37FC = 16.666666f;
#endif
// 0x004FDC08
RwInt32 dword_4FDC08[428];
// 0x004FE2B8
RwInt32 dword_4FE2B8[128];
// 0x004FE4B8
bool byte_4FE4B8;
// 0x004FE688
RwInt32 dword_4FE688[5];
// End of its data definitions.


// Globals with constructors defined here (their initializers and exit
// functions at the end of .text).
// The focus stack the front end installs (sub_1E7CE0); its implicit
// destructor's copy follows the unit's std::string constructor.
kujuUI::type_1E7CF0 unk_4FDBE4;
type_4FE4C0 dword_4FE4C0[0x26] = {
    type_4FE4C0(0, 26, 16),
    type_4FE4C0(1, 2, 17),
    type_4FE4C0(2, 7, 7),
    type_4FE4C0(3, 8, 10),
    type_4FE4C0(4, 6, 8),
    type_4FE4C0(5, 16, 11),
    type_4FE4C0(6, 21, 9),
    type_4FE4C0(7, 1, 3),
    type_4FE4C0(8, 0, 2),
    type_4FE4C0(9, 25, 6),
    type_4FE4C0(10, 28, 5),
    type_4FE4C0(11, 14, 4),
    type_4FE4C0(12, 10, 92),
    type_4FE4C0(13, 13, 95),
    type_4FE4C0(14, 22, 12),
    type_4FE4C0(15, 17, 14),
    type_4FE4C0(16, 4, 98),
    type_4FE4C0(17, 23, 101),
    type_4FE4C0(18, 24, 15),
    type_4FE4C0(19, 18, 88),
    type_4FE4C0(20, 19, 78),
    type_4FE4C0(21, 5, 80),
    type_4FE4C0(22, 27, 84),
    type_4FE4C0(23, 9, 11),
    type_4FE4C0(24, 15, -1),
    type_4FE4C0(25, 20, -1),
    type_4FE4C0(26, -1, -1),
    type_4FE4C0(27, 11, -1),
    type_4FE4C0(28, 12, -1),
    type_4FE4C0(29, -1, -1),
    type_4FE4C0(30, -1, -1),
    type_4FE4C0(31, 29, -1),
    type_4FE4C0(32, -1, -1),
    type_4FE4C0(33, -1, -1),
    type_4FE4C0(34, -1, 108),
    type_4FE4C0(35, -1, -1),
    type_4FE4C0(36, -1, -1),
    type_4FE4C0(37, -1, 104)
};
// Its data (PLAN M5): literals, constants and tables where the image has them.
// match: ?flt_3E37F4@@3MB @ 0x003E37F4
// match: ?flt_3E37F8@@3MB @ 0x003E37F8
// match: ?flt_3E37FC@@3MB @ 0x003E37FC
// match: ??_C@_0CK@LHECAPJB@Waiting?5for?5sections?5to?5finish?5l@ @ 0x003E3800
// match: .CRT$XCU+0 @ 0x00427210
// match: .CRT$XCU+4 @ 0x00427214

// match: _$E2 @ 0x0030C3F0
// match: _$E3 @ 0x0030EB40
// match: _$E5 @ 0x0030C410
// match: ??1type_1E7CF0@kujuUI@@UAE@XZ @ 0x001C5740
// match: ?sub_1C5800@@YAHH@Z @ 0x001C5800

RwInt32 sub_1C5800(RwInt32 arg_0)
{
    RwUInt32 var_4;

    if (byte_4FE4B8)
        return dword_4FDC08[arg_0];
    for (var_4 = 0; var_4 < 0x26; var_4++)
    {
        if (dword_4FE4C0[var_4].unk_00 == arg_0)
            return dword_4FE4C0[var_4].unk_04;
    }
    return -1;
}

// match: ??1type_3E0F54@@QAE@XZ @ 0x001C5760
type_3E0F54::~type_3E0F54()
{
}

// match: ?vf_000@type_3E0F54@@UAEXPAUtype_1F8560@@@Z @ 0x001C5780
void type_3E0F54::vf_000(type_1F8560 *arg_0)
{
    arg_0->sub_1F8520(unk_04);
    arg_0->sub_1F8520(unk_08);
    arg_0->sub_1F8520(unk_0C);
}

// match: ?vf_004@type_3E0F54@@UAEXPAUtype_1F8560@@@Z @ 0x001C57C0
void type_3E0F54::vf_004(type_1F8560 *arg_0)
{
    unk_04 = arg_0->sub_1F8560();
    unk_08 = arg_0->sub_1F8560();
    unk_0C = arg_0->sub_1F8560();
}

// match: ?sub_1C5860@@YAHH@Z @ 0x001C5860
RwInt32 sub_1C5860(RwInt32 arg_0)
{
    RwUInt32 var_4;

    if (byte_4FE4B8)
        return dword_4FE2B8[arg_0];
    for (var_4 = 0; var_4 < 0x26; var_4++)
    {
        if (dword_4FE4C0[var_4].unk_04 == arg_0)
            return dword_4FE4C0[var_4].unk_00;
    }
    return -1;
}

// match: ?sub_1C58C0@@YAXXZ @ 0x001C58C0
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void sub_1C58C0()
{
    RwInt32 lv_8;
    RwInt32 lv_C;
    type_4E5D30 *var_4;

    for (lv_8 = 0; lv_8 < 4; lv_8++)
    {
        var_4 = &dword_4E5D30[lv_8];
        lv_C = var_4->unk_04;

        if (lv_C)
        {
            if (0)
                sub_1C8A30("Waiting for sections to finish loading 2\n");
        }
    }
    sub_821C0();
}

// match: ?vf_000@type_3DA434@@UAEXPAUtype_1F8560@@@Z @ 0x001C5920
void type_3DA434::vf_000(type_1F8560 *arg_0)
{
    arg_0->sub_1F86D0(unk_0C, 0, 500.0f, 8);
    arg_0->sub_1F8860(unk_08, 8);
    arg_0->sub_1F8860(unk_04, 6);
}

// match: ?vf_004@type_3DA434@@UAEXPAUtype_1F8560@@@Z @ 0x001C5970
void type_3DA434::vf_004(type_1F8560 *arg_0)
{
    unk_0C = arg_0->sub_1F8640(0, 500.0f, 8);
    unk_08 = arg_0->sub_1F8810(8);
    unk_04 = arg_0->sub_1F8810(6);
}

// match: ?vf_000@type_3E0F6C@@UAEXPAUtype_1F8560@@@Z @ 0x001C59C0
void type_3E0F6C::vf_000(type_1F8560 *arg_0)
{
    arg_0->sub_1F86D0(unk_0C, 0, 500.0f, 8);
    arg_0->sub_1F8860(unk_08, 8);
    arg_0->sub_1F8860(unk_04, 6);
    arg_0->sub_1F8860(unk_09, 4);
}

// match: ?vf_004@type_3E0F6C@@UAEXPAUtype_1F8560@@@Z @ 0x001C5A20
void type_3E0F6C::vf_004(type_1F8560 *arg_0)
{
    unk_0C = arg_0->sub_1F8640(0, 500.0f, 8);
    unk_08 = arg_0->sub_1F8810(8);
    unk_04 = arg_0->sub_1F8810(6);
    unk_09 = arg_0->sub_1F8810(4);
}

// match: ?sub_1C5A80@type_3DA434@@QAEXM@Z @ 0x001C5A80
void type_3DA434::sub_1C5A80(RwReal arg_0)
{
    if (arg_0 > 500.0f)
        unk_0C = 500.0f;
    else
        unk_0C = arg_0;
}






// The message's implicit constructor, out of line (docs/toolchain.md: its
// vectors have inline constructors).









// Functions /OPT:ICF folded into another body (config/aliases.txt), defined here for the
// authentic link (PLAN M7) with that body; the placement link takes the folded one.

// ?sub_1C5A80@type_3E0F6C@@QAEXM@Z (folded into 0x1C5A80)
void type_3E0F6C::sub_1C5A80(RwReal arg_0)
{
    if (arg_0 > 500.0f)
        unk_0C = 500.0f;
    else
        unk_0C = arg_0;
}

// ?vf_000@type_3E0F84@@UAEXPAUtype_1F8560@@@Z (folded into 0x1B4670)
void type_3E0F84::vf_000(struct type_1F8560 *arg_0)
{
    arg_0->sub_1F8520(unk_04);
}
