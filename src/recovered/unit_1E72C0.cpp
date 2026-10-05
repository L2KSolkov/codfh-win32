/*
 * kujuUI's image library's pieces (game/kujuui.h): its images by name,
 * which it owns, and an image.
 */
#include <string.h>
#include "game/kujuui.h"

namespace kujuUI {

// Its data (PLAN M5): literals, constants and tables where the image has them.
// match: __ehhandler$??1type_1E72C0@kujuUI@@QAE@XZ>1>8 @ 0x004201C8
// match: __ehhandler$??1type_1E72C0@kujuUI@@QAE@XZ>1 @ 0x004201D0

// match: ??1type_1E72C0@kujuUI@@QAE@XZ @ 0x001E72C0
// match: __ehhandler$??1type_1E72C0@kujuUI@@QAE@XZ-0x8 @ 0x00303C10
// match: __ehhandler$??1type_1E72C0@kujuUI@@QAE@XZ @ 0x00303C18

type_1E72C0::~type_1E72C0()
{
    sub_1E7340();
}

// match: ?sub_1E7310@type_1E72C0@kujuUI@@QAEHPBDPAPAUtype_1E7410@2@@Z @ 0x001E7310
RwInt32 type_1E72C0::sub_1E7310(const RwChar *arg_0, type_1E7410 **arg_4)
{
    type_1E7410 *var_4 = *arg_4;
    *arg_4 = 0;
    return sub_1EFCF0(arg_0, var_4);
}

// match: ?sub_1E7340@type_1E72C0@kujuUI@@QAEXXZ @ 0x001E7340
void type_1E72C0::sub_1E7340()
{
    sub_1E7360();
}

// match: ?sub_1E7360@type_1E72C0@kujuUI@@QAEXXZ @ 0x001E7360
void type_1E72C0::sub_1E7360()
{
    for (type_1E0F80_map::iterator var_4 = unk_00.begin(); var_4 != unk_00.end(); ++var_4)
    {
        type_1E7410 *var_8 = (type_1E7410 *)var_4->second;
        delete var_8;
    }
}

// match: ??0type_1E7410@kujuUI@@QAE@PAUtype_1ECCE0@1@PBUtype_1E0330_rect@1@PBD@Z @ 0x001E7410
type_1E7410::type_1E7410(type_1ECCE0 *arg_0, const type_1E0330_rect *arg_4, const RwChar *arg_8)
{
    unk_2C = *arg_4;
    unk_3C = arg_0;
    RwUInt32 var_4 = strlen(arg_8);
    if (var_4 < 0x2C)
        strcpy(unk_00, arg_8);
    else
    {
        memcpy(unk_00, arg_8, 0x2B);
        unk_00[0x2B] = 0;
    }
}
}

// Functions /OPT:ICF folded into another body (config/aliases.txt), defined here for the
// authentic link (PLAN M7) with that body; the placement link takes the folded one.

// ??1type_1E7410@kujuUI@@QAE@XZ (folded into 0x1E41C0)
kujuUI::type_1E7410::~type_1E7410()
{
}
