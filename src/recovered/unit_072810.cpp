// The loaded script files: the tables of their contents by id, their
// relocation on load and the resolution of their imports. The file's
// original name is not recovered (M1), so it is named for its start address.

#include <string.h>

#include "rw/ostypes.h"
#include "game/functions.h"
#include "types/alfahash.h"
#include "types/alfaobject.h"
#include "types/scriptvm.h"
#include "types/type_72810.h"
#include "types/animkey.h"

// Its data definitions (PLAN M5), in the image's address order.
// 0x00428A48
RwReal flt_428A48 = 0.4f;
// 0x00428A4C
const RwChar *off_428A4C = "A";
// 0x00428A50
type_7CBD0_t flt_428A50[25] = {
    { 0.0f, 0.0f, 0.0f, 0.0f },
    { 0.0f, -1.573082f, 0.0f, 0.0f },
    { 0.0f, -8.145228f, -2.488352f, 0.0f },
    { 0.0f, -8.145231f, -2.488352f, 0.0f },
    { 3.007886f, -16.529427f, -10.187983f, 0.0f },
    { -2.914988f, -16.529427f, -10.187983f, 0.0f },
    { 0.0f, -12.771334f, -3.635333f, 0.0f },
    { 1.3f, -9.484962f, -12.298457f, 0.0f },
    { 0.0f, -9.362938f, -12.793544f, 0.0f },
    { -1.3f, -9.484962f, -12.298457f, 0.0f },
    { 0.0f, -10.748304f, -13.15517f, 0.0f },
    { -1.5f, -10.579453f, -12.486956f, 0.0f },
    { 1.5f, -10.579449f, -12.44701f, 0.0f },
    { 2.3f, -10.037543f, -11.121746f, 0.0f },
    { -2.3f, -10.03754f, -11.131828f, 0.0f },
    { -4.706317f, -17.845734f, -11.020386f, 0.0f },
    { -2.0f, -17.841347f, -13.4692f, 0.0f },
    { 2.0f, -17.841347f, -13.4692f, 0.0f },
    { 4.706317f, -17.845734f, -11.020386f, 0.0f },
    { -3.5f, -14.35103f, -10.912325f, 0.0f },
    { 3.5f, -14.35103f, -10.912325f, 0.0f },
    { 3.007886f, -16.529427f, -10.187983f, 0.0f },
    { 3.007886f, -16.529427f, -10.187983f, 0.0f },
    { -2.914988f, -16.529427f, -10.187983f, 0.0f },
    { -2.914988f, -16.529427f, -10.187983f, 0.0f },
};
// End of its data definitions.




// Globals with constructors defined here (their initializers and exit
// functions at the end of .text).
alfahash dword_449AD8;
alfahash dword_449AA4;
alfahash dword_449B0C;
alfahash dword_449A70;
// Its data (PLAN M5): literals, constants and tables where the image has them.
// match: ??_C@_01FHEEJDEE@A?$AA@ @ 0x003D316C
// match: ??_C@_0O@LIBFKHMM@god_soundbank?$AA@ @ 0x003D3170
// match: ??_C@_0BF@CLJNIHCI@god_streamsoundalias?$AA@ @ 0x003D3180
// match: ??_C@_0BG@NDFKCMIA@god_shufflesoundalias?$AA@ @ 0x003D3198
// match: ??_C@_0BH@MCIDMDNF@god_sequencesoundalias?$AA@ @ 0x003D31B0
// match: ??_C@_0BF@FGDLHEIO@god_randomsoundalias?$AA@ @ 0x003D31C8
// match: ??_C@_0BE@EKNAOMEM@god_indexsoundalias?$AA@ @ 0x003D31E0
// match: ??_C@_0BE@KAMMGCMJ@god_basicsoundalias?$AA@ @ 0x003D31F4
// match: ??_C@_0O@GIPDPDLD@god_objective?$AA@ @ 0x003D3208
// match: ??_C@_0P@ICNCIFCN@god_namedpoint?$AA@ @ 0x003D3218
// match: ??_C@_07GIOOBKCF@god_set?$AA@ @ 0x003D3228
// match: ??_C@_09MMNLGHHJ@god_clump?$AA@ @ 0x003D3230
// match: ??_C@_0L@MBENNFKN@god_unique?$AA@ @ 0x003D323C
// match: ??_C@_0L@KAAIDGJK@god_string?$AA@ @ 0x003D3248
// match: ??_C@_09MOMEHNFB@god_float?$AA@ @ 0x003D3254
// match: ??_C@_07FLBPECDP@god_int?$AA@ @ 0x003D3260
// match: .CRT$XCU+0 @ 0x00426DD8
// match: .CRT$XCU+4 @ 0x00426DDC
// match: .CRT$XCU+8 @ 0x00426DE0
// match: .CRT$XCU+12 @ 0x00426DE4
// match: ?flt_428A48@@3MA @ 0x00428A48
// match: ?off_428A4C@@3PBDB @ 0x00428A4C
// match: ?flt_428A50@@3PAUtype_7CBD0_t@@A @ 0x00428A50

