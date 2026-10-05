/*
 * type_4B85F8: the entity lists, the 16-byte records of dword_4B85F8 (16 of
 * them, named after that array). Each links its entities through
 * type_3D3548::unk_10 (next) and unk_14 (previous), newest first, and gives
 * them its id (unk_24). The database names the head field of the first
 * record, dword_4B8600, as an array of its own (type_4B8600), which the
 * callers that walk a list index.
 */
#ifndef TYPE_4B85F8_H
#define TYPE_4B85F8_H

#include "rw/ostypes.h"

struct type_3D3548;

struct type_4B85F8
{
    RwInt32 unk_00;             // in use
    RwInt32 unk_04;             // its id (0x11 when unused)
    type_3D3548 *unk_08;        // the newest entity
    type_3D3548 *unk_0C;        // the oldest

    // sub_D5170.
    type_4B85F8();
    // Empty, folded (/OPT:ICF) into pDtor (0x1E41C0): the lists' exit
    // function (0x30E3A0) passes it to the vector destructor iterator.
    ~type_4B85F8();
    // An empty method sub_D5480 (Restart) calls on each list, folded by
    // /OPT:ICF into pDtor (0x1E41C0), whose database name it takes.
    void pDtor();
    // Clears the list (sub_D5200 is the same through a call of its own).
    void sub_D5190();
    void sub_D5200();
    // Takes the list into use as number arg_0.
    void sub_D51D0(RwInt32 arg_0);
    // Adds the entity arg_0 at the front, and takes it out.
    void sub_D5220(type_3D3548 *arg_0);
    void sub_D5290(type_3D3548 *arg_0);
};
typedef RwChar type_4B85F8_size_check[sizeof(type_4B85F8) == 0x10 ? 1 : -1];
extern type_4B85F8 dword_4B85F8[16];

// The entity manager (sub_D5320 to sub_D62D0; the image's GameEntityManager,
// from its warnings: sub_D5480 is its Restart, sub_D5570 its Shutdown and
// sub_D61F0 its NotificationOfGodAssetTermination).
extern RwInt32 dword_4B8200;            // set up
extern struct type_3D3548 *dword_4B8204; // the dying entities (through unk_1C)
extern RwInt32 dword_4B8208;
extern struct type_3D3548 *dword_4B820C; // sub_D62D0's picks (through unk_18)
extern RwInt32 dword_4B8210;            // entity zones off (sub_D5E20)
extern RwInt32 dword_4B8214;
extern RwInt32 dword_4B8218;
extern RwInt32 dword_429268;            // the next handle's serial

// Sets the manager up with pool counts arg_0 (nine; the table's when 0).
void sub_D5320(RwInt32 *arg_0);
// Ends and shuts down the level's entities, warning of handles still held
// (sub_D5480 keeps the manager up, sub_D5570 shuts it down).
void sub_D5480();
void sub_D5570();
// Ends every entity not already ending.
void sub_D5650();
// Memory for an entity of arg_0 bytes (a spare one of a bigger pool when
// its own is full, arg_4 allowing that); arg_8 is compared with the
// candidates' triggers' vf_008.
void *sub_D56D0(RwInt32 arg_0, bool arg_4, RwInt32 arg_8);
// Ends the entity arg_0: at once (sub_D5AD0) when arg_4 is not positive,
// else after arg_4 updates on the dying list.
void sub_D5A60(struct type_3D3548 *arg_0, RwInt32 arg_4);
// Frees the entity arg_0: its jiggle, its effects, its list and handle,
// then its destructor and its pool memory.
void sub_D5AD0(struct type_3D3548 *arg_0);
// Adds the entity arg_0 to the list arg_4, and takes it out of its list.
void sub_D5B80(struct type_3D3548 *arg_0, RwInt32 arg_4);
void sub_D5BA0(struct type_3D3548 *arg_0);
// Gives the entity arg_0 a handle; whether one was free.
RwInt32 sub_D5BE0(struct type_3D3548 *arg_0);
// Frees the handle arg_0.
void sub_D5CC0(RwInt32 arg_0);
// Counts the dying entities down, freeing those done (all when arg_0).
void sub_D5D20(RwInt32 arg_0);
// Updates every entity: its trigger's callback (unk_388) when it has one,
// else its update virtuals (vf_038 to vf_04C), then its zone (sub_94060)
// and vf_050, and its jiggle; reports "HitByBulletAssassination" to those
// hit (unk_88_10) from beyond their trigger's range.
void sub_D5E20();
// The entity's zone: the smallest around it (type_3D3548::unk_90).
void sub_94060(struct type_3D3548 *arg_0);

// Ends the entities whose vf_058 matches arg_0.
void sub_D61F0(struct type_3DF8D8_04 *arg_0);
// Links the entities whose vf_000 accepts arg_0 through unk_18 from
// dword_4B820C (list 14 aside).
void sub_D62D0(void *arg_0);
// Resets the debris states (unk_4B8220).
void sub_D6350();

// The entity's slot +4 is its scalar deleting destructor, and sub_D5AD0
// deletes the entity through it (`delete` expands to the null test and the
// call with 1). type_3D3548 still declares that slot as vf_004, with its
// destructor (sub_73850, binary) not virtual, so the delete goes through
// this stand-in, which has the destructor in the same slot. It is never
// constructed, so it emits no vtable.
struct type_D5AD0
{
    virtual void vf_000();
    virtual ~type_D5AD0();
};

// A 4-byte slot of the pool sub_D63A0 walks: its first byte marks it taken.
struct type_D63A0
{
    RwUInt8 unk_00;
    RwUInt8 unk_01;
    RwInt16 unk_02;
};

#endif
