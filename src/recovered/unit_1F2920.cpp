/*
 * kujuUI's widget factory and top layout page (\COD\SHARED\UI\cTopLayoutPage.cpp,
 * game/kujuilayout.h): the factory's creators and validators, the page's
 * loading in steps (its file, image libraries, looks and fonts, widgets), its
 * title and its links; the font sets' list's and the validators' array's
 * instances follow.
 */
#include <string.h>
#include "game/kujuilayout.h"
#include "game/assert.h"

// Its data definitions (PLAN M5), in the image's address order.
// 0x0042D0E0
namespace kujuUI
{
const RwChar *dword_42D0E0 = "";
}
// 0x00504380
namespace kujuUI { type_1F2A00 *dword_504380; }
// 0x00504384
namespace kujuUI { RwInt32 dword_504384; }
// End of its data definitions.

// Its data (PLAN M5): literals, constants and tables where the image has them.
// match: ??_C@_0BA@OEPPCJNG@titledimensions?$AA@ @ 0x003E7A38
// match: ??_C@_05PHLGJONK@title?$AA@ @ 0x003E7A48
// match: ??_C@_0BA@IEGNGIBK@retainselection?$AA@ @ 0x003E7A50
// match: ??_C@_07DLHCIBDH@default?$AA@ @ 0x003E7A60
// match: ??_7cTopLayoutPage@kujuUI@@6B@ @ 0x003E7A68
// match: ??_C@_0CH@CCOEBNOH@Layout?5file?5?$CFs?5not?5found?5or?5pars@ @ 0x003E7AA4
// match: ??_C@_0CA@HILIIND@Missing?5font?5in?5page?5title?3?5?$CFs?6?$AA@ @ 0x003E7ACC
// match: ??_C@_0BM@DFDPCGCP@Missing?5border?5dimensions?$CB?6?$AA@ @ 0x003E7AEC
// match: ??_C@_0BB@KDMKEJPI@Parsing?5file?5?$CFs?6?$AA@ @ 0x003E7B08
// match: ??_C@_0CC@PNKPEKIN@?2COD?2SHARED?2UI?2cTopLayoutPage?4cp@ @ 0x003E7B1C
// match: ??_C@_0DN@BBFIIOPA@void?5__thiscall?5kujuUI?3?3cTopLayo@ @ 0x003E7B40
// match: ??_C@_0BJ@NLPCFLGB@Failed?5to?5load?5script?5?$CFs?$AA@ @ 0x003E7B80
// match: ??_C@_0BE@BMEGBJNG@Font?5?$CFs?5not?5found?4?6?$AA@ @ 0x003E7B9C
// match: __real@41500000 @ 0x003E7BB0
// match: __ehhandler$?sub_1F2920@kujuUI@@YAPAUtype_1F2A00@1@XZ>1>8 @ 0x00420EBC
// match: __ehhandler$?sub_1F2920@kujuUI@@YAPAUtype_1F2A00@1@XZ>1 @ 0x00420EC4
// match: __ehhandler$??0type_1F2A00@kujuUI@@QAE@XZ>1>8 @ 0x00420EE0
// match: __ehhandler$??0type_1F2A00@kujuUI@@QAE@XZ>1 @ 0x00420F58
// match: __ehhandler$??1type_1F2A00@kujuUI@@QAE@XZ>1>8 @ 0x00420F74
// match: __ehhandler$??1type_1F2A00@kujuUI@@QAE@XZ>1 @ 0x00420FEC
// match: __ehhandler$??0cTopLayoutPage@kujuUI@@QAE@XZ>1>8 @ 0x00421008
// match: __ehhandler$??0cTopLayoutPage@kujuUI@@QAE@XZ>1 @ 0x00421038
// match: __ehhandler$??1cTopLayoutPage@kujuUI@@UAE@XZ>1>8 @ 0x00421054
// match: __ehhandler$??1cTopLayoutPage@kujuUI@@UAE@XZ>1 @ 0x0042108C
// match: __ehhandler$?sub_1F3510@cTopLayoutPage@kujuUI@@QAEXXZ>1>8 @ 0x004210A8
// match: __ehhandler$?sub_1F3510@cTopLayoutPage@kujuUI@@QAEXXZ>1 @ 0x004210B8
// match: __ehhandler$?sub_1F4100@cTopLayoutPage@kujuUI@@QAE_NPAUtype_1C8DF0@2@PAU?$type_1EFCF0@Utype_1E6350@@@2@@Z>1>8 @ 0x004210D4
// match: __ehhandler$?sub_1F4100@cTopLayoutPage@kujuUI@@QAE_NPAUtype_1C8DF0@2@PAU?$type_1EFCF0@Utype_1E6350@@@2@@Z>1 @ 0x004210FC
// match: __ehhandler$?sub_1F4540@cTopLayoutPage@kujuUI@@QAEXABUtype_1A5EA0@@PAUtype_1E6350@@HHH@Z>1>8 @ 0x00421118
// match: __ehhandler$?sub_1F4540@cTopLayoutPage@kujuUI@@QAEXABUtype_1A5EA0@@PAUtype_1E6350@@HHH@Z>1 @ 0x00421128
// match: __ehhandler$?_Buynode@?$list@Utype_1E6350@@V?$allocator@Utype_1E6350@@@std@@@std@@IAEPAU_Node@?$_List_nod@Utype_1E6350@@V?$allocator@Utype_1E6350@@@std@@@2@XZ>1>8 @ 0x00421144
// match: __ehhandler$?_Buynode@?$list@Utype_1E6350@@V?$allocator@Utype_1E6350@@@std@@@std@@IAEPAU_Node@?$_List_nod@Utype_1E6350@@V?$allocator@Utype_1E6350@@@std@@@2@XZ>1>16>16 @ 0x00421154
// match: __ehhandler$?_Buynode@?$list@Utype_1E6350@@V?$allocator@Utype_1E6350@@@std@@@std@@IAEPAU_Node@?$_List_nod@Utype_1E6350@@V?$allocator@Utype_1E6350@@@std@@@2@XZ>1>16 @ 0x00421164
// match: __ehhandler$?_Buynode@?$list@Utype_1E6350@@V?$allocator@Utype_1E6350@@@std@@@std@@IAEPAU_Node@?$_List_nod@Utype_1E6350@@V?$allocator@Utype_1E6350@@@std@@@2@XZ>1 @ 0x00421178
// match: __ehhandler$?_Buynode@?$list@Utype_1E6350@@V?$allocator@Utype_1E6350@@@std@@@std@@IAEPAU_Node@?$_List_nod@Utype_1E6350@@V?$allocator@Utype_1E6350@@@std@@@2@PAU342@0ABUtype_1E6350@@@Z>1>8 @ 0x00421194
// match: __ehhandler$?_Buynode@?$list@Utype_1E6350@@V?$allocator@Utype_1E6350@@@std@@@std@@IAEPAU_Node@?$_List_nod@Utype_1E6350@@V?$allocator@Utype_1E6350@@@std@@@2@PAU342@0ABUtype_1E6350@@@Z>1>16>16 @ 0x004211AC
// match: __ehhandler$?_Buynode@?$list@Utype_1E6350@@V?$allocator@Utype_1E6350@@@std@@@std@@IAEPAU_Node@?$_List_nod@Utype_1E6350@@V?$allocator@Utype_1E6350@@@std@@@2@PAU342@0ABUtype_1E6350@@@Z>1>16 @ 0x004211BC
// match: __ehhandler$?_Buynode@?$list@Utype_1E6350@@V?$allocator@Utype_1E6350@@@std@@@std@@IAEPAU_Node@?$_List_nod@Utype_1E6350@@V?$allocator@Utype_1E6350@@@std@@@2@PAU342@0ABUtype_1E6350@@@Z>1 @ 0x004211D0
// match: __ehhandler$?_Incsize@?$list@Utype_1E6350@@V?$allocator@Utype_1E6350@@@std@@@std@@IAEXI@Z>1>8 @ 0x004211EC
// match: __ehhandler$?_Incsize@?$list@Utype_1E6350@@V?$allocator@Utype_1E6350@@@std@@@std@@IAEXI@Z>1 @ 0x004211F4
// match: .CRT$XCU+0 @ 0x00427358
// match: ?dword_42D0E0@kujuUI@@3PBDB @ 0x0042D0E0

