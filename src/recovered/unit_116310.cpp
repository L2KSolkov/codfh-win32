// The player's weapon copies (type_10F710_1A48 and its three derived kinds,
// types/type_10F710.h) and the weapon settings table they read
// (type_4C19C0, dword_4C19C0). The original file name is not in the image,
// so it is named for its start address.

#include <string.h>

#include "rw/ostypes.h"
#include "rw/baframe.h"
#include "rw/rpatomic.h"
#include "types/type_10F710.h"
#include "types/type_4C19C0.h"
#include "types/type_495F0.h"
#include "types/animobjpool.h"
#include "game/clumpdata.h"
#include "game/functions.h"
#include "game/vecutil.h"
#include "game/gameloop.h"
#include "game/data.h"
#include "types/type_3D3548.h"
#include "types/type_DC400.h"
#include "types/type_DA580.h"
#include "types/musicplayer.h"
#include "rw/rprandom.h"
#include "rw/bamatrix.h"
#include "types/type_F2FF0.h"
#include "types/type_F3130.h"
#include "types/type_D48D0.h"
#include "types/type_3DBC78.h"
#include "game/netmsg.h"
#include "rw/rphanim.h"
#include "rw/rtslerp.h"
#include "game/frand.h"
#include "types/type_4E5E50.h"
#include "types/type_8E670.h"
#include "types/animbank.h"
#include "types/vec4.h"
#include "types/projectile.h"
#include "types/type_3DD948.h"
#include "types/CGlobalSounds.h"
#ifdef CODFH_SP
#include "types/type_3DC048.h"
#include "types/type_72810.h"
#endif
#include "game/mathutil.h"
#include "rws/clumphelper.h"
#include "game/pooledconsts.h"
#include "rw/bavector.h"

// Its data definitions (PLAN M5), in the image's address order.
// 0x003DA4E8
extern const RwReal flt_3DA4E8 = 16.666666f;
// 0x003DA4EC
extern const RwReal flt_3DA4EC = 16.666666f;
// 0x003DA4F0
extern const RwV3d stru_3DA4F0 = { 1.0f, 0.0f, 0.0f };
// 0x003DA4FC
extern const RwV3d stru_3DA4FC = { 0.0f, 1.0f, 0.0f };
#ifndef CODFH_SP // single player has neither unreferenced 0.01f: the y axis ends the unit's constants (SP 0x2E63A8)
// 0x003DA508
extern const RwReal flt_3DA508 = 0.01f;
// 0x003DA50C
extern const RwReal flt_3DA50C = 0.01f;
#endif
// 0x00429B64
RwReal dword_429B64 = -35.0f;
// 0x00429B68
// Not referenced by name: one object (a lone zero global would be .bss).
RwUInt32 unk_429B68[5] = { 0x0, 0x41700000 /* 15.0f */, 0x43960000 /* 300.0f */, 0x1, 0x1 };
// 0x004C1970
RwInt32 dword_4C1970[4];
// 0x004C1980
RwInt32 dword_4C1980[10];
// 0x004C19A8
RwInt32 dword_4C19A8;
// 0x004C19AC
RwInt32 dword_4C19AC;
// End of its data definitions.


// Globals with constructors defined here (their initializers and exit
// functions at the end of .text).
type_4C19C0 dword_4C19C0[39];
// The out-of-line copy of type_4C19C0's inline constructor.
// Its data (PLAN M5): literals, constants and tables where the image has them.
// match: ?flt_3DA4E8@@3MB @ 0x003DA4E8
// match: ?flt_3DA4EC@@3MB @ 0x003DA4EC
// match: ?stru_3DA4F0@@3URwV3d@@B @ 0x003DA4F0
// match: ?stru_3DA4FC@@3URwV3d@@B @ 0x003DA4FC
// match: ?flt_3DA508@@3MB @ 0x003DA508
// match: ?flt_3DA50C@@3MB @ 0x003DA50C
// match: ??_7type_3DA510@@6B@ @ 0x003DA510
// match: ??_7type_3DA558@@6B@ @ 0x003DA558
// match: ??_7type_3DA5A0@@6B@ @ 0x003DA5A0
// match: ??_7type_10F710_1A48@@6B@ @ 0x003DA5E8
// match: ??_C@_0CB@GBMKHAB@WARNING?3?5Missing?5idle?5anim?50x?$CFx?4@ @ 0x003DA62C
// match: __ehhandler$?sub_116490@@YAPAUtype_10F710_1A48@@PAUtype_10F710@@PAURpClump@@HH@Z>1>8 @ 0x0041D310
// match: __ehhandler$?sub_116490@@YAPAUtype_10F710_1A48@@PAUtype_10F710@@PAURpClump@@HH@Z>1 @ 0x0041D330
// match: __ehhandler$??1type_10F710_1A48@@UAE@XZ>1>8 @ 0x0041D34C
// match: __ehhandler$??1type_10F710_1A48@@UAE@XZ>1 @ 0x0041D37C
// match: __ehhandler$?sub_119BA0@@YAHPAUtype_F2FF0@@@Z>1>8 @ 0x0041D398
// match: __ehhandler$?sub_119BA0@@YAHPAUtype_F2FF0@@@Z>1 @ 0x0041D3A0
// match: __ehhandler$?sub_119D50@@YAHPAUtype_F2FF0@@@Z>1>8 @ 0x0041D3BC
// match: __ehhandler$?sub_119D50@@YAHPAUtype_F2FF0@@@Z>1 @ 0x0041D3C4
// match: .CRT$XCU+0 @ 0x00427094
// match: ?dword_429B64@@3MA @ 0x00429B64
// match: ?unk_429B68@@3PAIA @ 0x00429B68

// match: ??0type_4C19C0@@QAE@XZ @ 0x0011DAB0
// match: _$E2 @ 0x0030B790
// match: ?sub_116310@@YAXXZ @ 0x00116310
// sp-match: ?sub_116310@@YAXXZ @ 0x000D0F80

// Clears the weapon settings (their keys, the fields 0x98 and 0xB0, no
// stream group) and the death animations' keys.
void sub_116310()
{
    RwInt32 var_4;

    for (var_4 = 0; var_4 < 39; var_4++)
    {
        dword_4C19C0[var_4].unk_00.unk_00 = 0;
        dword_4C19C0[var_4].unk_00.unk_04 = 0;
        dword_4C19C0[var_4].unk_0C.unk_00 = 0;
        dword_4C19C0[var_4].unk_0C.unk_04 = 0;
        dword_4C19C0[var_4].unk_14.unk_00 = 0;
        dword_4C19C0[var_4].unk_14.unk_04 = 0;
        dword_4C19C0[var_4].unk_B0 = 0;
        dword_4C19C0[var_4].unk_98 = 0;
        dword_4C19C0[var_4].unk_24 = -1;
    }
    dword_4C1970[0] = 0;
    dword_4C1970[1] = 0;
    dword_4C1970[2] = 0;
    dword_4C1970[3] = 0;
    dword_4C1980[0] = 0;
    dword_4C1980[1] = 0;
    dword_4C1980[2] = 0;
    dword_4C1980[3] = 0;
    dword_4C1980[4] = 0;
    dword_4C1980[5] = 0;
    dword_4C1980[6] = 0;
    dword_4C1980[7] = 0;
    dword_4C1980[8] = 0;
    dword_4C1980[9] = 0;
}

// match: ?sub_116470@type_10F710_1A48@@QAEXXZ @ 0x00116470
// sp-match: ?sub_116470@type_10F710_1A48@@QAEXXZ @ 0x000D3E80
void type_10F710_1A48::sub_116470()
{
    sub_117080();
}

// match: ?sub_116490@@YAPAUtype_10F710_1A48@@PAUtype_10F710@@PAURpClump@@HH@Z @ 0x00116490
// match: __ehhandler$?sub_116490@@YAPAUtype_10F710_1A48@@PAUtype_10F710@@PAURpClump@@HH@Z-0x3C @ 0x003013A0
// match: __ehhandler$?sub_116490@@YAPAUtype_10F710_1A48@@PAUtype_10F710@@PAURpClump@@HH@Z @ 0x003013DC
// sp-match: ?sub_116490@@YAPAUtype_10F710_1A48@@PAUtype_10F710@@PAURpClump@@HH@Z @ 0x000D5A10
// Builds the copy of weapon arg_8 for the player arg_0, of the kind the
// weapon needs, and sets it up.
type_10F710_1A48 *sub_116490(type_10F710 *arg_0, RpClump *arg_4, RwInt32 arg_8, RwInt32 arg_C)
{
    type_10F710_1A48 *var_10;

    switch (arg_8)
    {
    case 19:
    case 20:
    case 21:
    case 22:
    case 31:
    case 33:
    case 34:
    case 38:
        var_10 = new (4) type_3DA5A0;
        var_10->vf_004(arg_0, arg_4, arg_8, arg_C);
        break;
    case 29:
    case 35:
        var_10 = new (4) type_3DA558;
        var_10->vf_004(arg_0, arg_4, arg_8, arg_C);
        break;
    case 0:
    case 1:
    case 27:
    case 28:
        var_10 = new (4) type_3DA510;
        var_10->vf_004(arg_0, arg_4, arg_8, arg_C);
        break;
    default:
        var_10 = new (4) type_10F710_1A48;
        var_10->vf_004(arg_0, arg_4, arg_8, arg_C);
        break;
    }
    return var_10;
}

// match: ??_Gtype_3DA510@@UAEPAXI@Z @ 0x001166D0
// sp-match: ??_Gtype_3DA510@@UAEPAXI@Z @ 0x000D5B10
// (The derived kinds' scalar deleting destructor, compiler-written.)

// match: ??1type_10F710_1A48@@UAE@XZ @ 0x00116700
// match: __ehhandler$??1type_10F710_1A48@@UAE@XZ-0x42 @ 0x003013F0
// match: __ehhandler$??1type_10F710_1A48@@UAE@XZ @ 0x00301432
// sp-match: ??1type_10F710_1A48@@UAE@XZ @ 0x000D5940
// (In the class.)

// match: ??_Gtype_10F710_1A48@@UAEPAXI@Z @ 0x00116820
// sp-match: ??_Gtype_10F710_1A48@@UAEPAXI@Z @ 0x000D59E0
// (Its scalar deleting destructor, compiler-written.)

// match: ??1type_3DA510@@UAE@XZ @ 0x00116850
// sp-match: ??1type_3DA510@@UAE@XZ @ 0x000D5B30
// (The derived kinds' destructor, compiler-written; type_3DA558's and
// type_3DA5A0's, identical, fold into this one.)

// match: ??0type_10F710_1A48@@QAE@XZ @ 0x00116870
// sp-match: ??0type_10F710_1A48@@QAE@XZ @ 0x000D3E90
type_10F710_1A48::type_10F710_1A48()
{
    unk_41C = 0;
    unk_42C = 0;
    unk_41D = 0;
    unk_464 = 0;
}

// match: ?sub_1169B0@@YAPAURpAtomic@@PAU1@PAX@Z @ 0x001169B0
// sp-match: ?sub_1169B0@@YAPAURpAtomic@@PAU1@PAX@Z @ 0x000D1020
// RpClumpForAllAtomics callback: stops the atomic arg_0 rendering.
RpAtomic *sub_1169B0(RpAtomic *arg_0, void *arg_4)
{
    RwInt8 var_1;

    var_1 = ((RwObject *)arg_0)->flags;
    var_1 &= ~rpATOMICRENDER;
    RpAtomicSetFlags(arg_0, var_1);
    return arg_0;
}

// match: ?vf_00C@type_10F710_1A48@@UAE_NXZ @ 0x001169E0
// sp-match: ?vf_00C@type_10F710_1A48@@UAE_NXZ @ 0x000D1030
bool type_10F710_1A48::vf_00C()
{
    if (unk_43C.get_unk_08())
    {
        unk_43C.sub_129940(0);
    }
    if (unk_420.get_unk_08())
    {
        unk_420.sub_129940(0);
    }
    unk_41E = 0;
    return 1;
}

// match: ?vf_008@type_10F710_1A48@@UAE_NPAUtype_10F710@@PAURpClump@@H@Z @ 0x00116A40
// sp-match: ?vf_008@type_10F710_1A48@@UAE_NPAUtype_10F710@@PAURpClump@@H@Z @ 0x000D1070
bool type_10F710_1A48::vf_008(type_10F710 *arg_0, RpClump *arg_4, RwInt32 arg_8)
{
    RwFrame *l4;
    RpHAnimHierarchy *var_8;
    type_495F0 *fp_C;
    RpClump *local_10;
    RwFrame *stk_14;
    RpClump *loc18;

    if (unk_41E)
    {
        return 1;
    }
    var_8 = 0;
    fp_C = (type_495F0 *)sub_198800(&unk_448->unk_00);
    if (!fp_C || fp_C->vf_008() != 5)
    {
        return 0;
    }
    unk_41E = 1;
    local_10 = (RpClump *)fp_C->sub_18F800(&fp_C->unk_20);
    if ((arg_8 != 30 || (arg_8 == 30 && local_10)) && (arg_8 != 36 || (arg_8 == 36 && local_10)))
    {
        loc18 = RpClumpClone(local_10);
        sub_16D9A0(loc18);
        l4 = RpClumpGetFrame(loc18);
        stk_14 = RpClumpGetFrame(unk_430.get_unk_08());
        RwFrameAddChild(stk_14, l4);
        unk_420.sub_129940(0);
        unk_420.sub_129620(loc18);
        unk_420.sub_129690(unk_42C);
        var_8 = sub_16D970(unk_430.get_unk_08());
        sub_79270(loc18, var_8);
        RpClumpForAllAtomics(loc18, sub_1169B0, 0);
        RWS::ClumpHelper::SetCanCollide(*loc18, 1);
        unk_43C.sub_129620(0);
    }
    return 1;
}

