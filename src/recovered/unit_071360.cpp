// The Alfa object manager: the pools of the objects scripts run on (the
// strings name them: "m_pobjectPool" and the others), their allocation and
// release by kind, the scripts' locals, and the global script registers.
// The file's original name is not recovered (M1), so it is named for its
// start address.

#include "rw/ostypes.h"
#include "game/functions.h"
#include "types/alfasched.h"
#include "types/alfaobjman.h"
#include "types/alfaobject.h"
#include "types/type_3D2E7C.h"

// Its data definitions (PLAN M5), in the image's address order.
// 0x00449400
RwReal dword_449400;
// 0x00449404
RwInt32 dword_449404;
// 0x00449408
type_449408 dword_449408[101];
// 0x004498C4
RwInt32 dword_4498C4;
// 0x004498C8
RwInt32 dword_4498C8;
// End of its data definitions.


// Globals with constructors defined here (their initializers and exit
// functions at the end of .text).
type_16C2A0 dword_449A50;
type_16C2A0 dword_449A30;
type_16C2A0 dword_4499F0;
type_16C2A0 dword_4499D0;
type_16C2A0 dword_449A10;
type_16C2A0 dword_4499B0;
type_16C2A0 dword_449950[3];
// Its data (PLAN M5): literals, constants and tables where the image has them.
// match: ??_C@_0O@HLCLEDEF@m_memPools?$FL2?$FN?$AA@ @ 0x003D2E8C
// match: ??_C@_0O@HJGNPNBM@m_memPools?$FL1?$FN?$AA@ @ 0x003D2E9C
// match: ??_C@_0O@HIKPJHCL@m_memPools?$FL0?$FN?$AA@ @ 0x003D2EAC
// match: ??_C@_0BA@BAPJOODB@m_inputListPool?$AA@ @ 0x003D2EBC
// match: ??_C@_0BD@MNHKKIDL@m_taskTreeDataPool?$AA@ @ 0x003D2ECC
// match: ??_C@_0BB@OIGIFJNK@m_taskObjectPool?$AA@ @ 0x003D2EE0
// match: ??_C@_0BJ@EGOBEGNE@m_stateMachineObjectPool?$AA@ @ 0x003D2EF4
// match: ??_C@_0P@LLIBOENI@m_aiObjectPool?$AA@ @ 0x003D2F10
// match: ??_C@_0O@KDNDJACL@m_pobjectPool?$AA@ @ 0x003D2F20
// match: ??_C@_0CK@BBHIGEJF@Alfa?5Mem?5Pool?5?$CFd?5is?5not?5empty?5at@ @ 0x003D2F30
// match: ??_C@_0DG@JEFPMNK@Alfa?5Task?5Tree?5Pool?5is?5not?5empty@ @ 0x003D2F5C
// match: ??_C@_0DI@COEAOBFH@Alfa?5Task?5Object?5Pool?5is?5not?5emp@ @ 0x003D2F94
// match: ??_C@_0EA@DPGEPDGC@Alfa?5StateMachine?5Object?5Pool?5is@ @ 0x003D2FD0
// match: ??_C@_0DH@JFFKEKAK@Alfa?5Input?5List?5Pool?5is?5not?5empt@ @ 0x003D3010
// match: ??_C@_0DG@IBJOHLIF@Alfa?5AI?5Object?5Pool?5is?5not?5empty@ @ 0x003D3048
// match: ??_C@_0DD@HIJBKDBG@Alfa?5Object?5Pool?5is?5not?5empty?5at@ @ 0x003D3080
// match: ??_C@_0BB@PBICNCNO@CheckAllocations?$AA@ @ 0x003D30B4
// match: __ehhandler$?sub_71870@@YAIXZ>1>8 @ 0x0041B4D8
// match: __ehhandler$?sub_71870@@YAIXZ>1 @ 0x0041B4E0
// match: __ehhandler$?sub_71990@@YAPAUtype_3D2CD0@@XZ>1>8 @ 0x0041B4FC
// match: __ehhandler$?sub_71990@@YAPAUtype_3D2CD0@@XZ>1 @ 0x0041B504
// match: __ehhandler$?sub_71A90@@YAPAUtype_3D2DB8@@XZ>1>8 @ 0x0041B520
// match: __ehhandler$?sub_71A90@@YAPAUtype_3D2DB8@@XZ>1 @ 0x0041B528
// match: __ehhandler$?sub_71B90@@YAPAUtype_46120@@XZ>1>8 @ 0x0041B544
// match: __ehhandler$?sub_71B90@@YAPAUtype_46120@@XZ>1 @ 0x0041B54C
// match: .CRT$XCU+0 @ 0x00426DBC
// match: .CRT$XCU+4 @ 0x00426DC0
// match: .CRT$XCU+8 @ 0x00426DC4
// match: .CRT$XCU+12 @ 0x00426DC8
// match: .CRT$XCU+16 @ 0x00426DCC
// match: .CRT$XCU+20 @ 0x00426DD0
// match: .CRT$XCU+24 @ 0x00426DD4

