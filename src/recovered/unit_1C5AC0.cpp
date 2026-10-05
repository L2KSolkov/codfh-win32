// Split from unit_1C5700.cpp at 0x1C5AC0, where the image starts another object (message
// handlers): its .rdata begins at 0x3E382C with its own constant block (0.01, 0.01,
// 16.666666) before sub_1C5CA0's text (PLAN M7).

#include "game/netmsg.h"
#include "game/uiglue.h"
#include "game/gameloop.h"
#include "types/type_DC400.h"
#include "types/asynchload.h"

// Its data definitions (PLAN M5), in the image's address order.
// 0x003E382C
extern const RwReal flt_3E382C = 0.01f;
// 0x003E3830
extern const RwReal flt_3E3830 = 0.01f;
// 0x003E3834
extern const RwReal flt_3E3834 = 16.666666f;

// match: ?flt_3E382C@@3MB @ 0x003E382C
// match: ?flt_3E3830@@3MB @ 0x003E3830
// match: ?flt_3E3834@@3MB @ 0x003E3834


// match: ??0type_3E11AC@@QAE@XZ @ 0x001C5D40
// match: ??_C@_0BO@COHMMIEG@Local?5player?5threw?5a?5grenade?6?$AA@ @ 0x003E3838

// match: ?vf_000@type_3E1194@@UAEXPAUtype_1F8560@@@Z @ 0x001C5AC0
void type_3E1194::vf_000(type_1F8560 *arg_0)
{
    arg_0->sub_1F86D0(unk_04, 0, 500.0f, 8);
    arg_0->sub_1F85F0(unk_08.unk_00);
    arg_0->sub_1F85F0(unk_08.unk_04);
    arg_0->sub_1F85F0(unk_08.unk_08);
    arg_0->sub_1F85F0(unk_14);
}
// match: ?vf_004@type_3E1194@@UAEXPAUtype_1F8560@@@Z @ 0x001C5B30
void type_3E1194::vf_004(type_1F8560 *arg_0)
{
    unk_04 = arg_0->sub_1F8640(0, 500.0f, 8);
    unk_08.unk_00 = arg_0->sub_1F85A0();
    unk_08.unk_04 = arg_0->sub_1F85A0();
    unk_08.unk_08 = arg_0->sub_1F85A0();
    unk_14 = arg_0->sub_1F85A0();
}
// match: ?vf_000@type_3E11AC@@UAEXPAUtype_1F8560@@@Z @ 0x001C5B90
void type_3E11AC::vf_000(type_1F8560 *arg_0)
{
    arg_0->sub_1F85F0(unk_04.unk_00);
    arg_0->sub_1F85F0(unk_04.unk_04);
    arg_0->sub_1F85F0(unk_04.unk_08);
    arg_0->sub_1F85F0(unk_10.unk_00);
    arg_0->sub_1F85F0(unk_10.unk_04);
    arg_0->sub_1F85F0(unk_10.unk_08);
    arg_0->sub_1F8520(unk_1C);
    arg_0->sub_1F8860(unk_20, 8);
}
// match: ?vf_004@type_3E11AC@@UAEXPAUtype_1F8560@@@Z @ 0x001C5C20
void type_3E11AC::vf_004(type_1F8560 *arg_0)
{
    unk_04.unk_00 = arg_0->sub_1F85A0();
    unk_04.unk_04 = arg_0->sub_1F85A0();
    unk_04.unk_08 = arg_0->sub_1F85A0();
    unk_10.unk_00 = arg_0->sub_1F85A0();
    unk_10.unk_04 = arg_0->sub_1F85A0();
    unk_10.unk_08 = arg_0->sub_1F85A0();
    unk_1C = arg_0->sub_1F8560();
    unk_20 = arg_0->sub_1F8810(8);
}
// match: ?sub_1C5CA0@@YAXABUtype_1F8560_v@@0II@Z @ 0x001C5CA0
void sub_1C5CA0(const type_1F8560_v &arg_0, const type_1F8560_v &arg_4, RwUInt32 arg_8, RwUInt32 arg_C)
{
    type_3E11AC var_24;

    var_24.unk_04.unk_00 = arg_0.unk_00;
    var_24.unk_04.unk_04 = arg_0.unk_04;
    var_24.unk_04.unk_08 = arg_0.unk_08;
    var_24.unk_10.unk_00 = arg_4.unk_00;
    var_24.unk_10.unk_04 = arg_4.unk_04;
    var_24.unk_10.unk_08 = arg_4.unk_08;
    var_24.unk_1C = arg_8;
    var_24.unk_20 = arg_C;
    type_4F8058::get()->sub_1DDDB0(&var_24, type_4F8054::get()->get_unk_B0()->sub_1A8050());
    sub_1A8A70(&unk_4F7EB8, "Local player threw a grenade\n");
}
// match: ?vf_000@type_3E114C@@UAEXPAUtype_1F8560@@@Z @ 0x001C5DC0
void type_3E114C::vf_000(type_1F8560 *arg_0)
{
    RwInt32 var_4;

    arg_0->sub_1F86D0(unk_04, 0, 500.0f, 8);
    arg_0->sub_1F8860(unk_0C, 8);
    arg_0->sub_1F8860(unk_08, 5);
    arg_0->sub_1F8860(unk_0D, 4);
    var_4 = sub_1F84A0(110);
    arg_0->sub_1F8860(unk_10, var_4);
}
// match: ?vf_004@type_3E114C@@UAEXPAUtype_1F8560@@@Z @ 0x001C5E40
void type_3E114C::vf_004(type_1F8560 *arg_0)
{
    RwInt32 var_4;

    unk_04 = arg_0->sub_1F8640(0, 500.0f, 8);
    unk_0C = arg_0->sub_1F8810(8);
    unk_08 = arg_0->sub_1F8810(5);
    unk_0D = arg_0->sub_1F8810(4);
    var_4 = sub_1F84A0(110);
    unk_10 = arg_0->sub_1F8810(var_4);
}
// match: ?vf_000@type_3E1164@@UAEXPAUtype_1F8560@@@Z @ 0x001C5EC0
void type_3E1164::vf_000(type_1F8560 *arg_0)
{
    RwInt32 var_4;

    arg_0->sub_1F86D0(unk_04, 0, 500.0f, 8);
    arg_0->sub_1F85F0(unk_08.unk_00);
    arg_0->sub_1F85F0(unk_08.unk_04);
    arg_0->sub_1F85F0(unk_08.unk_08);
    arg_0->sub_1F85F0(unk_14);
    arg_0->sub_1F8860(unk_18, 8);
    var_4 = sub_1F84A0(110);
    arg_0->sub_1F8860(unk_1C, var_4);
}
// match: ?vf_004@type_3E1164@@UAEXPAUtype_1F8560@@@Z @ 0x001C5F60
void type_3E1164::vf_004(type_1F8560 *arg_0)
{
    RwInt32 var_4;

    unk_04 = arg_0->sub_1F8640(0, 500.0f, 8);
    unk_08.unk_00 = arg_0->sub_1F85A0();
    unk_08.unk_04 = arg_0->sub_1F85A0();
    unk_08.unk_08 = arg_0->sub_1F85A0();
    unk_14 = arg_0->sub_1F85A0();
    unk_18 = arg_0->sub_1F8810(8);
    var_4 = sub_1F84A0(110);
    unk_1C = arg_0->sub_1F8810(var_4);
}
// match: ?vf_000@type_3E117C@@UAEXPAUtype_1F8560@@@Z @ 0x001C5FF0
void type_3E117C::vf_000(type_1F8560 *arg_0)
{
    arg_0->sub_1F8860(unk_04, 3);
    arg_0->sub_1F8860(unk_08, 5);
}
// match: ?vf_004@type_3E117C@@UAEXPAUtype_1F8560@@@Z @ 0x001C6020
void type_3E117C::vf_004(type_1F8560 *arg_0)
{
    unk_04 = arg_0->sub_1F8810(3);
    unk_08 = arg_0->sub_1F8810(5);
}
// match: ?sub_1C6050@@YAXXZ @ 0x001C6050
void sub_1C6050()
{
    RwUInt32 var_4;

    for (var_4 = 0; var_4 < 5; var_4++)
        dword_4FE688[var_4] = 0;
}
// match: ?vf_004@type_3E0F84@@UAEXPAUtype_1F8560@@@Z @ 0x001C6080
void type_3E0F84::vf_004(type_1F8560 *arg_0)
{
    unk_04 = arg_0->sub_1F8560();
}
