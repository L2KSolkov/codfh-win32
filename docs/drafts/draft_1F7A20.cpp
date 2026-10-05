/*
 * kujuUI's widget creators' base and the factory's readers of a scope's
 * values (game/kujuui.h): the creator's validator, a widget's rectangle, its
 * look and font, its hooks into the registry; the layout page's links; and
 * the looks' state names.
 */
#include <string.h>
#include "game/kujuui.h"
#include "types/type_4D1DB8.h"

using namespace kujuUI;

// match: ??0type_3E7D94@kujuUI@@QAE@XZ @ 0x001F7A20
type_3E7D94::type_3E7D94()
{
}

// match: ??1type_3E7D94@kujuUI@@UAE@XZ @ 0x001F7A40
type_3E7D94::~type_3E7D94()
{
}

// match: ?sub_1F7A60@kujuUI@@YAXPBXPBD@Z @ 0x001F7A60
void kujuUI::sub_1F7A60(const void *arg_0, const RwChar *arg_4)
{
    RwInt32 var_4;
}

// match: ?sub_1F7A70@type_3E7D94@kujuUI@@QAEXPAPAVcScopeValidator@2@@Z @ 0x001F7A70
void type_3E7D94::sub_1F7A70(cScopeValidator **arg_0)
{
    *arg_0 = new cScopeValidator(vf_004(), "end", 1);
    vf_00C(*arg_0);
}

// match: ?sub_1F7B10@kujuUI@@YAHPAUtype_1C8DF0@1@PBDPAUtype_1E0330_rect@1@@Z @ 0x001F7B10
// arg_4 is a look (see sub_1F7EA0).
RwInt32 kujuUI::sub_1F7B10(type_1C8DF0 *arg_0, const RwChar *arg_4, type_1E0330_rect *arg_8)
{
    sub_1F7A60(arg_0, "position");
    RwInt32 var_8 = 0;
    type_1C8DF0_104 *var_4 = arg_0->sub_1C90B0(sub_1E34E0());
    if (var_4)
    {
        arg_8->unk_00 = var_4->sub_1C9890(0)->sub_1E3480();
        arg_8->unk_04 = var_4->sub_1C9890(1)->sub_1E3480();
        arg_8->unk_08 = var_4->sub_1C9890(2)->sub_1E3480();
        arg_8->unk_0C = var_4->sub_1C9890(3)->sub_1E3480();
        var_8 = 1;
    }
    else
    {
        type_1C8DF0_104 *var_C = arg_0->sub_1C90B0(sub_1E34D0());
        if (arg_4)
        {
            const type_1E0330_rect *var_10 = &((type_1E3BA0 *)arg_4)->sub_1E3BF0(0)->get_unk_2C();
            RwRaster *var_14 = (RwRaster *)((type_1E3BA0 *)arg_4)->sub_1E3BF0(0)->get_unk_3C()->sub_1ED650();
            arg_8->unk_00 = var_C->sub_1C9890(0)->sub_1E3480();
            arg_8->unk_04 = var_C->sub_1C9890(1)->sub_1E3480();
            arg_8->unk_08 = var_14->width * var_10->width() + arg_8->unk_00;
            arg_8->unk_0C = var_14->height * var_10->height() + arg_8->unk_04;
            var_8 = 1;
        }
        else
        {
            var_8 = 2;
        }
    }
    sub_1F7A60(var_8, pResourcePath);
    return var_8;
}

// match: ?sub_1F7CC0@kujuUI@@YAHPAUtype_1C8DF0@1@PAUtype_1ED670@1@PAUtype_3E75E8@1@@Z @ 0x001F7CC0
RwInt32 kujuUI::sub_1F7CC0(type_1C8DF0 *arg_0, type_1ED670 *arg_4, type_3E75E8 *arg_8)
{
    RwInt32 var_4 = 0;
    type_1C8DF0_104 *var_8 = arg_0->sub_1C90B0(sub_1E34F0());
    if (var_8)
    {
        type_1F7CC0_hook *var_C;
        arg_4->sub_1E0D50(var_8->sub_1C9890(0)->sub_1E3480(), 4, &var_C);
        if (var_C)
        {
            var_4 = 1;
            var_C->sub_1E7540(arg_8);
        }
        else
        {
            var_4 = 2;
        }
    }
    if (var_4)
    {
        sub_1F7A60(arg_0, sub_1E34F0()->get_unk_00());
        sub_1F7A60(var_4, var_8->sub_1C9890(0)->sub_1E3480());
    }
    return var_4;
}