// match: _$E2 @ 0x00309B30
// match: _$E3 @ 0x0030DE00
// match: _$E5 @ 0x00309B50
// match: _$E6 @ 0x0030DE10
// match: _$E8 @ 0x00309B70
// match: _$E9 @ 0x0030DE20
// match: _$E11 @ 0x00309B90
// match: _$E12 @ 0x0030DE30

RwUInt32 sub_72A50(void *arg_0);
bool sub_72A70(void *arg_0, void *arg_4);
bool sub_729C0(void *arg_0, void *arg_4);
RwUInt32 sub_72AE0(void *arg_0);
bool sub_72B00(void *arg_0, void *arg_4);
// An int it narrows: sub_6D5A0 pushes the whole dword of its performance id.
type_67620_74 *sub_72AC0(RwInt32 arg_0);

// match: ?sub_72810@@YAXXZ @ 0x00072810
// Sets the tables up.
void sub_72810()
{
    dword_449AD8.sub_67730(50, 25, sub_72A50, sub_72A70);
    dword_449AA4.sub_67730(450, 225, sub_72A50, sub_72A70);
    dword_449B0C.sub_67730(50, 25, sub_72A50, sub_729C0);
    dword_449A70.sub_67730(3000, 750, sub_72AE0, sub_72B00);
}

// match: ?sub_72890@@YAXXZ @ 0x00072890
void sub_72890()
{
    dword_449AD8.sub_67780();
    dword_449B0C.sub_67780();
    dword_449AA4.sub_67780();
    dword_449A70.sub_67780();
}

// match: ?sub_728C0@@YAXPAUtype_72900@@@Z @ 0x000728C0
// Adds arg_0 unless its id is present, and resolves its imports.
void sub_728C0(type_72900 *arg_0)
{
    if (sub_72900(arg_0->unk_04) == 0) {
        dword_449AD8.sub_67850(arg_0);
        sub_72FC0(arg_0->unk_12, arg_0->unk_14);
    }
}

// match: ?sub_72900@@YAHH@Z @ 0x00072900
RwInt32 sub_72900(RwInt32 arg_0)
{
    type_72900 var_1C;

    var_1C.unk_04 = arg_0;
    return (RwInt32)dword_449AD8.sub_67970(&var_1C);
}

// match: ?sub_72920@@YAXPAUtype_72990@@@Z @ 0x00072920
void sub_72920(type_72990 *arg_0)
{
    if (sub_72990(arg_0->unk_04) == 0) {
        dword_449B0C.sub_67850(arg_0);
        sub_72FC0(arg_0->unk_10, arg_0->unk_14);
    }
}

// match: ?sub_72960@@YAXPAUtype_72990@@@Z @ 0x00072960
void sub_72960(type_72990 *arg_0)
{
    if (sub_72990(arg_0->unk_04) != 0)
        dword_449B0C.sub_678C0(arg_0);
}

// match: ?sub_72990@@YAPAUtype_72990@@H@Z @ 0x00072990
type_72990 *sub_72990(RwInt32 arg_0)
{
    type_72990 var_20;

    var_20.unk_04 = arg_0;
    return (type_72990 *)dword_449B0C.sub_67970(&var_20);
}

// match: ?sub_729C0@@YA_NPAX0@Z @ 0x000729C0
bool sub_729C0(void *arg_0, void *arg_4)
{
    type_72990 *local_8;
    type_72990 *var_4;

    local_8 = (type_72990 *)arg_0;
    var_4 = (type_72990 *)arg_4;
    return local_8->unk_04 == var_4->unk_04;
}

