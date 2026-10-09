/*
 * codfh-match: RenderWare Audio's parameter types (rwaparam.h in the
 * library's PS2 header, docs/reference/rwacore_ps2.h): parameter values
 * from free lists by size (0x42EF98), the types in the symbol table
 * (0x516C50), their creation (plain, pointer, reference and derived),
 * destruction and the built-in type table (0x42EFC0), and the module open
 * and close.
 */
#include "rwa.h"
#include "rwaint.h"



#define rwaPARAMTYPE_POINTER    0x1000
#define rwaPARAMTYPE_REFERENCE  0x2000
#define rwaPARAMTYPE_DERIVED    0x4000

#define rwaNOVALUEFREELISTS     5

static RwUInt32 dword_506F58;       /* closing */
static RwUInt8 unk_506F64[0x24];    /* parameter types */
static RwUInt32 dword_506FD0;

extern rwaValueFreeList unk_42EF98[rwaNOVALUEFREELISTS];
extern _rwaParamTypeDef unk_42EFC0[];  /* the built-in types */
extern RwUInt8 unk_516C50[];        /* the symbol table */

extern RwUInt32 sub_23E440(RwUInt32 type);
extern void *sub_243670(void *freeList, RwUInt32 hint);
extern void sub_2437A0(void *freeList, void *item);
extern void sub_2438E0(void *freeList);
extern RwBool sub_243950(RwUInt32 size, RwUInt32 count, RwUInt32 align, RwInt32 a,
                         void *freeList, RwUInt32 hint);
extern void sub_244630(void *table);
extern RwaSymbolTable *sub_244650(RwaSymbolTable *table, RwaParamType *type);
extern RwaSymbolTable *sub_244690(RwaSymbolTable *table, RwaParamType *type);
extern RwaParamType *sub_2446D0(void *table, const RwaUUID *uuid);
extern RwaParamType *sub_244720(void *table, RwaParamType *parent);
extern RwaParamType *sub_244750(void *table, RwaParamType *parent);
extern RwaUniqueID *sub_240B40(RwaUniqueID *uniqueID);
extern RwaUniqueID *sub_240BF0(RwaUniqueID *uniqueID, const RwChar *name);
extern RwaUniqueID *sub_240C10(RwaUniqueID *uniqueID, const RwaUUID *uuid);
extern RwaUniqueID *sub_240C30(RwaUniqueID *uniqueID);
extern void *memcpy(void *dst, const void *src, RwUInt32 size);

// Its data (PLAN M5): literals, constants and tables where the image has them.
// match: _unk_3ED4AC @ 0x003ED4AC
// match: _unk_3ED4BC @ 0x003ED4BC
// match: _unk_3ED4CC @ 0x003ED4CC
// match: _unk_3ED4DC @ 0x003ED4DC
// match: _unk_3ED4EC @ 0x003ED4EC
// match: _unk_3ED4FC @ 0x003ED4FC
// match: _unk_3ED50C @ 0x003ED50C
// match: _unk_3ED51C @ 0x003ED51C
// match: _unk_3ED52C @ 0x003ED52C
// match: _unk_3ED53C @ 0x003ED53C
// match: _unk_3ED54C @ 0x003ED54C
// match: _unk_3ED55C @ 0x003ED55C
// match: _unk_3ED56C @ 0x003ED56C
// match: _unk_3ED57C @ 0x003ED57C
// match: _unk_3ED58C @ 0x003ED58C
// match: _unk_3ED59C @ 0x003ED59C

