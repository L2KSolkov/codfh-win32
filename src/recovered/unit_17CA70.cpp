// The shrimps (types/type_3DDE70.h, types/type_17CC40.h).

#include "rw/ostypes.h"
#include "rw/batypes.h"
#include "rw/bamatrix.h"
#include "rw/bavector.h"
#include "game/functions.h"
#include "game/data.h"
#include "game/gameloop.h"
#include "game/frand.h"
#include "game/clones.h"
#include "game/clumputil.h"
#include "types/type_3D3548.h"
#include "types/type_3D32F8.h"
#include "types/type_3DF8D8.h"
#include "types/type_44350.h"
#include "types/alfasched.h"
#include "types/SplinePath.h"
#include "types/ShrimpTrigger.h"
#include "types/type_17CC40.h"
#include "types/type_3DDE70.h"
#include <string.h>
#include "game/particles.h"
#include "game/worldmgr.h"
#include "rw/badevice.h"
#include "rw/rpworld.h"

// Its data definitions (PLAN M5), in the image's address order.
// 0x003DDE5C
extern const RwReal flt_3DDE5C = 16.666666f;
// 0x003DDE60
extern const RwV3d stru_3DDE60 = { 0.0f, 0.0f, 1.0f };
// 0x003DDE6C
extern const RwReal flt_3DDE6C = 16.666666f;
// 0x004E7238
struct type_17CC40 *dword_4E7238;
// 0x004E723C
type_3D3548 *dword_4E723C;
// 0x004E7240
RwInt32 dword_4E7240;
// End of its data definitions.


// Globals with constructors defined here (their initializers and exit
// functions at the end of .text).
type_16C2A0 dword_4E7244;
// Its data (PLAN M5): literals, constants and tables where the image has them.
// match: ?flt_3DDE5C@@3MB @ 0x003DDE5C
// match: ?stru_3DDE60@@3URwV3d@@B @ 0x003DDE60
// match: ?flt_3DDE6C@@3MB @ 0x003DDE6C
// match: ??_7type_3DDE70@@6B@ @ 0x003DDE70
// match: __ehhandler$??0type_3DDE70@@QAE@PAVShrimpTrigger@@@Z>1>8 @ 0x0041E4B0
// match: __ehhandler$??0type_3DDE70@@QAE@PAVShrimpTrigger@@@Z>1 @ 0x0041E4B8
// match: __ehhandler$?sub_17CB30@@YAPAUtype_3DDE70@@PAVShrimpTrigger@@@Z>1>8 @ 0x0041E4D4
// match: __ehhandler$?sub_17CB30@@YAPAUtype_3DDE70@@PAVShrimpTrigger@@@Z>1 @ 0x0041E4DC
// match: .CRT$XCU+0 @ 0x00427168

// match: _$E2 @ 0x0030BF40
// match: _$E3 @ 0x0030E980
// match: ??0type_3DDE70@@QAE@PAVShrimpTrigger@@@Z @ 0x0017CA70
// match: __ehhandler$??0type_3DDE70@@QAE@PAVShrimpTrigger@@@Z-0x8 @ 0x00302180
// match: __ehhandler$??0type_3DDE70@@QAE@PAVShrimpTrigger@@@Z @ 0x00302188
// sp-match: ??0type_3DDE70@@QAE@PAVShrimpTrigger@@@Z @ 0x00115D10
// sp-match: _$E2 @ 0x0021DE10
// sp-match: _$E3 @ 0x0021ED40

type_3DDE70::type_3DDE70(ShrimpTrigger *arg_0)
{
    sub_CCCD0((type_712B0 *)arg_0);
    unk_2C = arg_0->vf_018() | 0x800000; // not an address: entity kind bits
}

// match: ??_Gtype_3DDE70@@UAEPAXI@Z @ 0x0017CAE0
// sp-match: ??_Gtype_3DDE70@@UAEPAXI@Z @ 0x00116190
// (Compiler-written: the destructor, then operator delete.)

