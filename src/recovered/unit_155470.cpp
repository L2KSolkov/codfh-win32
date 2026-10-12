// The tank (type_3DC048, vtable off_3DC048) and the flak gun derived from it
// (type_3DC378, vtable off_3DC378), with the vehicle's bare constructor.

#include "rw/ostypes.h"
#include "rw/batypes.h"
#include "rw/bamatrix.h"
#include "game/functions.h"
#include "game/vecutil.h"
#include "types/type_3DBC78_450.h"
#include "types/type_3DF8D8.h"
#include "types/type_3DBC78.h"
#include "types/type_3DC048.h"
#include "types/type_3DC378.h"
#include "types/type_44350.h"
#include "types/type_3D32F8.h"
#include "types/type_10F710.h"
#include "game/clumpdata.h"
#include "types/animkey.h"
#include "types/animobjpool.h"
#include "rw/rtquat.h"
#include "rw/rphanim.h"
#include "game/gameloop.h"
#include "types/animbank.h"
#include "game/data.h"
#include "types/type_DC400.h"
#include <math.h>
#include "game/fade.h"
#include "types/CGlobalSounds.h"
#include "types/type_62A60.h"
#include "game/frand.h"
#include "types/type_4C19C0.h"
#include "types/type_15B110.h"
#include "rw/rtdict.h"
#include "rw/rpuvanim.h"
#include "types/type_141C10.h"
#include <string.h>
#include "rw/bavector.h"

// Its data definitions (PLAN M5), in the image's address order.
// 0x00429DE8
RwReal flt_429DE8 = 0.075f;
// 0x00429DEC
RwReal flt_429DEC = 0.6f;
// 0x00429DF0
RwReal flt_429DF0 = -80.0f;
// 0x00429DF4
RwReal flt_429DF4 = 60.0f;
// 0x00429DF8
RwReal dword_429DF8 = 0.2f;
// 0x00429DFC
RwReal dword_429DFC = -7.0f;
// 0x00429E00
RwReal dword_429E00 = 0.02f;
// 0x00429E04
RwReal dword_429E04 = 0.08f;
// 0x00429E08
RwReal flt_429E08 = 0.6f;
// 0x00429E0C
RwReal flt_429E0C = 10.0f;
// 0x00429E10
RwReal dword_429E10 = 0.005f;
// 0x00429E14
RwReal dword_429E14 = 0.5f;
// 0x00429E18
RwReal dword_429E18 = 0.08f;
// 0x00429E1C
RwReal dword_429E1C = 0.4f;
// 0x00429E20
RwReal flt_429E20 = 20.0f;
// 0x00429E24
RwReal flt_429E24 = 400.0f;
// 0x00429E28
RwReal flt_429E28 = 40.0f;
// 0x00429E2C
RwReal flt_429E2C = 0.1f;
// 0x00429E30
RwReal flt_429E30 = 1.0f;
// 0x00429E34
RwReal flt_429E34 = 1.0f;
// 0x00429E38
RwReal flt_429E38 = 5.0f;
// 0x00429E3C
RwReal flt_429E3C = 0.4f;
// 0x004D5160
RwInt32 dword_4D5160;
// End of its data definitions.


/* Local field accessors, not recovered symbols. Evidence: sub_155470
 * reads the trigger coordinates for its warning. Reference-returning
 * inlines retain those loads and its frame while allowing the bare vehicle
 * constructor expansion required by sub_15A8C0. */
static inline const RwReal & TriggerCoordinate90(const type_712B0 *trigger) { return trigger->unk_90; }
static inline const RwReal & TriggerCoordinate94(const type_712B0 *trigger) { return trigger->unk_94; }
static inline const RwReal & TriggerCoordinate98(const type_712B0 *trigger) { return trigger->unk_98; }

// Its data (PLAN M5): literals, constants and tables where the image has them.
// match: ??_7type_3DC048@@6B@ @ 0x003DC048
// match: __real@40333333 @ 0x003DC34C
// match: __real@43b3feb8 @ 0x003DC350
// match: ??_C@_0BD@BEMCMHG@SingleShotFinished?$AA@ @ 0x003DC354
// match: ??_C@_06GGDACGEK@turret?$AA@ @ 0x003DC368
// match: ??_C@_06HJJJFCDB@VTrack?$AA@ @ 0x003DC370
// match: ??_7type_3DC378@@6B@ @ 0x003DC378
// match: ??_C@_0BB@MDPLNIAE@AssumeGunnerRole?$AA@ @ 0x003DC67C
// match: ??_C@_0BB@JOCPJNHI@AssumeLoaderRole?$AA@ @ 0x003DC690
// match: ??_C@_0BA@BKFFGMDA@FlakGunDisabled?$AA@ @ 0x003DC6A4
// match: __ehhandler$?sub_14C820@@YAPAUtype_3DBC78@@PAUtype_712B0@@@Z>1>8 @ 0x0041DF2C
// match: __ehhandler$?sub_14C820@@YAPAUtype_3DBC78@@PAUtype_712B0@@@Z>1 @ 0x0041DF34
// match: __ehhandler$?sub_155470@@YAPAUtype_3DC048@@PAUtype_712B0@@@Z>1>8 @ 0x0041DE80
// match: __ehhandler$?sub_155470@@YAPAUtype_3DC048@@PAUtype_712B0@@@Z>1 @ 0x0041DE90
// match: __ehhandler$??0type_3DBC78@@QAE@XZ>1>8 @ 0x0041DEAC
// match: __ehhandler$??0type_3DBC78@@QAE@XZ>1 @ 0x0041DEEC
// match: __ehhandler$??1type_3DC048@@UAE@XZ>1>8 @ 0x0041DF08
// match: __ehhandler$??1type_3DC048@@UAE@XZ>1 @ 0x0041DF10
// match: __ehhandler$??0type_3DC378@@QAE@PAUtype_712B0@@@Z>1>8 @ 0x0041DF50
// match: __ehhandler$??0type_3DC378@@QAE@PAUtype_712B0@@@Z>1 @ 0x0041DF60
// match: __ehhandler$??1type_3DC378@@UAE@XZ>1>8 @ 0x0041DF7C
// match: __ehhandler$??1type_3DC378@@UAE@XZ>1 @ 0x0041DF94
// match: ?flt_429DE8@@3MA @ 0x00429DE8
// match: ?flt_429DEC@@3MA @ 0x00429DEC
// match: ?flt_429DF0@@3MA @ 0x00429DF0
// match: ?flt_429DF4@@3MA @ 0x00429DF4
// match: ?dword_429DF8@@3MA @ 0x00429DF8
// match: ?dword_429DFC@@3MA @ 0x00429DFC
// match: ?dword_429E00@@3MA @ 0x00429E00
// match: ?dword_429E04@@3MA @ 0x00429E04
// match: ?flt_429E08@@3MA @ 0x00429E08
// match: ?flt_429E0C@@3MA @ 0x00429E0C
// match: ?dword_429E10@@3MA @ 0x00429E10
// match: ?dword_429E14@@3MA @ 0x00429E14
// match: ?dword_429E18@@3MA @ 0x00429E18
// match: ?dword_429E1C@@3MA @ 0x00429E1C
// match: ?flt_429E20@@3MA @ 0x00429E20
// match: ?flt_429E24@@3MA @ 0x00429E24
// match: ?flt_429E28@@3MA @ 0x00429E28
// match: ?flt_429E2C@@3MA @ 0x00429E2C
// match: ?flt_429E30@@3MA @ 0x00429E30
// match: ?flt_429E34@@3MA @ 0x00429E34
// match: ?flt_429E38@@3MA @ 0x00429E38
// match: ?flt_429E3C@@3MA @ 0x00429E3C

// match: ?sub_155470@@YAPAUtype_3DC048@@PAUtype_712B0@@@Z @ 0x00155470
// match: __ehhandler$?sub_155470@@YAPAUtype_3DC048@@PAUtype_712B0@@@Z-0x19 @ 0x00301C10
// match: __ehhandler$?sub_155470@@YAPAUtype_3DC048@@PAUtype_712B0@@@Z @ 0x00301C29
// sp-match: ?sub_155470@@YAPAUtype_3DC048@@PAUtype_712B0@@@Z @ 0x000FF8C0
// (its constructor, defined in the class: single player calls its out-of-line copy)
// sp-match: ??0type_3DC048@@QAE@PAUtype_712B0@@@Z @ 0x000FF640

// Builds the tank for the trigger arg_0, or warns that there is no entity
// memory for it.
type_3DC048 *sub_155470(type_712B0 *arg_0)
{
    type_3DC048 *var_10;

    var_10 = (type_3DC048 *)sub_D56D0(0x29B0, arg_0->unk_24_18, arg_0->vf_008());
    if (var_10 != 0)
    {
        var_10 = new (var_10) type_3DC048(arg_0);
        if (var_10->unk_28 & 0x400000) // not an address: entity flag
        {
            sub_D5A60(var_10, 0);
            var_10 = 0;
        }
    }
#if defined(CODFH_SP) && !defined(CODFH_SP_LOGS) // single player compiles the debug print out (no warning; SP 0xFF8C0)
#else
    else
    {
        sub_19A750("WARNING: A spawn could not be created due to lack of entity memory. Trigger "
                   "location(%6.2f,%6.2f,%6.2f)",
                   TriggerCoordinate90(arg_0), TriggerCoordinate94(arg_0), TriggerCoordinate98(arg_0));
    }
#endif
    return var_10;
}

#ifdef CODFH_SP
// Single player compiles these trivial members here, with the constructor: its
// callers here keep edx across vf_2DC (SP 0xFE647, 0xFE6C7; the body is the shared
// `return 0`, SP 0x6CEB0) and drop the call to the empty vf_044 (SP 0xFDBA0).
void type_3DBC78::vf_044(RwReal arg_0)
{
}

RwInt32 type_3DBC78::vf_2DC()
{
    return 0;
}
#endif

// match: ??0type_3DBC78@@QAE@XZ @ 0x001555A0
// match: __ehhandler$??0type_3DBC78@@QAE@XZ-0x6A @ 0x00301C40
// match: __ehhandler$??0type_3DBC78@@QAE@XZ @ 0x00301CAA
// sp-match: ??0type_3DBC78@@QAE@XZ @ 0x000FF590
inline type_3DBC78::type_3DBC78()
{
}

// match: ?vf_2E8@type_3DC048@@UAEMXZ @ 0x001556B0
// sp-match: ?vf_2E8@type_3DC048@@UAEMXZ @ 0x000FEC40
RwReal type_3DC048::vf_2E8()
{
    return unk_2910;
}

// match: ?vf_2E0@type_3DC048@@UAEHXZ @ 0x001556D0
// sp-match: ?vf_2E0@type_3DC048@@UAEHXZ @ 0x000FEC50
RwInt32 type_3DC048::vf_2E0()
{
    return unk_290C;
}

// match: ??_Gtype_3DC048@@UAEPAXI@Z @ 0x001556F0
// sp-match: ??_Gtype_3DC048@@UAEPAXI@Z @ 0x000FEC60
// (Compiler-written: the destructor, then the class's plain operator delete.)

// match: ??1type_3DC048@@UAE@XZ @ 0x00155720
// match: __ehhandler$??1type_3DC048@@UAE@XZ-0x8 @ 0x00301CC0
// match: __ehhandler$??1type_3DC048@@UAE@XZ @ 0x00301CC8
// sp-match: ??1type_3DC048@@UAE@XZ @ 0x000FEC30
inline type_3DC048::~type_3DC048()
{
    vf_230();
}

// The vehicle factory (type_3DBC78's, though its code sits before unit_14C820's): the
// image has its EH handler between this object's destructor's and type_3DC378's
// constructor's, so it was compiled here.
// The trigger arg_0's position (its matrix's): a free inline with no
// address. Evidence: the vehicle factory's warning reads each coordinate
// through it, and its frame holds the leftovers of the three expansions.
inline RwV3d *trigger_pos(type_712B0 *arg_0)
{
    return &arg_0->unk_60_m.pos;
}

