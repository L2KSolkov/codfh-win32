// kujuUI's edit box creator (type_3E7284): split from unit_1E4250.cpp at 0x1E4D30, where the image
// ends that object (its deferred functions come before the next out-of-line one; PLAN M7).

#include "game/kujuui.h"
#include "game/parsedfile.h"
#include "game/frontend.h"
#include "types/type_4D1DB8.h"

// match: __ehhandler$?vf_008@type_3E7284@kujuUI@@UAEXPAUtype_1C8DF0@2@HHPAUtype_1ED670@2@PAUtype_3E7D08@2@PAPAU52@@Z>1>8 @ 0x00420004
// match: __ehhandler$?vf_008@type_3E7284@kujuUI@@UAEXPAUtype_1C8DF0@2@HHPAUtype_1ED670@2@PAUtype_3E7D08@2@PAPAU52@@Z>1 @ 0x0042000C
// match: ??_Gtype_3E7284@kujuUI@@UAEPAXI@Z @ 0x001E4D50
// match: ??_7type_3E7284@kujuUI@@6B@ @ 0x003E7284
// match: ??_C@_07GLMELOEJ@editbox?$AA@ @ 0x003E7294
// match: ??_C@_09BIBCMMCI@caretcomp?$AA@ @ 0x003E729C
// match: ??_C@_0N@FMNDNGPA@keyboardcomp?$AA@ @ 0x003E72A8
// match: ??_C@_0BB@FEODBMLC@keyboardeditcomp?$AA@ @ 0x003E72B8
// match: ??_C@_0N@ENLGDPDD@fontkeyboard?$AA@ @ 0x003E72CC
// match: ??_C@_0BB@JOJIBFMF@fontkeyboardedit?$AA@ @ 0x003E72DC
// match: ??_C@_09HDEFFHJH@caretsize?$AA@ @ 0x003E72F0
// match: ??_C@_08IAMDPENO@maxchars?$AA@ @ 0x003E72FC

// match: .CRT$XCU+0 @ 0x00427304
// match: .CRT$XCU+4 @ 0x00427308
// match: .CRT$XCU+8 @ 0x0042730C
// match: .CRT$XCU+12 @ 0x00427310
// match: .CRT$XCU+16 @ 0x00427314
// match: .CRT$XCU+20 @ 0x00427318
// match: .CRT$XCU+24 @ 0x0042731C
// match: _$E1 @ 0x0030D640
// match: _$E2 @ 0x0030EF30
// match: _$E4 @ 0x0030D680
// match: _$E5 @ 0x0030EF40
// match: _$E7 @ 0x0030D6C0
// match: _$E8 @ 0x0030EF50
// match: _$E10 @ 0x0030D700
// match: _$E11 @ 0x0030EF60
// match: _$E13 @ 0x0030D740
// match: _$E14 @ 0x0030EF70
// match: _$E16 @ 0x0030D780
// match: _$E17 @ 0x0030EF80
// match: _$E19 @ 0x0030D7C0
// match: _$E20 @ 0x0030EF90