// match: _$E1 @ 0x00309A40
// match: _$E2 @ 0x0030DD80
// match: _$E4 @ 0x00309A60
// match: _$E5 @ 0x0030DD90
// match: _$E7 @ 0x00309A80
// match: _$E8 @ 0x0030DDA0
// match: _$E10 @ 0x00309AA0
// match: _$E11 @ 0x0030DDB0
// match: _$E13 @ 0x00309AC0
// match: _$E14 @ 0x0030DDC0
// match: _$E16 @ 0x00309AE0
// match: _$E17 @ 0x0030DDD0
// match: _$E19 @ 0x00309B00
// match: _$E20 @ 0x0030DDE0

struct type_46120;

type_3D2DB8 *sub_71A90();
type_46120 *sub_71B90();

// match: sub_71360 @ 0x00071360
// Clears the registers and sets the counters and the pools' sizes.
void sub_71360()
{
    RwInt32 var_4;

    for (var_4 = 0; var_4 < 101; var_4++) {
        dword_449408[var_4].unk_04 = 0;
        dword_449408[var_4].unk_00 = 0;
        dword_449408[var_4].unk_08 = 0;
    }
    dword_4498C4 = 1;
    dword_449404 = 1;
    dword_4498C8 = 125;
    dword_449400 = 3.0f;
}

// match: sub_713E0 @ 0x000713E0
// Sets the pools up.
void sub_713E0()
{
    dword_449A50.sub_16C2C0(100, 0x150, "m_pobjectPool", 4, 0);
    dword_449A10.sub_16C2C0(1100, 0x2C, "m_aiObjectPool", 4, 0);
    dword_449A30.sub_16C2C0(1000, 0xA0, "m_stateMachineObjectPool", 4, 0);
    dword_4499F0.sub_16C2C0(dword_4498C8, 0x124, "m_taskObjectPool", 4, 0);
    dword_4499D0.sub_16C2C0(dword_4498C8, 0xC, "m_taskTreeDataPool", 4, 0);
    dword_4499B0.sub_16C2C0((RwInt32)(dword_4498C8 * dword_449400), 0x18, "m_inputListPool", 4, 0);
    dword_449950[0].sub_16C2C0(900, 0x20, "m_memPools[0]", 4, 0);
    dword_449950[1].sub_16C2C0(128, 0x80, "m_memPools[1]", 4, 0);
    dword_449950[2].sub_16C2C0(75, 0x180, "m_memPools[2]", 4, 0);
}

// match: sub_714F0 @ 0x000714F0
// Restart: checks the pools and clears the registers.
void sub_714F0()
{
    RwInt32 var_4;

    sub_715E0();
    for (var_4 = 0; var_4 < 101; var_4++) {
        dword_449408[var_4].unk_04 = 0;
        dword_449408[var_4].unk_00 = 0;
        dword_449408[var_4].unk_08 = 0;
    }
    dword_4498C4 = 1;
    dword_449404 = 1;
}

// match: sub_71560 @ 0x00071560
// Shutdown: checks the pools and shuts them down.
void sub_71560()
{
    sub_715E0();
    dword_449A50.sub_16C4D0(1);
    dword_449A30.sub_16C4D0(1);
    dword_4499F0.sub_16C4D0(1);
    dword_4499D0.sub_16C4D0(1);
    dword_449A10.sub_16C4D0(1);
    dword_4499B0.sub_16C4D0(1);
    dword_449950[0].sub_16C4D0(1);
    dword_449950[1].sub_16C4D0(1);
    dword_449950[2].sub_16C4D0(1);
}