// match: _$E1 @ 0x0030DAB0

using namespace kujuUI;

namespace kujuUI {
extern type_1F2A00 *dword_504380;
extern RwInt32 dword_504384;
extern const RwChar *dword_42D0E0;
}

// match: ?sub_1F2920@kujuUI@@YAPAUtype_1F2A00@1@XZ @ 0x001F2920
// match: __ehhandler$?sub_1F2920@kujuUI@@YAPAUtype_1F2A00@1@XZ-0xB @ 0x00304540
// match: __ehhandler$?sub_1F2920@kujuUI@@YAPAUtype_1F2A00@1@XZ @ 0x0030454B
type_1F2A00 *kujuUI::sub_1F2920()
{
    if (!dword_504380)
        dword_504380 = new type_1F2A00;
    return dword_504380;
}

// match: ?sub_1F29A0@kujuUI@@YAXXZ @ 0x001F29A0
void kujuUI::sub_1F29A0()
{
    delete dword_504380;
    dword_504380 = 0;
}

// match: ??0type_1F2A00@kujuUI@@QAE@XZ @ 0x001F2A00
// match: __ehhandler$??0type_1F2A00@kujuUI@@QAE@XZ-0xB1 @ 0x00304560
// match: __ehhandler$??0type_1F2A00@kujuUI@@QAE@XZ @ 0x00304611
type_1F2A00::type_1F2A00()
    : unk_A08("default", 1, 0, 0, 0, 0, 0, 0, 0), unk_A34("retainselection", 0, 0, 0, 0, 0, 0, 0, 0),
      unk_A60("title", 1, 1, 0, 0, 0, 0, 0, 0), unk_A8C("title", 0, 0, 0, 0, 0, 0, 0, 0),
      unk_AB8("titledimensions", 3, 3, 3, 0, 0, 0, 0, 0)
{
    sub_1F2E70(&unk_0C);
    sub_1F2E70(&unk_10);
    sub_1F2E70(&unk_14);
    sub_1F2E70(&unk_18);
    sub_1F2E70(&unk_1C);
    sub_1F2E70(&unk_20);
    sub_1F2E70(&unk_24);
    sub_1F2E70(&unk_28);
    unk_2C.sub_1C9F50(&unk_A08);
    unk_2C.sub_1C9F50(&unk_A34);
    unk_2C.sub_1C9F50(&unk_A60);
    unk_2C.sub_1C9F50(&unk_A8C);
    unk_2C.sub_1C9F50(&unk_AB8);
    RwUInt32 var_10 = unk_144.count();
    for (RwUInt32 var_14 = 0; var_14 != var_10; ++var_14)
        unk_2C.sub_1C9F70(unk_144.at(var_14));
    unk_2C.sub_1C9F50(sub_1E3740());
    unk_2C.sub_1C9F50(sub_1E3750());
    unk_2C.sub_1C9F50(sub_1E3760());
    unk_2C.sub_1C9F50(sub_1E3770());
    unk_2C.sub_1CA1A0(*sub_1EF810());
    unk_2C.sub_1C9F70(const_cast<cScopeValidator *>(sub_1E6590()));
    unk_2C.sub_1CA2A0();
}

