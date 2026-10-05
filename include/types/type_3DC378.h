/*
 * type_3DC378: the flak vehicle, an entity class derived from type_3DC048,
 * anchored at its vtable off_3DC378, which sub_15A8C0 installs after
 * off_3DC048 (sub_15A9E0 installs it again). It is the class
 * type_3D3548::vf_018 returns: its slot +0x018 returns this (sub_6FCD0).
 * The "FlakVehicle_" commands address its three crew seats (0 to 2).
 */
#ifndef TYPE_3DC378_H
#define TYPE_3DC378_H

#include "types/type_3DC048.h"

struct type_3DC378 : type_3DC048
{
    RwReal unk_29B0;            // its arc (vf_2EC, and -it vf_2E4)
    RwReal unk_29B4;            // the arc's cosine (vf_2E8)
    type_D48D0 unk_29B8[3];     // its crew (built as an array, the eh
                                // vector iterators with pCtor and pDtor)
    RwInt32 unk_29C4[3];        // their statuses (-1 at first)

    // Built for the trigger arg_0 (out of line, sub_15A8C0; its factory
    // sub_15A7B0 calls it): the tank's bare constructor inlined, its crew,
    // then its set-up.
    type_3DC378(type_712B0 *arg_0);
    // Taken down (vf_230: sub_39440, which only calls the tank's), its
    // crew, then the tank's destructor inlined.
    ~type_3DC378();
    // Empty and out of line (/OPT:ICF folded it into pDtor, 0x1E41C0); the
    // destructor calls it (folded into 0x39440).
    void pDtor();
    // Its set-up: the tank's, flag 0x400000, its arc, its crew and the main
    // gun's tag "RIFA"; it may not move. 1.
    RwInt32 sub_15AA70(type_712B0 *arg_0);

    // +0x038: it may attack only while every crewman its trigger requires
    // is aboard (the loader and third crewman at status 1); then the tank's.
    virtual void vf_038(RwReal arg_0);
    // +0x2F0: as the tank's, without the range.
    virtual RwInt32 vf_2F0(type_3D3548 *arg_0);
    // +0x300: the tank's main gun shot, always 1.
    virtual RwInt32 vf_300(RwInt32 arg_0);
    virtual void vf_230();
    // Inline: the constructor's vtable emits them after it, before ??_G (the image's order).
    virtual RwReal vf_2E4()
    {
        return -unk_29B0;
    }
    virtual RwReal vf_2EC()
    {
        return unk_29B0;
    }
    virtual RwReal vf_2E8()
    {
        return unk_29B4;
    }

    // Seat arg_0's crew member: set it to arg_4, get it, set its status
    // arg_4, and clear it with arg_4 ("FlakVehicle_SetCrewMember" and the
    // like); only the widths are known.
    void sub_15ABA0(RwInt32 arg_0, type_3D3548 *arg_4);
    RwInt32 sub_15AB40(RwInt32 arg_0);
    void sub_15ABE0(RwInt32 arg_0, RwInt32 arg_4);
    void sub_15AC00(RwInt32 arg_0, RwInt32 arg_4);
    // A crewman lost (sub_15AC00 with arg_4): the gunner's seat taken by
    // the third crewman ("AssumeGunnerRole", which also stops its firing),
    // the loader's likewise ("AssumeLoaderRole"), else the gun disabled
    // when its trigger says so (sub_15AE40 tells the crew,
    // "FlakGunDisabled"). The base's vf_2DC (0) gates the takeovers.
    void sub_15ACC0();
    void sub_15AD60();
    void sub_15ADF0();
    void sub_15AE20();
    void sub_15AE40(RwInt32 arg_0);
    RwInt32 sub_15AEE0();
    RwInt32 sub_15AF20();
    RwInt32 sub_15AF60();
    // vf_018, as the image's vtable has it (a trivial body, folded into
    // sub_6FCD0 with every other copy).
    virtual struct type_3DC378 *vf_018()
    {
        return this;
    }
    // vf_2E0, as the image's vtable has it (a trivial body, folded into
    // sub_115460 with every other copy).
    virtual RwInt32 vf_2E0()
    {
        return 1;
    }
    // vf_2DC, as the image's vtable has it: its takeovers are allowed (the
    // base's gives 0); folded into sub_115460 with every other `return 1`.
    virtual RwInt32 vf_2DC()
    {
        return 1;
    }
};

typedef RwChar type_3DC378_size_check[sizeof(type_3DC378) == 0x29D0 ? 1 : -1];

// sub_15A7B0: the flak gun's factory (FlakTrigger's), as sub_155470 is the
// tank's.
struct type_712B0;
type_3DC378 *sub_15A7B0(type_712B0 *arg_0);

#endif
