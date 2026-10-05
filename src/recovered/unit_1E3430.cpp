/*
 * kujuUI's widget values (game/kujuui.h): the value hook's base, a value
 * part's integer, the value definitions every widget reads (static
 * type_1C9590s, built by the file's dynamic initializers) and the two
 * validators over them, built on first use.
 */
#include "game/kujuui.h"
#include "game/parsedfile.h"

// Its data definitions (PLAN M5), in the image's address order.
// 0x00503500
namespace kujuUI { bool byte_503500; }
// End of its data definitions.

// Vtables (.rdata, PLAN M5): each in its own placement range (config/splits.txt).
// Its data (PLAN M5): literals, constants and tables where the image has them.
// match: ??_7type_1E34A0@kujuUI@@6B@ @ 0x003E7098
// match: ??_7type_3E70B0@kujuUI@@6B@ @ 0x003E70B0
// match: ??_C@_08OAGMDKAF@position?$AA@ @ 0x003E70B8
// match: ??_C@_09MNAEFABN@possource?$AA@ @ 0x003E70C4
// match: ??_C@_09NILLCKIE@component?$AA@ @ 0x003E70D0
// match: ??_C@_0L@PKODIMLO@compsource?$AA@ @ 0x003E70DC
// match: ??_C@_08DIGALHJN@compback?$AA@ @ 0x003E70E8
// match: ??_C@_05BGCJMGHI@click?$AA@ @ 0x003E70F4
// match: ??_C@_05PEEJIKOE@focus?$AA@ @ 0x003E70FC
// match: ??_C@_07BPJAFMGC@unfocus?$AA@ @ 0x003E7104
// match: ??_C@_07ICAJMOAO@content?$AA@ @ 0x003E710C
// match: ??_C@_04EFPADHIC@font?$AA@ @ 0x003E7114
// match: ??_C@_09HMHPLLLL@alignleft?$AA@ @ 0x003E711C
// match: ??_C@_0M@NCEFHJPM@aligncentre?$AA@ @ 0x003E7128
// match: ??_C@_0L@EGDABKNG@alignright?$AA@ @ 0x003E7134
// match: ??_C@_06OEKOLKIL@source?$AA@ @ 0x003E7140
// match: ??_C@_05CIAMLOHJ@padup?$AA@ @ 0x003E7148
// match: ??_C@_07CNBOLFDP@paddown?$AA@ @ 0x003E7150
// match: ??_C@_07NPBKCNAG@padleft?$AA@ @ 0x003E7158
// match: ??_C@_08PDEDLAHB@padright?$AA@ @ 0x003E7160
// match: ??_C@_09ELGBPJB@padcancel?$AA@ @ 0x003E716C
// match: ??_C@_09CBMECJBO@padselect?$AA@ @ 0x003E7178
// match: ??_C@_09BFFBBMIL@losefocus?$AA@ @ 0x003E7184
// match: ??_C@_0M@IFBEJFPF@innerborder?$AA@ @ 0x003E7190
// match: ??_C@_0O@EBLPPPJP@noinnerborder?$AA@ @ 0x003E719C
// match: ??_C@_0L@DAMKPBDI@lineheight?$AA@ @ 0x003E71AC
// match: ??_C@_08KOHOCBIL@oncancel?$AA@ @ 0x003E71B8
// match: ??_C@_08ILAMBHAE@onselect?$AA@ @ 0x003E71C4
// match: ??_C@_08PPDGPLMA@onaltsel?$AA@ @ 0x003E71D0
// match: ??_C@_08NLBNECHN@onoptsel?$AA@ @ 0x003E71DC
// match: ??_C@_06KLKLDLLI@widget?$AA@ @ 0x003E71E8
// match: ??_C@_08NCKPMOJE@navigate?$AA@ @ 0x003E71F0
// match: .CRT$XCU+0 @ 0x00427268
// match: .CRT$XCU+4 @ 0x0042726C
// match: .CRT$XCU+8 @ 0x00427270
// match: .CRT$XCU+12 @ 0x00427274
// match: .CRT$XCU+16 @ 0x00427278
// match: .CRT$XCU+20 @ 0x0042727C
// match: .CRT$XCU+24 @ 0x00427280
// match: .CRT$XCU+28 @ 0x00427284
// match: .CRT$XCU+32 @ 0x00427288
// match: .CRT$XCU+36 @ 0x0042728C
// match: .CRT$XCU+40 @ 0x00427290
// match: .CRT$XCU+44 @ 0x00427294
// match: .CRT$XCU+48 @ 0x00427298
// match: .CRT$XCU+52 @ 0x0042729C
// match: .CRT$XCU+56 @ 0x004272A0
// match: .CRT$XCU+60 @ 0x004272A4
// match: .CRT$XCU+64 @ 0x004272A8
// match: .CRT$XCU+68 @ 0x004272AC
// match: .CRT$XCU+72 @ 0x004272B0
// match: .CRT$XCU+76 @ 0x004272B4
// match: .CRT$XCU+80 @ 0x004272B8
// match: .CRT$XCU+84 @ 0x004272BC
// match: .CRT$XCU+88 @ 0x004272C0
// match: .CRT$XCU+92 @ 0x004272C4
// match: .CRT$XCU+96 @ 0x004272C8
// match: .CRT$XCU+100 @ 0x004272CC
// match: .CRT$XCU+104 @ 0x004272D0
// match: .CRT$XCU+108 @ 0x004272D4
// match: .CRT$XCU+112 @ 0x004272D8
// match: .CRT$XCU+116 @ 0x004272DC
// match: .CRT$XCU+120 @ 0x004272E0