// match: ?sub_1F7D80@kujuUI@@YAHPAUtype_1C8DF0@1@HPAPBD@Z @ 0x001F7D80
RwInt32 kujuUI::sub_1F7D80(type_1C8DF0 *arg_0, RwInt32 arg_4, const RwChar **arg_8)
{
    RwInt32 var_4 = sub_1F7EA0(arg_0, sub_1E3500(), arg_4, arg_8);
    return var_4;
}

// match: ?sub_1F7DB0@kujuUI@@YAHPAUtype_1C8DF0@1@PAUtype_1ED670@1@PAUtype_3E76E4@1@@Z @ 0x001F7DB0
RwInt32 kujuUI::sub_1F7DB0(type_1C8DF0 *arg_0, type_1ED670 *arg_4, type_3E76E4 *arg_8)
{
    RwInt32 var_4 = 0;
    type_1C8DF0_104 *var_8 = arg_0->sub_1C90B0(sub_1E3510());
    if (var_8)
    {
        type_1F7DB0_hook *var_C;
        arg_4->sub_1E0D50(var_8->sub_1C9890(0)->sub_1E3480(), 5, &var_C);
        if (var_C)
        {
            var_4 = 1;
            var_C->sub_1E7540(arg_8);
        }
        else
        {
            var_4 = 2;
        }
    }
    if (var_4)
    {
        sub_1F7A60(arg_0, sub_1E34F0()->get_unk_00());
        sub_1F7A60(var_4, var_8->sub_1C9890(0)->sub_1E3480());
    }
    return var_4;
}

// match: ?sub_1F7E70@kujuUI@@YAHPAUtype_1C8DF0@1@HPAH@Z @ 0x001F7E70
RwInt32 kujuUI::sub_1F7E70(type_1C8DF0 *arg_0, RwInt32 arg_4, RwInt32 *arg_8)
{
    RwInt32 var_4 = sub_1F7F40(arg_0, sub_1E3560(), arg_4, (RwUInt32 *)arg_8);
    return var_4;
}

// match: ?sub_1F7EA0@kujuUI@@YAHPAUtype_1C8DF0@1@PBUtype_1C9590@1@HPAPBD@Z @ 0x001F7EA0
// arg_8 is the looks by name (the factory's arg_4), and *arg_C the look.
RwInt32 kujuUI::sub_1F7EA0(type_1C8DF0 *arg_0, const type_1C9590 *arg_4, RwInt32 arg_8, const RwChar **arg_C)
{
    sub_1F7A60(arg_0, arg_4->get_unk_00());
    RwInt32 var_8 = 0;
    *arg_C = 0;
    const RwChar *var_4 = pResourcePath;
    type_1C8DF0_104 *var_C = arg_0->sub_1C90B0(arg_4);
    if (var_C)
    {
        var_4 = (const RwChar *)var_C->sub_1C9890(0)->sub_1E3480();
        *arg_C = (const RwChar *)((type_1EFCF0<type_1E3BA0> *)arg_8)->sub_1ED670(var_4);
        var_8 = *arg_C ? 1 : 2;
    }
    sub_1F7A60(var_8, var_4);
    return var_8;
}