// match: ??1type_3DDE70@@UAE@XZ @ 0x0017CB10
// sp-match: ??1type_3DDE70@@UAE@XZ @ 0x001161B0
// (Implicit: the base's destructor.)

// match: ?sub_17CB30@@YAPAUtype_3DDE70@@PAVShrimpTrigger@@@Z @ 0x0017CB30
// match: __ehhandler$?sub_17CB30@@YAPAUtype_3DDE70@@PAVShrimpTrigger@@@Z-0x11 @ 0x003021A0
// match: __ehhandler$?sub_17CB30@@YAPAUtype_3DDE70@@PAVShrimpTrigger@@@Z @ 0x003021B1
// sp-match: ?sub_17CB30@@YAPAUtype_3DDE70@@PAVShrimpTrigger@@@Z @ 0x00115D80
type_3DDE70 *sub_17CB30(ShrimpTrigger *arg_0)
{
    type_3DDE70 *var_10;

    var_10 = (type_3DDE70 *)sub_D56D0(0x3B0, arg_0->unk_24_18, arg_0->vf_008());
    if (var_10 != 0) {
        var_10 = new (var_10) type_3DDE70(arg_0);
        if (var_10->unk_28 & 0x400000) { // not an address: entity flag
            sub_D5A60(var_10, 0);
            var_10 = 0;
        }
    }
#ifndef CODFH_SP // single player compiles the debug print out
    else
        sub_19A750("WARNING: A spawn could not be created due to lack of entity memory. Trigger "
                   "location(%6.2f,%6.2f,%6.2f)",
                   arg_0->unk_90, arg_0->unk_94, arg_0->unk_98);
#endif
    return var_10;
}

// match: ?sub_17CC40@type_17CC40@@QAEHPAVTrigger@@@Z @ 0x0017CC40
// sp-match: ?sub_17CC40@type_17CC40@@QAEHPAVTrigger@@@Z @ 0x00115E20
RwInt32 type_17CC40::sub_17CC40(Trigger *arg_0)
{
    unk_08 = arg_0;
    unk_14 = 0;
    unk_18 = 0;
    unk_04 = 0;
    unk_10 = 0;
    unk_0C = 0;
    sub_17D350(this);
    return 1;
}

// match: ?sub_17CCA0@type_17CC40@@QAEXXZ @ 0x0017CCA0
// sp-match: ?sub_17CCA0@type_17CC40@@QAEXXZ @ 0x00115E50
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
// Frees its shrimps (unless they are not to be touched).
void type_17CC40::sub_17CCA0()
{
    type_17CA70_node *var_8;
    type_17CA70_node *l4;

    if (dword_4E7240)
        return;
    l4 = unk_14;
    var_8 = 0;
    while (l4)
    {
        var_8 = l4->unk_0C;
        sub_17D1D0(l4);
        dword_4E7244.sub_16C710(l4);
        if (dword_4E723C)
            sub_8B840(dword_4E723C);
        l4 = var_8;
    }
}