namespace kujuUI
{
// match: ??0type_3E7284@kujuUI@@QAE@XZ @ 0x001E4D30
type_3E7284::type_3E7284()
{
}
// match: ??1type_3E7284@kujuUI@@UAE@XZ @ 0x001E4D80
type_3E7284::~type_3E7284()
{
}
// match: ?vf_004@type_3E7284@kujuUI@@UAEPBDXZ @ 0x001E4DA0
const RwChar *type_3E7284::vf_004()
{
    return "editbox";
}

// The editbox's values (static type_1C9590s, built by the file's dynamic
// initializers), by the names their initializers give them: "fontkeyboard",
// "caretsize", "keyboardcomp", "caretcomp", "keyboardeditcomp",
// "fontkeyboardedit" and "maxchars".
extern type_1C9590 unk_503E9C;
extern type_1C9590 unk_503EC8;
extern type_1C9590 unk_503EF4;
extern type_1C9590 unk_503F20;
extern type_1C9590 unk_503F4C;
extern type_1C9590 unk_503F78;
extern type_1C9590 unk_503FA4;
// match: ?vf_008@type_3E7284@kujuUI@@UAEXPAUtype_1C8DF0@2@HHPAUtype_1ED670@2@PAUtype_3E7D08@2@PAPAU52@@Z @ 0x001E4DB0
// match: __ehhandler$?vf_008@type_3E7284@kujuUI@@UAEXPAUtype_1C8DF0@2@HHPAUtype_1ED670@2@PAUtype_3E7D08@2@PAPAU52@@Z-0xB @ 0x00303A80
// match: __ehhandler$?vf_008@type_3E7284@kujuUI@@UAEXPAUtype_1C8DF0@2@HHPAUtype_1ED670@2@PAUtype_3E7D08@2@PAPAU52@@Z @ 0x00303A8B
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void type_3E7284::vf_008(type_1C8DF0 *arg_0, RwInt32 arg_4, RwInt32 arg_8, type_1ED670 *arg_C, type_3E7D08 *arg_10,
                         type_3E7D08 **arg_14)
{
    type_1E0330_rect v38(0, 0, 0, 0);
    const RwChar *l18;
    const RwChar *v14;
    const RwChar *lv_10;
    const RwChar *x1C;
    RwInt32 var_24;
    RwUInt32 y20;
    RwUInt32 local_28;

    if (sub_1F7D80(arg_0, arg_4, &l18) == 1 && sub_1F7B10(arg_0, l18, &v38) == 1 &&
        sub_1F7E70(arg_0, arg_8, &var_24) == 1 && sub_1F7EA0(arg_0, &unk_503F20, arg_4, &v14) == 1 &&
        sub_1F7EA0(arg_0, &unk_503EF4, arg_4, &lv_10) == 1 && sub_1F7EA0(arg_0, &unk_503F4C, arg_4, &x1C) == 1 &&
        sub_1F7F40(arg_0, &unk_503E9C, arg_8, &y20) == 1 && sub_1F7F40(arg_0, &unk_503F78, arg_8, &local_28) == 1)
    {
        type_1C8DF0_104 *stk_64 = arg_0->sub_1C90B0(&unk_503FA4);
        RwInt32 var_48 = stk_64 ? stk_64->sub_1C9890(0)->sub_1E3480() : 0xFF;
        type_1C8DF0_104 *l3C = arg_0->sub_1C90B0(&unk_503EC8);
        type_1E0330_rect var_60(0, 0, l3C ? l3C->sub_1C9890(0)->sub_1E3480() : 4,
                                l3C ? l3C->sub_1C9890(1)->sub_1E3480() : 15);
        type_1C8DF0_104 *loc44 = arg_0->sub_1C90B0(sub_1E35A0());
        type_1F28C0 *var_50 = 0;

        if (loc44)
            arg_C->sub_1E0D50(loc44->sub_1C9890(0)->sub_1E3480(), 3, &var_50);
        sub_1F7A60(arg_0, "a source");
        if (!loc44)
        {
            if (CODFH_DEBUG_LOGS)
                sub_1C8A30("Widget factory - source missing! Widget \"%s\" type \"%s\"\n",
                           arg_0->sub_1C8FC0() ? arg_0->sub_1C8FC0() : "(none)", arg_0->sub_1C8FE0()->sub_1CA280());
        }
        sub_1F7A60(loc44 != 0, "");
        type_1C8DF0_104 *var_40 = arg_0->sub_1C90B0(sub_1E3520());
        type_1ED670_object *var_4C = 0;

        if (var_40)
            arg_C->sub_1E0D50(var_40->sub_1C9890(0)->sub_1E3480(), 0, &var_4C);
        *arg_14 = new type_3E7228(l18, v14, lv_10, x1C, var_24, y20, local_28, &v38, &var_60, var_48,
                                  var_4C, 0, var_50, arg_10);
        sub_1F7CC0(arg_0, arg_C, static_cast<type_3E76B4 *>(*arg_14));
        sub_1F7DB0(arg_0, arg_C, static_cast<type_3E76B4 *>(*arg_14));
    }
}
// match: ?vf_00C@type_3E7284@kujuUI@@UAEXPAVcScopeValidator@2@@Z @ 0x001E5190
void type_3E7284::vf_00C(cScopeValidator *arg_0)
{
    arg_0->sub_1CA1A0(sub_1E3720());
    arg_0->sub_1C9F50(sub_1E3520());
    arg_0->sub_1C9F50(sub_1E34E0());
    arg_0->sub_1C9F50(sub_1E34D0());
    arg_0->sub_1C9F50(sub_1E3560());
    arg_0->sub_1C9F50(sub_1E3500());
    arg_0->sub_1C9F50(sub_1E35A0());
    arg_0->sub_1C9F50(&unk_503F20);
    arg_0->sub_1C9F50(&unk_503EF4);
    arg_0->sub_1C9F50(&unk_503F4C);
    arg_0->sub_1C9F50(&unk_503E9C);
    arg_0->sub_1C9F50(&unk_503F78);
    arg_0->sub_1C9F50(&unk_503EC8);
    arg_0->sub_1C9F50(&unk_503FA4);
}
// match: ??1type_1ED670_object@kujuUI@@UAE@XZ @ 0x001E5260
type_1ED670_object::~type_1ED670_object()
{
}

// The value definitions and scope validators, built by their dynamic
// initializers (their exit functions call the out-of-line destructors).
type_1C9590 unk_503F20("caretcomp", 1, 0, 0, 0, 0, 0, 0, 0);
type_1C9590 unk_503EF4("keyboardcomp", 1, 0, 0, 0, 0, 0, 0, 0);
type_1C9590 unk_503F4C("keyboardeditcomp", 1, 0, 0, 0, 0, 0, 0, 0);
type_1C9590 unk_503E9C("fontkeyboard", 1, 0, 0, 0, 0, 0, 0, 0);
type_1C9590 unk_503F78("fontkeyboardedit", 1, 0, 0, 0, 0, 0, 0, 0);
type_1C9590 unk_503EC8("caretsize", 3, 3, 0, 0, 0, 0, 0, 0);
type_1C9590 unk_503FA4("maxchars", 3, 0, 0, 0, 0, 0, 0, 0);
}