// match: ??1type_1F2A00@kujuUI@@QAE@XZ @ 0x001F2D40
// match: __ehhandler$??1type_1F2A00@kujuUI@@QAE@XZ-0xB1 @ 0x00304620
// match: __ehhandler$??1type_1F2A00@kujuUI@@QAE@XZ @ 0x003046D1
type_1F2A00::~type_1F2A00()
{
    unk_144.clear();
}

// match: ?sub_1F2E70@type_1F2A00@kujuUI@@QAEXPAUtype_3E7D94@2@@Z @ 0x001F2E70
void type_1F2A00::sub_1F2E70(type_3E7D94 *arg_0)
{
    unk_00.sub_1EFCF0(arg_0->vf_004(), arg_0);
    cScopeValidator *var_4;
    arg_0->sub_1F7A70(&var_4);
    unk_144.take(var_4);
}

// match: ??0cTopLayoutPage@kujuUI@@QAE@XZ @ 0x001F2EC0
// match: __ehhandler$??0cTopLayoutPage@kujuUI@@QAE@XZ-0x48 @ 0x003046E0
// match: __ehhandler$??0cTopLayoutPage@kujuUI@@QAE@XZ @ 0x00304728
cTopLayoutPage::cTopLayoutPage()
    : cLayoutPage(0), unk_80(dword_42D0E0), unk_9C(0), unk_A0(0), unk_A4(0), unk_A8(0), unk_C4(0)
{
    ++dword_504384;
}

// match: ??_GcTopLayoutPage@kujuUI@@UAEPAXI@Z @ 0x001F3010

// match: ??1cTopLayoutPage@kujuUI@@UAE@XZ @ 0x001F3040
// match: __ehhandler$??1cTopLayoutPage@kujuUI@@UAE@XZ-0x56 @ 0x00304740
// match: __ehhandler$??1cTopLayoutPage@kujuUI@@UAE@XZ @ 0x00304796
cTopLayoutPage::~cTopLayoutPage()
{
    for (std::vector<type_3E7D08 *>::iterator var_10 = sub_1EDBE0(); var_10 != sub_1EDC10(); ++var_10)
        delete *var_10;
    if (--dword_504384 == 0)
    {
        sub_1F29A0();
        sub_1EF850();
    }
}

// match: ?sub_1F31C0@kujuUI@@YAPAUtype_3E7D08@1@PBDPBUtype_1F31C0_entry@1@I@Z @ 0x001F31C0
type_3E7D08 *kujuUI::sub_1F31C0(const RwChar *arg_0, const type_1F31C0_entry *arg_4, RwUInt32 arg_8)
{
    if (arg_0)
    {
        for (RwUInt32 var_4 = 0; var_4 != arg_8; ++var_4)
        {
            const type_1F31C0_entry *var_8 = &arg_4[var_4];
            if (var_8->unk_04 && !strcmp(var_8->unk_04, arg_0))
                return var_8->unk_00;
        }
    }
    return 0;
}

