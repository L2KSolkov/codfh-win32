/*
 * type_427408: one 12-byte record of the handler table unk_427408 in .data:
 * 36 records numbered 0-35, 0x427408-0x4275B8. A data-only type with no
 * vtable, constructor or methods, so it is anchored at its first instance.
 *
 *   +0x00 unk_00  record number: 0, 1, 2, ... in table order
 *   +0x04 unk_04  handler called by sub_12030 with three arguments
 *   +0x08 unk_08  handler called by sub_12070 with two arguments
 *
 * Every handler's first argument is the entity (type_3DBC78 *: handlers call
 * its vf_2DC). A first
 * handler's third argument is a pointer each handler interprets for itself
 * (sub_13900 reads an RwV3d through it). The second argument's type is not
 * established beyond its width.
 */
#ifndef TYPE_427408_H
#define TYPE_427408_H

#include "rw/ostypes.h"
#include "types/type_3DBC78.h"

struct type_427408
{
    RwInt32 unk_00;
    RwInt32 (*unk_04)(type_3DBC78 *, RwInt32, void *);
    RwInt32 (*unk_08)(type_3DBC78 *, RwInt32);
};
typedef RwChar type_427408_size_check[sizeof(type_427408) == 0xC ? 1 : -1];

extern type_427408 unk_427408[];

#endif
