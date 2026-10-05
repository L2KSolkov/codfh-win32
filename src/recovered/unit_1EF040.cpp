/*
 * kujuUI's plain raster (a 4 by 4 texture raster made once) and the pad's
 * held-button repeat (game/kujuui.h).
 */
#include <math.h>
#include "game/kujuui.h"

// Its data definitions (PLAN M5), in the image's address order.
// 0x0042D0D8
namespace kujuUI
{
RwReal dword_42D0D8 = 0.5f;
}
// 0x0042D0DC
namespace kujuUI
{
RwReal dword_42D0DC = 0.25f;
}
// 0x00504370
namespace kujuUI { RwRaster *dword_504370; }
// End of its data definitions.


using namespace kujuUI;

namespace kujuUI {
extern RwRaster *dword_504370;
extern RwReal dword_42D0D8;
extern RwReal dword_42D0DC;
}

// Its data (PLAN M5): literals, constants and tables where the image has them.
// match: ?dword_42D0D8@kujuUI@@3MA @ 0x0042D0D8
// match: ?dword_42D0DC@kujuUI@@3MA @ 0x0042D0DC

// match: ?sub_1EF040@kujuUI@@YAPAURwRaster@@XZ @ 0x001EF040

RwRaster *kujuUI::sub_1EF040()
{
    if (!dword_504370)
        dword_504370 = RwRasterCreate(4, 4, 32, rwRASTERTYPETEXTURE);
    return dword_504370;
}

// match: ??0type_1EF160@kujuUI@@QAE@XZ @ 0x001EF070
type_1EF160::type_1EF160()
{
    unk_00 = 0.0f;
    unk_05 = false;
}

// match: ?sub_1EF090@type_1EF160@kujuUI@@QAE_NM@Z @ 0x001EF090
bool type_1EF160::sub_1EF090(RwReal arg_0)
{
    bool var_1 = false;
    unk_00 += arg_0;
    if (unk_05)
    {
        if (unk_00 > dword_42D0D8)
        {
            unk_00 -= dword_42D0D8;
            var_1 = true;
            unk_05 = true;
        }
    }
    else if (unk_00 > dword_42D0DC)
    {
        unk_00 -= dword_42D0DC;
        var_1 = true;
    }
    return var_1;
}

// match: ?sub_1EF120@type_1EF160@kujuUI@@QAEXXZ @ 0x001EF120
void type_1EF160::sub_1EF120()
{
    unk_04 = true;
}

// match: ?sub_1EF140@type_1EF160@kujuUI@@QAEXXZ @ 0x001EF140
void type_1EF160::sub_1EF140()
{
    unk_04 = false;
    unk_00 = 0.0f;
}

// match: ?sub_1EF160@type_1EF160@kujuUI@@QAE_NXZ @ 0x001EF160
bool type_1EF160::sub_1EF160()
{
    return unk_04;
}

// match: ?sub_1EF180@type_1EF160@kujuUI@@QAEHXZ @ 0x001EF180
RwInt32 type_1EF160::sub_1EF180()
{
    RwReal var_4 = unk_00 - dword_42D0D8;
    if (var_4 >= 0.0f)
    {
        RwReal var_8;
        return (RwInt32)(RwReal)floor(var_8 = var_4 / dword_42D0DC);
    }
    return 0;
}

// Functions /OPT:ICF folded into another body (config/aliases.txt), defined here for the
// authentic link (PLAN M7) with that body; the placement link takes the folded one.

// ??1type_1EF160@kujuUI@@QAE@XZ (folded into 0x1E41C0)
kujuUI::type_1EF160::~type_1EF160()
{
}
