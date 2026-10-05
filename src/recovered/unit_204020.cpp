/*
 * The in-game menus (game/ingamemenu.h): the fourteen menus built and
 * deleted, queued to load and loaded a step at a time, and the menu arg_0.
 * The menus (unk_5044F0) and the load queue (unk_50452C) are kujuUI's
 * arrays of fourteen (game/kujufont.h); their constructors run from the
 * compiler's initialisers (0x30DAD0, 0x30DAE0), which IDA leaves inside a
 * chunk and which are not matched yet (docs/questions.md).
 */
#include "game/ingamemenu.h"
#include "game/ingamepages.h"
#include "game/frontend.h"
#include "game/livemenu.h"
#include "game/livebase.h"

// Its data definitions (PLAN M5), in the image's address order.
// 0x0042D278
const RwChar *dword_42D278[5] = { "Not signed in.", "Signing in...", "Sign-In Failed", "Not Signed In: Passcode Needed", "Signed in:" };
// (Defined after the data: VC7.1 emits a unit's data definitions in reverse order, and
// the image has these constants before the data's texts.)
// 0x003E8404
extern const RwReal flt_3E8404 = 0.01f;
// 0x003E8408
extern const RwReal flt_3E8408 = 0.01f;
// 0x003E840C
extern const RwReal flt_3E840C = 16.666666f;

// match: ?flt_3E8404@@3MB @ 0x003E8404
// match: ?flt_3E8408@@3MB @ 0x003E8408
// match: ?flt_3E840C@@3MB @ 0x003E840C
// match: ??_C@_0L@PFBAFLI@Signed?5in?3?$AA@ @ 0x003E8410
// match: ??_C@_0BP@LFIPBAAJ@Not?5Signed?5In?3?5Passcode?5Needed?$AA@ @ 0x003E841C
// match: ??_C@_0P@CLPMNBKD@Sign?9In?5Failed?$AA@ @ 0x003E843C
// match: ??_C@_0O@HOCAEILG@Signing?5in?4?4?4?$AA@ @ 0x003E844C
// match: ??_C@_0P@IEIKHKAM@Not?5signed?5in?4?$AA@ @ 0x003E845C
// match: ?dword_42D278@@3PAPBDA @ 0x0042D278

// Its data (PLAN M5): literals, constants and tables where the image has them.
// match: __ehhandler$?sub_204100@@YAXXZ>1>8 @ 0x00422668
// match: __ehhandler$?sub_204100@@YAXXZ>1 @ 0x004226D8
// match: .CRT$XCU+0 @ 0x0042735C
// match: .CRT$XCU+4 @ 0x00427360

// match: _$E1 @ 0x0030DAD0
// match: _$E3 @ 0x0030DAE0

using namespace kujuUI;

// Built by their dynamic initializers (0x30DAD0, 0x30DAE0).
type_1E61A0<type_1FBDA0_menu *, 14> unk_5044F0;
type_1E61A0<type_1FBDA0_menu *, 14> unk_50452C;
// The in-game menus' widgets set up and put away (not yet matched).
void sub_2173A0();
void sub_217450();

// The arrays' instances.
// match: ?capacity@?$type_1E61A0@PAUtype_1FBDA0_menu@@$0O@@@SAIXZ @ 0x00204800
// match: ?next@?$type_1E61A0@PAUtype_1FBDA0_menu@@$0O@@@QAEPAPAUtype_1FBDA0_menu@@XZ @ 0x00204810
// match: ?erase@?$type_1E61A0@PAUtype_1FBDA0_menu@@$0O@@@QAEXI@Z @ 0x00204850
// match: ?end@?$type_1E61A0@PAUtype_1FBDA0_menu@@$0O@@@QAE?AU?$type_1E61A0_it@PAUtype_1FBDA0_menu@@$0O@@@XZ @ 0x002048C0
// match: ?empty@?$type_1E61A0@PAUtype_1FBDA0_menu@@$0O@@@QAE_NXZ @ 0x002048F0
// match: ?clear@?$type_1E61A0@PAUtype_1FBDA0_menu@@$0O@@@QAEXXZ @ 0x00204910
// match: ??0?$type_1E61A0_cit@PAUtype_1FBDA0_menu@@$0O@@@QAE@ABU?$type_1E61A0_it@PAUtype_1FBDA0_menu@@$0O@@@@Z @ 0x00204960
// match: ??E?$type_1E61A0_cit@PAUtype_1FBDA0_menu@@$0O@@@QAEAAU0@XZ @ 0x00204990
// Their constructor, which the compiler's initialisers of the two arrays
// call (0x30DAD0, 0x30DAE0).
// match: ??0?$type_1E61A0@PAUtype_1FBDA0_menu@@$0O@@@QAE@XZ @ 0x002049B0
template type_1E61A0<type_1FBDA0_menu *, 14>::type_1E61A0();