// match: ?sub_729F0@@YAXPAUtype_72A30@@@Z @ 0x000729F0
void sub_729F0(type_72A30 *arg_0)
{
    if (sub_72A30(arg_0->unk_04) == 0) {
        dword_449AA4.sub_67850(arg_0);
        sub_72FC0(arg_0->unk_12, arg_0->unk_0C);
    }
}

// match: ?sub_72A30@@YAPAUtype_67620_74@@H@Z @ 0x00072A30
type_67620_74 *sub_72A30(RwInt32 arg_0)
{
    type_72A30 var_14;

    var_14.unk_04 = arg_0;
    return (type_67620_74 *)dword_449AA4.sub_67970(&var_14);
}

// match: ?sub_72A50@@YAIPAX@Z @ 0x00072A50
RwUInt32 sub_72A50(void *arg_0)
{
    type_72A30 *var_4;

    var_4 = (type_72A30 *)arg_0;
    return var_4->unk_04;
}

// match: ?sub_72A70@@YA_NPAX0@Z @ 0x00072A70
bool sub_72A70(void *arg_0, void *arg_4)
{
    type_72A30 *var_4;
    type_72A30 *local_8;

    var_4 = (type_72A30 *)arg_0;
    local_8 = (type_72A30 *)arg_4;
    return var_4->unk_04 == local_8->unk_04;
}

// match: ?sub_72AA0@@YAXPAUtype_67620_74@@@Z @ 0x00072AA0
void sub_72AA0(type_67620_74 *arg_0)
{
    dword_449A70.sub_67850(arg_0);
}

// match: ?sub_72AC0@@YAPAUtype_67620_74@@H@Z @ 0x00072AC0
type_67620_74 *sub_72AC0(RwInt32 arg_0)
{
    type_67620_74 var_14;

    var_14.unk_04 = arg_0;
    return (type_67620_74 *)dword_449A70.sub_67970(&var_14);
}

// match: ?sub_72AE0@@YAIPAX@Z @ 0x00072AE0
RwUInt32 sub_72AE0(void *arg_0)
{
    type_67620_74 *var_4;

    var_4 = (type_67620_74 *)arg_0;
    return var_4->unk_04;
}

// match: ?sub_72B00@@YA_NPAX0@Z @ 0x00072B00
bool sub_72B00(void *arg_0, void *arg_4)
{
    type_67620_74 *local_8;
    type_67620_74 *var_4;

    local_8 = (type_67620_74 *)arg_0;
    var_4 = (type_67620_74 *)arg_4;
    return local_8->unk_04 == var_4->unk_04;
}

// match: ?sub_72B30@@YAHPAD@Z @ 0x00072B30
RwInt32 sub_72B30(RwChar *arg_0)
{
    RwChar *var_4;

    var_4 = arg_0;
    strcmp(var_4, off_428A4C);
    return 4;
}

// match: ?sub_72B60@@YAXPAX0@Z @ 0x00072B60
void sub_72B60(void *arg_0, void *arg_4)
{
    if (*(RwInt32 *)arg_0 != 0)
        *(RwInt32 *)arg_0 = (RwInt32)arg_4 + *(RwInt32 *)arg_0;
}

// match: ?sub_72B80@@YAXPAD@Z @ 0x00072B80
void sub_72B80(RwChar *arg_0)
{
    sub_72B30(arg_0);
    operator delete(arg_0);
}

// match: ?sub_72BA0@@YAPAXPAD@Z @ 0x00072BA0
// Relocates the loaded file arg_0 by its kind; returns its contents.
void *sub_72BA0(RwChar *arg_0)
{
    type_72BA0 *var_4;

    sub_72B30(arg_0);
    var_4 = (type_72BA0 *)arg_0;
    switch (var_4->unk_03) {
    case 1:
        return sub_72C40(arg_0, 1);
    case 0:
        return arg_0;
    case 2:
        return sub_72D00(arg_0, 1);
    case 3:
        return sub_72D00(arg_0, 1);
    case 4:
        return sub_72F00(arg_0, 1);
    }
    return 0;
}

