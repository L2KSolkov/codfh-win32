/*
 * The shrimps (unit_17CA70): each ShrimpTrigger's type_17CC40 keeps a
 * list of shrimps (type_17CA70_node, from the pool dword_4E7244) that swim
 * along its spline path and are drawn as clones of its model's first atomic;
 * the type_17CC40s are linked from dword_4E7238. The trigger's spawn is a
 * bare entity of the class type_3DDE70 (dword_4E723C), made by sub_17D330.
 */
#ifndef TYPE_3DDE70_H
#define TYPE_3DDE70_H

#include "rw/ostypes.h"
#include "types/type_3D3548.h"
#include "types/alfasched.h"

class ShrimpTrigger;

// A shrimp (16 bytes): how far along the path, its speed (per second, a
// fraction of the path), and its links.
struct type_17CA70_node
{
    RwReal unk_00;
    RwReal unk_04;
    type_17CA70_node *unk_08;
    type_17CA70_node *unk_0C;
};

// The shrimp trigger's spawn: an entity class of its own with its vtable
// off_3DDE70, which overrides only its destructor.
struct type_3DDE70 : type_3D3548
{
    RwUInt8 unk_3A8[0x8];

    type_3DDE70(ShrimpTrigger *arg_0);
    // Its destructor is implicit (it does not reset the vtable pointer;
    // sub_17CB10).
    // The placement pair it is built in entity memory with (sub_6CCF0 and
    // the empty sub_19A750), and its plain operator delete for its deleting
    // destructor (folded into sub_19A750 too).
    static void *operator new(RwUInt32 arg_0, void *arg_4);
    static void operator delete(void *arg_0, void *arg_4);
    static void operator delete(void *arg_0);
    // vf_058, as the image's vtable has it (a trivial body, folded into
    // sub_32260 with every other copy).
    virtual RwInt32 vf_058(struct type_3DF8D8_04 *arg_0)
    {
        return 0;
    }
};
typedef RwChar type_3DDE70_size_check[sizeof(type_3DDE70) == 0x3B0 ? 1 : -1];

// Builds the spawn of the trigger arg_0, or warns that there is no entity
// memory for it.
type_3DDE70 *sub_17CB30(ShrimpTrigger *arg_0);

// The shrimps' pool, the list of their holders, the trigger's spawn, and
// set while they are not to be touched (set elsewhere).
extern type_16C2A0 dword_4E7244;
extern struct type_17CC40 *dword_4E7238;
extern RwInt32 dword_4E7240;
// Their clones' light direction (.rdata; sub_123AF0).
extern const RwV3d stru_3DDE60;

RwInt32 sub_17D240();
void sub_17D280();
void sub_17D2B0();
void sub_17D350(struct type_17CC40 *arg_0);
void sub_17D370(RwReal arg_0);

#endif
