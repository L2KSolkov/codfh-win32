// kujuUI's combobox creator (type_3E6FA4): split from unit_1E2160.cpp at 0x1E2BC0, where the image
// ends that object (its deferred functions come before the next out-of-line one; PLAN M7).

#include "game/kujuui.h"
#include "game/frontend.h"
#include "game/parsedfile.h"
#include "types/type_4D1DB8.h"

// match: __ehhandler$?vf_008@type_3E6FA4@kujuUI@@UAEXPAUtype_1C8DF0@2@HHPAUtype_1ED670@2@PAUtype_3E7D08@2@PAPAU52@@Z>1>8 @ 0x0041FEBC
// match: __ehhandler$?vf_008@type_3E6FA4@kujuUI@@UAEXPAUtype_1C8DF0@2@HHPAUtype_1ED670@2@PAUtype_3E7D08@2@PAPAU52@@Z>1 @ 0x0041FEF4
// match: ??_Gtype_3E6FA4@kujuUI@@UAEPAXI@Z @ 0x001E2BE0
// match: ??_7type_3E6FA4@kujuUI@@6B@ @ 0x003E6FA4
// match: ??_C@_08PEKOMHKE@combobox?$AA@ @ 0x003E6FB4
// match: ??_C@_0BH@GOKPFBMM@Combobox?5?9?5missing?5?$CFs?6?$AA@ @ 0x003E6FC0
// match: ??_C@_0BP@BCEMPIEC@Combobox?5?9?5font?5not?5found?3?5?$CFs?6?$AA@ @ 0x003E6FD8
// match: ??_C@_0N@HCALHJKH@cycle_updown?$AA@ @ 0x003E6FF8
// match: ??_C@_0P@HOLLIION@cycle_sideways?$AA@ @ 0x003E7008
// match: ??_C@_0BA@ENOEGEJL@cycle_shoulders?$AA@ @ 0x003E7018
// match: ??_C@_0N@LGAPIFGH@cycle_select?$AA@ @ 0x003E7028
// match: ??_C@_06CHGOAPND@prefix?$AA@ @ 0x003E7038
// match: ??_C@_07HEDKBPOE@postfix?$AA@ @ 0x003E7040
// match: ??_C@_09PMBFCLAK@promptpos?$AA@ @ 0x003E7048
// match: ??_C@_0L@FACEBCMG@promptfont?$AA@ @ 0x003E7054
// match: ??_C@_0BA@PLNFGBMG@promptalignleft?$AA@ @ 0x003E7060
// match: ??_C@_0BC@CONCMCCH@promptaligncentre?$AA@ @ 0x003E7070
// match: ??_C@_0BB@GIADLNIN@promptalignright?$AA@ @ 0x003E7084

// match: .CRT$XCU+0 @ 0x0042723C
// match: .CRT$XCU+4 @ 0x00427240
// match: .CRT$XCU+8 @ 0x00427244
// match: .CRT$XCU+12 @ 0x00427248
// match: .CRT$XCU+16 @ 0x0042724C
// match: .CRT$XCU+20 @ 0x00427250
// match: .CRT$XCU+24 @ 0x00427254
// match: .CRT$XCU+28 @ 0x00427258
// match: .CRT$XCU+32 @ 0x0042725C
// match: .CRT$XCU+36 @ 0x00427260
// match: .CRT$XCU+40 @ 0x00427264
// match: _$E1 @ 0x0030C9F0
// match: _$E2 @ 0x0030EC10
// match: _$E4 @ 0x0030CA30
// match: _$E5 @ 0x0030EC20
// match: _$E7 @ 0x0030CA70
// match: _$E8 @ 0x0030EC30
// match: _$E10 @ 0x0030CAB0
// match: _$E11 @ 0x0030EC40
// match: _$E13 @ 0x0030CAF0
// match: _$E14 @ 0x0030EC50
// match: _$E16 @ 0x0030CB30
// match: _$E17 @ 0x0030EC60
// match: _$E19 @ 0x0030CB70
// match: _$E20 @ 0x0030EC70
// match: _$E22 @ 0x0030CBB0
// match: _$E23 @ 0x0030EC80
// match: _$E25 @ 0x0030CBF0
// match: _$E26 @ 0x0030EC90
// match: _$E28 @ 0x0030CC30
// match: _$E29 @ 0x0030ECA0
// match: _$E31 @ 0x0030CC70
// match: _$E32 @ 0x0030ECB0

