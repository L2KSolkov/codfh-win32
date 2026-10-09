// The kind-4 object (type_3CE854), derived from kind 3: its constructor,
// destructor, the overrides and its member driver sub_3F310. It follows
// the squads' unit and precedes sub_3FA10's. Its original file name is not
// in the image, so it is named for its start address.

#include "rw/ostypes.h"
#include "game/functions.h"
#include "types/AIData.h"
#include "types/type_154C0_80.h"
#include "types/type_3CE6D0.h"
#include "types/type_3CE4F0.h"
#include "types/type_3CE854.h"
#include "types/type_3D3548.h"
#include "types/type_3DBC78.h"
#include "types/type_3DF30.h"

// Its data definitions (PLAN M5), in the image's address order.
// 0x003CE850
extern const RwReal flt_3CE850 = 16.666666f;
// End of its data definitions.


// Its data (PLAN M5): literals, constants and tables where the image has them.
// match: ?flt_3CE850@@3MB @ 0x003CE850
// match: ??_7type_3CE854@@6B@ @ 0x003CE854

// match: ??0type_3CE854@@QAE@XZ @ 0x0003F120
// sp-match: ??0type_3CE854@@QAE@XZ @ 0x0002FB00

// symbol: ??_7type_3CE854@@6B@ = 0x003CE854
type_3CE854::type_3CE854()
{
}

// match: ??_Gtype_3CE854@@UAEPAXI@Z @ 0x0003F140
// match: ??1type_3CE854@@UAE@XZ @ 0x0003F160
// sp-match: ??_Gtype_3CE854@@UAEPAXI@Z @ 0x0002FBB0
// sp-match: ??1type_3CE854@@UAE@XZ @ 0x0002FB20
type_3CE854::~type_3CE854()
{
}

// match: ?vf_004@type_3CE854@@UAEXPAUtype_3DF30@@@Z @ 0x0003F180
// sp-match: ?vf_004@type_3CE854@@UAEXPAUtype_3DF30@@@Z @ 0x0002FB30
// symbol: ?vf_004@type_3CE4F0@@UAEXPAUtype_3DF30@@@Z = 0x00033580
void type_3CE854::vf_004(type_3DF30 *arg_0)
{
    unk_20 = 0;
    type_3CE4F0::vf_004(arg_0);
}

// match: ?vf_008@type_3CE854@@UAEXXZ @ 0x0003F1B0
// sp-match: ?vf_008@type_3CE854@@UAEXXZ @ 0x0002FB40
// symbol: ?vf_008@type_3CE4F0@@UAEXXZ = 0x00039440
void type_3CE854::vf_008()
{
    type_3CE4F0::vf_008();
}

// match: ?vf_00C@type_3CE854@@UAEHMPAUtype_3D410@@@Z @ 0x0003F1D0
// sp-match: ?vf_00C@type_3CE854@@UAEHMPAUtype_3D410@@@Z @ 0x00030010
RwInt32 type_3CE854::vf_00C(RwReal arg_0, type_3D410 *arg_4)
{
#ifndef CODFH_SP // shape: single player reads the AI data's field straight from the call, into loop-scoped locals (SP 0x30010)
    AIData *var_10;
    RwUInt32 ebp_C;
    RwUInt32 v8;
#endif
    type_3D3548 *var_4;

    for (var_4 = unk_08->unk_00; var_4 != 0; var_4 = var_4->vf_118()) {
#ifdef CODFH_SP // shape: single player reads the AI data's field straight from the call, into loop-scoped locals (SP 0x30010)
        RwUInt32 ebp_C;
        RwUInt32 v8;
        v8 = var_4->vf_120()->unk_574;
#else
        var_10 = var_4->vf_120();
        v8 = var_10->unk_574;
#endif
        ebp_C = unk_18;
        if (v8 == ebp_C)
            sub_3F310(static_cast<type_3DBC78 *>(var_4), arg_4);
    }
    return type_3CE6D0::vf_00C(arg_0, arg_4);
}

// match: ?vf_018@type_3CE854@@UAEHPAUtype_3D3548@@@Z @ 0x0003F260
// sp-match: ?vf_018@type_3CE854@@UAEHPAUtype_3D3548@@@Z @ 0x0002FB50
RwInt32 type_3CE854::vf_018(type_3D3548 *arg_0)
{
    AIData *stk_18;
    RwUInt32 l14;
    AIData *var_10;
    RwUInt32 ebp_C;
    RwUInt32 v8;
    type_3CE6D0 *var_4;

    if (((arg_0->unk_2C >> 0x12) & 1) == 0)
        return 0;
    var_10 = arg_0->vf_120();
    v8 = var_10->unk_574;
    var_4 = sub_3D3E0(v8);
    if (var_4 != 0) {
        if (var_4 == this)
            return 1;
        var_4->vf_014(arg_0);
    }
    l14 = ebp_C = unk_18;
    stk_18 = arg_0->vf_120();
    stk_18->unk_574 = l14;
    return 1;
}

