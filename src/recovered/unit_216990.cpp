/*
 * The end of round host settings (game/ingamepages.h): the host options
 * pages' base over "EndRoundHostSettings.layout", going back to the
 * widget it was opened from.
 */
#include "game/ingamepages.h"

// Its data definitions (PLAN M5), in the image's address order.
// 0x003E9850
extern const RwReal flt_3E9850 = 0.01f;
// 0x003E9854
extern const RwReal flt_3E9854 = 0.01f;
// 0x003E9858
extern const RwReal flt_3E9858 = 16.666666f;
// End of its data definitions.


using namespace kujuUI;

// Its data (PLAN M5): literals, constants and tables where the image has them.
// match: ?flt_3E9850@@3MB @ 0x003E9850
// match: ?flt_3E9854@@3MB @ 0x003E9854
// match: ?flt_3E9858@@3MB @ 0x003E9858
// match: ??_7type_216990@@6Btype_200B90@@@ @ 0x003E985C
// match: ??_7type_216990@@6Btype_21CB10@@@ @ 0x003E9860

// match: ??0type_216990@@QAE@PBD0PAUtype_3E7D08@kujuUI@@@Z @ 0x00216990

type_216990::type_216990(const RwChar *arg_0, const RwChar *arg_4, type_3E7D08 *arg_8)
    : type_219FE0(arg_0, arg_4, 0, false)
{
    unk_6C0 = arg_8;
}

// match: ??_Gtype_216990@@UAEPAXI@Z @ 0x002169E0
// match: ??1type_216990@@UAE@XZ @ 0x00216A10
type_216990::~type_216990()
{
}

// match: ?vf_040@type_216990@@UAEXXZ @ 0x00216A40
void type_216990::vf_040()
{
    if (unk_6C0)
        unk_6C0->vf_01C(1, 0);
}

// match: ?vf_024@type_216990@@UAEHXZ @ 0x00216A80
RwInt32 type_216990::vf_024()
{
    if (unk_6C0)
        return 0x3A;
    return 0x32;
}
