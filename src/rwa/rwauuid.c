/*
 * codfh-match: RenderWare Audio's UUIDs and unique IDs (rwauuid.h in the
 * library's PS2 header, docs/reference/rwacore_ps2.h): UUID comparison and
 * byte swapping, the free list of copied UUIDs (0x506B48) and the unique
 * ID's UUID and name.
 */
#include "rwa.h"
#include "rwaint.h"

static RwUInt8 unk_506B48[0x24];    /* copied UUIDs */
static RwUInt32 dword_506B6C;

extern void sub_241FD0(RwUInt8 **cursor, const void *src, RwInt32 size);
extern void sub_2421B0(void *data);
extern void sub_2437A0(void *freeList, void *item);
extern void sub_2438E0(void *freeList);
extern RwBool sub_243950(RwUInt32 size, RwUInt32 count, RwUInt32 align, RwInt32 a,
                         void *freeList, RwUInt32 hint);
extern RwInt32 memcmp(const void *a, const void *b, RwUInt32 size);
extern void *memcpy(void *dst, const void *src, RwUInt32 size);

// match: _RwaUUIDCompare @ 0x00240980
RwInt32
RwaUUIDCompare(const RwaUUID *uuid1, const RwaUUID *uuid2)
{
    if (uuid1 == uuid2)
    {
        return 0;
    }

    return memcmp(uuid1, uuid2, sizeof(RwaUUID));
}

// match: _sub_2409B0 @ 0x002409B0
void
sub_2409B0(RwaUUID *uuid)
{
    RwUInt8    *cursor;
    RwaUUID     swapped;

    cursor = (RwUInt8 *)&swapped;
    sub_241FD0(&cursor, &uuid->time_low, sizeof(uuid->time_low));
    sub_241FD0(&cursor, &uuid->time_mid, sizeof(uuid->time_mid));
    sub_241FD0(&cursor, &uuid->time_hi_and_version, sizeof(uuid->time_hi_and_version));
    memcpy(cursor, uuid->node, sizeof(uuid->node));

    *uuid = swapped;
}

// match: _sub_240A30 @ 0x00240A30
void
sub_240A30(RwaV3d *vector)
{
    RwUInt8    *cursor;
    RwaV3d      swapped;

    cursor = (RwUInt8 *)&swapped;
    sub_241FD0(&cursor, &vector->x, sizeof(vector->x));
    sub_241FD0(&cursor, &vector->y, sizeof(vector->y));
    sub_241FD0(&cursor, &vector->z, sizeof(vector->z));

    *vector = swapped;
}

// match: _sub_240A90 @ 0x00240A90
RwBool
sub_240A90(void)
{
    if (sub_243950(sizeof(RwaUUID), 8, 8, 0, unk_506B48, rwaMEMHINTDUR_GLOBAL | rwaID_802))
    {
        dword_506B6C = TRUE;

        return TRUE;
    }

    return FALSE;
}

// match: _sub_240AC0 @ 0x00240AC0
void
sub_240AC0(void)
{
    sub_2438E0(unk_506B48);
    dword_506B6C = 0;
}

// match: _sub_240AE0 @ 0x00240AE0
RwaUniqueID *
sub_240AE0(RwaUniqueID *uniqueID)
{
    if (uniqueID->name && (uniqueID->flags & rwaUNIQUEIDFLAGS_COPIEDNAME))
    {
        sub_2421B0((void *)uniqueID->name);
        uniqueID->flags &= ~rwaUNIQUEIDFLAGS_COPIEDNAME;
    }

    return uniqueID;
}

// match: _sub_240B10 @ 0x00240B10
RwaUniqueID *
sub_240B10(RwaUniqueID *uniqueID)
{
    if (uniqueID->uuid && (uniqueID->flags & rwaUNIQUEIDFLAGS_COPIEDUUID))
    {
        sub_2437A0(unk_506B48, (void *)uniqueID->uuid);
        uniqueID->flags &= ~rwaUNIQUEIDFLAGS_COPIEDUUID;
    }

    return uniqueID;
}

// match: _sub_240B40 @ 0x00240B40
void
sub_240B40(RwaUniqueID *uniqueID)
{
    uniqueID->flags = 0;
    uniqueID->name = NULL;
    uniqueID->uuid = NULL;
}

// match: _sub_240B50 @ 0x00240B50
const RwaUUID *
sub_240B50(const RwaUUID *uuid, RwaUUID *copy, RwBool swap)
{
    *copy = *uuid;

    if (swap)
    {
        sub_2409B0(copy);
    }

    return uuid;
}

/* The library's case folds: the second operand's test differs from the
 * first's (characters up to 'A' are folded too). */
#define rwaFoldCase1(_c)                                                    \
    ((((_c) >= 'a' || (_c) >= 'A') && ((_c) <= 'z' || (_c) <= 'Z')) ?       \
     (RwChar)((_c) & 0xDF) : (_c))

#define rwaFoldCase2(_c)                                                    \
    ((((_c) >= 'a' || (_c) <= 'A') && ((_c) <= 'z' || (_c) <= 'Z')) ?       \
     (RwChar)((_c) & 0xDF) : (_c))

// match: _sub_240B90 @ 0x00240B90
RwInt32
sub_240B90(const RwChar *string1, const RwChar *string2, RwUInt32 count)
{
    do
    {
        RwChar  c1 = rwaFoldCase1(*string1);
        RwChar  c2 = rwaFoldCase2(*string2);

        if (c1 != c2)
        {
            return c1 - c2;
        }

        string1++;
        string2++;
    }
    while (--count);

    return 0;
}

// match: _sub_240BF0 @ 0x00240BF0
RwaUniqueID *
sub_240BF0(RwaUniqueID *uniqueID, const RwChar *name)
{
    sub_240AE0(uniqueID);
    uniqueID->name = name;
    uniqueID->flags &= ~rwaUNIQUEIDFLAGS_COPIEDNAME;

    return uniqueID;
}

// match: _sub_240C10 @ 0x00240C10
RwaUniqueID *
sub_240C10(RwaUniqueID *uniqueID, const RwaUUID *uuid)
{
    sub_240B10(uniqueID);
    uniqueID->uuid = uuid;
    uniqueID->flags &= ~rwaUNIQUEIDFLAGS_COPIEDUUID;

    return uniqueID;
}

// match: _sub_240C30 @ 0x00240C30
RwaUniqueID *
sub_240C30(RwaUniqueID *uniqueID)
{
    sub_240B10(uniqueID);
    sub_240AE0(uniqueID);

    return uniqueID;
}