// (AIData::set_unk_5B0, an inline single player keeps out of line: sub_3F310 calls it, SP 0x2FCAD)
// sp-match: ?set_unk_5B0@AIData@@QAEXPAURwV3d@@@Z @ 0x00011000
// match: sub_3F310 @ 0x0003F310
// sp-match: sub_3F310 @ 0x0002FBC0
void type_3CE854::sub_3F310(type_3DBC78 *arg_0, type_3D410 *arg_4)
{
    AIData *var_4;

    if ((arg_0->unk_28 & 1) != 0)
        return;
    var_4 = arg_0->vf_120();
    if (var_4->unk_51C == 0)
        return;
    unk_20 = 1;
    if (var_4->unk_58 == 0)
        var_4->sub_17AB0(0);
    if (((var_4->unk_49C >> 5) & 1) != 0)
        sub_34720(arg_0, arg_4);
    if (((var_4->unk_49C >> 4) & 1) == 0)
        return;
    switch (var_4->unk_5C) {
    default: {
        RwInt32 var_8;

        var_4->sub_22EF0(0);
        var_4->sub_29380(1);
        if (sub_12030(0x11, arg_0, (RwInt32)arg_4, 0) == 0) {
            if (sub_12030(0x10, arg_0, (RwInt32)arg_4, 0) == 0) {
                var_8 = sub_12070(arg_0, (RwInt32)arg_4);
                if (var_8 == 0) {
                    var_4->sub_29360();
                    if (sub_12030(0xE, arg_0, (RwInt32)arg_4, 0) == 0)
                        sub_12030(0xD, arg_0, (RwInt32)arg_4, 0);
                }
            }
        }
        break;
    }
    case 0x11: {
        type_154C0_80 *l14;
        type_154C0_80 *var_10;
        RwInt32 var_C;

        var_4->sub_22EF0(1);
        var_4->sub_29380(1);
        if (sub_12030(0x13, arg_0, (RwInt32)arg_4, 0) == 0) {
            if (sub_12030(0x12, arg_0, (RwInt32)arg_4, 0) == 0) {
                var_C = sub_12070(arg_0, (RwInt32)arg_4);
                if (var_C == 0) {
                    var_10 = var_4->sub_16ED0(var_4->unk_137C.sub_D4910(), 0);
                    if (var_10 != 0) {
#ifdef CODFH_SP // shape: single player calls set_unk_5B0 out of line (SP 0x2FBC0 calls SP 0x11000)
                        var_4->set_unk_5B0(&var_10->unk_14);
#else
                        var_4->unk_5B0 = var_10->unk_14;
#endif
                        var_C = sub_12030(0xF, arg_0, (RwInt32)arg_4, 0);
                        var_4->unk_137C.sub_D48D0(0);
                    }
                    if (var_C == 0) {
                        if (sub_12030(0x10, arg_0, (RwInt32)arg_4, 0) == 0) {
                            var_4->sub_29360();
                            if (sub_12030(0xE, arg_0, (RwInt32)arg_4, 0) == 0) {
                                l14 = var_4->sub_16ED0(var_4->unk_1374.sub_D4910(), 0);
                                if (l14 != 0) {
#ifdef CODFH_SP // shape: single player calls set_unk_5B0 out of line (SP 0x2FBC0 calls SP 0x11000)
                                    var_4->set_unk_5B0(&l14->unk_14);
#else
                                    var_4->unk_5B0 = l14->unk_14;
#endif
                                    var_C = sub_12030(0xF, arg_0, (RwInt32)arg_4, 0);
                                }
                                if (var_C == 0)
                                    sub_12030(0xD, arg_0, (RwInt32)arg_4, 0);
                            }
                        }
                    }
                }
            }
        }
        break;
    }
    case 0x10: {
        type_154C0_80 *var_1C;
        RwInt32 var_18;

        var_4->sub_22EF0(0);
        var_4->sub_29380(0);
        if (sub_12030(0x11, arg_0, (RwInt32)arg_4, 0) == 0) {
            var_18 = sub_12070(arg_0, (RwInt32)arg_4);
            if (var_18 == 0) {
                var_4->sub_29360();
                if (sub_12030(0xE, arg_0, (RwInt32)arg_4, 0) == 0) {
                    var_1C = var_4->sub_16ED0(var_4->unk_1374.sub_D4910(), 0);
                    if (var_1C != 0) {
#ifdef CODFH_SP // shape: single player calls set_unk_5B0 out of line (SP 0x2FBC0 calls SP 0x11000)
                        var_4->set_unk_5B0(&var_1C->unk_14);
#else
                        var_4->unk_5B0 = var_1C->unk_14;
#endif
                        var_18 = sub_12030(0xF, arg_0, (RwInt32)arg_4, 0);
                    }
                    if (var_18 == 0) {
                        if (var_18 == 0)
                            sub_12030(0xD, arg_0, (RwInt32)arg_4, 0);
                    }
                }
            }
        }
        break;
    }
    case 0x13: {
        type_154C0_80 *var_24;
        RwInt32 var_20;

        var_4->sub_29380(1);
        var_20 = sub_12070(arg_0, (RwInt32)arg_4);
        if (var_20 == 0) {
            if (sub_12030(0x11, arg_0, (RwInt32)arg_4, 0) == 0) {
                if (sub_12030(0x10, arg_0, (RwInt32)arg_4, 0) == 0) {
                    var_24 = var_4->sub_16ED0(var_4->unk_1374.sub_D4910(), 0);
                    if (var_24 != 0) {
#ifdef CODFH_SP // shape: single player calls set_unk_5B0 out of line (SP 0x2FBC0 calls SP 0x11000)
                        var_4->set_unk_5B0(&var_24->unk_14);
#else
                        var_4->unk_5B0 = var_24->unk_14;
#endif
                        var_20 = sub_12030(0xF, arg_0, (RwInt32)arg_4, 0);
                    }
                    sub_12030(0xD, arg_0, (RwInt32)arg_4, 0);
                }
            }
        }
        break;
    }
    case 0xF: {
        RwInt32 var_28;

        var_4->sub_22EF0(0);
        var_4->sub_29380(0);
        if (sub_12030(0x11, arg_0, (RwInt32)arg_4, 0) == 0) {
            var_28 = sub_12070(arg_0, (RwInt32)arg_4);
            if (var_28 == 0) {
                if (sub_12030(0x10, arg_0, (RwInt32)arg_4, 0) == 0) {
                    var_4->sub_29360();
                    sub_12030(0xD, arg_0, (RwInt32)arg_4, 0);
                }
            }
        }
        break;
    }
    case 0xE: {
        RwInt32 var_2C;

        var_4->sub_29380(1);
        if (sub_12030(0x11, arg_0, (RwInt32)arg_4, 0) == 0) {
            if (sub_12030(0x10, arg_0, (RwInt32)arg_4, 0) == 0) {
                var_2C = sub_12070(arg_0, (RwInt32)arg_4);
                if (var_2C == 0)
                    sub_12030(0xD, arg_0, (RwInt32)arg_4, 0);
            }
        }
        break;
    }
    case 0x12: {
        type_154C0_80 *var_38;
        type_154C0_80 *var_34;
        RwInt32 local_30;

        var_4->sub_29380(1);
        local_30 = sub_12070(arg_0, (RwInt32)arg_4);
        if (local_30 == 0) {
            if (sub_12030(0x11, arg_0, (RwInt32)arg_4, 0) == 0) {
                var_34 = var_4->sub_16ED0(var_4->unk_137C.sub_D4910(), 0);
                if (var_34 != 0) {
#ifdef CODFH_SP // shape: single player calls set_unk_5B0 out of line (SP 0x2FBC0 calls SP 0x11000)
                    var_4->set_unk_5B0(&var_34->unk_14);
#else
                    var_4->unk_5B0 = var_34->unk_14;
#endif
                    local_30 = sub_12030(0xF, arg_0, (RwInt32)arg_4, 0);
                    var_4->unk_137C.sub_D48D0(0);
                }
                if (local_30 == 0) {
                    if (sub_12030(0x10, arg_0, (RwInt32)arg_4, 0) == 0) {
                        var_4->sub_29360();
                        if (sub_12030(0xE, arg_0, (RwInt32)arg_4, 0) == 0) {
                            var_38 = var_4->sub_16ED0(var_4->unk_1374.sub_D4910(), 0);
                            if (var_38 != 0) {
#ifdef CODFH_SP // shape: single player calls set_unk_5B0 out of line (SP 0x2FBC0 calls SP 0x11000)
                                var_4->set_unk_5B0(&var_38->unk_14);
#else
                                var_4->unk_5B0 = var_38->unk_14;
#endif
                                local_30 = sub_12030(0xF, arg_0, (RwInt32)arg_4, 0);
                            }
                            var_4->sub_29360();
                            sub_12030(0xD, arg_0, (RwInt32)arg_4, 0);
                        }
                    }
                }
            }
        }
    }
    }
}