// What its data definitions name (the listener's object definition, unit_2417C0's,
// holds its parameter entries' values).
extern void *unk_42EE18[96];
extern RwUInt8 unk_506C68[];
extern RwUInt8 unk_506C8C[];
extern RwUInt8 unk_506CB0[];
extern RwUInt8 unk_506CB8[];
extern RwUInt8 unk_506CDC[];
extern RwUInt8 unk_506CE4[];
extern RwUInt8 unk_506CF0[];
extern RwUInt8 unk_506D18[];
extern RwUInt8 unk_506D40[];
extern RwUInt8 unk_506D68[];
extern RwUInt8 unk_506D90[];
extern RwUInt8 unk_506DB8[];
extern RwUInt8 unk_506DE0[];
extern RwUInt8 unk_506E08[];
extern RwUInt8 unk_506E30[];
extern RwUInt8 unk_506E58[];
extern RwUInt8 unk_506E80[];
extern RwUInt8 unk_506EA8[];
extern RwUInt8 unk_506ED0[];
extern RwUInt8 unk_506EF8[];
extern RwUInt8 unk_506F20[];
extern RwUInt8 unk_506F48[];
extern RwUInt8 unk_506F50[];
extern RwUInt8 unk_506F5C[];
extern RwUInt8 unk_506F88[];
extern RwUInt8 unk_506FAC[];
// Its data definitions (PLAN M5), in the image's address order.
// 0x003ED4AC
const RwaUUID unk_3ED4AC = { 0x6D23AD3F, 0x339E, 0x495E, { 0x91, 0x8D, 0x33, 0x13, 0xA8, 0x2D, 0xE3, 0xF7 } };
// 0x003ED4BC
const RwaUUID unk_3ED4BC = { 0xFA38E91C, 0x41CD, 0x496A, { 0xB3, 0xCB, 0xCF, 0x27, 0xF1, 0x37, 0x6C, 0xE7 } };
// 0x003ED4CC
const RwaUUID unk_3ED4CC = { 0x66ACDEEE, 0xD01E, 0x41CA, { 0x8B, 0x68, 0x39, 0x98, 0xAB, 0x6C, 0x0E, 0x5C } };
// 0x003ED4DC
const RwaUUID unk_3ED4DC = { 0x1FA3D753, 0xD63C, 0x4CD9, { 0xA5, 0x54, 0x06, 0xFE, 0x6C, 0x9A, 0xE9, 0x72 } };
// 0x003ED4EC
const RwaUUID unk_3ED4EC = { 0x2BB5DC2F, 0xBC08, 0x4CAF, { 0xB9, 0xE6, 0x4D, 0x62, 0xEE, 0x2F, 0xB3, 0xBE } };
// 0x003ED4FC
const RwaUUID unk_3ED4FC = { 0xB587511A, 0x9B95, 0x46BF, { 0xAD, 0x19, 0x5F, 0xFA, 0x22, 0x80, 0x6E, 0x05 } };
// 0x003ED50C
const RwaUUID unk_3ED50C = { 0x519BECE7, 0x4982, 0x42D5, { 0x96, 0x87, 0xE4, 0x8C, 0xC4, 0x5C, 0x51, 0x5F } };
// 0x003ED51C
const RwaUUID unk_3ED51C = { 0xA4BE9E52, 0x0CE2, 0x4C01, { 0x83, 0x94, 0xFC, 0xB4, 0x97, 0x7A, 0x6E, 0x5D } };
// 0x003ED52C
const RwaUUID unk_3ED52C = { 0x5195A8A5, 0x91DD, 0x4DB3, { 0xBA, 0x75, 0x97, 0xA8, 0xFC, 0xEC, 0x73, 0x79 } };
// 0x003ED53C
const RwaUUID unk_3ED53C = { 0x8427D6BE, 0xF551, 0x4F5C, { 0x9B, 0xCC, 0x2C, 0x3F, 0x99, 0x9F, 0xC2, 0x87 } };
// 0x003ED54C
const RwaUUID unk_3ED54C = { 0x808B62EF, 0xE2B6, 0x496A, { 0xBD, 0x7A, 0xA3, 0x83, 0x33, 0xF2, 0xF3, 0x06 } };
// 0x003ED55C
const RwaUUID unk_3ED55C = { 0x0DD9C91A, 0x1A92, 0x45C9, { 0xA6, 0xA6, 0x26, 0x94, 0xDE, 0xC7, 0xB3, 0x72 } };
// 0x003ED56C
const RwaUUID unk_3ED56C = { 0x2B2E61B9, 0xF455, 0x4D35, { 0x96, 0xD2, 0x49, 0xF9, 0x5B, 0xB4, 0x55, 0xE9 } };
// 0x003ED57C
const RwaUUID unk_3ED57C = { 0x0BE256AB, 0xBCBD, 0x4720, { 0x88, 0x66, 0x7C, 0x70, 0x30, 0x29, 0x48, 0xF4 } };
// 0x003ED58C
const RwaUUID unk_3ED58C = { 0xDF239C5A, 0x86D6, 0x4248, { 0xAA, 0x7A, 0xCB, 0x95, 0xBC, 0x1F, 0xCA, 0x43 } };
// 0x003ED59C
const RwaUUID unk_3ED59C = { 0xDF239C5A, 0x86D6, 0x4248, { 0xAA, 0x7A, 0xCB, 0x95, 0xBC, 0x1F, 0xCA, 0x43 } };
// 0x003ED5AC
const RwaUUID unk_3ED5AC = { 0x7BF22C5A, 0xBF59, 0x456C, { 0x9E, 0x15, 0x0A, 0xBD, 0xB7, 0xE3, 0x49, 0xE1 } };
// 0x0042EF98
rwaValueFreeList unk_42EF98[5] = {
    { &unk_506CB8, 0x1 },
    { &unk_506FAC, 0x2 },
    { &unk_506C68, 0x4 },
    { &unk_506F88, 0x8 },
    { &unk_506C8C, 0x10 },
};
// 0x0042EFC0
_rwaParamTypeDef unk_42EFC0[15] = {
    { 0, 0x400, 0x4, &unk_42EE18[76], &unk_3ED52C, 0, &unk_506CF0, &unk_42EE18[76] },
    { 0, 0x2, 0x1, &unk_42EE18[80], &unk_3ED4BC, 0, &unk_506D18, &unk_42EE18[80] },
    { 0, 0x1, 0x1, &unk_42EE18[81], &unk_3ED4AC, 0, &unk_506D40, &unk_42EE18[81] },
    { 0, 0x8, 0x2, &unk_42EE18[82], &unk_3ED4DC, 0, &unk_506D68, &unk_42EE18[82] },
    { 0, 0x4, 0x2, &unk_42EE18[83], &unk_3ED4CC, 0, &unk_506D90, &unk_42EE18[83] },
    { 0, 0x20, 0x4, &unk_42EE18[84], &unk_3ED4FC, 0, &unk_506DB8, &unk_42EE18[84] },
    { 0, 0x10, 0x4, &unk_42EE18[86], &unk_3ED4EC, 0, &unk_506DE0, &unk_42EE18[86] },
    { 0, 0x80, 0x8, &unk_42EE18[88], &unk_3ED51C, 0, &unk_506E08, &unk_42EE18[88] },
    { 0, 0x40, 0x8, &unk_42EE18[92], &unk_3ED50C, 0, &unk_506E30, &unk_42EE18[92] },
    { 0, 0x2000, 0x8, 0, &unk_3ED53C, &unk_3ED4AC, &unk_506E58, &unk_506CDC },
    { 0, 0x2000, 0xC, 0, &unk_3ED54C, &unk_3ED4AC, &unk_506E80, &unk_506CB0 },
    { 0, 0x4000, 0x0, &unk_42EE18[78], &unk_3ED55C, &unk_3ED4FC, &unk_506EA8, &unk_506F50 },
    { 0, 0x1000, 0x0, 0, &unk_3ED56C, 0, &unk_506ED0, &unk_506F48 },
    { 0, 0x2000, 0x40, 0, &unk_3ED57C, &unk_3ED56C, &unk_506EF8, &unk_506CE4 },
    { 0, 0x2000, 0x5C, 0, &unk_3ED58C, &unk_3ED56C, &unk_506F20, &unk_506F5C },
};
// 0x00506C68
RwUInt8 unk_506C68[36];
// 0x00506C8C
RwUInt8 unk_506C8C[36];
// 0x00506CB0
RwUInt8 unk_506CB0[8];
// 0x00506CB8
RwUInt8 unk_506CB8[36];
// 0x00506CDC
RwUInt8 unk_506CDC[8];
// 0x00506CE4
RwUInt8 unk_506CE4[12];
// 0x00506CF0
RwUInt8 unk_506CF0[40];
// 0x00506D18
RwUInt8 unk_506D18[40];
// 0x00506D40
RwUInt8 unk_506D40[40];
// 0x00506D68
RwUInt8 unk_506D68[40];
// 0x00506D90
RwUInt8 unk_506D90[40];
// 0x00506DB8
RwUInt8 unk_506DB8[40];
// 0x00506DE0
RwUInt8 unk_506DE0[40];
// 0x00506E08
RwUInt8 unk_506E08[40];
// 0x00506E30
RwUInt8 unk_506E30[40];
// 0x00506E58
RwUInt8 unk_506E58[40];
// 0x00506E80
RwUInt8 unk_506E80[40];
// 0x00506EA8
RwUInt8 unk_506EA8[40];
// 0x00506ED0
RwUInt8 unk_506ED0[40];
// 0x00506EF8
RwUInt8 unk_506EF8[40];
// 0x00506F20
RwUInt8 unk_506F20[40];
// 0x00506F48
RwUInt8 unk_506F48[8];
// 0x00506F50
RwUInt8 unk_506F50[8];
// 0x00506F5C
RwUInt8 unk_506F5C[8];
// 0x00506F88
RwUInt8 unk_506F88[36];
// 0x00506FAC
RwUInt8 unk_506FAC[36];
// End of its data definitions.