// match: ?sub_1F3230@kujuUI@@YAXPAUtype_3E7D08@1@PBDPBUtype_1F31C0_entry@1@IHPAVcLayoutPage@1@@Z @ 0x001F3230
void kujuUI::sub_1F3230(type_3E7D08 *arg_0, const RwChar *arg_4, const type_1F31C0_entry *arg_8, RwUInt32 arg_C,
                        RwInt32 arg_10, cLayoutPage *arg_14)
{
    if (arg_4)
    {
        type_3E7D08 *var_4 = sub_1F31C0(arg_4, arg_8, arg_C);
        if (var_4)
            arg_14->sub_1E8980(arg_0, var_4, arg_10);
    }
}

// match: ?sub_1F3270@kujuUI@@YAPBDPAUtype_1C9590@1@PAUtype_1C8DF0@1@@Z @ 0x001F3270
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
const RwChar *kujuUI::sub_1F3270(type_1C9590 *arg_0, type_1C8DF0 *arg_4)
{
    const RwChar *var_4 = 0;
    type_1C8DF0_104 *local_8 = arg_4->sub_1C90B0(arg_0);
    if (local_8 && local_8->sub_21D030() == 1 && local_8->sub_1C9890(0)->sub_1EE9D0() == 1)
        var_4 = (const RwChar *)local_8->sub_1C9890(0)->sub_1E3480();
    return var_4;
}

// match: ?sub_1F32D0@cTopLayoutPage@kujuUI@@QAEXXZ @ 0x001F32D0
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void cTopLayoutPage::sub_1F32D0()
{
    type_1F2A00 *var_4 = sub_1F2920();
    cParsedFile *local_8 = 0;
    cParsedFile::loadBinaryFile(unk_80.c_str(), &var_4->unk_2C, &local_8);
    unk_9C = local_8;
    unk_A8 = 2;
    if (!unk_9C)
    {
        if (CODFH_DEBUG_LOGS)
            sub_1C8A30("Layout file %s not found or parsable.\n", unk_80.c_str());
    }
}

// match: ?sub_1F3390@cTopLayoutPage@kujuUI@@QAEXXZ @ 0x001F3390
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void cTopLayoutPage::sub_1F3390()
{
    type_1C8DF0 *var_4 = unk_9C->sub_1E3480();
    for (RwUInt32 v8 = 0; v8 != var_4->sub_1C9120(); ++v8)
    {
        const type_1C9590 *stk_C;
        type_1C8DF0_104 *var_10 = var_4->sub_1C9140(v8);
        stk_C = var_10->unk_44;
        if (stk_C == sub_1EF830())
        {
            type_1C8DF0_104_00 *lv_14 = var_10->sub_1C9890(0);
            if (!sub_1F4430((const RwChar *)lv_14->sub_1E3480()))
                throwLoadError();
        }
    }
    unk_A8 = 3;
}

// match: ?sub_1F3430@cTopLayoutPage@kujuUI@@QAEXXZ @ 0x001F3430
void cTopLayoutPage::sub_1F3430()
{
    type_1C8DF0 *var_4 = unk_9C->sub_1E3480();
    for (RwUInt32 var_8 = 0; var_8 != var_4->sub_1C9090(); ++var_8)
    {
        type_1C8DF0 *var_10 = var_4->sub_1E3BF0(var_8);
        const cScopeValidator *var_C = var_10->sub_1C8FE0();
        if (var_C == sub_1E3CD0())
        {
            if (!unk_C8.sub_1EF560(var_10, &unk_AC))
                throwLoadError();
        }
        else if (var_C == sub_1E6590())
        {
            if (!sub_1F4100(var_10, &unk_B8))
                throwLoadError();
        }
    }
    unk_A8 = 4;
}