// match: ?vf_004@type_10F710_1A48@@UAE_NPAUtype_10F710@@PAURpClump@@HH@Z @ 0x00116BD0
// sp-match: ?vf_004@type_10F710_1A48@@UAE_NPAUtype_10F710@@PAURpClump@@HH@Z @ 0x000D1170
bool type_10F710_1A48::vf_004(type_10F710 *arg_0, RpClump *arg_4, RwInt32 arg_8, RwInt32 arg_C)
{
    RwInt32 var_4;

    unk_41C = 0;
    unk_42C = arg_0;
    unk_448 = &dword_4C19C0[arg_8];
    unk_458 = arg_8;
    unk_45C = 1;
    unk_41E = 0;
    unk_224 = 0;
    unk_430.sub_129620(arg_4);
    unk_420.sub_129620(0);
    unk_43C.sub_129620(0);
    if (arg_C)
    {
        vf_00C();
        vf_008(arg_0, arg_4, arg_8);
    }
    unk_414 = unk_448->unk_C8;
    unk_418 = 0;
    unk_44C = 0;
    unk_220 = 10000.0f;
    unk_21C = 0;
    unk_460 = 0;
    unk_41D = 1;
    unk_14 = 0;
    unk_12 = 0;
    unk_13 = 1;
    unk_234 = 0;
    unk_18 = unk_1C = unk_20 = 0.0f;
    unk_40 = 0;
    unk_3C = 0;
    unk_30 = 0;
    unk_30 = 0;
    unk_28 = 0;
    unk_24 = 0;
    unk_44 = 0;
    unk_45 = 0;
    unk_46 = 0;
    unk_11 = 0;
    unk_228 = 0;
    unk_230 = 0;
    unk_22C = 0;
    unk_4C = 0;
    unk_450 = 1.0f;
    unk_454 = 1.0f;
    unk_60 = 0;
    for (var_4 = 0; var_4 < 3; var_4++)
    {
        unk_238_a[var_4] = unk_448->unk_1C0_a[var_4];
        unk_25C_a[var_4] = unk_448->unk_3EC_a[var_4];
    }
    zero_v3d(&unk_280);
    zero_v3d(&unk_28C);
    unk_298 = 0.0f;
    unk_42C->unk_1B04 = 0;
    unk_50 = 0.0f;
    for (var_4 = 0; var_4 < 3; var_4++)
    {
        unk_170[var_4].imag.x = unk_170[var_4].imag.y = unk_170[var_4].imag.z = 0.0f;
        unk_170[var_4].real = 1.0f;
        unk_1A0[var_4].imag.x = unk_1A0[var_4].imag.y = unk_1A0[var_4].imag.z = 0.0f;
        unk_1A0[var_4].real = 1.0f;
        unk_1D0[var_4].x = unk_1D0[var_4].y = unk_1D0[var_4].z = 0.0f;
        unk_1F4[var_4].x = unk_1F4[var_4].y = unk_1F4[var_4].z = 0.0f;
    }
    unk_218 = 0;
    unk_48 = unk_448->unk_D4;
    return 1;
}

// match: ?sub_117050@type_10F710_1A48@@QAEXXZ @ 0x00117050
// sp-match: ?sub_117050@type_10F710_1A48@@QAEXXZ @ 0x000D1400
void type_10F710_1A48::sub_117050()
{
    sub_16E040(unk_420.get_unk_08());
}

// match: ?sub_117080@type_10F710_1A48@@QAE_NXZ @ 0x00117080
// sp-match: ?sub_117080@type_10F710_1A48@@QAE_NXZ @ 0x000D1410
// Drops its model and marks it not set up.
bool type_10F710_1A48::sub_117080()
{
    vf_00C();
    unk_41D = 0;
    return 1;
}

// match: ?sub_1170B0@type_10F710_1A48@@QAE_NHH@Z @ 0x001170B0
// sp-match: ?sub_1170B0@type_10F710_1A48@@QAE_NHH@Z @ 0x000D1430
// Readies it: drawn (with its partner), the rumble for its kind, its idle
// animation on the player (arg_4), its sway cleared, its rounds shown
// (arg_0, unless its kind needs no animation), the HUD's weapon, and for
// weapon 4 its bones.
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
bool type_10F710_1A48::sub_1170B0(RwInt32 arg_0, RwInt32 arg_4)
{
    RwInt32 var_4;
    RwInt32 v8;
    RpHAnimHierarchy *varC;

    unk_41C = 1;
    if (unk_460)
    {
        unk_460->unk_41C = 1;
    }
    sub_173180(unk_420.get_unk_08());
    switch (unk_48)
    {
    case 1:
    case 2:
        unk_4B9308.sub_EECD0(3, 0);
        break;
    default:
        unk_4B9308.sub_EECD0(3, 1);
        break;
    }
    if (arg_4)
    {
        if (sub_77B70(unk_448->unk_28, (void **)(&v8), (void **)(&var_4)))
        {
            unk_42C->unk_284->sub_794C0(0.0f);
            unk_42C->unk_284->sub_796A0((RtAnimAnimation *)v8, unk_448->unk_28, 0, (type_783F0 *)var_4, 0.0f,
                                        1.0f, 1.0f);
        }
        else if (unk_448->unk_28)
        {
            sub_16C220("WARNING: Missing idle anim 0x%x.", unk_448->unk_28);
        }
    }
    if (unk_448->unk_20)
    {
        vf_034();
    }
    unk_298 = 0.0f;
    unk_42C->unk_1B04 = 0;
    unk_28C.x = 0.0f;
    unk_28C.y = 0.0f;
    unk_28C.z = 0.0f;
    unk_13 = 1;
    if (arg_0 && get_unk_45C() != 2)
    {
        sub_115390(unk_414, unk_418);
    }
    if (dword_4B9190)
    {
        dword_4B9190->sub_E0800(unk_458);
        dword_4B9190->sub_E07A0(unk_414, unk_448->unk_C8);
        if (unk_458 == 32)
        {
            dword_4B9190->sub_DEB80(3);
            vf_01C();
        }
        else
        {
            dword_4B9190->sub_DEB80(0);
        }
    }
    varC = unk_42C->unk_284->unk_18;
    if (unk_458 == 4 && varC)
    {
        unk_54 = 360.0f / unk_448->unk_C8;
        unk_58 = RpHAnimIDGetIndex(varC, 0x2D1F);
        unk_5C = RpHAnimIDGetIndex(varC, 0x2D24);
    }
    return 1;
}

// match: ?sub_117370@type_10F710_1A48@@QAE_NXZ @ 0x00117370
// sp-match: ?sub_117370@type_10F710_1A48@@QAE_NXZ @ 0x000D1630
// Puts it away: not drawn (nor its partner), its model and (for weapons 29
// and 35) the player's clump set down, its sway and states cleared.
bool type_10F710_1A48::sub_117370()
{
    unk_41C = 0;
    if (unk_460)
    {
        unk_460->unk_41C = 0;
    }
    if (unk_420.get_unk_08())
    {
        sub_1735A0(unk_420.get_unk_08());
    }
    if (unk_458 == 29 || unk_458 == 35)
    {
        sub_173180(unk_430.get_unk_08());
    }
    unk_298 = 0.0f;
    unk_42C->unk_1B04 = 0;
    unk_42C->unk_1B14 = 0;
    unk_228 = 0;
    unk_230 = 0;
    unk_22C = 0;
    unk_13 = 1;
    return 1;
}

// match: ?sub_117460@type_10F710_1A48@@QAE_NXZ @ 0x00117460
// sp-match: ?sub_117460@type_10F710_1A48@@QAE_NXZ @ 0x000D16C0
bool type_10F710_1A48::sub_117460()
{
    // (A nested test: a plain one gives no setne.)
    if ((unk_224 != 0) != 0)
    {
        return 0;
    }
    if (!unk_228 && !unk_22C && !unk_11 && !unk_42C->unk_1B2C && !unk_45 && !unk_42C->unk_1B0C &&
        unk_42C->unk_19D0 != 12 && unk_42C->unk_19D0 != 13 && unk_13)
    {
        return 1;
    }
    return 0;
}

// match: ?sub_117510@type_10F710_1A48@@QAE_NXZ @ 0x00117510
// sp-match: ?sub_117510@type_10F710_1A48@@QAE_NXZ @ 0x000D1730
bool type_10F710_1A48::sub_117510()
{
    if (!unk_228 && !unk_22C && !unk_230 && !unk_11 && !unk_42C->unk_1B04 && !unk_42C->unk_1B2C &&
        unk_42C->unk_19D0 != 5 && unk_42C->unk_19D0 != 7 && unk_42C->unk_19D0 != 12 &&
        unk_42C->unk_19D0 != 13)
    {
        return 1;
    }
    return 0;
}

// match: ?sub_1175D0@type_10F710_1A48@@QAE_NXZ @ 0x001175D0
// sp-match: ?sub_1175D0@type_10F710_1A48@@QAE_NXZ @ 0x000D1790
bool type_10F710_1A48::sub_1175D0()
{
    if (!unk_230 && !unk_228 && unk_42C->unk_19D0 != 5 && unk_42C->unk_19D0 != 7 &&
        unk_42C->unk_19D0 != 12 && unk_42C->unk_19D0 != 13)
    {
        return 1;
    }
    return 0;
}

// match: ?vf_01C@type_10F710_1A48@@UAE_NXZ @ 0x00117650
// sp-match: ?vf_01C@type_10F710_1A48@@UAE_NXZ @ 0x000D17D0
bool type_10F710_1A48::vf_01C()
{
    RwInt32 var_4;
    RwInt32 local_8;

    if (sub_77B70(unk_448->unk_2C, (void **)(&local_8), (void **)(&var_4)) && unk_10)
    {
        unk_42C->unk_284->sub_794C0(0.06666667f);
        unk_42C->unk_284->sub_796A0((RtAnimAnimation *)local_8, unk_448->unk_2C, 0, (type_783F0 *)var_4, 0.0f,
                                    1.0f, 1.0f);
        unk_10 = 0;
        unk_45 = 1;
        return 1;
    }
    return 0;
}

#ifdef CODFH_SP
extern RwReal flt_4F286C[3];
// The difficulty's multiplier of flt_4F286C (1 outside 0 to 2), as
// difficulty_4F2890 is of its table: the shots read it (SP 0xD2535,
// 0xD25E9 and the others index 0x3EA794, flt_4F286C's twin).
inline RwReal difficulty_4F286C()
{
    return dword_42B714 > -1 && dword_42B714 < 3 ? flt_4F286C[dword_42B714] : 1.0f;
}
#endif