// match: _$E1 @ 0x0030CCB0
// match: _$E2 @ 0x0030ECC0
// match: _$E4 @ 0x0030CCF0
// match: _$E5 @ 0x0030ECD0
// match: _$E7 @ 0x0030CD30
// match: _$E8 @ 0x0030ECE0
// match: _$E10 @ 0x0030CD70
// match: _$E11 @ 0x0030ECF0
// match: _$E13 @ 0x0030CDB0
// match: _$E14 @ 0x0030ED00
// match: _$E16 @ 0x0030CDF0
// match: _$E17 @ 0x0030ED10
// match: _$E19 @ 0x0030CE30
// match: _$E20 @ 0x0030ED20
// match: _$E22 @ 0x0030CE70
// match: _$E23 @ 0x0030ED30
// match: _$E25 @ 0x0030CEB0
// match: _$E26 @ 0x0030ED40
// match: _$E28 @ 0x0030CEF0
// match: _$E29 @ 0x0030ED50
// match: _$E31 @ 0x0030CF30
// match: _$E32 @ 0x0030ED60
// match: _$E34 @ 0x0030CF70
// match: _$E35 @ 0x0030ED70
// match: _$E37 @ 0x0030CFB0
// match: _$E38 @ 0x0030ED80
// match: _$E40 @ 0x0030CFF0
// match: _$E41 @ 0x0030ED90
// match: _$E43 @ 0x0030D030
// match: _$E44 @ 0x0030EDA0
// match: _$E46 @ 0x0030D070
// match: _$E47 @ 0x0030EDB0
// match: _$E49 @ 0x0030D0B0
// match: _$E50 @ 0x0030EDC0
// match: _$E52 @ 0x0030D0F0
// match: _$E53 @ 0x0030EDD0
// match: _$E55 @ 0x0030D130
// match: _$E56 @ 0x0030EDE0
// match: _$E58 @ 0x0030D170
// match: _$E59 @ 0x0030EDF0
// match: _$E61 @ 0x0030D1B0
// match: _$E62 @ 0x0030EE00
// match: _$E64 @ 0x0030D1F0
// match: _$E65 @ 0x0030EE10
// match: _$E67 @ 0x0030D230
// match: _$E68 @ 0x0030EE20
// match: _$E70 @ 0x0030D270
// match: _$E71 @ 0x0030EE30
// match: _$E73 @ 0x0030D2B0
// match: _$E74 @ 0x0030EE40
// match: _$E76 @ 0x0030D2F0
// match: _$E77 @ 0x0030EE50
// match: _$E79 @ 0x0030D330
// match: _$E80 @ 0x0030EE60
// match: _$E82 @ 0x0030D370
// match: _$E83 @ 0x0030EE70
// match: _$E85 @ 0x0030D3B0
// match: _$E86 @ 0x0030EE80
// match: _$E88 @ 0x0030D3F0
// match: _$E89 @ 0x0030EE90
// match: _$E91 @ 0x0030D420
// match: _$E92 @ 0x0030EEA0