// match: ?sub_14C820@@YAPAUtype_3DBC78@@PAUtype_712B0@@@Z @ 0x0014C820
// match: __ehhandler$?sub_14C820@@YAPAUtype_3DBC78@@PAUtype_712B0@@@Z-0x11 @ 0x00301CE0
// match: __ehhandler$?sub_14C820@@YAPAUtype_3DBC78@@PAUtype_712B0@@@Z @ 0x00301CF1
// sp-match: ?sub_14C820@@YAPAUtype_3DBC78@@PAUtype_712B0@@@Z @ 0x000FF7C0
// Builds the vehicle for the trigger arg_0, or warns that there is no
// entity memory for it.
type_3DBC78 *sub_14C820(type_712B0 *arg_0)
{
    type_3DBC78 *var_10;

    var_10 = (type_3DBC78 *)sub_D56D0(0x2860, arg_0->unk_24_18, arg_0->vf_008());
    if (var_10 != 0)
    {
        var_10 = new (var_10) type_3DBC78(arg_0);
        if (var_10->unk_28 & 0x400000) // not an address: entity flag
        {
            sub_D5A60(var_10, 0);
            var_10 = 0;
        }
    }
#if defined(CODFH_SP) && !defined(CODFH_SP_LOGS) // single player compiles the debug print out (no warning; SP 0xFF7C0)
#else
    else
    {
        sub_19A750("WARNING: A spawn could not be created due to lack of entity memory. Trigger "
                   "location(%6.2f,%6.2f,%6.2f)",
                   trigger_pos(arg_0)->x, trigger_pos(arg_0)->y, trigger_pos(arg_0)->z);
    }
#endif
    return var_10;
}

// match: ?sub_155780@type_3DC048@@QAEHPAUtype_712B0@@@Z @ 0x00155780
// sp-match: ?sub_155780@type_3DC048@@QAEHPAUtype_712B0@@@Z @ 0x000FCCC0
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
RwInt32 type_3DC048::sub_155780(type_712B0 *arg_0)
{
    type_3DF8D8 *var_18;
    RwV3d var_14;
    type_712B0_3DBC78 *var8;
    RpHAnimHierarchy *l4;

    var8 = (type_712B0_3DBC78 *)arg_0;
    var_18 = sub_198800(&var8->unk_C0);
    unk_DD4 = ((type_14D2C0_10 *)var_18->unk_10)->get_unk_90();
    sub_14D2C0(arg_0);
    switch (((type_14D2C0_10 *)var_18->unk_10)->get_unk_8C())
    {
    case 0:
    case 2:
        unk_2C = 0x40002; // not an address: kind flags
        break;
    case 1:
    case 3:
    case 4:
        unk_2C = 0x40001; // not an address: kind flags
        break;
    }
    if (unk_11A0.get_unk_56C())
        unk_11A0.sub_17080();
    sub_3EE10(this);
    unk_2860 = 0;
    unk_2864 = 0;
    unk_286C = var8->unk_1A0;
    unk_2868 = 0.0f;
    unk_2870 = 0.0f;
    unk_2878 = 0.0f;
    unk_287C = 0.0f;
    unk_2874 = 0.0f;
    unk_2884 = 0.0f;
    unk_2888 = 0.0f;
    unk_2880 = 0.0f;
    unk_288C = var8->unk_1A8;
    unk_2898 = 0.0f;
    unk_2894 = 0.0f;
    unk_2890 = 0.0f;
    unk_28A4 = 0.0f;
    unk_28A0 = 0.0f;
    unk_289C = 0.0f;
    zero_v3d(&unk_28A8);
    zero_v3d(&unk_28B4);
    unk_28C0 = 0;
    unk_28C4 = dword_429DC8;
    unk_28C8 = 0;
    unk_28CC = dword_429DC8;
    unk_28D0 = 0;
    unk_28D4 = 0;
    unk_28D8 = 0;
    l4 = get_unk_284()->unk_18;
    unk_28DC = RpHAnimIDGetIndex(l4, 2);
    unk_28E0 = RpHAnimIDGetIndex(l4, 3);
    memset(unk_2918, 0, sizeof(unk_2918));
    unk_2918[0].unk_00 = RpHAnimIDGetIndex(l4, 4);
    unk_2918[1].unk_00 = RpHAnimIDGetIndex(l4, 6);
    unk_2918[2].unk_00 = RpHAnimIDGetIndex(l4, 7);
    if (sub_EC1F0(get_unk_264(), 0x41464952)) // not an address: a tag
        unk_DFC.unk_00[0].unk_38 = 0x41464952; // not an address: a tag
    else
        unk_DFC.unk_00[0].unk_38 = 0;
    if (sub_EC1F0(get_unk_264(), 0x42464952)) // not an address: a tag
        unk_DFC.unk_00[1].unk_38 = 0x42464952; // not an address: a tag
    else
        unk_DFC.unk_00[1].unk_38 = 0;
    if (sub_EC1F0(get_unk_264(), 0x43464952)) // not an address: a tag
        unk_DFC.unk_00[2].unk_38 = 0x43464952; // not an address: a tag
    else
        unk_DFC.unk_00[2].unk_38 = 0;
    unk_2990 = 0;
    unk_2994 = 0;
    unk_450.unk_29C = 0;
    unk_290C = 0;
    unk_2910 = -1.0f;
    unk_2914 = 1.0e37f;
    unk_2998 = 0;
    unk_29A0 = 0;
    unk_299C = 0;
    var_14.x = 1.0f;
    var_14.y = 0.0f;
    var_14.z = 1.0f;
    sub_153C40(&unk_28E4[0], unk_28DC, 6, 10, &var_14);
    var_14.x = 0.0f;
    var_14.y = 0.0f;
    var_14.z = 0.0f;
    var_14.y = 1.0f;
    sub_153C40(&unk_28E4[1], unk_28E0, 15, 40, &var_14);
    return 1;
}

// match: ?vf_054@type_3DC048@@UAEXH@Z @ 0x00155C40
// sp-match: ?vf_054@type_3DC048@@UAEXH@Z @ 0x000F9020
void type_3DC048::vf_054(RwInt32 arg_0)
{
    type_3DBC78::vf_054(arg_0);
}

// match: ?vf_110@type_3DC048@@UAEXPAURwV3d@@PAUtype_3D3548@@H@Z @ 0x00155C60
// sp-match: ?vf_110@type_3DC048@@UAEXPAURwV3d@@PAUtype_3D3548@@H@Z @ 0x000F9030
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void type_3DC048::vf_110(RwV3d *arg_0, type_3D3548 *arg_4, RwInt32 arg_8)
{
    RwMatrix *var_8;
    RpHAnimHierarchy *l4;

    if (unk_284 && unk_28_13)
    {
        l4 = get_unk_284()->unk_18;
        var_8 = RpHAnimHierarchyGetMatrixArray(l4);
        if (unk_28DC != -1)
            *arg_0 = var_8[unk_28DC].pos;
        else
            type_3DBC78::vf_110(arg_0, arg_4, arg_8);
    }
    else
    {
        *arg_0 = *sub_CD550();
        arg_0->y += 75.0f;
    }
}

// match: ?sub_155D30@@YAXPAUtype_7C8D0@@PAUtype_80300@@H_N@Z @ 0x00155D30
// sp-match: ?sub_155D30@@YAXPAUtype_7C8D0@@PAUtype_80300@@H_N@Z @ 0x000FCFA0
void sub_155D30(type_7C8D0 *arg_0, type_80300 *arg_4, RwInt32 arg_8, bool arg_C)
{
    type_3DC048 *var_4;
    type_7CBD0 *var_8;
    RwFrame *var_10;
    RpHAnimHierarchy *var_18;
    RwMatrix *var_1C;
    RtQuat *var_2C;
    type_7CBD0_hdr *var_30;
    type_7CBD0_t *var_34;
    RwMatrix var_80;
    RwInt32 var_84;
    RwMatrix var_D0;
    RwInt32 var_D4;
    RtQuat *var_D8;
    RpHAnimHierarchy *var_E4;
    RtQuat *var_E8;
    RtQuat *var_EC;
    RwV3d var_FC;
    RwV3d var_108;
    RtQuat *var_10C;
    RwV3d var_118;
    RwReal var_120;
    type_153C40 *var_124;

    var_4 = (type_3DC048 *)arg_8;
    var_8 = (type_7CBD0 *)arg_4->unk_144;
    if (arg_C && !var_4->unk_DB8)
    {
        var_10 = var_4->get_unk_340();
        var_18 = var_4->get_unk_284()->unk_18;
        var_1C = RpHAnimHierarchyGetMatrixArray(var_18);
        var_4->unk_DBC = var_18->numNodes * (sizeof(RtQuat) + sizeof(RwV3d)) + sizeof(type_7CBD0_hdr);
        var_4->unk_DB8 = (type_7CBD0_hdr *)RwMalloc(var_4->unk_DBC, 0x34251); // not an address: a memory hint
        memset(var_4->unk_DB8, 0, var_4->unk_DBC);
        var_4->unk_DB8->unk_00 = var_18->numNodes;
        var_4->unk_DB8->unk_01 = var_18->numNodes;
        var_4->unk_DB8->unk_02 = 1;
        var_4->unk_DB8->unk_08 = (RwUInt64)-1;
        var_4->unk_DB8->unk_10 = var_4->unk_D9C > -1 ? (RwUInt64)(1 << var_4->unk_D9C) : 0;
        sub_807C0((RtAnimInterpolator *)arg_4, var_4->unk_DB8);
        var_2C = var_8->unk_10;
        var_30 = var_4->unk_DB8;
        var_34 = (type_7CBD0_t *)&var_8->unk_10[var_30->unk_00];
        RwMatrixInvert(&var_80, RwFrameGetLTM(var_10));
        for (var_84 = 0; var_84 < var_18->numNodes; var_84++)
        {
            var_D0 = var_80;
            var_D4 = RpHAnimIDGetIndex(var_18, var_18->pNodeInfo[var_84].nodeID);
            RwMatrixTransform(&var_D0, &var_1C[var_D4], rwCOMBINEPRECONCAT);
            RtQuatConvertFromMatrix(&var_2C[var_84], &var_D0);
        }
        for (var_84 = 0; var_84 < var_4->unk_DB8->unk_02; var_84++)
        {
            var_34[var_84].unk_00.z = 0.0f;
            var_34[var_84].unk_00.y = 0.0f;
            var_34[var_84].unk_00.x = 0.0f;
        }
        var_D8 = (RtQuat *)(var_4->unk_DB8 + 1);
        memcpy(var_D8, var_2C, var_18->numNodes * sizeof(RtQuat));
        var_8->unk_04 = var_4->unk_DB8;
        var_8->unk_08 = sub_EC270(var_4->get_unk_264());
        for (var_84 = 0; var_84 < 3; var_84++)
            memcpy(&var_4->unk_2918[var_84].unk_18, &var_2C[var_4->unk_2918[var_84].unk_00], sizeof(RtQuat));
    }
    else if (arg_C && var_4->unk_DB8)
    {
        var_E4 = var_4->get_unk_284()->unk_18;
        var_E8 = (RtQuat *)(var_4->unk_DB8 + 1);
        var_EC = var_8->unk_10;
        memcpy(var_EC, var_E8, var_E4->numNodes * sizeof(RtQuat));
        sub_807C0((RtAnimInterpolator *)arg_4, var_4->unk_DB8);
        var_8->unk_04 = var_4->unk_DB8;
        var_8->unk_08 = sub_EC270(var_4->get_unk_264());
    }
    else
    {
        var_FC.x = 0.0f;
        var_FC.y = 1.0f;
        var_FC.z = 0.0f;
        var_108.x = 1.0f;
        var_108.y = 0.0f;
        var_108.z = 0.0f;
        sub_150350(arg_0, arg_4, arg_8, arg_C);
        if (var_4->unk_28DC != -1 && var_4->unk_28E0 != -1)
        {
            var_4->sub_17FC00(var_8, var_4->unk_28DC, 0, &var_FC, var_4->unk_2868, 1);
            var_4->sub_17FC00(var_8, var_4->unk_28E0, 0, &var_108, var_4->unk_2870, 1);
        }
        for (var_84 = 0; var_84 < 3; var_84++)
        {
            var_10C = var_8->unk_10;
            memcpy(&var_10C[var_4->unk_2918[var_84].unk_00], &var_4->unk_2918[var_84].unk_18, sizeof(RtQuat));
            if (var_4->unk_2918[var_84].unk_10 != 0.0f && var_4->unk_2918[var_84].unk_14 != 0.0f)
            {
                var_118.x = 0.0f;
                var_118.y = 0.0f;
                var_118.z = 0.0f;
                switch (var_4->unk_2918[var_84].unk_0C)
                {
                case 0:
                    var_118.x = -1.0f;
                    break;
                case 1:
                    var_118.y = -1.0f;
                    break;
                case 2:
                    var_118.z = -1.0f;
                    break;
                case 3:
                    var_118.x = 1.0f;
                    break;
                case 4:
                    var_118.y = 1.0f;
                    break;
                case 5:
                    var_118.z = 1.0f;
                    break;
                }
                var_120 = (var_4->unk_2918[var_84].unk_10 / var_4->unk_2918[var_84].unk_14) *
                          var_4->unk_2918[var_84].unk_08;
                var_4->sub_17FC00(var_8, var_4->unk_2918[var_84].unk_00, 0, &var_118, var_120, 0);
            }
        }
        if (var_4->unk_28_9)
        {
            if (var_4->vf_184() == -1)
            {
                var_4->unk_2860 = 0;
                var_4->unk_2864 = 0;
                var_4->unk_2878 = 0.0f;
                var_4->unk_287C = 0.0f;
                var_4->unk_2874 = 0.0f;
                var_4->unk_2884 = 0.0f;
                var_4->unk_2888 = 0.0f;
                var_4->unk_2880 = 0.0f;
                var_124 = var_4->unk_28E4;
                for (var_84 = 0; var_84 < 2; var_84++)
                {
                    if (var_124->unk_00 == -1)
                        break;
                }
                if (var_84 == 2)
                {
                    for (var_84 = 0; var_84 < 2; var_84++)
                    {
                        if (var_124->unk_00 >= 0)
                            var_4->sub_17FC00(var_8, var_124->unk_00, 0, &var_124->unk_08, var_124->unk_04, 0);
                        var_124++;
                    }
                }
            }
        }
    }
}

