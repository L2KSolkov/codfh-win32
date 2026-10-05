/*
 * The game browser's rows (game/browser.h): a list box row over a session,
 * its name, the browser's sort mode and two string helpers, its texts
 * (sub_1FB7B0) and the rows' order (sub_1FB5A0), whose names' strings call
 * the library's const char * constructor out of line (placed at 0x1C5700).
 */
#include "game/browser.h"
#include "types/type_4D1DB8.h"
#include "game/mpgame.h"
#include "game/uiglue.h"

// Its data definitions (PLAN M5), in the image's address order.
// 0x003E7E34
extern const RwReal flt_3E7E34 = 0.01f;
// 0x003E7E38
extern const RwReal flt_3E7E38 = 0.01f;
// 0x003E7E3C
extern const RwReal flt_3E7E3C = 0.01f;
// 0x003E7E40
extern const RwReal flt_3E7E40 = 0.01f;
// 0x003E7E44
extern const RwReal flt_3E7E44 = 16.666666f;
// 0x005043AC
RwInt32 dword_5043AC;
// End of its data definitions.


using namespace kujuUI;

// Vtables (.rdata, PLAN M5): each in its own placement range (config/splits.txt).
// Its data (PLAN M5): literals, constants and tables where the image has them.
// match: ?flt_3E7E34@@3MB @ 0x003E7E34
// match: ?flt_3E7E38@@3MB @ 0x003E7E38
// match: ?flt_3E7E3C@@3MB @ 0x003E7E3C
// match: ?flt_3E7E40@@3MB @ 0x003E7E40
// match: ?flt_3E7E44@@3MB @ 0x003E7E44
// match: ??_7type_1FB520@@6B@ @ 0x003E7E48
// match: ??_C@_08MBODEPG@Host?5new?$AA@ @ 0x003E7E50
// match: __ehhandler$?sub_1FB5A0@type_1FB520@@QAE_NABU1@@Z>1>8 @ 0x004214D4
// match: __ehhandler$?sub_1FB5A0@type_1FB520@@QAE_NABU1@@Z>1 @ 0x004214E4
// match: __ehhandler$?vf_004@type_1FB520@@UAEXXZ>1>8 @ 0x00421500
// match: __ehhandler$?vf_004@type_1FB520@@UAEXXZ>1 @ 0x00421548
// match: __ehhandler$?sub_1FBB90@type_1A5EA0@@QAEAAU1@Utype_1CB670@@@Z>1>8 @ 0x00421564
// match: __ehhandler$?sub_1FBB90@type_1A5EA0@@QAEAAU1@Utype_1CB670@@@Z>1 @ 0x0042156C

// match: ??0type_1FB520@@QAE@PAUtype_1FB520_session@@@Z @ 0x001FB520

type_1FB520::type_1FB520(type_1FB520_session *arg_0) : unk_40(arg_0)
{
}

// match: ??_Gtype_1FB520@@UAEPAXI@Z @ 0x001FB550

// match: ??1type_1FB520@@UAE@XZ @ 0x001FB580

// match: ?sub_1FB5A0@type_1FB520@@QAE_NABU1@@Z @ 0x001FB5A0
// match: __ehhandler$?sub_1FB5A0@type_1FB520@@QAE_NABU1@@Z-0x10 @ 0x00304B70
// match: __ehhandler$?sub_1FB5A0@type_1FB520@@QAE_NABU1@@Z @ 0x00304B80
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
bool type_1FB520::sub_1FB5A0(const type_1FB520 &arg_0)
{
    if (unk_40 && arg_0.unk_40)
    {
        switch (dword_5043AC)
        {
        case 0:
        {
            type_1A5EA0 q48(unk_40->unk_10);
            type_1A5EA0 stk_2C(arg_0.unk_40->unk_10);

            return q48 < stk_2C;
        }
        case 1:
            return unk_40->unk_28 < arg_0.unk_40->unk_28;
        case 2:
            return unk_40->unk_29 < arg_0.unk_40->unk_29;
        case 3:
            return unk_40->unk_2B < arg_0.unk_40->unk_2B;
        }
    }
    return unk_40 == 0;
}