// Fires once its recoil time (unk_220) reaches the settings' rate (unk_BC);
// false before. Whether its particles follow it (unk_465): always within 5
// of the rate unless the settings say so (unk_28C), else by chance as
// shots run together. With nothing loaded when rounds count it only plays
// the empty sound. Otherwise: the rumble (sub_119050); weapons 30 and 36
// fire the vehicle's gun from a vehicle's seat 2, and aim from the hand's
// weapon; its sound starts; past the first shots (unk_2A8 by stance) the
// recoil line (unk_24) is kicked by a random spread (the aimed settings
// when the player is aiming, unk_1B04), swung back when it runs past its
// bound, and the kick stored into the stance's sway (unk_238 or unk_25C)
// with the recoil's size (unk_18) growing; the aim is the camera's matrix
// blended towards the muzzle by the distance to the nearest world hit,
// turned by the recoil and a random spread; the bullet flies along it
// (0x202 for a player of kind 2, else 0x201; from the vehicle while its
// pair's second, with its gun's settings from seat 2), with its fire
// animation, its spread (unk_450, unk_454), the pair's muzzle particles, the
// weapon 4 twist, and the rounds display.
// match: ?vf_018@type_10F710_1A48@@UAE_NXZ @ 0x001176F0
// sp-match: ?vf_018@type_10F710_1A48@@UAE_NXZ @ 0x000D3FB0
bool type_10F710_1A48::vf_018()
{
    if (unk_220 < unk_448->unk_BC)
        return false;
    if (unk_220 <= unk_448->unk_BC + 5.0f)
    {
        if (unk_448->unk_28C)
            unk_465 = 1;
        else
        {
            unk_468++;
            unk_465 = (rand() & unk_468) != 0;
        }
    }
    else
    {
        unk_465 = 1;
        unk_468 = 0;
    }
    memset(&unk_29C, 0, sizeof(type_10F710_1A48_29C));
    unk_44 = 1;
    unk_220 = 0.0f;
    if (unk_414 || !unk_448->unk_CC || dword_4C19AC)
    {
        RpHAnimHierarchy *v_8;
        type_3DBC78 *v_C;
        RwInt32 v_10;
        RwMatrix v_60;
        RwLine v_7C;
        RwReal v_98;
        RwReal v_B0;
        RwReal v_110;
        RwReal v_114;
        RwMatrix *v_118;
        RwReal v_11C;
        RwLine v_134;
        RwInt32 v_138;
        RwReal v_184;
        RwMatrix v_1D0;
        RwMatrix v_210;
        RtSlerp *v_214;
        RwMatrix v_260;
        RwReal v_278;
        RwReal v_290;
        RwV3d v_2C8;
        RwV3d v_2D4;
        RwInt32 v_2D8;
        RwInt32 v_2F4;
        RwInt32 v_2F8;
        RwInt32 v_2FC;
        RwInt32 v_300;

        sub_119050();
        unk_48 = unk_448->unk_D4;
        v_8 = unk_42C->unk_284->unk_18;
        if (unk_458 == 30 || unk_458 == 36)
        {
            if (unk_42C->unk_4D0 == 2)
            {
                v_C = (type_3DBC78 *)unk_42C->vf_200();
                dword_4C19A8 = 1;
                v_10 = v_C->vf_2A8(1, 0, 1);
                dword_4C19A8 = 0;
                return v_10;
            }
            sub_EC310(unk_42C->unk_1A48[unk_42C->unk_1AE4]->unk_420.get_unk_08(), v_8, &v_60, 0x46495245, 0,
                      1); // not an address: 'FIRE'
        }
        else
        {
            sub_EC310(unk_420.get_unk_08(), v_8, &v_60, 0x46495245, 0, 1); // not an address: 'FIRE'
        }
        if (!unk_46 && unk_448->unk_1C && !unk_464)
        {
            unk_21C = unk_42C->unk_1C0.sub_8A980(&unk_448->unk_0C, unk_42C, 1, unk_42C->sub_CD550(), 0, 0);
            unk_46 = 1;
        }
        if ((RwUInt32)unk_40 >= unk_448->unk_2A8_u[unk_42C->unk_1A04])
        {
            v_7C.start.z = 0.0f;
            v_7C.end.z = 0.0f;
            if (unk_3C)
            {
                unk_24_l.end.x = unk_1C;
                unk_24_l.end.y = unk_20;
                v_7C.start.x = unk_24_l.end.x;
                v_7C.start.y = unk_24_l.end.y;
                RwV3dSubMacro(&v_7C.end, &unk_24_l.end, &unk_24_l.start);
                RwV3dAddMacro(&v_7C.end, &unk_24_l.end, &v_7C.end);
            }
            else
            {
                v_7C.start.x = unk_1C;
                v_7C.start.y = unk_20;
                v_7C.end.x = v_7C.start.x;
                v_7C.end.y = v_7C.start.y + 2.0f;
                unk_3C = 1;
            }
            if (unk_42C->unk_1B04)
            {
                v_98 = frand_range(-unk_448->unk_370_r[unk_42C->unk_1A04], unk_448->unk_370_r[unk_42C->unk_1A04]);
                v_B0 = frand_range(0.0f, unk_448->unk_364_r[unk_42C->unk_1A04]);
            }
            else
            {
                v_98 = frand_range(-unk_448->unk_2D8_r[unk_42C->unk_1A04], unk_448->unk_2D8_r[unk_42C->unk_1A04]);
                v_B0 = frand_range(0.0f, unk_448->unk_2CC_r[unk_42C->unk_1A04]);
            }
            unk_64 = v_98;
            sub_1403D0(&v_7C, v_B0);
            sub_1402B0(&v_7C, v_98);
            if (unk_42C->unk_1B04)
            {
                if (fabs_ref(v_7C.end.x) > unk_448->unk_34C_r[unk_42C->unk_1A04]
                    || fabs_ref(v_7C.end.y) > unk_448->unk_34C_r[unk_42C->unk_1A04])
                {
                    RwV3d v_F0;

                    v_F0 = v_7C.end;
                    v_7C.end = v_7C.start;
                    v_7C.start = v_F0;
                }
            }
            else
            {
                if (fabs_ref(v_7C.end.x) > unk_448->unk_2B4_r[unk_42C->unk_1A04]
                    || fabs_ref(v_7C.end.y) > unk_448->unk_2B4_r[unk_42C->unk_1A04])
                {
                    RwV3d v_10C;

                    v_10C = v_7C.end;
                    v_7C.end = v_7C.start;
                    v_7C.start = v_10C;
                }
            }
            v_110 = v_7C.end.x;
            v_114 = v_7C.end.y;
            unk_24_l = v_7C;
            if (unk_42C->unk_1B04)
            {
                unk_25C_a[unk_42C->unk_1A04].x -= v_114 - unk_20;
                unk_25C_a[unk_42C->unk_1A04].y += v_110 - unk_1C;
            }
            else
            {
                unk_238_a[unk_42C->unk_1A04].x -= v_114 - unk_20;
                unk_238_a[unk_42C->unk_1A04].y += v_110 - unk_1C;
            }
            unk_1C = v_110;
            unk_20 = v_114;
            sub_170ED0(unk_1C);
            sub_170ED0(unk_20);
            if (unk_42C->unk_1B04)
            {
                if (unk_18 < unk_448->unk_34C_r[unk_42C->unk_1A04])
                {
                    if (unk_18 != 0.0f)
                        unk_18 = unk_448->unk_358_r[unk_42C->unk_1A04]
                            * (unk_18 / unk_448->unk_34C_r[unk_42C->unk_1A04]) + unk_18;
                    else
                        unk_18 = 1.0f;
                }
            }
            else
            {
                if (unk_18 < unk_448->unk_2B4_r[unk_42C->unk_1A04])
                {
                    if (unk_18 != 0.0f && unk_448->unk_2B4_r[unk_42C->unk_1A04] != 0.0f)
                        unk_18 = unk_448->unk_2C0_r[unk_42C->unk_1A04]
                            * (unk_18 / unk_448->unk_2B4_r[unk_42C->unk_1A04]) + unk_18;
                    else
                        unk_18 = 1.0f;
                }
            }
            unk_40++;
        }
        else
            unk_40++;
        v_118 = RwFrameGetMatrix(RwCameraGetFrame((RwCamera *)dword_4E5C74));
#ifdef CODFH_SP
        // shape: the reach scaled by a literal 3, last (SP 0xD458C: fld [+0x488]; fmul 3.0)
        v_11C = unk_448->unk_488_f * 3.0f + flt_3CD8E0;
        v_134.start = v_118->pos;
        v_134.end.x = v_118->at.x * unk_448->unk_488_f * 3.0f + v_134.start.x;
        v_134.end.y = v_118->at.y * unk_448->unk_488_f * 3.0f + v_134.start.y;
        v_134.end.z = v_118->at.z * unk_448->unk_488_f * 3.0f + v_134.start.z;
#else
        v_11C = (RwDouble)unk_448->unk_488_f * flt_3D7118 + flt_3CD8E0;
        v_134.start = v_118->pos;
        v_134.end.x = v_118->at.x * unk_448->unk_488_f * flt_3D7118 + v_134.start.x;
        v_134.end.y = v_118->at.y * unk_448->unk_488_f * flt_3D7118 + v_134.start.y;
        v_134.end.z = v_118->at.z * unk_448->unk_488_f * flt_3D7118 + v_134.start.z;
#endif
        for (v_138 = 0; v_138 < 4; v_138++)
        {
            type_4E5D30 *v_13C;
            type_91F40 v_174;
            RwV3d v_180;

            v_13C = &dword_4E5D30[v_138];
            if (v_13C->get_unk_00() && v_13C->get_unk_28()
                && sub_91F40(v_13C->get_unk_28(), &v_134, &v_174, 1, 0x590000, 1)) // not an address: line-test flags
            {
                RwV3dSubMacro(&v_180, &v_174.unk_08, &v_118->pos);
                if (RwV3dLength((RwV3d *)&v_180) < v_11C)
                    v_11C = RwV3dLength((RwV3d *)&v_180);
            }
        }
        v_184 = 1.0f;
        if (v_11C >= unk_448->unk_48C_f && v_11C <= unk_448->unk_488_f)
        {
            v_1D0 = *v_118;
            v_210 = v_60;
            v_214 = RtSlerpCreate(0);
            RtSlerpInitialize(v_214, &v_1D0, &v_210);
            v_184 = 1.0f - (v_11C - unk_448->unk_48C_f) / (unk_448->unk_488_f - unk_448->unk_48C_f);
            RtSlerpGetMatrix(v_214, &v_260, v_184);
            RtSlerpDestroy(v_214);
        }
        else
            v_260 = *v_118;
        RwMatrixRotate(&v_260, &stru_3DA4F0, v_184 * unk_20 * -1.0f, rwCOMBINEPRECONCAT);
        RwMatrixRotate(&v_260, &stru_3DA4FC, v_184 * unk_1C, rwCOMBINEPRECONCAT);
        if (unk_42C->unk_1B04)
        {
            v_278 = frand_range(-unk_448->unk_388_r[unk_42C->unk_1A04], unk_448->unk_388_r[unk_42C->unk_1A04]);
            v_290 = frand_range(-unk_448->unk_388_r[unk_42C->unk_1A04], unk_448->unk_388_r[unk_42C->unk_1A04]);
        }
        else
        {
            v_278 = frand_range(-unk_448->unk_2F0_r[unk_42C->unk_1A04], unk_448->unk_2F0_r[unk_42C->unk_1A04]);
            v_290 = frand_range(-unk_448->unk_2F0_r[unk_42C->unk_1A04], unk_448->unk_2F0_r[unk_42C->unk_1A04]);
        }
        RwMatrixRotate(&v_260, &stru_3DA4F0, v_278, rwCOMBINEPRECONCAT);
        RwMatrixRotate(&v_260, &stru_3DA4FC, v_290, rwCOMBINEPRECONCAT);
        v_2C8 = v_260.pos;
        RwV3dIncrementScaledMacro(&v_2C8, &v_260.at, 2000.0f);
        RwV3dSubMacro(&v_2D4, &v_2C8, &v_260.pos);
        RwV3dNormalize(&v_2D4, &v_2D4);
        RwV3dScaleMacro(&v_2D4, &v_2D4, unk_448->unk_B8_f);
        if (unk_448->unk_CC && !unk_464 && !dword_4C19AC)
            unk_414--;
        if ((unk_42C->unk_2C & 7) == 2)
            v_2D8 = 0x202;
        else
            v_2D8 = 0x201;
#ifdef CODFH_SP // MP 0x1176F0; single player (SP 0xD3FB0) has no unk_217C: the block always runs
        if (1)
#else
        if (!unk_42C->unk_217C)
#endif
        {
            if (!unk_464)
            {
                unk_29C.unk_00 = 1;
#ifdef CODFH_SP // single player scales the damage by the difficulty (SP 0xD4A55)
                unk_29C.unk_04_r = (RwUInt32)unk_448->unk_C4 * difficulty_4F286C();
#else
                unk_29C.unk_04_r = (RwUInt32)unk_448->unk_C4 * 1.0f;
#endif
                sub_15F2C0(v_2D8, (RwInt32)unk_42C, &v_260, &v_2D4, unk_42C->vf_138(), (type_439A48 *)&unk_29C, 0);
            }
            else
            {
                void *v_2E4;

                v_2E4 = 0;
                switch (unk_42C->unk_4D0)
                {
                case 0:
                    v_2E4 = 0;
                    break;
                case 2:
                    v_2E4 = &unk_448->unk_4FC;
                    break;
                default:
                    v_2E4 = 0;
                }
                unk_29C.unk_00 = 0;
#ifdef CODFH_SP // likewise (SP 0xD4AEB)
                unk_29C.unk_04_r = (RwUInt32)unk_448->unk_C4 * difficulty_4F286C();
#else
                unk_29C.unk_04_r = (RwUInt32)unk_448->unk_C4 * 1.0f;
#endif
                sub_15F2C0(v_2D8, (RwInt32)unk_42C->vf_200(), &v_260, &v_2D4, unk_42C->vf_138(),
                           (type_439A48 *)&unk_29C, (RwInt32)v_2E4);
                unk_42C->unk_1C0.sub_8A980(&dword_4AEFEC, unk_42C, 1, unk_42C->sub_CD550(), 0, 0);
            }
        }
        v_2F4 = 0;
        v_2F8 = 0;
        v_2FC = 0;
        v_300 = unk_42C->unk_1A48[unk_42C->unk_1AE4]->get_unk_458();
        if (!(v_300 == 17 || v_300 == 13 || v_300 == 18 || v_300 == 0 ? 1 : 0) || unk_448->unk_90 || !unk_42C->unk_1B04 || unk_42C->unk_1B0C)
        {
            v_2FC = unk_448->unk_2C;
            if (unk_230)
                v_2FC = unk_448->unk_74;
            if (unk_42C->unk_1B04 && unk_448->unk_90)
                v_2FC = unk_448->unk_94;
            if (!unk_464 && sub_77B70(v_2FC, (void **)(&v_2F4), (void **)(&v_2F8)))
            {
                unk_42C->unk_284->sub_794C0(0.06666667f);
                unk_42C->unk_284->sub_796A0((RtAnimAnimation *)v_2F4, v_2FC, 0, (struct type_783F0 *)v_2F8, 0.0f,
                                            1.0f, 1.0f);
                unk_10 = 0;
                unk_45 = 1;
            }
        }
        unk_450 = crand() * 2 * unk_448->unk_18C_f - unk_448->unk_18C_f;
        unk_454 = crand() * 2 * unk_448->unk_190_f + 1.0f - unk_448->unk_190_f;
        if (unk_464)
        {
            RwMatrix v_360;
            type_F2FF0 *v_364;
            type_F2FF0 *v_368;

            v_360 = v_260;
            dword_4C19A8 = 1;
            v_364 = (type_F2FF0 *)sub_F2FF0(unk_448->unk_548, &v_360, 0, 0, false, false);
            v_368 = (type_F2FF0 *)sub_F2FF0(unk_448->unk_54C, &v_360, 0, 0, false, false);
            dword_4C19A8 = 0;
            if (!unk_42C->unk_4D0)
            {
                if (v_364)
                {
                    v_364->unk_150_h = unk_42C->get_unk_384_h();
                    v_364->unk_158 = unk_458;
                    v_364->unk_154 = sub_119D50;
                    v_364->unk_40 |= 0x40;
                }
                if (v_368)
                {
                    v_368->unk_150_h = unk_42C->get_unk_384_h();
                    v_368->unk_158 = unk_458;
                    v_368->unk_154 = sub_119D50;
                    v_368->unk_40 |= 0x40;
                }
            }
        }
        unk_50 = unk_50 + unk_54;
        if (unk_50 > 360.0f)
            unk_50 -= 360.0f;
        sub_115390(unk_414, unk_418);
        if (dword_4B9190)
            dword_4B9190->sub_E07A0(unk_414, unk_448->unk_C8);
        return true;
    }
    unk_48 = 1;
    unk_42C->unk_1C0.sub_8A980(&dword_4B1F4C, unk_42C, 0, (RwV3d *)unk_42C->vf_0C4(), 1, 0);
    return false;
}

// match: ?sub_119050@type_10F710_1A48@@QAEXXZ @ 0x00119050
// sp-match: ?sub_119050@type_10F710_1A48@@QAEXXZ @ 0x000D1860
void type_10F710_1A48::sub_119050()
{
    switch (unk_458)
    {
    case 8:
        unk_4E5E50.sub_176180(2, 0, 1.0f, 0);
        break;
    case 4:
        unk_4E5E50.sub_176180(3, 0, 1.0f, 0);
        break;
    }
}

// match: ?sub_1190B0@type_10F710_1A48@@QAEXXZ @ 0x001190B0
// sp-match: ?sub_1190B0@type_10F710_1A48@@QAEXXZ @ 0x000D18A0
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void type_10F710_1A48::sub_1190B0()
{
    RwInt32 var_4;
    RwInt32 local_8;

    if (sub_77B70(unk_448->unk_5C, (void **)(&local_8), (void **)(&var_4)))
    {
        unk_42C->unk_284->sub_794C0(0.06666667f);
        unk_42C->unk_284->sub_796A0((RtAnimAnimation *)local_8, unk_448->unk_5C, 0, (type_783F0 *)var_4, 0.0f,
                                    1.0f, 1.0f);
        unk_10 = 0;
        unk_11 = 1;
        unk_13 = 1;
        if (unk_12)
        {
            unk_4C = 1;
            if (unk_60 > 0)
            {
                unk_60 = 0;
            }
        }
        unk_12 = 0;
        unk_13 = 1;
    }
}

// match: ?vf_020@type_10F710_1A48@@UAE_NXZ @ 0x00119180
// sp-match: ?vf_020@type_10F710_1A48@@UAE_NXZ @ 0x000D1950
bool type_10F710_1A48::vf_020()
{
    RwInt32 var_4;
    RwInt32 v8;
    RwInt32 varC;

    var_4 = unk_448->unk_30;
    if (unk_46)
    {
        unk_42C->unk_1C0.sub_8A910(unk_21C);
        unk_21C = 0;
        unk_42C->unk_1C0.sub_8A980(&unk_448->unk_14, unk_42C, 1, unk_42C->sub_CD550(), 0, 0);
        unk_46 = 0;
    }
    if (unk_42C->unk_1B04 && !unk_230)
    {
        unk_42C->unk_1B10 = 1;
    }
    if (unk_230)
    {
        var_4 = unk_448->unk_78;
    }
    if (unk_418)
    {
        unk_48 = unk_448->unk_D4;
        if (unk_448->unk_80)
        {
            if (sub_77B70(unk_448->unk_84, (void **)(&varC), (void **)(&v8)))
            {
                unk_42C->unk_284->sub_794C0(0.06666667f);
                unk_42C->unk_284->sub_796A0((RtAnimAnimation *)varC, unk_448->unk_84, 0, (type_783F0 *)v8,
                                            0.0f, 1.0f, 1.0f);
                unk_60 = 1;
            }
        }
        else if (sub_77B70(var_4, (void **)(&varC), (void **)(&v8)))
        {
            unk_42C->unk_284->sub_794C0(0.06666667f);
            unk_42C->unk_284->sub_796A0((RtAnimAnimation *)varC, var_4, 0, (type_783F0 *)v8, 0.0f, 1.0f,
                                        1.0f);
        }
        unk_10 = 0;
        unk_12 = 1;
        unk_13 = 0;
        unk_11 = 0;
        return 1;
    }
    return 0;
}

// match: ?vf_010@type_10F710_1A48@@UAE_NXZ @ 0x001193B0
// sp-match: ?vf_010@type_10F710_1A48@@UAE_NXZ @ 0x000D1B10
bool type_10F710_1A48::vf_010()
{
    RwInt32 var_4;
    RwInt32 local_8;

    var_4 = unk_414;
    local_8 = unk_418;
    if (var_4 <= 0 && local_8 > 0 && !unk_12 && unk_13)
    {
        return 1;
    }
    return 0;
}

