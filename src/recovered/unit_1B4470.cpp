// Message handlers: split from unit_1B18E0.cpp at 0x1B4470, where the image ends that object (its
// deferred functions come before the next out-of-line one; PLAN M7).

#include <xtl.h>
#include "game/netmsg.h"
#include "game/data.h"
#include "game/bombsites.h"
#include "game/flags.h"
#include "game/mpgame.h"
#include "game/gameloop.h"
#include "types/type_DC400.h"
#include "game/functions.h"
#include "game/debugtext.h"
#include "game/netplayer.h"
#include "game/parsedfile.h"
#include "types/alfaobject.h"

void sub_1C4A10();

// match: ?sub_1B4470@@YAXXZ @ 0x001B4470
void sub_1B4470()
{
    sub_1C4A10();
    dword_4FB9E0.sub_1B5750();
    dword_4F6A7C.sub_1A4B00();
    dword_4B86F8 |= 8;
}
void sub_1C5220();
extern RwUInt8 byte_4FDAA8;
// match: ?sub_1B44A0@@YAXXZ @ 0x001B44A0
void sub_1B44A0()
{
    sub_1C4A10();
    dword_4FB9E0.sub_1B5750();
    dword_4F6A7C.sub_1A4B00();
    if (dword_4FB9E0.get_unk_C8() && byte_4FDAA8)
        sub_1C5220();
    dword_4B86F8 |= 4;
}
// match: ?sub_1B44F0@@YAXXZ @ 0x001B44F0
void sub_1B44F0()
{
    dword_4FB9E0.sub_1B6360();
}
// match: ?sub_1B4500@@YAXXZ @ 0x001B4500
void sub_1B4500()
{
    dword_4FB9E0.sub_1B6250();
}
// match: ?sub_1B4510@@YAXXZ @ 0x001B4510
void sub_1B4510()
{
    dword_4FB9E0.sub_1B69B0();
}
// match: ?sub_1B4520@@YAXXZ @ 0x001B4520
void sub_1B4520()
{
    dword_4FB9E0.sub_1B6AA0();
}
// match: ?vf_000@type_3E105C@@UAEXPAUtype_1F8560@@@Z @ 0x001B4530
void type_3E105C::vf_000(type_1F8560 *arg_0)
{
    dword_4FB9E0.sub_1B57E0(arg_0);
    dword_4FBB20.sub_1BDB10(arg_0);
    unk_4F8184.sub_1A8730(arg_0);
    dword_4F8288.sub_1C2970(arg_0);
    unk_4F7EB8.unk_384.sub_1B21A0(arg_0);
    unk_4F7EB8.unk_04.vf_000(arg_0);
    unk_4F7EB8.unk_D0.vf_000(arg_0);
}
// match: ?vf_004@type_3E105C@@UAEXPAUtype_1F8560@@@Z @ 0x001B45A0
void type_3E105C::vf_004(type_1F8560 *arg_0)
{
    if (((kujuUI::type_1C8DF0_104_00 *)&dword_4FB9E0)->sub_1E3480() == 1)
    {
        dword_4FB9E0.sub_1B5860(arg_0);
        dword_4FBB20.sub_1BDC30(arg_0);
        unk_4F8184.sub_1A87F0(arg_0);
        dword_4F8288.sub_1C29D0(arg_0);
        unk_4F7EB8.unk_384.sub_1B2290(arg_0);
        unk_4F7EB8.unk_04.vf_004(arg_0);
        unk_4F7EB8.unk_D0.vf_004(arg_0);
        dword_4FB9E0.sub_1B59D0();
    }
}
// match: ?vf_000@type_3E1074@@UAEXPAUtype_1F8560@@@Z @ 0x001B4630
void type_3E1074::vf_000(type_1F8560 *arg_0)
{
    dword_4FB9E0.sub_1B4C10(arg_0);
}
// match: ?vf_004@type_3E1074@@UAEXPAUtype_1F8560@@@Z @ 0x001B4650
void type_3E1074::vf_004(type_1F8560 *arg_0)
{
    dword_4FB9E0.sub_1B4C80(arg_0);
}
// match: ?vf_000@type_3E10BC@@UAEXPAUtype_1F8560@@@Z @ 0x001B4670
void type_3E10BC::vf_000(type_1F8560 *arg_0)
{
    arg_0->sub_1F8520(unk_04);
}
// match: ?vf_004@type_3E10BC@@UAEXPAUtype_1F8560@@@Z @ 0x001B4690
void type_3E10BC::vf_004(type_1F8560 *arg_0)
{
    dword_4FB9E0.sub_1B6EF0(arg_0->sub_1F8560());
}