// match: _unk_3ED5AC @ 0x003ED5AC


// match: _unk_42EF98 @ 0x0042EF98


// match: _unk_42EFC0 @ 0x0042EFC0

// match: _sub_2418E0 @ 0x002418E0
// sp-match: _sub_2418E0 @ 0x00155A20

void *
sub_2418E0(RwUInt32 type)
{
    RwUInt32    size = sub_23E440(type);
    RwUInt32    i;

    for (i = 0; i < rwaNOVALUEFREELISTS; i++)
    {
        if (unk_42EF98[i].size == size)
        {
            return sub_243670(unk_42EF98[i].freeList, rwaMEMHINTDUR_EVENT | rwaID_803);
        }
    }

    return NULL;
}

// match: _sub_241920 @ 0x00241920
// sp-match: _sub_241920 @ 0x00155A60
void
sub_241920(void *value, RwUInt32 type)
{
    RwUInt32    size = sub_23E440(type);
    RwUInt32    i;

    for (i = 0; i < rwaNOVALUEFREELISTS; i++)
    {
        if (unk_42EF98[i].size == size)
        {
            sub_2437A0(unk_42EF98[i].freeList, value);

            return;
        }
    }
}

// match: _sub_241960 @ 0x00241960
// sp-match: _sub_241960 @ 0x00155AA0
static void
sub_241960(RwaParamType *paramType)
{
    if (!(paramType->flags & 1))
    {
        sub_2437A0(unk_506F64, paramType);
    }
}