// match: ?sub_17CD10@type_17CC40@@QAE_NXZ @ 0x0017CD10
// sp-match: ?sub_17CD10@type_17CC40@@QAE_NXZ @ 0x00115EA0
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
bool type_17CC40::sub_17CD10()
{
    bool var_5;
    type_3DF8D8 *fp_1C;
    type_3DFEEC *lcl_18;
    type_3DF8D8 *stk_14;
    type_3DF8D8 *local_10;
    RwReal fp_C;
    type_17CA70_node *l4;

    if (dword_4E7240)
        return false;
    fp_C = frand_range(0.0f, 100.0f);
    if (fp_C > ((ShrimpTrigger *)unk_08)->unk_DC)
        return false;
    l4 = (type_17CA70_node *)dword_4E7244.sub_16C5A0(0);
    var_5 = false;
    if (!unk_04)
    {
        local_10 = sub_198800(&((ShrimpTrigger *)unk_08)->unk_C0);
        if (!local_10 || local_10->vf_008() != 3)
            return false;
        stk_14 = local_10;
        unk_10 = Clump_FindFirstAtomic(((type_3DF9C4 *)(RpClump *)stk_14)->sub_190A10());
        unk_0C = 0;
        if (((ShrimpTrigger *)unk_08)->unk_C8.unk_00 || ((ShrimpTrigger *)unk_08)->unk_C8.unk_04)
        {
            fp_1C = sub_198800(&((ShrimpTrigger *)unk_08)->unk_C8);
            lcl_18 = (type_3DFEEC *)fp_1C;
            unk_0C = lcl_18->unk_24;
        }
        unk_04 = 1;
    }
    if (l4)
    {
        memset(l4, 0, 0x10);
        l4->unk_04 = ((ShrimpTrigger *)unk_08)->unk_D0_r;
        l4->unk_00 = 0;
        sub_17D180(l4);
        var_5 = true;
    }
    return var_5;
}

// match: ?sub_17CE90@type_17CC40@@QAEXM@Z @ 0x0017CE90
// sp-match: ?sub_17CE90@type_17CC40@@QAEXM@Z @ 0x00115FC0
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void type_17CC40::sub_17CE90(RwReal arg_0)
{
    RwReal var_C;
    type_17CA70_node *bp_8;
    type_17CA70_node *bp_4;

    if (dword_4E7240)
        return;
    bp_4 = unk_14;
    bp_8 = 0;
    if (!unk_0C)
        return;
#ifdef CODFH_SP // shape: SP 0x115FEA multiplies step by step (16.666, 0.001, 60, 0.35)
    var_C = deltaTime * flt_3DDE6C;
    var_C = (var_C = (var_C = var_C * 0.001f) * 60.0f) * 0.35f;
#else
    var_C = (var_C = (var_C = deltaTime * flt_3DDE6C / 1000.0f) * 60.0f) * 0.35f;
#endif
    while (bp_4)
    {
        bp_8 = bp_4->unk_0C;
        bp_4->unk_00 = var_C * bp_4->unk_04 + bp_4->unk_00;
        if (bp_4->unk_00 > 1.0f)
            bp_4->unk_00 = 1.0f;
        if (bp_4->unk_00 < 0.0f)
            bp_4->unk_00 = 0;
        if (bp_4->unk_00 >= 1.0f || bp_4->unk_00 <= 0.0f)
        {
            if (unk_0C->unk_1C_0 == 2)
            {
                bp_4->unk_04 = -bp_4->unk_04;
            }
            else if (unk_0C->unk_1C_0 == 1)
            {
                bp_4->unk_00 = 0;
            }
            else
            {
                sub_17D1D0(bp_4);
                dword_4E7244.sub_16C710(bp_4);
                if (dword_4E723C)
                    sub_8B840(dword_4E723C);
            }
        }
        bp_4 = bp_8;
    }
}

// match: ?sub_17CFF0@type_17CC40@@QAEXPAURwCamera@@@Z @ 0x0017CFF0
// sp-match: ?sub_17CFF0@type_17CC40@@QAEXPAURwCamera@@@Z @ 0x00115980
void type_17CC40::sub_17CFF0(RwCamera *arg_0)
{
    type_17CA70_node *var_8;
    RwRGBAReal var_18;
    bool var_19;
    RwReal var_20;
    RwV3d var_2C;
    RwV3d var_38;
    RwMatrix var_80;

    if (dword_4E7240)
        return;
    var_8 = unk_14;
    if (!unk_0C)
        return;
    var_18.alpha = 1.0f;
    var_18.blue = var_18.green = var_18.red = 0;
    sub_123AF0(unk_10, 1, 0, 0, &var_18, (RwV3d *)&stru_3DDE60);
    while (var_8)
    {
        var_19 = false;
        var_20 = var_8->unk_00 + var_8->unk_04;
        if (var_20 > 1.0f || var_20 < 0.0f)
        {
            var_20 = var_8->unk_00 - var_8->unk_04;
            var_19 = true;
        }
        unk_0C->sub_BA990(var_8->unk_00, &var_2C, 0);
        unk_0C->sub_BA990(var_20, &var_38, 0);
        RwV3dSubMacro(&var_38, &var_38, &var_2C);
        if (var_19)
            RwV3dScaleMacro(&var_38, &var_38, -1.0f);
        sub_140CE0(&var_80, &var_2C, &var_38);
        sub_123FE0((type_1243F0 *)&var_80, 1, 0);
        var_8 = var_8->unk_0C;
    }
    sub_124D70();
}

