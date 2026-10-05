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

// Where the front end's sounds are heard, and where they play (both zero).
extern RwV3d unk_5044E4;
extern RwV3d unk_42D26C;

// match: ??0type_3E83E4@@QAE@XZ @ 0x00203D80
type_3E83E4::type_3E83E4()
{
}

// match: ??1type_3E83E4@@QAE@XZ @ 0x00203DB0
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
