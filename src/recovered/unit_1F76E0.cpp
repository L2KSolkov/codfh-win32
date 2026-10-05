/*
 * kujuUI's widget (game/kujuui.h): its constructor, destructor and focus; the
 * interface's root widget and its update and drawing each frame; and the
 * widget factory's building of a widget from a scope (game/kujuilayout.h).
 */
#include "game/kujuilayout.h"
#include "game/startup.h"
#include "rw/baengine.h"
#include "rws/gftime.h"

// Its data definitions (PLAN M5), in the image's address order.
// 0x0050438C
namespace kujuUI { bool byte_50438C; }
// 0x00504390
namespace kujuUI { type_3E7D08 *dword_504390; }
// 0x00504394
namespace kujuUI { RwUInt32 dword_504394; }
// 0x00504398
namespace kujuUI { RwRGBA unk_504398; }
// End of its data definitions.


using namespace kujuUI;

// Its data (PLAN M5): literals, constants and tables where the image has them.
// match: ??_7type_3E7D08@kujuUI@@6B@ @ 0x003E7D08
// match: ??_C@_0BN@CMBFHNNN@Failed?5to?5create?5widget?5?$CFs?4?6?$AA@ @ 0x003E7D38
// match: ??_C@_0CI@PCJCPKE@Failed?5to?5create?5widget?5?$CFs?0?5name@ @ 0x003E7D58
// match: __ehhandler$?sub_1F77D0@kujuUI@@YAXPAURwCamera@@_N@Z>1>8 @ 0x004213F4
// match: __ehhandler$?sub_1F77D0@kujuUI@@YAXPAURwCamera@@_N@Z>1 @ 0x004213FC

// match: ??0type_3E7D08@kujuUI@@QAE@PAU01@@Z @ 0x001F76E0

type_3E7D08::type_3E7D08(type_3E7D08 *arg_0) : unk_04(arg_0), unk_08(false)
{
}

// match: ?sub_1F7720@type_3E7D08@kujuUI@@QAE_NXZ @ 0x001F7720
bool type_3E7D08::sub_1F7720()
{
    return unk_08;
}

// match: ??1type_3E7D08@kujuUI@@UAE@XZ @ 0x001F7740
type_3E7D08::~type_3E7D08()
{
}

// match: ?sub_1F7760@kujuUI@@YAPAUtype_3E7D08@1@XZ @ 0x001F7760
type_3E7D08 *kujuUI::sub_1F7760()
{
    return dword_504390;
}

// match: ?sub_1F7770@kujuUI@@YAXPAUtype_3E7D08@1@@Z @ 0x001F7770
void kujuUI::sub_1F7770(type_3E7D08 *arg_0)
{
    dword_504390 = arg_0;
    dword_504394 = RWS::Time::GetTime();
}

// match: ?sub_1F7790@type_3E7D08@kujuUI@@QAEXXZ @ 0x001F7790
void type_3E7D08::sub_1F7790()
{
    unk_08 = true;
    givenFocus();
}

// match: ?sub_1F77B0@type_3E7D08@kujuUI@@QAEXXZ @ 0x001F77B0
void type_3E7D08::sub_1F77B0()
{
    unk_08 = false;
    lostFocus();
}

