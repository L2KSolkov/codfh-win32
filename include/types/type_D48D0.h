/*
 * type_D48D0: a handle to an entity, anchored at its lowest method
 * sub_D48D0 (no vtable; its constructor is inline and stores 0, its
 * destructor is empty).
 *
 * unk_00 is an id in the handle table dword_4B6A00 (8-byte entries: id,
 * entity pointer); its low word is the entry index. sub_D48D0 copies an
 * entity's id (type_3D3548::unk_384), or 0 for no entity. sub_D4910 returns
 * the entity while the table entry still holds the same id, else 0.
 */
#ifndef TYPE_D48D0_H
#define TYPE_D48D0_H

#include "rw/ostypes.h"

struct type_3D3548;

// An entity's handle id as a struct (type_3D3548::unk_384_h), which
// sub_D48D0 copies whole.
struct type_3D3548_384
{
    union
    {
        RwInt32 unk_00;
        struct
        {
            RwInt16 unk_00_w;   // the table index
            RwInt16 unk_02_w;   // the serial (dword_429268 when given)
        };
    };
};

struct type_D48D0
{
    union
    {
        RwInt32 unk_00;
        type_3D3548_384 unk_00_h;
    };

    type_D48D0()
    {
        unk_00 = 0;
    }
    // Empty; out of line it is pDtor (0x1E41C0), folded with other types'
    // empty destructors (AIData::sub_2E580's unwind funclet).
    ~type_D48D0()
    {
    }
    // Takes a bare id (AIData::sub_2E580 assigns the one a type_3DAFC8_1DDC
    // record stores); by value, so the argument is copied first. Not a copy
    // assignment, so copying a handle stays a plain copy (sub_29FC0 copies a
    // whole path with rep movsd).
    void operator=(RwInt32 arg_0)
    {
        unk_00 = arg_0;
    }
    void sub_D48D0(type_3D3548 *arg_0);
    type_3D3548 *sub_D4910();
    // Its id through a local of its own: an inline with no address and so
    // no database name, named for what it returns. Evidence: the projectile
    // generators' check of their parent, turret and barrel (sub_11F8E0)
    // tests each id through a temporary before looking the entity up.
    RwInt32 get_id()
    {
        RwInt32 r = unk_00;
        return r;
    }
};

// The handle table's entries: an id and the entity it names (dword_4B6A00).
struct type_4B6A00
{
    union
    {
        RwInt32 unk_00;
        struct
        {
            RwInt16 unk_00_w;   // as type_3D3548_384
            RwInt16 unk_02_w;
        };
    };
    struct type_3D3548 *unk_04;
};
extern type_4B6A00 dword_4B6A00[];

#endif
