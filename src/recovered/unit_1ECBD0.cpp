/*
 * kujuUI's image library (game/kujuui.h): a texture and the images in it
 * by name, read from its ".index" file, and the list of those loaded; and
 * the reference-counted pointer's release (game/kujufont.h).
 */
#include <string.h>
#include "game/kujuui.h"
#include "game/kujufont.h"
#include "game/parsedfile.h"
#include "types/type_4D1DB8.h"

// Its data definitions (PLAN M5), in the image's address order.
// 0x0042D0D0
namespace kujuUI
{
const RwChar *dword_42D0D0 = ".tga";
}
// 0x0042D0D4
namespace kujuUI
{
const RwChar *dword_42D0D4 = ".index";
}
// 0x00504220
namespace kujuUI { cScopeValidator *dword_504220; }
// 0x00504224
namespace kujuUI { type_1ECCE0 *dword_504224; }
// End of its data definitions.

// Its data (PLAN M5): literals, constants and tables where the image has them.
// match: ??_C@_06OJFGGPJP@?4index?$AA@ @ 0x003E74FC
// match: ??_7type_1ECCE0@kujuUI@@6B@ @ 0x003E7504
// match: ??_C@_0M@EGAACMIH@?5finished?4?6?$AA@ @ 0x003E7508
// match: ??_C@_04ONKFDMMC@?$CFs?0?5?$AA@ @ 0x003E7514
// match: ??_C@_0DO@CECEFFDI@?6?$CB?$CB?$CB?5tried?5to?5insert?5an?5already?5@ @ 0x003E751C
// match: ??_C@_05NGOMGBBD@image?$AA@ @ 0x003E755C
// match: ??_C@_0BN@FLAPIOAJ@Enumerating?5images?5in?5?$CC?$CFs?$CC?3?5?$AA@ @ 0x003E7564
// match: __ehhandler$??0type_1ECCE0@kujuUI@@QAE@PBDPAPAUtype_1EEEE0@@PAU01@@Z>1>8 @ 0x00420690
// match: __ehhandler$??0type_1ECCE0@kujuUI@@QAE@PBDPAPAUtype_1EEEE0@@PAU01@@Z>1 @ 0x004206A0
// match: __ehhandler$??1type_1ECCE0@kujuUI@@UAE@XZ>1>8 @ 0x004206BC
// match: __ehhandler$??1type_1ECCE0@kujuUI@@UAE@XZ>1 @ 0x004206D4
// match: __ehhandler$?sub_1ECDE0@kujuUI@@YA_NPBDPAPAUtype_1EEEE0@@@Z>1>8 @ 0x004206F0
// match: __ehhandler$?sub_1ECDE0@kujuUI@@YA_NPBDPAPAUtype_1EEEE0@@@Z>1 @ 0x00420700
// match: __ehhandler$?sub_1ED040@kujuUI@@YA?AU?$type_E8780@Utype_1ECCE0@kujuUI@@@@PBD@Z>1>8 @ 0x0042071C
// match: __ehhandler$?sub_1ED040@kujuUI@@YA?AU?$type_E8780@Utype_1ECCE0@kujuUI@@@@PBD@Z>1 @ 0x0042073C
// match: __ehhandler$?sub_1ED290@type_1ECCE0@kujuUI@@QAE_NXZ>1>8 @ 0x00420758
// match: __ehhandler$?sub_1ED290@type_1ECCE0@kujuUI@@QAE_NXZ>1 @ 0x00420770
// match: .CRT$XCU+0 @ 0x00427350
// match: .CRT$XCU+4 @ 0x00427354
// match: ?dword_42D0D0@kujuUI@@3PBDB @ 0x0042D0D0
// match: ?dword_42D0D4@kujuUI@@3PBDB @ 0x0042D0D4

// match: _$E1 @ 0x0030DA50
// match: _$E2 @ 0x0030F020
// match: _$E4 @ 0x0030DA70
// match: _$E5 @ 0x0030F030

namespace kujuUI {
extern type_1ECCE0 *dword_504224;
extern const RwChar *dword_42D0D0;
extern const RwChar *dword_42D0D4;
extern type_1C9590 unk_504228;
extern cScopeValidator unk_504258;
extern cScopeValidator *dword_504220;
}

using namespace kujuUI;