// match: ?vf_038@type_3DC048@@UAEXM@Z @ 0x00156580
// sp-match: ?vf_038@type_3DC048@@UAEXM@Z @ 0x000FD4E0
void type_3DC048::vf_038(RwReal arg_0)
{
    RwInt32 var_4;

    if (!unk_DB4)
    {
        get_unk_284()->sub_794C0(0);
        unk_DB4 = get_unk_284()->sub_79930(sub_155D30, 1.0f, 1.0f);
#ifdef CODFH_SP // SP expands type_78AC0::sub_6DF40 here, over its 4-entry ring (SP 0xFD4E0: % 4)
        {
            type_7C8D0 *var_284 = get_unk_284();
            RwInt32 i = (var_284->unk_20 + var_284->unk_24 - 1) % type_7C8D0_ring_size;
            var_284->unk_34[i].unk_08_30 = 0;
        }
#else
        ((type_78AC0 *)get_unk_284())->sub_6DF40();
        unused_slot();
#endif
    }
    for (var_4 = 0; var_4 < 3; var_4++)
    {
        if (unk_2918[var_4].unk_04 && unk_2918[var_4].unk_10 != unk_2918[var_4].unk_14)
        {
            unk_2918[var_4].unk_10 += arg_0 / 30.0f;
            if (unk_2918[var_4].unk_10 > unk_2918[var_4].unk_14)
                unk_2918[var_4].unk_10 = unk_2918[var_4].unk_14;
        }
        else if (!unk_2918[var_4].unk_04 && unk_2918[var_4].unk_10 != 0.0f)
        {
            unk_2918[var_4].unk_10 -= arg_0 / 30.0f;
            if (unk_2918[var_4].unk_10 < 0.0f)
                unk_2918[var_4].unk_10 = 0.0f;
        }
    }
    unk_11A0.sub_17190(arg_0);
}

// match: ?vf_03C@type_3DC048@@UAEXM@Z @ 0x00156770
// sp-match: ?vf_03C@type_3DC048@@UAEXM@Z @ 0x000FEDD0
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void type_3DC048::vf_03C(RwReal arg_0)
{
    RwReal stk_64;
    RwReal var_60;
    RwReal var_5C;
    RwReal bp_58;
    RwReal p54;
    RwReal var_50;
    RwReal m_4C;
    RwReal local_48;
    RwReal local_44;
    RwReal local_40;
    RwReal p3C;
    RwReal var_38;
    RwReal l34;
    RwReal var30;
    RwReal ebp_2C;
    RwReal lcl_28;
    RwReal frm_24;
    RwReal var_20;
    RwReal l1C;
    RwReal m_18;
    RwReal ebp_14;
    RwReal lv_10;
    RwInt32 var_C;
    type_10F710 *bp_8;
    type_712B0_3DBC78 *bp_4;

    type_3DBC78::vf_03C(arg_0);
    sub_15A160();
    if (unk_DFC.unk_300 >= 0)
        vf_2A8(unk_DFC.unk_300, 0, 0);
    bp_8 = (type_10F710 *)sub_1745A0(0);
    bp_4 = (type_712B0_3DBC78 *)get_unk_34C();
    var_C = bp_8 == unk_118C.sub_D4910();
    if (var_C && !bp_8->unk_4D0)
    {
        lv_10 = unk_4B9308.sub_EE8F0(bp_8->unk_3D8, 6);
        if ((dword_4B86F8 >> 6) & 1)
            lv_10 = 0.0f;
        if (lv_10 != 0.0f)
            bp_8->unk_4E0 = dword_429DF8;
        else
            bp_8->unk_4E0 = bp_8->unk_4EC;
        m_18 = bp_8->unk_4E0 - bp_8->unk_4E4;
        if (m_18 != 0.0f)
        {
            frm_24 = 3.0f;
            var_20 = 2.0f;
#ifdef CODFH_SP // shape:
            l1C = flt_3DBC58 * deltaTime / 1000.0f;
#else
            l1C = deltaTime * flt_3DBC58 / 1000.0f;
#endif
            ebp_14 = sub_141700(&bp_8->unk_4E8, m_18, 0.0f, var_20, frm_24, frm_24, l1C, 0);
            bp_8->unk_4E4 += ebp_14;
            bp_8->unk_534 = bp_8->unk_4E4;
        }
    }
    if (var_C && bp_8->unk_4D0 == 1)
    {
        lcl_28 = 1.2f;
        var30 = 0.85f;
#ifdef CODFH_SP // shape:
        ebp_2C = fabs(unk_2874) + fabs(unk_2880);
#else
        ebp_2C = (RwReal)fabs((RwDouble)unk_2874) + (RwReal)fabs((RwDouble)unk_2880);
#endif
        if (ebp_2C > 0.95f)
#ifdef CODFH_SP // shape:
            bp_8->unk_4DC += flt_3DBC58 * deltaTime / 1000.0f;
#else
            bp_8->unk_4DC += deltaTime * flt_3DBC58 / 1000.0f;
#endif
        else
            bp_8->unk_4DC = 0.0f;
        if (bp_8->unk_4DC > 0.3f)
        {
            var_38 = (l34 = bp_8->unk_4DC - 0.3f) / 1.5f;
            var_38 = 1.0f > var_38 ? var_38 : 1.0f;
            lcl_28 += 2.8f * var_38;
            var30 += 1.0f * var_38;
        }
        if (bp_8->unk_1B04)
        {
            p3C = 0.7f;
            lcl_28 = lcl_28 * p3C;
            var30 = var30 * p3C;
        }
        sub_112DA0(&unk_2898, unk_2874, &unk_2894, flt_429DE8, flt_429DEC, 1000.0f, arg_0);
#ifdef CODFH_SP // shape:
        unk_2890 += unk_2898 * (lcl_28 * (bp_4->unk_19C_f * (arg_0 / 60.0f)));
#else
        unk_2890 += lcl_28 * bp_4->unk_19C_f * (arg_0 / 60.0f) * unk_2898;
#endif
        if (unk_2890 < 0.0f)
            unk_2890 = 360.0f + unk_2890;
        if (unk_2890 > 360.0f)
            unk_2890 = unk_2890 - 360.0f;
        sub_112DA0(&unk_28A4, unk_2880, &unk_28A0, flt_429DE8, flt_429DEC, 1000.0f, arg_0);
#ifdef CODFH_SP // shape:
        unk_289C += unk_28A4 * (var30 * (bp_4->unk_19C_f * (arg_0 / 60.0f)));
#else
        unk_289C += var30 * bp_4->unk_19C_f * (arg_0 / 60.0f) * unk_28A4;
#endif
        unk_289C = sub_22C20(unk_289C, flt_429DF0, flt_429DF4);
        unk_2874 = 0.0f;
        unk_2880 = 0.0f;
    }
    if (unk_2998)
    {
        sub_156FC0();
    }
    else
    {
        local_40 = 1.0f;
        if (var_C && (RwReal)fabs((RwDouble)(bp_8->unk_4E4 - bp_8->unk_4EC)) > 0.1f)
        {
            local_44 = bp_8->unk_4E4 - bp_8->unk_4EC;
            local_44 = local_44 / (dword_429DF8 - bp_8->unk_4EC);
            local_48 = 0.7f;
            local_40 -= local_48 * local_44;
        }
        if (var_C && bp_8->unk_4D0 > 0)
        {
            sub_112DA0(&unk_2884, unk_2880, &unk_2888, flt_429DE8, flt_429DEC, 1000.0f, arg_0);
        }
        else
        {
            unk_2884 = unk_2880;
            unk_2888 = 0.0f;
        }
#ifdef CODFH_SP // shape:
        unk_2870 += local_40 * (bp_4->unk_19C_f * (unk_2884 * (arg_0 / 60.0f)));
#else
        unk_2870 += local_40 * bp_4->unk_19C_f * (arg_0 / 60.0f) * unk_2884;
#endif
        if (!bp_8->unk_4D0)
            var_50 = -18.0f;
        else
            var_50 = dword_429DFC;
        m_4C = 33.84f;
#ifdef CODFH_SP // shape:
        unk_2870 = sub_22C20(unk_2870, -m_4C, -var_50);
#else
        var_60 = -var_50;
        stk_64 = -m_4C;
        unk_2870 = sub_22C20(unk_2870, stk_64, var_60);
#endif
        if (var_C && bp_8->unk_4D0 > 0)
        {
            sub_112DA0(&unk_2878, unk_2874, &unk_287C, flt_429DE8, flt_429DEC, 1000.0f, arg_0);
        }
        else
        {
            unk_2878 = unk_2874;
            unk_287C = 0.0f;
        }
#ifdef CODFH_SP // shape:
        unk_2868 += local_40 * (bp_4->unk_19C_f * (unk_2878 * (arg_0 / 60.0f)));
#else
        unk_2868 += local_40 * bp_4->unk_19C_f * (arg_0 / 60.0f) * unk_2878;
#endif
        if (unk_2868 < 0.0f)
            unk_2868 = 360.0f + unk_2868;
        if (unk_2868 > 360.0f)
            unk_2868 = unk_2868 - 360.0f;
        if (unk_286C < 360.0f)
        {
            bp_58 = unk_286C / 2.0f;
            p54 = 360.0f - bp_58;
            if (unk_2868 > bp_58 && unk_2868 < 180.0f)
                unk_2868 = bp_58;
            else if (unk_2868 < p54 && unk_2868 >= 180.0f)
                unk_2868 = p54;
        }
        if (vf_2E0())
        {
            var_5C = unk_2868 > 180.0f ? unk_2868 - 360.0f : unk_2868;
            if (vf_2E4() > var_5C)
                unk_2868 = vf_2E4() + 360.0f;
            if (vf_2EC() < var_5C)
                unk_2868 = vf_2EC();
        }
    }
}

// match: ?sub_156FC0@type_3DC048@@QAEXXZ @ 0x00156FC0
// sp-match: ?sub_156FC0@type_3DC048@@QAEXXZ @ 0x000FD730
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
// Brings the turret and the gun back to centre, then ends the centring.
void type_3DC048::sub_156FC0()
{
    RwReal var_14;
    RwReal lv_10;
    RwReal var_C;
    RwReal bp_8;
    RwReal bp_4;

    var_14 = 2.0f;
    bp_4 = 0.05f;
#ifdef CODFH_SP // shape:
    lv_10 = (flt_3DBC58 * deltaTime / 1000.0f) * 60.0f;
#else
    lv_10 = deltaTime * flt_3DBC58 / 1000.0f * 60.0f;
#endif
    if (unk_2868 >= 180.0f)
        var_C = 360.0f - unk_2868;
    else
        var_C = unk_2868;
    bp_8 = sub_141700(&unk_299C, var_C, 0.0f, var_14, bp_4, bp_4, lv_10, 0);
    if (unk_2868 > 180.0f)
        unk_2868 += bp_8;
    else
        unk_2868 = unk_2868 - bp_8;
    if ((RwReal)fabs((RwDouble)unk_2868) <= 0.001f || unk_2868 >= 359.99f)
    {
        unk_2868 = 0.0f;
        unk_299C = 0.0f;
    }
    var_C = -unk_2870;
    bp_8 = sub_141700(&unk_29A0, var_C, 0.0f, var_14, bp_4, bp_4, lv_10, 0);
    unk_2870 += bp_8;
    if ((RwReal)fabs((RwDouble)unk_2870) <= 0.001f)
    {
        unk_2870 = 0.0f;
        unk_29A0 = 0.0f;
    }
    if (unk_2868 == 0.0f && unk_2870 == 0.0f)
    {
        unk_2998 = 0;
        sub_159A00();
    }
}