// match: _sub_241980 @ 0x00241980
// sp-match: _sub_241980 @ 0x00155AC0
static void
sub_241980(RwaParamType *paramType)
{
    if (!(paramType->flags & 2))
    {
        if (paramType->rangeMin)
        {
            sub_241920(paramType->rangeMin, paramType->type);
        }

        if (paramType->rangeMax)
        {
            sub_241920(paramType->rangeMax, paramType->type);
        }
    }
}

// match: _sub_2419B0 @ 0x002419B0
// sp-match: _sub_2419B0 @ 0x00155AF0
void
sub_2419B0(RwaParamType *paramType, RwBool recurse)
{
    RwaParamType   *child;

    while ((child = sub_244720(unk_516C50, paramType)) != NULL)
    {
        if (recurse == TRUE)
        {
            sub_2419B0(child, recurse);
        }
    }

    sub_241960(paramType);
    sub_244690((RwaSymbolTable *)unk_516C50, paramType);
    sub_240C30(&paramType->uniqueID);
    sub_241980(paramType);
}

// match: _sub_241A20 @ 0x00241A20
// sp-match: _sub_241A20 @ 0x00155B60
void
sub_241A20(void)
{
    RwaParamType       *paramType;
    RwUInt32            i;

    dword_506F58 = 1;

    while ((paramType = sub_244750(unk_516C50, NULL)) != NULL)
    {
        sub_2419B0(paramType, TRUE);
    }

    sub_244630(unk_516C50);
    sub_2438E0(unk_506F64);

    for (i = rwaNOVALUEFREELISTS; i > 0; i--)
    {
        sub_2438E0(unk_42EF98[i - 1].freeList);
    }

    dword_506FD0 = 0;
}

