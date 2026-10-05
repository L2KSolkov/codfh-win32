// An object whose code the original link dropped (/OPT:REF): only its data is in
// the image, at 0x3E24C0-0x3E254C, before the network player's (unit_1B7B20): its
// constants (16.666666 and a few more), the network player interface's vtable
// (type_3E24E8, which the player's constructor also emits: a same-named COMDAT is
// the first object's) and the text "WARNING: Missing idle anim %d.", which
// unit_1BAA90's sub_1BAE40 also prints.

#include "rw/ostypes.h"
#include "rw/batypes.h"
#include "game/netmsg.h"
#include "game/debugtext.h"

// Its data definitions (PLAN M5), in the image's address order.
// 0x003E24C0
extern const RwReal flt_3E24C0 = 16.666666f;
// 0x003E24C4
extern const RwReal flt_3E24C4 = 1.0f;
// 0x003E24C8
extern const RwReal flt_3E24C8 = 0.0f;
// 0x003E24CC
extern const RwReal flt_3E24CC = 0.0f;
// 0x003E24D0
extern const RwReal flt_3E24D0 = 0.0f;
// 0x003E24D4
extern const RwReal flt_3E24D4 = 1.0f;
// 0x003E24D8
extern const RwReal flt_3E24D8 = 0.0f;
// 0x003E24DC
extern const RwReal flt_3E24DC = 0.01f;
// 0x003E24E0
extern const RwReal flt_3E24E0 = 0.01f;
// 0x003E24E4
extern const RwReal flt_3E24E4 = 0.0f;
// End of its data definitions.

// Its data (PLAN M5): literals, constants and tables where the image has them.
// match: ?flt_3E24C0@@3MB @ 0x003E24C0
// match: ?flt_3E24C4@@3MB @ 0x003E24C4
// match: ?flt_3E24C8@@3MB @ 0x003E24C8
// match: ?flt_3E24CC@@3MB @ 0x003E24CC
// match: ?flt_3E24D0@@3MB @ 0x003E24D0
// match: ?flt_3E24D4@@3MB @ 0x003E24D4
// match: ?flt_3E24D8@@3MB @ 0x003E24D8
// match: ?flt_3E24DC@@3MB @ 0x003E24DC
// match: ?flt_3E24E0@@3MB @ 0x003E24E0
// match: ?flt_3E24E4@@3MB @ 0x003E24E4
// match: ??_7type_3E24E8@@6B@ @ 0x003E24E8
// match: ??_C@_0BP@NHIDMHDM@WARNING?3?5Missing?5idle?5anim?5?$CFd?4?$AA@ @ 0x003E252C

// Not in the image: stand-ins for the dropped code. The constructor of a class
// built on the interface (game/netmsg.h), which emits the interface's vtable
// here. Unreferenced.
dropped_3E24E8::dropped_3E24E8()
{
}

// The code that first printed the idle animation warning. Unreferenced.
void dropped_3E252C(RwInt32 arg_0)
{
    sub_16C220("WARNING: Missing idle anim %d.", arg_0);
}