// match: ?sub_1571D0@@YAXXZ @ 0x001571D0
// sp-match: ?sub_1571D0@@YAXXZ @ 0x000F90D0
void sub_1571D0()
{
    dword_4D5160 = 1;
}

// match: ?sub_1571E0@@YAXPAUtype_10F710@@HPAUtype_3DC048@@@Z @ 0x001571E0
// sp-match: ?sub_1571E0@@YAXPAUtype_10F710@@HPAUtype_3DC048@@@Z @ 0x000FD8C0
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void sub_1571E0(type_10F710 *arg_0, RwInt32 arg_4, type_3DC048 *arg_8)
{
    RwReal var_10;
    RwReal var_C;
    RwInt32 bp_8;
    type_712B0_3DBC78 *bp_4;

    if (dword_4D5164 == 1)
    {
        if (dword_4D5160)
        {
            bp_4 = (type_712B0_3DBC78 *)arg_8->get_unk_34C();
            // Two frame slots no code touches (after this temporary and
            // after the posture's): empty inline expansions, as in the
            // vehicle's vf_038.
            unused_slot();
            if (!arg_0->unk_4D4)
            {
                arg_0->sub_10E750(1, 1);
                arg_8->sub_159910(0);
                arg_8->unk_288C = bp_4->unk_1A8;
                sub_157600(arg_0, bp_4->unk_114);
            }
            else if (!arg_0->unk_4D0)
            {
                arg_0->sub_10E750(0, 0);
                arg_8->sub_159910(1);
                arg_8->unk_288C = dword_429DFC;
            }
            if (arg_0->unk_4D4 == 1)
            {
                arg_8->unk_28A4 = 0.0f;
                arg_8->unk_28A0 = 0.0f;
                arg_8->unk_2894 = 0.0f;
                arg_8->unk_2898 = 0.0f;
                arg_8->unk_2890 = arg_8->unk_2868;
                arg_8->unk_289C = arg_8->unk_2870;
                arg_0->unk_1A48[arg_0->unk_1AE4]->sub_117370();
                arg_0->unk_1AE4 = arg_0->get_unk_1AEC();
                unused_slot();
                arg_0->unk_1A48[arg_0->unk_1AE4]->sub_1170B0(1, 1);
                arg_0->sub_10E750(1, 1);
                if (dword_4B9190)
                    dword_4B9190->sub_E0CC0();
            }
            if (arg_0->unk_4D4 == 2)
            {
                sub_157600(arg_0, bp_4->unk_114);
                arg_0->sub_10E750(0, 0);
                arg_8->unk_28B4.z = 0.0f;
                arg_8->unk_28B4.y = 0.0f;
                arg_8->unk_28B4.x = 0.0f;
                arg_8->unk_28C0 = 1;
            }
            arg_0->unk_1C0.sub_8A980(&dword_4B1C60[arg_0->unk_4D4], 0, 4, arg_0->sub_CD550(), 0, 0);
            arg_0->unk_4D0 = arg_0->unk_4D4;
            if (dword_4B9190)
                dword_4B9190->sub_E0B60(arg_8->unk_DD4, arg_8, arg_0->unk_4D0);
            sub_151550();
            sub_1252E0(sub_1571D0, 0);
            sub_124EE0(flt_429DCC, 0);
            dword_4D5164 = 2;
            dword_4D5160 = 0;
        }
    }
    else if (dword_4D5164 == 2)
    {
        if (dword_4D5160)
            dword_4D5164 = 0;
    }
    else
    {
        var_10 = 0.0f;
        var_C = 0.0f;
        if (!((dword_4B86F8 >> 7) & 1) && !((dword_4B86F8 >> 6) & 1) && arg_8->vf_174() > 0 && !arg_8->unk_28_9)
        {
            var_10 = unk_4B9308.sub_EE8F0(arg_0->unk_3D8, 9);
            var_C = unk_4B9308.sub_EE8F0(arg_0->unk_3D8, 10);
        }
        bp_8 = 0;
        if (var_10 != 0.0f)
        {
            if (!arg_0->unk_4D0)
            {
                arg_0->unk_4D4 = 2;
                bp_8 = 1;
            }
            else if (arg_0->unk_4D0 == 2)
            {
                arg_0->unk_4D4 = 1;
                bp_8 = 1;
            }
        }
        else if (var_C != 0.0f)
        {
            if (arg_0->unk_4D0 == 1)
            {
                arg_0->unk_4D4 = 2;
                bp_8 = 1;
            }
            else if (arg_0->unk_4D0 == 2)
            {
                arg_0->unk_4D4 = 0;
                bp_8 = 1;
            }
        }
        if (bp_8)
        {
            sub_1252E0(sub_1571D0, 1);
            sub_124EE0(flt_429DCC, 1);
            dword_4D5164 = 1;
            dword_4D5160 = 0;
        }
    }
}

// match: ?sub_157600@@YAXPAUtype_10F710@@H@Z @ 0x00157600
// sp-match: ?sub_157600@@YAXPAUtype_10F710@@H@Z @ 0x000F90E0
void sub_157600(type_10F710 *arg_0, RwInt32 arg_4)
{
    RwInt32 var_4;

    switch (arg_4)
    {
    case 1:
        var_4 = 35;
        break;
    case 0:
        var_4 = 29;
    default:
        var_4 = 29;
    }
    arg_0->unk_1A48[arg_0->unk_1AE4]->sub_117370();
    arg_0->unk_1AE4 = var_4;
    arg_0->unk_1A48[arg_0->unk_1AE4]->sub_1170B0(1, 1);
}

// match: ?sub_157680@@YAXXZ @ 0x00157680
// sp-match: ?sub_157680@@YAXXZ @ 0x000F9130
void sub_157680()
{
    sub_151550();
}

// Turns arg_0 about the x axis by arg_4 (replacing its rotation), then about
// the y axis by arg_8: an inline vf_044 expands in multiplayer and single
// player keeps out of line (SP 0xF9140, called from SP 0xFE2EC).
// sp-match: ?sp_sub_F9140@@YAXPAURwFrame@@MM@Z @ 0x000F9140
inline void sp_sub_F9140(RwFrame *arg_0, RwReal arg_4, RwReal arg_8)
{
    RwFrameRotate(arg_0, &stru_3DBC5C, arg_4, rwCOMBINEREPLACE);
    RwFrameRotate(arg_0, &stru_3DBC68, arg_8, rwCOMBINEPOSTCONCAT);
}

// match: ?vf_2FC@type_3DC048@@UAEXM@Z @ 0x00157690
// sp-match: ?vf_2FC@type_3DC048@@UAEXM@Z @ 0x000F9170
void type_3DC048::vf_2FC(RwReal arg_0)
{
    type_3DBC78::vf_2FC(arg_0);
}

// match: ?vf_044@type_3DC048@@UAEXM@Z @ 0x001576B0
// sp-match: ?vf_044@type_3DC048@@UAEXM@Z @ 0x000FDBA0
void type_3DC048::vf_044(RwReal arg_0)
{
    type_3D3548 *var_8;
    type_10F710 *var_C;
    type_712B0_3DBC78 *var_18;
    RwFrame *var_20;
    RwReal var_28;
    RwReal var_2C;
    RwV3d var_38;
    RwV3d *var_50;
    RwFrame *var_54;
    RwV3d *var_58;
    RwReal var_5C;
    RpHAnimHierarchy *var_64;
    RwMatrix *var_68;
    RwMatrix *var_6C;
    RwReal var_70;
    RwV3d var_88;
    RwReal var_8C;
    RwV3d var_98;
    RwV3d var_A4;
    RwInt32 var_A8;
    RwV3d var_B4;
    RwReal var_C4;
    RwReal var_C8;
    RwReal var_CC;
    RwReal var_DC;
    RwMatrix var_160;
    RwReal var_164;

    type_3DBC78::vf_044(arg_0);
    var_8 = unk_118C.sub_D4910();
    if (!(var_8 && var_8->unk_2C_4))
        return;
    var_C = (type_10F710 *)var_8;
    if (!(var_C && var_C->vf_200() == this && var_C->get_unk_19D0_r() == 5))
        return;
    var_18 = (type_712B0_3DBC78 *)get_unk_34C();
    var_20 = var_C->get_unk_340();
    sub_1571E0(var_C, (RwInt32)&unk_25C, this);
    switch (var_C->unk_4D0)
    {
    case 0:
        var_28 = var_18->unk_110;
        var_2C = unk_2868 * 0.017453292f;
        var_38.x = var_18->unk_118.x;
        var_38.y = var_18->unk_118.y;
        var_38.z = var_18->unk_118.z;
        var_38.x += sin(var_2C) * var_28;
        var_38.z += cos(var_2C) * var_28;
        sp_sub_F9140(var_20, unk_2870, unk_2868);
        RwFrameTranslate(var_20, &var_38, rwCOMBINEPOSTCONCAT);
        RwFrameUpdateObjects(var_20);
        break;
    case 2:
        var_38.x = 0.0f;
        var_38.y = dword_429DC4;
        var_38.z = -dword_429DC8;
        var_50 = &RwFrameGetMatrix(get_unk_340())->pos;
        var_54 = RwFrameGetParent(var_20);
        var_58 = &RwFrameGetMatrix(var_54)->pos;
#ifdef CODFH_SP // single player reads the pad without the input test (SP 0xFDC6B)
        var_5C = unk_4B9308.sub_EE9A0(0, 6);
#else
        var_5C = unk_4B9308.sub_EE8F0(0, 6);
#endif
        if ((dword_4B86F8 >> 6) & 1)
            var_5C = 0.0f;
        if (var_5C != 0.0f)
        {
            var_64 = get_unk_284()->unk_18;
            var_68 = RpHAnimHierarchyGetMatrixArray(var_64);
            var_6C = &var_68[unk_28DC];
        }
        else
        {
            var_6C = RwFrameGetMatrix(var_54);
        }
        sub_141320(&var_38, &var_38, var_6C);
        RwV3dAdd(&var_38, &var_6C->pos, &var_38);
        if (unk_28CC >= flt_429E24)
            var_38.y = dword_429DC4 + var_50->y;
        if (unk_28C0)
        {
            unk_28C0 = 0;
            unk_28A8 = var_38;
        }
        else
        {
            var_70 = dword_429E00;
            if (var_5C != 0.0f)
                var_70 = dword_429E04;
            RwV3d var_7C = var_6C->pos;
            var_7C.y += 75.0f;
            RwV3dSub(&var_88, &var_38, &var_7C);
            var_8C = RwV3dLength((RwV3d *)&var_88);
            if (var_8C == 0.0f)
            {
                var_98 = var_38;
            }
            else
            {
                RwV3dScale(&var_A4, &var_88, (var_8C + flt_429E20) / var_8C);
                RwV3dAdd(&var_98, &var_7C, &var_A4);
            }
            var_A8 = 0;
            if (sub_FCAE0(&var_7C, &var_98, &var_B4, 0, 0, 0, 1))
            {
                RwV3d var_C0;
                RwV3dSub(&var_C0, &var_B4, var_50);
                var_C0.y = 0.0f;
                var_C4 = RwV3dLength((RwV3d *)&var_C0) - flt_429E20;
                if (var_C4 < flt_429E20)
                    var_C4 = flt_429E20;
                if (var_C4 < unk_28CC)
                {
                    unk_28CC = var_C4;
                    unk_28D0 = dword_429DD0;
                    var_A8 = 1;
                }
            }
            var_C8 = dword_429E18;
            var_CC = dword_429E1C;
            if (!var_A8)
            {
                unk_28D0 -= arg_0 * 0.5f;
                if (unk_28D0 < 0.0f)
                {
                    unk_28D0 = 0.0f;
                    var_C8 = dword_429E10;
                    var_CC = dword_429E14;
                    unk_28CC = dword_429DC8;
                }
            }
            sub_112DA0(&unk_28C4, unk_28CC, &unk_28C8, var_C8, var_CC, 1000.0f, arg_0);
            sub_112DA0(&unk_28A8.x, var_38.x, &unk_28B4.x, var_70, flt_429E08, 1000.0f, arg_0);
            sub_112DA0(&unk_28A8.y, var_38.y, &unk_28B4.y, var_70 * 0.5f, flt_429E08, 1000.0f, arg_0);
            sub_112DA0(&unk_28A8.z, var_38.z, &unk_28B4.z, var_70, flt_429E08, 1000.0f, arg_0);
            RwV3d var_D8;
            RwV3dSub(&var_D8, &unk_28A8, var_50);
            var_D8.y = 0.0f;
            var_DC = RwV3dLength((RwV3d *)&var_D8);
            RwV3dScale(&var_D8, &var_D8, unk_28C4 / var_DC);
            unk_28A8.x = var_D8.x + var_50->x;
            unk_28A8.z = var_D8.z + var_50->z;
            if (unk_28CC < flt_429E24)
                sub_112DA0(&unk_28D4, flt_429E28, &unk_28D8, var_70 * 0.5f, flt_429E08, 1000.0f, arg_0);
            else
                sub_112DA0(&unk_28D4, 0.0f, &unk_28D8, var_70 * 0.5f, flt_429E08, 1000.0f, arg_0);
        }
        RwMatrix var_120;
        RwMatrixInitializeMacro(&var_120, rwMATRIXTYPENORMAL);
        RwV3dSub(&var_120.at, var_58, &unk_28A8);
        var_120.at.y = var_50->y - unk_28A8.y;
        RwV3dNormalize(&var_120.at, &var_120.at);
        var_120.up.x = var_120.up.z = 0.0f;
        var_120.up.y = 1.0f;
        RwV3dCrossProductMacro(&var_120.right, &var_120.up, &var_120.at);
        RwV3dNormalize(&var_120.right, &var_120.right);
        RwV3dCrossProductMacro(&var_120.at, &var_120.right, &var_120.up);
        RwMatrixInitializeMacro(&var_C->unk_490, rwMATRIXTYPENORMAL);
        RwMatrixInitializeMacro(&var_160, rwMATRIXTYPENORMAL);
        var_164 = flt_429E0C + unk_28D4;
        sub_14D1B0(&var_160, var_120.right.x, var_120.right.y, var_120.right.z, var_164);
        RwMatrixMultiply(&var_C->unk_490, &var_120, &var_160);
        var_C->unk_490.pos = unk_28A8;
        break;
    }
}

