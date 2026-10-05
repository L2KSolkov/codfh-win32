/*
 * The shell's hooks (game/frontend.h): the front end's sound player, and
 * the front end's sounds played on the listener or at the player.
 */
#include "game/frontend.h"
#include "game/data.h"
#include "game/functions.h"
#include "types/CGlobalSounds.h"
#include "types/soundbank.h"
#include "types/type_3D3548.h"

// Its data definitions (PLAN M5), in the image's address order.
// 0x003E83E0
extern const RwReal flt_3E83E0 = 16.666666f;
// 0x0042D26C
RwV3d unk_42D26C = { 0.0f, 0.0f, 2.0f };
// 0x005044E4
RwV3d unk_5044E4;
// End of its data definitions.


// Where the front end's sounds are heard, and where they play (both zero).
extern RwV3d unk_5044E4;
extern RwV3d unk_42D26C;

// Its data (PLAN M5): literals, constants and tables where the image has them.
// match: ?flt_3E83E0@@3MB @ 0x003E83E0
// match: ??_7type_3E83E4@@6B@ @ 0x003E83E4
// match: ??_7type_3E83F4@@6B@ @ 0x003E83F4
// match: __ehhandler$??1type_3E83E4@@QAE@XZ>1>8 @ 0x00422644
// match: __ehhandler$??1type_3E83E4@@QAE@XZ>1 @ 0x0042264C
// match: ?unk_42D26C@@3URwV3d@@A @ 0x0042D26C

// match: ??0type_3E83E4@@QAE@XZ @ 0x00203D80

type_3E83E4::type_3E83E4()
{
}

// match: ??1type_3E83E4@@QAE@XZ @ 0x00203DB0
// match: __ehhandler$??1type_3E83E4@@QAE@XZ-0xB @ 0x003055D0
// match: __ehhandler$??1type_3E83E4@@QAE@XZ @ 0x003055DB
type_3E83E4::~type_3E83E4()
{
    unk_04.sub_88DF0();
}

// match: ?vf_04@type_3E83E4@@UAEXH@Z @ 0x00203E10
void type_3E83E4::vf_04(RwInt32 arg_0)
{
    if (dword_44E834)
    {
        do
        {
            dword_44E8AC->unk_28 = unk_5044E4;
            dword_44E8AC->unk_70 |= 1;
        } while (0);
        switch (arg_0)
        {
        case 0:
            dword_4B1E98.sub_8A980(&dword_4B1C88, 0, 0, &unk_42D26C, 1, 1);
            break;
        case 1:
            dword_4B1E98.sub_8A980(&dword_4B1C00, 0, 0, &unk_42D26C, 1, 1);
            break;
        case 2:
            dword_4B1E98.sub_8A980(&dword_4B1C98, 0, 0, &unk_42D26C, 1, 1);
            break;
        case 3:
            dword_4B1E98.sub_8A980(&dword_4B1B48, 0, 0, &unk_42D26C, 1, 1);
            break;
        }
    }
    else if (sub_1745A0(0))
    {
        switch (arg_0)
        {
        case 0:
            dword_4B1E98.sub_8A980(&dword_4B1C88, 0, 0, (RwV3d *)sub_1745A0(0)->vf_0C4(), 1, 1);
            break;
        case 1:
            dword_4B1E98.sub_8A980(&dword_4B1C00, 0, 0, (RwV3d *)sub_1745A0(0)->vf_0C4(), 1, 1);
            break;
        case 2:
            dword_4B1E98.sub_8A980(&dword_4B1C98, 0, 0, (RwV3d *)sub_1745A0(0)->vf_0C4(), 1, 1);
            break;
        case 3:
            dword_4B1E98.sub_8A980(&dword_4B1B48, 0, 0, (RwV3d *)sub_1745A0(0)->vf_0C4(), 1, 1);
            break;
        }
    }
}

// Members /OPT:ICF folded into shared trivial bodies (config/aliases.txt): defined here for
// the authentic link (PLAN M7); the placement link takes the shared bodies.

// ?vf_00@type_3E83E4@@UAEXXZ (folded into the empty body at 0x1E41C0)
void type_3E83E4::vf_00()
{
}

// ?vf_08@type_3E83E4@@UAEXXZ (folded into the empty body at 0x1E41C0)
void type_3E83E4::vf_08()
{
}

// ?vf_0C@type_3E83E4@@UAEXXZ (folded into the empty body at 0x1E41C0)
void type_3E83E4::vf_0C()
{
}