// match: ?vf_014@type_10F710_1A48@@UAE_NXZ @ 0x00119400
// sp-match: ?vf_014@type_10F710_1A48@@UAE_NXZ @ 0x000D1B40
bool type_10F710_1A48::vf_014()
{
    if ((RwUInt32)unk_414 < unk_448->unk_C8 && (RwUInt32)unk_418 > 0 && !unk_12 && !unk_11 && unk_13)
    {
        if (unk_458 == 15 && (RwUInt32)unk_414 > 0)
        {
            return 0;
        }
        return 1;
    }
    return 0;
}

// dword_4F83D8, through a result local: an inline with no address and so no
// database name, named for the word. Evidence: sub_119480 tests it through a
// slot of its own.
inline RwInt32 get_4F83D8()
{
    RwInt32 r = dword_4F83D8;
    return r;
}

// A constant false test: an inline with no address and so no database
// name, named for what it gives. Evidence: sub_119480 materialises a zero
// (xor; je) before its second test, which a literal 0 would have removed.
inline bool always_0()
{
    return 0;
}

// match: ?sub_119480@@YAXXZ @ 0x00119480
// sp-match: ?sub_119480@@YAXXZ @ 0x000D1B90
void sub_119480()
{
#ifdef CODFH_SP // single player's fade callback only ends the mission: SP 0xD1D6C hands sub_1252E0 0xD1B90, `or dword_4B86F8 (SP 0x3B4590), 8` (folded with sub_150B00)
    dword_4B86F8 |= 8;
#else
    type_4F805C *var_4;

    var_4 = dword_4F805C;
    if (var_4 && var_4->unk_217C)
    {
        unk_4F7EB8.sub_1AB2C0();
    }
    else
    {
        dword_44E8A0 = 0;
        if (always_0() && !get_4F83D8())
        {
            unk_4F7EB8.sub_1AB400(4);
            unk_4F7EB8.sub_1AB420(1);
        }
        else
        {
            unk_4F7EB8.sub_1AB400(1);
        }
    }
#endif
}

// match: ?vf_028@type_10F710_1A48@@UAE_NXZ @ 0x00119500
// sp-match: ?vf_028@type_10F710_1A48@@UAE_NXZ @ 0x000D1BA0
bool type_10F710_1A48::vf_028()
{
    RwInt32 var_4;
    RwInt32 v8;
    RwInt32 stk_C;
    RwInt32 var_10;
    RwInt32 lv_14;

    if (unk_14 <= 0 && !((dword_4B86F8 >> 6) & 1))
    {
        var_4 = unk_448->unk_7C;
        if (!var_4)
        {
            var_4 = dword_4C1970[0];
        }
        if (sub_77B70(var_4, (void **)(&stk_C), (void **)(&v8)))
        {
            unk_42C->unk_284->sub_794C0(0.06666667f);
            unk_42C->unk_284->sub_796A0((RtAnimAnimation *)stk_C, var_4, 0, (type_783F0 *)v8, 0.0f, 1.0f,
                                        1.0f);
            unk_14++;
            unk_42C->unk_19F4 = RpRandom() % 2 + 1;
        }
        else
        {
            unk_14 = 2;
            unk_42C->unk_19F4 = RpRandom() % 2 + 1;
        }
    }
    else if (unk_14 == 1)
    {
        switch (unk_42C->unk_1A04)
        {
        case 1:
            var_4 = dword_4C1980[2];
            break;
        case 2:
            var_4 = dword_4C1980[3];
            break;
        default:
            if (unk_42C->unk_19F4 == 1)
            {
                var_4 = dword_4C1980[0];
            }
            else
            {
                var_4 = dword_4C1980[1];
            }
            break;
        }
        if (sub_77B70(var_4, (void **)(&stk_C), (void **)(&v8)))
        {
            unk_42C->unk_284->sub_794C0(0.0f);
            unk_42C->unk_284->sub_796A0((RtAnimAnimation *)stk_C, var_4, 0, (type_783F0 *)v8, 0.0f, 1.0f,
                                        1.0f);
            unk_14++;
#ifdef CODFH_SP // single player shows the killed-in-action help message when help is on (SP 0xD1D0A)
            if (dword_4F28F0->unk_28)
            {
                type_3DF8D8_04 v_msg;

                sub_198A20("COD_HelpMessages+Generic+Error_LevelFailKIA", &v_msg);
                sub_17C500(&v_msg, 0, 1);
            }
#endif
        }
        else
        {
            return 0;
        }
    }
    else if (unk_14 >= 2)
    {
#ifdef CODFH_SP
        // single player fades out with no session test, and sets the
        // player's camera's landed flag (SP 0xD1D5D, +0x210C: MP's +0x2110)
        if (unk_14 == 2)
        {
            type_3DD948 *v_w;

            sub_124EE0(2.0f, 1);
            sub_1252E0(sub_119480, 1);
            v_w = (type_3DD948 *)unk_42C->unk_2110.sub_D4910();
            if (v_w)
                v_w->unk_3B0 = 1;
        }
#else
        if ((var_10 = dword_4FBAA8) == 0 && (lv_14 = dword_4FBAA4) == 0 && unk_14 == 2)
        {
            if (!((dword_4B86F8 >> 4) & 1))
            {
                sub_124EE0(2.0f, 1);
                sub_1252E0(sub_119480, 1);
            }
            else
            {
                return 1;
            }
        }
#endif
        switch (unk_42C->unk_1A04)
        {
        case 1:
            var_4 = dword_4C1980[7];
            break;
        case 2:
            var_4 = dword_4C1980[8];
            break;
        default:
            if (unk_42C->unk_19F4 == 1)
            {
                var_4 = dword_4C1980[5];
            }
            else
            {
                var_4 = dword_4C1980[6];
            }
            break;
        }
        if (sub_77B70(var_4, (void **)(&stk_C), (void **)(&v8)))
        {
            unk_42C->unk_284->sub_794C0(0.06666667f);
            unk_42C->unk_284->sub_796A0((RtAnimAnimation *)stk_C, var_4, 0, (type_783F0 *)v8, 0.0f, 1.0f,
                                        1.0f);
            unk_14++;
        }
        else
        {
            return 0;
        }
    }
    return 1;
}

// match: ?sub_119830@type_10F710_1A48@@QAE_NHH@Z @ 0x00119830
// sp-match: ?sub_119830@type_10F710_1A48@@QAE_NHH@Z @ 0x000D1E40
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
// Takes the stance arg_0: its animation (arg_4 picks the aimed ones), unless
// busy or (with the second recoil settings) holding weapon 0, 13, 17 or 18;
// then its sway bounded by the stance's (less 1 while the recoil ends).
bool type_10F710_1A48::sub_119830(RwInt32 arg_0, RwInt32 arg_4)
{
    RtAnimAnimation *slot_C;
    RwInt32 bp_8;
    RwInt32 bp_4;

    bp_4 = 0;
    if (arg_4)
    {
        switch (arg_0)
        {
        case 0:
            bp_4 = unk_448->unk_64;
            break;
        case 1:
            bp_4 = unk_448->unk_4C;
            break;
        case 2:
            bp_4 = unk_448->unk_50;
            break;
        }
    }
    else
    {
        switch (arg_0)
        {
        case 0:
            bp_4 = unk_448->unk_58;
            break;
        case 1:
            bp_4 = unk_448->unk_54;
            break;
        case 2:
            bp_4 = unk_448->unk_60;
            break;
        }
    }
    if (sub_77B70(bp_4, (void **)((RwInt32 *)&slot_C), (void **)(&bp_8)))
    {
        RwInt32 var_10;

        var_10 = unk_42C->unk_1A48[unk_42C->unk_1AE4]->get_unk_458();
        if ((!(var_10 == 17 || var_10 == 13 || var_10 == 18 || var_10 == 0 ? 1 : 0) || !unk_42C->unk_1B04) &&
            !unk_45 && !unk_42C->unk_1B2C && !unk_228 && !unk_22C && !unk_12 && !unk_11 && !unk_224)
        {
            unk_42C->unk_284->sub_794C0(0.0f);
            unk_42C->unk_284->sub_796A0(slot_C, bp_4, 0, (type_783F0 *)bp_8, 0.0f, 1.0f, 1.0f);
        }
        unk_10 = 0;
        unk_234 = 1;
        unk_42C->unk_1A18 = 1.0f / (slot_C->duration * 30.0f);
    }
    if (unk_298 > unk_448->unk_3B0_a[unk_42C->unk_1A04] || unk_298 > unk_448->unk_410_a[unk_42C->unk_1A04])
    {
        if (unk_448->unk_3B0_a[unk_42C->unk_1A04] > unk_448->unk_410_a[unk_42C->unk_1A04])
        {
            unk_298 = unk_448->unk_3B0_a[unk_42C->unk_1A04];
        }
        else
        {
            unk_298 = unk_448->unk_410_a[unk_42C->unk_1A04];
        }
        if (unk_42C->unk_1B08)
        {
            unk_298 -= 1.0f;
        }
    }
    return 1;
}

// match: ?sub_119B70@@YAPAUtype_4C19C0@@H@Z @ 0x00119B70
// sp-match: ?sub_119B70@@YAPAUtype_4C19C0@@H@Z @ 0x000D2040
type_4C19C0 *sub_119B70(RwInt32 arg_0)
{
    if (arg_0 < 0 || arg_0 >= 39)
    {
        return 0;
    }
    return &dword_4C19C0[arg_0];
}

// match: ?sub_119BA0@@YAHPAUtype_F2FF0@@@Z @ 0x00119BA0
// match: __ehhandler$?sub_119BA0@@YAHPAUtype_F2FF0@@@Z-0x8 @ 0x00301440
// match: __ehhandler$?sub_119BA0@@YAHPAUtype_F2FF0@@@Z @ 0x00301448
// sp-match: ?sub_119BA0@@YAHPAUtype_F2FF0@@@Z @ 0x000D2060
// A weapon's particle system's callback (its unk_154, vf_030): follows its
// entity's weapon in hand's tagged matrix unk_158 (on its model, else on the
// player's clump), turned about z by the weapon's unk_450 and scaled by its
// unk_454. With no entity, 0 once an endless system is left.
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
RwInt32 sub_119BA0(type_F2FF0 *arg_0)
{
    RwInt32 var_14 = 1;
    type_D48D0 lv_10;
    type_3D3548 *var_18;
    type_10F710 *slot_1C;
    RwV3d v28;
    RwV3d v34;
    type_10F710_1A48 *l38;

    lv_10 = arg_0->unk_150;
    var_18 = lv_10.sub_D4910();
    if (var_18)
    {
        slot_1C = var_18->vf_00C();
        l38 = slot_1C->unk_1A48[slot_1C->unk_1AE4];
        if (l38 && !sub_EC310(l38->unk_420.get_unk_08(), slot_1C->unk_284->get_unk_18(), (RwMatrix *)arg_0,
                                 arg_0->unk_158, 0, 0))
        {
            sub_EC310(l38->unk_430.get_unk_08(), slot_1C->unk_284->get_unk_18(), (RwMatrix *)arg_0, arg_0->unk_158,
                      0, 0);
        }
        v28.x = 0.0f;
        v28.y = 0.0f;
        v28.z = 1.0f;
        RwMatrixRotate((RwMatrix *)arg_0, &v28, l38->get_unk_450(), rwCOMBINEPRECONCAT);
        v34.x = v34.y = v34.z = l38->get_unk_454();
        RwMatrixScale((RwMatrix *)arg_0, &v34, rwCOMBINEPRECONCAT);
    }
    else if (arg_0->unk_44->unk_20 == 0.0f)
    {
        var_14 = 0;
    }
    return var_14;
}

// match: ?sub_119D50@@YAHPAUtype_F2FF0@@@Z @ 0x00119D50
// match: __ehhandler$?sub_119D50@@YAHPAUtype_F2FF0@@@Z-0x8 @ 0x00301460
// match: __ehhandler$?sub_119D50@@YAHPAUtype_F2FF0@@@Z @ 0x00301468
// sp-match: ?sub_119D50@@YAHPAUtype_F2FF0@@@Z @ 0x000D2170
// Likewise for the muzzle flash (vf_018): the weapon's model's 'FIRE' matrix,
// moved by the settings' unk_168 of weapon unk_158.
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
RwInt32 sub_119D50(type_F2FF0 *arg_0)
{
    RwInt32 var_14 = 1;
    type_D48D0 var_18;
    type_3D3548 *v20;
    RwInt32 local_24;
    type_10F710 *bp_28;
    RwMatrix loc70;
    RwMatrix slot_B0;

    var_18 = arg_0->unk_150;
    v20 = var_18.sub_D4910();
    local_24 = arg_0->unk_158;
    if (v20)
    {
        bp_28 = v20->vf_00C();
        sub_EC310(bp_28->unk_1A48[bp_28->unk_1AE4]->unk_420.get_unk_08(), bp_28->unk_284->get_unk_18(), &loc70,
                  0x46495245, 0, 1); // not an address: the tag 'FIRE'
        slot_B0 = loc70;
        RwMatrixTranslate(&slot_B0, &bp_28->unk_1A48[local_24]->get_unk_448()->unk_168, rwCOMBINEPRECONCAT);
        *(RwMatrix *)arg_0 = slot_B0;
    }
    else if (arg_0->unk_44->unk_20 == 0.0f)
    {
        var_14 = 0;
    }
    return var_14;
}

// match: ?vf_024@type_10F710_1A48@@UAEXXZ @ 0x00119ED0
// sp-match: ?vf_024@type_10F710_1A48@@UAEXXZ @ 0x000D2260
// Reloads: moves what the clip lacks from the reserve, and shows it.
void type_10F710_1A48::vf_024()
{
    RwUInt32 var_4;

    var_4 = unk_448->unk_C8 - unk_414;
    var_4 = var_4 < (RwUInt32)unk_418 ? var_4 : unk_418;
    unk_414 += var_4;
    unk_418 -= var_4;
    if (dword_4B9190)
    {
        dword_4B9190->sub_E07A0(unk_414, unk_448->unk_C8);
    }
    sub_115390(unk_414, unk_418);
    unk_12 = 0;
}