// match: ?vf_268@type_3DC048@@UAEXPAUtype_10F710@@@Z @ 0x00158100
// sp-match: ?vf_268@type_3DC048@@UAEXPAUtype_10F710@@@Z @ 0x000FE310
void type_3DC048::vf_268(type_10F710 *arg_0)
{
    type_3DBC78::vf_268(arg_0);
    sub_159910(0);
}

// match: ?vf_270@type_3DC048@@UAEXXZ @ 0x00158130
// sp-match: ?vf_270@type_3DC048@@UAEXXZ @ 0x000FE330
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void type_3DC048::vf_270()
{
    type_10F710 *var_8;
    type_3D3548 *l4;

    l4 = unk_118C.sub_D4910();
    if (l4 && l4->unk_2C_4)
    {
        var_8 = (type_10F710 *)l4;
        if (var_8)
            var_8->unk_4D0 = 0;
    }
    unk_2874 = 0.0f;
    unk_2880 = 0.0f;
    type_3DBC78::vf_270();
    sub_159910(1);
}

// match: ?vf_28C@type_3DC048@@UAEXM@Z @ 0x001581B0
// sp-match: ?vf_28C@type_3DC048@@UAEXM@Z @ 0x000F9180
void type_3DC048::vf_28C(RwReal arg_0)
{
    if (!unk_1134 || !unk_DC4)
        unk_450.unk_248 = 0.0f;
    else
        unk_450.unk_248 = arg_0;
}

// match: ?vf_294@type_3DC048@@UAEXMM@Z @ 0x001581F0
// sp-match: ?vf_294@type_3DC048@@UAEXMM@Z @ 0x000F91B0
void type_3DC048::vf_294(RwReal arg_0, RwReal arg_4)
{
    if (unk_2994)
        return;
    if (!unk_DC0)
        return;
    if (unk_28E0 != -1 && unk_28DC == -1 && unk_DC4)
        vf_28C(arg_0);
    else
        unk_2874 = arg_0;
}

// match: ?vf_298@type_3DC048@@UAEXMM@Z @ 0x00158260
// sp-match: ?vf_298@type_3DC048@@UAEXMM@Z @ 0x000F9200
void type_3DC048::vf_298(RwReal arg_0, RwReal arg_4)
{
    if (unk_2994)
        return;
    if (!unk_DC0)
        return;
    unk_2880 = arg_0;
}

// match: ?vf_2A4@type_3DC048@@UAEHH@Z @ 0x001582A0
// sp-match: ?vf_2A4@type_3DC048@@UAEHH@Z @ 0x000F9230
RwInt32 type_3DC048::vf_2A4(RwInt32 arg_0)
{
    if (!arg_0 && (unk_DCC || !unk_DC0))
        return 0;
    if (unk_DFC.unk_00[arg_0].unk_2C < unk_DFC.unk_00[arg_0].unk_30)
        return 0;
    if (unk_DFC.unk_00[arg_0].unk_20 <= 0)
        return 0;
    if ((1 << arg_0) & unk_1100)
        return 0;
    if (!vf_2F0(unk_11A0.unk_1374.sub_D4910()))
        return 0;
    return 1;
}

// match: ?vf_2A8@type_3DC048@@UAEHHPAURwV3d@@H@Z @ 0x00158370
// sp-match: ?vf_2A8@type_3DC048@@UAEHHPAURwV3d@@H@Z @ 0x000F92B0
RwInt32 type_3DC048::vf_2A8(RwInt32 arg_0, RwV3d *arg_4, RwInt32 arg_8)
{
    type_4C19C0 *var_8;
    RwV3d var_D8;

    var_8 = 0;
    if (!arg_8 && !vf_2A4(arg_0))
        return 0;
    unk_DFC.unk_00[arg_0].unk_2C = 0.0f;
    if (unk_DFC.unk_00[arg_0].unk_20 == unk_DFC.unk_00[arg_0].unk_34)
        unk_DFC.unk_00[arg_0].unk_18 = 0.0f;
    unk_DFC.unk_00[arg_0].unk_20 = unk_DFC.unk_00[arg_0].unk_20 - 1;
    switch (arg_0)
    {
    case 0:
        if (!vf_300(arg_0))
            return 0;
        break;
    case 1:
    case 2:
    {
        RwMatrix var_50;
        RwV3d var_5C;
        type_3D3548 *var_60;
        RwReal var_80;
        RwInt32 var_E4;

        if (!unk_DC0)
            return 0;
        if (!sub_EC2D0(get_unk_264(), (RwInt32)&var_50, unk_DFC.unk_00[arg_0].unk_38, 0, 0))
            return 0;
        if (arg_4)
        {
            RwV3dSub(&var_5C, arg_4, &var_50.pos);
            RwV3dNormalize(&var_5C, &var_5C);
            var_50.at = var_5C;
            RwV3dCrossProductMacro(&var_50.up, &var_50.right, &var_50.at);
            RwV3dCrossProductMacro(&var_50.right, &var_50.at, &var_50.up);
        }
        var_60 = sub_1745A0(0);
        var_8 = sub_119B70(30);
        if (sub_1745A0(0) != unk_118C.sub_D4910())
        {
            var_80 = frand_range(-vf_164() * difficulty_4F2890(),
                                 vf_164() * difficulty_4F2890());
            RwMatrixRotate(&var_50, &var_50.up, var_80, rwCOMBINEPRECONCAT);
            var_80 = frand_range(-vf_168() * difficulty_4F2890(),
                                 vf_168() * difficulty_4F2890());
            RwMatrixRotate(&var_50, &var_50.right, var_80, rwCOMBINEPRECONCAT);
        }
        else
        {
            var_80 = frand_range(-var_8->unk_2F0_r[((type_10F710 *)var_60)->unk_1A04],
                                 var_8->unk_2F0_r[((type_10F710 *)var_60)->unk_1A04]);
            RwMatrixRotate(&var_50, &var_50.up, var_80, rwCOMBINEPRECONCAT);
            var_80 = frand_range(-var_8->unk_2F0_r[((type_10F710 *)var_60)->unk_1A04],
                                 var_8->unk_2F0_r[((type_10F710 *)var_60)->unk_1A04]);
            RwMatrixRotate(&var_50, &var_50.right, var_80, rwCOMBINEPRECONCAT);
        }
        RwV3dScale(&var_D8, &var_50.at, unk_DFC.unk_00[arg_0].unk_0C);
        if (unk_DFC.unk_00[arg_0].get_unk_08())
        {
            unk_DFC.unk_00[arg_0].unk_3C.unk_00 = 3;
            unk_DFC.unk_00[arg_0].unk_3C.unk_38 = (RwInt32)unk_DFC.unk_00[arg_0].get_unk_08();
            if ((unk_2C & 7) == 2)
                var_E4 = 0x1002;
            else
                var_E4 = 0x1001;
        }
        else
        {
            unk_DFC.unk_00[arg_0].unk_3C.unk_00 = 0;
            if ((unk_2C & 7) == 2)
                var_E4 = 0x202;
            else
                var_E4 = 0x201;
        }
        unk_DFC.unk_00[arg_0].unk_3C.unk_04_r = unk_DFC.unk_00[arg_0].unk_24;
        sub_15F2C0(var_E4, (RwInt32)this, &var_50, &var_D8, unk_1194, (type_439A48 *)&unk_DFC.unk_00[arg_0].unk_3C,
                   (RwInt32)&var_8->unk_4FC);
        sub_F2FF0(unk_DFC.unk_00[arg_0].unk_10, &var_50, 0, 0, 0, 0);
        sub_F2FF0(unk_DFC.unk_00[arg_0].unk_14, &var_50, 0, 0, 0, 0);
        if (unk_118C.sub_D4910() == var_60)
            unk_1C0.sub_8A980(&unk_3D4.unk_58[arg_0], this, 4, var_60->sub_CD550(), 0, 0);
        else
            unk_1C0.sub_8A980(&unk_3D4.unk_58[arg_0], this, 4, sub_CD550(), 0, 0);
        break;
    }
    case 3:
    {
        RwMatrix var_130;
        RwReal var_150;
        RwInt32 var_178;
        type_3D3548 *var_17C;

        if (!sub_EC2D0(get_unk_264(), (RwInt32)&var_130, unk_DFC.unk_00[arg_0].unk_38, 0, 0))
            return 0;
        var_150 = frand_range(-vf_164() * difficulty_4F2890(),
                              vf_164() * difficulty_4F2890());
        RwMatrixRotate(&var_130, &var_130.up, var_150, rwCOMBINEPRECONCAT);
        var_150 = frand_range(-vf_168() * difficulty_4F2890(),
                              vf_168() * difficulty_4F2890());
        RwMatrixRotate(&var_130, &var_130.right, var_150, rwCOMBINEPRECONCAT);
        RwV3dScale(&var_D8, &var_130.at, unk_DFC.unk_00[arg_0].unk_0C);
        if (unk_DFC.unk_00[arg_0].get_unk_08())
        {
            unk_DFC.unk_00[arg_0].unk_3C.unk_00 = 3;
            unk_DFC.unk_00[arg_0].unk_3C.unk_38 = (RwInt32)unk_DFC.unk_00[arg_0].get_unk_08();
            if ((unk_2C & 7) == 2)
                var_178 = 0x1002;
            else
                var_178 = 0x1001;
        }
        else
        {
            unk_DFC.unk_00[arg_0].unk_3C.unk_00 = 0;
            if ((unk_2C & 7) == 2)
                var_178 = 0x202;
            else
                var_178 = 0x201;
        }
        unk_DFC.unk_00[arg_0].unk_3C.unk_04_r = unk_DFC.unk_00[arg_0].unk_24;
        sub_15F2C0(var_178, (RwInt32)this, &var_130, &var_D8, unk_1194, (type_439A48 *)&unk_DFC.unk_00[arg_0].unk_3C, 0);
        sub_F2FF0(unk_DFC.unk_00[arg_0].unk_10, &var_130, 0, 0, 0, 0);
        sub_F2FF0(unk_DFC.unk_00[arg_0].unk_14, &var_130, 0, 0, 0, 0);
        var_17C = sub_1745A0(0);
        if (unk_118C.sub_D4910() == var_17C)
            unk_1C0.sub_8A980(&unk_3D4.unk_58[arg_0], this, 4, var_17C->sub_CD550(), 0, 0);
        else
            unk_1C0.sub_8A980(&unk_3D4.unk_58[arg_0], this, 4, sub_CD550(), 0, 0);
        break;
    }
    }
    return 1;
}