// match: ?sub_1F3510@cTopLayoutPage@kujuUI@@QAEXXZ @ 0x001F3510
// match: __ehhandler$?sub_1F3510@cTopLayoutPage@kujuUI@@QAEXXZ-0x16 @ 0x003047A0
// match: __ehhandler$?sub_1F3510@cTopLayoutPage@kujuUI@@QAEXXZ @ 0x003047B6
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void cTopLayoutPage::sub_1F3510()
{
    if (CODFH_DEBUG_LOGS)
        sub_1C8A30("Parsing file %s\n", unk_80.c_str());
    RwInt32 ebp_14 = 0;
    type_1C8DF0_104 *l2448 = unk_9C->sub_1E3480()->sub_1C90B0(sub_1F2920()->get_unk_A60());
    type_1C8DF0_104 *lcl_44 = 0;

    if (!l2448)
    {
        lcl_44 = unk_9C->sub_1E3480()->sub_1C90B0(sub_1F2920()->get_unk_A8C());
        if (lcl_44)
            ebp_14 = 1;
    }
    else
        ebp_14 = 2;
    bool loc35 = (bool)(lcl_44 || l2448);
    type_1C8DF0_104 *l34 = loc35 ? unk_9C->sub_1E3480()->sub_1C90B0(sub_1F2920()->get_unk_AB8()) : 0;

    if (loc35 && !l34)
    {
        if (CODFH_DEBUG_LOGS)
            sub_1C8A30("Missing border dimensions!\n");
    }
    type_3E7D08 *o30 = 0;
    RwUInt32 lv_10 = 0;
    type_1C8DF0 *m_40 = unk_9C->sub_1E3480();
    type_1EFCF0<type_3E7D08 *> *loc20 = unk_A4;
    type_1F31C0_entry lcl_2444[256];

    sub_1EDBC0(m_40->sub_1C9090() - unk_B8.sub_1E10A0() - unk_AC.sub_1E10A0() + ebp_14);
    for (RwUInt32 var_244C = 0; var_244C != m_40->sub_1C9090(); ++var_244C)
    {
        type_1C8DF0 *var_2454 = m_40->sub_1E3BF0(var_244C);
        const cScopeValidator *var_2450 = var_2454->sub_1C8FE0();

        if (var_2450 != sub_1E3CD0() && var_2450 != sub_1E6590())
        {
            type_3E7D08 *var_2458 = 0;

            widget_factory()->sub_1F7960(var_2454, &unk_AC, &unk_B8, unk_A0, this, &var_2458);
            if (var_2458)
            {
                if (loc20)
                {
                    const RwChar *var_2464 = var_2454->sub_1C8FC0();

                    if (var_2464)
                    {
                        type_3E7D08 **var_2468 = loc20->sub_1ED670(var_2464);

                        if (var_2468)
                            *var_2468 = var_2458;
                    }
                }
                sub_1E8A20(var_2458);
                if (!o30 && var_2458->vf_010())
                    o30 = var_2458;
                const RwChar *fp_245C = var_2454->sub_1C8FC0();
                type_1F31C0_entry *u2460 = &lcl_2444[lv_10];

                u2460->unk_00 = var_2458;
                u2460->unk_04 = fp_245C;
                u2460->unk_08[0] = sub_1F3270(sub_1E35D0(), var_2454);
                u2460->unk_08[1] = sub_1F3270(sub_1E35E0(), var_2454);
                u2460->unk_08[2] = sub_1F3270(sub_1E35B0(), var_2454);
                u2460->unk_08[3] = sub_1F3270(sub_1E35C0(), var_2454);
                u2460->unk_08[4] = sub_1F3270(sub_1E35F0(), var_2454);
                u2460->unk_08[5] = sub_1F3270(sub_1E3600(), var_2454);
                u2460->unk_08[6] = sub_1F3270(sub_1E3610(), var_2454);
                lv_10++;
            }
        }
    }
    type_1C8DF0_104 *ebp_1C = m_40->sub_1C90B0(sub_1E3740());
    type_1C8DF0_104 *l18 = m_40->sub_1C90B0(sub_1E3750());
    type_1C8DF0_104 *ebp_2C = m_40->sub_1C90B0(sub_1E3760());
    type_1C8DF0_104 *p3C = m_40->sub_1C90B0(sub_1E3770());

    if (ebp_1C)
    {
        type_1DFE80_target *var_246C;

        unk_A0->sub_1E0D50(ebp_1C->sub_1C9890(0)->sub_1E3480(), 0, &var_246C);
        sub_1F43D0(7, var_246C);
    }
    if (l18)
    {
        type_1DFE80_target *var_2470;

        unk_A0->sub_1E0D50(l18->sub_1C9890(0)->sub_1E3480(), 0, &var_2470);
        sub_1F43D0(4, var_2470);
    }
    if (ebp_2C)
    {
        type_1DFE80_target *var_2474;

        unk_A0->sub_1E0D50(ebp_2C->sub_1C9890(0)->sub_1E3480(), 0, &var_2474);
        sub_1F43D0(5, var_2474);
    }
    if (p3C)
    {
        type_1DFE80_target *var_2478;

        unk_A0->sub_1E0D50(p3C->sub_1C9890(0)->sub_1E3480(), 0, &var_2478);
        sub_1F43D0(6, var_2478);
    }
    for (RwUInt32 var_247C = 0; var_247C != lv_10; ++var_247C)
    {
        type_1F31C0_entry *var_2480 = &lcl_2444[var_247C];

        sub_1F3230(var_2480->unk_00, var_2480->unk_08[6], lcl_2444, lv_10, 14, this);
        sub_1F3230(var_2480->unk_00, var_2480->unk_08[0], lcl_2444, lv_10, 0, this);
        sub_1F3230(var_2480->unk_00, var_2480->unk_08[1], lcl_2444, lv_10, 1, this);
        sub_1F3230(var_2480->unk_00, var_2480->unk_08[2], lcl_2444, lv_10, 2, this);
        sub_1F3230(var_2480->unk_00, var_2480->unk_08[3], lcl_2444, lv_10, 3, this);
        sub_1F3230(var_2480->unk_00, var_2480->unk_08[4], lcl_2444, lv_10, 7, this);
        sub_1F3230(var_2480->unk_00, var_2480->unk_08[5], lcl_2444, lv_10, 4, this);
    }
    type_1C8DF0_104 *lcl_28 = m_40->sub_1C90B0(sub_1F2920()->get_unk_A08());
    type_3E7D08 *w24 = 0;

    if (lcl_28)
    {
        w24 = sub_1F31C0((const RwChar *)lcl_28->sub_1C9890(0)->sub_1E3480(), lcl_2444, lv_10);
        if (w24)
            sub_1E8A40(w24);
    }
    if (!sub_1E8BB0() && o30)
        sub_1E8A40(o30);
    sub_1E8C30(m_40->sub_1C90B0(sub_1F2920()->get_unk_A34()) != 0);
    if (l2448 && l34)
    {
        type_1E6350 *var_2484 = unk_B8.sub_1ED670((const RwChar *)l2448->sub_1C9890(1)->sub_1E3480());

        if (var_2484)
        {
            type_1A5EA0 var_24A4((const RwChar *)l2448->sub_1C9890(0)->sub_1E3480(), 0);

            sub_1F4540(var_24A4, var_2484, l34->sub_1C9890(0)->sub_1E3480(), l34->sub_1C9890(1)->sub_1E3480(),
                       l34->sub_1C9890(2)->sub_1E3480());
        }
        else if (CODFH_DEBUG_LOGS)
            sub_1C8A30("Missing font in page title: %s\n", unk_80.c_str());
    }
    else if (lcl_44 && l34)
        sub_1F4540(type_1CB670(), 0, l34->sub_1C9890(0)->sub_1E3480(), l34->sub_1C9890(1)->sub_1E3480(),
                   l34->sub_1C9890(2)->sub_1E3480());
    delete unk_9C;
    unk_9C = 0;
    unk_A0 = 0;
    unk_AC.sub_1E1080();
    unk_B8.sub_1E1080();
    unk_A8 = 5;
    vf_038();
}