namespace kujuUI {

// match: ??1type_1E34A0@kujuUI@@UAE@XZ @ 0x001E3430
type_1E34A0::~type_1E34A0()
{
}

// match: ??0type_1E34A0@kujuUI@@QAE@XZ @ 0x001E3450
type_1E34A0::type_1E34A0()
{
    unk_04 = 0;
}

// match: ?sub_1E3480@type_1C8DF0_104_00@kujuUI@@QBEHXZ @ 0x001E3480
RwInt32 type_1C8DF0_104_00::sub_1E3480() const
{
    return unk_04;
}

// match: ?sub_1E34A0@type_1E34A0@kujuUI@@QAEXPAUtype_3E76B4@2@@Z @ 0x001E34A0
void type_1E34A0::sub_1E34A0(type_3E76B4 *arg_0)
{
    unk_04 = arg_0;
    if (unk_04)
        vf_014();
}
extern type_1C9590 unk_5037AC;
extern type_1C9590 unk_503804;
extern type_1C9590 unk_503A50;
extern type_1C9590 unk_503504;
extern type_1C9590 unk_503AA8;
extern type_1C9590 unk_503B2C;
extern type_1C9590 unk_503728;
extern type_1C9590 unk_503B00;
extern type_1C9590 unk_50355C;
extern type_1C9590 unk_5036FC;
extern type_1C9590 unk_503BDC;
extern type_1C9590 unk_503888;
extern type_1C9590 unk_503B84;
extern type_1C9590 unk_503B58;
extern type_1C9590 unk_503C08;
extern type_1C9590 unk_503780;
extern type_1C9590 unk_503AD4;
extern type_1C9590 unk_503830;
extern type_1C9590 unk_503BB0;
extern type_1C9590 unk_5038B4;
extern type_1C9590 unk_5036D0;
extern type_1C9590 unk_50390C;
extern type_1C9590 unk_503530;
extern type_1C9590 unk_503A7C;
extern type_1C9590 unk_5038E0;
extern type_1C9590 unk_503754;
extern type_1C9590 unk_5037D8;
extern type_1C9590 unk_503588;
extern type_1C9590 unk_50385C;
extern cScopeValidator unk_5035B8;
extern cScopeValidator unk_503938;
extern bool byte_503500;

// match: ?sub_1E34D0@kujuUI@@YAPAUtype_1C9590@1@XZ @ 0x001E34D0
type_1C9590 *sub_1E34D0()
{
    return &unk_5037AC;
}

// match: ?sub_1E34E0@kujuUI@@YAPAUtype_1C9590@1@XZ @ 0x001E34E0
type_1C9590 *sub_1E34E0()
{
    return &unk_503804;
}

// match: ?sub_1E34F0@kujuUI@@YAPAUtype_1C9590@1@XZ @ 0x001E34F0
type_1C9590 *sub_1E34F0()
{
    return &unk_503A50;
}

// match: ?sub_1E3500@kujuUI@@YAPAUtype_1C9590@1@XZ @ 0x001E3500
type_1C9590 *sub_1E3500()
{
    return &unk_503504;
}

// match: ?sub_1E3510@kujuUI@@YAPAUtype_1C9590@1@XZ @ 0x001E3510
type_1C9590 *sub_1E3510()
{
    return &unk_503AA8;
}

// match: ?sub_1E3520@kujuUI@@YAPAUtype_1C9590@1@XZ @ 0x001E3520
type_1C9590 *sub_1E3520()
{
    return &unk_503B2C;
}

// match: ?sub_1E3530@kujuUI@@YAPAUtype_1C9590@1@XZ @ 0x001E3530
type_1C9590 *sub_1E3530()
{
    return &unk_503728;
}

// match: ?sub_1E3540@kujuUI@@YAPAUtype_1C9590@1@XZ @ 0x001E3540
type_1C9590 *sub_1E3540()
{
    return &unk_503B00;
}

// match: ?sub_1E3550@kujuUI@@YAPAUtype_1C9590@1@XZ @ 0x001E3550
type_1C9590 *sub_1E3550()
{
    return &unk_50355C;
}

// match: ?sub_1E3560@kujuUI@@YAPAUtype_1C9590@1@XZ @ 0x001E3560
type_1C9590 *sub_1E3560()
{
    return &unk_5036FC;
}

// match: ?sub_1E3570@kujuUI@@YAPAUtype_1C9590@1@XZ @ 0x001E3570
type_1C9590 *sub_1E3570()
{
    return &unk_503BDC;
}

// match: ?sub_1E3580@kujuUI@@YAPAUtype_1C9590@1@XZ @ 0x001E3580
type_1C9590 *sub_1E3580()
{
    return &unk_503888;
}

// match: ?sub_1E3590@kujuUI@@YAPAUtype_1C9590@1@XZ @ 0x001E3590
type_1C9590 *sub_1E3590()
{
    return &unk_503B84;
}

// match: ?sub_1E35A0@kujuUI@@YAPAUtype_1C9590@1@XZ @ 0x001E35A0
type_1C9590 *sub_1E35A0()
{
    return &unk_503B58;
}

// match: ?sub_1E35B0@kujuUI@@YAPAUtype_1C9590@1@XZ @ 0x001E35B0
type_1C9590 *sub_1E35B0()
{
    return &unk_503C08;
}

// match: ?sub_1E35C0@kujuUI@@YAPAUtype_1C9590@1@XZ @ 0x001E35C0
type_1C9590 *sub_1E35C0()
{
    return &unk_503780;
}

// match: ?sub_1E35D0@kujuUI@@YAPAUtype_1C9590@1@XZ @ 0x001E35D0
type_1C9590 *sub_1E35D0()
{
    return &unk_503AD4;
}

// match: ?sub_1E35E0@kujuUI@@YAPAUtype_1C9590@1@XZ @ 0x001E35E0
type_1C9590 *sub_1E35E0()
{
    return &unk_503830;
}

// match: ?sub_1E35F0@kujuUI@@YAPAUtype_1C9590@1@XZ @ 0x001E35F0
type_1C9590 *sub_1E35F0()
{
    return &unk_503BB0;
}

// match: ?sub_1E3600@kujuUI@@YAPAUtype_1C9590@1@XZ @ 0x001E3600
type_1C9590 *sub_1E3600()
{
    return &unk_5038B4;
}

// match: ?sub_1E3610@kujuUI@@YAPAUtype_1C9590@1@XZ @ 0x001E3610
type_1C9590 *sub_1E3610()
{
    return &unk_5036D0;
}

// match: ?sub_1E3620@kujuUI@@YAPAUtype_1C9590@1@XZ @ 0x001E3620
type_1C9590 *sub_1E3620()
{
    return &unk_50390C;
}

// match: ?sub_1E3630@kujuUI@@YAPAUtype_1C9590@1@XZ @ 0x001E3630
type_1C9590 *sub_1E3630()
{
    return &unk_503530;
}

// match: ?sub_1E3640@kujuUI@@YAXXZ @ 0x001E3640
void sub_1E3640()
{
    unk_5035B8.sub_1C9F50(&unk_5037AC);
    unk_5035B8.sub_1C9F50(&unk_503804);
    unk_5035B8.sub_1C9F50(&unk_503A50);
    unk_5035B8.sub_1C9F50(&unk_503504);
    unk_5035B8.sub_1C9F50(&unk_503AA8);
    unk_503938.sub_1C9F50(&unk_503C08);
    unk_503938.sub_1C9F50(&unk_503780);
    unk_503938.sub_1C9F50(&unk_503AD4);
    unk_503938.sub_1C9F50(&unk_503830);
    unk_503938.sub_1C9F50(&unk_503BB0);
    unk_503938.sub_1C9F50(&unk_5038B4);
    unk_503938.sub_1C9F50(&unk_5036D0);
    byte_503500 = true;
}

// match: ?sub_1E3700@kujuUI@@YAABVcScopeValidator@1@XZ @ 0x001E3700
const cScopeValidator &sub_1E3700()
{
    if (!byte_503500)
        sub_1E3640();
    return unk_5035B8;
}

// match: ?sub_1E3720@kujuUI@@YAABVcScopeValidator@1@XZ @ 0x001E3720
const cScopeValidator &sub_1E3720()
{
    if (!byte_503500)
        sub_1E3640();
    return unk_503938;
}

// match: ?sub_1E3740@kujuUI@@YAPAUtype_1C9590@1@XZ @ 0x001E3740
type_1C9590 *sub_1E3740()
{
    return &unk_503A7C;
}

// match: ?sub_1E3750@kujuUI@@YAPAUtype_1C9590@1@XZ @ 0x001E3750
type_1C9590 *sub_1E3750()
{
    return &unk_5038E0;
}

// match: ?sub_1E3760@kujuUI@@YAPAUtype_1C9590@1@XZ @ 0x001E3760
type_1C9590 *sub_1E3760()
{
    return &unk_503754;
}

// match: ?sub_1E3770@kujuUI@@YAPAUtype_1C9590@1@XZ @ 0x001E3770
type_1C9590 *sub_1E3770()
{
    return &unk_5037D8;
}

// match: ?sub_1E3780@kujuUI@@YAPAUtype_1C9590@1@XZ @ 0x001E3780
type_1C9590 *sub_1E3780()
{
    return &unk_503588;
}

// match: ?sub_1E3790@kujuUI@@YAPAUtype_1C9590@1@XZ @ 0x001E3790
type_1C9590 *sub_1E3790()
{
    return &unk_50385C;
}
}