// match: ?vf_300@type_3DC048@@UAEHH@Z @ 0x00158FC0
// sp-match: ?vf_300@type_3DC048@@UAEHH@Z @ 0x000F98E0
// The main gun's shot (gun arg_0, from vf_2A8): its shell spread by the
// difficulty, with the settings of weapon 29, a shake for the player
// within 500, a recoil push, and "SingleShotFinished".
RwInt32 type_3DC048::vf_300(RwInt32 arg_0)
{
    RwMatrix var_50;
    RwReal var_70;
    RwV3d var_98;
    type_4C19C0 *var_9C;
    RwInt32 var_A4;
    type_3D3548 *var_A8;
    RwV3d var_B4;
    RwReal var_B8;
    RwReal var_BC;
    RwV3d var_C8;
    RwV3d var_D4;
    RwInt32 var_D8;

    if (!sub_EC2D0(get_unk_264(), (RwInt32)&var_50, unk_DFC.unk_00[arg_0].unk_38, 0, 0))
        return 0;
    var_70 = frand_range(-vf_164() * difficulty_4F2890(),
                         vf_164() * difficulty_4F2890());
    RwMatrixRotate(&var_50, &var_50.up, var_70, rwCOMBINEPRECONCAT);
    var_70 = frand_range(-vf_168() * difficulty_4F2890(),
                         vf_168() * difficulty_4F2890());
    RwMatrixRotate(&var_50, &var_50.right, var_70, rwCOMBINEPRECONCAT);
    RwV3dScale(&var_98, &var_50.at, unk_DFC.unk_00[arg_0].unk_0C);
    var_9C = sub_119B70(29);
    unk_DFC.unk_00[arg_0].unk_3C.unk_00 = 3;
    unk_DFC.unk_00[arg_0].unk_3C.unk_04_r = unk_DFC.unk_00[arg_0].unk_24;
    unk_DFC.unk_00[arg_0].unk_3C.unk_38 = (RwInt32)unk_DFC.unk_00[arg_0].get_unk_08();
    unk_DFC.unk_00[arg_0].unk_3C.unk_3C = 1;
    unk_DFC.unk_00[arg_0].unk_3C.unk_40 = var_9C->unk_C0;
    unk_DFC.unk_00[arg_0].unk_3C.unk_44 = var_9C->unk_194;
    unk_DFC.unk_00[arg_0].unk_3C.unk_48 = var_9C->unk_198;
    unk_DFC.unk_00[arg_0].unk_3C.unk_4C_r = var_9C->unk_D0;
    unk_DFC.unk_00[arg_0].unk_8C = var_9C->unk_4B4;
    unk_DFC.unk_00[arg_0].unk_90 = unk_DFC.unk_00[arg_0].unk_28;
    unk_DFC.unk_00[arg_0].unk_94 = var_9C->unk_4BC;
    unk_DFC.unk_00[arg_0].unk_98 = var_9C->unk_4C0;
    unk_DFC.unk_00[arg_0].unk_9C = var_9C->unk_4C4;
    unk_DFC.unk_00[arg_0].unk_A0 = var_9C->unk_4C8;
    unk_DFC.unk_00[arg_0].unk_A4 = var_9C->unk_4CC;
    unk_DFC.unk_00[arg_0].unk_AC = var_9C->unk_98;
    unk_DFC.unk_00[arg_0].unk_A8 = var_9C->unk_9C;
    unk_DFC.unk_00[arg_0].unk_B4 = var_9C->unk_A0;
    unk_DFC.unk_00[arg_0].unk_B0 = var_9C->unk_A4;
    unk_DFC.unk_00[arg_0].unk_B8 = var_9C->unk_A8;
    unk_DFC.unk_00[arg_0].unk_BC = var_9C->unk_AC;
    if ((unk_2C & 7) == 2)
        var_A4 = 0x1002;
    else
        var_A4 = 0x1001;
    sub_15F2C0(var_A4, (RwInt32)this, &var_50, &var_98, unk_1194, (type_439A48 *)&unk_DFC.unk_00[arg_0].unk_3C, 0);
    sub_F2FF0(unk_DFC.unk_00[arg_0].unk_10, &var_50, 0, 0, 0, 0);
    sub_F2FF0(unk_DFC.unk_00[arg_0].unk_14, &var_50, 0, 0, 0, 0);
    var_A8 = sub_1745A0(0);
    if (var_A8)
    {
#ifdef CODFH_SP
        // shape: the difference in a block-scoped local, so /O2 loads each
        // vf_0C4 call's vtable before the previous component's store (SP 0xF9C38)
        RwV3d d;
        RwV3dSub(&d, &var_50.pos, (RwV3d *)var_A8->vf_0C4());
        var_B8 = RwV3dLength(&d);
#else
        RwV3dSub(&var_B4, &var_50.pos, (RwV3d *)var_A8->vf_0C4());
        var_B8 = RwV3dLength((RwV3d *)&var_B4);
#endif
        if (var_B8 < 500.0f)
        {
            var_BC = ((500.0f - var_B8) / 500.0f) * var_9C->unk_98_f;
            ((type_10F710 *)var_A8)->sub_110A10(var_BC);
        }
    }
    if (unk_118C.sub_D4910() == var_A8)
        unk_1C0.sub_8A980(&unk_3D4.unk_58[arg_0], this, 4, var_A8->sub_CD550(), 0, 0);
    else
        unk_1C0.sub_8A980(&unk_3D4.unk_58[arg_0], this, 4, sub_CD550(), 0, 0);
    var_C8.x = 0.0f;
    var_C8.y = 200.0f;
    var_C8.z = 100.0f;
    var_D4.x = 0.0f;
    var_D4.y = 0.0f;
    var_D4.z = -2.0f * unk_450.unk_24C;
    sub_141320(&var_C8, &var_C8, &var_50);
    sub_141320(&var_D4, &var_D4, &var_50);
    vf_264(60, &var_D4, &var_C8);
    var_D8 = 0;
    sub_6B5F0("SingleShotFinished", (type_67620 *)(vf_098()), 0, 0, &var_D8, 1, 1, 0);
    return 1;
}

// match: ?vf_2B8@type_3DC048@@UAEXXZ @ 0x001597A0
// sp-match: ?vf_2B8@type_3DC048@@UAEXXZ @ 0x000FE370
void type_3DC048::vf_2B8()
{
    type_3DBC78::vf_2B8();
    if (unk_2998)
        return;
    if (!unk_2860 && (RwReal)fabs((RwDouble)unk_2874) > flt_429E2C)
    {
        unk_2860 = 1;
        sub_159950();
    }
    else if (unk_2860 && (RwReal)fabs((RwDouble)unk_2874) < flt_429E2C)
    {
        unk_2860 = 0;
        if (!unk_2864)
            sub_159A00();
    }
    if (!unk_2864 && (RwReal)fabs((RwDouble)unk_2880) > flt_429E2C)
    {
        unk_2864 = 1;
        sub_159950();
    }
    else if (unk_2864 && (RwReal)fabs((RwDouble)unk_2880) < flt_429E2C)
    {
        unk_2864 = 0;
        if (!unk_2860)
            sub_159A00();
    }
}

// match: ?sub_159910@type_3DC048@@QAEXH@Z @ 0x00159910
// sp-match: ?sub_159910@type_3DC048@@QAEXH@Z @ 0x000F9DC0
// Shows its "turret" part (arg_0) or hides it.
void type_3DC048::sub_159910(RwInt32 arg_0)
{
    sub_16D8C0(get_unk_264(), "turret", arg_0 != 0);
}

// match: ?sub_159950@type_3DC048@@QAEXXZ @ 0x00159950
// sp-match: ?sub_159950@type_3DC048@@QAEXXZ @ 0x000F9DF0
void type_3DC048::sub_159950()
{
    type_3D3548 *var_4;

    if (!unk_1148)
    {
        var_4 = sub_1745A0(0);
        if (unk_118C.sub_D4910() == var_4)
            unk_1148 = var_4->unk_1C0.sub_8A980(&unk_3D4.unk_40, this, 4, var_4->sub_CD550(), 0, 0);
        else
            unk_1148 = unk_1C0.sub_8A980(&unk_3D4.unk_40, this, 4, sub_CD550(), 0, 0);
    }
}

// match: ?sub_159A00@type_3DC048@@QAEXXZ @ 0x00159A00
// sp-match: ?sub_159A00@type_3DC048@@QAEXXZ @ 0x000F9E70
void type_3DC048::sub_159A00()
{
    type_3D3548 *var_4;

    if (unk_1148)
    {
        unk_1C0.sub_8A910(unk_1148);
        unk_1148 = 0;
    }
    var_4 = sub_1745A0(0);
    if (unk_118C.sub_D4910() == var_4)
        var_4->unk_1C0.sub_8A980(&unk_3D4.unk_48, this, 4, var_4->sub_CD550(), 0, 0);
    else
        unk_1C0.sub_8A980(&unk_3D4.unk_48, this, 4, sub_CD550(), 0, 0);
}

// match: ?sub_159AC0@@YAPAURtAnimAnimation@@XZ @ 0x00159AC0
// sp-match: ?sub_159AC0@@YAPAURtAnimAnimation@@XZ @ 0x000FE460
// The tracks' "VTrack" UV animation from the current dictionary, made there
// once: two linear key frames a second apart, the second moved one down.
RtAnimAnimation *sub_159AC0()
{
    RtAnimAnimation *var_4;
    RtDict *var_8;
    RwUInt32 var_C;
    RwReal var_10;
    RwUInt32 var_14;
    type_159AC0 *var_18;
    type_159AC0 *var_1C;
    RpUVAnimKeyFrame *var_20;
    RwReal var_24;
    RwV3d var_30;
    RwUInt32 var_34;
    RwReal *var_38;
    RwMatrix var_80;

    var_4 = 0;
    var_8 = schema;
    if (var_8)
    {
        var_4 = (RtAnimAnimation *)RtDictFindNamedEntry(var_8, "VTrack");
        if (var_4)
            return var_4;
        var_C = 2;
        var_10 = 1.0f;
        var_14 = 0;
        var_4 = RpUVAnimCreate("VTrack", 1, var_C, var_10, &var_14, rpUVANIMPARAMKEYFRAMES);
        var_18 = (type_159AC0 *)RwMalloc(sizeof(type_159AC0), 0x10000);
        var_1C = var_18;
        var_1C->unk_00 = (RpUVAnimKeyFrame *)RwMalloc(var_C * sizeof(RpUVAnimKeyFrame), 0x10000);
        var_20 = var_1C->unk_00;
        var_1C->unk_04 = var_C;
        var_24 = 0.0f;
        var_30.x = 0.0f;
        var_30.y = 0.0f;
        var_30.z = 0.0f;
        for (var_34 = 0; var_34 < var_C; var_34++)
        {
            var_38 = var_20->data;
            RwMatrixTranslate(&var_80, &var_30, rwCOMBINEREPLACE);
            var_38[0] = 1.0f;
            var_38[1] = 0.0f;
            var_38[2] = 0.0f;
            var_38[3] = 1.0f;
            var_38[4] = var_80.pos.x;
            var_38[5] = var_80.pos.y;
            var_20->time = var_24;
            var_30.y -= 1.0f;
            var_24 += 1.0f;
            var_20++;
        }
        sub_159CB0(var_4, var_18, 1);
        RwFree(var_18->unk_00);
        RwFree(var_18);
        RtDictAddEntry(var_8, var_4);
        RpUVAnimDestroy(var_4);
    }
    return var_4;
}

