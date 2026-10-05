/*
 * The error screens (game/ingamepages.h): a message and "continue". Setting
 * the message (sub_216C10) unwinds its text through the library's
 * out-of-line string destructor (sub_43900) and is not matched
 * (docs/questions.md).
 */
#include "game/ingamepages.h"

// Its data definitions (PLAN M5), in the image's address order.
// 0x003E98B0
extern const RwReal flt_3E98B0 = 0.01f;
// 0x003E98B4
extern const RwReal flt_3E98B4 = 0.01f;
// 0x003E98B8
extern const RwReal flt_3E98B8 = 16.666666f;
// End of its data definitions.


using namespace kujuUI;

// Its data (PLAN M5): literals, constants and tables where the image has them.
// match: ?flt_3E98B0@@3MB @ 0x003E98B0
// match: ?flt_3E98B4@@3MB @ 0x003E98B4
// match: ?flt_3E98B8@@3MB @ 0x003E98B8
// match: ??_C@_08DLICDMBN@continue?$AA@ @ 0x003E98BC
// match: ??_7type_216C10@@6B@ @ 0x003E98C8
// match: ??_7?$type_3E7CE8@Utype_216C10@@@kujuUI@@6B@ @ 0x003E9918
// match: __ehhandler$??0type_216C10@@QAE@PBDPAUtype_21A5E0@@@Z>1>8 @ 0x00424448
// match: __ehhandler$??0type_216C10@@QAE@PBDPAUtype_21A5E0@@@Z>1 @ 0x00424460
// match: __ehhandler$??1type_216C10@@UAE@XZ>1>8 @ 0x0042447C
// match: __ehhandler$??1type_216C10@@UAE@XZ>1 @ 0x0042448C
// match: __ehhandler$?sub_216C10@type_216C10@@QAEXPBD@Z>1>8 @ 0x004244A8
// match: __ehhandler$?sub_216C10@type_216C10@@QAEXPBD@Z>1 @ 0x004244B0

// match: ??0type_216C10@@QAE@PBDPAUtype_21A5E0@@@Z @ 0x00216AB0
// match: __ehhandler$??0type_216C10@@QAE@PBDPAUtype_21A5E0@@@Z-0x24 @ 0x00307230
// match: __ehhandler$??0type_216C10@@QAE@PBDPAUtype_21A5E0@@@Z @ 0x00307254

type_216C10::type_216C10(const RwChar *arg_0, type_21A5E0 *arg_4)
    : type_21CB10(arg_0, arg_4, 0), unk_17C(this, &type_216C10::sub_220A80)
{
    sub_204FC0("continue", &unk_17C);
    sub_204FC0("Reason", &unk_154);
}

// match: ??_Gtype_216C10@@UAEPAXI@Z @ 0x00216B70
// match: ??1type_216C10@@UAE@XZ @ 0x00216BA0
// match: __ehhandler$??1type_216C10@@UAE@XZ-0x16 @ 0x00307260
// match: __ehhandler$??1type_216C10@@UAE@XZ @ 0x00307276
type_216C10::~type_216C10()
{
}

// Shows the localised text for the key arg_0 as the message.
// match: ?sub_216C10@type_216C10@@QAEXPBD@Z @ 0x00216C10
// match: __ehhandler$?sub_216C10@type_216C10@@QAEXPBD@Z-0x8 @ 0x00307280
// match: __ehhandler$?sub_216C10@type_216C10@@QAEXPBD@Z @ 0x00307288
void type_216C10::sub_216C10(const RwChar *arg_0)
{
    type_1A5EA0 var_2C(arg_0, 0);

    unk_154.sub_1F28C0(var_2C);
}

// The actions' members (game/kujuui.h's template, its definitions
// repeated here).
// match: ??0?$type_3E7CE8@Utype_216C10@@@kujuUI@@QAE@PAUtype_216C10@@P82@AEXXZ@Z @ 0x00216C90
template <class T> type_3E7CE8<T>::type_3E7CE8(T *arg_0, void (T::*arg_4)())
{
    unk_04 = arg_0;
    unk_08 = arg_4;
}

// match: ??_G?$type_3E7CE8@Utype_216C10@@@kujuUI@@UAEPAXI@Z @ 0x00216CF0
// match: ??1?$type_3E7CE8@Utype_216C10@@@kujuUI@@UAE@XZ @ 0x00216CD0
template <class T> type_3E7CE8<T>::~type_3E7CE8()
{
}

template <class T> void type_3E7CE8<T>::pvf_008()
{
    (unk_04->*unk_08)();
}

// Functions /OPT:ICF folded into another body (config/aliases.txt), defined here for the
// authentic link (PLAN M7) with that body; the placement link takes the folded one.

// ?sub_220A80@type_216C10@@QAEXXZ (folded into 0x220A80)
void type_216C10::sub_220A80()
{
    sub_1C4B10();
}