// match: ?throwLoadError@cTopLayoutPage@kujuUI@@QAEXXZ @ 0x001F4020
void cTopLayoutPage::throwLoadError()
{
    delete unk_9C;
    unk_A0 = 0;
    unk_A4 = 0;
    unk_A8 = 6;
    if (CODFH_DEBUG_LOGS)
        sub_1C8A30("Failed to load script %s", unk_80.c_str());
#line 635 "\\COD\\SHARED\\UI\\cTopLayoutPage.cpp"
    sub_1C7F20(false, __FILE__, __LINE__, __FUNCSIG__, 3);
}

// match: ?sub_1F4100@cTopLayoutPage@kujuUI@@QAE_NPAUtype_1C8DF0@2@PAU?$type_1EFCF0@Utype_1E6350@@@2@@Z @ 0x001F4100
// match: __ehhandler$?sub_1F4100@cTopLayoutPage@kujuUI@@QAE_NPAUtype_1C8DF0@2@PAU?$type_1EFCF0@Utype_1E6350@@@2@@Z-0x2E @ 0x003047C0
// match: __ehhandler$?sub_1F4100@cTopLayoutPage@kujuUI@@QAE_NPAUtype_1C8DF0@2@PAU?$type_1EFCF0@Utype_1E6350@@@2@@Z @ 0x003047EE
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
bool cTopLayoutPage::sub_1F4100(type_1C8DF0 *arg_0, type_1EFCF0<type_1E6350> *arg_4)
{
    type_E8780<type_1E5A60> frm_24[6];
    bool lcl_25 = true;
    RwUInt32 m_48 = 0;
    const RwChar *w44 = arg_0->sub_1C8FC0();
    RwUInt32 loc40[6];
    for (; m_48 != arg_0->sub_1C9120(); ++m_48)
    {
        type_1C8DF0_104 *fp_64 = arg_0->sub_1C9140(m_48);
        const RwChar *w60 = fp_64->sub_1C9870();
        const RwChar *loc50 = (const RwChar *)fp_64->sub_1C9890(0)->sub_1E3480();
        RwInt32 lcl_68 = sub_1F8120(w60);
        lcl_25 = false;
        RwUInt32 loc54 = fp_64->sub_1C9890(1)->sub_1E3480();
        RwUInt32 bp_5c = fp_64->sub_1C9890(2)->sub_1E3480();
        RwUInt32 m_58 = fp_64->sub_1C9890(3)->sub_1E3480();
        RwUInt32 q4c = fp_64->sub_1C9890(4)->sub_1E3480();
        if (lcl_68 != 6)
        {
            type_E8780<type_1E5A60> var_6C(sub_1E5A80(loc50));
            if (!var_6C.sub_E87C0())
            {
                frm_24[lcl_68] = var_6C;
                loc40[lcl_68] = bp_5c << 8 | loc54 | m_58 << 16 | q4c << 24;
                lcl_25 = true;
            }
            else if (CODFH_DEBUG_LOGS)
                sub_1C8A30("Font %s not found.\n", loc50);
        }
    }
    if (lcl_25 && w44)
    {
        sub_1E6510(frm_24, loc40);
        std::list<type_1E6350>::iterator var_70 = unk_38.insert(unk_38.begin(), type_1E6350(frm_24, loc40));
        arg_4->sub_1EFCF0(w44, &*var_70);
    }
    return lcl_25;
}

