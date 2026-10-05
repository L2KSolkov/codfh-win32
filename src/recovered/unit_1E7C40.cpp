/*
 * kujuUI's focus stack (game/kujuui.h): the widgets that take the pad from
 * the others, the top one getting the events and focus, and the array
 * template's members it brings in (game/kujufont.h).
 */
#include "game/kujuui.h"

// Its data definitions (PLAN M5), in the image's address order.
// 0x0050420C
namespace kujuUI { type_1E7CF0 *dword_50420C; }
// End of its data definitions.


namespace kujuUI {

// Globals with constructors defined here (their initializers and exit
// functions at the end of .text).
type_1EF160 unk_504210;
// Vtables (.rdata, PLAN M5): each in its own placement range (config/splits.txt).
// Its data (PLAN M5): literals, constants and tables where the image has them.
// match: ??_7type_1E7CF0@kujuUI@@6B@ @ 0x003E73C8
// match: __ehhandler$??0type_1E7CF0@kujuUI@@QAE@XZ>1>8 @ 0x00420280
// match: __ehhandler$??0type_1E7CF0@kujuUI@@QAE@XZ>1 @ 0x00420288
// match: .CRT$XCU+0 @ 0x0042734C

// match: _$E1 @ 0x0030DA30
// match: _$E2 @ 0x0030F010
// match: ??0type_1E7CF0@kujuUI@@QAE@XZ @ 0x001E7C40
// match: __ehhandler$??0type_1E7CF0@kujuUI@@QAE@XZ-0x8 @ 0x00303CB0
// match: __ehhandler$??0type_1E7CF0@kujuUI@@QAE@XZ @ 0x00303CB8

type_1E7CF0::type_1E7CF0() : type_3E7D08(0)
{
    unk_20 = true;
    unk_21 = false;
}

// match: ??_Gtype_1E7CF0@kujuUI@@UAEPAXI@Z @ 0x001E7CB0

extern type_1E7CF0 *dword_50420C;

// match: ?sub_1E7CE0@kujuUI@@YAXPAUtype_1E7CF0@1@@Z @ 0x001E7CE0
void sub_1E7CE0(type_1E7CF0 *arg_0)
{
    dword_50420C = arg_0;
}

// match: ?sub_1E7CF0@kujuUI@@YAPAUtype_1E7CF0@1@XZ @ 0x001E7CF0
type_1E7CF0 *sub_1E7CF0()
{
    return dword_50420C;
}

// match: ?sub_1E7D00@type_1E7CF0@kujuUI@@QAE_NPAUtype_3E7D08@2@@Z @ 0x001E7D00
bool type_1E7CF0::sub_1E7D00(type_3E7D08 *arg_0)
{
    return unk_0C.find(arg_0) != -1;
}

// match: ?sub_1E7D30@type_1E7CF0@kujuUI@@QAEXPAUtype_3E7D08@2@@Z @ 0x001E7D30
void type_1E7CF0::sub_1E7D30(type_3E7D08 *arg_0)
{
    type_3E7D08 *var_4 = sub_1E7FE0();
    if (var_4)
        var_4->sub_1F77B0();
    *unk_0C.next() = arg_0;
    arg_0->sub_1F7790();
    if (unk_504210.sub_1EF160())
        unk_504210.sub_1EF140();
}

// match: ?sub_1E7D90@type_1E7CF0@kujuUI@@QAEXPAUtype_3E7D08@2@@Z @ 0x001E7D90
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void type_1E7CF0::sub_1E7D90(type_3E7D08 *arg_0)
{
    if (arg_0->sub_1F7720())
        arg_0->sub_1F77B0();
    RwInt32 var_8 = unk_0C.find(arg_0);
    unk_0C.erase(var_8);
    type_3E7D08 *l4 = sub_1E7FE0();
    if (l4 && !l4->sub_1F7720())
        l4->sub_1F7790();
    if (unk_504210.sub_1EF160())
        unk_504210.sub_1EF140();
}

// match: ?vf_014@type_1E7CF0@kujuUI@@UAEXM@Z @ 0x001E7E20
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void type_1E7CF0::vf_014(RwReal arg_0)
{
    if (!unk_0C.empty())
    {
        ::type_1E61A0<type_3E7D08 *, 4> var_20;
        for (::type_1E61A0_it<type_3E7D08 *, 4> var_28 = unk_0C.begin(); var_28.ne(unk_0C.end()); var_28.inc())
            *var_20.next() = *var_28.get();
        ::type_1E61A0_it<type_3E7D08 *, 4> bp_8 = var_20.end();
        do
        {
            *var_20.at(0) = *unk_0C.at(0);
            bp_8.dec();
            type_3E7D08 *var_2C = *bp_8.get();
            var_2C->vf_014(arg_0);
        } while (bp_8.ne(var_20.begin()));
    }
}

// match: ?vf_018@type_1E7CF0@kujuUI@@UAEXPAUtype_1E4130@2@@Z @ 0x001E7F20
void type_1E7CF0::vf_018(type_1E4130 *arg_0)
{
    type_3E7D08 *var_4 = sub_1E7FE0();
    if (var_4)
    {
        if (unk_0C.count() == 1 || unk_21)
            var_4->vf_018(arg_0);
        else
        {
            for (::type_1E61A0_it<type_3E7D08 *, 4> var_C = unk_0C.begin(); *var_C.get() != var_4; var_C.inc())
            {
                type_3E7D08 *var_10 = *var_C.get();
                var_10->vf_018(arg_0);
            }
            arg_0->sub_1E4210(0xA0000000);
            var_4->vf_018(arg_0);
        }
    }
}

// match: ?sub_1E7FE0@type_1E7CF0@kujuUI@@QAEPAUtype_3E7D08@2@XZ @ 0x001E7FE0
type_3E7D08 *type_1E7CF0::sub_1E7FE0()
{
    return unk_0C.empty() ? 0 : *unk_0C.at(unk_0C.count() - 1);
}

// match: ?givenFocus@type_1E7CF0@kujuUI@@UAEXXZ @ 0x001E8030
void type_1E7CF0::givenFocus()
{
    type_3E7D08 *var_4 = sub_1E7FE0();
    if (var_4)
        var_4->sub_1F7790();
}

// match: ?lostFocus@type_1E7CF0@kujuUI@@UAEXXZ @ 0x001E8060
void type_1E7CF0::lostFocus()
{
    type_3E7D08 *var_4 = sub_1E7FE0();
    if (var_4)
        var_4->sub_1F77B0();
}

// match: ?processEvent@type_1E7CF0@kujuUI@@UAE?AW4eEventWasHandled@2@ABVcStateChange@2@@Z @ 0x001E8090
eEventWasHandled type_1E7CF0::processEvent(const cStateChange &arg_0)
{
    type_3E7D08 *var_4 = sub_1E7FE0();
    if (var_4)
        return var_4->processEvent(arg_0);
    return (eEventWasHandled)1;
}

// match: ?sub_1E80D0@type_1E7CF0@kujuUI@@QAEIXZ @ 0x001E80D0
RwUInt32 type_1E7CF0::sub_1E80D0()
{
    return unk_0C.count();
}

// match: ?sub_1E80F0@type_1E7CF0@kujuUI@@QAEX_N@Z @ 0x001E80F0
void type_1E7CF0::sub_1E80F0(bool arg_0)
{
    unk_20 = arg_0;
}

// match: ?sub_1E8110@type_1E7CF0@kujuUI@@QAEX_N@Z @ 0x001E8110
void type_1E7CF0::sub_1E8110(bool arg_0)
{
    unk_21 = arg_0;
}

// match: ?vf_020@type_1E7CF0@kujuUI@@UAE?AUtype_1E0330_rect@2@XZ @ 0x001E8130
type_1E0330_rect type_1E7CF0::vf_020()
{
    if (!unk_0C.empty())
        return (*unk_0C.at(unk_0C.count() - 1))->vf_020();
    return type_1E0330_rect();
}

// The array template's members this unit instantiates first.
// match: ??0?$type_1E61A0@PAUtype_3E7D08@kujuUI@@$03@@QAE@XZ @ 0x001E8190
// match: ?at@?$type_1E61A0@PAUtype_3E7D08@kujuUI@@$03@@QAEPAPAUtype_3E7D08@kujuUI@@I@Z @ 0x001E81B0
// match: ?erase@?$type_1E61A0@PAUtype_3E7D08@kujuUI@@$03@@QAEXI@Z @ 0x001E81E0
// match: ?find@?$type_1E61A0@PAUtype_3E7D08@kujuUI@@$03@@QAEHABQAUtype_3E7D08@kujuUI@@@Z @ 0x001E8250
// match: ?end@?$type_1E61A0@PAUtype_3E7D08@kujuUI@@$03@@QAE?AU?$type_1E61A0_it@PAUtype_3E7D08@kujuUI@@$03@@XZ @ 0x001E82A0
// match: ?empty@?$type_1E61A0@PAUtype_3E7D08@kujuUI@@$03@@QAE_NXZ @ 0x001E82D0
// match: ?dec@?$type_1E61A0_it@PAUtype_3E7D08@kujuUI@@$03@@QAEAAU1@XZ @ 0x001E82F0
// match: ?ne@?$type_1E61A0_it@PAUtype_3E7D08@kujuUI@@$03@@QBE_NABU1@@Z @ 0x001E8310
}