// match: ?sub_72C40@@YAPAUtype_67620_74@@PAD_N@Z @ 0x00072C40
type_67620_74 *sub_72C40(RwChar *arg_0, bool arg_4)
{
    type_72BA0 *varC;
    type_67620_74 *local_8;
    RwInt32 var_4;

    if (arg_4) {
        varC = (type_72BA0 *)arg_0;
        local_8 = (type_67620_74 *)(arg_0 + 4);
        if (varC->unk_02 != 0)
            return local_8;
        varC->unk_02 = 1;
    } else
        local_8 = (type_67620_74 *)arg_0;
    sub_72B60(local_8, arg_0);
    sub_72B60(&local_8->unk_10, arg_0);
    sub_72B60(&local_8->unk_08, arg_0);
    for (var_4 = 0; var_4 < local_8->unk_06; var_4++)
        sub_72B60(&local_8->unk_10[var_4], arg_0);
    return local_8;
}

// match: ?sub_72D00@@YAPAUtype_72990@@PAD_N@Z @ 0x00072D00
type_72990 *sub_72D00(RwChar *arg_0, bool arg_4)
{
    type_72BA0 *local_C;
    type_72990 *var_4;
    RwInt32 loc8;
    bool local_D;
    RwInt32 l14;

    if (arg_4) {
        local_C = (type_72BA0 *)arg_0;
        var_4 = (type_72990 *)(arg_0 + 4);
        if (local_C->unk_02 != 0)
            return var_4;
        local_C->unk_02 = 1;
    } else
        var_4 = (type_72990 *)arg_0;
    sub_72B60(var_4, var_4);
    sub_72B60(&var_4->unk_08, var_4);
    sub_72B60(&var_4->unk_18, var_4);
    sub_72B60(&var_4->unk_14, var_4);
    for (loc8 = 0; loc8 < var_4->unk_0C; loc8++) {
        sub_72B60(&var_4->unk_08[loc8].unk_04, var_4->unk_08);
        sub_72B60(&var_4->unk_08[loc8].unk_08, var_4->unk_08);
        sub_72B60(&var_4->unk_08[loc8].unk_0C, var_4->unk_08);
        if (var_4->unk_18 != 0)
            sub_72B60(&((RwInt32 *)var_4->unk_18)[loc8], (void *)var_4->unk_18);
    }
    for (loc8 = 0; loc8 < var_4->unk_0C; loc8++) {
        if ((RwInt32)var_4->unk_08[loc8].unk_00 != -1) {
            local_D = false;
            for (l14 = 0; l14 < var_4->unk_0C; l14++) {
                if ((RwInt32)var_4->unk_08[loc8].unk_00 == var_4->unk_08[l14].unk_10) {
                    var_4->unk_08[loc8].unk_00 = &var_4->unk_08[l14];
                    local_D = true;
                    break;
                }
            }
        } else
            var_4->unk_08[loc8].unk_00 = 0;
    }
    return var_4;
}

// match: ?sub_72F00@@YAPAUtype_72A30@@PAD_N@Z @ 0x00072F00
type_72A30 *sub_72F00(RwChar *arg_0, bool arg_4)
{
    type_72BA0 *local_8;
    type_72A30 *var_4;

    if (arg_4) {
        local_8 = (type_72BA0 *)arg_0;
        var_4 = (type_72A30 *)(arg_0 + 4);
        if (local_8->unk_02 != 0)
            return var_4;
        local_8->unk_02 = 1;
    } else
        var_4 = (type_72A30 *)arg_0;
    sub_72B60(var_4, var_4);
    sub_72B60(&var_4->unk_08, var_4);
    sub_72B60(&var_4->unk_0C, var_4);
    return var_4;
}

// match: ?CompareFunction@@YAHPBX0@Z @ 0x00072F80
// CompareFunction (the database's name).
RwInt32 CompareFunction(const void *arg_0, const void *arg_4)
{
    const type_4492EC *local_8;
    const type_4492EC *var_4;

    local_8 = (const type_4492EC *)arg_0;
    var_4 = (const type_4492EC *)arg_4;
    if (local_8->unk_04 < var_4->unk_04)
        return -1;
    if (local_8->unk_04 > var_4->unk_04)
        return 1;
    return 0;
}