// match: ?sub_1F43D0@cTopLayoutPage@kujuUI@@QAEXHPAUtype_1DFE80_target@2@@Z @ 0x001F43D0
void cTopLayoutPage::sub_1F43D0(RwInt32 arg_0, type_1DFE80_target *arg_4)
{
    unk_44.sub_1DFE50(arg_0, arg_4);
}

// match: ?processEvent@cTopLayoutPage@kujuUI@@UAE?AW4eEventWasHandled@2@ABVcStateChange@2@@Z @ 0x001F43F0
eEventWasHandled cTopLayoutPage::processEvent(const cStateChange &arg_0)
{
    if (cLayoutPage::processEvent(arg_0) == 1)
        return static_cast<type_3E6CE4 &>(unk_44).processEvent(arg_0);
    return (eEventWasHandled)1;
}

// match: ?sub_1F4430@cTopLayoutPage@kujuUI@@QAE_NPBD@Z @ 0x001F4430
bool cTopLayoutPage::sub_1F4430(const RwChar *arg_0)
{
    return unk_C8.sub_1EF460(arg_0);
}

// match: ?sub_1F4450@cTopLayoutPage@kujuUI@@QAEXXZ @ 0x001F4450
void cTopLayoutPage::sub_1F4450()
{
    switch (unk_A8)
    {
    case 1:
        sub_1F32D0();
        break;
    case 2:
        sub_1F3390();
        break;
    case 3:
        sub_1F3430();
        break;
    case 4:
        sub_1F3510();
        break;
    }
}

// match: ?sub_1F44C0@cTopLayoutPage@kujuUI@@QAEXPBDPAUtype_1ED670@2@PAU?$type_1EFCF0@PAUtype_3E7D08@kujuUI@@@2@@Z @ 0x001F44C0
void cTopLayoutPage::sub_1F44C0(const RwChar *arg_0, type_1ED670 *arg_4, type_1EFCF0<type_3E7D08 *> *arg_8)
{
    unk_80 = dword_42D0E0;
    unk_80 += arg_0;
    unk_A0 = arg_4;
    unk_A8 = 1;
    unk_A4 = arg_8;
}

// match: ?sub_1F4540@cTopLayoutPage@kujuUI@@QAEXABUtype_1A5EA0@@PAUtype_1E6350@@HHH@Z @ 0x001F4540
// match: __ehhandler$?sub_1F4540@cTopLayoutPage@kujuUI@@QAEXABUtype_1A5EA0@@PAUtype_1E6350@@HHH@Z-0x16 @ 0x00304800
// match: __ehhandler$?sub_1F4540@cTopLayoutPage@kujuUI@@QAEXABUtype_1A5EA0@@PAUtype_1E6350@@HHH@Z @ 0x00304816
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void cTopLayoutPage::sub_1F4540(const type_1A5EA0 &arg_0, type_1E6350 *arg_4, RwInt32 arg_8, RwInt32 arg_C,
                                RwInt32 arg_10)
{
    bool bp_d = arg_0.empty() ? false : true;
    type_1E0330_rect o30 = vf_020();
    type_1E0330_rect m_48 = o30;
    type_1E0330_rect loc20 = o30;
    if (bp_d)
    {
        m_48.unk_04 -= arg_C;
        loc20.unk_04 -= arg_C;
    }
    RwReal l34 = arg_10 + 13.0f;
    m_48.unk_04 -= l34;
    m_48.unk_0C += l34 + 2.0f;
    m_48.unk_00 -= l34;
    m_48.unk_08 += l34;
    loc20.unk_0C = arg_8 + loc20.unk_04;
    type_3E6D0C *fp_38 = new type_3E6D0C(m_48, 0, this);
    if (bp_d)
    {
        unk_C4 = new cStaticText((RwInt32)arg_4, &loc20, 0, 0, this);
        unk_C4->pvf_008(arg_0);
        loc20.unk_04 += arg_C;
        loc20.unk_04 -= arg_10;
        if ((RwInt32)loc20.unk_04 & 1)
            loc20.unk_04 += 1.0f;
        type_1E0330_rect var_58(loc20.unk_00, loc20.unk_04, loc20.unk_08, loc20.unk_04 + 1.0f);
        fp_38->sub_1E0400(&var_58);
        sub_1ED9F0(unk_C4);
    }
    sub_1ED9F0(fp_38);
}