// match: ??0type_1ECCE0@kujuUI@@QAE@PBDPAPAUtype_1EEEE0@@PAU01@@Z @ 0x001ECBD0
// match: __ehhandler$??0type_1ECCE0@kujuUI@@QAE@PBDPAPAUtype_1EEEE0@@PAU01@@Z-0x13 @ 0x00303EF0
// match: __ehhandler$??0type_1ECCE0@kujuUI@@QAE@PBDPAPAUtype_1EEEE0@@PAU01@@Z @ 0x00303F03
type_1ECCE0::type_1ECCE0(const RwChar *arg_0, type_1EEEE0 **arg_4, type_1ECCE0 *arg_8) : unk_08(arg_0), unk_24(*arg_4)
{
    unk_34 = arg_8;
    unk_38 = 0.5f / unk_24->get_unk_00()->width;
    unk_3C = 0.5f / unk_24->get_unk_00()->height;
    *arg_4 = 0;
}

// match: ??_Gtype_1ECCE0@kujuUI@@UAEPAXI@Z @ 0x001ECCB0

// match: ??1type_1ECCE0@kujuUI@@UAE@XZ @ 0x001ECCE0
// match: __ehhandler$??1type_1ECCE0@kujuUI@@UAE@XZ-0x1E @ 0x00303F10
// match: __ehhandler$??1type_1ECCE0@kujuUI@@UAE@XZ @ 0x00303F2E
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
type_1ECCE0::~type_1ECCE0()
{
    delete unk_24;
    type_1ECCE0 *lv_10 = 0;
    type_1ECCE0 *var_14 = dword_504224;
    while (var_14 != this)
    {
        lv_10 = var_14;
        var_14 = var_14->unk_34;
    }
    if (lv_10)
        lv_10->unk_34 = unk_34;
    else
        dword_504224 = unk_34;
}

// match: ?sub_1ECDE0@kujuUI@@YA_NPBDPAPAUtype_1EEEE0@@@Z @ 0x001ECDE0
// match: __ehhandler$?sub_1ECDE0@kujuUI@@YA_NPBDPAPAUtype_1EEEE0@@@Z-0x19 @ 0x00303F40
// match: __ehhandler$?sub_1ECDE0@kujuUI@@YA_NPBDPAPAUtype_1EEEE0@@@Z @ 0x00303F59
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
bool kujuUI::sub_1ECDE0(const RwChar *arg_0, type_1EEEE0 **arg_4)
{
    type_1E6B50 *lv_10;
    *arg_4 = 0;
    RwUInt32 var_14 = strlen(arg_0);
    RwChar var_11C[0x100];
    memcpy(var_11C, arg_0, var_14);
    strcpy(&var_11C[var_14], dword_42D0D0);
    lv_10 = 0;
    if (!lv_10)
    {
        memcpy(var_11C, arg_0, var_14);
        strcpy(&var_11C[var_14], ".dds");
        sub_1EEFB0(var_11C, arg_4);
    }
    if (lv_10)
    {
        while (lv_10->unk_00 * lv_10->unk_04 > 512 * 512)
        {
            type_1E6B50 *var_124;
            lv_10->sub_1E7100(&var_124);
            delete lv_10;
            lv_10 = var_124;
        }
        type_1EECE0 var_120(lv_10);
        *arg_4 = new type_1EEEE0(var_120);
        delete lv_10;
    }
    return *arg_4 != 0;
}

// match: ?sub_1ED040@kujuUI@@YA?AU?$type_E8780@Utype_1ECCE0@kujuUI@@@@PBD@Z @ 0x001ED040
// match: __ehhandler$?sub_1ED040@kujuUI@@YA?AU?$type_E8780@Utype_1ECCE0@kujuUI@@@@PBD@Z-0x34 @ 0x00303F70
// match: __ehhandler$?sub_1ED040@kujuUI@@YA?AU?$type_E8780@Utype_1ECCE0@kujuUI@@@@PBD@Z @ 0x00303FA4
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
type_E8780<type_1ECCE0> kujuUI::sub_1ED040(const RwChar *arg_0)
{
    type_E8780<type_1ECCE0> var_14(type_1ECCE0::sub_1ED220(arg_0));
    if (!var_14.sub_E87C0())
        return var_14;
    type_1EEEE0 *lv_10 = 0;
    if (sub_1ECDE0(arg_0, &lv_10))
    {
        type_1ECCE0 *var_18 = new type_1ECCE0(arg_0, &lv_10, dword_504224);
        dword_504224 = var_18;
        if (var_18->sub_1ED290())
            return type_E8780<type_1ECCE0>(var_18);
        delete var_18;
    }
    return 0;
}

// match: ?sub_1ED1E0@kujuUI@@YAPBVcScopeValidator@1@XZ @ 0x001ED1E0
const cScopeValidator *kujuUI::sub_1ED1E0()
{
    if (!dword_504220)
    {
        unk_504258.sub_1C9F50(&unk_504228);
        unk_504258.sub_1CA2A0();
        dword_504220 = &unk_504258;
    }
    return dword_504220;
}