// match: sub_715E0 @ 0x000715E0
// Warns of pools with elements still out.
void sub_715E0()
{
    type_16C2A0 *local_8;
    RwInt32 var_4;

    if (dword_449A50.in_use()) {
        sub_19A750("CheckAllocations");
        sub_19A750("Alfa Object Pool is not empty at restart/shutdown!");
    }
    if (dword_449A10.in_use()) {
        sub_19A750("CheckAllocations");
        sub_19A750("Alfa AI Object Pool is not empty at restart/shutdown!");
    }
    if (dword_4499B0.in_use()) {
        sub_19A750("CheckAllocations");
        sub_19A750("Alfa Input List Pool is not empty at restart/shutdown!");
    }
    if (dword_449A30.in_use()) {
        sub_19A750("CheckAllocations");
        sub_19A750("Alfa StateMachine Object Pool is not empty at restart/shutdown!");
    }
    if (dword_4499F0.in_use()) {
        sub_19A750("CheckAllocations");
        sub_19A750("Alfa Task Object Pool is not empty at restart/shutdown!");
    }
    if (dword_4499D0.in_use()) {
        sub_19A750("CheckAllocations");
        sub_19A750("Alfa Task Tree Pool is not empty at restart/shutdown!");
    }
    for (var_4 = 0; var_4 < 3; var_4++) {
        local_8 = &dword_449950[var_4];
        if (local_8->in_use()) {
            sub_19A750("CheckAllocations");
            sub_19A750("Alfa Mem Pool %d is not empty at restart!");
        }
    }
}

// match: ?sub_71770@@YAPAUtype_3D2C88@@H@Z @ 0x00071770
type_3D2C88 *sub_71770(RwInt32 arg_0)
{
    switch (arg_0) {
    case 1:
        return sub_71990();
    case 2:
        return sub_71A90();
    case 3:
        return (type_3D2C88 *)sub_71B90();
    }
    return 0;
}

// match: ?sub_717B0@@YAXPAUtype_3D2C88@@@Z @ 0x000717B0
void sub_717B0(type_3D2C88 *arg_0)
{
    switch (arg_0->vf_014()) {
    case 1:
        sub_67520(arg_0->get_unk_04());
        break;
    case 2:
        sub_67520(arg_0->get_unk_04());
        break;
    case 3:
        sub_67520(arg_0->get_unk_04());
        break;
    }
}

// match: ?sub_71820@@YAPAUtype_3D2E20_118@@XZ @ 0x00071820
type_3D2E20_118 *sub_71820()
{
    type_3D2E20_118 *var_4;

    var_4 = (type_3D2E20_118 *)dword_4499B0.sub_16C5A0(0);
    var_4->unk_04 = 0;
    var_4->unk_00 = 0;
    return var_4;
}

// match: ?sub_71850@@YAXPAUtype_3D2E20_118@@@Z @ 0x00071850
void sub_71850(type_3D2E20_118 *arg_0)
{
    dword_4499B0.sub_16C710(arg_0);
}

// match: ?sub_71870@@YAIXZ @ 0x00071870
// match: __ehhandler$?sub_71870@@YAIXZ-0x11 @ 0x002FF8A0
// match: __ehhandler$?sub_71870@@YAIXZ @ 0x002FF8B1
// A new AI object; returns its handle.
RwUInt32 sub_71870()
{
    type_3D2E7C *var_10;
    RwUInt32 lv_14;

    var_10 = (type_3D2E7C *)dword_449A10.sub_16C5A0(0);
    var_10 = new (var_10) type_3D2E7C;
    var_10->vf_000(dword_4498C4++);
    lv_14 = sub_673C0((type_67620 *)var_10, 4);
    var_10->sub_1E7540(lv_14);
    return var_10->get_unk_04();
}

// match: ?sub_71940@@YAXPAUtype_3D2E7C@@@Z @ 0x00071940
void sub_71940(type_3D2E7C *arg_0)
{
    arg_0->unk_04 = 0;
    arg_0->sub_70D40();
    dword_449A10.sub_16C710(arg_0);
}

// match: ?sub_71970@@YAXPAUtype_3D2C88@@@Z @ 0x00071970
void sub_71970(type_3D2C88 *arg_0)
{
    sub_67520(arg_0->get_unk_04());
}

// match: ?sub_71990@@YAPAUtype_3D2CD0@@XZ @ 0x00071990
type_3D2CD0 *sub_71990()
{
    type_3D2CD0 *var_10;
    RwUInt32 lv_14;

    var_10 = (type_3D2CD0 *)dword_449A50.sub_16C5A0(0);
    var_10 = new (var_10) type_3D2CD0;
    var_10->vf_054(1, dword_4498C4++);
    lv_14 = sub_673C0((type_67620 *)var_10, 1);
    var_10->sub_1E7540(lv_14);
    return var_10;
}

// match: ?sub_71A60@@YAXPAUtype_3D2CD0@@@Z @ 0x00071A60
void sub_71A60(type_3D2CD0 *arg_0)
{
    arg_0->unk_04 = 0;
    arg_0->vf_050();
    dword_449A50.sub_16C710(arg_0);
}