// match: ?sub_159CB0@@YAHPAURtAnimAnimation@@PAUtype_159AC0@@H@Z @ 0x00159CB0
// sp-match: ?sub_159CB0@@YAHPAURtAnimAnimation@@PAUtype_159AC0@@H@Z @ 0x000F9F00
RwInt32 sub_159CB0(RtAnimAnimation *arg_0, type_159AC0 *arg_4, RwInt32 arg_8)
{
    RwReal *var_80;
    RpUVAnimKeyFrame *var_7C;
    RwReal var_78;
    RwInt32 var_74;
    RwReal *var_28;
    RpUVAnimKeyFrame *var_24;
    RwInt32 var_20;
    RwInt32 var_1C;
    RpUVAnimKeyFrame *var_18;
    RwInt32 var_14;
    RwInt32 var_10;
    RwInt32 *var_C;
    RwUInt8 **var_8;
    RpUVAnimKeyFrame **var_4;

    var_4 = (RpUVAnimKeyFrame **)RwMalloc(arg_8 * sizeof(RpUVAnimKeyFrame *), 0x10000);
    var_8 = (RwUInt8 **)RwMalloc(arg_8 * sizeof(RwUInt8 *), 0x10000);
    var_C = (RwInt32 *)RwMalloc(arg_8 * sizeof(RwInt32), 0x10000);
    memset(var_4, 0, arg_8 * sizeof(RpUVAnimKeyFrame *));
    var_10 = 0;
    for (var_14 = 0; var_14 < arg_8; var_14++)
    {
        var_8[var_14] = arg_4[var_14].unk_00_b;
        var_C[var_14] = arg_4[var_14].unk_04;
        var_10 += arg_4[var_14].unk_04;
    }
    var_18 = ((type_159CB0 *)arg_0)->pFrames;
    var_1C = ((type_159CB0 *)arg_0)->interpInfo->animKeyFrameSize;
    for (var_20 = 0; var_20 < 2; var_20++)
    {
        for (var_14 = 0; var_14 < arg_8; var_14++)
        {
            RwMatrix var_70;

            do
            {
                var_24 = (RpUVAnimKeyFrame *)var_8[var_14];
                var_28 = var_24->data;
                var_70.right.x = var_28[0];
                var_70.right.y = var_28[1];
                var_70.right.z = 0.0f;
                var_70.up.x = var_28[2];
                var_70.up.y = var_28[3];
                var_70.up.z = 0.0f;
                var_70.at.x = 0.0f;
                var_70.at.y = 0.0f;
                var_70.at.z = 0.0f;
                var_70.pos.x = var_28[4];
                var_70.pos.y = var_28[5];
                var_70.pos.z = 0.0f;
                RwMatrixUpdate(&var_70);
            } while (0);
            RpUVAnimKeyFrameInit(arg_0, var_18, var_4[var_14], ((RpUVAnimKeyFrame *)var_8[var_14])->time, &var_70);
            var_4[var_14] = var_18;
            var_18++;
            var_8[var_14] += var_1C;
            var_C[var_14]--;
            var_10--;
        }
    }
    for (var_20 = 0; var_20 < var_10; var_20++)
    {
        RwMatrix var_C0;

        var_74 = -1;
        var_78 = 3.4028235e38f;
        for (var_14 = 0; var_14 < arg_8; var_14++)
        {
            if (var_4[var_14]->time < var_78 && var_C[var_14])
            {
                var_78 = var_4[var_14]->time;
                var_74 = var_14;
            }
        }
        do
        {
            var_7C = (RpUVAnimKeyFrame *)var_8[var_74];
            var_80 = var_7C->data;
            var_C0.right.x = var_80[0];
            var_C0.right.y = var_80[1];
            var_C0.right.z = 0.0f;
            var_C0.up.x = var_80[2];
            var_C0.up.y = var_80[3];
            var_C0.up.z = 0.0f;
            var_C0.at.x = 0.0f;
            var_C0.at.y = 0.0f;
            var_C0.at.z = 0.0f;
            var_C0.pos.x = var_80[4];
            var_C0.pos.y = var_80[5];
            var_C0.pos.z = 0.0f;
            RwMatrixUpdate(&var_C0);
        } while (0);
        RpUVAnimKeyFrameInit(arg_0, var_18, var_4[var_74], ((RpUVAnimKeyFrame *)var_8[var_74])->time, &var_C0);
        var_4[var_74] = var_18;
        var_18++;
        var_8[var_74] += var_1C;
        var_C[var_74]--;
    }
    var_18 = ((type_159CB0 *)arg_0)->pFrames;
    for (var_14 = 0; var_14 < arg_8; var_14++)
    {
        var_18->prevFrame = var_4[var_14];
        var_18++;
    }
    RwFree(var_4);
    RwFree(var_8);
    RwFree(var_C);
    return 1;
}

// match: ?sub_15A0F0@type_3DC048@@QAEXPAUtype_3DFEEC@@@Z @ 0x0015A0F0
// sp-match: ?sub_15A0F0@type_3DC048@@QAEXPAUtype_3DFEEC@@@Z @ 0x000FA2C0
void type_3DC048::sub_15A0F0(type_3DFEEC *arg_0)
{
    if (arg_0)
    {
        unk_2994 = 1;
        unk_2990 = arg_0;
    }
}

// match: ?sub_15A120@type_3DC048@@QAEXXZ @ 0x0015A120
// sp-match: ?sub_15A120@type_3DC048@@QAEXXZ @ 0x000FA2E0
void type_3DC048::sub_15A120()
{
    unk_2994 = 0;
    unk_2990 = 0;
    unk_2874 = 0.0f;
    unk_2880 = 0.0f;
}

// match: ?sub_15A160@type_3DC048@@QAEXXZ @ 0x0015A160
// sp-match: ?sub_15A160@type_3DC048@@QAEXXZ @ 0x000FA300
void type_3DC048::sub_15A160()
{
    RwMatrix var_50;
    RwV3d *var_54;
    RwV3d *var_58;
    RwV3d var_64;
    RwV3d var_70;
    RwV3d var_7C;
    RwReal var_80;
    RwV3d var_8C;
    RwV3d var_98;
    RwReal var_9C;
    RwReal var_A0;
    RwReal var_A4;
    RwReal var_A8;

    if (!(unk_2994 && unk_DC0))
        return;
    sub_EC2D0(get_unk_264(), (RwInt32)&var_50, unk_DFC.unk_00[0].unk_38, 0, 1);
    var_54 = &var_50.pos;
    var_58 = unk_2990->vf_00C();
    if (!var_58)
    {
        sub_15A120();
        return;
    }
    var_64.x = var_58->x - var_54->x;
    var_64.y = 0.0f;
    var_64.z = var_58->z - var_54->z;
    RwV3dNormalize(&var_70, &var_64);
    var_7C = var_50.at;
    var_80 = var_7C.y / RwV3dLength((RwV3d *)&var_7C);
    var_7C.y = 0.0f;
    RwV3dNormalize(&var_8C, &var_7C);
    RwV3dCrossProductMacro(&var_98, &var_8C, &var_70);
    var_9C = RwV3dDotProduct(&var_8C, &var_70);
    if (var_9C < 0.99f)
        var_9C = 0.0f;
    else
        var_9C = (var_9C - 0.99f) * 100.0f;
    unk_2994 = 0;
    if (var_98.y > 0.0f)
        vf_294(1.0f - var_9C, 1.0f);
    else if (var_98.y < 0.0f)
        vf_294(-1.0f + var_9C, 1.0f);
    var_64.y = var_58->y - var_54->y;
    var_A0 = var_58->y - var_54->y;
    var_A8 = (var_A4 = var_A0 / RwV3dLength((RwV3d *)&var_64)) - var_80;
    if (var_A8 < 0.087 && var_A8 > -0.087)
        vf_298(-var_A8, 1.0f);
    else if (var_A8 > 0.0f)
        vf_298(-1.0f, 1.0f);
    else
        vf_298(1.0f, 1.0f);
    unk_2994 = 1;
}

// match: ?sub_15A480@type_3DC048@@QAEHH@Z @ 0x0015A480
// sp-match: ?sub_15A480@type_3DC048@@QAEHH@Z @ 0x000FA550
RwInt32 type_3DC048::sub_15A480(RwInt32 arg_0)
{
    return unk_2918[arg_0].unk_04;
}

// match: ?sub_15A4A0@type_3DC048@@QAEXHHHHH@Z @ 0x0015A4A0
// sp-match: ?sub_15A4A0@type_3DC048@@QAEXHHHHH@Z @ 0x000FA570
void type_3DC048::sub_15A4A0(RwInt32 arg_0, RwInt32 arg_4, RwInt32 arg_8, RwInt32 arg_C, RwInt32 arg_10)
{
    unk_2918[arg_0].unk_04 = arg_10;
    unk_2918[arg_0].unk_14_i = arg_C;
    unk_2918[arg_0].unk_0C = arg_8;
    unk_2918[arg_0].unk_08 = arg_4;
    if (arg_10)
        unk_2918[arg_0].unk_10 = 0.0f;
    else
        unk_2918[arg_0].unk_10 = *(RwReal *)&arg_C;
}

// match: ?sub_15A530@type_3DC048@@QAEXMM@Z @ 0x0015A530
// sp-match: ?sub_15A530@type_3DC048@@QAEXMM@Z @ 0x000FA5C0
void type_3DC048::sub_15A530(RwReal arg_0, RwReal arg_4)
{
    unk_290C = 1;
    unk_2914 = arg_0 * arg_0;
    unk_2910 = cos((0.5f * arg_4 * 3.1415927f) / 180.0f);
}

// match: ?sub_15A590@type_3DC048@@QAEXXZ @ 0x0015A590
// sp-match: ?sub_15A590@type_3DC048@@QAEXXZ @ 0x000FA600
void type_3DC048::sub_15A590()
{
    unk_290C = 0;
    unk_2914 = 1.0e37f;
    unk_2910 = -1.0f;
}

// match: ?vf_2B0@type_3DC048@@UAEXXZ @ 0x0015A5D0
// sp-match: ?vf_2B0@type_3DC048@@UAEXXZ @ 0x000FA620
void type_3DC048::vf_2B0()
{
    if (unk_2998)
        return;
    sub_159950();
    unk_2998 = 1;
    unk_299C = 0.0f;
    unk_29A0 = 0.0f;
}

// match: ?vf_2F0@type_3DC048@@UAEHPAUtype_3D3548@@@Z @ 0x0015A620
// sp-match: ?vf_2F0@type_3DC048@@UAEHPAUtype_3D3548@@@Z @ 0x000FA660
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
RwInt32 type_3DC048::vf_2F0(type_3D3548 *arg_0)
{
    RwV3d var_18;
    RwReal var_C;
    RwFrame *bp_8;
    RpClump *bp_4;

    if (!vf_2E0() || !arg_0)
        return 1;
    bp_4 = unk_25C.unk_08;
    if (bp_4)
    {
        bp_8 = RpClumpGetFrame(bp_4);
        if (!sub_1409C0(arg_0->vf_0CC(), RwFrameGetMatrix(bp_8), vf_2E8(), 0.0f))
            return 0;
        RwV3dSub(&var_18, arg_0->sub_CD550(), sub_CD550());
        var_C = RwV3dDotProduct(&var_18, &var_18);
        if (var_C < unk_2914)
            return 1;
    }
    return 0;
}

// match: ?vf_058@type_3DC048@@UAEHPAUtype_3DF8D8_04@@@Z @ 0x0015A750
// sp-match: ?vf_058@type_3DC048@@UAEHPAUtype_3DF8D8_04@@@Z @ 0x000FA760
RwInt32 type_3DC048::vf_058(type_3DF8D8_04 *arg_0)
{
    type_3DF8D8_04 *var_4;

    if (unk_2990)
    {
        var_4 = &unk_2990->unk_04;
        // (Both halves of arg_0 are compared with the first of the key, as
        // the image does.)
        if (var_4->unk_00 == arg_0->unk_00 && var_4->unk_00 == arg_0->unk_04)
            return 1;
    }
    return type_3DBC78::vf_058(arg_0);
}

// match: ?sub_15A7B0@@YAPAUtype_3DC378@@PAUtype_712B0@@@Z @ 0x0015A7B0
// match: __ehhandler$?sub_15A7B0@@YAPAUtype_3DC378@@PAUtype_712B0@@@Z-0x11 @ 0x00301CE0
// match: __ehhandler$?sub_15A7B0@@YAPAUtype_3DC378@@PAUtype_712B0@@@Z @ 0x00301CF1
// sp-match: ?sub_15A7B0@@YAPAUtype_3DC378@@PAUtype_712B0@@@Z @ 0x000FF960
// Builds the flak gun for the trigger arg_0, or warns that there is no
// entity memory for it.
type_3DC378 *sub_15A7B0(type_712B0 *arg_0)
{
    type_3DC378 *var_10;

    var_10 = (type_3DC378 *)sub_D56D0(0x29D0, arg_0->unk_24_18, arg_0->vf_008());
    if (var_10 != 0)
    {
        var_10 = new (var_10) type_3DC378(arg_0);
        if (var_10->unk_28 & 0x400000) // not an address: entity flag
        {
            sub_D5A60(var_10, 0);
            var_10 = 0;
        }
    }
#if defined(CODFH_SP) && !defined(CODFH_SP_LOGS) // single player compiles the debug print out (no warning; SP 0xFF960)
#else
    else
    {
        sub_19A750("WARNING: A spawn could not be created due to lack of entity memory. Trigger "
                   "location(%6.2f,%6.2f,%6.2f)",
                   arg_0->unk_90, arg_0->unk_94, arg_0->unk_98);
    }
#endif
    return var_10;
}