namespace kujuUI
{
// match: ??0type_3E6FA4@kujuUI@@QAE@XZ @ 0x001E2BC0
type_3E6FA4::type_3E6FA4()
{
}
// match: ??1type_3E6FA4@kujuUI@@UAE@XZ @ 0x001E2C10
type_3E6FA4::~type_3E6FA4()
{
}
// match: ?vf_004@type_3E6FA4@kujuUI@@UAEPBDXZ @ 0x001E2C30
const RwChar *type_3E6FA4::vf_004()
{
    return "combobox";
}

// The combobox's values (static type_1C9590s defined with the file's
// data, and the shared ones given by functions).
extern type_1C9590 unk_50331C;
extern type_1C9590 unk_503348;
extern type_1C9590 unk_503374;
extern type_1C9590 unk_5033A0;
extern type_1C9590 unk_5033CC;
extern type_1C9590 unk_5033F8;
extern type_1C9590 unk_503424;
extern type_1C9590 unk_503450;
extern type_1C9590 unk_50347C;
extern type_1C9590 unk_5034A8;
extern type_1C9590 unk_5034D4;
// match: ?vf_008@type_3E6FA4@kujuUI@@UAEXPAUtype_1C8DF0@2@HHPAUtype_1ED670@2@PAUtype_3E7D08@2@PAPAU52@@Z @ 0x001E2C40
// match: __ehhandler$?vf_008@type_3E6FA4@kujuUI@@UAEXPAUtype_1C8DF0@2@HHPAUtype_1ED670@2@PAUtype_3E7D08@2@PAPAU52@@Z-0x65 @ 0x00303900
// match: __ehhandler$?vf_008@type_3E6FA4@kujuUI@@UAEXPAUtype_1C8DF0@2@HHPAUtype_1ED670@2@PAUtype_3E7D08@2@PAPAU52@@Z @ 0x00303965
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void type_3E6FA4::vf_008(type_1C8DF0 *arg_0, RwInt32 arg_4, RwInt32 arg_8, type_1ED670 *arg_C, type_3E7D08 *arg_10,
                         type_3E7D08 **arg_14)
{
    type_1E0330_rect var_24(0, 0, 0, 0);
    RwInt32 var_14;
    const RwChar *lv_10;

    if (sub_1F7D80(arg_0, arg_4, &lv_10) == 1 && sub_1F7B10(arg_0, lv_10, &var_24) == 1 &&
        sub_1F7E70(arg_0, arg_8, &var_14) == 1)
    {
        type_1E34A0 *var80 = 0;
        type_1C8DF0_104 *frm_3C = arg_0->sub_1C90B0(sub_1E35A0());
        RwInt32 local_30 = 0;

        if (arg_0->sub_1C90B0(&unk_5033F8))
            local_30 = 1;
        else if (arg_0->sub_1C90B0(&unk_503450))
            local_30 = 3;
        else if (arg_0->sub_1C90B0(&unk_503348))
            local_30 = 2;
        const RwChar *stk_2C = 0;
        const RwChar *local_44 = 0;
        type_1C8DF0_104 *local_40 = arg_0->sub_1C90B0(&unk_50347C);
        type_1C8DF0_104 *var_34 = arg_0->sub_1C90B0(&unk_50331C);

        if (local_40)
            stk_2C = (const RwChar *)local_40->sub_1C9890(0)->sub_1E3480();
        if (var_34)
            local_44 = (const RwChar *)var_34->sub_1C9890(0)->sub_1E3480();
        if (frm_3C)
        {
            RwInt32 var_84 = frm_3C->sub_1C9890(0)->sub_1E3480();

            arg_C->sub_1E0D50(var_84, 1, &var80);
        }
        sub_1F7A60(arg_0, "a source");
        if (!frm_3C)
        {
            if (CODFH_DEBUG_LOGS)
                sub_1C8A30("Widget factory - source missing! Widget \"%s\" type \"%s\"\n",
                           arg_0->sub_1C8FC0() ? arg_0->sub_1C8FC0() : "(none)", arg_0->sub_1C8FE0()->sub_1CA280());
        }
        sub_1F7A60(frm_3C != 0, "");
        type_1C8DF0_104 *var28 = arg_0->sub_1C90B0(sub_1E3550());
        type_1CB670 p78;
        RwUInt32 slot_48 = 0;
        type_1E0330_rect var_58;
        RwUInt32 local_7C;

        if (var28)
        {
            type_1C8DF0_104 *local_8C = arg_0->sub_1C90B0(&unk_5034D4);
            type_1C8DF0_104 *stk_88 = arg_0->sub_1C90B0(&unk_5033CC);
            RwInt32 var_90 = sub_1F7F40(arg_0, &unk_5033CC, arg_8, &slot_48);

            if (var_90 != 1)
            {
                if (CODFH_DEBUG_LOGS)
                    sub_1C8A30("Combobox - font not found: %s\n", unk_5033CC.unk_00);
            }
            if (local_8C && slot_48)
            {
                p78 = type_1CB670((const RwChar *)var28->sub_1C9890(0)->sub_1E3480(), 0);
                var_58 = type_1E0330_rect((RwReal)local_8C->sub_1C9890(0)->sub_1E3480(),
                                         (RwReal)local_8C->sub_1C9890(1)->sub_1E3480(),
                                         (RwReal)local_8C->sub_1C9890(2)->sub_1E3480(),
                                         (RwReal)local_8C->sub_1C9890(3)->sub_1E3480());
                local_7C = arg_0->sub_1C90B0(&unk_5034A8) ? 0 : arg_0->sub_1C90B0(&unk_5033A0) ? 2 : 1;
            }
            else
            {
                if (CODFH_DEBUG_LOGS)
                    sub_1C8A30("Combobox - missing %s\n", unk_5034D4.unk_00);
            }
        }
        RwInt32 lv_38 = arg_0->sub_1C90B0(sub_1E3570()) ? 0 : arg_0->sub_1C90B0(sub_1E3590()) ? 2 : 1;

        *arg_14 = new type_3E6F74(lv_10, &var_24, sub_1F7FE0(arg_0), var80, type_1CB670(stk_2C, 0),
                                  type_1CB670(local_44, 0), var_14, p78.empty() ? 0 : &p78, &var_58, &local_7C, slot_48,
                                  lv_38, local_30, arg_10);
        sub_1F7CC0(arg_0, arg_C, static_cast<type_3E76B4 *>(*arg_14));
        sub_1F7DB0(arg_0, arg_C, static_cast<type_3E76B4 *>(*arg_14));
    }
}
// match: ?vf_00C@type_3E6FA4@kujuUI@@UAEXPAVcScopeValidator@2@@Z @ 0x001E3320
void type_3E6FA4::vf_00C(cScopeValidator *arg_0)
{
    arg_0->sub_1CA1A0(sub_1E3700());
    arg_0->sub_1CA1A0(sub_1E3720());
    arg_0->sub_1C9F50(sub_1E35A0());
    arg_0->sub_1C9F50(sub_1E3560());
    arg_0->sub_1C9F50(sub_1E3570());
    arg_0->sub_1C9F50(sub_1E3580());
    arg_0->sub_1C9F50(sub_1E3590());
    arg_0->sub_1C9F50(&unk_50347C);
    arg_0->sub_1C9F50(&unk_50331C);
    arg_0->sub_1C9F50(&unk_503424);
    arg_0->sub_1C9F50(&unk_5033F8);
    arg_0->sub_1C9F50(&unk_503450);
    arg_0->sub_1C9F50(&unk_503348);
    arg_0->sub_1C9F50(&unk_5034D4);
    arg_0->sub_1C9F50(sub_1E3550());
    arg_0->sub_1C9F50(&unk_5033CC);
    arg_0->sub_1C9F50(&unk_5034A8);
    arg_0->sub_1C9F50(&unk_503374);
    arg_0->sub_1C9F50(&unk_5033A0);
}

// The value definitions and scope validators, built by their dynamic
// initializers (their exit functions call the out-of-line destructors).
type_1C9590 unk_503424("cycle_updown", 0, 0, 0, 0, 0, 0, 0, 0);
type_1C9590 unk_5033F8("cycle_sideways", 0, 0, 0, 0, 0, 0, 0, 0);
type_1C9590 unk_503450("cycle_shoulders", 0, 0, 0, 0, 0, 0, 0, 0);
type_1C9590 unk_503348("cycle_select", 0, 0, 0, 0, 0, 0, 0, 0);
type_1C9590 unk_50347C("prefix", 1, 0, 0, 0, 0, 0, 0, 0);
type_1C9590 unk_50331C("postfix", 1, 0, 0, 0, 0, 0, 0, 0);
type_1C9590 unk_5034D4("promptpos", 3, 3, 3, 3, 0, 0, 0, 0);
type_1C9590 unk_5033CC("promptfont", 1, 0, 0, 0, 0, 0, 0, 0);
type_1C9590 unk_5034A8("promptalignleft", 0, 0, 0, 0, 0, 0, 0, 0);
type_1C9590 unk_503374("promptaligncentre", 0, 0, 0, 0, 0, 0, 0, 0);
type_1C9590 unk_5033A0("promptalignright", 0, 0, 0, 0, 0, 0, 0, 0);
}