// match: ?sub_17D180@type_17CC40@@QAEXPAUtype_17CA70_node@@@Z @ 0x0017D180
// sp-match: ?sub_17D180@type_17CC40@@QAEXPAUtype_17CA70_node@@@Z @ 0x00115AE0
void type_17CC40::sub_17D180(type_17CA70_node *arg_0)
{
    arg_0->unk_0C = unk_14;
    arg_0->unk_08 = 0;
    if (unk_14)
        unk_14->unk_08 = arg_0;
    unk_14 = arg_0;
}

// match: ?sub_17D1D0@type_17CC40@@QAEXPAUtype_17CA70_node@@@Z @ 0x0017D1D0
// sp-match: ?sub_17D1D0@type_17CC40@@QAEXPAUtype_17CA70_node@@@Z @ 0x00115B10
void type_17CC40::sub_17D1D0(type_17CA70_node *arg_0)
{
    type_17CA70_node *var_4;

    var_4 = arg_0->unk_08;
    if (var_4)
        var_4->unk_0C = arg_0->unk_0C;
    var_4 = arg_0->unk_0C;
    if (var_4)
        var_4->unk_08 = arg_0->unk_08;
    if (arg_0 == unk_14)
        unk_14 = arg_0->unk_0C;
    arg_0->unk_0C = 0;
    arg_0->unk_08 = 0;
}

// match: ?sub_17D240@@YAHXZ @ 0x0017D240
// sp-match: ?sub_17D240@@YAHXZ @ 0x00115B50
// Sets the shrimps up (500 in the pool).
RwInt32 sub_17D240()
{
    dword_4E7244.sub_16C2C0(500, 0x10, "Shrimps", 4, 0);
    dword_4E7238 = 0;
    dword_4E723C = 0;
    return 1;
}

// match: ?sub_17D280@@YAXXZ @ 0x0017D280
// sp-match: ?sub_17D280@@YAXXZ @ 0x00115B90
// Ends the spawn.
void sub_17D280()
{
    if (dword_4E723C)
        sub_D5A60(dword_4E723C, 0);
    dword_4E723C = 0;
}

// match: ?sub_17D2B0@@YAXXZ @ 0x0017D2B0
// sp-match: ?sub_17D2B0@@YAXXZ @ 0x001160E0
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
// Shuts the shrimps down.
void sub_17D2B0()
{
    type_17CC40 *var_8;
    type_17CC40 *l4;

    l4 = dword_4E7238;
    var_8 = 0;
    while (l4)
    {
        var_8 = l4->unk_18;
        l4->sub_17CCA0();
        l4 = var_8;
    }
    dword_4E7244.sub_16C4D0(1);
    dword_4E7238 = 0;
    if (dword_4E723C)
        sub_D5A60(dword_4E723C, 0);
    dword_4E723C = 0;
}

// match: ?sub_17D330@@YAXPAVShrimpTrigger@@@Z @ 0x0017D330
// sp-match: ?sub_17D330@@YAXPAVShrimpTrigger@@@Z @ 0x00116140
void sub_17D330(ShrimpTrigger *arg_0)
{
    dword_4E723C = sub_17CB30(arg_0);
}