// match: ?sub_1F7F40@kujuUI@@YAHPAUtype_1C8DF0@1@PBUtype_1C9590@1@HPAI@Z @ 0x001F7F40
// arg_8 is the font sets by name (the factory's arg_8), and *arg_C the set.
RwInt32 kujuUI::sub_1F7F40(type_1C8DF0 *arg_0, const type_1C9590 *arg_4, RwInt32 arg_8, RwUInt32 *arg_C)
{
    sub_1F7A60(arg_0, arg_4->get_unk_00());
    RwUInt32 var_4 = 0;
    type_1C8DF0_104 *var_C = arg_0->sub_1C90B0(arg_4);
    RwInt32 var_10 = 0;
    const RwChar *var_8 = pResourcePath;
    if (var_C)
    {
        var_8 = (const RwChar *)var_C->sub_1C9890(0)->sub_1E3480();
        var_4 = (RwUInt32)((type_1EFCF0<type_1E6350> *)arg_8)->sub_1ED670(var_8);
        var_10 = var_4 ? 1 : 2;
    }
    *arg_C = var_4;
    sub_1F7A60(var_10, var_8);
    return var_10;
}

// match: ?sub_1F7FE0@kujuUI@@YA_NPAUtype_1C8DF0@1@@Z @ 0x001F7FE0
bool kujuUI::sub_1F7FE0(type_1C8DF0 *arg_0)
{
    return !arg_0->sub_1C90B0(sub_1E3610());
}

// match: ?sub_1F8000@kujuUI@@YAHXZ @ 0x001F8000
RwInt32 kujuUI::sub_1F8000()
{
    return dword_42D254;
}

// match: ??0type_1F8040@kujuUI@@QAE@PAUtype_3E7D08@1@0H@Z @ 0x001F8010
type_1F8040::type_1F8040(type_3E7D08 *arg_0, type_3E7D08 *arg_4, RwInt32 arg_8)
{
    unk_00 = arg_0;
    unk_04 = arg_4;
    unk_08 = arg_8;
}

// match: ??0type_1F8040@kujuUI@@QAE@PAUtype_3E7D08@1@H@Z @ 0x001F8040
type_1F8040::type_1F8040(type_3E7D08 *arg_0, RwInt32 arg_4)
{
    unk_00 = arg_0;
    unk_04 = 0;
    unk_08 = arg_4;
}

// match: ??Mtype_1F8040@kujuUI@@QBE_NABU01@@Z @ 0x001F8070
bool type_1F8040::operator<(const type_1F8040 &arg_0) const
{
    if (unk_00 < arg_0.sub_1EE9D0())
        return true;
    if (unk_00 > arg_0.sub_1EE9D0())
        return false;
    return unk_08 < arg_0.sub_FB710();
}

// match: ?sub_1F80C0@kujuUI@@YAPBDXZ @ 0x001F80C0
const RwChar *kujuUI::sub_1F80C0()
{
    return "normal";
}

// match: ?sub_1F80D0@kujuUI@@YAPBDXZ @ 0x001F80D0
const RwChar *kujuUI::sub_1F80D0()
{
    return "highlight";
}

// match: ?sub_1F80E0@kujuUI@@YAPBDXZ @ 0x001F80E0
const RwChar *kujuUI::sub_1F80E0()
{
    return "highlightalt";
}

// match: ?sub_1F80F0@kujuUI@@YAPBDXZ @ 0x001F80F0
const RwChar *kujuUI::sub_1F80F0()
{
    return "disabled";
}

// match: ?sub_1F8100@kujuUI@@YAPBDXZ @ 0x001F8100
const RwChar *kujuUI::sub_1F8100()
{
    return "dishighlight";
}

// match: ?sub_1F8110@kujuUI@@YAPBDXZ @ 0x001F8110
const RwChar *kujuUI::sub_1F8110()
{
    return "pressing";
}

// match: ?sub_1F8120@kujuUI@@YAHPBD@Z @ 0x001F8120
RwInt32 kujuUI::sub_1F8120(const RwChar *arg_0)
{
    if (!strcmp(arg_0, sub_1F80C0()))
        return 0;
    if (!strcmp(arg_0, sub_1F80D0()))
        return 1;
    if (!strcmp(arg_0, sub_1F80E0()))
        return 2;
    if (!strcmp(arg_0, sub_1F80F0()))
        return 3;
    if (!strcmp(arg_0, sub_1F8100()))
        return 4;
    if (!strcmp(arg_0, sub_1F8110()))
        return 5;
    return 6;
}