// match: ?vf_030@type_10F710_1A48@@UAEXHHH@Z @ 0x00119FA0
// sp-match: ?vf_030@type_10F710_1A48@@UAEXHHH@Z @ 0x000D4E30
// Its animation's events (arg_0, with the event's data arg_4): particles at
// a point of its model (1300) or at the player's offset (1301), particles on
// a tagged matrix that follow it (1302), a spent shell (3000), a sound (1100,
// by the surface's or the player's tag), a reload (2400, event 6), the
// sequence (1700), and the end of an animation (1): the next state (drawing,
// bipod, reload by rounds), then the animation that follows.
void type_10F710_1A48::vf_030(RwInt32 arg_0, RwInt32 arg_4, RwInt32 arg_8)
{
    type_3DF8D8_04 var_C;
    type_4E5E40 *var_10;
    type_4E5E40_08 *var_14;

    var_10 = &dword_4E5E40;
    var_14 = var_10->unk_08;
    switch ((RwUInt32)arg_0)
    {
    case 1300:
    {
        type_10F710_1A48_ev *var_1C;
        RwV3d *var_20;
        RpClump *var_24;
        RwFrame *var_28;
        RwMatrix *var_2C;
        RwV3d var_38;
        RwMatrix var_80;

        var_1C = (type_10F710_1A48_ev *)arg_4;
        var_20 = (RwV3d *)arg_4;
        var_24 = unk_420.get_unk_08();
        var_28 = RpClumpGetFrame(var_24);
        var_2C = RwFrameGetLTM(var_28);
        var_38.x = var_20->x;
        var_38.y = var_20->y;
        var_38.z = var_20->z;
        var_80 = *var_2C;
        RwMatrixTranslate(&var_80, &var_38, rwCOMBINEPRECONCAT);
        sub_F2FF0(var_1C->unk_0C, &var_80, 0, 1, 0, 1);
        break;
    }
    case 1301:
    {
        type_10F710_1A48_ev *var_84;
        RwV3d *var_88;
        RwV3d var_94;
        RwMatrix var_E0;

        var_84 = (type_10F710_1A48_ev *)arg_4;
        var_88 = (RwV3d *)arg_4;
        var_94.x = var_88->x;
        var_94.y = var_88->y;
        var_94.z = var_88->z;
        RwMatrixSetIdentity(&var_E0);
        RwMatrixTranslate(&var_E0, &var_94, rwCOMBINEREPLACE);
        sub_F2FF0(var_84->unk_0C, &var_E0, 0, 1, 0, 1);
        break;
    }
    case 1302:
    {
        type_10F710_1A48_ev *var_E4;
        RwMatrix var_130;
        type_F2FF0 *var_134;
        type_F2FF0 *var_148;

        var_E4 = (type_10F710_1A48_ev *)arg_4;
        if (unk_465)
        {
            if (sub_EC310(unk_420.get_unk_08(), unk_42C->unk_284->get_unk_18(), &var_130, var_E4->unk_00, 0, 0))
            {
                var_134 = (type_F2FF0 *)sub_F2FF0(var_E4->unk_0C, &var_130, 0, 1, 0, 1);
                if (var_134)
                {
                    var_134->unk_150_h = unk_42C->get_unk_384_h();
                    var_134->unk_158 = var_E4->unk_00;
                    var_134->unk_154 = sub_119BA0;
                    var_134->unk_40 |= 0x40;
                }
            }
            else if (sub_EC310(unk_430.get_unk_08(), unk_42C->unk_284->get_unk_18(), &var_130, var_E4->unk_00, 0,
                               1))
            {
                var_148 = (type_F2FF0 *)sub_F2FF0(var_E4->unk_0C, &var_130, 0, 1, 0, 1);
                if (var_148)
                {
                    var_148->unk_150_h = unk_42C->get_unk_384_h();
                    var_148->unk_158 = var_E4->unk_00;
                    var_148->unk_154 = sub_119BA0;
                    var_148->unk_40 |= 0x40;
                }
            }
        }
        break;
    }
    case 3000:
    {
        type_10F710_1A48_shell *var_154;
        RwMatrix var_1A0;

        var_154 = (type_10F710_1A48_shell *)arg_4;
        switch (var_154->unk_00)
        {
        case 1:
            if (!unk_414 &&
                sub_EC310(unk_420.get_unk_08(), unk_42C->unk_284->get_unk_18(), &var_1A0, 0x53484C4C, 0, 0))
            { // not an address: the tag 'SHLL'
                sub_F2FF0(var_154->unk_04, &var_1A0, 0, 1, 0, 1);
                var_C.unk_00 = var_154->unk_08.unk_00;
                var_C.unk_04 = var_154->unk_08.unk_04;
                unk_42C->unk_1C0.sub_8A980(&var_C, unk_42C, 0, unk_42C->sub_CD550(), 0, 0);
            }
            break;
        }
        break;
    }
    case 1100:
        memcpy(&var_C, (void *)arg_4, 8);
        if (((type_10F710_1A48_snd *)arg_4)->unk_08 & 1)
        {
            if (unk_42C->unk_294 < 0)
            {
                if (dword_44E838)
                {
                    type_3DF8D8_04 var_1A8;
                    type_3D3548 *var_1AC;

                    var_1A8.unk_00 = 0x9FAFD39B; // not an address: a key
                    var_1A8.unk_04 = 0xAB43C2E3; // not an address: a key
                    var_1AC = sub_1745A0(0);
                    dword_4B1E98.sub_8A980(&var_1A8, 0, 0, var_1AC->sub_CD550(), 1, 0);
                }
#ifndef CODFH_SP // single player compiles the debug print and its test out (SP 0xD4E30)
                if (dword_44E860 && dword_44E874)
                {
                    sub_19A750("Audio: WARNING! Player on non-tagged surface! Using 0 for Index Alias purposes");
                }
#endif
                unk_42C->unk_294 = 0;
            }
            unk_42C->unk_1C0.sub_8AA70(&var_C, var_14[unk_42C->unk_294].unk_00, unk_42C, 0, unk_42C->sub_CD550(), 0,
                                       0);
        }
        else if (((type_10F710_1A48_snd *)arg_4)->unk_08 & 0x10)
        {
            unk_42C->unk_1C0.sub_8AA70(&var_C, var_14[unk_42C->unk_290].unk_00, unk_42C, 0, unk_42C->sub_CD550(), 0,
                                       0);
        }
        else
        {
            unk_42C->unk_1C0.sub_8A980(&var_C, unk_42C, 0, unk_42C->sub_CD550(), 0, 0);
        }
        break;
    case 2400:
    {
        RwInt32 *var_1B0;

        var_1B0 = (RwInt32 *)arg_4;
        switch (*var_1B0)
        {
        case 6:
            if (unk_12)
            {
                vf_024();
            }
            break;
        }
        break;
    }
    case 1:
    {
        RwReal var_1B8;
        RwReal var_1BC;
        RwReal var_1C0;
        RwInt32 var_1C4;
        RwInt32 var_1C8;
        type_10F710_1A48 *var_1DC;
        RwInt32 var_1EC;
        RwInt32 var_1F0;

        var_1B8 = 0.0f;
        var_1BC = 1.0f;
        var_1C0 = 1.0f;
        var_1C4 = unk_448->unk_28;
        var_1C8 = 0;
        unk_13 = 1;
        if (unk_42C->unk_1A04 == 2)
        {
            switch (unk_42C->unk_19D8)
            {
            case 1:
            case 3:
                var_1C4 = unk_448->unk_3C;
                unk_42C->unk_19D8 = 1;
                break;
            case 2:
            case 4:
                var_1C4 = unk_448->unk_40;
                unk_42C->unk_19D8 = 2;
                break;
            case 0:
            case 5:
                var_1C4 = unk_448->unk_28;
                unk_42C->unk_19D8 = 0;
                break;
            }
        }
        if (unk_42C->unk_19D0 != 10)
        {
            switch (unk_224)
            {
            case 1:
                unk_224 = 2;
                var_1C4 = unk_448->unk_34;
                if (unk_42C->unk_1A48[unk_42C->unk_20F8]->get_unk_45C() == 2)
                {
                    var_1C0 = 3.0f;
                }
                break;
            case 2:
                unk_42C->sub_100560();
                unk_224 = 0;
                var_1C4 = unk_448->unk_38;
                var_1DC = unk_42C->get_hand();
                if (var_1DC && var_1DC->get_unk_45C() == 2)
                {
                    ((type_3DA5A0 *)var_1DC)->sub_11B870(1.0f);
                    return;
                }
                if (var_1DC)
                {
                    var_1DC->unk_224 = 3;
                    var_1C4 = var_1DC->get_unk_448()->unk_38;
                }
                if (unk_42C->unk_1B30[unk_42C->unk_1AE8 == 0] == 32)
                {
                    unk_42C->unk_1B30[unk_42C->unk_1AE8 == 0] = -1;
                }
                break;
            case 3:
                unk_224 = 0;
                if (!unk_414 && unk_418)
                {
                    vf_020();
                    var_1C8 = 1;
                    var_1C4 = 0;
                }
                break;
            }
        }
        if (unk_228)
        {
            unk_228 = 0;
            unk_230 = 1;
            unk_42C->unk_544 = 0.0f;
            unk_42C->unk_548 = 0.0f;
            unk_42C->unk_530 = 0.0f;
        }
        if (unk_22C)
        {
            unk_22C = 0;
        }
        if (unk_230)
        {
            var_1C4 = unk_448->unk_70;
        }
        if (unk_234)
        {
            unk_234 = 0;
        }
        if (unk_42C->unk_1B04)
        {
            var_1C0 = 0.1f;
        }
        if (unk_12 && !var_1C8)
        {
            if (unk_448->unk_80)
            {
                switch (unk_60)
                {
                case 1:
                    if (sub_77B70(unk_448->unk_88, (void **)(&var_1F0), (void **)(&var_1EC)))
                    {
                        unk_42C->unk_284->sub_794C0(0.06666667f);
                        unk_42C->unk_284->sub_796A0((RtAnimAnimation *)var_1F0, unk_448->unk_88, 0,
                                                    (type_783F0 *)var_1EC, 0.0f, 1.0f, 1.0f);
                    }
                    unk_60 = 2;
                    unk_13 = 0;
                    break;
                case 2:
                    unk_414++;
                    unk_418--;
                    if (dword_4B9190)
                    {
                        dword_4B9190->sub_E07A0(unk_414, unk_448->unk_C8);
                    }
                    sub_115390(unk_414, unk_418);
                    unk_13 = 0;
                    if (!unk_418 || (RwUInt32)unk_414 == unk_448->unk_C8)
                    {
                        unk_60 = 3;
                        if (sub_77B70(unk_448->unk_8C, (void **)(&var_1F0), (void **)(&var_1EC)))
                        {
                            unk_42C->unk_284->sub_794C0(0.06666667f);
                            unk_42C->unk_284->sub_796A0((RtAnimAnimation *)var_1F0, unk_448->unk_8C, 0,
                                                        (type_783F0 *)var_1EC, 0.0f, 1.0f, 1.0f);
                        }
                    }
                    else if (sub_77B70(unk_448->unk_88, (void **)(&var_1F0), (void **)(&var_1EC)))
                    {
                        unk_42C->unk_284->sub_794C0(0.06666667f);
                        unk_42C->unk_284->sub_796A0((RtAnimAnimation *)var_1F0, unk_448->unk_88, 0,
                                                    (type_783F0 *)var_1EC, 0.0f, 1.0f, 1.0f);
                    }
                    break;
                case 3:
                    unk_60 = 0;
                    unk_12 = 0;
                    unk_13 = 1;
                    break;
                default:
                    unk_60 = 0;
                    unk_12 = 0;
                    unk_13 = 1;
                    break;
                }
            }
            else
            {
                vf_024();
            }
        }
        else if (var_1C4 && sub_77B70(var_1C4, (void **)(&var_1F0), (void **)(&var_1EC)))
        {
            unk_42C->unk_284->sub_794C0(0.0f);
            unk_42C->unk_284->sub_796A0((RtAnimAnimation *)var_1F0, var_1C4, 0, (type_783F0 *)var_1EC, var_1B8,
                                        var_1BC, var_1C0);
        }
        if (unk_14 > 0)
        {
            vf_028();
        }
#ifdef CODFH_SP // single player clears them only while unk_45 is set (SP 0xD53BD)
        if (unk_45)
        {
            unk_45 = 0;
            unk_42C->unk_1B1C = 0;
            unk_42C->unk_1B14 = 0;
        }
#else
        unk_45 = 0;
        unk_42C->unk_1B1C = 0;
        unk_42C->unk_1B14 = 0;
#endif
        if (!var_1C8 && !unk_60)
        {
            unk_10 = 1;
        }
        unk_11 = 0;
        if (unk_42C->unk_19D0 == 14)
        {
            unk_42C->sub_10E750(0, 1);
        }
        break;
    }
    case 1700:
        sub_11CF50(unk_42C);
        break;
    }
}

// match: ?vf_004@type_3DA5A0@@UAE_NPAUtype_10F710@@PAURpClump@@HH@Z @ 0x0011AF30
// sp-match: ?vf_004@type_3DA5A0@@UAE_NPAUtype_10F710@@PAURpClump@@HH@Z @ 0x000D22D0
// The launcher kind (2): the base set-up, and nothing loaded or firing.
bool type_3DA5A0::vf_004(type_10F710 *arg_0, RpClump *arg_4, RwInt32 arg_8, RwInt32 arg_C)
{
    type_10F710_1A48::vf_004(arg_0, arg_4, arg_8, arg_C);
    unk_45C = 2;
    unk_474 = 0;
    unk_470 = 0;
    unk_478 = 0;
    return 1;
}

// (vf_020, type_10F710.h's trivial inline: single player keeps this file's copy,
// after vf_018 in the image)
// sp-match: ?vf_020@type_3DA5A0@@UAE_NXZ @ 0x000D23C0

// match: ?vf_018@type_3DA5A0@@UAE_NXZ @ 0x0011AF90
// sp-match: ?vf_018@type_3DA5A0@@UAE_NXZ @ 0x000D2320
// Fires: its settings' animation unk_2C, unless out of rounds (with some to
// hold); whether it may.
bool type_3DA5A0::vf_018()
{
    RwInt32 var_4;
    RwInt32 local_8;

    if (unk_418 || !unk_448->unk_CC)
    {
        if (sub_77B70(unk_448->unk_2C, (void **)(&local_8), (void **)(&var_4)))
        {
            unk_42C->unk_284->sub_794C0(0.06666667f);
            unk_42C->unk_284->sub_796A0((RtAnimAnimation *)local_8, unk_448->unk_2C, 0, (type_783F0 *)var_4, 0.0f,
                                        1.0f, 1.0f);
            unk_10 = 0;
        }
#ifdef CODFH_DRAW_TRIGGERS
        else
        {
            // (the debug tools: a map that never set this grenade's throw animation
            // up, as the multiplayer maps: the animation's events at once,
            // the release (1900, the projectile) and the end (back to the
            // weapon before), when the projectile's object is loaded)
            type_495F0 *pDef = (type_495F0 *)sub_198800(&unk_448->unk_00);

            if (pDef && sub_198800(&pDef->unk_38.unk_04))
            {
                vf_030(1900, 0, 0);
                vf_030(1, 0, 0);
            }
        }
#endif
        return 1;
    }
    return 0;
}

