/*
 * The shell on a camera (game/frontend.h): its in-game menus' manager
 * pointed at the opening menu once the menus are loaded, run, and put away
 * with its items.
 */
#include "game/liveservice.h"
#include "game/frontend.h"
#include "game/options.h"
#include "game/savestate.h"
#include "game/startup.h"

// Its data definitions (PLAN M5), in the image's address order.
// 0x005044DC
RwInt32 dword_5044DC;
// End of its data definitions.


// The items' instantiations.
// Its data (PLAN M5): literals, constants and tables where the image has them.
// match: __ehhandler$??0type_200960@@QAE@PAURwCamera@@@Z>1>8 @ 0x00422170
// match: __ehhandler$??0type_200960@@QAE@PAURwCamera@@@Z>1 @ 0x00422178
// match: __ehhandler$??1type_200960@@QAE@XZ>1>8 @ 0x00422194
// match: __ehhandler$??1type_200960@@QAE@XZ>1 @ 0x0042219C

// match: ??0?$type_1E61A0@PAX$04@@QAE@XZ @ 0x00200B00
// match: ?delete_all@?$type_1E61A0@PAX$04@@QAEXXZ @ 0x00200B20
// match: ?item_size@?$type_1E61A0@PAX$04@@SAIXZ @ 0x00200B80
// match: ??0type_200960@@QAE@PAURwCamera@@@Z @ 0x00200960
// match: __ehhandler$??0type_200960@@QAE@PAURwCamera@@@Z-0xB @ 0x00305120
// match: __ehhandler$??0type_200960@@QAE@PAURwCamera@@@Z @ 0x0030512B

type_200960::type_200960(RwCamera *arg_0) : unk_00(arg_0), unk_04(0)
{
    type_1FBDA0_menu *bp_10 = 0;
    bool bp_11 = false;

    sub_204100();
    while (!sub_204750())
        sub_204700();
    if (dword_4F45F8->unk_3C != 0)
    {
        if (dword_4F45F8->unk_3C == 1)
        {
            sub_227560()->sub_2270E0(1);
            dword_4F45F8->unk_3C = 2;
        }
        else
            dword_4F45F8->unk_3C = 0;
    }
    switch (dword_5044DC)
    {
    case 0:
        bp_10 = sub_2046C0(13);
        bp_11 = true;
        break;
    case 1:
        bp_10 = sub_2046C0(13);
        break;
    case 2:
        bp_10 = sub_2046C0(13);
        break;
    }
    if (bp_11)
        sub_1C4F70(1);
    // A compiled-out check of the camera: no code, but its load moves the
    // compiler's register rotation.
    if (!unk_00)
    {
    }
    unk_04.sub_1FBDA0(bp_10);
}

// match: ??1type_200960@@QAE@XZ @ 0x00200A90
// match: __ehhandler$??1type_200960@@QAE@XZ-0xB @ 0x00305140
// match: __ehhandler$??1type_200960@@QAE@XZ @ 0x0030514B
type_200960::~type_200960()
{
    unk_14.delete_all();
}

// match: ?sub_200AE0@type_200960@@QAEXXZ @ 0x00200AE0
void type_200960::sub_200AE0()
{
    unk_04.sub_1FBE70(unk_00);
}
