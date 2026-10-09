/*
 * The searching pages' dots (game/livemenu.h): a text with zero to three
 * dots cycling as time passes; and the score limit's constructor after it
 * (its texts type_1CB670, default-constructed out of line) with its
 * deleting destructor.
 */
#include "game/livemenu.h"

// Its data definitions (PLAN M5), in the image's address order.
#ifndef CODFH_SP // MP only: unreferenced constants single player does not emit (not in default.xbe; /O2 keeps them only while they are external)
// 0x003E9344
extern const RwReal flt_3E9344 = 0.01f;
// 0x003E9348
extern const RwReal flt_3E9348 = 0.01f;
// 0x003E934C
extern const RwReal flt_3E934C = 16.666666f;
#endif
// 0x00505180
RwReal flt_505180;
// End of its data definitions.


using namespace kujuUI;

// Its data (PLAN M5): literals, constants and tables where the image has them.
// match: ?flt_3E9344@@3MB @ 0x003E9344
// match: ?flt_3E9348@@3MB @ 0x003E9348
// match: ?flt_3E934C@@3MB @ 0x003E934C
// match: ??_7type_20EC00@@6B@ @ 0x003E9350
// match: __ehhandler$?sub_20EB30@@YA?AUtype_1CB670@@ABU1@M@Z>1>8 @ 0x00423708
// match: __ehhandler$?sub_20EB30@@YA?AUtype_1CB670@@ABU1@M@Z>1 @ 0x00423718
// match: __ehhandler$??0type_20EC00@@QAE@HHHHHHHHPAUtype_1ED670_object@kujuUI@@@Z>1>8 @ 0x00423734
// match: __ehhandler$??0type_20EC00@@QAE@HHHHHHHHPAUtype_1ED670_object@kujuUI@@@Z>1 @ 0x0042377C

// match: ?sub_20EB30@@YA?AUtype_1CB670@@ABU1@M@Z @ 0x0020EB30
// match: __ehhandler$?sub_20EB30@@YA?AUtype_1CB670@@ABU1@M@Z-0x21 @ 0x00306880
// match: __ehhandler$?sub_20EB30@@YA?AUtype_1CB670@@ABU1@M@Z @ 0x003068A1

type_1CB670 sub_20EB30(const type_1CB670 &arg_0, RwReal arg_4)
{
    RwInt32 lv_10;
    type_1CB670 lv_30(arg_0);

    lv_10 = (RwInt32)((flt_505180 += arg_4) * 4.0f) & 3;
    for (RwInt32 lv_34 = 0; lv_34 != lv_10; lv_34++)
        add_text(lv_30, *sub_1CBA30());
    return lv_30;
}

// The score limit: from arg_0 to arg_4 (starting at arg_8, stepped by
// arg_C and arg_10 when held, arg_14, arg_18), "No limit" at the least when
// arg_1C is 1; the hook arg_20.
// match: ??0type_20EC00@@QAE@HHHHHHHHPAUtype_1ED670_object@kujuUI@@@Z @ 0x0020EC00
// match: __ehhandler$??0type_20EC00@@QAE@HHHHHHHHPAUtype_1ED670_object@kujuUI@@@Z-0x59 @ 0x003068B0
// match: __ehhandler$??0type_20EC00@@QAE@HHHHHHHHPAUtype_1ED670_object@kujuUI@@@Z @ 0x00306909
type_20EC00::type_20EC00(RwInt32 arg_0, RwInt32 arg_4, RwInt32 arg_8, RwInt32 arg_C, RwInt32 arg_10, RwInt32 arg_14,
                         RwInt32 arg_18, RwInt32 arg_1C, type_1ED670_object *arg_20)
    : type_1E76A0(arg_0, arg_4, arg_8, arg_C, arg_10, arg_14, arg_18,
                  arg_1C == 1 ? type_1CB670("No limit", 0) : type_1CB670(), type_1CB670(), type_1CB670(), arg_20)
{
}

// match: ??_Gtype_20EC00@@UAEPAXI@Z @ 0x0020EDD0