// Fires its projectile (at its animation's event 1900): from the model's
// "FIRE" node, pushed along the camera's at row, at the settings' speed
// for how it was loaded (unk_47C) turned up by the camera's right row
// (unk_4D8); its record (unk_390, the 0x84-byte settings sub_15F2C0 takes)
// filled from the settings, of table 5 with arg_0, 6 with arg_4 (and the
// longer time), else 2; a grenade kind (0x402) for a player of kind 2,
// else 0x401; raised by 10 while crouched; then the network is told.
// match: ?sub_11B040@type_3DA5A0@@QAEXHH@Z @ 0x0011B040
// sp-match: ?sub_11B040@type_3DA5A0@@QAEXHH@Z @ 0x000D23D0
void type_3DA5A0::sub_11B040(RwInt32 arg_0, RwInt32 arg_4)
{
    RwInt32 v_8;
    RwReal v_C;
    RwMatrix *v_10;
    RpHAnimHierarchy *v_14;
    RwMatrix *v_18;
    RpClump *v_1C;
    RwMatrix v_60;
    RwMatrix *v_64;
    RwReal v_68;
    RwV3d v_74;
    RwMatrix v_C0;
    RwV3d v_CC;
    type_495F0 *v_D0;
    RwInt32 v_DC;

    if (unk_47C)
    {
        v_8 = 0;
        v_C = 13.0f;
    }
    else
    {
        v_8 = 1;
        v_C = 15.0f;
    }
    v_10 = RwFrameGetMatrix(RwCameraGetFrame((RwCamera *)dword_4E5C74));
    memset(&unk_390, 0, sizeof(type_439A48));
    v_14 = unk_42C->unk_284->unk_18;
    v_18 = RpHAnimHierarchyGetMatrixArray(v_14);
    v_1C = unk_420.unk_08;
    sub_EC310(v_1C, v_14, &v_60, 0x46495245, 0, 1); // not an address: 'FIRE'
    v_64 = v_18;
    v_68 = dword_429B64;
    if (unk_458 == 0x21)
        v_68 = 15.0f;
    RwV3dScaleMacro(&v_74, &v_10->at, dword_429B64);
    RwV3dAddMacro(&v_60.pos, &v_74, &v_60.pos);
    RwMatrixInitializeMacro(&v_C0, rwMATRIXTYPENORMAL);
    sub_14D1B0(&v_C0, v_10->right.x, v_10->right.y, v_10->right.z, unk_448->unk_4D8);
    sub_141320(&v_CC, &v_10->at, &v_C0);
    RwV3dScaleMacro(&v_CC, &v_CC, (&unk_448->unk_490)[v_8]);
    v_D0 = (type_495F0 *)sub_198800(&unk_448->unk_00);
    if (arg_0)
        ((type_439A48 *)&unk_390)->unk_00 = 5;
    else if (arg_4)
        ((type_439A48 *)&unk_390)->unk_00 = 6;
    else
        ((type_439A48 *)&unk_390)->unk_00 = 2;
#ifdef CODFH_SP // single player scales the damage by the difficulty (SP 0xD2535)
    ((type_439A48 *)&unk_390)->unk_04 = (RwUInt32)unk_448->unk_C4 * difficulty_4F286C();
#else
    ((type_439A48 *)&unk_390)->unk_04 = (RwUInt32)unk_448->unk_C4 * 1.0f;
#endif
    ((type_439A48 *)&unk_390)->unk_38 = v_D0->sub_18F800(&v_D0->unk_38);
    ((type_439A48 *)&unk_390)->unk_3C = 1;
    ((type_439A48 *)&unk_390)->unk_40 = unk_448->unk_C0_f;
    ((type_439A48 *)&unk_390)->unk_44 = (&unk_448->unk_498)[v_8];
    ((type_439A48 *)&unk_390)->unk_48 = (&unk_448->unk_4AC_f)[v_8];
    ((type_439A48 *)&unk_390)->unk_4C = unk_448->unk_D0;
    if (arg_4)
        ((type_439A48 *)&unk_390)->unk_50 = 18000.0f;
    else
        ((type_439A48 *)&unk_390)->unk_50 = unk_448->unk_4B4;
#ifdef CODFH_SP // and this one likewise (SP 0xD25E9)
    ((type_439A48 *)&unk_390)->unk_54 = unk_448->unk_4B8_f * difficulty_4F286C();
#else
    ((type_439A48 *)&unk_390)->unk_54 = unk_448->unk_4B8_f * 1.0f;
#endif
    ((type_439A48 *)&unk_390)->unk_58 = unk_448->unk_4BC;
    ((type_439A48 *)&unk_390)->unk_60 = unk_448->unk_4C4_f;
    ((type_439A48 *)&unk_390)->unk_5C = unk_448->unk_4C0;
    ((type_439A48 *)&unk_390)->unk_64 = unk_448->unk_4C8_f;
    ((type_439A48 *)&unk_390)->unk_68 = unk_448->unk_4CC;
    ((type_439A48 *)&unk_390)->unk_70 = unk_448->unk_98_f;
    ((type_439A48 *)&unk_390)->unk_6C = unk_448->unk_9C;
    ((type_439A48 *)&unk_390)->unk_78 = unk_448->unk_A0_f;
    ((type_439A48 *)&unk_390)->unk_74 = unk_448->unk_A4_f;
    ((type_439A48 *)&unk_390)->unk_7C = unk_448->unk_A8;
    ((type_439A48 *)&unk_390)->unk_80 = unk_448->unk_AC_f;
    if ((unk_42C->unk_2C & 7) == 2)
        v_DC = 0x402;
    else
        v_DC = 0x401;
    v_60.up.x = 0.0f;
    v_60.up.y = 1.0f;
    v_60.up.z = 0.0f;
    v_60.at.x = 0.0f;
    v_60.at.y = 0.0f;
    v_60.at.z = 1.0f;
    v_60.right.x = 1.0f;
    v_60.right.y = 0.0f;
    v_60.right.z = 0.0f;
    if (unk_42C->unk_1A04 == 2)
        v_60.pos.y += 10.0f;
    sub_15F2C0(v_DC, (RwInt32)unk_42C, &v_60, &v_CC, unk_42C->vf_138(), (type_439A48 *)&unk_390, 0);
#ifndef CODFH_SP // single player sends no network message for the shot (SP 0xD26A0 returns after sub_15F2C0)
    sub_1C5CA0((type_1F8560_v &)v_60.pos, (type_1F8560_v &)v_CC, v_8, unk_458);
#endif
}