// match: ?sub_1F77D0@kujuUI@@YAXPAURwCamera@@_N@Z @ 0x001F77D0
// match: __ehhandler$?sub_1F77D0@kujuUI@@YAXPAURwCamera@@_N@Z-0xB @ 0x00304A90
// match: __ehhandler$?sub_1F77D0@kujuUI@@YAXPAURwCamera@@_N@Z @ 0x00304A9B
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void kujuUI::sub_1F77D0(RwCamera *arg_0, bool arg_4)
{
    byte_50438C = true;
    if (dword_504390)
    {
        RwUInt32 loc18 = RWS::Time::GetTime();
        RwUInt32 stk_14 = loc18 - dword_504394;
        RwReal local_10 = stk_14 / 1000.0f;
        if (arg_4)
        {
            RwCameraClear(arg_0, &unk_504398, 3);
            RwCameraBeginUpdate(arg_0);
        }
        type_1E4130 var_D4;
        var_D4.pDtor();
        dword_504390->vf_014(local_10);
        dword_504390->vf_018(&var_D4);
        sub_1B18D0()->sub_1B00F0();
        var_D4.sub_1E41D0();
        if (arg_4)
        {
            RwCameraEndUpdate(arg_0);
            RwCameraShowRaster(arg_0, 0, 1);
        }
        dword_504394 = loc18;
    }
    byte_50438C = false;
}

// match: ?vf_01C@type_3E7D08@kujuUI@@UAE_NHH@Z @ 0x001F7920
bool type_3E7D08::vf_01C(RwInt32 arg_0, RwInt32 arg_4)
{
    if (unk_04)
        return unk_04->vf_01C(arg_0, arg_4);
    return false;
}

// match: ?sub_1F7960@type_1F2A00@kujuUI@@QAEXPAUtype_1C8DF0@2@PAU?$type_1EFCF0@Utype_1E3BA0@kujuUI@@@2@PAU?$type_1EFCF0@Utype_1E6350@@@2@PAUtype_1ED670@2@PAUtype_3E7D08@2@PAPAU72@@Z @ 0x001F7960
// The creators take the looks and the font sets as integers (their slot 2's
// declared types).
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void type_1F2A00::sub_1F7960(type_1C8DF0 *arg_0, type_1EFCF0<type_1E3BA0> *arg_4, type_1EFCF0<type_1E6350> *arg_8,
                             type_1ED670 *arg_C, type_3E7D08 *arg_10, type_3E7D08 **arg_14)
{
    *arg_14 = 0;
    const RwChar *varC = arg_0->sub_1C8FE0()->sub_1CA280();
    type_3E7D94 *var_4 = unk_00.sub_1ED670(varC);
    RwInt32 v8 = sub_1F8000();
    if (var_4)
    {
        var_4->vf_008(arg_0, (RwInt32)arg_4, (RwInt32)arg_8, arg_C, arg_10, arg_14);
        if (!*arg_14)
        {
            if (arg_0->sub_1C8FC0())
            {
                if (0)
                {
                    sub_1C8A30("Failed to create widget %s, name \"%s\".\n", varC, arg_0->sub_1C8FC0());
                }
            }
            else
            {
                if (0)
                {
                    sub_1C8A30("Failed to create widget %s.\n", varC);
                }
            }
        }
    }
}

// Functions /OPT:ICF folded into another body (config/aliases.txt), defined here for the
// authentic link (PLAN M7) with that body; the placement link takes the folded one.

// ?vf_008@type_3E7D08@kujuUI@@UAEXXZ (folded into 0x1E41C0)
void kujuUI::type_3E7D08::vf_008()
{
}

// ?vf_00C@type_3E7D08@kujuUI@@UAEXXZ (folded into 0x1E41C0)
void kujuUI::type_3E7D08::vf_00C()
{
}

// Functions /OPT:ICF folded into another body (config/aliases.txt), defined here for the
// authentic link (PLAN M7) with that body; the placement link takes the folded one.

// ?vf_024@type_3E7D08@kujuUI@@UAEHXZ (folded into 0x1E4CB0)
RwInt32 kujuUI::type_3E7D08::vf_024()
{
        return 0;
    }

// Functions /OPT:ICF folded into another body (config/aliases.txt), defined here for the
// authentic link (PLAN M7) with that body; the placement link takes the folded one.

// ?sub_1E3480@type_3E7D08@kujuUI@@QBEPAU12@XZ (folded into 0x1E3480)
struct kujuUI::type_3E7D08 * kujuUI::type_3E7D08::sub_1E3480() const
{
    return unk_04;
}