namespace kujuUI
{

// The value definitions and scope validators, built by their dynamic
// initializers (their exit functions call the out-of-line destructors).
type_1C9590 unk_503804("position", 3, 3, 3, 3, 0, 0, 0, 0);
type_1C9590 unk_5037AC("position", 3, 3, 0, 0, 0, 0, 0, 0);
type_1C9590 unk_503A50("possource", 1, 0, 0, 0, 0, 0, 0, 0);
type_1C9590 unk_503504("component", 1, 0, 0, 0, 0, 0, 0, 0);
type_1C9590 unk_503AA8("compsource", 1, 0, 0, 0, 0, 0, 0, 0);
type_1C9590 unk_503588("compback", 1, 0, 0, 0, 0, 0, 0, 0);
type_1C9590 unk_503B2C("click", 1, 0, 0, 0, 0, 0, 0, 0);
type_1C9590 unk_503728("focus", 1, 0, 0, 0, 0, 0, 0, 0);
type_1C9590 unk_503B00("unfocus", 1, 0, 0, 0, 0, 0, 0, 0);
type_1C9590 unk_50355C("content", 1, 0, 0, 0, 0, 0, 0, 0);
type_1C9590 unk_5036FC("font", 1, 0, 0, 0, 0, 0, 0, 0);
type_1C9590 unk_503BDC("alignleft", 0, 0, 0, 0, 0, 0, 0, 0);
type_1C9590 unk_503888("aligncentre", 0, 0, 0, 0, 0, 0, 0, 0);
type_1C9590 unk_503B84("alignright", 0, 0, 0, 0, 0, 0, 0, 0);
type_1C9590 unk_503B58("source", 1, 0, 0, 0, 0, 0, 0, 0);
type_1C9590 unk_503C08("padup", 1, 0, 0, 0, 0, 0, 0, 0);
type_1C9590 unk_503780("paddown", 1, 0, 0, 0, 0, 0, 0, 0);
type_1C9590 unk_503AD4("padleft", 1, 0, 0, 0, 0, 0, 0, 0);
type_1C9590 unk_503830("padright", 1, 0, 0, 0, 0, 0, 0, 0);
type_1C9590 unk_503BB0("padcancel", 1, 0, 0, 0, 0, 0, 0, 0);
type_1C9590 unk_5038B4("padselect", 1, 0, 0, 0, 0, 0, 0, 0);
type_1C9590 unk_5036D0("losefocus", 1, 0, 0, 0, 0, 0, 0, 0);
type_1C9590 unk_50390C("innerborder", 0, 0, 0, 0, 0, 0, 0, 0);
type_1C9590 unk_503530("noinnerborder", 0, 0, 0, 0, 0, 0, 0, 0);
type_1C9590 unk_50385C("lineheight", 3, 0, 0, 0, 0, 0, 0, 0);
type_1C9590 unk_503A7C("oncancel", 1, 0, 0, 0, 0, 0, 0, 0);
type_1C9590 unk_5038E0("onselect", 1, 0, 0, 0, 0, 0, 0, 0);
type_1C9590 unk_503754("onaltsel", 1, 0, 0, 0, 0, 0, 0, 0);
type_1C9590 unk_5037D8("onoptsel", 1, 0, 0, 0, 0, 0, 0, 0);
cScopeValidator unk_5035B8("widget", "end", 1);
cScopeValidator unk_503938("navigate", "end", 1);

}

// Functions /OPT:ICF folded into another body (config/aliases.txt), defined here for the
// authentic link (PLAN M7) with that body; the placement link takes the folded one.

// ?sub_1F7A60@kujuUI@@YAXHH@Z (folded into 0x1F7A60)
void kujuUI::sub_1F7A60(RwInt32 arg_0, RwInt32 arg_4)
{
    RwInt32 var_4;
}

// ?sub_1F7A60@kujuUI@@YAXHPBD@Z (folded into 0x1F7A60)
void kujuUI::sub_1F7A60(RwInt32 arg_0, RwChar const * arg_4)
{
    RwInt32 var_4;
}

// Functions /OPT:ICF folded into another body (config/aliases.txt), defined here for the
// authentic link (PLAN M7) with that body; the placement link takes the folded one.

// ?sub_1E3480@type_1E34A0@kujuUI@@QAEPAUtype_3E6F74@2@XZ (folded into 0x1E3480)
struct kujuUI::type_3E6F74 * kujuUI::type_1E34A0::sub_1E3480()
{
    return (kujuUI::type_3E6F74 *)(unk_04);
}