// match: ?sub_204020@@YAXH@Z @ 0x00204020
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void sub_204020(RwInt32 arg_0)
{
    type_1FBDA0_menu *l4 = sub_2046C0(arg_0);
    RwInt32 var_8 = l4->sub_15FC40();

    if (var_8 != 5 && var_8 != 0)
        *unk_50452C.next() = l4;
}

// match: ?sub_204060@@YAXXZ @ 0x00204060
void sub_204060()
{
    sub_204020(13);
    sub_204020(11);
    sub_204020(12);
    sub_204020(2);
    sub_204020(0);
    sub_204020(1);
    sub_204020(5);
    sub_204020(4);
    sub_204020(3);
    sub_204020(6);
    sub_204020(7);
    sub_204020(8);
    sub_204020(9);
    sub_204020(10);
}

// match: ?sub_204100@@YAXXZ @ 0x00204100
// match: __ehhandler$?sub_204100@@YAXXZ-0x9A @ 0x003055F0
// match: __ehhandler$?sub_204100@@YAXXZ @ 0x0030568A
void sub_204100()
{
    *unk_5044F0.next() = (type_1FBDA0_menu *)new type_206190();
    *unk_5044F0.next() = (type_1FBDA0_menu *)new type_2062B0();
    *unk_5044F0.next() = (type_1FBDA0_menu *)new type_206D10();
    *unk_5044F0.next() = (type_1FBDA0_menu *)new type_207160();
    *unk_5044F0.next() = (type_1FBDA0_menu *)new type_20A7B0();
    *unk_5044F0.next() = (type_1FBDA0_menu *)new type_20B570();
    *unk_5044F0.next() = (type_1FBDA0_menu *)new type_20B9D0();
    *unk_5044F0.next() = (type_1FBDA0_menu *)new type_20C2F0();
    *unk_5044F0.next() = (type_1FBDA0_menu *)new type_2097E0();
    *unk_5044F0.next() = (type_1FBDA0_menu *)new type_209BF0();
    *unk_5044F0.next() = (type_1FBDA0_menu *)new type_2098F0();
    *unk_5044F0.next() = (type_1FBDA0_menu *)new type_209D00();
    *unk_5044F0.next() = (type_1FBDA0_menu *)new type_20A670();
    *unk_5044F0.next() = (type_1FBDA0_menu *)new type_20AA10();
    ((type_20E850 *)((type_1FBDA0_menu *)sub_20A540()))->sub_20EA40();
    sub_204060();
    sub_2173A0();
    type_1E7CF0 *var_10 = sub_1E7CF0();
    var_10->sub_1E80F0(true);
    var_10->sub_1E8110(false);
}

// match: ?sub_204620@@YAXXZ @ 0x00204620
void sub_204620()
{
    for (RwInt32 var_4 = 0; var_4 != 14; var_4++)
        delete *unk_5044F0.at(var_4);
    unk_5044F0.clear();
    unk_50452C.clear();
    delete sub_20A540();
    sub_217450();
}

// match: ?sub_2046C0@@YAPAUtype_1FBDA0_menu@@H@Z @ 0x002046C0
type_1FBDA0_menu *sub_2046C0(RwInt32 arg_0)
{
    return *unk_5044F0.at(arg_0);
}

// match: ?sub_2046E0@@YA_NXZ @ 0x002046E0
bool sub_2046E0()
{
    return !unk_5044F0.empty();
}

// match: ?sub_204700@@YAXXZ @ 0x00204700
void sub_204700()
{
    if (!unk_50452C.empty())
    {
        type_1FBDA0_menu *var_4 = *unk_50452C.at(0);
        var_4->sub_1F4450();
        if (var_4->sub_15FC40() == 5)
            unk_50452C.erase(0);
    }
}

// match: ?sub_204750@@YA_NXZ @ 0x00204750
bool sub_204750()
{
    return sub_204770() == type_1E61A0<type_1FBDA0_menu *, 14>::capacity();
}

// match: ?sub_204770@@YAHXZ @ 0x00204770
RwInt32 sub_204770()
{
    RwInt32 var_4 = 0;

    for (type_1E61A0_cit<type_1FBDA0_menu *, 14> var_C(unk_5044F0.begin()); var_C.ne(unk_5044F0.end()); ++var_C)
    {
        type_1FBDA0_menu *var_10 = *var_C.get();
        if (var_10->sub_15FC40() == 5 || var_10->sub_15FC40() == 0)
            var_4++;
    }
    return var_4;
}