// match: ??0type_3DC378@@QAE@PAUtype_712B0@@@Z @ 0x0015A8C0
// match: __ehhandler$??0type_3DC378@@QAE@PAUtype_712B0@@@Z-0x20 @ 0x00301D00
// match: __ehhandler$??0type_3DC378@@QAE@PAUtype_712B0@@@Z @ 0x00301D20
// sp-match: ??0type_3DC378@@QAE@PAUtype_712B0@@@Z @ 0x000FF690
type_3DC378::type_3DC378(type_712B0 *arg_0)
{
    sub_15AA70(arg_0);
}

// match: ?vf_2E4@type_3DC378@@UAEMXZ @ 0x0015A950
// sp-match: ?vf_2E4@type_3DC378@@UAEMXZ @ 0x000FF700

// match: ?vf_2EC@type_3DC378@@UAEMXZ @ 0x0015A970
// sp-match: ?vf_2EC@type_3DC378@@UAEMXZ @ 0x000FF710

// match: ?vf_2E8@type_3DC378@@UAEMXZ @ 0x0015A990
// sp-match: ?vf_2E8@type_3DC378@@UAEMXZ @ 0x000FF720

// match: ??_Gtype_3DC378@@UAEPAXI@Z @ 0x0015A9B0
// sp-match: ??_Gtype_3DC378@@UAEPAXI@Z @ 0x000FF730
// (Compiler-written: the destructor, then the class's plain operator delete.)

// match: ??1type_3DC378@@UAE@XZ @ 0x0015A9E0
// match: __ehhandler$??1type_3DC378@@UAE@XZ-0x28 @ 0x00301D30
// match: __ehhandler$??1type_3DC378@@UAE@XZ @ 0x00301D58
// sp-match: ??1type_3DC378@@UAE@XZ @ 0x000FF750
type_3DC378::~type_3DC378()
{
    vf_230();
}

// match: ?sub_15AA70@type_3DC378@@QAEHPAUtype_712B0@@@Z @ 0x0015AA70
// sp-match: ?sub_15AA70@type_3DC378@@QAEHPAUtype_712B0@@@Z @ 0x000FE5B0
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
RwInt32 type_3DC378::sub_15AA70(type_712B0 *arg_0)
{
    RwInt32 var_8;
    type_712B0_3DBC78 *l4;

    sub_155780(arg_0);
    unk_2C |= 0x400000; // not an address: kind flags
    l4 = (type_712B0_3DBC78 *)arg_0;
    unk_29B0 = l4->unk_200;
    unk_29B4 = cos(unk_29B0);
    for (var_8 = 0; var_8 < 3; var_8++)
    {
        unk_29B8[var_8].sub_D48D0(0);
        unk_29C4[var_8] = -1;
    }
    unk_DFC.unk_00[0].unk_38 = 0x41464952; // not an address: a tag
    unk_DC4 = 0;
    return 1;
}

// match: ?sub_15AB40@type_3DC378@@QAEHH@Z @ 0x0015AB40
// sp-match: ?sub_15AB40@type_3DC378@@QAEHH@Z @ 0x000FA790
RwInt32 type_3DC378::sub_15AB40(RwInt32 arg_0)
{
    type_3D3548 *var_4;

    var_4 = unk_29B8[arg_0].sub_D4910();
    if (var_4 && var_4->vf_098())
        return var_4->vf_098()->get_unk_04();
    return 0;
}

// match: ?sub_15ABA0@type_3DC378@@QAEXHPAUtype_3D3548@@@Z @ 0x0015ABA0
// sp-match: ?sub_15ABA0@type_3DC378@@QAEXHPAUtype_3D3548@@@Z @ 0x000FA7D0
void type_3DC378::sub_15ABA0(RwInt32 arg_0, type_3D3548 *arg_4)
{
    unk_29B8[arg_0].sub_D48D0(arg_4);
    unk_29C4[arg_0] = 0;
}

// match: ?sub_15ABE0@type_3DC378@@QAEXHH@Z @ 0x0015ABE0
// sp-match: ?sub_15ABE0@type_3DC378@@QAEXHH@Z @ 0x000FA800
void type_3DC378::sub_15ABE0(RwInt32 arg_0, RwInt32 arg_4)
{
    unk_29C4[arg_0] = arg_4;
}

// match: ?sub_15AC00@type_3DC378@@QAEXHH@Z @ 0x0015AC00
// sp-match: ?sub_15AC00@type_3DC378@@QAEXHH@Z @ 0x000FF410
void type_3DC378::sub_15AC00(RwInt32 arg_0, RwInt32 arg_4)
{
    switch (arg_0)
    {
    case 0:
        unk_29B8[0].sub_D48D0(0);
        unk_29C4[0] = -1;
        if (arg_4)
            sub_15ACC0();
        break;
    case 1:
        unk_29B8[1].sub_D48D0(0);
        unk_29C4[1] = -1;
        if (arg_4)
            sub_15AD60();
        break;
    case 2:
        unk_29B8[2].sub_D48D0(0);
        unk_29C4[2] = -1;
        if (arg_4)
            sub_15ADF0();
        break;
    }
}

// match: ?sub_15ACC0@type_3DC378@@QAEXXZ @ 0x0015ACC0
// sp-match: ?sub_15ACC0@type_3DC378@@QAEXXZ @ 0x000FE630
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void type_3DC378::sub_15ACC0()
{
    RwInt32 var_8;
    type_3D3548 *l4;

    l4 = unk_29B8[2].sub_D4910();
    if (l4 && type_3DBC78::vf_2DC())
    {
        sub_6B5F0("AssumeGunnerRole", (type_67620 *)(l4->vf_098()), 0, 0, &var_8, 0, 1, 0);
        unk_DC0 = 0;
        sub_15ABE0(2, 0);
        sub_15AE20();
    }
    else if (sub_15AF20())
    {
        sub_15AE40(1);
    }
}

// match: ?sub_15AD60@type_3DC378@@QAEXXZ @ 0x0015AD60
// sp-match: ?sub_15AD60@type_3DC378@@QAEXXZ @ 0x000FE6B0
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void type_3DC378::sub_15AD60()
{
    RwInt32 var_8;
    type_3D3548 *l4;

    l4 = unk_29B8[2].sub_D4910();
    if (l4 && type_3DBC78::vf_2DC())
    {
        sub_6B5F0("AssumeLoaderRole", (type_67620 *)(l4->vf_098()), 0, 0, &var_8, 0, 1, 0);
        sub_15ABE0(2, 0);
        sub_15AE20();
    }
    else if (sub_15AEE0())
    {
        sub_15AE40(1);
    }
}

// match: ?sub_15ADF0@type_3DC378@@QAEXXZ @ 0x0015ADF0
// sp-match: ?sub_15ADF0@type_3DC378@@QAEXXZ @ 0x000FE720
void type_3DC378::sub_15ADF0()
{
    if (sub_15AF60())
        sub_15AE40(1);
}

// match: ?sub_15AE20@type_3DC378@@QAEXXZ @ 0x0015AE20
// sp-match: ?sub_15AE20@type_3DC378@@QAEXXZ @ 0x000FA820
void type_3DC378::sub_15AE20()
{
    unk_DC0 = 0;
}

// match: ?sub_15AE40@type_3DC378@@QAEXH@Z @ 0x0015AE40
// sp-match: ?sub_15AE40@type_3DC378@@QAEXH@Z @ 0x000FA830
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void type_3DC378::sub_15AE40(RwInt32 arg_0)
{
    RwInt32 var_8;
    RwInt32 l4;

    unk_DC0 = 0;
    for (l4 = 0; l4 < 3; l4++)
    {
        if (unk_29B8[l4].sub_D4910())
        {
            var_8 = arg_0;
            sub_6B5F0("FlakGunDisabled", (type_67620 *)(unk_29B8[l4].sub_D4910()->vf_098()), 0, 0, &var_8, 1, 1, 0);
        }
    }
}

// match: ?sub_15AEE0@type_3DC378@@QAEHXZ @ 0x0015AEE0
// sp-match: ?sub_15AEE0@type_3DC378@@QAEHXZ @ 0x000FA8A0
RwInt32 type_3DC378::sub_15AEE0()
{
    type_712B0_3DBC78 *var_4;

    var_4 = (type_712B0_3DBC78 *)get_unk_34C();
    if (var_4)
        return var_4->unk_208;
    return 0;
}

// match: ?sub_15AF20@type_3DC378@@QAEHXZ @ 0x0015AF20
// sp-match: ?sub_15AF20@type_3DC378@@QAEHXZ @ 0x000FA8C0
RwInt32 type_3DC378::sub_15AF20()
{
    type_712B0_3DBC78 *var_4;

    var_4 = (type_712B0_3DBC78 *)get_unk_34C();
    if (var_4)
        return var_4->unk_204;
    return 1;
}

// match: ?sub_15AF60@type_3DC378@@QAEHXZ @ 0x0015AF60
// sp-match: ?sub_15AF60@type_3DC378@@QAEHXZ @ 0x000FA8E0
RwInt32 type_3DC378::sub_15AF60()
{
    type_712B0_3DBC78 *var_4;

    var_4 = (type_712B0_3DBC78 *)get_unk_34C();
    if (var_4)
        return var_4->unk_20C;
    return 0;
}

// match: ?vf_038@type_3DC378@@UAEXM@Z @ 0x0015AFA0
// sp-match: ?vf_038@type_3DC378@@UAEXM@Z @ 0x000FE740
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void type_3DC378::vf_038(RwReal arg_0)
{
    type_3D3548 *var_10;
    type_3D3548 *var_C;
    RwInt32 bp_8;
    type_3D3548 *bp_4;

    bp_4 = unk_29B8[0].sub_D4910();
    var_C = unk_29B8[1].sub_D4910();
    var_10 = unk_29B8[2].sub_D4910();
    bp_8 = 0;
    if ((!sub_15AF20() || bp_4) && (!sub_15AEE0() || (var_C && unk_29C4[1] == 1)) &&
        (!sub_15AF60() || (var_10 && unk_29C4[2] == 1)))
        bp_8 = 1;
    if (bp_8)
        unk_DC0 = 1;
    else
        unk_DC0 = 0;
    type_3DC048::vf_038(arg_0);
}

// match: ?vf_2F0@type_3DC378@@UAEHPAUtype_3D3548@@@Z @ 0x0015B070
// sp-match: ?vf_2F0@type_3DC378@@UAEHPAUtype_3D3548@@@Z @ 0x000FA900
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
RwInt32 type_3DC378::vf_2F0(type_3D3548 *arg_0)
{
    RwFrame *var_8;
    RpClump *l4;

    if (!vf_2E0() || !arg_0)
        return 1;
    l4 = unk_25C.unk_08;
    if (l4)
    {
        var_8 = RpClumpGetFrame(l4);
        return sub_1409C0(arg_0->vf_0CC(), RwFrameGetMatrix(var_8), vf_2E8(), 0.0f);
    }
    return 0;
}

// match: ?vf_300@type_3DC378@@UAEHH@Z @ 0x0015B0F0
// sp-match: ?vf_300@type_3DC378@@UAEHH@Z @ 0x000FA970
RwInt32 type_3DC378::vf_300(RwInt32 arg_0)
{
    type_3DC048::vf_300(arg_0);
    return 1;
}

// Functions /OPT:ICF folded into another body (config/aliases.txt), defined here for the
// authentic link (PLAN M7) with that body; the placement link takes the folded one.

// ?vf_230@type_3DC048@@UAEXXZ (folded into 0x1E41C0)
void type_3DC048::vf_230()
{
}

// Functions /OPT:ICF folded into the shared empty body (pDtor, 0x1E41C0) and
// into its caller (0x39440); defined for the authentic link (PLAN M7).

void type_3DC378::pDtor()
{
}

void type_3DC378::vf_230()
{
    pDtor();
}