// match: __rwaParamTypeHandleRefreshType @ 0x00241AB0
// sp-match: __rwaParamTypeHandleRefreshType @ 0x00155BF0
RwaParamTypeHandle *
_rwaParamTypeHandleRefreshType(RwaParamTypeHandle *handle)
{
    if (handle->isUUID == TRUE)
    {
        RwaParamType   *paramType = sub_2446D0(unk_516C50, handle->u.paramTypeUUID);

        if (!paramType)
        {
            return NULL;
        }

        handle->u.paramType = paramType;
        handle->isUUID = FALSE;
    }

    return handle;
}

// match: _sub_241AE0 @ 0x00241AE0
// sp-match: _sub_241AE0 @ 0x00155C20
RwaParamType *
sub_241AE0(RwUInt32 type, const void *rangeMin, const void *rangeMax, RwaParamType *paramType,
           RwUInt8 *rangeStorage)
{
    RwUInt32    size = sub_23E440(type);

    if (!paramType)
    {
        paramType = (RwaParamType *)sub_243670(unk_506F64, rwaMEMHINTDUR_EVENT | rwaID_803);
        paramType->flags = 0;
    }
    else
    {
        paramType->flags = 1;
    }

    paramType->rangeMin = NULL;
    paramType->rangeMax = NULL;

    if (rangeStorage)
    {
        paramType->flags |= 2;

        if (rangeMin)
        {
            paramType->rangeMin = rangeStorage;
            if (rangeMax)
            {
                paramType->rangeMax = rangeStorage + sub_23E440(type);
            }
        }
        else if (rangeMax)
        {
            paramType->rangeMax = rangeStorage;
        }
    }
    else
    {
        if (rangeMin)
        {
            paramType->rangeMin = sub_2418E0(type);
            if (!paramType->rangeMin)
            {
                sub_241980(paramType);
            }
        }

        if (rangeMax)
        {
            paramType->rangeMax = sub_2418E0(type);
            if (!paramType->rangeMax)
            {
                sub_241960(paramType);
                sub_241980(paramType);
            }
        }
    }

    if (rangeMin)
    {
        memcpy(paramType->rangeMin, rangeMin, size);
    }

    if (rangeMax)
    {
        memcpy(paramType->rangeMax, rangeMax, size);
    }

    sub_240B40(&paramType->uniqueID);
    paramType->type = type;
    paramType->paramType = NULL;
    sub_244650((RwaSymbolTable *)unk_516C50, paramType);

    return paramType;
}

// match: _sub_241C10 @ 0x00241C10
// sp-match: _sub_241C10 @ 0x00155D50
RwaParamType *
sub_241C10(RwUInt32 type, RwaParamType *parent, void *max, RwaParamType *paramType,
           RwUInt8 *rangeStorage)
{
    void           *rangeMin = NULL;
    void           *rangeMax = max;
    RwaParamType   *result;

    result = sub_241AE0(rwaPARAMTYPE_REFERENCE, &rangeMin, &rangeMax, paramType, rangeStorage);
    if (!result)
    {
        return NULL;
    }

    if (parent)
    {
        type = parent->type | rwaPARAMTYPE_DERIVED;
        result->paramType = parent;
    }

    result->type |= type;

    return result;
}

// match: _RwaParamTypeCreatePointer @ 0x00241C80
// sp-match: _RwaParamTypeCreatePointer @ 0x00155DC0
RwaParamType *
RwaParamTypeCreatePointer(RwaParamType *parent, RwaParamType *paramType, RwUInt8 *rangeStorage)
{
    RwaParamType   *result;

    if (parent)
    {
        result = sub_241AE0(rwaPARAMTYPE_POINTER, parent->rangeMin, parent->rangeMax, paramType,
                            rangeStorage);
        if (!result)
        {
            return NULL;
        }

        result->paramType = parent;

        return result;
    }

    return sub_241AE0(rwaPARAMTYPE_POINTER, NULL, NULL, paramType, rangeStorage);
}