// match: ?sub_71A90@@YAPAUtype_3D2DB8@@XZ @ 0x00071A90
type_3D2DB8 *sub_71A90()
{
    type_3D2DB8 *var_10;
    RwUInt32 lv_14;

    var_10 = (type_3D2DB8 *)dword_449A30.sub_16C5A0(0);
    var_10 = new (var_10) type_3D2DB8;
    var_10->vf_04C(2, dword_4498C4++);
    lv_14 = sub_673C0((type_67620 *)var_10, 2);
    var_10->sub_1E7540(lv_14);
    return var_10;
}

// match: ?sub_71B60@@YAXPAUtype_3D2DB8@@@Z @ 0x00071B60
void sub_71B60(type_3D2DB8 *arg_0)
{
    arg_0->unk_04 = 0;
    arg_0->vf_050();
    dword_449A30.sub_16C710(arg_0);
}

// match: ?sub_71B90@@YAPAUtype_46120@@XZ @ 0x00071B90
type_46120 *sub_71B90()
{
    type_3D2E20 *var_10;
    RwUInt32 lv_14;

    var_10 = (type_3D2E20 *)dword_4499F0.sub_16C5A0(0);
    var_10 = new (var_10) type_3D2E20;
    var_10->vf_054(3, dword_4498C4++);
    lv_14 = sub_673C0((type_67620 *)var_10, 3);
    var_10->sub_1E7540(lv_14);
    return (type_46120 *)var_10;
}

// match: ?sub_71C60@@YAXPAUtype_3D2E20@@@Z @ 0x00071C60
void sub_71C60(type_3D2E20 *arg_0)
{
    if (arg_0->unk_114 != 0)
        arg_0->sub_703C0();
    arg_0->unk_04 = 0;
    arg_0->vf_050();
    dword_4499F0.sub_16C710(arg_0);
}

// match: ?sub_71CA0@@YAPAUtype_3D2E20_114@@XZ @ 0x00071CA0
type_3D2E20_114 *sub_71CA0()
{
    type_3D2E20_114 *var_4;

    var_4 = (type_3D2E20_114 *)dword_4499D0.sub_16C5A0(0);
    return var_4;
}

// match: ?sub_71CC0@@YAXPAUtype_3D2E20_114@@@Z @ 0x00071CC0
void sub_71CC0(type_3D2E20_114 *arg_0)
{
    dword_4499D0.sub_16C710(arg_0);
}

// match: ?sub_71CE0@@YAPAHH@Z @ 0x00071CE0
// Scripts' locals of arg_0 bytes from the first memory pool with room.
RwInt32 *sub_71CE0(RwInt32 arg_0)
{
    RwInt32 var_4;

    for (var_4 = 0; var_4 < 3; var_4++) {
        if (!dword_449950[var_4].sub_16C7E0() && arg_0 <= dword_449950[var_4].get_unk_10())
            return (RwInt32 *)dword_449950[var_4].sub_16C5A0(0);
    }
    return 0;
}

// match: ?sub_71D50@@YAXPAH@Z @ 0x00071D50
void sub_71D50(RwInt32 *arg_0)
{
    RwInt32 var_4;

    for (var_4 = 0; var_4 < 3; var_4++) {
        if (dword_449950[var_4].sub_16C770(arg_0))
            dword_449950[var_4].sub_16C710(arg_0);
    }
}

// match: ?sub_71DB0@@YAXHHPAX@Z @ 0x00071DB0
void sub_71DB0(RwInt32 arg_0, RwInt32 arg_4, void *arg_8)
{
    switch (arg_4) {
    case 0:
        ((RwInt32 *)arg_8)[0] = dword_449408[arg_0].unk_00;
        break;
    case 1:
        ((RwInt32 *)arg_8)[0] = dword_449408[arg_0].unk_00;
        break;
    case 2:
        ((RwInt32 *)arg_8)[0] = dword_449408[arg_0].unk_00;
        break;
    case 3:
        ((RwInt32 *)arg_8)[0] = dword_449408[arg_0].unk_00;
        ((RwInt32 *)arg_8)[1] = dword_449408[arg_0].unk_04;
        break;
    }
}

// match: ?sub_71E40@@YAXHHPAX@Z @ 0x00071E40
void sub_71E40(RwInt32 arg_0, RwInt32 arg_4, void *arg_8)
{
    switch (arg_4) {
    case 0:
    case 1:
    case 2:
        dword_449408[arg_0].unk_00 = ((RwInt32 *)arg_8)[0];
        dword_449408[arg_0].unk_08 = arg_4;
        break;
    case 3:
        dword_449408[arg_0].unk_00 = ((RwInt32 *)arg_8)[0];
        dword_449408[arg_0].unk_04 = ((RwInt32 *)arg_8)[1];
        dword_449408[arg_0].unk_08 = arg_4;
        break;
    }
}