// The library's string constructor from a C string, out of line here.
// match: ??0?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@QAE@PBD@Z @ 0x001C5700

// match: ?sub_1FB760@type_1FB520@@QAE?AUtype_1A5EA0@@XZ @ 0x001FB760
type_1A5EA0 type_1FB520::sub_1FB760()
{
    return type_1A5EA0(unk_40 ? unk_40->unk_10 : "");
}

// Its texts: the session's name, game type, level and players ("n/most");
// with no session, the player's name and "Host new".
// match: ?vf_004@type_1FB520@@UAEXXZ @ 0x001FB7B0
// match: __ehhandler$?vf_004@type_1FB520@@UAEXXZ-0x5A @ 0x00304B90
// match: __ehhandler$?vf_004@type_1FB520@@UAEXXZ @ 0x00304BEA
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void type_1FB520::vf_004()
{
    if (unk_40)
    {
        const RwChar *v34 = sub_1A3CB0(unk_40->unk_2B);
        const RwChar *l38 = sub_1C4590(unk_40->unk_28);

        sub_1EC2C0(sub_1CB720(unk_40->unk_10), 0);
        sub_1EC2C0(type_1CB670(v34, 0), 1);
        sub_1EC2C0(type_1CB670(l38, 0), 2);
        type_1CB670 lv_2C;
        RwUInt8 local_2D = unk_40->unk_29;

        if (local_2D > unk_40->unk_2A)
            local_2D = unk_40->unk_2A;
        lv_2C.sub_1FBB70(local_2D).sub_1FBB90(*sub_1CBB30()).sub_1FBB70(unk_40->unk_2A);
        sub_1EC2C0(lv_2C, 3);
    }
    else
    {
        sub_1EC2C0(sub_1CB720(sub_1C42E0()), 0);
        sub_1EC2C0(type_1CB670(), 2);
        sub_1EC2C0(type_1CB670("Host new", 0), 1);
        sub_1EC2C0(type_1CB670(), 3);
    }
}

// match: ?sub_1FBB50@@YAHXZ @ 0x001FBB50
RwInt32 sub_1FBB50()
{
    return dword_5043AC;
}

// match: ?sub_1FBB60@@YAXH@Z @ 0x001FBB60
void sub_1FBB60(RwInt32 arg_0)
{
    dword_5043AC = arg_0;
}

// match: ?sub_1FBB70@type_1A5EA0@@QAEAAU1@E@Z @ 0x001FBB70
type_1A5EA0 &type_1A5EA0::sub_1FBB70(RwUInt8 arg_0)
{
    sub_1C8540(arg_0);
    return *this;
}

// match: ?sub_1FBB90@type_1A5EA0@@QAEAAU1@Utype_1CB670@@@Z @ 0x001FBB90
// match: __ehhandler$?sub_1FBB90@type_1A5EA0@@QAEAAU1@Utype_1CB670@@@Z-0x8 @ 0x00304C00
// match: __ehhandler$?sub_1FBB90@type_1A5EA0@@QAEAAU1@Utype_1CB670@@@Z @ 0x00304C08
type_1A5EA0 &type_1A5EA0::sub_1FBB90(type_1CB670 arg_0)
{
    sub_1C84F0(arg_0);
    return *this;
}

// Functions /OPT:ICF folded into another body (config/aliases.txt), defined here for the
// authentic link (PLAN M7) with that body; the placement link takes the folded one.

// ?sub_21D030@type_1FB520@@QAEPAUtype_1FB520_session@@XZ (folded into 0x21D030)
struct type_1FB520_session *type_1FB520::sub_21D030()
{
    return unk_40;
}