// match: _sub_241CD0 @ 0x00241CD0
// sp-match: _sub_241CD0 @ 0x00155E10
RwaParamType *
sub_241CD0(void *rangeMin, void *rangeMax, RwaParamType *parent, RwaParamType *paramType,
           RwUInt8 *rangeStorage)
{
    RwUInt32        type = parent->type;
    RwaParamType   *result;

    while (!rangeMin && paramType)
    {
        rangeMin = parent->rangeMin;
        paramType = parent->paramType;
    }

    while (!rangeMax && paramType)
    {
        rangeMax = parent->rangeMax;
        paramType = parent->paramType;
    }

    result = sub_241AE0(type, rangeMin, rangeMax, paramType, rangeStorage);
    if (!result)
    {
        return NULL;
    }

    result->paramType = parent;
    result->type |= rwaPARAMTYPE_DERIVED;

    return result;
}

// match: _sub_241D40 @ 0x00241D40
// sp-match: _sub_241D40 @ 0x00155E80
_rwaParamTypeDef *
sub_241D40(_rwaParamTypeDef *defs, RwUInt32 count)
{
    RwUInt32        i;
    RwaParamType   *paramType;

    for (i = 0; i < count; i++)
    {
        _rwaParamTypeDef   *def = &defs[i];

        if (def->type == rwaPARAMTYPE_REFERENCE)
        {
            RwaParamType   *parent = sub_2446D0(unk_516C50, def->sourceTypeUUID);

            paramType = sub_241C10(rwaPARAMTYPE_REFERENCE, parent, (void *)def->size,
                                   def->paramType, def->rangeStorage);
        }
        else if (def->type == rwaPARAMTYPE_DERIVED)
        {
            RwaParamType   *parent = sub_2446D0(unk_516C50, def->sourceTypeUUID);
            RwUInt32        size = sub_23E440(parent->type);

            paramType = sub_241CD0(def->range, def->range + size, parent, def->paramType,
                                   def->rangeStorage);
        }
        else if (def->type == rwaPARAMTYPE_POINTER)
        {
            paramType = RwaParamTypeCreatePointer(def->sourceTypeUUID ?
                                                  sub_2446D0(unk_516C50, def->sourceTypeUUID) :
                                                  NULL,
                                                  def->paramType, def->rangeStorage);
        }
        else
        {
            paramType = sub_241AE0(def->type, def->range, def->range + def->size,
                                   def->paramType, def->rangeStorage);
        }

        if (!paramType)
        {
            while (i > 0)
            {
                sub_2419B0(sub_2446D0(unk_516C50, defs[i - 1].typeUUID), TRUE);
                i--;
            }

            return NULL;
        }

        sub_240C10(&paramType->uniqueID, def->typeUUID);
        sub_240BF0(&paramType->uniqueID, def->name);
    }

    return defs;
}

// match: _sub_241E90 @ 0x00241E90
// sp-match: _sub_241E90 @ 0x00155FD0
RwBool
sub_241E90(void)
{
    return sub_241D40(unk_42EFC0, 15) != NULL;
}

// match: _sub_241EB0 @ 0x00241EB0
// sp-match: _sub_241EB0 @ 0x00155FF0
RwBool
sub_241EB0(void)
{
    RwUInt32    i;

    sub_244630(unk_516C50);

    for (i = 0; i < rwaNOVALUEFREELISTS; i++)
    {
        if (!sub_243950(unk_42EF98[i].size, 8, 8, 0, unk_42EF98[i].freeList,
                        rwaMEMHINTDUR_GLOBAL | rwaID_803))
        {
            while (i > 0)
            {
                sub_2438E0(unk_42EF98[i - 1].freeList);
                i--;
            }
        }
    }

    dword_506F58 = 0;
    dword_506FD0 = 1;

    if (sub_243950(sizeof(RwaParamType), 0x10, 8, 0, unk_506F64,
                   rwaMEMHINTDUR_GLOBAL | rwaID_803))
    {
        if (sub_241E90() == TRUE)
        {
            return TRUE;
        }

        sub_2438E0(unk_506F64);
    }

    while (i > 0)
    {
        sub_2438E0(unk_42EF98[i - 1].freeList);
        i--;
    }

    dword_506FD0 = 0;

    return FALSE;
}