// match: ?sub_1ED220@type_1ECCE0@kujuUI@@SAPAU12@PBD@Z @ 0x001ED220
type_1ECCE0 *type_1ECCE0::sub_1ED220(const RwChar *arg_0)
{
    type_1ECCE0 *var_4 = dword_504224;
    while (var_4 && var_4->unk_08 != arg_0)
        var_4 = var_4->unk_34;
    return var_4;
}

// match: ?sub_1ED290@type_1ECCE0@kujuUI@@QAE_NXZ @ 0x001ED290
// match: __ehhandler$?sub_1ED290@type_1ECCE0@kujuUI@@QAE_NXZ-0x1E @ 0x00303FB0
// match: __ehhandler$?sub_1ED290@type_1ECCE0@kujuUI@@QAE_NXZ @ 0x00303FCE
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
bool type_1ECCE0::sub_1ED290()
{
    cParsedFile *lv_10;
    bool lv_11;
    type_1A5EA0 var_34(sub_1E72B0());
    var_34.sub_1C84F0(unk_08);
    var_34.sub_1C84F0(dword_42D0D4);
    lv_10 = 0;
    lv_11 = false;
    cParsedFile::loadBinaryFile(var_34.c_str(), sub_1ED1E0(), &lv_10);
    if (lv_10)
    {
        if (0)
            sub_1C8A30("Enumerating images in \"%s\": ", unk_08.c_str());
        lv_11 = true;
        type_1C8DF0 *var_3C = lv_10->sub_1E3480();
        RwUInt32 var_38 = var_3C->sub_1C9120();
        for (RwUInt32 var_40 = 0; var_40 != var_38 && lv_11; ++var_40)
        {
            type_1C8DF0_104 *var_44 = var_3C->sub_1C9140(var_40);
            if (!strcmp(var_44->sub_1C9870(), "image"))
            {
                type_1C8DF0_104_00 *var_48 = var_44->sub_6FCD0();
                type_1E7410 *var_4C;
                RwInt32 var_50;
                const RwChar *var_54;
                type_1E0330_rect x64(var_48[1].sub_1CA870(), var_48[2].sub_1CA870(), var_48[3].sub_1CA870(),
                                        var_48[4].sub_1CA870());
                var_54 = (const RwChar *)var_48->sub_1E3480();
                var_4C = new type_1E7410(this, &x64, var_54);
                var_50 = unk_28.sub_1E7310(var_4C->unk_00, &var_4C);
                if (!var_50)
                {
                    if (0)
                        sub_1C8A30("\n!!! tried to insert an already existing image name - %s !!!\n", var_54);
                    lv_11 = false;
                }
                else if (0)
                    sub_1C8A30("%s, ", var_54);
            }
        }
        if (0)
            sub_1C8A30(" finished.\n");
        delete lv_10;
    }
    return lv_11;
}

// match: ?sub_1ED630@type_1ECCE0@kujuUI@@QAEPAUtype_1E7410@2@PBD@Z @ 0x001ED630
type_1E7410 *type_1ECCE0::sub_1ED630(const RwChar *arg_0)
{
    return unk_28.sub_1ED670(arg_0);
}

// match: ?sub_1ED650@type_1ECCE0@kujuUI@@QAEHXZ @ 0x001ED650
RwInt32 type_1ECCE0::sub_1ED650()
{
    RwRaster *var_4 = unk_24->unk_00;
    return (RwInt32)var_4;
}

// ?sub_1ED670@type_1ED670@kujuUI@@QAEPAUtype_1ED670_object@2@H@Z (folded into 0x1ED670)
type_1ED670_object *type_1ED670::sub_1ED670(RwInt32 arg_0)
{
    type_1ED670_object *var_4 = ((type_1E0F80 *)this)->sub_1E0FC0((const RwChar *)arg_0);
    return var_4;
}

// match: ?sub_1ED670@?$type_1EFCF0@Utype_1E7410@kujuUI@@@kujuUI@@QAEPAUtype_1E7410@2@PBD@Z @ 0x001ED670

// match: ??1?$type_E8780@Utype_1ECCE0@kujuUI@@@@QAE@XZ @ 0x001ED6A0

// match: ?sub_1ED6C0@?$type_E8780@Utype_1ECCE0@kujuUI@@@@QAEXXZ @ 0x001ED6C0

namespace kujuUI
{

// The value definitions and scope validators, built by their dynamic
// initializers (their exit functions call the out-of-line destructors).
cScopeValidator unk_504258;
type_1C9590 unk_504228("image", 1, 4, 4, 4, 4, 0, 0, 0);

}