// std::list<type_1E6350>'s and the validators' array's instances.
// match: ??1?$list@Utype_1E6350@@V?$allocator@Utype_1E6350@@@std@@@std@@QAE@XZ @ 0x001F47D0
// match: ?_Insert@?$list@Utype_1E6350@@V?$allocator@Utype_1E6350@@@std@@@std@@QAEXViterator@12@ABUtype_1E6350@@@Z @ 0x001F4810
// match: ?_Buynode@?$list@Utype_1E6350@@V?$allocator@Utype_1E6350@@@std@@@std@@IAEPAU_Node@?$_List_nod@Utype_1E6350@@V?$allocator@Utype_1E6350@@@std@@@2@XZ @ 0x001F4870
// match: __ehhandler$?_Buynode@?$list@Utype_1E6350@@V?$allocator@Utype_1E6350@@@std@@@std@@IAEPAU_Node@?$_List_nod@Utype_1E6350@@V?$allocator@Utype_1E6350@@@std@@@2@XZ @ 0x00304820
// match: ?clear@?$list@Utype_1E6350@@V?$allocator@Utype_1E6350@@@std@@@std@@QAEXXZ @ 0x001F4950
// match: ?_Buynode@?$list@Utype_1E6350@@V?$allocator@Utype_1E6350@@@std@@@std@@IAEPAU_Node@?$_List_nod@Utype_1E6350@@V?$allocator@Utype_1E6350@@@std@@@2@PAU342@0ABUtype_1E6350@@@Z @ 0x001F49E0
// match: __ehhandler$?_Buynode@?$list@Utype_1E6350@@V?$allocator@Utype_1E6350@@@std@@@std@@IAEPAU_Node@?$_List_nod@Utype_1E6350@@V?$allocator@Utype_1E6350@@@std@@@2@PAU342@0ABUtype_1E6350@@@Z-0x11 @ 0x00304830
// match: __ehhandler$?_Buynode@?$list@Utype_1E6350@@V?$allocator@Utype_1E6350@@@std@@@std@@IAEPAU_Node@?$_List_nod@Utype_1E6350@@V?$allocator@Utype_1E6350@@@std@@@2@PAU342@0ABUtype_1E6350@@@Z @ 0x00304841
// match: ?_Incsize@?$list@Utype_1E6350@@V?$allocator@Utype_1E6350@@@std@@@std@@IAEXI@Z @ 0x001F4AA0
// match: __ehhandler$?_Incsize@?$list@Utype_1E6350@@V?$allocator@Utype_1E6350@@@std@@@std@@IAEXI@Z-0x8 @ 0x00304850
// match: __ehhandler$?_Incsize@?$list@Utype_1E6350@@V?$allocator@Utype_1E6350@@@std@@@std@@IAEXI@Z @ 0x00304858
// match: ??0?$type_1E61A0@VcScopeValidator@kujuUI@@$07@@QAE@XZ @ 0x001F4B70
// match: ?at@?$type_1E61A0@VcScopeValidator@kujuUI@@$07@@QAEPAVcScopeValidator@kujuUI@@I@Z @ 0x001F4B90
// match: ?take@?$type_1E61A0@VcScopeValidator@kujuUI@@$07@@QAEXPAVcScopeValidator@kujuUI@@@Z @ 0x001F4BC0
// match: ?count@?$type_1E61A0@VcScopeValidator@kujuUI@@$07@@QAEIXZ @ 0x001F4C00
// match: ?clear@?$type_1E61A0@VcScopeValidator@kujuUI@@$07@@QAEXXZ @ 0x001F4C20
// match: ??1_Node@?$_List_nod@Utype_1E6350@@V?$allocator@Utype_1E6350@@@std@@@std@@QAE@XZ @ 0x001F4C90
// match: ?next@?$type_1E61A0@VcScopeValidator@kujuUI@@$07@@QAEPAVcScopeValidator@kujuUI@@XZ @ 0x001F4CB0
// match: ?item_size@?$type_1E61A0@VcScopeValidator@kujuUI@@$07@@SAIXZ @ 0x001F4CF0

// match: ?sub_1F4790@cTopLayoutPage@kujuUI@@QAE_NABUtype_1A5EA0@@@Z @ 0x001F4790
bool cTopLayoutPage::sub_1F4790(const type_1A5EA0 &arg_0)
{
    if (unk_C4)
    {
        unk_C4->pvf_008(arg_0);
        return true;
    }
    return false;
}

// The length of dword_42D0E0, measured when the program starts (nothing reads it).
RwUInt32 dword_504388 = strlen(dword_42D0E0);

// Functions /OPT:ICF folded into another body (config/aliases.txt), defined here for the
// authentic link (PLAN M7) with that body; the placement link takes the folded one.

// ?vf_038@cTopLayoutPage@kujuUI@@UAEXXZ (folded into 0x1E41C0)
void kujuUI::cTopLayoutPage::vf_038()
{
}

// Functions /OPT:ICF folded into another body (config/aliases.txt), defined here for the
// authentic link (PLAN M7) with that body; the placement link takes the folded one.

// ?sub_15FC40@cTopLayoutPage@kujuUI@@QAEHXZ (folded into 0x15FC40)
RwInt32 kujuUI::cTopLayoutPage::sub_15FC40()
{
    return unk_A8;
}
