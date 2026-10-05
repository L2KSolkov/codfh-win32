/*
 * The in-game controls' legend (game/ingamepages.h): two texts over the
 * pause menu.
 */
#include "game/ingamepages.h"

// Its data definitions (PLAN M5), in the image's address order.
// 0x003E9CCC
extern const RwReal flt_3E9CCC = 0.01f;
// 0x003E9CD0
extern const RwReal flt_3E9CD0 = 0.01f;
// 0x003E9CD4
extern const RwReal flt_3E9CD4 = 16.666666f;
// End of its data definitions.


using namespace kujuUI;

// Its data (PLAN M5): literals, constants and tables where the image has them.
// match: ?flt_3E9CCC@@3MB @ 0x003E9CCC
// match: ?flt_3E9CD0@@3MB @ 0x003E9CD0
// match: ?flt_3E9CD4@@3MB @ 0x003E9CD4
// match: ??_C@_09HDEKPJNE@RightText?$AA@ @ 0x003E9CD8
// match: ??_C@_08BBFEGILF@LeftText?$AA@ @ 0x003E9CE4
// match: ??_7type_218DD0@@6B@ @ 0x003E9CF0
// match: __ehhandler$??0type_218DD0@@QAE@PBDPAUtype_21A5E0@@@Z>1>8 @ 0x00424930
// match: __ehhandler$??0type_218DD0@@QAE@PBDPAUtype_21A5E0@@@Z>1 @ 0x00424948
// match: __ehhandler$??1type_218DD0@@UAE@XZ>1>8 @ 0x00424964
// match: __ehhandler$??1type_218DD0@@UAE@XZ>1 @ 0x00424974

// match: ??0type_218DD0@@QAE@PBDPAUtype_21A5E0@@@Z @ 0x00218DD0
// match: __ehhandler$??0type_218DD0@@QAE@PBDPAUtype_21A5E0@@@Z-0x24 @ 0x003076C0
// match: __ehhandler$??0type_218DD0@@QAE@PBDPAUtype_21A5E0@@@Z @ 0x003076E4

type_218DD0::type_218DD0(const RwChar *arg_0, type_21A5E0 *arg_4) : type_21CB10(arg_0, arg_4, 0)
{
    sub_204FC0("LeftText", &unk_154);
    sub_204FC0("RightText", &unk_17C);
}

// match: ??_Gtype_218DD0@@UAEPAXI@Z @ 0x00218E80
// match: ??1type_218DD0@@UAE@XZ @ 0x00218EB0
// match: __ehhandler$??1type_218DD0@@UAE@XZ-0x16 @ 0x003076F0
// match: __ehhandler$??1type_218DD0@@UAE@XZ @ 0x00307706
type_218DD0::~type_218DD0()
{
}

// match: ?sub_218F20@type_218DD0@@QAEXABUtype_1A5EA0@@@Z @ 0x00218F20
void type_218DD0::sub_218F20(const type_1A5EA0 &arg_0)
{
    unk_154.sub_1F28C0(arg_0);
}