// match: ?vf_030@type_3DA5A0@@UAEXHHH@Z @ 0x0011B590
// sp-match: ?vf_030@type_3DA5A0@@UAEXHHH@Z @ 0x000D5720
// Its animation's events: at an animation's end, the death's next step, the
// loaded animation (kept or dropped by unk_47C), or back to the weapon
// before (unk_1AF0) after firing; 1900 fires (sub_11B040) unless the
// player's unk_217C; the rest as the base's.
void type_3DA5A0::vf_030(RwInt32 arg_0, RwInt32 arg_4, RwInt32 arg_8)
{
    RwInt32 l4;
    RwInt32 var_8;
    RwInt32 fp_C;
    RwInt32 v10;
    RwInt32 local_14;
    type_4C19C0 *var18;
    type_10F710 *var_1C;
    RwInt32 l20;
    type_10F710 *fp_24;
    type_10F710 *fp_28;

    if (arg_0 == 1 && unk_14 > 0)
    {
        vf_028();
    }
    else if (arg_0 == 1 && unk_474)
    {
        if (unk_47C)
        {
            fp_C = unk_448->unk_4A4;
        }
        else
        {
            fp_C = unk_448->unk_4A8;
        }
        if (sub_77B70(fp_C, (void **)(&var_8), (void **)(&l4)))
        {
            unk_42C->unk_284->sub_794C0(0.06666667f);
            unk_42C->unk_284->sub_796A0((RtAnimAnimation *)var_8, fp_C, 0, (type_783F0 *)l4, 0.0f, 1.0f, 1.0f);
            unk_10 = 0;
            unk_474 = 0;
            unk_470 = 1;
        }
    }
    else if (arg_0 == 1 && unk_478)
    {
        unk_470 = 0;
        unk_42C->unk_1B2C = 0;
        var_1C = unk_42C;
        var_1C->unk_1A48[var_1C->unk_1AE4]->sub_117370();
        l20 = unk_42C->unk_1AF0;
        fp_24 = unk_42C;
        fp_24->unk_1AE4 = l20;
        fp_28 = unk_42C;
        fp_28->unk_1A48[fp_28->unk_1AE4]->sub_1170B0(1, 1);
        var18 = unk_42C->unk_1A48[unk_42C->unk_1AE4]->get_unk_448();
#ifdef CODFH_SP // shape: single player reuses the first pair of locals, so both pairs share the dead argument slots (SP 0xD5720)
        if (sub_77B70(var18->unk_38, (void **)(&var_8), (void **)(&l4)))
        {
            unk_42C->unk_284->sub_794C0(0.0f);
            unk_42C->unk_284->sub_796A0((RtAnimAnimation *)var_8, var18->unk_38, 0, (type_783F0 *)l4, 0.0f,
                                        1.0f, 3.0f);
#else
        if (sub_77B70(var18->unk_38, (void **)(&local_14), (void **)(&v10)))
        {
            unk_42C->unk_284->sub_794C0(0.0f);
            unk_42C->unk_284->sub_796A0((RtAnimAnimation *)local_14, var18->unk_38, 0, (type_783F0 *)v10, 0.0f,
                                        1.0f, 3.0f);
#endif
            unk_42C->unk_1A48[unk_42C->unk_1AE4]->unk_224 = 3;
        }
    }
    else if (arg_0 == 1900)
    {
#ifdef CODFH_SP // MP 0x11B590; single player (SP 0xD5720) has no unk_217C: the block always runs
        if (1)
#else
        if (!unk_42C->unk_217C)
#endif
        {
            sub_11B040(unk_448->unk_4D0, unk_448->unk_4D4);
        }
        unk_478 = 1;
        unk_470 = 0;
    }
    else
    {
        type_10F710_1A48::vf_030(arg_0, arg_4, arg_8);
    }
}

// match: ?sub_11B870@type_3DA5A0@@QAEXM@Z @ 0x0011B870
// sp-match: ?sub_11B870@type_3DA5A0@@QAEXM@Z @ 0x000D2750
// Loads it (the base's event handler, for a weapon change to it): its
// settings' animation unk_4A0, then loaded (unk_474, unk_47C) with the
// player's unk_1B2C set. arg_0 is unused.
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void type_3DA5A0::sub_11B870(RwReal arg_0)
{
    RwInt32 var_4;
    RwInt32 local_8;

    if (unk_448 && sub_77B70(unk_448->unk_4A0, (void **)(&local_8), (void **)(&var_4)))
    {
        unk_42C->unk_284->sub_794C0(0.06666667f);
        unk_42C->unk_284->sub_796A0((RtAnimAnimation *)local_8, unk_448->unk_4A0, 0, (type_783F0 *)var_4, 0.0f, 1.0f,
                                    1.0f);
        unk_10 = 0;
        unk_474 = 1;
        unk_42C->unk_1B2C = 1;
        unk_47C = 1;
    }
}

// match: ?vf_004@type_3DA558@@UAE_NPAUtype_10F710@@PAURpClump@@HH@Z @ 0x0011B940
// sp-match: ?vf_004@type_3DA558@@UAE_NPAUtype_10F710@@PAURpClump@@HH@Z @ 0x000D2800
// The mounted kind (4): the base set-up, then (arg_C) its object's model
// (settings' named object's unk_38) set down.
bool type_3DA558::vf_004(type_10F710 *arg_0, RpClump *arg_4, RwInt32 arg_8, RwInt32 arg_C)
{
    type_495F0 *var_4;
    RpClump *local_8;

    type_10F710_1A48::vf_004(arg_0, arg_4, arg_8, arg_C);
    unk_45C = 4;
    var_4 = (type_495F0 *)sub_198800(&unk_448->unk_00);
    if (arg_C)
    {
        local_8 = (RpClump *)var_4->sub_18F800(&var_4->unk_38);
        RWS::ClumpHelper::SetCanCollide(*local_8, 0);
    }
    return 1;
}

// Fires once its recoil time (unk_220) reaches the settings' rate (unk_BC);
// false before. From a vehicle's seat the vehicle fires (its vf_2A8).
// Otherwise from the model's "FIRE" node towards 2000 along the view: the
// camera's matrix, or within the settings' near and far ranges (unk_48C,
// unk_488) of the nearest world hit along the camera's at row a blend
// towards the aim matrix (sub_141690) by that distance; its spread (unk_450,
// unk_454) random within the settings'; the projectile's record (unk_30C,
// table 3) filled from the settings; a round taken when they count
// (unk_CC); fired as kind 0x1002 for a player of kind 2, else 0x1001; the
// vehicle it stands on pushed back by its mass, the camera shaken, the
// muzzle light lit, and its animation played (or its particle events'
// effects spawned from a vehicle's seat).
// match: ?vf_018@type_3DA558@@UAE_NXZ @ 0x0011B9C0
// sp-match: ?vf_018@type_3DA558@@UAE_NXZ @ 0x000D2860
bool type_3DA558::vf_018()
{
    RpHAnimHierarchy *v_8;
    RwMatrix *v_C;
    RwMatrix v_50;
    RwV3d v_1E0;
    type_3DBC78 *v_1E4;
    RwV3d v_200;
    type_495F0 *v_204;
    RwInt32 v_214;
    type_3DBC78 *v_218;
    RwInt32 v_260;
    RwInt32 v_264;
    type_783F0_04 *v_268;
    RwInt32 *v_26C;

    if (unk_220 < unk_448->unk_BC)
        return false;
    memset(&unk_30C, 0, sizeof(type_439A48));
    unk_220 = 0.0f;
    v_8 = unk_42C->unk_284->unk_18;
    v_C = RpHAnimHierarchyGetMatrixArray(v_8);
    unk_48 = unk_448->unk_D4;
    if (!unk_42C->unk_4D0)
    {
        RpClump *v_10;
        RwMatrix *v_54;
        RwReal v_58;
        RwLine v_70;
        RwInt32 v_74;
        type_4E5D30 *v_78;
        type_91F40 v_B0;
        RwV3d v_BC;
        RwReal v_C0;
        RwMatrix v_100;
        RwMatrix v_140;
        RwMatrix v_180;
        RtSlerp *v_184;
        RwMatrix v_1D0;
        RwMatrix *v_1D4;
        v_10 = unk_420.unk_08;
        sub_EC310(v_10, v_8, &v_50, 0x46495245, 0, 1); // not an address: 'FIRE'
        v_54 = RwFrameGetMatrix(RwCameraGetFrame((RwCamera *)dword_4E5C74));
#ifdef CODFH_SP
        // shape: the reach scaled by a literal 3, last (SP 0xD2910: fld [+0x488]; fmul 3.0)
        v_58 = unk_448->unk_488_f * 3.0f + flt_3CD8E0;
        v_70.start = v_54->pos;
        v_70.end.x = v_54->at.x * unk_448->unk_488_f * 3.0f + v_70.start.x;
        v_70.end.y = v_54->at.y * unk_448->unk_488_f * 3.0f + v_70.start.y;
        v_70.end.z = v_54->at.z * unk_448->unk_488_f * 3.0f + v_70.start.z;
#else
        v_58 = (RwDouble)unk_448->unk_488_f * flt_3D7118 + flt_3CD8E0;
        v_70.start = v_54->pos;
        v_70.end.x = v_54->at.x * unk_448->unk_488_f * flt_3D7118 + v_70.start.x;
        v_70.end.y = v_54->at.y * unk_448->unk_488_f * flt_3D7118 + v_70.start.y;
        v_70.end.z = v_54->at.z * unk_448->unk_488_f * flt_3D7118 + v_70.start.z;
#endif
        for (v_74 = 0; v_74 < 4; v_74++)
        {
            v_78 = &dword_4E5D30[v_74];
            if (v_78->get_unk_00() && v_78->get_unk_28()
                && sub_91F40(v_78->get_unk_28(), &v_70, &v_B0, 1, 0x590000, 1)) // not an address: line-test flags
            {
                RwV3dSubMacro(&v_BC, &v_B0.unk_08, &v_54->pos);
                if (RwV3dLength((RwV3d *)&v_BC) < v_58)
                    v_58 = RwV3dLength((RwV3d *)&v_BC);
            }
        }
        v_C0 = 1.0f;
        if (v_58 >= unk_448->unk_48C_f && v_58 <= unk_448->unk_488_f)
        {
            v_100 = *v_54;
            sub_141690(&v_140, 0);
            v_180 = v_140;
            v_184 = RtSlerpCreate(0);
            RtSlerpInitialize(v_184, &v_100, &v_180);
            v_C0 = 1.0f - (v_58 - unk_448->unk_48C_f) / (unk_448->unk_488_f - unk_448->unk_48C_f);
            RtSlerpGetMatrix(v_184, &v_1D0, v_C0);
            RtSlerpDestroy(v_184);
        }
        else
            v_1D0 = *v_54;
        v_1D4 = &v_1D0;
        v_1E0 = v_1D4->pos;
        RwV3dIncrementScaledMacro(&v_1E0, &v_1D4->at, 2000.0f);
    }
    else
    {
        v_1E4 = (type_3DBC78 *)unk_42C->vf_200();
        return v_1E4->vf_2A8(0, 0, 1);
    }
    unk_450 = crand() * 2 * unk_448->unk_18C_f - unk_448->unk_18C_f;
    unk_454 = crand() * 2 * unk_448->unk_190_f + 1.0f - unk_448->unk_190_f;
    RwV3dSubMacro(&v_200, &v_1E0, &v_50.pos);
    RwV3dNormalize(&v_200, &v_200);
    RwV3dScaleMacro(&v_200, &v_200, unk_448->unk_B8_f);
    if (unk_448->unk_CC)
        unk_418--;
    v_204 = (type_495F0 *)sub_198800(&unk_448->unk_00);
    ((type_439A48 *)&unk_30C)->unk_00 = 3;
#ifdef CODFH_SP // single player scales the damage by the difficulty (SP 0xD2C39)
    ((type_439A48 *)&unk_30C)->unk_04 = (RwUInt32)unk_448->unk_C4 * difficulty_4F286C();
#else
    ((type_439A48 *)&unk_30C)->unk_04 = (RwUInt32)unk_448->unk_C4 * 1.0f;
#endif
    ((type_439A48 *)&unk_30C)->unk_38 = v_204->sub_18F800(&v_204->unk_38);
    ((type_439A48 *)&unk_30C)->unk_3C = 1;
    ((type_439A48 *)&unk_30C)->unk_40 = unk_448->unk_C0_f;
    ((type_439A48 *)&unk_30C)->unk_44 = unk_448->unk_194_f;
    ((type_439A48 *)&unk_30C)->unk_48 = unk_448->unk_198_f;
    ((type_439A48 *)&unk_30C)->unk_4C = unk_448->unk_D0;
    ((type_439A48 *)&unk_30C)->unk_50 = unk_448->unk_4B4;
    ((type_439A48 *)&unk_30C)->unk_54 = unk_448->unk_4B8_f;
    ((type_439A48 *)&unk_30C)->unk_58 = unk_448->unk_4BC;
    ((type_439A48 *)&unk_30C)->unk_5C = unk_448->unk_4C0;
    ((type_439A48 *)&unk_30C)->unk_60 = unk_448->unk_4C4_f;
    ((type_439A48 *)&unk_30C)->unk_64 = unk_448->unk_4C8_f;
    ((type_439A48 *)&unk_30C)->unk_68 = unk_448->unk_4CC;
    ((type_439A48 *)&unk_30C)->unk_70 = unk_448->unk_98_f;
    ((type_439A48 *)&unk_30C)->unk_6C = unk_448->unk_9C;
    ((type_439A48 *)&unk_30C)->unk_78 = unk_448->unk_A0_f;
    ((type_439A48 *)&unk_30C)->unk_74 = unk_448->unk_A4_f;
    ((type_439A48 *)&unk_30C)->unk_7C = unk_448->unk_A8;
    ((type_439A48 *)&unk_30C)->unk_80 = unk_448->unk_AC_f;
    if ((unk_42C->unk_2C & 7) == 2)
        v_214 = 0x1002;
    else
        v_214 = 0x1001;
    sub_15F2C0(v_214, (RwInt32)unk_42C, &v_50, &v_200, unk_42C->vf_138(), (type_439A48 *)&unk_30C, 0);
    v_218 = (type_3DBC78 *)unk_42C->vf_200();
    if (v_218)
    {
        RwV3d v_224;
        RwV3d v_230;
        v_224.x = 0.0f;
        v_224.y = 200.0f;
        v_224.z = 100.0f;
        v_230.x = 0.0f;
        v_230.y = 0.0f;
        v_230.z = -5.0f * v_218->unk_450.unk_24C;
        sub_141320(&v_224, &v_224, &v_50);
        sub_141320(&v_230, &v_230, &v_50);
        v_218->vf_264(0xF0, &v_230, &v_224);
    }
    unk_4E5E50.sub_176180(4, 0, 1.0f, 0);
    if (!unk_42C->unk_4D0)
    {
        type_3DBC78 *v_234;
        type_140490 v_250;
        RwV3d v_25C;
        v_234 = (type_3DBC78 *)unk_42C->vf_200();
        v_250.x = 1.0f;
        v_250.y = 1.0f;
        v_250.z = 1.0f;
        v_250.w = 1.0f;
        v_25C.x = 1.0f;
        v_25C.y = 0.0f;
        v_25C.z = 0.0f;
        v_234->unk_90.sub_8F140(1, 0.1f, &v_25C, (type_8BEC0 *)&v_250, 0, 0);
    }
    if (sub_77B70(unk_448->unk_2C, (void **)(&v_264), (void **)(&v_260)))
    {
        if (!unk_42C->unk_4D0)
        {
            unk_42C->unk_284->sub_794C0(0.06666667f);
            unk_42C->unk_284->sub_796A0((RtAnimAnimation *)v_264, unk_448->unk_2C, 0, (struct type_783F0 *)v_260,
                                        0.0f, 1.0f, 1.0f);
            unk_10 = 0;
        }
        else
        {
            v_268 = ((type_783F0 *)v_260)->sub_78550(0.0f, -1);
            while (v_268)
            {
                if (v_268->unk_00 == 0x514)
                {
                    v_26C = &v_268->unk_08;
                    sub_F2FF0(v_26C[3], &v_50, 0, 1, 0, 1);
                }
                v_268 = ((type_783F0 *)v_260)->sub_785C0(v_268, -1);
            }
        }
    }
    return true;
}

// match: ?vf_004@type_3DA510@@UAE_NPAUtype_10F710@@PAURpClump@@HH@Z @ 0x0011C4C0
// sp-match: ?vf_004@type_3DA510@@UAE_NPAUtype_10F710@@PAURpClump@@HH@Z @ 0x000D2FD0
// The third kind (3): as the mounted kind's.
bool type_3DA510::vf_004(type_10F710 *arg_0, RpClump *arg_4, RwInt32 arg_8, RwInt32 arg_C)
{
    type_495F0 *var_4;
    RpClump *local_8;

    type_10F710_1A48::vf_004(arg_0, arg_4, arg_8, arg_C);
    unk_45C = 3;
    var_4 = (type_495F0 *)sub_198800(&unk_448->unk_00);
    if (arg_C)
    {
        local_8 = (RpClump *)var_4->sub_18F800(&var_4->unk_38);
        RWS::ClumpHelper::SetCanCollide(*local_8, 0);
    }
    return 1;
}

// Fires once its recoil time (unk_220) reaches the settings' rate (unk_BC);
// false before. With nothing loaded when rounds count (unk_CC) and no
// infinite ammunition (dword_4C19AC) it only plays the empty sound and
// sets unk_48. Otherwise, as the mounted kind's fire, from the bone 0x2B73
// moved by the settings' offset (unk_168) towards 1000 along the blended
// view: a round taken, the projectile's record (unk_30C, table 4) filled,
// fired as kind 0x1002 for a player of kind 2, else 0x1001; the settings'
// particle system (unk_4DC) spawned upright at the muzzle and handed to the
// projectile (with the flame callback sub_119BA0, pushed along the aim at
// 10), the player's camera shaken, its animation played, and the rounds
// display updated.
// match: ?vf_018@type_3DA510@@UAE_NXZ @ 0x0011C540
// sp-match: ?vf_018@type_3DA510@@UAE_NXZ @ 0x000D3030
bool type_3DA510::vf_018()
{
    if (unk_220 < unk_448->unk_BC)
        return false;
    memset(&unk_30C, 0, sizeof(type_439A48));
    unk_220 = 0.0f;
    if (unk_414 || !unk_448->unk_CC || dword_4C19AC)
    {
        RpHAnimHierarchy *v_8;
        RwMatrix *v_C;
        RwInt32 v_10;
        RwMatrix *v_14;
        RwMatrix v_60;
        RwV3d v_6C;
        RwMatrix *v_70;
        RwReal v_74;
        RwLine v_8C;
        RwInt32 v_90;
        type_4E5D30 *v_94;
        type_91F40 v_CC;
        RwV3d v_D8;
        RwReal v_DC;
        RwMatrix v_120;
        RwMatrix v_160;
        RwMatrix v_1A0;
        RtSlerp *v_1A4;
        RwMatrix v_1F0;
        RwV3d v_1FC;
        RwV3d v_208;
        type_495F0 *v_20C;
        RwInt32 v_21C;
        type_3DC858 *v_220;
        type_F2FF0 *v_224;
        type_3DD948 *v_234;
        RwInt32 v_238;
        RwInt32 v_23C;

        v_8 = unk_42C->unk_284->unk_18;
        v_C = RpHAnimHierarchyGetMatrixArray(v_8);
        unk_48 = unk_448->unk_D4;
        v_10 = RpHAnimIDGetIndex(v_8, 0x2B73);
        v_14 = &v_C[v_10];
        v_60 = *v_14;
        sub_141320(&v_6C, &unk_448->unk_168, v_14);
        RwMatrixTranslate(&v_60, &v_6C, rwCOMBINEPOSTCONCAT);
        v_70 = RwFrameGetMatrix(RwCameraGetFrame((RwCamera *)dword_4E5C74));
#ifdef CODFH_SP
        // shape: the reach scaled by a literal 3, last (SP 0xD3153: fld [+0x488]; fmul 3.0)
        v_74 = unk_448->unk_488_f * 3.0f + flt_3CD8E0;
        v_8C.start = v_70->pos;
        v_8C.end.x = v_70->at.x * unk_448->unk_488_f * 3.0f + v_8C.start.x;
        v_8C.end.y = v_70->at.y * unk_448->unk_488_f * 3.0f + v_8C.start.y;
        v_8C.end.z = v_70->at.z * unk_448->unk_488_f * 3.0f + v_8C.start.z;
#else
        v_74 = (RwDouble)unk_448->unk_488_f * flt_3D7118 + flt_3CD8E0;
        v_8C.start = v_70->pos;
        v_8C.end.x = v_70->at.x * unk_448->unk_488_f * flt_3D7118 + v_8C.start.x;
        v_8C.end.y = v_70->at.y * unk_448->unk_488_f * flt_3D7118 + v_8C.start.y;
        v_8C.end.z = v_70->at.z * unk_448->unk_488_f * flt_3D7118 + v_8C.start.z;
#endif
        for (v_90 = 0; v_90 < 4; v_90++)
        {
            v_94 = &dword_4E5D30[v_90];
            if (v_94->get_unk_00() && v_94->get_unk_28()
                && sub_91F40(v_94->get_unk_28(), &v_8C, &v_CC, 1, 0x590000, 1)) // not an address: line-test flags
            {
                RwV3dSubMacro(&v_D8, &v_CC.unk_08, &v_70->pos);
                if (RwV3dLength((RwV3d *)&v_D8) < v_74)
                    v_74 = RwV3dLength((RwV3d *)&v_D8);
            }
        }
        v_DC = 1.0f;
        if (v_74 >= unk_448->unk_48C_f && v_74 <= unk_448->unk_488_f)
        {
            v_120 = *v_70;
            sub_141690(&v_160, 0);
            v_1A0 = v_160;
            v_1A4 = RtSlerpCreate(0);
            RtSlerpInitialize(v_1A4, &v_120, &v_1A0);
            v_DC = 1.0f - (v_74 - unk_448->unk_48C_f) / (unk_448->unk_488_f - unk_448->unk_48C_f);
            RtSlerpGetMatrix(v_1A4, &v_1F0, v_DC);
            RtSlerpDestroy(v_1A4);
        }
        else
            v_1F0 = *v_70;
        v_14 = &v_1F0;
        v_1FC = v_14->pos;
        RwV3dIncrementScaledMacro(&v_1FC, &v_14->at, 1000.0f);
        RwV3dSubMacro(&v_208, &v_1FC, &v_60.pos);
        RwV3dNormalize(&v_208, &v_208);
        RwV3dScaleMacro(&v_208, &v_208, unk_448->unk_B8_f);
        if (unk_448->unk_CC && !dword_4C19AC)
            unk_414--;
        v_20C = (type_495F0 *)sub_198800(&unk_448->unk_00);
        ((type_439A48 *)&unk_30C)->unk_00 = 4;
#ifdef CODFH_SP // single player scales the damage by the difficulty (SP 0xD3420)
        ((type_439A48 *)&unk_30C)->unk_04 = (RwUInt32)unk_448->unk_C4 * difficulty_4F286C();
#else
        ((type_439A48 *)&unk_30C)->unk_04 = (RwUInt32)unk_448->unk_C4 * 1.0f;
#endif
        ((type_439A48 *)&unk_30C)->unk_38 = v_20C->sub_18F800(&v_20C->unk_38);
        ((type_439A48 *)&unk_30C)->unk_3C = 1;
        ((type_439A48 *)&unk_30C)->unk_40 = unk_448->unk_C0_f;
        ((type_439A48 *)&unk_30C)->unk_44 = unk_448->unk_194_f;
        ((type_439A48 *)&unk_30C)->unk_48 = unk_448->unk_198_f;
        ((type_439A48 *)&unk_30C)->unk_4C = unk_448->unk_D0;
        ((type_439A48 *)&unk_30C)->unk_50 = unk_448->unk_4B4;
        ((type_439A48 *)&unk_30C)->unk_54 = unk_448->unk_4B8_f;
        ((type_439A48 *)&unk_30C)->unk_58 = unk_448->unk_4BC;
        ((type_439A48 *)&unk_30C)->unk_5C = unk_448->unk_4C0;
        ((type_439A48 *)&unk_30C)->unk_60 = unk_448->unk_4C4_f;
        ((type_439A48 *)&unk_30C)->unk_64 = unk_448->unk_4C8_f;
        ((type_439A48 *)&unk_30C)->unk_68 = unk_448->unk_4CC;
        ((type_439A48 *)&unk_30C)->unk_70 = unk_448->unk_98_f;
        ((type_439A48 *)&unk_30C)->unk_6C = unk_448->unk_9C;
        ((type_439A48 *)&unk_30C)->unk_78 = unk_448->unk_A0_f;
        ((type_439A48 *)&unk_30C)->unk_74 = unk_448->unk_A4_f;
        ((type_439A48 *)&unk_30C)->unk_7C = unk_448->unk_A8;
        ((type_439A48 *)&unk_30C)->unk_80 = unk_448->unk_AC_f;
        if ((unk_42C->unk_2C & 7) == 2)
            v_21C = 0x1002;
        else
            v_21C = 0x1001;
        v_220 = (type_3DC858 *)sub_15F2C0(v_21C, (RwInt32)unk_42C, &v_60, &v_208, unk_42C->vf_138(),
                                          (type_439A48 *)&unk_30C, 0);
        v_60.at.x = 0.0f;
        v_60.at.y = 0.0f;
        v_60.at.z = 1.0f;
        v_60.up.x = 0.0f;
        v_60.up.y = 1.0f;
        v_60.up.z = 0.0f;
        v_60.right.x = 1.0f;
        v_60.right.y = 0.0f;
        v_60.right.z = 0.0f;
        v_224 = (type_F2FF0 *)sub_F2FF0(unk_448->unk_4DC, &v_60, 0, 0, false, true);
        v_220->unk_70.sub_F2880(v_224);
        if (v_224)
        {
            RwV3d v_230;
            v_224->unk_154 = sub_119BA0;
            RwV3dScaleMacro(&v_230, &v_208, 10.0f);
            sub_19E9B0((type_19E9B0 *)&v_224->unk_60, &v_230);
        }
        v_234 = (type_3DD948 *)unk_42C->unk_2110.sub_D4910();
        v_234->sub_175E50(6.0f, 8.0f, 5.0f);
        if (sub_77B70(unk_448->unk_2C, (void **)(&v_23C), (void **)(&v_238)))
        {
            unk_42C->unk_284->sub_794C0(0.06666667f);
            unk_42C->unk_284->sub_796A0((RtAnimAnimation *)v_23C, unk_448->unk_2C, 0, (struct type_783F0 *)v_238,
                                        0.0f, 1.0f, 1.0f);
            unk_10 = 0;
            unk_45 = 1;
        }
        unk_42C->sub_108B60();
        return true;
    }
    unk_48 = 1;
    unk_42C->unk_1C0.sub_8A980(&dword_4B1F4C, unk_42C, 0, (RwV3d *)unk_42C->vf_0C4(), 1, 0);
    return false;
}

// Both sides (arg_0 & arg_4), through an inline with no address: the melee
// strike computes the hit entity's side (the second argument) first.
inline RwInt32 and_sides(RwInt32 arg_0, RwInt32 arg_4)
{
    return arg_0 & arg_4;
}

// match: ?sub_11CF50@type_10F710_1A48@@QAEXPAUtype_10F710@@@Z @ 0x0011CF50
// sp-match: ?sub_11CF50@type_10F710_1A48@@QAEXPAUtype_10F710@@@Z @ 0x000D3720
void type_10F710_1A48::sub_11CF50(type_10F710 *arg_0)
{
    type_75600 frm_124;
    type_4E5D30 *local_f4;
    RwReal local_f0;
    RwV3d var_ec;
    RpIntersection frm_24;
    RwInt32 bp_8;
    RwInt32 bp_4;

#ifndef CODFH_SP // MP 0x11CF50 only: single player (SP 0xD3720) has no unk_217C
    if (arg_0->unk_217C)
    {
        return;
    }
#endif
    var_ec.x = unk_448->unk_E0;
    var_ec.y = 50.0f;
    var_ec.z = unk_448->unk_E0;
    bp_4 = 0;
    type_93DF0 var_e0;
    frm_24.type = rpINTERSECTSPHERE;
    frm_24.t.sphere.center = *RwMatrixGetPos(RwFrameGetLTM(arg_0->get_unk_340()));
    frm_24.t.sphere.center.y -= 50.0f;
    frm_24.t.sphere.radius = var_ec.x;
    local_f0 = frm_24.t.sphere.radius * frm_24.t.sphere.radius;
    var_e0.unk_6C = 0;
    var_e0.unk_24 = local_f0;
    var_e0.unk_20 = 0;
    var_e0.unk_18 = 0;
    var_e0.unk_04 = arg_0;
    var_e0.unk_14 = arg_0->get_unk_340();
    var_e0.unk_0C = 0;
    var_e0.unk_08 = 0;
    var_e0.unk_60 = 0;
    var_e0.unk_64 = 0;
    var_e0.unk_7C = 0;
    var_e0.unk_28 = 0.0f;
    var_e0.unk_48 = arg_0->unk_50_r;
    var_e0.unk_50 = &bp_4;
    var_e0.unk_58 = 0;
    var_e0.unk_54 = 0;
    var_e0.unk_70 = sub_8F940();
    bp_8 = 0;
    for (bp_8 = 0; bp_8 < 4; bp_8++)
    {
        local_f4 = &dword_4E5D30[bp_8];
        if (local_f4->get_unk_00() && local_f4->get_unk_28())
        {
            RpWorldForAllAtomicIntersections(local_f4->get_unk_28(), &frm_24, sub_104D00, &var_e0);
        }
    }
    if (var_e0.unk_28 != 0.0f && var_e0.unk_08)
    {
#ifndef CODFH_SP // single player has no team test here (SP 0xD3720)
        if (get_4FB9F8() || !(get_unk_2C_side(var_e0.unk_08) == (unk_42C->unk_2C & 7)))
#endif
        {
            memset(&frm_124, 0, sizeof(type_75600));
            frm_124.unk_00_w = 0;
            frm_124.unk_02_w = 1;
            if ((unk_42C->unk_2C & 7) == 2)
            {
                frm_124.unk_08 = 0x202;
            }
            else
            {
                frm_124.unk_08 = 0x201;
            }
            frm_124.unk_14 = 0;
            frm_124.unk_18 = 0;
            if ((var_e0.unk_08->vf_008() || var_e0.unk_08->vf_024())
                && and_sides(arg_0->unk_2C & 7, var_e0.unk_08->unk_2C & 7))
            {
                frm_124.unk_28 = 0.0f;
                frm_124.unk_2C = 0.0f;
            }
            else
            {
                frm_124.unk_28 = unk_448->unk_DC_f;
                frm_124.unk_2C = unk_448->unk_DC_f;
            }
            frm_124.unk_0C = arg_0;
            frm_124.unk_10 = arg_0->unk_2C;
            frm_124.unk_24 = var_e0.unk_08->vf_07C(2, &frm_24, 0, 0);
            var_e0.unk_08->vf_064(&frm_124);
            var_e0.unk_08->unk_1C0.sub_8A980(&dword_4AF030, (type_3D3548 *)this, 0, var_e0.unk_08->sub_CD550(), 0,
                                             0);
        }
    }
}

// match: ?vf_038@type_10F710_1A48@@UAEHXZ @ 0x0011D330
// sp-match: ?vf_038@type_10F710_1A48@@UAEHXZ @ 0x0006CEB0
RwInt32 type_10F710_1A48::vf_038()
{
    RwInt32 var_4;

    var_4 = 0;
    return 0;
}

// match: ?vf_034@type_10F710_1A48@@UAEXXZ @ 0x0011D350
// sp-match: ?vf_034@type_10F710_1A48@@UAEXXZ @ 0x000D39B0
// Takes its stance poses from its model: each of the tagged matrices ST01
// and ST02 (standing), CR01 and CR02 (crouched), PR01 and PR02 (prone),
// relative to the tagged POT matrix, as a rotation (unk_170, unk_1A0) and an
// offset (unk_1D0, unk_1F4) by stance.
void type_10F710_1A48::vf_034()
{
    RpClump *var_8;
    type_EC1F0 *var_C;
    RwMatrix var_50;
    RwMatrix var_90;

    var_8 = unk_420.get_unk_08();
    var_C = sub_EC1F0(var_8, 0x544F5000); // not an address: the tag 'POT'
    var_50 = var_C->unk_10;
    var_C = sub_EC1F0(var_8, 0x53543031); // not an address: the tag 'ST01'
    RwMatrixInvert(&var_90, &var_C->unk_10);
    RwMatrixTransform(&var_90, &var_50, rwCOMBINEPRECONCAT);
    RtQuatConvertFromMatrix(&unk_170[0], &var_90);
    unk_1D0[0] = var_90.pos;
    var_C = sub_EC1F0(var_8, 0x53543032); // not an address: the tag 'ST02'
    RwMatrixInvert(&var_90, &var_C->unk_10);
    RwMatrixTransform(&var_90, &var_50, rwCOMBINEPRECONCAT);
    RtQuatConvertFromMatrix(&unk_1A0[0], &var_90);
    unk_1F4[0] = var_90.pos;
    var_C = sub_EC1F0(var_8, 0x43523031); // not an address: the tag 'CR01'
    RwMatrixInvert(&var_90, &var_C->unk_10);
    RwMatrixTransform(&var_90, &var_50, rwCOMBINEPRECONCAT);
    RtQuatConvertFromMatrix(&unk_170[1], &var_90);
    unk_1D0[1] = var_90.pos;
    var_C = sub_EC1F0(var_8, 0x43523032); // not an address: the tag 'CR02'
    RwMatrixInvert(&var_90, &var_C->unk_10);
    RwMatrixTransform(&var_90, &var_50, rwCOMBINEPRECONCAT);
    RtQuatConvertFromMatrix(&unk_1A0[1], &var_90);
    unk_1F4[1] = var_90.pos;
    var_C = sub_EC1F0(var_8, 0x50523031); // not an address: the tag 'PR01'
    RwMatrixInvert(&var_90, &var_C->unk_10);
    RwMatrixTransform(&var_90, &var_50, rwCOMBINEPRECONCAT);
    RtQuatConvertFromMatrix(&unk_170[2], &var_90);
    unk_1D0[2] = var_90.pos;
    var_C = sub_EC1F0(var_8, 0x50523032); // not an address: the tag 'PR02'
    RwMatrixInvert(&var_90, &var_C->unk_10);
    RwMatrixTransform(&var_90, &var_50, rwCOMBINEPRECONCAT);
    RtQuatConvertFromMatrix(&unk_1A0[2], &var_90);
    unk_1F4[2] = var_90.pos;
}

// match: ?sub_11D650@type_10F710_1A48@@QAEXM@Z @ 0x0011D650
// sp-match: ?sub_11D650@type_10F710_1A48@@QAEXM@Z @ 0x000D3C10
void type_10F710_1A48::sub_11D650(RwReal arg_0)
{
    unk_18 = arg_0 * unk_448->unk_2B4_r[unk_42C->unk_1A04];
}

// match: ?sub_11D690@type_10F710_1A48@@QAEMXZ @ 0x0011D690
// sp-match: ?sub_11D690@type_10F710_1A48@@QAEMXZ @ 0x000D3C40
RwReal type_10F710_1A48::sub_11D690()
{
    if (unk_448 && unk_448->unk_2B4_r[unk_42C->unk_1A04] != 0.0f)
    {
        if (unk_448->unk_2B4_r[unk_42C->unk_1A04] != 0.0f)
        {
            return unk_18 / unk_448->unk_2B4_r[unk_42C->unk_1A04];
        }
        return unk_18;
    }
    return 0.0f;
}

// match: ?sub_11D740@type_10F710_1A48@@QAEX_N@Z @ 0x0011D740
// sp-match: ?sub_11D740@type_10F710_1A48@@QAEX_N@Z @ 0x000D3CA0
// Ends its recoil, carrying what is left of it into the stance's sway
// (unk_25C_a with arg_0, else unk_238_a).
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void type_10F710_1A48::sub_11D740(bool arg_0)
{
    RwReal var_4;
    RwReal local_8;

    var_4 = unk_1C;
    local_8 = unk_20;
    unk_20 = 0.0f;
    unk_1C = 0.0f;
    unk_18 = 0.0f;
    unk_40 = 0;
    unk_3C = 0;
    if (arg_0)
    {
        unk_25C_a[unk_42C->unk_1A04].x = local_8 + unk_25C_a[unk_42C->unk_1A04].x;
        unk_25C_a[unk_42C->unk_1A04].y = unk_25C_a[unk_42C->unk_1A04].y - var_4;
    }
    else
    {
        unk_238_a[unk_42C->unk_1A04].x = local_8 + unk_238_a[unk_42C->unk_1A04].x;
        unk_238_a[unk_42C->unk_1A04].y = unk_238_a[unk_42C->unk_1A04].y - var_4;
    }
}

// match: ?vf_03C@type_10F710_1A48@@UAEXPAUtype_10F710_1A48_save@@@Z @ 0x0011D890
// sp-match: ?vf_03C@type_10F710_1A48@@UAEXPAUtype_10F710_1A48_save@@@Z @ 0x000D3D40
// Saves its state into arg_0 (the checkpoint).
void type_10F710_1A48::vf_03C(type_10F710_1A48_save *arg_0)
{
    arg_0->unk_04 = unk_414;
    arg_0->unk_08 = unk_418;
    arg_0->unk_0D = unk_10;
    arg_0->unk_0E = unk_11;
    arg_0->unk_0F = unk_12;
    arg_0->unk_10 = unk_14;
    arg_0->unk_14 = unk_40;
    arg_0->unk_20 = unk_20;
    arg_0->unk_24 = unk_1C;
    arg_0->unk_28 = unk_44;
    arg_0->unk_30 = unk_220;
    arg_0->unk_0C = unk_41C;
    arg_0->unk_B8 = unk_228;
    arg_0->unk_BC = unk_230;
    memcpy(&arg_0->unk_C0, &unk_29C, sizeof(unk_29C));
    memcpy(&arg_0->unk_F8, &unk_30C, 0x84);
}

// match: ?vf_040@type_10F710_1A48@@UAEXPAUtype_10F710_1A48_save@@@Z @ 0x0011D9A0
// sp-match: ?vf_040@type_10F710_1A48@@UAEXPAUtype_10F710_1A48_save@@@Z @ 0x000D3DE0
// Restores it from arg_0.
void type_10F710_1A48::vf_040(type_10F710_1A48_save *arg_0)
{
    unk_414 = arg_0->unk_04;
    unk_418 = arg_0->unk_08;
    unk_10 = arg_0->unk_0D;
    unk_11 = arg_0->unk_0E;
    unk_12 = arg_0->unk_0F;
    unk_14 = arg_0->unk_10;
    unk_40 = arg_0->unk_14;
    unk_20 = arg_0->unk_20;
    unk_1C = arg_0->unk_24;
    unk_44 = arg_0->unk_28;
    unk_220 = arg_0->unk_30;
    unk_41C = arg_0->unk_0C;
    unk_228 = arg_0->unk_B8;
    unk_230 = arg_0->unk_BC;
    memcpy(&unk_29C, &arg_0->unk_C0, sizeof(unk_29C));
    memcpy(&unk_30C, &arg_0->unk_F8, 0x84);
}

// Members /OPT:ICF folded into shared trivial bodies (config/aliases.txt): defined here for
// the authentic link (PLAN M7); the placement link takes the shared bodies.

// ?vf_02C@type_10F710_1A48@@UAEXXZ (folded into the empty body at 0x1E41C0)
void type_10F710_1A48::vf_02C()
{
}
