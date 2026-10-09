/*
 * In-game menu 12's sign-in page (game/livemenu.h): waits for the network
 * system's state and opens the next menu.
 */
#include "game/liveservice.h"
#include "types/cXboxLive.h"
#include "game/livemenu.h"
#include "game/ingamemenu.h"
#include "game/startup.h"

// Its data definitions (PLAN M5), in the image's address order.
#ifndef CODFH_SP // MP only: unreferenced constants single player does not emit (not in default.xbe; /O2 keeps them only while they are external)
// 0x003E8DB0
extern const RwReal flt_3E8DB0 = 0.01f;
// 0x003E8DB4
extern const RwReal flt_3E8DB4 = 0.01f;
// 0x003E8DB8
extern const RwReal flt_3E8DB8 = 16.666666f;
#endif
// End of its data definitions.


// Its data (PLAN M5): literals, constants and tables where the image has them.
// match: ?flt_3E8DB0@@3MB @ 0x003E8DB0
// match: ?flt_3E8DB4@@3MB @ 0x003E8DB4
// match: ?flt_3E8DB8@@3MB @ 0x003E8DB8
// match: ??_7type_20A670@@6B@ @ 0x003E8DC0

// match: ??0type_20A670@@QAE@XZ @ 0x0020A670

type_20A670::type_20A670() : type_2049D0("", 0, true)
{
    unk_188 = 1;
}

// match: ??_Gtype_20A670@@UAEPAXI@Z @ 0x0020A6B0
// match: ??1type_20A670@@UAE@XZ @ 0x0020A6E0
type_20A670::~type_20A670()
{
}

// match: ?vf_014@type_20A670@@UAEXM@Z @ 0x0020A700
void type_20A670::vf_014(RwReal arg_0)
{
    if (unk_188)
    {
        sub_227560()->sub_2270E0(1);
        unk_188 = 0;
    }
    if (!sub_1D8810()->unk_2918_is_1())
    {
        if (sub_1D8810()->voice_running())
            sub_1FC310()->sub_1FBDA0(sub_2046C0(6));
        else
            sub_1FC310()->sub_1FBDA0(sub_2046C0(13));
        unk_188 = 1;
    }
}