// match: ?sub_17D350@@YAXPAUtype_17CC40@@@Z @ 0x0017D350
// sp-match: ?sub_17D350@@YAXPAUtype_17CC40@@@Z @ 0x00115BB0
void sub_17D350(type_17CC40 *arg_0)
{
    arg_0->unk_18 = dword_4E7238;
    dword_4E7238 = arg_0;
}

// match: ?sub_17D370@@YAXM@Z @ 0x0017D370
// sp-match: ?sub_17D370@@YAXM@Z @ 0x00116160
// Moves every holder's shrimps.
void sub_17D370(RwReal arg_0)
{
    type_17CC40 *var_4;

    var_4 = dword_4E7238;
    while (var_4)
    {
        var_4->sub_17CE90(arg_0);
        var_4 = var_4->unk_18;
    }
}

// match: ?sub_17D3A0@@YAXPAURwCamera@@@Z @ 0x0017D3A0
// sp-match: ?sub_17D3A0@@YAXPAURwCamera@@@Z @ 0x00115BD0
// Draws every holder's shrimps into the camera arg_0 (in the default world,
// with its ambient and first directional lights), alpha-tested.
void sub_17D3A0(RwCamera *arg_0)
{
    type_17CC40 *var_4;

    var_4 = dword_4E7238;
    RpWorldAddCamera(dword_4E5C78, arg_0);
    if (clump)
        RpWorldAddLight(dword_4E5C78, clump);
    if (get_light(0))
        RpWorldAddLight(dword_4E5C78, get_light(0));
    if (RwCameraBeginUpdate(arg_0))
    {
        RwRenderStateSet(rwRENDERSTATEVERTEXALPHAENABLE, (void *)0);
        RwRenderStateSet(rwRENDERSTATEFOGENABLE, (void *)1);
        RwRenderStateSet(rwRENDERSTATESRCBLEND, (void *)rwBLENDSRCALPHA);
        RwRenderStateSet(rwRENDERSTATEDESTBLEND, (void *)rwBLENDINVSRCALPHA);
        RwRenderStateSet(rwRENDERSTATEZWRITEENABLE, (void *)1);
        RwRenderStateSet(rwRENDERSTATEZTESTENABLE, (void *)1);
        RwRenderStateSet(rwRENDERSTATEALPHATESTFUNCTION, (void *)5);
        RwRenderStateSet(rwRENDERSTATEALPHATESTFUNCTIONREF, (void *)0);
        while (var_4)
        {
            var_4->sub_17CFF0(arg_0);
            var_4 = var_4->unk_18;
        }
        RwCameraEndUpdate(arg_0);
    }
    RpWorldRemoveCamera(dword_4E5C78, arg_0);
    if (clump)
        RpWorldRemoveLight(dword_4E5C78, clump);
    if (get_light(0))
        RpWorldRemoveLight(dword_4E5C78, get_light(0));
}

// Functions /OPT:ICF folded into another body (config/aliases.txt), defined here for the
// authentic link (PLAN M7) with that body; the placement link takes the folded one.

// ??2type_3DDE70@@SAPAXIPAX@Z (folded into 0x6CCF0)
void *type_3DDE70::operator new(RwUInt32 arg_0, void *arg_4)
{
    return arg_4;
}

// Functions /OPT:ICF folded into another body (config/aliases.txt), defined here for the
// authentic link (PLAN M7) with that body; the placement link takes the folded one.

// ??3type_3DDE70@@SAXPAX@Z (folded into 0x19A750)
#ifndef CODFH_SP // single player's deleting destructor calls it (SP 0x1161A0, sp_nullsub_1): not in this file there
void type_3DDE70::operator delete(void * arg_0)
{
}
#endif

// Functions /OPT:ICF folded into another body (config/aliases.txt), defined here for the
// authentic link (PLAN M7) with that body; the placement link takes the folded one.

// ??3type_3DDE70@@SAXPAX0@Z (folded into 0x19A750)
void type_3DDE70::operator delete(void * arg_0, void * arg_4)
{
}