// match: ?sub_72FC0@@YAXHPAUtype_72FC0@@@Z @ 0x00072FC0
// Resolves the arg_0 imports at arg_4 by their kinds.
void sub_72FC0(RwInt32 arg_0, type_72FC0 *arg_4)
{
    RwInt32 var_4;

    for (var_4 = 0; var_4 < arg_0; var_4++) {
        switch (arg_4[var_4].unk_08 & 0xF0000000) {
        case 0:
            sub_730D0(&arg_4[var_4]);
            break;
        case 0x10000000:
            sub_73050(&arg_4[var_4]);
            break;
        case 0x20000000:
            sub_73090(&arg_4[var_4]);
            break;
        }
    }
}

// match: ?sub_73050@@YAXPAUtype_72FC0@@@Z @ 0x00073050
void sub_73050(type_72FC0 *arg_0)
{
    type_73050 var_8 = {0, 0};

    var_8.unk_00 = arg_0->unk_00;
    var_8.unk_04 = arg_0->unk_04;
    sub_198900((type_3DF8D8_04 *)&var_8, 11, 0, 0, 0, 0);
}

// match: ?sub_73090@@YAXPAUtype_72FC0@@@Z @ 0x00073090
void sub_73090(type_72FC0 *arg_0)
{
    type_73050 var_8 = {0, 0};

    var_8.unk_00 = arg_0->unk_00;
    var_8.unk_04 = arg_0->unk_04;
    sub_198900((type_3DF8D8_04 *)&var_8, 12, 0, 0, 0, 0);
}

// match: ?sub_730D0@@YAXPAUtype_72FC0@@@Z @ 0x000730D0
void sub_730D0(type_72FC0 *arg_0)
{
    type_73050 var_8 = {0, 0};
    bool local_9;
    RwInt32 var_10;

    var_8.unk_00 = arg_0->unk_00;
    var_8.unk_04 = arg_0->unk_04;
    local_9 = false;
    for (var_10 = 0; var_10 < dword_449304; var_10++) {
        if ((dword_449308[var_10].unk_00 & 0x0FFFFFFF) == arg_0->unk_08) {
            sub_73160(&var_8, dword_449308[var_10].unk_04);
            local_9 = true;
            break;
        }
    }
}

// match: ?sub_73160@@YAXPAUtype_73050@@PBD@Z @ 0x00073160
// Registers the global arg_0 by the type name String1.
void sub_73160(type_73050 *arg_0, const RwChar *String1)
{
    if (_strcmpi(String1, "god_int") == 0)
        sub_198900((type_3DF8D8_04 *)arg_0, 1, 0, 0, 0, 0);
    else if (_strcmpi(String1, "god_float") == 0)
        sub_198900((type_3DF8D8_04 *)arg_0, 1, 0, 0, 0, 0);
    else if (_strcmpi(String1, "god_string") == 0)
        sub_198900((type_3DF8D8_04 *)arg_0, 2, 0, 0, 0, 0);
    else if (_strcmpi(String1, "god_unique") == 0)
        sub_198900((type_3DF8D8_04 *)arg_0, 1, 0, 0, 0, 0);
    else if (_strcmpi(String1, "god_clump") == 0)
        sub_198900((type_3DF8D8_04 *)arg_0, 3, 0, 0, 0, 0);
    else if (_strcmpi(String1, "god_set") == 0)
        sub_198900((type_3DF8D8_04 *)arg_0, 0x2E, 0, 0, 0, 1);
    else if (_strcmpi(String1, "god_namedpoint") == 0)
        sub_198900((type_3DF8D8_04 *)arg_0, 0x2D, 0, 0, 0, 0);
    else if (_strcmpi(String1, "god_objective") == 0) {
    } else if (_strcmpi(String1, "god_basicsoundalias") == 0
               || _strcmpi(String1, "god_indexsoundalias") == 0
               || _strcmpi(String1, "god_randomsoundalias") == 0
               || _strcmpi(String1, "god_sequencesoundalias") == 0
               || _strcmpi(String1, "god_shufflesoundalias") == 0
               || _strcmpi(String1, "god_streamsoundalias") == 0) {
    } else if (_strcmpi(String1, "god_soundbank") == 0) {
    }
}
